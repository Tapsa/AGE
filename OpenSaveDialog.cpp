#include "Common.h"
#include "CustomWidgets.h"
#include "EditableVersion.h"
#include "OpenSaveDialog.h"

OpenSaveDialog::OpenSaveDialog(wxWindow *parent, const wxString &title, wxDialog *slave, const wxFont &font)
    : wxDialog(parent, -1, title + " files...", wxDefaultPosition, wxSize(500, 250), wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxNO_DEFAULT)
{
    SetFont(font);
    Layout = new wxFlexGridSizer(2, 2, 2);
    ForceDat = false;
    Main = new wxBoxSizer(wxVERTICAL);
    SolidText *Defaults_Label = new SolidText(slave, " Defaults: ");
    Defaults = new wxBoxSizer(wxHORIZONTAL);
    Defaults_StarWars = new wxBoxSizer(wxHORIZONTAL);
    Buttons = new wxBoxSizer(wxHORIZONTAL);
    Radio_DatFileLocation = new PairedCheckBox(slave, "Compressed data set (*.dat):", (wxWindow **)&Path_DatFileLocation);

    ButtonOK = new wxButton(slave, wxID_OK, title);
    ButtonCancel = new wxButton(slave, wxID_CANCEL, "Cancel");
    Buttons->Add(ButtonOK);
    Buttons->Add(ButtonCancel);

    Button_DefaultAoE = new wxButton(slave, wxID_ANY, "Age of Empires");
    Button_DefaultRoR = new wxButton(slave, wxID_ANY, "Rise of Rome");
    Button_DefaultDE1 = new wxButton(slave, wxID_ANY, "Age of Empires: Definitive Edition");
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
    Defaults_StarWars->Add(Button_DefaultDE1, 0, wxEXPAND);
    Defaults_StarWars->Add(Button_DefaultDE2, 0, wxEXPAND);

    SolidText *Text_GenieVer = new SolidText(slave, "      Genie version:");
    ComboBox_GenieVer = new wxOwnerDrawnComboBox(slave, wxID_ANY, "", wxDefaultPosition, wxSize(350, -1), 0, 0, wxCB_READONLY);
    ComboBox_GenieVer->Append("TEST");
    ComboBox_GenieVer->Append("TEST.DAT");
    ComboBox_GenieVer->Append("MICKEY.DAT");
    ComboBox_GenieVer->Append("DAVE.DAT");
    ComboBox_GenieVer->Append("MATT.DAT < 6.92");
    ComboBox_GenieVer->Append("Age of Empires Beta (7.04 - 7.11)");
    ComboBox_GenieVer->Append("Age of Empires (7.2)");
    ComboBox_GenieVer->Append("Rise of Rome (7.24)");
    ComboBox_GenieVer->Append("Age of Kings E3 (9.36)");
    ComboBox_GenieVer->Append("Age of Kings Alpha (10.19)");
    ComboBox_GenieVer->Append("Age of Kings Beta (11.05)");
    ComboBox_GenieVer->Append("Age of Kings (11.5)");
    ComboBox_GenieVer->Append("The Conquerors (11.76)");
    ComboBox_GenieVer->Append("The Conquerors (11.76) + UserPatch 1.5");
    ComboBox_GenieVer->Append("The Conquerors (11.76) + Terrain patch");
    ComboBox_GenieVer->Append("Forgotten + African Kingdoms + Rajas > 12");
    ComboBox_GenieVer->Append("Star Wars: Galactic Battlegrounds (1.0)");
    ComboBox_GenieVer->Append("Clone Campaigns (1.1)");
    ComboBox_GenieVer->Append("Mod: Expanding Fronts (1.3 - 1.4) / Terrain patch");
    ComboBox_GenieVer->Append("Mod: Expanding Fronts (>= 1.4.1) / Terrain + tech tree patch");
    ComboBox_GenieVer->Append("Age of Empires: Definitive Edition");
    ComboBox_GenieVer->Append("Age of Empires II: Definitive Edition");
    ComboBox_GenieVer->SetSelection(EV_TC);
    SolidText *RecentText = new SolidText(slave, "      Recent paths:");
    CheckBox_Recent = new wxOwnerDrawnComboBox(slave, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, 0, wxCB_READONLY);

    SolidText *DriveText = new SolidText(slave, "      Drive letter:");
    DriveLetterBox = new wxTextCtrl(slave, wxID_ANY, "C", wxDefaultPosition, wxSize(50, -1));
    SolidText *LanguageText = new SolidText(slave, " Language: * ");
    LanguageBox = new wxTextCtrl(slave, wxID_ANY, "en", wxDefaultPosition, wxSize(50, -1));
    LanguageBox->SetToolTip("For AoK HD paths");
    Extras = new wxBoxSizer(wxHORIZONTAL);
    CheckBox_CustomDefault = new PairedCheckBox(slave, "Custom path override:", (wxWindow **)&Path_CustomDefault);
    Path_CustomDefault = new wxDirPickerCtrl(slave, wxID_ANY, "", "Select a folder", wxDefaultPosition, wxDefaultSize, wxDIRP_USE_TEXTCTRL | wxDIRP_DIR_MUST_EXIST);
    wxSizer *sizer1 = new wxBoxSizer(wxHORIZONTAL);
    wxSizer *sizer2 = new wxBoxSizer(wxHORIZONTAL);

    CheckBox_LangFileLocation = new PairedCheckBox(slave, "Language file location:", (wxWindow **)&Path_LangFileLocation);
    CheckBox_LangX1FileLocation = new PairedCheckBox(slave, "Language x1 file location:", (wxWindow **)&Path_LangX1FileLocation);
    CheckBox_LangX1P1FileLocation = new PairedCheckBox(slave, "Language p1 file location:", (wxWindow **)&Path_LangX1P1FileLocation);

    Layout->Add(RecentText, 1, wxEXPAND);
    Layout->Add(CheckBox_Recent, 1, wxEXPAND);
    Layout->Add(Text_GenieVer, 1, wxEXPAND);
    sizer1->Add(ComboBox_GenieVer);
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

    Button_DefaultAoE->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &OpenSaveDialog::OnDefaultAoE, this);
    Button_DefaultRoR->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &OpenSaveDialog::OnDefaultRoR, this);
    Button_DefaultDE1->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &OpenSaveDialog::OnDefaultDE1, this);
    Button_DefaultAoK->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &OpenSaveDialog::OnDefaultAoK, this);
    Button_DefaultTC->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &OpenSaveDialog::OnDefaultTC, this);
    Button_DefaultAoKHD->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &OpenSaveDialog::OnDefaultAoKHD, this);
    Button_DefaultAP->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &OpenSaveDialog::OnDefaultAoP, this);
    Button_DefaultDE2->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &OpenSaveDialog::OnDefaultDE2, this);
    Button_DefaultSWGB->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &OpenSaveDialog::OnDefaultSWGB, this);
    Button_DefaultCC->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &OpenSaveDialog::OnDefaultCC, this);
    CheckBox_Recent->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &OpenSaveDialog::OnRecent, this);
    ButtonOK->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](wxCommandEvent &)
    {
        if (ComboBox_GenieVer->GetSelection() >= 0)
        {
            EndModal(wxID_OK);
        }
        else
        {
            wxMessageBox("Select genie version", "Notice");
        }
    });
