#include "Common.h"
#include "AGE_Frame.h"
#include "AGE_Copies.hpp"

#ifndef Main_h
#define Main_h

class AGE: public wxApp
{
	virtual bool OnInit();
	void FixSize(AGE_Frame*);

	vector<AGE_Frame*> windows;
	wxString argPath;
	Copies copies;
};

DECLARE_APP(AGE)

#endif
