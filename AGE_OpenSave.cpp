#include "AGE_OpenSave.h"
#include "AGE_OpenDialog.h"

AGE_OpenSave::AGE_OpenSave(wxWindow *parent, wxString title, wxDialog *slave)
: wxDialog(parent, -1, title+" files...", wxDefaultPosition, wxSize(500, 250), wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxNO_DEFAULT)
{
    ForceDat = false;
	Main = new wxBoxSizer(wxVERTICAL);
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
	Button_DefaultFE = new wxButton(slave, wxID_ANY, "HD:TF defaults");
	Button_DefaultAP = new wxButton(slave, wxID_ANY, "HD:AK defaults");
	Button_DefaultSWGB = new wxButton(slave, wxID_ANY, "SWGB defaults");
	Button_DefaultCC = new wxButton(slave, wxID_ANY, "CC defaults");

	Defaults->Add(Button_DefaultAoE, 1, wxEXPAND);
	Defaults->Add(Button_DefaultRoR, 1, wxEXPAND);
	Defaults->Add(Button_DefaultAoK, 1, wxEXPAND);
	Defaults->Add(Button_DefaultTC, 1, wxEXPAND);
	Defaults->Add(Button_DefaultAoKHD, 1, wxEXPAND);
	Defaults->Add(Button_DefaultFE, 1, wxEXPAND);
	Defaults->Add(Button_DefaultAP, 1, wxEXPAND);
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
	CheckBox_GenieVer->Append("Age of Empires (7.2)");
	CheckBox_GenieVer->Append("Rise of Rome (7.24)");
	CheckBox_GenieVer->Append("Age of Kings Alpha (10.19)");
	CheckBox_GenieVer->Append("Age of Kings Beta (11.05)");
	CheckBox_GenieVer->Append("Age of Kings (11.5)");
	CheckBox_GenieVer->Append("The Conquerors (11.76)");
	CheckBox_GenieVer->Append("Age of Empires II: HD Edition > 12");
	CheckBox_GenieVer->Append("Star Wars Galactic Battlegrounds (1.0)");
	CheckBox_GenieVer->Append("Clone Campaigns (1.1)");
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
	CheckBox_LangX1FileLocation = new wxCheckBox(slave, wxID_ANY, "Language x1 file location:");
	CheckBox_LangX1FileLocation->SetValue(true);
	CheckBox_LangX1P1FileLocation = new wxCheckBox(slave, wxID_ANY, "Language p1 file location:");
	CheckBox_LangX1P1FileLocation->SetValue(true);

	//SetDefaultItem(ButtonOK);
	//slave->SetDefaultItem(ButtonOK);
	Connect(CheckBox_Recent->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_OpenSave::OnRecent));
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
