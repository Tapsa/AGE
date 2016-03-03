#pragma once
#include "AGE_TextControls.h"

class AGEODComboBox: public wxChoice
{
public:
    AGEODComboBox(wxWindow *parent, int width = AGETextCtrl::LARGE, long style = 0):
    wxChoice(parent, wxID_ANY, wxDefaultPosition, wxSize(width, -1), 0, 0, style)
    {
        Connect(GetId(), wxEVT_MOUSEWHEEL, wxMouseEventHandler(AGEODComboBox::wheelParent));
    }

protected:
    void wheelParent(wxMouseEvent &event)
    {
        GetParent()->GetEventHandler()->ProcessEvent(event);
    }
};

class AGEComboBox: public wxChoice, public AGELinkedBox
{
public:
    AGEComboBox(wxWindow *parent, int width):
    wxChoice(parent, wxID_ANY, wxDefaultPosition, wxSize(width, -1))
    {
        Connect(GetId(), wxEVT_MOUSEWHEEL, wxMouseEventHandler(AGEComboBox::wheelParent));
    }

    virtual void OnUpdate(wxCommandEvent&)=0;
protected:
    void enable(bool yes){Enable(yes);}
    AGETextCtrl *TextBox;
    void wheelParent(wxMouseEvent &event)
    {
        GetParent()->GetEventHandler()->ProcessEvent(event);
    }
};

class ComboBox_Plus1: public AGEComboBox
{
public:
    ComboBox_Plus1(wxWindow *parent, AGETextCtrl *Pointer, int width = AGETextCtrl::LARGE):
    AGEComboBox(parent, width)
    {
        TextBox = Pointer;
        TextBox->LinkedBoxes.push_back(this);
        Connect(GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ComboBox_Plus1::OnUpdate));
    }

protected:
    void OnUpdate(wxCommandEvent &event);
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
        Connect(GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ComboBox_EffectType::OnUpdate));
    }

protected:
    void OnUpdate(wxCommandEvent &event);
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
        Connect(GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ComboBox_EffectAttribute::OnUpdate));
    }

protected:
    void OnUpdate(wxCommandEvent &event);
    void update(int value);
};
