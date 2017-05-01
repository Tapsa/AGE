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
	Button_DefaultSWGB = new wxButton(this, wxID_ANY, "SWGB defaults");
	Button_DefaultCC = new wxButton(this, wxID_ANY, "CC defaults");

	SaveDefaults->Add(Button_DefaultAoE, 1, wxEXPAND);
	SaveDefaults->Add(Button_DefaultRoR, 1, wxEXPAND);
	SaveDefaults->Add(Button_DefaultAoK, 1, wxEXPAND);
	SaveDefaults->Add(Button_DefaultTC, 1, wxEXPAND);
	SaveDefaults->Add(Button_DefaultSWGB, 1, wxEXPAND);
	SaveDefaults->Add(Button_DefaultCC, 1, wxEXPAND);

	Text_GenieVer = new wxStaticText(this, wxID_ANY, "      Genie version:");
	CheckBox_GenieVer = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	CheckBox_GenieVer->Append("Age of Empires");
	CheckBox_GenieVer->Append("Rise of Rome");
	CheckBox_GenieVer->Append("Age of Kings Alpha 09.07.0222");
	CheckBox_GenieVer->Append("Age of Kings");
	CheckBox_GenieVer->Append("The Conquerors");
	CheckBox_GenieVer->Append("Star Wars Galactic Battlegrounds");
	CheckBox_GenieVer->Append("Clone Campaigns");
	CheckBox_GenieVer->SetSelection(4);

	DriveLetterBox = new wxTextCtrl(this, wxID_ANY, "C", wxDefaultPosition, wxSize(0, 20), 0/*, wxDefaultValidator, wxTextCtrlNameStr*/);
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
//	SaveLayout->Add(chDrsFileLocation, 1, wxEXPAND);
//	SaveLayout->Add(fpDrsFileLocation, 1, wxEXPAND);
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

	this->SetSizerAndFit(MainSave);

	Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_SaveDialog::OnOK));
	Connect(Button_DefaultAoE->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_SaveDialog::OnDefaultAoE));
	Connect(Button_DefaultRoR->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_SaveDialog::OnDefaultRoR));
	Connect(Button_DefaultAoK->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_SaveDialog::OnDefaultAoK));
	Connect(Button_DefaultTC->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_SaveDialog::OnDefaultTC));
	Connect(Button_DefaultSWGB->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_SaveDialog::OnDefaultSWGB));
	Connect(Button_DefaultCC->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_SaveDialog::OnDefaultCC));
	Connect(CheckBox_DatFileLocation->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_SaveDialog::OnSelectDat));
	Connect(CheckBox_ApfFileLocation->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_SaveDialog::OnSelectApf));
//	Connect(chDrsFileLocation->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_SaveDialog::OnSelectDrs));
}

void AGE_SaveDialog::OnOK(wxCommandEvent &Event)
{
	EndModal(wxID_OK);
}

void AGE_SaveDialog::OnDefaultAoE(wxCommandEvent &Event)
{
	wxString Path;
	Path = DriveLetterBox->GetValue();

	if(wxIsPlatform64Bit())
	{
	    Path += ":\\Program Files (x86)\\Microsoft Games\\";
	}
	else
	{
	    Path += ":\\Program Files\\Microsoft Games\\";
	}

	CheckBox_GenieVer->SetSelection(0);
	Path_DatFileLocation->SetPath(wxString(Path + "Age of Empires\\data\\Empires.dat"));
	Path_LangFileLocation->SetPath(wxString(Path + "Age of Empires\\language.dll"));
	Path_LangX1FileLocation->SetPath(wxT(""));
	Path_LangX1P1FileLocation->SetPath(wxT(""));
	CheckBox_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(false);
	CheckBox_LangX1P1FileLocation->SetValue(false);
}

void AGE_SaveDialog::OnDefaultRoR(wxCommandEvent &Event)
{
	wxString Path;
	Path = DriveLetterBox->GetValue();

	if(wxIsPlatform64Bit())
	{
	    Path += ":\\Program Files (x86)\\Microsoft Games\\";
	}
	else
	{
	    Path += ":\\Program Files\\Microsoft Games\\";
	}

	CheckBox_GenieVer->SetSelection(1);
	Path_DatFileLocation->SetPath(wxString(Path + "Age of Empires\\data2\\Empires.dat"));
	Path_LangFileLocation->SetPath(wxString(Path + "Age of Empires\\language.dll"));
	Path_LangX1FileLocation->SetPath(wxString(Path + "Age of Empires\\languagex.dll"));
	Path_LangX1P1FileLocation->SetPath(wxT(""));
	CheckBox_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(true);
	CheckBox_LangX1P1FileLocation->SetValue(false);
}

void AGE_SaveDialog::OnDefaultAoK(wxCommandEvent &Event)
{
	wxString Path;
	Path = DriveLetterBox->GetValue();

	if(wxIsPlatform64Bit())
	{
	    Path += ":\\Program Files (x86)\\Microsoft Games\\";
	}
	else
	{
	    Path += ":\\Program Files\\Microsoft Games\\";
	}

	CheckBox_GenieVer->SetSelection(3);
	Path_DatFileLocation->SetPath(wxString(Path + "Age of Empires II\\data\\Empires2.dat"));
	Path_LangFileLocation->SetPath(wxString(Path + "Age of Empires II\\language.dll"));
	Path_LangX1FileLocation->SetPath(wxT(""));
	Path_LangX1P1FileLocation->SetPath(wxT(""));
	CheckBox_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(false);
	CheckBox_LangX1P1FileLocation->SetValue(false);
}

void AGE_SaveDialog::OnDefaultTC(wxCommandEvent &Event)
{
	wxString Path;
	Path = DriveLetterBox->GetValue();

	if(wxIsPlatform64Bit())
	{
	    Path += ":\\Program Files (x86)\\Microsoft Games\\";
	}
	else
	{
	    Path += ":\\Program Files\\Microsoft Games\\";
	}

	CheckBox_GenieVer->SetSelection(4);
	Path_DatFileLocation->SetPath(wxString(Path + "Age of Empires II\\data\\Empires2_x1_p1.dat"));
	Path_LangFileLocation->SetPath(wxString(Path + "Age of Empires II\\language.dll"));
	Path_LangX1FileLocation->SetPath(wxString(Path + "Age of Empires II\\language_x1.dll"));
	Path_LangX1P1FileLocation->SetPath(wxString(Path + "Age of Empires II\\language_x1_p1.dll"));
	CheckBox_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(true);
	CheckBox_LangX1P1FileLocation->SetValue(true);
}

void AGE_SaveDialog::OnDefaultSWGB(wxCommandEvent &Event)
{
	wxString Path;
	Path = DriveLetterBox->GetValue();

	if(wxIsPlatform64Bit())
	{
	    Path += ":\\Program Files (x86)\\LucasArts\\Star Wars Galactic Battlegrounds Saga\\";
	}
	else
	{
	    Path += ":\\Program Files\\LucasArts\\Star Wars Galactic Battlegrounds Saga\\";
	}

	CheckBox_GenieVer->SetSelection(5);
	Path_DatFileLocation->SetPath(wxString(Path + "Game\\Data\\GENIE.DAT"));
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
	wxString Path;
	Path = DriveLetterBox->GetValue();

	if(wxIsPlatform64Bit())
	{
	    Path += ":\\Program Files (x86)\\LucasArts\\Star Wars Galactic Battlegrounds Saga\\";
	}
	else
	{
	    Path += ":\\Program Files\\LucasArts\\Star Wars Galactic Battlegrounds Saga\\";
	}

	CheckBox_GenieVer->SetSelection(6);
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
