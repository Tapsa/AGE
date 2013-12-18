#include "AGE_TextControls.h"

const wxString AGETextCtrl::BATCHWARNING
= "Use b+[x], b-[x], b*[x] or b/[x]\nwhere [x] is a number.";
const wxString AGETextCtrl::BWTITLE = "Incorrect batch script!";
const wxString AGETextCtrl::IETITLE = "Invalid entry!";

int TextCtrl_Byte::SaveEdits()
{
	if(container.empty()) return 1;
	wxString value = GetValue().c_str();
	if(value.size() > 0)
	{
		short batchMode = 0;
		if(value[0] == 'b' && !BatchCheck(value, batchMode))
		{
			wxMessageBox(BATCHWARNING, BWTITLE);
			return 1;
		}
		try
		{
			int8_t casted = (int8_t)lexical_cast<short>(value);
			if(lexical_cast<short>(value) == casted)
			{
				if(batchMode > 0)
				{
					BatchSave(container, batchMode, casted);
					ChangeValue(lexical_cast<string>(*container[0]));
					if(LinkedBox) LinkedBox->Update(casted);
					return 0;
				}
				if(*container[0] != casted)
				{
					for(auto &pointer: container)
					{
						*pointer = casted;
					}
					if(LinkedBox) LinkedBox->Update(casted);
					return 0;
				}
			}
			else
			{
				return 2;
			}
		}
		catch(bad_lexical_cast e)
		{
			return 2;
		}
	}
	else
	{
		ChangeValue(lexical_cast<string>((short)*container[0]));
	}
	return 1;
}

int TextCtrl_UByte::SaveEdits()
{
	if(container.empty()) return 1;
	wxString value = GetValue().c_str();
	if(value.size() > 0)
	{
		short batchMode = 0;
		if(value[0] == 'b' && !BatchCheck(value, batchMode))
		{
			wxMessageBox(BATCHWARNING, BWTITLE);
			return 1;
		}
		try
		{
			uint8_t casted = (uint8_t)lexical_cast<short>(value);
			if(lexical_cast<short>(value) == casted)
			{
				if(batchMode > 0)
				{
					BatchSave(container, batchMode, casted);
					ChangeValue(lexical_cast<string>(*container[0]));
					if(LinkedBox) LinkedBox->Update(casted);
					return 0;
				}
				if(*container[0] != casted)
				{
					for(auto &pointer: container)
					{
						*pointer = casted;
					}
					if(LinkedBox) LinkedBox->Update(casted);
					return 0;
				}
			}
			else
			{
				return 2;
			}
		}
		catch(bad_lexical_cast e)
		{
			return 2;
		}
	}
	else
	{
		ChangeValue(lexical_cast<string>((short)*container[0]));
	}
	return 1;
}

int TextCtrl_Float::SaveEdits()
{
	if(container.empty()) return 1;
	wxString value = GetValue().c_str();
	if(value.size() > 0)
	{
		short batchMode = 0;
		if(value[0] == 'b' && !BatchCheck(value, batchMode))
		{
			wxMessageBox(BATCHWARNING, BWTITLE);
			return 1;
		}
		try
		{
			float casted = lexical_cast<float>(value);
			if(batchMode > 0)
			{
				BatchSave(container, batchMode, casted);
				ChangeValue(lexical_cast<string>(*container[0]));
				if(LinkedBox) LinkedBox->Update(casted);
				return 0;
			}
			if(*container[0] != casted)
			{
				for(auto &pointer: container)
				{
					*pointer = casted;
				}
				if(LinkedBox) LinkedBox->Update(casted);
				return 0;
			}
		}
		catch(bad_lexical_cast e)
		{
			return 2;
		}
	}
	else
	{
		ChangeValue(lexical_cast<string>(*container[0]));
	}
	return 1;
}

int TextCtrl_Long::SaveEdits()
{
	if(container.empty()) return 1;
	wxString value = GetValue().c_str();
	if(value.size() > 0)
	{
		short batchMode = 0;
		if(value[0] == 'b' && !BatchCheck(value, batchMode))
		{
			wxMessageBox(BATCHWARNING, BWTITLE);
			return 1;
		}
		try
		{
			int32_t casted = lexical_cast<int32_t>(value);
			if(batchMode > 0)
			{
				BatchSave(container, batchMode, casted);
				ChangeValue(lexical_cast<string>(*container[0]));
				if(LinkedBox) LinkedBox->Update(casted);
				return 0;
			}
			if(*container[0] != casted)
			{
				for(auto &pointer: container)
				{
					*pointer = casted;
				}
				if(LinkedBox) LinkedBox->Update(casted);
				return 0;
			}
		}
		catch(bad_lexical_cast e)
		{
			return 2;
		}
	}
	else
	{
		ChangeValue(lexical_cast<string>(*container[0]));
	}
	return 1;
}

int TextCtrl_Short::SaveEdits()
{
	if(container.empty()) return 1;
	wxString value = GetValue().c_str();
	if(value.size() > 0)
	{
		short batchMode = 0;
		if(value[0] == 'b' && !BatchCheck(value, batchMode))
		{
			wxMessageBox(BATCHWARNING, BWTITLE);
			return 1;
		}
		try
		{
			int16_t casted = lexical_cast<int16_t>(value);
			if(batchMode > 0)
			{
				BatchSave(container, batchMode, casted);
				ChangeValue(lexical_cast<string>(*container[0]));
				if(LinkedBox) LinkedBox->Update(casted);
				return 0;
			}
			if(*container[0] != casted)
			{
				for(auto &pointer: container)
				{
					*pointer = casted;
				}
				if(LinkedBox) LinkedBox->Update(casted);
				return 0;
			}
		}
		catch(bad_lexical_cast e)
		{
			return 2;
		}
	}
	else
	{
		ChangeValue(lexical_cast<string>(*container[0]));
	}
	return 1;
}

int TextCtrl_UShort::SaveEdits()
{
	if(container.empty()) return 1;
	wxString value = GetValue().c_str();
	if(value.size() > 0)
	{
		short batchMode = 0;
		if(value[0] == 'b' && !BatchCheck(value, batchMode))
		{
			wxMessageBox(BATCHWARNING, BWTITLE);
			return 1;
		}
		try
		{
			uint16_t casted = lexical_cast<uint16_t>(value);
			if(batchMode > 0)
			{
				BatchSave(container, batchMode, casted);
				ChangeValue(lexical_cast<string>(*container[0]));
				if(LinkedBox) LinkedBox->Update(casted);
				return 0;
			}
			if(*container[0] != casted)
			{
				for(auto &pointer: container)
				{
					*pointer = casted;
				}
				if(LinkedBox) LinkedBox->Update(casted);
				return 0;
			}
		}
		catch(bad_lexical_cast e)
		{
			return 2;
		}
	}
	else
	{
		ChangeValue(lexical_cast<string>(*container[0]));
	}
	return 1;
}

int TextCtrl_String::SaveEdits()	// This may crash the program.
{
	if(container.empty()) return 1;
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
			return 0;
		}
	}
	else
	{
		ChangeValue(*container[0]);
	}
	return 1;
}
