#include "Common.h"

class AGE_OpenDialog: public wxDialog
{
	public:
	
	AGE_OpenDialog(wxWindow *parent, bool MustHaveDat = false);

	/* Events */

	void OnDefaultAoE(wxCommandEvent &Event);
	void OnDefaultRoR(wxCommandEvent &Event);
	void OnDefaultAoK(wxCommandEvent &Event);
	void OnDefaultTC(wxCommandEvent &Event);
	void OnDefaultAoKHD(wxCommandEvent &Event);
	void OnDefaultSWGB(wxCommandEvent &Event);
	void OnDefaultCC(wxCommandEvent &Event);
	void OnChangeDatRadio(wxCommandEvent &Event);
	void OnSelectLang(wxCommandEvent &Event);
	void OnSelectLangX1(wxCommandEvent &Event);
	void OnSelectLangX1P1(wxCommandEvent &Event);
//	void OnSelectDrs(wxCommandEvent &Event);
	void OnOK(wxCommandEvent &Event);
	
	/* Member Variables */
	
	wxBoxSizer *OpenArea;
	wxBoxSizer *MainOpen;
	wxBoxSizer *OpenDefaults;
	wxFlexGridSizer *OpenLayout;
	wxBoxSizer *OpenButtons;
	wxButton *Button_DefaultAoE;
	wxButton *Button_DefaultRoR;
	wxButton *Button_DefaultAoK;
	wxButton *Button_DefaultTC;
	wxButton *Button_DefaultAoKHD;
	wxButton *Button_DefaultSWGB;
	wxButton *Button_DefaultCC;
	wxStaticText *Text_GenieVer;
	wxComboBox *CheckBox_GenieVer;
	wxStaticText *DriveText;
	wxTextCtrl *DriveLetterBox;
	wxStaticText *WindowCountText;
	wxTextCtrl *WindowCountBox;
	wxStaticText *LanguageText;
	wxTextCtrl *LanguageBox;
	wxBoxSizer *DriveLetterArea;
	wxCheckBox *CheckBox_CustomDefault;
	wxDirPickerCtrl *Path_CustomDefault;
	wxRadioButton *Radio_DatFileLocation;
	wxFilePickerCtrl *Path_DatFileLocation;
	wxRadioButton *Radio_UnzFileLocation;
	wxFilePickerCtrl *Path_UnzFileLocation;
	wxRadioButton *Radio_ApfFileLocation;
	wxFilePickerCtrl *Path_ApfFileLocation;
//	wxRadioButton *Radio_NoFile;
	wxCheckBox *CheckBox_LangFileLocation;
	wxFilePickerCtrl *Path_LangFileLocation;
	wxCheckBox *CheckBox_LangX1FileLocation;
	wxFilePickerCtrl *Path_LangX1FileLocation;
	wxCheckBox *CheckBox_LangX1P1FileLocation;
	wxFilePickerCtrl *Path_LangX1P1FileLocation;
	wxCheckBox *CheckBox_LangWrite;
	wxCheckBox *CheckBox_LangWriteToLatest;
	wxButton *OpenButtonOK;
	wxButton *OpenButtonCancel;
};
