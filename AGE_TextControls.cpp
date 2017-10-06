#include "AGE_TextControls.h"

const wxString AGEBaseCtrl::BATCHWARNING = "Use b+[x], b-[x], b*[x] or b/[x]\nwhere [x] is a number.";
const wxString AGEBaseCtrl::BWTITLE = "Incorrect batch script!";
const wxString AGEBaseCtrl::IETITLE = "Invalid entry!";
const unsigned short lengthiest = 0x7FFF;
unsigned AGETextCtrl::SMALL=50, AGETextCtrl::MEDIUM=70, AGETextCtrl::NORMAL=100, AGETextCtrl::LARGE=150, AGETextCtrl::GIANT=200;

void ProperList::OnDrawItem(wxDC &dc, const wxRect &rect, size_t n) const
{
    dc.SetTextForeground(wxSystemSettings::GetColour(IsSelected(n) ?
        wxSYS_COLOUR_HIGHLIGHTTEXT : wxSYS_COLOUR_WINDOWTEXT));
    dc.DrawText(names[n], rect.x + 2, rect.y);
}

void ProperList::OnDrawBackground(wxDC &dc, const wxRect &rect, size_t n) const
{
    if(IsSelected(n))
    wxRendererNative::Get().DrawItemSelectionRect(const_cast<ProperList*>(this),
    dc, rect, wxCONTROL_SELECTED | wxCONTROL_FOCUSED);
}

void ProperList::EnsureVisible(size_t n)
{
    if(!IsRowVisible(n))
    {
        size_t ve = GetVisibleRowsEnd();
        if(n > ve)
        {
            ScrollRows(n - ve);
        }
        else
        {
            ScrollToRow(n);
        }
    }
}

AGETextCtrl* AGETextCtrl::init(const ContainerType type, vector<AGETextCtrl*> *group,
    wxFrame *frame, DelayedPopUp *editor, wxWindow *parent, unsigned length)
{
    AGETextCtrl* product;
    switch(type)
    {
    case CByte: product = new TextCtrl_Byte(frame, editor, parent, length); break;
    case CUByte: product = new TextCtrl_UByte(frame, editor, parent, length); break;
    case CFloat: product = new TextCtrl_Float(frame, editor, parent, length); break;
    case CLong: product = new TextCtrl_Long(frame, editor, parent, length); break;
    case CShort: product = new TextCtrl_Short(frame, editor, parent, length); break;
    case CUShort: product = new TextCtrl_UShort(frame, editor, parent, length); break;
    case CString: product = new TextCtrl_String(frame, editor, parent, length); break;
    }
    if(NULL != group) group->push_back(product);
    return product;
}

int TextCtrl_Byte::SaveEdits(bool forced)
{
    if(editor->hexMode || container.empty()) return 1;
    if(editedFileId != editor->loadedFileId) return 1;
    string value = string(GetValue().mb_str());
    if(value.size() > 0)
    {
        short batchMode = 0;
        if(value[0] == 'b' && !BatchCheck(value, batchMode))
        {
            editor->post(BATCHWARNING, BWTITLE, NULL);
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
                        ++edits;
                        switch(batchMode)
                        {
                            case 1: *(int8_t*)pointer += casted; break;
                            case 2: *(int8_t*)pointer -= casted; break;
                            case 3: *(int8_t*)pointer *= casted; break;
                            case 4: *(int8_t*)pointer /= casted; break;
                            case 5: *(int8_t*)pointer %= casted; break;
                        }
                    }
                    ChangeValue(lexical_cast<string>((short)*(int8_t*)container.back()));
                    HandleResults(*(int8_t*)container.back());
                    return 0;
                }
                if(*(int8_t*)container.back() != casted || forced)
                {
                    for(auto &pointer: container)
                    {
                        ++edits;
                        *(int8_t*)pointer = casted;
                    }
                    HandleResults(casted);
                    return 0;
                }
            }
            else
            {
                editor->post("Please enter a number from -128 to 127", IETITLE, this);
                return 2;
            }
        }
        catch(bad_lexical_cast)
        {
            editor->post("Please enter a number from -128 to 127", IETITLE, this);
            return 2;
        }
    }
    else
    {
        ChangeValue(lexical_cast<string>((short)*(int8_t*)container.back()));
    }
    return 1;
}

