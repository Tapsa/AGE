/* AGE_ComboBoxes.h */

#include "AGE_TextControls.h"
#include "wx/odcombo.h"

#ifndef ComboBox_Byte_h
#define ComboBox_Byte_h

class ComboBox_Byte : public wxOwnerDrawnComboBox
{
	public:

	ComboBox_Byte(wxWindow * parent, TextCtrl_Byte * value);
	~ComboBox_Byte(){}

	/* Events */

	void OnUpdate(wxCommandEvent& Event);
	void OnKillFocus(wxFocusEvent& Event);

	/* Member Variables */

	TextCtrl_Byte * Container;
};

#endif

#ifndef ComboBox_Float_h
#define ComboBox_Float_h

class ComboBox_Float : public wxOwnerDrawnComboBox
{
	public:

	ComboBox_Float(wxWindow * parent, TextCtrl_Float * value);
	~ComboBox_Float(){}

	/* Events */

	void OnUpdate(wxCommandEvent& Event);
	void OnKillFocus(wxFocusEvent& Event);

	/* Member Variables */

	TextCtrl_Float * Container;
};

#endif

#ifndef ComboBox_Long_h
#define ComboBox_Long_h

class ComboBox_Long : public wxOwnerDrawnComboBox
{
	public:

	ComboBox_Long(wxWindow * parent, TextCtrl_Long * value);
	~ComboBox_Long(){}

	/* Events */

	void OnUpdate(wxCommandEvent& Event);
	void OnKillFocus(wxFocusEvent& Event);

	/* Member Variables */

	TextCtrl_Long * Container;
};

#endif

#ifndef ComboBox_Short_h
#define ComboBox_Short_h

class ComboBox_Short : public wxOwnerDrawnComboBox
{
	public:

	ComboBox_Short(wxWindow * parent, TextCtrl_Short * value);
	~ComboBox_Short(){}

	/* Events */

	void OnUpdate(wxCommandEvent& Event);
	void OnKillFocus(wxFocusEvent& Event);

	/* Member Variables */

	TextCtrl_Short * Container;
};

#endif

#ifndef ComboBox_Byte_EffectType_h
#define ComboBox_Byte_EffectType_h

class ComboBox_Byte_EffectType : public wxOwnerDrawnComboBox
{
	public:

	ComboBox_Byte_EffectType(wxWindow * parent, TextCtrl_Byte * value);
	~ComboBox_Byte_EffectType(){}

	/* Events */

	void OnUpdate(wxCommandEvent& Event);
	void OnKillFocus(wxFocusEvent& Event);

	/* Member Variables */

	TextCtrl_Byte * Container;
};

#endif
/*
#ifndef ComboBox_Byte_UnitType_h
#define ComboBox_Byte_UnitType_h

class ComboBox_Byte_UnitType : public wxOwnerDrawnComboBox
{
	public:

	ComboBox_Byte_UnitType(wxWindow * parent, TextCtrl_Byte * value);
	~ComboBox_Byte_UnitType(){}

//	Events

	void OnUpdate(wxCommandEvent& Event);
	void OnKillFocus(wxFocusEvent& Event);

//	Member Variables

	TextCtrl_Byte * Container;
};

#endif*/
