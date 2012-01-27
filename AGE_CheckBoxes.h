/* AGE_CheckBoxes.h */

#include "AGE_TextControls.h"

#ifndef CheckBox_Bool_h
#define CheckBox_Bool_h

class CheckBox_Bool : public wxCheckBox
{
	public:

	CheckBox_Bool(wxWindow * parent, string InitValue, TextCtrl_Bool * value);

	/* Events */

	void OnUpdate(wxCommandEvent& Event);
	void OnKillFocus(wxFocusEvent& Event);

	/* Member Variables */

	TextCtrl_Bool * Container;
};

#endif

#ifndef CheckBox_Byte_h
#define CheckBox_Byte_h

class CheckBox_Byte : public wxCheckBox
{
	public:

	CheckBox_Byte(wxWindow * parent, string InitValue, TextCtrl_Byte * value);

	/* Events */

	void OnUpdate(wxCommandEvent& Event);
	void OnKillFocus(wxFocusEvent& Event);

	/* Member Variables */

	TextCtrl_Byte * Container;
};

#endif

#ifndef CheckBox_Float_h
#define CheckBox_Float_h

class CheckBox_Float : public wxCheckBox
{
	public:

	CheckBox_Float(wxWindow * parent, string InitValue, TextCtrl_Float * value);

	/* Events */

	void OnUpdate(wxCommandEvent& Event);
	void OnKillFocus(wxFocusEvent& Event);

	/* Member Variables */

	TextCtrl_Float * Container;
};

#endif

#ifndef CheckBox_Short_h
#define CheckBox_Short_h

class CheckBox_Short : public wxCheckBox
{
	public:

	CheckBox_Short(wxWindow * parent, string InitValue, TextCtrl_Short * value);

	/* Events */

	void OnUpdate(wxCommandEvent& Event);
	void OnKillFocus(wxFocusEvent& Event);

	/* Member Variables */

	TextCtrl_Short * Container;
};

#endif

#ifndef CheckBox_Short_ZeroIsYes_h
#define CheckBox_Short_ZeroIsYes_h

class CheckBox_Short_ZeroIsYes : public wxCheckBox
{
	public:

	CheckBox_Short_ZeroIsYes(wxWindow * parent, string InitValue, TextCtrl_Short * value);

	/* Events */

	void OnUpdate(wxCommandEvent& Event);
	void OnKillFocus(wxFocusEvent& Event);

	/* Member Variables */

	TextCtrl_Short * Container;
};

#endif

#ifndef CheckBox_Long_ZeroIsYes_h
#define CheckBox_Long_ZeroIsYes_h

class CheckBox_Long_ZeroIsYes : public wxCheckBox
{
	public:

	CheckBox_Long_ZeroIsYes(wxWindow * parent, string InitValue, TextCtrl_Long * value);

	/* Events */

	void OnUpdate(wxCommandEvent& Event);
	void OnKillFocus(wxFocusEvent& Event);

	/* Member Variables */

	TextCtrl_Long * Container;
};

#endif
