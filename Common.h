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
