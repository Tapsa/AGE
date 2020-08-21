#include "AGE_AboutDialog.h"
#include "AppIcon64.xpm"

const wxString AGE_AboutDialog::AGE_VER = "2020.8.21";

AGE_AboutDialog::AGE_AboutDialog(wxWindow *parent, const wxFont &font)
: wxDialog(parent, -1, "About Advanced Genie Editor", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxNO_DEFAULT)
{
    SetFont(font);
    SolidText *Title = new SolidText(this, "Advanced Genie Editor\nVersion "+AGE_VER+"\nGPLv3 2011 - 2020\n\nDevelopers:\nMikko \"Tapsa\" P, since 2.0b\nApre - genieutils, 2.1a to 3.1\nEstien Nifo aka StSB77, 1.0a to 2.0a");
    wxStaticBitmap *Image = new wxStaticBitmap(this, wxID_ANY, wxBitmap(AppIcon64_xpm));
    SolidText *Credits = new SolidText(this, "Credits:\nYkkrosh - GeniEd 1 source code\nScenario_t_c - GeniEd 2 source code\nAlexandra \"Taichi San\", DarkRain654 - data file research\nDiGiT, JustTesting1234, AOHH - genie file structure\nCysion, Kris, Sarthos - important help\nBF_Tanks - some help\nDonnieboy, Sarn, chab - tooltip texts\ngagman - new icon");
    wxHyperlinkCtrl *AoKHThread = new wxHyperlinkCtrl(this, wxID_ANY, "Age of Kings Heaven AGE forum topic", "http://aok.heavengames.com/cgi-bin/forums/display.cgi?action=st&fn=9&tn=44059&st=recent&f=9,44059,0,365", wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxHL_CONTEXTMENU | wxHL_ALIGN_LEFT);
    //UPXInfo = new SolidText(this, "Compressed with:");
    //UPXLink = new wxHyperlinkCtrl(this, wxID_ANY, "The Ultimate Packer for eXecutables", "http://upx.sourceforge.net", wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxHL_CONTEXTMENU | wxHL_ALIGN_LEFT);

    wxBoxSizer *MainRight = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *MainAbout = new wxBoxSizer(wxVERTICAL);

    MainRight->Add(Title, 1, wxEXPAND);
    MainRight->Add(Image);
    MainAbout->Add(MainRight, 0, wxALL, 10);
    MainAbout->Add(Credits, 0, wxALL - wxUP, 10);
    MainAbout->Add(AoKHThread, 0, wxALL - wxUP, 10);
    //MainAbout->Add(UPXInfo);
    //MainAbout->Add(UPXLink);

    SetSizerAndFit(MainAbout);
}

namespace GG
{

size_t cache_depth = 42;
LRU_SLP<int, genie::SlpFilePtr> slp_cache_resnum;
LRU_SLP<wxString, genie::SlpFilePtr> slp_cache_resname;
LRU_SLP<wxString, genie::SmpFilePtr> smp_cache_resname;

void LoadPalettes(vector<vector<genie::Color>> &palettes, const wxString &path)
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
        int splitter = line.find(',');
        if(wxNOT_FOUND != splitter)
        {
            long pal_num;
            if(line.Left(splitter).ToCLong(&pal_num))
            {
                while(++avail_num <= pal_num)
                {
                    palettes.push_back(vector<genie::Color>());
                }
                try
                {
                    genie::PalFile pal;
                    int cut = path.rfind('\\');
                    pal.load((path(0, ++cut) + line(++splitter, -1)).c_str());
                    palettes.push_back(pal.getColors());
                }
                catch(const std::ios_base::failure&){}
            }
        }
    }
}

// Need to use basic string for SFML and genieutils uses it too...
string LoadSound(wxArrayString &folders, const string &filename, int resnum)
{
    for(auto &f: folders)
    {
        string folder(f), sound = folder + filename;
        if(!wxFileName(sound).FileExists())
            sound = folder + lexical_cast<string>(resnum) + ".wav";
        if(wxFileName(sound).FileExists())
        {
            return sound;
        }
    }
    return "";
}

const unsigned char* LoadSound(vector<genie::DrsFile*> &datafiles, int resnum)
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
        slp_cache_resnum.put(resnum, slp);
    }
    return slp;
}

genie::SlpFilePtr LoadSLP(const wxString &filename)
{
    genie::SlpFilePtr slp = slp_cache_resname.use(filename);
    if(!slp)
    {
        try
        {
            slp.reset(new genie::SlpFile());
            slp->load(filename.c_str());
            slp->freelock();
            slp_cache_resname.put(filename, slp);
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
    genie::SmpFilePtr smp = smp_cache_resname.use(filename);
    if(!smp)
    {
        try
        {
            smp.reset(new genie::SmpFile());
            smp->load(filename.c_str());
            smp->freelock();
            smp_cache_resname.put(filename, smp);
        }
        catch(const std::ios_base::failure&)
        {
            return genie::SmpFilePtr();
        }
    }
    return smp;
}

}
