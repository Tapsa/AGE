#pragma once
#include <wx/string.h>
#include <wx/window.h>

class DelayedMessageRelay
{
public:
    bool hasMessage = false, hexMode = false, accurateFloats = false;
    wxString popUpMessage, popUpTitle;
    wxWindow *focusTarget = 0;
    size_t unSaved = 0, loadedFileId = 0;

    void post(const wxString &message, const wxString &title, wxWindow *target = nullptr);
};
