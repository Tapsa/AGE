#pragma once
#include <wx/event.h>

class AGETextCtrl;
class LinkedControl
{
public:
    LinkedControl(AGETextCtrl *link);
    inline void TakeControl(void);
    virtual void OnChoose(wxCommandEvent &) = 0;
    virtual void SetChoice(int) = 0;
    virtual void EnableControl(bool) = 0;

protected:
    AGETextCtrl *TextControl;
};
