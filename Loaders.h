#pragma once
#include <list>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <wx/arrstr.h>
#include "genie/resource/Color.h"
#include "genie/resource/DrsFile.h"
#include "genie/resource/SlpFile.h"
#include "genie/resource/SmpFile.h"
#include "genie/resource/SmxFile.h"

namespace GG
{

void LoadPalettes(std::vector<std::vector<genie::Color>> &palettes, const wxString &path);
void LoadPlayerPalette(std::vector<std::vector<genie::Color>> &palettes, const wxString &path);
std::string LoadSound(wxArrayString &folders, const std::string &filename, int resnum);
const unsigned char *LoadSound(std::vector<genie::DrsFile *> &datafiles, int resnum);
genie::SlpFilePtr LoadSLP(genie::DrsFile &pack, int resnum);
genie::SlpFilePtr LoadSLP(const wxString &filename);
genie::SmpFilePtr LoadSMP(const wxString &filename);
genie::SmxFilePtr LoadSMX(const wxString &filename);

extern size_t cache_depth;

class LRU_SLP
{
public:
    typedef std::pair<wxString, genie::SpriteFilePtr> pair_t;
    typedef typename std::list<pair_t>::iterator lit_t;

    // Handle least recently used cache here.
    void put(const wxString &key, const genie::SpriteFilePtr &slp);

    genie::SpriteFilePtr use(const wxString &key);

private:
    std::list<pair_t> slp_cache_list;
    std::unordered_map<wxString, lit_t> slp_cache_map;
};

}
