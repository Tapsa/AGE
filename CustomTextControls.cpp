#include "Common.h"
#include "BaseMainFrame.h"
#include "CustomTextControls.h"
#include "LinkedControl.h"

const wxString BATCHWARNING = "Use b+[x], b-[x], b*[x] or b/[x]\nwhere [x] is a number.";
const wxString BWTITLE = "Incorrect batch script!";
const wxString IETITLE = "Invalid entry!";
unsigned AGETextCtrl::SMALL = 50;
unsigned AGETextCtrl::MEDIUM = 70;
unsigned AGETextCtrl::NORMAL = 100;
unsigned AGETextCtrl::LARGE = 150;
unsigned AGETextCtrl::GIANT = 200;

AGETextCtrl::AGETextCtrl(wxWindow *parent, int width) :
    wxTextCtrl(parent, wxID_ANY, "", wxDefaultPosition, wxSize(width, -1), wxTE_PROCESS_ENTER),
    numEdits(0), LinkedBox(nullptr)
{
}

void AGETextCtrl::SetAsText(unsigned value)
{
    ChangeValue(lexical_cast<std::string>(value));
}

void AGETextCtrl::update()
{
    if (container.empty())
    {
        Clear();
        Enable(false);
        if (LinkedBox != nullptr)
        {
            LinkedBox->SetChoice(-1);
            LinkedBox->EnableControl(false);
        }
        return;
    }
    editedFileId = frame->popUp.loadedFileId;
    replenish();
    Enable(true);
}

void AGETextCtrl::refill()
{
    if (container.empty())
    {
        Clear();
        return;
    }
    editedFileId = frame->popUp.loadedFileId;
    replenish();
}

bool AGETextCtrl::BatchCheck(std::string &value, short &batchMode) const
{
    if (value.size() < 3) return false;
    switch ((char)value[1])
    {
        case '+': batchMode = 1; value = value.substr(2); return true;
        case '-': batchMode = 2; value = value.substr(2); return true;
        case '*': batchMode = 3; value = value.substr(2); return true;
        case '/': batchMode = 4; value = value.substr(2); return true;
        case '%': batchMode = 5; value = value.substr(2); return true;
        default: return false;
    }
}

void AGETextCtrl::HandleResults(int casted)
{
    if (LinkedBox != nullptr)
    {
        LinkedBox->SetChoice(casted);
    }
    frame->SetStatusText(wxString::Format("Edits: %zu + %zu", frame->popUp.unSaved, numEdits), 3);
    frame->popUp.unSaved += numEdits;
    numEdits = 0;
}

TextIndexControl::TextIndexControl(wxWindow *parent, wxSize dimensions) :
    wxTextCtrl(parent, wxID_ANY, "", wxDefaultPosition, dimensions, wxTE_MULTILINE),
    index(0)
{
    Bind(wxEVT_MOUSEWHEEL, [this](wxMouseEvent &event)
    {
        GetParent()->GetEventHandler()->ProcessEvent(event);
    });
}

NumberControl::NumberControl(ContainerType type, wxWindow *parent, BaseMainFrame *frame,
    std::vector<AGETextCtrl *> *group, bool connect, int width) :
    AGETextCtrl(parent, width)
{
    this->frame = frame;
    SetCastType(type);
    if (connect)
    {
        Bind(wxEVT_KILL_FOCUS, &NumberControl::OnKillFocus, this);
        Bind(wxEVT_TEXT_ENTER, &NumberControl::OnEnter, this);
    }
    if (nullptr != group)
    {
        group->push_back(this);
    }
}

