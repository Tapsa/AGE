#include "AGE_OpenSave.h"

AGE_OpenSave::AGE_OpenSave(wxWindow *parent, wxString title)
: wxDialog(parent, -1, title+" files...", wxDefaultPosition, wxSize(500, 250), wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxNO_DEFAULT)
{
	ForceDat = false;
	Area = new wxBoxSizer(wxVERTICAL);
	Main = new wxBoxSizer(wxHORIZONTAL);
	Defaults = new wxBoxSizer(wxHORIZONTAL);
	Buttons = new wxBoxSizer(wxHORIZONTAL);

	Button_DefaultAoE = new wxButton(this, wxID_ANY, "AoE defaults");
	Button_DefaultRoR = new wxButton(this, wxID_ANY, "RoR defaults");
	Button_DefaultAoK = new wxButton(this, wxID_ANY, "AoK defaults");
	Button_DefaultTC = new wxButton(this, wxID_ANY, "TC defaults");
	Button_DefaultAoKHD = new wxButton(this, wxID_ANY, "AoK HD defaults");
	Button_DefaultSWGB = new wxButton(this, wxID_ANY, "SWGB defaults");
	Button_DefaultCC = new wxButton(this, wxID_ANY, "CC defaults");

	Defaults->Add(Button_DefaultAoE, 1, wxEXPAND);
	Defaults->Add(Button_DefaultRoR, 1, wxEXPAND);
	Defaults->Add(Button_DefaultAoK, 1, wxEXPAND);
	Defaults->Add(Button_DefaultTC, 1, wxEXPAND);
	Defaults->Add(Button_DefaultAoKHD, 1, wxEXPAND);
	Defaults->Add(Button_DefaultSWGB, 1, wxEXPAND);
	Defaults->Add(Button_DefaultCC, 1, wxEXPAND);

	Text_GenieVer = new wxStaticText(this, wxID_ANY, "      Genie version:");
	CheckBox_GenieVer = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
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
	CheckBox_GenieVer->Append("Star Wars Galactic Battlegrounds (1.0 - 1.1)");
	//CheckBox_GenieVer->Append("Clone Campaigns 1.1");
	CheckBox_GenieVer->SetSelection(EV_TC);

	DriveLetterBox = new wxTextCtrl(this, wxID_ANY, "C", wxDefaultPosition, wxSize(50, 20));
	LanguageBox = new wxTextCtrl(this, wxID_ANY, "en", wxDefaultPosition, wxSize(50, 20));
	LanguageBox->SetToolTip("For AoK HD paths");
	CheckBox_CustomDefault = new wxCheckBox(this, wxID_ANY, "Custom path override:");
	CheckBox_CustomDefault->SetValue(false);
	Path_CustomDefault = new wxDirPickerCtrl(this, wxID_ANY, "", "Select a folder", wxDefaultPosition, wxSize(0, 20), wxDIRP_USE_TEXTCTRL | wxDIRP_DIR_MUST_EXIST);

	CheckBox_LangFileLocation = new wxCheckBox(this, wxID_ANY, "Language.dll location:");
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation = new wxCheckBox(this, wxID_ANY, "Language_x1.dll location:");
	CheckBox_LangX1FileLocation->SetValue(true);
	CheckBox_LangX1P1FileLocation = new wxCheckBox(this, wxID_ANY, "Language_x1_p1.dll location:");
	CheckBox_LangX1P1FileLocation->SetValue(true);

	ButtonOK = new wxButton(this, wxID_OK, "OK");
	ButtonCancel = new wxButton(this, wxID_CANCEL, "Cancel");

	Buttons->Add(ButtonOK, 1, wxEXPAND);
	Buttons->Add(ButtonCancel, 1, wxEXPAND);

	SetDefaultItem(ButtonOK);
}
