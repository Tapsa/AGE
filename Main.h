/* Main.h */

#include "AGE_Frame.h"

#ifndef Main_h
#define Main_h

class AGE: public wxApp
{
    virtual bool OnInit();
    
    AGE_Frame *MainWindow;
};

DECLARE_APP(AGE)

#endif
