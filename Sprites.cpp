#include "Common.h"
#include "Loaders.h"
#include "Sprites.h"

void AGE_SLP::reload(void)
{
    slpID = -3;
    lastSlpID = -2;
    filename = "";
}

void AGE_SLPs::reload(void)
{
    deltas.clear();
    AGE_SLP::reload();
    GG::LoadNextBatch();
}

size_t AGE_SLPs::getMemoryInUse(void)
{
    size_t bytes = slp ? slp->getSizeInMemory() : 0u;
    for (const auto &delta : deltas)
    {
        bytes += delta.second.slp ? delta.second.slp->getSizeInMemory() : 0u;
    }
    return bytes;
}
