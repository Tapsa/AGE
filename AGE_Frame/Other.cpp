#include "../AGE_Frame.h"
#include "../DRSunlock.xpm"
#include "../DRSlock.xpm"
#include "../Tree32.xpm"

wxArrayString AGE_AreaTT84::ages, AGE_AreaTT84::researches, AGE_AreaTT84::units;
float AGE_SLP::bearing = 0.f;
unsigned AGE_SLP::setbearing = 0u;

void AGE_Frame::OnOpen(wxCommandEvent &event)
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
                wxCommandEvent SaveFiles(wxEVT_COMMAND_MENU_SELECTED, eSave);
                ProcessEvent(SaveFiles);
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
		AGE_OpenDialog OpenBox(this);

        int RecentItems;
        {
            wxFileConfig RecentOpen("AGE", "Tapsa", "age3recent.ini", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
            RecentOpen.Read("Recent/Items", &RecentItems, 0);
            OpenBox.RecentValues.resize(RecentItems);
            for(int i=0; i < RecentItems; ++i)
            {
                OpenBox.RecentValues[i].Alloc(8);
                wxString temp, entry = "Recent" + lexical_cast<string>(i + 1);
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
        OpenBox.CheckBox_Recent->Append("10 point hint: donate euros to me");
        OpenBox.CheckBox_Recent->SetSelection(0);

		OpenBox.CheckBox_CustomDefault->SetValue(UseCustomPath);
		OpenBox.Path_CustomDefault->SetPath(CustomFolder);
		OpenBox.CheckBox_GenieVer->SetSelection(GameVersion);
        OpenBox.TerrainsBox->Enable(ResizeTerrains);

		OpenBox.DriveLetterBox->ChangeValue(DriveLetter);
		OpenBox.LanguageBox->ChangeValue(Language);
		OpenBox.TerrainsBox->ChangeValue(lexical_cast<string>(CustomTerrains));
		OpenBox.Path_DRS->SetPath(FolderDRS);
		OpenBox.Path_DRS2->SetPath(FolderDRS2);
		OpenBox.Path_DRS3->SetPath(Path1stDRS);
		OpenBox.CheckBox_DRSPath->SetValue(UseDRS);
		OpenBox.CheckBox_DRSPath2->SetValue(UseMod);
		OpenBox.CheckBox_DRSPath3->SetValue(UseExtra);

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
		UseCustomPath = OpenBox.CheckBox_CustomDefault->GetValue();
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
		UseDRS = OpenBox.CheckBox_DRSPath->GetValue();
		UseMod = OpenBox.CheckBox_DRSPath2->GetValue();
		UseExtra = OpenBox.CheckBox_DRSPath3->GetValue();
		WriteLangs = OpenBox.CheckBox_LangWrite->GetValue();
		LangWriteToLatest = OpenBox.CheckBox_LangWriteToLatest->GetValue();

		if(!load)
		{
			return;
		}
		popUp.unSaved = 0;
		++popUp.loadedFileId;

        wxFileConfig Config("AGE", "Tapsa", "age2configw"+lexical_cast<string>(window_num + 1)+".ini", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
        Config.Write("DefaultFiles/DriveLetter", DriveLetter);
        Config.Write("DefaultFiles/UseCustomPath", UseCustomPath);
        Config.Write("DefaultFiles/CustomFolder", CustomFolder);
        Config.Write("DefaultFiles/Version", GameVersion);
        Config.Write("DefaultFiles/DatUsed", DatUsed);
        Config.Write("DefaultFiles/DatFilename", DatFileName);
        Config.Write("DefaultFiles/FolderDRS", FolderDRS);
        Config.Write("DefaultFiles/FolderDRS2", FolderDRS2);
        Config.Write("DefaultFiles/Path1stDRS", Path1stDRS);
        Config.Write("DefaultFiles/UseDRS", UseDRS);
        Config.Write("DefaultFiles/UseMod", UseMod);
        Config.Write("DefaultFiles/UseExtra", UseExtra);
        Config.Write("DefaultFiles/LangsUsed", LangsUsed);
        Config.Write("DefaultFiles/WriteLangs", WriteLangs);
        Config.Write("DefaultFiles/LangWriteToLatest", LangWriteToLatest);
        Config.Write("DefaultFiles/Language", Language);
        Config.Write("DefaultFiles/LangFilename", LangFileName);
        Config.Write("DefaultFiles/LangX1Filename", LangX1FileName);
        Config.Write("DefaultFiles/LangX1P1Filename", LangX1P1FileName);
        Config.Write("DefaultFiles/AutoBackups", AutoBackups);
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
        wxFileConfig RecentSave("AGE", "Tapsa", "age3recent.ini", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
        RecentSave.Write("Recent/Items", items);
        for(int i=0; i < items; ++i)
        {
            wxString entry = "Recent" + lexical_cast<string>(i + 1);
            RecentSave.Write(entry + "/DatVersion", OpenBox.RecentValues[i][0]);
            RecentSave.Write(entry + "/DatPath", OpenBox.RecentValues[i][1]);
            RecentSave.Write(entry + "/Lang", OpenBox.RecentValues[i][2]);
            RecentSave.Write(entry + "/LangX1", OpenBox.RecentValues[i][3]);
            RecentSave.Write(entry + "/LangX1P1", OpenBox.RecentValues[i][4]);
            RecentSave.Write(entry + "/PathDRS", OpenBox.RecentValues[i][5]);
            RecentSave.Write(entry + "/PathDRS2", OpenBox.RecentValues[i][6]);
            RecentSave.Write(entry + "/PathDRS3", OpenBox.RecentValues[i][7]);
        }
	}

	switch(GameVersion)
	{
		case EV_TEST: GenieVersion = genie::GV_TEST; break;
		case EV_MIK: GenieVersion = genie::GV_MIK; break;
		case EV_DAVE: GenieVersion = genie::GV_DAVE; break;
		case EV_MATT: GenieVersion = genie::GV_MATT; break;
		case EV_AoEB: GenieVersion = genie::GV_AoEB; break;
		case EV_AoE: GenieVersion = genie::GV_AoE; break;
		case EV_RoR: GenieVersion = genie::GV_RoR; break;
		case EV_AoKA: GenieVersion = genie::GV_AoKA; break;
		case EV_AoKB: GenieVersion = genie::GV_AoKB; break;
		case EV_AoK: GenieVersion = genie::GV_AoK; break;
		case EV_TC: GenieVersion = genie::GV_TC; break;
		case EV_Cysion: GenieVersion = genie::GV_Cysion; break;
		case EV_SWGB: GenieVersion = genie::GV_SWGB; break;
		case EV_CC: GenieVersion = genie::GV_CC; break;
		case EV_EF: GenieVersion = genie::GV_CC; break;
		default: GenieVersion = genie::GV_None; wxMessageBox("Wrong version", "Oops!");
	}

	if(dataset)
	{
		delete dataset;
		dataset = 0;
	}
	else
	{
		TabBar_Main->ChangeSelection(4);
	}

    if(wxFileName(DatFileName).FileExists())
	{
		SetStatusText("Reading file...", 0);
		wxBusyCursor WaitCursor;

		dataset = new genie::DatFile();
		try
		{
			genie::Terrain::setTerrainCount(ResizeTerrains ? CustomTerrains : 0);
#ifndef NDEBUG
            dataset->setVerboseMode(true);
#endif
			dataset->setGameVersion(GenieVersion);
			dataset->load(DatFileName.c_str());
		}
		catch(std::ios_base::failure e)
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
        LoadTXT(LangFileName);
        if(LangX1FileName.size() && 't' == LangX1FileName[LangX1FileName.size() - 1])
        LoadTXT(LangX1FileName);
        if(LangX1P1FileName.size() && 't' == LangX1P1FileName[LangX1P1FileName.size() - 1])
        LoadTXT(LangX1P1FileName);
	}
	else
	{
        UseTXT = false;
		if(Lang)
		{
			delete Lang;
			Lang = 0;
		}
		if(LangX)
		{
			delete LangX;
			LangX = 0;
		}
		if(LangXP)
		{
			delete LangXP;
			LangXP = 0;
		}

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
				catch(std::ios_base::failure e)
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
				catch(std::ios_base::failure e)
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
				catch(std::ios_base::failure e)
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
    wxCommandEvent loadDRS(wxEVT_COMMAND_MENU_SELECTED, eDRS);
    loadDRS.SetInt(false);
    ProcessEvent(loadDRS);
    if(UseDRS)
	{
        if(UseTXT)
        {
            palettes.clear();
            loadPalette(FolderDRS);
            if(UseMod) loadPalette(FolderDRS2);
            // Load extra palettes
            wxString folder = FolderDRS, res;
            folder.Replace("drs", "dat", false);
            wxDir dir(folder);
            if(!dir.IsOpened()) return;
            bool found = dir.GetFirst(&res, "*.pal");
            while(found)
            {
                try
                {
                    genie::PalFile pal;
                    pal.load((folder + "\\" + res).c_str());
                    palettes.push_back(pal.getColors());
                }
                catch(std::ios_base::failure e){}
                found = dir.GetNext(&res);
            }
        }
        else
        {
            GetToolBar()->ToggleTool(eDRS, true);
            loadDRS.SetInt(true);
            ProcessEvent(loadDRS);
        }
	}

	if(dataset)
	{	// Without these, nothing can be edited.
		SetStatusText("Listing...", 0);
		wxBusyCursor WaitCursor;

		// No research gaia fix.
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
			{
				if(dataset->Civs[loop].UnitPointers[loop2] != 0)
				{
					dataset->Civs[loop].UnitPointers[loop2] = 1;
					if(EnableIDFix)
					{
						dataset->Civs[loop].Units[loop2].ID1 = loop2;
						if(GenieVersion >= genie::GV_AoE)
						dataset->Civs[loop].Units[loop2].ID2 = loop2;
						if(GenieVersion >= genie::GV_AoK)
						dataset->Civs[loop].Units[loop2].ID3 = loop2;
						else
						if(dataset->Civs[loop].Units[loop2].Type >= 40 && dataset->Civs[loop].Units[loop2].Type <= 80)
						for(size_t loop3 = dataset->Civs[loop].Units[loop2].Bird.Commands.size(); loop3--> 0;)
						dataset->Civs[loop].Units[loop2].Bird.Commands[loop3].ID = loop3;
					}
				}
			}
		}
		if(EnableIDFix)
		{
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
		}
		if(GenieVersion >= genie::GV_AoE)
		for(size_t loop = dataset->Graphics.size(); loop--> 0;)
		{
			if(dataset->GraphicPointers[loop] != 0)
			{
				dataset->GraphicPointers[loop] = 1;
				if(EnableIDFix)
				dataset->Graphics[loop].ID = loop;
			}
		}
		for(size_t loop = dataset->TerrainRestrictions.size(); loop--> 0;)
		{
			if(dataset->TerrainRestrictionPointers1[loop] != 0)
			dataset->TerrainRestrictionPointers1[loop] = 1;
			if(GenieVersion >= genie::GV_AoKA)
			if(dataset->TerrainRestrictionPointers2[loop] != 0)
			dataset->TerrainRestrictionPointers2[loop] = 1;
		}

		How2List = SEARCH;

		UnitCommands_Type_ComboBox->Clear();
		UnitCommands_Type_ComboBox->Append("Unused Ability/Invalid Ability");	// Selection 0
		//UnitCommands_Type_ComboBox->Append("0: Unknown Ability");
		UnitCommands_Type_ComboBox->Append("1: Move to");
		UnitCommands_Type_ComboBox->Append("2: Follow");
		UnitCommands_Type_ComboBox->Append("3: Garrison");
		UnitCommands_Type_ComboBox->Append("4: Explore");
		UnitCommands_Type_ComboBox->Append("5: Gather/Rebuild");
		UnitCommands_Type_ComboBox->Append("6: Natural Wonders Cheat");
		UnitCommands_Type_ComboBox->Append("7: Attack");
		UnitCommands_Type_ComboBox->Append("8: Shoot");
		UnitCommands_Type_ComboBox->Append("10: Fly");
		UnitCommands_Type_ComboBox->Append("11: Scare/Hunt");
		UnitCommands_Type_ComboBox->Append("12: Unload (Boat-Like)");
		UnitCommands_Type_ComboBox->Append("13: Guard");
		UnitCommands_Type_ComboBox->Append("14: Siege Tower Ability");
		//UnitCommands_Type_ComboBox->Append("15: Unknown Ability");
		//UnitCommands_Type_ComboBox->Append("17: Unknown Ability");
		//UnitCommands_Type_ComboBox->Append("18: Unknown Ability");
		//UnitCommands_Type_ComboBox->Append("19: Unknown Ability");
		UnitCommands_Type_ComboBox->Append("20: Escape?");
		UnitCommands_Type_ComboBox->Append("21: Make");
		//UnitCommands_Type_ComboBox->Append("22: Unknown Ability");
		//UnitCommands_Type_ComboBox->Append("24: Unknown Ability");
		//UnitCommands_Type_ComboBox->Append("100: Unknown Ability");
		UnitCommands_Type_ComboBox->Append("101: Build");
		UnitCommands_Type_ComboBox->Append("102: Make an Object");
		UnitCommands_Type_ComboBox->Append("103: Make a Tech");
		UnitCommands_Type_ComboBox->Append("104: Convert");
		UnitCommands_Type_ComboBox->Append("105: Heal");
		UnitCommands_Type_ComboBox->Append("106: Repair");
		UnitCommands_Type_ComboBox->Append("107: Get Auto-converted");
		UnitCommands_Type_ComboBox->Append("108: Discovery");
		UnitCommands_Type_ComboBox->Append("109: Retreat to Shooting Range");
		UnitCommands_Type_ComboBox->Append("110: Hunt");
		UnitCommands_Type_ComboBox->Append("111: Trade");
		//UnitCommands_Type_ComboBox->Append("112: Unknown Ability");
		//UnitCommands_Type_ComboBox->Append("113: Unknown Ability");
		UnitCommands_Type_ComboBox->Append("120: Generate Wonder Victory");
		UnitCommands_Type_ComboBox->Append("121: Deselect when Tasked");
		UnitCommands_Type_ComboBox->Append("122: Loot");
		UnitCommands_Type_ComboBox->Append("123: Housing");
		UnitCommands_Type_ComboBox->Append("124: Pack");
		UnitCommands_Type_ComboBox->Append("125: Unpack & Attack");
		UnitCommands_Type_ComboBox->Append("130: Off-Map Trade 1");
		UnitCommands_Type_ComboBox->Append("131: Off-Map Trade 2");
		UnitCommands_Type_ComboBox->Append("132: Pickup Unit");
		UnitCommands_Type_ComboBox->Append("133: Unknown Pickup Ability");
		UnitCommands_Type_ComboBox->Append("134: Unknown Pickup Ability");
		UnitCommands_Type_ComboBox->Append("135: Kidnap Unit");
		UnitCommands_Type_ComboBox->Append("136: Deposit Unit");	// Selection 33
		UnitCommands_Type_ComboBox->Append("149: Shear");	// Selection 33
		UnitCommands_Type_ComboBox->Append("150: Regeneration");
		UnitCommands_Type_ComboBox->Append("151: Feitoria Ability");
		UnitCommands_Type_ComboBox->SetSelection(0);

		AGE_AreaTT84::ages.Clear();
		if(GenieVersion >= genie::GV_SWGB)
		{
			AGE_AreaTT84::ages.Add("0 - None");
			AGE_AreaTT84::ages.Add("1st Tech Level");
			AGE_AreaTT84::ages.Add("2nd Tech Level");
			AGE_AreaTT84::ages.Add("3rd Tech Level");
			AGE_AreaTT84::ages.Add("4th Tech Level");
			AGE_AreaTT84::ages.Add("5th Tech Level");
		}
		else if(GenieVersion >= genie::GV_AoKA)
		{
			AGE_AreaTT84::ages.Add("0 - None");
			AGE_AreaTT84::ages.Add("Dark Age");
			AGE_AreaTT84::ages.Add("Feudal Age");
			AGE_AreaTT84::ages.Add("Castle Age");
			AGE_AreaTT84::ages.Add("Imperial Age");
			AGE_AreaTT84::ages.Add("Post-Imperial Age");
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
        DefRoRCivRes.Add("Gold Storage ");
        DefRoRCivRes.Add("Population Headroom");
        DefRoRCivRes.Add("Conversion Range");
        DefRoRCivRes.Add("Current Age");
        DefRoRCivRes.Add("Artifacts Captured");
        DefRoRCivRes.Add("Trade Bonus");
        DefRoRCivRes.Add("Trade Goods");
        DefRoRCivRes.Add("Trade Production");
        DefRoRCivRes.Add("Current Population");
        DefRoRCivRes.Add("Corpse Decay Time");
        DefRoRCivRes.Add("Discovery");
        DefRoRCivRes.Add("Ruins Captured");
        DefRoRCivRes.Add("Meat Storage");
        DefRoRCivRes.Add("Berry Storage");
        DefRoRCivRes.Add("Fish Storage");
        DefRoRCivRes.Add("Unknown");
        DefRoRCivRes.Add("Total Units Owned");
        DefRoRCivRes.Add("Units Killed");
        DefRoRCivRes.Add("Research Count");
        DefRoRCivRes.Add("% Map Explored");
        DefRoRCivRes.Add("Bronze Age tech ID");
        DefRoRCivRes.Add("Iron Age tech ID");
        DefRoRCivRes.Add("Tool Age tech ID");
        DefRoRCivRes.Add("Attack Warning Sound ID");
        DefRoRCivRes.Add("Enable Priest Conversion");
        DefRoRCivRes.Add("Enable Building Conversion");
        DefRoRCivRes.Add("Unknown");
        DefRoRCivRes.Add("Building Count");
        DefRoRCivRes.Add("Food Count");
        DefRoRCivRes.Add("Unit Count");
        DefRoRCivRes.Add("Maintenance");
        DefRoRCivRes.Add("Faith");
        DefRoRCivRes.Add("Faith Recharging Rate");
        DefRoRCivRes.Add("Farm Food Amount");
        DefRoRCivRes.Add("Civilian Population");
        DefRoRCivRes.Add("Unknown");
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
        DefRoRCivRes.Add("Amount Houses");
        DefRoRCivRes.Add("Monasteries");
        DefRoRCivRes.Add("Tribute Sent");
        DefRoRCivRes.Add("All Ruins Have Been Captured");
        DefRoRCivRes.Add("All Relics Have Been Captured");
        DefRoRCivRes.Add("RoR: Medicine");
        DefRoRCivRes.Add("RoR: Martyrdom");

        // AoK & TC
		DefAoE2Armors.Add("0 - Unused");
		DefAoE2Armors.Add("1 - Infantry");	// Selection 2
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
		DefAoE2Armors.Add("14 - Predator Animals"); // FE
		DefAoE2Armors.Add("15 - Archers");
		DefAoE2Armors.Add("16 - Ships & Camels & Saboteurs");
		DefAoE2Armors.Add("17 - Rams");
		DefAoE2Armors.Add("18 - Trees");
		DefAoE2Armors.Add("19 - Unique Units (except Turtle Ship)");
		DefAoE2Armors.Add("20 - Siege Weapons");
		DefAoE2Armors.Add("21 - Standard Buildings");
		DefAoE2Armors.Add("22 - Walls & Gates");
		DefAoE2Armors.Add("23 - Gunpowder Units"); // FE
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
        DefAoKCivRes.Add("Gold Storage ");
        DefAoKCivRes.Add("Population Headroom");
        DefAoKCivRes.Add("Conversion Range");
        DefAoKCivRes.Add("Current Age");
        DefAoKCivRes.Add("Relics Captured");
        DefAoKCivRes.Add("Trade Bonus");
        DefAoKCivRes.Add("Trade Goods");
        DefAoKCivRes.Add("Trade Production");
        DefAoKCivRes.Add("Current Population");
        DefAoKCivRes.Add("Corpse Decay Time");
        DefAoKCivRes.Add("Discovery");
        DefAoKCivRes.Add("Monuments Captured");
        DefAoKCivRes.Add("Meat Storage");
        DefAoKCivRes.Add("Berry Storage");
        DefAoKCivRes.Add("Fish Storage");
        DefAoKCivRes.Add("Unknown");
        DefAoKCivRes.Add("Total Units Owned");
        DefAoKCivRes.Add("Units Killed");
        DefAoKCivRes.Add("Research Count");
        DefAoKCivRes.Add("% Map Explored");
        DefAoKCivRes.Add("Castle Age tech ID");
        DefAoKCivRes.Add("Imperial Age tech ID");
        DefAoKCivRes.Add("Feudal Age tech ID");
        DefAoKCivRes.Add("Attack Warning Sound ID");
        DefAoKCivRes.Add("Enable Monk Conversion");
        DefAoKCivRes.Add("Enable Building Conversion");
        DefAoKCivRes.Add("Unknown");
        DefAoKCivRes.Add("Building Count");
        DefAoKCivRes.Add("Food Count");
        DefAoKCivRes.Add("Bonus Population Cap");
        DefAoKCivRes.Add("Maintenance");
        DefAoKCivRes.Add("Faith");
        DefAoKCivRes.Add("Faith Recharging Rate");
        DefAoKCivRes.Add("Farm Food Amount");
        DefAoKCivRes.Add("Civilian Population");
        DefAoKCivRes.Add("Unknown");
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
        DefAoKCivRes.Add("Amount Houses");
        DefAoKCivRes.Add("Monasteries");
        DefAoKCivRes.Add("Tribute Sent");
        DefAoKCivRes.Add("All Ruins Have Been Captured");
        DefAoKCivRes.Add("All Relics Have Been Captured");
        DefAoKCivRes.Add("Ore Storage");
        DefAoKCivRes.Add("Kidnap Storage");
        DefAoKCivRes.Add("Dark Age tech ID");
        DefAoKCivRes.Add("Trade Good Quality");
        DefAoKCivRes.Add("Trade Market Level");
        DefAoKCivRes.Add("Formations");
        DefAoKCivRes.Add("Building Housing Rate");
        DefAoKCivRes.Add("Tax Gather Rate");
        DefAoKCivRes.Add("Gather Accumulator");
        DefAoKCivRes.Add("Salvage Decay Rate");
        DefAoKCivRes.Add("Allow Formations");
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
        DefAoKCivRes.Add("Start with Packed Town Center");
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
        DefAoKCivRes.Add("Object Cost Sum");
        DefAoKCivRes.Add("Research Cost Sum");
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

		// SWGB & CC
		DefSWGBArmors.Add("0 - Aircraft");	// Selection 1
		// Airspeeder
		// AIR SHIPS!!!
		// Geonosian Warrior
		// Wild Gungan Flyer
		DefSWGBArmors.Add("1 - Heavy Assault Machines");	// Selection 2
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
		DefSWGBArmors.Add("30 - Tame Animals");	// Selection 31
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
        DefSWGBCivRes.Add("Nova Storage ");
        DefSWGBCivRes.Add("Population Headroom");
        DefSWGBCivRes.Add("Conversion Range");
        DefSWGBCivRes.Add("Current Age");
        DefSWGBCivRes.Add("Holocrons Captured");
        DefSWGBCivRes.Add("Trade Bonus");
        DefSWGBCivRes.Add("Trade Goods");
        DefSWGBCivRes.Add("Recharge Rate of Shields");
        DefSWGBCivRes.Add("Current Population");
        DefSWGBCivRes.Add("Corpse Decay Time");
        DefSWGBCivRes.Add("Discovery");
        DefSWGBCivRes.Add("Monuments Captured");
        DefSWGBCivRes.Add("Meat Storage");
        DefSWGBCivRes.Add("Berry Storage");
        DefSWGBCivRes.Add("Fish Storage");
        DefSWGBCivRes.Add("Power Core Range");
        DefSWGBCivRes.Add("Total Units Owned");
        DefSWGBCivRes.Add("Units Killed");
        DefSWGBCivRes.Add("Research Count");
        DefSWGBCivRes.Add("% Map Explored");
        DefSWGBCivRes.Add("Submarine Detection");
        DefSWGBCivRes.Add("Shield Generator Range");
        DefSWGBCivRes.Add("Unknown");
        DefSWGBCivRes.Add("Drop-off Time of Shields");
        DefSWGBCivRes.Add("Enable Jedi Conversion");
        DefSWGBCivRes.Add("Enable Building Conversion");
        DefSWGBCivRes.Add("Unknown");
        DefSWGBCivRes.Add("Building Count");
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
        DefSWGBCivRes.Add("All Ruins Have Been Captured");
        DefSWGBCivRes.Add("All Relics Have Been Captured");
        DefSWGBCivRes.Add("Enable Stealth for Masters");
        DefSWGBCivRes.Add("Kidnap Storage");
        DefSWGBCivRes.Add("Masters Can See Hidden Units");
        DefSWGBCivRes.Add("Trade Good Quality");
        DefSWGBCivRes.Add("Trade Market Level");
        DefSWGBCivRes.Add("Formations");
        DefSWGBCivRes.Add("Building Housing Rate");
        DefSWGBCivRes.Add("Tax Gather Rate");
        DefSWGBCivRes.Add("Gather Accumulator");
        DefSWGBCivRes.Add("Salvage Decay Rate");
        DefSWGBCivRes.Add("Allow Formations");
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
        DefSWGBCivRes.Add("Research Cost Modifier");
        DefSWGBCivRes.Add("Research Time Modifier");
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
        DefSWGBCivRes.Add("Research Cost Sum");
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

        wxFileConfig Customs("AGE", "Tapsa", "age3namesV0001.ini", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
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
        wxArrayString AoE1Armors, AoE2Armors, SWGBArmors;
        wxString read_buf;
        for(size_t loop = 0; loop < AoE1Count; ++loop)
        {
            if(!Customs.Read("AoE1Names/"+lexical_cast<string>(loop), &read_buf, DefAoE1Armors[loop]))
                Customs.Write("AoE1Names/"+lexical_cast<string>(loop), DefAoE1Armors[loop]);
            AoE1Armors.Add(read_buf);
        }
        for(size_t loop = 0; loop < AoE2Count; ++loop)
        {
            if(!Customs.Read("AoE2Names/"+lexical_cast<string>(loop), &read_buf, DefAoE2Armors[loop]))
                Customs.Write("AoE2Names/"+lexical_cast<string>(loop), DefAoE2Armors[loop]);
            AoE2Armors.Add(read_buf);
        }
        for(size_t loop = 0; loop < SWGBCount; ++loop)
        {
            if(!Customs.Read("SWGBNames/"+lexical_cast<string>(loop), &read_buf, DefSWGBArmors[loop]))
                Customs.Write("SWGBNames/"+lexical_cast<string>(loop), DefSWGBArmors[loop]);
            SWGBArmors.Add(read_buf);
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

		for(size_t loop = 0; loop < 3; ++loop)
		{
			Units_Class_ComboBox[loop]->Clear();
			Units_Class_ComboBox[loop]->Append("No Class/Invalid Class");	// Selection 0
			if(GenieVersion < genie::GV_SWGB)
			{
				Units_Class_ComboBox[loop]->Append("0 - Archer");// archery-class
				Units_Class_ComboBox[loop]->Append("1 - Artifact/Ruins");
				Units_Class_ComboBox[loop]->Append("2 - Trade Boat");
				Units_Class_ComboBox[loop]->Append("3 - Building");// building-class
				Units_Class_ComboBox[loop]->Append("4 - Civilian");// villager-class
				Units_Class_ComboBox[loop]->Append("5 - Ocean Fish");// ocean-fish-class
				Units_Class_ComboBox[loop]->Append("6 - Infantry");// infantry-class
				Units_Class_ComboBox[loop]->Append("7 - Berry Bush");// forage-food
				Units_Class_ComboBox[loop]->Append("8 - Stone Mine");
				Units_Class_ComboBox[loop]->Append("9 - Prey Animal");// deer-food
				Units_Class_ComboBox[loop]->Append("10 - Predator Animal");// boar-food
				Units_Class_ComboBox[loop]->Append("11 - Other/Dead/Projectile");
				Units_Class_ComboBox[loop]->Append("12 - Cavalry");// cavalry-class
				Units_Class_ComboBox[loop]->Append("13 - Siege Weapon");// siege-weapon-class
				Units_Class_ComboBox[loop]->Append("14 - Terrain");
				Units_Class_ComboBox[loop]->Append("15 - Tree");
				Units_Class_ComboBox[loop]->Append("16 - Tree Stump");
				Units_Class_ComboBox[loop]->Append("17 - Unused");
				Units_Class_ComboBox[loop]->Append("18 - Priest");// monastery-class
				Units_Class_ComboBox[loop]->Append("19 - Trade Cart");
				Units_Class_ComboBox[loop]->Append("20 - Transport Boat");
				Units_Class_ComboBox[loop]->Append("21 - Fishing Boat");
				Units_Class_ComboBox[loop]->Append("22 - Warship");// warship-class
				if(GenieVersion < genie::GV_AoKA)
					Units_Class_ComboBox[loop]->Append("23 - Chariot Archer");
				else
					Units_Class_ComboBox[loop]->Append("23 - Conquistador");// cavalry-cannon-class
				Units_Class_ComboBox[loop]->Append("24 - War Elephant");
				Units_Class_ComboBox[loop]->Append("25 - Hero");
				Units_Class_ComboBox[loop]->Append("26 - Elephant Archer");
				Units_Class_ComboBox[loop]->Append("27 - Wall");// wall-class
				Units_Class_ComboBox[loop]->Append("28 - Phalanx");
				Units_Class_ComboBox[loop]->Append("29 - Domesticated Animal");
				Units_Class_ComboBox[loop]->Append("30 - Flag");
				Units_Class_ComboBox[loop]->Append("31 - Unknown Fish");
				Units_Class_ComboBox[loop]->Append("32 - Gold Mine");
				Units_Class_ComboBox[loop]->Append("33 - Shore Fish");// fish-food // shore-fish-class
				Units_Class_ComboBox[loop]->Append("34 - Cliff");
				if(GenieVersion < genie::GV_AoKA)
					Units_Class_ComboBox[loop]->Append("35 - Chariot");
				else
					Units_Class_ComboBox[loop]->Append("35 - Petard");// petard-class
				Units_Class_ComboBox[loop]->Append("36 - Cavalry Archer");// cavalry-archer-class
				Units_Class_ComboBox[loop]->Append("37 - Dolphin/Smoke");
				Units_Class_ComboBox[loop]->Append("38 - Bird");
				if(GenieVersion < genie::GV_AoKA)
					Units_Class_ComboBox[loop]->Append("39 - Slinger");
				else
					Units_Class_ComboBox[loop]->Append("39 - Gate");// gate-class
				Units_Class_ComboBox[loop]->Append("40 - Pile");
				Units_Class_ComboBox[loop]->Append("41 - Pile of Resource");
				Units_Class_ComboBox[loop]->Append("42 - Relic");
				Units_Class_ComboBox[loop]->Append("43 - Monk with Relic");
				Units_Class_ComboBox[loop]->Append("44 - Hand Cannoneer");// archery-cannon-class
				Units_Class_ComboBox[loop]->Append("45 - Two Handed Swordsman");
				Units_Class_ComboBox[loop]->Append("46 - Pikeman");
				Units_Class_ComboBox[loop]->Append("47 - Scout Cavalry");
				Units_Class_ComboBox[loop]->Append("48 - Ore Mine");
				Units_Class_ComboBox[loop]->Append("49 - Farm");// farm-food // farm-class
				Units_Class_ComboBox[loop]->Append("50 - Spearman");
				Units_Class_ComboBox[loop]->Append("51 - Packed Siege Unit");// packed-trebuchet-class
				Units_Class_ComboBox[loop]->Append("52 - Tower");// tower-class
				Units_Class_ComboBox[loop]->Append("53 - Boarding Boat");
				Units_Class_ComboBox[loop]->Append("54 - Unpacked Siege Unit");// unpacked-trebuchet-class
				Units_Class_ComboBox[loop]->Append("55 - Scorpion");// scorpion-class
				Units_Class_ComboBox[loop]->Append("56 - Raider");
				Units_Class_ComboBox[loop]->Append("57 - Cavalry Raider");
				Units_Class_ComboBox[loop]->Append("58 - Livestock");// sheep-food // livestock-class
				Units_Class_ComboBox[loop]->Append("59 - King");// king-class
				Units_Class_ComboBox[loop]->Append("60 - Unused");
				Units_Class_ComboBox[loop]->Append("61 - Horse");
			}
			else
			{
				Units_Class_ComboBox[loop]->Append("0 - Unused");	// Selection 1
				Units_Class_ComboBox[loop]->Append("1 - Nerf/Bantha");
				Units_Class_ComboBox[loop]->Append("2 - Fambaa");
				Units_Class_ComboBox[loop]->Append("3 - Unused");
				Units_Class_ComboBox[loop]->Append("4 - Wild Animal");
				Units_Class_ComboBox[loop]->Append("5 - Monster/Trouble");
				Units_Class_ComboBox[loop]->Append("6 - Wall");
				Units_Class_ComboBox[loop]->Append("7 - Farm");
				Units_Class_ComboBox[loop]->Append("8 - Gate");
				Units_Class_ComboBox[loop]->Append("9 - Fortress/A-A Turret");
				Units_Class_ComboBox[loop]->Append("10 - Turret");
				Units_Class_ComboBox[loop]->Append("11 - Cruiser");
				Units_Class_ComboBox[loop]->Append("12 - Unused");
				Units_Class_ComboBox[loop]->Append("13 - Destroyer");
				Units_Class_ComboBox[loop]->Append("14 - Utility Trawler");
				Units_Class_ComboBox[loop]->Append("15 - Frigate 1");
				Units_Class_ComboBox[loop]->Append("16 - A-A Destroyer 1");
				Units_Class_ComboBox[loop]->Append("17 - Transport Ship");
				Units_Class_ComboBox[loop]->Append("18 - Building");
				Units_Class_ComboBox[loop]->Append("19 - Doppleganger");
				Units_Class_ComboBox[loop]->Append("20 - Other/Dead/Projectile");
				Units_Class_ComboBox[loop]->Append("21 - Command Base");
				Units_Class_ComboBox[loop]->Append("22 - Cliff");
				Units_Class_ComboBox[loop]->Append("23 - Fish");
				Units_Class_ComboBox[loop]->Append("24 - Unused");
				Units_Class_ComboBox[loop]->Append("25 - Shore Fish");
				Units_Class_ComboBox[loop]->Append("26 - Game Engine Stuff");
				Units_Class_ComboBox[loop]->Append("27 - Fruit Bush");
				Units_Class_ComboBox[loop]->Append("28 - Holocron");
				Units_Class_ComboBox[loop]->Append("29 - Nova");
				Units_Class_ComboBox[loop]->Append("30 - Ore");
				Units_Class_ComboBox[loop]->Append("31 - Tree/Carbon");
				Units_Class_ComboBox[loop]->Append("32 - Artillery");
				Units_Class_ComboBox[loop]->Append("33 - A-A Mobile");
				Units_Class_ComboBox[loop]->Append("34 - Undeployed Cannon");
				Units_Class_ComboBox[loop]->Append("35 - Pummel");
				Units_Class_ComboBox[loop]->Append("36 - Cannon");
				Units_Class_ComboBox[loop]->Append("37 - Unused");
				Units_Class_ComboBox[loop]->Append("38 - Unused");
				Units_Class_ComboBox[loop]->Append("39 - Frigate 2");
				Units_Class_ComboBox[loop]->Append("40 - A-A Destroyer 2");
				Units_Class_ComboBox[loop]->Append("41 - Unused");
				Units_Class_ComboBox[loop]->Append("42 - Bridge/Eye Candy");
				Units_Class_ComboBox[loop]->Append("43 - Bomber");
				Units_Class_ComboBox[loop]->Append("44 - Bounty Hunter");
				Units_Class_ComboBox[loop]->Append("45 - Cargo Trader");
				Units_Class_ComboBox[loop]->Append("46 - Mixed 1");
				Units_Class_ComboBox[loop]->Append("47 - Scout");
				Units_Class_ComboBox[loop]->Append("48 - Fighter");
				Units_Class_ComboBox[loop]->Append("49 - Grenade Trooper");
				Units_Class_ComboBox[loop]->Append("50 - Jedi");
				Units_Class_ComboBox[loop]->Append("51 - Jedi with Holocron");
				Units_Class_ComboBox[loop]->Append("52 - Trooper");
				Units_Class_ComboBox[loop]->Append("53 - War Machine");
				Units_Class_ComboBox[loop]->Append("54 - Medic");
				Units_Class_ComboBox[loop]->Append("55 - A-A Trooper");
				Units_Class_ComboBox[loop]->Append("56 - Mounted Trooper");
				Units_Class_ComboBox[loop]->Append("57 - Fambaa Shield Generator");
				Units_Class_ComboBox[loop]->Append("58 - Workers");
				Units_Class_ComboBox[loop]->Append("59 - Air Transport");
				Units_Class_ComboBox[loop]->Append("60 - Horse-like Animal");
				Units_Class_ComboBox[loop]->Append("61 - Power Droid");
				Units_Class_ComboBox[loop]->Append("62 - Air Cruiser");
				Units_Class_ComboBox[loop]->Append("63 - Geonosian Warrior");
				Units_Class_ComboBox[loop]->Append("64 - Jedi Starfighter");
			}
			Units_Class_ComboBox[loop]->SetSelection(0);

			Attacks_Class_ComboBox[loop]->Clear();
			Attacks_Class_ComboBox[loop]->Append("Unused Type/No Type");	// Selection 0
			if(GenieVersion < genie::GV_AoKA) // AoE and RoR
			{	// Use "atc -1|arc -1|disa" to discover these!
				for(size_t loop2 = 0; loop2 < AoE1Count; ++loop2)
				Attacks_Class_ComboBox[loop]->Append(AoE1Armors[loop2]);
			}
			else if(GenieVersion < genie::GV_SWGB) // AoK and TC
			{
				for(size_t loop2 = 0; loop2 < AoE2Count; ++loop2)
				Attacks_Class_ComboBox[loop]->Append(AoE2Armors[loop2]);
			}
			else // SWGB and CC
			{
				for(size_t loop2 = 0; loop2 < SWGBCount; ++loop2)
				Attacks_Class_ComboBox[loop]->Append(SWGBArmors[loop2]);
			}
			Attacks_Class_ComboBox[loop]->SetSelection(0);
		}

		for(size_t loop = 0; loop < 2; ++loop)
		{
			Units_SearchFilters[loop]->Clear();
			Units_SearchFilters[loop]->Append("*Choose*");
			Units_SearchFilters[loop]->Append(Type20);
			Units_SearchFilters[loop]->Append(Type30);
			Units_SearchFilters[loop]->Append(Type40);
			Units_SearchFilters[loop]->Append(Type50);
			Units_SearchFilters[loop]->Append(Type60);
			Units_SearchFilters[loop]->Append(Type70);
			Units_SearchFilters[loop]->Append(Type80);
			Units_SearchFilters[loop]->SetSelection(0);

			Research_SearchFilters[loop]->Clear();
			Research_SearchFilters[loop]->Append("Lang File Name");	// 0
			Research_SearchFilters[loop]->Append("Internal Name");
			Research_SearchFilters[loop]->Append("Required Researches");
			Research_SearchFilters[loop]->Append("Min. Req. Researches");
			Research_SearchFilters[loop]->Append("Research Location");
			Research_SearchFilters[loop]->Append("Research Time");
			Research_SearchFilters[loop]->Append("Technology");
			Research_SearchFilters[loop]->Append("Type");
			Research_SearchFilters[loop]->Append("Icon");
			Research_SearchFilters[loop]->Append("Button");
			Research_SearchFilters[loop]->Append("Lang File Pointer 1");
			Research_SearchFilters[loop]->Append("Lang File Pointer 2");
			Research_SearchFilters[loop]->Append("Pointer 3");
			Research_SearchFilters[loop]->Append("Cost Types");
			Research_SearchFilters[loop]->Append("Cost Amounts");
			Research_SearchFilters[loop]->Append("Cost Uses");
			if(GenieVersion >= genie::GV_AoK)
			{
				Research_SearchFilters[loop]->Append("Civilization");
				Research_SearchFilters[loop]->Append("Full Tech Mode");
				if(GenieVersion >= genie::GV_SWGB)
				Research_SearchFilters[loop]->Append("Internal Name 2");
			}
			Research_SearchFilters[loop]->SetSelection(0);

			Sounds_Items_SearchFilters[loop]->Clear();
			Sounds_Items_SearchFilters[loop]->Append("Filename");	// 0
			Sounds_Items_SearchFilters[loop]->Append("DRS");
			Sounds_Items_SearchFilters[loop]->Append("Probability");
			if(GenieVersion >= genie::GV_AoKA)
			{
				Sounds_Items_SearchFilters[loop]->Append("Civilization");
				Sounds_Items_SearchFilters[loop]->Append("Unknown");
			}
			Sounds_Items_SearchFilters[loop]->SetSelection(0);
		}

		SetStatusText(lexical_cast<string>(dataset->FileVersion), 4);

		Effects_AttributesC_ComboBox->Clear();
		Effects_AttributesC_ComboBox->Append("No Attribute/Invalid Attribute");		// Selection 0
		Effects_AttributesC_ComboBox->Append("0 - Hit Points");		// Selection 1
		Effects_AttributesC_ComboBox->Append("1 - Line of Sight");
		Effects_AttributesC_ComboBox->Append("2 - Garrison Capacity");
		Effects_AttributesC_ComboBox->Append("3 - Unit Size X");
		Effects_AttributesC_ComboBox->Append("4 - Unit Size Y");
		Effects_AttributesC_ComboBox->Append("5 - Movement Speed (types 20-80)");
		Effects_AttributesC_ComboBox->Append("6 - Rotation Speed (types 30-80)");
		Effects_AttributesC_ComboBox->Append("7 - Unknown?");
		if(GenieVersion < genie::GV_AoKA)
		{
			Effects_AttributesC_ComboBox->Append("8 - Armor (no multiply, types 50-80)");
			Effects_AttributesC_ComboBox->Append("9 - Attack (no multiply, types 50-80)");
		}
		else
		{
			Effects_AttributesC_ComboBox->Append("8 - Armor (types 50-80)");
			Effects_AttributesC_ComboBox->Append("9 - Attack (types 50-80)");
		}
		Effects_AttributesC_ComboBox->Append("10 - Attack Reloading Time (types 50-80)");
		Effects_AttributesC_ComboBox->Append("11 - Accuracy Percent (types 50-80)");
		Effects_AttributesC_ComboBox->Append("12 - Max Range (types 50-80)");
		Effects_AttributesC_ComboBox->Append("13 - Working Rate (types 30-80)");
		Effects_AttributesC_ComboBox->Append("14 - Resource Carriage");
		Effects_AttributesC_ComboBox->Append("15 - Default Armor (types 50-80)");
		Effects_AttributesC_ComboBox->Append("16 - Projectile Unit (types 50-80)");
		Effects_AttributesC_ComboBox->Append("17 - Icon/Graphics Angle (type 80)");
		Effects_AttributesC_ComboBox->Append("18 - Ter restr to multiply dmg rcvd (always sets, types 50-80)");
		if(GenieVersion < genie::GV_AoEB)
        {
            Effects_AttributesC_ComboBox->Append("19 - Unused");
        }
        else
        {
            Effects_AttributesC_ComboBox->Append("19 - Enable Intelligent Projectiles (type 60)");
        }
		if(GenieVersion < genie::GV_AoKA)
		{
			Effects_AttributesC_ComboBox->Append("20 - Unused");
			Effects_AttributesC_ComboBox->Append("21 - Unused");
			Effects_AttributesC_ComboBox->Append("22 - Unused");
			Effects_AttributesC_ComboBox->Append("23 - Unused");
			Effects_AttributesC_ComboBox->Append("100 - Resource Costs (types 70-80)");
            if(GenieVersion == genie::GV_RoR)
			Effects_AttributesC_ComboBox->Append("101 - Amount of 1st resource storage (set only)");
		}
		else
		{
			Effects_AttributesC_ComboBox->Append("20 - Min Range (types 50-80)");
			Effects_AttributesC_ComboBox->Append("21 - Amount of 1st resource storage");
			Effects_AttributesC_ComboBox->Append("22 - Blast Width (types 50-80)");
			Effects_AttributesC_ComboBox->Append("23 - Search Radius (types 40-80)");
			Effects_AttributesC_ComboBox->Append("100 - Resource Costs (types 70-80)");
			Effects_AttributesC_ComboBox->Append("101 - Train Time (types 70-80)");
			Effects_AttributesC_ComboBox->Append("102 - Total Missiles (types 70-80)");
			Effects_AttributesC_ComboBox->Append("103 - Food Costs (types 70-80)");
			if(GenieVersion < genie::GV_SWGB)
			{
				Effects_AttributesC_ComboBox->Append("104 - Wood Costs (types 70-80)");
				Effects_AttributesC_ComboBox->Append("105 - Gold Costs (types 70-80)");
				Effects_AttributesC_ComboBox->Append("106 - Stone Costs (types 70-80)");
			}
			else
			{
				Effects_AttributesC_ComboBox->Append("104 - Carbon Costs (types 70-80)");
				Effects_AttributesC_ComboBox->Append("105 - Nova Costs (types 70-80)");
				Effects_AttributesC_ComboBox->Append("106 - Ore Costs (types 70-80)");
			}
			Effects_AttributesC_ComboBox->Append("107 - Max Total Missiles (types 70-80)");
            if(GenieVersion >= genie::GV_AoKB)
			Effects_AttributesC_ComboBox->Append("108 - Garrison Heal Rate (type 80)");
            if(GenieVersion == genie::GV_Cysion)
            Effects_AttributesC_ComboBox->Append("109 - Regeneration Rate (types 40-80)");
		}
		Effects_AttributesC_ComboBox->SetSelection(0);

		Units_GraphicSet->Clear();
		if(GenieVersion < genie::GV_AoKA)
		{
			// AoE
			Units_GraphicSet->Append("0 West Middle Easterns");
			Units_GraphicSet->Append("1 Greeks");
			Units_GraphicSet->Append("2 East Middle Easterns");
			Units_GraphicSet->Append("3 Asians");
			// + RoR
			Units_GraphicSet->Append("4 Romans");
			Units_GraphicSet->Append("5 Unused");
			Units_GraphicSet->Append("6 Unused");
			Units_GraphicSet->Append("7 Unused");
			Units_GraphicSet->Append("8 Unused");
		}
		else if(GenieVersion < genie::GV_SWGB)
		{
			Units_GraphicSet->Append("0 Unused");
			// AoK
			Units_GraphicSet->Append("1 East Europeans");
			Units_GraphicSet->Append("2 West Europeans");
			Units_GraphicSet->Append("3 Asians");
			Units_GraphicSet->Append("4 Arabs");
			// + TC
			Units_GraphicSet->Append("5 Americans");
			Units_GraphicSet->Append("6 Unused");
			Units_GraphicSet->Append("7 Unused");
			Units_GraphicSet->Append("8 Unused");
		}
		else
		{
			// SWGB
			Units_GraphicSet->Append("0 Unused");
			Units_GraphicSet->Append("1 Galactic Empire");
			Units_GraphicSet->Append("2 Gungans");
			Units_GraphicSet->Append("3 Rebels");
			Units_GraphicSet->Append("4 Royal Naboo");
			Units_GraphicSet->Append("5 Trade Federation");
			Units_GraphicSet->Append("6 Wookiees");
			Units_GraphicSet->Append("7 Republic");
			Units_GraphicSet->Append("8 Confederacy");
		}
		Units_GraphicSet->Append("9 Ask Tapsa for more!");
		Units_GraphicSet->SetSelection(0);

        Effects_Type_ComboBox->Clear();
        Effects_Type_ComboBox->Append("No Type/Invalid Type");	// Selection 0
        Effects_Type_ComboBox->Append("0 - Attribute Modifier (Set)");	// Selection 1
        Effects_Type_ComboBox->Append("1 - Resource Modifier (Set/+/-)");
        Effects_Type_ComboBox->Append("2 - Enable/Disable Unit");
        Effects_Type_ComboBox->Append("3 - Upgrade Unit");
        Effects_Type_ComboBox->Append("4 - Attribute Modifier (+/-)");
        Effects_Type_ComboBox->Append("5 - Attribute Modifier (Multiply)");
        Effects_Type_ComboBox->Append("6 - Resource Modifier (Multiply)");
        if(GenieVersion == genie::GV_Cysion)
        {
            Effects_Type_ComboBox->Append("10 - Team Attribute Modifier (Set)");	// Selection 8
            Effects_Type_ComboBox->Append("11 - Team Resource Modifier (Set/+/-)");
            Effects_Type_ComboBox->Append("12 - Team Enable/Disable Unit");
            Effects_Type_ComboBox->Append("13 - Team Upgrade Unit");
            Effects_Type_ComboBox->Append("14 - Team Attribute Modifier (+/-)");
            Effects_Type_ComboBox->Append("15 - Team Attribute Modifier (Multiply)");
            Effects_Type_ComboBox->Append("16 - Team Resource Modifier (Multiply)");
        }
        else
        {
            for(size_t loop = 10; loop < 17; ++loop)
            Effects_Type_ComboBox->Append(lexical_cast<string>(loop) + " - AoK HD only");
        }
        if(GenieVersion < genie::GV_AoKA) Effects_Type_ComboBox->Append("101 - AoK+ only");
        else Effects_Type_ComboBox->Append("101 - Research Cost Modifier (Set/+/-)");
        Effects_Type_ComboBox->Append("102 - Disable Research");
        if(GenieVersion < genie::GV_AoKA) Effects_Type_ComboBox->Append("103 - AoK+ only");
        else Effects_Type_ComboBox->Append("103 - Research Time Modifier (Set/+/-)");	// Selection 17
        Effects_Type_ComboBox->SetSelection(0);

		DataOpened = true;
		OnGameVersionChange();
		LoadLists();
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
		UnitLines_UnitLines_ListV->DeleteAllItems();
		UnitLines_UnitLineUnits_ListV->DeleteAllItems();
	}
	//InitCivs(true);
	InitUnits(GenieVersion < genie::GV_AoKA, true);
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
		TechTrees_MainList_Ages_ListV->DeleteAllItems();
		TechTrees_Ages_Buildings.List->DeleteAllItems();
		TechTrees_Ages_Units.List->DeleteAllItems();
		TechTrees_Ages_Researches.List->DeleteAllItems();
		TechTrees_MainList_Buildings_ListV->DeleteAllItems();
		TechTrees_Buildings_Buildings.List->DeleteAllItems();
		TechTrees_Buildings_Units.List->DeleteAllItems();
		TechTrees_Buildings_Researches.List->DeleteAllItems();
		TechTrees_MainList_Units_ListV->DeleteAllItems();
		TechTrees_Units_Units.List->DeleteAllItems();
		TechTrees_MainList_Researches_ListV->DeleteAllItems();
		TechTrees_Researches_Buildings.List->DeleteAllItems();
		TechTrees_Researches_Units.List->DeleteAllItems();
		TechTrees_Researches_Researches.List->DeleteAllItems();
	}

    wxTimerEvent E;
	OnCivsTimer(E);
	OnUnitsTimer(E);
	OnResearchTimer(E);
	OnTechTimer(E);
	OnGraphicsTimer(E);
	OnSoundsTimer(E);
	OnTerrainsTimer(E);
	OnTerrainRestrictionsTerrainTimer(E);
	OnPlayerColorsTimer(E);
	OnTerrainBordersTimer(E);
	OnRandomMapTimer(E);
	if(GenieVersion >= genie::GV_AoKA)
	{
		OnTTAgesTimer(E);
		OnTTBuildingTimer(E);
		OnTTUnitTimer(E);
		OnTTResearchTimer(E);
		if(GenieVersion >= genie::GV_SWGB)
		OnUnitLinesTimer(E);
	}
}

void AGE_Frame::OnGameVersionChange()
{
	if(DataOpened)	// Hiding stuff according to game version should be here.
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

		bool show;

		// Test ->
		show = (GenieVersion >= genie::GV_TEST) ? true : false;
		Sounds_Unknown2_Holder->Show(show);
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
		Units_Unselectable_Holder->Show(show);
		Units_SelectionEffect_Holder->Show(show);
		Units_EditorSelectionColour_Holder->Show(show);
		Units_SelectionRadius_Holder->Show(show);
		Units_HPBarHeight2_Holder->Show(show);
		Units_MoveSound_Holder->Show(show);
		Units_DisplayedPierceArmour_Holder->Show(show);
		Units_DisplayedMeleeArmour_Holder->Show(show);
		Units_DisplayedAttack_Holder->Show(show);
		Units_DisplayedRange_Holder->Show(show);
		Units_ReloadTime2_Holder->Show(show);
		if(!show || ShowUnknowns)
		{
			Units_Unknown6_Holder->Show(show);
			Units_Unknown7_Holder->Show(show);
			Units_Unknown8_Holder->Show(show);
		}

		// AoE ->
		show = (GenieVersion >= genie::GV_AoE) ? true : false;
		Units_ID2_Holder->Show(show);
		General_Unknown2_Holder->Show(show);
		for(size_t loop = 2; loop < General_TileSizes.size(); loop += 3)
		General_TileSizes[loop]->Show(show);

		// AoK Alfa ->
		show = (GenieVersion >= genie::GV_AoKA) ? true : false;
		for(size_t loop = 4; loop < 6; ++loop)
		{
			Research_RequiredTechs[loop]->Show(show);
			Research_RequiredTechs_ComboBox[loop]->Show(show);
		}
		Units_TrainSound[1]->Show(show);
		Units_TrainSound_ComboBox[1]->Show(show);
		Units_SelectionMask_Holder->Show(show);
		Units_SelectionShapeType_Holder->Show(show);
		Units_SelectionShape_Holder->Show(show);
		Units_ID3_Holder->Show(show);
		Units_MissileCount_Holder->Show(show);
		Units_MissileDuplicationCount_Holder->Show(show);
		Units_AttackMissileDuplicationSpawning_Holder->Show(show);
		Units_AttackMissileDuplicationUnit_Holder->Show(show);
		Units_ChargingGraphic_Holder->Show(show);
		Units_ChargingMode_Holder->Show(show);
		Units_AnnexUnit1_Holder->Show(show);
		Units_AnnexUnitMisplacement1_Holder->Show(show);
		Units_HeadUnit_Holder->Show(show);
		Units_TransformUnit_Holder->Show(show);
		Units_GarrisonType_Holder->Show(show);
		Units_GarrisonHealRate_Holder->Show(show);
		Units_LootSwitch_Holder->Show(show);
		Units_UnknownSound_Holder->Show(show);
		Units_UnknownType_Holder->Show(show);
		TerRestrict_Graphics_Holder->Show(show);
		SoundItems_Civ_Holder->Show(show);
		Colors_Palette_Holder->Show(show);
		Colors_MinimapColor_Holder->Show(show);
		TechTrees_Main->Show(show);
		TabBar_Main->SetPageText(2, show ? "Tech Trees" : "AoK+ only");
		if(!show || ShowUnknowns)
		{
			Units_Type70plusUnknownArea_Holder->Show(show);
			Units_Type80plusUnknownArea_Holder->Show(show);
			Units_PileUnit_Holder->Show(show);
			SoundItems_Unknown_Holder->Show(show);
			Colors_UnknownArea_Holder->Show(show);
		}

		// AoE & RoR
		Colors_Name_Holder->Show(!show);

		if(show) // AoK Alfa ->
		{
			Colors_ID->changeContainerType(CLong);
			Colors_ColorL->changeContainerType(CLong);
			Colors_Unknown1->changeContainerType(CLong);
			Colors_Unknown2->changeContainerType(CLong);
		}
		else // <- RoR
		{
			Colors_ID->changeContainerType(CShort);
			Colors_Unknown1->changeContainerType(CShort);
			Colors_ColorL->changeContainerType(CUByte);
			Colors_Unknown2->changeContainerType(CUByte);
		}

		// AoK Beta ->
		show = (GenieVersion >= genie::GV_AoKB) ? true : false;
		Units_HeroMode_Holder->Show(show);
		Units_GarrisonGraphic_Holder->Show(show);
		Units_StandingGraphic[1]->Show(show);
		Units_StandingGraphic_ComboBox[1]->Show(show);
		Units_AccuracyDispersion_Holder->Show(show);
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
		if(!show || ShowUnknowns)
		{
			Units_RotationAngles_Holder->Show(show);
			Graphics_Unknown3_Holder->Show(show);
		}

		// AoK ->
		show = (GenieVersion >= genie::GV_AoK) ? true : false;
		Units_Exists_Holder->Show(show);
		Units_UnitCommands_Add->Enable(show);
		if(!show || ShowUnknowns)
		{
			Units_Disabled_Holder->Show(show);
		}

		// TC ->
		show = (GenieVersion >= genie::GV_TC) ? true : false;
		Units_SnowGraphicID_Holder->Show(show);
		Units_Attributes2_Grid->Show(show);

		if(show) // TC ->
		{
			Units_DefaultArmor->changeContainerType(CShort);
		}
		else // <- AoK
		{
			Units_DefaultArmor->changeContainerType(CByte);
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
		if(!show || ShowUnknowns)
		{
			Civs_SUnknown1_Holder->Show(show);
			General_Variables1_Holder->Show(show);
		}
		Terrains_Unknown1_Holder->Show(!show && ShowUnknowns);

		if(show) // SWGB ->
		{
			Graphics_Name->setMaxChars(25);
			Graphics_Name2->setMaxChars(25);
			SoundItems_Name->setMaxChars(27);
			Terrains_Name->setMaxChars(17);
			Terrains_Name2->setMaxChars(17);
			TerRestrict_Amount->changeContainerType(CFloat);
		}
		else // <- TC
		{
			Graphics_Name->setMaxChars(21);
			Graphics_Name2->setMaxChars(13);
			SoundItems_Name->setMaxChars(13);
			Terrains_Name->setMaxChars(13);
			Terrains_Name2->setMaxChars(13);
			TerRestrict_Amount->changeContainerType(CLong);
		}
	}

//	Every data area should be layouted.
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

void AGE_Frame::OnSave(wxCommandEvent &event)
{
	AGE_SaveDialog SaveBox(this);
    SaveDialog = &SaveBox;
    SaveBox.SyncWithReadPaths->Connect(SaveBox.SyncWithReadPaths->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnSyncSaveWithOpen), NULL, this);

    int RecentItems;
    {
        wxFileConfig RecentOpen("AGE", "Tapsa", "age3recents.ini", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
        RecentOpen.Read("Recent/Items", &RecentItems, 0);
        SaveBox.RecentValues.resize(RecentItems);
        for(int i=0; i < RecentItems; ++i)
        {
            SaveBox.RecentValues[i].Alloc(5);
            wxString temp, entry = "Recent" + lexical_cast<string>(i + 1);
            RecentOpen.Read(entry + "/DatVersion", &temp, "9000"); SaveBox.RecentValues[i].Add(temp);
            RecentOpen.Read(entry + "/DatPath", &temp, wxEmptyString); SaveBox.RecentValues[i].Add(temp);
            RecentOpen.Read(entry + "/Lang", &temp, wxEmptyString); SaveBox.RecentValues[i].Add(temp);
            RecentOpen.Read(entry + "/LangX1", &temp, wxEmptyString); SaveBox.RecentValues[i].Add(temp);
            RecentOpen.Read(entry + "/LangX1P1", &temp, wxEmptyString); SaveBox.RecentValues[i].Add(temp);
        }
    }
	if(SaveBox.RecentValues.size())
    for(int i=0; i < RecentItems; ++i)
	SaveBox.CheckBox_Recent->Append(SaveBox.RecentValues[i][1]);
	else
	SaveBox.CheckBox_Recent->Append("10 point hint: donate euros to me");
	SaveBox.CheckBox_Recent->SetSelection(0);

	SaveBox.Path_DatFileLocation->SetFocus();
	SaveBox.DriveLetterBox->ChangeValue(DriveLetter);
	SaveBox.CheckBox_CustomDefault->SetValue(UseCustomPath);
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
        wxCommandEvent sync(wxEVT_COMMAND_CHECKBOX_CLICKED, SaveBox.SyncWithReadPaths->GetId());
        sync.SetInt(true);
        SaveBox.SyncWithReadPaths->GetEventHandler()->ProcessEvent(sync);
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
        wxFileConfig Config("AGE", "Tapsa", "age2configw"+lexical_cast<string>(window_num + 1)+".ini", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
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
        wxFileConfig RecentSave("AGE", "Tapsa", "age3recents.ini", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
        RecentSave.Write("Recent/Items", RecentItems);
        for(int i=0; i < RecentItems; ++i)
        {
            wxString entry = "Recent" + lexical_cast<string>(i + 1);
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
		catch(std::ios_base::failure e)
		{
			wxMessageBox("Unable to save the file!");
			return;
		}
	}
	/*if(SaveApf)
	{
		//	 Not Implemented Yet = Nothing Happens
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
    catch(std::ios_base::failure e)
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
    catch(std::ios_base::failure e)
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
    catch(std::ios_base::failure e)
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

			Units_UnknownArea_Holder->Show(ShowUnknowns);
			Units_CommandHolder_Grid3->Show(ShowUnknowns);
			Graphics_3_Grid->Show(ShowUnknowns);
			Graphics_Deltas_Grid_Data2->Show(ShowUnknowns);
			Sounds_Unknown1_Holder->Show(ShowUnknowns);
			Sounds_Unknown2_Holder->Show(ShowUnknowns);
			SoundItems_Unknown_Holder->Show(ShowUnknowns);
			Colors_UnknownArea_Holder->Show(ShowUnknowns);
			General_TopRow->Show(ShowUnknowns);

			OnGameVersionChange(); // Does layouting and refreshing and ... check it out.
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
			TipText.Append("You can have multiple search entries separated with \"|\" letter.\n");
			TipText.Append("Upper search boxes are inclusive and lower ones exclusive.\n");
			TipText.Append("Example: \"tower|ship|ram\"\n");
			TipText.Append("You can switch from \"or\" finding to \"and\" finding with check boxes.\n");
			TipText.Append("Meaning that every search entry has to match.\n");
			wxMessageBox(TipText, "Tips");
            break;
		}
		case eAbout:
		{
			AGE_AboutDialog AGEAbout(this);
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
                parentPos.x += 1000;
                slp_window = new wxFrame(this, wxID_ANY, "SLP", parentPos, wxSize(512, 600), StayOnTopSLP ? (wxSTAY_ON_TOP | wxDEFAULT_FRAME_STYLE) : wxDEFAULT_FRAME_STYLE);
                slp_window->SetIcon(wxIcon(Tree32_xpm));
                wxPanel *panel = new wxPanel(slp_window);
                slp_view = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE);
                slp_next = new wxButton(panel, eNextFrame, "Show -> frame");
                slp_prev = new wxButton(panel, ePrevFrame, "Show <- frame");
                slp_first = new wxButton(panel, eFirstFrame, "Show first frame");
                wxColour back(SLPbackR, SLPbackG, SLPbackB);
                slp_background = new wxColourPickerCtrl(panel, ePickBgColor, back, wxDefaultPosition, wxDefaultSize, wxCLRP_SHOW_LABEL);
                slp_frame_export = new wxButton(panel, eExportFrame, "Export frame to PNGs");
                slp_frame_import = new wxButton(panel, eImportFrame, "Import PNGs to frame");
                slp_save = new wxButton(panel, eSaveSLP, "Save SLP");
                slp_tool = new wxButton(panel, eSLPTool, "SLP Tool");
                slp_merge_shadow = new wxButton(panel, eSLPMergeShadow, "Merge shadow from 2 to 1");
                slp_tool_layout = new wxFlexGridSizer(2, 2, 2);
                wxStaticText *text_source1 = new wxStaticText(panel, wxID_ANY, " Source SLP 1");
                wxStaticText *text_source2 = new wxStaticText(panel, wxID_ANY, " Source SLP 2");
                wxStaticText *text_target1 = new wxStaticText(panel, wxID_ANY, " Target SLP");
                slp_source1 = new wxFilePickerCtrl(panel, wxID_ANY, "", "Select a file", "SLP|*.slp", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
                slp_source2 = new wxFilePickerCtrl(panel, wxID_ANY, "", "Select a file", "SLP|*.slp", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_USE_TEXTCTRL | wxFLP_FILE_MUST_EXIST);
                slp_target1 = new wxFilePickerCtrl(panel, wxID_ANY, "", "Select a file", "SLP|*.slp", wxDefaultPosition, wxDefaultSize, wxFLP_SAVE | wxFLP_USE_TEXTCTRL | wxFLP_OVERWRITE_PROMPT);
                slp_hotspot = new wxCheckBox(panel, eShowHotspot, "Hotspot");
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
                slp_angles = new wxCheckBox(panel, wxID_ANY, "Rotate angles *");
                slp_angles->SetValue(true);
                slp_collision = new wxCheckBox(panel, eCollisionShape, "Collision Shape");
                slp_collision->SetValue(DrawCollisionShape);
                slp_clearance = new wxCheckBox(panel, eClearanceShape, "Clearance Shape");
                slp_clearance->SetValue(DrawClearanceShape);
                slp_selection = new wxCheckBox(panel, eSelectionShape, "Selection Shape");
                slp_selection->SetValue(DrawSelectionShape);
                slp_angles->SetToolTip("Right click image to manually set angle\nNo east side support yet");
                slp_sizer = new wxBoxSizer(wxVERTICAL);
                wxSizer *sizer2 = new wxBoxSizer(wxHORIZONTAL);
                wxSizer *sizer3 = new wxBoxSizer(wxHORIZONTAL);
                wxSizer *sizer4 = new wxBoxSizer(wxHORIZONTAL);
                wxSizer *sizer5 = new wxBoxSizer(wxHORIZONTAL);

                slp_sizer->Add(slp_view, 1, wxEXPAND);
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

                slp_view->Connect(slp_view->GetId(), wxEVT_PAINT, wxPaintEventHandler(AGE_Frame::OnDrawGraphicSLP), NULL, this);
                slp_view->Connect(slp_view->GetId(), wxEVT_ERASE_BACKGROUND, wxEraseEventHandler(AGE_Frame::OnGraphicErase), NULL, this);
                slp_view->Connect(slp_view->GetId(), wxEVT_RIGHT_DOWN, wxMouseEventHandler(AGE_Frame::OnFrameMouse), NULL, this);
                slp_view->Connect(slp_view->GetId(), wxEVT_CHAR, wxKeyEventHandler(AGE_Frame::OnFrameKey), NULL, this);
                slp_window->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(AGE_Frame::OnExitSLP), NULL, this);
                slp_first->Connect(eFirstFrame, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnFrameButton), NULL, this);
                slp_next->Connect(eNextFrame, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnFrameButton), NULL, this);
                slp_prev->Connect(ePrevFrame, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnFrameButton), NULL, this);
                slp_frame_export->Connect(eExportFrame, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnFrameButton), NULL, this);
                slp_frame_import->Connect(eImportFrame, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnFrameButton), NULL, this);
                slp_save->Connect(eSaveSLP, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnFrameButton), NULL, this);
                slp_tool->Connect(eSLPTool, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnFrameButton), NULL, this);
                slp_merge_shadow->Connect(eSLPMergeShadow, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnFrameButton), NULL, this);
                slp_hotspot->Connect(eShowHotspot, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnFrameButton), NULL, this);
                slp_animate->Connect(eAnimSLP, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnFrameButton), NULL, this);
                slp_shadow->Connect(eShowShadows, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnFrameButton), NULL, this);
                slp_outline->Connect(eShowOutline, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnFrameButton), NULL, this);
                slp_delta->Connect(eShowDeltas, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnFrameButton), NULL, this);
                slp_stack->Connect(eShowStack, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnFrameButton), NULL, this);
                slp_annex->Connect(eShowAnnexes, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnFrameButton), NULL, this);
                slp_terrain->Connect(eShowTerrain, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnFrameButton), NULL, this);
                slp_collision->Connect(eCollisionShape, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnFrameButton), NULL, this);
                slp_clearance->Connect(eClearanceShape, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnFrameButton), NULL, this);
                slp_selection->Connect(eSelectionShape, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnFrameButton), NULL, this);
                slp_background->Connect(ePickBgColor, wxEVT_COMMAND_COLOURPICKER_CHANGED, wxCommandEventHandler(AGE_Frame::OnFrameButton), NULL, this);
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
		/*case eIdFix:
		{
			EnableIDFix = event.IsChecked();
			wxMessageBox("Please restart this program.\nI do not recommend disabling index fixes!");
            break;
		}*/
		case eDRS:
        {
            if(event.IsChecked())
            {
                if(!UseTXT)
                {
                    GetToolBar()->SetToolNormalBitmap(eDRS, wxBitmap(DRS_lock_xpm));
                    // Reload DRS files.
                    wxArrayString FilesToRead;
                    if(GenieVersion == genie::GV_TC)
                    {
                        FilesToRead.Add("\\gamedata_x1_p1.drs");
                        FilesToRead.Add("\\gamedata_x1.drs");
                        FilesToRead.Add("\\sounds_x1.drs");
                    }
                    else if(GenieVersion == genie::GV_CC)
                    {
                        if(GameVersion == EV_EF)
                        {
                            FilesToRead.Add("\\gamedata_x2.drs");
                            FilesToRead.Add("\\interfac_x2.drs");
                            FilesToRead.Add("\\graphics_x2.drs");
                            FilesToRead.Add("\\terrain_x2.drs");
                            FilesToRead.Add("\\sounds_x2.drs");
                        }
                        FilesToRead.Add("\\gamedata_x1.drs");
                        FilesToRead.Add("\\interfac_x1.drs");
                        FilesToRead.Add("\\graphics_x1.drs");
                        FilesToRead.Add("\\terrain_x1.drs");
                        FilesToRead.Add("\\sounds_x1.drs");
                    }
                    else if(GenieVersion == genie::GV_RoR)
                    {
                        FilesToRead.Add("2\\interfac.drs");
                        FilesToRead.Add("2\\graphics.drs");
                        FilesToRead.Add("2\\sounds.drs");
                    }
                    if(GenieVersion > genie::GV_RoR)
                    {
                        FilesToRead.Add("\\gamedata.drs");
                    }
                    FilesToRead.Add("\\interfac.drs");
                    FilesToRead.Add("\\graphics.drs");
                    FilesToRead.Add("\\terrain.drs");
                    FilesToRead.Add("\\sounds.drs");
                    if(GenieVersion < genie::GV_AoKB)
                    {
                        FilesToRead.Add("\\border.drs");
                    }

                    if(UseExtra)
                    {
                        genie::DrsFile *topDRS = new genie::DrsFile();
                        try
                        {
                            topDRS->setGameVersion(GenieVersion);
                            topDRS->load(Path1stDRS.c_str());
                            datafiles.push_back(topDRS);
                        }
                        catch(std::ios_base::failure e)
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
                            palettes.push_back(pal.get()->getColors());
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
            graphicAnimTimer.Stop();
            if(!UseTXT)
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
            if(UseTXT)
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
                                catch(out_of_range){}
                                if(frame)
                                {
                                    uint64_t palData = frame.get()->getProperties();
                                    palData <<= 32;
                                    palData += frame.get()->getPaletteOffset();
                                    slpPaletteCombinations.insert(make_pair(res, palData));
                                    ++frames;
                                }
                            }
                        }
                        catch(std::ios_base::failure e){}
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
                os << hex << setw(16) << setfill('0') << uppercase << palData.first;
                os << ' ' << palData.second;
                log_out << buffer.str() << endl;
            }*/
			help.Append("Click \"Help\" from the toolbar to see this again.\n\n");
			help.Append("Here are examples which cover all the nice features.\n");
			help.Append("(This is assuming that you edit Age of Empires II: The Conquerors)\n\n");
			help.Append("Advanced Searching\n\n");
			help.Append("Let's suppose that you want to edit buildings (type 80) of class 3,\n");
			help.Append("but not camps nor houses or yurts.\n");
			help.Append("See the two combo boxes having \"Lang File Name\" selected by default?\n");
			help.Append("Select \"Type\" to the upper one and \"Class\" to the lower one.\n");
			help.Append("Then put \"t 80|c 3,\" to the upper search box\n");
			help.Append("and \"camp|house|yurt\" to the lower (exclusive) search box.\n");
			help.Append("Select the upper \"And\" check box to make sure that the search returns\n");
			help.Append("only units to which ALL search terms in the upper search box match.\n\n");
			help.Append("Batch Processing\n\n");
			help.Append("Let's suppose that you want to multiply the garrison heal rate\n");
			help.Append("of all selected units (buildings) by 1.3.\n");
			help.Append("Simply select all the desired units and put into garrison heal rate box \"b*1.3\", ");
			help.Append("or just put the absolute value you want for all selected units.\n");
			help.Append("The other batch modifiers are b+, b- and b/.\n");
			help.Append("Note that overflows are not checked!\n\n");
			help.Append("Cross Copy Between Files\n\n");
			help.Append("Let's suppose that you want to copy all ships to another dat file.\n");
			help.Append("From the toolbar, click +++ to open another window.\n");
			help.Append("Now that you have a second window titled \"AGE window 2\" open with a dat file, ");
			help.Append("let's begin the copying.\n");
			help.Append("(You can copy to another game version if you dare.)\n");
			help.Append("On the first window, select all the ships (search for \"ship\").\n");
			help.Append("Then click copy and go to the second window.\n");
			help.Append("Then click paste or paste insert wherever you want the ships.\n");
			help.Append("That's it.");
			wxMessageBox(help, "Short Guide to Advanced Editing");
            break;
		}
		case eHex:
		{
			popUp.hexMode = event.IsChecked();
			LoadLists();
            break;
		}
		case eFloat:
		{
			popUp.accurateFloats = event.IsChecked();
			LoadLists();
            break;
		}
		case ePaste:
		{
			Paste11 = event.IsChecked();
            break;
		}
		case eAddWindow:
        {
            for(size_t win = 0; win < 4; ++win)
            if(!AGE_Frame::openEditors[win])
            {
                AGE_Frame* newWindow = new AGE_Frame("AGE " + AGE_AboutDialog::AGE_VER + " window "+lexical_cast<string>(win+1), win);
                FixSize(newWindow);
                wxCommandEvent OpenFiles(wxEVT_COMMAND_MENU_SELECTED, newWindow->eOpen);
                newWindow->GetEventHandler()->ProcessEvent(OpenFiles);
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
			StayOnTopSLP = event.IsChecked();
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
                AGE_Frame::openEditors[win]->GetEventHandler()->ProcessEvent(ce);
            }
            ProcessEvent(ce);
            break;
        }
        default: wxMessageBox(lexical_cast<string>(event.GetId()), "wxEvent error!");
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

void AGE_Frame::loadPalette(const wxString &folder)
{
    if(folder.empty()) return;
    if(!wxDir::Exists(folder)) return;
    try
    {
        genie::PalFile pal;
        wxString name = folder + "\\interface\\50500.bina";
        pal.load(name.c_str());
        palettes.push_back(pal.getColors());
    }
    catch(std::ios_base::failure e){}
}

void AGE_Frame::addFilesToRead(const wxArrayString &files, const wxString &folder)
{
    if(folder.empty() || !wxDir::Exists(folder)) return;
    for(int i=0; i < files.size(); ++i)
    {
        genie::DrsFile *interfac = new genie::DrsFile();
        wxString location = folder + files[i];
        try
        {
            interfac->setGameVersion(GenieVersion);
            interfac->load(location.c_str());
            datafiles.push_back(interfac);
        }
        catch(std::ios_base::failure e)
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

void AGE_Frame::SLPtoBitMap(AGE_SLP *graphic)
{
    if(graphic->slpID == graphic->lastSlpID)
    {
        LoadSLPFrame(graphic);
        return;
    }
    graphic->lastSlpID = graphic->slpID;
    if(UseTXT)
    {
        wxArrayString folders;
        if(UseMod) addSLPFolders4SLPs(folders, FolderDRS2);
        addSLPFolders4SLPs(folders, FolderDRS);
        for(int i=0; i < folders.size(); ++i)
        {
            if(!graphic->filename.empty())
            try
            {
                graphic->slp.reset(new genie::SlpFile());
                wxString name = folders[i] + graphic->filename + ".slp";
                //log_out << name << endl;
                graphic->slp.get()->load(name.c_str());
                graphic->slp.get()->freelock();
                LoadSLPFrame(graphic);
                return;
            }
            catch(std::ios_base::failure e){}
        }
        folders.clear();
        if(UseMod) addDRSFolders4SLPs(folders, FolderDRS2);
        addDRSFolders4SLPs(folders, FolderDRS);
        for(int i=0; i < folders.size(); ++i)
        {
            // HD uses slp ID instead
            try
            {
                graphic->slp.reset(new genie::SlpFile());
                wxString name = folders[i] + lexical_cast<string>(graphic->slpID) + ".slp";
                //log_out << name << endl;
                graphic->slp.get()->load(name.c_str());
                graphic->slp.get()->freelock();
                LoadSLPFrame(graphic);
                return;
            }
            catch(std::ios_base::failure e){}
        }
    }
    else
    {
        for(auto &file: datafiles)
        {
            graphic->slp = file->getSlpFile(graphic->slpID);
            //log_out << file->getFileName() << " : " << slpID << endl;
            if(graphic->slp)
            {
                LoadSLPFrame(graphic);
                return;
            }
        }
    }
    graphic->slp.reset();
    graphic->bitmap = wxNullBitmap;
}

void AGE_Frame::LoadSLPFrame(AGE_SLP *graphic)
{
    if(!graphic->slp)
    {
        graphic->bitmap = wxNullBitmap;
        SetStatusText("Loading frame without SLP", 1);
        return;
    }
    genie::SlpFramePtr frame;
    SetStatusText("Looking for frame "+FormatInt(graphic->frameID), 1);
    graphic->frames = graphic->slp.get()->getFrameCount();
    if(graphic->frames)
    {
        graphic->frameID %= graphic->frames;
        try
        {
            frame = graphic->slp.get()->getFrame(graphic->frameID);
        }
        catch(out_of_range){}
    }
    if(!frame)
    {
        graphic->bitmap = wxNullBitmap;
        SetStatusText("No frame: " + FormatInt(graphic->frameID) + ", frames: " + FormatInt(graphic->frames), 1);
        return;
    }

    int width = frame.get()->getWidth();
    int height = frame.get()->getHeight();
    short pal_chooser = frame.get()->getProperties() >> 16;
    graphic->xpos = graphic->flip ? frame.get()->hotspot_x - width : -frame.get()->hotspot_x;
    graphic->ypos = -frame.get()->hotspot_y;
    int area = width * height;
    vector<uint8_t> rgbdata(area * 4, 0);
    uint8_t *val = rgbdata.data();
    uint8_t *alpha = val + area * 3;
    const genie::SlpFrameData *imgdata = &frame.get()->img_data;
    if(frame.get()->is32bit())
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
                genie::Color rgba = (*pal)[uint8_t(imgdata->player_color_mask[i].index + AGE_SLP::playerColorStart)];
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
                    genie::Color rgba = (*pal)[AGE_SLP::playerColorID];
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
    graphic->bitmap = wxBitmap(img, 24);
}

void AGE_Frame::BitMaptoSLP(AGE_SLP *graphic)
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
        frame = graphic->slp.get()->getFrame(graphic->frameID);
    }
    catch(out_of_range){}
    if(!frame)
    {
        wxMessageBox("Congrats seeing this message", "No SLP frame " + lexical_cast<string>(graphic->frameID));
        return;
    }
    genie::SlpFrameData *imgdata = &frame.get()->img_data;
    if(frame.get()->is32bit())
    {
        frame.get()->setSize(img.GetWidth(), img.GetHeight());
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
        size_t numbeg = line.find_first_not_of(" \t");
        if(string::npos != numbeg)
        {
            size_t numend = line.find_first_of(" \t", numbeg + 1);
            string index = line.substr(numbeg, numend - numbeg);
            try
            {
                int ID = lexical_cast<int>(index);
                size_t beg = line.find("\"", numend) + 1;
                size_t end = line.find("\"", beg);
                LangTxt[ID] = line.substr(beg, end - beg);
            }
            catch(bad_lexical_cast e){}
        }
    }
}

wxString AGE_Frame::LangDLLstring(int ID, int Letters)
{
	if(ID < 0) return "";
	string Result = "";
	if(UseTXT)
	{
		Result = LangTxt[ID];
	}
	else if(sizeof(size_t) > 4 || WriteLangs)
	{
		if(LangsUsed & 4 && !(Result = LangXP->getString(ID)).empty()){}
		else if(LangsUsed & 2 && !(Result = LangX->getString(ID)).empty()){}
		else if(LangsUsed & 1 && !(Result = Lang->getString(ID)).empty()){}
	}
	else // Does not work when building as 64-bit
	{
		char Buffer[Letters];
		if(LangsUsed & 4 && LoadStringA(LanguageDLL[2], ID, Buffer, Letters) && strlen(Buffer) > 0) Result = Buffer;
		else if(LangsUsed & 2 && LoadStringA(LanguageDLL[1], ID, Buffer, Letters) && strlen(Buffer) > 0) Result = Buffer;
		else if(LangsUsed & 1 && LoadStringA(LanguageDLL[0], ID, Buffer, Letters) && strlen(Buffer) > 0) Result = Buffer;
	}
    wxString text(Result);
    text.Replace("\n", "\r\n");
	return text;
}

void AGE_Frame::OnKillFocus_LangDLL(wxFocusEvent &event)
{
    event.Skip();
    TextCtrl_DLL *control = (TextCtrl_DLL*)event.GetEventObject();
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

void AGE_Frame::showPopUp(wxIdleEvent& event)
{
    if(popUp.hasMessage)
    {
        wxMessageBox(popUp.popUpMessage, popUp.popUpTitle);
        popUp.hasMessage = false;
        if(popUp.focusTarget)
        {
            if(popUp.focusTarget->IsEnabled() && popUp.focusTarget->IsShownOnScreen())
            popUp.focusTarget->SetFocus();
            popUp.focusTarget = 0;
        }
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
        if(useAnd[0]) // All search parts must match.
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
        if(useAnd[1]) // All search parts must match.
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

//	Following kill focuses are used to update lists in user interface

void AGE_Frame::OnSelection_SearchFilters(wxCommandEvent &event)
{
	if(event.GetId() == Units_FilterSelector->GetId())
	{
		ListUnits(UnitCivID, false);
		Units_Search->SetFocus();
		return;
	}
	for(size_t loop = 0; loop < 2; ++loop) // Custom search filters
	{
		if(event.GetId() == Units_SearchFilters[loop]->GetId())
		{
			ListUnits(UnitCivID, false);
			Units_Search->SetFocus();
		}
		else if(event.GetId() == Graphics_SearchFilters[loop]->GetId())
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

void AGE_Frame::virtualListing(AGEListView* list)
{
    long firstVisible = list->GetTopItem();
    long firstSelected = list->GetFirstSelected();
    int lastItemCount = list->GetItemCount();

    //list->SetItemCount(0); // Clears selections and makes all calls to SetItemPosition be ignored.
    list->SetItemCount(list->names.size());
    list->SetColumnWidth(0, wxLIST_AUTOSIZE_USEHEADER);
    if(list->names.empty()) return;

	// Set selections and first visible item.
    if(firstSelected == -1)
    {
        firstSelected = 0;
    }
    long sweeper = firstSelected;
    while(true)
    {
        list->Select(sweeper, false);
        if(!list->GetSelectedItemCount()) break;
        sweeper = list->GetNextSelected(sweeper);
    }
    if(How2List == ADD || firstSelected >= list->names.size())
    {
        firstSelected = list->names.size() - 1;
    }
    list->SetItemPosition(firstVisible, wxPoint(0, 0));
    list->Select(firstSelected, true);
    if(How2List != SEARCH)
    {
        list->EnsureVisible(lastItemCount < list->GetItemCount() ? list->names.size() - 1 : firstSelected);
        list->SetFocus();
    }
    list->Refresh();
	How2List = SEARCH;
}

void AGE_Frame::FillLists(vector<ComboBox_Plus1*> &boxlist, wxArrayString &names)
{
	for(ComboBox_Plus1* &list: boxlist)
	{
		int selection = list->GetSelection();
		list->Clear();
		list->Append("-1 - None");
		list->Append(names);
		list->SetSelection(selection < list->GetCount() ? selection : 0);
	}
}

void AGE_AreaTT84::FillItemCombo(int selection, bool update)
{
	int oldList = lastList;
	if(Mode->GetValue().empty()) lastList = 0;
	else lastList = lexical_cast<int>(Mode->GetValue());
	if(lastList != oldList || update)
	{
		ItemCombo->Clear();
		ItemCombo->Append("-1 - None");
		switch(lastList)
		{
			case 0:
				ItemCombo->Append(ages);
				break;
			case 1:
			case 2:
				ItemCombo->Append(units);
				break;
			case 3:
				ItemCombo->Append(researches);
				break;
			default: return;
		}
	}
	ItemCombo->SetSelection(selection);
}

bool AGE_Frame::Paste11Check(size_t pastes, size_t copies)
{
	bool result = copies == pastes;
	if(!result)
	wxMessageBox(wxString::Format("%u copies, %u selections.\nClick paste tool to switch to sequential paste.", copies, pastes), "Selections Mismatch");
	return result;
}

void AGE_Frame::SearchAllSubVectors(AGEListView *list, wxTextCtrl *topSearch, wxTextCtrl *subSearch)
{
	int selections = list->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
	if(selections < 1) return;

    set<uint32_t> topNums, subNums;
	for(size_t loop = 0, lastItem = -1; loop < selections; ++loop)
	{
        lastItem = list->GetNextSelected(lastItem);
        string line(list->GetItemText(lastItem));
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

void AGE_Frame::getSelectedItems(const int selections, const AGEListView* list, vector<int> &indexes)
{
    ++randomi;
    indexes.resize(selections);
    for(int sel = 0, lastItem = -1; sel < selections; ++sel)
    {
        lastItem = list->GetNextSelected(lastItem);
        indexes[sel] = list->indexes[lastItem];
    }
    SetStatusText("Times listed: "+lexical_cast<string>(randomi), 2);
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

void AGE_Frame::SaveBackup()
{
	try
	{
		dataset->saveAs((DatFileName.substr(0, DatFileName.size()-4)+"_backup"+CurrentTime()+".dat").c_str());
	}
	catch(std::ios_base::failure e)
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
	os << 1 + parts->tm_mon;
	os << parts->tm_mday;
	os << parts->tm_hour;
	os << parts->tm_min;
	os << parts->tm_sec;
	return buffer.str();
}

AGE_SLP* AGE_Frame::getCurrentGraphics()
{
    AGE_SLP *graphic = 0;
    if(AGE_SLP::currentDisplay == AGE_SLP::SHOW::GRAPHIC)
    {
        graphic = &graphicSLP;
    }
    else if(AGE_SLP::currentDisplay == AGE_SLP::SHOW::UNIT)
    {
        graphic = &unitSLP;
    }
    return graphic;
}

void AGE_Frame::OnFrameButton(wxCommandEvent &event)
{
    switch(event.GetId())
    {
        case eNextFrame:
        {
            AGE_SLP *graphic = getCurrentGraphics();
            if(graphic)
            {
                bool framesleft = false;
                if(graphic->slp)
                {
                    ChooseNextFrame(*graphic, framesleft);
                }
                for(auto &delta: graphic->deltas)
                {
                    if(!delta.second.slp) continue;
                    ChooseNextFrame(delta.second, framesleft);
                }
                HandleLastFrame(*graphic, framesleft, 1u);
                slp_view->Refresh();
            }
            break;
        }
        case ePrevFrame:
        {
            AGE_SLP *graphic = getCurrentGraphics();
            if(graphic)
            {
                bool framesleft = false;
                if(graphic->slp)
                {
                    ChoosePreviousFrame(*graphic, framesleft);
                }
                for(auto &delta: graphic->deltas)
                {
                    if(!delta.second.slp) continue;
                    ChoosePreviousFrame(delta.second, framesleft);
                }
                HandleLastFrame(*graphic, framesleft, 2u);
                slp_view->Refresh();
            }
            break;
        }
        case eFirstFrame:
        {
            AGE_SLP::bearing = 0.f;
            AGE_SLP::setbearing = 1u;
            slp_view->Refresh();
            break;
        }
        case eExportFrame:
        {
            exportFrame = true;
            if(AGE_SLP::currentDisplay == AGE_SLP::SHOW::GRAPHIC)
            {
                SLPtoBitMap(&graphicSLP);
                if(graphicSLP.bitmap.IsOk())
                if(!graphicSLP.bitmap.SaveFile("Testi.png", wxBITMAP_TYPE_PNG))
                    wxMessageBox("Saving frame as PNG failed", "SLP");
            }
            else wxMessageBox("Choose a graphic from graphics tab", "SLP");
            exportFrame = false;
            break;
        }
        case eImportFrame:
        {
            if(AGE_SLP::currentDisplay == AGE_SLP::SHOW::GRAPHIC)
            {
                BitMaptoSLP(&graphicSLP);
            }
            graphicAnimTimer.Start(100);
            break;
        }
        case eSaveSLP:
        {
            if(AGE_SLP::currentDisplay == AGE_SLP::SHOW::GRAPHIC)
            {
                if(!graphicSLP.slp)
                {
                    wxMessageBox("No SLP to save", "SLP");
                    return;
                }
                if(graphicSLP.filename.empty())
                {
                    wxMessageBox("No SLP filename", "SLP");
                    return;
                }
                try
                {
                    wxString name = graphicSLP.filename + ".slp";
                    graphicSLP.slp.get()->saveAs(name.c_str());
                    wxMessageBox("Saved SLP " + name, "SLP");
                }
                catch(std::ios_base::failure e)
                {
                    wxMessageBox("Saving SLP failed", "SLP");
                }
            }
            else wxMessageBox("Look at some graphic", "SLP");
            break;
        }
        case eSLPTool:
        {
            slp_tool_on = !slp_tool_on;
            slp_tool_layout->Show(slp_tool_on);
            slp_sizer->Layout();
            slp_window->Fit();
            break;
        }
        case eSLPMergeShadow:
        {
            genie::SlpFilePtr slp_src1(new genie::SlpFile());
            genie::SlpFilePtr slp_src2(new genie::SlpFile());
            try
            {
                slp_src1.get()->load(slp_source1->GetPath().c_str());
                slp_src1.get()->freelock();
                slp_src2.get()->load(slp_source2->GetPath().c_str());
                slp_src2.get()->freelock();
            }
            catch(std::ios_base::failure e)
            {
                wxMessageBox("Error reading SLP files", "SLP");;
                return;
            }
            for(uint32_t frame = 0; frame < slp_src1.get()->getFrameCount(); ++frame)
            {
                genie::SlpFramePtr frame1, frame2;
                try
                {
                    frame1 = slp_src1.get()->getFrame(frame);
                    frame2 = slp_src2.get()->getFrame(frame);
                }
                catch(out_of_range)
                {
                    wxMessageBox("Frame count mismatch", "SLP");
                    break;
                }

                int32_t offset_x, offset_y;
                // Resize frame if the other frame is bigger in some dimension.
                frame1.get()->enlargeForMerge(*(frame2.get()), offset_x, offset_y);
                uint32_t width = frame1.get()->getWidth(), height = frame1.get()->getHeight();

                genie::SlpFrameData *imgdata = &frame1.get()->img_data;
                imgdata->shadow_mask.clear();
                for(auto const &shadow_pixel: frame2.get()->img_data.shadow_mask)
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
                slp_src1.get()->saveAs(slp_target1->GetPath().c_str());
                wxMessageBox("Merged SLP files", "SLP");
            }
            catch(std::ios_base::failure e)
            {
                wxMessageBox("Saving SLP failed", "SLP");
            }
            break;
        }
        case eShowHotspot:
        {
            DrawHot = event.IsChecked();
            slp_view->Refresh();
            break;
        }
		case eAnimSLP:
		{
			AnimSLP = event.IsChecked();
            slp_view->Refresh();
            break;
		}
		case eShowShadows:
		{
			ShowShadows = event.IsChecked();
            slp_view->Refresh();
            break;
		}
		case eShowOutline:
		{
			ShowOutline = event.IsChecked();
            slp_view->Refresh();
            break;
		}
		case eShowDeltas:
		{
			ShowDeltas = event.IsChecked();
            graphicSLP.slpID = unitSLP.slpID = -2;
            slp_view->Refresh();
            break;
		}
		case eShowStack:
		{
			ShowStack = event.IsChecked();
            graphicSLP.slpID = unitSLP.slpID = -2;
            slp_view->Refresh();
            break;
		}
		case eShowAnnexes:
		{
			ShowAnnexes = event.IsChecked();
            graphicSLP.slpID = unitSLP.slpID = -2;
            slp_view->Refresh();
            break;
		}
        case eShowTerrain:
        {
			DrawTerrain = event.IsChecked();
            slp_view->Refresh();
            break;
        }
        case ePickBgColor:
        {
            wxColour back(slp_background->GetColour());
            SLPbackR = back.Red();
            SLPbackG = back.Green();
            SLPbackB = back.Blue();
            slp_background_brush = wxBrush(back);
            slp_view->Refresh();
            break;
        }
        case eCollisionShape:
        {
			DrawCollisionShape = event.IsChecked();
            slp_view->Refresh();
            break;
        }
        case eClearanceShape:
        {
			DrawClearanceShape = event.IsChecked();
            slp_view->Refresh();
            break;
        }
        case eSelectionShape:
        {
			DrawSelectionShape = event.IsChecked();
            slp_view->Refresh();
            break;
        }
    }
}

void AGE_Frame::OnFrameMouse(wxMouseEvent &event)
{
    int centerX, centerY;
    CalcDrawCenter(slp_view, centerX, centerY);
    wxPoint coords(slp_view->ScreenToClient(wxGetMousePosition()));
    coords.x -= centerX;
    coords.y -= centerY;
    AGE_SLP::bearing = atan2(coords.x, -coords.y * 2) + 3.1416f;
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
            dx[i] = &dataset->Graphics[GraphicIDs.front()].Deltas[DeltaIDs[i]].DirectionX;
            dy[i] = &dataset->Graphics[GraphicIDs.front()].Deltas[DeltaIDs[i]].DirectionY;
        }
    }
    switch(event.GetKeyCode())
    {
        case 'a':
        {
            slp_extra_info = "X - 1";
            for(size_t i = 0; i < dx.size(); ++i) --*dx[i];
            break;
        }
        case 'd':
        {
            slp_extra_info = "X + 1";
            for(size_t i = 0; i < dx.size(); ++i) ++*dx[i];
            break;
        }
        case 's':
        {
            slp_extra_info = "Y + 1";
            for(size_t i = 0; i < dy.size(); ++i) ++*dy[i];
            break;
        }
        case 'w':
        {
            slp_extra_info = "Y - 1";
            for(size_t i = 0; i < dy.size(); ++i) --*dy[i];
            break;
        }
        default: return;
    }
    popUp.unSaved += DeltaIDs.size();
    wxTimerEvent E;
    OnGraphicDeltasTimer(E);
    graphicSLP.slpID = -3;
    slp_view->Refresh();
}

void AGE_Frame::OnExitSLP(wxCloseEvent &event)
{
    SubMenu_SLP->Check(eShowSLP, false);
    wxCommandEvent closeSLP(wxEVT_COMMAND_MENU_SELECTED, eShowSLP);
    closeSLP.SetInt(false);
    ProcessEvent(closeSLP);
}

void AGE_Frame::OnExit(wxCloseEvent &event)
{
    {
        wxFileConfig Config("AGE", "Tapsa", "age2configw"+lexical_cast<string>(window_num + 1)+".ini", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
        Config.Write("Interaction/PromptForFilesOnOpen", PromptForFilesOnOpen);
        Config.Write("Interaction/AutoCopy", AutoCopy);
        Config.Write("Interaction/CopyGraphics", CopyGraphics);
        Config.Write("Interaction/AllCivs", Units_SpecialCopy_Civs->GetValue());
        Config.Write("Interaction/EnableIDFix", EnableIDFix);
        Config.Write("Interaction/ShowSLP", ShowSLP);
        Config.Write("Interaction/ShowIcons", ShowIcons);
        Config.Write("Interaction/AnimSLP", AnimSLP);
        Config.Write("Interaction/ShowShadows", ShowShadows);
        Config.Write("Interaction/ShowOutline", ShowOutline);
        Config.Write("Interaction/ShowDeltas", ShowDeltas);
        Config.Write("Interaction/ShowStack", ShowStack);
        Config.Write("Interaction/ShowAnnexes", ShowAnnexes);
        Config.Write("Interaction/DrawTerrain", DrawTerrain);
        Config.Write("Interaction/FilterAllSubs", FilterAllSubs);
        Config.Write("Interface/ShowUnknowns", ShowUnknowns);
        Config.Write("Interface/ResizeTerrains", ResizeTerrains);
        Config.Write("Interface/StayOnTop", StayOnTop);
        Config.Write("Interface/StayOnTopSLP", StayOnTopSLP);
        Config.Write("Interface/Paste11", Paste11);
        Config.Write("Interface/MaxWindowWidth", MaxWindowWidth);
        Config.Write("Interface/SLPareaPerCent", SLPareaPerCent);
        Config.Write("Interface/SLPbackR", SLPbackR);
        Config.Write("Interface/SLPbackG", SLPbackG);
        Config.Write("Interface/SLPbackB", SLPbackB);
        Config.Write("Interface/DrawCollisionShape", DrawCollisionShape);
        Config.Write("Interface/DrawClearanceShape", DrawClearanceShape);
        Config.Write("Interface/DrawSelectionShape", DrawSelectionShape);
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
                wxCommandEvent SaveFiles(wxEVT_COMMAND_MENU_SELECTED, eSave);
                ProcessEvent(SaveFiles);
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
    wxCommandEvent loadDRS(wxEVT_COMMAND_MENU_SELECTED, eDRS);
    loadDRS.SetInt(false);
    ProcessEvent(loadDRS);

    delete dataset;
    if(WriteLangs)
    {
        delete Lang;
        delete LangX;
        delete LangXP;
    }

    AGE_Frame::openEditors[window_num] = 0;
    while(graphicAnimTimer.IsRunning())
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
