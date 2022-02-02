#pragma once
#include "OpenSaveDialog.h"

class OpenDialog : public OpenSaveDialog
{
public:
    OpenDialog(wxWindow *parent, const wxFont &font);

    /* Events */

    void OnDefaultAoE(wxCommandEvent &event) override;
    void OnDefaultRoR(wxCommandEvent &event) override;
    void OnDefaultDE1(wxCommandEvent &event) override;
    void OnDefaultAoK(wxCommandEvent &event) override;
    void OnDefaultTC(wxCommandEvent &event) override;
    void OnDefaultAoKHD(wxCommandEvent &event) override;
    void OnDefaultAoP(wxCommandEvent &event) override;
    void OnDefaultDE2(wxCommandEvent &event) override;
    void OnDefaultSWGB(wxCommandEvent &event) override;
    void OnDefaultCC(wxCommandEvent &event) override;
    void OnRecent(wxCommandEvent &event) override;

    /* Member Variables */

    wxCheckBox *CheckBox_LangWriteToLatest;
    wxButton *Button_RawDecompress;
    wxFilePickerCtrl *Path_RawDecompress, *Path_DRS3, *Path_Palettes,
        *Path_PlayerColorPalette, *Path_CustomNames;
    wxTextCtrl *TerrainsBox;
    PairedCheckBox *CheckBox_DRSPath, *CheckBox_DRSPath2, *CheckBox_DRSPath3,
       *CheckBox_SlpPath, *CheckBox_ModSlpPath;
    wxDirPickerCtrl *Path_DRS, *Path_DRS2, *Path_SLP, *Path_ModSLP;
};
