/* AGE_TextControls.cpp */

#include "AGE_TextControls.h"

void TextCtrl_Bool::OnKillFocus(wxFocusEvent& Event)
{
	wxString Value = GetValue().c_str();
	NoLoadList = false;
	if(Container == NULL)
	{
	    NoLoadList = true;
	}
	else if(Value.size() > 0)
	{
		try
		{
			if(*((bool*)Container) != lexical_cast<bool>(Value))
			{
			    *((bool*)Container) = lexical_cast<bool>(Value);
			}
			else
			{
				NoLoadList = true;
			}
		}
		catch(bad_lexical_cast e)
		{
			NoLoadList = true;
		    wxMessageBox("Invalid entry!\nPlease enter 0 or 1");
		    SetFocus();
		}
	}
	else
	{
		ChangeValue(lexical_cast<string>(*Container));
	}
//	Event.Skip();
}

void TextCtrl_Byte::OnKillFocus(wxFocusEvent& Event)
{
	wxString Value = GetValue().c_str();
	NoLoadList = false;
	if(Container == NULL)
	{
	    NoLoadList = true;
	}
	else if(Value.size() > 0)
	{
		try
		{
		    if(*((char*)Container) != (char)lexical_cast<short>(Value))
			{
			    if(lexical_cast<short>(Value) == (char)lexical_cast<short>(Value))
			    {
					*((char*)Container) = (char)lexical_cast<short>(Value);
				}
			    else
			    {
					NoLoadList = true;
			    	wxMessageBox("Invalid entry!\nPlease enter a number from -128 to 127");
			    	SetFocus();
			    }
			}
			else
			{
			    NoLoadList = true;
			}
		}
		catch(bad_lexical_cast e)
		{
			NoLoadList = true;
		    wxMessageBox("Invalid entry!\nPlease enter a number from -128 to 127");
		    SetFocus();
		}
	}
	else
	{
		ChangeValue(lexical_cast<string>((short)*Container));
	}
//	Event.Skip();
}

void TextCtrl_Float::OnKillFocus(wxFocusEvent& Event)
{
	wxString Value = GetValue().c_str();
	NoLoadList = false;
	if(Container == NULL)
	{
	    NoLoadList = true;
	}
	else if(Value.size() > 0)
	{
		try
	    {
			if(*((float*)Container) != lexical_cast<float>(Value))
			{
			    *((float*)Container) = lexical_cast<float>(Value);
			}
			else
			{
				NoLoadList = true;
			}
		}
		catch(bad_lexical_cast e)
		{
			NoLoadList = true;
		    wxMessageBox("Invalid entry!\nPlease enter a valid floating point number");
		    SetFocus();
		}
	}
	else
	{
		ChangeValue(lexical_cast<string>(*Container));
	}
//	Event.Skip();
}

void TextCtrl_Long::OnKillFocus(wxFocusEvent& Event)
{
	wxString Value = GetValue().c_str();
	NoLoadList = false;
	if(Container == NULL)
	{
		NoLoadList = true;
	}
	else if(Value.size() > 0)
	{
		try
		{
			if(*((long*)Container) != lexical_cast<long>(Value))
			{
				*((long*)Container) = lexical_cast<long>(Value);
			}
			else
			{
				NoLoadList = true;
			}
		}
		catch(bad_lexical_cast e)
		{
			NoLoadList = true;
			wxMessageBox("Invalid entry!\nPlease enter a number from -2 147 483 648 to 2 147 483 647");
			SetFocus();
		}
	}
	else
	{
		ChangeValue(lexical_cast<string>(*Container));
	}
//	Event.Skip();
}

void TextCtrl_Short::OnKillFocus(wxFocusEvent& Event)
{
	wxString Value = GetValue().c_str();
	NoLoadList = false;
	if(Container == NULL)
	{
		NoLoadList = true;
	}
	else if(Value.size() > 0)
	{
		try
		{
			if(*((short*)Container) != lexical_cast<short>(Value))
			{
				*((short*)Container) = lexical_cast<short>(Value);
			}
			else
			{
				NoLoadList = true;
			}
		}
		catch(bad_lexical_cast e)
		{
			NoLoadList = true;
			wxMessageBox("Invalid entry!\nPlease enter a number from -32 768 to 32 767");
			SetFocus();
		}
	}
	else
	{
		ChangeValue(lexical_cast<string>(*Container));
	}
//	Event.Skip();
}

