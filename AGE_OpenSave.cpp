#include "AGE_OpenSave.h"

AGE_OpenSave::AGE_OpenSave(wxWindow *parent, const wxString &title, wxDialog *slave, const wxFont &font)
: wxDialog(parent, -1, title+" files...", wxDefaultPosition, wxSize(500, 250), wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxNO_DEFAULT)
{
    SetFont(font);
    Layout = new wxFlexGridSizer(2, 2, 2);
    ForceDat = false;
    Main = new wxBoxSizer(wxVERTICAL);
    wxStaticText *Defaults_Label = new wxStaticText(slave, wxID_ANY, " Defaults: ");
    Defaults = new wxBoxSizer(wxHORIZONTAL);
    Defaults_StarWars = new wxBoxSizer(wxHORIZONTAL);
    Buttons = new wxBoxSizer(wxHORIZONTAL);
    Radio_DatFileLocation = new AGE_PairedCheckBox(slave, "Compressed data set (*.dat):", (wxWindow**)&Path_DatFileLocation);

    ButtonOK = new wxButton(slave, wxID_OK, title);
    ButtonCancel = new wxButton(slave, wxID_CANCEL, "Cancel");
    Gift = new wxHyperlinkCtrl(slave, wxID_ANY, "Donate to Tapsa", "https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=4JDUUTF6B9HFN&lc=FI&item_name=Helping%20Tapsa&currency_code=EUR&bn=PP%2dDonationsBF%3abtn_donate_SM%2egif%3aNonHostedGuest");
    Buttons->Add(Gift, 0, wxLEFT | wxRIGHT, 15);
    Buttons->Add(ButtonOK);
    Buttons->Add(ButtonCancel);

    Button_DefaultAoE = new wxButton(slave, wxID_ANY, "Age of Empires");
    Button_DefaultRoR = new wxButton(slave, wxID_ANY, "Rise of Rome");
    Button_DefaultAoK = new wxButton(slave, wxID_ANY, "Age of Kings");
    Button_DefaultTC = new wxButton(slave, wxID_ANY, "The Conquerors");
    Button_DefaultAoKHD = new wxButton(slave, wxID_ANY, "Age of Empires II: HD");
    Button_DefaultAP = new wxButton(slave, wxID_ANY, "The Forgotten + The African Kingdoms");
    Button_DefaultSWGB = new wxButton(slave, wxID_ANY, "Star Wars: Galactic Battlegrounds");
    Button_DefaultCC = new wxButton(slave, wxID_ANY, "Clone Campaigns");
#ifdef WIN32
    Button_PathFromRegistry = new wxButton(slave, wxID_ANY, "Fill paths from registry");
#endif

    Defaults->Add(Defaults_Label);
    Defaults->Add(Button_DefaultAoE, 0, wxEXPAND);
    Defaults->Add(Button_DefaultRoR, 0, wxEXPAND);
    Defaults->Add(Button_DefaultAoK, 0, wxEXPAND);
    Defaults->Add(Button_DefaultTC, 0, wxEXPAND);
    Defaults->Add(Button_DefaultAoKHD, 0, wxEXPAND);
    Defaults->Add(Button_DefaultAP, 0, wxEXPAND | wxRIGHT, 50);
    Defaults_StarWars->Add(Button_DefaultSWGB, 0, wxEXPAND | wxLEFT, 50);
    Defaults_StarWars->Add(Button_DefaultCC, 0, wxEXPAND);

    wxStaticText *Text_GenieVer = new wxStaticText(slave, wxID_ANY, "      Genie version:");
    CheckBox_GenieVer = new wxChoice(slave, wxID_ANY, wxDefaultPosition, wxSize(256, -1));
    CheckBox_GenieVer->Append("TEST");
    CheckBox_GenieVer->Append("TEST.DAT");
    CheckBox_GenieVer->Append("MICKEY.DAT");
    CheckBox_GenieVer->Append("DAVE.DAT");
    CheckBox_GenieVer->Append("MATT.DAT < 6.92");
    CheckBox_GenieVer->Append("Age of Empires Beta (7.04 - 7.11)");
    CheckBox_GenieVer->Append("Age of Empires (7.2)");
    CheckBox_GenieVer->Append("Rise of Rome (7.24)");
    CheckBox_GenieVer->Append("Age of Kings Alpha (10.19)");
    CheckBox_GenieVer->Append("Age of Kings Beta (11.05)");
    CheckBox_GenieVer->Append("Age of Kings (11.5)");
    CheckBox_GenieVer->Append("The Conquerors (11.76)");
    CheckBox_GenieVer->Append("The Forgotten + The African Kingdoms > 12");
    CheckBox_GenieVer->Append("Star Wars: Galactic Battlegrounds (1.0)");
    CheckBox_GenieVer->Append("Clone Campaigns (1.1)");
    CheckBox_GenieVer->Append("Mod: Expanding Fronts");
    CheckBox_GenieVer->SetSelection(EV_TC);
    wxStaticText *RecentText = new wxStaticText(slave, wxID_ANY, "      Recent paths:");
    CheckBox_Recent = new wxChoice(slave, wxID_ANY);

    wxStaticText *DriveText = new wxStaticText(this, wxID_ANY, "      Drive letter:");
    DriveLetterBox = new wxTextCtrl(slave, wxID_ANY, "C", wxDefaultPosition, wxSize(50, -1));
    wxStaticText *LanguageText = new wxStaticText(this, wxID_ANY, " Language: * ");
    LanguageBox = new wxTextCtrl(slave, wxID_ANY, "en", wxDefaultPosition, wxSize(50, -1));
    LanguageBox->SetToolTip("For AoK HD paths");
    Extras = new wxBoxSizer(wxHORIZONTAL);
    CheckBox_CustomDefault = new AGE_PairedCheckBox(slave, "Custom path override:", (wxWindow**)&Path_CustomDefault);
    Path_CustomDefault = new wxDirPickerCtrl(slave, wxID_ANY, "", "Select a folder", wxDefaultPosition, wxDefaultSize, wxDIRP_USE_TEXTCTRL | wxDIRP_DIR_MUST_EXIST);
    wxSizer *sizer1 = new wxBoxSizer(wxHORIZONTAL);
    wxSizer *sizer2 = new wxBoxSizer(wxHORIZONTAL);

    CheckBox_LangFileLocation = new AGE_PairedCheckBox(slave, "Language file location:", (wxWindow**)&Path_LangFileLocation);
    CheckBox_LangX1FileLocation = new AGE_PairedCheckBox(slave, "Language x1 file location:", (wxWindow**)&Path_LangX1FileLocation);
    CheckBox_LangX1P1FileLocation = new AGE_PairedCheckBox(slave, "Language p1 file location:", (wxWindow**)&Path_LangX1P1FileLocation);

    Layout->Add(RecentText, 1, wxEXPAND);
    Layout->Add(CheckBox_Recent, 1, wxEXPAND);
    Layout->Add(Text_GenieVer, 1, wxEXPAND);
    sizer1->Add(CheckBox_GenieVer);
#ifdef WIN32
    sizer1->Add(Button_PathFromRegistry);
#endif
    Layout->Add(sizer1, 1, wxEXPAND);
    sizer2->Add(DriveText, 1, wxEXPAND);
    sizer2->Add(DriveLetterBox, 0, wxRIGHT, 15);
    Layout->Add(sizer2, 1, wxEXPAND);
    Extras->Add(LanguageText);
    Extras->Add(LanguageBox);
    Layout->Add(Extras, 1, wxEXPAND);
    Layout->AddSpacer(15);
    Layout->AddSpacer(15);
    Layout->Add(CheckBox_CustomDefault, 1, wxEXPAND);
    Layout->Add(Path_CustomDefault, 1, wxEXPAND);
    Layout->Add(Radio_DatFileLocation, 1, wxEXPAND);

    Connect(Button_DefaultAoE->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenSave::OnDefaultAoE));
    Connect(Button_DefaultRoR->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenSave::OnDefaultRoR));
    Connect(Button_DefaultAoK->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenSave::OnDefaultAoK));
    Connect(Button_DefaultTC->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenSave::OnDefaultTC));
    Connect(Button_DefaultAoKHD->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenSave::OnDefaultAoKHD));
    Connect(Button_DefaultAP->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenSave::OnDefaultAoP));
    Connect(Button_DefaultSWGB->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenSave::OnDefaultSWGB));
    Connect(Button_DefaultCC->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenSave::OnDefaultCC));
    Connect(CheckBox_Recent->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_OpenSave::OnRecent));
    Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenSave::OnOK));
