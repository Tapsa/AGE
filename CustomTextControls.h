#pragma once
#include <string>
#include <vector>
#include <wx/textctrl.h>

//  The purpose of these custom text controls is that you get specified error messages
//  when your mouse cursor focus gets off from a data edit box.

enum ContainerType { CUByte, CFloat, CLong, CULong, CShort };

class BaseMainFrame;
class LinkedControl;

class AGETextCtrl : public wxTextCtrl
{
public:
    AGETextCtrl(wxWindow *parent, int width);

    inline void clear() { container.clear(); }
    inline void prepend(void *data) { container.push_back(data); }
    virtual void replenish() = 0;
    virtual int SaveEdits(bool forced = false) = 0;
    void SetAsText(unsigned value);
    void update();
    void refill();

    static unsigned SMALL, MEDIUM, NORMAL, LARGE, GIANT;

protected:
    inline void OnKillFocus(wxFocusEvent &event) { event.Skip(); SaveEdits(); }
    inline void OnEnter(wxCommandEvent &) { SaveEdits(true); }
    bool BatchCheck(std::string &value, short &batchMode) const;
    void HandleResults(int casted);

    size_t editedFileId, numEdits;
    BaseMainFrame *frame;
    LinkedControl *LinkedBox;
    std::vector<void *> container;
    friend class LinkedControl;
};

class TextIndexControl : public wxTextCtrl
{
public:
    TextIndexControl(wxWindow *parent, wxSize dimensions);

    int index;
};

class NumberControl : public AGETextCtrl
{
public:
    NumberControl(ContainerType type, wxWindow *parent, BaseMainFrame *frame,
        std::vector<AGETextCtrl *> *group, bool connect = true, int width = NORMAL);
    void SetCastType(const ContainerType type);

private:
    inline void replenish() override { (this->*ShowNumber)(); }
    inline int SaveEdits(bool forced) override { return (this->*SaveChanges)(forced); }
    void (NumberControl:: *ShowNumber)(void) = nullptr;
    int (NumberControl:: *SaveChanges)(bool) = nullptr;

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

class StringControl : public AGETextCtrl
{
public:
    StringControl(wxWindow *parent, BaseMainFrame *frame, std::vector<AGETextCtrl *> *group,
        unsigned length = NORMAL, bool connect = true);
    int SaveEdits(bool forced = false) override;
    void replenish() override;
    inline void setMaxChars(unsigned short size) { maxSize = size; }

private:
    unsigned short maxSize;
};
