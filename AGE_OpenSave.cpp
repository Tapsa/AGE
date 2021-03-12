#include "AGE_OpenSave.h"

AGE_OpenSave::AGE_OpenSave(wxWindow *parent, const wxString &title, wxDialog *slave, const wxFont &font)
: wxDialog(parent, -1, title+" files...", wxDefaultPosition, wxSize(500, 250), wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxNO_DEFAULT)
{
    SetFont(font);
    Layout = new wxFlexGridSizer(2, 2, 2);
    ForceDat = false;
    Main = new wxBoxSizer(wxVERTICAL);
    SolidText *Defaults_Label = new SolidText(slave, " Defaults: ");
    Defaults = new wxBoxSizer(wxHORIZONTAL);
    Defaults_StarWars = new wxBoxSizer(wxHORIZONTAL);
    Buttons = new wxBoxSizer(wxHORIZONTAL);
    Radio_DatFileLocation = new AGE_PairedCheckBox(slave, "Compressed data set (*.dat):", (wxWindow**)&Path_DatFileLocation);

    ButtonOK = new wxButton(slave, wxID_OK, title);
    ButtonCancel = new wxButton(slave, wxID_CANCEL, "Cancel");
    Buttons->Add(ButtonOK);
    Buttons->Add(ButtonCancel);

    Button_DefaultAoE = new wxButton(slave, wxID_ANY, "Age of Empires");
    Button_DefaultRoR = new wxButton(slave, wxID_ANY, "Rise of Rome");
    Button_DefaultAoK = new wxButton(slave, wxID_ANY, "Age of Kings");
    Button_DefaultTC = new wxButton(slave, wxID_ANY, "The Conquerors");
    Button_DefaultAoKHD = new wxButton(slave, wxID_ANY, "Age of Empires II: HD");
    Button_DefaultAP = new wxButton(slave, wxID_ANY, "Forgotten + African Kingdoms + Rajas");
    Button_DefaultSWGB = new wxButton(slave, wxID_ANY, "Star Wars: Galactic Battlegrounds");
    Button_DefaultCC = new wxButton(slave, wxID_ANY, "Clone Campaigns");
    Button_DefaultDE2 = new wxButton(slave, wxID_ANY, "Age of Empires II: Definitive Edition");
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
    Defaults_StarWars->Add(Button_DefaultDE2, 0, wxEXPAND);

    SolidText *Text_GenieVer = new SolidText(slave, "      Genie version:");
    CheckBox_GenieVer = new wxOwnerDrawnComboBox(slave, wxID_ANY, "", wxDefaultPosition, wxSize(256, -1), 0, 0, wxCB_READONLY);
    CheckBox_GenieVer->Append("TEST");
    CheckBox_GenieVer->Append("TEST.DAT");
    CheckBox_GenieVer->Append("MICKEY.DAT");
    CheckBox_GenieVer->Append("DAVE.DAT");
    CheckBox_GenieVer->Append("MATT.DAT < 6.92");
    CheckBox_GenieVer->Append("Age of Empires Beta (7.04 - 7.11)");
    CheckBox_GenieVer->Append("Age of Empires (7.2)");
    CheckBox_GenieVer->Append("Rise of Rome (7.24)");
    CheckBox_GenieVer->Append("Age of Kings E3 (9.36)");
    CheckBox_GenieVer->Append("Age of Kings Alpha (10.19)");
    CheckBox_GenieVer->Append("Age of Kings Beta (11.05)");
    CheckBox_GenieVer->Append("Age of Kings (11.5)");
    CheckBox_GenieVer->Append("The Conquerors (11.76)");
    CheckBox_GenieVer->Append("The Conquerors (11.76) + Terrain patch");
    CheckBox_GenieVer->Append("Forgotten + African Kingdoms + Rajas > 12");
    CheckBox_GenieVer->Append("Star Wars: Galactic Battlegrounds (1.0)");
    CheckBox_GenieVer->Append("Clone Campaigns (1.1)");
    CheckBox_GenieVer->Append("Mod: Expanding Fronts (>= 1.3) / Terrain patch");
    CheckBox_GenieVer->Append("Age of Empires: Definitive Edition");
    CheckBox_GenieVer->Append("Age of Empires II: Definitive Edition");
    CheckBox_GenieVer->SetSelection(EV_TC);
    SolidText *RecentText = new SolidText(slave, "      Recent paths:");
    CheckBox_Recent = new wxOwnerDrawnComboBox(slave, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, 0, wxCB_READONLY);

    SolidText *DriveText = new SolidText(slave, "      Drive letter:");
    DriveLetterBox = new wxTextCtrl(slave, wxID_ANY, "C", wxDefaultPosition, wxSize(50, -1));
    SolidText *LanguageText = new SolidText(slave, " Language: * ");
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

    Button_DefaultAoE->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_OpenSave::OnDefaultAoE, this);
    Button_DefaultRoR->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_OpenSave::OnDefaultRoR, this);
    Button_DefaultAoK->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_OpenSave::OnDefaultAoK, this);
    Button_DefaultTC->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_OpenSave::OnDefaultTC, this);
    Button_DefaultAoKHD->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_OpenSave::OnDefaultAoKHD, this);
    Button_DefaultAP->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_OpenSave::OnDefaultAoP, this);
    Button_DefaultDE2->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_OpenSave::OnDefaultDE2, this);
    Button_DefaultSWGB->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_OpenSave::OnDefaultSWGB, this);
    Button_DefaultCC->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_OpenSave::OnDefaultCC, this);
    CheckBox_Recent->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &AGE_OpenSave::OnRecent, this);
    ButtonOK->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](wxCommandEvent&){EndModal(wxID_OK);});
