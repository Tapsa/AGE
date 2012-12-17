#include "AGE_TextControls.h"

#ifndef AGE_ComboBoxes_h
#define AGE_ComboBoxes_h

class AGEComboBox: public wxOwnerDrawnComboBox
{
	public:
	AGEComboBox(wxWindow *parent):
	wxOwnerDrawnComboBox(parent, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY){}

	virtual void OnUpdate(wxCommandEvent &Event)=0;
	virtual void OnKillFocus(wxFocusEvent &Event)=0;
	virtual bool SaveEdits()=0;

	AGETextCtrl *TextBox;
};

class ComboBox_Plus1: public AGEComboBox
{
	public:
	ComboBox_Plus1(wxWindow *parent, AGETextCtrl *Pointer):
	AGEComboBox(parent)
	{
		TextBox = Pointer;
		TextBox->LinkedBox = this;
		TextBox->Disconnect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGETextCtrl::OnKillFocus));
		TextBox->Connect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(ComboBox_Plus1::OnKillFocus), NULL, this);

		Connect(GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ComboBox_Plus1::OnUpdate));
	}

	void OnUpdate(wxCommandEvent &Event);
	void OnKillFocus(wxFocusEvent &Event){SaveEdits();}
	bool SaveEdits();
};

class ComboBox_EffectType: public AGEComboBox
{
	public:
	ComboBox_EffectType(wxWindow *parent, AGETextCtrl *Pointer):
	AGEComboBox(parent)
	{
		TextBox = Pointer;
		TextBox->LinkedBox = this;
		TextBox->Disconnect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGETextCtrl::OnKillFocus));
		TextBox->Connect(TextBox->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(ComboBox_EffectType::OnKillFocus), NULL, this);

		Connect(GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ComboBox_EffectType::OnUpdate));
	}

	void OnUpdate(wxCommandEvent &Event);
	void OnKillFocus(wxFocusEvent &Event){SaveEdits();}
	bool SaveEdits();
};

#endif
