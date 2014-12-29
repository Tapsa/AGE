#include "AGE_SaveDialog.h"

AGE_SaveDialog::AGE_SaveDialog(wxWindow *parent)
: wxDialog(parent, -1, "Save files...", wxDefaultPosition, wxSize(500, 250), wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxNO_DEFAULT)
{
	SaveArea = new wxBoxSizer(wxVERTICAL);
	MainSave = new wxBoxSizer(wxHORIZONTAL);
	SaveDefaults = new wxBoxSizer(wxHORIZONTAL);
	SaveLayout = new wxFlexGridSizer(7, 2, 2, 2);
	SaveButtons = new wxBoxSizer(wxHORIZONTAL);

	Button_DefaultAoE = new wxButton(this, wxID_ANY, "AoE defaults");
	Button_DefaultRoR = new wxButton(this, wxID_ANY, "RoR defaults");
	Button_DefaultAoK = new wxButton(this, wxID_ANY, "AoK defaults");
	Button_DefaultTC = new wxButton(this, wxID_ANY, "TC defaults");
	Button_DefaultAoKHD = new wxButton(this, wxID_ANY, "AoK HD defaults");
	Button_DefaultSWGB = new wxButton(this, wxID_ANY, "SWGB defaults");
	Button_DefaultCC = new wxButton(this, wxID_ANY, "CC defaults");

	SaveDefaults->Add(Button_DefaultAoE, 1, wxEXPAND);
	SaveDefaults->Add(Button_DefaultRoR, 1, wxEXPAND);
	SaveDefaults->Add(Button_DefaultAoK, 1, wxEXPAND);
	SaveDefaults->Add(Button_DefaultTC, 1, wxEXPAND);
	SaveDefaults->Add(Button_DefaultAoKHD, 1, wxEXPAND);
	SaveDefaults->Add(Button_DefaultSWGB, 1, wxEXPAND);
	SaveDefaults->Add(Button_DefaultCC, 1, wxEXPAND);

	Text_GenieVer = new wxStaticText(this, wxID_ANY, "      Genie version:");
	CheckBox_GenieVer = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	CheckBox_GenieVer->Append("TEST.DAT < 6.92");
	CheckBox_GenieVer->Append("DAVE.DAT");
	CheckBox_GenieVer->Append("MATT.DAT");
	CheckBox_GenieVer->Append("Age of Empires Beta 7.04");
	CheckBox_GenieVer->Append("Age of Empires Trial Beta 7.11");
	CheckBox_GenieVer->Append("Age of Empires 7.2");
	CheckBox_GenieVer->Append("Rise of Rome 7.24");
	CheckBox_GenieVer->Append("Age of Kings Alpha 10.19");
	CheckBox_GenieVer->Append("Age of Kings Beta 11.05");
	CheckBox_GenieVer->Append("Age of Kings 11.5");
	CheckBox_GenieVer->Append("The Conquerors 11.76");
	CheckBox_GenieVer->Append("Star Wars Galactic Battlegrounds 1.0");
	CheckBox_GenieVer->Append("Clone Campaigns 1.1");
	CheckBox_GenieVer->SetSelection(EV_TC);

	DriveLetterBox = new wxTextCtrl(this, wxID_ANY, "C", wxDefaultPosition, wxSize(50, 20));
	LanguageBox = new wxTextCtrl(this, wxID_ANY, "en", wxDefaultPosition, wxSize(50, 20));
	//LanguageBox->SetToolTip("For AoK HD paths");
	CheckBox_CustomDefault = new wxCheckBox(this, wxID_ANY, "Custom path override:");
	CheckBox_CustomDefault->SetValue(false);
	Path_CustomDefault = new wxDirPickerCtrl(this, wxID_ANY, "", "Select a folder", wxDefaultPosition, wxSize(0, 20), wxDIRP_USE_TEXTCTRL | wxDIRP_DIR_MUST_EXIST);
	CheckBox_DatFileLocation = new wxCheckBox(this, wxID_ANY, "Compressed Dat File (*.dat):");
	CheckBox_DatFileLocation->SetValue(true);
	Path_DatFileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "Compressed Dat File (*.dat)|*.dat", wxDefaultPosition, wxSize(0, 20), wxFLP_SAVE | wxFLP_USE_TEXTCTRL | wxFLP_OVERWRITE_PROMPT);
	CheckBox_UnzFileLocation = new wxCheckBox(this, wxID_ANY, "Decompressed Dat File (*.unz):");
	CheckBox_UnzFileLocation->Disable();
	Path_UnzFileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "Decompressed Dat File (*.unz)|*.unz", wxDefaultPosition, wxSize(0, 20), wxFLP_SAVE | wxFLP_USE_TEXTCTRL | wxFLP_OVERWRITE_PROMPT);
	Path_UnzFileLocation->Disable();
	CheckBox_ApfFileLocation = new wxCheckBox(this, wxID_ANY, "Patch File (*.apf):");
	Path_ApfFileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "Patch File (*.apf)|*.apf", wxDefaultPosition, wxSize(0, 20), wxFLP_SAVE | wxFLP_USE_TEXTCTRL | wxFLP_OVERWRITE_PROMPT);
	CheckBox_ApfFileLocation->Disable();
	Path_ApfFileLocation->Disable();

	CheckBox_LangFileLocation = new wxCheckBox(this, wxID_ANY, "Language.dll location:");
	CheckBox_LangFileLocation->Enable(false);
	Path_LangFileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "Dynamic Link Library (*.dll)|*.dll", wxDefaultPosition, wxSize(0, 20), wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
	CheckBox_LangX1FileLocation = new wxCheckBox(this, wxID_ANY, "Language_x1.dll location:");
	CheckBox_LangX1FileLocation->Enable(false);
	Path_LangX1FileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "Dynamic Link Library (*.dll)|*.dll", wxDefaultPosition, wxSize(0, 20), wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
	CheckBox_LangX1P1FileLocation = new wxCheckBox(this, wxID_ANY, "Language_x1_p1.dll location:");
	CheckBox_LangX1P1FileLocation->Enable(false);
	Path_LangX1P1FileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "Dynamic Link Library (*.dll)|*.dll", wxDefaultPosition, wxSize(0, 20), wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
	CheckBox_LangWrite = new wxCheckBox(this, wxID_ANY, "Save language files *");
	CheckBox_LangWrite->SetToolTip("WARNING! This feature is still experimental");

	wxString Path;
	Path = DriveLetterBox->GetValue();

	SaveLayout->Add(Text_GenieVer, 1, wxEXPAND);
	SaveLayout->Add(CheckBox_GenieVer, 1, wxEXPAND);
	SaveLayout->AddSpacer(15);
	SaveLayout->AddSpacer(15);
	SaveLayout->Add(CheckBox_DatFileLocation, 1, wxEXPAND);
	SaveLayout->Add(Path_DatFileLocation, 1, wxEXPAND);
	SaveLayout->Add(CheckBox_UnzFileLocation, 1, wxEXPAND);
	SaveLayout->Add(Path_UnzFileLocation, 1, wxEXPAND);
	SaveLayout->Add(CheckBox_ApfFileLocation, 1, wxEXPAND);
	SaveLayout->Add(Path_ApfFileLocation, 1, wxEXPAND);
	SaveLayout->AddSpacer(15);
	SaveLayout->AddSpacer(15);
	SaveLayout->Add(CheckBox_LangFileLocation, 1, wxEXPAND);
	SaveLayout->Add(Path_LangFileLocation, 1, wxEXPAND);
	SaveLayout->Add(CheckBox_LangX1FileLocation, 1, wxEXPAND);
	SaveLayout->Add(Path_LangX1FileLocation, 1, wxEXPAND);
	SaveLayout->Add(CheckBox_LangX1P1FileLocation, 1, wxEXPAND);
	SaveLayout->Add(Path_LangX1P1FileLocation, 1, wxEXPAND);
	SaveLayout->Add(CheckBox_LangWrite, 1, wxEXPAND);
	SaveLayout->AddSpacer(15);
	SaveLayout->AddSpacer(15);
	SaveLayout->AddSpacer(15);

	SaveLayout->AddGrowableCol(1, 1);
	SaveLayout->AddGrowableRow(1, 1);
	SaveLayout->AddGrowableRow(5, 1);

	SaveButtonOK = new wxButton(this, wxID_OK, "OK");
	SaveButtonCancel = new wxButton(this, wxID_CANCEL, "Cancel");

	SaveButtons->Add(SaveButtonOK, 1, wxEXPAND);
	SaveButtons->Add(SaveButtonCancel, 1, wxEXPAND);

	SaveArea->AddSpacer(5);
	SaveArea->Add(SaveDefaults, 0, wxALIGN_CENTRE);
	SaveArea->AddSpacer(15);
	SaveArea->Add(SaveLayout, 1, wxEXPAND);
	SaveArea->AddSpacer(15);
	SaveArea->Add(SaveButtons, 0, wxALIGN_RIGHT);
	SaveArea->AddSpacer(5);

	MainSave->AddSpacer(5);
	MainSave->Add(SaveArea, 1, wxEXPAND);
	MainSave->AddSpacer(5);

	CheckBox_GenieVer->Enable(false);
	DriveLetterBox->Show(false);
	LanguageBox->Show(false);
	CheckBox_CustomDefault->Show(false);
	Path_CustomDefault->Show(false);

	this->SetSizerAndFit(MainSave);

	Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_SaveDialog::OnOK));
	Connect(Button_DefaultAoE->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_SaveDialog::OnDefaultAoE));
	Connect(Button_DefaultRoR->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_SaveDialog::OnDefaultRoR));
	Connect(Button_DefaultAoK->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_SaveDialog::OnDefaultAoK));
	Connect(Button_DefaultTC->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_SaveDialog::OnDefaultTC));
	Connect(Button_DefaultAoKHD->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_SaveDialog::OnDefaultAoKHD));
	Connect(Button_DefaultSWGB->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_SaveDialog::OnDefaultSWGB));
	Connect(Button_DefaultCC->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_SaveDialog::OnDefaultCC));
	Connect(CheckBox_DatFileLocation->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_SaveDialog::OnSelectDat));
	Connect(CheckBox_ApfFileLocation->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_SaveDialog::OnSelectApf));
}