#ifdef WIN32
    Button_PathFromRegistry->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &AGE_OpenSave::OnPathFromRegistry, this);
#endif
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

void AGE_OpenSave::OnDefault(const wxString &part)
{
    wxString custom = Path_CustomDefault->GetPath();

    if(CheckBox_CustomDefault->GetValue() && custom.size() > 3)
    {
        game_path = custom;
    }
    else
    {
        game_path = DriveLetterBox->GetValue() + (wxIsPlatform64Bit() ? ":\\Program Files (x86)" : ":\\Program Files") + part;
    }
}

void AGE_OpenSave::OnDefaultAoE(wxCommandEvent &event)
{
    OnDefault("\\Microsoft Games\\Age of Empires");

    CheckBox_GenieVer->SetSelection(EV_AoE);
    if(!ForceDat) Path_DatFileLocation->SetPath(game_path + "\\data\\empires.dat");
    Path_LangFileLocation->SetPath(game_path + "\\language.dll");
    Path_LangX1FileLocation->SetPath(wxEmptyString);
    Path_LangX1P1FileLocation->SetPath(wxEmptyString);
    Radio_DatFileLocation->SetValue(true);
    CheckBox_LangFileLocation->SetValue(true);
    CheckBox_LangX1FileLocation->SetValue(false);
    CheckBox_LangX1P1FileLocation->SetValue(false);
    CheckBox_LangWrite->Enable(true);
}

void AGE_OpenSave::OnDefaultRoR(wxCommandEvent &event)
{
    OnDefault("\\Microsoft Games\\Age of Empires");

    CheckBox_GenieVer->SetSelection(EV_RoR);
    if(!ForceDat) Path_DatFileLocation->SetPath(game_path + "\\data2\\empires.dat");
    Path_LangFileLocation->SetPath(game_path + "\\language.dll");
    Path_LangX1FileLocation->SetPath(game_path + "\\languagex.dll");
    Path_LangX1P1FileLocation->SetPath(wxEmptyString);
    Radio_DatFileLocation->SetValue(true);
    CheckBox_LangFileLocation->SetValue(true);
    CheckBox_LangX1FileLocation->SetValue(true);
    CheckBox_LangX1P1FileLocation->SetValue(false);
    CheckBox_LangWrite->Enable(true);
}

void AGE_OpenSave::OnDefaultAoK(wxCommandEvent &event)
{
    OnDefault("\\Microsoft Games\\Age of Empires II");

    CheckBox_GenieVer->SetSelection(EV_AoK);
    if(!ForceDat) Path_DatFileLocation->SetPath(game_path + "\\data\\empires2.dat");
    Path_LangFileLocation->SetPath(game_path + "\\language.dll");
    Path_LangX1FileLocation->SetPath(wxEmptyString);
    Path_LangX1P1FileLocation->SetPath(wxEmptyString);
    Radio_DatFileLocation->SetValue(true);
    CheckBox_LangFileLocation->SetValue(true);
    CheckBox_LangX1FileLocation->SetValue(false);
    CheckBox_LangX1P1FileLocation->SetValue(false);
    CheckBox_LangWrite->Enable(true);
}

void AGE_OpenSave::OnDefaultTC(wxCommandEvent &event)
{
    OnDefault("\\Microsoft Games\\Age of Empires II");

    CheckBox_GenieVer->SetSelection(EV_TC);
    if(!ForceDat) Path_DatFileLocation->SetPath(game_path + "\\data\\empires2_x1_p1.dat");
    Path_LangFileLocation->SetPath(game_path + "\\language.dll");
    Path_LangX1FileLocation->SetPath(game_path + "\\language_x1.dll");
    Path_LangX1P1FileLocation->SetPath(game_path + "\\language_x1_p1.dll");
    Radio_DatFileLocation->SetValue(true);
    CheckBox_LangFileLocation->SetValue(true);
    CheckBox_LangX1FileLocation->SetValue(true);
    CheckBox_LangX1P1FileLocation->SetValue(true);
    CheckBox_LangWrite->Enable(true);
}