void NumberControl::SetCastType(const ContainerType type)
{
    switch (type)
    {
        case CUByte:
            ShowNumber = &NumberControl::ShowNumberAsUByte;
            SaveChanges = &NumberControl::SaveChangesAsUByte;
            SetBackgroundColour(wxColour(255, 235, 215));
            break;
        case CFloat:
            ShowNumber = &NumberControl::ShowNumberAsFloat;
            SaveChanges = &NumberControl::SaveChangesAsFloat;
            SetBackgroundColour(wxColour(255, 225, 255));
            break;
        case CLong:
            ShowNumber = &NumberControl::ShowNumberAsLong;
            SaveChanges = &NumberControl::SaveChangesAsLong;
            SetBackgroundColour(wxColour(215, 255, 255));
            break;
        case CULong:
            ShowNumber = &NumberControl::ShowNumberAsULong;
            SaveChanges = &NumberControl::SaveChangesAsULong;
            SetBackgroundColour(wxColour(215, 255, 255));
            break;
        case CShort:
            ShowNumber = &NumberControl::ShowNumberAsShort;
            SaveChanges = &NumberControl::SaveChangesAsShort;
            SetBackgroundColour(wxColour(210, 230, 255));
            break;
    }
}

int NumberControl::SaveChangesAsUByte(bool forced)
{
    if (frame->popUp.hexMode || container.empty()) return 1;
    if (editedFileId != frame->popUp.loadedFileId) return 1;
    std::string value = std::string(GetValue().mb_str());
    if (value.size() > 0)
    {
        short batchMode = 0;
        if (value[0] == 'b' && !BatchCheck(value, batchMode))
        {
            frame->popUp.post(BATCHWARNING, BWTITLE);
            return 1;
        }
        try
        {
            uint8_t casted = (uint8_t)lexical_cast<short>(value);
            if (lexical_cast<short>(value) == casted)
            {
                if (batchMode > 0)
                {
                    for (void *pointer : container)
                    {
                        ++numEdits;
                        switch (batchMode)
                        {
                            case 1: *(uint8_t *)pointer += casted; break;
                            case 2: *(uint8_t *)pointer -= casted; break;
                            case 3: *(uint8_t *)pointer *= casted; break;
                            case 4: *(uint8_t *)pointer /= casted; break;
                            case 5: *(uint8_t *)pointer %= casted; break;
                        }
                    }
                    ChangeValue(lexical_cast<std::string>((short)*(uint8_t *)container.back()));
                    HandleResults(*(uint8_t *)container.back());
                    return 0;
                }
                if (*(uint8_t *)container.back() != casted || forced)
                {
                    for (void *pointer : container)
                    {
                        ++numEdits;
                        *(uint8_t *)pointer = casted;
                    }
                    HandleResults(casted);
                    return 0;
                }
            }
            else
            {
                boost::throw_exception(bad_lexical_cast(typeid(short), typeid(std::string)));
            }
        }
        catch (const bad_lexical_cast &)
        {
            frame->popUp.post("Please enter a number from 0 to 255", IETITLE, this);
            return 2;
        }
    }
    else
    {
        ChangeValue(lexical_cast<std::string>((short)*(uint8_t *)container.back()));
    }
    return 1;
}

int NumberControl::SaveChangesAsFloat(bool forced)
{
    if (frame->popUp.hexMode || container.empty()) return 1;
    if (editedFileId != frame->popUp.loadedFileId) return 1;
    std::string value = std::string(GetValue().mb_str());
    if (value.size() > 0)
    {
        short batchMode = 0;
        if (value[0] == 'b' && !BatchCheck(value, batchMode))
        {
            frame->popUp.post(BATCHWARNING, BWTITLE);
            return 1;
        }
        try
        {
            float casted;
            if (value == "max") casted = 3.402823466e+38f;
            else if (value == "min") casted = 1.175494351e-38f;
            else casted = lexical_cast<float>(value);
            if (batchMode > 0)
            {
                for (void *pointer : container)
                {
                    ++numEdits;
                    switch (batchMode)
                    {
                        case 1: *(float *)pointer += casted; break;
                        case 2: *(float *)pointer -= casted; break;
                        case 3: *(float *)pointer *= casted; break;
                        case 4: *(float *)pointer /= casted; break;
                    }
                }
                ChangeValue(lexical_cast<std::string>(*(float *)container.back()));
                HandleResults(*(float *)container.back());
                return 0;
            }
            if (*(float *)container.back() != casted || forced)
            {
                for (void *pointer : container)
                {
                    ++numEdits;
                    *(float *)pointer = casted;
                }
                HandleResults(casted);
                return 0;
            }
        }
        catch (const bad_lexical_cast &)
        {
            frame->popUp.post("Please enter a valid floating point number", IETITLE, this);
            return 2;
        }
    }
    else
    {
        ChangeValue(lexical_cast<std::string>(*(float *)container.back()));
    }
    return 1;
}

