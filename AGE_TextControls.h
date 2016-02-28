#pragma once
#include "Common.h"

//  The purpose of these custom text controls is that you get specified error messages
//  when your mouse cursor focus gets off from a data edit box.

class AGEListView: public wxListView
{
public:
    AGEListView(wxWindow *parent, const wxSize &size):
    wxListView(parent, wxID_ANY, wxDefaultPosition, size, wxLC_VIRTUAL | wxLC_REPORT | wxLC_NO_HEADER)
    {
        SetItemCount(0);
        InsertColumn(0, wxEmptyString, wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE_USEHEADER);
    }

    wxArrayString names;
    vector<size_t> indexes;

private:
    virtual wxString OnGetItemText(long item, long column) const;
};

class AGELinkedBox
{
public:
    virtual void update(int)=0;
    virtual void enable(bool)=0;
};

class AGETextCtrl: public wxTextCtrl
{
public:
    AGETextCtrl(wxWindow *parent, int width):
    wxTextCtrl(parent, wxID_ANY, "", wxDefaultPosition, wxSize(width, -1), wxTE_PROCESS_ENTER){edits = 0;}

    static const unsigned SMALL=50, MEDIUM=70, NORMAL=100, LARGE=150, GIANT=200;
    static AGETextCtrl* init(const ContainerType type, vector<AGETextCtrl*> *group,
        wxFrame *frame, DelayedPopUp *editor, wxWindow *parent, unsigned length = NORMAL);
    virtual int SaveEdits(bool forced = false)=0;
    virtual void update()
    {
        if(container.empty())
        {
            Clear();
            Enable(false);
            if(!LinkedBoxes.empty())
            for(auto it = LinkedBoxes.begin(); it != LinkedBoxes.end(); ++it)
            {
                (*it)->update(-1);
                (*it)->enable(false);
            }
            return;
        }
        editedFileId = editor->loadedFileId;
        replenish();
        Enable(true);
    }
    virtual void refill()
    {
        if(container.empty())
        {
            Clear();
            return;
        }
        editedFileId = editor->loadedFileId;
        replenish();
    }
    virtual void replenish()=0;
    void changeContainerType(const ContainerType type)
    {
        switch(type)
        {
        case CByte: SetBackgroundColour(wxColour(255, 235, 215)); break;
        case CUByte: SetBackgroundColour(wxColour(255, 235, 215)); break;
        case CFloat: SetBackgroundColour(wxColour(255, 225, 255)); break;
        case CLong: SetBackgroundColour(wxColour(215, 255, 255)); break;
        case CShort: SetBackgroundColour(wxColour(210, 230, 255)); break;
        case CUShort: SetBackgroundColour(wxColour(210, 230, 255)); break;
        case CString: SetBackgroundColour(wxColour(220, 255, 220)); break;
        }
    }
    inline void clear(){container.clear();}
    inline void prepend(void* data){container.push_back(data);}
    inline void setMaxChars(unsigned short size){maxSize = size;}

    static const wxString BATCHWARNING, BWTITLE, IETITLE;
    vector<AGELinkedBox*> LinkedBoxes; // These are for check and combo boxes.

protected:
    void OnKillFocus(wxFocusEvent &event)
    {
        event.Skip();
        SaveEdits();
    }
    void OnEnter(wxCommandEvent &event){SaveEdits(true);}

    bool BatchCheck(string &value, short &batchMode)
    {
        if(value.size() < 3) return false;
        switch((char)value[1])
        {
            case '+': batchMode = 1; value = value.substr(2); return true;
            case '-': batchMode = 2; value = value.substr(2); return true;
            case '*': batchMode = 3; value = value.substr(2); return true;
            case '/': batchMode = 4; value = value.substr(2); return true;
            case '%': batchMode = 5; value = value.substr(2); return true;
            default: return false;
        }
    }
    void HandleResults(int casted)
    {
        if(!LinkedBoxes.empty())
        for(auto it = LinkedBoxes.begin(); it != LinkedBoxes.end(); ++it)
        {
            (*it)->update(casted);
        }
        frame->SetStatusText("Edits: "+lexical_cast<string>(editor->unSaved)+" + "+lexical_cast<string>(edits), 3);
        editor->unSaved += edits;
        edits = 0;
    }

    wxFrame* frame;
    DelayedPopUp *editor;
    ContainerType type;
    vector<void*> container; // Change to forward_list. No it's slower than vector.
    int editedFileId, edits;
    unsigned maxSize;
};

