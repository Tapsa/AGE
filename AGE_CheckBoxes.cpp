#include "AGE_CheckBoxes.h"

void CheckBox_2State::OnUpdate(wxCommandEvent &event)
{
    TextBox->ChangeValue(lexical_cast<string>(GetValue()));
    TextBox->SaveEdits();
}

void CheckBox_2State::update(int value)
{
    SetValue(value);
}
