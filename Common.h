#pragma once
#include <string>
#include <array>
#include <vector>
//#include <list>
//#include <forward_list>
#include <map>
#include <set>
//#include <regex>
//#include <atomic>
#include <thread>
#include <iomanip>
#include <functional>
#include <SFML/Audio.hpp>
#include <wx/wx.h>
#include <wx/aboutdlg.h>
//#include <wx/collpane.h>
#include <wx/config.h>
#include <wx/fileconf.h>
#include <wx/filename.h>
#include <wx/filepicker.h>
#include <wx/ffile.h>
#include <wx/hyperlink.h>
#include <wx/notebook.h>
#include <wx/odcombo.h>
//#include <wx/listctrl.h>
#include <wx/tooltip.h>
#include <wx/timer.h>
#include <wx/image.h>
#include <wx/dcbuffer.h>
#include <wx/dir.h>
//#include <wx/sound.h>
#include <wx/clrpicker.h>
#include <wx/thread.h>
#include <wx/accel.h>
#include <wx/tokenzr.h>
#include <wx/wrapsizer.h>
#include <wx/stdpaths.h>

// For getting the config directory path
// I wish anything other than wxwidgets was used..
#if defined(__linux__)
#include <filesystem>
#endif

// uncomment to disable assert()
// #define NDEBUG
#include <cassert>

#ifdef WIN32
#include <wx/msw/registry.h>
#include <windows.h>
#include <psapi.h>
#else
// dummies for code that is not used on linux
#define HINSTANCE ssize_t
#define LoadStringA(lib, id, buf, letters) (false)
#define LoadLibrary(name) (0)
#endif

#include "genie/script/ScnFile.h"
#include "genie/resource/Color.h"
#include "genie/resource/SlpFrame.h"
#include "genie/resource/DrsFile.h"
#include "genie/dat/DatFile.h"  // Newer dat system
#include "genie/lang/LangFile.h"
using namespace std;

typedef std::unique_ptr<wxConfig> ConfigPtr;
// Have to be unique_ptr because wxConfig is utter garbage
static inline ConfigPtr getConfig(const std::string &name)
{
    ConfigPtr LocalConfig(new wxConfig("", "", name, "", wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH | wxCONFIG_USE_SUBDIR ));

#if defined (__linux__)
    // Holy shit wxwidgets is crap
    // This has been a standard for, what, 15 years?
    std::string globalPath;
    char *rawPath = getenv("XDG_CONFIG_HOME");
    if (rawPath) {
        globalPath = std::string(rawPath);
    }
    if (globalPath.empty()) {
        rawPath = getenv("HOME");
        if (rawPath) {
            globalPath = getenv("HOME");
            globalPath += "/.config";
        }
    } else if (globalPath.find(':') != std::string::npos) {
        std::istringstream stream(globalPath);
        std::string testPath;
        while (std::getline(stream, testPath, ':')) {
            if (!std::filesystem::exists(testPath)) {
                continue;
            } if (!std::filesystem::is_directory(testPath)) {
                continue;
            }

            globalPath = testPath;
            break;
        }
    }

    globalPath += "/AdvancedGenieEditor/";
    if (!std::filesystem::exists(globalPath)) {
        std::filesystem::create_directory(globalPath);
    }

    std::string::size_type backslashPos = name.find("\\");
    if (backslashPos != std::string::npos) {
        globalPath += name.substr(backslashPos + 1);
    } else {
        globalPath += name;
    }

    globalPath += ".ini";

    if (!std::filesystem::exists(globalPath) && LocalConfig->GetNumberOfEntries(true) > 0) {
        std::cout << "Copying in old " << globalPath << std::endl;
        std::error_code copyError;
        if (!std::filesystem::copy_file(name, globalPath, copyError)) {
            std::cerr << "Failed to copy in old config " << copyError.message() << std::endl;
            return LocalConfig;
        }
    }

    ConfigPtr GlobalConfig(new wxConfig("", "", globalPath, "", wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH | wxCONFIG_USE_SUBDIR ));
    const int globalEntryCount = GlobalConfig->GetNumberOfEntries(true);
    const int localEntryCount = LocalConfig->GetNumberOfEntries(true);

    if (localEntryCount > 0 && globalEntryCount != localEntryCount) {
        std::cerr << "Warning: Inconsistent number of entries in local config " << name << " (" << localEntryCount << " and global config " << globalPath << " (" << globalEntryCount << ")" << std::endl;
    }
    return GlobalConfig;
#else
    return LocalConfig;
#endif
}

class DelayedPopUp
{
public:
    bool hasMessage = false, hexMode = false, accurateFloats = false;
    wxString popUpMessage, popUpTitle;
    wxWindow *focusTarget = 0;
    int unSaved = 0, loadedFileId = 0;

    void post(const wxString &message, const wxString &title, wxWindow *target)
    {
        popUpTitle = title;
        popUpMessage = message;
        focusTarget = target;
        hasMessage = true;
    }
};

enum EditableVersion
{
    EV_ORIG,
    EV_TEST,
    EV_MIK,
    EV_DAVE,
    EV_MATT,
    EV_AoEB,
    EV_AoE,
    EV_RoR,
    EV_AoKE3,
    EV_AoKA,
    EV_AoKB,
    EV_AoK,
    EV_TC,
    EV_Cysion,
    EV_SWGB,
    EV_CC,
    EV_EF,
    EV_Tapsa
};

enum ContainerType {CByte, CUByte, CFloat, CLong, CShort, CUShort, CString};

class SolidText: public wxStaticText
{
public:
    SolidText(wxWindow *parent, const wxString &label, long style = 0, const wxSize &size = wxDefaultSize):
    wxStaticText(parent, wxID_ANY, label, wxDefaultPosition, size, style)
    {
        Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent&){});
    }
};

class APanel: public wxPanel
{
public:
    APanel(): wxPanel() {fixes();}
    APanel(wxWindow *parent, const wxSize &size = wxDefaultSize):
    wxPanel(parent, wxID_ANY, wxDefaultPosition, size) {fixes();}

private:
    // Prevent jumping back to last focused child or sibling
    void fixes()
    {
        Bind(wxEVT_CHILD_FOCUS, [](wxChildFocusEvent&){}); // No scrolling
        Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent&){SetFocusIgnoringChildren();});
    }
};

class AScrolled: public wxScrolled<APanel>
{
public:
    AScrolled(wxWindow *parent):
    wxScrolled<APanel>(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxTAB_TRAVERSAL)
    {
        // Smooth scrolling
        Bind(wxEVT_MOUSEWHEEL, [this](wxMouseEvent &event)
        {
            GetViewStart(&pos, &pos);
            Scroll(0, event.GetWheelRotation() < 0 ? pos + 3 : max(pos - 3, 0));
        });
    }

    int pos;
};
