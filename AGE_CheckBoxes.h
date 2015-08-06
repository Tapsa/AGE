#include "AGE_TextControls.h"

#ifndef AGE_CheckBoxes_h
#define AGE_CheckBoxes_h

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
        TextBox->LinkedBoxes.push_front(this);
        Bind(wxEVT_COMMAND_CHECKBOX_CLICKED, &CheckBox_2State::OnUpdate, this);
    }

protected:
    void OnUpdate(wxCommandEvent &event);
    void update(int value);
};

class CheckBox_ZeroIsYes: public AGECheckBox
{
public:
    CheckBox_ZeroIsYes(wxWindow *parent, wxString label, AGETextCtrl *Pointer):
    AGECheckBox(parent, label)
    {
        TextBox = Pointer;
        TextBox->LinkedBoxes.push_front(this);
        Bind(wxEVT_COMMAND_CHECKBOX_CLICKED, &CheckBox_ZeroIsYes::OnUpdate, this);
    }

protected:
    void OnUpdate(wxCommandEvent &event);
    void update(int value);
};

#endif