class TextCtrl_DLL: public wxTextCtrl
{
public:
    TextCtrl_DLL(wxWindow *parent, wxSize dimensions):
    wxTextCtrl(parent, wxID_ANY, "", wxDefaultPosition, dimensions, wxTE_MULTILINE)
    {
        Connect(GetId(), wxEVT_MOUSEWHEEL, wxMouseEventHandler(TextCtrl_DLL::wheelParent));
    }

    void wheelParent(wxMouseEvent &event)
    {
        GetParent()->GetEventHandler()->ProcessEvent(event);
    }
    int index;
};

class TextCtrl_Byte: public AGETextCtrl
{
public:
    TextCtrl_Byte(wxFrame *frame, DelayedPopUp *editor, wxWindow *parent, unsigned size):
    AGETextCtrl(parent, size)
    {
        this->frame = frame;
        this->editor = editor;
        SetBackgroundColour(wxColour(255, 235, 215));
        Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Byte::OnKillFocus));    // Must-have
        Connect(GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(TextCtrl_Byte::OnEnter));
    }
    int SaveEdits(bool forced = false);
    void replenish();
};

class TextCtrl_UByte: public AGETextCtrl
{
public:
    TextCtrl_UByte(wxFrame *frame, DelayedPopUp *editor, wxWindow *parent, unsigned size):
    AGETextCtrl(parent, size)
    {
        this->frame = frame;
        this->editor = editor;
        SetBackgroundColour(wxColour(255, 235, 215));
        Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_UByte::OnKillFocus));
        Connect(GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(TextCtrl_UByte::OnEnter));
    }
    int SaveEdits(bool forced = false);
    void replenish();
};

class TextCtrl_Float: public AGETextCtrl
{
public:
    TextCtrl_Float(wxFrame *frame, DelayedPopUp *editor, wxWindow *parent, unsigned petit):
    AGETextCtrl(parent, petit)
    {
        this->frame = frame;
        this->editor = editor;
        SetBackgroundColour(wxColour(255, 225, 255));
        Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Float::OnKillFocus));
        Connect(GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(TextCtrl_Float::OnEnter));
    }
    int SaveEdits(bool forced = false);
    void replenish();
};

class TextCtrl_Long: public AGETextCtrl
{
public:
    TextCtrl_Long(wxFrame *frame, DelayedPopUp *editor, wxWindow *parent, unsigned petit):
    AGETextCtrl(parent, petit)
    {
        this->frame = frame;
        this->editor = editor;
        SetBackgroundColour(wxColour(215, 255, 255));
        Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Long::OnKillFocus));
        Connect(GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(TextCtrl_Long::OnEnter));
    }
    int SaveEdits(bool forced = false);
    void replenish();
};

class TextCtrl_Short: public AGETextCtrl
{
public:
    TextCtrl_Short(wxFrame *frame, DelayedPopUp *editor, wxWindow *parent, unsigned petit):
    AGETextCtrl(parent, petit)
    {
        this->frame = frame;
        this->editor = editor;
        SetBackgroundColour(wxColour(210, 230, 255));
        Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Short::OnKillFocus));
        Connect(GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(TextCtrl_Short::OnEnter));
    }
    int SaveEdits(bool forced = false);
    void replenish();
};

class TextCtrl_UShort: public AGETextCtrl
{
public:
    TextCtrl_UShort(wxFrame *frame, DelayedPopUp *editor, wxWindow *parent, unsigned petit):
    AGETextCtrl(parent, petit)
    {
        this->frame = frame;
        this->editor = editor;
        SetBackgroundColour(wxColour(210, 230, 255));
        Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_UShort::OnKillFocus));
        Connect(GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(TextCtrl_UShort::OnEnter));
    }
    int SaveEdits(bool forced = false);
    void replenish();
};

class TextCtrl_String: public AGETextCtrl
{
public:
    TextCtrl_String(wxFrame *frame, DelayedPopUp *editor, wxWindow *parent, unsigned CLength = 0):
    AGETextCtrl(parent, AGETextCtrl::GIANT)
    {
        this->frame = frame;
        this->editor = editor;
        maxSize = CLength;
        SetBackgroundColour(wxColour(220, 255, 220));
        Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_String::OnKillFocus));
        Connect(GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(TextCtrl_String::OnEnter));
    }
    int SaveEdits(bool forced = false);
    void replenish();
};
