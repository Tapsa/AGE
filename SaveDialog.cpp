#include "Common.h"
#include "SaveDialog.h"

SaveDialog::SaveDialog(wxWindow *parent, const wxFont &font)
    : OpenSaveDialog(parent, "Save", this, font)
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
    ButtonOK->SetDefault();
    ButtonOK->SetFocus();
}

void SaveDialog::OnDefaultDE1(wxCommandEvent &event)
{
    OpenSaveDialog::OnDefaultDE1(event);

    CheckBox_LangFileLocation->SetValue(false);
    CheckBox_LangX1FileLocation->SetValue(false);
}

void SaveDialog::OnDefaultAoKHD(wxCommandEvent &event)
{
    OpenSaveDialog::OnDefaultAoKHD(event);

    CheckBox_LangFileLocation->SetValue(false);
    CheckBox_LangX1FileLocation->SetValue(false);
}

void SaveDialog::OnDefaultAoP(wxCommandEvent &event)
{
    OpenSaveDialog::OnDefaultAoP(event);

    CheckBox_LangFileLocation->SetValue(false);
    CheckBox_LangX1FileLocation->SetValue(false);
}

void SaveDialog::OnDefaultDE2(wxCommandEvent &event)
{
    OpenSaveDialog::OnDefaultDE2(event);

    CheckBox_LangFileLocation->SetValue(false);
    CheckBox_LangX1FileLocation->SetValue(false);
}