int NumberControl::SaveChangesAsLong(bool forced)
{
    if (frame->popUp.hexMode || container.empty()) return 1;
    if (editedFileId != frame->popUp.loadedFileId) return 1;
    std::string value = std::string(GetValue().mb_str());
    if (value.size() > 0)
    {
        short batchMode = 0;
        if (value[0] == 'b' && !BatchCheck(value, batchMode))
        {
            frame->popUp.post(BATCHWARNING, BWTITLE);
            return 1;
        }
        try
        {
            int32_t casted = lexical_cast<int32_t>(value);
            if (batchMode > 0)
            {
                for (void *pointer : container)
                {
                    ++numEdits;
                    switch (batchMode)
                    {
                        case 1: *(int32_t *)pointer += casted; break;
                        case 2: *(int32_t *)pointer -= casted; break;
                        case 3: *(int32_t *)pointer *= casted; break;
                        case 4: *(int32_t *)pointer /= casted; break;
                        case 5: *(int32_t *)pointer %= casted; break;
                    }
                }
                ChangeValue(lexical_cast<std::string>(*(int32_t *)container.back()));
                HandleResults(*(int32_t *)container.back());
                return 0;
            }
            if (*(int32_t *)container.back() != casted || forced)
            {
                for (void *pointer : container)
                {
                    ++numEdits;
                    *(int32_t *)pointer = casted;
                }
                HandleResults(casted);
                return 0;
            }
        }
        catch (const bad_lexical_cast &)
        {
            frame->popUp.post("Please enter a number from -2 147 483 648 to 2 147 483 647", IETITLE, this);
            return 2;
        }
    }
    else
    {
        ChangeValue(lexical_cast<std::string>(*(int32_t *)container.back()));
    }
    return 1;
}

int NumberControl::SaveChangesAsULong(bool forced)
{
    if (frame->popUp.hexMode || container.empty()) return 1;
    if (editedFileId != frame->popUp.loadedFileId) return 1;
    std::string value = std::string(GetValue().mb_str());
    if (value.size() > 0)
    {
        short batchMode = 0;
        if (value[0] == 'b' && !BatchCheck(value, batchMode))
        {
            frame->popUp.post(BATCHWARNING, BWTITLE);
            return 1;
        }
        try
        {
            uint32_t casted = lexical_cast<uint32_t>(value);
            if (batchMode > 0)
            {
                for (void *pointer : container)
                {
                    ++numEdits;
                    switch (batchMode)
                    {
                        case 1: *(uint32_t *)pointer += casted; break;
                        case 2: *(uint32_t *)pointer -= casted; break;
                        case 3: *(uint32_t *)pointer *= casted; break;
                        case 4: *(uint32_t *)pointer /= casted; break;
                        case 5: *(uint32_t *)pointer %= casted; break;
                    }
                }
                ChangeValue(lexical_cast<std::string>(*(uint32_t *)container.back()));
                HandleResults(*(uint32_t *)container.back());
                return 0;
            }
            if (*(uint32_t *)container.back() != casted || forced)
            {
                for (void *pointer : container)
                {
                    ++numEdits;
                    *(uint32_t *)pointer = casted;
                }
                HandleResults(casted);
                return 0;
            }
        }
        catch (const bad_lexical_cast &)
        {
            frame->popUp.post("Please enter a number from 0 to 4 294 967 295", IETITLE, this);
            return 2;
        }
    }
    else
    {
        ChangeValue(lexical_cast<std::string>(*(uint32_t *)container.back()));
    }
    return 1;
}

