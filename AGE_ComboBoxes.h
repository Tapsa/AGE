#pragma once
#include "AGE_TextControls.h"

class AGEODComboBox: public wxChoice
{
public:
    AGEODComboBox(wxWindow *parent, int width = AGETextCtrl::LARGE, long style = 0):
    wxChoice(parent, wxID_ANY, wxDefaultPosition, wxSize(width, -1), 0, 0, style)
    {
        Bind(wxEVT_MOUSEWHEEL, [=](wxMouseEvent &event){GetParent()->GetEventHandler()->ProcessEvent(event);});
    }
};

class AGEComboBox: public wxChoice, public AGELinkedBox
{
public:
    AGEComboBox(wxWindow *parent, int width):
    wxChoice(parent, wxID_ANY, wxDefaultPosition, wxSize(width, -1))
    {
        Bind(wxEVT_MOUSEWHEEL, [=](wxMouseEvent &event){GetParent()->GetEventHandler()->ProcessEvent(event);});
    }

    virtual void OnUpdate(wxCommandEvent&)=0;
protected:
    void enable(bool yes){Enable(yes);}
    AGETextCtrl *TextBox;
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

protected:
    void OnUpdate(wxCommandEvent&);
    void update(int value);
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
