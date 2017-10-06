#pragma once
#include "AGE_TextControls.h"
#include "SharedComboPopup.h"

class AGEComboBox: public wxComboCtrl
{
public:
    AGEComboBox(wxWindow *parent, wxArrayString *choices, int width = AGETextCtrl::LARGE, bool pass = true):
    wxComboCtrl(parent, wxID_ANY, "", wxDefaultPosition, wxSize(width, -1), wxCB_READONLY)
    {
        popup = new SharedComboPopup();
        SetPopupControl(popup);
        popup->SetFont(parent->GetFont());
        popup->Imbue(choices);
        if(pass)
        Bind(wxEVT_MOUSEWHEEL, [this](wxMouseEvent &event){GetParent()->GetEventHandler()->ProcessEvent(event);});
    }
    unsigned int GetCount() const {return popup->GetCount();}
    void SetSelection(int n);
    int GetSelection() const {return popup->GetSelection();}
    void Flash();
    void SwapList(wxArrayString *choices) {popup->Imbue(choices);}

private:
    SharedComboPopup *popup;
};

class ComboBox_Plus1: public AGEComboBox, public AGELinkedBox
{
public:
    ComboBox_Plus1(wxWindow *parent, AGETextCtrl *ptr, wxArrayString *choices, int width = AGETextCtrl::LARGE):
    AGEComboBox(parent, choices, width)
    {
        TextBox = ptr;
        TextBox->LinkedBoxes.push_back(this);
        Bind(wxEVT_COMBOBOX, &ComboBox_Plus1::OnChoose, this);
    }
    void OnChoose(wxCommandEvent&);

private:
    void SetChoice(int);
    void EnableCtrl(bool yes) {Enable(yes);}
};

class ComboBox_EffectType: public AGEComboBox, public AGELinkedBox
{
public:
    ComboBox_EffectType(wxWindow *parent, AGETextCtrl *ptr, wxArrayString *choices):
    AGEComboBox(parent, choices, AGETextCtrl::GIANT)
    {
        TextBox = ptr;
        TextBox->LinkedBoxes.push_back(this);
    }
    void OnChoose(wxCommandEvent&);

private:
    void SetChoice(int);
    void EnableCtrl(bool yes) {Enable(yes);}
};

class ComboBox_EffectAttribute: public AGEComboBox, public AGELinkedBox
{
public:
    ComboBox_EffectAttribute(wxWindow *parent, AGETextCtrl *ptr, wxArrayString *choices):
    AGEComboBox(parent, choices, AGETextCtrl::LARGE)
    {
        TextBox = ptr;
        TextBox->LinkedBoxes.push_back(this);
    }
    void OnChoose(wxCommandEvent&);

private:
    void SetChoice(int);
    void EnableCtrl(bool yes) {Enable(yes);}
};
