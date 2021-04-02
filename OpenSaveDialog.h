#pragma once
#include <vector>
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/filepicker.h>
#include <wx/odcombo.h>
#include <wx/sizer.h>

class PairedCheckBox: public wxCheckBox
{
public:
    PairedCheckBox(wxWindow *parent, const wxString &label, wxWindow **pair);
    void DoSet3StateValue(wxCheckBoxState state) override;

private:
    wxWindow **window_pair;
};

class OpenSaveDialog : public wxDialog
{
public:
    OpenSaveDialog(wxWindow *parent, const wxString &title, wxDialog *slave, const wxFont &font);

    /* Events */

    void OnDefault(const wxString &part);
    virtual void OnDefaultAoE(wxCommandEvent &event);
    virtual void OnDefaultRoR(wxCommandEvent &event);
    virtual void OnDefaultDE1(wxCommandEvent &event);
    virtual void OnDefaultAoK(wxCommandEvent &event);
    virtual void OnDefaultTC(wxCommandEvent &event);
    virtual void OnDefaultAoKHD(wxCommandEvent &event);
    virtual void OnDefaultAoP(wxCommandEvent &event);
    virtual void OnDefaultDE2(wxCommandEvent &event);
    virtual void OnDefaultSWGB(wxCommandEvent &event);
    virtual void OnDefaultCC(wxCommandEvent &event);
    virtual void OnRecent(wxCommandEvent &event);

    /* Member Variables */

    bool ForceDat;
    int path_src = 0;
    wxBoxSizer *Main;
    wxBoxSizer *Defaults, *Defaults_StarWars;
    wxFlexGridSizer *Layout;
    wxBoxSizer *Buttons, *Extras;
    wxButton *Button_DefaultAoE;
    wxButton *Button_DefaultRoR;
    wxButton *Button_DefaultAoK;
    wxButton *Button_DefaultDE1;
    wxButton *Button_DefaultTC;
    wxButton *Button_DefaultAoKHD;
    wxButton *Button_DefaultAP;
    wxButton *Button_DefaultSWGB;
    wxButton *Button_DefaultCC;
    wxButton *Button_DefaultDE2;
    wxOwnerDrawnComboBox *ComboBox_GenieVer;
    wxTextCtrl *DriveLetterBox;
    wxTextCtrl *LanguageBox;
    PairedCheckBox *CheckBox_CustomDefault;
    wxDirPickerCtrl *Path_CustomDefault;
    PairedCheckBox *Radio_DatFileLocation;
    wxFilePickerCtrl *Path_DatFileLocation;
    PairedCheckBox *CheckBox_LangFileLocation;
    wxFilePickerCtrl *Path_LangFileLocation;
    PairedCheckBox *CheckBox_LangX1FileLocation;
    wxFilePickerCtrl *Path_LangX1FileLocation;
    PairedCheckBox *CheckBox_LangX1P1FileLocation;
    wxFilePickerCtrl *Path_LangX1P1FileLocation;
    wxCheckBox *CheckBox_LangWrite;
    wxButton *ButtonOK;
    wxButton *ButtonCancel;
    wxOwnerDrawnComboBox *CheckBox_Recent;
    std::vector<wxArrayString> RecentValues;

#ifdef WIN32
    wxButton *Button_PathFromRegistry;
    virtual void OnPathFromRegistry(wxCommandEvent &event);
#endif

protected:
    wxString game_path;
};
