#include "AGE_TextControls.h"

bool TextCtrl_Byte::SaveEdits()
{
	if(Container == NULL) return false;
	wxString Value = GetValue().c_str();
	if(Value.size() > 0)
	{
		try
		{
		    if(*Container != (char)lexical_cast<short>(Value))
			{
			    if(lexical_cast<short>(Value) == (char)lexical_cast<short>(Value))
			    {
					*Container = (char)lexical_cast<short>(Value);
					return true;
				}
			    else
			    {
			    	wxMessageBox("Invalid entry!\nPlease enter a number from -128 to 127");
			    	SetFocus();
			    }
			}
		}
		catch(bad_lexical_cast e)
		{
		    wxMessageBox("Invalid entry!\nPlease enter a number from -128 to 127");
		    SetFocus();
		}
	}
	else
	{
		ChangeValue(lexical_cast<string>((short)*Container));
	}
	return false;
}

bool TextCtrl_UByte::SaveEdits()
{
	if(Container == NULL) return false;
	wxString Value = GetValue().c_str();
	if(Value.size() > 0)
	{
		try
		{
		    if(*Container != (unsigned char)lexical_cast<short>(Value))
			{
			    if(lexical_cast<short>(Value) == (unsigned char)lexical_cast<short>(Value))
			    {
					*Container = (unsigned char)lexical_cast<short>(Value);
					return true;
				}
			    else
			    {
			    	wxMessageBox("Invalid entry!\nPlease enter a number from 0 to 255");
			    	SetFocus();
			    }
			}
		}
		catch(bad_lexical_cast e)
		{
		    wxMessageBox("Invalid entry!\nPlease enter a number from 0 to 255");
		    SetFocus();
		}
	}
	else
	{
		ChangeValue(lexical_cast<string>((short)*Container));
	}
	return false;
}

bool TextCtrl_Float::SaveEdits()
{
	if(Container == NULL) return false;
	wxString Value = GetValue().c_str();
	if(Value.size() > 0)
	{
		try
	    {
			if(*Container != lexical_cast<float>(Value))
			{
			    *Container = lexical_cast<float>(Value);
				return true;
			}
		}
		catch(bad_lexical_cast e)
		{
		    wxMessageBox("Invalid entry!\nPlease enter a valid floating point number");
		    SetFocus();
		}
	}
	else
	{
		ChangeValue(lexical_cast<string>(*Container));
	}
	return false;
}

bool TextCtrl_Long::SaveEdits()
{
	if(Container == NULL) return false;
	wxString Value = GetValue().c_str();
	if(Value.size() > 0)
	{
		try
		{
			if(*Container != lexical_cast<int32_t>(Value))
			{
				*Container = lexical_cast<int32_t>(Value);
				return true;
			}
		}
		catch(bad_lexical_cast e)
		{
			wxMessageBox("Invalid entry!\nPlease enter a number from -2 147 483 648 to 2 147 483 647");
			SetFocus();
		}
	}
	else
	{
		ChangeValue(lexical_cast<string>(*Container));
	}
	return false;
}

bool TextCtrl_LongMulti::SaveEdits()
{
	if(container.size() < 1) return false;
	wxString Value = GetValue().c_str();
	if(Value.size() > 0)
	{
		try
		{
			if(*container[0] != lexical_cast<int32_t>(Value))
			{
				for(short loop=0; loop<container.size(); loop++)
				{
					*container[loop] = lexical_cast<int32_t>(Value);
				}
				return true;
			}
		}
		catch(bad_lexical_cast e)
		{
			wxMessageBox("Invalid entry!\nPlease enter a number from -2 147 483 648 to 2 147 483 647");
			SetFocus();
		}
	}
	else
	{
		ChangeValue(lexical_cast<string>(*container[0]));
	}
	return false;
}

bool TextCtrl_Short::SaveEdits()
{
	if(Container == NULL) return false;
	wxString Value = GetValue().c_str();
	if(Value.size() > 0)
	{
		try
		{
			if(*Container != lexical_cast<int16_t>(Value))
			{
				*Container = lexical_cast<int16_t>(Value);
				return true;
			}
		}
		catch(bad_lexical_cast e)
		{
			wxMessageBox("Invalid entry!\nPlease enter a number from -32 768 to 32 767");
			SetFocus();
		}
	}
	else
	{
		ChangeValue(lexical_cast<string>(*Container));
	}
	return false;
}

bool TextCtrl_UShort::SaveEdits()
{
	if(Container == NULL) return false;
	wxString Value = GetValue().c_str();
	if(Value.size() > 0)
	{
		try
		{
			if(*Container != lexical_cast<uint16_t>(Value))
			{
				*Container = lexical_cast<uint16_t>(Value);
				return true;
			}
		}
		catch(bad_lexical_cast e)
		{
			wxMessageBox("Invalid entry!\nPlease enter a number from 0 to 65 535");
			SetFocus();
		}
	}
	else
	{
		ChangeValue(lexical_cast<string>(*Container));
	}
	return false;
}

bool TextCtrl_String::SaveEdits()	// This may crash the program.
{
	if(Container == NULL) return false;
	wxString Value = GetValue().c_str();
	if(Value.size() > 0)
	{
	    if(*Container != Value) // Has been changed
	    {
			if(Value.size() <= MaxSize)
			{
				*Container = Value; // Update data field
			}
			else
			{
				Value = Value.substr(0, MaxSize);
				*Container = Value;
				ChangeValue(*Container);
			}
			return true;
	    }
	}
	else
	{
		ChangeValue(*Container);
	}
	return false;
}