void AGE_SaveDialog::OnOK(wxCommandEvent &Event)
{
	EndModal(wxID_OK);
}

void AGE_SaveDialog::OnDefaultAoE(wxCommandEvent &Event)
{
	wxString Path = DriveLetterBox->GetValue(), Custom = Path_CustomDefault->GetPath();

	if(CheckBox_CustomDefault->GetValue() && Custom.size() > 0)
	{
		Path = Custom;
	}
	else if(wxIsPlatform64Bit())
	{
	    Path += ":\\Program Files (x86)\\Microsoft Games\\Age of Empires";
	}
	else
	{
	    Path += ":\\Program Files\\Microsoft Games\\Age of Empires";
	}

	CheckBox_GenieVer->SetSelection(EV_AoE);
	Path_DatFileLocation->SetPath(wxString(Path + "\\data\\empires.dat"));
	Path_LangFileLocation->SetPath(wxString(Path + "\\language.dll"));
	Path_LangX1FileLocation->SetPath(wxT(""));
	Path_LangX1P1FileLocation->SetPath(wxT(""));
	CheckBox_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(false);
	CheckBox_LangX1P1FileLocation->SetValue(false);
}

void AGE_SaveDialog::OnDefaultRoR(wxCommandEvent &Event)
{
	wxString Path = DriveLetterBox->GetValue(), Custom = Path_CustomDefault->GetPath();

	if(CheckBox_CustomDefault->GetValue() && Custom.size() > 0)
	{
		Path = Custom;
	}
	else if(wxIsPlatform64Bit())
	{
	    Path += ":\\Program Files (x86)\\Microsoft Games\\Age of Empires";
	}
	else
	{
	    Path += ":\\Program Files\\Microsoft Games\\Age of Empires";
	}

	CheckBox_GenieVer->SetSelection(EV_RoR);
	Path_DatFileLocation->SetPath(wxString(Path + "\\data2\\empires.dat"));
	Path_LangFileLocation->SetPath(wxString(Path + "\\language.dll"));
	Path_LangX1FileLocation->SetPath(wxString(Path + "\\languagex.dll"));
	Path_LangX1P1FileLocation->SetPath(wxT(""));
	CheckBox_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(true);
	CheckBox_LangX1P1FileLocation->SetValue(false);
}

