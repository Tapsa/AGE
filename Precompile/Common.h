#pragma once
// All headers in this header should be precompiled

// Standard
#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <functional>
#include <iomanip>
#include <ios>
#include <list>
#include <map>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// Win32
#ifdef WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <psapi.h>
#endif

// boost
#include <boost/lexical_cast.hpp>

// wxWidgets
#include <wx/app.h>
#include <wx/arrstr.h>
#include <wx/bitmap.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/clrpicker.h>
#include <wx/config.h>
#include <wx/dc.h>
#include <wx/dcbuffer.h>
#include <wx/dialog.h>
#include <wx/dir.h>
#include <wx/display.h>
#include <wx/event.h>
#include <wx/ffile.h>
#include <wx/fileconf.h>
#include <wx/filename.h>
#include <wx/filepicker.h>
#include <wx/frame.h>
#include <wx/hyperlink.h>
#include <wx/log.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>
#ifdef WIN32
#include <wx/msw/registry.h>
#endif
#include <wx/notebook.h>
#include <wx/odcombo.h>
#include <wx/panel.h>
#include <wx/radiobox.h>
#include <wx/renderer.h>
#include <wx/scrolwin.h>
#include <wx/sizer.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/stdpaths.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/textdlg.h>
#include <wx/timer.h>
#include <wx/tokenzr.h>
#include <wx/toolbar.h>
#include <wx/vlbox.h>
#include <wx/window.h>
#include <wx/wrapsizer.h>

// Simple and Fast Multimedia Library
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

using boost::lexical_cast;
using boost::bad_lexical_cast;
