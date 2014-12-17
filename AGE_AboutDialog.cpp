#include "AGE_AboutDialog.h"
#include "AboutIcon.xpm"

const wxString AGE_AboutDialog::AGE_VER = "3.14";

AGE_AboutDialog::AGE_AboutDialog(wxWindow *parent)
: wxDialog(parent, -1, "About Advanced Genie Editor", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxNO_DEFAULT)
{
	Title = new wxStaticText(this, wxID_ANY, "Advanced Genie Editor\nVersion "+AGE_VER+"\nCopyleft 2011 - 2014\n\nDevelopers:\nMikko \"Tapsa\" P, since 2.0b\nApre - genieutils, 2.1a to 3.1\nEstien Nifo aka StSB77, 1.0a to 2.0a");
	Image = new wxStaticBitmap(this, wxID_ANY, wxBitmap(AboutIcon_xpm));
	Credits = new wxStaticText(this, wxID_ANY, "Credits:\nYkkrosh - GeniEd 1 source code\nScenario_t_c - GeniEd 2 source code\nAlexandra \"Taichi San\", DarkRain654 - data file research\nDiGiT, JustTesting1234 - genie file structure\nSarthos - important help\nBF_Tanks - some help\nDonnieboy, Sarn, chab - tooltip texts\nLeif Ericson - new icon");
	AoKHThread = new wxHyperlinkCtrl(this, wxID_ANY, "Age of Kings Heaven AGE forum topic", "http://aok.heavengames.com/cgi-bin/aokcgi/display.cgi?action=st&fn=4&tn=41300&st=recent&f=4,41300,0,365", wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxHL_CONTEXTMENU | wxHL_ALIGN_LEFT);
	UPXInfo = new wxStaticText(this, wxID_ANY, "Compressed with:");
	UPXLink = new wxHyperlinkCtrl(this, wxID_ANY, "The Ultimate Packer for eXecutables", "http://upx.sourceforge.net", wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxHL_CONTEXTMENU | wxHL_ALIGN_LEFT);

	MainLeft = new wxBoxSizer(wxVERTICAL);
	MainRight = new wxBoxSizer(wxVERTICAL);
	MainAbout = new wxBoxSizer(wxHORIZONTAL);

	MainLeft->Add(-1, 15);
	MainLeft->Add(Image, 0, 0);
	MainLeft->Add(-1, 15);

	MainRight->Add(-1, 15);
	MainRight->Add(Title, 0, wxEXPAND);
	MainRight->Add(-1, 15);
	MainRight->Add(Credits, 1, wxEXPAND);
	MainRight->Add(-1, 15);
	MainRight->Add(AoKHThread, 0, wxEXPAND);
	MainRight->Add(-1, 15);
	MainRight->Add(UPXInfo, 0, wxEXPAND);
	MainRight->Add(UPXLink, 0, wxEXPAND);
	MainRight->Add(-1, 15);

	MainAbout->Add(15, -1);
	MainAbout->Add(MainLeft, 0, wxEXPAND);
	MainAbout->Add(15, -1);
	MainAbout->Add(MainRight, 1, wxEXPAND);
	MainAbout->Add(15, -1);

	SetSizerAndFit(MainAbout);
}

/*AGE_HelpInfo::AGE_HelpInfo(wxWindow *parent)
: wxDialog(parent, -1, "Short Guide to Advanced Editing", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxNO_DEFAULT)
{
	Main = new wxBoxSizer(wxVERTICAL);

	AdvancedSearching = new wxCollapsiblePane(this, wxID_ANY, "Advanced Searching");
	BatchEditing = new wxCollapsiblePane(this, wxID_ANY, "Batch Editing");
	CrossWindowsMassCopying = new wxCollapsiblePane(this, wxID_ANY, "Cross-windows Mass Copying");
	ForDiscoveringUnknowns = new wxCollapsiblePane(this, wxID_ANY, "For Discovering Unknowns");

	AdvSearch = new wxBoxSizer(wxVERTICAL);
	BatchEdit = new wxBoxSizer(wxVERTICAL);
	MassCopy = new wxBoxSizer(wxVERTICAL);
	Unknowns = new wxBoxSizer(wxVERTICAL);

	MainInfo = new wxStaticText(this, wxID_ANY, "LOL it's a test!");
	AdvSearchInfo = new wxStaticText(this, wxID_ANY, "LOL it's a test!");
	BatchEditInfo = new wxStaticText(this, wxID_ANY, "LOL it's a test!");
	MassCopyInfo = new wxStaticText(this, wxID_ANY, "LOL it's a test!");
	UnknownsInfo = new wxStaticText(this, wxID_ANY, "LOL it's a test!");

	AdvSearch->Add(AdvSearchInfo, 1, wxEXPAND);
	AdvancedSearching->SetSizer(AdvSearch);

	BatchEdit->Add(BatchEditInfo, 1, wxEXPAND);
	BatchEditing->SetSizer(BatchEdit);

	MassCopy->Add(MassCopyInfo, 1, wxEXPAND);
	CrossWindowsMassCopying->SetSizer(MassCopy);

	Unknowns->Add(UnknownsInfo, 1, wxEXPAND);
	ForDiscoveringUnknowns->SetSizer(Unknowns);

	Main->Add(MainInfo, 1, wxEXPAND);
	Main->Add(-1, 5);
	Main->Add(AdvancedSearching, 0, wxEXPAND);
	Main->Add(-1, 5);
	Main->Add(BatchEditing, 0, wxEXPAND);
	Main->Add(-1, 5);
	Main->Add(CrossWindowsMassCopying, 0, wxEXPAND);
	Main->Add(-1, 5);
	Main->Add(ForDiscoveringUnknowns, 0, wxEXPAND);

	SetSizerAndFit(Main);
}*/
