#include "AGE_TextControls.h"

const wxString AGETextCtrl::BATCHWARNING = "Use b+[x], b-[x], b*[x] or b/[x]\nwhere [x] is a number.";
const wxString AGETextCtrl::BWTITLE = "Incorrect batch script!";
const wxString AGETextCtrl::IETITLE = "Invalid entry!";

int TextCtrl_Byte::SaveEdits()
{
	if(!AGETextCtrl::editable || AGETextCtrl::hexMode || container.empty()) return 1;
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
					for(auto &pointer: container)
					{
						switch(batchMode)
						{
							case 1: *(int8_t*)pointer += casted; break;
							case 2: *(int8_t*)pointer -= casted; break;
							case 3: *(int8_t*)pointer *= casted; break;
							case 4: *(int8_t*)pointer /= casted; break;
							case 5: *(int8_t*)pointer %= casted; break;
						}
					}
					ChangeValue(lexical_cast<string>((short)*(int8_t*)container[0]));
					if(LinkedBox) LinkedBox->Update(casted);
					return 0;
				}
				if(*(int8_t*)container[0] != casted)
				{
					for(auto &pointer: container)
					{
						*(int8_t*)pointer = casted;
					}
					if(LinkedBox) LinkedBox->Update(casted);
					return 0;
				}
			}
			else
			{
				wxMessageBox("Please enter a number from -128 to 127", IETITLE);
				SetFocus();
				return 2;
			}
		}
		catch(bad_lexical_cast e)
		{
			wxMessageBox("Please enter a number from -128 to 127", IETITLE);
			SetFocus();
			return 2;
		}
	}
	else
	{
		ChangeValue(lexical_cast<string>((short)*(int8_t*)container[0]));
	}
	return 1;
}

int TextCtrl_UByte::SaveEdits()
{
	if(!AGETextCtrl::editable || AGETextCtrl::hexMode || container.empty()) return 1;
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
					for(auto &pointer: container)
					{
						switch(batchMode)
						{
							case 1: *(uint8_t*)pointer += casted; break;
							case 2: *(uint8_t*)pointer -= casted; break;
							case 3: *(uint8_t*)pointer *= casted; break;
							case 4: *(uint8_t*)pointer /= casted; break;
							case 5: *(uint8_t*)pointer %= casted; break;
						}
					}
					ChangeValue(lexical_cast<string>((short)*(uint8_t*)container[0]));
					if(LinkedBox) LinkedBox->Update(casted);
					return 0;
				}
				if(*(uint8_t*)container[0] != casted)
				{
					for(auto &pointer: container)
					{
						*(uint8_t*)pointer = casted;
					}
					if(LinkedBox) LinkedBox->Update(casted);
					return 0;
				}
			}
			else
			{
				wxMessageBox("Please enter a number from 0 to 255", IETITLE);
				SetFocus();
				return 2;
			}
		}
		catch(bad_lexical_cast e)
		{
			wxMessageBox("Please enter a number from 0 to 255", IETITLE);
			SetFocus();
			return 2;
		}
	}
	else
	{
		ChangeValue(lexical_cast<string>((short)*(uint8_t*)container[0]));
	}
	return 1;
}

int TextCtrl_Float::SaveEdits()
{
	if(!AGETextCtrl::editable || AGETextCtrl::hexMode || container.empty()) return 1;
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
				for(auto &pointer: container)
				{
					switch(batchMode)
					{
						case 1: *(float*)pointer += casted; break;
						case 2: *(float*)pointer -= casted; break;
						case 3: *(float*)pointer *= casted; break;
						case 4: *(float*)pointer /= casted; break;
					}
				}
				ChangeValue(lexical_cast<string>(*(float*)container[0]));
				if(LinkedBox) LinkedBox->Update(casted);
				return 0;
			}
			if(*(float*)container[0] != casted)
			{
				for(auto &pointer: container)
				{
					*(float*)pointer = casted;
				}
				if(LinkedBox) LinkedBox->Update(casted);
				return 0;
			}
		}
		catch(bad_lexical_cast e)
		{
			wxMessageBox("Please enter a valid floating point number", IETITLE);
			SetFocus();
			return 2;
		}
	}
	else
	{
		ChangeValue(lexical_cast<string>(*(float*)container[0]));
	}
	return 1;
}

