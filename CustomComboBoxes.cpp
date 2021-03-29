#include "Common.h"
#include "CustomComboBoxes.h"

AGEComboBox::AGEComboBox(wxWindow *parent, wxArrayString *choices, int width, bool pass) :
    wxComboCtrl(parent, wxID_ANY, "", wxDefaultPosition, wxSize(width, -1), wxCB_READONLY)
{
    popup = new SharedComboPopup();
    SetPopupControl(popup);
    popup->SetFont(parent->GetFont());
    popup->Imbue(choices);
    if (pass)
    {
        // Stop accidental selection changes
        Bind(wxEVT_MOUSEWHEEL, [this](wxMouseEvent &event) {GetParent()->GetEventHandler()->ProcessEvent(event); });
    }
}

void AGEComboBox::SetSelection(int n)
{
    wxString str;

    if (GetCount())
    {
        popup->SetSelection(n);

        if (n >= 0)
        {
            str = popup->GetString(n);
        }
    }

    // Refresh text portion in control
    if (m_text)
        m_text->ChangeValue(str);
    else
        m_valueString = str;

    Refresh();
}

void AGEComboBox::Flash()
{
    int sel = GetSelection();
    popup->Flash();
    SetSelection(sel >= 0 && sel < GetCount() ? sel : 0);
}

LinkedComboBox::LinkedComboBox(wxWindow *parent, AGETextCtrl *link, wxArrayString *choices,
    bool connect, int width) :
    AGEComboBox(parent, choices, width), LinkedControl(link)
{
    if (connect)
    {
        Bind(wxEVT_COMBOBOX, &LinkedComboBox::OnChoose, this);
    }
}

void LinkedComboBox::OnChoose(wxCommandEvent &)
{
    TextControl->ChangeValue(lexical_cast<std::string>(GetSelection() - 1));
    TextControl->SaveEdits();
}

void LinkedComboBox::SetChoice(int value)
{
    if (GetCount() == 0) return;
    if (value >= 0 && ++value < GetCount())
    {
        SetSelection(value);
    }
    else
    {
        SetSelection(0);
    }
}
