#include "Common.h"
#include "AGE_Frame.h"
#include "AGE_Copies.hpp"

#ifndef Main_h
#define Main_h

class AGE: public wxApp
{
    virtual bool OnInit();
    
	vector<AGE_Frame*> windows;
	Copies copies;
};

DECLARE_APP(AGE)

#endif
