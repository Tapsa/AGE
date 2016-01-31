#pragma once
#include "Common.h"

class AGE_OpenSave: public wxDialog
{
public:
    AGE_OpenSave(wxWindow *parent, wxString title, wxDialog *slave);

    /* Events */

    virtual void OnDefaultAoE(wxCommandEvent &event)=0;
    virtual void OnDefaultRoR(wxCommandEvent &event)=0;
    virtual void OnDefaultAoK(wxCommandEvent &event)=0;
    virtual void OnDefaultTC(wxCommandEvent &event)=0;
    virtual void OnDefaultAoKHD(wxCommandEvent &event)=0;
    virtual void OnDefaultAoP(wxCommandEvent &event)=0;
    virtual void OnDefaultSWGB(wxCommandEvent &event)=0;
    virtual void OnDefaultCC(wxCommandEvent &event)=0;
    virtual void OnSelectLang(wxCommandEvent &event)=0;
    virtual void OnSelectLangX1(wxCommandEvent &event)=0;
    virtual void OnSelectLangX1P1(wxCommandEvent &event)=0;
    virtual void OnOK(wxCommandEvent &event)=0;
    virtual void OnRecent(wxCommandEvent &event);

    /* Member Variables */

    bool ForceDat;
    wxBoxSizer *Main;
    wxBoxSizer *Defaults, *Defaults_StarWars;
    wxFlexGridSizer *Layout;
    wxBoxSizer *Buttons, *Extras;
    wxButton *Button_DefaultAoE;
    wxButton *Button_DefaultRoR;
    wxButton *Button_DefaultAoK;
    wxButton *Button_DefaultTC;
    wxButton *Button_DefaultAoKHD;
    wxButton *Button_DefaultAP;
    wxButton *Button_DefaultSWGB;
    wxButton *Button_DefaultCC;
    wxComboBox *CheckBox_GenieVer;
    wxTextCtrl *DriveLetterBox;
    wxTextCtrl *LanguageBox;
    wxCheckBox *CheckBox_CustomDefault;
    wxDirPickerCtrl *Path_CustomDefault;
    wxCheckBox *Radio_DatFileLocation;
    wxFilePickerCtrl *Path_DatFileLocation;
    wxCheckBox *CheckBox_LangFileLocation;
    wxFilePickerCtrl *Path_LangFileLocation;
    wxCheckBox *CheckBox_LangX1FileLocation;
    wxFilePickerCtrl *Path_LangX1FileLocation;
    wxCheckBox *CheckBox_LangX1P1FileLocation;
    wxFilePickerCtrl *Path_LangX1P1FileLocation;
    wxCheckBox *CheckBox_LangWrite;
    wxButton *ButtonOK;
    wxButton *ButtonCancel;
    wxComboBox *CheckBox_Recent;
    vector<wxArrayString> RecentValues;
    wxHyperlinkCtrl *Gift;

#ifdef WIN32
    wxButton *Button_PathFromRegistry;
    virtual void OnPathFromRegistry(wxCommandEvent &event)=0;
#endif
};
