#pragma once
#include "AGE_TextControls.h"

class AGECheckBox: public wxCheckBox, public AGELinkedBox
{
public:
    AGECheckBox(wxWindow *parent, wxString label):
    wxCheckBox(parent, wxID_ANY, label, wxDefaultPosition, wxSize(0, 20)){}

    virtual void OnUpdate(wxCommandEvent&)=0;
protected:
    void enable(bool yes){Enable(yes);}

    AGETextCtrl *TextBox;
};

class CheckBox_2State: public AGECheckBox
{
public:
    CheckBox_2State(wxWindow *parent, wxString label, AGETextCtrl *Pointer):
    AGECheckBox(parent, label)
    {
        TextBox = Pointer;
        TextBox->LinkedBoxes.push_back(this);
        Connect(GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CheckBox_2State::OnUpdate));
    }

protected:
    void OnUpdate(wxCommandEvent &event);
    void update(int value);
};