void AGE_SaveDialog::OnDefaultAoK(wxCommandEvent &Event)
{
	wxString Path = DriveLetterBox->GetValue(), Custom = Path_CustomDefault->GetPath();

	if(CheckBox_CustomDefault->GetValue() && Custom.size() > 0)
	{
		Path = Custom;
	}
	else if(wxIsPlatform64Bit())
	{
	    Path += ":\\Program Files (x86)\\Microsoft Games\\Age of Empires II";
	}
	else
	{
	    Path += ":\\Program Files\\Microsoft Games\\Age of Empires II";
	}

	CheckBox_GenieVer->SetSelection(EV_AoK);
	Path_DatFileLocation->SetPath(wxString(Path + "\\data\\empires2.dat"));
	Path_LangFileLocation->SetPath(wxString(Path + "\\language.dll"));
	Path_LangX1FileLocation->SetPath(wxT(""));
	Path_LangX1P1FileLocation->SetPath(wxT(""));
	CheckBox_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(false);
	CheckBox_LangX1P1FileLocation->SetValue(false);
}

void AGE_SaveDialog::OnDefaultTC(wxCommandEvent &Event)
{
	wxString Path = DriveLetterBox->GetValue(), Custom = Path_CustomDefault->GetPath();

	if(CheckBox_CustomDefault->GetValue() && Custom.size() > 0)
	{
		Path = Custom;
	}
	else if(wxIsPlatform64Bit())
	{
	    Path += ":\\Program Files (x86)\\Microsoft Games\\Age of Empires II";
	}
	else
	{
	    Path += ":\\Program Files\\Microsoft Games\\Age of Empires II";
	}

	CheckBox_GenieVer->SetSelection(EV_TC);
	Path_DatFileLocation->SetPath(wxString(Path + "\\data\\empires2_x1_p1.dat"));
	Path_LangFileLocation->SetPath(wxString(Path + "\\language.dll"));
	Path_LangX1FileLocation->SetPath(wxString(Path + "\\language_x1.dll"));
	Path_LangX1P1FileLocation->SetPath(wxString(Path + "\\language_x1_p1.dll"));
	CheckBox_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(true);
	CheckBox_LangX1P1FileLocation->SetValue(true);
}

