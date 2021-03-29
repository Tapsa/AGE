#pragma once
#include "CustomTextControls.h"
#include "LinkedControl.h"
#include "SharedComboPopup.h"

class AGEComboBox : public wxComboCtrl
{
public:
    AGEComboBox(wxWindow *parent, wxArrayString *choices, int width = AGETextCtrl::LARGE, bool pass = true);

    inline int GetCount() const { return popup->GetCount(); }
    inline int GetSelection() const { return popup->GetSelection(); }
    inline void SwapList(wxArrayString *choices) { popup->Imbue(choices); }
    void SetSelection(int n);
    void Flash();

private:
    SharedComboPopup *popup;
};

class LinkedComboBox : public AGEComboBox, public LinkedControl
{
public:
    LinkedComboBox(wxWindow *parent, AGETextCtrl *link, wxArrayString *choices,
        bool connect = true, int width = AGETextCtrl::LARGE);

    inline void OnChoose(wxCommandEvent &event) override;
    inline void SetChoice(int value) override;

private:
    inline void EnableControl(bool yes) override { Enable(yes); }
};
