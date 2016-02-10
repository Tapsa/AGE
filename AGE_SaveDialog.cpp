#include "AGE_SaveDialog.h"

AGE_SaveDialog::AGE_SaveDialog(wxWindow *parent)
: AGE_OpenSave(parent, "Save", this)
{
    Path_DatFileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "Compressed data set (*.dat)|*.dat", wxDefaultPosition, wxDefaultSize, wxFLP_SAVE | wxFLP_USE_TEXTCTRL | wxFLP_OVERWRITE_PROMPT);

    Path_LangFileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "DLL or text (*.dll, *.txt)|*.dll;*.txt", wxDefaultPosition, wxDefaultSize, wxFLP_SAVE | wxFLP_USE_TEXTCTRL | wxFLP_OVERWRITE_PROMPT);
    Path_LangX1FileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "DLL or text (*.dll, *.txt)|*.dll;*.txt", wxDefaultPosition, wxDefaultSize, wxFLP_SAVE | wxFLP_USE_TEXTCTRL | wxFLP_OVERWRITE_PROMPT);
    Path_LangX1P1FileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "DLL or text (*.dll, *.txt)|*.dll;*.txt", wxDefaultPosition, wxDefaultSize, wxFLP_SAVE | wxFLP_USE_TEXTCTRL | wxFLP_OVERWRITE_PROMPT);
    CheckBox_LangWrite = new wxCheckBox(this, wxID_ANY, "Save language files *");
    CheckBox_LangWrite->SetToolTip("WARNING! This feature is still experimental");
    SyncWithReadPaths = new wxCheckBox(this, wxID_ANY, "Sync with read paths");

    Layout->Show(4, false);
    Layout->Show(5, false);
    Layout->Show(8, false);
    Layout->Show(9, false);

	Layout->Add(Path_DatFileLocation, 1, wxEXPAND);
	Layout->AddSpacer(15);
	Layout->AddSpacer(15);
	Layout->Add(CheckBox_LangFileLocation, 1, wxEXPAND);
	Layout->Add(Path_LangFileLocation, 1, wxEXPAND);
	Layout->Add(CheckBox_LangX1FileLocation, 1, wxEXPAND);
	Layout->Add(Path_LangX1FileLocation, 1, wxEXPAND);
	Layout->Add(CheckBox_LangX1P1FileLocation, 1, wxEXPAND);
	Layout->Add(Path_LangX1P1FileLocation, 1, wxEXPAND);
	Layout->Add(CheckBox_LangWrite, 1, wxEXPAND);
	Layout->AddSpacer(15);
	Layout->AddSpacer(15);
	Layout->AddSpacer(15);
    Buttons->Insert(0, SyncWithReadPaths);

	Layout->AddGrowableCol(1, 1);
	Layout->AddGrowableRow(11, 1);

	Main->Add(Defaults, 0, wxALIGN_LEFT | wxTOP | wxLEFT | wxRIGHT, 5);
	Main->Add(Defaults_StarWars, 0, wxALIGN_LEFT | wxBOTTOM | wxLEFT | wxRIGHT, 5);
	Main->Add(Layout, 1, wxEXPAND | wxALL, 5);
	Main->Add(Buttons, 0, wxALIGN_RIGHT | wxALL, 5);

    SetSizerAndFit(Main);
    SetDefaultItem(ButtonOK);
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
    CheckBox_CustomDefault->SetValue(event.GetExtraLong());
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
    CheckBox_CustomDefault->SetValue(event.GetExtraLong());
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
    CheckBox_CustomDefault->SetValue(event.GetExtraLong());
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
    CheckBox_CustomDefault->SetValue(event.GetExtraLong());
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
    CheckBox_CustomDefault->SetValue(event.GetExtraLong());
    OnDefault("\\Steam\\steamapps\\common\\Age2HD");
    wxString locale = LanguageBox->GetValue();

	CheckBox_GenieVer->SetSelection(EV_TC);
    CheckBox_LangWrite->Enable(false);
	if(!ForceDat) Path_DatFileLocation->SetPath(game_path + "\\resources\\_common\\dat\\empires2_x1_p1.dat");
	Path_LangFileLocation->SetPath(game_path + "\\resources\\"+locale+"\\strings\\key-value\\key-value-strings-utf8.txt");
	Path_LangX1FileLocation->SetPath(game_path + "\\resources\\"+locale+"\\strings\\key-value\\key-value-modded-strings-utf8.txt");
	Path_LangX1P1FileLocation->SetPath(wxEmptyString);
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(false);
	CheckBox_LangX1FileLocation->SetValue(false);
	CheckBox_LangX1P1FileLocation->SetValue(false);
}

void AGE_OpenSave::OnDefaultAoP(wxCommandEvent &event)
{
    CheckBox_CustomDefault->SetValue(event.GetExtraLong());
    OnDefault("\\Steam\\steamapps\\common\\Age2HD");
    wxString locale = LanguageBox->GetValue();

	CheckBox_GenieVer->SetSelection(EV_Cysion);
    CheckBox_LangWrite->Enable(false);
	if(!ForceDat) Path_DatFileLocation->SetPath(game_path + "\\resources\\_common\\dat\\empires2_x2_p1.dat");
	Path_LangFileLocation->SetPath(game_path + "\\resources\\"+locale+"\\strings\\key-value\\key-value-strings-utf8.txt");
	Path_LangX1FileLocation->SetPath(game_path + "\\resources\\"+locale+"\\strings\\key-value\\key-value-modded-strings-utf8.txt");
	Path_LangX1P1FileLocation->SetPath(wxEmptyString);
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(false);
	CheckBox_LangX1FileLocation->SetValue(false);
	CheckBox_LangX1P1FileLocation->SetValue(false);
}

void AGE_OpenSave::OnDefaultSWGB(wxCommandEvent &event)
{
    CheckBox_CustomDefault->SetValue(event.GetExtraLong());
    OnDefault("\\GOG Games\\Star Wars - Galactic Battlegrounds");

	CheckBox_GenieVer->SetSelection(EV_SWGB);
	if(!ForceDat) Path_DatFileLocation->SetPath(game_path + "\\Game\\Data\\genie.dat");
	Path_LangFileLocation->SetPath(game_path + "\\Game\\language.dll");
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
    CheckBox_CustomDefault->SetValue(event.GetExtraLong());
    OnDefault("\\GOG Games\\Star Wars - Galactic Battlegrounds");

    if(event.GetExtraLong() == 1346980949)
    {
        CheckBox_GenieVer->SetSelection(EV_EF);
        if(!ForceDat) Path_DatFileLocation->SetPath(game_path + "\\Game\\Data\\genie_x2.dat");
        Path_LangX1P1FileLocation->SetPath(game_path + "\\Game\\language_x2.dll");
        CheckBox_LangX1P1FileLocation->SetValue(true);
    }
    else
    {
        CheckBox_GenieVer->SetSelection(EV_CC);
        if(!ForceDat) Path_DatFileLocation->SetPath(game_path + "\\Game\\Data\\genie_x1.dat");
        Path_LangX1P1FileLocation->SetPath(wxEmptyString);
        CheckBox_LangX1P1FileLocation->SetValue(false);
    }
    Path_LangFileLocation->SetPath(game_path + "\\Game\\language.dll");
    Path_LangX1FileLocation->SetPath(game_path + "\\Game\\language_x1.dll");
    Radio_DatFileLocation->SetValue(true);
    CheckBox_LangFileLocation->SetValue(true);
    CheckBox_LangX1FileLocation->SetValue(true);
    CheckBox_LangWrite->Enable(true);
}
