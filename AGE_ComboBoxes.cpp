/* AGE_ComboBoxes.cpp */

#include "AGE_ComboBoxes.h"

void ComboBox_Byte::OnUpdate(wxCommandEvent& Event)
{
	Container->SetValue(lexical_cast<string>(GetSelection() - 1));
	
	wxFocusEvent Temp(wxEVT_KILL_FOCUS);
	Container->OnKillFocus(Temp);
}

void ComboBox_Float::OnUpdate(wxCommandEvent& Event)
{
	Container->SetValue(lexical_cast<string>(GetSelection() - 1));
	
	wxFocusEvent Temp(wxEVT_KILL_FOCUS);
	Container->OnKillFocus(Temp);
}

void ComboBox_Short::OnUpdate(wxCommandEvent& Event)
{
	Container->SetValue(lexical_cast<string>(GetSelection() - 1));
	
	wxFocusEvent Temp(wxEVT_KILL_FOCUS);
	Container->OnKillFocus(Temp);
}

void ComboBox_Long::OnUpdate(wxCommandEvent& Event)
{
	Container->SetValue(lexical_cast<string>(GetSelection() - 1));
	
	wxFocusEvent Temp(wxEVT_KILL_FOCUS);
	Container->OnKillFocus(Temp);
}

void ComboBox_Byte_EffectType::OnUpdate(wxCommandEvent& Event)
{
	short Selection = GetSelection();
	if(Selection == 1)
	{
		Container->SetValue("0");
	}
	else if(Selection == 2)
	{
		Container->SetValue("1");
	}
	else if(Selection == 3)
	{
		Container->SetValue("2");
	}
	else if(Selection == 4)
	{
		Container->SetValue("3");
	}
	else if(Selection == 5)
	{
		Container->SetValue("4");
	}
	else if(Selection == 6)
	{
		Container->SetValue("5");
	}
	else if(Selection == 7)
	{
		Container->SetValue("6");
	}
	else if(Selection == 8)
	{
		Container->SetValue("101");
	}
	else if(Selection == 9)
	{
		Container->SetValue("102");
	}
	else if(Selection == 10)
	{
		Container->SetValue("103");
	}
	else
	{
		Container->SetValue("-1");
	}
	
	wxFocusEvent Temp(wxEVT_KILL_FOCUS);
	Container->OnKillFocus(Temp);
}

void ComboBox_Byte_UnitType::OnUpdate(wxCommandEvent& Event)
{
	short Selection = GetSelection();
	if(Selection == 1)
	{
		Container->SetValue("10");
	}
	else if(Selection == 2)
	{
		Container->SetValue("20");
	}
	else if(Selection == 3)
	{
		Container->SetValue("30");
	}
	else if(Selection == 4)
	{
		Container->SetValue("60");
	}
	else if(Selection == 5)
	{
		Container->SetValue("70");
	}
	else if(Selection == 6)
	{
		Container->SetValue("80");
	}
	else
	{
		Container->SetValue("-1");
	}
	
	wxFocusEvent Temp(wxEVT_KILL_FOCUS);
	Container->OnKillFocus(Temp);
}

void ComboBox_Short_AttackType::OnUpdate(wxCommandEvent& Event)
{
	Container->SetValue(lexical_cast<string>(GetSelection()));
	
	wxFocusEvent Temp(wxEVT_KILL_FOCUS);
	Container->OnKillFocus(Temp);
}

void ComboBox_Byte::OnKillFocus(wxFocusEvent& Event)
{
	((TextCtrl_Byte*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Byte*)Event.GetEventObject())->NoLoadList)
	{
		short Value = lexical_cast<short>(((TextCtrl_Byte*)Event.GetEventObject())->GetValue());
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
		short Value = lexical_cast<short>(((TextCtrl_Short*)Event.GetEventObject())->GetValue());
		((ComboBox_Short*)((TextCtrl_Short*)Event.GetEventObject())->ParentContainer)->SetSelection(0);
		((ComboBox_Short*)((TextCtrl_Short*)Event.GetEventObject())->ParentContainer)->SetSelection(Value + 1);
	}
}

void ComboBox_Long::OnKillFocus(wxFocusEvent& Event)
{
	((TextCtrl_Long*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Long*)Event.GetEventObject())->NoLoadList)
	{
		long Value = lexical_cast<long>(((TextCtrl_Short*)Event.GetEventObject())->GetValue());
		((ComboBox_Long*)((TextCtrl_Long*)Event.GetEventObject())->ParentContainer)->SetSelection(0);
		((ComboBox_Long*)((TextCtrl_Long*)Event.GetEventObject())->ParentContainer)->SetSelection(Value + 1);
	}
}

