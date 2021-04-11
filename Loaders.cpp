#include "Common.h"
#include "Loaders.h"
#include "genie/resource/SmpFile.h"
#include "genie/resource/SmxFile.h"

namespace GG
{

size_t cache_size;
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
    if (wxEmptyString == path)
        return;

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
    for(wxString &f: folders)
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
    for(genie::DrsFile* file: datafiles)
    {
        const unsigned char* sound = file->getWavPtr(resnum);
        if(sound)
        {
            return sound;
        }
    }
    return 0;
}

genie::SpriteFilePtr LoadSLP(genie::DrsFile &pack, int resnum)
{
    genie::SpriteFilePtr slp = pack.getSlpFile(resnum);
    if(slp)
    {
        // Takes care of unloading excess SLPs.
        slp_cache.put(lexical_cast<std::string>(resnum), slp);
    }
    return slp;
}

genie::SpriteFilePtr LoadSLP(const wxString &filename)
{
    genie::SpriteFilePtr slp = slp_cache.use(filename);
    if(!slp)
    {
        try
        {
            slp.reset(new genie::SlpFile());
            slp->loadAndRelease(filename.c_str());
            slp_cache.put(filename, slp);
        }
        catch(const std::ios_base::failure&)
        {
            return genie::SlpFilePtr();
        }
    }
    return slp;
}

genie::SpriteFilePtr LoadSMP(const wxString &filename)
{
    genie::SpriteFilePtr smp = slp_cache.use(filename);
    if(!smp)
    {
        try
        {
            smp.reset(new genie::SmpFile());
            smp->loadAndRelease(filename.c_str());
            slp_cache.put(filename, smp);
        }
        catch(const std::ios_base::failure&)
        {
            return genie::SmpFilePtr();
        }
    }
    return smp;
}

genie::SpriteFilePtr LoadSMX(const wxString &filename)
{
    genie::SpriteFilePtr smx = slp_cache.use(filename);
    if(!smx)
    {
        try
        {
            smx.reset(new genie::SmxFile());
            smx->loadAndRelease(filename.c_str());
            slp_cache.put(filename, smx);
        }
        catch(const std::ios_base::failure&)
        {
            return genie::SmxFilePtr();
        }
    }
    return smx;
}

void LoadNextBatch(void)
{
    slp_cache.AdvanceProductionBatch();
}

void LRU_SLP::put(const wxString &key, const genie::SpriteFilePtr &slp)
{
    // Put key as first item.
    memory_in_use += slp->getSizeInMemory();
    map_it it = slp_cache_map.find(key);
    slp_cache_list.emplace_front(production_batch, key, slp);
    if (it != slp_cache_map.end())
    {
        memory_in_use -= it->second->slp->getSizeInMemory();
        slp_cache_list.erase(it->second);
        //slp_cache_map.erase(it); // Why is this needed?
    }
    slp_cache_map[key] = slp_cache_list.begin();

    // Unload from end excess items.
    list_it last = slp_cache_list.end();
    while (memory_in_use > cache_size && --last != slp_cache_list.begin())
    {
        if (last->batch != production_batch)
        {
            memory_in_use -= last->slp->getSizeInMemory();
            // Remember to unload before popping.
            last->slp->unload();
            slp_cache_map.erase(last->key);
            slp_cache_list.erase(list_it(last++));
        }
    }
}

genie::SpriteFilePtr LRU_SLP::use(const wxString &key)
{
    map_it it = slp_cache_map.find(key);
    if (it == slp_cache_map.end())
    {
        return genie::SpriteFilePtr();
    }
    else
    {
        slp_cache_list.splice(slp_cache_list.begin(), slp_cache_list, it->second);
        return it->second->slp;
    }
}

}
