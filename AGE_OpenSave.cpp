#include "AGE_OpenSave.h"

AGE_OpenSave::AGE_OpenSave(wxWindow *parent, wxString title, wxDialog *slave)
: wxDialog(parent, -1, title+" files...", wxDefaultPosition, wxSize(500, 250), wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxNO_DEFAULT)
{
	ForceDat = false;
	Area = new wxBoxSizer(wxVERTICAL);
	Main = new wxBoxSizer(wxHORIZONTAL);
	Defaults = new wxBoxSizer(wxHORIZONTAL);
	Buttons = new wxBoxSizer(wxHORIZONTAL);

	ButtonOK = new wxButton(this, wxID_OK, title);
	ButtonCancel = new wxButton(this, wxID_CANCEL, "Cancel");
	Buttons->Add(ButtonOK, 1, wxEXPAND);
	Buttons->Add(ButtonCancel, 1, wxEXPAND);

	Button_DefaultAoE = new wxButton(slave, wxID_ANY, "AoE defaults");
	Button_DefaultRoR = new wxButton(slave, wxID_ANY, "RoR defaults");
	Button_DefaultAoK = new wxButton(slave, wxID_ANY, "AoK defaults");
	Button_DefaultTC = new wxButton(slave, wxID_ANY, "TC defaults");
	Button_DefaultAoKHD = new wxButton(slave, wxID_ANY, "AoK HD defaults");
	Button_DefaultSWGB = new wxButton(slave, wxID_ANY, "SWGB defaults");
	Button_DefaultCC = new wxButton(slave, wxID_ANY, "CC defaults");

	Defaults->Add(Button_DefaultAoE, 1, wxEXPAND);
	Defaults->Add(Button_DefaultRoR, 1, wxEXPAND);
	Defaults->Add(Button_DefaultAoK, 1, wxEXPAND);
	Defaults->Add(Button_DefaultTC, 1, wxEXPAND);
	Defaults->Add(Button_DefaultAoKHD, 1, wxEXPAND);
	Defaults->Add(Button_DefaultSWGB, 1, wxEXPAND);
	Defaults->Add(Button_DefaultCC, 1, wxEXPAND);

	Text_GenieVer = new wxStaticText(slave, wxID_ANY, "      Genie version:");
	CheckBox_GenieVer = new wxComboBox(slave, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	CheckBox_GenieVer->Append("TEST");
	CheckBox_GenieVer->Append("TEST.DAT");
	CheckBox_GenieVer->Append("MICKEY.DAT");
	CheckBox_GenieVer->Append("DAVE.DAT");
	CheckBox_GenieVer->Append("MATT.DAT < 6.92");
	CheckBox_GenieVer->Append("Age of Empires Beta (7.04 - 7.11)");
	//CheckBox_GenieVer->Append("Age of Empires Trial Beta 7.11");
	CheckBox_GenieVer->Append("Age of Empires (7.2 - 7.24)");
	//CheckBox_GenieVer->Append("Rise of Rome 7.24");
	CheckBox_GenieVer->Append("Age of Kings Alpha (10.19)");
	CheckBox_GenieVer->Append("Age of Kings Beta (11.05)");
	CheckBox_GenieVer->Append("Age of Kings (11.5)");
	CheckBox_GenieVer->Append("The Conquerors (11.76 - 12.0)");
	CheckBox_GenieVer->Append("Age of Empires II: HD Edition > 12");
	CheckBox_GenieVer->Append("Star Wars Galactic Battlegrounds (1.0 - 1.1)");
	//CheckBox_GenieVer->Append("Clone Campaigns 1.1");
	CheckBox_GenieVer->SetSelection(EV_TC);
	RecentText = new wxStaticText(slave, wxID_ANY, "      Recent paths:");
	CheckBox_Recent = new wxComboBox(slave, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);

	DriveLetterBox = new wxTextCtrl(slave, wxID_ANY, "C", wxDefaultPosition, wxSize(50, 20));
	LanguageBox = new wxTextCtrl(slave, wxID_ANY, "en", wxDefaultPosition, wxSize(50, 20));
	LanguageBox->SetToolTip("For AoK HD paths");
	CheckBox_CustomDefault = new wxCheckBox(slave, wxID_ANY, "Custom path override:");
	CheckBox_CustomDefault->SetValue(false);
	Path_CustomDefault = new wxDirPickerCtrl(slave, wxID_ANY, "", "Select a folder", wxDefaultPosition, wxSize(0, 20), wxDIRP_USE_TEXTCTRL | wxDIRP_DIR_MUST_EXIST);

	CheckBox_LangFileLocation = new wxCheckBox(slave, wxID_ANY, "Language file location:");
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation = new wxCheckBox(slave, wxID_ANY, "Language_x1.dll location:");
	CheckBox_LangX1FileLocation->SetValue(true);
	CheckBox_LangX1P1FileLocation = new wxCheckBox(slave, wxID_ANY, "Language_x1_p1.dll location:");
	CheckBox_LangX1P1FileLocation->SetValue(true);

	//SetDefaultItem(ButtonOK);
	//slave->SetDefaultItem(ButtonOK);
	Connect(CheckBox_Recent->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_OpenSave::OnRecent));
}

void AGE_OpenSave::OnRecent(wxCommandEvent &Event)
{
	auto sel = CheckBox_Recent->GetSelection();
	if(RecentDatVersions.size() == 0) return;
	CheckBox_GenieVer->SetSelection(RecentDatVersions[sel]);
	Path_DatFileLocation->SetPath(RecentDatPaths[sel]);
	Path_LangFileLocation->SetPath(RecentLangs[sel]);
	Path_LangX1FileLocation->SetPath(RecentLangX1s[sel]);
	Path_LangX1P1FileLocation->SetPath(RecentLangX1P1s[sel]);
	CheckBox_LangFileLocation->SetValue(RecentLangs[sel].size());
	CheckBox_LangX1FileLocation->SetValue(RecentLangX1s[sel].size());
	CheckBox_LangX1P1FileLocation->SetValue(RecentLangX1P1s[sel].size());
}