int TextCtrl_UByte::SaveEdits(bool forced)
{
    if(editor->hexMode || container.empty()) return 1;
    if(editedFileId != editor->loadedFileId) return 1;
    string value = string(GetValue().mb_str());
    if(value.size() > 0)
    {
        short batchMode = 0;
        if(value[0] == 'b' && !BatchCheck(value, batchMode))
        {
            editor->post(BATCHWARNING, BWTITLE, NULL);
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
                        ++edits;
                        switch(batchMode)
                        {
                            case 1: *(uint8_t*)pointer += casted; break;
                            case 2: *(uint8_t*)pointer -= casted; break;
                            case 3: *(uint8_t*)pointer *= casted; break;
                            case 4: *(uint8_t*)pointer /= casted; break;
                            case 5: *(uint8_t*)pointer %= casted; break;
                        }
                    }
                    ChangeValue(lexical_cast<string>((short)*(uint8_t*)container.back()));
                    HandleResults(*(uint8_t*)container.back());
                    return 0;
                }
                if(*(uint8_t*)container.back() != casted || forced)
                {
                    for(auto &pointer: container)
                    {
                        ++edits;
                        *(uint8_t*)pointer = casted;
                    }
                    HandleResults(casted);
                    return 0;
                }
            }
            else
            {
                editor->post("Please enter a number from 0 to 255", IETITLE, this);
                return 2;
            }
        }
        catch(bad_lexical_cast)
        {
            editor->post("Please enter a number from 0 to 255", IETITLE, this);
            return 2;
        }
    }
    else
    {
        ChangeValue(lexical_cast<string>((short)*(uint8_t*)container.back()));
    }
    return 1;
}

int TextCtrl_Float::SaveEdits(bool forced)
{
    if(editor->hexMode || container.empty()) return 1;
    if(editedFileId != editor->loadedFileId) return 1;
    string value = string(GetValue().mb_str());
    if(value.size() > 0)
    {
        short batchMode = 0;
        if(value[0] == 'b' && !BatchCheck(value, batchMode))
        {
            editor->post(BATCHWARNING, BWTITLE, NULL);
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
                    ++edits;
                    switch(batchMode)
                    {
                        case 1: *(float*)pointer += casted; break;
                        case 2: *(float*)pointer -= casted; break;
                        case 3: *(float*)pointer *= casted; break;
                        case 4: *(float*)pointer /= casted; break;
                    }
                }
                ChangeValue(lexical_cast<string>(*(float*)container.back()));
                HandleResults(*(float*)container.back());
                return 0;
            }
            if(*(float*)container.back() != casted || forced)
            {
                for(auto &pointer: container)
                {
                    ++edits;
                    *(float*)pointer = casted;
                }
                HandleResults(casted);
                return 0;
            }
        }
        catch(bad_lexical_cast)
        {
            editor->post("Please enter a valid floating point number", IETITLE, this);
            return 2;
        }
    }
    else
    {
        ChangeValue(lexical_cast<string>(*(float*)container.back()));
    }
    return 1;
}

int TextCtrl_Long::SaveEdits(bool forced)
{
    if(editor->hexMode || container.empty()) return 1;
    if(editedFileId != editor->loadedFileId) return 1;
    string value = string(GetValue().mb_str());
    if(value.size() > 0)
    {
        short batchMode = 0;
        if(value[0] == 'b' && !BatchCheck(value, batchMode))
        {
            editor->post(BATCHWARNING, BWTITLE, NULL);
            return 1;
        }
        try
        {
            int32_t casted = lexical_cast<int32_t>(value);
            if(batchMode > 0)
            {
                for(auto &pointer: container)
                {
                    ++edits;
                    switch(batchMode)
                    {
                        case 1: *(int32_t*)pointer += casted; break;
                        case 2: *(int32_t*)pointer -= casted; break;
                        case 3: *(int32_t*)pointer *= casted; break;
                        case 4: *(int32_t*)pointer /= casted; break;
                        case 5: *(int32_t*)pointer %= casted; break;
                    }
                }
                ChangeValue(lexical_cast<string>(*(int32_t*)container.back()));
                HandleResults(*(int32_t*)container.back());
                return 0;
            }
            if(*(int32_t*)container.back() != casted || forced)
            {
                for(auto &pointer: container)
                {
                    ++edits;
                    *(int32_t*)pointer = casted;
                }
                HandleResults(casted);
                return 0;
            }
        }
        catch(bad_lexical_cast)
        {
            editor->post("Please enter a number from -2 147 483 648 to 2 147 483 647", IETITLE, this);
            return 2;
        }
    }
    else
    {
        ChangeValue(lexical_cast<string>(*(int32_t*)container.back()));
    }
    return 1;
}

