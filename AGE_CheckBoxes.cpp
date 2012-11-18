#include "AGE_CheckBoxes.h"

void CheckBox_Byte::OnUpdate(wxCommandEvent &Event)
{
	TextBox->ChangeValue(lexical_cast<string>(GetValue()));
	TextBox->SaveEdits();
}

void CheckBox_Float::OnUpdate(wxCommandEvent &Event)
{
	TextBox->ChangeValue(lexical_cast<string>(GetValue()));
	TextBox->SaveEdits();
}

void CheckBox_Short::OnUpdate(wxCommandEvent &Event)
{
	TextBox->ChangeValue(lexical_cast<string>(GetValue()));
	TextBox->SaveEdits();
}

void CheckBox_Short_ZeroIsYes::OnUpdate(wxCommandEvent &Event)
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

void CheckBox_Long_ZeroIsYes::OnUpdate(wxCommandEvent &Event)
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

bool CheckBox_Byte::SaveEdits()
{
	if(TextBox->SaveEdits())
	{
		SetValue(lexical_cast<short>(TextBox->GetValue()));
		return true;
	}
	return false;
}

bool CheckBox_Float::SaveEdits()
{
	if(TextBox->SaveEdits())
	{
		SetValue(lexical_cast<float>(TextBox->GetValue()));
		return true;
	}
	return false;
}

bool CheckBox_Short::SaveEdits()
{
	if(TextBox->SaveEdits())
	{
		SetValue(lexical_cast<short>(TextBox->GetValue()));
		return true;
	}
	return false;
}

bool CheckBox_Short_ZeroIsYes::SaveEdits()
{
	if(TextBox->SaveEdits())
	{
		if(lexical_cast<short>(TextBox->GetValue()) == 0)
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

bool CheckBox_Long_ZeroIsYes::SaveEdits()
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
