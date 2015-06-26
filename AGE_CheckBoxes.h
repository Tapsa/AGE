#include "AGE_TextControls.h"

#ifndef AGE_CheckBoxes_h
#define AGE_CheckBoxes_h

class AGECheckBox: public wxCheckBox, public AGELinkedBox
{
public:
    AGECheckBox(wxWindow *parent, wxString label):
    wxCheckBox(parent, wxID_ANY, label, wxDefaultPosition, wxSize(0, 20)){}

    virtual void OnUpdate(wxCommandEvent&)=0;

    AGETextCtrl *TextBox;
};

class CheckBox_2State: public AGECheckBox
{
public:
    CheckBox_2State(wxWindow *parent, wxString label, AGETextCtrl *Pointer):
    AGECheckBox(parent, label)
    {
        TextBox = Pointer;
        TextBox->LinkedBoxes.push_front(this);
        Connect(GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CheckBox_2State::OnUpdate));
    }

    void OnUpdate(wxCommandEvent &Event);
    void Update(int value);
};

class CheckBox_ZeroIsYes: public AGECheckBox
{
public:
    CheckBox_ZeroIsYes(wxWindow *parent, wxString label, AGETextCtrl *Pointer):
    AGECheckBox(parent, label)
    {
        TextBox = Pointer;
        TextBox->LinkedBoxes.push_front(this);
        Connect(GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CheckBox_ZeroIsYes::OnUpdate));
    }

    void OnUpdate(wxCommandEvent &Event);
    void Update(int value);
};

#endif
