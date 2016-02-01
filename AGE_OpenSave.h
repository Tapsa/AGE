#pragma once
#include "Common.h"

class AGE_PairedCheckBox: public wxCheckBox
{
public:
    AGE_PairedCheckBox(wxWindow *parent, const wxString &label, wxWindow **pair);
    void DoSet3StateValue(wxCheckBoxState state);

private:
    wxWindow **window_pair;
};

class AGE_OpenSave: public wxDialog
{
public:
    AGE_OpenSave(wxWindow *parent, const wxString &title, wxDialog *slave);

    /* Events */

    void OnDefault(const wxString &part);
    virtual void OnDefaultAoE(wxCommandEvent &event);
    virtual void OnDefaultRoR(wxCommandEvent &event);
    virtual void OnDefaultAoK(wxCommandEvent &event);
    virtual void OnDefaultTC(wxCommandEvent &event);
    virtual void OnDefaultAoKHD(wxCommandEvent &event);
    virtual void OnDefaultAoP(wxCommandEvent &event);
    virtual void OnDefaultSWGB(wxCommandEvent &event);
    virtual void OnDefaultCC(wxCommandEvent &event);
    virtual void OnOK(wxCommandEvent &event);
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
    AGE_PairedCheckBox *CheckBox_CustomDefault;
    wxDirPickerCtrl *Path_CustomDefault;
    AGE_PairedCheckBox *Radio_DatFileLocation;
    wxFilePickerCtrl *Path_DatFileLocation;
    AGE_PairedCheckBox *CheckBox_LangFileLocation;
    wxFilePickerCtrl *Path_LangFileLocation;
    AGE_PairedCheckBox *CheckBox_LangX1FileLocation;
    wxFilePickerCtrl *Path_LangX1FileLocation;
    AGE_PairedCheckBox *CheckBox_LangX1P1FileLocation;
    wxFilePickerCtrl *Path_LangX1P1FileLocation;
    wxCheckBox *CheckBox_LangWrite;
    wxButton *ButtonOK;
    wxButton *ButtonCancel;
    wxComboBox *CheckBox_Recent;
    vector<wxArrayString> RecentValues;
    wxHyperlinkCtrl *Gift;

#ifdef WIN32
    wxButton *Button_PathFromRegistry;
    virtual void OnPathFromRegistry(wxCommandEvent &event);
#endif

protected:
    wxString game_path;
};
