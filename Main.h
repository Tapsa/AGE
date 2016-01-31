#pragma once
#include "Common.h"
#include "AGE_Frame.h"
#include "AGE_Copies.hpp"

class AGE: public wxApp
{
    virtual bool OnInit();
};

DECLARE_APP(AGE)
