#include "AGE_SaveDialog.h"

AGE_SaveDialog::AGE_SaveDialog(wxWindow *parent)
: AGE_OpenSave(parent, "Save", this)
{
    Radio_DatFileLocation->SetValue(true);
    Path_DatFileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "Compressed data set (*.dat)|*.dat", wxDefaultPosition, wxDefaultSize, wxFLP_SAVE | wxFLP_USE_TEXTCTRL | wxFLP_OVERWRITE_PROMPT);

    Path_LangFileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "DLL or text (*.dll, *.txt)|*.dll;*.txt", wxDefaultPosition, wxDefaultSize, wxFLP_SAVE | wxFLP_USE_TEXTCTRL | wxFLP_OVERWRITE_PROMPT);
    Path_LangX1FileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "DLL or text (*.dll, *.txt)|*.dll;*.txt", wxDefaultPosition, wxDefaultSize, wxFLP_SAVE | wxFLP_USE_TEXTCTRL | wxFLP_OVERWRITE_PROMPT);
    Path_LangX1P1FileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "DLL or text (*.dll, *.txt)|*.dll;*.txt", wxDefaultPosition, wxDefaultSize, wxFLP_SAVE | wxFLP_USE_TEXTCTRL | wxFLP_OVERWRITE_PROMPT);
    CheckBox_LangWrite = new wxCheckBox(this, wxID_ANY, "Save language files *");
    CheckBox_LangWrite->SetToolTip("WARNING! This feature is still experimental");

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

	Layout->AddGrowableCol(1, 1);
	Layout->AddGrowableRow(11, 1);

	Main->Add(Defaults, 0, wxALIGN_LEFT | wxTOP | wxLEFT | wxRIGHT, 5);
	Main->Add(Defaults_StarWars, 0, wxALIGN_LEFT | wxBOTTOM | wxLEFT | wxRIGHT, 5);
	Main->Add(Layout, 1, wxEXPAND | wxALL, 5);
	Main->Add(Buttons, 0, wxALIGN_RIGHT | wxALL, 5);

    SetSizerAndFit(Main);
    SetDefaultItem(ButtonOK);

    Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_SaveDialog::OnOK));
    Connect(Radio_DatFileLocation->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_SaveDialog::OnSelectDat));
}

void AGE_SaveDialog::OnOK(wxCommandEvent &event)
{
    EndModal(wxID_OK);
}

void AGE_SaveDialog::OnDefaultAoE(wxCommandEvent &event)
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
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(false);
	CheckBox_LangX1P1FileLocation->SetValue(false);
}

void AGE_SaveDialog::OnDefaultRoR(wxCommandEvent &event)
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
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(true);
	CheckBox_LangX1P1FileLocation->SetValue(false);
}

void AGE_SaveDialog::OnDefaultAoK(wxCommandEvent &event)
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
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(false);
	CheckBox_LangX1P1FileLocation->SetValue(false);
}

void AGE_SaveDialog::OnDefaultTC(wxCommandEvent &event)
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
}

void AGE_SaveDialog::OnDefaultAoKHD(wxCommandEvent &event)
{
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
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(false);
	CheckBox_LangX1FileLocation->SetValue(false);
	CheckBox_LangX1P1FileLocation->SetValue(false);
}

void AGE_SaveDialog::OnDefaultAoP(wxCommandEvent &event)
{
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
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(false);
	CheckBox_LangX1FileLocation->SetValue(false);
	CheckBox_LangX1P1FileLocation->SetValue(false);
}

void AGE_SaveDialog::OnDefaultSWGB(wxCommandEvent &event)
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
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(false);
	CheckBox_LangX1P1FileLocation->SetValue(false);
}

void AGE_SaveDialog::OnDefaultCC(wxCommandEvent &event)
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
	Radio_DatFileLocation->SetValue(true);
	CheckBox_LangFileLocation->SetValue(true);
	CheckBox_LangX1FileLocation->SetValue(true);
	CheckBox_LangX1P1FileLocation->SetValue(false);
}

#ifdef WIN32
void AGE_SaveDialog::OnPathFromRegistry(wxCommandEvent &event)
{
    switch(CheckBox_GenieVer->GetSelection())
    {
        case EV_AoE:
            break;
        case EV_RoR:
            break;
        case EV_AoK:
            break;
        case EV_TC:
            break;
        case EV_Cysion:
            break;
        case EV_SWGB:
            break;
        case EV_CC:
            break;
        case EV_EF:
            break;
        default:
    }
}
#endif

void AGE_SaveDialog::OnSelectDat(wxCommandEvent &event)
{
    Path_DatFileLocation->Enable(event.IsChecked());
}

void AGE_SaveDialog::OnSelectLang(wxCommandEvent &event)
{
    Path_LangFileLocation->Enable(event.IsChecked());
}

void AGE_SaveDialog::OnSelectLangX1(wxCommandEvent &event)
{
    Path_LangX1FileLocation->Enable(event.IsChecked());
}

void AGE_SaveDialog::OnSelectLangX1P1(wxCommandEvent &event)
{
    Path_LangX1P1FileLocation->Enable(event.IsChecked());
}