int NumberControl::SaveChangesAsShort(bool forced)
{
    if (frame->popUp.hexMode || container.empty()) return 1;
    if (editedFileId != frame->popUp.loadedFileId) return 1;
    std::string value = std::string(GetValue().mb_str());
    if (value.size() > 0)
    {
        short batchMode = 0;
        if (value[0] == 'b' && !BatchCheck(value, batchMode))
        {
            frame->popUp.post(BATCHWARNING, BWTITLE);
            return 1;
        }
        try
        {
            int16_t casted = lexical_cast<int16_t>(value);
            if (batchMode > 0)
            {
                for (void *pointer : container)
                {
                    ++numEdits;
                    switch (batchMode)
                    {
                        case 1: *(int16_t *)pointer += casted; break;
                        case 2: *(int16_t *)pointer -= casted; break;
                        case 3: *(int16_t *)pointer *= casted; break;
                        case 4: *(int16_t *)pointer /= casted; break;
                        case 5: *(int16_t *)pointer %= casted; break;
                    }
                }
                ChangeValue(lexical_cast<std::string>(*(int16_t *)container.back()));
                HandleResults(*(int16_t *)container.back());
                return 0;
            }
            if (*(int16_t *)container.back() != casted || forced)
            {
                for (void *pointer : container)
                {
                    ++numEdits;
                    *(int16_t *)pointer = casted;
                }
                HandleResults(casted);
                return 0;
            }
        }
        catch (const bad_lexical_cast &)
        {
            frame->popUp.post("Please enter a number from -32 768 to 32 767", IETITLE, this);
            return 2;
        }
    }
    else
    {
        ChangeValue(lexical_cast<std::string>(*(int16_t *)container.back()));
    }
    return 1;
}

void NumberControl::ShowNumberAsUByte()
{
    if (frame->popUp.hexMode)
    {
        std::stringbuf buffer;
        std::ostream os(&buffer);
        os << std::hex << std::setfill('0') << std::setw(2) << std::uppercase;
        os << (short)*(uint8_t *)container.back();
        ChangeValue(buffer.str());
    }
    else
    {
        ChangeValue(lexical_cast<std::string>((short)*(uint8_t *)container.back()));
    }
    if (LinkedBox != nullptr)
    {
        LinkedBox->SetChoice(*(uint8_t *)container.back());
        LinkedBox->EnableControl(true);
    }
}

void NumberControl::ShowNumberAsFloat()
{
    if (frame->popUp.hexMode)
    {
        std::stringbuf buffer;
        std::ostream os(&buffer);
        os << std::hex << std::setfill('0') << std::setw(8) << std::uppercase;
        os << *(uint32_t *)container.back();
        ChangeValue(buffer.str());
    }
    else
    {
        if (frame->popUp.accurateFloats)
        {
            ChangeValue(lexical_cast<std::string>(*(float *)container.back()));
        }
        else
        {
            std::stringbuf buffer;
            std::ostream os(&buffer);
            if (*(int32_t *)container.back() == 0x7F7FFFFF) os << "max";
            else if (*(int32_t *)container.back() == 0x00800000) os << "min";
            else os << *(float *)container.back();
            ChangeValue(buffer.str());
        }
    }
    if (LinkedBox != nullptr)
    {
        LinkedBox->SetChoice(*(float *)container.back());
        LinkedBox->EnableControl(true);
    }
}

void NumberControl::ShowNumberAsLong()
{
    if (frame->popUp.hexMode)
    {
        std::stringbuf buffer;
        std::ostream os(&buffer);
        os << std::hex << std::setfill('0') << std::setw(8) << std::uppercase;
        os << *(uint32_t *)container.back();
        ChangeValue(buffer.str());
    }
    else
    {
        ChangeValue(lexical_cast<std::string>(*(int32_t *)container.back()));
    }
    if (LinkedBox != nullptr)
    {
        LinkedBox->SetChoice(*(int32_t *)container.back());
        LinkedBox->EnableControl(true);
    }
}

