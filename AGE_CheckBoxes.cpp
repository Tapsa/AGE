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

bool CheckBox_2State::SaveEdits()
{
	if(TextBox->SaveEdits())
	{
		SetValue(lexical_cast<float>(TextBox->GetValue()));
		return true;
	}
	return false;
}

bool CheckBox_ZeroIsYes::SaveEdits()
{
	if(TextBox->SaveEdits())
	{
		if(lexical_cast<long>(TextBox->GetValue()) == 0)
		{
			SetValue(true);
		}
		else
		{
			SetValue(false);
		}
		return true;
	}
	return false;
}
