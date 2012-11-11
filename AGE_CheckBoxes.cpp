/* AGE_CheckBoxes.cpp */

#include "AGE_CheckBoxes.h"

void CheckBox_Bool::OnUpdate(wxCommandEvent &Event)
{
	Container->ChangeValue(lexical_cast<string>((bool)GetValue()));

	wxFocusEvent Temp;
	Container->OnKillFocus(Temp);
}

void CheckBox_Byte::OnUpdate(wxCommandEvent &Event)
{
	Container->ChangeValue(lexical_cast<string>((int16_t)GetValue()));

	wxFocusEvent Temp;
	Container->OnKillFocus(Temp);
}

void CheckBox_Float::OnUpdate(wxCommandEvent &Event)
{
	Container->ChangeValue(lexical_cast<string>((float)GetValue()));

	wxFocusEvent Temp;
	Container->OnKillFocus(Temp);
}

void CheckBox_Short::OnUpdate(wxCommandEvent &Event)
{
	Container->ChangeValue(lexical_cast<string>((int16_t)GetValue()));

	wxFocusEvent Temp;
	Container->OnKillFocus(Temp);
}

void CheckBox_Short_ZeroIsYes::OnUpdate(wxCommandEvent &Event)
{
	bool State = GetValue();
	if(State == true)
	{
		Container->ChangeValue("0");
	}
	else
	{
		Container->ChangeValue("-1");
	}

	wxFocusEvent Temp;
	Container->OnKillFocus(Temp);
}

void CheckBox_Long_ZeroIsYes::OnUpdate(wxCommandEvent &Event)
{
	bool State = GetValue();
	if(State == true)
	{
		Container->ChangeValue("0");
	}
	else
	{
		Container->ChangeValue("-1");
	}

	wxFocusEvent Temp;
	Container->OnKillFocus(Temp);
}

void CheckBox_Bool::OnKillFocus(wxFocusEvent &Event)
{
	((TextCtrl_Bool*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Bool*)Event.GetEventObject())->NoLoadList)
	{
		bool Value = lexical_cast<bool>(((TextCtrl_Bool*)Event.GetEventObject())->GetValue());
		((CheckBox_Bool*)((TextCtrl_Bool*)Event.GetEventObject())->ParentContainer)->SetValue(Value);
	}
}

void CheckBox_Byte::OnKillFocus(wxFocusEvent &Event)
{
	((TextCtrl_Byte*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Byte*)Event.GetEventObject())->NoLoadList)
	{
		int16_t Value = lexical_cast<int16_t>(((TextCtrl_Byte*)Event.GetEventObject())->GetValue());
		((CheckBox_Byte*)((TextCtrl_Byte*)Event.GetEventObject())->ParentContainer)->SetValue(Value);
	}
}

void CheckBox_Float::OnKillFocus(wxFocusEvent &Event)
{
	((TextCtrl_Float*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Float*)Event.GetEventObject())->NoLoadList)
	{
		float Value = lexical_cast<float>(((TextCtrl_Float*)Event.GetEventObject())->GetValue());
		((CheckBox_Float*)((TextCtrl_Float*)Event.GetEventObject())->ParentContainer)->SetValue(Value);
	}
}

void CheckBox_Short::OnKillFocus(wxFocusEvent &Event)
{
	((TextCtrl_Short*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Short*)Event.GetEventObject())->NoLoadList)
	{
		int16_t Value = lexical_cast<int16_t>(((TextCtrl_Short*)Event.GetEventObject())->GetValue());
		((CheckBox_Short*)((TextCtrl_Short*)Event.GetEventObject())->ParentContainer)->SetValue(Value);
	}
}

void CheckBox_Short_ZeroIsYes::OnKillFocus(wxFocusEvent &Event)
{
	((TextCtrl_Short*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Short*)Event.GetEventObject())->NoLoadList)
	{
		switch(lexical_cast<int16_t>(((TextCtrl_Short*)Event.GetEventObject())->GetValue()))
		{
			case -1:
			{
				((CheckBox_Short_ZeroIsYes*)((TextCtrl_Short*)Event.GetEventObject())->ParentContainer)->SetValue(false);
			}
			break;
			case 0:
			{
				((CheckBox_Short_ZeroIsYes*)((TextCtrl_Short*)Event.GetEventObject())->ParentContainer)->SetValue(true);
			}
			break;
			default:
			{
				((CheckBox_Short_ZeroIsYes*)((TextCtrl_Short*)Event.GetEventObject())->ParentContainer)->SetValue(false);
			}
			break;
		}
	}
}

void CheckBox_Long_ZeroIsYes::OnKillFocus(wxFocusEvent &Event)
{
	((TextCtrl_Long*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Long*)Event.GetEventObject())->NoLoadList)
	{
		switch(lexical_cast<int32_t>(((TextCtrl_Long*)Event.GetEventObject())->GetValue()))
		{
			case -1:
			{
				((CheckBox_Long_ZeroIsYes*)((TextCtrl_Long*)Event.GetEventObject())->ParentContainer)->SetValue(false);
			}
			break;
			case 0:
			{
				((CheckBox_Long_ZeroIsYes*)((TextCtrl_Long*)Event.GetEventObject())->ParentContainer)->SetValue(true);
			}
			break;
			default:
			{
				((CheckBox_Long_ZeroIsYes*)((TextCtrl_Long*)Event.GetEventObject())->ParentContainer)->SetValue(false);
			}
			break;
		}
	}
}
