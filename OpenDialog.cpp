#include "Common.h"
#include "CustomWidgets.h"
#include "OpenDialog.h"
#include "genie/dat/DatFile.h"

OpenDialog::OpenDialog(wxWindow *parent, const wxFont &font)
    : OpenSaveDialog(parent, "Open", this, font)
{
    SolidText *TerrainsText = new SolidText(this, "      Terrains: ");
    TerrainsBox = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1));
    Path_DatFileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "Compressed data set (*.dat)|*.dat", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
    Button_RawDecompress = new wxButton(this, wxID_ANY, "Decompress only", wxDefaultPosition, wxSize(5, -1));
    Path_RawDecompress = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "Compressed genie file|*", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);

    Path_LangFileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "DLL or text (*.dll, *.txt)|*.dll;*.txt", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
    Path_LangX1FileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "DLL or text (*.dll, *.txt)|*.dll;*.txt", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
    Path_LangX1P1FileLocation = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "DLL or text (*.dll, *.txt)|*.dll;*.txt", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
    CheckBox_LangWrite = new wxCheckBox(this, wxID_ANY, "Write language files *");
    CheckBox_LangWrite->SetToolTip("WARNING! This feature is still experimental\nand affects reading too");
    CheckBox_LangWrite->SetBackgroundColour(wxColour(240, 200, 200));
    CheckBox_LangWriteToLatest = new wxCheckBox(this, wxID_ANY, "Write to the latest file instead of the base file *      Google Resource Hacker or Resource Tuner");
    CheckBox_LangWriteToLatest->SetToolTip("If you write to the latest file (x1/p1),\nyou only need to distribute that file,\nbut your edits will not affect the vanilla game");
    CheckBox_DRSPath = new PairedCheckBox(this, "Path for DRS files *", (wxWindow **)&Path_DRS);
    CheckBox_DRSPath->SetToolTip("Path to the folder containing all drs files/folders");
    CheckBox_DRSPath2 = new PairedCheckBox(this, "Path for mod DRS files", (wxWindow **)&Path_DRS2);
    CheckBox_DRSPath3 = new PairedCheckBox(this, "Extra 1st priority DRS file", (wxWindow **)&Path_DRS3);
    CheckBox_SlpPath = new PairedCheckBox(this, "Path for loose SLP files", (wxWindow **)&Path_SLP);
    CheckBox_ModSlpPath = new PairedCheckBox(this, "Path for mod SLP files", (wxWindow **)&Path_ModSLP);
    SolidText *Text_PalettesPath = new SolidText(this, "Path for palette configuration *");
    Text_PalettesPath->SetToolTip("Used by Age of Empires DE and II DE");
    SolidText *Text_PlayerColorPalettePath = new SolidText(this, "Path for player color palette *");
    Text_PlayerColorPalettePath->SetToolTip("Used by Age of Empires DE and II DE");
    SolidText *Text_CustomNamesPath = new SolidText(this, "Path for custom names *");
    Text_CustomNamesPath->SetToolTip("Used to populate lists for attacks, armors, civilization resources, and terrain tables");
    Path_DRS = new wxDirPickerCtrl(this, wxID_ANY, "", "Select a folder", wxDefaultPosition, wxDefaultSize, wxDIRP_USE_TEXTCTRL | wxDIRP_DIR_MUST_EXIST);
    Path_DRS2 = new wxDirPickerCtrl(this, wxID_ANY, "", "Select a folder", wxDefaultPosition, wxDefaultSize, wxDIRP_USE_TEXTCTRL | wxDIRP_DIR_MUST_EXIST);
    Path_DRS3 = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "DRS (*.drs)|*.drs", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
    Path_SLP = new wxDirPickerCtrl(this, wxID_ANY, "", "Select a folder", wxDefaultPosition, wxDefaultSize, wxDIRP_USE_TEXTCTRL | wxDIRP_DIR_MUST_EXIST);
    Path_ModSLP = new wxDirPickerCtrl(this, wxID_ANY, "", "Select a folder", wxDefaultPosition, wxDefaultSize, wxDIRP_USE_TEXTCTRL | wxDIRP_DIR_MUST_EXIST);
    Path_Palettes = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "Configuration (*.conf)|*.conf", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
    Path_PlayerColorPalette = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "Palette (*.pal)|*.pal", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
    Path_CustomNames = new wxFilePickerCtrl(this, wxID_ANY, "", "Select a file", "Names (*.ini)|*.ini", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);

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
    Layout->Add(CheckBox_SlpPath, 1, wxEXPAND);
    Layout->Add(Path_SLP, 1, wxEXPAND);
    Layout->Add(CheckBox_ModSlpPath, 1, wxEXPAND);
    Layout->Add(Path_ModSLP, 1, wxEXPAND);
    Layout->Add(Text_PalettesPath, 1, wxEXPAND);
    Layout->Add(Path_Palettes, 1, wxEXPAND);
    Layout->Add(Text_PlayerColorPalettePath, 1, wxEXPAND);
    Layout->Add(Path_PlayerColorPalette, 1, wxEXPAND);
    Layout->Add(Text_CustomNamesPath, 1, wxEXPAND);
    Layout->Add(Path_CustomNames, 1, wxEXPAND);
    Layout->AddSpacer(15);
    Layout->AddSpacer(15);

    Layout->AddGrowableCol(1, 1);
    Layout->AddGrowableRow(21, 1);

    Main->Add(Defaults, 0, wxALIGN_LEFT | wxTOP | wxLEFT | wxRIGHT, 5);
    Main->Add(Defaults_StarWars, 0, wxALIGN_LEFT | wxBOTTOM | wxLEFT | wxRIGHT, 5);
    Main->Add(Layout, 1, wxEXPAND | wxALL, 5);
    Main->Add(Buttons, 0, wxALIGN_RIGHT | wxALL, 5);

    TerrainsBox->Enable(false);
    SetSizerAndFit(Main);

    Button_RawDecompress->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [this](wxCommandEvent &)
    {
        wxString filename = Path_RawDecompress->GetPath();
        wxString savename = filename + "u";
        if (!filename.empty())
        {
            genie::DatFile raw;
            raw.extractRaw(filename.c_str(), savename.c_str());
        }
    });

    ButtonOK->SetDefault();
    ButtonOK->SetFocus();
}