#ifdef WIN32
    Button_PathFromRegistry->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &OpenSaveDialog::OnPathFromRegistry, this);
#endif
}

void OpenSaveDialog::OnRecent(wxCommandEvent &event)
{
    if (RecentValues.empty()) return;
    int sel = CheckBox_Recent->GetSelection();
    ComboBox_GenieVer->SetSelection(lexical_cast<int>(RecentValues[sel][0]));
    Path_DatFileLocation->SetPath(RecentValues[sel][1]);
    Path_LangFileLocation->SetPath(RecentValues[sel][2]);
    Path_LangX1FileLocation->SetPath(RecentValues[sel][3]);
    Path_LangX1P1FileLocation->SetPath(RecentValues[sel][4]);
    CheckBox_LangFileLocation->SetValue(RecentValues[sel][2].size());
    CheckBox_LangX1FileLocation->SetValue(RecentValues[sel][3].size());
    CheckBox_LangX1P1FileLocation->SetValue(RecentValues[sel][4].size());
}

void OpenSaveDialog::OnDefault(const wxString &part)
{
    wxString custom = Path_CustomDefault->GetPath();

    if (CheckBox_CustomDefault->GetValue() && custom.size() > 3)
    {
        game_path = custom;
    }
    else
    {
        game_path = DriveLetterBox->GetValue() + (wxIsPlatform64Bit() ? ":\\Program Files (x86)" : ":\\Program Files") + part;
    }
}