void AGE_OpenSave::OnDefaultAoKHD(wxCommandEvent &event)
{
    OnDefault("\\Steam\\steamapps\\common\\Age2HD");
    wxString locale = LanguageBox->GetValue();

    CheckBox_GenieVer->SetSelection(EV_TC);
    CheckBox_LangWrite->Enable(false);
    if(!ForceDat) Path_DatFileLocation->SetPath(game_path + "\\resources\\_common\\dat\\empires2_x1_p1.dat");
    Path_LangFileLocation->SetPath(game_path + "\\resources\\"+locale+"\\strings\\key-value\\key-value-strings-utf8.txt");
    Path_LangX1FileLocation->SetPath(game_path + "\\resources\\"+locale+"\\strings\\key-value\\key-value-modded-strings-utf8.txt");
    Path_LangX1P1FileLocation->SetPath(wxEmptyString);
    Radio_DatFileLocation->SetValue(true);
    CheckBox_LangX1P1FileLocation->SetValue(false);
}

void AGE_OpenSave::OnDefaultAoP(wxCommandEvent &event)
{
    OnDefault("\\Steam\\steamapps\\common\\Age2HD");
    wxString locale = LanguageBox->GetValue();

    CheckBox_GenieVer->SetSelection(EV_Cysion);
    CheckBox_LangWrite->Enable(false);
    if(!ForceDat) Path_DatFileLocation->SetPath(game_path + "\\resources\\_common\\dat\\empires2_x2_p1.dat");
    Path_LangFileLocation->SetPath(game_path + "\\resources\\"+locale+"\\strings\\key-value\\key-value-strings-utf8.txt");
    Path_LangX1FileLocation->SetPath(game_path + "\\resources\\"+locale+"\\strings\\key-value\\key-value-modded-strings-utf8.txt");
    Path_LangX1P1FileLocation->SetPath(wxEmptyString);
    Radio_DatFileLocation->SetValue(true);
    CheckBox_LangX1P1FileLocation->SetValue(false);
}

void AGE_OpenSave::OnDefaultDE2(wxCommandEvent &event)
{
    OnDefault("\\Steam\\steamapps\\common\\AoE2DE");
    wxString locale = LanguageBox->GetValue();

    CheckBox_GenieVer->SetSelection(EV_DE2);
    CheckBox_LangWrite->Enable(false);
    if(!ForceDat) Path_DatFileLocation->SetPath(game_path + "\\resources\\_common\\dat\\empires2_x2_p1.dat");
    Path_LangFileLocation->SetPath(game_path + "\\resources\\"+locale+"\\strings\\key-value\\key-value-strings-utf8.txt");
    Path_LangX1FileLocation->SetPath(game_path + "\\resources\\"+locale+"\\strings\\key-value\\key-value-modded-strings-utf8.txt");
    Path_LangX1P1FileLocation->SetPath(wxEmptyString);
    Radio_DatFileLocation->SetValue(true);
    CheckBox_LangX1P1FileLocation->SetValue(false);
}

void AGE_OpenSave::OnDefaultSWGB(wxCommandEvent &event)
{
    OnDefault("\\GOG Games\\Star Wars - Galactic Battlegrounds");

    CheckBox_GenieVer->SetSelection(EV_SWGB);
    if(!ForceDat) Path_DatFileLocation->SetPath(game_path + "\\Data\\genie.dat");
    Path_LangFileLocation->SetPath(game_path + "\\language.dll");
    Path_LangX1FileLocation->SetPath(wxEmptyString);
    Path_LangX1P1FileLocation->SetPath(wxEmptyString);
    Radio_DatFileLocation->SetValue(true);
    CheckBox_LangFileLocation->SetValue(true);
    CheckBox_LangX1FileLocation->SetValue(false);
    CheckBox_LangX1P1FileLocation->SetValue(false);
    CheckBox_LangWrite->Enable(true);
}

