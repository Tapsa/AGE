#include <string>
#include <array>
#include <vector>
#include <list>
#include <forward_list>
#include <map>
#include <set>
//#include <regex>
//#include <atomic>
#include <thread>
#include <iomanip>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <wx/wx.h>
#include <wx/aboutdlg.h>
#include <wx/collpane.h>
#include <wx/fileconf.h>
#include <wx/filename.h>
#include <wx/filepicker.h>
#include <wx/hyperlink.h>
#include <wx/notebook.h>
#include <wx/odcombo.h>
#include <wx/listctrl.h>
#include <wx/tooltip.h>
#include <wx/timer.h>
#include <wx/image.h>
#include <wx/dcbuffer.h>

// uncomment to disable assert()
// #define NDEBUG
#include <cassert>

#ifdef WIN32
#include <windows.h>
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
#include "genie/dat/DatFile.h"	// Newer dat system
#include "genie/lang/LangFile.h"
using namespace std;
using boost::lexical_cast;
using boost::bad_lexical_cast;

#ifndef COMMON_H
#define COMMON_H

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
	EV_AoKA,
	EV_AoKB,
	EV_AoK,
	EV_TC,
	EV_Cysion,
	EV_SWGB,
	EV_CC
};

enum ContainerType {CByte, CUByte, CFloat, CLong, CShort, CUShort, CString};

#endif