int TextCtrl_Long::SaveEdits()
{
	if(!AGETextCtrl::editable || AGETextCtrl::hexMode || container.empty()) return 1;
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
				for(auto &pointer: container)
				{
					switch(batchMode)
					{
						case 1: *(int32_t*)pointer += casted; break;
						case 2: *(int32_t*)pointer -= casted; break;
						case 3: *(int32_t*)pointer *= casted; break;
						case 4: *(int32_t*)pointer /= casted; break;
						case 5: *(int32_t*)pointer %= casted; break;
					}
				}
				ChangeValue(lexical_cast<string>(*(int32_t*)container[0]));
				if(LinkedBox) LinkedBox->Update(casted);
				return 0;
			}
			if(*(int32_t*)container[0] != casted)
			{
				for(auto &pointer: container)
				{
					*(int32_t*)pointer = casted;
				}
				if(LinkedBox) LinkedBox->Update(casted);
				return 0;
			}
		}
		catch(bad_lexical_cast e)
		{
			wxMessageBox("Please enter a number from -2 147 483 648 to 2 147 483 647", IETITLE);
			SetFocus();
			return 2;
		}
	}
	else
	{
		ChangeValue(lexical_cast<string>(*(int32_t*)container[0]));
	}
	return 1;
}

int TextCtrl_Short::SaveEdits()
{
	if(!AGETextCtrl::editable || AGETextCtrl::hexMode || container.empty()) return 1;
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
				for(auto &pointer: container)
				{
					switch(batchMode)
					{
						case 1: *(int16_t*)pointer += casted; break;
						case 2: *(int16_t*)pointer -= casted; break;
						case 3: *(int16_t*)pointer *= casted; break;
						case 4: *(int16_t*)pointer /= casted; break;
						case 5: *(int16_t*)pointer %= casted; break;
					}
				}
				ChangeValue(lexical_cast<string>(*(int16_t*)container[0]));
				if(LinkedBox) LinkedBox->Update(casted);
				return 0;
			}
			if(*(int16_t*)container[0] != casted)
			{
				for(auto &pointer: container)
				{
					*(int16_t*)pointer = casted;
				}
				if(LinkedBox) LinkedBox->Update(casted);
				return 0;
			}
		}
		catch(bad_lexical_cast e)
		{
			wxMessageBox("Please enter a number from -32 768 to 32 767", IETITLE);
			SetFocus();
			return 2;
		}
	}
	else
	{
		ChangeValue(lexical_cast<string>(*(int16_t*)container[0]));
	}
	return 1;
}

int TextCtrl_UShort::SaveEdits()
{
	if(!AGETextCtrl::editable || AGETextCtrl::hexMode || container.empty()) return 1;
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
				for(auto &pointer: container)
				{
					switch(batchMode)
					{
						case 1: *(uint16_t*)pointer += casted; break;
						case 2: *(uint16_t*)pointer -= casted; break;
						case 3: *(uint16_t*)pointer *= casted; break;
						case 4: *(uint16_t*)pointer /= casted; break;
						case 5: *(uint16_t*)pointer %= casted; break;
					}
				}
				ChangeValue(lexical_cast<string>(*(uint16_t*)container[0]));
				if(LinkedBox) LinkedBox->Update(casted);
				return 0;
			}
			if(*(uint16_t*)container[0] != casted)
			{
				for(auto &pointer: container)
				{
					*(uint16_t*)pointer = casted;
				}
				if(LinkedBox) LinkedBox->Update(casted);
				return 0;
			}
		}
		catch(bad_lexical_cast e)
		{
			wxMessageBox("Please enter a number from 0 to 65 535", IETITLE);
			SetFocus();
			return 2;
		}
	}
	else
	{
		ChangeValue(lexical_cast<string>(*(uint16_t*)container[0]));
	}
	return 1;
}

