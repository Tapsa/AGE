#include "Common.hpp"
#include "AGE_TextControls.h"

#ifndef ComboBox_Byte_h
#define ComboBox_Byte_h

class ComboBox_Byte : public wxOwnerDrawnComboBox
{
	public:

	ComboBox_Byte(wxWindow * parent, TextCtrl_Byte * Pointer)
	: wxOwnerDrawnComboBox(parent, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY)
	{
		Container = Pointer;
		Container->ParentContainer = this;
		Container->Disconnect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Byte::OnKillFocus));
		Container->Connect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(ComboBox_Byte::OnKillFocus), this);

		Connect(this->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ComboBox_Byte::OnUpdate));
	}

//	Events

	void OnUpdate(wxCommandEvent& Event);
	void OnKillFocus(wxFocusEvent& Event);

//	Member Variables

	TextCtrl_Byte * Container;
};

#endif

#ifndef ComboBox_Float_h
#define ComboBox_Float_h

class ComboBox_Float : public wxOwnerDrawnComboBox
{
	public:

	ComboBox_Float(wxWindow * parent, TextCtrl_Float * Pointer)
	: wxOwnerDrawnComboBox(parent, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY)
	{
		Container = Pointer;
		Container->ParentContainer = this;
		Container->Disconnect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Float::OnKillFocus));
		Container->Connect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(ComboBox_Float::OnKillFocus), this);

		Connect(this->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ComboBox_Float::OnUpdate));
	}

//	Events

	void OnUpdate(wxCommandEvent& Event);
	void OnKillFocus(wxFocusEvent& Event);

//	Member Variables

	TextCtrl_Float * Container;
};

#endif

#ifndef ComboBox_Long_h
#define ComboBox_Long_h

class ComboBox_Long : public wxOwnerDrawnComboBox
{
	public:

	ComboBox_Long(wxWindow * parent, TextCtrl_Long * Pointer)
	: wxOwnerDrawnComboBox(parent, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY)
	{
		Container = Pointer;
		Container->ParentContainer = this;
		Container->Disconnect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Long::OnKillFocus));
		Container->Connect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(ComboBox_Long::OnKillFocus), this);

		Connect(this->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ComboBox_Long::OnUpdate));
	}

//	Events

	void OnUpdate(wxCommandEvent& Event);
	void OnKillFocus(wxFocusEvent& Event);

//	Member Variables

	TextCtrl_Long * Container;
};

#endif

#ifndef ComboBox_Short_h
#define ComboBox_Short_h

class ComboBox_Short : public wxOwnerDrawnComboBox
{
	public:

	ComboBox_Short(wxWindow * parent, TextCtrl_Short * Pointer)
	: wxOwnerDrawnComboBox(parent, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY)
	{
		Container = Pointer;
		Container->ParentContainer = this;
		Container->Disconnect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Short::OnKillFocus));
		Container->Connect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(ComboBox_Short::OnKillFocus), this);

		Connect(this->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ComboBox_Short::OnUpdate));
	}

//	Events

	void OnUpdate(wxCommandEvent& Event);
	void OnKillFocus(wxFocusEvent& Event);

//	Member Variables

	TextCtrl_Short * Container;
};

#endif

#ifndef ComboBox_Byte_EffectType_h
#define ComboBox_Byte_EffectType_h

class ComboBox_Byte_EffectType : public wxOwnerDrawnComboBox
{
	public:

	ComboBox_Byte_EffectType(wxWindow * parent, TextCtrl_Byte * Pointer)
	: wxOwnerDrawnComboBox(parent, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY)
	{
		Container = Pointer;
		Container->ParentContainer = this;
		Container->Disconnect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Byte::OnKillFocus));
		Container->Connect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(ComboBox_Byte_EffectType::OnKillFocus), this);

		Connect(this->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ComboBox_Byte_EffectType::OnUpdate));
	}

//	Events

	void OnUpdate(wxCommandEvent& Event);
	void OnKillFocus(wxFocusEvent& Event);

//	Member Variables

	TextCtrl_Byte * Container;
};

#endif
