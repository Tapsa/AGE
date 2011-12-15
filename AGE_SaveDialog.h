/* AGE_SaveDialog.h */

#include "wx/wx.h"
#include "wx/filepicker.h"

#ifndef AGESaveDialog_h
#define AGESaveDialog_h

class AGE_SaveDialog: public wxDialog
{
	public:

	AGE_SaveDialog(wxWindow *parent);

	/* Events */

	void OnDefaultAoE(wxCommandEvent& Event);
	void OnDefaultRoR(wxCommandEvent& Event);
	void OnDefaultAoK(wxCommandEvent& Event);
	void OnDefaultTC(wxCommandEvent& Event);
	void OnDefaultSWGB(wxCommandEvent& Event);
	void OnDefaultCC(wxCommandEvent& Event);
	void OnSelectDat(wxCommandEvent& Event);
	void OnSelectApf(wxCommandEvent& Event);
//	void OnSelectDrs(wxCommandEvent& Event);
	void OnOK(wxCommandEvent& Event);

	/* Member Variables */

	wxBoxSizer * SaveArea;
	wxBoxSizer * MainSave;
	wxBoxSizer * SaveDefaults;
	wxFlexGridSizer * SaveLayout;
	wxBoxSizer * SaveButtons;
	wxButton * Button_DefaultAoE;
	wxButton * Button_DefaultRoR;
	wxButton * Button_DefaultAoK;
	wxButton * Button_DefaultTC;
	wxButton * Button_DefaultSWGB;
	wxButton * Button_DefaultCC;
	wxStaticText * Text_GenieVer;
	wxComboBox * CheckBox_GenieVer;
	wxTextCtrl * DriveLetterBox;
	wxCheckBox * CheckBox_DatFileLocation;
	wxFilePickerCtrl * Path_DatFileLocation;
	wxCheckBox * CheckBox_UnzFileLocation;
	wxFilePickerCtrl * Path_UnzFileLocation;
	wxCheckBox * CheckBox_ApfFileLocation;
	wxFilePickerCtrl * Path_ApfFileLocation;
//	wxCheckBox * chDrsFileLocation;
//	wxFilePickerCtrl * fpDrsFileLocation;
	wxButton * SaveButtonOK;
	wxButton * SaveButtonCancel;
};

#endif