int TextCtrl_String::SaveEdits()	// This may crash the program.
{
	if(!AGETextCtrl::editable || container.empty()) return 1;
	wxString value = GetValue().c_str();
	if(value.size() > 0)
	{
		if(*(string*)container[0] != value) // Has been changed
		{
			if(value.size() <= MaxSize)
			{
				for(auto &pointer: container)
				{
					*(string*)pointer = value; // Update data field
				}
			}
			else
			{
				value = value.substr(0, MaxSize);
				for(auto &pointer: container)
				{
					*(string*)pointer = value;
				}
				ChangeValue(*(string*)container[0]);
			}
			return 0;
		}
	}
	else
	{
		ChangeValue(*(string*)container[0]);
	}
	return 1;
}

void TextCtrl_Byte::Update()
{
	if(AGETextCtrl::hexMode)
	{
		stringbuf buffer;
		ostream os (&buffer);
		os << hex << showbase << uppercase << (short)*(uint8_t*)container[0];
		ChangeValue(buffer.str());
	}
	else
	{
		ChangeValue(lexical_cast<string>((short)*(int8_t*)container[0]));
	}
	if(LinkedBox) LinkedBox->Update(*(int8_t*)container[0]);
}

void TextCtrl_UByte::Update()
{
	if(AGETextCtrl::hexMode)
	{
		stringbuf buffer;
		ostream os (&buffer);
		os << hex << showbase << uppercase << (short)*(uint8_t*)container[0];
		ChangeValue(buffer.str());
	}
	else
	{
		ChangeValue(lexical_cast<string>((short)*(uint8_t*)container[0]));
	}
	if(LinkedBox) LinkedBox->Update(*(uint8_t*)container[0]);
}

void TextCtrl_Float::Update()
{
	if(AGETextCtrl::hexMode)
	{
		stringbuf buffer;
		ostream os (&buffer);
		os << hex << showbase << uppercase << *(uint32_t*)container[0];
		ChangeValue(buffer.str());
	}
	else
	{
		if(AGETextCtrl::accurateFloats)
		{
			ChangeValue(lexical_cast<string>(*(float*)container[0]));
		}
		else
		{
			stringbuf buffer;
			ostream os (&buffer);
			os << *(float*)container[0];
			ChangeValue(buffer.str());
		}
	}
	if(LinkedBox) LinkedBox->Update(*(float*)container[0]);
}

void TextCtrl_Long::Update()
{
	if(AGETextCtrl::hexMode)
	{
		stringbuf buffer;
		ostream os (&buffer);
		os << hex << showbase << uppercase << *(uint32_t*)container[0];
		ChangeValue(buffer.str());
	}
	else
	{
		ChangeValue(lexical_cast<string>(*(int32_t*)container[0]));
	}
	if(LinkedBox) LinkedBox->Update(*(int32_t*)container[0]);
}

void TextCtrl_Short::Update()
{
	if(AGETextCtrl::hexMode)
	{
		stringbuf buffer;
		ostream os (&buffer);
		os << hex << showbase << uppercase << *(uint16_t*)container[0];
		ChangeValue(buffer.str());
	}
	else
	{
		ChangeValue(lexical_cast<string>(*(int16_t*)container[0]));
	}
	if(LinkedBox) LinkedBox->Update(*(int16_t*)container[0]);
}

void TextCtrl_UShort::Update()
{
	if(AGETextCtrl::hexMode)
	{
		stringbuf buffer;
		ostream os (&buffer);
		os << hex << showbase << uppercase << *(uint16_t*)container[0];
		ChangeValue(buffer.str());
	}
	else
	{
		ChangeValue(lexical_cast<string>(*(uint16_t*)container[0]));
	}
	if(LinkedBox) LinkedBox->Update(*(uint16_t*)container[0]);
}

void TextCtrl_String::Update()
{
	ChangeValue(*(string*)container[0]);
}
