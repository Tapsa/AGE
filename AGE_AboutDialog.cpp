#include "AGE_AboutDialog.h"
#include "AboutIcon.xpm"

const wxString AGE_AboutDialog::AGE_VER = "2015.12.17";

AGE_AboutDialog::AGE_AboutDialog(wxWindow *parent)
: wxDialog(parent, -1, "About Advanced Genie Editor", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxNO_DEFAULT)
{
    Title = new wxStaticText(this, wxID_ANY, "Advanced Genie Editor\nVersion "+AGE_VER+"\nGPLv3 2011 - 2015\n\nDevelopers:\nMikko \"Tapsa\" P, since 2.0b\nApre - genieutils, 2.1a to 3.1\nEstien Nifo aka StSB77, 1.0a to 2.0a");
    Image = new wxStaticBitmap(this, wxID_ANY, wxBitmap(AboutIcon_xpm));
    Credits = new wxStaticText(this, wxID_ANY, "Credits:\nYkkrosh - GeniEd 1 source code\nScenario_t_c - GeniEd 2 source code\nAlexandra \"Taichi San\", DarkRain654 - data file research\nDiGiT, JustTesting1234, AOHH - genie file structure\nCysion, Skybox Labs, Sarthos - important help\nBF_Tanks - some help\nDonnieboy, Sarn, chab - tooltip texts\nLeif Ericson - new icon");
    AoKHThread = new wxHyperlinkCtrl(this, wxID_ANY, "Age of Kings Heaven AGE forum topic", "http://aok.heavengames.com/cgi-bin/forums/display.cgi?action=st&fn=9&tn=44059&st=recent&f=9,44059,0,365", wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxHL_CONTEXTMENU | wxHL_ALIGN_LEFT);
    //UPXInfo = new wxStaticText(this, wxID_ANY, "Compressed with:");
    //UPXLink = new wxHyperlinkCtrl(this, wxID_ANY, "The Ultimate Packer for eXecutables", "http://upx.sourceforge.net", wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxHL_CONTEXTMENU | wxHL_ALIGN_LEFT);

    MainRight = new wxBoxSizer(wxVERTICAL);
    MainAbout = new wxBoxSizer(wxHORIZONTAL);

    MainRight->Add(Title, 0, wxEXPAND);
    MainRight->Add(Credits, 1, wxEXPAND | wxTOP | wxBOTTOM, 15);
    MainRight->Add(AoKHThread, 0, wxEXPAND);
    //MainRight->Add(UPXInfo, 0, wxEXPAND);
    //MainRight->Add(UPXLink, 0, wxEXPAND);

    MainAbout->Add(Image, 0, wxALL, 15);
    MainAbout->Add(MainRight, 1, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 15);

    SetSizerAndFit(MainAbout);
}
