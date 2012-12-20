#include "AGE_TextControls.h"

bool TextCtrl_Byte::SaveEdits()
{
	if(container.empty()) return false;
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
					for(auto &pointer: container)
					{
						*pointer = casted;
					}
					if(LinkedBox) LinkedBox->Update(casted);
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

bool TextCtrl_UByte::SaveEdits()
{
	if(container.empty()) return false;
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
					for(auto &pointer: container)
					{
						*pointer = casted;
					}
					if(LinkedBox) LinkedBox->Update(casted);
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
	if(container.empty()) return false;
	wxString value = GetValue().c_str();
	if(value.size() > 0)
	{
		try
		{
			float casted = lexical_cast<float>(value);
			if(*container[0] != casted)
			{
				for(auto &pointer: container)
				{
					*pointer = casted;
				}
				if(LinkedBox) LinkedBox->Update(casted);
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

bool TextCtrl_Long::SaveEdits()
{
	if(container.empty()) return false;
	wxString value = GetValue().c_str();
	if(value.size() > 0)
	{
		try
		{
			int32_t casted = lexical_cast<int32_t>(value);
			if(*container[0] != casted)
			{
				for(auto &pointer: container)
				{
					*pointer = casted;
				}
				if(LinkedBox) LinkedBox->Update(casted);
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
	if(container.empty()) return false;
	wxString value = GetValue().c_str();
	if(value.size() > 0)
	{
		try
		{
			int16_t casted = lexical_cast<int16_t>(value);
			if(*container[0] != casted)
			{
				for(auto &pointer: container)
				{
					*pointer = casted;
				}
				if(LinkedBox) LinkedBox->Update(casted);
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

bool TextCtrl_UShort::SaveEdits()
{
	if(container.empty()) return false;
	wxString value = GetValue().c_str();
	if(value.size() > 0)
	{
		try
		{
			uint16_t casted = lexical_cast<uint16_t>(value);
			if(*container[0] != casted)
			{
				for(auto &pointer: container)
				{
					*pointer = casted;
				}
				if(LinkedBox) LinkedBox->Update(casted);
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

bool TextCtrl_String::SaveEdits()	// This may crash the program.
{
	if(container.empty()) return false;
	wxString value = GetValue().c_str();
	if(value.size() > 0)
	{
		if(*container[0] != value) // Has been changed
		{
			if(value.size() <= MaxSize)
			{
				for(auto &pointer: container)
				{
					*pointer = value; // Update data field
				}
			}
			else
			{
				value = value.substr(0, MaxSize);
				for(auto &pointer: container)
				{
					*pointer = value;
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
