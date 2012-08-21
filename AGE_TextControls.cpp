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

void TextCtrl_UByte::OnKillFocus(wxFocusEvent& Event)
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
		    if(*((unsigned char*)Container) != (unsigned char)lexical_cast<short>(Value))
			{
			    if(lexical_cast<short>(Value) == (unsigned char)lexical_cast<short>(Value))
			    {
					*((unsigned char*)Container) = (unsigned char)lexical_cast<short>(Value);
				}
			    else
			    {
					NoLoadList = true;
			    	wxMessageBox("Invalid entry!\nPlease enter a number from 0 to 255");
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
		    wxMessageBox("Invalid entry!\nPlease enter a number from 0 to 255");
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
			if(*((int32_t*)Container) != lexical_cast<int32_t>(Value))
			{
				*((int32_t*)Container) = lexical_cast<int32_t>(Value);
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
			if(*((int16_t*)Container) != lexical_cast<int16_t>(Value))
			{
				*((int16_t*)Container) = lexical_cast<int16_t>(Value);
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

void TextCtrl_UShort::OnKillFocus(wxFocusEvent& Event)
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
			if(*((uint16_t*)Container) != lexical_cast<uint16_t>(Value))
			{
				*((uint16_t*)Container) = lexical_cast<uint16_t>(Value);
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
