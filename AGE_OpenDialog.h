#pragma once
#include "AGE_OpenSave.h"

class AGE_OpenDialog: public AGE_OpenSave
{
public:
    AGE_OpenDialog(wxWindow *parent, const wxFont &font);

    /* Events */

    void OnDefaultAoE(wxCommandEvent &event);
    void OnDefaultRoR(wxCommandEvent &event);
    void OnDefaultAoK(wxCommandEvent &event);
    void OnDefaultTC(wxCommandEvent &event);
    void OnDefaultAoKHD(wxCommandEvent &event);
    void OnDefaultAoP(wxCommandEvent &event);
    void OnDefaultSWGB(wxCommandEvent &event);
    void OnDefaultCC(wxCommandEvent &event);
    void OnRecent(wxCommandEvent &event);

    /* Member Variables */

    wxCheckBox *CheckBox_LangWriteToLatest;
    wxButton *Button_RawDecompress;
    wxFilePickerCtrl *Path_RawDecompress, *Path_DRS3;
    wxTextCtrl *TerrainsBox;
    AGE_PairedCheckBox *CheckBox_DRSPath, *CheckBox_DRSPath2, *CheckBox_DRSPath3;
    wxDirPickerCtrl *Path_DRS, *Path_DRS2;
};