void OpenDialog::OnDefaultAoE(wxCommandEvent &event)
{
    OpenSaveDialog::OnDefaultAoE(event);

    Path_DRS->SetPath(game_path + "\\data");
    CheckBox_DRSPath->SetValue(true);
    TerrainsBox->ChangeValue("32");
}

void OpenDialog::OnDefaultRoR(wxCommandEvent &event)
{
    OpenSaveDialog::OnDefaultRoR(event);

    Path_DRS->SetPath(game_path + "\\data");
    CheckBox_DRSPath->SetValue(true);
    TerrainsBox->ChangeValue("32");
}

void OpenDialog::OnDefaultDE1(wxCommandEvent &event)
{
    OpenSaveDialog::OnDefaultDE1(event);

    CheckBox_LangFileLocation->SetValue(true);
    Path_DRS->SetPath(game_path + "\\Data\\DRS");
    Path_SLP->SetPath(game_path + "\\Assets\\SLP");
    Path_Palettes->SetPath(game_path + "\\Assets\\Palettes\\palettes.conf");
    Path_PlayerColorPalette->SetPath(game_path + "\\Assets\\Palettes\\playercolor_blue.pal");
    TerrainsBox->ChangeValue("96");
    CheckBox_DRSPath->SetValue(true);
}

void OpenDialog::OnDefaultAoK(wxCommandEvent &event)
{
    OpenSaveDialog::OnDefaultAoK(event);

    Path_DRS->SetPath(game_path + "\\data");
    CheckBox_DRSPath->SetValue(true);
    TerrainsBox->ChangeValue("32");
}

void OpenDialog::OnDefaultTC(wxCommandEvent &event)
{
    OpenSaveDialog::OnDefaultTC(event);

    Path_DRS->SetPath(game_path + "\\data");
    CheckBox_DRSPath->SetValue(true);
    TerrainsBox->ChangeValue("42");
}

void OpenDialog::OnDefaultAoKHD(wxCommandEvent &event)
{
    OpenSaveDialog::OnDefaultAoKHD(event);

    CheckBox_LangFileLocation->SetValue(true);
    CheckBox_LangX1FileLocation->SetValue(true);
    Path_DRS->SetPath(game_path + "\\resources\\_common\\drs");
    TerrainsBox->ChangeValue("42");
    CheckBox_DRSPath->SetValue(true);
}

void OpenDialog::OnDefaultAoP(wxCommandEvent &event)
{
    OpenSaveDialog::OnDefaultAoP(event);

    CheckBox_LangFileLocation->SetValue(true);
    CheckBox_LangX1FileLocation->SetValue(true);
    Path_DRS->SetPath(game_path + "\\resources\\_common\\drs");
    TerrainsBox->ChangeValue("100");
    CheckBox_DRSPath->SetValue(true);
}

void OpenDialog::OnDefaultDE2(wxCommandEvent &event)
{
    OpenSaveDialog::OnDefaultDE2(event);

    CheckBox_LangFileLocation->SetValue(true);
    CheckBox_LangX1FileLocation->SetValue(true);
    Path_DRS->SetPath(game_path + "\\resources\\_common\\drs");
    Path_SLP->SetPath(game_path + "\\resources\\_common\\drs\\graphics");
    Path_Palettes->SetPath(game_path + "\\resources\\_common\\palettes\\palettes.conf");
    Path_PlayerColorPalette->SetPath(game_path + "\\resources\\_common\\palettes\\playercolor_blue.pal");
    TerrainsBox->ChangeValue("200");
    CheckBox_DRSPath->SetValue(true);
}

void OpenDialog::OnDefaultSWGB(wxCommandEvent &event)
{
    OpenSaveDialog::OnDefaultSWGB(event);

    Path_DRS->SetPath(game_path + "\\data");
    CheckBox_DRSPath->SetValue(true);
    TerrainsBox->ChangeValue("55");
}

void OpenDialog::OnDefaultCC(wxCommandEvent &event)
{
    OpenSaveDialog::OnDefaultCC(event);

    Path_DRS->SetPath(game_path + "\\data");
    CheckBox_DRSPath->SetValue(true);
    TerrainsBox->ChangeValue("55");
}

void OpenDialog::OnRecent(wxCommandEvent &event)
{
    if (RecentValues.empty()) return;
    int sel = CheckBox_Recent->GetSelection();
    ComboBox_GenieVer->SetSelection(lexical_cast<int>(RecentValues[sel][0]));
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
    Path_SLP->SetPath(RecentValues[sel][8]);
    Path_ModSLP->SetPath(RecentValues[sel][9]);
    Path_Palettes->SetPath(RecentValues[sel][10]);
    Path_PlayerColorPalette->SetPath(RecentValues[sel][11]);
    Path_CustomNames->SetPath(RecentValues[sel][12]);
}
