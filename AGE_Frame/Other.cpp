#include "Common.h"
#include "../AboutDialog.h"
#include "../AGE_Frame.h"
#include "../EditableVersion.h"
#include "../Loaders.h"
#include "../OpenDialog.h"
#include "../SaveDialog.h"

#ifndef WIN32
// dummies for code that is not used on linux
#define LoadStringA(lib, id, buf, letters) (false)
#define LoadLibrary(name) (0)
#endif

// Icons
#include "../DRSunlock.xpm"
#include "../DRSlock.xpm"

genie::GameVersion EditorVersionAsGameVersion(int ver)
{
    switch(ver)
    {
        case EV_TEST: return genie::GV_TEST;
        case EV_MIK: return genie::GV_MIK;
        case EV_DAVE: return genie::GV_DAVE;
        case EV_MATT: return genie::GV_MATT;
        case EV_AoEB: return genie::GV_AoEB;
        case EV_AoE: return genie::GV_AoE;
        case EV_RoR: return genie::GV_RoR;
        case EV_AoKE3: return genie::GV_AoKE3;
        case EV_AoKA: return genie::GV_AoKA;
        case EV_AoKB: return genie::GV_AoKB;
        case EV_AoK: return genie::GV_AoK;
        case EV_TC: return genie::GV_TC;
        case EV_UP: return genie::GV_TC;
        case EV_TCV: return genie::GV_TCV;
        case EV_Cysion: return genie::GV_Cysion;
        case EV_DE2: return genie::GV_C2;
        case EV_SWGB: return genie::GV_SWGB;
        case EV_CC: return genie::GV_CC;
        case EV_EF: return genie::GV_CCV;
        case EV_EF2: return genie::GV_CCV2;
        case EV_Tapsa: return genie::GV_Tapsa;

        default: wxMessageBox("Wrong version", "Oops!");
        return genie::GV_None;
    }
}

wxString FixEditorVersion(wxString ver)
{
    switch (lexical_cast<int>(ver))
    {
        case EV_TEST:
            return "Test      ";
        case EV_MIK:
            return "Mike      ";
        case EV_DAVE:
            return "Dave      ";
        case EV_MATT:
            return "Matt      ";
        case EV_AoEB:
            return "AoE Beta  ";
        case EV_AoE:
            return "AoE       ";
        case EV_RoR:
            return "RoR       ";
        case EV_Tapsa:
            return "AoE DE    ";
        case EV_AoKE3:
            return "AoK E3    ";
        case EV_AoKA:
            return "AoK Alpha ";
        case EV_AoKB:
            return "AoK Beta  ";
        case EV_AoK:
            return "AoK       ";
        case EV_TC:
            return "TC        ";
        case EV_UP:
            return "UP        ";
        case EV_TCV:
            return "TC TP     ";
        case EV_Cysion:
            return "AoK HD    ";
        case EV_DE2:
            return "AoK DE    ";
        case EV_SWGB:
            return "SWGB      ";
        case EV_CC:
            return "CC        ";
        case EV_EF:
            return "EF old    ";
        case EV_EF2:
            return "EF        ";
        default:
            return "None      ";
    }
}