void NumberControl::ShowNumberAsULong()
{
    if (frame->popUp.hexMode)
    {
        std::stringbuf buffer;
        std::ostream os(&buffer);
        os << std::hex << std::setfill('0') << std::setw(8) << std::uppercase;
        os << *(uint32_t *)container.back();
        ChangeValue(buffer.str());
    }
    else
    {
        ChangeValue(lexical_cast<std::string>(*(uint32_t *)container.back()));
    }
    if (LinkedBox != nullptr)
    {
        LinkedBox->SetChoice(*(uint32_t *)container.back());
        LinkedBox->EnableControl(true);
    }
}

void NumberControl::ShowNumberAsShort()
{
    if (frame->popUp.hexMode)
    {
        std::stringbuf buffer;
        std::ostream os(&buffer);
        os << std::hex << std::setfill('0') << std::setw(4) << std::uppercase;
        os << *(uint16_t *)container.back();
        ChangeValue(buffer.str());
    }
    else
    {
        ChangeValue(lexical_cast<std::string>(*(int16_t *)container.back()));
    }
    if (LinkedBox != nullptr)
    {
        LinkedBox->SetChoice(*(int16_t *)container.back());
        LinkedBox->EnableControl(true);
    }
}

StringControl::StringControl(wxWindow *parent, BaseMainFrame *frame, std::vector<AGETextCtrl *> *group,
    unsigned length, bool connect) :
    AGETextCtrl(parent, AGETextCtrl::GIANT), maxSize(length)
{
    this->frame = frame;
    SetBackgroundColour(wxColour(220, 255, 220));
    if (connect)
    {
        Bind(wxEVT_KILL_FOCUS, &StringControl::OnKillFocus, this);
        Bind(wxEVT_TEXT_ENTER, &StringControl::OnEnter, this);
    }
    if (nullptr != group)
    {
        group->push_back(this);
    }
}

int StringControl::SaveEdits(bool forced) // This may crash the program.
{
    if (container.empty()) return 1;
    if (editedFileId != frame->popUp.loadedFileId) return 1;
    std::string value = std::string(GetValue().mb_str());
    if (*(std::string *)container.back() != value || forced) // Has been changed
    {
        if (value.length() >= 1 && (char)value[0] == '/')
        {
            char mode = value.length() >= 3 ? (char)value[1] : 0;
            switch (mode)
            {
                case '+':
                {
                    for (void *pointer : container)
                    {
                        ++numEdits;
                        *(std::string *)pointer += value.substr(2, maxSize - (*(std::string *)pointer).length());
                    }
                    break;
                }
                case '-':
                {
                    int cut = 0;
                    try
                    {
                        cut = lexical_cast<int>(value.substr(2));
                    }
                    catch (const bad_lexical_cast &)
                    {
                        frame->popUp.post("Please enter a number from 0 to " + lexical_cast<std::string>(maxSize), BWTITLE, this);
                        return 2;
                    }
                    for (void *pointer : container)
                    {
                        ++numEdits;
                        *(std::string *)pointer = (*(std::string *)pointer).substr(0, (*(std::string *)pointer).length() - cut);
                    }
                    break;
                }
                default:
                {
                    frame->popUp.post("Supported batch modifiers for strings are /+[text] and /-[integer]", BWTITLE, this);
                    return 1;
                }
            }
            ChangeValue(*(std::string *)container.back());
            HandleResults(0);
            return 0;
        }
        if (value.size() <= maxSize)
        {
            for (void *pointer : container)
            {
                ++numEdits;
                *(std::string *)pointer = value; // replenish data field
            }
        }
        else
        {
            value = value.substr(0, maxSize);
            for (void *pointer : container)
            {
                ++numEdits;
                *(std::string *)pointer = value;
            }
            ChangeValue(*(std::string *)container.back());
        }
        HandleResults(0);
        return 0;
    }
    return 1;
}

void StringControl::replenish()
{
    ChangeValue(*(std::string *)container.back());
}
