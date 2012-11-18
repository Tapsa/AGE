#include "AGE_TextControls.h"

#ifndef AGE_ComboBoxes_h
#define AGE_ComboBoxes_h

class ComboBox_Byte: public wxOwnerDrawnComboBox
{
	public:

	ComboBox_Byte(wxWindow *parent, TextCtrl_Byte *Pointer):
	wxOwnerDrawnComboBox(parent, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY)
	{
		TextBox = Pointer;
		TextBox->LinkedBox = this;
		TextBox->Disconnect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Byte::OnKillFocus));
		// ..., NULL, this); because this is not the same class as to wich this is to be connected.
		TextBox->Connect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(ComboBox_Byte::OnKillFocus), NULL, this);

		Connect(GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ComboBox_Byte::OnUpdate));
	}

//	Events

	void OnUpdate(wxCommandEvent &Event);
	void OnKillFocus(wxFocusEvent &Event){SaveEdits();}
	bool SaveEdits();

//	Member Variables

	TextCtrl_Byte *TextBox;
};

class ComboBox_Float: public wxOwnerDrawnComboBox
{
	public:

	ComboBox_Float(wxWindow *parent, TextCtrl_Float *Pointer):
	wxOwnerDrawnComboBox(parent, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY)
	{
		TextBox = Pointer;
		TextBox->LinkedBox = this;
		TextBox->Disconnect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Float::OnKillFocus));
		TextBox->Connect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(ComboBox_Float::OnKillFocus), NULL, this);

		Connect(GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ComboBox_Float::OnUpdate));
	}

//	Events

	void OnUpdate(wxCommandEvent &Event);
	void OnKillFocus(wxFocusEvent &Event){SaveEdits();}
	bool SaveEdits();

//	Member Variables

	TextCtrl_Float *TextBox;
};

class ComboBox_Long: public wxOwnerDrawnComboBox
{
	public:

	ComboBox_Long(wxWindow *parent, TextCtrl_Long *Pointer):
	wxOwnerDrawnComboBox(parent, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY)
	{
		TextBox = Pointer;
		TextBox->LinkedBox = this;
		TextBox->Disconnect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Long::OnKillFocus));
		TextBox->Connect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(ComboBox_Long::OnKillFocus), NULL, this);

		Connect(GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ComboBox_Long::OnUpdate));
	}

//	Events

	void OnUpdate(wxCommandEvent &Event);
	void OnKillFocus(wxFocusEvent &Event){SaveEdits();}
	bool SaveEdits();

//	Member Variables

	TextCtrl_Long *TextBox;
};

class ComboBox_Short: public wxOwnerDrawnComboBox
{
	public:

	ComboBox_Short(wxWindow *parent, TextCtrl_Short *Pointer):
	wxOwnerDrawnComboBox(parent, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY)
	{
		TextBox = Pointer;
		TextBox->LinkedBox = this;
		TextBox->Disconnect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Short::OnKillFocus));
		TextBox->Connect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(ComboBox_Short::OnKillFocus), NULL, this);

		Connect(GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ComboBox_Short::OnUpdate));
	}

//	Events

	void OnUpdate(wxCommandEvent &Event);
	void OnKillFocus(wxFocusEvent &Event){SaveEdits();}
	bool SaveEdits();

//	Member Variables

	TextCtrl_Short *TextBox;
};

class ComboBox_Byte_EffectType: public wxOwnerDrawnComboBox
{
	public:

	ComboBox_Byte_EffectType(wxWindow *parent, TextCtrl_Byte *Pointer):
	wxOwnerDrawnComboBox(parent, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY)
	{
		TextBox = Pointer;
		TextBox->LinkedBox = this;
		TextBox->Disconnect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Byte::OnKillFocus));
		TextBox->Connect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(ComboBox_Byte_EffectType::OnKillFocus), NULL, this);

		Connect(GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ComboBox_Byte_EffectType::OnUpdate));
	}

//	Events

	void OnUpdate(wxCommandEvent &Event);
	void OnKillFocus(wxFocusEvent &Event){SaveEdits();}
	bool SaveEdits();

//	Member Variables

	TextCtrl_Byte *TextBox;
};

#endif
