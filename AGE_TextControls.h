#pragma once
#include "Common.h"

class ProperList: public wxVListBox
{
public:
    ProperList(wxWindow* parent, const wxSize& size);
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

//  The purpose of these custom text controls is that you get specified error messages
//  when your mouse cursor focus gets off from a data edit box.

class AGETextCtrl;
class LinkedControl
{
public:
    LinkedControl(AGETextCtrl* link);
    inline void TakeControl(void);
    virtual void OnChoose(wxCommandEvent&) = 0;
    virtual void SetChoice(int) = 0;
    virtual void EnableControl(bool) = 0;

protected:
    AGETextCtrl *TextControl;
};

class AGE_Frame;
class AGETextCtrl: public wxTextCtrl
{
public:
    AGETextCtrl(wxWindow* parent, int width);

    inline void clear() { container.clear(); }
    inline void prepend(void* data) { container.push_back(data); }
    virtual void replenish() = 0;
    virtual int SaveEdits(bool forced = false) = 0;
    void update();
    void refill();

    static unsigned SMALL, MEDIUM, NORMAL, LARGE, GIANT;
    static const wxString BATCHWARNING, BWTITLE, IETITLE;

protected:
    inline void OnKillFocus(wxFocusEvent& event) { event.Skip(); SaveEdits(); }
    inline void OnEnter(wxCommandEvent&) { SaveEdits(true); }
    bool BatchCheck(string& value, short& batchMode) const;
    void HandleResults(int casted);

    int editedFileId, numEdits;
    AGE_Frame* frame;
    LinkedControl* LinkedBox;
    vector<void*> container;
    friend class LinkedControl;
};

class TextCtrl_DLL: public wxTextCtrl
{
public:
    TextCtrl_DLL(wxWindow* parent, wxSize dimensions);

    int index;
};

class NumberControl : public AGETextCtrl
{
public:
    NumberControl(ContainerType type, wxWindow* parent, AGE_Frame* frame, vector<AGETextCtrl*>* group,
        bool connect = true, int width = NORMAL);
    void SetCastType(const ContainerType type);

private:
    inline void replenish() override { (this->*ShowNumber)(); }
    inline int SaveEdits(bool forced) override { return (this->*SaveChanges)(forced); }
    void (NumberControl::* ShowNumber)(void) = nullptr;
    int (NumberControl::* SaveChanges)(bool) = nullptr;

    void ShowNumberAsUByte(void);
    void ShowNumberAsFloat(void);
    void ShowNumberAsLong(void);
    void ShowNumberAsULong(void);
    void ShowNumberAsShort(void);

    int SaveChangesAsUByte(bool force = false);
    int SaveChangesAsFloat(bool force = false);
    int SaveChangesAsLong(bool force = false);
    int SaveChangesAsULong(bool force = false);
    int SaveChangesAsShort(bool force = false);
};

extern const unsigned short lengthiest;

class StringControl : public AGETextCtrl
{
public:
    StringControl(wxWindow* parent, AGE_Frame* frame, vector<AGETextCtrl*>* group,
        unsigned length = NORMAL, bool connect = true);
    int SaveEdits(bool forced = false) override;
    void replenish() override;
    inline void setMaxChars(unsigned short size) { maxSize = size; }

private:
    unsigned short maxSize;
};