void ComboBox_Byte_EffectType::OnKillFocus(wxFocusEvent& Event)
{
	((TextCtrl_Byte*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Byte*)Event.GetEventObject())->NoLoadList)
	{
		short Value = lexical_cast<short>(((TextCtrl_Byte*)Event.GetEventObject())->GetValue());
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

void ComboBox_Byte_UnitType::OnKillFocus(wxFocusEvent& Event)
{
	((TextCtrl_Byte*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Byte*)Event.GetEventObject())->NoLoadList)
	{
		short Value = lexical_cast<short>(((TextCtrl_Byte*)Event.GetEventObject())->GetValue());
		if(Value == 10)
		{
			((ComboBox_Byte_UnitType*)((TextCtrl_Byte*)Event.GetEventObject())->ParentContainer)->SetSelection(1);
		}
		else if(Value == 20)
		{
			((ComboBox_Byte_UnitType*)((TextCtrl_Byte*)Event.GetEventObject())->ParentContainer)->SetSelection(2);
		}
		else if(Value == 30)
		{
			((ComboBox_Byte_UnitType*)((TextCtrl_Byte*)Event.GetEventObject())->ParentContainer)->SetSelection(3);
		}
		else if(Value == 60)
		{
			((ComboBox_Byte_UnitType*)((TextCtrl_Byte*)Event.GetEventObject())->ParentContainer)->SetSelection(4);
		}
		else if(Value == 70)
		{
			((ComboBox_Byte_UnitType*)((TextCtrl_Byte*)Event.GetEventObject())->ParentContainer)->SetSelection(5);
		}
		else if(Value == 80)
		{
			((ComboBox_Byte_UnitType*)((TextCtrl_Byte*)Event.GetEventObject())->ParentContainer)->SetSelection(6);
		}
		else
		{
			((ComboBox_Byte_UnitType*)((TextCtrl_Byte*)Event.GetEventObject())->ParentContainer)->SetSelection(0);
		}
	}
}

void ComboBox_Short_AttackType::OnKillFocus(wxFocusEvent& Event)
{
	((TextCtrl_Short*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Short*)Event.GetEventObject())->NoLoadList)
	{
		short Value = lexical_cast<short>(((TextCtrl_Short*)Event.GetEventObject())->GetValue());
		((ComboBox_Short_AttackType*)((TextCtrl_Short*)Event.GetEventObject())->ParentContainer)->SetSelection(0);
		((ComboBox_Short_AttackType*)((TextCtrl_Short*)Event.GetEventObject())->ParentContainer)->SetSelection(Value);
	}
}

ComboBox_Byte::ComboBox_Byte(wxWindow * parent, TextCtrl_Byte * Pointer)
: wxOwnerDrawnComboBox(parent, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY)
{
	Container = Pointer;
	Container->ParentContainer = this;

	Container->Disconnect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Byte::OnKillFocus));
	Container->Connect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(ComboBox_Byte::OnKillFocus), this);

	Connect(this->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ComboBox_Byte::OnUpdate));
}

ComboBox_Float::ComboBox_Float(wxWindow * parent, TextCtrl_Float * Pointer)
: wxOwnerDrawnComboBox(parent, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY)
{
	Container = Pointer;
	Container->ParentContainer = this;

	Container->Disconnect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Float::OnKillFocus));
	Container->Connect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(ComboBox_Float::OnKillFocus), this);

	Connect(this->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ComboBox_Float::OnUpdate));
}

ComboBox_Short::ComboBox_Short(wxWindow * parent, TextCtrl_Short * Pointer)
: wxOwnerDrawnComboBox(parent, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY)
{
	Container = Pointer;
	Container->ParentContainer = this;

	Container->Disconnect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Short::OnKillFocus));
	Container->Connect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(ComboBox_Short::OnKillFocus), this);

	Connect(this->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ComboBox_Short::OnUpdate));
}

ComboBox_Long::ComboBox_Long(wxWindow * parent, TextCtrl_Long * Pointer)
: wxOwnerDrawnComboBox(parent, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY)
{
	Container = Pointer;
	Container->ParentContainer = this;

	Container->Disconnect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Long::OnKillFocus));
	Container->Connect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(ComboBox_Long::OnKillFocus), this);

	Connect(this->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ComboBox_Long::OnUpdate));
}

ComboBox_Byte_EffectType::ComboBox_Byte_EffectType(wxWindow * parent, TextCtrl_Byte * Pointer)
: wxOwnerDrawnComboBox(parent, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY)
{
	Container = Pointer;
	Container->ParentContainer = this;

	Container->Disconnect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Byte::OnKillFocus));
	Container->Connect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(ComboBox_Byte_EffectType::OnKillFocus), this);

	Connect(this->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ComboBox_Byte_EffectType::OnUpdate));
}

ComboBox_Byte_UnitType::ComboBox_Byte_UnitType(wxWindow * parent, TextCtrl_Byte * Pointer)
: wxOwnerDrawnComboBox(parent, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY)
{
	Container = Pointer;
	Container->ParentContainer = this;

	Container->Disconnect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Byte::OnKillFocus));
	Container->Connect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(ComboBox_Byte_UnitType::OnKillFocus), this);

	Connect(this->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ComboBox_Byte_UnitType::OnUpdate));
}

ComboBox_Short_AttackType::ComboBox_Short_AttackType(wxWindow * parent, TextCtrl_Short * Pointer)
: wxOwnerDrawnComboBox(parent, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY)
{
	Container = Pointer;
	Container->ParentContainer = this;

	Container->Disconnect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Short::OnKillFocus));
	Container->Connect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(ComboBox_Short_AttackType::OnKillFocus), this);

	Connect(this->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ComboBox_Short_AttackType::OnUpdate));
}
