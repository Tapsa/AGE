#include "AGE_CheckBoxes.h"

void CheckBox_2State::OnUpdate(wxCommandEvent &Event)
{
	TextBox->ChangeValue(lexical_cast<string>(GetValue()));
	TextBox->SaveEdits();
}

void CheckBox_ZeroIsYes::OnUpdate(wxCommandEvent &Event)
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

void CheckBox_2State::Update(long value)
{
	SetValue(value);
}

void CheckBox_ZeroIsYes::Update(long value)
{
	if(value == 0)
	{
		SetValue(true);
	}
	else
	{
		SetValue(false);
	}
}
