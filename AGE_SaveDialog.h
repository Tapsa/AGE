#include "AGE_OpenSave.h"

class AGE_SaveDialog: public AGE_OpenSave
{
public:
	AGE_SaveDialog(wxWindow *parent);

	/* Events */

	void OnDefaultAoE(wxCommandEvent &Event);
	void OnDefaultRoR(wxCommandEvent &Event);
	void OnDefaultAoK(wxCommandEvent &Event);
	void OnDefaultTC(wxCommandEvent &Event);
	void OnDefaultAoKHD(wxCommandEvent &Event);
	void OnDefaultFE(wxCommandEvent &Event);
	void OnDefaultAoP(wxCommandEvent &Event);
	void OnDefaultSWGB(wxCommandEvent &Event);
	void OnDefaultCC(wxCommandEvent &Event);
	void OnSelectDat(wxCommandEvent &Event);
	void OnSelectApf(wxCommandEvent &Event);
	void OnSelectLang(wxCommandEvent &Event);
	void OnSelectLangX1(wxCommandEvent &Event);
	void OnSelectLangX1P1(wxCommandEvent &Event);
	void OnOK(wxCommandEvent &Event);

	/* Member Variables */

	wxCheckBox *CheckBox_DatFileLocation;
};