void TextCtrl_UnShort::OnKillFocus(wxFocusEvent& Event)
{
	wxString Value = GetValue().c_str();
	NoLoadList = false;
	if(Container == NULL)
	{
		NoLoadList = true;
	}
	else if(Value.size() > 0)
	{
		try
		{
			if(*((unsigned short*)Container) != lexical_cast<unsigned short>(Value))
			{
				*((unsigned short*)Container) = lexical_cast<unsigned short>(Value);
			}
			else
			{
				NoLoadList = true;
			}
		}
		catch(bad_lexical_cast e)
		{
			NoLoadList = true;
			wxMessageBox("Invalid entry!\nPlease enter a number from 0 to 65 535");
			SetFocus();
		}
	}
	else
	{
		ChangeValue(lexical_cast<string>(*Container));
	}
//	Event.Skip();
}

void TextCtrl_String::OnKillFocus(wxFocusEvent& Event)	// This may crash the program.
{
	NoLoadList = false;
	if(Container == NULL)
	{
	    NoLoadList = true;
	}
	else if(Length == -1) // is a string, no warnings shows up.
	{
	    if(*((string*)Container) != GetValue().c_str()) // has been changed
	    {
	    	*((string*)Container) = GetValue().c_str(); // update data field
	    }
	    else
	    {
	        NoLoadList = true;
	    }
	}
	else if(Length > GetValue().size() + 1) // is a set of chars, this works!
	{
	    if(strncmp((char*)Container, GetValue().c_str(), Length) != 0)
	    {
			strncpy((char*)Container, GetValue().c_str(), Length);
		}
		else
		{
		    NoLoadList = true;
		}
	}
	else // is shown when too many chars in a char control.
	{
	    NoLoadList = true;
	    wxMessageBox("Max length: " + lexical_cast<string>(Length));
	    SetFocus();
	}
//	Event.Skip();
}

TextCtrl_Bool::TextCtrl_Bool(wxWindow * parent, string InitValue, bool * Pointer)
: wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20), 0, wxDefaultValidator)
{
	Container = Pointer;
	this->SetBackgroundColour(wxColour(255, 255, 205));
	Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Bool::OnKillFocus));	// Must-have
}

TextCtrl_Byte::TextCtrl_Byte(wxWindow * parent, string InitValue, char * Pointer)
: wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20), 0, wxDefaultValidator)
{
	Container = Pointer;
	this->SetBackgroundColour(wxColour(255, 235, 215));
	Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Byte::OnKillFocus));	// Must-have
}

TextCtrl_Float::TextCtrl_Float(wxWindow * parent, string InitValue, float * Pointer)
: wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20), 0, wxDefaultValidator)
{
	Container = Pointer;
	this->SetBackgroundColour(wxColour(255, 225, 255));
	Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Float::OnKillFocus));
}

TextCtrl_Long::TextCtrl_Long(wxWindow * parent, string InitValue, long * Pointer)
: wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20), 0, wxDefaultValidator)
{
	Container = Pointer;
	this->SetBackgroundColour(wxColour(215, 255, 255));
	Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Long::OnKillFocus));
}

TextCtrl_Short::TextCtrl_Short(wxWindow * parent, string InitValue, short * Pointer)
: wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20), 0, wxDefaultValidator)
{
	Container = Pointer;
	this->SetBackgroundColour(wxColour(210, 230, 255));
	Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Short::OnKillFocus));
}

TextCtrl_UnShort::TextCtrl_UnShort(wxWindow * parent, string InitValue, unsigned short * Pointer)
: wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20), 0, wxDefaultValidator)
{
	Container = Pointer;
	this->SetBackgroundColour(wxColour(210, 230, 255));
	Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_UnShort::OnKillFocus));
}

TextCtrl_String::TextCtrl_String(wxWindow * parent, string InitValue, void * Pointer, short CLength)
: wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20), 0, wxDefaultValidator)
{
	Container = Pointer;
	Length = CLength;
	this->SetBackgroundColour(wxColour(220, 255, 220));
	Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_String::OnKillFocus));
}
