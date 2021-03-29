#pragma once
#include "OpenSaveDialog.h"

class OpenDialog : public OpenSaveDialog
{
public:
    OpenDialog(wxWindow *parent, const wxFont &font);

    /* Events */

    void OnDefaultAoE(wxCommandEvent &event);
    void OnDefaultRoR(wxCommandEvent &event);
    void OnDefaultAoK(wxCommandEvent &event);
    void OnDefaultTC(wxCommandEvent &event);
    void OnDefaultAoKHD(wxCommandEvent &event);
    void OnDefaultAoP(wxCommandEvent &event);
    void OnDefaultDE2(wxCommandEvent &event);
    void OnDefaultSWGB(wxCommandEvent &event);
    void OnDefaultCC(wxCommandEvent &event);
    void OnRecent(wxCommandEvent &event);

    /* Member Variables */

    wxCheckBox *CheckBox_LangWriteToLatest;
    wxButton *Button_RawDecompress;
    wxFilePickerCtrl *Path_RawDecompress, *Path_DRS3, *Path_Palettes, *Path_PlayerColorPalette;
    wxTextCtrl *TerrainsBox;
    PairedCheckBox *CheckBox_DRSPath, *CheckBox_DRSPath2, *CheckBox_DRSPath3, *CheckBox_SlpPath;
    wxDirPickerCtrl *Path_DRS, *Path_DRS2, *Path_SLP;
};
