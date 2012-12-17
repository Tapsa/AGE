#include "AGE_TextControls.h"

#ifndef AGE_CheckBoxes_h
#define AGE_CheckBoxes_h

class AGECheckBox: public wxCheckBox
{
	public:
	AGECheckBox(wxWindow *parent, wxString label):
	wxCheckBox(parent, wxID_ANY, label, wxDefaultPosition, wxSize(0, 20)){}

	virtual void OnUpdate(wxCommandEvent &Event)=0;
	virtual void OnKillFocus(wxFocusEvent &Event)=0;
	virtual bool SaveEdits()=0;

	AGETextCtrl *TextBox;
};

class CheckBox_2State: public AGECheckBox
{
	public:
	CheckBox_2State(wxWindow *parent, wxString label, AGETextCtrl *Pointer):
	AGECheckBox(parent, label)
	{
		TextBox = Pointer;
		TextBox->LinkedBox = this;
		TextBox->Disconnect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGETextCtrl::OnKillFocus));
		TextBox->Connect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(CheckBox_2State::OnKillFocus), NULL, this);

		Connect(GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CheckBox_2State::OnUpdate));
	}

	void OnUpdate(wxCommandEvent &Event);
	void OnKillFocus(wxFocusEvent &Event){SaveEdits();}
	bool SaveEdits();
};

class CheckBox_ZeroIsYes: public AGECheckBox
{
	public:
	CheckBox_ZeroIsYes(wxWindow *parent, wxString label, AGETextCtrl *Pointer):
	AGECheckBox(parent, label)
	{
		TextBox = Pointer;
		TextBox->LinkedBox = this;
		TextBox->Disconnect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGETextCtrl::OnKillFocus));
		TextBox->Connect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(CheckBox_ZeroIsYes::OnKillFocus), NULL, this);

		Connect(GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CheckBox_ZeroIsYes::OnUpdate));
	}

	void OnUpdate(wxCommandEvent &Event);
	void OnKillFocus(wxFocusEvent &Event){SaveEdits();}
	bool SaveEdits();
};

#endif