void AGE_OpenSave::OnDefaultCC(wxCommandEvent &event)
{
    OnDefault("\\GOG Games\\Star Wars - Galactic Battlegrounds");

    if(path_src == 2)
    {
        CheckBox_GenieVer->SetSelection(EV_EF);
        if(!ForceDat) Path_DatFileLocation->SetPath(game_path + "\\Data\\genie_x2.dat");
        Path_LangX1P1FileLocation->SetPath(game_path + "\\language_x2.dll");
        CheckBox_LangX1P1FileLocation->SetValue(true);
    }
    else
    {
        CheckBox_GenieVer->SetSelection(EV_CC);
        if(!ForceDat) Path_DatFileLocation->SetPath(game_path + "\\Data\\genie_x1.dat");
        Path_LangX1P1FileLocation->SetPath(wxEmptyString);
        CheckBox_LangX1P1FileLocation->SetValue(false);
    }
    Path_LangFileLocation->SetPath(game_path + "\\language.dll");
    Path_LangX1FileLocation->SetPath(game_path + "\\language_x1.dll");
    Radio_DatFileLocation->SetValue(true);
    CheckBox_LangFileLocation->SetValue(true);
    CheckBox_LangX1FileLocation->SetValue(true);
    CheckBox_LangWrite->Enable(true);
}

#ifdef WIN32
void AGE_OpenSave::OnPathFromRegistry(wxCommandEvent &event)
{
    bool customx = CheckBox_CustomDefault->GetValue();
    wxString path, custom = Path_CustomDefault->GetPath();
    CheckBox_CustomDefault->SetValue(true);
    path_src = 1;
    switch(CheckBox_GenieVer->GetSelection())
    {
        case EV_AoE:
        {
            wxRegKey key(wxRegKey::HKLM, "Software\\Microsoft\\Microsoft Games\\Age of Empires\\1.0");
            if(key.Exists())
            {
                if(key.QueryValue("EXE Path", path))
                {
                    DriveLetterBox->ChangeValue(path[0]);
                    Path_CustomDefault->SetPath(path);
                    OnDefaultAoE(event);
                }
            }
            break;
        }
        case EV_RoR:
        {
            wxRegKey key(wxRegKey::HKLM, "Software\\Microsoft\\Microsoft Games\\Age of Empires Expansion\\1.0");
            if(key.Exists())
            {
                if(key.QueryValue("EXE Path", path))
                {
                    DriveLetterBox->ChangeValue(path[0]);
                    Path_CustomDefault->SetPath(path);
                    OnDefaultRoR(event);
                }
            }
            break;
        }
        case EV_AoK:
        {
            wxRegKey key(wxRegKey::HKLM, "Software\\Microsoft\\Microsoft Games\\Age of Empires\\2.0");
            if(key.Exists())
            {
                if(key.QueryValue("EXE Path", path))
                {
                    DriveLetterBox->ChangeValue(path[0]);
                    Path_CustomDefault->SetPath(path);
                    OnDefaultAoK(event);
                }
            }
            break;
        }
        case EV_TC:
        case EV_TCV:
        {
            wxRegKey key(wxRegKey::HKLM, "Software\\Microsoft\\Microsoft Games\\Age of Empires II: The Conquerors Expansion\\1.0");
            if(key.Exists())
            {
                if(key.QueryValue("EXE Path", path))
                {
                    DriveLetterBox->ChangeValue(path[0]);
                    Path_CustomDefault->SetPath(path);
                    OnDefaultTC(event);
                }
            }
            break;
        }
        case EV_SWGB:
        {
            wxRegKey key(wxRegKey::HKLM, "Software\\LucasArts Entertainment Company LLC\\Star Wars Galactic Battlegrounds\\1.0");
            if(key.Exists())
            {
                if(key.QueryValue("Game Path", path))
                {
                    path.Truncate(path.size() - 1);
                    DriveLetterBox->ChangeValue(path[0]);
                    Path_CustomDefault->SetPath(path);
                    OnDefaultSWGB(event);
                }
            }
            break;
        }
        case EV_CC:
        {
            wxRegKey key(wxRegKey::HKLM, "Software\\LucasArts Entertainment Company LLC\\Star Wars Galactic Battlegrounds: Clone Campaigns\\1.0");
            if(key.Exists())
            {
                if(key.QueryValue("Game Path", path))
                {
                    path.Truncate(path.size() - 1);
                    DriveLetterBox->ChangeValue(path[0]);
                    Path_CustomDefault->SetPath(path);
                    OnDefaultCC(event);
                }
            }
            break;
        }
        case EV_EF:
        {
            wxRegKey key(wxRegKey::HKLM, "Software\\LucasArts Entertainment Company LLC\\Star Wars Galactic Battlegrounds: Clone Campaigns\\1.0");
            if(key.Exists())
            {
                path_src = 2;
                if(key.QueryValue("Game Path", path))
                {
                    path.Truncate(path.size() - 1);
                    DriveLetterBox->ChangeValue(path[0]);
                    Path_CustomDefault->SetPath(path);
                    OnDefaultCC(event);
                }
            }
            break;
        }
        default: break;
    }
    CheckBox_CustomDefault->SetValue(customx);
    Path_CustomDefault->SetPath(custom);
    if(path.empty()) wxMessageBox("No registry entry found.", "Advanced Genie Editor");
}
#endif

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
