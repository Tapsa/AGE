#pragma once
#include <wx/frame.h>
#include "DataCopies.hpp"
#include "DelayedMessageRelay.h"

class BaseMainFrame : public wxFrame
{
public:
    BaseMainFrame(const wxString &title);
    static BaseMainFrame *Create(wxString commands);
    virtual void OnOpen(wxCommandEvent &event) = 0;
    virtual void OnExit(wxCloseEvent &event) = 0;

    // Enables working error messages after focus loss.
    DelayedMessageRelay popUp;

protected:
    // Stuff used when editing multiple files at once.
    static BaseMainFrame *openEditors[4];
    static Copies copies;
};
