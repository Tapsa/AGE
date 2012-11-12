#include "Common.h"
#include "AboutIcon.xpm"

class AGE_AboutDialog: public wxDialog
{
	public:

	AGE_AboutDialog(wxWindow *parent);

//	Member Variables

	wxStaticText *Title;
	wxStaticBitmap *Image;
	wxStaticText *Credits;
	wxHyperlinkCtrl *AoKHThread; //http://aok.heavengames.com/cgi-bin/aokcgi/display.cgi?action=ct&f=4,38606,0,365
	wxStaticText *UPXInfo;
	wxHyperlinkCtrl *UPXLink; //http://upx.sourceforge.net/

	wxBoxSizer *MainLeft;
	wxBoxSizer *MainRight;
	wxBoxSizer *MainAbout;
};
