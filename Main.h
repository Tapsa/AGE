#pragma once
#include <wx/app.h>

struct ma_engine;

class AGE : public wxApp
{
    bool OnInit() override;
    int OnExit() override;

public:
    static ma_engine SoundEngine;
};

DECLARE_APP(AGE)
