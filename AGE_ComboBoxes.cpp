#include "AGE_ComboBoxes.h"

void ComboBox_Byte::OnUpdate(wxCommandEvent &Event)
{
	TextBox->ChangeValue(lexical_cast<string>(GetSelection() - 1));
	TextBox->SaveEdits();
}

void ComboBox_Float::OnUpdate(wxCommandEvent &Event)
{
	TextBox->ChangeValue(lexical_cast<string>(GetSelection() - 1));
	TextBox->SaveEdits();
}

void ComboBox_Short::OnUpdate(wxCommandEvent &Event)
{
	TextBox->ChangeValue(lexical_cast<string>(GetSelection() - 1));
	TextBox->SaveEdits();
}

void ComboBox_Long::OnUpdate(wxCommandEvent &Event)
{
	TextBox->ChangeValue(lexical_cast<string>(GetSelection() - 1));
	TextBox->SaveEdits();
}

void ComboBox_Byte_EffectType::OnUpdate(wxCommandEvent &Event)
{
	short Selection = GetSelection();
	if(Selection == 1)
	{
		TextBox->ChangeValue("0");
	}
	else if(Selection == 2)
	{
		TextBox->ChangeValue("1");
	}
	else if(Selection == 3)
	{
		TextBox->ChangeValue("2");
	}
	else if(Selection == 4)
	{
		TextBox->ChangeValue("3");
	}
	else if(Selection == 5)
	{
		TextBox->ChangeValue("4");
	}
	else if(Selection == 6)
	{
		TextBox->ChangeValue("5");
	}
	else if(Selection == 7)
	{
		TextBox->ChangeValue("6");
	}
	else if(Selection == 8)
	{
		TextBox->ChangeValue("101");
	}
	else if(Selection == 9)
	{
		TextBox->ChangeValue("102");
	}
	else if(Selection == 10)
	{
		TextBox->ChangeValue("103");
	}
	else
	{
		TextBox->ChangeValue("-1");
	}
	TextBox->SaveEdits();
}

bool ComboBox_Byte::SaveEdits()
{
	if(TextBox->SaveEdits())
	{
		SetSelection(0);
		SetSelection(lexical_cast<short>(TextBox->GetValue()) + 1);
		return true;
	}
	return false;
}

bool ComboBox_Float::SaveEdits()
{
	if(TextBox->SaveEdits())
	{
		SetSelection(0);
		SetSelection(lexical_cast<float>(TextBox->GetValue()) + 1);
		return true;
	}
	return false;
}

bool ComboBox_Short::SaveEdits()
{
	if(TextBox->SaveEdits())
	{
		SetSelection(0);
		SetSelection(lexical_cast<short>(TextBox->GetValue()) + 1);
		return true;
	}
	return false;
}

bool ComboBox_Long::SaveEdits()
{
	if(TextBox->SaveEdits())
	{
		SetSelection(0);
		SetSelection(lexical_cast<long>(TextBox->GetValue()) + 1);
		return true;
	}
	return false;
}

bool ComboBox_Byte_EffectType::SaveEdits()
{
	if(TextBox->SaveEdits())
	{
		short Value = lexical_cast<short>(TextBox->GetValue());
		if((Value >= 0) && (Value <= 6))
		{
			SetSelection(Value + 1);
		}
		else if((Value >= 101) && (Value <= 103))
		{
			SetSelection(Value - 93);
		}
		else
		{
			SetSelection(0);
		}
		return true;
	}
	return false;
}
