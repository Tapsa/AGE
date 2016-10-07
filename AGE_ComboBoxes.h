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
    AGEComboBox(wxWindow *parent, int width):
    wxComboCtrl(parent, wxID_ANY, "", wxDefaultPosition, wxSize(width, -1), wxTE_PROCESS_ENTER)
    {
        popup = new SharedComboPopup();
        SetPopupControl(popup);
        Bind(wxEVT_MOUSEWHEEL, [=](wxMouseEvent &event){GetParent()->GetEventHandler()->ProcessEvent(event);});
    }
    //void OnDrawItem(wxDC &dc, const wxRect &rect, int item, int flags) const;
    virtual void OnUpdate(wxCommandEvent&)=0;
    void Imbue(wxArrayString *choices) {popup->Imbue(choices);}

//  Temporary functions
    int Append(const wxString&) {return 0;}
    int Append(const wxArrayString&) {return 0;}
    virtual unsigned int GetCount() const {return 0;}
    virtual void SetSelection(int n) {}
    virtual int GetSelection() const {return 0;}

protected:
    void enable(bool yes){Enable(yes);}
    AGETextCtrl *TextBox;
    SharedComboPopup *popup;
};

class ComboBox_Plus1: public AGEComboBox
{
public:
    ComboBox_Plus1(wxWindow *parent, AGETextCtrl *Pointer, int width = AGETextCtrl::LARGE):
    AGEComboBox(parent, width)
    {
        TextBox = Pointer;
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
    ComboBox_EffectType(wxWindow *parent, AGETextCtrl *Pointer):
    AGEComboBox(parent, AGETextCtrl::GIANT)
    {
        TextBox = Pointer;
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
    ComboBox_EffectAttribute(wxWindow *parent, AGETextCtrl *Pointer):
    AGEComboBox(parent, AGETextCtrl::LARGE)
    {
        TextBox = Pointer;
        TextBox->LinkedBoxes.push_back(this);
        Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &ComboBox_EffectAttribute::OnUpdate, this);
    }

protected:
    void OnUpdate(wxCommandEvent&);
    void update(int value);
};
