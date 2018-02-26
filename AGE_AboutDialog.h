#pragma once
#include "Common.h"

class AGE_AboutDialog: public wxDialog
{
public:
	AGE_AboutDialog(wxWindow *parent, const wxFont &font);

	static const wxString AGE_VER;
};

namespace GG
{

void LoadPalettes(vector<vector<genie::Color>> &palettes, const wxString &path);
string LoadSound(wxArrayString &folders, const string &filename, int resnum);
const unsigned char* LoadSound(vector<genie::DrsFile*> &datafiles, int resnum);
genie::SlpFilePtr LoadSLP(genie::DrsFile &pack, int resnum);
genie::SlpFilePtr LoadSLP(const wxString &filename);

extern size_t cache_depth;

template <typename key_t>
class LRU_SLP
{
public:
    typedef pair<key_t, genie::SlpFilePtr> pair_t;
    typedef typename list<pair_t>::iterator lit_t;

    // Handle least recently used cache here.
    void put(const key_t &key, const genie::SlpFilePtr &slp)
    {
        // Put key as first item.
        auto it = slp_cache_map.find(key);
        slp_cache_list.push_front(pair_t(key, slp));
        if(it != slp_cache_map.end())
        {
            slp_cache_list.erase(it->second);
            //slp_cache_map.erase(it); // Why is this needed?
        }
        slp_cache_map[key] = slp_cache_list.begin();

        // Unload from end excess items.
        if(slp_cache_map.size() > cache_depth)
        {
            auto last = --(slp_cache_list.end());
            // Remember to unload before popping.
            last->second->unload();
            slp_cache_map.erase(last->first);
            slp_cache_list.pop_back();
        }
    }

    genie::SlpFilePtr use(const key_t &key)
    {
        auto it = slp_cache_map.find(key);
        if(it == slp_cache_map.end())
        {
            return genie::SlpFilePtr();
        }
        else
        {
            slp_cache_list.splice(slp_cache_list.begin(), slp_cache_list, it->second);
            return it->second->second;
        }
    }

private:
    list<pair_t> slp_cache_list;
    unordered_map<key_t, lit_t> slp_cache_map;
};

extern LRU_SLP<int> slp_cache_resnum;
extern LRU_SLP<std::string> slp_cache_resname;

}