void OpenSaveDialog::OnDefaultAoE(wxCommandEvent &event)
{
    OnDefault("\\Microsoft Games\\Age of Empires");

    ComboBox_GenieVer->SetSelection(EV_AoE);
    if (!ForceDat) Path_DatFileLocation->SetPath(game_path + "\\data\\empires.dat");
    Path_LangFileLocation->SetPath(game_path + "\\language.dll");
    Path_LangX1FileLocation->SetPath(wxEmptyString);
    Path_LangX1P1FileLocation->SetPath(wxEmptyString);
    Radio_DatFileLocation->SetValue(true);
    CheckBox_LangFileLocation->SetValue(true);
    CheckBox_LangX1FileLocation->SetValue(false);
    CheckBox_LangX1P1FileLocation->SetValue(false);
    CheckBox_LangWrite->Enable(true);
}

void OpenSaveDialog::OnDefaultRoR(wxCommandEvent &event)
{
    OnDefault("\\Microsoft Games\\Age of Empires");

    ComboBox_GenieVer->SetSelection(EV_RoR);
    if (!ForceDat) Path_DatFileLocation->SetPath(game_path + "\\data2\\empires.dat");
    Path_LangFileLocation->SetPath(game_path + "\\language.dll");
    Path_LangX1FileLocation->SetPath(game_path + "\\languagex.dll");
    Path_LangX1P1FileLocation->SetPath(wxEmptyString);
    Radio_DatFileLocation->SetValue(true);
    CheckBox_LangFileLocation->SetValue(true);
    CheckBox_LangX1FileLocation->SetValue(true);
    CheckBox_LangX1P1FileLocation->SetValue(false);
    CheckBox_LangWrite->Enable(true);
}

void OpenSaveDialog::OnDefaultDE1(wxCommandEvent &event)
{
    OnDefault("\\Steam\\steamapps\\common\\AoEDE");
    wxString locale = LanguageBox->GetValue();

    ComboBox_GenieVer->SetSelection(EV_Tapsa);
    CheckBox_LangWrite->Enable(false);
    if (!ForceDat) Path_DatFileLocation->SetPath(game_path + "\\Data\\empires.dat");
    Path_LangFileLocation->SetPath(game_path + "\\Data\\Localization\\" + locale + "\\strings.txt");
    Path_LangX1FileLocation->SetPath(wxEmptyString);
    Path_LangX1P1FileLocation->SetPath(wxEmptyString);
    Radio_DatFileLocation->SetValue(true);
    CheckBox_LangX1FileLocation->SetValue(false);
    CheckBox_LangX1P1FileLocation->SetValue(false);
}

void OpenSaveDialog::OnDefaultAoK(wxCommandEvent &event)
{
    OnDefault("\\Microsoft Games\\Age of Empires II");

    ComboBox_GenieVer->SetSelection(EV_AoK);
    if (!ForceDat) Path_DatFileLocation->SetPath(game_path + "\\data\\empires2.dat");
    Path_LangFileLocation->SetPath(game_path + "\\language.dll");
    Path_LangX1FileLocation->SetPath(wxEmptyString);
    Path_LangX1P1FileLocation->SetPath(wxEmptyString);
    Radio_DatFileLocation->SetValue(true);
    CheckBox_LangFileLocation->SetValue(true);
    CheckBox_LangX1FileLocation->SetValue(false);
    CheckBox_LangX1P1FileLocation->SetValue(false);
    CheckBox_LangWrite->Enable(true);
}

