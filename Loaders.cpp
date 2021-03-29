#include "Common.h"
#include "Loaders.h"

namespace GG
{

size_t cache_depth = 42;
LRU_SLP slp_cache;

void LoadPalettes(std::vector<std::vector<genie::Color>> &palettes, const wxString &path)
{
    if(wxEmptyString == path)
        return;

    wxString list;
    {
        wxFFile config(path);
        if(config.IsOpened())
        {
            config.ReadAll(&list);
        }
        else wxMessageBox("Failed to load " + path);
    }
    palettes.resize(1);
    wxArrayString lines = wxStringTokenize(list, '\n');
    long avail_num = 1;
    for(const wxString &line: lines)
    {
        size_t splitter = line.find(',');
        if(wxNOT_FOUND != splitter)
        {
            long pal_num;
            if(line.Left(splitter).ToCLong(&pal_num))
            {
                while(++avail_num <= pal_num)
                {
                    palettes.push_back(std::vector<genie::Color>());
                }
                try
                {
                    genie::PalFile pal;
                    size_t cut = path.rfind('\\');
                    pal.load((path(0U, ++cut) + line(++splitter, static_cast<size_t>(-1))).c_str());
                    palettes.push_back(pal.getColors());
                }
                catch(const std::ios_base::failure&){}
            }
        }
    }
}

void LoadPlayerPalette(std::vector<std::vector<genie::Color>> &palettes, const wxString &path)
{
    genie::PalFile pal;
    try
    {
        pal.load(path.c_str());
    }
    catch (const std::ios_base::failure&)
    {
        wxMessageBox("Cannot load player palette");
        return;
    }
    palettes.clear();
    palettes.push_back(pal.getColors());
}

// Need to use basic std::string for SFML and genieutils uses it too...
std::string LoadSound(wxArrayString &folders, const std::string &filename, int resnum)
{
    for(auto &f: folders)
    {
        std::string folder(f), sound = folder + filename;
        if(!wxFileName(sound).FileExists())
            sound = folder + lexical_cast<std::string>(resnum) + ".wav";
        if(wxFileName(sound).FileExists())
        {
            return sound;
        }
    }
    return "";
}

const unsigned char* LoadSound(std::vector<genie::DrsFile*> &datafiles, int resnum)
{
    for(auto &file: datafiles)
    {
        const unsigned char* sound = file->getWavPtr(resnum);
        if(sound)
        {
            return sound;
        }
    }
    return 0;
}

genie::SlpFilePtr LoadSLP(genie::DrsFile &pack, int resnum)
{
    genie::SlpFilePtr slp = pack.getSlpFile(resnum);
    if(slp)
    {
        // Takes care of unloading excess SLPs.
        slp_cache.put(lexical_cast<std::string>(resnum), slp);
    }
    return slp;
}

genie::SlpFilePtr LoadSLP(const wxString &filename)
{
    genie::SlpFilePtr slp = std::static_pointer_cast<genie::SlpFile>(slp_cache.use(filename));
    if(!slp)
    {
        try
        {
            slp.reset(new genie::SlpFile());
            slp->load(filename.c_str());
            slp->freelock();
            slp_cache.put(filename, slp);
        }
        catch(const std::ios_base::failure&)
        {
            return genie::SlpFilePtr();
        }
    }
    return slp;
}

genie::SmpFilePtr LoadSMP(const wxString &filename)
{
    genie::SmpFilePtr smp = std::static_pointer_cast<genie::SmpFile>(slp_cache.use(filename));
    if(!smp)
    {
        try
        {
            smp.reset(new genie::SmpFile());
            smp->load(filename.c_str());
            smp->freelock();
            slp_cache.put(filename, smp);
        }
        catch(const std::ios_base::failure&)
        {
            return genie::SmpFilePtr();
        }
    }
    return smp;
}

genie::SmxFilePtr LoadSMX(const wxString &filename)
{
    genie::SmxFilePtr smx = std::static_pointer_cast<genie::SmxFile>(slp_cache.use(filename));
    if(!smx)
    {
        try
        {
            smx.reset(new genie::SmxFile());
            smx->load(filename.c_str());
            smx->freelock();
            slp_cache.put(filename, smx);
        }
        catch(const std::ios_base::failure&)
        {
            return genie::SmxFilePtr();
        }
    }
    return smx;
}

void LRU_SLP::put(const wxString &key, const genie::SpriteFilePtr &slp)
{
    // Put key as first item.
    auto it = slp_cache_map.find(key);
    slp_cache_list.push_front(pair_t(key, slp));
    if (it != slp_cache_map.end())
    {
        slp_cache_list.erase(it->second);
        //slp_cache_map.erase(it); // Why is this needed?
    }
    slp_cache_map[key] = slp_cache_list.begin();

    // Unload from end excess items.
    if (slp_cache_map.size() > cache_depth)
    {
        auto last = --(slp_cache_list.end());
        // Remember to unload before popping.
        last->second->unload();
        slp_cache_map.erase(last->first);
        slp_cache_list.pop_back();
    }
}

genie::SpriteFilePtr LRU_SLP::use(const wxString &key)
{
    auto it = slp_cache_map.find(key);
    if (it == slp_cache_map.end())
    {
        return genie::SpriteFilePtr();
    }
    else
    {
        slp_cache_list.splice(slp_cache_list.begin(), slp_cache_list, it->second);
        return it->second->second;
    }
}

}
