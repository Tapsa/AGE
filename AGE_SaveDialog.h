#include "Common.h"

class AGE_SaveDialog: public wxDialog
{
	public:

	AGE_SaveDialog(wxWindow *parent);

	/* Events */

	void OnDefaultAoE(wxCommandEvent &Event);
	void OnDefaultRoR(wxCommandEvent &Event);
	void OnDefaultAoK(wxCommandEvent &Event);
	void OnDefaultTC(wxCommandEvent &Event);
	void OnDefaultAoKHD(wxCommandEvent &Event);
	void OnDefaultSWGB(wxCommandEvent &Event);
	void OnDefaultCC(wxCommandEvent &Event);
	void OnSelectDat(wxCommandEvent &Event);
	void OnSelectApf(wxCommandEvent &Event);
	void OnSelectLang(wxCommandEvent &Event);
	void OnSelectLangX1(wxCommandEvent &Event);
	void OnSelectLangX1P1(wxCommandEvent &Event);
//	void OnSelectDrs(wxCommandEvent &Event);
	void OnOK(wxCommandEvent &Event);

	/* Member Variables */

	wxBoxSizer *SaveArea;
	wxBoxSizer *MainSave;
	wxBoxSizer *SaveDefaults;
	wxFlexGridSizer *SaveLayout;
	wxBoxSizer *SaveButtons;
	wxButton *Button_DefaultAoE;
	wxButton *Button_DefaultRoR;
	wxButton *Button_DefaultAoK;
	wxButton *Button_DefaultTC;
	wxButton *Button_DefaultAoKHD;
	wxButton *Button_DefaultSWGB;
	wxButton *Button_DefaultCC;
	wxStaticText *Text_GenieVer;
	wxComboBox *CheckBox_GenieVer;
	wxTextCtrl *DriveLetterBox;
	wxTextCtrl *LanguageBox;
	wxCheckBox *CheckBox_CustomDefault;
	wxDirPickerCtrl *Path_CustomDefault;
	wxCheckBox *CheckBox_DatFileLocation;
	wxFilePickerCtrl *Path_DatFileLocation;
	wxCheckBox *CheckBox_UnzFileLocation;
	wxFilePickerCtrl *Path_UnzFileLocation;
	wxCheckBox *CheckBox_ApfFileLocation;
	wxFilePickerCtrl *Path_ApfFileLocation;
	wxCheckBox *CheckBox_LangFileLocation;
	wxFilePickerCtrl *Path_LangFileLocation;
	wxCheckBox *CheckBox_LangX1FileLocation;
	wxFilePickerCtrl *Path_LangX1FileLocation;
	wxCheckBox *CheckBox_LangX1P1FileLocation;
	wxFilePickerCtrl *Path_LangX1P1FileLocation;
	wxCheckBox *CheckBox_LangWrite;
	wxButton *SaveButtonOK;
	wxButton *SaveButtonCancel;
};
