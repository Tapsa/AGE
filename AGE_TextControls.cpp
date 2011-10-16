/* AGE_TextControls.cpp */

#include "AGE_TextControls.h"

void TextCtrl_Byte::OnKillFocus(wxFocusEvent& Event)
{
	string Value = GetValue().c_str();
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
			    	wxMessageBox("Invalid Entry!\nPlease enter a number from -128 to 127");
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
		    wxMessageBox("Crashing Entry!\nPlease enter a number from -128 to 127");
		    SetFocus();
		}
	}
	else
	{
		NoLoadList = true;
	    wxMessageBox("Empty Entry!\nPlease enter a number from -128 to 127");
	    SetFocus();
	}
}

void TextCtrl_Float::OnKillFocus(wxFocusEvent& Event)
{
	string Value = GetValue().c_str();
	NoLoadList = false;
	if(Container == NULL)
	{
	    NoLoadList = true;
	}
	else if(Value.size() > 0)
	{
		try
	    {
			if(*Container != lexical_cast<float>(Value))
			{
			    *Container = lexical_cast<float>(Value);
			}
			else
			{
				NoLoadList = true;
			}
		}
		catch(bad_lexical_cast e)
		{
			NoLoadList = true;
		    wxMessageBox("Invalid Entry!\nPlease enter a valid floating point number");
		    SetFocus();
		}
	}
	else
	{
		NoLoadList = true;
	    wxMessageBox("Empty Entry!\nPlease enter a valid floating point number");
	    SetFocus();
	}
}

void TextCtrl_Long::OnKillFocus(wxFocusEvent& Event)
{
	string Value = GetValue().c_str();
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
			wxMessageBox("Invalid Entry!\nPlease enter a number from -2 147 483 648 to 2 147 483 647");
			SetFocus();
		}
	}
	else
	{
		NoLoadList = true;
		wxMessageBox("Empty Entry!\nPlease enter a number from -2 147 483 648 to 2 147 483 647");
		SetFocus();
	}
}

void TextCtrl_Short::OnKillFocus(wxFocusEvent& Event)
{
	string Value = GetValue().c_str();
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
			wxMessageBox("Invalid Entry!\nPlease enter a number from -32 768 to 32 767");
			SetFocus();
		}
	}
	else
	{
		NoLoadList = true;
		wxMessageBox("Empty Entry!\nPlease enter a number from -32 768 to 32 767");
		SetFocus();
	}
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
}

TextCtrl_Byte::TextCtrl_Byte(wxWindow * parent, string InitValue, void * Pointer)
: wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator)
{
	Container = Pointer;
	this->SetBackgroundColour(wxColour(255, 235, 215));	
	Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Byte::OnKillFocus));	// Must-have
}

TextCtrl_Float::TextCtrl_Float(wxWindow * parent, string InitValue, float * Pointer)
: wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator)
{
	Container = Pointer;
	this->SetBackgroundColour(wxColour(255, 225, 255));
	Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Float::OnKillFocus));
}

TextCtrl_Long::TextCtrl_Long(wxWindow * parent, string InitValue, long * Pointer)
: wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator)
{
	Container = Pointer;
	this->SetBackgroundColour(wxColour(215, 255, 255));
	Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Long::OnKillFocus));
}

TextCtrl_Short::TextCtrl_Short(wxWindow * parent, string InitValue, short * Pointer)
: wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator)
{
	Container = Pointer;
	this->SetBackgroundColour(wxColour(210, 230, 255));
	Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Short::OnKillFocus));
}

TextCtrl_String::TextCtrl_String(wxWindow * parent, string InitValue, void * Pointer, short CLength)
: wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator)
{
	Container = Pointer;
	Length = CLength;
	this->SetBackgroundColour(wxColour(220, 255, 220));
	Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_String::OnKillFocus));
}
