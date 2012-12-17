#include "AGE_TextControls.h"

bool TextCtrl_Byte::SaveEdits()
{
	if(container.size() < 1) return false;
	wxString value = GetValue().c_str();
	if(value.size() > 0)
	{
		try
		{
			char casted = (char)lexical_cast<short>(value);
			if(lexical_cast<short>(value) == casted)
			{
				if(*container[0] != casted)
			    {
					for(int loop=0; loop<container.size(); loop++)
					{
						*container[loop] = casted;
					}
					return true;
				}
			}
			else
			{
				wxMessageBox("Invalid entry!\nPlease enter a number from -128 to 127");
				SetFocus();
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
		ChangeValue(lexical_cast<string>((short)*container[0]));
	}
	return false;
}

bool TextCtrl_AByte::SaveEdits()
{
	if(container.size() < 1) return false;
	wxString value = GetValue().c_str();
	if(value.size() > 0)
	{
		try
		{
			char casted = (char)lexical_cast<short>(value);
			if(lexical_cast<short>(value) == casted)
			{
				if(*container[0][0] != casted)
				{
					for(int loop=0; loop<container.size(); loop++)
					{
						for(int loop2=0; loop2<container[loop].size(); loop2++)
						*container[loop][loop2] = casted;
					}
					return true;
				}
			}
			else
			{
				wxMessageBox("Invalid entry!\nPlease enter a number from -128 to 127");
				SetFocus();
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
		ChangeValue(lexical_cast<string>((short)*container[0][0]));
	}
	return false;
}

bool TextCtrl_UByte::SaveEdits()
{
	if(container.size() < 1) return false;
	wxString value = GetValue().c_str();
	if(value.size() > 0)
	{
		try
		{
			unsigned char casted = (unsigned char)lexical_cast<short>(value);
			if(lexical_cast<short>(value) == casted)
			{
				if(*container[0] != casted)
			    {
					for(int loop=0; loop<container.size(); loop++)
					{
						*container[loop] = casted;
					}
					return true;
				}
			}
			else
			{
				wxMessageBox("Invalid entry!\nPlease enter a number from 0 to 255");
				SetFocus();
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
		ChangeValue(lexical_cast<string>((short)*container[0]));
	}
	return false;
}

bool TextCtrl_Float::SaveEdits()
{
	if(container.size() < 1) return false;
	wxString value = GetValue().c_str();
	if(value.size() > 0)
	{
		try
	    {
			float casted = lexical_cast<float>(value);
			if(*container[0] != casted)
			{
			    for(int loop=0; loop<container.size(); loop++)
				{
					*container[loop] = casted;
				}
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
		ChangeValue(lexical_cast<string>(*container[0]));
	}
	return false;
}

bool TextCtrl_AFloat::SaveEdits()
{
	if(container.size() < 1) return false;
	wxString value = GetValue().c_str();
	if(value.size() > 0)
	{
		try
	    {
			float casted = lexical_cast<float>(value);
			if(*container[0][0] != casted)
			{
				for(int loop=0; loop<container.size(); loop++)
				{
					for(int loop2=0; loop2<container[loop].size(); loop2++)
					*container[loop][loop2] = casted;
				}
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
		ChangeValue(lexical_cast<string>(*container[0][0]));
	}
	return false;
}

bool TextCtrl_Long::SaveEdits()
{
	if(container.size() < 1) return false;
	wxString value = GetValue().c_str();
	if(value.size() > 0)
	{
		try
		{
			int32_t casted = lexical_cast<int32_t>(value);
			if(*container[0] != casted)
			{
				for(int loop=0; loop<container.size(); loop++)
				{
					*container[loop] = casted;
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

bool TextCtrl_ALong::SaveEdits()
{
	if(container.size() < 1) return false;
	wxString value = GetValue().c_str();
	if(value.size() > 0)
	{
		try
		{
			int32_t casted = lexical_cast<int32_t>(value);
			if(*container[0][0] != casted)
			{
				for(int loop=0; loop<container.size(); loop++)
				{
					for(int loop2=0; loop2<container[loop].size(); loop2++)
					*container[loop][loop2] = casted;
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
		ChangeValue(lexical_cast<string>(*container[0][0]));
	}
	return false;
}

bool TextCtrl_Short::SaveEdits()
{
	if(container.size() < 1) return false;
	wxString value = GetValue().c_str();
	if(value.size() > 0)
	{
		try
		{
			int16_t casted = lexical_cast<int16_t>(value);
			if(*container[0] != casted)
			{
				for(int loop=0; loop<container.size(); loop++)
				{
					*container[loop] = casted;
				}
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
		ChangeValue(lexical_cast<string>(*container[0]));
	}
	return false;
}

bool TextCtrl_AShort::SaveEdits()
{
	if(container.size() < 1) return false;
	wxString value = GetValue().c_str();
	if(value.size() > 0)
	{
		try
		{
			int16_t casted = lexical_cast<int16_t>(value);
			if(*container[0][0] != casted)
			{
				for(int loop=0; loop<container.size(); loop++)
				{
					for(int loop2=0; loop2<container[loop].size(); loop2++)
					*container[loop][loop2] = casted;
				}
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
		ChangeValue(lexical_cast<string>(*container[0][0]));
	}
	return false;
}

bool TextCtrl_UShort::SaveEdits()
{
	if(container.size() < 1) return false;
	wxString value = GetValue().c_str();
	if(value.size() > 0)
	{
		try
		{
			uint16_t casted = lexical_cast<uint16_t>(value);
			if(*container[0] != casted)
			{
				for(int loop=0; loop<container.size(); loop++)
				{
					*container[loop] = casted;
				}
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
		ChangeValue(lexical_cast<string>(*container[0]));
	}
	return false;
}

bool TextCtrl_AUShort::SaveEdits()
{
	if(container.size() < 1) return false;
	wxString value = GetValue().c_str();
	if(value.size() > 0)
	{
		try
		{
			uint16_t casted = lexical_cast<uint16_t>(value);
			if(*container[0][0] != casted)
			{
				for(int loop=0; loop<container.size(); loop++)
				{
					for(int loop2=0; loop2<container[loop].size(); loop2++)
					*container[loop][loop2] = casted;
				}
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
		ChangeValue(lexical_cast<string>(*container[0][0]));
	}
	return false;
}

bool TextCtrl_String::SaveEdits()	// This may crash the program.
{
	if(container.size() < 1) return false;
	wxString value = GetValue().c_str();
	if(value.size() > 0)
	{
	    if(*container[0] != value) // Has been changed
	    {
			if(value.size() <= MaxSize)
			{
				for(int loop=0; loop<container.size(); loop++)
				{
					*container[loop] = value; // Update data field
				}
			}
			else
			{
				value = value.substr(0, MaxSize);
				for(int loop=0; loop<container.size(); loop++)
				{
					*container[loop] = value;
				}
				ChangeValue(*container[0]);
			}
			return true;
	    }
	}
	else
	{
		ChangeValue(*container[0]);
	}
	return false;
}

bool TextCtrl_AString::SaveEdits()	// This may crash the program.
{
	if(container.size() < 1) return false;
	wxString value = GetValue().c_str();
	if(value.size() > 0)
	{
	    if(*container[0][0] != value) // Has been changed
	    {
			if(value.size() <= MaxSize)
			{
				for(int loop=0; loop<container.size(); loop++)
				{
					for(int loop2=0; loop2<container[loop].size(); loop2++)
					*container[loop][loop2] = value;
				}
			}
			else
			{
				value = value.substr(0, MaxSize);
				for(int loop=0; loop<container.size(); loop++)
				{
					for(int loop2=0; loop2<container[loop].size(); loop2++)
					*container[loop][loop2] = value;
				}
				ChangeValue(*container[0][0]);
			}
			return true;
	    }
	}
	else
	{
		ChangeValue(*container[0][0]);
	}
	return false;
}
