#include "AGE_ComboBoxes.h"

void ComboBox_Plus1::OnUpdate(wxCommandEvent &Event)
{
	TextBox->ChangeValue(lexical_cast<string>(GetSelection() - 1));
	TextBox->SaveEdits();
}

void ComboBox_EffectType::OnUpdate(wxCommandEvent &Event)
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
		case 8: TextBox->ChangeValue("101"); break;
		case 9: TextBox->ChangeValue("102"); break;
		case 10: TextBox->ChangeValue("103"); break;
		default: TextBox->ChangeValue("-1");
	}
	TextBox->SaveEdits();
}

bool ComboBox_Plus1::SaveEdits()
{
	if(TextBox->SaveEdits())
	{
		SetSelection(0);
		SetSelection(lexical_cast<double>(TextBox->GetValue()) + 1);
		return true;
	}
	return false;
}

bool ComboBox_EffectType::SaveEdits()
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
