#include "AGE_TextControls.h"

#ifndef AGE_CheckBoxes_h
#define AGE_CheckBoxes_h

class CheckBox_Bool: public wxCheckBox
{
	public:

	CheckBox_Bool(wxWindow *parent, string InitValue, TextCtrl_Bool *Pointer):
	wxCheckBox(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20))
	{
		Container = Pointer;
		Container->ParentContainer = this;

		Container->Disconnect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Bool::OnKillFocus));
		Container->Connect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(CheckBox_Bool::OnKillFocus), this);

		Connect(this->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CheckBox_Bool::OnUpdate));
	}

//	Events

	void OnUpdate(wxCommandEvent &Event);
	void OnKillFocus(wxFocusEvent &Event);

//	Member Variables

	TextCtrl_Bool *Container;
};

class CheckBox_Byte: public wxCheckBox
{
	public:

	CheckBox_Byte(wxWindow *parent, string InitValue, TextCtrl_Byte *Pointer):
	wxCheckBox(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20))
	{
		Container = Pointer;
		Container->ParentContainer = this;

		Container->Disconnect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Byte::OnKillFocus));
		Container->Connect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(CheckBox_Byte::OnKillFocus), this);

		Connect(this->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CheckBox_Byte::OnUpdate));
	}

//	Events

	void OnUpdate(wxCommandEvent &Event);
	void OnKillFocus(wxFocusEvent &Event);

//	Member Variables

	TextCtrl_Byte *Container;
};

class CheckBox_Float: public wxCheckBox
{
	public:

	CheckBox_Float(wxWindow *parent, string InitValue, TextCtrl_Float *Pointer):
	wxCheckBox(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20))
	{
		Container = Pointer;
		Container->ParentContainer = this;

		Container->Disconnect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Float::OnKillFocus));
		Container->Connect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(CheckBox_Float::OnKillFocus), this);

		Connect(this->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CheckBox_Float::OnUpdate));
	}

//	Events

	void OnUpdate(wxCommandEvent &Event);
	void OnKillFocus(wxFocusEvent &Event);

//	Member Variables

	TextCtrl_Float *Container;
};

class CheckBox_Short: public wxCheckBox
{
	public:

	CheckBox_Short(wxWindow *parent, string InitValue, TextCtrl_Short *Pointer):
	wxCheckBox(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20))
	{
		Container = Pointer;
		Container->ParentContainer = this;

		Container->Disconnect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Short::OnKillFocus));
		Container->Connect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(CheckBox_Short::OnKillFocus), this);

		Connect(this->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CheckBox_Short::OnUpdate));
	}

//	Events

	void OnUpdate(wxCommandEvent &Event);
	void OnKillFocus(wxFocusEvent &Event);

//	Member Variables

	TextCtrl_Short *Container;
};

class CheckBox_Short_ZeroIsYes: public wxCheckBox
{
	public:

	CheckBox_Short_ZeroIsYes(wxWindow *parent, string InitValue, TextCtrl_Short *Pointer):
	wxCheckBox(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20))
	{
		Container = Pointer;
		Container->ParentContainer = this;

		Container->Disconnect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Short::OnKillFocus));
		Container->Connect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(CheckBox_Short_ZeroIsYes::OnKillFocus), this);

		Connect(this->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CheckBox_Short_ZeroIsYes::OnUpdate));
	}

//	Events

	void OnUpdate(wxCommandEvent &Event);
	void OnKillFocus(wxFocusEvent &Event);

//	Member Variables

	TextCtrl_Short *Container;
};

class CheckBox_Long_ZeroIsYes: public wxCheckBox
{
	public:

	CheckBox_Long_ZeroIsYes(wxWindow *parent, string InitValue, TextCtrl_Long *Pointer):
	wxCheckBox(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20))
	{
		Container = Pointer;
		Container->ParentContainer = this;

		Container->Disconnect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Long::OnKillFocus));
		Container->Connect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(CheckBox_Long_ZeroIsYes::OnKillFocus), this);

		Connect(this->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CheckBox_Long_ZeroIsYes::OnUpdate));
	}

//	Events

	void OnUpdate(wxCommandEvent &Event);
	void OnKillFocus(wxFocusEvent &Event);

//	Member Variables

	TextCtrl_Long *Container;
};

#endif
