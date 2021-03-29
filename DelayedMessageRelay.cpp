#include "Common.h"
#include "DelayedMessageRelay.h"

void DelayedMessageRelay::post(const wxString &message, const wxString &title, wxWindow *target)
{
    popUpTitle = title;
    popUpMessage = message;
    focusTarget = target;
    hasMessage = true;
}
