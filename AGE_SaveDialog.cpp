#include "AGE_SaveDialog.h"

AGE_SaveDialog::AGE_SaveDialog(wxWindow *parent)
: AGE_OpenSave(parent, "Save")
{
	Layout = new wxFlexGridSizer(7, 2, 2, 2);

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

	Path_LangFileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "Dynamic Link Library (*.dll)|*.dll", wxDefaultPosition, wxSize(0, 20), wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
	Path_LangX1FileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "Dynamic Link Library (*.dll)|*.dll", wxDefaultPosition, wxSize(0, 20), wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
	Path_LangX1P1FileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "Dynamic Link Library (*.dll)|*.dll", wxDefaultPosition, wxSize(0, 20), wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
	CheckBox_LangWrite = new wxCheckBox(this, wxID_ANY, "Save language files *");
	CheckBox_LangWrite->SetToolTip("WARNING! This feature is still experimental");

	DriveLetterBox->Show(false);
	LanguageBox->Show(false);
	CheckBox_CustomDefault->Show(false);
	Path_CustomDefault->Show(false);

	Layout->Add(Text_GenieVer, 1, wxEXPAND);
	Layout->Add(CheckBox_GenieVer, 1, wxEXPAND);
	Layout->Add(DriveLetterBox, 1, wxEXPAND);
	Layout->Add(LanguageBox, 1, wxEXPAND);
	Layout->AddSpacer(15);
	Layout->AddSpacer(15);
	Layout->Add(CheckBox_CustomDefault, 1, wxEXPAND);
	Layout->Add(Path_CustomDefault, 1, wxEXPAND);
	Layout->Add(CheckBox_DatFileLocation, 1, wxEXPAND);
	Layout->Add(Path_DatFileLocation, 1, wxEXPAND);
	Layout->Add(CheckBox_UnzFileLocation, 1, wxEXPAND);
	Layout->Add(Path_UnzFileLocation, 1, wxEXPAND);
	Layout->Add(CheckBox_ApfFileLocation, 1, wxEXPAND);
	Layout->Add(Path_ApfFileLocation, 1, wxEXPAND);
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

	Layout->AddGrowableCol(1, 1);
	Layout->AddGrowableRow(1, 1);
	Layout->AddGrowableRow(5, 1);

	Area->AddSpacer(5);
	Area->Add(Defaults, 0, wxALIGN_CENTRE);
	Area->AddSpacer(15);
	Area->Add(Layout, 1, wxEXPAND);
	Area->AddSpacer(15);
	Area->Add(Buttons, 0, wxALIGN_RIGHT);
	Area->AddSpacer(5);

	Main->AddSpacer(5);
	Main->Add(Area, 1, wxEXPAND);
	Main->AddSpacer(5);

	this->SetSizerAndFit(Main);

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
	if(!ForceDat) Path_DatFileLocation->SetPath(wxString(Path + "\\data\\empires.dat"));
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

	CheckBox_GenieVer->SetSelection(EV_AoE);
	if(!ForceDat) Path_DatFileLocation->SetPath(wxString(Path + "\\data2\\empires.dat"));
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
	if(!ForceDat) Path_DatFileLocation->SetPath(wxString(Path + "\\data\\empires2.dat"));
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
	if(!ForceDat) Path_DatFileLocation->SetPath(wxString(Path + "\\data\\empires2_x1_p1.dat"));
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
	if(!ForceDat) Path_DatFileLocation->SetPath(wxString(Path + "\\Data\\empires2_x1_p1.dat"));
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
	if(!ForceDat) Path_DatFileLocation->SetPath(wxString(Path + "Game\\Data\\genie.dat"));
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

	CheckBox_GenieVer->SetSelection(EV_SWGB);
	if(!ForceDat) Path_DatFileLocation->SetPath(wxString(Path + "Game\\Data\\genie_x1.dat"));
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
