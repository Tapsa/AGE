/* AGE_ComboBoxes.cpp */

#include "AGE_ComboBoxes.h"

void ComboBox_Byte::OnUpdate(wxCommandEvent& Event)
{
	Container->ChangeValue(lexical_cast<string>(GetSelection() - 1));
	
	wxFocusEvent Temp(wxEVT_KILL_FOCUS);
	Container->OnKillFocus(Temp);
}

void ComboBox_Float::OnUpdate(wxCommandEvent& Event)
{
	Container->ChangeValue(lexical_cast<string>(GetSelection() - 1));
	
	wxFocusEvent Temp(wxEVT_KILL_FOCUS);
	Container->OnKillFocus(Temp);
}

void ComboBox_Short::OnUpdate(wxCommandEvent& Event)
{
	Container->ChangeValue(lexical_cast<string>(GetSelection() - 1));
	
	wxFocusEvent Temp(wxEVT_KILL_FOCUS);
	Container->OnKillFocus(Temp);
}

void ComboBox_Long::OnUpdate(wxCommandEvent& Event)
{
	Container->ChangeValue(lexical_cast<string>(GetSelection() - 1));
	
	wxFocusEvent Temp(wxEVT_KILL_FOCUS);
	Container->OnKillFocus(Temp);
}

void ComboBox_Byte_EffectType::OnUpdate(wxCommandEvent& Event)
{
	short Selection = GetSelection();
	if(Selection == 1)
	{
		Container->ChangeValue("0");
	}
	else if(Selection == 2)
	{
		Container->ChangeValue("1");
	}
	else if(Selection == 3)
	{
		Container->ChangeValue("2");
	}
	else if(Selection == 4)
	{
		Container->ChangeValue("3");
	}
	else if(Selection == 5)
	{
		Container->ChangeValue("4");
	}
	else if(Selection == 6)
	{
		Container->ChangeValue("5");
	}
	else if(Selection == 7)
	{
		Container->ChangeValue("6");
	}
	else if(Selection == 8)
	{
		Container->ChangeValue("101");
	}
	else if(Selection == 9)
	{
		Container->ChangeValue("102");
	}
	else if(Selection == 10)
	{
		Container->ChangeValue("103");
	}
	else
	{
		Container->ChangeValue("-1");
	}
	
	wxFocusEvent Temp(wxEVT_KILL_FOCUS);
	Container->OnKillFocus(Temp);
}

void ComboBox_Byte::OnKillFocus(wxFocusEvent& Event)
{
	((TextCtrl_Byte*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Byte*)Event.GetEventObject())->NoLoadList)
	{
		int16_t Value = lexical_cast<int16_t>(((TextCtrl_Byte*)Event.GetEventObject())->GetValue());
		((ComboBox_Byte*)((TextCtrl_Byte*)Event.GetEventObject())->ParentContainer)->SetSelection(0);
		((ComboBox_Byte*)((TextCtrl_Byte*)Event.GetEventObject())->ParentContainer)->SetSelection(Value + 1);
	}
}

void ComboBox_Float::OnKillFocus(wxFocusEvent& Event)
{
	((TextCtrl_Float*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Float*)Event.GetEventObject())->NoLoadList)
	{
		float Value = lexical_cast<float>(((TextCtrl_Float*)Event.GetEventObject())->GetValue());
		((ComboBox_Float*)((TextCtrl_Float*)Event.GetEventObject())->ParentContainer)->SetSelection(0);
		((ComboBox_Float*)((TextCtrl_Float*)Event.GetEventObject())->ParentContainer)->SetSelection(Value + 1);
	}
}

void ComboBox_Short::OnKillFocus(wxFocusEvent& Event)
{
	((TextCtrl_Short*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Short*)Event.GetEventObject())->NoLoadList)
	{
		int16_t Value = lexical_cast<int16_t>(((TextCtrl_Short*)Event.GetEventObject())->GetValue());
		((ComboBox_Short*)((TextCtrl_Short*)Event.GetEventObject())->ParentContainer)->SetSelection(0);
		((ComboBox_Short*)((TextCtrl_Short*)Event.GetEventObject())->ParentContainer)->SetSelection(Value + 1);
	}
}

void ComboBox_Long::OnKillFocus(wxFocusEvent& Event)
{
	((TextCtrl_Long*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Long*)Event.GetEventObject())->NoLoadList)
	{
		int32_t Value = lexical_cast<int32_t>(((TextCtrl_Long*)Event.GetEventObject())->GetValue());
		((ComboBox_Long*)((TextCtrl_Long*)Event.GetEventObject())->ParentContainer)->SetSelection(0);
		((ComboBox_Long*)((TextCtrl_Long*)Event.GetEventObject())->ParentContainer)->SetSelection(Value + 1);
	}
}

void ComboBox_Byte_EffectType::OnKillFocus(wxFocusEvent& Event)
{
	((TextCtrl_Byte*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Byte*)Event.GetEventObject())->NoLoadList)
	{
		int16_t Value = lexical_cast<int16_t>(((TextCtrl_Byte*)Event.GetEventObject())->GetValue());
		if((Value >= 0) && (Value <= 6))
		{
			((ComboBox_Byte_EffectType*)((TextCtrl_Byte*)Event.GetEventObject())->ParentContainer)->SetSelection(Value + 1);
		}
		else if((Value >= 101) && (Value <= 103))
		{
			((ComboBox_Byte_EffectType*)((TextCtrl_Byte*)Event.GetEventObject())->ParentContainer)->SetSelection(Value - 93);
		}
		else
		{
			((ComboBox_Byte_EffectType*)((TextCtrl_Byte*)Event.GetEventObject())->ParentContainer)->SetSelection(0);
		}
	}
}