void AGE_SaveDialog::OnDefaultAoKHD(wxCommandEvent &Event)
{
	wxString Path = DriveLetterBox->GetValue(), Custom = Path_CustomDefault->GetPath(),
	Lang = LanguageBox->GetValue();

	if(CheckBox_CustomDefault->GetValue() && Custom.size() > 0)
	{
		Path = Custom;
	}
	else if(wxIsPlatform64Bit())
	{
	    Path += ":\\Program Files (x86)\\Steam\\steamapps\\common\\Age2HD";
	}
	else
	{
	    Path += ":\\Program Files\\Steam\\steamapps\\common\\Age2HD";
	}

	CheckBox_GenieVer->SetSelection(EV_TC);
	Path_DatFileLocation->SetPath(wxString(Path + "\\Data\\empires2_x1_p1.dat"));
	Path_LangFileLocation->SetPath(wxString(Path + "\\Bin\\" + Lang + "\\language.dll"));
	Path_LangX1FileLocation->SetPath(wxString(Path + "\\Bin\\" + Lang + "\\language_x1.dll"));
	Path_LangX1P1FileLocation->SetPath(wxString(Path + "\\Bin\\" + Lang + "\\language_x1_p1.dll"));
	CheckBox_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(true);
	CheckBox_LangX1P1FileLocation->SetValue(true);
}

