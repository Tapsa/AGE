#include "AGE_CheckBoxes.h"

void CheckBox_2State::OnChoose(wxCommandEvent&)
{
    TextBox->ChangeValue(std::to_string(GetValue()));
    TextBox->SaveEdits();
}