void OpenSaveDialog::OnDefaultTC(wxCommandEvent &event)
{
    OnDefault("\\Microsoft Games\\Age of Empires II");

    ComboBox_GenieVer->SetSelection(EV_TC);
    if (!ForceDat) Path_DatFileLocation->SetPath(game_path + "\\data\\empires2_x1_p1.dat");
    Path_LangFileLocation->SetPath(game_path + "\\language.dll");
    Path_LangX1FileLocation->SetPath(game_path + "\\language_x1.dll");
    Path_LangX1P1FileLocation->SetPath(game_path + "\\language_x1_p1.dll");
    Radio_DatFileLocation->SetValue(true);
    CheckBox_LangFileLocation->SetValue(true);
    CheckBox_LangX1FileLocation->SetValue(true);
    CheckBox_LangX1P1FileLocation->SetValue(true);
    CheckBox_LangWrite->Enable(true);
}

void OpenSaveDialog::OnDefaultAoKHD(wxCommandEvent &event)
{
    OnDefault("\\Steam\\steamapps\\common\\Age2HD");
    wxString locale = LanguageBox->GetValue();

    ComboBox_GenieVer->SetSelection(EV_TC);
    CheckBox_LangWrite->Enable(false);
    if (!ForceDat) Path_DatFileLocation->SetPath(game_path + "\\resources\\_common\\dat\\empires2_x1_p1.dat");
    Path_LangFileLocation->SetPath(game_path + "\\resources\\" + locale + "\\strings\\key-value\\key-value-strings-utf8.txt");
    Path_LangX1FileLocation->SetPath(game_path + "\\resources\\" + locale + "\\strings\\key-value\\key-value-modded-strings-utf8.txt");
    Path_LangX1P1FileLocation->SetPath(wxEmptyString);
    Radio_DatFileLocation->SetValue(true);
    CheckBox_LangX1P1FileLocation->SetValue(false);
}

void OpenSaveDialog::OnDefaultAoP(wxCommandEvent &event)
{
    OnDefault("\\Steam\\steamapps\\common\\Age2HD");
    wxString locale = LanguageBox->GetValue();

    ComboBox_GenieVer->SetSelection(EV_Cysion);
    CheckBox_LangWrite->Enable(false);
    if (!ForceDat) Path_DatFileLocation->SetPath(game_path + "\\resources\\_common\\dat\\empires2_x2_p1.dat");
    Path_LangFileLocation->SetPath(game_path + "\\resources\\" + locale + "\\strings\\key-value\\key-value-strings-utf8.txt");
    Path_LangX1FileLocation->SetPath(game_path + "\\resources\\" + locale + "\\strings\\key-value\\key-value-modded-strings-utf8.txt");
    Path_LangX1P1FileLocation->SetPath(wxEmptyString);
    Radio_DatFileLocation->SetValue(true);
    CheckBox_LangX1P1FileLocation->SetValue(false);
}

void OpenSaveDialog::OnDefaultDE2(wxCommandEvent &event)
{
    OnDefault("\\Steam\\steamapps\\common\\AoE2DE");
    wxString locale = LanguageBox->GetValue();

    ComboBox_GenieVer->SetSelection(EV_DE2);
    CheckBox_LangWrite->Enable(false);
    if (!ForceDat) Path_DatFileLocation->SetPath(game_path + "\\resources\\_common\\dat\\empires2_x2_p1.dat");
    Path_LangFileLocation->SetPath(game_path + "\\resources\\" + locale + "\\strings\\key-value\\key-value-strings-utf8.txt");
    Path_LangX1FileLocation->SetPath(game_path + "\\resources\\" + locale + "\\strings\\key-value\\key-value-modded-strings-utf8.txt");
    Path_LangX1P1FileLocation->SetPath(wxEmptyString);
    Radio_DatFileLocation->SetValue(true);
    CheckBox_LangX1P1FileLocation->SetValue(false);
}

void OpenSaveDialog::OnDefaultSWGB(wxCommandEvent &event)
{
    OnDefault("\\GOG Games\\Star Wars - Galactic Battlegrounds");

    ComboBox_GenieVer->SetSelection(EV_SWGB);
    if (!ForceDat) Path_DatFileLocation->SetPath(game_path + "\\Data\\genie.dat");
    Path_LangFileLocation->SetPath(game_path + "\\language.dll");
    Path_LangX1FileLocation->SetPath(wxEmptyString);
    Path_LangX1P1FileLocation->SetPath(wxEmptyString);
    Radio_DatFileLocation->SetValue(true);
    CheckBox_LangFileLocation->SetValue(true);
    CheckBox_LangX1FileLocation->SetValue(false);
    CheckBox_LangX1P1FileLocation->SetValue(false);
    CheckBox_LangWrite->Enable(true);
}

