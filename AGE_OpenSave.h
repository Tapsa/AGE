#include "Common.h"

#ifndef AGE_OpenSave_h
#define AGE_OpenSave_h

class AGE_OpenSave: public wxDialog
{
public:
	AGE_OpenSave(wxWindow *parent, wxString title, wxDialog *slave);

	/* Events */

	virtual void OnDefaultAoE(wxCommandEvent &Event)=0;
	virtual void OnDefaultRoR(wxCommandEvent &Event)=0;
	virtual void OnDefaultAoK(wxCommandEvent &Event)=0;
	virtual void OnDefaultTC(wxCommandEvent &Event)=0;
	virtual void OnDefaultAoKHD(wxCommandEvent &Event)=0;
	virtual void OnDefaultFE(wxCommandEvent &Event)=0;
	virtual void OnDefaultAoP(wxCommandEvent &Event)=0;
	virtual void OnDefaultSWGB(wxCommandEvent &Event)=0;
	virtual void OnDefaultCC(wxCommandEvent &Event)=0;
	virtual void OnSelectLang(wxCommandEvent &Event)=0;
	virtual void OnSelectLangX1(wxCommandEvent &Event)=0;
	virtual void OnSelectLangX1P1(wxCommandEvent &Event)=0;
	virtual void OnOK(wxCommandEvent &Event)=0;
	void OnRecent(wxCommandEvent &Event);

	/* Member Variables */

	bool ForceDat, opener;
	wxBoxSizer *Main;
	wxBoxSizer *Defaults;
	wxFlexGridSizer *Layout;
	wxBoxSizer *Buttons;
	wxButton *Button_DefaultAoE;
	wxButton *Button_DefaultRoR;
	wxButton *Button_DefaultAoK;
	wxButton *Button_DefaultTC;
	wxButton *Button_DefaultAoKHD;
	wxButton *Button_DefaultFE;
	wxButton *Button_DefaultAP;
	wxButton *Button_DefaultSWGB;
	wxButton *Button_DefaultCC;
	wxStaticText *Text_GenieVer;
	wxComboBox *CheckBox_GenieVer;
	wxTextCtrl *DriveLetterBox;
	wxTextCtrl *LanguageBox;
	wxCheckBox *CheckBox_CustomDefault;
	wxDirPickerCtrl *Path_CustomDefault;
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
	wxStaticText *RecentText;
	wxComboBox *CheckBox_Recent;
	vector<wxArrayString> RecentValues;
};

#endif
