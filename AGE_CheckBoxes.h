#include "AGE_TextControls.h"

#ifndef AGE_CheckBoxes_h
#define AGE_CheckBoxes_h

class CheckBox_Byte: public wxCheckBox
{
	public:

	CheckBox_Byte(wxWindow *parent, string label, TextCtrl_Byte *Pointer):
	wxCheckBox(parent, wxID_ANY, label, wxDefaultPosition, wxSize(0, 20))
	{
		TextBox = Pointer;
		TextBox->LinkedBox = this;
		TextBox->Disconnect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Byte::OnKillFocus));
		TextBox->Connect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(CheckBox_Byte::OnKillFocus), NULL, this);

		Connect(GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CheckBox_Byte::OnUpdate));
	}

//	Events

	void OnUpdate(wxCommandEvent &Event);
	void OnKillFocus(wxFocusEvent &Event){SaveEdits();}
	bool SaveEdits();

//	Member Variables

	TextCtrl_Byte *TextBox;
};

class CheckBox_Float: public wxCheckBox
{
	public:

	CheckBox_Float(wxWindow *parent, string label, TextCtrl_Float *Pointer):
	wxCheckBox(parent, wxID_ANY, label, wxDefaultPosition, wxSize(0, 20))
	{
		TextBox = Pointer;
		TextBox->LinkedBox = this;
		TextBox->Disconnect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Float::OnKillFocus));
		TextBox->Connect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(CheckBox_Float::OnKillFocus), NULL, this);

		Connect(GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CheckBox_Float::OnUpdate));
	}

//	Events

	void OnUpdate(wxCommandEvent &Event);
	void OnKillFocus(wxFocusEvent &Event){SaveEdits();}
	bool SaveEdits();

//	Member Variables

	TextCtrl_Float *TextBox;
};

class CheckBox_Short: public wxCheckBox
{
	public:

	CheckBox_Short(wxWindow *parent, string label, TextCtrl_Short *Pointer):
	wxCheckBox(parent, wxID_ANY, label, wxDefaultPosition, wxSize(0, 20))
	{
		TextBox = Pointer;
		TextBox->LinkedBox = this;
		TextBox->Disconnect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Short::OnKillFocus));
		TextBox->Connect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(CheckBox_Short::OnKillFocus), NULL, this);

		Connect(GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CheckBox_Short::OnUpdate));
	}

//	Events

	void OnUpdate(wxCommandEvent &Event);
	void OnKillFocus(wxFocusEvent &Event){SaveEdits();}
	bool SaveEdits();

//	Member Variables

	TextCtrl_Short *TextBox;
};

class CheckBox_Short_ZeroIsYes: public wxCheckBox
{
	public:

	CheckBox_Short_ZeroIsYes(wxWindow *parent, string label, TextCtrl_Short *Pointer):
	wxCheckBox(parent, wxID_ANY, label, wxDefaultPosition, wxSize(0, 20))
	{
		TextBox = Pointer;
		TextBox->LinkedBox = this;
		TextBox->Disconnect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Short::OnKillFocus));
		TextBox->Connect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(CheckBox_Short_ZeroIsYes::OnKillFocus), NULL, this);

		Connect(GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CheckBox_Short_ZeroIsYes::OnUpdate));
	}

//	Events

	void OnUpdate(wxCommandEvent &Event);
	void OnKillFocus(wxFocusEvent &Event){SaveEdits();}
	bool SaveEdits();

//	Member Variables

	TextCtrl_Short *TextBox;
};

class CheckBox_Long_ZeroIsYes: public wxCheckBox
{
	public:

	CheckBox_Long_ZeroIsYes(wxWindow *parent, string label, TextCtrl_Long *Pointer):
	wxCheckBox(parent, wxID_ANY, label, wxDefaultPosition, wxSize(0, 20))
	{
		TextBox = Pointer;
		TextBox->LinkedBox = this;
		TextBox->Disconnect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Long::OnKillFocus));
		TextBox->Connect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(CheckBox_Long_ZeroIsYes::OnKillFocus), NULL, this);

		Connect(GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CheckBox_Long_ZeroIsYes::OnUpdate));
	}

//	Events

	void OnUpdate(wxCommandEvent &Event);
	void OnKillFocus(wxFocusEvent &Event){SaveEdits();}
	bool SaveEdits();

//	Member Variables

	TextCtrl_Long *TextBox;
};

#endif
