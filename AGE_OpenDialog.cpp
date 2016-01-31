#include "AGE_OpenDialog.h"

AGE_OpenDialog::AGE_OpenDialog(wxWindow *parent)
: AGE_OpenSave(parent, "Open", this)
{
    wxStaticText *TerrainsText = new wxStaticText(this, wxID_ANY, "      Terrains: ");
    TerrainsBox = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, 20));
    Path_DatFileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "Compressed data set (*.dat)|*.dat", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
    Button_RawDecompress = new wxButton(this, wxID_ANY, "Decompress only", wxDefaultPosition, wxSize(5, 20));
    Path_RawDecompress = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "Compressed genie file|*", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);

	Path_LangFileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "DLL or text (*.dll, *.txt)|*.dll;*.txt", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
	Path_LangX1FileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "DLL or text (*.dll, *.txt)|*.dll;*.txt", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
	Path_LangX1P1FileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "DLL or text (*.dll, *.txt)|*.dll;*.txt", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
	CheckBox_LangWrite = new wxCheckBox(this, wxID_ANY, "Write language files *");
	CheckBox_LangWrite->SetToolTip("WARNING! This feature is still experimental\nand affects reading too");
    CheckBox_LangWrite->SetBackgroundColour(wxColour(240, 200, 200));
	CheckBox_LangWriteToLatest = new wxCheckBox(this, wxID_ANY, "Write to the latest file instead of the base file *      Google Resource Hacker or Resource Tuner");
	CheckBox_LangWriteToLatest->SetToolTip("If you write to the latest file (x1/p1),\nyou only need to distribute that file,\nbut your edits will not affect the vanilla game");
    CheckBox_DRSPath = new wxCheckBox(this, wxID_ANY, "Path for DRS files *");
    CheckBox_DRSPath->SetToolTip("Path to the folder containing all drs files/folders");
    CheckBox_DRSPath2 = new wxCheckBox(this, wxID_ANY, "Path for mod DRS files");
    CheckBox_DRSPath3 = new wxCheckBox(this, wxID_ANY, "Extra 1st priority DRS file");
    Path_DRS = new wxDirPickerCtrl(this, wxID_ANY, "", "Select a folder", wxDefaultPosition, wxDefaultSize, wxDIRP_USE_TEXTCTRL | wxDIRP_DIR_MUST_EXIST);
    Path_DRS2 = new wxDirPickerCtrl(this, wxID_ANY, "", "Select a folder", wxDefaultPosition, wxDefaultSize, wxDIRP_USE_TEXTCTRL | wxDIRP_DIR_MUST_EXIST);
    Path_DRS3 = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "DRS (*.drs)|*.drs", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);

    Extras->Add(TerrainsText);
    Extras->Add(TerrainsBox);
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
	Layout->Add(CheckBox_DRSPath, 1, wxEXPAND);
	Layout->Add(Path_DRS, 1, wxEXPAND);
	Layout->Add(CheckBox_DRSPath2, 1, wxEXPAND);
	Layout->Add(Path_DRS2, 1, wxEXPAND);
	Layout->Add(CheckBox_DRSPath3, 1, wxEXPAND);
	Layout->Add(Path_DRS3, 1, wxEXPAND);
	Layout->AddSpacer(15);
	Layout->AddSpacer(15);

	Layout->AddGrowableCol(1, 1);
	Layout->AddGrowableRow(16, 1);

	Main->Add(Defaults, 0, wxALIGN_LEFT | wxTOP | wxLEFT | wxRIGHT, 5);
	Main->Add(Defaults_StarWars, 0, wxALIGN_LEFT | wxBOTTOM | wxLEFT | wxRIGHT, 5);
	Main->Add(Layout, 1, wxEXPAND | wxALL, 5);
	Main->Add(Buttons, 0, wxALIGN_RIGHT | wxALL, 5);

    TerrainsBox->Enable(false);
	SetSizerAndFit(Main);
    SetDefaultItem(ButtonOK);

	Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnOK));
	Connect(Radio_DatFileLocation->GetId(), wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(AGE_OpenDialog::OnChangeDatRadio));
	Connect(CheckBox_LangFileLocation->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnSelectLang));
	Connect(CheckBox_LangX1FileLocation->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnSelectLangX1));
	Connect(CheckBox_LangX1P1FileLocation->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnSelectLangX1P1));
	Connect(Button_RawDecompress->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_OpenDialog::OnDecompress));
}

