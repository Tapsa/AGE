#include "AGE_OpenDialog.h"

AGE_OpenDialog::AGE_OpenDialog(wxWindow *parent)
: AGE_OpenSave(parent, "Open", this)
{
	Layout = new wxFlexGridSizer(2, 2, 2);

	DriveText = new wxStaticText(this, wxID_ANY, "      Drive letter:");
	WindowCountText = new wxStaticText(this, wxID_ANY, "      Windows (files) to open: * ");
	DriveLetterArea = new wxBoxSizer(wxHORIZONTAL);
	WindowCountBox = new wxTextCtrl(this, wxID_ANY, "2", wxDefaultPosition, wxSize(50, 20));
	WindowCountBox->SetToolTip("Open multiple editors to easily copy between files and game versions\nUse the normal copy and paste buttons\n4 windows seem to be the maximum");
	LanguageText = new wxStaticText(this, wxID_ANY, "      Language: * ");
	TerrainsText = new wxStaticText(this, wxID_ANY, "      Terrains: ");
	TerrainsBox = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, 20));
	Radio_DatFileLocation = new wxCheckBox(this, wxID_ANY, "Compressed data set (*.dat):");
	Path_DatFileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "Compressed data set (*.dat)|*.dat", wxDefaultPosition, wxSize(0, 20), wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
	Button_RawDecompress = new wxButton(this, wxID_ANY, "Decompress only", wxDefaultPosition, wxSize(5, 20));
	Path_RawDecompress = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "Compressed data set (*.dat)|*.dat", wxDefaultPosition, wxSize(0, 20), wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);

	Path_LangFileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "DLL or text (*.dll, *.txt)|*.dll;*.txt", wxDefaultPosition, wxSize(0, 20), wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
	Path_LangX1FileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "DLL or text (*.dll, *.txt)|*.dll;*.txt", wxDefaultPosition, wxSize(0, 20), wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
	Path_LangX1P1FileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "DLL or text (*.dll, *.txt)|*.dll;*.txt", wxDefaultPosition, wxSize(0, 20), wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
	CheckBox_LangWrite = new wxCheckBox(this, wxID_ANY, "Write language files *");
	CheckBox_LangWrite->SetToolTip("WARNING! This feature is still experimental\nand affects reading too");
	CheckBox_LangWriteToLatest = new wxCheckBox(this, wxID_ANY, "Write to the latest file instead of the base file *");
	CheckBox_LangWriteToLatest->SetToolTip("If you write to the latest file (x1/p1),\nyou only need to distribute that file,\nbut your edits will not affect the vanilla game");

	Layout->Add(Text_GenieVer, 1, wxEXPAND);
	Layout->Add(CheckBox_GenieVer, 1, wxEXPAND);
	Layout->Add(RecentText, 1, wxEXPAND);
	Layout->Add(CheckBox_Recent, 1, wxEXPAND);
	Layout->Add(DriveText, 1, wxEXPAND);
	DriveLetterArea->Add(DriveLetterBox, 0);
	DriveLetterArea->Add(WindowCountText, 0);
	DriveLetterArea->Add(WindowCountBox, 0);
	DriveLetterArea->Add(LanguageText, 0);
	DriveLetterArea->Add(LanguageBox, 0);
	DriveLetterArea->Add(TerrainsText, 0);
	DriveLetterArea->Add(TerrainsBox, 0);
	DriveLetterArea->AddStretchSpacer(1);
	Layout->Add(DriveLetterArea, 1, wxEXPAND);
	Layout->AddSpacer(15);
	Layout->AddSpacer(15);
	Layout->Add(CheckBox_CustomDefault, 1, wxEXPAND);
	Layout->Add(Path_CustomDefault, 1, wxEXPAND);
	Layout->Add(Radio_DatFileLocation, 1, wxEXPAND);
	Layout->Add(Path_DatFileLocation, 1, wxEXPAND);
	Layout->Add(Button_RawDecompress, 1, wxEXPAND);
	Layout->Add(Path_RawDecompress, 1, wxEXPAND);
	Layout->AddSpacer(15);
	Layout->AddSpacer(15);
	Layout->Add(CheckBox_LangFileLocation, 1, wxEXPAND);
	Layout->Add(Path_LangFileLocation, 1, wxEXPAND);
	Layout->Add(CheckBox_LangX1FileLocation, 1, wxEXPAND);
	Layout->Add(Path_LangX1FileLocation, 1, wxEXPAND);
	Layout->Add(CheckBox_LangX1P1FileLocation, 1, wxEXPAND);
	Layout->Add(Path_LangX1P1FileLocation, 1, wxEXPAND);
	Layout->Add(CheckBox_LangWrite, 1, wxEXPAND);
	Layout->Add(CheckBox_LangWriteToLatest, 1, wxEXPAND);
	Layout->AddSpacer(15);
	Layout->AddSpacer(15);

	Layout->AddGrowableCol(1, 1);
	Layout->AddGrowableRow(12, 1);

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

	SetSizerAndFit(Main);

	Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnOK));
	Connect(Button_DefaultAoE->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnDefaultAoE));
	Connect(Button_DefaultRoR->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnDefaultRoR));
	Connect(Button_DefaultAoK->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnDefaultAoK));
	Connect(Button_DefaultTC->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnDefaultTC));
	Connect(Button_DefaultAoKHD->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnDefaultAoKHD));
	Connect(Button_DefaultFE->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnDefaultFE));
	Connect(Button_DefaultSWGB->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnDefaultSWGB));
	Connect(Button_DefaultCC->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnDefaultCC));
	Connect(Radio_DatFileLocation->GetId(), wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(AGE_OpenDialog::OnChangeDatRadio));
	Connect(CheckBox_LangFileLocation->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnSelectLang));
	Connect(CheckBox_LangX1FileLocation->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnSelectLangX1));
	Connect(CheckBox_LangX1P1FileLocation->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnSelectLangX1P1));
	Connect(Button_RawDecompress->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnDecompress));
}

