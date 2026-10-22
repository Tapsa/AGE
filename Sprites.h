#pragma once
#include <map>
#include <wx/bitmap.h>
#include "OwnedSound.h"
#include "genie/resource/SpriteFile.h"

const float PI2A = 6.28319f, PI2 = 6.2832f;

class AGE_SLP
{
public:
    int32_t slpID = -1, frameID, datID = -1, lastSlpID = -2, startframe;
    uint16_t angles, fpa, frames, mirror;
    wxString filename = "";
    genie::SpriteFilePtr slp;
    wxBitmap bitmap;
    std::array<OwnedSound, 4> sounds;
    int16_t xpos = 0, ypos = 0, xdelta = 0, ydelta = 0, delays[4] = {0, -1, -1, -1};
    bool flip = false, is32 = false;
    float beginbearing = 0.f, endbearing = PI2A;

    virtual void reload(void);
};

class AGE_SLPs : public AGE_SLP
{
public:
    std::multimap<int, AGE_SLP> deltas;
    bool pause = false;

    void reload(void) override;
    size_t getMemoryInUse(void);
};
