#include "AGE_Frame.h"

#ifndef AGE_h
#define AGE_h

class AGE : public wxApp
{
    virtual bool OnInit();
    
    AGE_Frame * MainWindow;
};

DECLARE_APP(AGE)

#endif
