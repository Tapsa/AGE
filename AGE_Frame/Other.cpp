#include "../AGE_Frame.h"

wxArrayString AGE_AreaTT84::ages, AGE_AreaTT84::researches, AGE_AreaTT84::units;
bool AGETextCtrl::editable;
bool AGETextCtrl::hexMode;
bool AGETextCtrl::accurateFloats;

void AGE_Frame::OnOpen(wxCommandEvent &Event)
{
	AGETextCtrl::editable = false;
	wxCommandEvent Selected;

	if(!SkipOpenDialog)
	{
		AGE_OpenDialog OpenBox(this, NeedDat);

		OpenBox.CheckBox_GenieVer->SetSelection(GameVersion);

		switch(DatUsed)
		{
			case 0:
			{
				OpenBox.Radio_DatFileLocation->SetValue(true);
				Selected.SetEventType(wxEVT_COMMAND_RADIOBUTTON_SELECTED);
				Selected.SetId(OpenBox.Radio_DatFileLocation->GetId());
				Selected.SetInt(true);
				OpenBox.GetEventHandler()->ProcessEvent(Selected);
			}
			break;
			case 2:
			{
				OpenBox.Radio_ApfFileLocation->SetValue(true);
				Selected.SetEventType(wxEVT_COMMAND_RADIOBUTTON_SELECTED);
				Selected.SetId(OpenBox.Radio_ApfFileLocation->GetId());
				Selected.SetInt(true);
				OpenBox.GetEventHandler()->ProcessEvent(Selected);
			}
			break;
		}

		OpenBox.DriveLetterBox->ChangeValue(DriveLetter);
		OpenBox.CheckBox_CustomDefault->SetValue(UseCustomPath);
		OpenBox.Path_CustomDefault->SetPath(CustomFolder);
		OpenBox.LanguageBox->ChangeValue(Language);
		if(AGEwindow == 1) OpenBox.WindowCountBox->ChangeValue(lexical_cast<string>(SimultaneousFiles));
		OpenBox.Path_DatFileLocation->SetPath(DatFileName);
		OpenBox.Path_ApfFileLocation->SetPath(ApfFileName);

		OpenBox.CheckBox_LangFileLocation->SetValue(LangsUsed & 1);
		Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
		Selected.SetId(OpenBox.CheckBox_LangFileLocation->GetId());
		Selected.SetInt(LangsUsed & 1);
		OpenBox.GetEventHandler()->ProcessEvent(Selected);

		OpenBox.CheckBox_LangX1FileLocation->SetValue(LangsUsed & 2);
		Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
		Selected.SetId(OpenBox.CheckBox_LangX1FileLocation->GetId());
		Selected.SetInt(LangsUsed & 2);
		OpenBox.GetEventHandler()->ProcessEvent(Selected);

		OpenBox.CheckBox_LangX1P1FileLocation->SetValue(LangsUsed & 4);
		Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
		Selected.SetId(OpenBox.CheckBox_LangX1P1FileLocation->GetId());
		Selected.SetInt(LangsUsed & 4);
		OpenBox.GetEventHandler()->ProcessEvent(Selected);

		OpenBox.Path_LangFileLocation->SetPath(LangFileName);
		OpenBox.Path_LangX1FileLocation->SetPath(LangX1FileName);
		OpenBox.Path_LangX1P1FileLocation->SetPath(LangX1P1FileName);
		OpenBox.CheckBox_LangWrite->SetValue(WriteLangs);
		OpenBox.CheckBox_LangWriteToLatest->SetValue(LangWriteToLatest);

		AGETextCtrl::editable = true;
		if(OpenBox.ShowModal() != wxID_OK) return; // What this does?

		GameVersion = OpenBox.CheckBox_GenieVer->GetSelection();
		if(OpenBox.Radio_DatFileLocation->GetValue())
		{
			DatUsed = 0;
		}
		else if(OpenBox.Radio_ApfFileLocation->GetValue())
		{
			DatUsed = 2;
		}
		else
		{
			DatUsed = 3;
		}

		DriveLetter = OpenBox.DriveLetterBox->GetValue();
		UseCustomPath = OpenBox.CheckBox_CustomDefault->GetValue();
		CustomFolder = OpenBox.Path_CustomDefault->GetPath();
		Language = OpenBox.LanguageBox->GetValue();
		if(AGEwindow == 1) SimultaneousFiles = lexical_cast<int>(OpenBox.WindowCountBox->GetValue());
		DatFileName = OpenBox.Path_DatFileLocation->GetPath();
		ApfFileName = OpenBox.Path_ApfFileLocation->GetPath();

		if(OpenBox.CheckBox_LangFileLocation->IsChecked())
		{
			LangsUsed |= 1;
		}
		else
		{
			LangsUsed &= ~1;
		}
		if(OpenBox.CheckBox_LangX1FileLocation->IsChecked())
		{
			LangsUsed |= 2;
		}
		else
		{
			LangsUsed &= ~2;
		}
		if(OpenBox.CheckBox_LangX1P1FileLocation->IsChecked())
		{
			LangsUsed |= 4;
		}
		else
		{
			LangsUsed &= ~4;
		}

		LangFileName = OpenBox.Path_LangFileLocation->GetPath();
		LangX1FileName = OpenBox.Path_LangX1FileLocation->GetPath();
		LangX1P1FileName = OpenBox.Path_LangX1P1FileLocation->GetPath();
		WriteLangs = OpenBox.CheckBox_LangWrite->GetValue();
		LangWriteToLatest = OpenBox.CheckBox_LangWriteToLatest->GetValue();
	}

	switch(GameVersion)
	{
		case EV_TEST: GenieVersion = genie::GV_TEST; break;
		case EV_MIK: GenieVersion = genie::GV_MIK; break;
		case EV_DAVE: GenieVersion = genie::GV_DAVE; break;
		case EV_MATT: GenieVersion = genie::GV_MATT; break;
		case EV_AoEB: GenieVersion = genie::GV_AoEB; break;
		case EV_AoETB: GenieVersion = genie::GV_AoETB; break;
		case EV_AoE: GenieVersion = genie::GV_AoE; break;
		case EV_RoR: GenieVersion = genie::GV_RoR; break;
		case EV_AoKA: GenieVersion = genie::GV_AoKA; break;
		case EV_AoKB: GenieVersion = genie::GV_AoKB; break;
		case EV_AoK: GenieVersion = genie::GV_AoK; break;
		case EV_TC: GenieVersion = genie::GV_TC; break;
		case EV_SWGB: GenieVersion = genie::GV_SWGB; break;
		case EV_CC: GenieVersion = genie::GV_CC; break;
		default: GenieVersion = genie::GV_None; wxMessageBox("Wrong version", "Oops!");
	}

	if(Lang != NULL)
	{
		delete Lang;
		Lang = NULL;
	}
	if(LangX != NULL)
	{
		delete LangX;
		LangX = NULL;
	}
	if(LangXP != NULL)
	{
		delete LangXP;
		LangXP = NULL;
	}

	if(LangsUsed & 1)
	{
		if(sizeof(size_t) > 4 || WriteLangs)
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
				Lang = NULL;
				return;
			}
		}
		else LanguageDLL[0] = LoadLibrary(LangFileName.c_str());
	}
	if(LangsUsed & 2)
	{
		if(sizeof(size_t) > 4 || WriteLangs)
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
				LangX = NULL;
				return;
			}
		}
		else LanguageDLL[1] = LoadLibrary(LangX1FileName.c_str());
	}
	if(LangsUsed & 4)
	{
		if(sizeof(size_t) > 4 || WriteLangs)
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
				LangXP = NULL;
				return;
			}
		}
		else LanguageDLL[2] = LoadLibrary(LangX1P1FileName.c_str());
	}

	if(GenieFile != NULL)
	{
		TechTrees_Ages_Items.Mode->container.resize(0);
		TechTrees_Buildings_Items.Mode->container.resize(0);
		TechTrees_Units_Items.Mode->container.resize(0);
		TechTrees_Researches_Items.Mode->container.resize(0);
		delete GenieFile;
		GenieFile = NULL;
	}
	else
	{
		TabBar_Main->ChangeSelection(4);
	}

	{
		SetStatusText("Reading file...", 0);
		wxBusyCursor WaitCursor;

		GenieFile = new genie::DatFile();
		try
		{
			GenieFile->setGameVersion(GenieVersion);
			GenieFile->load(DatFileName.c_str());
		}
		catch(std::ios_base::failure e)
		{
			wxMessageBox("Failed to load "+DatFileName);
			delete GenieFile;
			GenieFile = NULL;
			return;
		}
	}

	if(GenieFile != NULL)
	{	// Without these, nothing can be edited.
		SetStatusText("Listing...", 0);
		wxBusyCursor WaitCursor;

		// No research gaia fix.
		if(GenieFile->Civs.size() > 1)
		{
			for(short loop = GenieFile->Civs[0].Units.size(); loop--> 0;)
				GenieFile->Civs[0].Units[loop].Enabled = GenieFile->Civs[1].Units[loop].Enabled;
		}
		// Pointers contain useless data, which the game overrides anyway.
		// ID and pointer fixes.
		for(short loop = GenieFile->Civs.size(); loop--> 0;)
		{
			for(short loop2 = GenieFile->Civs[loop].Units.size(); loop2--> 0;)
			{
				if(GenieFile->Civs[loop].UnitPointers[loop2] != 0)
				{
					GenieFile->Civs[loop].UnitPointers[loop2] = 1;
					if(EnableIDFix)
					{
						GenieFile->Civs[loop].Units[loop2].ID1 = loop2;
						if(GenieVersion >= genie::GV_AoE)
						GenieFile->Civs[loop].Units[loop2].ID2 = loop2;
						if(GenieVersion >= genie::GV_AoK)
						GenieFile->Civs[loop].Units[loop2].ID3 = loop2;
						else
						if(GenieFile->Civs[loop].Units[loop2].Type >= 40 && GenieFile->Civs[loop].Units[loop2].Type <= 80)
						for(short loop3 = GenieFile->Civs[loop].Units[loop2].Bird.Commands.size(); loop3--> 0;)
						GenieFile->Civs[loop].Units[loop2].Bird.Commands[loop3].ID = loop3;
					}
				}
			}
		}
		if(EnableIDFix)
		{
			for(short loop = GenieFile->PlayerColours.size(); loop--> 0;)
			{
				GenieFile->PlayerColours[loop].ID = loop;
			}
			for(short loop = GenieFile->Sounds.size(); loop--> 0;)
			{
				GenieFile->Sounds[loop].ID = loop;
			}
			if(GenieVersion >= genie::GV_SWGB)
			for(short loop = GenieFile->UnitLines.size(); loop--> 0;)
			{
				GenieFile->UnitLines[loop].ID = loop;
			}
		}
		if(GenieVersion >= genie::GV_AoE)
		for(short loop = GenieFile->Graphics.size(); loop--> 0;)
		{
			if(GenieFile->GraphicPointers[loop] != 0)
			{
				GenieFile->GraphicPointers[loop] = 1;
				if(EnableIDFix)
				GenieFile->Graphics[loop].ID = loop;
			}
		}
		for(short loop = GenieFile->TerrainRestrictions.size(); loop--> 0;)
		{
			if(GenieFile->TerrainRestrictionPointers1[loop] != 0)
			GenieFile->TerrainRestrictionPointers1[loop] = 1;
			if(GenieVersion >= genie::GV_AoKA)
			if(GenieFile->TerrainRestrictionPointers2[loop] != 0)
			GenieFile->TerrainRestrictionPointers2[loop] = 1;
		}

		Added = false;

		UnitCommands_Type_ComboBox->Clear();
		UnitCommands_Type_ComboBox->Append("Unused Ability/Invalid Ability");	// Selection 0
		UnitCommands_Type_ComboBox->Append("1: Move to");
		UnitCommands_Type_ComboBox->Append("2: Follow");
		UnitCommands_Type_ComboBox->Append("3: Garrison");
		UnitCommands_Type_ComboBox->Append("4: Explore");
		UnitCommands_Type_ComboBox->Append("5: Gather/Rebuild");
		UnitCommands_Type_ComboBox->Append("6: Unknown Animal Ability");
		UnitCommands_Type_ComboBox->Append("7: Attack");
		UnitCommands_Type_ComboBox->Append("8: Shoot");
		UnitCommands_Type_ComboBox->Append("10: Fly");
		UnitCommands_Type_ComboBox->Append("11: Unknown Predator Ability");
		UnitCommands_Type_ComboBox->Append("12: Unload (Boat-Like)");
		UnitCommands_Type_ComboBox->Append("13: Guard");
		//UnitCommands_Type_ComboBox->Append("14: Unknown Ability");
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
		UnitCommands_Type_ComboBox->Append("109: Unknown Ability");
		UnitCommands_Type_ComboBox->Append("110: Hunt");
		UnitCommands_Type_ComboBox->Append("111: Trade");
		//UnitCommands_Type_ComboBox->Append("112: Unknown Ability");
		//UnitCommands_Type_ComboBox->Append("113: Unknown Ability");
		UnitCommands_Type_ComboBox->Append("120: Generate Wonder Victory");
		UnitCommands_Type_ComboBox->Append("121: Deselect when Tasked");
		UnitCommands_Type_ComboBox->Append("122: Loot");
		UnitCommands_Type_ComboBox->Append("123: Housing");
		UnitCommands_Type_ComboBox->Append("125: Unpack & Attack");
		//UnitCommands_Type_ComboBox->Append("130: Unknown Ability");
		UnitCommands_Type_ComboBox->Append("131: Unknown Ability");
		UnitCommands_Type_ComboBox->Append("132: Pickup Unit");
		//UnitCommands_Type_ComboBox->Append("133: Unknown Pickup Ability");
		//UnitCommands_Type_ComboBox->Append("134: Unknown Pickup Ability");
		UnitCommands_Type_ComboBox->Append("135: Kidnap Unit");
		UnitCommands_Type_ComboBox->Append("136: Deposit Unit");	// Selection 33
		UnitCommands_Type_ComboBox->Append("149: Shear");	// Selection 33
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

		wxArrayString DefAoE1Armors, DefAoE2Armors, DefSWGBArmors;
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
		DefAoE2Armors.Add("14 - Unused");
		DefAoE2Armors.Add("15 - Archers");
		DefAoE2Armors.Add("16 - Ships & Camels & Saboteurs");
		DefAoE2Armors.Add("17 - Rams");
		DefAoE2Armors.Add("18 - Trees");
		DefAoE2Armors.Add("19 - Unique Units (except Turtle Ship)");
		DefAoE2Armors.Add("20 - Siege Weapons");
		DefAoE2Armors.Add("21 - Standard Buildings");
		DefAoE2Armors.Add("22 - Walls & Gates");
		DefAoE2Armors.Add("23 - Unused");
		DefAoE2Armors.Add("24 - Boars");
		DefAoE2Armors.Add("25 - Monks");
		DefAoE2Armors.Add("26 - Castle");
		DefAoE2Armors.Add("27 - Spearmen");
		DefAoE2Armors.Add("28 - Cavalry Archers");
		DefAoE2Armors.Add("29 - Eagle Warriors");
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

		Customs = new wxFileConfig(wxEmptyString, "Tapsa", "age2armornames.ini", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
		long ExtraCount, AoE1Count, AoE2Count, SWGBCount;
		if(!Customs->Read("Count/AoE1Count", &AoE1Count, DefAoE1Armors.GetCount()))
			Customs->Write("Count/AoE1Count", (int)DefAoE1Armors.GetCount());
		if(!Customs->Read("Count/AoE2Count", &AoE2Count, DefAoE2Armors.GetCount()))
			Customs->Write("Count/AoE2Count", (int)DefAoE2Armors.GetCount());
		if(!Customs->Read("Count/SWGBCount", &SWGBCount, DefSWGBArmors.GetCount()))
			Customs->Write("Count/SWGBCount", (int)DefSWGBArmors.GetCount());
		wxArrayString AoE1Armors, AoE2Armors, SWGBArmors;
		for(short loop = 0; loop < AoE1Count; ++loop)
		{
			wxString MoveHolder;
			if(!Customs->Read("AoE1Names/"+lexical_cast<string>(loop), &MoveHolder, DefAoE1Armors[loop]))
				Customs->Write("AoE1Names/"+lexical_cast<string>(loop), DefAoE1Armors[loop]);
			AoE1Armors.Add(MoveHolder);
		}
		for(short loop = 0; loop < AoE2Count; ++loop)
		{
			wxString MoveHolder;
			if(!Customs->Read("AoE2Names/"+lexical_cast<string>(loop), &MoveHolder, DefAoE2Armors[loop]))
				Customs->Write("AoE2Names/"+lexical_cast<string>(loop), DefAoE2Armors[loop]);
			AoE2Armors.Add(MoveHolder);
		}
		for(short loop = 0; loop < SWGBCount; ++loop)
		{
			wxString MoveHolder;
			if(!Customs->Read("SWGBNames/"+lexical_cast<string>(loop), &MoveHolder, DefSWGBArmors[loop]))
				Customs->Write("SWGBNames/"+lexical_cast<string>(loop), DefSWGBArmors[loop]);
			SWGBArmors.Add(MoveHolder);
		}
		delete Customs;

		for(short loop = 0; loop < 3; ++loop)
		{
			Units_Class_ComboBox[loop]->Clear();
			Units_Class_ComboBox[loop]->Append("No Class/Invalid Class");	// Selection 0
			if(GenieVersion < genie::GV_SWGB)
			{
				Units_Class_ComboBox[loop]->Append("0 - Archery");// archery-class
				Units_Class_ComboBox[loop]->Append("1 - Artifact/Ruins");
				Units_Class_ComboBox[loop]->Append("2 - Trade Boat");
				Units_Class_ComboBox[loop]->Append("3 - Building");// building-class
				Units_Class_ComboBox[loop]->Append("4 - Villager");// villager-class
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
				Units_Class_ComboBox[loop]->Append("18 - Monk");// monastery-class
				Units_Class_ComboBox[loop]->Append("19 - Trade Cart");
				Units_Class_ComboBox[loop]->Append("20 - Transport Boat");
				Units_Class_ComboBox[loop]->Append("21 - Fishing Boat");
				Units_Class_ComboBox[loop]->Append("22 - Warship");// warship-class
				if(GenieVersion <= genie::GV_RoR)
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
				if(GenieVersion <= genie::GV_RoR)
					Units_Class_ComboBox[loop]->Append("35 - Chariot");
				else
					Units_Class_ComboBox[loop]->Append("35 - Petard");// petard-class
				Units_Class_ComboBox[loop]->Append("36 - Cavalry Archer");// cavalry-archer-class
				Units_Class_ComboBox[loop]->Append("37 - Dolphin/Smoke");
				Units_Class_ComboBox[loop]->Append("38 - Bird");
				if(GenieVersion <= genie::GV_RoR)
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
				Units_Class_ComboBox[loop]->Append("51 - Packed Trebuchet");// packed-trebuchet-class
				Units_Class_ComboBox[loop]->Append("52 - Tower");// tower-class
				Units_Class_ComboBox[loop]->Append("53 - Boarding Boat");
				Units_Class_ComboBox[loop]->Append("54 - Unpacked Trebuchet");// unpacked-trebuchet-class
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
			Attacks_Class_ComboBox[loop]->Append("Unused Class/No Class");	// Selection 0
			if(GenieVersion <= genie::GV_RoR) // AoE and RoR
			{	// Use "atc -1|arc -1|disa" to discover these!
				for(short loop2 = 0; loop2 < AoE1Count; ++loop2)
				Attacks_Class_ComboBox[loop]->Append(AoE1Armors[loop2]);
			}
			else if(GenieVersion < genie::GV_SWGB) // AoK and TC
			{
				for(short loop2 = 0; loop2 < AoE2Count; ++loop2)
				Attacks_Class_ComboBox[loop]->Append(AoE2Armors[loop2]);
			}
			else // SWGB and CC
			{
				for(short loop2 = 0; loop2 < SWGBCount; ++loop2)
				Attacks_Class_ComboBox[loop]->Append(SWGBArmors[loop2]);
			}
			Attacks_Class_ComboBox[loop]->SetSelection(0);
		}

		for(short loop = 0; loop < 2; ++loop)
		{
			Units_SearchFilters[loop]->Clear();
			Units_SearchFilters[loop]->Append("Lang DLL Name");	// 0
			Units_SearchFilters[loop]->Append("Internal Name");
			Units_SearchFilters[loop]->Append("Type");
			Units_SearchFilters[loop]->Append("Class");
			Units_SearchFilters[loop]->Append("Terrain Restriction");
			Units_SearchFilters[loop]->Append("Dead Unit");
			Units_SearchFilters[loop]->Append("Civilization (TC+)");
			Units_SearchFilters[loop]->Append("Projectile Unit");
			Units_SearchFilters[loop]->Append("Max Range");
			Units_SearchFilters[loop]->Append("Train Location");
			Units_SearchFilters[loop]->Append("Attacks");
			Units_SearchFilters[loop]->Append("Attack Classes");
			Units_SearchFilters[loop]->Append("Armors");
			Units_SearchFilters[loop]->Append("Armor Classes");
			Units_SearchFilters[loop]->Append("Commands");
			Units_SearchFilters[loop]->Append("Pointer");
		/*	Units_SearchFilters[loop]->Append("Garrison Type");
			Units_SearchFilters[loop]->Append("Enabled");
			Units_SearchFilters[loop]->Append("Hidden in Editor");
			Units_SearchFilters[loop]->Append("Visible in Fog");
			Units_SearchFilters[loop]->Append("Death Mode");
			Units_SearchFilters[loop]->Append("Hero Mode");
			Units_SearchFilters[loop]->Append("Air Mode");
			Units_SearchFilters[loop]->Append("Fly Mode");
			Units_SearchFilters[loop]->Append("Building Mode");
			Units_SearchFilters[loop]->Append("Placement Mode");
			Units_SearchFilters[loop]->Append("Interaction Mode");
			Units_SearchFilters[loop]->Append("Minimap Mode");
			Units_SearchFilters[loop]->Append("Sheep Conversion");
			Units_SearchFilters[loop]->Append("Villager Mode");
			Units_SearchFilters[loop]->Append("Unseletable");
			Units_SearchFilters[loop]->Append("Selection Mask");
			Units_SearchFilters[loop]->Append("Selection Shape Type");
			Units_SearchFilters[loop]->Append("Selection Shape");
			Units_SearchFilters[loop]->Append("Selection Effect");
			Units_SearchFilters[loop]->Append("Editor Selection Color");
			Units_SearchFilters[loop]->Append("Unitline");
			Units_SearchFilters[loop]->Append("Tracking Unit Used");
			Units_SearchFilters[loop]->Append("Command Attribute");
			Units_SearchFilters[loop]->Append("Stack Unit");
			Units_SearchFilters[loop]->Append("Terrain");
			Units_SearchFilters[loop]->Append("Research");
		*/	Units_SearchFilters[loop]->SetSelection(0);

			Research_Research_SearchFilters[loop]->Clear();
			Research_Research_SearchFilters[loop]->Append("Lang DLL Name");	// 0
			Research_Research_SearchFilters[loop]->Append("Internal Name");
			Research_Research_SearchFilters[loop]->Append("Required Researches");
			Research_Research_SearchFilters[loop]->Append("Min. Req. Researches");
			Research_Research_SearchFilters[loop]->Append("Research Location");
			Research_Research_SearchFilters[loop]->Append("Research Time");
			Research_Research_SearchFilters[loop]->Append("Technology");
			Research_Research_SearchFilters[loop]->Append("Type");
			Research_Research_SearchFilters[loop]->Append("Icon");
			Research_Research_SearchFilters[loop]->Append("Button");
			Research_Research_SearchFilters[loop]->Append("Lang DLL Pointer 1");
			Research_Research_SearchFilters[loop]->Append("Lang DLL Pointer 2");
			Research_Research_SearchFilters[loop]->Append("Pointer 3");
			Research_Research_SearchFilters[loop]->Append("Cost Types");
			Research_Research_SearchFilters[loop]->Append("Cost Amounts");
			Research_Research_SearchFilters[loop]->Append("Cost Uses");
			if(GenieVersion >= genie::GV_AoK)
			{
				Research_Research_SearchFilters[loop]->Append("Civilization");
				Research_Research_SearchFilters[loop]->Append("Full Tech Mode");
				if(GenieVersion >= genie::GV_SWGB)
				Research_Research_SearchFilters[loop]->Append("Internal Name 2");
			}
			Research_Research_SearchFilters[loop]->SetSelection(0);

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

		Items.Add(0);
		OnCivCountChange();
		ListTerrainRestrictions(true);
		InitPlayerColors();
		InitSounds(true);
		InitGraphics(true);
		ListTerrainNumbers();
		InitTerrains1(true);
		InitTerrainBorders(true);
		ListGeneral();
		InitRandomMaps();
		InitTechs(true);
		if(GenieVersion >= genie::GV_SWGB)
		{
			InitUnitLines();
		}
		else
		{
			UnitLines_UnitLines_List->Clear();
			UnitLines_UnitLineUnits_List->Clear();
		}
		InitCivs(true);
		InitUnits(GenieVersion <= genie::GV_RoR, true);
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
			TechTrees_MainList_Ages_List->Clear();
			TechTrees_Ages_Buildings.List->Clear();
			TechTrees_Ages_Units.List->Clear();
			TechTrees_Ages_Researches.List->Clear();
			TechTrees_MainList_Buildings_List->Clear();
			TechTrees_Buildings_Buildings.List->Clear();
			TechTrees_Buildings_Units.List->Clear();
			TechTrees_Buildings_Researches.List->Clear();
			TechTrees_MainList_Units_List->Clear();
			TechTrees_Units_Units.List->Clear();
			TechTrees_MainList_Researches_List->Clear();
			TechTrees_Researches_Buildings.List->Clear();
			TechTrees_Researches_Units.List->Clear();
			TechTrees_Researches_Researches.List->Clear();
		}
		if(TimesOpened < 3)
		{
			Units_List->Deselect(0);
			srand(time(NULL));
			short sels = rand() % 2 + 3;
			for(short i=0; ++i<sels;)
			Units_List->SetSelection(rand() % (12 - TimesOpened) + 4);
			Units_List->SetFirstItem(0);
		}

		wxCommandEvent E;
		OnCivsSelect(E);
		OnUnitsSelect(E);
		OnResearchSelect(E);
		OnTechSelect(E);
		OnGraphicsSelect(E);
		OnSoundsSelect(E);
		OnTerrainsSelect(E);
		OnTerrainRestrictionsTerrainSelect(E);
		OnPlayerColorsSelect(E);
		OnTerrainBordersSelect(E);
		OnUnknownsSelect(E);
		if(GenieVersion >= genie::GV_AoKA)
		{
			OnTTAgesSelect(E);
			OnTTBuildingSelect(E);
			OnTTUnitSelect(E);
			OnTTResearchSelect(E);
			if(GenieVersion >= genie::GV_SWGB)
			OnUnitLinesSelect(E);
		}

		Effects_AttributesC_ComboBox->Clear();
		Effects_AttributesC_ComboBox->Append("No Attribute/Invalid Attribute");		// Selection 0
		Effects_AttributesC_ComboBox->Append("0 - Hit Points");		// Selection 1
		Effects_AttributesC_ComboBox->Append("1 - Line of Sight");
		Effects_AttributesC_ComboBox->Append("2 - Garrison Capacity");
		Effects_AttributesC_ComboBox->Append("3 - Unit Size Radius 1");
		Effects_AttributesC_ComboBox->Append("4 - Unit Size Radius 2");
		Effects_AttributesC_ComboBox->Append("5 - Movement Speed");
		Effects_AttributesC_ComboBox->Append("6 - Garrison Recovery Rate");
		Effects_AttributesC_ComboBox->Append("7 - Unknown?");
		if(GenieVersion > genie::GV_RoR)
		{
			Effects_AttributesC_ComboBox->Append("8 - Armor");
			Effects_AttributesC_ComboBox->Append("9 - Attack");
		}
		else
		{
			Effects_AttributesC_ComboBox->Append("8 - Armor (no multiply)");
			Effects_AttributesC_ComboBox->Append("9 - Attack (no multiply)");
		}
		Effects_AttributesC_ComboBox->Append("10 - Attack Reloading Time");
		Effects_AttributesC_ComboBox->Append("11 - Accuracy Percent");
		Effects_AttributesC_ComboBox->Append("12 - Range");
		Effects_AttributesC_ComboBox->Append("13 - Working Rate");
		Effects_AttributesC_ComboBox->Append("14 - Resource Carriage");
		Effects_AttributesC_ComboBox->Append("15 - Default Armor");
		Effects_AttributesC_ComboBox->Append("16 - New Projectile Unit");
		Effects_AttributesC_ComboBox->Append("17 - Upgrade Icon (by age, no multiply)");
		Effects_AttributesC_ComboBox->Append("18 - Unknown21 (always sets)");
		Effects_AttributesC_ComboBox->Append("19 - Enable Intelligent Projectiles");
		if(GenieVersion > genie::GV_RoR)
		{
			Effects_AttributesC_ComboBox->Append("20 - Minimum Range");
			Effects_AttributesC_ComboBox->Append("21 - Population Support");
			Effects_AttributesC_ComboBox->Append("22 - Blast Radius");
			Effects_AttributesC_ComboBox->Append("23 - Search Radius");
			Effects_AttributesC_ComboBox->Append("100 - Resource Cost");
			Effects_AttributesC_ComboBox->Append("101 - Creation Time");
			Effects_AttributesC_ComboBox->Append("102 - Number of Garrison Arrows");
			Effects_AttributesC_ComboBox->Append("103 - Food Cost");
			if(GenieVersion < genie::GV_SWGB)
			{
				Effects_AttributesC_ComboBox->Append("104 - Wood Cost");
				Effects_AttributesC_ComboBox->Append("105 - Gold Cost");
				Effects_AttributesC_ComboBox->Append("106 - Stone Cost");
			}
			else
			{
				Effects_AttributesC_ComboBox->Append("104 - Carbon Cost");
				Effects_AttributesC_ComboBox->Append("105 - Nova Cost");
				Effects_AttributesC_ComboBox->Append("106 - Ore Cost");
			}
			Effects_AttributesC_ComboBox->Append("107 - Max Dup. Missiles");
			Effects_AttributesC_ComboBox->Append("108 - Healing Rate");
		}
		else
		{
			Effects_AttributesC_ComboBox->Append("20 - Unused");
			Effects_AttributesC_ComboBox->Append("21 - Unused");
			Effects_AttributesC_ComboBox->Append("22 - Unused");
			Effects_AttributesC_ComboBox->Append("23 - Unused");
			Effects_AttributesC_ComboBox->Append("100 - Resource Cost");
			Effects_AttributesC_ComboBox->Append("101 - Population Support (set only)");
		}
		Effects_AttributesC_ComboBox->SetSelection(0);

		Units_GraphicSet->Clear();
		if(GenieVersion <= genie::GV_RoR)
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

		DataOpened = true;
		OnGameVersionChange();
	}
	SetStatusText("", 0);

	NeedDat = false;
	SkipOpenDialog = false;
}

void AGE_Frame::OnGameVersionChange()
{
	if(DataOpened)	// Hiding stuff according to game version should be here.
	{
		// Some general tab handling
		for(auto loop = GenieFile->TerrainBlock.getTerrainHeaderSize(); loop < General_TerrainHeader.size(); ++loop)
		General_TerrainHeader[loop]->Show(false);
		for(auto loop = GenieFile->TerrainBlock.getZeroSpaceSize(); loop < General_AfterBorders.size(); ++loop)
		General_AfterBorders[loop]->Show(false);
		for(auto loop = GenieFile->TerrainBlock.getCivDataSize(); loop < General_TerrainRendering.size(); ++loop)
		General_TerrainRendering[loop]->Show(false);
		for(auto loop = GenieFile->TerrainBlock.getSomethingSize(); loop < General_Something.size(); ++loop)
		General_Something[loop]->Show(false);
		if(ShowUnknowns)
		{
			for(short loop = 0; loop < GenieFile->TerrainBlock.getTerrainHeaderSize(); ++loop)
			General_TerrainHeader[loop]->Show(true);
			for(short loop = 0; loop < GenieFile->TerrainBlock.getZeroSpaceSize(); ++loop)
			General_AfterBorders[loop]->Show(true);
			for(short loop = 0; loop < GenieFile->TerrainBlock.getCivDataSize(); ++loop)
			General_TerrainRendering[loop]->Show(true);
			for(short loop = 0; loop < GenieFile->TerrainBlock.getSomethingSize(); ++loop)
			General_Something[loop]->Show(true);
		}

		bool show;

		// Test ->
		show = (GenieVersion >= genie::GV_TEST) ? true : false;
		Sounds_Unknown2_Holder->Show(show);
		Units_DropSite[1]->Show(show);
		Units_DropSite_ComboBox[1]->Show(show);
		if(show)
		{
			SoundItems_Resource->SetBackgroundColour(wxColour(215, 255, 255));
			Graphics_SLP->SetBackgroundColour(wxColour(215, 255, 255));
		}
		else
		{
			SoundItems_Resource->SetBackgroundColour(wxColour(210, 230, 255));
			Graphics_SLP->SetBackgroundColour(wxColour(210, 230, 255));
		}

		// Mickey ->
		show = (GenieVersion >= genie::GV_MIK) ? true : false;
		Civs_TechTree_Holder->Show(show);
		Units_PlacementBypassTerrain_Holder->Show(show);

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
		Units_Unknown6_Holder->Show(show);
		Units_Unknown7_Holder->Show(show);
		Units_Unknown8_Holder->Show(show);
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

		// AoE ->
		show = (GenieVersion >= genie::GV_AoE) ? true : false;
		Units_ID2_Holder->Show(show);

		// AoK Alfa ->
		show = (GenieVersion >= genie::GV_AoKA) ? true : false;
		for(short loop = 4; loop < 6; ++loop)
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
		Units_MissileGraphicDelay_Holder->Show(show);
		Units_AttackMissileDuplicationAmount1_Holder->Show(show);
		Units_AttackMissileDuplicationAmount2_Holder->Show(show);
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
		TerRestrict_Unknown1_Holder->Show(show);
		TerRestrict_Graphics_Holder->Show(show);
		TerRestrict_Amount_Holder->Show(show);
		SoundItems_Civ_Holder->Show(show);
		Colors_Palette_Holder->Show(show);
		Colors_MinimapColor_Holder->Show(show);
		TechTrees_Main->Show(show);
		TabBar_Main->SetPageText(2, show ? "Tech Trees" : "AoK+ only");
		if(!show || ShowUnknowns)
		{
			Units_Type70plusUnknownArea_Holder->Show(show);
			Units_Unknown33_Holder->Show(show);
			Units_Unknown35_Holder->Show(show);
			Units_PileUnit_Holder->Show(show);
			SoundItems_Unknown_Holder->Show(show);
			Colors_UnknownArea_Holder->Show(show);
		}

		// AoE & RoR
		Colors_Name_Holder->Show(!show);

		if(show) // AoK Alfa ->
		{
			Colors_ColorL->SetBackgroundColour(wxColour(215, 255, 255));
		}
		else // <- RoR
		{
			Colors_ColorL->SetBackgroundColour(wxColour(210, 230, 255));
		}

		// AoK Beta ->
		show = (GenieVersion >= genie::GV_AoKB) ? true : false;
		Units_HeroMode_Holder->Show(show);
		Units_GarrisonGraphic_Holder->Show(show);
		Units_StandingGraphic[1]->Show(show);
		Units_StandingGraphic_ComboBox[1]->Show(show);
		Units_AccuracyErrorRadius_Holder->Show(show);
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
			Units_Unknown16B_Holder->Show(show);
			Graphics_Unknown3_Holder->Show(show);
		}

		// AoK ->
		show = (GenieVersion >= genie::GV_AoK) ? true : false;
		Units_Exists_Holder->Show(show);
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
			Units_DefaultArmor->SetBackgroundColour(wxColour(210, 230, 255));
		}
		else // <- AoK
		{
			Units_DefaultArmor->SetBackgroundColour(wxColour(255, 235, 215));
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
			Graphics_Name->SetMaxSize(25);
			Graphics_Name2->SetMaxSize(25);
			SoundItems_Name->SetMaxSize(27);
			Terrains_Name->SetMaxSize(17);
			Terrains_Name2->SetMaxSize(17);
		}
		else // <- TC
		{
			Graphics_Name->SetMaxSize(21);
			Graphics_Name2->SetMaxSize(13);
			SoundItems_Name->SetMaxSize(13);
			Terrains_Name->SetMaxSize(13);
			Terrains_Name2->SetMaxSize(13);
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
	Units_Scroller->GetSizer()->FitInside(Units_Scroller);
	Research_Scroller->GetSizer()->FitInside(Research_Scroller);
	TechTrees_ScrollerAges->GetSizer()->FitInside(TechTrees_ScrollerAges);
	TechTrees_ScrollerBuildings->GetSizer()->FitInside(TechTrees_ScrollerBuildings);
	TechTrees_ScrollerUnits->GetSizer()->FitInside(TechTrees_ScrollerUnits);
	TechTrees_ScrollerResearches->GetSizer()->FitInside(TechTrees_ScrollerResearches);
	Graphics_Scroller->GetSizer()->FitInside(Graphics_Scroller);
	Terrains_Scroller->GetSizer()->FitInside(Terrains_Scroller);
	General_Scroller->GetSizer()->FitInside(General_Scroller);
	Unknown_Scroller->GetSizer()->FitInside(Unknown_Scroller);
	Refresh(); // Does this refresh non-visible tabs?
}

void AGE_Frame::OnSave(wxCommandEvent &Event)
{
	wxCommandEvent Selected;

	AGE_SaveDialog SaveBox(this);
	SaveBox.Path_DatFileLocation->SetFocus();

	SaveBox.DriveLetterBox->ChangeValue(DriveLetter);
	SaveBox.CheckBox_CustomDefault->SetValue(UseCustomPath);
	SaveBox.Path_CustomDefault->SetPath(CustomFolder);
	SaveBox.LanguageBox->ChangeValue(Language);
	SaveBox.CheckBox_GenieVer->SetSelection(SaveGameVersion);

	SaveBox.CheckBox_DatFileLocation->SetValue(SaveDat);
	Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
	Selected.SetId(SaveBox.CheckBox_DatFileLocation->GetId());
	Selected.SetInt(SaveDat);
	SaveBox.GetEventHandler()->ProcessEvent(Selected);

	SaveBox.Path_DatFileLocation->SetPath(SaveDatFileName);

	SaveBox.CheckBox_ApfFileLocation->SetValue(SaveApf);
	Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
	Selected.SetId(SaveBox.CheckBox_ApfFileLocation->GetId());
	Selected.SetInt(SaveApf);
	SaveBox.GetEventHandler()->ProcessEvent(Selected);

	SaveBox.Path_ApfFileLocation->SetPath(SaveApfFileName);

	SaveBox.CheckBox_LangFileLocation->SetValue(LangsUsed & 1);
	Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
	Selected.SetId(SaveBox.CheckBox_LangFileLocation->GetId());
	Selected.SetInt(LangsUsed & 1);
	SaveBox.GetEventHandler()->ProcessEvent(Selected);

	SaveBox.CheckBox_LangX1FileLocation->SetValue(LangsUsed & 2);
	Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
	Selected.SetId(SaveBox.CheckBox_LangX1FileLocation->GetId());
	Selected.SetInt(LangsUsed & 2);
	SaveBox.GetEventHandler()->ProcessEvent(Selected);

	SaveBox.CheckBox_LangX1P1FileLocation->SetValue(LangsUsed & 4);
	Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
	Selected.SetId(SaveBox.CheckBox_LangX1P1FileLocation->GetId());
	Selected.SetInt(LangsUsed & 4);
	SaveBox.GetEventHandler()->ProcessEvent(Selected);

	SaveBox.Path_LangFileLocation->SetPath(SaveLangFileName);
	SaveBox.Path_LangX1FileLocation->SetPath(SaveLangX1FileName);
	SaveBox.Path_LangX1P1FileLocation->SetPath(SaveLangX1P1FileName);

	if(SaveBox.ShowModal() != wxID_OK) return;

	SaveGameVersion = SaveBox.CheckBox_GenieVer->GetSelection();
	SaveDat = SaveBox.CheckBox_DatFileLocation->IsChecked();
	SaveApf = SaveBox.CheckBox_ApfFileLocation->IsChecked();
	SaveLangs = SaveBox.CheckBox_LangWrite->IsChecked();

	SaveDatFileName = SaveBox.Path_DatFileLocation->GetPath();
	SaveApfFileName = SaveBox.Path_ApfFileLocation->GetPath();
	SaveLangFileName = SaveBox.Path_LangFileLocation->GetPath();
	SaveLangX1FileName = SaveBox.Path_LangX1FileLocation->GetPath();
	SaveLangX1P1FileName = SaveBox.Path_LangX1P1FileLocation->GetPath();

	if(SaveDat)
	{
		SetStatusText("Saving dat file...", 0);
		wxBusyCursor WaitCursor;

		try
		{
			GenieFile->saveAs(SaveDatFileName.c_str());
		}
		catch(std::ios_base::failure e)
		{
			wxMessageBox("Unable to save the file!");
			return;
		}
	}
	if(SaveApf)
	{
		//	 Not Implemented Yet = Nothing Happens
	}

	if(SaveLangs)
	{
		SetStatusText("Saving language files...", 0);
		wxBusyCursor WaitCursor;
		if(LangsUsed & 1)
		{
			try
			{
				Lang->saveAs(SaveLangFileName.c_str());
			}
			catch(std::ios_base::failure e)
			{
				wxMessageBox("Unable to save language file!");
				return;
			}
		}
		if(LangsUsed & 2)
		{
			try
			{
				LangX->saveAs(SaveLangX1FileName.c_str());
			}
			catch(std::ios_base::failure e)
			{
				wxMessageBox("Unable to save language expansion file!");
				return;
			}
		}
		if(LangsUsed & 4)
		{
			try
			{
				LangXP->saveAs(SaveLangX1P1FileName.c_str());
			}
			catch(std::ios_base::failure e)
			{
				wxMessageBox("Unable to save language expansion patch file!");
				return;
			}
		}
	}

	SetStatusText("Selected files saved.", 0);
}

void AGE_Frame::OnMenuOption(wxCommandEvent &Event)
{
	switch(Event.GetId())
	{
		case MenuOption_Prompt:
		{
			PromptForFilesOnOpen = Event.IsChecked();
		}
		break;
		case ToolBar_Show:
		{
			ShowUnknowns = Event.IsChecked();

			Units_UnknownArea_Holder->Show(ShowUnknowns);
			Units_CommandHolder_Grid3->Show(ShowUnknowns);
			Graphics_3_Grid->Show(ShowUnknowns);
			Graphics_Deltas_Grid_Data2->Show(ShowUnknowns);
			Terrains_Unknowns1_Grid->Show(ShowUnknowns);
			Terrains_Unknown7_Holder->Show(ShowUnknowns);
			Borders_Unknonws->Show(ShowUnknowns);
			Sounds_Unknown1_Holder->Show(ShowUnknowns);
			Sounds_Unknown2_Holder->Show(ShowUnknowns);
			SoundItems_Unknown_Holder->Show(ShowUnknowns);
			Colors_UnknownArea_Holder->Show(ShowUnknowns);
			General_TopRow->Show(ShowUnknowns);
			General_ScrollSpace->Show(ShowUnknowns);

			OnGameVersionChange(); // Does layouting and refreshing and ... check it out.
		}
		break;
		case MenuOption_Buttons:
		{
			ShowButtons = Event.IsChecked();

			Terrains_Add->Enable(ShowButtons);
			Terrains_Insert->Enable(ShowButtons);
			Terrains_Delete->Enable(ShowButtons);
			Terrains_PasteInsert->Enable(ShowButtons);
		}
		break;
		case wxID_EXIT:
		{
			Close(true);
		}
		break;
		case MenuOption_Tips:
		{
			wxString TipText;
			TipText.Append("You can have multiple search entries separated with \"|\" letter.\n");
			TipText.Append("Upper search boxes are inclusive and lower ones exclusive.\n");
			TipText.Append("Example: \"tower|ship|ram\"\n");
			TipText.Append("You can switch from \"or\" finding to \"and\" finding with check boxes.\n");
			TipText.Append("Meaning that every search entry has to match.\n");
			wxMessageBox(TipText, "Tips");
		}
		break;
		case MenuOption_About:
		{
			AGE_AboutDialog AGEAbout(this);
			AGEAbout.ShowModal();
		}
		break;
		/*case MenuOption_IDFix:
		{
			EnableIDFix = Event.IsChecked();
			wxMessageBox("Please restart this program.\nI do not recommend disabling index fixes!");
		}
		break;*/
		case ToolBar_Help:
		{
			//AGE_HelpInfo AGEHelp(this);
			//AGEHelp.ShowModal();
			wxString help = "ATTENTION!\nChanges to editing boxes affect all selected items!\n";
			help.Append("Click \"Help\" from the toolbar to see this again.\n\n");
			help.Append("Here are examples which cover all the nice features.\n");
			help.Append("(This is assuming that you edit Age of Empires II: The Conquerors)\n\n");
			help.Append("Advanced Searching\n\n");
			help.Append("Let's suppose that you want to edit buildings (type 80) of class 3,\n");
			help.Append("but not camps nor houses or yurts.\n");
			help.Append("See the two combo boxes having \"Lang DLL Name\" selected by default?\n");
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
			help.Append("On the open dialog, you must put \"2\" into \"Windows to open\"!\n");
			help.Append("Now that you have a second window titled \"AGE window 2\" open with a dat file, ");
			help.Append("let's begin the copying.\n");
			help.Append("(You can copy to another game version if you dare.)\n");
			help.Append("On the first window, select all the ships (search for \"ship\").\n");
			help.Append("Then click copy and go to the second window.\n");
			help.Append("Then click paste or paste insert wherever you want the ships.\n");
			help.Append("That's it.");
			/*help.Append("\n\nFor Discovering Unknowns\n");
			help.Append("\nBlue Boxes (16 bit integers)\n");
			help.Append("If 256 does something, the box might need to be split\n");
			help.Append("into two orange boxes (8 bit integers).\n");
			help.Append("\nLight Blue Boxes (32 bit integers)\n");
			help.Append("If 256, 65536 or 16777216 does something,\nthe box might need to be split\n");
			help.Append("into four orange boxes (8 bit integers)\n");
			help.Append("or into two blue boxes (16 bit integers)\n");
			help.Append("or into two orange boxes and one blue box.");*/
			wxMessageBox(help, "Short Guide to Advanced Editing");
		}
		break;
		case ToolBar_Hex:
		{
			AGETextCtrl::hexMode = Event.IsChecked();
		}
		break;
		case ToolBar_Float:
		{
			AGETextCtrl::accurateFloats = Event.IsChecked();
		}
		break;
		default: wxMessageBox(lexical_cast<string>(Event.GetId()), "wxEvent error!");
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

string AGE_Frame::LangDLLstring(int ID, int Letters)
{
	if(ID < 0) return "";
	string Result = "";
	if(sizeof(size_t) > 4 || WriteLangs)
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
	return Result;
}

void AGE_Frame::OnKillFocus_LangDLL(wxFocusEvent &Event)
{
	TextCtrl_DLL *control = (TextCtrl_DLL*)Event.GetEventObject();
	if(!control->IsModified() || !WriteLangs || control->index < 0) return;
	int ID = control->index;
	string Name = string(control->GetValue());
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
	control->DiscardEdits();
	Event.Skip();
}

bool AGE_Frame::SearchMatches(wxString itemText)
{
	// Make this so that no strings are altered! Easy ways?
	bool matches = false;

	// If there is no search text, list normally
	// If search text has a match
	if(searchText.empty() || (itemText.find(searchText) != string::npos))
	{
		matches = true;
	}
	else
	{
		size_t found = searchText.find("|");
		if(found != string::npos)
		{
			size_t pos = 0;
			if(useAnd[0]) // All search parts must match
			{
				matches = true;
				while(1)
				{
					if(itemText.find(searchText.substr(pos, found-pos)) == string::npos)
					{
						matches = false;
						break;
					}
					if(found == string::npos) break;
					pos = found+1;
					found = searchText.find("|", pos);
				}
			}
			else // Only one match needed
			{
				while(1)
				{
					if(itemText.find(searchText.substr(pos, found-pos)) != string::npos)
					{
						matches = true;
						break;
					}
					if(found == string::npos) break;
					pos = found+1;
					found = searchText.find("|", pos);
				}
			}
		}
	}

	// We don't need to check for excluding if it's not going to be listed.
	// If there is no exclude text, list normally.
	// If exclude text has a match.
	if(!matches || excludeText.empty()) return matches;
	if(itemText.find(excludeText) != string::npos)
	{
		matches = false;
	}
	else
	{
		size_t found = excludeText.find("|");
		if(found != string::npos)
		{
			size_t pos = 0;
			if(useAnd[1]) // All search parts must match
			{
				matches = false;
				while(1)
				{
					if(itemText.find(excludeText.substr(pos, found-pos)) == string::npos)
					{
						matches = true;
						break;
					}
					if(found == string::npos) break;
					pos = found+1;
					found = excludeText.find("|", pos);
				}
			}
			else // Only one match needed
			{
				while(1)
				{
					if(itemText.find(excludeText.substr(pos, found-pos)) != string::npos)
					{
						matches = false;
						break;
					}
					if(found == string::npos) break;
					pos = found+1;
					found = excludeText.find("|", pos);
				}
			}
		}
	}

	return matches;
}

//	Following kill focuses are used to update lists in user interface

void AGE_Frame::OnSelection_SearchFilters(wxCommandEvent &Event)
{
	for(short loop = 0; loop < 2; ++loop) // Custom search filters
	{
		if(Event.GetId() == Units_SearchFilters[loop]->GetId())
		{
			ListUnits(UnitCivID, false);
			Units_Search->SetFocus();
		}
		else if(Event.GetId() == Graphics_Graphics_SearchFilters[loop]->GetId())
		{
			ListGraphics(false);
			Graphics_Graphics_Search->SetFocus();
		}
		else if(Event.GetId() == TechTrees_MainList_Units_SearchFilters[loop]->GetId())
		{
			ListTTUnits();
			TechTrees_MainList_Units_Search->SetFocus();
		}
		else if(Event.GetId() == TechTrees_MainList_Buildings_SearchFilters[loop]->GetId())
		{
			ListTTBuildings();
			TechTrees_MainList_Buildings_Search->SetFocus();
		}
		else if(Event.GetId() == TechTrees_MainList_Researches_SearchFilters[loop]->GetId())
		{
			ListTTResearches();
			TechTrees_MainList_Researches_Search->SetFocus();
		}
		else if(Event.GetId() == Research_Research_SearchFilters[loop]->GetId())
		{
			ListResearches(false);
			Research_Research_Search->SetFocus();
		}
		else if(Event.GetId() == Sounds_Items_SearchFilters[loop]->GetId())
		{
			ListSoundItems();
			Sounds_Items_Search->SetFocus();
		}
	}
}

void AGE_Frame::Listing(wxListBox* &List, wxArrayString &names, list<void*> &data)
{
	int selections = List->GetSelections(Items);
	chrono::time_point<chrono::system_clock> startTime = chrono::system_clock::now();
	List->Set(names);
	bool showTime = ((chrono::duration_cast<chrono::milliseconds>(startTime - endTime)).count() > 1000) ? true : false;
	endTime = chrono::system_clock::now();
	auto it = data.begin();
	for(short loop = 0; loop < List->GetCount(); ++loop)
	{
		List->SetClientData(loop, *it++);
	}
	if(showTime)
	SetStatusText("Re-listing time: "+lexical_cast<string>((chrono::duration_cast<chrono::milliseconds>(endTime - startTime)).count())+" ms", 1);

	if(selections == 0)
	{
		List->SetSelection(0);
		return;
	}
	if(Added || Items.Item(0) >= List->GetCount())
	{
		List->SetFirstItem(List->GetCount() - 1);
		List->SetSelection(List->GetCount() - 1);
		Added = false;
		return;
	}
	List->SetFirstItem(Items.Item(0) - 3);
	List->SetSelection(Items.Item(0));
}

void AGE_Frame::FillLists(list<ComboBox_Plus1*> &boxlist, wxArrayString &names)
{
	for(ComboBox_Plus1* &list: boxlist)
	{
		int selection = list->GetSelection();
		list->Clear();
		list->Append("-1 - None");
		list->Append(names);
		list->SetSelection(selection);
	}
}

void AGE_AreaTT84::FillItemCombo(int selection, bool update)
{
	if(Mode->container.size() == 0) return;
	int oldList = lastList;
	lastList = *(int32_t*)Mode->container[0];
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

void AGE_Frame::SearchAllSubVectors(wxListBox* &List, wxTextCtrl* &TopSearch, wxTextCtrl* &SubSearch)
{
	int selections = List->GetSelections(Items);
	if(selections < 1) return;

	wxString TopText, SubText, Line;
	size_t found;
	for(int loop = 0; loop < selections; ++loop)
	{
		Line = List->GetString(Items.Item(loop));
		found = Line.find(" ", 3);
		if(loop == 0)
		{
			TopText = " "+Line.substr(2, found-1)+"-"; // Cutting the tech number. (for example)
			SubText = " "+Line.substr(found+2, Line.find(" ", found+3)-found-1)+"-"; // Cutting the effect number.
		}
		else
		{
			TopText += "| "+Line.substr(2, found-1)+"-"; // Cutting the sound number.
			SubText += "| "+Line.substr(found+2, Line.find(" ", found+3)-found-1)+"-"; // Cutting the filename.
		}
		TopSearch->SetValue(TopText);
		SubSearch->SetValue(SubText);
	}
}

wxString AGE_Frame::FormatFloat(float value)
{
	if(AGETextCtrl::accurateFloats)
	return lexical_cast<string>(value);

	stringbuf buffer;
	ostream os (&buffer);
	os << value;
	return buffer.str();
}

void AGE_Frame::OnExit(wxCloseEvent &Event)
{
	Config = new wxFileConfig(wxEmptyString, "Tapsa", "age2configw"+lexical_cast<string>(AGEwindow)+".ini", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	Config->Write("/EditorVersion", AGE_AboutDialog::AGE_VER);
	Config->Write("/TimesOpened", ++TimesOpened);
	Config->Write("Interaction/PromptForFilesOnOpen", PromptForFilesOnOpen);
	Config->Write("Interaction/AutoCopy", AutoCopy);
	Config->Write("Interaction/CopyGraphics", CopyGraphics);
	Config->Write("Interaction/AllCivs", Units_SpecialCopy_Civs->GetValue());
	Config->Write("Interaction/EnableIDFix", EnableIDFix);
	Config->Write("Interface/ShowUnknowns", ShowUnknowns);
	Config->Write("Interface/ShowButtons", ShowButtons);
	if(AGEwindow == 1) Config->Write("DefaultFiles/SimultaneousFiles", SimultaneousFiles);
	Config->Write("DefaultFiles/DriveLetter", DriveLetter);
	Config->Write("DefaultFiles/UseCustomPath", UseCustomPath);
	Config->Write("DefaultFiles/CustomFolder", CustomFolder);
	Config->Write("DefaultFiles/Version", GameVersion);
	Config->Write("DefaultFiles/SaveVersion", SaveGameVersion);
	Config->Write("DefaultFiles/DatUsed", DatUsed);
	Config->Write("DefaultFiles/DatFilename", DatFileName);
	Config->Write("DefaultFiles/ApfFilename", ApfFileName);
	Config->Write("DefaultFiles/SaveDatFilename", SaveDatFileName);
	Config->Write("DefaultFiles/SaveApfFilename", SaveApfFileName);
	Config->Write("DefaultFiles/LangsUsed", LangsUsed);
	Config->Write("DefaultFiles/WriteLangs", WriteLangs);
	Config->Write("DefaultFiles/SaveLangs", SaveLangs);
	Config->Write("DefaultFiles/LangWriteToLatest", LangWriteToLatest);
	Config->Write("DefaultFiles/Language", Language);
	Config->Write("DefaultFiles/LangCharset", LangCharset);
	Config->Write("DefaultFiles/LangFilename", LangFileName);
	Config->Write("DefaultFiles/LangX1Filename", LangX1FileName);
	Config->Write("DefaultFiles/LangX1P1Filename", LangX1P1FileName);
	Config->Write("DefaultFiles/SaveLangFilename", SaveLangFileName);
	Config->Write("DefaultFiles/SaveLangX1Filename", SaveLangX1FileName);
	Config->Write("DefaultFiles/SaveLangX1P1Filename", SaveLangX1P1FileName);
	Config->Write("DefaultFiles/SaveDat", SaveDat);
	Config->Write("DefaultFiles/SaveApf", SaveApf);
	delete Config;

	TabBar_Main->Destroy();

	delete GenieFile;
	if(WriteLangs)
	{
		delete Lang;
		delete LangX;
		delete LangXP;
	}

	Destroy();
}