void AGE_OpenDialog::OnDecompress(wxCommandEvent &event)
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

void AGE_OpenDialog::OnOK(wxCommandEvent &event)
{
	Path_DatFileLocation->Enable(event.GetId() == Radio_DatFileLocation->GetId());
	EndModal(wxID_OK);
}

void AGE_OpenDialog::OnDefaultAoE(wxCommandEvent &event)
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
	Path_LangX1FileLocation->SetPath(wxEmptyString);
	Path_LangX1P1FileLocation->SetPath(wxEmptyString);
	Path_DRS->SetPath(Path + "\\data");
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(false);
	CheckBox_LangX1P1FileLocation->SetValue(false);
	CheckBox_DRSPath->SetValue(true);
	CheckBox_DRSPath->Enable(true);
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

void AGE_OpenDialog::OnDefaultRoR(wxCommandEvent &event)
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
	if(!ForceDat) Path_DatFileLocation->SetPath(wxString(Path + "\\data2\\empires.dat"));
	Path_LangFileLocation->SetPath(wxString(Path + "\\language.dll"));
	Path_LangX1FileLocation->SetPath(wxString(Path + "\\languagex.dll"));
	Path_LangX1P1FileLocation->SetPath(wxEmptyString);
	Path_DRS->SetPath(Path + "\\data");
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(true);
	CheckBox_LangX1P1FileLocation->SetValue(false);
	CheckBox_DRSPath->SetValue(true);
	CheckBox_DRSPath->Enable(true);
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

void AGE_OpenDialog::OnDefaultAoK(wxCommandEvent &event)
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
	Path_LangX1FileLocation->SetPath(wxEmptyString);
	Path_LangX1P1FileLocation->SetPath(wxEmptyString);
	Path_DRS->SetPath(Path + "\\data");
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(false);
	CheckBox_LangX1P1FileLocation->SetValue(false);
	CheckBox_DRSPath->SetValue(true);
	CheckBox_DRSPath->Enable(true);
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

void AGE_OpenDialog::OnDefaultTC(wxCommandEvent &event)
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
	Path_DRS->SetPath(Path + "\\data");
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(true);
	CheckBox_LangX1P1FileLocation->SetValue(true);
	CheckBox_DRSPath->SetValue(true);
	CheckBox_DRSPath->Enable(true);
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

void AGE_OpenDialog::OnDefaultAoKHD(wxCommandEvent &event)
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

	CheckBox_GenieVer->SetSelection(EV_TC);
	if(!ForceDat) Path_DatFileLocation->SetPath(wxString(Path + "\\resources\\_common\\dat\\empires2_x1_p1.dat"));
	Path_LangFileLocation->SetPath(wxString(Path + "\\resources\\"+locale+"\\strings\\key-value\\key-value-strings-utf8.txt"));
	Path_LangX1FileLocation->SetPath(wxString(Path + "\\resources\\"+locale+"\\strings\\key-value\\key-value-modded-strings-utf8.txt"));
	Path_LangX1P1FileLocation->SetPath(wxEmptyString);
	Path_DRS->SetPath(wxString(Path + "\\resources\\_common\\drs"));
	TerrainsBox->ChangeValue("42");
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(true);
	CheckBox_LangX1P1FileLocation->SetValue(false);
	CheckBox_DRSPath->SetValue(true);
	CheckBox_DRSPath->Enable(false);
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

