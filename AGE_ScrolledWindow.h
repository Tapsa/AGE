/* AGE_ScrolledWindow.h */

#include "wx/wx.h"
//#include "wx/window.h"

#ifndef AGEScrolledWindow_h
#define AGEScrolledWindow_h

class AGE_ScrolledWindow : public wxScrolledWindow
{
	public:
	
	AGE_ScrolledWindow(wxWindow * parent, long style);
	
	/* Event Methods */
	
	void OnSize(wxSizeEvent& Event);
};

#endif
