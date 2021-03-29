#include "Common.h"
#include "CustomTextControls.h"
#include "LinkedControl.h"

LinkedControl::LinkedControl(AGETextCtrl* link) :
    TextControl(link)
{
    TakeControl();
}

void LinkedControl::TakeControl(void)
{
    TextControl->LinkedBox = this;
}