void AGE_OpenDialog::OnDefaultAoP(wxCommandEvent &event)
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
	if(!ForceDat) Path_DatFileLocation->SetPath(wxString(Path + "\\resources\\_common\\dat\\empires2_x2_p1.dat"));
	Path_LangFileLocation->SetPath(wxString(Path + "\\resources\\"+locale+"\\strings\\key-value\\key-value-strings-utf8.txt"));
	Path_LangX1FileLocation->SetPath(wxString(Path + "\\resources\\"+locale+"\\strings\\key-value\\key-value-modded-strings-utf8.txt"));
	Path_LangX1P1FileLocation->SetPath(wxEmptyString);
	Path_DRS->SetPath(wxString(Path + "\\resources\\_common\\drs"));
	TerrainsBox->ChangeValue("100");
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(true);
	CheckBox_LangX1P1FileLocation->SetValue(false);
	CheckBox_DRSPath->SetValue(true);
	CheckBox_DRSPath->Enable(false);
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

void AGE_OpenDialog::OnDefaultSWGB(wxCommandEvent &event)
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
	Path_LangX1FileLocation->SetPath(wxEmptyString);
	Path_LangX1P1FileLocation->SetPath(wxEmptyString);
	Path_DRS->SetPath(Path + "Game\\data");
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(false);
	CheckBox_LangX1P1FileLocation->SetValue(false);
	CheckBox_DRSPath->SetValue(true);
	CheckBox_DRSPath->Enable(true);
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

void AGE_OpenDialog::OnDefaultCC(wxCommandEvent &event)
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
	if(!ForceDat) Path_DatFileLocation->SetPath(wxString(Path + "Game\\Data\\genie_x1.dat"));
	Path_LangFileLocation->SetPath(wxString(Path + "Game\\language.dll"));
	Path_LangX1FileLocation->SetPath(wxString(Path + "Game\\language_x1.dll"));
	Path_LangX1P1FileLocation->SetPath(wxEmptyString);
	Path_DRS->SetPath(Path + "Game\\data");
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(true);
	CheckBox_LangX1P1FileLocation->SetValue(false);
	CheckBox_DRSPath->SetValue(true);
	CheckBox_DRSPath->Enable(true);
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

#ifdef WIN32
void AGE_OpenDialog::OnPathFromRegistry(wxCommandEvent &event)
{
    wxString path;
    switch(CheckBox_GenieVer->GetSelection())
    {
        case EV_AoE:
            break;
        case EV_RoR:
            break;
        case EV_AoK:
            break;
        case EV_TC:
            wxRegKey key(wxRegKey::HKLM, "Software\\Microsoft\\Microsoft Games\\Age of Empires II: The Conquerors Expansion\\1.0");
            if(key.Exists())
            {
                key.QueryValue("EXE Path", path)
            }
            break;
        case EV_Cysion:
            break;
        case EV_SWGB:
            break;
        case EV_CC:
            wxRegKey key(wxRegKey::HKLM, "Software\\LucasArts Entertainment Company LLC\\Star Wars Galactic Battlegrounds: Clone Campaigns\\1.0");
            if(key.Exists())
            {
                key.QueryValue("Game Path", path)
            }
            break;
        case EV_EF:
            wxRegKey key(wxRegKey::HKLM, "Software\\LucasArts Entertainment Company LLC\\Star Wars Galactic Battlegrounds: Expanding Fronts\\1.0");
            if(key.Exists())
            {
                key.QueryValue("Game Path", path)
            }
            break;
        default:
    }
}
#endif

void AGE_OpenDialog::OnChangeDatRadio(wxCommandEvent &event)
{
	Path_DatFileLocation->Enable(event.GetId() == Radio_DatFileLocation->GetId());
}

void AGE_OpenDialog::OnSelectLang(wxCommandEvent &event)
{
	Path_LangFileLocation->Enable(event.IsChecked());
}

void AGE_OpenDialog::OnSelectLangX1(wxCommandEvent &event)
{
	Path_LangX1FileLocation->Enable(event.IsChecked());
}

void AGE_OpenDialog::OnSelectLangX1P1(wxCommandEvent &event)
{
	Path_LangX1P1FileLocation->Enable(event.IsChecked());
}

void AGE_OpenDialog::OnRecent(wxCommandEvent &event)
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
    Path_DRS->SetPath(RecentValues[sel][5]);
    Path_DRS2->SetPath(RecentValues[sel][6]);
    Path_DRS3->SetPath(RecentValues[sel][7]);
}
