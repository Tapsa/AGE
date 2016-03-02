#include "Common.h"

class AGE_AboutDialog: public wxDialog
{
	public:

	AGE_AboutDialog(wxWindow *parent, const wxFont &font);

//	Member Variables

	wxStaticText *Title;
	wxStaticBitmap *Image;
	wxStaticText *Credits;
	wxHyperlinkCtrl *AoKHThread; //http://aok.heavengames.com/cgi-bin/aokcgi/display.cgi?action=ct&f=4,38606,0,365
	//wxStaticText *UPXInfo;
	//wxHyperlinkCtrl *UPXLink; //http://upx.sourceforge.net/

	wxBoxSizer *MainRight;
	wxBoxSizer *MainAbout;

	static const wxString AGE_VER;
};

/*class AGE_HelpInfo: public wxDialog
{
	public:

	AGE_HelpInfo(wxWindow *parent);

	wxBoxSizer *Main;
	wxStaticText *MainInfo;
	wxCollapsiblePane *AdvancedSearching;
	wxBoxSizer *AdvSearch;
	wxStaticText *AdvSearchInfo;
	wxCollapsiblePane *BatchEditing;
	wxBoxSizer *BatchEdit;
	wxStaticText *BatchEditInfo;
	wxCollapsiblePane *CrossWindowsMassCopying;
	wxBoxSizer *MassCopy;
	wxStaticText *MassCopyInfo;
	wxCollapsiblePane *ForDiscoveringUnknowns;
	wxBoxSizer *Unknowns;
	wxStaticText *UnknownsInfo;
};*/
