#include "AGE_OpenSave.h"

#ifndef AGE_OpenDialog_H
#define AGE_OpenDialog_H

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
	void OnDefaultFE(wxCommandEvent &event);
	void OnDefaultAoP(wxCommandEvent &event);
	void OnDefaultSWGB(wxCommandEvent &event);
	void OnDefaultCC(wxCommandEvent &event);
	void OnChangeDatRadio(wxCommandEvent &event);
	void OnSelectLang(wxCommandEvent &event);
	void OnSelectLangX1(wxCommandEvent &event);
	void OnSelectLangX1P1(wxCommandEvent &event);
	void OnOK(wxCommandEvent &event);
	void OnDecompress(wxCommandEvent &event);
    void OnRecent(wxCommandEvent &Event);

	/* Member Variables */

	wxStaticText *DriveText;
	wxStaticText *LanguageText;
	wxBoxSizer *DriveLetterArea;
	wxCheckBox *Radio_DatFileLocation;
	wxCheckBox *CheckBox_LangWriteToLatest;
	wxButton *Button_RawDecompress;
	wxFilePickerCtrl *Path_RawDecompress;
	wxStaticText *TerrainsText;
	wxTextCtrl *TerrainsBox;
    wxStaticText *DRSPath;
    wxCheckBox *CheckBox_DRSPath, *CheckBox_DRSPath2;
    wxDirPickerCtrl *Path_DRS, *Path_DRS2;
};

#endif
