/* AGE_AboutDialog.h */

#include "wx/wx.h"
#include "wx/hyperlink.h"
#include "AboutIcon.xpm"

class AGE_AboutDialog: public wxDialog
{
	public:

	AGE_AboutDialog(wxWindow *parent);
	
//	Member Variables
	
	wxStaticText * Title;
	wxStaticBitmap * Image;
	wxStaticText * Credits;
	wxHyperlinkCtrl * AoKHThread; //http://aok.heavengames.com/cgi-bin/aokcgi/display.cgi?action=ct&f=4,38606,0,365
	wxStaticText * UPXInfo;
	wxHyperlinkCtrl * UPXLink; //http://upx.sourceforge.net/
	
	wxBoxSizer * MainLeft;
	wxBoxSizer * MainRight;
	wxBoxSizer * MainAbout;
};

/*#ifndef AGEStorage_h
#define AGEStorage_h

class AGE_Storage
{
	public:

	AGE_Storage();
	
//	Member Functions
	
	bool Save();
	bool Undo();
	bool Redo();
	bool Release();
	
//	Member Variables
	deque<short> Saves;
};

#endif*/