void AGE_Frame::OnOpen(wxCommandEvent&)
{
    if(popUp.unSaved > 0)
    {
        int answer = wxMessageBox("Do you want to save changes made to open files?\nThere are "
                        +lexical_cast<std::string>(popUp.unSaved)+" unsaved changes.",
                        "Advanced Genie Editor", wxICON_QUESTION | wxCANCEL | wxYES_NO);
        if(answer != wxNO)
        {
            if(answer == wxYES)
            {
                wxCommandEvent SaveFiles(wxEVT_MENU, eSave);
                OnSave(SaveFiles);
            }
            else return;
        }
        else if(AutoBackups) SaveBackup();
    }

    if(slp_window)
    {
        // TODO: Make the SLP view inactive until new data is loaded.
    }
    if(!SkipOpenDialog)
    {
        OpenDialog OpenBox(this, font);

        int RecentItems, RecentVersion;
        {
            wxConfig RecentOpen("", "", "AGE2\\RecentOpen", "", wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
            RecentOpen.Read("Recent/Items", &RecentItems, 0);
            RecentOpen.Read("Recent/Version", &RecentVersion, 1);
            RecentItems = std::min(30, RecentItems);
            OpenBox.RecentValues.resize(RecentItems);
            for(int i=0; i < RecentItems; ++i)
            {
                OpenBox.RecentValues[i].Alloc(13);
                wxString temp, entry = "Recent" + wxString::Format("%04d", i + 1);
                RecentOpen.Read(entry + "/DatVersion", &temp, "-1");
                if (RecentVersion < 2 && lexical_cast<int>(temp) > EV_TC)
                {
                    temp = "-1";
                }
                if (RecentVersion < 4)
                {
                    int version = lexical_cast<int>(temp);
                    if (version > EV_EF)
                    {
                        ++version;
                        temp = lexical_cast<std::string>(version);
                    }
                }
                OpenBox.RecentValues[i].Add(temp);
                RecentOpen.Read(entry + "/DatPath", &temp, wxEmptyString); OpenBox.RecentValues[i].Add(temp);
                RecentOpen.Read(entry + "/Lang", &temp, wxEmptyString); OpenBox.RecentValues[i].Add(temp);
                RecentOpen.Read(entry + "/LangX1", &temp, wxEmptyString); OpenBox.RecentValues[i].Add(temp);
                RecentOpen.Read(entry + "/LangX1P1", &temp, wxEmptyString); OpenBox.RecentValues[i].Add(temp);
                RecentOpen.Read(entry + "/PathDRS", &temp, wxEmptyString); OpenBox.RecentValues[i].Add(temp);
                RecentOpen.Read(entry + "/PathDRS2", &temp, wxEmptyString); OpenBox.RecentValues[i].Add(temp);
                RecentOpen.Read(entry + "/PathDRS3", &temp, wxEmptyString); OpenBox.RecentValues[i].Add(temp);
                RecentOpen.Read(entry + "/LooseSLP", &temp, wxEmptyString); OpenBox.RecentValues[i].Add(temp);
                if (RecentVersion >= 3)
                {
                    RecentOpen.Read(entry + "/LooseModSLP", &temp, wxEmptyString); OpenBox.RecentValues[i].Add(temp);
                }
                else
                {
                    OpenBox.RecentValues[i].Add("");
                }
                RecentOpen.Read(entry + "/PathPalettes", &temp, wxEmptyString); OpenBox.RecentValues[i].Add(temp);
                RecentOpen.Read(entry + "/PathPlayerPalette", &temp, wxEmptyString); OpenBox.RecentValues[i].Add(temp);
                if (RecentVersion >= 5)
                {
                    RecentOpen.Read(entry + "/PathCustomNames", &temp, wxEmptyString); OpenBox.RecentValues[i].Add(temp);
                }
                else
                {
                    OpenBox.RecentValues[i].Add("");
                }
            }
        }
        if (OpenBox.RecentValues.size())
        {
            for (int i = 0; i < RecentItems; ++i)
            {
                OpenBox.CheckBox_Recent->Append(FixEditorVersion(OpenBox.RecentValues[i][0]) + OpenBox.RecentValues[i][1]);
            }
        }
        else
        {
            OpenBox.CheckBox_Recent->Append("Happy Modding!");
        }
        OpenBox.CheckBox_Recent->SetSelection(0);

        OpenBox.Path_CustomDefault->SetPath(CustomFolder);
        if (RecentVersion >= 2)
        {
            OpenBox.ComboBox_GenieVer->SetSelection(GameVersion);
        }
        else
        {
            OpenBox.ComboBox_GenieVer->SetSelection(-1);
        }
        OpenBox.TerrainsBox->Enable(ResizeTerrains);

        OpenBox.DriveLetterBox->ChangeValue(DriveLetter);
        OpenBox.LanguageBox->ChangeValue(Language);
        OpenBox.TerrainsBox->ChangeValue(lexical_cast<std::string>(CustomTerrains));
        OpenBox.Path_DRS->SetPath(FolderDRS);
        OpenBox.Path_DRS2->SetPath(FolderDRS2);
        OpenBox.Path_DRS3->SetPath(Path1stDRS);
        OpenBox.Path_SLP->SetPath(PathSLP);
        OpenBox.Path_ModSLP->SetPath(PathModSLP);
        OpenBox.Path_Palettes->SetPath(PathPalettes);
        OpenBox.Path_PlayerColorPalette->SetPath(PathPlayerColorPalette);
        OpenBox.Path_CustomNames->SetPath(PathCustomNames);
        OpenBox.CheckBox_DRSPath->SetValue(UseDRS);
        OpenBox.CheckBox_DRSPath2->SetValue(UseMod);
        OpenBox.CheckBox_DRSPath3->SetValue(UseExtra);
        OpenBox.CheckBox_SlpPath->SetValue(UseLooseSLP);
        OpenBox.CheckBox_ModSlpPath->SetValue(UseLooseModSLP);

        if((argPath).size() > 3)
        {
            OpenBox.ForceDat = true;
            OpenBox.Radio_DatFileLocation->SetValue(true);
            OpenBox.Path_DatFileLocation->SetPath(argPath);
        }
        else
        {
            OpenBox.Radio_DatFileLocation->SetValue(DatUsed == 0);
            OpenBox.Path_DatFileLocation->SetPath(DatFileName);
        }

        OpenBox.CheckBox_LangFileLocation->SetValue(LangsUsed & 1);
        OpenBox.CheckBox_LangX1FileLocation->SetValue(LangsUsed & 2);
        OpenBox.CheckBox_LangX1P1FileLocation->SetValue(LangsUsed & 4);
        OpenBox.Path_LangFileLocation->SetPath(LangFileName);
        OpenBox.Path_LangX1FileLocation->SetPath(LangX1FileName);
        OpenBox.Path_LangX1P1FileLocation->SetPath(LangX1P1FileName);
        OpenBox.CheckBox_LangWrite->SetValue(WriteLangs);
        OpenBox.CheckBox_LangWriteToLatest->SetValue(LangWriteToLatest);

        bool load = OpenBox.ShowModal() == wxID_OK;

        GameVersion = OpenBox.ComboBox_GenieVer->GetSelection();
        DatUsed = OpenBox.Radio_DatFileLocation->GetValue() ? 0 : 3;

        DriveLetter = OpenBox.DriveLetterBox->GetValue();
        CustomFolder = OpenBox.Path_CustomDefault->GetPath();
        Language = OpenBox.LanguageBox->GetValue();
        CustomTerrains = lexical_cast<int>(OpenBox.TerrainsBox->GetValue());
        DatFileName = OpenBox.Path_DatFileLocation->GetPath();

        LangsUsed = OpenBox.CheckBox_LangFileLocation->IsChecked() ? LangsUsed | 1 : LangsUsed & ~1;
        LangsUsed = OpenBox.CheckBox_LangX1FileLocation->IsChecked() ? LangsUsed | 2 : LangsUsed & ~2;
        LangsUsed = OpenBox.CheckBox_LangX1P1FileLocation->IsChecked() ? LangsUsed | 4 : LangsUsed & ~4;

        LangFileName = OpenBox.Path_LangFileLocation->GetPath();
        LangX1FileName = OpenBox.Path_LangX1FileLocation->GetPath();
        LangX1P1FileName = OpenBox.Path_LangX1P1FileLocation->GetPath();
        FolderDRS = OpenBox.Path_DRS->GetPath();
        FolderDRS2 = OpenBox.Path_DRS2->GetPath();
        Path1stDRS = OpenBox.Path_DRS3->GetPath();
        PathSLP = OpenBox.Path_SLP->GetPath();
        PathModSLP = OpenBox.Path_ModSLP->GetPath();
        PathPalettes = OpenBox.Path_Palettes->GetPath();
        PathPlayerColorPalette = OpenBox.Path_PlayerColorPalette->GetPath();
        PathCustomNames = OpenBox.Path_CustomNames->GetPath();
        UseDRS = OpenBox.CheckBox_DRSPath->GetValue();
        UseMod = OpenBox.CheckBox_DRSPath2->GetValue();
        UseExtra = OpenBox.CheckBox_DRSPath3->GetValue();
        UseLooseSLP = OpenBox.CheckBox_SlpPath->GetValue();
        UseLooseModSLP = OpenBox.CheckBox_ModSlpPath->GetValue();
        WriteLangs = OpenBox.CheckBox_LangWrite->GetValue();
        LangWriteToLatest = OpenBox.CheckBox_LangWriteToLatest->GetValue();

        if(!load)
        {
            return;
        }
        popUp.unSaved = 0;
        ++popUp.loadedFileId;

        {
            wxConfig Config("", "", "AGE2\\ConfigWindow" + lexical_cast<std::string>(window_num + 1), "", wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
            Config.Write("DefaultFiles/DriveLetter", DriveLetter);
            Config.Write("DefaultFiles/CustomFolder", CustomFolder);
            Config.Write("DefaultFiles/Version", GameVersion);
            Config.Write("DefaultFiles/DatUsed", DatUsed);
            Config.Write("DefaultFiles/DatFilename", DatFileName);
            Config.Write("DefaultFiles/FolderDRS", FolderDRS);
            Config.Write("DefaultFiles/FolderDRS2", FolderDRS2);
            Config.Write("DefaultFiles/Path1stDRS", Path1stDRS);
            Config.Write("DefaultFiles/PathLooseSprites", PathSLP);
            Config.Write("DefaultFiles/PathLooseModSprites", PathModSLP);
            Config.Write("DefaultFiles/PathPalettes", PathPalettes);
            Config.Write("DefaultFiles/PathPlayerPalette", PathPlayerColorPalette);
            Config.Write("DefaultFiles/UseDRS", UseDRS);
            Config.Write("DefaultFiles/UseMod", UseMod);
            Config.Write("DefaultFiles/UseExtra", UseExtra);
            Config.Write("DefaultFiles/UseLooseSprites", UseLooseSLP);
            Config.Write("DefaultFiles/UseLooseModSprites", UseLooseModSLP);
            Config.Write("DefaultFiles/LangsUsed", LangsUsed);
            Config.Write("DefaultFiles/WriteLangs", WriteLangs);
            Config.Write("DefaultFiles/LangWriteToLatest", LangWriteToLatest);
            Config.Write("DefaultFiles/Language", Language);
            Config.Write("DefaultFiles/LangFilename", LangFileName);
            Config.Write("DefaultFiles/LangX1Filename", LangX1FileName);
            Config.Write("DefaultFiles/LangX1P1Filename", LangX1P1FileName);
            Config.Write("Misc/CustomTerrains", CustomTerrains);
        }

        if(!OpenBox.CheckBox_LangFileLocation->IsChecked()) LangFileName = "";
        if(!OpenBox.CheckBox_LangX1FileLocation->IsChecked()) LangX1FileName = "";
        if(!OpenBox.CheckBox_LangX1P1FileLocation->IsChecked()) LangX1P1FileName = "";

        wxArrayString latest;
        latest.Alloc(13);
        latest.Add(lexical_cast<std::string>(GameVersion));
        latest.Add(DatFileName);
        latest.Add(LangFileName);
        latest.Add(LangX1FileName);
        latest.Add(LangX1P1FileName);
        latest.Add(FolderDRS);
        latest.Add(FolderDRS2);
        latest.Add(Path1stDRS);
        latest.Add(PathSLP);
        latest.Add(PathModSLP);
        latest.Add(PathPalettes);
        latest.Add(PathPlayerColorPalette);
        latest.Add(PathCustomNames);
        int items = produceRecentValues(latest, OpenBox.RecentValues);
        wxConfig RecentOpen("", "", "AGE2\\RecentOpen", "", wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
        RecentOpen.Write("Recent/Items", items);
        RecentOpen.Write("Recent/Version", 5);
        for(int i=0; i < items; ++i)
        {
            wxString entry = "Recent" + wxString::Format("%04d", i + 1);
            RecentOpen.Write(entry + "/DatVersion", OpenBox.RecentValues[i][0]);
            RecentOpen.Write(entry + "/DatPath", OpenBox.RecentValues[i][1]);
            RecentOpen.Write(entry + "/Lang", OpenBox.RecentValues[i][2]);
            RecentOpen.Write(entry + "/LangX1", OpenBox.RecentValues[i][3]);
            RecentOpen.Write(entry + "/LangX1P1", OpenBox.RecentValues[i][4]);
            RecentOpen.Write(entry + "/PathDRS", OpenBox.RecentValues[i][5]);
            RecentOpen.Write(entry + "/PathDRS2", OpenBox.RecentValues[i][6]);
            RecentOpen.Write(entry + "/PathDRS3", OpenBox.RecentValues[i][7]);
            RecentOpen.Write(entry + "/LooseSLP", OpenBox.RecentValues[i][8]);
            RecentOpen.Write(entry + "/LooseModSLP", OpenBox.RecentValues[i][9]);
            RecentOpen.Write(entry + "/PathPalettes", OpenBox.RecentValues[i][10]);
            RecentOpen.Write(entry + "/PathPlayerPalette", OpenBox.RecentValues[i][11]);
            RecentOpen.Write(entry + "/PathCustomNames", OpenBox.RecentValues[i][12]);
        }
    }

    if (PathSLP.empty())
    {
        UseLooseSLP = false;
    }
    if (PathModSLP.empty())
    {
        UseLooseModSLP = false;
    }

    GenieVersion = EditorVersionAsGameVersion(GameVersion);
    LooseHD = false;

    delete dataset;
    dataset = 0;

    if(wxFileName(DatFileName).FileExists())
    {
        SetStatusText("Reading file...", 0);
        wxBusyCursor WaitCursor;

        dataset = new genie::DatFile();
        genie::Terrain::setTerrainCount(ResizeTerrains ? CustomTerrains : 0);
#ifndef NDEBUG
        dataset->setVerboseMode(true);
#endif
        dataset->setGameVersion(GenieVersion);
        try
        {
            dataset->load(DatFileName.c_str());
            // In case genieutils interpret another one.
            GenieVersion = dataset->getGameVersion();
        }
        catch(const std::ios_base::failure&)
        {
            wxMessageBox("Failed to load "+DatFileName);
            delete dataset;
            dataset = 0;
            return;
        }
    }
    else wxMessageBox("No file " + DatFileName);

    FillMissingFrames = GenieVersion > genie::GV_LatestTap && GenieVersion < genie::GV_C2 ||
        GenieVersion > genie::GV_LatestDE2 || GenieVersion < genie::GV_Tapsa;

    // txt language file
    LangTxt.clear();
    if(LangFileName.size() && 't' == LangFileName[LangFileName.size() - 1])
    {
        UseTXT = true;
        // Bad way of coding, please fix.
        if(GenieVersion == genie::GV_TC || GenieVersion == genie::GV_TCV || GenieVersion >= genie::GV_Cysion && GenieVersion <= genie::GV_LatestDE2)
        {
            LooseHD = true;
        }
        LoadTXT(LangFileName);
        if(LangX1FileName.size() && 't' == LangX1FileName[LangX1FileName.size() - 1])
        LoadTXT(LangX1FileName);
        if(LangX1P1FileName.size() && 't' == LangX1P1FileName[LangX1P1FileName.size() - 1])
        LoadTXT(LangX1P1FileName);
    }
    else
    {
        UseTXT = false;
        delete Lang;
        Lang = 0;
        delete LangX;
        LangX = 0;
        delete LangXP;
        LangXP = 0;

        if(LangsUsed & 1)
        {
            if(!wxFileName(LangFileName).FileExists())
            {
                wxMessageBox("No file " + LangFileName);
            }
            else if(sizeof(size_t) > 4 || WriteLangs)
            {
                Lang = new genie::LangFile();
                Lang->setDefaultCharset(LangCharset);
                try
                {
                    Lang->load(LangFileName.c_str());
                }
                catch(const std::ios_base::failure&)
                {
                    wxMessageBox("Failed to load "+LangFileName);
                    delete Lang;
                    Lang = 0;
                    return;
                }
            }
            else LanguageDLL[0] = LoadLibrary(LangFileName.c_str());
        }
        if(LangsUsed & 2)
        {
            if(!wxFileName(LangX1FileName).FileExists())
            {
                wxMessageBox("No file " + LangX1FileName);
            }
            else if(sizeof(size_t) > 4 || WriteLangs)
            {
                LangX = new genie::LangFile();
                LangX->setDefaultCharset(LangCharset);
                try
                {
                    LangX->load(LangX1FileName.c_str());
                }
                catch(const std::ios_base::failure&)
                {
                    wxMessageBox("Failed to load "+LangX1FileName);
                    delete LangX;
                    LangX = 0;
                    return;
                }
            }
            else LanguageDLL[1] = LoadLibrary(LangX1FileName.c_str());
        }
        if(LangsUsed & 4)
        {
            if(!wxFileName(LangX1P1FileName).FileExists())
            {
                wxMessageBox("No file " + LangX1P1FileName);
            }
            else if(sizeof(size_t) > 4 || WriteLangs)
            {
                LangXP = new genie::LangFile();
                LangXP->setDefaultCharset(LangCharset);
                try
                {
                    LangXP->load(LangX1P1FileName.c_str());
                }
                catch(const std::ios_base::failure&)
                {
                    wxMessageBox("Failed to load "+LangX1P1FileName);
                    delete LangXP;
                    LangXP = 0;
                    return;
                }
            }
            else LanguageDLL[2] = LoadLibrary(LangX1P1FileName.c_str());
        }
    }

    GetToolBar()->ToggleTool(eDRS, false);
    wxCommandEvent loadDRS(wxEVT_MENU, eDRS);
    loadDRS.SetInt(false);
    OnMenuOption(loadDRS);
    if(UseDRS)
    {
        soundfolders.Clear();
        if(LooseHD)
        {
            palettes.clear();
            bool gotcha = false;
            wxString folder = FolderDRS2, res;
            // Get a list of folders for sounds
            if(UseMod && !folder.empty())
            {
                gotcha = loadPalette(folder);
                wxString soundfolder = FolderDRS2;
                soundfolder.Replace("drs", "sound\\terrain", false);
                if(wxDir::Exists(soundfolder))
                soundfolders.Add(soundfolder + "\\");
                if(wxDir::Exists(folder + "\\gamedata_x2"))
                soundfolders.Add(folder + "\\gamedata_x2\\");
                if(wxDir::Exists(folder + "\\sounds"))
                soundfolders.Add(folder + "\\sounds\\");
                if(wxDir::Exists(folder + "\\interface"))
                soundfolders.Add(folder + "\\interface\\");
            }
            folder = FolderDRS;
            if(!folder.empty())
            {
                if(!gotcha) loadPalette(folder);
                wxString soundfolder = FolderDRS;
                soundfolder.Replace("drs", "sound\\terrain", false);
                if(wxDir::Exists(soundfolder))
                soundfolders.Add(soundfolder + "\\");
                if(wxDir::Exists(folder + "\\gamedata_x2"))
                soundfolders.Add(folder + "\\gamedata_x2\\");
                if(wxDir::Exists(folder + "\\sounds"))
                soundfolders.Add(folder + "\\sounds\\");
                if(wxDir::Exists(folder + "\\interface"))
                soundfolders.Add(folder + "\\interface\\");

                // Load extra palettes
                folder.Replace("drs", "dat", false);
                wxDir dir(folder);
                if(dir.IsOpened())
                {
                    bool found = dir.GetFirst(&res, "*.pal");
                    while(found)
                    {
                        genie::PalFile pal;
                        try
                        {
                            pal.load((folder + "\\" + res).c_str());
                            palettes.push_back(pal.getColors());
                        }
                        catch(const std::ios_base::failure&){}
                        found = dir.GetNext(&res);
                    }
                }
                else wxMessageBox("Cannot open folder " + folder);
            }
        }
        else
        {
            wxString folder = FolderDRS2;
            if(UseMod && !folder.empty())
            {
                folder.Replace("data", GenieVersion < genie::GV_AoKE3 ? "sound" : "sound\\terrain", false);
                if(wxDir::Exists(folder))
                soundfolders.Add(folder + "\\");
            }
            folder = FolderDRS;
            if(!folder.empty())
            {
                folder.Replace("data", GenieVersion < genie::GV_AoKE3 ? "sound" : "sound\\terrain", false);
                if(wxDir::Exists(folder))
                soundfolders.Add(folder + "\\");
            }

            GetToolBar()->ToggleTool(eDRS, true);
            loadDRS.SetInt(true);
            OnMenuOption(loadDRS);
        }
    }
    // Load custom palettes
    GG::LoadPalettes(palettes, PathPalettes);
    GG::LoadPlayerPalette(pc_palettes, PathPlayerColorPalette);

    if(dataset)
    {   // Without these, nothing can be edited.
        SetStatusText("Listing...", 0);
        wxBusyCursor WaitCursor;

        // No research gaia fix. Not needed due to better auto copy. Noobs could use manual auto copy!
        if(dataset->Civs.size() > 1)
        {
            for(size_t loop = dataset->Civs.front().Units.size(); loop--> 0;)
                dataset->Civs.front().Units[loop].Enabled = dataset->Civs[1].Units[loop].Enabled;
        }
        // Pointers contain useless data, which the game overrides anyway.
        // ID and pointer fixes.
        for(size_t loop = dataset->Civs.size(); loop--> 0;)
        {
            for(size_t loop2 = dataset->Civs[loop].Units.size(); loop2--> 0;)
            if(dataset->Civs[loop].UnitPointers[loop2] != 0)
            {
                dataset->Civs[loop].UnitPointers[loop2] = 1;
                dataset->Civs[loop].Units[loop2].ID = loop2;
                if (GenieVersion >= genie::GV_AoE)
                {
                    dataset->Civs[loop].Units[loop2].CopyID = loop2;
                }
                if (GenieVersion >= genie::GV_AoK)
                {
                    dataset->Civs[loop].Units[loop2].BaseID = loop2;
                }
                if (dataset->Civs[loop].Units[loop2].Type >= 40 && dataset->Civs[loop].Units[loop2].Type <= 80)
                {
                    if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
                    {
                        auto it = std::find_if(dataset->Civs[loop].Units[loop2].Bird.DropSites.rbegin(), dataset->Civs[loop].Units[loop2].Bird.DropSites.rend(), [](int i) { return i != -1; });
                        if (it != dataset->Civs[loop].Units[loop2].Bird.DropSites.rend())
                        {
                            size_t size = dataset->Civs[loop].Units[loop2].Bird.DropSites.size() - (it - dataset->Civs[loop].Units[loop2].Bird.DropSites.rbegin());
                            dataset->Civs[loop].Units[loop2].Bird.DropSites.resize(size);
                        }
                        else
                        {
                            dataset->Civs[loop].Units[loop2].Bird.DropSites.clear();
                        }
                    }
                    else if (GenieVersion < genie::GV_AoK)
                    {
                        for (size_t loop3 = dataset->Civs[loop].Units[loop2].Bird.TaskList.size(); loop3-- > 0;)
                        {
                            dataset->Civs[loop].Units[loop2].Bird.TaskList[loop3].ID = loop3;
                        }
                    }
                }
            }
        }
        for(size_t loop = dataset->PlayerColours.size(); loop--> 0;)
        {
            dataset->PlayerColours[loop].ID = loop;
        }
        for(size_t loop = dataset->Sounds.size(); loop--> 0;)
        {
            dataset->Sounds[loop].ID = loop;
        }
        if(GenieVersion >= genie::GV_SWGB)
        for(size_t loop = dataset->UnitLines.size(); loop--> 0;)
        {
            dataset->UnitLines[loop].ID = loop;
        }
        if(GenieVersion >= genie::GV_AoE)
        for(size_t loop = dataset->Graphics.size(); loop--> 0;)
        {
            if(dataset->GraphicPointers[loop] != 0)
            {
                dataset->GraphicPointers[loop] = 1;
                dataset->Graphics[loop].ID = loop;
            }
        }
        for(size_t loop = dataset->TerrainRestrictions.size(); loop--> 0;)
        {
            if(dataset->FloatPtrTerrainTables[loop] != 0)
            dataset->FloatPtrTerrainTables[loop] = 1;
            if(GenieVersion >= genie::GV_AoKA)
            if(dataset->TerrainPassGraphicPointers[loop] != 0)
            dataset->TerrainPassGraphicPointers[loop] = 1;
        }

        How2List = ListMode::SEARCH;
        FillListsBasedOnGameVersion();
        SetStatusText(lexical_cast<std::string>(dataset->FileVersion), 4);
        DataOpened = true;
        TabBar_Main->Freeze();
        //OnGameVersionChange();
        wxCommandEvent event(wxEVT_MENU, eVasili);
        OnMenuOption(event);
        event.SetId(eUnknown);
        event.SetInt(GenieVersion < genie::GV_SWGB ? true : ShowUnknowns);
        OnMenuOption(event);
        GetToolBar()->ToggleTool(eUnknown, ShowUnknowns);
        GetToolBar()->EnableTool(eUnknown, GenieVersion >= genie::GV_SWGB);

        LoadLists();
        TabBar_Main->Thaw();
    }
    SetStatusText("", 0);

    SkipOpenDialog = false;
    if(AutoBackups) SaveBackup();
}

void AGE_Frame::OnGameVersionChange()
{
    if(DataOpened)  // Hiding stuff according to game version should be here.
    {
        // Some general tab handling
        for(size_t loop = dataset->TerrainBlock.getSomethingSize(); loop < General_Something.size(); ++loop)
        General_Something[loop]->Show(false);
        for(size_t loop = dataset->TerrainBlock.getBytesSize(); loop < General_SomeBytes.size(); ++loop)
        General_SomeBytes[loop]->Show(false);
        if(ShowUnknowns)
        {
            for(size_t loop = 0; loop < dataset->TerrainBlock.getSomethingSize(); ++loop)
            General_Something[loop]->Show(true);
            for(size_t loop = 0; loop < dataset->TerrainBlock.getBytesSize(); ++loop)
            General_SomeBytes[loop]->Show(true);
        }

        // Test ->
        bool show = (GenieVersion >= genie::GV_TEST) ? true : false;
        Sounds_CacheTime_Holder->Show(show);
        if(show)
        {
            SoundItems_Resource->SetCastType(CLong);
            Graphics_SLP->SetCastType(CLong);
        }
        else
        {
            SoundItems_Resource->SetCastType(CShort);
            Graphics_SLP->SetCastType(CShort);
        }

        // Mickey ->
        show = (GenieVersion >= genie::GV_MIK) ? true : false;
        Civs_TechTree_Holder->Show(show);
        Units_PlacementSideTerrain_Holder->Show(show);
        Borders_BorderStyle_Holder->Show(GenieVersion != genie::GV_MIK);

        // Matt ->
        show = (GenieVersion >= genie::GV_MATT) ? true : false;
        Units_LanguageDLLCreation_Holder->Show(show);
        Research_LangDLLArea_Holder->Show(show);

        // AoE Beta ->
        show = (GenieVersion >= genie::GV_AoEB) ? true : false;
        Research_PointerArea_Holder->Show(show);
        Research_HotKey_Holder->Show(show);
        Research_DLL_LanguageDLLHelp->Show(show);
        Research_DLL_LanguageDLLName2->Show(show);
        Terrains_SLP_Holder->Show(show);
        Borders_SLP_Holder->Show(show);
        Units_LanguageDLLHelp_Holder->Show(show);
        Units_LanguageDLLHotKeyText_Holder->Show(show);
        Units_HotKey_Holder->Show(show);
        Units_LangHotKey_Holder->Show(show);
        Units_DLL_LanguageHelp->Show(show);
        Units_DLL_LanguageHKText->Show(show);
        Units_Recyclable_Holder->Show(show);
        Units_SelectionEffect_Holder->Show(show);
        Units_EditorSelectionColour_Holder->Show(show);
        Units_SelectionRadius_Holder->Show(show);
        Units_MoveSound_Holder->Show(show);
        Units_DisplayedPierceArmour_Holder->Show(show);
        Units_DisplayedMeleeArmour_Holder->Show(show);
        Units_DisplayedAttack_Holder->Show(show);
        Units_DisplayedRange_Holder->Show(show);
        Units_DisplayedReloadTime_Holder->Show(show);
        Units_TrackAsResource_Holder->Show(show);
        Units_CreateDoppelgangerOnDeath_Holder->Show(show);
        Units_ResourceGroup_Holder->Show(show);

        // AoE ->
        show = (GenieVersion >= genie::GV_AoE) ? true : false;
        Units_CopyID_Holder->Show(show);
        General_TileSizesPadding_Holder->Show(show);
        for(size_t loop = 2; loop < General_TileSizes.size(); loop += 3)
        General_TileSizes[loop]->Show(show);

        // AoK E3 ->
        show = (GenieVersion >= genie::GV_AoKE3) ? true : false;
        Colors_PlayerPalette_Holder->Show(show);
        Colors_OutlineColor_Holder->Show(show);
        Colors_SelectionColor1_Holder->Show(show);
        Colors_SelectionColor2_Holder->Show(show);
        Colors_ReferenceID_Holder->Show(show);
        SoundItems_Civ_Holder->Show(show);
        SoundFile_CopyCivToCiv->Show(show);
        SourceCiv_Holder->Show(show);
        TargetCiv_Holder->Show(show);
        SoundItems_IconSet_Holder->Show(show);
        Units_DamageSound_Holder->Show(show);
        Units_OcclusionMode_Holder->Show(show);
        Units_CreatableType_Holder->Show(show);
        Units_MissileCount_Holder->Show(show);
        Units_MissileDuplicationCount_Holder->Show(show);
        Units_AttackMissileDuplicationSpawning_Holder->Show(show);
        Units_AttackMissileDuplicationUnit_Holder->Show(show);
        Units_ChargingGraphic_Holder->Show(show);
        Units_ChargingMode_Holder->Show(show);
        Units_AnnexUnit1_Holder->Show(show);
        Units_AnnexUnitMisplacement1_Holder->Show(show);
        Units_TransformUnit_Holder->Show(show);
        Units_TransformSound_Holder->Show(show);
        Units_GarrisonType_Text->Show(show);
        Units_GarrisonType_Holder->Show(show);
        Units_GarrisonHealRate_Text->Show(show);
        Units_GarrisonHealRate->Show(show);
        Units_PileUnit_Holder->Show(show);
        Units_LootSwitch_Holder->Show(show);
        Colors_MinimapColor2_Holder->Show(show);
        Colors_MinimapColor3_Holder->Show(show);
        Units_RearAttackModifier_Holder->Show(show);
        Units_FlankAttackModifier_Holder->Show(show);
        Units_CanBurn_Holder->Show(show);
        Units_GarrisonRepairRate_Holder->Show(show);
        Colors_Name_Holder->Show(!show);
        Colors_ResourceID_Holder->Show(!show);
        Colors_Type_Holder->Show(!show);
        if(show)
        {
            Colors_ID->SetCastType(CLong);
            Colors_MinimapColor->SetCastType(CLong);
        }
        else
        {
            Colors_ID->SetCastType(CShort);
            Colors_MinimapColor->SetCastType(CUByte);
        }

        // AoK Alfa ->
        show = (GenieVersion >= genie::GV_AoKA) ? true : false;
        for(size_t loop = 4; loop < 6; ++loop)
        {
            Research_RequiredTechs[loop]->Show(show);
            Research_RequiredTechs_ComboBox[loop]->Show(show);
        }
        Units_ObstructionType_Holder->Show(show);
        Units_ObstructionClass_Holder->Show(show);
        Units_BaseID_Holder->Show(show);
        Units_HeadUnit_Holder->Show(show);
        TerRestrict_Graphics_Holder->Show(show);
        TechTrees_Main->Show(show);
        TabBar_Main->SetPageText(2, show ? "Tech Trees" : "AoK+ only");

        // AoK Beta ->
        show = (GenieVersion >= genie::GV_AoKB) ? true : false;
        Units_HeroMode_Holder->Show(show);
        Units_GarrisonGraphic_Holder->Show(show);
        Units_StandingGraphic[1]->Show(show);
        Units_StandingGraphic_ComboBox[1]->Show(show);
        Units_AccuracyDispersion_Holder->Show(show);
        Units_RotationAngles_Holder->Show(show);
        TechTrees_Ages_Buildings.Add->Enable(show);
        TechTrees_Ages_Units.Add->Enable(show);
        TechTrees_Ages_Researches.Add->Enable(show);
        TechTrees_Ages_Buildings.Insert->Enable(show);
        TechTrees_Ages_Units.Insert->Enable(show);
        TechTrees_Ages_Researches.Insert->Enable(show);
        TechTrees_Ages_Buildings.Delete->Enable(show);
        TechTrees_Ages_Units.Delete->Enable(show);
        TechTrees_Ages_Researches.Delete->Enable(show);
        TechTrees_Ages_Buildings.PasteInsert->Enable(show);
        TechTrees_Ages_Units.PasteInsert->Enable(show);
        TechTrees_Ages_Researches.PasteInsert->Enable(show);
        TechTrees_Buildings_Buildings.Add->Enable(show);
        TechTrees_Buildings_Units.Add->Enable(show);
        TechTrees_Buildings_Researches.Add->Enable(show);
        TechTrees_Buildings_Buildings.Insert->Enable(show);
        TechTrees_Buildings_Units.Insert->Enable(show);
        TechTrees_Buildings_Researches.Insert->Enable(show);
        TechTrees_Buildings_Buildings.Delete->Enable(show);
        TechTrees_Buildings_Units.Delete->Enable(show);
        TechTrees_Buildings_Researches.Delete->Enable(show);
        TechTrees_Buildings_Buildings.PasteInsert->Enable(show);
        TechTrees_Buildings_Units.PasteInsert->Enable(show);
        TechTrees_Buildings_Researches.PasteInsert->Enable(show);
        TechTrees_Units_Units.Add->Enable(show);
        TechTrees_Units_Units.Insert->Enable(show);
        TechTrees_Units_Units.Delete->Enable(show);
        TechTrees_Units_Units.PasteInsert->Enable(show);
        TechTrees_Units_Units.CopyAllToSelected->Enable(show);
        TechTrees_Researches_Buildings.Add->Enable(show);
        TechTrees_Researches_Units.Add->Enable(show);
        TechTrees_Researches_Researches.Add->Enable(show);
        TechTrees_Researches_Buildings.Insert->Enable(show);
        TechTrees_Researches_Units.Insert->Enable(show);
        TechTrees_Researches_Researches.Insert->Enable(show);
        TechTrees_Researches_Buildings.Delete->Enable(show);
        TechTrees_Researches_Units.Delete->Enable(show);
        TechTrees_Researches_Researches.Delete->Enable(show);
        TechTrees_Researches_Buildings.PasteInsert->Enable(show);
        TechTrees_Researches_Units.PasteInsert->Enable(show);
        TechTrees_Researches_Researches.PasteInsert->Enable(show);
        Terrains_BlendPriority_Holder->Show(show);
        Terrains_BlendType_Holder->Show(show);
        Civs_TeamBonus_Holder->Show(show);
        Research_Civ_Holder->Show(show);
        Research_FullTechMode_Holder->Show(show);
        Graphics_EditorFlag_Holder->Show(show);

        // AoK ->
        show = (GenieVersion >= genie::GV_AoK) ? true : false;
        Units_Exists_Holder->Show(show);
        Units_Tasks_Add->Enable(show);
        Units_Disabled_Holder->Show(show);

        // TC ->
        show = (GenieVersion >= genie::GV_TC) ? true : false;
        Units_SnowGraphicID_Holder->Show(show);
        Units_A2_Grid->Show(show);

        if(show) // TC ->
        {
            Units_BaseArmor->SetCastType(CShort);
        }
        else // <- AoK
        {
            Units_BaseArmor->SetCastType(CUByte);
        }

        // SWGB ->
        show = (GenieVersion >= genie::GV_SWGB) ? true : false;
        Research_Name_Holder[1]->Show(show);
        Civs_Name_Holder[1]->Show(show);
        Units_Name2_Holder->Show(show);
        Units_Unitline_Holder->Show(show);
        Units_MinTechLevel_Holder->Show(show);
        UnitLines_Main->Show(show);
        TabBar_Main->SetPageText(5, show ? "Unitlines" : "SW only");
        Civs_SUnknown1_Holder->Show(show);
        General_Variables1_Holder->Show(show && ShowUnknowns);
        Terrains_Phantom_Holder->Show(!show);

        bool appear = GenieVersion >= genie::GV_Tapsa && GenieVersion <= genie::GV_LatestTap;
        bool emerge = GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2;
        if(appear || emerge)
        {
            Graphics_Name->setMaxChars(maxStringlength);
            Graphics_FileName->setMaxChars(maxStringlength);
            SoundItems_Name->setMaxChars(maxStringlength);
            Terrains_Name->setMaxChars(maxStringlength);
            Terrains_FileName->setMaxChars(maxStringlength);
            // Fixed size elsewhere
            Techs_Name->setMaxChars(maxStringlength);
            Civs_Name[0]->setMaxChars(maxStringlength);
        }
        if(appear)
        {
            Terrains_BlendPriority_Holder->Show(true);
            Terrains_BlendType_Holder->Show(true);
            TerRestrict_Graphics_Holder->Show(true);
            Units_ObstructionType_Holder->Show(true);
            Units_ObstructionClass_Holder->Show(true);
            Terrains_BlendPriority->SetCastType(CShort);
            Terrains_BlendType->SetCastType(CShort);
            Units_BaseArmor->SetCastType(CShort);
            TerRestrict_Amount->SetCastType(CFloat);
        }
        else
        {
            if(!emerge)
            {
                Techs_Name->setMaxChars(31);
                Civs_Name[0]->setMaxChars(20);
            }
            if(show) // SWGB ->
            {
                Graphics_Name->setMaxChars(25);
                Graphics_FileName->setMaxChars(25);
                SoundItems_Name->setMaxChars(27);
                Terrains_Name->setMaxChars(17);
                Terrains_FileName->setMaxChars(17);
                TerRestrict_Amount->SetCastType(CFloat);
            }
            else // <- TC
            {
                if(!emerge)
                {
                    Graphics_Name->setMaxChars(21);
                    Graphics_FileName->setMaxChars(13);
                    SoundItems_Name->setMaxChars(13);
                    Terrains_Name->setMaxChars(13);
                    Terrains_FileName->setMaxChars(13);
                }
                TerRestrict_Amount->SetCastType(CLong);
            }
            Terrains_BlendPriority->SetCastType(CLong);
            Terrains_BlendType->SetCastType(CLong);
        }
        if(emerge)
        {
            Units_LanguageDLLName->SetCastType(CLong);
            Units_LanguageDLLCreation->SetCastType(CLong);
            Research_LangDLLName->SetCastType(CLong);
            Research_LangDLLDescription->SetCastType(CLong);
        }
        else
        {
            Units_LanguageDLLName->SetCastType(CShort);
            Units_LanguageDLLCreation->SetCastType(CShort);
            Research_LangDLLName->SetCastType(CShort);
            Research_LangDLLDescription->SetCastType(CShort);
        }
        Graphics_FirstFrame_Holder->Show(appear);
        Units_TelemetryID_Holder->Show(appear);
        Units_BloodUnitID_Holder->Show(appear || emerge);
        Sounds_TotalProbability_Holder->Show(appear || emerge);
        Sounds_TotalProbability_Text->Show(appear || emerge);
        Terrains_IsWater_Holder->Show(appear || emerge);
        Terrains_HideInEditor_Holder->Show(appear || emerge);
        Terrains_StringID_Holder->Show(appear || emerge);
        Terrains_OverlayMaskName->Show(emerge);
        Units_DestructionGraphicID_Holder->Show(emerge);
        Units_DestructionRubbleGraphicID_Holder->Show(emerge);
        Units_SpawningGraphic_Holder->Show(emerge);
        Units_UpgradeGraphic_Holder->Show(emerge);
        Units_HeroGlowGraphic_Holder->Show(emerge);
        Units_ResearchingGraphic_Holder->Show(emerge);
        Units_ResearchCompletedGraphic_Holder->Show(emerge);
        Units_MinCollisionSizeMultiplier_Holder->Show(emerge);
        Units_WwiseTrainSound->Show(emerge);
        Units_WwiseDamageSound->Show(emerge);
        Units_WwiseSelectionSound->Show(emerge);
        Units_WwiseDyingSound->Show(emerge);
        Units_WwiseAttackSound->Show(emerge);
        Units_WwiseMoveSound->Show(emerge);
        Units_WwiseTransformSound->Show(emerge);
        Units_WwiseConstructionSound->Show(emerge);
        Units_DropSites_Buttons_Upper->Show(emerge);
        Units_DropSites_PasteInsert->Show(emerge);
        Units_BonusDamageResistance_Holder->Show(emerge);
        Units_Charge_Grid->Show(emerge);
        Units_ConversionChanceMod->Show(emerge);
        Units_ConversionChanceMod_Text->Show(emerge);
        Units_MaxConversionTimeMod->Show(emerge);
        Units_MaxConversionTimeMod_Text->Show(emerge);
        Units_MinConversionTimeMod->Show(emerge);
        Units_MinConversionTimeMod_Text->Show(emerge);
        Units_BlastDamage->Show(emerge);
        Units_BlastDamage_Text->Show(emerge);
        Tasks_WwiseResourceGatheringSound->Show(emerge);
        Tasks_WwiseResourceDepositSound->Show(emerge);
        Graphics_ParticleEffectName_Text->Show(emerge);
        Graphics_ParticleEffectName_Holder->Show(emerge);
        Graphics_WwiseSoundID->Show(emerge);
        Graphics_WwiseAngleSoundID[0]->Show(emerge);
        Graphics_WwiseAngleSoundID[1]->Show(emerge);
        Graphics_WwiseAngleSoundID[2]->Show(emerge);
        Terrains_WwiseSoundID->Show(emerge);
        Terrains_SoundStopID_Holder->Show(emerge);
        Terrains_Borders->Show(!emerge);
        Terrains_OverlayMaskName_Text->Show(emerge);
        Terrains_OverlayMaskName_Holder->Show(emerge);
        Terrains_TerrainUnitMaskedDensity_Holder->Show(emerge);
        Terrains_GreatSpace->GetItem(Terrains_SpaceLeft)->SetFlag(emerge ? 0 : wxEXPAND);
        Terrains_GreatSpace->GetItem(Terrains_SpaceLeft)->SetProportion(emerge ? 0 : 3);
        Borders_DataArea->Show(!emerge);
        Borders_UsedCountHolder->Show(!emerge);
        Borders_Copy->Show(!emerge);
        Borders_Paste->Show(!emerge);
        Borders_MoveUp->Show(emerge);
        Borders_MoveDown->Show(emerge);
        Techs_Repeatable_Holder->Show(emerge);
    }

//  Every data area should be layouted.
    Civs_Main->Layout();
    Units_Main->Layout();
    Research_Main->Layout();
    Techs_Main->Layout();
    TechTrees_Main->Layout();
    TechTrees_TabAges->Layout();
    TechTrees_TabBuildings->Layout();
    TechTrees_TabUnits->Layout();
    TechTrees_TabResearches->Layout();
    Graphics_Main->Layout();
    Terrains_Main->Layout();
    TerRestrict_Main->Layout();
    Sounds_Main->Layout();
    Colors_Main->Layout();
    UnitLines_Main->Layout();
    Borders_Main->Layout();
    General_Main->Layout();
    Unknown_Main->Layout();
    Refresh(); // Does this refresh non-visible tabs?
}

void AGE_Frame::OnSave(wxCommandEvent&)
{
    SaveDialog SaveBox(this, font);
    auto OnSyncSaveWithOpen = [this, &SaveBox](wxCommandEvent &event)
    {
        if (event.IsChecked())
        {
            SaveBox.ComboBox_GenieVer->SetSelection(GameVersion);
            SaveBox.Path_DatFileLocation->SetPath(DatFileName);
            SaveBox.Path_LangFileLocation->SetPath(LangFileName);
            SaveBox.Path_LangX1FileLocation->SetPath(LangX1FileName);
            SaveBox.Path_LangX1P1FileLocation->SetPath(LangX1P1FileName);
        }
    };
    SaveBox.SyncWithReadPaths->Bind(wxEVT_CHECKBOX, OnSyncSaveWithOpen);

    int RecentItems, RecentVersion;
    {
        wxConfig RecentSave("", "", "AGE2\\RecentSave", "", wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
        RecentSave.Read("Recent/Items", &RecentItems, 0);
        RecentSave.Read("Recent/Version", &RecentVersion, 1);
        RecentItems = std::min(30, RecentItems);
        SaveBox.RecentValues.resize(RecentItems);
        for(int i=0; i < RecentItems; ++i)
        {
            SaveBox.RecentValues[i].Alloc(5);
            wxString temp, entry = "Recent" + wxString::Format("%04d", i + 1);
            RecentSave.Read(entry + "/DatVersion", &temp, "-1");
            if (RecentVersion < 2 && lexical_cast<int>(temp) > EV_TC)
            {
                temp = "-1";
            }
            if (RecentVersion < 4)
            {
                int version = lexical_cast<int>(temp);
                if (version > EV_EF)
                {
                    ++version;
                    temp = lexical_cast<std::string>(version);
                }
            }
            SaveBox.RecentValues[i].Add(temp);
            RecentSave.Read(entry + "/DatPath", &temp, wxEmptyString); SaveBox.RecentValues[i].Add(temp);
            RecentSave.Read(entry + "/Lang", &temp, wxEmptyString); SaveBox.RecentValues[i].Add(temp);
            RecentSave.Read(entry + "/LangX1", &temp, wxEmptyString); SaveBox.RecentValues[i].Add(temp);
            RecentSave.Read(entry + "/LangX1P1", &temp, wxEmptyString); SaveBox.RecentValues[i].Add(temp);
        }
    }
    if (SaveBox.RecentValues.size())
    {
        for (int i = 0; i < RecentItems; ++i)
        {
            SaveBox.CheckBox_Recent->Append(FixEditorVersion(SaveBox.RecentValues[i][0]) + SaveBox.RecentValues[i][1]);
        }
    }
    else
    {
        SaveBox.CheckBox_Recent->Append("Happy Modding!");
    }
    SaveBox.CheckBox_Recent->SetSelection(0);

    SaveBox.Path_DatFileLocation->SetFocus();
    SaveBox.DriveLetterBox->ChangeValue(DriveLetter);
    SaveBox.Path_CustomDefault->SetPath(CustomFolder);
    SaveBox.LanguageBox->ChangeValue(Language);
    SaveBox.CheckBox_LangWrite->Enable(WriteLangs);
    SaveBox.CheckBox_LangWrite->SetValue(WriteLangs);

    if((argPath).size() > 3)
    {
        SaveBox.ForceDat = true;
        SaveBox.Radio_DatFileLocation->SetValue(true);
        SaveBox.Path_DatFileLocation->SetPath(argPath);
    }
    else
    {
        SaveBox.Radio_DatFileLocation->SetValue(SaveDat);
        SaveBox.Path_DatFileLocation->SetPath(SaveDatFileName);
    }

    SaveBox.CheckBox_LangFileLocation->SetValue(LangsUsed & 1);
    SaveBox.CheckBox_LangX1FileLocation->SetValue(LangsUsed & 2);
    SaveBox.CheckBox_LangX1P1FileLocation->SetValue(LangsUsed & 4);
    if(SyncSaveWithOpen)
    {
        SaveBox.SyncWithReadPaths->SetValue(true); // I wish this call was enough.
        wxCommandEvent sync(wxEVT_CHECKBOX);
        sync.SetInt(true);
        OnSyncSaveWithOpen(sync);
    }
    else
    {
        if (RecentVersion >= 2)
        {
            SaveBox.ComboBox_GenieVer->SetSelection(SaveGameVersion);
        }
        else
        {
            SaveBox.ComboBox_GenieVer->SetSelection(-1);
        }
        SaveBox.Path_LangFileLocation->SetPath(SaveLangFileName);
        SaveBox.Path_LangX1FileLocation->SetPath(SaveLangX1FileName);
        SaveBox.Path_LangX1P1FileLocation->SetPath(SaveLangX1P1FileName);
    }

    bool save = SaveBox.ShowModal() == wxID_OK;

    SaveGameVersion = SaveBox.ComboBox_GenieVer->GetSelection();
    SaveDat = SaveBox.Radio_DatFileLocation->IsChecked();
    SaveLangs = SaveBox.CheckBox_LangWrite->IsChecked();
    SaveDatFileName = SaveBox.Path_DatFileLocation->GetPath();
    SaveLangFileName = SaveBox.Path_LangFileLocation->GetPath();
    SaveLangX1FileName = SaveBox.Path_LangX1FileLocation->GetPath();
    SaveLangX1P1FileName = SaveBox.Path_LangX1P1FileLocation->GetPath();
    SyncSaveWithOpen = DatFileName == SaveDatFileName && LangFileName == SaveLangFileName && LangX1FileName == SaveLangX1FileName && LangX1P1FileName == SaveLangX1P1FileName;

    if (SaveGameVersion >= EV_Tapsa && SaveDatFileName.Contains("steamapps"))
    {
        int answer = wxMessageBox("Saving into steamapps folder may not work in the game.\nYou should create a mod folder tree and save into it.",
            "Warning", wxICON_WARNING | wxCANCEL | wxCANCEL_DEFAULT | wxOK);
        if (answer == wxCANCEL)
        {
            return;
        }
    }

    if (!save)
    {
        return;
    }

    {
        wxConfig Config("", "", "AGE2\\ConfigWindow"+lexical_cast<std::string>(window_num + 1), "", wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
        Config.Write("DefaultFiles/SyncSaveWithOpen", SyncSaveWithOpen);
        Config.Write("DefaultFiles/SaveVersion", SaveGameVersion);
        Config.Write("DefaultFiles/SaveDatFilename", SaveDatFileName);
        Config.Write("DefaultFiles/SaveLangs", SaveLangs);
        Config.Write("DefaultFiles/SaveLangFilename", SaveLangFileName);
        Config.Write("DefaultFiles/SaveLangX1Filename", SaveLangX1FileName);
        Config.Write("DefaultFiles/SaveLangX1P1Filename", SaveLangX1P1FileName);
        Config.Write("DefaultFiles/SaveDat", SaveDat);
        Config.Write("Misc/CustomTerrains", CustomTerrains);
    }

    if (!SaveBox.CheckBox_LangFileLocation->IsChecked())
    {
        SaveLangFileName = "";
    }
    if (!SaveBox.CheckBox_LangX1FileLocation->IsChecked())
    {
        SaveLangX1FileName = "";
    }
    if (!SaveBox.CheckBox_LangX1P1FileLocation->IsChecked())
    {
        SaveLangX1P1FileName = "";
    }

    {
        wxArrayString latest;
        latest.Alloc(5);
        latest.Add(lexical_cast<std::string>(SaveGameVersion));
        latest.Add(SaveDatFileName);
        latest.Add(SaveLangFileName);
        latest.Add(SaveLangX1FileName);
        latest.Add(SaveLangX1P1FileName);
        RecentItems = produceRecentValues(latest, SaveBox.RecentValues);
        wxConfig RecentSave("", "", "AGE2\\RecentSave", "", wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
        RecentSave.Write("Recent/Items", RecentItems);
        RecentSave.Write("Recent/Version", 4);
        for(int i=0; i < RecentItems; ++i)
        {
            wxString entry = "Recent" + wxString::Format("%04d", i + 1);
            RecentSave.Write(entry + "/DatVersion", SaveBox.RecentValues[i][0]);
            RecentSave.Write(entry + "/DatPath", SaveBox.RecentValues[i][1]);
            RecentSave.Write(entry + "/Lang", SaveBox.RecentValues[i][2]);
            RecentSave.Write(entry + "/LangX1", SaveBox.RecentValues[i][3]);
            RecentSave.Write(entry + "/LangX1P1", SaveBox.RecentValues[i][4]);
        }
    }

    if(SaveDat)
    {
        SetStatusText("Saving dat file...", 0);
        wxBusyCursor WaitCursor;
        // Workaround for multiple windows.
        genie::Terrain::setTerrainCount(ResizeTerrains ? CustomTerrains : 0);

        // Can save as different game version
        genie::GameVersion SaveGenieVersion = EditorVersionAsGameVersion(SaveGameVersion);
        if(GenieVersion != SaveGenieVersion || genie::GV_Tapsa == GenieVersion || genie::GV_C2 == GenieVersion)
        {
            if(GenieVersion <= genie::GV_LatestDE2 && genie::GV_C2 <= GenieVersion)
            {
                if(GenieVersion < genie::GV_C15)
                {
                    // Thanks Maimi.
                    for(size_t civ = 0; civ < dataset->Civs.size(); ++civ)
                    {
                        for(size_t unit = 0; unit < dataset->UnitHeaders.size(); ++unit)
                        {
                            if(dataset->Civs[civ].Units[unit].Type >= 40)
                            {
                                dataset->Civs[civ].Units[unit].Bird.TaskList = dataset->UnitHeaders[unit].TaskList;
                            }
                        }
                    }
                }
                GenieVersion = genie::GV_LatestDE2;
                // Remember to update this version number!
                dataset->FileVersion = "VER 7.8";
            }
            else if(GenieVersion <= genie::GV_LatestTap && genie::GV_Tapsa <= GenieVersion)
            {
                GenieVersion = genie::GV_LatestTap;
                dataset->FileVersion = "VER 4.5";
            }
            else
            {
                GenieVersion = SaveGenieVersion;
                wxMessageBox("Saving with different game version!");
            }
            dataset->setGameVersion(GenieVersion);
        }

        if (GenieVersion != genie::GV_TCV && GenieVersion != genie::GV_CCV && GenieVersion != genie::GV_CCV2)
        {
            // A fix that should never be needed
            int TerrainsInData = dataset->TerrainBlock.Terrains.size();
            int BordersInTerrains = 0;
            for (int terrain = 0; terrain < TerrainsInData; ++terrain)
            {
                BordersInTerrains += dataset->TerrainBlock.Terrains[terrain].Borders.size();
            }
            BordersInTerrains /= TerrainsInData;
            if (TerrainsInData != BordersInTerrains)
            {
                wxString viesti = "Send file to Tapsa for repair!\nTerrains: " + lexical_cast<std::string>(TerrainsInData);
                viesti += "\nBorders: " + lexical_cast<std::string>(BordersInTerrains);
                viesti += "\nLoaded game version: " + lexical_cast<std::string>(dataset->TerrainBlock.getGameVersion());
                viesti += "\nTerrain game version: " + lexical_cast<std::string>(dataset->TerrainBlock.Terrains.front().getGameVersion());
                wxMessageBox(viesti);
            }
            // <-- ends here
        }

        try
        {
            dataset->saveAs(SaveDatFileName.c_str());
        }
        catch(const std::ios_base::failure&)
        {
            wxMessageBox("Unable to save the file!");
            return;
        }
    }
    /*if(SaveApf)
    {
        //   Not Implemented Yet = Nothing Happens
    }*/
    if (SaveLangs)
    {
        SetStatusText("Saving language files...", 0);
        wxBusyCursor WaitCursor;
        if (LangWriteToLatest)
        {
            if (LangsUsed & 4)
            {
                if (!SaveLangX1P1())
                    return;
            }
            else if (LangsUsed & 2)
            {
                if (!SaveLangX1())
                    return;
            }
            else
            {
                if (!SaveLang())
                    return;
            }
        }
        else
        {
            if (LangsUsed & 1)
            {
                if (!SaveLang())
                    return;
            }
            if (LangsUsed & 2)
            {
                if (!SaveLangX1())
                    return;
            }
            if (LangsUsed & 4)
            {
                if (!SaveLangX1P1())
                    return;
            }
        }
    }

    SetStatusText("Selected files saved. "+lexical_cast<std::string>(popUp.unSaved)+" dat edits.", 0);
    popUp.unSaved = 0;
}

bool AGE_Frame::SaveLang()
{
    try
    {
        Lang->saveAs(SaveLangFileName.c_str());
    }
    catch(const std::ios_base::failure&)
    {
        wxMessageBox("Unable to save language file!");
        return false;
    }
    return true;
}

bool AGE_Frame::SaveLangX1()
{
    try
    {
        LangX->saveAs(SaveLangX1FileName.c_str());
    }
    catch(const std::ios_base::failure&)
    {
        wxMessageBox("Unable to save expansion language file!");
        return false;
    }
    return true;
}

bool AGE_Frame::SaveLangX1P1()
{
    try
    {
        LangXP->saveAs(SaveLangX1P1FileName.c_str());
    }
    catch(const std::ios_base::failure&)
    {
        wxMessageBox("Unable to save expansion language patch file!");
        return false;
    }
    return true;
}

void AGE_Frame::OnMenuOption(wxCommandEvent &event)
{
    switch(event.GetId())
    {
        case ePrompt:
        {
            PromptForFilesOnOpen = event.IsChecked();
            break;
        }
        case eNeverHide:
        {
            NeverHideAttributes = event.IsChecked();
            break;
        }
        case eBackup:
        {
            AutoBackups = event.IsChecked();
            break;
        }
        case eUnknown:
        {
            ShowUnknowns = event.IsChecked();
            // Does layouting and refreshing and ... check it out.
            OnGameVersionChange();
            break;
        }
        case eButtons:
        {
            ResizeTerrains = event.IsChecked();

            Terrains_Add->Enable(ResizeTerrains);
            Terrains_Delete->Enable(ResizeTerrains);
            break;
        }
        case wxID_EXIT:
        {
            Close(true);
            break;
        }
        case eTips:
        {
            wxString TipText;
            TipText.Append("You can have multiple search entries separated with '|' letter.\n");
            TipText.Append("Upper search boxes are inclusive and lower ones exclusive.\n");
            TipText.Append("Example: \"tower|ship|ram\"\n");
            TipText.Append("You can switch from \"or\" finding to \"and\" finding with check boxes.\n");
            TipText.Append("Meaning that every search entry has to match.\n");
            wxMessageBox(TipText, "Tips");
            break;
        }
        case eAbout:
        {
            AboutDialog AGEAbout(this, font);
            AGEAbout.ShowModal();
            break;
        }
        case eTabBar:
        {
            if(slp_window) slp_view->Refresh();
            break;
        }
        case eVasili:
        {
#ifdef WIN32
            EmptyWorkingSet(GetCurrentProcess());
#endif
            break;
        }
        case eDRS:
        {
            if(event.IsChecked())
            {
                if(!LooseHD)
                {
                    GetToolBar()->SetToolNormalBitmap(eDRS, wxBitmap(DRS_lock_xpm));
                    // Reload DRS files.
                    wxArrayString FilesToRead;
                    if(GenieVersion < genie::GV_AoKE3)
                    {
                        if(GenieVersion >= genie::GV_RoR)
                        {
                            FilesToRead.Add("2\\sounds.drs");
                            FilesToRead.Add("2\\graphics.drs");
                            FilesToRead.Add("2\\interfac.drs");
                        }
                    }
                    else
                    {
                        if(GenieVersion == genie::GV_TC || GenieVersion == genie::GV_TCV)
                        {
                            FilesToRead.Add("\\sounds_x1.drs");
                            FilesToRead.Add("\\gamedata_x1.drs");
                            FilesToRead.Add("\\gamedata_x1_p1.drs");
                        }
                        else if(GenieVersion == genie::GV_CC || GenieVersion == genie::GV_CCV || GenieVersion == genie::GV_CCV2)
                        {
                            if(GameVersion == EV_EF || GameVersion == EV_EF2)
                            {
                                FilesToRead.Add("\\sounds_x2.drs");
                                FilesToRead.Add("\\graphics_x2.drs");
                                FilesToRead.Add("\\terrain_x2.drs");
                                FilesToRead.Add("\\interfac_x2.drs");
                                FilesToRead.Add("\\gamedata_x2.drs");
                            }
                            FilesToRead.Add("\\sounds_x1.drs");
                            if (GameVersion == EV_EF || GameVersion == EV_EF2)
                            {
                                FilesToRead.Add("\\graphics_x1_p1.drs");
                                FilesToRead.Add("\\terrain_x1_p1.drs");
                                FilesToRead.Add("\\interfac_x1_p1.drs");
                            }
                            else
                            {
                                FilesToRead.Add("\\graphics_x1.drs");
                                FilesToRead.Add("\\terrain_x1.drs");
                                FilesToRead.Add("\\interfac_x1.drs");
                            }
                            FilesToRead.Add("\\gamedata_x1.drs");
                        }
                    }
                    FilesToRead.Add("\\sounds.drs");
                    if (GameVersion == EV_EF || GameVersion == EV_EF2)
                    {
                        FilesToRead.Add("\\graphics_p1.drs");
                        FilesToRead.Add("\\terrain_p1.drs");
                    }
                    else
                    {
                        FilesToRead.Add("\\graphics.drs");
                        FilesToRead.Add("\\terrain.drs");
                    }
                    if(GenieVersion < genie::GV_AoKB)
                    {
                        FilesToRead.Add("\\border.drs");
                    }
                    if (GameVersion == EV_EF || GameVersion == EV_EF2)
                    {
                        FilesToRead.Add("\\interfac_p1.drs");
                    }
                    else
                    {
                        FilesToRead.Add("\\interfac.drs");
                    }
                    if(GenieVersion >= genie::GV_AoKE3)
                    {
                        FilesToRead.Add("\\gamedata.drs");
                    }

                    if(UseExtra)
                    {
                        genie::DrsFile *topDRS = new genie::DrsFile();
                        topDRS->setGameVersion(GenieVersion);
                        try
                        {
                            topDRS->load(Path1stDRS.c_str());
                            datafiles.push_back(topDRS);
                        }
                        catch(const std::ios_base::failure&)
                        {
                            delete topDRS;
                        }
                    }
                    if(UseMod) addFilesToRead(FilesToRead, FolderDRS2);
                    addFilesToRead(FilesToRead, FolderDRS);
                    genie::PalFilePtr pal;
                    for (genie::DrsFile *file : datafiles)
                    {
                        pal.reset();
                        pal = file->getPalFile(50500);
                        if(pal)
                        {
                            palettes.push_back(pal->getColors());
                            break;
                        }
                    }
                }
                if(slp_window) slp_view->Refresh();
                Units_IconID_SLP->Refresh();
                Research_IconID_SLP->Refresh();
                break;
            }
            GetToolBar()->SetToolNormalBitmap(eDRS, wxBitmap(DRS_unlock_xpm));
            // Unload DRS files, stop animations.
            animater.Stop();
            if(!LooseHD)
            {
                for (genie::DrsFile *file : datafiles)
                {
                    delete file;
                }
                datafiles.clear();
                palettes.clear();
            }
            break;
        }
        case eHelp:
        {
            //AGE_HelpInfo AGEHelp(this);
            //AGEHelp.ShowModal();
            wxString help = "ATTENTION!\nChanges to editing boxes affect all selected items!\n";
            /* Very useful piece for SLP debugging.
            int slps = 0, frames = 0;
            if(LooseHD)
            {
                wxArrayString folders;
                addSLPFolders4SLPs(folders, FolderDRS);
                /SLPs: 133, frames: 1795
                0000 0000
                0700 0000
                1700 0000
                0000 0100
                0705 0100
                0000 0200
                0000 0300
                0000 0400
                0000 0500
                0000 0600
                C78E 3C00
                A7CF F300
                07FA 0102
                171B FF30
                77FF 384C
                BFFF 82A3
                0700 00FE
                Clone Campaigns special terrain SLP properties
                0000001B 15037
                00000040 15023
                00000040 15024
                000000D0 15001
                000000DB 15036
                000000E0 15011
                00000AF0 15026
                019C20E4 15007
                02885840 15010
                03547468 15002
                80000000 15029
                ///folders.clear();/
                //addDRSFolders4SLPs(folders, FolderDRS); //Found properties: 0x00, 0x08, 0x10, 0x18, no offsets.
                for(int i=0; i < folders.size(); ++i)
                //for (genie::DrsFile *file: datafiles)
                {
                    wxDir dir(folders[i]);
                    if(!dir.IsOpened()) continue;
                    wxString res;
                    bool found = dir.GetFirst(&res, "*.slp");
                    while(found)
                    //wxMessageBox("SLPs in this DRS: "+FormatInt(file->slp_ids.size()));
                    //for(auto &slpID: file->slp_ids)
                    {
                        try
                        {
                            genie::SlpFile slp;
                            log_out << "Loading SLP file " << res << endl;
                            slp.load((folders[i] + res).c_str());
                            //slp = file->getSlpFile(slpID);
                            //if(!slp) continue;
                            ++slps;
                            genie::SlpFramePtr frame;
                            for(int i=0; i < slp.getFrameCount(); ++i)
                            {
                                try
                                {
                                    frame = slp.getFrame(i);
                                }
                                catch(const out_of_range&){}
                                if(frame)
                                {
                                    uint64_t palData = frame->getProperties();
                                    palData <<= 32;
                                    palData += frame->getPaletteOffset();
                                    slpPaletteCombinations.insert(make_pair(res, palData));
                                    ++frames;
                                }
                            }
                        }
                        catch(const std::ios_base::failure&){}
                        found = dir.GetNext(&res);
                    }
                }
            }
            log_out << "SLPs: "+FormatInt(slps)+", frames: "+FormatInt(frames) << endl;
            multimap<uint64_t, wxString> slpPaletteSorted;
            for(auto &palData: slpPaletteCombinations)
            {
                slpPaletteSorted.insert(make_pair(palData.second, palData.first));
            }
            for(auto &palData: slpPaletteSorted)
            {
                //palData.first = __builtin_bswap64(palData.first);
                stringbuf buffer;
                ostream os (&buffer);
                os << hex << setfill('0') << setw(16) << uppercase << palData.first;
                os << ' ' << palData.second;
                log_out << buffer.str() << endl;
            }*/
            help.Append("Click \"Help\" from the toolbar to see this again.\n\n"
            "Here are examples which cover all the nice features.\n"
            "(This is assuming that you edit Age of Empires II: The Conquerors)\n\n"
            "Advanced Searching\n\n"
            "Let's suppose that you want to edit buildings (type 80) of class 3,\n"
            "but not camps nor houses or yurts.\n"
            "See the two combo boxes having \"Lang File Name\" selected by default?\n"
            "Select \"Type\" to the upper one and \"Class\" to the lower one.\n"
            "Then put \"t 80|c 3,\" to the upper search box\n"
            "and \"camp|house|yurt\" to the lower (exclusive) search box.\n"
            "Select the upper \"And\" check box to make sure that the search returns\n"
            "only units to which ALL search terms in the upper search box match.\n\n"
            "Batch Processing\n\n"
            "Let's suppose that you want to multiply the garrison heal rate\n"
            "of all selected units (buildings) by 1.3.\n"
            "Simply select all the desired units and put into garrison heal rate box \"b*1.3\",\n"
            "or just put the absolute value you want for all selected units.\n"
            "The other batch modifiers are b+, b- and b/.\n"
            "Note that overflows are not checked!\n\n"
            "Cross Copy Between Files\n\n"
            "Let's suppose that you want to copy all ships to another dat file.\n"
            "From the toolbar, click +++ to open another window.\n"
            "Now that you have a second window titled \"AGE window 2\" open with a dat file,\n"
            "let's begin the copying.\n"
            "(You can copy to another game version if you dare.)\n"
            "On the first window, select all the ships (search for \"ship\").\n"
            "Then click copy and go to the second window.\n"
            "Then click paste or paste insert wherever you want the ships.\n"
            "That's it.");
            wxMessageBox(help, "Short Guide to Advanced Editing");
            break;
        }
        case eHex:
        {
            popUp.hexMode = event.IsChecked();
            if(dataset) LoadLists();
            break;
        }
        case eFloat:
        {
            popUp.accurateFloats = event.IsChecked();
            if(dataset) LoadLists();
            break;
        }
        case ePaste:
        {
            Paste11 = event.IsChecked();
            break;
        }
        case eReselection:
        {
            Reselection = event.IsChecked();
            break;
        }
        case eAddWindow:
        {
            for(size_t win = 0; win < 4; ++win)
            if(!openEditors[win])
            {
                AGE_Frame* newWindow = new AGE_Frame("AGE " + AboutDialog::AGE_VER + " window "+lexical_cast<std::string>(win+1), win);
                wxCommandEvent open;
                newWindow->OnOpen(open);
                break;
            }
            break;
        }
        case eStayOnTop:
        {
            ToggleWindowStyle(wxSTAY_ON_TOP);
            StayOnTop = event.IsChecked();
            break;
        }
        case hotWin1:
        {
            if (openEditors[0])
            {
                openEditors[0]->Raise();
            }
            break;
        }
        case hotWin2:
        {
            if (openEditors[1])
            {
                openEditors[1]->Raise();
            }
            break;
        }
        case hotWin3:
        {
            if (openEditors[2])
            {
                openEditors[2]->Raise();
            }
            break;
        }
        case hotWin4:
        {
            if (openEditors[3])
            {
                openEditors[3]->Raise();
            }
            break;
        }
        case closeAll:
        {
            wxCloseEvent ce(wxEVT_CLOSE_WINDOW);
            openEditors[window_num] = 0;
            for(size_t win = 0; win < 4; ++win)
            if(openEditors[win])
            {
                openEditors[win]->OnExit(ce);
            }
            OnExit(ce);
            break;
        }
        case eCompileList:
        {
            wxString folder = wxStandardPaths::Get().GetDocumentsDir();
            wxTextFile slp_csv(folder + "\\slps.csv");
            wxTextFile obj_csv(folder + "\\objs.csv");
            if(!slp_csv.Create() && !slp_csv.Open())
            {
                wxMessageBox("Failed to load/create slps.csv");
            }
            if(!obj_csv.Create() && !obj_csv.Open())
            {
                wxMessageBox("Failed to load/create objs.csv");
            }
            slp_csv.Clear();
            obj_csv.Clear();

            slp_csv.AddLine("SLP,PicFilename,Name,NumFrames,NumFacets,AnimDuration,ReplayDelay");
            for(size_t sprite = 0; sprite < dataset->Graphics.size(); ++sprite)
            if(dataset->GraphicPointers[sprite])
            {
                slp_csv.AddLine(lexical_cast<std::string>(dataset->Graphics[sprite].SLP)
                            +','+dataset->Graphics[sprite].FileName
                            +','+dataset->Graphics[sprite].Name
                            +','+lexical_cast<std::string>(dataset->Graphics[sprite].FrameCount)
                            +','+lexical_cast<std::string>(dataset->Graphics[sprite].AngleCount)
                            +','+lexical_cast<std::string>(dataset->Graphics[sprite].AnimationDuration)
                            +','+lexical_cast<std::string>(dataset->Graphics[sprite].ReplayDelay));
            }

            size_t unit, civ, depth = 0;
            obj_csv.AddLine("Civ,IconSet,UnitID,UnitName,LangName,"
                "Name,PicFilename,Layer,NumFrames,NumFacets");
            std::function<void(size_t)> sprite_checker = [&](size_t sprite)
            {
                ++depth;
                if(sprite < dataset->Graphics.size() && dataset->GraphicPointers[sprite])
                {
                    if(!dataset->Graphics[sprite].FileName.empty())
                    {
                        obj_csv.AddLine(dataset->Civs[civ].Name
                            +','+lexical_cast<std::string>((int)dataset->Civs[civ].IconSet)
                            +','+lexical_cast<std::string>(unit)
                            +','+dataset->Civs[civ].Units[unit].Name
                            +','+TranslatedText(dataset->Civs[civ].Units[unit].LanguageDLLName, 24)
                            //+','+lexical_cast<std::string>((int)dataset->Civs[civ].Units[unit].OcclusionMode)
                            +','+dataset->Graphics[sprite].Name
                            +','+dataset->Graphics[sprite].FileName
                            +','+lexical_cast<std::string>((int)dataset->Graphics[sprite].Layer)
                            +','+lexical_cast<std::string>(dataset->Graphics[sprite].FrameCount)
                            +','+lexical_cast<std::string>(dataset->Graphics[sprite].AngleCount));
                    }
                    if(depth == 1)
                    for(size_t delta = 0; delta < dataset->Graphics[sprite].Deltas.size(); ++delta)
                    {
                        sprite_checker(dataset->Graphics[sprite].Deltas[delta].GraphicID);
                    }
                }
                --depth;
            };

            //obj_csv.AddLine("Civ,IconSet,UnitID,Name,LangNameID,LangName,LangHKID,Hotkey");
            for(civ = 0; civ < dataset->Civs.size(); ++civ)
            {
                for(unit = 0; unit < dataset->Civs[civ].Units.size(); ++unit)
                {
                    //int langname = dataset->Civs[civ].Units[unit].LanguageDLLName;
                    //int hotkey = dataset->Civs[civ].Units[unit].HotKey;

                    /*obj_csv.AddLine(dataset->Civs[civ].Name
                            +','+lexical_cast<std::string>((int)dataset->Civs[civ].IconSet)
                            +','+lexical_cast<std::string>(unit)
                            +','+dataset->Civs[civ].Units[unit].Name
                            +','+lexical_cast<std::string>(langname)
                            +','+TranslatedText(langname, 24)
                            +','+lexical_cast<std::string>(hotkey)
                            +','+TranslatedText(hotkey, 8));*/

                    //if(dataset->Civs[civ].Units[unit].OcclusionMode)
                    if(dataset->Civs[civ].UnitPointers[unit] != 0)
                    {
                        // Gather information about all the graphics unit uses.
                        sprite_checker(dataset->Civs[civ].Units[unit].StandingGraphic.first);
                        sprite_checker(dataset->Civs[civ].Units[unit].StandingGraphic.second);
                        sprite_checker(dataset->Civs[civ].Units[unit].DyingGraphic);
                        sprite_checker(dataset->Civs[civ].Units[unit].UndeadGraphic);
                        for(size_t sprite = 0; sprite < dataset->Civs[civ].Units[unit].DamageGraphics.size(); ++sprite)
                        {
                            sprite_checker(dataset->Civs[civ].Units[unit].DamageGraphics[sprite].GraphicID);
                        }
                        switch((short)dataset->Civs[civ].Units[unit].Type)
                        {
                            case 80:
                            sprite_checker(dataset->Civs[civ].Units[unit].Building.ConstructionGraphicID);
                            sprite_checker(dataset->Civs[civ].Units[unit].Building.DestructionGraphicID);
                            sprite_checker(dataset->Civs[civ].Units[unit].Building.DestructionRubbleGraphicID);
                            sprite_checker(dataset->Civs[civ].Units[unit].Building.SnowGraphicID);
                            case 70:
                            sprite_checker(dataset->Civs[civ].Units[unit].Creatable.GarrisonGraphic);
                            sprite_checker(dataset->Civs[civ].Units[unit].Creatable.SpecialGraphic);
                            case 60:
                            case 50:
                            sprite_checker(dataset->Civs[civ].Units[unit].Type50.AttackGraphic);
                            case 40:
                            if(GenieVersion != genie::GV_RoR && GameVersion != EV_Tapsa)
                            {
                                for(size_t task = 0; task < dataset->UnitHeaders[unit].TaskList.size(); ++task)
                                {
                                    sprite_checker(dataset->UnitHeaders[unit].TaskList[task].MovingGraphicID);
                                    sprite_checker(dataset->UnitHeaders[unit].TaskList[task].ProceedingGraphicID);
                                    sprite_checker(dataset->UnitHeaders[unit].TaskList[task].WorkingGraphicID);
                                    sprite_checker(dataset->UnitHeaders[unit].TaskList[task].CarryingGraphicID);
                                }
                            }
                            else for(size_t task = 0; task < dataset->Civs[civ].Units[unit].Bird.TaskList.size(); ++task)
                            {
                                sprite_checker(dataset->Civs[civ].Units[unit].Bird.TaskList[task].MovingGraphicID);
                                sprite_checker(dataset->Civs[civ].Units[unit].Bird.TaskList[task].ProceedingGraphicID);
                                sprite_checker(dataset->Civs[civ].Units[unit].Bird.TaskList[task].WorkingGraphicID);
                                sprite_checker(dataset->Civs[civ].Units[unit].Bird.TaskList[task].CarryingGraphicID);
                            }
                            case 30:
                            sprite_checker(dataset->Civs[civ].Units[unit].DeadFish.WalkingGraphic);
                            sprite_checker(dataset->Civs[civ].Units[unit].DeadFish.RunningGraphic);
                        }
                    }
                }
            }

            wxString results = "slps.csv ";
                results += slp_csv.Write() ? "saved" : "not saved";
                results += "\nobjs.csv ";
                results += obj_csv.Write() ? "saved" : "not saved";
            wxMessageBox(results);
            break;
        }
        case eBoxWidth:
        {
            wxTextEntryDialog ted(this, "Enter new multiplier for data box widths",
                "Set Box Width Multiplier", FormatFloat(boxWidthMultiplier));
            ted.SetTextValidator(wxFILTER_NUMERIC);
            if(ted.ShowModal() == wxID_OK)
            {
                try
                {
                    boxWidthMultiplier = lexical_cast<float>(ted.GetValue());
                    wxMessageBox("Please restart me!", "AGE");
                }
                catch(const bad_lexical_cast&)
                {
                    wxMessageBox("Bad floating point", "AGE");
                }
            }
            break;
        }
        case eScrollRate:
        {
            wxTextEntryDialog ted(this, "Enter new scroll rate in pixels. 120 is the most sensitive.",
                "Set Scroll Rate", FormatInt(AScrolled::rate * 120.f));
            ted.SetTextValidator(wxFILTER_NUMERIC);
            if(ted.ShowModal() == wxID_OK)
            {
                try
                {
                    AScrolled::rate = lexical_cast<float>(ted.GetValue()) / 120.f;
                }
                catch(const bad_lexical_cast&)
                {
                    wxMessageBox("Bad floating point", "AGE");
                }
            }
            break;
        }
        default: wxMessageBox("ID "+lexical_cast<std::string>(event.GetId())+"\nType "+lexical_cast<std::string>(event.GetEventType()), "Unhandled Event");
    }
}

int AGE_Frame::produceRecentValues(wxArrayString &latest, std::vector<wxArrayString> &RecentValues)
{
    RecentValues.insert(RecentValues.begin(), latest);
    int RecentItems = RecentValues.size();
    for(int i=1; i < RecentItems; ++i)
    if(RecentValues[i] == latest)
    {
        RecentValues.erase(RecentValues.begin() + i);
        --RecentItems;
        break;
    }
    return RecentItems;
}

void AGE_Frame::addFilesToRead(const wxArrayString &files, const wxString &folder)
{
    if(folder.empty() || !wxDir::Exists(folder)) return;
    for(int i=0; i < files.size(); ++i)
    {
        genie::DrsFile *interfac = new genie::DrsFile();
        wxString location = folder + files[i];
        interfac->setGameVersion(GenieVersion);
        try
        {
            interfac->load(location.c_str());
            datafiles.push_back(interfac);
        }
        catch(const std::ios_base::failure&)
        {
            delete interfac;
        }
    }
}

void AGE_Frame::LoadTXT(const wxString &filename)
{
    std::string line(filename);
    std::ifstream infile(line);
    while (getline(infile, line))
    {
        size_t num = 0;
        while (isdigit(static_cast<uint8_t>(line[num])))
        {
            ++num;
        }
        if (num)
        {
            size_t ID = lexical_cast<size_t>(line.substr(0, num));
            size_t beg = line.find('"', num) + 1;
            size_t len = line.find('"', beg) - beg;
            if (len) LangTxt[ID] = line.substr(beg, len);
        }
    }
}

wxString AGE_Frame::TranslatedText(int ID, int letters)
{
    if (ID < 0) return "";
    wxString result = "";
    if (UseTXT)
    {
        result = LangTxt[ID];
        result.Replace("\\n", "\r\n");
        result.Replace("\\\\", "\\");
        result.Replace("\\\"", "\"");
    }
    else
    {
        if (sizeof(size_t) > 4 || WriteLangs)
        {
            if (LangsUsed & 4 && !(result = LangXP->getString(ID)).empty()) {}
            else if (LangsUsed & 2 && !(result = LangX->getString(ID)).empty()) {}
            else if (LangsUsed & 1 && !(result = Lang->getString(ID)).empty()) {}
        }
        else // Does not work when building as 64-bit
        {
            char *buffer = new char[letters];
            if (LangsUsed & 4 && LoadStringA(LanguageDLL[2], ID, buffer, letters)) result = buffer;
            else if (LangsUsed & 2 && LoadStringA(LanguageDLL[1], ID, buffer, letters)) result = buffer;
            else if (LangsUsed & 1 && LoadStringA(LanguageDLL[0], ID, buffer, letters)) result = buffer;
            delete[] buffer;
        }
        result.Replace("\n", "\r\n");
    }
    return result;
}

void AGE_Frame::OnKillFocus_LangDLL(wxFocusEvent &event)
{
    event.Skip();
    TextIndexControl *control = static_cast<TextIndexControl *>(event.GetEventObject());
    if (control->IsModified())
    {
        control->DiscardEdits();
        if (control->index < 0) return;
        if (!WriteLangs)
        {
            wxString message = "In order to edit language entries, check write language files in the open files dialog and reopen them.";
            popUp.post(message, "Warning");
            return;
        }

        int ID = control->index;
        wxString text(control->GetValue());
        text.Replace("\r\n", "\n");
        std::string Name = std::string(text);
        if (LangWriteToLatest)
        {
            if (LangsUsed & 4) LangXP->setString(ID, Name);
            else if (LangsUsed & 2) LangX->setString(ID, Name);
            else if (LangsUsed & 1) Lang->setString(ID, Name);
        }
        else
        {
            if (LangsUsed & 4 && !LangXP->getString(ID).empty()) LangXP->setString(ID, "");
            if (LangsUsed & 2 && !LangX->getString(ID).empty()) LangX->setString(ID, "");
            if (LangsUsed & 1) Lang->setString(ID, Name);
        }
        SetStatusText("Wrote \"" + Name + "\" to " + lexical_cast<std::string>(ID), 0);
    }
}

wxString AGE_Frame::FormatFloat(float value)
{
    if (popUp.accurateFloats)
        return lexical_cast<std::string>(value);

    std::stringbuf buffer;
    std::ostream os(&buffer);
    os << value;
    return buffer.str();
}

wxString AGE_Frame::FormatInt(int value)
{
    if (!popUp.hexMode)
        return lexical_cast<std::string>(value);

    std::stringbuf buffer;
    std::ostream os(&buffer);
    os << std::hex << std::uppercase << value;
    return buffer.str();
}

wxString AGE_Frame::FormatUnsigned(unsigned value)
{
    if (!popUp.hexMode)
        return lexical_cast<std::string>(value);

    std::stringbuf buffer;
    std::ostream os(&buffer);
    os << std::hex << std::uppercase << value;
    return buffer.str();
}

void AGE_Frame::SaveBackup()
{
    if(dataset != nullptr)
    {
        try
        {
            dataset->saveAs((DatFileName.substr(0, DatFileName.size() - 4) + "_backup" + CurrentTime() + ".dat").c_str());
        }
        catch (const std::ios_base::failure&)
        {
            wxMessageBox("Error saving backup!");
        }
    }
}

wxString AGE_Frame::CurrentTime()
{
    time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct tm *parts = localtime(&now);

    std::stringbuf buffer;
    std::ostream os(&buffer);
    os << 1900 + parts->tm_year;
    os << std::setfill('0') << std::setw(2);
    os << 1 + parts->tm_mon;
    os << std::setw(2) << parts->tm_mday;
    os << std::setw(2) << parts->tm_hour;
    os << std::setw(2) << parts->tm_min;
    os << std::setw(2) << parts->tm_sec;
    return buffer.str();
}

void AGE_Frame::OnExit(wxCloseEvent &event)
{
    {
        wxConfig Config("", "", "AGE2\\ConfigWindow"+lexical_cast<std::string>(window_num + 1), "", wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
        Config.Write("DefaultFiles/AutoBackups", AutoBackups);
        Config.Write("Interaction/PromptForFilesOnOpen", PromptForFilesOnOpen);
        Config.Write("Interaction/AutoCopy", AutoCopy);
        Config.Write("Interaction/AutoCopyAngles", AutoCopyAngles);
        Config.Write("Interaction/CopyGraphics", CopyGraphics);
        Config.Write("Interaction/AllCivs", Units_SpecialCopy_Civs->GetValue());
        Config.Write("Interaction/ShowSLP", ShowSLP);
        Config.Write("Interaction/ShowIcons", ShowIcons);
        Config.Write("Interaction/AnimSLP", AnimSLP);
        Config.Write("Interaction/ShowShadows", ShowShadows);
        Config.Write("Interaction/ShowOutline", ShowOutline);
        Config.Write("Interaction/ShowDeltas", ShowDeltas);
        Config.Write("Interaction/ShowStack", ShowStack);
        Config.Write("Interaction/ShowAnnexes", ShowAnnexes);
        Config.Write("Interaction/RotateAngles", RotateAngles);
        Config.Write("Interaction/DrawTerrain", DrawTerrain);
        Config.Write("Interaction/FilterAllSubs", FilterAllSubs);
        Config.Write("Interaction/PlaySounds", PlaySounds);
        Config.Write("Interaction/NeverHideAttributes", NeverHideAttributes);
        Config.Write("Interface/ShowUnknowns", ShowUnknowns);
        Config.Write("Interface/ResizeTerrains", ResizeTerrains);
        Config.Write("Interface/StayOnTop", StayOnTop);
        Config.Write("Interface/KeepViewOnTop", KeepViewOnTop);
        Config.Write("Interface/Paste11", Paste11);
        Config.Write("Interface/Reselection", Reselection);
        Config.Write("Interface/MaxWindowWidthV2", maxWindowWidthV2);
        wxPoint pos = GetPosition();
        Config.Write("Interface/WindowPosX", pos.x);
        Config.Write("Interface/WindowPosY", pos.y);
        Config.Write("Interface/Zooming", slp_zoom);
        Config.Write("Interface/AlexZoom", AlexZoom);
        Config.Write("Interface/ViewBackgroundR", ViewBackR);
        Config.Write("Interface/ViewBackgroundG", ViewBackG);
        Config.Write("Interface/ViewBackgroundB", ViewBackB);
        Config.Write("Interface/DrawAngles", DrawAngles);
        Config.Write("Interface/DrawCollisionShape", DrawCollisionShape);
        Config.Write("Interface/DrawClearanceShape", DrawClearanceShape);
        Config.Write("Interface/DrawSelectionShape", DrawOutline);
        Config.Write("Interface/CacheSizeMB", static_cast<int>(GG::cache_size / 1000000u));
        Config.Write("Interface/ViewPosX", ViewPosX);
        Config.Write("Interface/ViewPosY", ViewPosY);
        Config.Write("Interface/BoxWidthMultiplier", boxWidthMultiplier);
        // Global settings
        if (window_num == 0)
        {
            int rate = AScrolled::rate * 120.f;
            Config.Write("Interface/ScrollRate", rate);
        }
    }

    if(event.CanVeto() && popUp.unSaved > 0)
    {
        int answer = wxMessageBox("Do you want to save changes made to open files?\nThere are "
                        +lexical_cast<std::string>(popUp.unSaved)+" unsaved changes.",
                        "Advanced Genie Editor", wxICON_QUESTION | wxCANCEL | wxYES_NO);
        if(answer != wxNO)
        {
            if(answer == wxYES)
            {
                wxCommandEvent SaveFiles(wxEVT_MENU, eSave);
                OnSave(SaveFiles);
            }
            else
            {
                event.Veto();
                return;
            }
        }
        else if(AutoBackups) SaveBackup();
    }

    GetToolBar()->ToggleTool(eDRS, false);
    wxCommandEvent loadDRS(wxEVT_MENU, eDRS);
    loadDRS.SetInt(false);
    OnMenuOption(loadDRS);

    delete dataset;
    if(WriteLangs)
    {
        delete Lang;
        delete LangX;
        delete LangXP;
    }

    openEditors[window_num] = 0;
    while(animater.IsRunning())
    {
        if(event.CanVeto())
        {
            event.Veto();
            return;
        }
    }
    popUp.loadedFileId = -1;
    Tab_Research->Reparent(TabBar_Main);
    Tab_Techs->Reparent(TabBar_Main);
    Tab_TechTrees->Reparent(TabBar_Main);
    Tab_Civs->Reparent(TabBar_Main);
    Tab_Units->Reparent(TabBar_Main);
    Tab_UnitLine->Reparent(TabBar_Main);
    Tab_Graphics->Reparent(TabBar_Main);
    Tab_General->Reparent(TabBar_Main);
    Tab_Terrains->Reparent(TabBar_Main);
    Tab_TerrainBorders->Reparent(TabBar_Main);
    Tab_TerrainRestrictions->Reparent(TabBar_Main);
    Tab_Sounds->Reparent(TabBar_Main);
    Tab_PlayerColors->Reparent(TabBar_Main);
    Tab_Unknown->Reparent(TabBar_Main);
    Tab_TechTreeAges->Reparent(Tab_TechTrees);
    Tab_TechTreeBuildings->Reparent(Tab_TechTrees);
    Tab_TechTreeUnits->Reparent(Tab_TechTrees);
    Tab_TechTreeResearches->Reparent(Tab_TechTrees);
    Destroy();
}
