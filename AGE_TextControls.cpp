#include "AGE_TextControls.h"

const wxString AGETextCtrl::BATCHWARNING = "Use b+[x], b-[x], b*[x] or b/[x]\nwhere [x] is a number.";
const wxString AGETextCtrl::BWTITLE = "Incorrect batch script!";
const wxString AGETextCtrl::IETITLE = "Invalid entry!";

int TextCtrl_Byte::SaveEdits(bool forced)
{
	if(AGETextCtrl::hexMode[window] || container.empty()) return 1;
	if(curFileLoaded != AGETextCtrl::fileLoaded[window]) return 1;
	string value = string(GetValue().mb_str());
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
					AGETextCtrl::unSaved[window] += container.size();
					return 0;
				}
				if(*(int8_t*)container[0] != casted || forced)
				{
					for(auto &pointer: container)
					{
						*(int8_t*)pointer = casted;
					}
					if(LinkedBox) LinkedBox->Update(casted);
					AGETextCtrl::unSaved[window] += container.size();
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

int TextCtrl_UByte::SaveEdits(bool forced)
{
	if(AGETextCtrl::hexMode[window] || container.empty()) return 1;
	if(curFileLoaded != AGETextCtrl::fileLoaded[window]) return 1;
	string value = string(GetValue().mb_str());
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
					AGETextCtrl::unSaved[window] += container.size();
					return 0;
				}
				if(*(uint8_t*)container[0] != casted || forced)
				{
					for(auto &pointer: container)
					{
						*(uint8_t*)pointer = casted;
					}
					if(LinkedBox) LinkedBox->Update(casted);
					AGETextCtrl::unSaved[window] += container.size();
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

int TextCtrl_Float::SaveEdits(bool forced)
{
	if(AGETextCtrl::hexMode[window] || container.empty()) return 1;
	if(curFileLoaded != AGETextCtrl::fileLoaded[window]) return 1;
	string value = string(GetValue().mb_str());
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
			float casted;
			if(value == "max") casted = 3.40282347e+38;
			else if(value == "min") casted = 1.17549435e-38;
			else casted = lexical_cast<float>(value);
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
				AGETextCtrl::unSaved[window] += container.size();
				return 0;
			}
			if(*(float*)container[0] != casted || forced)
			{
				for(auto &pointer: container)
				{
					*(float*)pointer = casted;
				}
				if(LinkedBox) LinkedBox->Update(casted);
				AGETextCtrl::unSaved[window] += container.size();
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

int TextCtrl_Long::SaveEdits(bool forced)
{
	if(AGETextCtrl::hexMode[window] || container.empty()) return 1;
	if(curFileLoaded != AGETextCtrl::fileLoaded[window]) return 1;
	string value = string(GetValue().mb_str());
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
				AGETextCtrl::unSaved[window] += container.size();
				return 0;
			}
			if(*(int32_t*)container[0] != casted || forced)
			{
				for(auto &pointer: container)
				{
					*(int32_t*)pointer = casted;
				}
				if(LinkedBox) LinkedBox->Update(casted);
				AGETextCtrl::unSaved[window] += container.size();
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

int TextCtrl_Short::SaveEdits(bool forced)
{
	if(AGETextCtrl::hexMode[window] || container.empty()) return 1;
	if(curFileLoaded != AGETextCtrl::fileLoaded[window]) return 1;
	string value = string(GetValue().mb_str());
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
				AGETextCtrl::unSaved[window] += container.size();
				return 0;
			}
			if(*(int16_t*)container[0] != casted || forced)
			{
				for(auto &pointer: container)
				{
					*(int16_t*)pointer = casted;
				}
				if(LinkedBox) LinkedBox->Update(casted);
				AGETextCtrl::unSaved[window] += container.size();
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

int TextCtrl_UShort::SaveEdits(bool forced)
{
	if(AGETextCtrl::hexMode[window] || container.empty()) return 1;
	if(curFileLoaded != AGETextCtrl::fileLoaded[window]) return 1;
	string value = string(GetValue().mb_str());
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
				AGETextCtrl::unSaved[window] += container.size();
				return 0;
			}
			if(*(uint16_t*)container[0] != casted || forced)
			{
				for(auto &pointer: container)
				{
					*(uint16_t*)pointer = casted;
				}
				if(LinkedBox) LinkedBox->Update(casted);
				AGETextCtrl::unSaved[window] += container.size();
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

int TextCtrl_String::SaveEdits(bool forced)	// This may crash the program.
{
	if(container.empty()) return 1;
	if(curFileLoaded != AGETextCtrl::fileLoaded[window]) return 1;
	string value = string(GetValue().mb_str());
	if(value.size() > 0)
	{
		if(*(string*)container[0] != value || forced) // Has been changed
		{
			short batchMode = 0;
			if(value[0] == 'b' && !BatchCheck(value, batchMode))
			{
				goto fix;
				wxMessageBox(BATCHWARNING, BWTITLE);
				return 1;
			}
			if(batchMode > 0)
			{
				for(auto &pointer: container)
				{
					string vasili = *(string*)pointer;
					switch(batchMode)
					{
						case 1: vasili += value; vasili = vasili.substr(0, MaxSize); break;
						case 2: vasili = vasili.substr(0, vasili.size() - lexical_cast<int>(value)); break;
					}
					*(string*)pointer = vasili;
				}
				ChangeValue(*(string*)container[0]);
				AGETextCtrl::unSaved[window] += container.size();
				return 0;
			}
			fix:
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
			AGETextCtrl::unSaved[window] += container.size();
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
	curFileLoaded = AGETextCtrl::fileLoaded[window];
	if(AGETextCtrl::hexMode[window])
	{
		stringbuf buffer;
		ostream os (&buffer);
		os << hex << setw(2) << setfill('0') << uppercase << (short)*(uint8_t*)container[0];
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
	curFileLoaded = AGETextCtrl::fileLoaded[window];
	if(AGETextCtrl::hexMode[window])
	{
		stringbuf buffer;
		ostream os (&buffer);
		os << hex << setw(2) << setfill('0') << uppercase << (short)*(uint8_t*)container[0];
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
	curFileLoaded = AGETextCtrl::fileLoaded[window];
	if(AGETextCtrl::hexMode[window])
	{
		stringbuf buffer;
		ostream os (&buffer);
		os << hex << setw(8) << setfill('0') << uppercase << *(uint32_t*)container[0];
		ChangeValue(buffer.str());
	}
	else
	{
		if(AGETextCtrl::accurateFloats[window])
		{
			ChangeValue(lexical_cast<string>(*(float*)container[0]));
		}
		else
		{
			stringbuf buffer;
			ostream os (&buffer);
			if(*(int32_t*)container[0] == 0x7F7FFFFF) os << "max";
			else if(*(int32_t*)container[0] == 0x00800000) os << "min";
			else os << *(float*)container[0];
			ChangeValue(buffer.str());
		}
	}
	if(LinkedBox) LinkedBox->Update(*(float*)container[0]);
}

void TextCtrl_Long::Update()
{
	curFileLoaded = AGETextCtrl::fileLoaded[window];
	if(AGETextCtrl::hexMode[window])
	{
		stringbuf buffer;
		ostream os (&buffer);
		os << hex << setw(8) << setfill('0') << uppercase << *(uint32_t*)container[0];
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
	curFileLoaded = AGETextCtrl::fileLoaded[window];
	if(AGETextCtrl::hexMode[window])
	{
		stringbuf buffer;
		ostream os (&buffer);
		os << hex << setw(4) << setfill('0') << uppercase << *(uint16_t*)container[0];
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
	curFileLoaded = AGETextCtrl::fileLoaded[window];
	if(AGETextCtrl::hexMode[window])
	{
		stringbuf buffer;
		ostream os (&buffer);
		os << hex << setw(4) << setfill('0') << uppercase << *(uint16_t*)container[0];
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
	curFileLoaded = AGETextCtrl::fileLoaded[window];
	ChangeValue(*(string*)container[0]);
}