int TextCtrl_Short::SaveEdits(bool forced)
{
    if(editor->hexMode || container.empty()) return 1;
    if(editedFileId != editor->loadedFileId) return 1;
    string value = string(GetValue().mb_str());
    if(value.size() > 0)
    {
        short batchMode = 0;
        if(value[0] == 'b' && !BatchCheck(value, batchMode))
        {
            editor->post(BATCHWARNING, BWTITLE, NULL);
            return 1;
        }
        try
        {
            int16_t casted = lexical_cast<int16_t>(value);
            if(batchMode > 0)
            {
                for(auto &pointer: container)
                {
                    ++edits;
                    switch(batchMode)
                    {
                        case 1: *(int16_t*)pointer += casted; break;
                        case 2: *(int16_t*)pointer -= casted; break;
                        case 3: *(int16_t*)pointer *= casted; break;
                        case 4: *(int16_t*)pointer /= casted; break;
                        case 5: *(int16_t*)pointer %= casted; break;
                    }
                }
                ChangeValue(lexical_cast<string>(*(int16_t*)container.back()));
                HandleResults(*(int16_t*)container.back());
                return 0;
            }
            if(*(int16_t*)container.back() != casted || forced)
            {
                for(auto &pointer: container)
                {
                    ++edits;
                    *(int16_t*)pointer = casted;
                }
                HandleResults(casted);
                return 0;
            }
        }
        catch(bad_lexical_cast)
        {
            editor->post("Please enter a number from -32 768 to 32 767", IETITLE, this);
            return 2;
        }
    }
    else
    {
        ChangeValue(lexical_cast<string>(*(int16_t*)container.back()));
    }
    return 1;
}

int TextCtrl_UShort::SaveEdits(bool forced)
{
    if(editor->hexMode || container.empty()) return 1;
    if(editedFileId != editor->loadedFileId) return 1;
    string value = string(GetValue().mb_str());
    if(value.size() > 0)
    {
        short batchMode = 0;
        if(value[0] == 'b' && !BatchCheck(value, batchMode))
        {
            editor->post(BATCHWARNING, BWTITLE, NULL);
            return 1;
        }
        try
        {
            uint16_t casted = lexical_cast<uint16_t>(value);
            if(batchMode > 0)
            {
                for(auto &pointer: container)
                {
                    ++edits;
                    switch(batchMode)
                    {
                        case 1: *(uint16_t*)pointer += casted; break;
                        case 2: *(uint16_t*)pointer -= casted; break;
                        case 3: *(uint16_t*)pointer *= casted; break;
                        case 4: *(uint16_t*)pointer /= casted; break;
                        case 5: *(uint16_t*)pointer %= casted; break;
                    }
                }
                ChangeValue(lexical_cast<string>(*(uint16_t*)container.back()));
                HandleResults(*(uint16_t*)container.back());
                return 0;
            }
            if(*(uint16_t*)container.back() != casted || forced)
            {
                for(auto &pointer: container)
                {
                    ++edits;
                    *(uint16_t*)pointer = casted;
                }
                HandleResults(casted);
                return 0;
            }
        }
        catch(bad_lexical_cast)
        {
            editor->post("Please enter a number from 0 to 65 535", IETITLE, this);
            return 2;
        }
    }
    else
    {
        ChangeValue(lexical_cast<string>(*(uint16_t*)container.back()));
    }
    return 1;
}

int TextCtrl_String::SaveEdits(bool forced) // This may crash the program.
{
    if(container.empty()) return 1;
    if(editedFileId != editor->loadedFileId) return 1;
    string value = string(GetValue().mb_str());
    if(*(string*)container.back() != value || forced) // Has been changed
    {
        // Broken, strings like "C-Bonus" are interpret as batch mode 2.
        /*if(value.size() > 2)
        {
            short batchMode = 0;
            BatchCheck(value, batchMode);
            if(batchMode > 0)
            {
                for(auto &pointer: container)
                {
                    ++edits;
                    string vasili = *(string*)pointer;
                    switch(batchMode)
                    {
                        case 1: vasili += value; vasili = vasili.substr(0, maxSize); break;
                        case 2: vasili = vasili.substr(0, vasili.size() - lexical_cast<int>(value)); break;
                    }
                    *(string*)pointer = vasili;
                }
                ChangeValue(*(string*)container.back());
                HandleResults(0);
                return 0;
            }
        }*/
        if(value.size() <= maxSize)
        {
            for(auto &pointer: container)
            {
                ++edits;
                *(string*)pointer = value; // replenish data field
            }
        }
        else
        {
            value = value.substr(0, maxSize);
            for(auto &pointer: container)
            {
                ++edits;
                *(string*)pointer = value;
            }
            ChangeValue(*(string*)container.back());
        }
        HandleResults(0);
        return 0;
    }
    return 1;
}

