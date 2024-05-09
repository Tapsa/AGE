#include "Common.h"
#include "AboutDialog.h"
#include "AppIcon64.xpm"
#include "CustomWidgets.h"
#include "Licenses/boost.h"
#include "Licenses/GPLv3.h"
#include "Licenses/LGPLv2.h"
#include "Licenses/liblz4.h"
#include "Licenses/SFML.h"
#include "Licenses/wxWidgets.h"

const wxString AboutDialog::AGE_VER = "2024.5.9";

AboutDialog::AboutDialog(wxWindow *parent, const wxFont &font)
    : wxDialog(parent, -1, "About Advanced Genie Editor", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxNO_DEFAULT)
{
    SetFont(font);
    SolidText *Title = new SolidText(this, "Advanced Genie Editor\nVersion " + AGE_VER +
        "\nGPLv3 2011 - 2024\n\nDevelopers:"
        "\nMikko Tapio Partonen (Tapsa), since 2.0b (2011)"
        "\nManuel Winocur, since 2023"
        "\nArmin Preiml (Apre) - genieutils, from 2011 to 2013"
        "\nEstien Nifo (StSB77), from 1.0a to 2.0a");
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
        "\nOpen Audio Library - GNU Library General Public License, Version 2, June 1991"
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
    wxSizer *Buttons = new wxGridSizer(5, 2, 2);
    wxButton *ButtonBoost = new wxButton(this, wxID_ANY, "boost");
    wxButton *ButtonGPLv3 = new wxButton(this, wxID_ANY, "GPLv3");
    wxButton *ButtonLGPLv2 = new wxButton(this, wxID_ANY, "LGPLv2");
    wxButton *ButtonLz4 = new wxButton(this, wxID_ANY, "lz4");
    wxButton *ButtonSFML = new wxButton(this, wxID_ANY, "SFML");
    wxButton *ButtonWx = new wxButton(this, wxID_ANY, "wxWidgets");
    wxButton *ButtonOK = new wxButton(this, wxID_OK, "All right");

    ButtonGPLv3->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [](wxCommandEvent &)
    {
        wxMessageBox(licenseGPLv3, "GNU General Public License, Version 3, 29 June 2007");
    });
    ButtonLGPLv2->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [](wxCommandEvent &)
    {
        wxMessageBox(licenseLGPLv2, "GNU Library General Public License, Version 2, June 1991");
    });
    ButtonLz4->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [](wxCommandEvent &)
    {
        wxMessageBox(licenseLZ4, "lz4 - BSD 2-Clause License");
    });
    ButtonWx->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [](wxCommandEvent &)
    {
        wxMessageBox(licenseWx, "wxWindows Library Licence, Version 3.1, 2005");
    });
    ButtonBoost->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [](wxCommandEvent &)
    {
        wxMessageBox(licenseBoost, "Boost Software License, Version 1.0, 17 August 2003");
    });
    ButtonSFML->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [](wxCommandEvent &)
    {
        wxMessageBox(licenseSFML, "SFML - zlib/libpng License");
    });

    Buttons->Add(ButtonBoost);
    Buttons->Add(ButtonGPLv3);
    Buttons->Add(ButtonLGPLv2);
    Buttons->Add(ButtonLz4);
    Buttons->Add(ButtonSFML);
    Buttons->Add(ButtonWx);
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
