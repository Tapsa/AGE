#pragma once
#include "Common.h"

//  The purpose of these custom text controls is that you get specified error messages
//  when your mouse cursor focus gets off from a data edit box.

// TODO: Remove useless timers and extra binds.
class ProperList: public wxVListBox
{
public:
    ProperList(wxWindow *parent, const wxSize &size):
    wxVListBox(parent, wxID_ANY, wxDefaultPosition, size, wxLB_INT_HEIGHT | wxLB_MULTIPLE)//wxLB_EXTENDED)
    {
        SetItemCount(0);
        row_height = GetCharHeight();
    }
    void EnsureVisible(size_t n);
    inline void Sweep() {names.clear(); indexes.clear();}
    //inline void Add(const wxString &name, size_t i);

    wxArrayString names;
    vector<size_t> indexes;

private:
    wxCoord OnMeasureItem(size_t) const override {return row_height;}
    void OnDrawItem(wxDC &dc, const wxRect &rect, size_t n) const override;
    void OnDrawBackground(wxDC &dc, const wxRect &rect, size_t n) const override;

    int row_height = 0;
};

class AGETextCtrl;
class AGELinkedBox
{
public:
    virtual void OnChoose(wxCommandEvent&)=0;
    virtual void SetChoice(int)=0;
    virtual void EnableCtrl(bool)=0;

    AGETextCtrl *TextBox;
};

// This could be used if linked box system gets abolished.
class AGEBaseCtrl
{
public:
    inline void clear(){container.clear();}
    inline void prepend(void* data){container.push_back(data);}
    virtual int SaveEdits(bool forced = false)=0;

    static const wxString BATCHWARNING, BWTITLE, IETITLE;

protected:
    void OnKillFocus(wxFocusEvent &event)
    {
        event.Skip();
        SaveEdits();
    }
    void OnEnter(wxCommandEvent&){SaveEdits(true);}

    vector<void*> container;
    ContainerType type;
    int editedFileId, edits;
    DelayedPopUp *editor;
    wxFrame* frame;
};

class AGETextCtrl: public wxTextCtrl, public AGEBaseCtrl
{
public:
    AGETextCtrl(wxWindow *parent, int width):
    wxTextCtrl(parent, wxID_ANY, "", wxDefaultPosition, wxSize(width, -1), wxTE_PROCESS_ENTER){edits = 0;}

    static const unsigned SMALL=50, MEDIUM=70, NORMAL=100, LARGE=150, GIANT=200;
    static AGETextCtrl* init(const ContainerType type, vector<AGETextCtrl*> *group,
        wxFrame *frame, DelayedPopUp *editor, wxWindow *parent, unsigned length = NORMAL);
    virtual void update()
    {
        if(container.empty())
        {
            Clear();
            Enable(false);
            if(!LinkedBoxes.empty())
            for(auto it = LinkedBoxes.begin(); it != LinkedBoxes.end(); ++it)
            {
                (*it)->SetChoice(-1);
                (*it)->EnableCtrl(false);
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
    inline void setMaxChars(unsigned short size){maxSize = size;}

    vector<AGELinkedBox*> LinkedBoxes; // These are for check boxes.

protected:
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
        for(auto it = LinkedBoxes.begin(); it != LinkedBoxes.end(); ++it)
        {
            (*it)->SetChoice(casted);
        }
        frame->SetStatusText("Edits: "+lexical_cast<string>(editor->unSaved)+" + "+lexical_cast<string>(edits), 3);
        editor->unSaved += edits;
        edits = 0;
    }

    unsigned maxSize;
};

class TextCtrl_DLL: public wxTextCtrl
{
public:
    TextCtrl_DLL(wxWindow *parent, wxSize dimensions):
    wxTextCtrl(parent, wxID_ANY, "", wxDefaultPosition, dimensions, wxTE_MULTILINE)
    {
        Bind(wxEVT_MOUSEWHEEL, [this](wxMouseEvent &event){GetParent()->GetEventHandler()->ProcessEvent(event);});
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
        Bind(wxEVT_KILL_FOCUS, &TextCtrl_Byte::OnKillFocus, this);    // Must-have
        Bind(wxEVT_TEXT_ENTER, &TextCtrl_Byte::OnEnter, this);
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
        Bind(wxEVT_KILL_FOCUS, &TextCtrl_UByte::OnKillFocus, this);
        Bind(wxEVT_TEXT_ENTER, &TextCtrl_UByte::OnEnter, this);
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
        Bind(wxEVT_KILL_FOCUS, &TextCtrl_Float::OnKillFocus, this);
        Bind(wxEVT_TEXT_ENTER, &TextCtrl_Float::OnEnter, this);
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
        Bind(wxEVT_KILL_FOCUS, &TextCtrl_Long::OnKillFocus, this);
        Bind(wxEVT_TEXT_ENTER, &TextCtrl_Long::OnEnter, this);
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
        Bind(wxEVT_KILL_FOCUS, &TextCtrl_Short::OnKillFocus, this);
        Bind(wxEVT_TEXT_ENTER, &TextCtrl_Short::OnEnter, this);
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
        Bind(wxEVT_KILL_FOCUS, &TextCtrl_UShort::OnKillFocus, this);
        Bind(wxEVT_TEXT_ENTER, &TextCtrl_UShort::OnEnter, this);
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
        Bind(wxEVT_KILL_FOCUS, &TextCtrl_String::OnKillFocus, this);
        Bind(wxEVT_TEXT_ENTER, &TextCtrl_String::OnEnter, this);
    }
    int SaveEdits(bool forced = false);
    void replenish();
};