void OpenSaveDialog::OnDefaultCC(wxCommandEvent &event)
{
    OnDefault("\\GOG Games\\Star Wars - Galactic Battlegrounds");

    if (path_src == 2)
    {
        ComboBox_GenieVer->SetSelection(EV_EF2);
        if (!ForceDat) Path_DatFileLocation->SetPath(game_path + "\\Data\\genie_x2.dat");
        Path_LangX1P1FileLocation->SetPath(game_path + "\\language_x2.dll");
        CheckBox_LangX1P1FileLocation->SetValue(true);
    }
    else
    {
        ComboBox_GenieVer->SetSelection(EV_CC);
        if (!ForceDat) Path_DatFileLocation->SetPath(game_path + "\\Data\\genie_x1.dat");
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
void OpenSaveDialog::OnPathFromRegistry(wxCommandEvent &event)
{
    bool customx = CheckBox_CustomDefault->GetValue();
    wxString path, custom = Path_CustomDefault->GetPath();
    CheckBox_CustomDefault->SetValue(true);
    path_src = 1;
    switch (ComboBox_GenieVer->GetSelection())
    {
        case EV_AoE:
        {
            wxRegKey key(wxRegKey::HKLM, "Software\\Microsoft\\Microsoft Games\\Age of Empires\\1.0", wxRegKey::WOW64ViewMode_32);
            if (key.Exists())
            {
                if (key.QueryValue("EXE Path", path))
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
            wxRegKey key(wxRegKey::HKLM, "Software\\Microsoft\\Microsoft Games\\Age of Empires Expansion\\1.0", wxRegKey::WOW64ViewMode_32);
            if (key.Exists())
            {
                if (key.QueryValue("EXE Path", path))
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
            wxRegKey key(wxRegKey::HKLM, "Software\\Microsoft\\Microsoft Games\\Age of Empires\\2.0", wxRegKey::WOW64ViewMode_32);
            if (key.Exists())
            {
                if (key.QueryValue("EXE Path", path))
                {
                    DriveLetterBox->ChangeValue(path[0]);
                    Path_CustomDefault->SetPath(path);
                    OnDefaultAoK(event);
                }
            }
            break;
        }
        case EV_TC:
        case EV_UP:
        case EV_TCV:
        {
            wxRegKey key(wxRegKey::HKLM, "Software\\Microsoft\\Microsoft Games\\Age of Empires II: The Conquerors Expansion\\1.0", wxRegKey::WOW64ViewMode_32);
            if (key.Exists())
            {
                if (key.QueryValue("EXE Path", path))
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
            wxRegKey key(wxRegKey::HKLM, "Software\\LucasArts Entertainment Company LLC\\Star Wars Galactic Battlegrounds\\1.0", wxRegKey::WOW64ViewMode_32);
            if (key.Exists())
            {
                if (key.QueryValue("Game Path", path))
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
            wxRegKey key(wxRegKey::HKLM, "Software\\LucasArts Entertainment Company LLC\\Star Wars Galactic Battlegrounds: Clone Campaigns\\1.0", wxRegKey::WOW64ViewMode_32);
            if (key.Exists())
            {
                if (key.QueryValue("Game Path", path))
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
        case EV_EF2:
        {
            wxRegKey key(wxRegKey::HKLM, "Software\\LucasArts Entertainment Company LLC\\Star Wars Galactic Battlegrounds: Clone Campaigns\\1.0", wxRegKey::WOW64ViewMode_32);
            if (key.Exists())
            {
                path_src = 2;
                if (key.QueryValue("Game Path", path))
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
    if (path.empty()) wxMessageBox("No registry entry found.", "Advanced Genie Editor");
}
#endif

PairedCheckBox::PairedCheckBox(wxWindow *parent, const wxString &label, wxWindow **pair)
    : wxCheckBox(parent, wxID_ANY, label)
{
    window_pair = pair;
}

void PairedCheckBox::DoSet3StateValue(wxCheckBoxState state)
{
    wxCheckBox::DoSet3StateValue(state);
    (*window_pair)->Enable(state != wxCHK_UNCHECKED);
}
