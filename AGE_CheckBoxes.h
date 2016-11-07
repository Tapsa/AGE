#pragma once
#include "AGE_TextControls.h"

class CheckBox_2State: public wxCheckBox, public AGELinkedBox
{
public:
    CheckBox_2State(wxWindow *parent, wxString label, AGETextCtrl *ptr):
    wxCheckBox(parent, wxID_ANY, label)
    {
        TextBox = ptr;
        TextBox->LinkedBoxes.push_back(this);
        Bind(wxEVT_COMMAND_CHECKBOX_CLICKED, &CheckBox_2State::OnChoose, this);
    }
    void OnChoose(wxCommandEvent&);

private:
    void SetChoice(int value) {SetValue(value);}
    void EnableCtrl(bool yes) {Enable(yes);}
};
