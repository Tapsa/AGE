#pragma once
#include <list>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <wx/arrstr.h>
#include "genie/resource/Color.h"
#include "genie/resource/DrsFile.h"
#include "genie/resource/SpriteFile.h"

namespace GG
{

void LoadPalettes(std::vector<std::vector<genie::Color>> &palettes, const wxString &path);
void LoadPlayerPalette(std::vector<std::vector<genie::Color>> &palettes, const wxString &path);
std::string LoadSound(wxArrayString &folders, const std::string &filename, int resnum);
const unsigned char *LoadSound(std::vector<genie::DrsFile *> &datafiles, int resnum);
genie::SpriteFilePtr LoadSLP(genie::DrsFile &pack, int resnum);
genie::SpriteFilePtr LoadSLP(const wxString &filename);
genie::SpriteFilePtr LoadSMP(const wxString &filename);
genie::SpriteFilePtr LoadSMX(const wxString &filename);

// This will ensure that all sprites are displayed.
void LoadNextBatch(void);

extern size_t cache_size;

class CachedSprite
{
public:
    CachedSprite(size_t batch, wxString key, genie::SpriteFilePtr slp) :
        batch(batch), key(key), slp(slp)
    {
    }
    size_t batch;
    wxString key;
    genie::SpriteFilePtr slp;
};

class LRU_SLP
{
public:
    typedef typename std::list<CachedSprite>::iterator list_it;
    typedef typename std::unordered_map<wxString, list_it>::iterator map_it;

    // Handle least recently used cache here.
    void put(const wxString &key, const genie::SpriteFilePtr &slp);

    genie::SpriteFilePtr use(const wxString &key);

    inline void AdvanceProductionBatch(void) { ++production_batch; }

private:
    size_t production_batch = 0;
    size_t memory_in_use = 0;
    std::list<CachedSprite> slp_cache_list;
    std::unordered_map<wxString, list_it> slp_cache_map;
};

}
