#include "AGE_CheckBoxes.h"

void CheckBox_2State::OnUpdate(wxCommandEvent &event)
{
    TextBox->ChangeValue(lexical_cast<string>(GetValue()));
    TextBox->SaveEdits();
}

void CheckBox_ZeroIsYes::OnUpdate(wxCommandEvent &event)
{
    if(GetValue())
    {
        TextBox->ChangeValue("0");
    }
    else
    {
        TextBox->ChangeValue("-1");
    }
    TextBox->SaveEdits();
}

void CheckBox_2State::update(int value)
{
    SetValue(value);
}

void CheckBox_ZeroIsYes::update(int value)
{
    SetValue(value == 0);
}
