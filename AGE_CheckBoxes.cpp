#include "AGE_CheckBoxes.h"

void CheckBox_2State::OnChoose(wxCommandEvent&)
{
    TextBox->ChangeValue(lexical_cast<string>(GetValue()));
    TextBox->SaveEdits();
}