void AGE_SaveDialog::OnDefaultSWGB(wxCommandEvent &Event)
{
	wxString Path = DriveLetterBox->GetValue(), Custom = Path_CustomDefault->GetPath();

	if(CheckBox_CustomDefault->GetValue() && Custom.size() > 0)
	{
		Path = Custom;
	}
	else if(wxIsPlatform64Bit())
	{
	    Path += ":\\Program Files (x86)\\LucasArts\\Star Wars Galactic Battlegrounds Saga\\";
	}
	else
	{
	    Path += ":\\Program Files\\LucasArts\\Star Wars Galactic Battlegrounds Saga\\";
	}

	CheckBox_GenieVer->SetSelection(EV_SWGB);
	Path_DatFileLocation->SetPath(wxString(Path + "Game\\Data\\genie.dat"));
	Path_LangFileLocation->SetPath(wxString(Path + "Game\\language.dll"));
	Path_LangX1FileLocation->SetPath(wxT(""));
	Path_LangX1P1FileLocation->SetPath(wxT(""));
	CheckBox_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(false);
	CheckBox_LangX1P1FileLocation->SetValue(false);
}

void AGE_SaveDialog::OnDefaultCC(wxCommandEvent &Event)
{
	wxString Path = DriveLetterBox->GetValue(), Custom = Path_CustomDefault->GetPath();

	if(CheckBox_CustomDefault->GetValue() && Custom.size() > 0)
	{
		Path = Custom;
	}
	else if(wxIsPlatform64Bit())
	{
	    Path += ":\\Program Files (x86)\\LucasArts\\Star Wars Galactic Battlegrounds Saga\\";
	}
	else
	{
	    Path += ":\\Program Files\\LucasArts\\Star Wars Galactic Battlegrounds Saga\\";
	}

	CheckBox_GenieVer->SetSelection(EV_CC);
	Path_DatFileLocation->SetPath(wxString(Path + "Game\\Data\\genie_x1.dat"));
	Path_LangFileLocation->SetPath(wxString(Path + "Game\\language.dll"));
	Path_LangX1FileLocation->SetPath(wxString(Path + "Game\\language_x1.dll"));
	Path_LangX1P1FileLocation->SetPath(wxT(""));
	CheckBox_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(true);
	CheckBox_LangX1P1FileLocation->SetValue(false);
}

void AGE_SaveDialog::OnSelectDat(wxCommandEvent &Event)
{
    Path_DatFileLocation->Enable(Event.IsChecked());
}

void AGE_SaveDialog::OnSelectApf(wxCommandEvent &Event)
{
    Path_ApfFileLocation->Enable(Event.IsChecked());
}

void AGE_SaveDialog::OnSelectLang(wxCommandEvent &Event)
{
	Path_LangFileLocation->Enable(Event.IsChecked());
}

void AGE_SaveDialog::OnSelectLangX1(wxCommandEvent &Event)
{
	Path_LangX1FileLocation->Enable(Event.IsChecked());
}

void AGE_SaveDialog::OnSelectLangX1P1(wxCommandEvent &Event)
{
    Path_LangX1P1FileLocation->Enable(Event.IsChecked());
}
