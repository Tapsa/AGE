#include "../AGE_Frame.h"
#include "../DRSunlock.xpm"
#include "../DRSlock.xpm"
#include "../Villager32.xpm"

float AGE_SLP::bearing = 0.f;
unsigned AGE_SLP::setbearing = 0u;

genie::GameVersion AGE_Frame::version(int ver)
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
        case EV_Cysion: return genie::GV_Cysion;
        case EV_DE2: return genie::GV_C2;
        case EV_SWGB: return genie::GV_SWGB;
        case EV_CC: return genie::GV_CC;
        case EV_EF: return genie::GV_CC;
        case EV_Tapsa: return genie::GV_Tapsa;

        default: wxMessageBox("Wrong version", "Oops!");
        return genie::GV_None;
    }
}

void AGE_Frame::OnOpen(wxCommandEvent&)
{
    if(popUp.unSaved > 0)
    {
        int answer = wxMessageBox("Do you want to save changes made to open files?\nThere are "
                        +lexical_cast<string>(popUp.unSaved)+" unsaved changes.",
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
        AGE_OpenDialog OpenBox(this, font);

        int RecentItems;
        {
            wxConfig RecentOpen("", "", "AGE2\\RecentOpen", "", wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
            RecentOpen.Read("Recent/Items", &RecentItems, 0);
            OpenBox.RecentValues.resize(RecentItems);
            for(int i=0; i < RecentItems; ++i)
            {
                OpenBox.RecentValues[i].Alloc(8);
                wxString temp, entry = "Recent" + wxString::Format("%04d", i + 1);
                RecentOpen.Read(entry + "/DatVersion", &temp, "9000"); OpenBox.RecentValues[i].Add(temp);
                RecentOpen.Read(entry + "/DatPath", &temp, wxEmptyString); OpenBox.RecentValues[i].Add(temp);
                RecentOpen.Read(entry + "/Lang", &temp, wxEmptyString); OpenBox.RecentValues[i].Add(temp);
                RecentOpen.Read(entry + "/LangX1", &temp, wxEmptyString); OpenBox.RecentValues[i].Add(temp);
                RecentOpen.Read(entry + "/LangX1P1", &temp, wxEmptyString); OpenBox.RecentValues[i].Add(temp);
                RecentOpen.Read(entry + "/PathDRS", &temp, wxEmptyString); OpenBox.RecentValues[i].Add(temp);
                RecentOpen.Read(entry + "/PathDRS2", &temp, wxEmptyString); OpenBox.RecentValues[i].Add(temp);
                RecentOpen.Read(entry + "/PathDRS3", &temp, wxEmptyString); OpenBox.RecentValues[i].Add(temp);
            }
        }
        if(OpenBox.RecentValues.size())
        for(int i=0; i < RecentItems; ++i)
        OpenBox.CheckBox_Recent->Append(OpenBox.RecentValues[i][1]);
        else
        OpenBox.CheckBox_Recent->Append("Happy Modding!");
        OpenBox.CheckBox_Recent->SetSelection(0);

        OpenBox.Path_CustomDefault->SetPath(CustomFolder);
        OpenBox.CheckBox_GenieVer->SetSelection(GameVersion);
        OpenBox.TerrainsBox->Enable(ResizeTerrains);

        OpenBox.DriveLetterBox->ChangeValue(DriveLetter);
        OpenBox.LanguageBox->ChangeValue(Language);
        OpenBox.TerrainsBox->ChangeValue(lexical_cast<string>(CustomTerrains));
        OpenBox.Path_DRS->SetPath(FolderDRS);
        OpenBox.Path_DRS2->SetPath(FolderDRS2);
        OpenBox.Path_DRS3->SetPath(Path1stDRS);
        OpenBox.Path_SLP->SetPath(PathSLP);
        OpenBox.CheckBox_DRSPath->SetValue(UseDRS);
        OpenBox.CheckBox_DRSPath2->SetValue(UseMod);
        OpenBox.CheckBox_DRSPath3->SetValue(UseExtra);
        OpenBox.CheckBox_SlpPath->SetValue(UseLooseSLP);

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

        bool load = OpenBox.ShowModal() == wxID_OK; // What this does?

        GameVersion = OpenBox.CheckBox_GenieVer->GetSelection();
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
        UseDRS = OpenBox.CheckBox_DRSPath->GetValue();
        UseMod = OpenBox.CheckBox_DRSPath2->GetValue();
        UseExtra = OpenBox.CheckBox_DRSPath3->GetValue();
        UseLooseSLP = OpenBox.CheckBox_SlpPath->GetValue();
        WriteLangs = OpenBox.CheckBox_LangWrite->GetValue();
        LangWriteToLatest = OpenBox.CheckBox_LangWriteToLatest->GetValue();

        if(!load)
        {
            return;
        }
        popUp.unSaved = 0;
        ++popUp.loadedFileId;

        wxConfig Config("", "", "AGE2\\ConfigWindow"+lexical_cast<string>(window_num + 1), "", wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
        Config.Write("DefaultFiles/DriveLetter", DriveLetter);
        Config.Write("DefaultFiles/CustomFolder", CustomFolder);
        Config.Write("DefaultFiles/Version", GameVersion);
        Config.Write("DefaultFiles/DatUsed", DatUsed);
        Config.Write("DefaultFiles/DatFilename", DatFileName);
        Config.Write("DefaultFiles/FolderDRS", FolderDRS);
        Config.Write("DefaultFiles/FolderDRS2", FolderDRS2);
        Config.Write("DefaultFiles/Path1stDRS", Path1stDRS);
        Config.Write("DefaultFiles/PathLooseSprites", PathSLP);
        Config.Write("DefaultFiles/UseDRS", UseDRS);
        Config.Write("DefaultFiles/UseMod", UseMod);
        Config.Write("DefaultFiles/UseExtra", UseExtra);
        Config.Write("DefaultFiles/UseLooseSprites", UseLooseSLP);
        Config.Write("DefaultFiles/LangsUsed", LangsUsed);
        Config.Write("DefaultFiles/WriteLangs", WriteLangs);
        Config.Write("DefaultFiles/LangWriteToLatest", LangWriteToLatest);
        Config.Write("DefaultFiles/Language", Language);
        Config.Write("DefaultFiles/LangFilename", LangFileName);
        Config.Write("DefaultFiles/LangX1Filename", LangX1FileName);
        Config.Write("DefaultFiles/LangX1P1Filename", LangX1P1FileName);
        Config.Write("Misc/CustomTerrains", CustomTerrains);

        if(!OpenBox.CheckBox_LangFileLocation->IsChecked()) LangFileName = "";
        if(!OpenBox.CheckBox_LangX1FileLocation->IsChecked()) LangX1FileName = "";
        if(!OpenBox.CheckBox_LangX1P1FileLocation->IsChecked()) LangX1P1FileName = "";

        wxArrayString latest;
        latest.Alloc(8);
        latest.Add(lexical_cast<string>(GameVersion));
        latest.Add(DatFileName);
        latest.Add(LangFileName);
        latest.Add(LangX1FileName);
        latest.Add(LangX1P1FileName);
        latest.Add(FolderDRS);
        latest.Add(FolderDRS2);
        latest.Add(Path1stDRS);
        int items = produceRecentValues(latest, OpenBox.RecentValues);
        wxConfig RecentOpen("", "", "AGE2\\RecentOpen", "", wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
        RecentOpen.Write("Recent/Items", items);
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
        }
    }

    GenieVersion = version(GameVersion);
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

    // txt language file
    LangTxt.clear();
    if(LangFileName.size() && 't' == LangFileName[LangFileName.size() - 1])
    {
        UseTXT = true;
        // Bad way of coding, please fix.
        if(GenieVersion == genie::GV_TC || GenieVersion >= genie::GV_Cysion && GenieVersion <= genie::GV_LatestDE2)
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
        // Load custom palettes
        GG::LoadPalettes(palettes, PalettesPath);
    }

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
                if(GenieVersion >= genie::GV_AoE)
                dataset->Civs[loop].Units[loop2].CopyID = loop2;
                if(GenieVersion >= genie::GV_AoK)
                dataset->Civs[loop].Units[loop2].BaseID = loop2;
                else
                if(dataset->Civs[loop].Units[loop2].Type >= 40 && dataset->Civs[loop].Units[loop2].Type <= 80)
                for(size_t loop3 = dataset->Civs[loop].Units[loop2].Bird.TaskList.size(); loop3--> 0;)
                dataset->Civs[loop].Units[loop2].Bird.TaskList[loop3].ID = loop3;
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

        How2List = SEARCH;

        task_names.Clear();
        // When changing this, edit all 4 other places too
        task_names.Add("Unused Ability/Invalid Ability");   // Selection 0
        task_names.Add("0: None");
        task_names.Add("1: Move to");
        task_names.Add(GenieVersion < genie::GV_AoKA ? "2: None" : "2: Follow");
        task_names.Add("3: Garrison");
        task_names.Add("4: Explore");
        task_names.Add("5: Gather/Rebuild");
        task_names.Add("6: Graze, deleted?");
        task_names.Add("7: Combat");
        task_names.Add("8: Shoot");
        task_names.Add("9: Attack");
        task_names.Add("10: Fly");
        task_names.Add("11: Scare/Hunt, deleted?");
        task_names.Add("12: Unload (Boat-Like)");
        task_names.Add(GenieVersion < genie::GV_AoKA ? "13: None" : "13: Guard");
        task_names.Add(GenieVersion < genie::GV_AoKA ? "14: None" : "HD 14: Siege Tower Ability");
        task_names.Add("20: Escape, deleted?");
        task_names.Add("21: Make");
        //task_names.Add("100: Num"); // Useless
        task_names.Add("101: Build");
        task_names.Add("102: Make a Unit");
        task_names.Add("103: Make a Tech");
        task_names.Add("104: Convert");
        task_names.Add("105: Heal");
        task_names.Add("106: Repair");
        task_names.Add("107: Get Auto-converted");
        task_names.Add("108: Discovery Artifact");
        task_names.Add("109: Unknown, nothing?");
        task_names.Add("110: Hunt");
        task_names.Add("111: Trade");
        task_names.Add("120: Generate Wonder Victory");
        if(GenieVersion >= genie::GV_AoKA)
        {
            task_names.Add("121: Deselect when Tasked (Farm)");
            task_names.Add("122: Loot (Gather)");
            task_names.Add("123: Housing");
            task_names.Add("124: Pack");
            task_names.Add("125: Unpack & Attack");
            task_names.Add("130: Unknown, nothing?");
            task_names.Add("131: Off-Map Trade");
            task_names.Add("132: Pickup Unit");
            task_names.Add("133: Charge Attack");
            task_names.Add("134: Transform Unit");
            task_names.Add("135: Kidnap Unit");
            task_names.Add("136: Deposit Unit");
            task_names.Add("149: Shear");
            task_names.Add("HD 150: Regeneration");
            task_names.Add("HD 151: Feitoria Ability");
        }
        Tasks_ActionType_ComboBox->Flash();

        age_names.Clear();
        age_names.Add("Nomad");
        if(GenieVersion >= genie::GV_SWGB)
        {
            age_names.Add("1st Tech Level");
            age_names.Add("2nd Tech Level");
            age_names.Add("3rd Tech Level");
            age_names.Add("4th Tech Level");
            age_names.Add("5th Tech Level");
        }
        else if(GenieVersion >= genie::GV_AoKA)
        {
            age_names.Add("Dark Age");
            age_names.Add("Feudal Age");
            age_names.Add("Castle Age");
            age_names.Add("Imperial Age");
            age_names.Add("Post-Imperial Age");
        }
        else
        {
            age_names.Add("Stone Age");
            age_names.Add("Tool Age");
            age_names.Add("Bronze Age");
            age_names.Add("Iron Age");
            age_names.Add("Post-Iron Age");
        }

        wxArrayString DefAoE1Armors, DefAoE2Armors, DefSWGBArmors,
            DefAoE1TerrainRests, DefAoE2TerrainRests, DefSWGBTerrainRests,
            DefRoRCivRes, DefAoKCivRes, DefSWGBCivRes;

        // AoE & RoR
        DefAoE1Armors.Add("0 - Stone Defense & Fire Galley");
        DefAoE1Armors.Add("1 - Stone Defense & Archers");
        DefAoE1Armors.Add("2 - Unused");
        DefAoE1Armors.Add("3 - Base Pierce");
        DefAoE1Armors.Add("4 - Base Melee");
        DefAoE1Armors.Add("5 - Unused");
        DefAoE1Armors.Add("6 - Buildings");
        DefAoE1Armors.Add("7 - Priests");
        DefAoE1Armors.Add("8 - Cavalry");
        DefAoE1Armors.Add("9 - Infantry");
        DefAoE1Armors.Add("10 - Stone Defense");
        DefAoE1Armors.Add("11 - Unused");
        DefAoE1Armors.Add("12 - Villagers & Gazelles & Medusa");
        DefAoE1TerrainRests.Add("Land + water");
        DefAoE1TerrainRests.Add("Land");
        DefAoE1TerrainRests.Add("Beach");
        DefAoE1TerrainRests.Add("Water");
        DefAoE1TerrainRests.Add("Land");
        DefAoE1TerrainRests.Add("Nothing");
        DefAoE1TerrainRests.Add("Water + beach");
        DefAoE1TerrainRests.Add("Land + shallows");
        DefAoE1TerrainRests.Add("Plain");
        DefAoE1TerrainRests.Add("Land - dirt");
        DefAoE1TerrainRests.Add("Land + beach");
        DefRoRCivRes.Add("Food Storage");
        DefRoRCivRes.Add("Wood Storage");
        DefRoRCivRes.Add("Stone Storage");
        DefRoRCivRes.Add("Gold Storage");
        DefRoRCivRes.Add("Population Headroom");// MAX_POP
        DefRoRCivRes.Add("Conversion Range");
        DefRoRCivRes.Add("Current Age");
        DefRoRCivRes.Add("Artifacts Captured");
        DefRoRCivRes.Add("Unused (Trade Bonus)");
        DefRoRCivRes.Add("Trade Goods");
        DefRoRCivRes.Add("Trade Production");
        DefRoRCivRes.Add("Current Population");// POPULATION
        DefRoRCivRes.Add("Corpse Decay Time");
        DefRoRCivRes.Add("Remarkable Discovery");
        DefRoRCivRes.Add("Ruins Captured");
        DefRoRCivRes.Add("Meat Storage");
        DefRoRCivRes.Add("Berry Storage");
        DefRoRCivRes.Add("Fish Storage");
        DefRoRCivRes.Add("Unused (Trade Tax)");
        DefRoRCivRes.Add("Total Units Owned");// TOTAL_UNITS / TOTAL_POP
        DefRoRCivRes.Add("Units Killed");
        DefRoRCivRes.Add("Technology Count");
        DefRoRCivRes.Add("% Map Explored");
        DefRoRCivRes.Add("Bronze Age Tech ID");
        DefRoRCivRes.Add("Iron Age Tech ID");
        DefRoRCivRes.Add("Tool Age Tech ID");
        DefRoRCivRes.Add("Attack Warning Sound ID");
        DefRoRCivRes.Add("Enable Priest Conversion");
        DefRoRCivRes.Add("Enable Building Conversion");
        DefRoRCivRes.Add("Bribery (Gold Replace)");// Allows paying missing cost with gold.
        DefRoRCivRes.Add("Unused (Building Limit)");
        DefRoRCivRes.Add("Unused (Food Limit)");
        DefRoRCivRes.Add("Unit Limit");
        DefRoRCivRes.Add("Food Maintenance");
        DefRoRCivRes.Add("Faith");
        DefRoRCivRes.Add("Faith Recharging Rate");
        DefRoRCivRes.Add("Farm Food Amount");
        DefRoRCivRes.Add("Civilian Population");
        DefRoRCivRes.Add("Unused");
        DefRoRCivRes.Add("All Techs Achieved");
        DefRoRCivRes.Add("Military Population");
        DefRoRCivRes.Add("Conversions");
        DefRoRCivRes.Add("Standing Wonders");
        DefRoRCivRes.Add("Razings");
        DefRoRCivRes.Add("Kill Ratio");
        DefRoRCivRes.Add("Survival to Finish");
        DefRoRCivRes.Add("Tribute Inefficiency");
        DefRoRCivRes.Add("Gold Mining Productivity");
        DefRoRCivRes.Add("Town Center Unavailable");
        DefRoRCivRes.Add("Gold Counter");
        DefRoRCivRes.Add("Reveal Ally");
        DefRoRCivRes.Add("Unused (Houses)");
        DefRoRCivRes.Add("Temples");
        DefRoRCivRes.Add("Tribute Sent");
        DefRoRCivRes.Add("All Ruins Captured");
        DefRoRCivRes.Add("All Artifacts Captured");
        DefRoRCivRes.Add("RoR: Heal Bonus");
        DefRoRCivRes.Add("RoR: Martyrdom");

        // AoK & TC
        DefAoE2Armors.Add("0 - Unused");
        DefAoE2Armors.Add("1 - Infantry");  // Selection 2
        DefAoE2Armors.Add("2 - Turtle Ships");
        DefAoE2Armors.Add("3 - Base Pierce");
        DefAoE2Armors.Add("4 - Base Melee");
        DefAoE2Armors.Add("5 - War Elephants");
        DefAoE2Armors.Add("6 - Unused");
        DefAoE2Armors.Add("7 - Unused");
        DefAoE2Armors.Add("8 - Cavalry");
        DefAoE2Armors.Add("9 - Unused");
        DefAoE2Armors.Add("10 - Unused");
        DefAoE2Armors.Add("11 - All Buildings (except Port)");
        DefAoE2Armors.Add("12 - Unused");
        DefAoE2Armors.Add("13 - Stone Defense");
        DefAoE2Armors.Add("14 - FE Predator Animals"); // FE
        DefAoE2Armors.Add("15 - Archers");
        DefAoE2Armors.Add("16 - Ships & Camels & Saboteurs");
        DefAoE2Armors.Add("17 - Rams");
        DefAoE2Armors.Add("18 - Trees");
        DefAoE2Armors.Add("19 - Unique Units (except Turtle Ship)");
        DefAoE2Armors.Add("20 - Siege Weapons");
        DefAoE2Armors.Add("21 - Standard Buildings");
        DefAoE2Armors.Add("22 - Walls & Gates");
        DefAoE2Armors.Add("23 - FE Gunpowder Units"); // FE
        DefAoE2Armors.Add("24 - Boars");
        DefAoE2Armors.Add("25 - Monks");
        DefAoE2Armors.Add("26 - Castle");
        DefAoE2Armors.Add("27 - Spearmen");
        DefAoE2Armors.Add("28 - Cavalry Archers");
        DefAoE2Armors.Add("29 - Eagle Warriors");
        DefAoE2Armors.Add("30 - HD Camels");
        DefAoE2TerrainRests.Add("All");
        DefAoE2TerrainRests.Add("Land + shallows");
        DefAoE2TerrainRests.Add("Beach");
        DefAoE2TerrainRests.Add("Water");
        DefAoE2TerrainRests.Add("Land");
        DefAoE2TerrainRests.Add("Nothing");
        DefAoE2TerrainRests.Add("Water");
        DefAoE2TerrainRests.Add("All - water");
        DefAoE2TerrainRests.Add("Land - farm");
        DefAoE2TerrainRests.Add("Nothing");
        DefAoE2TerrainRests.Add("Land + beach");
        DefAoE2TerrainRests.Add("Land - farm");
        DefAoE2TerrainRests.Add("All - water bridge");
        DefAoE2TerrainRests.Add("Water");
        DefAoE2TerrainRests.Add("All - water bridge");
        DefAoE2TerrainRests.Add("Water");
        DefAoE2TerrainRests.Add("Grass + beach");
        DefAoE2TerrainRests.Add("Water (+bridge) - beach");
        DefAoE2TerrainRests.Add("All - water bridge");
        DefAoE2TerrainRests.Add("Only water + ice");
        DefAoE2TerrainRests.Add("All - water");
        DefAoE2TerrainRests.Add("Shallow water");
        DefAoKCivRes.Add("Food Storage");
        DefAoKCivRes.Add("Wood Storage");
        DefAoKCivRes.Add("Stone Storage");
        DefAoKCivRes.Add("Gold Storage");
        DefAoKCivRes.Add("Population Headroom");
        DefAoKCivRes.Add("Conversion Range");
        DefAoKCivRes.Add("Current Age");
        DefAoKCivRes.Add("Relics Captured");
        DefAoKCivRes.Add("Unused (Trade Bonus)");
        DefAoKCivRes.Add("Trade Goods");
        DefAoKCivRes.Add("Unused (Trade Production)");
        DefAoKCivRes.Add("Current Population");
        DefAoKCivRes.Add("Corpse Decay Time");
        DefAoKCivRes.Add("Remarkable Discovery");
        DefAoKCivRes.Add("Monuments Captured");
        DefAoKCivRes.Add("Meat Storage");
        DefAoKCivRes.Add("Berry Storage");
        DefAoKCivRes.Add("Fish Storage");
        DefAoKCivRes.Add("Unused");
        DefAoKCivRes.Add("Total Units Owned");
        DefAoKCivRes.Add("Units Killed");
        DefAoKCivRes.Add("Technology Count");
        DefAoKCivRes.Add("% Map Explored");
        DefAoKCivRes.Add("Castle Age Tech ID");
        DefAoKCivRes.Add("Imperial Age Tech ID");
        DefAoKCivRes.Add("Feudal Age Tech ID");
        DefAoKCivRes.Add("Attack Warning Sound ID");
        DefAoKCivRes.Add("Enable Monk Conversion");
        DefAoKCivRes.Add("Enable Building Conversion");
        DefAoKCivRes.Add("Unused");
        DefAoKCivRes.Add("Unused (Building Limit)");
        DefAoKCivRes.Add("Unused (Food Limit)");
        DefAoKCivRes.Add("Bonus Population Cap");
        DefAoKCivRes.Add("Food Maintenance");
        DefAoKCivRes.Add("Faith");
        DefAoKCivRes.Add("Faith Recharging Rate");
        DefAoKCivRes.Add("Farm Food Amount");
        DefAoKCivRes.Add("Civilian Population");
        DefAoKCivRes.Add("Unused");
        DefAoKCivRes.Add("All Techs Achieved");
        DefAoKCivRes.Add("Military Population");
        DefAoKCivRes.Add("Conversions");
        DefAoKCivRes.Add("Standing Wonders");
        DefAoKCivRes.Add("Razings");
        DefAoKCivRes.Add("Kill Ratio");
        DefAoKCivRes.Add("Survival to Finish");
        DefAoKCivRes.Add("Tribute Inefficiency");
        DefAoKCivRes.Add("Gold Mining Productivity");
        DefAoKCivRes.Add("Town Center Unavailable");
        DefAoKCivRes.Add("Gold Counter");
        DefAoKCivRes.Add("Reveal Ally");
        DefAoKCivRes.Add("Unused (Houses)");
        DefAoKCivRes.Add("Monasteries");
        DefAoKCivRes.Add("Tribute Sent");
        DefAoKCivRes.Add("All Monuments Captured");
        DefAoKCivRes.Add("All Relics Captured");
        DefAoKCivRes.Add("Ore Storage");
        DefAoKCivRes.Add("Kidnap Storage");
        DefAoKCivRes.Add("Dark Age Tech ID");
        DefAoKCivRes.Add("Unused (Trade Good Quality)");
        DefAoKCivRes.Add("Unused (Trade Market Level)");
        DefAoKCivRes.Add("Unused (Formations)");
        DefAoKCivRes.Add("Building Housing Rate");
        DefAoKCivRes.Add("Tax Gather Rate");
        DefAoKCivRes.Add("Gather Accumulator");
        DefAoKCivRes.Add("Salvage Decay Rate");
        DefAoKCivRes.Add("Unused (Allow Formations)");
        DefAoKCivRes.Add("Can Convert");
        DefAoKCivRes.Add("Hit Points Killed");
        DefAoKCivRes.Add("Killed P1");
        DefAoKCivRes.Add("Killed P2");
        DefAoKCivRes.Add("Killed P3");
        DefAoKCivRes.Add("Killed P4");
        DefAoKCivRes.Add("Killed P5");
        DefAoKCivRes.Add("Killed P6");
        DefAoKCivRes.Add("Killed P7");
        DefAoKCivRes.Add("Killed P8");
        DefAoKCivRes.Add("Conversion Resistance");
        DefAoKCivRes.Add("Trade Vig Rate");
        DefAoKCivRes.Add("Stone Mining Productivity");
        DefAoKCivRes.Add("Queued Units");
        DefAoKCivRes.Add("Training Count");
        DefAoKCivRes.Add("Start with Unit 444 (PTWC)");
        DefAoKCivRes.Add("Boarding Recharge Rate");
        DefAoKCivRes.Add("Starting Villagers");
        DefAoKCivRes.Add("Research Cost Modifier");
        DefAoKCivRes.Add("Research Time Modifier");
        DefAoKCivRes.Add("Convert Boats");
        DefAoKCivRes.Add("Fish Trap Food Amount");
        DefAoKCivRes.Add("Heal Rate Modifier");
        DefAoKCivRes.Add("Healing Range"); // 90 alpha ends here
        DefAoKCivRes.Add("Starting Food");
        DefAoKCivRes.Add("Starting Wood");
        DefAoKCivRes.Add("Starting Stone");
        DefAoKCivRes.Add("Starting Gold");
        DefAoKCivRes.Add("Enable PTWC / Kidnap / Loot");
        DefAoKCivRes.Add("Berserker Heal Timer");
        DefAoKCivRes.Add("Dominant Sheep Control");
        DefAoKCivRes.Add("Building Cost Sum");
        DefAoKCivRes.Add("Tech Cost Sum");
        DefAoKCivRes.Add("Relic Income Sum");
        DefAoKCivRes.Add("Trade Income Sum");
        DefAoKCivRes.Add("P1 Tribute");
        DefAoKCivRes.Add("P2 Tribute");
        DefAoKCivRes.Add("P3 Tribute");
        DefAoKCivRes.Add("P4 Tribute");
        DefAoKCivRes.Add("P5 Tribute");
        DefAoKCivRes.Add("P6 Tribute");
        DefAoKCivRes.Add("P7 Tribute");
        DefAoKCivRes.Add("P8 Tribute");
        DefAoKCivRes.Add("P1 Kill Value");
        DefAoKCivRes.Add("P2 Kill Value");
        DefAoKCivRes.Add("P3 Kill Value");
        DefAoKCivRes.Add("P4 Kill Value");
        DefAoKCivRes.Add("P5 Kill Value");
        DefAoKCivRes.Add("P6 Kill Value");
        DefAoKCivRes.Add("P7 Kill Value");
        DefAoKCivRes.Add("P8 Kill Value");
        DefAoKCivRes.Add("P1 Razings");
        DefAoKCivRes.Add("P2 Razings");
        DefAoKCivRes.Add("P3 Razings");
        DefAoKCivRes.Add("P4 Razings");
        DefAoKCivRes.Add("P5 Razings");
        DefAoKCivRes.Add("P6 Razings");
        DefAoKCivRes.Add("P7 Razings");
        DefAoKCivRes.Add("P8 Razings");
        DefAoKCivRes.Add("P1 Razing Value");
        DefAoKCivRes.Add("P2 Razing Value");
        DefAoKCivRes.Add("P3 Razing Value");
        DefAoKCivRes.Add("P4 Razing Value");
        DefAoKCivRes.Add("P5 Razing Value");
        DefAoKCivRes.Add("P6 Razing Value");
        DefAoKCivRes.Add("P7 Razing Value");
        DefAoKCivRes.Add("P8 Razing Value");
        DefAoKCivRes.Add("Standing Castles");
        DefAoKCivRes.Add("Hit Points Razed");
        DefAoKCivRes.Add("Kills by P1");
        DefAoKCivRes.Add("Kills by P2");
        DefAoKCivRes.Add("Kills by P3");
        DefAoKCivRes.Add("Kills by P4");
        DefAoKCivRes.Add("Kills by P5");
        DefAoKCivRes.Add("Kills by P6");
        DefAoKCivRes.Add("Kills by P7");
        DefAoKCivRes.Add("Kills by P8");
        DefAoKCivRes.Add("Razings by P1");
        DefAoKCivRes.Add("Razings by P2");
        DefAoKCivRes.Add("Razings by P3");
        DefAoKCivRes.Add("Razings by P4");
        DefAoKCivRes.Add("Razings by P5");
        DefAoKCivRes.Add("Razings by P6");
        DefAoKCivRes.Add("Razings by P7");
        DefAoKCivRes.Add("Razings by P8");
        DefAoKCivRes.Add("Value Killed by Others");
        DefAoKCivRes.Add("Value Razed by Others");
        DefAoKCivRes.Add("Killed by Others");
        DefAoKCivRes.Add("Razed by Others");
        DefAoKCivRes.Add("Tribute from P1");
        DefAoKCivRes.Add("Tribute from P2");
        DefAoKCivRes.Add("Tribute from P3");
        DefAoKCivRes.Add("Tribute from P4");
        DefAoKCivRes.Add("Tribute from P5");
        DefAoKCivRes.Add("Tribute from P6");
        DefAoKCivRes.Add("Tribute from P7");
        DefAoKCivRes.Add("Tribute from P8");
        DefAoKCivRes.Add("Value Current Units");
        DefAoKCivRes.Add("Value Current Buildings");
        DefAoKCivRes.Add("Food Total");
        DefAoKCivRes.Add("Wood Total");
        DefAoKCivRes.Add("Stone Total");
        DefAoKCivRes.Add("Gold Total");
        DefAoKCivRes.Add("Total Value of Kills");
        DefAoKCivRes.Add("Total Tribute Received");
        DefAoKCivRes.Add("Total Value of Razings");
        DefAoKCivRes.Add("Total Castles Built");
        DefAoKCivRes.Add("Total Wonders Built");
        DefAoKCivRes.Add("Tribute Score");
        DefAoKCivRes.Add("Convert Min Adjustment");
        DefAoKCivRes.Add("Convert Max Adjustment");
        DefAoKCivRes.Add("Convert Resist Min Adjustment");
        DefAoKCivRes.Add("Convert Resist Max Adjustment");
        DefAoKCivRes.Add("Convert Building Min");
        DefAoKCivRes.Add("Convert Building Max");
        DefAoKCivRes.Add("Convert Building Chance");
        DefAoKCivRes.Add("Reveal Enemy");
        DefAoKCivRes.Add("Value Wonders Castles"); // 184 beta ends here
        DefAoKCivRes.Add("Food Score");
        DefAoKCivRes.Add("Wood Score");
        DefAoKCivRes.Add("Stone Score");
        DefAoKCivRes.Add("Gold Score");
        DefAoKCivRes.Add("TC: Chopping Productivity");
        DefAoKCivRes.Add("TC: Food-gathering Productivity");
        DefAoKCivRes.Add("TC: Relic Gold Production Rate");
        DefAoKCivRes.Add("TC: Converted Units Die");
        DefAoKCivRes.Add("TC: Theocracy");
        DefAoKCivRes.Add("TC: Crenellations");
        DefAoKCivRes.Add("TC: Construction Rate Modifier");
        DefAoKCivRes.Add("TC: Hun Wonder Bonus");
        DefAoKCivRes.Add("TC: Spies Discount"); // 197 The Conquerors ends here
        DefAoKCivRes.Add("AK: Unused");
        DefAoKCivRes.Add("AK: Unused");
        DefAoKCivRes.Add("AK: Unused");
        DefAoKCivRes.Add("AK: Unused");
        DefAoKCivRes.Add("AK: Unused");
        DefAoKCivRes.Add("AK: Unused");
        DefAoKCivRes.Add("AK: Unused");
        DefAoKCivRes.Add("AK: Feitoria Food Productivity");
        DefAoKCivRes.Add("AK: Feitoria Wood Productivity");
        DefAoKCivRes.Add("AK: Feitoria Stone Productivity");
        DefAoKCivRes.Add("AK: Feitoria Gold Productivity");
        DefAoKCivRes.Add("RR: Reveal Enemy Town Centers");
        DefAoKCivRes.Add("RR: Relics Visible on Map");

        // SWGB & CC
        DefSWGBArmors.Add("0 - Aircraft");  // Selection 1
        // Airspeeder
        // AIR SHIPS!!!
        // Geonosian Warrior
        // Wild Gungan Flyer
        DefSWGBArmors.Add("1 - Heavy Assault Machines");    // Selection 2
        // Assault Mech
        // AT-AT
        // Blizzards
        DefSWGBArmors.Add("2 - Heavy Weapons");
        // Undeployed Cannon
        // Artillery
        // A-A Mobiles
        // Pummels
        // Strike Mechs
        // Mech Destroyers
        // Cannon
        // Decimator
        // AT-AT
        // Echo Base Ion Cannon
        // Blizzards
        // Evok Catapult
        DefSWGBArmors.Add("3 - Base Ranged/DuraArmor");
        DefSWGBArmors.Add("4 - Base Melee/Armor");
        DefSWGBArmors.Add("5 - Jedis & Bounty Hunters");
        // Jedi
        // Jedi with Holocron
        // Bounty Hunter
        DefSWGBArmors.Add("6 - Assault Machines");
        // Destroyer Droids
        // Strike Mechs
        // Mech Destroyers
        // Assault Mechs
        // Scouts
        // Jabba's Sail Barge
        // Desert Skiff
        // Decimator
        // AT-AT
        // Blizzards
        DefSWGBArmors.Add("7 - Decimators");
        // Assault Mechs
        // Decimator
        // AT-AT
        // Blizzards
        DefSWGBArmors.Add("8 - Shield & Power Units");
        // Power Cores
        // Shield Wall
        // Shield Generators
        // Droid Storage Facility
        // Power Droids
        // Echo Base Power Generator
        DefSWGBArmors.Add("9 - Ships");
        // Utility Trawler
        // Frigates
        // Cruisers
        // Destroyers
        // A-A Destroyers
        // Transport Ships
        DefSWGBArmors.Add("10 - Submarines");
        // Frigates
        // Underwater Prefab Shelters
        // Gungan Buildings
        DefSWGBArmors.Add("11 - All Buildings");
        // BUILDINGS!!!
        DefSWGBArmors.Add("12 - Unused");
        DefSWGBArmors.Add("13 - Defense Buildings");
        // Gate
        // Turrets
        // A-A Turrets
        // Echo Base Ion Cannon
        // Fortress
        // Theed Arch
        DefSWGBArmors.Add("14 - Troopers");
        // Royal Crusaders
        // Berserker
        // Chewbacca
        // Bounty Hunter
        // Troopers
        // Mounted Troopers
        // Grenade Trooper
        // A-A Troopers
        // Acklay
        // Nexu
        // Klaatu
        // Nikito
        // Reek
        // Rancor
        DefSWGBArmors.Add("15 - Mounted Troopers");
        // Berserker
        // Scouts
        // Mounted Troopers
        // Anakin's Podracer
        // Landspeeder
        // Sebulba's Podracer
        // Skyhopper
        DefSWGBArmors.Add("16 - Cruisers");
        // Cruisers
        DefSWGBArmors.Add("17 - Pummels & Cannons");
        // Undeployed Cannon
        // Pummels
        // Cannon
        DefSWGBArmors.Add("18 - Unused");
        DefSWGBArmors.Add("19 - Workers");
        // B'omarr Temple
        // Underwater Prefab Shelters
        // Asteroid Supply Depot
        // Boorka's Palace
        // Adv A-A Turret
        // Reytha Soldier
        // Mara Jade
        // R2-D2
        // Battleship Cores
        // Landed Freighter
        // Han Solo on Tauntaun
        DefSWGBArmors.Add("20 - Destroyers");
        // Destroyers
        DefSWGBArmors.Add("21 - Standard Buildings");
        // BUILDINGS!!!
        DefSWGBArmors.Add("22 - Walls & Gates");
        // GATES
        // WALLS
        // Theed Arch
        DefSWGBArmors.Add("23 - Air Cruisers");
        // Air Cruisers
        // Blockade Runner
        // Star Destroyer
        // Deathstar
        DefSWGBArmors.Add("24 - Wild Animals");
        // Wild Fambaa
        // Acklay
        // Falumpaset
        // Nexu
        // Reek
        // Dewback
        // Ronto
        // Fambaa
        // Massif
        // Orray
        // Shaak
        // Rancor
        DefSWGBArmors.Add("25 - Unused");
        DefSWGBArmors.Add("26 - Fortress");
        // Fortress
        DefSWGBArmors.Add("27 - Unused");
        DefSWGBArmors.Add("28 - Unused");
        DefSWGBArmors.Add("29 - Unused");
        DefSWGBArmors.Add("30 - Tame Animals"); // Selection 31
        // Fambaa Shield Generators
        // Wild Fambaa
        // Kaadu
        // Tauntaun
        // Cu-pa
        // Womp Rat
        DefSWGBTerrainRests.Add("All");
        DefSWGBTerrainRests.Add("Land + unbuildable");
        DefSWGBTerrainRests.Add("Shore");
        DefSWGBTerrainRests.Add("Water");
        DefSWGBTerrainRests.Add("Land");
        DefSWGBTerrainRests.Add("Land + shore, impassable water");
        DefSWGBTerrainRests.Add("Water + ice2 - swamp");
        DefSWGBTerrainRests.Add("Land - water, lava");
        DefSWGBTerrainRests.Add("Land - water, lava, farm");
        DefSWGBTerrainRests.Add("Only water");
        DefSWGBTerrainRests.Add("Land - shore");
        DefSWGBTerrainRests.Add("Land - water, lava, farm");
        DefSWGBTerrainRests.Add("All - lava");
        DefSWGBTerrainRests.Add("Water");
        DefSWGBTerrainRests.Add("All - lava");
        DefSWGBTerrainRests.Add("Land + shore, impassable water");
        DefSWGBTerrainRests.Add("Grass + shore");
        DefSWGBTerrainRests.Add("Water - shore + impassable water");
        DefSWGBTerrainRests.Add("All - impassable water, lava");
        DefSWGBTerrainRests.Add("Land + shore, impassable water");
        DefSWGBTerrainRests.Add("Land + shore, impassable water");
        DefSWGBTerrainRests.Add("Water - deep water");
        DefSWGBTerrainRests.Add("All - impassable water, lava");
        DefSWGBTerrainRests.Add("No restriction");
        DefSWGBTerrainRests.Add("Only water");
        DefSWGBTerrainRests.Add("Land + shore, impassable water");
        DefSWGBTerrainRests.Add("Land + shore, impassable water");
        DefSWGBTerrainRests.Add("Deep water");
        DefSWGBTerrainRests.Add("Wasteland");
        DefSWGBTerrainRests.Add("Ice");
        DefSWGBTerrainRests.Add("Lava");
        DefSWGBTerrainRests.Add("Water2");
        DefSWGBTerrainRests.Add("Rock4");
        DefSWGBCivRes.Add("Food Storage");
        DefSWGBCivRes.Add("Carbon Storage");
        DefSWGBCivRes.Add("Ore Storage");
        DefSWGBCivRes.Add("Nova Storage");
        DefSWGBCivRes.Add("Population Headroom");
        DefSWGBCivRes.Add("Conversion Range");
        DefSWGBCivRes.Add("Current Tech Level");
        DefSWGBCivRes.Add("Holocrons Captured");
        DefSWGBCivRes.Add("Unused (Trade Bonus)");
        DefSWGBCivRes.Add("Trade Goods");
        DefSWGBCivRes.Add("Recharge Rate of Shields");
        DefSWGBCivRes.Add("Current Population");
        DefSWGBCivRes.Add("Corpse Decay Time");
        DefSWGBCivRes.Add("Remarkable Discovery");
        DefSWGBCivRes.Add("Monuments Captured");
        DefSWGBCivRes.Add("Meat Storage");
        DefSWGBCivRes.Add("Berry Storage");
        DefSWGBCivRes.Add("Fish Storage");
        DefSWGBCivRes.Add("Power Core Range");
        DefSWGBCivRes.Add("Total Units Owned");
        DefSWGBCivRes.Add("Units Killed");
        DefSWGBCivRes.Add("Technology Count");
        DefSWGBCivRes.Add("% Map Explored");
        DefSWGBCivRes.Add("Submarine Detection");
        DefSWGBCivRes.Add("Shield Generator Range");
        DefSWGBCivRes.Add("Unknown");
        DefSWGBCivRes.Add("Drop-off Time of Shields");
        DefSWGBCivRes.Add("Enable Jedi Conversion");
        DefSWGBCivRes.Add("Enable Building Conversion");
        DefSWGBCivRes.Add("Unknown");
        DefSWGBCivRes.Add("Unused (Building Limit)");
        DefSWGBCivRes.Add("Enable A-A Attack for AT-AT");
        DefSWGBCivRes.Add("Bonus Population Cap");
        DefSWGBCivRes.Add("Power Core Shielding");
        DefSWGBCivRes.Add("Force");
        DefSWGBCivRes.Add("Force Recharging Rate");
        DefSWGBCivRes.Add("Farm Food Amount");
        DefSWGBCivRes.Add("Civilian Population");
        DefSWGBCivRes.Add("Shields On for Bombers/Fighters");
        DefSWGBCivRes.Add("All Techs Achieved");
        DefSWGBCivRes.Add("Military Population");
        DefSWGBCivRes.Add("Conversions");
        DefSWGBCivRes.Add("Standing Monuments");
        DefSWGBCivRes.Add("Razings");
        DefSWGBCivRes.Add("Kill Ratio");
        DefSWGBCivRes.Add("Survival to Finish");
        DefSWGBCivRes.Add("Tribute Inefficiency");
        DefSWGBCivRes.Add("Nova Mining Productivity");
        DefSWGBCivRes.Add("Town Center Unavailable");
        DefSWGBCivRes.Add("Gold Counter");
        DefSWGBCivRes.Add("Reveal Ally");
        DefSWGBCivRes.Add("Shielding");
        DefSWGBCivRes.Add("Monasteries");
        DefSWGBCivRes.Add("Tribute Sent");
        DefSWGBCivRes.Add("All Ruins Captured");
        DefSWGBCivRes.Add("All Relics Captured");
        DefSWGBCivRes.Add("Enable Stealth for Masters");
        DefSWGBCivRes.Add("Kidnap Storage");
        DefSWGBCivRes.Add("Masters Can See Hidden Units");
        DefSWGBCivRes.Add("Trade Good Quality");
        DefSWGBCivRes.Add("Trade Market Level");
        DefSWGBCivRes.Add("Unused (Formations)");
        DefSWGBCivRes.Add("Building Housing Rate");
        DefSWGBCivRes.Add("Tax Gather Rate");
        DefSWGBCivRes.Add("Gather Accumulator");
        DefSWGBCivRes.Add("Salvage Decay Rate");
        DefSWGBCivRes.Add("Unused (Allow Formations)");
        DefSWGBCivRes.Add("Can Convert");
        DefSWGBCivRes.Add("Hit Points Killed");
        DefSWGBCivRes.Add("Killed P1");
        DefSWGBCivRes.Add("Killed P2");
        DefSWGBCivRes.Add("Killed P3");
        DefSWGBCivRes.Add("Killed P4");
        DefSWGBCivRes.Add("Killed P5");
        DefSWGBCivRes.Add("Killed P6");
        DefSWGBCivRes.Add("Killed P7");
        DefSWGBCivRes.Add("Killed P8");
        DefSWGBCivRes.Add("Conversion Resistance");
        DefSWGBCivRes.Add("Trade Vig Rate");
        DefSWGBCivRes.Add("Ore Mining Productivity");
        DefSWGBCivRes.Add("Queued Units");
        DefSWGBCivRes.Add("Training Count");
        DefSWGBCivRes.Add("Start with Packed Town Center");
        DefSWGBCivRes.Add("Boarding Recharge Rate");
        DefSWGBCivRes.Add("Starting Villagers");
        DefSWGBCivRes.Add("Tech Cost Modifier");
        DefSWGBCivRes.Add("Tech Time Modifier");
        DefSWGBCivRes.Add("Concentration");
        DefSWGBCivRes.Add("Fish Trap Food Amount");
        DefSWGBCivRes.Add("Medic Healing Rate");
        DefSWGBCivRes.Add("Healing Range");
        DefSWGBCivRes.Add("Starting Food");
        DefSWGBCivRes.Add("Starting Carbon");
        DefSWGBCivRes.Add("Starting Ore");
        DefSWGBCivRes.Add("Starting Nova");
        DefSWGBCivRes.Add("Enable PTWC / Kidnap / Loot");
        DefSWGBCivRes.Add("Berserker Heal Timer");
        DefSWGBCivRes.Add("Dominant Sheep Control");
        DefSWGBCivRes.Add("Object Cost Sum");
        DefSWGBCivRes.Add("Tech Cost Sum");
        DefSWGBCivRes.Add("Holocron Nova Sum");
        DefSWGBCivRes.Add("Trade Income Sum");
        DefSWGBCivRes.Add("P1 Tribute");
        DefSWGBCivRes.Add("P2 Tribute");
        DefSWGBCivRes.Add("P3 Tribute");
        DefSWGBCivRes.Add("P4 Tribute");
        DefSWGBCivRes.Add("P5 Tribute");
        DefSWGBCivRes.Add("P6 Tribute");
        DefSWGBCivRes.Add("P7 Tribute");
        DefSWGBCivRes.Add("P8 Tribute");
        DefSWGBCivRes.Add("P1 Kill Value");
        DefSWGBCivRes.Add("P2 Kill Value");
        DefSWGBCivRes.Add("P3 Kill Value");
        DefSWGBCivRes.Add("P4 Kill Value");
        DefSWGBCivRes.Add("P5 Kill Value");
        DefSWGBCivRes.Add("P6 Kill Value");
        DefSWGBCivRes.Add("P7 Kill Value");
        DefSWGBCivRes.Add("P8 Kill Value");
        DefSWGBCivRes.Add("P1 Razings");
        DefSWGBCivRes.Add("P2 Razings");
        DefSWGBCivRes.Add("P3 Razings");
        DefSWGBCivRes.Add("P4 Razings");
        DefSWGBCivRes.Add("P5 Razings");
        DefSWGBCivRes.Add("P6 Razings");
        DefSWGBCivRes.Add("P7 Razings");
        DefSWGBCivRes.Add("P8 Razings");
        DefSWGBCivRes.Add("P1 Razing Value");
        DefSWGBCivRes.Add("P2 Razing Value");
        DefSWGBCivRes.Add("P3 Razing Value");
        DefSWGBCivRes.Add("P4 Razing Value");
        DefSWGBCivRes.Add("P5 Razing Value");
        DefSWGBCivRes.Add("P6 Razing Value");
        DefSWGBCivRes.Add("P7 Razing Value");
        DefSWGBCivRes.Add("P8 Razing Value");
        DefSWGBCivRes.Add("Standing Fortresses");
        DefSWGBCivRes.Add("Hit Points Razed");
        DefSWGBCivRes.Add("Kills by P1");
        DefSWGBCivRes.Add("Kills by P2");
        DefSWGBCivRes.Add("Kills by P3");
        DefSWGBCivRes.Add("Kills by P4");
        DefSWGBCivRes.Add("Kills by P5");
        DefSWGBCivRes.Add("Kills by P6");
        DefSWGBCivRes.Add("Kills by P7");
        DefSWGBCivRes.Add("Kills by P8");
        DefSWGBCivRes.Add("Razings by P1");
        DefSWGBCivRes.Add("Razings by P2");
        DefSWGBCivRes.Add("Razings by P3");
        DefSWGBCivRes.Add("Razings by P4");
        DefSWGBCivRes.Add("Razings by P5");
        DefSWGBCivRes.Add("Razings by P6");
        DefSWGBCivRes.Add("Razings by P7");
        DefSWGBCivRes.Add("Razings by P8");
        DefSWGBCivRes.Add("Value Killed by Others");
        DefSWGBCivRes.Add("Value Razed by Others");
        DefSWGBCivRes.Add("Killed by Others");
        DefSWGBCivRes.Add("Razed by Others");
        DefSWGBCivRes.Add("Tribute from P1");
        DefSWGBCivRes.Add("Tribute from P2");
        DefSWGBCivRes.Add("Tribute from P3");
        DefSWGBCivRes.Add("Tribute from P4");
        DefSWGBCivRes.Add("Tribute from P5");
        DefSWGBCivRes.Add("Tribute from P6");
        DefSWGBCivRes.Add("Tribute from P7");
        DefSWGBCivRes.Add("Tribute from P8");
        DefSWGBCivRes.Add("Value Current Units");
        DefSWGBCivRes.Add("Value Current Buildings");
        DefSWGBCivRes.Add("Food Total");
        DefSWGBCivRes.Add("Carbon Total");
        DefSWGBCivRes.Add("Ore Total");
        DefSWGBCivRes.Add("Nova Total");
        DefSWGBCivRes.Add("Total Value of Kills");
        DefSWGBCivRes.Add("Total Tribute Received");
        DefSWGBCivRes.Add("Total Value of Razings");
        DefSWGBCivRes.Add("Total Fortresses Built");
        DefSWGBCivRes.Add("Total Monuments Built");
        DefSWGBCivRes.Add("Tribute Score");
        DefSWGBCivRes.Add("Convert Min Adjustment");
        DefSWGBCivRes.Add("Convert Max Adjustment");
        DefSWGBCivRes.Add("Convert Resist Min Adjustment");
        DefSWGBCivRes.Add("Convert Resist Max Adjustment");
        DefSWGBCivRes.Add("Convert Building Min");
        DefSWGBCivRes.Add("Convert Building Max");
        DefSWGBCivRes.Add("Convert Building Chance");
        DefSWGBCivRes.Add("Reveal Enemy");
        DefSWGBCivRes.Add("Value Wonders Castles");
        DefSWGBCivRes.Add("Food Score");
        DefSWGBCivRes.Add("Carbon Score");
        DefSWGBCivRes.Add("Ore Score");
        DefSWGBCivRes.Add("Nova Score");
        DefSWGBCivRes.Add("Carbon Gathering Productivity");
        DefSWGBCivRes.Add("Food-gathering Productivity");
        DefSWGBCivRes.Add("Holocron Nova Production Rate");
        DefSWGBCivRes.Add("Converted Units Die");
        DefSWGBCivRes.Add("Meditation");
        DefSWGBCivRes.Add("Crenellations");
        DefSWGBCivRes.Add("Construction Rate Modifier");
        DefSWGBCivRes.Add("Biological Self Regeneration");
        DefSWGBCivRes.Add("Spies Discount");
        DefSWGBCivRes.Add("Unknown");
        DefSWGBCivRes.Add("Unknown");
        DefSWGBCivRes.Add("Misc Counter 1");
        DefSWGBCivRes.Add("Misc Counter 2");
        DefSWGBCivRes.Add("Misc Counter 3");
        DefSWGBCivRes.Add("Misc Counter 4");
        DefSWGBCivRes.Add("Misc Counter 5");
        DefSWGBCivRes.Add("Unknown");
        DefSWGBCivRes.Add("Unknown");
        DefSWGBCivRes.Add("Unknown");
        DefSWGBCivRes.Add("Unknown");
        DefSWGBCivRes.Add("Unknown");
        DefSWGBCivRes.Add("CC: Unknown");

        wxFileConfig Customs("", "", "AGE3NamesV0004.ini", "", wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
        long AoE1Count, AoE2Count, SWGBCount, AoE1CountTR, AoE2CountTR, SWGBCountTR, RoRCountCR, AoKCountCR, SWGBCountCR;
        if(!Customs.Read("Count/AoE1Count", &AoE1Count, DefAoE1Armors.GetCount()))
            Customs.Write("Count/AoE1Count", (int)DefAoE1Armors.GetCount());
        if(!Customs.Read("Count/AoE2Count", &AoE2Count, DefAoE2Armors.GetCount()))
            Customs.Write("Count/AoE2Count", (int)DefAoE2Armors.GetCount());
        if(!Customs.Read("Count/SWGBCount", &SWGBCount, DefSWGBArmors.GetCount()))
            Customs.Write("Count/SWGBCount", (int)DefSWGBArmors.GetCount());
        if(!Customs.Read("Count/AoE1TerrainRestrictionCount", &AoE1CountTR, DefAoE1TerrainRests.GetCount()))
            Customs.Write("Count/AoE1TerrainRestrictionCount", (int)DefAoE1TerrainRests.GetCount());
        if(!Customs.Read("Count/AoE2TerrainRestrictionCount", &AoE2CountTR, DefAoE2TerrainRests.GetCount()))
            Customs.Write("Count/AoE2TerrainRestrictionCount", (int)DefAoE2TerrainRests.GetCount());
        if(!Customs.Read("Count/SWGBTerrainRestrictionCount", &SWGBCountTR, DefSWGBTerrainRests.GetCount()))
            Customs.Write("Count/SWGBTerrainRestrictionCount", (int)DefSWGBTerrainRests.GetCount());
        if(!Customs.Read("Count/RoRCivResCount", &RoRCountCR, DefRoRCivRes.GetCount()))
            Customs.Write("Count/RoRCivResCount", (int)DefRoRCivRes.GetCount());
        if(!Customs.Read("Count/AoKCivResCount", &AoKCountCR, DefAoKCivRes.GetCount()))
            Customs.Write("Count/AoKCivResCount", (int)DefAoKCivRes.GetCount());
        if(!Customs.Read("Count/SWGBCivResCount", &SWGBCountCR, DefSWGBCivRes.GetCount()))
            Customs.Write("Count/SWGBCivResCount", (int)DefSWGBCivRes.GetCount());
        wxString read_buf;

        armor_names.Clear();
        armor_names.Add("Unused Type/No Type");
        if(GenieVersion < genie::GV_AoKA) // AoE and RoR
        for(size_t loop = 0; loop < AoE1Count; ++loop)
        {
            if(!Customs.Read("AoE1Names/"+lexical_cast<string>(loop), &read_buf, DefAoE1Armors[loop]))
                Customs.Write("AoE1Names/"+lexical_cast<string>(loop), DefAoE1Armors[loop]);
            armor_names.Add(read_buf);
        }
        else if(GenieVersion < genie::GV_SWGB) // AoK and TC
        for(size_t loop = 0; loop < AoE2Count; ++loop)
        {
            if(!Customs.Read("AoE2Names/"+lexical_cast<string>(loop), &read_buf, DefAoE2Armors[loop]))
                Customs.Write("AoE2Names/"+lexical_cast<string>(loop), DefAoE2Armors[loop]);
            armor_names.Add(read_buf);
        }
        else // SWGB and CC
        for(size_t loop = 0; loop < SWGBCount; ++loop)
        {
            if(!Customs.Read("SWGBNames/"+lexical_cast<string>(loop), &read_buf, DefSWGBArmors[loop]))
                Customs.Write("SWGBNames/"+lexical_cast<string>(loop), DefSWGBArmors[loop]);
            armor_names.Add(read_buf);
        }
        Effects_89_Type_CB1->Flash();
        for(size_t loop = 0; loop < 2; ++loop)
        {
            Attacks_Class_ComboBox[loop]->Flash();
        }

        for(size_t loop = 0; loop < AoE1CountTR; ++loop)
        {
            if(!Customs.Read("AoE1TerrainRestrictionNames/"+lexical_cast<string>(loop), &read_buf, DefAoE1TerrainRests[loop]))
                Customs.Write("AoE1TerrainRestrictionNames/"+lexical_cast<string>(loop), DefAoE1TerrainRests[loop]);
            AoE1TerrainRestrictions.Add(read_buf);
        }
        for(size_t loop = 0; loop < AoE2CountTR; ++loop)
        {
            if(!Customs.Read("AoE2TerrainRestrictionNames/"+lexical_cast<string>(loop), &read_buf, DefAoE2TerrainRests[loop]))
                Customs.Write("AoE2TerrainRestrictionNames/"+lexical_cast<string>(loop), DefAoE2TerrainRests[loop]);
            AoE2TerrainRestrictions.Add(read_buf);
        }
        for(size_t loop = 0; loop < SWGBCountTR; ++loop)
        {
            if(!Customs.Read("SWGBTerrainRestrictionNames/"+lexical_cast<string>(loop), &read_buf, DefSWGBTerrainRests[loop]))
                Customs.Write("SWGBTerrainRestrictionNames/"+lexical_cast<string>(loop), DefSWGBTerrainRests[loop]);
            SWGBTerrainRestrictions.Add(read_buf);
        }
        for(size_t loop = 0; loop < RoRCountCR; ++loop)
        {
            if(!Customs.Read("RoRCivResNames/"+lexical_cast<string>(loop), &read_buf, DefRoRCivRes[loop]))
                Customs.Write("RoRCivResNames/"+lexical_cast<string>(loop), DefRoRCivRes[loop]);
            RoRCivResources.Add(read_buf);
        }
        for(size_t loop = 0; loop < AoKCountCR; ++loop)
        {
            if(!Customs.Read("AoKCivResNames/"+lexical_cast<string>(loop), &read_buf, DefAoKCivRes[loop]))
                Customs.Write("AoKCivResNames/"+lexical_cast<string>(loop), DefAoKCivRes[loop]);
            AoKCivResources.Add(read_buf);
        }
        for(size_t loop = 0; loop < SWGBCountCR; ++loop)
        {
            if(!Customs.Read("SWGBCivResNames/"+lexical_cast<string>(loop), &read_buf, DefSWGBCivRes[loop]))
                Customs.Write("SWGBCivResNames/"+lexical_cast<string>(loop), DefSWGBCivRes[loop]);
            SWGBCivResources.Add(read_buf);
        }

        class_names.Clear();
        class_names.Add("No Class/Invalid Class");   // Selection 0
        if(GenieVersion < genie::GV_SWGB)
        {
            class_names.Add("0 - Archer");
            class_names.Add("1 - Artifact");
            class_names.Add("2 - Trade Boat");
            class_names.Add("3 - Building");
            class_names.Add("4 - Civilian");
            class_names.Add("5 - Ocean Fish");
            class_names.Add("6 - Infantry");
            class_names.Add("7 - Berry Bush");
            class_names.Add("8 - Stone Mine");
            class_names.Add("9 - Prey Animal");
            class_names.Add("10 - Predator Animal");
            class_names.Add("11 - Miscellaneous");
            class_names.Add("12 - Cavalry");
            class_names.Add("13 - Siege Weapon");
            class_names.Add("14 - Terrain");
            class_names.Add("15 - Tree");
            class_names.Add("16 - Tree Stump");
            class_names.Add("17 - Healer");
            class_names.Add(GenieVersion < genie::GV_AoKA ? "18 - Priest" : "18 - Monk");
            class_names.Add("19 - Trade Cart");
            class_names.Add("20 - Transport Boat");
            class_names.Add("21 - Fishing Boat");
            class_names.Add("22 - Warship");
            class_names.Add(GenieVersion < genie::GV_AoKA ? "23 - Chariot Archer" : "23 - Conquistador");
            class_names.Add("24 - War Elephant");
            class_names.Add("25 - Hero");
            class_names.Add("26 - Elephant Archer");
            class_names.Add("27 - Wall");
            class_names.Add("28 - Phalanx");
            class_names.Add("29 - Domestic Animal");
            class_names.Add("30 - Flag");
            class_names.Add("31 - Deep Sea Fish");
            class_names.Add("32 - Gold Mine");
            class_names.Add("33 - Shore Fish");
            class_names.Add("34 - Cliff");
            class_names.Add(GenieVersion < genie::GV_AoKA ? "35 - Chariot" : "35 - Petard");
            class_names.Add("36 - Cavalry Archer");
            class_names.Add("37 - Doppelganger");
            class_names.Add("38 - Bird");
            if(GenieVersion < genie::GV_AoKA)
            {
                class_names.Add("39 - Slinger");
            }
            // Above class names are checked for AoE 1
            else
            {
                class_names.Add("39 - Gate");
                class_names.Add("40 - Salvage Pile");
                class_names.Add("41 - Resource Pile");
                class_names.Add("42 - Relic");
                class_names.Add("43 - Monk with Relic");
                class_names.Add("44 - Hand Cannoneer");
                class_names.Add("45 - Two Handed Swordsman");
                class_names.Add("46 - Pikeman");
                class_names.Add("47 - Scout");
                class_names.Add("48 - Ore Mine");
                class_names.Add("49 - Farm");
                class_names.Add("50 - Spearman");
                class_names.Add("51 - Packed Unit");
                class_names.Add("52 - Tower");
                class_names.Add("53 - Boarding Boat");
                class_names.Add("54 - Unpacked Siege Unit");
                class_names.Add("55 - Ballista");
                class_names.Add("56 - Raider");
                class_names.Add("57 - Cavalry Raider");
                class_names.Add("58 - Livestock");
                class_names.Add("59 - King");
                class_names.Add("60 - Misc Building");
                class_names.Add("61 - Controlled Animal");
            }
            // Above class names are checked for AoE 2
        }
        else
        {
            class_names.Add("0 - Unused");   // Selection 1
            class_names.Add("1 - Nerf/Bantha");
            class_names.Add("2 - Fambaa");
            class_names.Add("3 - Unused");
            class_names.Add("4 - Wild Animal");
            class_names.Add("5 - Monster/Trouble");
            class_names.Add("6 - Wall");
            class_names.Add("7 - Farm");
            class_names.Add("8 - Gate");
            class_names.Add("9 - Fortress/A-A Turret");
            class_names.Add("10 - Turret");
            class_names.Add("11 - Cruiser");
            class_names.Add("12 - Unused");
            class_names.Add("13 - Destroyer");
            class_names.Add("14 - Utility Trawler");
            class_names.Add("15 - Frigate 1");
            class_names.Add("16 - A-A Destroyer 1");
            class_names.Add("17 - Transport Ship");
            class_names.Add("18 - Building");
            class_names.Add("19 - Doppelganger");
            class_names.Add("20 - Other/Dead/Projectile");
            class_names.Add("21 - Command Base");
            class_names.Add("22 - Cliff");
            class_names.Add("23 - Fish");
            class_names.Add("24 - Unused");
            class_names.Add("25 - Shore Fish");
            class_names.Add("26 - Game Engine Stuff");
            class_names.Add("27 - Fruit Bush");
            class_names.Add("28 - Holocron");
            class_names.Add("29 - Nova");
            class_names.Add("30 - Ore");
            class_names.Add("31 - Tree/Carbon");
            class_names.Add("32 - Artillery");
            class_names.Add("33 - A-A Mobile");
            class_names.Add("34 - Undeployed Cannon");
            class_names.Add("35 - Pummel");
            class_names.Add("36 - Cannon");
            class_names.Add("37 - Unused");
            class_names.Add("38 - Unused");
            class_names.Add("39 - Frigate 2");
            class_names.Add("40 - A-A Destroyer 2");
            class_names.Add("41 - Unused");
            class_names.Add("42 - Bridge/Eye Candy");
            class_names.Add("43 - Bomber");
            class_names.Add("44 - Bounty Hunter");
            class_names.Add("45 - Cargo Trader");
            class_names.Add("46 - Mixed 1");
            class_names.Add("47 - Scout");
            class_names.Add("48 - Fighter");
            class_names.Add("49 - Grenade Trooper");
            class_names.Add("50 - Jedi");
            class_names.Add("51 - Jedi with Holocron");
            class_names.Add("52 - Trooper");
            class_names.Add("53 - War Machine");
            class_names.Add("54 - Medic");
            class_names.Add("55 - A-A Trooper");
            class_names.Add("56 - Mounted Trooper");
            class_names.Add("57 - Fambaa Shield Generator");
            class_names.Add("58 - Workers");
            class_names.Add("59 - Air Transport");
            class_names.Add("60 - Domestic Animal");
            class_names.Add("61 - Power Droid");
            class_names.Add("62 - Air Cruiser");
            class_names.Add("63 - Geonosian Warrior");
            class_names.Add("64 - Jedi Starfighter");
        }
        Effects_B_ComboBox->Flash();

        // This is here in case filters will be made game version dependent.
        unit_filters.Clear();
        unit_filters.Add("*Choose*");
        for(wxString &filter: Type20) unit_filters.Add(filter);
        for(wxString &filter: Type30) unit_filters.Add(filter);
        for(wxString &filter: Type40) unit_filters.Add(filter);
        for(wxString &filter: Type50) unit_filters.Add(filter);
        for(wxString &filter: Type60) unit_filters.Add(filter);
        for(wxString &filter: Type70) unit_filters.Add(filter);
        for(wxString &filter: Type80) unit_filters.Add(filter);
        unit_filters.Sort();

        research_filters.Clear();
        research_filters.Add("Lang File Name"); // 0
        research_filters.Add("Internal Name");
        research_filters.Add("Required Techs");
        research_filters.Add("Min. Req. Techs");
        research_filters.Add("Research Location");
        research_filters.Add("Research Time");
        research_filters.Add("Effect");
        research_filters.Add("Type");
        research_filters.Add("Icon");
        research_filters.Add("Button");
        research_filters.Add("Lang Help");
        research_filters.Add("Lang Tech Tree");
        research_filters.Add("Hotkey");
        research_filters.Add("Cost Types");
        research_filters.Add("Cost Amounts");
        research_filters.Add("Cost Uses");
        if(GenieVersion >= genie::GV_AoK)
        {
            research_filters.Add("Civilization");
            research_filters.Add("Full Tech Mode");
            if(GenieVersion >= genie::GV_SWGB)
            research_filters.Add("Internal Name 2");
            if(GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
            research_filters.Add("Repeatable");
        }

        soundfile_filters.Clear();
        soundfile_filters.Add("Filename");   // 0
        soundfile_filters.Add("DRS");
        soundfile_filters.Add("Probability");
        if(GenieVersion >= genie::GV_AoKE3)
        {
            soundfile_filters.Add("Civilization");
            soundfile_filters.Add("Unknown");
        }

        for(size_t loop = 0; loop < 2; ++loop)
        {
            Units_Class_ComboBox[loop]->Flash();
            Units_SearchFilters[loop]->Flash();
            Research_SearchFilters[loop]->Flash();
            Sounds_Items_SearchFilters[loop]->Flash();
        }

        SetStatusText(lexical_cast<string>(dataset->FileVersion), 4);

        effect_attribute_names.Clear();
        effect_attribute_names.Add("No Attribute/Invalid Attribute");     // Selection 0
        effect_attribute_names.Add("0 - Hit Points");     // Selection 1
        effect_attribute_names.Add("1 - Line of Sight");
        effect_attribute_names.Add("2 - Garrison Capacity");
        effect_attribute_names.Add("3 - Unit Size X");
        effect_attribute_names.Add("4 - Unit Size Y");
        effect_attribute_names.Add("5 - Movement Speed (types 20-80)");
        effect_attribute_names.Add("6 - Rotation Speed (types 30-80)");
        effect_attribute_names.Add("7 - Unused");
        if(GenieVersion < genie::GV_AoKA)
        {
            effect_attribute_names.Add("8 - Armor (no multiply, types 50-80)");
            effect_attribute_names.Add("9 - Attack (no multiply, types 50-80)");
        }
        else
        {
            effect_attribute_names.Add("8 - Armor (types 50-80)");
            effect_attribute_names.Add("9 - Attack (types 50-80)");
        }
        effect_attribute_names.Add("10 - Attack Reload Time (types 50-80)");
        effect_attribute_names.Add("11 - Accuracy Percent (types 50-80)");
        effect_attribute_names.Add("12 - Max Range (types 50-80)");
        effect_attribute_names.Add("13 - Work Rate (types 30-80)");
        effect_attribute_names.Add("14 - Carry Capacity");
        effect_attribute_names.Add("15 - Base Armor (types 50-80)");
        effect_attribute_names.Add("16 - Projectile Unit (types 50-80)");
        effect_attribute_names.Add("17 - Icon/Graphics Angle (type 80)");
        effect_attribute_names.Add("18 - Terrain Defense Bonus (always sets, types 50-80)");
        if(GenieVersion < genie::GV_AoEB)
        {
            effect_attribute_names.Add("19 - Unused");
        }
        else
        {
            effect_attribute_names.Add("19 - Enable Smart Projectiles (type 60)");
        }
        if(GenieVersion < genie::GV_AoKA)
        {
            effect_attribute_names.Add("20 - Unused");
            effect_attribute_names.Add("21 - Unused");
            effect_attribute_names.Add("22 - Unused");
            effect_attribute_names.Add("23 - Unused");
            effect_attribute_names.Add("100 - Resource Costs (types 70-80)");
            if(GenieVersion >= genie::GV_RoR)
            effect_attribute_names.Add("101 - Population (set only)");
        }
        else
        {
            effect_attribute_names.Add("20 - Min Range (types 50-80)");
            effect_attribute_names.Add("21 - Amount of 1st resource storage");
            effect_attribute_names.Add("22 - Blast Width (types 50-80)");
            effect_attribute_names.Add("23 - Search Radius (types 40-80)");
            effect_attribute_names.Add("100 - Resource Costs (types 70-80)");
            effect_attribute_names.Add("101 - Train Time (types 70-80)");
            effect_attribute_names.Add("102 - Total Missiles (types 70-80)");
            effect_attribute_names.Add("103 - Food Costs (types 70-80)");
            if(GenieVersion < genie::GV_SWGB)
            {
                effect_attribute_names.Add("104 - Wood Costs (types 70-80)");
                effect_attribute_names.Add("105 - Gold Costs (types 70-80)");
                effect_attribute_names.Add("106 - Stone Costs (types 70-80)");
            }
            else
            {
                effect_attribute_names.Add("104 - Carbon Costs (types 70-80)");
                effect_attribute_names.Add("105 - Nova Costs (types 70-80)");
                effect_attribute_names.Add("106 - Ore Costs (types 70-80)");
            }
            effect_attribute_names.Add("107 - Max Total Missiles (types 70-80)");
            if(GenieVersion >= genie::GV_AoKB)
            effect_attribute_names.Add("108 - Garrison Heal Rate (type 80)");
            if(GenieVersion >= genie::GV_Cysion && GenieVersion <= genie::GV_LatestDE2)
            effect_attribute_names.Add("109 - Regeneration Rate (types 40-80)");
        }
        Effects_C_ComboBox->Flash();

        graphicset_names.Clear();
        if(GenieVersion < genie::GV_AoKA)
        {
            // AoE
            graphicset_names.Add("0 West Middle Easterns");
            graphicset_names.Add("1 Greeks");
            graphicset_names.Add("2 East Middle Easterns");
            graphicset_names.Add("3 Asians");
            // + RoR
            graphicset_names.Add("4 Romans");
        }
        else if(GenieVersion < genie::GV_SWGB)
        {
            graphicset_names.Add("0 Unused");
            // AoK
            graphicset_names.Add("1 Central Europeans");
            graphicset_names.Add("2 West Europeans");
            graphicset_names.Add("3 East Asians");
            graphicset_names.Add("4 Arabs");
            // + TC
            graphicset_names.Add("5 Americans");
            // + FE
            if(GenieVersion >= genie::GV_Cysion)
            {
                graphicset_names.Add("6 South Europeans");
                graphicset_names.Add("7 Indians");
                graphicset_names.Add("8 East Europeans");
                graphicset_names.Add("9 Africans");
                graphicset_names.Add("10 South East Asians");
                graphicset_names.Add("11 Central Asians");
            }
        }
        else
        {
            // SWGB
            graphicset_names.Add("0 Unused");
            graphicset_names.Add("1 Galactic Empire");
            graphicset_names.Add("2 Gungans");
            graphicset_names.Add("3 Rebels");
            graphicset_names.Add("4 Royal Naboo");
            graphicset_names.Add("5 Trade Federation");
            graphicset_names.Add("6 Wookiees");
            graphicset_names.Add("7 Republic");
            graphicset_names.Add("8 Confederacy");
            graphicset_names.Add("9 Ask Tapsa for more!");
        }
        Units_GraphicSet->Flash();

        effect_type_names.Clear();
        effect_type_names.Add("No Type/Invalid Type");  // Selection 0
        effect_type_names.Add("0 - Attribute Modifier (Set)");  // Selection 1
        effect_type_names.Add("1 - Resource Modifier (Set/+/-)");
        effect_type_names.Add("2 - Enable/Disable Unit");
        effect_type_names.Add("3 - Upgrade Unit");
        effect_type_names.Add("4 - Attribute Modifier (+/-)");
        effect_type_names.Add("5 - Attribute Modifier (Multiply)");
        if(GenieVersion < genie::GV_AoKA)
        {
            effect_type_names.Add("6 - Resource Modifier (Multiply), needs exe mod!");
        }
        else
        {
            effect_type_names.Add("6 - Resource Modifier (Multiply)");
        }
        if(GenieVersion >= genie::GV_Cysion && GenieVersion <= genie::GV_LatestDE2)
        {
            effect_type_names.Add("10 - Team Attribute Modifier (Set)");    // Selection 8
            effect_type_names.Add("11 - Team Resource Modifier (Set/+/-)");
            effect_type_names.Add("12 - Team Enable/Disable Unit");
            effect_type_names.Add("13 - Team Upgrade Unit");
            effect_type_names.Add("14 - Team Attribute Modifier (+/-)");
            effect_type_names.Add("15 - Team Attribute Modifier (Multiply)");
            effect_type_names.Add("16 - Team Resource Modifier (Multiply)");
        }
        else
        {
            for(size_t loop = 10; loop < 17; ++loop)
            effect_type_names.Add(lexical_cast<string>(loop) + " - AoK HD only");
        }
        if(GenieVersion < genie::GV_AoKA) effect_type_names.Add("101 - AoK+ only");
        else effect_type_names.Add("101 - Tech Cost Modifier (Set/+/-)");
        effect_type_names.Add("102 - Disable Tech");
        if(GenieVersion < genie::GV_AoKA) effect_type_names.Add("103 - AoK+ only");
        else effect_type_names.Add("103 - Tech Time Modifier (Set/+/-)");   // Selection 17
        Effects_Type_ComboBox->Flash();

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

void AGE_Frame::LoadLists()
{
    OnCivCountChange();
    ListTerrainRestrictions(true);
    InitPlayerColors();
    InitSounds(true);
    InitGraphics(true);
    ListTerrainNumbers();
    InitTerrains1(true);
    InitTerrainBorders(true);
    ListMapData();
    InitRandomMaps();
    InitTechs(true);
    if(GenieVersion >= genie::GV_SWGB)
    {
        InitUnitLines();
    }
    else
    {
        UnitLines_UnitLines_ListV->Clear();
        UnitLines_UnitLineUnits_ListV->Clear();
    }
    //InitCivs(true);
    InitUnits(GenieVersion < genie::GV_AoKE3, true);
    InitResearches(true);
    if(GenieVersion >= genie::GV_AoKA)
    {
        InitTTAges();
        InitTTBuildings();
        InitTTUnits();
        InitTTResearches();
    }
    else
    {
        TechTrees_MainList_Ages_ListV->Clear();
        TechTrees_Ages_Buildings.List->Clear();
        TechTrees_Ages_Units.List->Clear();
        TechTrees_Ages_Researches.List->Clear();
        TechTrees_MainList_Buildings_ListV->Clear();
        TechTrees_Buildings_Buildings.List->Clear();
        TechTrees_Buildings_Units.List->Clear();
        TechTrees_Buildings_Researches.List->Clear();
        TechTrees_MainList_Units_ListV->Clear();
        TechTrees_Units_Units.List->Clear();
        TechTrees_MainList_Researches_ListV->Clear();
        TechTrees_Researches_Buildings.List->Clear();
        TechTrees_Researches_Units.List->Clear();
        TechTrees_Researches_Researches.List->Clear();
    }
    if(GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
    {
        InitTerrainBlends();
    }

    wxCommandEvent e;
    OnCivSelect(e);
    OnUnitSelect(e);
    OnResearchSelect(e);
    OnEffectSelect(e);
    OnGraphicSelect(e);
    OnSoundSelect(e);
    OnTerrainSelect(e);
    OnTerrainRestrictionsTerrainSelect(e);
    OnPlayerColorSelect(e);
    OnTerrainBorderSelect(e);
    OnRandomMapSelect(e);
    if(GenieVersion >= genie::GV_AoKA)
    {
        OnTTAgeSelect(e);
        OnTTBuildingSelect(e);
        OnTTUnitSelect(e);
        OnTTResearchSelect(e);
        if(GenieVersion >= genie::GV_SWGB)
        OnUnitLineSelect(e);
    }
}

void AGE_Frame::OnGameVersionChange()
{
    if(DataOpened)  // Hiding stuff according to game version should be here.
    {
        // Some general tab handling
        for(auto loop = dataset->TerrainBlock.getSomethingSize(); loop < General_Something.size(); ++loop)
        General_Something[loop]->Show(false);
        for(auto loop = dataset->TerrainBlock.getBytesSize(); loop < General_SomeBytes.size(); ++loop)
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
        Units_DropSite[1]->Show(show);
        Units_DropSite_ComboBox[1]->Show(show);
        if(show)
        {
            SoundItems_Resource->changeContainerType(CLong);
            Graphics_SLP->changeContainerType(CLong);
        }
        else
        {
            SoundItems_Resource->changeContainerType(CShort);
            Graphics_SLP->changeContainerType(CShort);
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
        Units_GarrisonType_Holder->Show(show);
        Units_GarrisonHealRate_Holder->Show(show);
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
            Colors_ID->changeContainerType(CLong);
            Colors_MinimapColor->changeContainerType(CLong);
        }
        else
        {
            Colors_ID->changeContainerType(CShort);
            Colors_MinimapColor->changeContainerType(CUByte);
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
            Units_BaseArmor->changeContainerType(CShort);
        }
        else // <- AoK
        {
            Units_BaseArmor->changeContainerType(CByte);
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
            Graphics_Name->setMaxChars(lengthiest);
            Graphics_FileName->setMaxChars(lengthiest);
            SoundItems_Name->setMaxChars(lengthiest);
            Terrains_Name->setMaxChars(lengthiest);
            Terrains_FileName->setMaxChars(lengthiest);
            // Fixed size elsewhere
            Techs_Name->setMaxChars(lengthiest);
            Civs_Name[0]->setMaxChars(lengthiest);
        }
        if(appear)
        {
            Terrains_BlendPriority_Holder->Show(true);
            Terrains_BlendType_Holder->Show(true);
            TerRestrict_Graphics_Holder->Show(true);
            Units_ObstructionType_Holder->Show(true);
            Units_ObstructionClass_Holder->Show(true);
            Terrains_BlendPriority->changeContainerType(CShort);
            Terrains_BlendType->changeContainerType(CShort);
            Units_BaseArmor->changeContainerType(CShort);
            TerRestrict_Amount->changeContainerType(CFloat);
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
                TerRestrict_Amount->changeContainerType(CFloat);
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
                TerRestrict_Amount->changeContainerType(CLong);
            }
            Terrains_BlendPriority->changeContainerType(CLong);
            Terrains_BlendType->changeContainerType(CLong);
        }
        if(emerge)
        {
            Research_LangDLLName->changeContainerType(CLong);
            Research_LangDLLDescription->changeContainerType(CLong);
        }
        else
        {
            Research_LangDLLName->changeContainerType(CUShort);
            Research_LangDLLDescription->changeContainerType(CUShort);
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
        Units_DropSite[2]->Show(emerge);
        Units_DropSite_ComboBox[2]->Show(emerge);
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

void AGE_Frame::OnSyncSaveWithOpen(wxCommandEvent &event)
{
    if(event.IsChecked())
    {
        SaveDialog->CheckBox_GenieVer->SetSelection(GameVersion);
        SaveDialog->Path_DatFileLocation->SetPath(DatFileName);
        SaveDialog->Path_LangFileLocation->SetPath(LangFileName);
        SaveDialog->Path_LangX1FileLocation->SetPath(LangX1FileName);
        SaveDialog->Path_LangX1P1FileLocation->SetPath(LangX1P1FileName);
    }
}

void AGE_Frame::OnSave(wxCommandEvent&)
{
    AGE_SaveDialog SaveBox(this, font);
    SaveDialog = &SaveBox;
    SaveBox.SyncWithReadPaths->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnSyncSaveWithOpen, this);

    int RecentItems;
    {
        wxConfig RecentSave("", "", "AGE2\\RecentSave", "", wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
        RecentSave.Read("Recent/Items", &RecentItems, 0);
        SaveBox.RecentValues.resize(RecentItems);
        for(int i=0; i < RecentItems; ++i)
        {
            SaveBox.RecentValues[i].Alloc(5);
            wxString temp, entry = "Recent" + wxString::Format("%04d", i + 1);
            RecentSave.Read(entry + "/DatVersion", &temp, "9000"); SaveBox.RecentValues[i].Add(temp);
            RecentSave.Read(entry + "/DatPath", &temp, wxEmptyString); SaveBox.RecentValues[i].Add(temp);
            RecentSave.Read(entry + "/Lang", &temp, wxEmptyString); SaveBox.RecentValues[i].Add(temp);
            RecentSave.Read(entry + "/LangX1", &temp, wxEmptyString); SaveBox.RecentValues[i].Add(temp);
            RecentSave.Read(entry + "/LangX1P1", &temp, wxEmptyString); SaveBox.RecentValues[i].Add(temp);
        }
    }
    if(SaveBox.RecentValues.size())
    for(int i=0; i < RecentItems; ++i)
    SaveBox.CheckBox_Recent->Append(SaveBox.RecentValues[i][1]);
    else
    SaveBox.CheckBox_Recent->Append("Happy Modding!");
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
        SaveBox.CheckBox_GenieVer->SetSelection(SaveGameVersion);
        SaveBox.Path_LangFileLocation->SetPath(SaveLangFileName);
        SaveBox.Path_LangX1FileLocation->SetPath(SaveLangX1FileName);
        SaveBox.Path_LangX1P1FileLocation->SetPath(SaveLangX1P1FileName);
    }

    bool save = SaveBox.ShowModal() == wxID_OK;
    SaveGameVersion = SaveBox.CheckBox_GenieVer->GetSelection();
    SaveDat = SaveBox.Radio_DatFileLocation->IsChecked();
    SaveLangs = SaveBox.CheckBox_LangWrite->IsChecked();
    SaveDatFileName = SaveBox.Path_DatFileLocation->GetPath();
    SaveLangFileName = SaveBox.Path_LangFileLocation->GetPath();
    SaveLangX1FileName = SaveBox.Path_LangX1FileLocation->GetPath();
    SaveLangX1P1FileName = SaveBox.Path_LangX1P1FileLocation->GetPath();
    SyncSaveWithOpen = DatFileName == SaveDatFileName && LangFileName == SaveLangFileName && LangX1FileName == SaveLangX1FileName && LangX1P1FileName == SaveLangX1P1FileName;

    if(!save) return;
    {
        wxConfig Config("", "", "AGE2\\ConfigWindow"+lexical_cast<string>(window_num + 1), "", wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
        Config.Write("DefaultFiles/SyncSaveWithOpen", SyncSaveWithOpen);
        Config.Write("DefaultFiles/SaveVersion", SaveGameVersion);
        Config.Write("DefaultFiles/SaveDatFilename", SaveDatFileName);
        Config.Write("DefaultFiles/SaveLangs", SaveLangs);
        Config.Write("DefaultFiles/SaveLangFilename", SaveLangFileName);
        Config.Write("DefaultFiles/SaveLangX1Filename", SaveLangX1FileName);
        Config.Write("DefaultFiles/SaveLangX1P1Filename", SaveLangX1P1FileName);
        Config.Write("DefaultFiles/SaveDat", SaveDat);
        Config.Write("Misc/CustomTerrains", CustomTerrains);

        if(!SaveBox.CheckBox_LangFileLocation->IsChecked()) SaveLangFileName = "";
        if(!SaveBox.CheckBox_LangX1FileLocation->IsChecked()) SaveLangX1FileName = "";
        if(!SaveBox.CheckBox_LangX1P1FileLocation->IsChecked()) SaveLangX1P1FileName = "";

        wxArrayString latest;
        latest.Alloc(5);
        latest.Add(lexical_cast<string>(SaveGameVersion));
        latest.Add(SaveDatFileName);
        latest.Add(SaveLangFileName);
        latest.Add(SaveLangX1FileName);
        latest.Add(SaveLangX1P1FileName);
        int RecentItems = produceRecentValues(latest, SaveBox.RecentValues);
        wxConfig RecentSave("", "", "AGE2\\RecentSave", "", wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
        RecentSave.Write("Recent/Items", RecentItems);
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
        genie::GameVersion SaveGenieVersion = version(SaveGameVersion);
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
                dataset->FileVersion = "VER 7.2";
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

        // A fix that should never be needed
        int TerrainsInData = dataset->TerrainBlock.Terrains.size();
        int BordersInTerrains = 0;
        for(int terrain = 0; terrain < TerrainsInData; ++terrain)
        {
            BordersInTerrains += dataset->TerrainBlock.Terrains[terrain].Borders.size();
        }
        BordersInTerrains /= TerrainsInData;
        if(TerrainsInData != BordersInTerrains)
        {
            wxString viesti = "Send file to Tapsa for repair!\nTerrains: " + lexical_cast<string>(TerrainsInData);
            viesti += "\nBorders: " + lexical_cast<string>(BordersInTerrains);
            viesti += "\nLoaded game version: " + lexical_cast<string>(dataset->TerrainBlock.getGameVersion());
            viesti += "\nTerrain game version: " + lexical_cast<string>(dataset->TerrainBlock.Terrains.front().getGameVersion());
            wxMessageBox(viesti);
        }
        // <-- ends here

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
    if(SaveLangs)
    {
        SetStatusText("Saving language files...", 0);
        wxBusyCursor WaitCursor;
        if(LangWriteToLatest)
        {
            if(LangsUsed & 4)
            {
                if(!SaveLangX1P1()) return;
            }
            else if(LangsUsed & 2)
            {
                if(!SaveLangX1()) return;
            }
            else
            {
                if(!SaveLang()) return;
            }
        }
        else
        {
            if(LangsUsed & 1)
            {
                if(!SaveLang()) return;
            }
            if(LangsUsed & 2)
            {
                if(!SaveLangX1()) return;
            }
            if(LangsUsed & 4)
            {
                if(!SaveLangX1P1()) return;
            }
        }
    }

    SetStatusText("Selected files saved. "+lexical_cast<string>(popUp.unSaved)+" dat edits.", 0);
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

bool slp_tool_on; // !IsShown()
void AGE_Frame::OnMenuOption(wxCommandEvent &event)
{
    switch(event.GetId())
    {
        case ePrompt:
        {
            PromptForFilesOnOpen = event.IsChecked();
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
            AGE_AboutDialog AGEAbout(this, font);
            AGEAbout.ShowModal();
            break;
        }
        case eTabBar:
        {
            if(slp_window) slp_view->Refresh();
            break;
        }
        case eShowSLP:
        {
            ShowSLP = event.IsChecked();

            Units_Main->Layout();
            Research_Main->Layout();
            Refresh();

            if(ShowSLP)
            {
                wxPoint parentPos = GetPosition();
                parentPos.x += MinWindowWidth;
                slp_window = new wxFrame(this, wxID_ANY, "SLP", parentPos, wxSize(512, 600), KeepViewOnTop ? (wxSTAY_ON_TOP | wxDEFAULT_FRAME_STYLE) : wxDEFAULT_FRAME_STYLE);
                //slp_window->SetBackgroundStyle(wxBG_STYLE_SYSTEM);
                slp_window->SetBackgroundColour(wxColour(240, 240, 240));
                slp_window->SetIcon(wxIcon(Villager32_xpm));
                slp_window->SetFont(font);
                APanel *panel = new APanel(slp_window);
                slp_view = new APanel(panel);//, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE);
                slp_next = new wxButton(panel, eNextFrame, "Show -> frame");
                slp_prev = new wxButton(panel, ePrevFrame, "Show <- frame");
                slp_first = new wxButton(panel, eFirstFrame, "Show first frame");
                wxColour back(ViewBackR, ViewBackG, ViewBackB);
                slp_background = new wxColourPickerCtrl(panel, ePickBgColor, back, wxDefaultPosition, wxDefaultSize, wxCLRP_SHOW_LABEL);
                slp_frame_export = new wxButton(panel, eExportFrame, "Export frame to PNGs");
                slp_frame_import = new wxButton(panel, eImportFrame, "Import PNGs to frame");
                slp_save = new wxButton(panel, eSaveSLP, "Save SLP");
                slp_tool = new wxButton(panel, eSLPTool, "SLP Tool");
                slp_zoom_btn = new wxButton(panel, eZoom, "Zoom: " + lexical_cast<string>(int(slp_zoom * 100)) + " %");
                slp_merge_shadow = new wxButton(panel, eSLPMergeShadow, "Merge shadow from 2 to 1");
                slp_tool_layout = new wxFlexGridSizer(2, 2, 2);
                SolidText *text_source1 = new SolidText(panel, " Source SLP 1");
                SolidText *text_source2 = new SolidText(panel, " Source SLP 2");
                SolidText *text_target1 = new SolidText(panel, " Target SLP");
                slp_source1 = new wxFilePickerCtrl(panel, wxID_ANY, "", "Select a file", "SLP|*.slp", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
                slp_source2 = new wxFilePickerCtrl(panel, wxID_ANY, "", "Select a file", "SLP|*.slp", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
                slp_target1 = new wxFilePickerCtrl(panel, wxID_ANY, "", "Select a file", "SLP|*.slp", wxDefaultPosition, wxDefaultSize, wxFLP_SAVE | wxFLP_USE_TEXTCTRL | wxFLP_OVERWRITE_PROMPT);
                slp_hotspot = new wxCheckBox(panel, eShowHotspot, "Hotspot");
                slp_show_angles = new wxCheckBox(panel, eShowAngles, "Show angles");
                slp_show_angles->SetValue(DrawAngles);
                slp_animate = new wxCheckBox(panel, eAnimSLP, "Animate");
                slp_animate->SetValue(AnimSLP);
                slp_shadow = new wxCheckBox(panel, eShowShadows, "Shadow");
                slp_shadow->SetValue(ShowShadows);
                slp_outline = new wxCheckBox(panel, eShowOutline, "Outline");
                slp_outline->SetValue(ShowOutline);
                slp_delta = new wxCheckBox(panel, eShowDeltas, "Delta");
                slp_delta->SetValue(ShowDeltas);
                slp_stack = new wxCheckBox(panel, eShowStack, "Stack");
                slp_stack->SetValue(ShowStack);
                slp_annex = new wxCheckBox(panel, eShowAnnexes, "Annex");
                slp_annex->SetValue(ShowAnnexes);
                slp_terrain = new wxCheckBox(panel, eShowTerrain, "Terrain");
                slp_terrain->SetValue(DrawTerrain);
                slp_angles = new wxCheckBox(panel, eRotateAngles, "Rotate angles *");
                slp_angles->SetValue(RotateAngles);
                slp_collision = new wxCheckBox(panel, eCollisionShape, "Collision Shape");
                slp_collision->SetValue(DrawCollisionShape);
                slp_clearance = new wxCheckBox(panel, eClearanceShape, "Clearance Shape");
                slp_clearance->SetValue(DrawClearanceShape);
                slp_selection = new wxCheckBox(panel, eOutline, "Selection Shape");
                slp_selection->SetValue(DrawOutline);
                slp_sounds = new wxCheckBox(panel, ePlaySounds, "Play Sounds");
                slp_sounds->SetValue(PlaySounds);
                slp_angles->SetToolTip("Right click image to manually set angle");
                slp_sizer = new wxBoxSizer(wxVERTICAL);
                wxSizer *sizer2 = new wxBoxSizer(wxHORIZONTAL);
                wxSizer *sizer3 = new wxBoxSizer(wxHORIZONTAL);
                wxSizer *sizer4 = new wxBoxSizer(wxHORIZONTAL);
                wxSizer *sizer5 = new wxBoxSizer(wxHORIZONTAL);

                slp_sizer->Add(slp_view, 1, wxEXPAND);
                sizer5->Add(slp_show_angles, 0, wxALL, 2);
                sizer5->Add(slp_sounds, 0, wxALL, 2);
                sizer5->Add(slp_collision, 0, wxALL, 2);
                sizer5->Add(slp_clearance, 0, wxALL, 2);
                sizer5->Add(slp_selection, 0, wxALL, 2);
                sizer3->Add(slp_animate, 0, wxALL, 2);
                sizer3->Add(slp_shadow, 0, wxALL, 2);
                sizer3->Add(slp_outline, 0, wxALL, 2);
                sizer3->Add(slp_delta, 0, wxALL, 2);
                sizer3->Add(slp_stack, 0, wxALL, 2);
                sizer3->Add(slp_annex, 0, wxALL, 2);
                sizer3->Add(slp_terrain, 0, wxALL, 2);
                sizer2->Add(slp_angles, 0, wxALL, 2);
                sizer2->Add(slp_first);
                sizer2->Add(slp_prev);
                sizer2->Add(slp_next);
                sizer2->Add(slp_background);
                sizer4->Add(slp_frame_export);
                sizer4->Add(slp_frame_import);
                sizer4->Add(slp_save);
                sizer4->Add(slp_tool);
                sizer4->Add(slp_zoom_btn);
                sizer3->Add(slp_hotspot, 0, wxALL, 2);
                slp_tool_layout->Add(text_source1, 1, wxEXPAND);
                slp_tool_layout->Add(slp_source1, 1, wxEXPAND);
                slp_tool_layout->Add(text_source2, 1, wxEXPAND);
                slp_tool_layout->Add(slp_source2, 1, wxEXPAND);
                slp_tool_layout->Add(text_target1, 1, wxEXPAND);
                slp_tool_layout->Add(slp_target1, 1, wxEXPAND);
                slp_tool_layout->AddSpacer(1);
                slp_tool_layout->Add(slp_merge_shadow);
                slp_sizer->Add(slp_tool_layout, 0, wxEXPAND);
                slp_sizer->Add(sizer3, 0, wxEXPAND);
                slp_sizer->Add(sizer5, 0, wxEXPAND);
                slp_sizer->Add(sizer2, 0, wxEXPAND);
                slp_sizer->Add(sizer4, 0, wxEXPAND);
                slp_tool_layout->AddGrowableCol(1, 1);
                slp_tool_layout->Show(slp_tool_on);
                panel->SetSizer(slp_sizer);

                slp_view->Bind(wxEVT_PAINT, &AGE_Frame::OnDrawGraphicSLP, this);
                slp_view->Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent&){});
                slp_view->Bind(wxEVT_RIGHT_DOWN, &AGE_Frame::OnFrameMouse, this);
                slp_view->Bind(wxEVT_KEY_DOWN, &AGE_Frame::OnFrameKey, this);
                slp_window->Bind(wxEVT_CLOSE_WINDOW, &AGE_Frame::OnExitSLP, this);
                slp_first->Bind(wxEVT_BUTTON, &AGE_Frame::OnFrameButton, this);
                slp_next->Bind(wxEVT_BUTTON, &AGE_Frame::OnFrameButton, this);
                slp_prev->Bind(wxEVT_BUTTON, &AGE_Frame::OnFrameButton, this);
                slp_frame_export->Bind(wxEVT_BUTTON, &AGE_Frame::OnFrameButton, this);
                slp_frame_import->Bind(wxEVT_BUTTON, &AGE_Frame::OnFrameButton, this);
                slp_save->Bind(wxEVT_BUTTON, &AGE_Frame::OnFrameButton, this);
                slp_tool->Bind(wxEVT_BUTTON, &AGE_Frame::OnFrameButton, this);
                slp_zoom_btn->Bind(wxEVT_BUTTON, &AGE_Frame::OnFrameButton, this);
                slp_merge_shadow->Bind(wxEVT_BUTTON, &AGE_Frame::OnFrameButton, this);
                slp_hotspot->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_animate->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_shadow->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_outline->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_delta->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_stack->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_annex->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_angles->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_sounds->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_terrain->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_collision->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_clearance->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_selection->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_background->Bind(wxEVT_COLOURPICKER_CHANGED, &AGE_Frame::OnFrameButton, this);
                slp_show_angles->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnFrameButton, this);
                slp_window->Show();
            }
            else
            {
                if(slp_window) // What if users manage to close this?
                {
                    slp_window->Destroy();
                    slp_window = 0;
                }
            }
            break;
        }
        case eShowIcons:
        {
            ShowIcons = event.IsChecked();

            Units_IconID_SLP->Show(ShowIcons);
            Research_IconID_SLP->Show(ShowIcons);
            break;
        }
        case eVasili:
        {
#ifdef WIN32
            EmptyWorkingSet(GetCurrentProcess());
#endif
            break;
        }
        case eSlpPals:
        {
            wxFileDialog pd(this, "Open palette configuration file", "", "palettes.conf",
                "Configuration files (*.conf)|*.conf", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
            if(pd.ShowModal() == wxID_OK)
            {
                PalettesPath = pd.GetPath();
                GG::LoadPalettes(palettes, PalettesPath);
            }
            break;
        }
        case eSlpPCPal:
        {
            wxFileDialog pd(this, "Open palette file", "", "playercolor_blue.pal",
                "Palette files (*.pal)|*.pal", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
            if(pd.ShowModal() == wxID_OK)
            {
                pc_palettes.clear();
                genie::PalFile pal;
                try
                {
                    pal.load(pd.GetPath().c_str());
                    pc_palettes.push_back(pal.getColors());
                }
                catch(const std::ios_base::failure&)
                {
                    wxMessageBox("Cannot load palette");
                }
            }
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
                        if(GenieVersion == genie::GV_TC)
                        {
                            FilesToRead.Add("\\sounds_x1.drs");
                            FilesToRead.Add("\\gamedata_x1.drs");
                            FilesToRead.Add("\\gamedata_x1_p1.drs");
                        }
                        else if(GenieVersion == genie::GV_CC)
                        {
                            if(GameVersion == EV_EF)
                            {
                                FilesToRead.Add("\\sounds_x2.drs");
                                FilesToRead.Add("\\graphics_x2.drs");
                                FilesToRead.Add("\\terrain_x2.drs");
                                FilesToRead.Add("\\interfac_x2.drs");
                                FilesToRead.Add("\\gamedata_x2.drs");
                            }
                            FilesToRead.Add("\\sounds_x1.drs");
                            FilesToRead.Add("\\graphics_x1.drs");
                            FilesToRead.Add("\\terrain_x1.drs");
                            FilesToRead.Add("\\interfac_x1.drs");
                            FilesToRead.Add("\\gamedata_x1.drs");
                        }
                    }
                    FilesToRead.Add("\\sounds.drs");
                    FilesToRead.Add("\\graphics.drs");
                    FilesToRead.Add("\\terrain.drs");
                    if(GenieVersion < genie::GV_AoKB)
                    {
                        FilesToRead.Add("\\border.drs");
                    }
                    FilesToRead.Add("\\interfac.drs");
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
                    for(auto &file: datafiles)
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
                for(auto &file: datafiles) delete file;
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
                //for(auto &file: datafiles)
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
            if(!AGE_Frame::openEditors[win])
            {
                AGE_Frame* newWindow = new AGE_Frame("AGE " + AGE_AboutDialog::AGE_VER + " window "+lexical_cast<string>(win+1), win);
                FixSize(newWindow);
                wxCommandEvent OpenFiles(wxEVT_MENU, newWindow->eOpen);
                newWindow->OnOpen(OpenFiles);
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
        case eStayOnTopSLP:
        {
            if(slp_window) slp_window->ToggleWindowStyle(wxSTAY_ON_TOP);
            KeepViewOnTop = event.IsChecked();
            break;
        }
        case hotWin1:
        {
            if(AGE_Frame::openEditors[0]) AGE_Frame::openEditors[0]->Raise();
            break;
        }
        case hotWin2:
        {
            if(AGE_Frame::openEditors[1]) AGE_Frame::openEditors[1]->Raise();
            break;
        }
        case hotWin3:
        {
            if(AGE_Frame::openEditors[2]) AGE_Frame::openEditors[2]->Raise();
            break;
        }
        case hotWin4:
        {
            if(AGE_Frame::openEditors[3]) AGE_Frame::openEditors[3]->Raise();
            break;
        }
        case closeAll:
        {
            wxCloseEvent ce(wxEVT_CLOSE_WINDOW);
            AGE_Frame::openEditors[window_num] = 0;
            for(size_t win = 0; win < 4; ++win)
            if(AGE_Frame::openEditors[win])
            {
                AGE_Frame::openEditors[win]->OnExit(ce);
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

            slp_csv.AddLine("SLP,PicFilename,Name,NumFrames,NumFacets");
            for(size_t sprite = 0; sprite < dataset->Graphics.size(); ++sprite)
            if(dataset->GraphicPointers[sprite])
            {
                slp_csv.AddLine(lexical_cast<string>(dataset->Graphics[sprite].SLP)
                            +','+dataset->Graphics[sprite].FileName
                            +','+dataset->Graphics[sprite].Name
                            +','+lexical_cast<string>(dataset->Graphics[sprite].FrameCount)
                            +','+lexical_cast<string>(dataset->Graphics[sprite].AngleCount));
            }

            size_t unit, civ, depth = 0;
            obj_csv.AddLine("Civ,IconSet,UnitID,UnitName,LangName,"
                "Name,PicFilename,Layer,NumFrames,NumFacets");
            function<void(size_t)> sprite_checker = [&](size_t sprite)
            {
                ++depth;
                if(sprite < dataset->Graphics.size() && dataset->GraphicPointers[sprite])
                {
                    if(!dataset->Graphics[sprite].FileName.empty())
                    {
                        obj_csv.AddLine(dataset->Civs[civ].Name
                            +','+lexical_cast<string>((int)dataset->Civs[civ].IconSet)
                            +','+lexical_cast<string>(unit)
                            +','+dataset->Civs[civ].Units[unit].Name
                            +','+TranslatedText(dataset->Civs[civ].Units[unit].LanguageDLLName, 24)
                            //+','+lexical_cast<string>((int)dataset->Civs[civ].Units[unit].OcclusionMode)
                            +','+dataset->Graphics[sprite].Name
                            +','+dataset->Graphics[sprite].FileName
                            +','+lexical_cast<string>((int)dataset->Graphics[sprite].Layer)
                            +','+lexical_cast<string>(dataset->Graphics[sprite].FrameCount)
                            +','+lexical_cast<string>(dataset->Graphics[sprite].AngleCount));
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
                            +','+lexical_cast<string>((int)dataset->Civs[civ].IconSet)
                            +','+lexical_cast<string>(unit)
                            +','+dataset->Civs[civ].Units[unit].Name
                            +','+lexical_cast<string>(langname)
                            +','+TranslatedText(langname, 24)
                            +','+lexical_cast<string>(hotkey)
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
        case eCacheDepth:
        {
            wxTextEntryDialog ted(this, "Enter new cache depth", "Set Cache Depth", lexical_cast<string>(GG::cache_depth));
            ted.SetTextValidator(wxFILTER_DIGITS);
            if(ted.ShowModal() == wxID_OK)
            {
                GG::cache_depth = lexical_cast<size_t>(ted.GetValue());
            }
            break;
        }
        case eSlpZoom:
        {
            wxTextEntryDialog ted(this, "Replace <x#> with", "Set Zoom Level", AlexZoom);
            ted.SetTextValidator(wxFILTER_ALPHANUMERIC);
            if(ted.ShowModal() == wxID_OK)
            {
                AlexZoom = ted.GetValue();
            }
            break;
        }
        case eBoxWidth:
        {
            wxTextEntryDialog ted(this, "Enter new multiplier for data box widths", "Set Box Width Multiplier", FormatFloat(boxWidthMultiplier));
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
        default: wxMessageBox("ID "+lexical_cast<string>(event.GetId())+"\nType "+lexical_cast<string>(event.GetEventType()), "Unhandled Event");
    }
}

int AGE_Frame::produceRecentValues(wxArrayString &latest, vector<wxArrayString> &RecentValues)
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

bool AGE_Frame::loadPalette(const wxString &folder)
{
    if(!wxDir::Exists(folder)) return false;
    genie::PalFile pal;
    wxString name = folder + "\\interface\\50500.bina";
    try
    {
        pal.load(name.c_str());
        palettes.push_back(pal.getColors());
        return true;
    }
    catch(const std::ios_base::failure&){}
    return false;
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

void AGE_Frame::addSLPFolders4SLPs(wxArrayString &folders, wxString folder)
{
    if(folder.empty()) return;
    folder.Replace("drs", "slp", false);
    if(!wxDir::Exists(folder)) return;
    folders.Add(folder + "\\");
}

void AGE_Frame::addDRSFolders4SLPs(wxArrayString &folders, const wxString &folder)
{
    if(folder.empty()) return;
    if(wxDir::Exists(folder + "\\gamedata_x2"))
    folders.Add(folder + "\\gamedata_x2\\");
    if(wxDir::Exists(folder + "\\gamedata_x1"))
    folders.Add(folder + "\\gamedata_x1\\");
    if(wxDir::Exists(folder + "\\interface"))
    folders.Add(folder + "\\interface\\");
    if(wxDir::Exists(folder + "\\graphics"))
    folders.Add(folder + "\\graphics\\");
    if(wxDir::Exists(folder + "\\terrain"))
    folders.Add(folder + "\\terrain\\");
}

bool AGE_Frame::LoadSLP(AGE_SLP *graphic)
{
    if(graphic->slpID == graphic->lastSlpID)
    {
        return true;
    }
    graphic->lastSlpID = graphic->slpID;

    if(UseLooseSLP)
    {
        if(!graphic->filename.empty())
        {
            if(GameVersion == EV_DE2 || GameVersion == EV_Tapsa)
            {
                graphic->filename.Replace("<x#>", AlexZoom, false);
            }
            wxString plainName = PathSLP + "\\" + graphic->filename;
            if(wxFileName(plainName + ".smp").FileExists())
            {
               graphic->smp = GG::LoadSMP(plainName + ".smp");
               if(graphic->smp) return true;
            }
            if(wxFileName(plainName + ".slp").FileExists())
            {
               graphic->slp = GG::LoadSLP(plainName + ".slp");
               if(graphic->slp) return true;
            }
        }
    }
    if(LooseHD)
    {
        wxArrayString folders;
        if(!graphic->filename.empty())
        {
            if(UseMod) addSLPFolders4SLPs(folders, FolderDRS2);
            addSLPFolders4SLPs(folders, FolderDRS);
            for(int i=0; i < folders.size(); ++i)
            {
                graphic->slp = GG::LoadSLP(folders[i] + graphic->filename + ".slp");
                if(graphic->slp) return true;
            }
            folders.clear();
        }
        if(UseMod) addDRSFolders4SLPs(folders, FolderDRS2);
        addDRSFolders4SLPs(folders, FolderDRS);
        for(int i=0; i < folders.size(); ++i)
        {
            // HD uses slp ID instead
            graphic->slp = GG::LoadSLP(folders[i] + lexical_cast<string>(graphic->slpID) + ".slp");
            if(graphic->slp) return true;
        }
    }
    else
    {
        for(auto &file: datafiles)
        {
            graphic->slp = GG::LoadSLP(*file, graphic->slpID);
            if(graphic->slp) return true;
        }
    }
    graphic->slp.reset();
    graphic->bitmap = wxNullBitmap;
    return false;
}

void AGE_Frame::FrameToBitmap(AGE_SLP *graphic, bool centralize)
{
    if(graphic->frameID < 0)
    {
        graphic->bitmap = wxNullBitmap;
        return;
    }
    if(graphic->smp)
    {
        genie::SmpFramePtr frame;
        SetStatusText("Looking for frame "+FormatInt(graphic->frameID), 1);
        graphic->frames = graphic->smp->getFrameCount();
        if(graphic->frames)
        {
            try
            {
                frame = graphic->smp->getFrame(graphic->frameID);
            }
            catch(const out_of_range&){}
        }
        if(!frame)
        {
            graphic->bitmap = wxNullBitmap;
            SetStatusText("No frame: " + FormatInt(graphic->frameID) + ", frames: " + FormatInt(graphic->frames), 1);
            return;
        }

        const int width = frame->getWidth();
        const int height = frame->getHeight();
        graphic->xpos = -frame->layer_hotspot_x;
        graphic->ypos = -frame->layer_hotspot_y;
        const int area = width * height;
        vector<uint8_t> rgbdata(area * 4, 0);
        uint8_t *val = rgbdata.data();
        uint8_t *alpha = val + area * 3;
        const genie::SmpFrameData *imgdata = &frame->img_data;
        const vector<genie::Color> *pal = &palettes.front();
        if(!pal->empty())
        {
            for(int i=0; i < area; ++i)
            {
                size_t pal_chooser = 0x3F & imgdata->pixel_indexes[i] >> 10;
                if(pal_chooser < palettes.size())
                {
                    pal = &palettes[pal_chooser];
                }
                genie::Color rgba = (*pal)[0x3FF & imgdata->pixel_indexes[i]];
                *val++ = rgba.r;
                *val++ = rgba.g;
                *val++ = rgba.b;
                *alpha++ = imgdata->alpha_channel[i] ? rgba.a : 0;
            }
            // In case of using separate player color palette
            bool sep_pcp = pc_palettes.size();
            if(sep_pcp)
            {
                pal = &pc_palettes.front();
            }
            // Apply player color
            for(int i=0; i < imgdata->player_color_mask.size(); ++i)
            {
                int flat = imgdata->player_color_mask[i].y * width + imgdata->player_color_mask[i].x;
                int loc = 3 * flat;
                int locA = 3 * area + flat;
                genie::Color rgba = (*pal)[0x3FF & imgdata->player_color_mask[i].index];
                rgbdata[loc] = rgba.r;
                rgbdata[loc + 1] = rgba.g;
                rgbdata[loc + 2] = rgba.b;
                rgbdata[locA] = 255;
            }
        }
        unsigned char *pic = (unsigned char*)rgbdata.data();
        unsigned char *trans = pic + area * 3;
        wxImage img(width, height, pic, trans, true);
        if(centralize)
        {
            int left = frame->hotspot_x, right = width - left,
                top = frame->hotspot_y, bottom = height - top;
            int half_width = left > right ? left : right;
            int half_height = top > bottom ? top : bottom;
            img.Resize(wxSize(half_width * 2, half_height * 2), wxPoint(min(half_width, half_width - left), min(half_height, half_height - top)));
        }
        graphic->bitmap = wxBitmap(img, 24);
        return;
    }
    if(!graphic->slp)
    {
        graphic->bitmap = wxNullBitmap;
        SetStatusText("Loading frame without SLP", 1);
        return;
    }
    genie::SlpFramePtr frame;
    SetStatusText("Looking for frame "+FormatInt(graphic->frameID), 1);
    graphic->frames = graphic->slp->getFrameCount();
    if(graphic->frames)
    {
        try
        {
            frame = graphic->slp->getFrame(graphic->frameID);
        }
        catch(const out_of_range&){}
    }
    if(!frame)
    {
        graphic->bitmap = wxNullBitmap;
        SetStatusText("No frame: " + FormatInt(graphic->frameID) + ", frames: " + FormatInt(graphic->frames), 1);
        return;
    }

    const int width = frame->getWidth();
    const int height = frame->getHeight();
    const short pal_chooser = frame->getProperties() >> 16;
    graphic->xpos = graphic->flip ? frame->hotspot_x - width : -frame->hotspot_x;
    graphic->ypos = -frame->hotspot_y;
    const int area = width * height;
    vector<uint8_t> rgbdata(area * 4, 0);
    uint8_t *val = rgbdata.data();
    uint8_t *alpha = val + area * 3;
    const genie::SlpFrameData *imgdata = &frame->img_data;
    graphic->is32 = frame->is32bit();
    if(graphic->is32)
    {
        for(int i=0; i < area; ++i)
        {
            uint32_t bgra = imgdata->bgra_channels[i];
            *val++ = uint8_t(bgra >> 16);
            *val++ = uint8_t(bgra >> 8);
            *val++ = uint8_t(bgra);
            *alpha++ = uint8_t(bgra >> 24);
        }
        // Apply transparency
        if(!ShowOutline)
        for(int i=0; i < imgdata->transparency_mask.size(); ++i)
        {
            int flat = imgdata->transparency_mask[i].y * width + imgdata->transparency_mask[i].x;
            rgbdata[3 * area + flat] = 0;
        }
        // Temp hack for interface files
        graphic->xpos = -width / 2;
        graphic->ypos = -height / 3 * 2;
    }
    else
    {
        const vector<genie::Color> *pal = &palettes.front();
        if(imgdata->palette.size())
        {
            pal = &imgdata->palette;
        }
        else if(pal_chooser != 0 && pal_chooser < palettes.size())
        {
            pal = &palettes[pal_chooser];
        }
        if(!pal->empty())
        {
            for(int i=0; i < area; ++i)
            {
                genie::Color rgba = (*pal)[imgdata->pixel_indexes[i]];
                *val++ = rgba.r;
                *val++ = rgba.g;
                *val++ = rgba.b;
                *alpha++ = imgdata->alpha_channel[i];
            }
            // In case of using separate player color palette
            bool sep_pcp = pc_palettes.size();
            if(sep_pcp)
            {
                pal = &pc_palettes.front();
            }
            // Apply shadows
            if(ShowShadows)
            for(int i=0; i < imgdata->shadow_mask.size(); ++i)
            {
                int flat = imgdata->shadow_mask[i].y * width + imgdata->shadow_mask[i].x;
                int loc = 3 * flat;
                int locA = 3 * area + flat;
                rgbdata[loc] = 0;
                rgbdata[loc + 1] = 0;
                rgbdata[loc + 2] = 0;
                rgbdata[locA] = 127;
            }
            // Apply player color
            for(int i=0; i < imgdata->player_color_mask.size(); ++i)
            {
                int flat = imgdata->player_color_mask[i].y * width + imgdata->player_color_mask[i].x;
                int loc = 3 * flat;
                int locA = 3 * area + flat;
                genie::Color rgba = (*pal)[imgdata->player_color_mask[i].index + (sep_pcp ? 0 : AGE_SLP::playerColorStart)];
                rgbdata[loc] = rgba.r;
                rgbdata[loc + 1] = rgba.g;
                rgbdata[loc + 2] = rgba.b;
                if(exportFrame)
                {
                    rgbdata[locA] = 230 + imgdata->player_color_mask[i].index;
                }
                else
                {
                    rgbdata[locA] = 255;
                }
            }
            // Apply outlines
            if(ShowOutline)
            {
                // Shield
                for(int i=0; i < imgdata->shield_mask.size(); ++i)
                {
                    int flat = imgdata->shield_mask[i].y * width + imgdata->shield_mask[i].x;
                    int loc = 3 * flat;
                    int locA = 3 * area + flat;
                    rgbdata[loc] = 0;
                    rgbdata[loc + 1] = 255;
                    rgbdata[loc + 2] = 0;
                    rgbdata[locA] = exportFrame ? 201: 255;
                }
                // Player color
                for(int i=0; i < imgdata->outline_pc_mask.size(); ++i)
                {
                    int flat = imgdata->outline_pc_mask[i].y * width + imgdata->outline_pc_mask[i].x;
                    int loc = 3 * flat;
                    int locA = 3 * area + flat;
                    genie::Color rgba = sep_pcp ? pal->front() : (*pal)[AGE_SLP::playerColorID];
                    rgbdata[loc] = rgba.r;
                    rgbdata[loc + 1] = rgba.g;
                    rgbdata[loc + 2] = rgba.b;
                    rgbdata[locA] = exportFrame ? 200: 255;
                }
            }
        }
    }
    unsigned char *pic = (unsigned char*)rgbdata.data();
    unsigned char *trans = pic + area * 3;
    wxImage img(width, height, pic, trans, true);
    if(graphic->flip) img = img.Mirror();
    if(centralize)
    {
        int left = frame->hotspot_x, right = width - left,
            top = frame->hotspot_y, bottom = height - top;
        int half_width = left > right ? left : right;
        int half_height = top > bottom ? top : bottom;
        img.Resize(wxSize(half_width * 2, half_height * 2), wxPoint(min(half_width, half_width - left), min(half_height, half_height - top)));
    }
    graphic->bitmap = wxBitmap(img, 24);
}

void AGE_Frame::BitmapToSLP(AGE_SLP *graphic)
{
    wxImage img("Testi.png", wxBITMAP_TYPE_PNG);
    unsigned char *pic = img.GetData();
    if(!img.HasAlpha()) img.InitAlpha();
    if(!img.HasAlpha())
    {
        wxMessageBox("Alpha channel missing", "Aborting...");
        return;
    }
    unsigned char *trans = img.GetAlpha();
    if(!graphic->slp)
    {
        wxMessageBox("Congrats seeing this message", "No SLP");
        return;
    }
    genie::SlpFramePtr frame;
    try
    {
        frame = graphic->slp->getFrame(graphic->frameID);
    }
    catch(const out_of_range&){}
    if(!frame)
    {
        wxMessageBox("Congrats seeing this message", "No SLP frame " + lexical_cast<string>(graphic->frameID));
        return;
    }
    genie::SlpFrameData *imgdata = &frame->img_data;
    if(frame->is32bit())
    {
        frame->setSize(img.GetWidth(), img.GetHeight());
        uint32_t *val = imgdata->bgra_channels.data();
        for(int y=0; y < img.GetHeight(); ++y)
        for(int x=0; x < img.GetWidth(); ++x)
        {
            unsigned char red = *pic++;
            unsigned char green = *pic++;
            unsigned char blue = *pic++;
            unsigned char alpha = *trans++;
            *val++ = (red << 16) + (green << 8) + blue + (alpha << 24);
        }
        wxMessageBox("Frame image filled from PNG", "SLP");
    }
    else
    {
        wxMessageBox("No 8-bit frame support yet", "SLP");
    }
}

/* Check if File Exists

bool AGE_Frame::FileExists(const char * value)
{
    FILE * handle;
    handle = fopen(value, "rb");
    if(handle)
    {
        fclose(handle);
        return true;
    }
    return false;
}*/

void AGE_Frame::LoadTXT(const wxString &filename)
{
    ifstream infile(filename);
    string line;
    while(getline(infile, line))
    {
        size_t num = 0;
        while(isdigit(line[num]))
        {
            ++num;
        }
        if(num)
        {
            size_t ID = lexical_cast<size_t>(line.substr(0, num));
            size_t beg = line.find('"', num) + 1;
            size_t len = line.find('"', beg) - beg;
            if(len) LangTxt[ID] = line.substr(beg, len);
        }
    }
}

wxString AGE_Frame::TranslatedText(int ID, int letters)
{
    if(ID < 0) return "";
    wxString result = "";
    if(UseTXT)
    {
        result = LangTxt[ID];
        result.Replace("\\n", "\r\n");
        result.Replace("\\\\", "\\");
        result.Replace("\\\"", "\"");
    }
    else
    {
        if(sizeof(size_t) > 4 || WriteLangs)
        {
            if(LangsUsed & 4 && !(result = LangXP->getString(ID)).empty()){}
            else if(LangsUsed & 2 && !(result = LangX->getString(ID)).empty()){}
            else if(LangsUsed & 1 && !(result = Lang->getString(ID)).empty()){}
        }
        else // Does not work when building as 64-bit
        {
            char buffer[letters];
            if(LangsUsed & 4 && LoadStringA(LanguageDLL[2], ID, buffer, letters)) result = buffer;
            else if(LangsUsed & 2 && LoadStringA(LanguageDLL[1], ID, buffer, letters)) result = buffer;
            else if(LangsUsed & 1 && LoadStringA(LanguageDLL[0], ID, buffer, letters)) result = buffer;
        }
        result.Replace("\n", "\r\n");
    }
    return result;
}

void AGE_Frame::OnKillFocus_LangDLL(wxFocusEvent &event)
{
    event.Skip();
    TextCtrl_DLL *control = static_cast<TextCtrl_DLL*>(event.GetEventObject());
    if(control->IsModified())
    {
        control->DiscardEdits();
        if(control->index < 0) return;
        if(!WriteLangs)
        {
            wxString message = "In order to edit language entries, check write language files in the open files dialog and reopen them.";
            popUp.post(message, "Warning", NULL);
            return;
        }

        int ID = control->index;
        wxString text(control->GetValue());
        text.Replace("\r\n", "\n");
        string Name = string(text);
        if(LangWriteToLatest)
        {
            if(LangsUsed & 4) LangXP->setString(ID, Name);
            else if(LangsUsed & 2) LangX->setString(ID, Name);
            else if(LangsUsed & 1) Lang->setString(ID, Name);
        }
        else
        {
            if(LangsUsed & 4 && !LangXP->getString(ID).empty()) LangXP->setString(ID, "");
            if(LangsUsed & 2 && !LangX->getString(ID).empty()) LangX->setString(ID, "");
            if(LangsUsed & 1) Lang->setString(ID, Name);
        }
        SetStatusText("Wrote \""+Name+"\" to "+lexical_cast<string>(ID), 0);
    }
}

void AGE_Frame::InitSearch(const wxString &yes, const wxString &no)
{
    SearchYes = wxStringTokenize(yes, "|");
    SearchNo = wxStringTokenize(no, "|");
}

bool AGE_Frame::SearchMatches(const wxString &hay)
{
    bool matches = false;

    // If there is no search text, list normally.
    if(SearchYes.empty())
    {
        matches = true;
    }
    else // If search text has a match.
    {
        if(SearchAnd) // All search parts must match.
        {
            matches = true;
            for(const wxString &pin: SearchYes)
            if(wxNOT_FOUND == hay.Find(pin))
            {
                matches = false;
                break;
            }
        }
        else // Only one match needed.
        {
            for(const wxString &pin: SearchYes)
            if(wxNOT_FOUND != hay.Find(pin))
            {
                matches = true;
                break;
            }
        }
    }

    // We don't need to check for excluding if it's not going to be listed.
    // If there is no exclude text, list normally.
    if(!matches || SearchNo.empty())
    {
        return matches;
    }
    else // If exclude text has a match.
    {
        if(ExcludeAnd) // All search parts must match.
        {
            matches = false;
            for(const wxString &pin: SearchNo)
            if(wxNOT_FOUND == hay.Find(pin))
            {
                matches = true;
                break;
            }
        }
        else // Only one match needed.
        {
            for(const wxString &pin: SearchNo)
            if(wxNOT_FOUND != hay.Find(pin))
            {
                matches = false;
                break;
            }
        }
    }

    return matches;
}

//  Following kill focuses are used to update lists in user interface

void AGE_Frame::OnSelection_SearchFilters(wxCommandEvent &event)
{
    for(size_t loop = 0; loop < 2; ++loop) // Custom search filters
    {
        if(event.GetId() == Graphics_SearchFilters[loop]->GetId())
        {
            ListGraphics(false);
            Graphics_Graphics_Search->SetFocus();
        }
        else if(event.GetId() == Terrains_SearchFilters[loop]->GetId())
        {
            ListTerrains1(false);
            Terrains_Terrains_Search->SetFocus();
        }
        else if(event.GetId() == TechTrees_MainList_Units_SearchFilters[loop]->GetId())
        {
            ListTTUnits();
            TechTrees_MainList_Units_Search->SetFocus();
        }
        else if(event.GetId() == TechTrees_MainList_Buildings_SearchFilters[loop]->GetId())
        {
            ListTTBuildings();
            TechTrees_MainList_Buildings_Search->SetFocus();
        }
        else if(event.GetId() == TechTrees_MainList_Researches_SearchFilters[loop]->GetId())
        {
            ListTTResearches();
            TechTrees_MainList_Researches_Search->SetFocus();
        }
        else if(event.GetId() == Research_SearchFilters[loop]->GetId())
        {
            ListResearches(false);
            Research_Research_Search->SetFocus();
        }
        else if(event.GetId() == Sounds_Items_SearchFilters[loop]->GetId())
        {
            ListSoundItems();
            Sounds_Items_Search->SetFocus();
        }
    }
}

/*void AGE_Frame::Listing(wxListBox *List, wxArrayString &names, list<void*> &data)
{
    int selections = List->GetSelections(Items);
    int listsize = List->GetCount(); // Size before
    chrono::time_point<chrono::system_clock> startTime = chrono::system_clock::now();
    if(How2List == ADD)
    {
        if(names.size() > listsize)
        {
            List->Append(names.Last());
            SetStatusText("Added 1 visible", 2);
        }
        else
        {
            SetStatusText("Added 1 hidden", 2);
        }
        SetStatusText("Edits: "+lexical_cast<string>(popUp.unSaved)+" + 1", 3);
        ++popUp.unSaved;
    }
    else if(How2List == DEL)
    {
        if(20 * selections < listsize)
        {
            for(int sel = Items.size(); sel--> 0;)
            List->Delete(Items.Item(sel));
            SetStatusText("Deleted 1 by 1", 2);
        }
        else
        {
            List->Set(names);
            SetStatusText("Listed all again", 2);
        }
        SetStatusText("Edits: "+lexical_cast<string>(popUp.unSaved)+" + "+lexical_cast<string>(selections), 3);
        popUp.unSaved += selections;
    }
    else if(How2List == PASTE && Paste11)
    {
        for(int sel = 0; sel < selections; ++sel)
        {
            List->SetString(Items.Item(sel), names[Items.Item(sel)]);
        }
        SetStatusText("Pasted 1 to 1", 2);
        SetStatusText("Edits: "+lexical_cast<string>(popUp.unSaved)+" + "+lexical_cast<string>(selections), 3);
        popUp.unSaved += selections;
    }
    else
    {
        List->Set(names);
        if(How2List != SEARCH)
        {
            SetStatusText("Listed all again", 2);
            if(How2List == ENABLE)
            {
                SetStatusText("Edits: "+lexical_cast<string>(popUp.unSaved)+" + "+lexical_cast<string>(selections), 3);
                popUp.unSaved += selections;
            }
            else // Need more input to calculate edits for paste and inserts.
            {
                SetStatusText("Edits: "+lexical_cast<string>(popUp.unSaved)+" + 1", 3);
                ++popUp.unSaved;
            }
        }
    }
    bool showTime = ((chrono::duration_cast<chrono::milliseconds>(startTime - endTime)).count() > 1000) ? true : false;
    endTime = chrono::system_clock::now();
    listsize = List->GetCount(); // Size after
    if(listsize == 0) return;

    // Data pointers need to be reassigned always.
    auto it = data.begin();
    for(size_t loop = 0; loop < listsize; ++loop)
    {
        List->SetClientData(loop, *it++);
    }
    if(showTime)
    SetStatusText("Re-listing time: "+lexical_cast<string>((chrono::duration_cast<chrono::milliseconds>(endTime - startTime)).count())+" ms", 1);

    // Set selections and first visible item.
    if(How2List != SEARCH)
        List->SetFocus();
    if(selections == 0)
    {
        List->SetSelection(0);
        How2List = SEARCH;
        return;
    }
    if(How2List == ADD || Items.Item(0) >= listsize)
    {
        if(How2List == ADD)
        for(int sel = 0; sel < Items.size(); ++sel)
        List->Deselect(Items.Item(sel));
        //List->SetFirstItem(listsize - 1);
        List->SetSelection(listsize - 1);
        How2List = SEARCH;
        return;
    }
    if(FirstVisible != -1)
    {
        List->SetFirstItem(FirstVisible);
        FirstVisible = -1;
    }
    else
    {
        int first = Items.Item(0) - 3;
        if(first >= 0) List->SetFirstItem(first);
    }
    List->SetSelection(Items.Item(0));
    How2List = SEARCH;
}*/

void AGE_Frame::RefreshList(ProperList *list, vector<int> *oldies)
{
    unsigned long cookie;
    auto first_visible = list->GetVisibleRowsBegin();
    auto first_selected = list->GetFirstSelected(cookie);
    //auto last_item_count = list->GetItemCount();
    auto name_count = list->names.size();

    //list->SetItemCount(0); // Clears selections and makes all calls to SetItemPosition be ignored.
    list->SetItemCount(name_count);
    if(name_count)
    {
        // Set selections and first visible item.
        if(first_selected == wxNOT_FOUND)
        {
            first_selected = 0;
        }
        list->DeselectAll();
        if(How2List == ADD || first_selected >= name_count)
        {
            first_selected = name_count - 1;
        }
        list->ScrollToRow(first_visible);
        if(Reselection && How2List != ADD && How2List != DEL && oldies)
        {
            // Select old indexes again.
            auto old = oldies->crbegin();
            auto it = list->indexes.crbegin();
            first_selected = 0;
            while(old != oldies->crend() && it != list->indexes.crend())
            {
                if(*it == *old)
                {
                    first_selected = list->indexes.crend() - 1 - it;
                    list->Select(first_selected, true);
                    ++it;
                    ++old;
                }
                else if(*it > *old)
                {
                    ++it;
                }
                else
                {
                    ++old;
                }
            }
        }
        if(!list->GetSelectedCount())
        {
            list->Select(first_selected, true);
        }
        list->EnsureVisible(first_selected);
        if(How2List != SEARCH)
        {
            list->SetFocus();
        }
    }

    How2List = SEARCH;
    list->Refresh();
}

bool AGE_Frame::Paste11Check(size_t pastes, size_t copies)
{
    bool result = copies == pastes;
    if(!result)
    wxMessageBox(wxString::Format("%u copies, %u selections.\nClick paste tool to switch to sequential paste.", copies, pastes), "Selections Mismatch");
    return result;
}

void AGE_Frame::SearchAllSubVectors(ProperList *list, wxTextCtrl *topSearch, wxTextCtrl *subSearch)
{
    size_t selections = list->GetSelectedCount();
    wxBusyCursor WaitCursor;
    if(selections == 0) return;

    unsigned long cookie;
    set<uint32_t> topNums, subNums;
    int last = list->GetFirstSelected(cookie);
    for(size_t loop = 0; loop < selections; ++loop)
    {
        string line(list->names[last]);
        last = list->GetNextSelected(cookie);
        size_t found = line.find(" ", 3);
        topNums.insert(lexical_cast<uint32_t>(line.substr(2, found - 2)));
        subNums.insert(lexical_cast<uint32_t>(line.substr(2 + found, line.find(" ", found + 3) - found - 2)));
    }
    wxString topText;
    for(const auto &num: topNums) topText += " " + lexical_cast<string>(num) + " -|";
    topSearch->SetValue(topText.Truncate(topText.size() - 1));
    if(FilterAllSubs)
    {
        wxString subText;
        for(const auto &num: subNums) subText += " " + lexical_cast<string>(num) + " -|";
        subSearch->SetValue(subText.Truncate(subText.size() - 1));
    }
}

/*int AGE_Frame::FindItem(wxArrayInt &selections, int find, int min, int max)
{
    while(max >= min)
    {
        int mid = min + ((max - min) / 2);
        if(find == selections.Item(mid)) return mid;
        if(find > selections.Item(mid)) min = mid + 1;
        else max = mid - 1;
    }
    return -1;
}*/

void AGE_Frame::getSelectedItems(const size_t selections, const ProperList *list, vector<int> &indexes)
{
    unsigned long cookie;
    indexes.resize(selections);
    int last = list->GetFirstSelected(cookie);
    for(size_t sel = 0; sel < selections; ++sel)
    {
        indexes[sel] = list->indexes[last];
        last = list->GetNextSelected(cookie);
    }
    SetStatusText("Times listed: "+lexical_cast<string>(++times_listed), 2);
}

// To show contents of last selected item instead of first selection.
/*void AGE_Frame::SwapSelection(int last, wxArrayInt &selections)
{
    // This breaks erasing items :(
    // Look if selections include the last selection.
    int found = FindItem(selections, last, 0, selections.GetCount() - 1);
    // Swap last selection with the first one.
    if(found > 0)
    {
        int swap = selections.Item(found);
        selections.RemoveAt(found);
        selections.Insert(swap, 0);
    }
}*/

wxString AGE_Frame::FormatFloat(float value)
{
    if(popUp.accurateFloats)
    return lexical_cast<string>(value);

    stringbuf buffer;
    ostream os (&buffer);
    os << value;
    return buffer.str();
}

wxString AGE_Frame::FormatInt(int value)
{
    if(!popUp.hexMode)
    return lexical_cast<string>(value);

    stringbuf buffer;
    ostream os (&buffer);
    os << hex << uppercase << value;
    return buffer.str();
}

wxString AGE_Frame::FormatUnsigned(unsigned value)
{
    if(!popUp.hexMode)
    return lexical_cast<string>(value);

    stringbuf buffer;
    ostream os (&buffer);
    os << hex << uppercase << value;
    return buffer.str();
}

void AGE_Frame::SaveBackup()
{
    try
    {
        dataset->saveAs((DatFileName.substr(0, DatFileName.size()-4)+"_backup"+CurrentTime()+".dat").c_str());
    }
    catch(const std::ios_base::failure&)
    {
        wxMessageBox("Error saving backup!");
    }
}

wxString AGE_Frame::CurrentTime()
{
    time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    struct tm *parts = localtime(&now);

    stringbuf buffer;
    ostream os (&buffer);
    os << 1900 + parts->tm_year;
    os << setfill('0') << setw(2);
    os << 1 + parts->tm_mon;
    os << setw(2) << parts->tm_mday;
    os << setw(2) << parts->tm_hour;
    os << setw(2) << parts->tm_min;
    os << setw(2) << parts->tm_sec;
    return buffer.str();
}

AGE_SLPs* AGE_Frame::getCurrentGraphics()
{
    AGE_SLPs *graphic = 0;
    if(AGE_SLP::currentDisplay == AGE_SLP::SHOW::GRAPHIC)
    {
        graphic = &gallery;
    }
    else if(AGE_SLP::currentDisplay == AGE_SLP::SHOW::UNIT)
    {
        graphic = &museum;
    }
    return graphic;
}

void AGE_Frame::OnFrameButton(wxCommandEvent &event)
{
    switch(event.GetId())
    {
        case eNextFrame:
        {
            AGE_SLPs *graphic = getCurrentGraphics();
            if(graphic)
            {
                bool framesleft = false;
                if(graphic->slp || graphic->smp)
                {
                    ChooseNextFrame(*graphic, framesleft);
                }
                for(auto &delta: graphic->deltas)
                {
                    if(!delta.second.slp) continue;
                    ChooseNextFrame(delta.second, framesleft);
                }
                HandleLastFrame(graphic->angles, framesleft, 1u);
            }
            break;
        }
        case ePrevFrame:
        {
            AGE_SLPs *graphic = getCurrentGraphics();
            if(graphic)
            {
                bool framesleft = false;
                if(graphic->slp || graphic->smp)
                {
                    ChoosePreviousFrame(*graphic, framesleft);
                }
                for(auto &delta: graphic->deltas)
                {
                    if(!delta.second.slp) continue;
                    ChoosePreviousFrame(delta.second, framesleft);
                }
                HandleLastFrame(graphic->angles, framesleft, 2u);
            }
            break;
        }
        case eFirstFrame:
        {
            AGE_SLP::bearing = 0.f;
            AGE_SLP::setbearing = 1u;
            break;
        }
        case eExportFrame:
        {
            exportFrame = true;
            if(AGE_SLP::currentDisplay == AGE_SLP::SHOW::GRAPHIC)
            {
                if(LoadSLP(&gallery)) FrameToBitmap(&gallery, true);
                if(gallery.bitmap.IsOk())
                if(!gallery.bitmap.SaveFile(gallery.filename + ".png", wxBITMAP_TYPE_PNG))
                    wxMessageBox("Saving frame as PNG failed", "SLP");
            }
            else wxMessageBox("Choose a graphic from graphics tab", "SLP");
            exportFrame = false;
            return;
        }
        case eImportFrame:
        {
            if(AGE_SLP::currentDisplay == AGE_SLP::SHOW::GRAPHIC)
            {
                BitmapToSLP(&gallery);
            }
            animater.Start(100);
            return;
        }
        case eSaveSLP:
        {
            if(AGE_SLP::currentDisplay == AGE_SLP::SHOW::GRAPHIC)
            {
                if(!gallery.slp)
                {
                    wxMessageBox("No SLP to save", "SLP");
                    return;
                }
                if(gallery.filename.empty())
                {
                    wxMessageBox("No SLP filename", "SLP");
                    return;
                }
                wxString name = gallery.filename + ".slp";
                try
                {
                    gallery.slp->saveAs(name.c_str());
                    wxMessageBox("Saved SLP " + name, "SLP");
                }
                catch(const std::ios_base::failure&)
                {
                    wxMessageBox("Saving SLP failed", "SLP");
                }
            }
            else wxMessageBox("Look at some graphic", "SLP");
            return;
        }
        case eSLPTool:
        {
            slp_tool_on = !slp_tool_on;
            slp_tool_layout->Show(slp_tool_on);
            slp_sizer->Layout();
            slp_window->Fit();
            return;
        }
        case eZoom:
        {
            wxTextEntryDialog ted(this, "Enter new zooming %", "Set Scale Factor", lexical_cast<string>(int(slp_zoom * 100)));
            ted.SetTextValidator(wxFILTER_DIGITS);
            if(ted.ShowModal() == wxID_OK)
            {
                int zoom_percent = min(800, lexical_cast<int>(ted.GetValue()));
                slp_zoom = zoom_percent / 100.f;
                slp_zoom_btn->SetLabel("Zoom: " + lexical_cast<string>(zoom_percent) + " %");
            }
            break;
        }
        case eSLPMergeShadow:
        {
            genie::SlpFilePtr slp_src1(new genie::SlpFile());
            genie::SlpFilePtr slp_src2(new genie::SlpFile());
            try
            {
                slp_src1->load(slp_source1->GetPath().c_str());
                slp_src1->freelock();
                slp_src2->load(slp_source2->GetPath().c_str());
                slp_src2->freelock();
            }
            catch(const std::ios_base::failure&)
            {
                wxMessageBox("Error reading SLP files", "SLP");
                return;
            }
            for(uint32_t frame = 0; frame < slp_src1->getFrameCount(); ++frame)
            {
                genie::SlpFramePtr frame1, frame2;
                try
                {
                    frame1 = slp_src1->getFrame(frame);
                    frame2 = slp_src2->getFrame(frame);
                }
                catch(const out_of_range&)
                {
                    wxMessageBox("Frame count mismatch", "SLP");
                    break;
                }

                int32_t offset_x, offset_y;
                // Resize frame if the other frame is bigger in some dimension.
                frame1->enlargeForMerge(*frame2, offset_x, offset_y);
                uint32_t width = frame1->getWidth(), height = frame1->getHeight();

                genie::SlpFrameData *imgdata = &frame1->img_data;
                imgdata->shadow_mask.clear();
                for(auto const &shadow_pixel: frame2->img_data.shadow_mask)
                {
                    const uint32_t x = shadow_pixel.x + offset_x,
                        y = shadow_pixel.y + offset_y,
                        slot = y * width + x;
                    if(x < width && y < height)
                    {
                        if(imgdata->alpha_channel[slot] == 0)
                        {
                            imgdata->shadow_mask.push_back({x, y});
                        }
                    }
                }
            }
            try
            {
                slp_src1->saveAs(slp_target1->GetPath().c_str());
                wxMessageBox("Merged SLP files", "SLP");
            }
            catch(const std::ios_base::failure&)
            {
                wxMessageBox("Saving SLP failed", "SLP");
            }
            return;
        }
        case eShowHotspot:
        {
            DrawHot = event.IsChecked();
            break;
        }
        case eShowAngles:
        {
            DrawAngles = event.IsChecked();
            break;
        }
        case eAnimSLP:
        {
            AnimSLP = event.IsChecked();
            break;
        }
        case eShowShadows:
        {
            ShowShadows = event.IsChecked();
            break;
        }
        case eShowOutline:
        {
            ShowOutline = event.IsChecked();
            break;
        }
        case eShowDeltas:
        {
            ShowDeltas = event.IsChecked();
            gallery.slpID = museum.slpID = RELOAD;
            break;
        }
        case eShowStack:
        {
            ShowStack = event.IsChecked();
            gallery.slpID = museum.slpID = RELOAD;
            break;
        }
        case eShowAnnexes:
        {
            ShowAnnexes = event.IsChecked();
            gallery.slpID = museum.slpID = RELOAD;
            break;
        }
        case eRotateAngles:
        {
            RotateAngles = event.IsChecked();
            break;
        }
        case eShowTerrain:
        {
            DrawTerrain = event.IsChecked();
            break;
        }
        case ePickBgColor:
        {
            wxColour back(slp_background->GetColour());
            ViewBackR = back.Red();
            ViewBackG = back.Green();
            ViewBackB = back.Blue();
            slp_background_brush = wxBrush(back);
            break;
        }
        case eCollisionShape:
        {
            DrawCollisionShape = event.IsChecked();
            break;
        }
        case eClearanceShape:
        {
            DrawClearanceShape = event.IsChecked();
            break;
        }
        case eOutline:
        {
            DrawOutline = event.IsChecked();
            break;
        }
        case ePlaySounds:
        {
            PlaySounds = event.IsChecked();
            break;
        }
    }
    slp_view->Refresh();
}

void AGE_Frame::OnFrameMouse(wxMouseEvent &event)
{
    int centerX, centerY;
    CalcDrawCenter(slp_view, centerX, centerY);
    wxPoint coords(slp_view->ScreenToClient(wxGetMousePosition()));
    coords.x -= centerX;
    coords.y -= centerY;
    AGE_SLP::bearing = atan2(coords.x, -coords.y << 1) + 3.1416f;
    assert(AGE_SLP::bearing >= 0.f && PI2 >= AGE_SLP::bearing);
    AGE_SLP::setbearing = 1u;
    slp_view->Refresh();
}

void AGE_Frame::OnFrameKey(wxKeyEvent &event)
{
    if(!dataset) return;
    vector<int16_t*> dx(DeltaIDs.size()), dy(DeltaIDs.size());
    if(GraphicIDs.size())
    {
        for(size_t i = 0; i < DeltaIDs.size(); ++i)
        {
            dx[i] = &dataset->Graphics[GraphicIDs.front()].Deltas[DeltaIDs[i]].OffsetX;
            dy[i] = &dataset->Graphics[GraphicIDs.front()].Deltas[DeltaIDs[i]].OffsetY;
        }
    }
    switch(event.GetKeyCode())
    {
        case 'A':
        {
            slp_extra_info = "X - 1";
            for(size_t i = 0; i < dx.size(); ++i) --*dx[i];
            break;
        }
        case 'D':
        {
            slp_extra_info = "X + 1";
            for(size_t i = 0; i < dx.size(); ++i) ++*dx[i];
            break;
        }
        case 'S':
        {
            slp_extra_info = "Y + 1";
            for(size_t i = 0; i < dy.size(); ++i) ++*dy[i];
            break;
        }
        case 'W':
        {
            slp_extra_info = "Y - 1";
            for(size_t i = 0; i < dy.size(); ++i) --*dy[i];
            break;
        }
        default: return;
    }
    popUp.unSaved += DeltaIDs.size();
    wxCommandEvent e;
    OnGraphicDeltaSelect(e);
    gallery.slpID = RELOAD;
    slp_view->Refresh();
}

void AGE_Frame::OnExitSLP(wxCloseEvent &event)
{
    SubMenu_SLP->Check(eShowSLP, false);
    wxCommandEvent closeSLP(wxEVT_MENU, eShowSLP);
    closeSLP.SetInt(false);
    OnMenuOption(closeSLP);
}

void AGE_Frame::OnExit(wxCloseEvent &event)
{
    {
        wxConfig Config("", "", "AGE2\\ConfigWindow"+lexical_cast<string>(window_num + 1), "", wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
        Config.Write("DefaultFiles/AutoBackups", AutoBackups);
        Config.Write("DefaultFiles/PalettesPath", PalettesPath);
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
        Config.Write("Interface/ShowUnknowns", ShowUnknowns);
        Config.Write("Interface/ResizeTerrains", ResizeTerrains);
        Config.Write("Interface/StayOnTop", StayOnTop);
        Config.Write("Interface/KeepViewOnTop", KeepViewOnTop);
        Config.Write("Interface/Paste11", Paste11);
        Config.Write("Interface/Reselection", Reselection);
        Config.Write("Interface/MaxWindowWidthV2", MaxWindowWidthV2);
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
        Config.Write("Interface/CacheDepth", GG::cache_depth);
        Config.Write("Interface/ViewPosX", ViewPosX);
        Config.Write("Interface/ViewPosY", ViewPosY);
        Config.Write("Interface/BoxWidthMultiplier", boxWidthMultiplier);
    }

    if(event.CanVeto() && popUp.unSaved > 0)
    {
        int answer = wxMessageBox("Do you want to save changes made to open files?\nThere are "
                        +lexical_cast<string>(popUp.unSaved)+" unsaved changes.",
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

    AGE_Frame::openEditors[window_num] = 0;
    while(animater.IsRunning())
    {
        if(event.CanVeto())
        {
            event.Veto();
            return;
        }
    }
    popUp.loadedFileId = -1;
    Destroy();
}
