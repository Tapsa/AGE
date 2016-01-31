#pragma once
#include "AGE_OpenSave.h"

class AGE_OpenDialog: public AGE_OpenSave
{
public:
    AGE_OpenDialog(wxWindow *parent);

    /* Events */

    void OnDefaultAoE(wxCommandEvent &event);
    void OnDefaultRoR(wxCommandEvent &event);
    void OnDefaultAoK(wxCommandEvent &event);
    void OnDefaultTC(wxCommandEvent &event);
    void OnDefaultAoKHD(wxCommandEvent &event);
    void OnDefaultAoP(wxCommandEvent &event);
    void OnDefaultSWGB(wxCommandEvent &event);
    void OnDefaultCC(wxCommandEvent &event);
    void OnChangeDatRadio(wxCommandEvent &event);
    void OnSelectLang(wxCommandEvent &event);
    void OnSelectLangX1(wxCommandEvent &event);
    void OnSelectLangX1P1(wxCommandEvent &event);
    void OnOK(wxCommandEvent &event);
    void OnDecompress(wxCommandEvent &event);
    void OnRecent(wxCommandEvent &event);

    /* Member Variables */

    wxCheckBox *CheckBox_LangWriteToLatest;
    wxButton *Button_RawDecompress;
    wxFilePickerCtrl *Path_RawDecompress, *Path_DRS3;
    wxTextCtrl *TerrainsBox;
    wxCheckBox *CheckBox_DRSPath, *CheckBox_DRSPath2, *CheckBox_DRSPath3;
    wxDirPickerCtrl *Path_DRS, *Path_DRS2;

#ifdef WIN32
    void OnPathFromRegistry(wxCommandEvent &event);
#endif
};
