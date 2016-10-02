#include "Common.h"

class AGE_AboutDialog: public wxDialog
{
	public:

	AGE_AboutDialog(wxWindow *parent, const wxFont &font);

//	Member Variables

	SolidText *Title;
	wxStaticBitmap *Image;
	SolidText *Credits;
	wxHyperlinkCtrl *AoKHThread; //http://aok.heavengames.com/cgi-bin/aokcgi/display.cgi?action=ct&f=4,38606,0,365
	//SolidText *UPXInfo;
	//wxHyperlinkCtrl *UPXLink; //http://upx.sourceforge.net/

	wxBoxSizer *MainRight;
	wxBoxSizer *MainAbout;

	static const wxString AGE_VER;
};
