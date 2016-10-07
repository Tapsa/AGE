#pragma once
#include "AGE_TextControls.h"
#include "SharedComboPopup.h"

class AGEODComboBox: public wxOwnerDrawnComboBox
{
public:
    AGEODComboBox(wxWindow *parent, int width = AGETextCtrl::LARGE, long style = wxCB_READONLY):
    wxOwnerDrawnComboBox(parent, wxID_ANY, "", wxDefaultPosition, wxSize(width, -1), 0, 0, wxTE_PROCESS_ENTER | style)
    {
        Bind(wxEVT_MOUSEWHEEL, [=](wxMouseEvent &event){GetParent()->GetEventHandler()->ProcessEvent(event);});
    }
    //void OnDrawItem(wxDC &dc, const wxRect &rect, int item, int flags) const;
};

class AGEComboBox: public wxComboCtrl, public AGELinkedBox // AGELinkedBox -> AGEBaseCtrl
{
public:
    AGEComboBox(wxWindow *parent, wxArrayString *choices, int width):
    wxComboCtrl(parent, wxID_ANY, "", wxDefaultPosition, wxSize(width, -1), wxTE_PROCESS_ENTER)
    {
        popup = new SharedComboPopup();
        SetPopupControl(popup);
        popup->Imbue(choices);
        Bind(wxEVT_MOUSEWHEEL, [=](wxMouseEvent &event){GetParent()->GetEventHandler()->ProcessEvent(event);});
    }
    //void OnDrawItem(wxDC &dc, const wxRect &rect, int item, int flags) const;
    virtual void OnUpdate(wxCommandEvent&)=0;
    unsigned int GetCount() const {return popup->GetCount();}
    void SetSelection(int n);
    int GetSelection() const {return popup->GetSelection();}
    void Flash() {popup->Flash();}
    void SwapList(wxArrayString *choices) {popup->Imbue(choices);}

protected:
    void enable(bool yes){Enable(yes);}
    AGETextCtrl *TextBox;
    SharedComboPopup *popup;
};

class ComboBox_Plus1: public AGEComboBox
{
public:
    ComboBox_Plus1(wxWindow *parent, AGETextCtrl *ptr, wxArrayString *choices, int width = AGETextCtrl::LARGE):
    AGEComboBox(parent, choices, width)
    {
        TextBox = ptr;
        TextBox->LinkedBoxes.push_back(this);
        Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &ComboBox_Plus1::OnUpdate, this);
    }

    void update(int value);
protected:
    void OnUpdate(wxCommandEvent&);
};

class ComboBox_EffectType: public AGEComboBox
{
public:
    ComboBox_EffectType(wxWindow *parent, AGETextCtrl *ptr, wxArrayString *choices):
    AGEComboBox(parent, choices, AGETextCtrl::GIANT)
    {
        TextBox = ptr;
        TextBox->LinkedBoxes.push_back(this);
        Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &ComboBox_EffectType::OnUpdate, this);
    }

protected:
    void OnUpdate(wxCommandEvent&);
    void update(int value);
};

class ComboBox_EffectAttribute: public AGEComboBox
{
public:
    ComboBox_EffectAttribute(wxWindow *parent, AGETextCtrl *ptr, wxArrayString *choices):
    AGEComboBox(parent, choices, AGETextCtrl::LARGE)
    {
        TextBox = ptr;
        TextBox->LinkedBoxes.push_back(this);
        Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &ComboBox_EffectAttribute::OnUpdate, this);
    }

protected:
    void OnUpdate(wxCommandEvent&);
    void update(int value);
};
