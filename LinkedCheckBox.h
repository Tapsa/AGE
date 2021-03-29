#pragma once
#include <wx/checkbox.h>
#include "LinkedControl.h"

class LinkedCheckBox : public wxCheckBox, public LinkedControl
{
public:
    LinkedCheckBox(wxWindow *parent, wxString label, AGETextCtrl *link, bool connect = true);
    inline void OnChoose(wxCommandEvent &) override;

private:
    inline void SetChoice(int value) override { SetValue(value); }
    inline void EnableControl(bool yes) override { Enable(yes); }
};
