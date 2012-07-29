/* AGE_CheckBoxes.cpp */

#include "AGE_CheckBoxes.h"

void CheckBox_Bool::OnUpdate(wxCommandEvent& Event)
{
	Container->ChangeValue(lexical_cast<string>((bool)GetValue()));

	wxFocusEvent Temp;
	Container->OnKillFocus(Temp);
}

void CheckBox_Byte::OnUpdate(wxCommandEvent& Event)
{
	Container->ChangeValue(lexical_cast<string>((int8_t)GetValue()));

	wxFocusEvent Temp;
	Container->OnKillFocus(Temp);
}

void CheckBox_Float::OnUpdate(wxCommandEvent& Event)
{
	Container->ChangeValue(lexical_cast<string>((float)GetValue()));

	wxFocusEvent Temp;
	Container->OnKillFocus(Temp);
}

void CheckBox_Short::OnUpdate(wxCommandEvent& Event)
{
	Container->ChangeValue(lexical_cast<string>((int16_t)GetValue()));

	wxFocusEvent Temp;
	Container->OnKillFocus(Temp);
}

void CheckBox_Short_ZeroIsYes::OnUpdate(wxCommandEvent& Event)
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

void CheckBox_Long_ZeroIsYes::OnUpdate(wxCommandEvent& Event)
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

void CheckBox_Bool::OnKillFocus(wxFocusEvent& Event)
{
	((TextCtrl_Bool*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Bool*)Event.GetEventObject())->NoLoadList)
	{
		bool Value = lexical_cast<bool>(((TextCtrl_Bool*)Event.GetEventObject())->GetValue());
		((CheckBox_Bool*)((TextCtrl_Bool*)Event.GetEventObject())->ParentContainer)->SetValue(Value);
	}
}

void CheckBox_Byte::OnKillFocus(wxFocusEvent& Event)
{
	((TextCtrl_Byte*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Byte*)Event.GetEventObject())->NoLoadList)
	{
		int8_t Value = lexical_cast<int8_t>(((TextCtrl_Byte*)Event.GetEventObject())->GetValue());
		((CheckBox_Byte*)((TextCtrl_Byte*)Event.GetEventObject())->ParentContainer)->SetValue(Value);
	}
}

void CheckBox_Float::OnKillFocus(wxFocusEvent& Event)
{
	((TextCtrl_Float*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Float*)Event.GetEventObject())->NoLoadList)
	{
		float Value = lexical_cast<float>(((TextCtrl_Float*)Event.GetEventObject())->GetValue());
		((CheckBox_Float*)((TextCtrl_Float*)Event.GetEventObject())->ParentContainer)->SetValue(Value);
	}
}

void CheckBox_Short::OnKillFocus(wxFocusEvent& Event)
{
	((TextCtrl_Short*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Short*)Event.GetEventObject())->NoLoadList)
	{
		int16_t Value = lexical_cast<int16_t>(((TextCtrl_Short*)Event.GetEventObject())->GetValue());
		((CheckBox_Short*)((TextCtrl_Short*)Event.GetEventObject())->ParentContainer)->SetValue(Value);
	}
}

void CheckBox_Short_ZeroIsYes::OnKillFocus(wxFocusEvent& Event)
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

void CheckBox_Long_ZeroIsYes::OnKillFocus(wxFocusEvent& Event)
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

CheckBox_Bool::CheckBox_Bool(wxWindow * parent, string InitValue, TextCtrl_Bool * Pointer)
: wxCheckBox(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20), 0, wxDefaultValidator)
{
	Container = Pointer;
	Container->ParentContainer = this;

	Container->Disconnect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Bool::OnKillFocus));
	Container->Connect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(CheckBox_Bool::OnKillFocus), this);

	Connect(this->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CheckBox_Bool::OnUpdate));
}

CheckBox_Byte::CheckBox_Byte(wxWindow * parent, string InitValue, TextCtrl_Byte * Pointer)
: wxCheckBox(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20), 0, wxDefaultValidator)
{
	Container = Pointer;
	Container->ParentContainer = this;

	Container->Disconnect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Byte::OnKillFocus));
	Container->Connect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(CheckBox_Byte::OnKillFocus), this);

	Connect(this->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CheckBox_Byte::OnUpdate));
}

CheckBox_Float::CheckBox_Float(wxWindow * parent, string InitValue, TextCtrl_Float * Pointer)
: wxCheckBox(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20), 0, wxDefaultValidator)
{
	Container = Pointer;
	Container->ParentContainer = this;

	Container->Disconnect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Float::OnKillFocus));
	Container->Connect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(CheckBox_Float::OnKillFocus), this);

	Connect(this->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CheckBox_Float::OnUpdate));
}

CheckBox_Short::CheckBox_Short(wxWindow * parent, string InitValue, TextCtrl_Short * Pointer)
: wxCheckBox(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20), 0, wxDefaultValidator)
{
	Container = Pointer;
	Container->ParentContainer = this;

	Container->Disconnect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Short::OnKillFocus));
	Container->Connect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(CheckBox_Short::OnKillFocus), this);

	Connect(this->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CheckBox_Short::OnUpdate));
}

CheckBox_Short_ZeroIsYes::CheckBox_Short_ZeroIsYes(wxWindow * parent, string InitValue, TextCtrl_Short * Pointer)
: wxCheckBox(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20), 0, wxDefaultValidator)
{
	Container = Pointer;
	Container->ParentContainer = this;

	Container->Disconnect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Short::OnKillFocus));
	Container->Connect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(CheckBox_Short_ZeroIsYes::OnKillFocus), this);

	Connect(this->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CheckBox_Short_ZeroIsYes::OnUpdate));
}

CheckBox_Long_ZeroIsYes::CheckBox_Long_ZeroIsYes(wxWindow * parent, string InitValue, TextCtrl_Long * Pointer)
: wxCheckBox(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20), 0, wxDefaultValidator)
{
	Container = Pointer;
	Container->ParentContainer = this;

	Container->Disconnect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Long::OnKillFocus));
	Container->Connect(Container->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(CheckBox_Long_ZeroIsYes::OnKillFocus), this);

	Connect(this->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CheckBox_Long_ZeroIsYes::OnUpdate));
}