void AGE_OpenDialog::OnDecompress(wxCommandEvent &Event)
{
	genie::DatFile *raw;
	wxString filename = Path_RawDecompress->GetPath();
	wxString savename = filename+"u";
	if(!filename.empty())
	{
		raw = new genie::DatFile();
		raw->extractRaw(filename.c_str(), savename.c_str());
		delete raw;
	}
}

void AGE_OpenDialog::OnOK(wxCommandEvent &Event)
{
	Path_DatFileLocation->Enable(Event.GetId() == Radio_DatFileLocation->GetId());
	EndModal(wxID_OK);
}

void AGE_OpenDialog::OnDefaultAoE(wxCommandEvent &Event)
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
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(false);
	CheckBox_LangX1P1FileLocation->SetValue(false);
	wxCommandEvent Selected(wxEVT_COMMAND_RADIOBUTTON_SELECTED, Radio_DatFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
	Selected.SetInt(true);
	Selected.SetId(CheckBox_LangFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetInt(false);
	Selected.SetId(CheckBox_LangX1FileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetId(CheckBox_LangX1P1FileLocation->GetId());
	ProcessEvent(Selected);
}

void AGE_OpenDialog::OnDefaultRoR(wxCommandEvent &Event)
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
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(true);
	CheckBox_LangX1P1FileLocation->SetValue(false);
	wxCommandEvent Selected(wxEVT_COMMAND_RADIOBUTTON_SELECTED, Radio_DatFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
	Selected.SetInt(true);
	Selected.SetId(CheckBox_LangFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetId(CheckBox_LangX1FileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetInt(false);
	Selected.SetId(CheckBox_LangX1P1FileLocation->GetId());
	ProcessEvent(Selected);
}

void AGE_OpenDialog::OnDefaultAoK(wxCommandEvent &Event)
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
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(false);
	CheckBox_LangX1P1FileLocation->SetValue(false);
	wxCommandEvent Selected(wxEVT_COMMAND_RADIOBUTTON_SELECTED, Radio_DatFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
	Selected.SetInt(true);
	Selected.SetId(CheckBox_LangFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetInt(false);
	Selected.SetId(CheckBox_LangX1FileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetId(CheckBox_LangX1P1FileLocation->GetId());
	ProcessEvent(Selected);
}

void AGE_OpenDialog::OnDefaultTC(wxCommandEvent &Event)
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
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(true);
	CheckBox_LangX1P1FileLocation->SetValue(true);
	wxCommandEvent Selected(wxEVT_COMMAND_RADIOBUTTON_SELECTED, Radio_DatFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
	Selected.SetInt(true);
	Selected.SetId(CheckBox_LangFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetId(CheckBox_LangX1FileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetId(CheckBox_LangX1P1FileLocation->GetId());
	ProcessEvent(Selected);
}

void AGE_OpenDialog::OnDefaultAoKHD(wxCommandEvent &Event)
{
	CheckBox_LangWrite->Enable(false);
	wxString Path = DriveLetterBox->GetValue(), Custom = Path_CustomDefault->GetPath(),
	locale = LanguageBox->GetValue();

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

	CheckBox_GenieVer->SetSelection(EV_Cysion);
	if(!ForceDat) Path_DatFileLocation->SetPath(wxString(Path + "\\resources\\_common\\dat\\empires2_x1_p1.dat"));
	Path_LangFileLocation->SetPath(wxString(Path + "\\resources\\"+locale+"\\strings\\key-value\\key-value-strings-utf8.txt"));
	Path_LangX1FileLocation->SetPath(wxT(""));
	Path_LangX1P1FileLocation->SetPath(wxT(""));
	TerrainsBox->ChangeValue("42");
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(false);
	CheckBox_LangX1P1FileLocation->SetValue(false);
	wxCommandEvent Selected(wxEVT_COMMAND_RADIOBUTTON_SELECTED, Radio_DatFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
	Selected.SetInt(true);
	Selected.SetId(CheckBox_LangFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetInt(false);
	Selected.SetId(CheckBox_LangX1FileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetId(CheckBox_LangX1P1FileLocation->GetId());
	ProcessEvent(Selected);
}

void AGE_OpenDialog::OnDefaultFE(wxCommandEvent &Event)
{
	CheckBox_LangWrite->Enable(false);
	wxString Path = DriveLetterBox->GetValue(), Custom = Path_CustomDefault->GetPath(),
	locale = LanguageBox->GetValue();

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

	CheckBox_GenieVer->SetSelection(EV_Cysion);
	if(!ForceDat) Path_DatFileLocation->SetPath(wxString(Path + "\\resources-dlc2\\_common\\dat\\empires2_x2_p1.dat"));
	Path_LangFileLocation->SetPath(wxString(Path + "\\resources\\"+locale+"\\strings\\key-value\\key-value-strings-utf8.txt"));
	Path_LangX1FileLocation->SetPath(wxString(Path + "\\resources-dlc2\\"+locale+"\\strings\\key-value\\key-value-strings-utf8.txt"));
	Path_LangX1P1FileLocation->SetPath(wxT(""));
	TerrainsBox->ChangeValue("100");
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(true);
	CheckBox_LangX1P1FileLocation->SetValue(false);
	wxCommandEvent Selected(wxEVT_COMMAND_RADIOBUTTON_SELECTED, Radio_DatFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
	Selected.SetInt(true);
	Selected.SetId(CheckBox_LangFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetId(CheckBox_LangX1FileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetInt(false);
	Selected.SetId(CheckBox_LangX1P1FileLocation->GetId());
	ProcessEvent(Selected);
}

void AGE_OpenDialog::OnDefaultSWGB(wxCommandEvent &Event)
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
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(false);
	CheckBox_LangX1P1FileLocation->SetValue(false);
	wxCommandEvent Selected(wxEVT_COMMAND_RADIOBUTTON_SELECTED, Radio_DatFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
	Selected.SetInt(true);
	Selected.SetId(CheckBox_LangFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetInt(false);
	Selected.SetId(CheckBox_LangX1FileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetId(CheckBox_LangX1P1FileLocation->GetId());
	ProcessEvent(Selected);
}

void AGE_OpenDialog::OnDefaultCC(wxCommandEvent &Event)
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
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(true);
	CheckBox_LangX1P1FileLocation->SetValue(false);
	wxCommandEvent Selected(wxEVT_COMMAND_RADIOBUTTON_SELECTED, Radio_DatFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
	Selected.SetInt(true);
	Selected.SetId(CheckBox_LangFileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetId(CheckBox_LangX1FileLocation->GetId());
	ProcessEvent(Selected);
	Selected.SetInt(false);
	Selected.SetId(CheckBox_LangX1P1FileLocation->GetId());
	ProcessEvent(Selected);
}

void AGE_OpenDialog::OnChangeDatRadio(wxCommandEvent &Event)
{
	Path_DatFileLocation->Enable(Event.GetId() == Radio_DatFileLocation->GetId());
}

void AGE_OpenDialog::OnSelectLang(wxCommandEvent &Event)
{
	Path_LangFileLocation->Enable(Event.IsChecked());
}

void AGE_OpenDialog::OnSelectLangX1(wxCommandEvent &Event)
{
	Path_LangX1FileLocation->Enable(Event.IsChecked());
}

void AGE_OpenDialog::OnSelectLangX1P1(wxCommandEvent &Event)
{
	Path_LangX1P1FileLocation->Enable(Event.IsChecked());
}
