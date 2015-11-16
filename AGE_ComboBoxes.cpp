#include "AGE_ComboBoxes.h"

void ComboBox_Plus1::OnUpdate(wxCommandEvent &event)
{
    TextBox->ChangeValue(lexical_cast<string>(GetSelection() - 1));
    TextBox->SaveEdits();
}

void ComboBox_EffectType::OnUpdate(wxCommandEvent &event)
{
    switch(GetSelection())
    {
        case 1: TextBox->ChangeValue("0"); break;
        case 2: TextBox->ChangeValue("1"); break;
        case 3: TextBox->ChangeValue("2"); break;
        case 4: TextBox->ChangeValue("3"); break;
        case 5: TextBox->ChangeValue("4"); break;
        case 6: TextBox->ChangeValue("5"); break;
        case 7: TextBox->ChangeValue("6"); break;
        case 8: TextBox->ChangeValue("10"); break;
        case 9: TextBox->ChangeValue("11"); break;
        case 10: TextBox->ChangeValue("12"); break;
        case 11: TextBox->ChangeValue("13"); break;
        case 12: TextBox->ChangeValue("14"); break;
        case 13: TextBox->ChangeValue("15"); break;
        case 14: TextBox->ChangeValue("16"); break;
        case 15: TextBox->ChangeValue("101"); break;
        case 16: TextBox->ChangeValue("102"); break;
        case 17: TextBox->ChangeValue("103"); break;
        default: TextBox->ChangeValue("-1");
    }
    TextBox->SaveEdits();
}

void ComboBox_EffectAttribute::OnUpdate(wxCommandEvent &event)
{
    int selection = GetSelection();
    selection = (selection < 25) ? selection - 1 : selection + 75;
    TextBox->ChangeValue(lexical_cast<string>(selection));
    TextBox->SaveEdits();
}

void ComboBox_Plus1::update(int value)
{
    if(GetCount() == 0) return;
    if(++value < GetCount())
    SetSelection(value);
    else SetSelection(0);
}

void ComboBox_EffectType::update(int value)
{
    if(GetCount() == 0) return;
    if((value >= 0) && (value <= 6))
    {
        SetSelection(value + 1);
    }
    else if((value >= 10) && (value <= 16))
    {
        SetSelection(value - 2);
    }
    else if((value >= 101) && (value <= 103))
    {
        SetSelection(value - 86);
    }
    else
    {
        SetSelection(0);
    }
}

void ComboBox_EffectAttribute::update(int value)
{
    if(GetCount() == 0) return;
    if((value >= 0) && (value <= 23))
    {
        SetSelection(value + 1);
    }
    else if((value >= 100) && (value <= 108))
    {
        SetSelection(value - 75);
    }
    else
    {
        SetSelection(0);
    }
}
