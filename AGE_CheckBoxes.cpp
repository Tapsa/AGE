#include "AGE_CheckBoxes.h"

LinkedCheckBox::LinkedCheckBox(wxWindow* parent, wxString label, AGETextCtrl* link, bool connect) :
    wxCheckBox(parent, wxID_ANY, label), LinkedControl(link)
{
    if (connect)
    {
        Bind(wxEVT_CHECKBOX, &LinkedCheckBox::OnChoose, this);
    }
}

void LinkedCheckBox::OnChoose(wxCommandEvent&)
{
    TextControl->ChangeValue(lexical_cast<string>(GetValue()));
    TextControl->SaveEdits();
}
