#pragma once
#include "AGE_OpenSave.h"

class AGE_SaveDialog: public AGE_OpenSave
{
public:
    AGE_SaveDialog(wxWindow *parent);

    /* Events */

    void OnDefaultAoE(wxCommandEvent &event);
    void OnDefaultRoR(wxCommandEvent &event);
    void OnDefaultAoK(wxCommandEvent &event);
    void OnDefaultTC(wxCommandEvent &event);
    void OnDefaultAoKHD(wxCommandEvent &event);
    void OnDefaultAoP(wxCommandEvent &event);
    void OnDefaultSWGB(wxCommandEvent &event);
    void OnDefaultCC(wxCommandEvent &event);
    void OnSelectDat(wxCommandEvent &event);
    void OnSelectApf(wxCommandEvent &event);
    void OnSelectLang(wxCommandEvent &event);
    void OnSelectLangX1(wxCommandEvent &event);
    void OnSelectLangX1P1(wxCommandEvent &event);
    void OnOK(wxCommandEvent &event);
#ifdef WIN32
    void OnPathFromRegistry(wxCommandEvent &event);
#endif
};