void TextCtrl_Byte::replenish()
{
    if(editor->hexMode)
    {
        stringbuf buffer;
        ostream os (&buffer);
        os << hex << setfill('0') << setw(2) << uppercase << (short)*(uint8_t*)container.back();
        ChangeValue(buffer.str());
    }
    else
    {
        ChangeValue(lexical_cast<string>((short)*(int8_t*)container.back()));
    }
    if(!LinkedBoxes.empty())
    for(auto it = LinkedBoxes.begin(); it != LinkedBoxes.end(); ++it)
    {
        (*it)->SetChoice(*(int8_t*)container.back());
        (*it)->EnableCtrl(true);
    }
}

void TextCtrl_UByte::replenish()
{
    if(editor->hexMode)
    {
        stringbuf buffer;
        ostream os (&buffer);
        os << hex << setfill('0') << setw(2) << uppercase << (short)*(uint8_t*)container.back();
        ChangeValue(buffer.str());
    }
    else
    {
        ChangeValue(lexical_cast<string>((short)*(uint8_t*)container.back()));
    }
    if(!LinkedBoxes.empty())
    for(auto it = LinkedBoxes.begin(); it != LinkedBoxes.end(); ++it)
    {
        (*it)->SetChoice(*(uint8_t*)container.back());
        (*it)->EnableCtrl(true);
    }
}

void TextCtrl_Float::replenish()
{
    if(editor->hexMode)
    {
        stringbuf buffer;
        ostream os (&buffer);
        os << hex << setfill('0') << setw(8) << uppercase << *(uint32_t*)container.back();
        ChangeValue(buffer.str());
    }
    else
    {
        if(editor->accurateFloats)
        {
            ChangeValue(lexical_cast<string>(*(float*)container.back()));
        }
        else
        {
            stringbuf buffer;
            ostream os (&buffer);
            if(*(int32_t*)container.back() == 0x7F7FFFFF) os << "max";
            else if(*(int32_t*)container.back() == 0x00800000) os << "min";
            else os << *(float*)container.back();
            ChangeValue(buffer.str());
        }
    }
    if(!LinkedBoxes.empty())
    for(auto it = LinkedBoxes.begin(); it != LinkedBoxes.end(); ++it)
    {
        (*it)->SetChoice(*(float*)container.back());
        (*it)->EnableCtrl(true);
    }
}

void TextCtrl_Long::replenish()
{
    if(editor->hexMode)
    {
        stringbuf buffer;
        ostream os (&buffer);
        os << hex << setfill('0') << setw(8) << uppercase << *(uint32_t*)container.back();
        ChangeValue(buffer.str());
    }
    else
    {
        ChangeValue(lexical_cast<string>(*(int32_t*)container.back()));
    }
    if(!LinkedBoxes.empty())
    for(auto it = LinkedBoxes.begin(); it != LinkedBoxes.end(); ++it)
    {
        (*it)->SetChoice(*(int32_t*)container.back());
        (*it)->EnableCtrl(true);
    }
}

void TextCtrl_Short::replenish()
{
    if(editor->hexMode)
    {
        stringbuf buffer;
        ostream os (&buffer);
        os << hex << setfill('0') << setw(4) << uppercase << *(uint16_t*)container.back();
        ChangeValue(buffer.str());
    }
    else
    {
        ChangeValue(lexical_cast<string>(*(int16_t*)container.back()));
    }
    if(!LinkedBoxes.empty())
    for(auto it = LinkedBoxes.begin(); it != LinkedBoxes.end(); ++it)
    {
        (*it)->SetChoice(*(int16_t*)container.back());
        (*it)->EnableCtrl(true);
    }
}

void TextCtrl_UShort::replenish()
{
    if(editor->hexMode)
    {
        stringbuf buffer;
        ostream os (&buffer);
        os << hex << setfill('0') << setw(4) << uppercase << *(uint16_t*)container.back();
        ChangeValue(buffer.str());
    }
    else
    {
        ChangeValue(lexical_cast<string>(*(uint16_t*)container.back()));
    }
    if(!LinkedBoxes.empty())
    for(auto it = LinkedBoxes.begin(); it != LinkedBoxes.end(); ++it)
    {
        (*it)->SetChoice(*(uint16_t*)container.back());
        (*it)->EnableCtrl(true);
    }
}

void TextCtrl_String::replenish()
{
    ChangeValue(*(string*)container.back());
}
