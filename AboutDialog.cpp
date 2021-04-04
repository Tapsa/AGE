#include "Common.h"
#include "AboutDialog.h"
#include "AppIcon64.xpm"
#include "CustomWidgets.h"
#include "License GPLv3.h"
#include "License liblz4.h"

const wxString AboutDialog::AGE_VER = "2021.4.4";

AboutDialog::AboutDialog(wxWindow *parent, const wxFont &font)
    : wxDialog(parent, -1, "About Advanced Genie Editor", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxNO_DEFAULT)
{
    SetFont(font);
    SolidText *Title = new SolidText(this, "Advanced Genie Editor\nVersion " + AGE_VER +
        "\nGPLv3 2011 - 2021\n\nDevelopers:\nMikko \"Tapsa\" P, since 2.0b\nApre - genieutils, 2.1a to 3.1"
        "\nEstien Nifo aka StSB77, 1.0a to 2.0a");
    wxStaticBitmap *Image = new wxStaticBitmap(this, wxID_ANY, wxBitmap(AppIcon64_xpm));
    SolidText *Credits = new SolidText(this, "Credits:\nYkkrosh - GeniEd 1 source code"
        "\nScenario_t_c - GeniEd 2 source code\nAlexandra \"Taichi San\", DarkRain654 - data file research"
        "\nDiGiT, JustTesting1234, AOHH - genie file structure\nCysion, Kris, Sarthos - important help"
        "\nTevious - SMX support\nGrenadier (RvA) - terrain patch\nwithmorten - UserPatch effect support"
        "\nBF_Tanks - some help\nDonnieboy, Sarn, chab - tooltip texts\ngagman - new icon");
    SolidText *LibCredits = new SolidText(this, "Libraries used:"
        "\nwxWidgets - wxWindows Library Licence, Version 3.1, 2005"
        "\nboost - Boost Software License, Version 1.0, 17 August 2003"
        "\nSimple and Fast Multimedia Library - zlib/libpng License"
        "\nlibiconv - GNU General Public License, Version 3, 29 June 2007"
        "\nlz4 - BSD 2-Clause License");
    wxHyperlinkCtrl *AoKHThread = new wxHyperlinkCtrl(this, wxID_ANY, "Age of Kings Heaven AGE forum topic",
        "http://aok.heavengames.com/cgi-bin/forums/display.cgi?action=st&fn=9&tn=44059&st=recent&f=9,44059,0,365",
        wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxHL_CONTEXTMENU | wxHL_ALIGN_LEFT);
    wxHyperlinkCtrl *SourceLinkGUI = new wxHyperlinkCtrl(this, wxID_ANY, "Tapsa/AGE on GitHub",
        "https://github.com/Tapsa/AGE", wxDefaultPosition, wxDefaultSize,
        wxNO_BORDER | wxHL_CONTEXTMENU | wxHL_ALIGN_LEFT);
    wxHyperlinkCtrl *SourceLinkFIO = new wxHyperlinkCtrl(this, wxID_ANY, "Tapsa/genieutils on GitHub",
        "https://github.com/Tapsa/genieutils", wxDefaultPosition, wxDefaultSize,
        wxNO_BORDER | wxHL_CONTEXTMENU | wxHL_ALIGN_LEFT);

    wxBoxSizer *MainRight = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *MainAbout = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *Buttons = new wxBoxSizer(wxHORIZONTAL);
    wxButton *ButtonOK = new wxButton(this, wxID_OK, "All right");
    wxButton *ButtonGPLv3 = new wxButton(this, wxID_ANY, "GPLv3");
    wxButton *ButtonLz4 = new wxButton(this, wxID_ANY, "lz4");

    ButtonGPLv3->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [](wxCommandEvent &)
    {
        wxMessageBox(licenseGPLv3, "GNU General Public License, Version 3, 29 June 2007");
    });
    ButtonLz4->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [](wxCommandEvent &)
    {
        wxMessageBox(licenseLZ4, "lz4 - BSD 2-Clause License");
    });

    Buttons->Add(ButtonGPLv3);
    Buttons->Add(ButtonLz4);
    Buttons->Add(ButtonOK);
    MainRight->Add(Title, 1, wxEXPAND);
    MainRight->Add(Image);
    MainAbout->Add(MainRight, 0, wxALL, 10);
    MainAbout->Add(Credits, 0, wxALL - wxUP, 10);
    MainAbout->Add(AoKHThread, 0, wxRIGHT | wxLEFT, 10);
    MainAbout->Add(SourceLinkGUI, 0, wxRIGHT | wxLEFT, 10);
    MainAbout->Add(SourceLinkFIO, 0, wxRIGHT | wxLEFT, 10);
    MainAbout->Add(LibCredits, 0, wxALL, 10);
    MainAbout->Add(Buttons, 0, wxALIGN_RIGHT | wxALL, 5);

    SetSizerAndFit(MainAbout);

    ButtonOK->SetDefault();
    ButtonOK->SetFocus();
}