#ifdef WIN32
    Connect(Button_PathFromRegistry->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenSave::OnPathFromRegistry));
#endif
}

void AGE_OpenSave::OnOK(wxCommandEvent &event)
{
    EndModal(wxID_OK);
}

void AGE_OpenSave::OnRecent(wxCommandEvent &event)
{
    if(RecentValues.empty()) return;
    auto sel = CheckBox_Recent->GetSelection();
    CheckBox_GenieVer->SetSelection(lexical_cast<int>(RecentValues[sel][0]));
    Path_DatFileLocation->SetPath(RecentValues[sel][1]);
    Path_LangFileLocation->SetPath(RecentValues[sel][2]);
    Path_LangX1FileLocation->SetPath(RecentValues[sel][3]);
    Path_LangX1P1FileLocation->SetPath(RecentValues[sel][4]);
    CheckBox_LangFileLocation->SetValue(RecentValues[sel][2].size());
    CheckBox_LangX1FileLocation->SetValue(RecentValues[sel][3].size());
    CheckBox_LangX1P1FileLocation->SetValue(RecentValues[sel][4].size());
}

AGE_PairedCheckBox::AGE_PairedCheckBox(wxWindow *parent, const wxString &label, wxWindow **pair)
: wxCheckBox(parent, wxID_ANY, label)
{
    window_pair = pair;
}

void AGE_PairedCheckBox::DoSet3StateValue(wxCheckBoxState state)
{
    wxCheckBox::DoSet3StateValue(state);
    (*window_pair)->Enable(state != wxCHK_UNCHECKED);
}
