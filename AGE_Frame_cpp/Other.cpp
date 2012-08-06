/* AGEFrame_cpp/Other.cpp */

#include "../AGE_Frame.h"
using boost::lexical_cast;

void AGE_Frame::OnOpen(wxCommandEvent& Event)
{
//	int ErrCode = 0;
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
			case 1:
			{
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
			case 3:
			{
			}
			break;
		}

		OpenBox.DriveLetterBox->ChangeValue(DriveLetter);
		OpenBox.Path_DatFileLocation->SetPath(DatFileName);
		OpenBox.Path_ApfFileLocation->SetPath(ApfFileName);

		if(LangsUsed & 1)
		{
			OpenBox.CheckBox_LangFileLocation->SetValue(true);
			Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
			Selected.SetId(OpenBox.CheckBox_LangFileLocation->GetId());
			Selected.SetInt(true);
			OpenBox.GetEventHandler()->ProcessEvent(Selected);
		}
		else
		{
			OpenBox.CheckBox_LangFileLocation->SetValue(false);
			Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
			Selected.SetId(OpenBox.CheckBox_LangFileLocation->GetId());
			Selected.SetInt(false);
			OpenBox.GetEventHandler()->ProcessEvent(Selected);
		}
		if(LangsUsed & 2)
		{
			OpenBox.CheckBox_LangX1FileLocation->SetValue(true);
			Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
			Selected.SetId(OpenBox.CheckBox_LangX1FileLocation->GetId());
			Selected.SetInt(true);
			OpenBox.GetEventHandler()->ProcessEvent(Selected);
		}
		else
		{
			OpenBox.CheckBox_LangX1FileLocation->SetValue(false);
			Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
			Selected.SetId(OpenBox.CheckBox_LangX1FileLocation->GetId());
			Selected.SetInt(false);
			OpenBox.GetEventHandler()->ProcessEvent(Selected);
		}
		if(LangsUsed & 4)
		{
			OpenBox.CheckBox_LangX1P1FileLocation->SetValue(true);
			Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
			Selected.SetId(OpenBox.CheckBox_LangX1P1FileLocation->GetId());
			Selected.SetInt(true);
			OpenBox.GetEventHandler()->ProcessEvent(Selected);
		}
		else
		{
			OpenBox.CheckBox_LangX1P1FileLocation->SetValue(false);
			Selected.SetEventType(wxEVT_COMMAND_CHECKBOX_CLICKED);
			Selected.SetId(OpenBox.CheckBox_LangX1P1FileLocation->GetId());
			Selected.SetInt(false);
			OpenBox.GetEventHandler()->ProcessEvent(Selected);
		}

		OpenBox.Path_LangFileLocation->SetPath(LangFileName);
		OpenBox.Path_LangX1FileLocation->SetPath(LangX1FileName);
		OpenBox.Path_LangX1P1FileLocation->SetPath(LangX1P1FileName);

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
	}

	if(LangsUsed & 1)
	{
		LanguageDll[0] = LoadLibrary(LangFileName.c_str());
	}
	if(LangsUsed & 2)
	{
		LanguageDll[1] = LoadLibrary(LangX1FileName.c_str());
	}
	if(LangsUsed & 4)
	{
		LanguageDll[2] = LoadLibrary(LangX1P1FileName.c_str());
	}

	genie::GameVersion GenieVersion;
	switch(GameVersion)
	{
		case 0:
			GenieVersion = genie::GV_AoE;
			break;
		case 1:
			GenieVersion = genie::GV_RoR;
			break;
		case 2:
			GenieVersion = genie::GV_AoK;
			break;
		case 3:
			GenieVersion = genie::GV_TC;
			break;
		case 4:
			GenieVersion = genie::GV_SWGB;
			break;
		case 5:
			GenieVersion = genie::GV_CC;
			break;
		default:
		GenieVersion = genie::GV_None;
	}

	switch(DatUsed)
	{
		case 0:
		{
			if(GenieFile != NULL)
			{
				delete GenieFile;
				GenieFile = NULL;
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
					delete GenieFile;
					GenieFile = NULL;
					wxMessageBox("Unable to load the file!");
					return;
				}
			}
		}
		break;
		case 2:
		{

		}
		break;
	}

	if(GenieFile != NULL)
	{	// Without these, nothing can be edited.
		SetStatusText("Listing...", 0);
		wxBusyCursor WaitCursor;
		//wxMessageBox("Started to open the file!");
		//Units_Civs_List->SetSelection(0);

//		No research gaia fix
		for(short loop = 0;loop < GenieFile->Civs[0].Units.size();loop++)
			GenieFile->Civs[0].Units[loop].Enabled = GenieFile->Civs[1].Units[loop].Enabled;
//		ID and pointer fixes
		for(short loop = 0;loop < GenieFile->Civs.size();loop++)
		{
			for(short loop2 = 0;loop2 < GenieFile->Civs[loop].Units.size();loop2++)
			{
				if(GenieFile->Civs[loop].UnitPointers[loop2] != 0)
				{
					GenieFile->Civs[loop].UnitPointers[loop2] = lexical_cast<long>(1);
					if(EnableIDFix)
					{
						GenieFile->Civs[loop].Units[loop2].ID1 = lexical_cast<short>(loop2);
						GenieFile->Civs[loop].Units[loop2].ID2 = lexical_cast<short>(loop2);
						if(GameVersion >= 2)
						GenieFile->Civs[loop].Units[loop2].ID3 = lexical_cast<short>(loop2);
						else
						if(GenieFile->Civs[loop].Units[loop2].Type >= 40 && GenieFile->Civs[loop].Units[loop2].Type <= 80)
						for(short loop3 = 0;loop3 < GenieFile->Civs[loop].Units[loop2].Bird.Commands.size();loop3++)
						GenieFile->Civs[loop].Units[loop2].Bird.Commands[loop3].ID = lexical_cast<short>(loop3);
					}
				}
			}
			//if(loop > 0)
			//for(short loop2 = 0;loop2 < GenieFile->Civs[loop].Resources.size();loop2++)
			//if(loop2 != 82)
			//if(GenieFile->Civs[loop].Resources[loop2] == 0)
			//GenieFile->Civs[loop].Resources[loop2] = lexical_cast<float>(1);
		}
		if(EnableIDFix)
		{
			for(short loop = 0;loop < GenieFile->PlayerColours.size();loop++)
			{
				GenieFile->PlayerColours[loop].ID = lexical_cast<long>(loop);
			}
			for(short loop = 0;loop < GenieFile->Sounds.size();loop++)
			{
				GenieFile->Sounds[loop].ID = lexical_cast<long>(loop);
			}
			if(GameVersion >= 4)
			for(short loop = 0;loop < GenieFile->UnitLines.size();loop++)
			{
				GenieFile->UnitLines[loop].ID = lexical_cast<short>(loop);
			}
		}
		for(short loop = 0;loop < GenieFile->Graphics.size();loop++)
		{
			if(GenieFile->GraphicPointers[loop] != 0)
			{
				GenieFile->GraphicPointers[loop] = lexical_cast<long>(1);
				if(EnableIDFix)
				GenieFile->Graphics[loop].ID = lexical_cast<short>(loop);
			}
		}
		for(short loop = 0;loop < GenieFile->TerrainRestrictions.size();loop++)
		{
			if(GenieFile->TerrainRestrictionPointers1[loop] != 0)
			GenieFile->TerrainRestrictionPointers1[loop] = lexical_cast<long>(1);
			if(GameVersion >= 2)
			if(GenieFile->TerrainRestrictionPointers2[loop] != 0)
			GenieFile->TerrainRestrictionPointers2[loop] = lexical_cast<long>(1);
		}

		Added = false;

		if(UnitCommands_ComboBox_Types->GetCount() > 0)
		{
			UnitCommands_ComboBox_Types->Clear();
		}
		UnitCommands_ComboBox_Types->Append("Unused Ability/Invalid Ability");	// Selection 0
		UnitCommands_ComboBox_Types->Append("Ability to Garrison");	// Selection 1
		UnitCommands_ComboBox_Types->Append("Ability to Mine Gold");
		UnitCommands_ComboBox_Types->Append("Ability to Mine Stone");
		UnitCommands_ComboBox_Types->Append("Ability to Fish, Forage, or Farm");
		UnitCommands_ComboBox_Types->Append("Ability to Rebuild");
		UnitCommands_ComboBox_Types->Append("Unknown Animal Ability");
		UnitCommands_ComboBox_Types->Append("Ability to Attack");
		UnitCommands_ComboBox_Types->Append("Ability to Fly");
		UnitCommands_ComboBox_Types->Append("Unknown Predator Animal Ability");
		UnitCommands_ComboBox_Types->Append("Ability to Unload (Boat-Like)");
		UnitCommands_ComboBox_Types->Append("Ability to Auto-Attack");
		UnitCommands_ComboBox_Types->Append("Unknown Farm Ability");
		UnitCommands_ComboBox_Types->Append("Ability to Build");
		UnitCommands_ComboBox_Types->Append("Ability to Convert");
		UnitCommands_ComboBox_Types->Append("Ability to Heal");
		UnitCommands_ComboBox_Types->Append("Ability to Repair");
		UnitCommands_ComboBox_Types->Append("Ability to Get Auto-converted?");
		UnitCommands_ComboBox_Types->Append("Type 109, Sub -1");
		UnitCommands_ComboBox_Types->Append("Ability to Chop Wood");
		UnitCommands_ComboBox_Types->Append("Ability to Hunt Prey Animals");
		UnitCommands_ComboBox_Types->Append("Ability to Hunt Predator Animals");
		UnitCommands_ComboBox_Types->Append("Ability to Trade");
		UnitCommands_ComboBox_Types->Append("Ability to Generate Wonder Victory*");
		UnitCommands_ComboBox_Types->Append("Type 121, Sub -1");
		UnitCommands_ComboBox_Types->Append("Ability to Mine Porex (Ore)");
		UnitCommands_ComboBox_Types->Append("Ability to Unpack & Attack");
		UnitCommands_ComboBox_Types->Append("Type 131, Sub -1");
		UnitCommands_ComboBox_Types->Append("Ability to Pickup Unit");
		UnitCommands_ComboBox_Types->Append("Type 135, Sub -1");
		UnitCommands_ComboBox_Types->Append("Ability to Deposit Unit");	// Selection 30
		UnitCommands_ComboBox_Types->SetSelection(0);

		if(Units_ComboBox_GarrisonType->GetCount() > 0)
		{
			Units_ComboBox_GarrisonType->Clear();
		}
		Units_ComboBox_GarrisonType->Append("No Type/Invalid Type");	// Selection 0
		if(GameVersion >= 2)
		{
			Units_ComboBox_GarrisonType->Append("0 - None");	// Selection 1
			Units_ComboBox_GarrisonType->Append("1 - Villager");
			Units_ComboBox_GarrisonType->Append("2 - Infantry");
			Units_ComboBox_GarrisonType->Append("3 - Villager + Infantry");
			Units_ComboBox_GarrisonType->Append("4 - Cavalry");
			Units_ComboBox_GarrisonType->Append("5 - Cavalry + Villager");
			Units_ComboBox_GarrisonType->Append("6 - Cavalry + Infantry");
			Units_ComboBox_GarrisonType->Append("7 - Cavalry + Infantry + Villager");
			Units_ComboBox_GarrisonType->Append("8 - Monk");
			Units_ComboBox_GarrisonType->Append("9 - Monk + Villager");
			Units_ComboBox_GarrisonType->Append("10 - Monk + Infantry");
			Units_ComboBox_GarrisonType->Append("11 - Monk + Infantry + Villager");
			Units_ComboBox_GarrisonType->Append("12 - Monk + Cavalry");
			Units_ComboBox_GarrisonType->Append("13 - Monk + Villager + Cavalry");
			Units_ComboBox_GarrisonType->Append("14 - Monk + Cavalry + Infantry");
			Units_ComboBox_GarrisonType->Append("15 - Monk + Villager + Infantry + Cavalry");
		}
		else if(GameVersion >= 4)
		{
			Units_ComboBox_GarrisonType->Append("0 - None");	// Selection 1
			Units_ComboBox_GarrisonType->Append("1 - Worker");
			Units_ComboBox_GarrisonType->Append("2 - Infantry");
			Units_ComboBox_GarrisonType->Append("3 - Worker + Infantry");
			Units_ComboBox_GarrisonType->Append("4 - Mounted");
			Units_ComboBox_GarrisonType->Append("5 - Mounted + Worker");
			Units_ComboBox_GarrisonType->Append("6 - Mounted + Infantry");
			Units_ComboBox_GarrisonType->Append("7 - Mounted + Infantry + Worker");
			Units_ComboBox_GarrisonType->Append("8 - Jedi");
			Units_ComboBox_GarrisonType->Append("9 - Jedi + Worker");
			Units_ComboBox_GarrisonType->Append("10 - Jedi + Infantry");
			Units_ComboBox_GarrisonType->Append("11 - Jedi + Infantry + Worker");
			Units_ComboBox_GarrisonType->Append("12 - Jedi + Mounted");
			Units_ComboBox_GarrisonType->Append("13 - Jedi + Worker + Mounted");
			Units_ComboBox_GarrisonType->Append("14 - Jedi + Mounted + Infantry");
			Units_ComboBox_GarrisonType->Append("15 - Jedi + Worker + Infantry + Mounted");
		}
		Units_ComboBox_GarrisonType->SetSelection(0);

		Customs = new wxFileConfig("AGE Lists", wxEmptyString, "age2lists.ini", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
		long ExtraCount;
		Customs->Read("Count/ExtraCount", &ExtraCount, 5);
		wxString MoveHolder = "";
		for(short loop = 0;loop < 3;loop++)
		{
			if(Units_ComboBox_Class[loop]->GetCount() > 0)
			{
				Units_ComboBox_Class[loop]->Clear();
			}
			Units_ComboBox_Class[loop]->Append("No Class/Invalid Class");	// Selection 0
			if(GameVersion < 4)
			{
				Units_ComboBox_Class[loop]->Append("0 - Archer");	// Selection 1
				Units_ComboBox_Class[loop]->Append("1 - Artifact");
				Units_ComboBox_Class[loop]->Append("2 - Trade Boat");
				Units_ComboBox_Class[loop]->Append("3 - Building");
				Units_ComboBox_Class[loop]->Append("4 - Civilian");
				Units_ComboBox_Class[loop]->Append("5 - Sea Fish");
				Units_ComboBox_Class[loop]->Append("6 - Soldier");
				Units_ComboBox_Class[loop]->Append("7 - Berry Bush");
				Units_ComboBox_Class[loop]->Append("8 - Stone Mine");
				Units_ComboBox_Class[loop]->Append("9 - Prey Animal");
				Units_ComboBox_Class[loop]->Append("10 - Predator Animal");
				Units_ComboBox_Class[loop]->Append("11 - Other/Dead/Projectile");
				Units_ComboBox_Class[loop]->Append("12 - Cavalry");
				Units_ComboBox_Class[loop]->Append("13 - Siege Weapon");
				Units_ComboBox_Class[loop]->Append("14 - Terrain");
				Units_ComboBox_Class[loop]->Append("15 - Tree");
				Units_ComboBox_Class[loop]->Append("16 - Tree Stump");
				Units_ComboBox_Class[loop]->Append("17 - Unused");
				Units_ComboBox_Class[loop]->Append("18 - Priest");
				Units_ComboBox_Class[loop]->Append("19 - Trade Cart");
				Units_ComboBox_Class[loop]->Append("20 - Transport Boat");
				Units_ComboBox_Class[loop]->Append("21 - Fishing Boat");
				Units_ComboBox_Class[loop]->Append("22 - War Boat");
				Units_ComboBox_Class[loop]->Append("23 - Conquistador");
				Units_ComboBox_Class[loop]->Append("24 - War Elephant");
				Units_ComboBox_Class[loop]->Append("25 - Unused");
				Units_ComboBox_Class[loop]->Append("26 - Elephant Archer");
				Units_ComboBox_Class[loop]->Append("27 - Wall");
				Units_ComboBox_Class[loop]->Append("28 - Phalanx");
				Units_ComboBox_Class[loop]->Append("29 - Unused");
				Units_ComboBox_Class[loop]->Append("30 - Flag");
				Units_ComboBox_Class[loop]->Append("31 - Unused");
				Units_ComboBox_Class[loop]->Append("32 - Gold Mine");
				Units_ComboBox_Class[loop]->Append("33 - Shore Fish");
				Units_ComboBox_Class[loop]->Append("34 - Cliff");
				Units_ComboBox_Class[loop]->Append("35 - Petard/Chariot");
				Units_ComboBox_Class[loop]->Append("36 - Cavalry Archer");
				Units_ComboBox_Class[loop]->Append("37 - Dolphin/Smoke");
				Units_ComboBox_Class[loop]->Append("38 - Bird");
				Units_ComboBox_Class[loop]->Append("39 - Gate/Slinger");
				Units_ComboBox_Class[loop]->Append("40 - Pile");
				Units_ComboBox_Class[loop]->Append("41 - Pile of Resource");
				Units_ComboBox_Class[loop]->Append("42 - Relic");
				Units_ComboBox_Class[loop]->Append("43 - Monk with Relic");
				Units_ComboBox_Class[loop]->Append("44 - Hand Cannoneer");
				Units_ComboBox_Class[loop]->Append("45 - Two Handed Swordsman");
				Units_ComboBox_Class[loop]->Append("46 - Pikeman");
				Units_ComboBox_Class[loop]->Append("47 - Scout Cavalry");
				Units_ComboBox_Class[loop]->Append("48 - Ore Mine");
				Units_ComboBox_Class[loop]->Append("49 - Farm");
				Units_ComboBox_Class[loop]->Append("50 - Spearman");
				Units_ComboBox_Class[loop]->Append("51 - Packed Siege Unit");
				Units_ComboBox_Class[loop]->Append("52 - Tower");
				Units_ComboBox_Class[loop]->Append("53 - Boarding Boat");
				Units_ComboBox_Class[loop]->Append("54 - Unpacked Siege Unit");
				Units_ComboBox_Class[loop]->Append("55 - Scorpion");
				Units_ComboBox_Class[loop]->Append("56 - Raider");
				Units_ComboBox_Class[loop]->Append("57 - Cavalry Raider");
				Units_ComboBox_Class[loop]->Append("58 - Sheep");
				Units_ComboBox_Class[loop]->Append("59 - King");
				Units_ComboBox_Class[loop]->Append("60 - Unused");
				Units_ComboBox_Class[loop]->Append("61 - Horse");
			}
			else
			{
				Units_ComboBox_Class[loop]->Append("0 - Unused");	// Selection 1
				Units_ComboBox_Class[loop]->Append("1 - Nerf/Bantha");
				Units_ComboBox_Class[loop]->Append("2 - Fambaa");
				Units_ComboBox_Class[loop]->Append("3 - Unused");
				Units_ComboBox_Class[loop]->Append("4 - Wild Animal");
				Units_ComboBox_Class[loop]->Append("5 - Monster/Trouble");
				Units_ComboBox_Class[loop]->Append("6 - Wall");
				Units_ComboBox_Class[loop]->Append("7 - Farm");
				Units_ComboBox_Class[loop]->Append("8 - Gate");
				Units_ComboBox_Class[loop]->Append("9 - Fortress/A-A Turret");
				Units_ComboBox_Class[loop]->Append("10 - Turret");
				Units_ComboBox_Class[loop]->Append("11 - Cruiser");
				Units_ComboBox_Class[loop]->Append("12 - Unused");
				Units_ComboBox_Class[loop]->Append("13 - Destroyer");
				Units_ComboBox_Class[loop]->Append("14 - Utility Trawler");
				Units_ComboBox_Class[loop]->Append("15 - Frigate 1");
				Units_ComboBox_Class[loop]->Append("16 - A-A Destroyer 1");
				Units_ComboBox_Class[loop]->Append("17 - Transport Ship");
				Units_ComboBox_Class[loop]->Append("18 - Building");
				Units_ComboBox_Class[loop]->Append("19 - Doppleganger");
				Units_ComboBox_Class[loop]->Append("20 - Other/Dead/Projectile");
				Units_ComboBox_Class[loop]->Append("21 - Command Base");
				Units_ComboBox_Class[loop]->Append("22 - Cliff");
				Units_ComboBox_Class[loop]->Append("23 - Fish");
				Units_ComboBox_Class[loop]->Append("24 - Unused");
				Units_ComboBox_Class[loop]->Append("25 - Shore Fish");
				Units_ComboBox_Class[loop]->Append("26 - Game Engine Stuff");
				Units_ComboBox_Class[loop]->Append("27 - Fruit Bush");
				Units_ComboBox_Class[loop]->Append("28 - Holocron");
				Units_ComboBox_Class[loop]->Append("29 - Nova");
				Units_ComboBox_Class[loop]->Append("30 - Ore");
				Units_ComboBox_Class[loop]->Append("31 - Tree/Carbon");
				Units_ComboBox_Class[loop]->Append("32 - Artillery");
				Units_ComboBox_Class[loop]->Append("33 - A-A Mobile");
				Units_ComboBox_Class[loop]->Append("34 - Undeployed Cannon");
				Units_ComboBox_Class[loop]->Append("35 - Pummel");
				Units_ComboBox_Class[loop]->Append("36 - Cannon");
				Units_ComboBox_Class[loop]->Append("37 - Unused");
				Units_ComboBox_Class[loop]->Append("38 - Unused");
				Units_ComboBox_Class[loop]->Append("39 - Frigate 2");
				Units_ComboBox_Class[loop]->Append("40 - A-A Destroyer 2");
				Units_ComboBox_Class[loop]->Append("41 - Unused");
				Units_ComboBox_Class[loop]->Append("42 - Bridge/Eye Candy");
				Units_ComboBox_Class[loop]->Append("43 - Bomber");
				Units_ComboBox_Class[loop]->Append("44 - Bounty Hunter");
				Units_ComboBox_Class[loop]->Append("45 - Cargo Trader");
				Units_ComboBox_Class[loop]->Append("46 - Mixed 1");
				Units_ComboBox_Class[loop]->Append("47 - Scout");
				Units_ComboBox_Class[loop]->Append("48 - Fighter");
				Units_ComboBox_Class[loop]->Append("49 - Grenade Trooper");
				Units_ComboBox_Class[loop]->Append("50 - Jedi");
				Units_ComboBox_Class[loop]->Append("51 - Jedi with Holocron");
				Units_ComboBox_Class[loop]->Append("52 - Trooper");
				Units_ComboBox_Class[loop]->Append("53 - War Machine");
				Units_ComboBox_Class[loop]->Append("54 - Medic");
				Units_ComboBox_Class[loop]->Append("55 - A-A Trooper");
				Units_ComboBox_Class[loop]->Append("56 - Mounted Trooper");
				Units_ComboBox_Class[loop]->Append("57 - Fambaa Shield Generator");
				Units_ComboBox_Class[loop]->Append("58 - Workers");
				Units_ComboBox_Class[loop]->Append("59 - Air Transport");
				Units_ComboBox_Class[loop]->Append("60 - Horse-like Animal");
				Units_ComboBox_Class[loop]->Append("61 - Power Droid");
				Units_ComboBox_Class[loop]->Append("62 - Air Cruiser");
				Units_ComboBox_Class[loop]->Append("63 - Geonosian Warrior");
				Units_ComboBox_Class[loop]->Append("64 - Jedi Starfighter");
			}
			Units_ComboBox_Class[loop]->SetSelection(0);

			if(Attacks_ComboBox_Class[loop]->GetCount() > 0)
			{
				Attacks_ComboBox_Class[loop]->Clear();
			}
			Attacks_ComboBox_Class[loop]->Append("Unused Class/No Class");	// Selection 0
			if(GameVersion < 4)
			{
				Attacks_ComboBox_Class[loop]->Append("0 - Unused");
				Attacks_ComboBox_Class[loop]->Append("1 - Infantry");	// Selection 2
				Attacks_ComboBox_Class[loop]->Append("2 - Turtle Ships");
				Attacks_ComboBox_Class[loop]->Append("3 - Base Pierce");
				Attacks_ComboBox_Class[loop]->Append("4 - Base Melee");
				Attacks_ComboBox_Class[loop]->Append("5 - War Elephants");
				Attacks_ComboBox_Class[loop]->Append("6 - Unused");
				Attacks_ComboBox_Class[loop]->Append("7 - Unused");
				Attacks_ComboBox_Class[loop]->Append("8 - Cavalry");
				Attacks_ComboBox_Class[loop]->Append("9 - Unused");
				Attacks_ComboBox_Class[loop]->Append("10 - Unused");
				Attacks_ComboBox_Class[loop]->Append("11 - All Buildings (except Port)");
				Attacks_ComboBox_Class[loop]->Append("12 - Unused");
				Attacks_ComboBox_Class[loop]->Append("13 - Stone Defense");
				Attacks_ComboBox_Class[loop]->Append("14 - Unused");
				Attacks_ComboBox_Class[loop]->Append("15 - Archers");
				Attacks_ComboBox_Class[loop]->Append("16 - Ships & Camels & Saboteurs");
				Attacks_ComboBox_Class[loop]->Append("17 - Rams");
				Attacks_ComboBox_Class[loop]->Append("18 - Trees");
				Attacks_ComboBox_Class[loop]->Append("19 - Unique Units (except Turtle Ship)");
				Attacks_ComboBox_Class[loop]->Append("20 - Siege Weapons");
				Attacks_ComboBox_Class[loop]->Append("21 - Standard Buildings");
				Attacks_ComboBox_Class[loop]->Append("22 - Walls & Gates");
				Attacks_ComboBox_Class[loop]->Append("23 - Unused");
				Attacks_ComboBox_Class[loop]->Append("24 - Boars");
				Attacks_ComboBox_Class[loop]->Append("25 - Monks");
				Attacks_ComboBox_Class[loop]->Append("26 - Castle");
				Attacks_ComboBox_Class[loop]->Append("27 - Spearmen");
				Attacks_ComboBox_Class[loop]->Append("28 - Cavalry Archers");
				Attacks_ComboBox_Class[loop]->Append("29 - Eagle Warriors");
				Attacks_ComboBox_Class[loop]->Append("30 - Unused");	// Selection 31
			}
			else	// SWGB and CC
			{
				Attacks_ComboBox_Class[loop]->Append("0 - Aircraft");	// Selection 1
				// Airspeeder
				// AIR SHIPS!!!
				// Geonosian Warrior
				// Wild Gungan Flyer
				Attacks_ComboBox_Class[loop]->Append("1 - Heavy Assault Machines");	// Selection 2
				// Assault Mech
				// AT-AT
				// Blizzards
				Attacks_ComboBox_Class[loop]->Append("2 - Heavy Weapons");
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
				Attacks_ComboBox_Class[loop]->Append("3 - Base Melee/Armor");
				Attacks_ComboBox_Class[loop]->Append("4 - Base Ranged/DuraArmor");
				Attacks_ComboBox_Class[loop]->Append("5 - Jedis & Bounty Hunters");
				// Jedi
				// Jedi with Holocron
				// Bounty Hunter
				Attacks_ComboBox_Class[loop]->Append("6 - Assault Machines");
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
				Attacks_ComboBox_Class[loop]->Append("7 - Decimators");
				// Assault Mechs
				// Decimator
				// AT-AT
				// Blizzards
				Attacks_ComboBox_Class[loop]->Append("8 - Shield & Power Units");
				// Power Cores
				// Shield Wall
				// Shield Generators
				// Droid Storage Facility
				// Power Droids
				// Echo Base Power Generator
				Attacks_ComboBox_Class[loop]->Append("9 - Ships");
				// Utility Trawler
				// Frigates
				// Cruisers
				// Destroyers
				// A-A Destroyers
				// Transport Ships
				Attacks_ComboBox_Class[loop]->Append("10 - Submarines");
				// Frigates
				// Underwater Prefab Shelters
				// Gungan Buildings
				Attacks_ComboBox_Class[loop]->Append("11 - All Buildings");
				// BUILDINGS!!!
				Attacks_ComboBox_Class[loop]->Append("12 - Unused");
				Attacks_ComboBox_Class[loop]->Append("13 - Defense Buildings");
				// Gate
				// Turrets
				// A-A Turrets
				// Echo Base Ion Cannon
				// Fortress
				// Theed Arch
				Attacks_ComboBox_Class[loop]->Append("14 - Troopers");
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
				Attacks_ComboBox_Class[loop]->Append("15 - Mounted Troopers");
				// Berserker
				// Scouts
				// Mounted Troopers
				// Anakin's Podracer
				// Landspeeder
				// Sebulba's Podracer
				// Skyhopper
				Attacks_ComboBox_Class[loop]->Append("16 - Cruisers");
				// Cruisers
				Attacks_ComboBox_Class[loop]->Append("17 - Pummels & Cannons");
				// Undeployed Cannon
				// Pummels
				// Cannon
				Attacks_ComboBox_Class[loop]->Append("18 - Unused");
				Attacks_ComboBox_Class[loop]->Append("19 - Workers");
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
				Attacks_ComboBox_Class[loop]->Append("20 - Destroyers");
				// Destroyers
				Attacks_ComboBox_Class[loop]->Append("21 - Standard Buildings");
				// BUILDINGS!!!
				Attacks_ComboBox_Class[loop]->Append("22 - Walls & Gates");
				// GATES
				// WALLS
				// Theed Arch
				Attacks_ComboBox_Class[loop]->Append("23 - Air Cruisers");
				// Air Cruisers
				// Blockade Runner
				// Star Destroyer
				// Deathstar
				Attacks_ComboBox_Class[loop]->Append("24 - Wild Animals");
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
				Attacks_ComboBox_Class[loop]->Append("25 - Unused");
				Attacks_ComboBox_Class[loop]->Append("26 - Fortress");
				// Fortress
				Attacks_ComboBox_Class[loop]->Append("27 - Unused");
				Attacks_ComboBox_Class[loop]->Append("28 - Unused");
				Attacks_ComboBox_Class[loop]->Append("29 - Unused");
				Attacks_ComboBox_Class[loop]->Append("30 - Tame Animals");	// Selection 31
				// Fambaa Shield Generators
				// Wild Fambaa
				// Kaadu
				// Tauntaun
				// Cu-pa
				// Womp Rat
			}
			//Well, if best APUs can run any game 1080p on lowest settings without considerable lag, I might consider buying one.
			for(short loop2 = 0;loop2 < ExtraCount;loop2++)
			{
				Customs->Read("Names/"+lexical_cast<string>(loop2+31), &MoveHolder, lexical_cast<string>(loop2+31)+" - Extra Class");
				Attacks_ComboBox_Class[loop]->Append(MoveHolder);
			}
			Attacks_ComboBox_Class[loop]->SetSelection(0);
		}
		delete Customs;

		for(short loop = 0;loop < 2;loop++)
		{
			if(Units_Units_SearchFilters[loop]->GetCount() > 0)
			{
				Units_Units_SearchFilters[loop]->Clear();
			}
			Units_Units_SearchFilters[loop]->Append("Lang DLL Name");	// 0
			Units_Units_SearchFilters[loop]->Append("Internal Name");
			Units_Units_SearchFilters[loop]->Append("Type");
			Units_Units_SearchFilters[loop]->Append("Class");
			Units_Units_SearchFilters[loop]->Append("Max Range");
			Units_Units_SearchFilters[loop]->Append("Train Location");
			Units_Units_SearchFilters[loop]->Append("Pointer");
		/*	Units_Units_SearchFilters[loop]->Append("Garrison Type");
			Units_Units_SearchFilters[loop]->Append("Projectile Unit");
			Units_Units_SearchFilters[loop]->Append("Enabled");
			Units_Units_SearchFilters[loop]->Append("Hidden In Editor");
			Units_Units_SearchFilters[loop]->Append("Visible In Fog");
			Units_Units_SearchFilters[loop]->Append("Death Mode");
			Units_Units_SearchFilters[loop]->Append("Hero Mode");
			Units_Units_SearchFilters[loop]->Append("Air Mode");
			Units_Units_SearchFilters[loop]->Append("Fly Mode");
			Units_Units_SearchFilters[loop]->Append("Building Mode");
			Units_Units_SearchFilters[loop]->Append("Placement Mode");
			Units_Units_SearchFilters[loop]->Append("Terrain Restriction");
			Units_Units_SearchFilters[loop]->Append("Interaction Mode");
			Units_Units_SearchFilters[loop]->Append("Minimap Mode");
			Units_Units_SearchFilters[loop]->Append("Sheep Conversion");
			Units_Units_SearchFilters[loop]->Append("Villager Mode");
			Units_Units_SearchFilters[loop]->Append("Unseletable");
			Units_Units_SearchFilters[loop]->Append("Selection Mask");
			Units_Units_SearchFilters[loop]->Append("Selection Shape Type");
			Units_Units_SearchFilters[loop]->Append("Selection Shape");
			Units_Units_SearchFilters[loop]->Append("Selection Effect");
			Units_Units_SearchFilters[loop]->Append("Editor Selection Color");
			Units_Units_SearchFilters[loop]->Append("Unitline");
			Units_Units_SearchFilters[loop]->Append("Tracking Unit Used");
			Units_Units_SearchFilters[loop]->Append("Command Attribute");
			Units_Units_SearchFilters[loop]->Append("Stack Unit");
			Units_Units_SearchFilters[loop]->Append("Terrain");
			Units_Units_SearchFilters[loop]->Append("Research");
		*/	Units_Units_SearchFilters[loop]->SetSelection(0);

			if(Research_Research_SearchFilters[loop]->GetCount() > 0)
			{
				Research_Research_SearchFilters[loop]->Clear();
			}
			Research_Research_SearchFilters[loop]->Append("Lang DLL Name");	// 0
			Research_Research_SearchFilters[loop]->Append("Internal Name");
			Research_Research_SearchFilters[loop]->Append("Research Location");
			if(GameVersion >= 2)
			{
				Research_Research_SearchFilters[loop]->Append("Civilization");
				Research_Research_SearchFilters[loop]->Append("Full Tech. Mode");
			}
			Research_Research_SearchFilters[loop]->SetSelection(0);
		}

		Items.Add(0);
		//wxMessageBox("Loaded!");
		if(GameVersion >= 2)
		{
			ListUnitHeads(Zero);	// This needs to happen before unit listing to avoid crash.
			ListTTAgess();
			ListTTBuildings();
			ListTTUnits();
			ListTTResearches();
		}
		else
		{
			if(Units_UnitHeads_List->GetCount() > 0)
			Units_UnitHeads_List->Clear();
			if(TechTrees_MainList_Ages_List->GetCount() > 0)
			TechTrees_MainList_Ages_List->Clear();
			if(TechTrees_DataList_Ages_List_Buildings->GetCount() > 0)
			TechTrees_DataList_Ages_List_Buildings->Clear();
			if(TechTrees_DataList_Ages_List_Units->GetCount() > 0)
			TechTrees_DataList_Ages_List_Units->Clear();
			if(TechTrees_DataList_Ages_List_Researches->GetCount() > 0)
			TechTrees_DataList_Ages_List_Researches->Clear();
			if(TechTrees_MainList_Buildings_List->GetCount() > 0)
			TechTrees_MainList_Buildings_List->Clear();
			if(TechTrees_DataList_Buildings_List_Buildings->GetCount() > 0)
			TechTrees_DataList_Buildings_List_Buildings->Clear();
			if(TechTrees_DataList_Buildings_List_Units->GetCount() > 0)
			TechTrees_DataList_Buildings_List_Units->Clear();
			if(TechTrees_DataList_Buildings_List_Researches->GetCount() > 0)
			TechTrees_DataList_Buildings_List_Researches->Clear();
			if(TechTrees_MainList_Units_List->GetCount() > 0)
			TechTrees_MainList_Units_List->Clear();
			if(TechTrees_DataList_Units_List_Units->GetCount() > 0)
			TechTrees_DataList_Units_List_Units->Clear();
			if(TechTrees_MainList_Researches_List->GetCount() > 0)
			TechTrees_MainList_Researches_List->Clear();
			if(TechTrees_DataList_Researches_List_Buildings->GetCount() > 0)
			TechTrees_DataList_Researches_List_Buildings->Clear();
			if(TechTrees_DataList_Researches_List_Units->GetCount() > 0)
			TechTrees_DataList_Researches_List_Units->Clear();
			if(TechTrees_DataList_Researches_List_Researches->GetCount() > 0)
			TechTrees_DataList_Researches_List_Researches->Clear();
		}
		ListCivs();
		ListUnits(Zero);
		if(GameVersion >= 4)
		{
			ListUnitLines();
		}
		else
		{
			if(UnitLines_UnitLines_List->GetCount() > 0)
			UnitLines_UnitLines_List->Clear();
			if(UnitLines_UnitLineUnits_List->GetCount() > 0)
			UnitLines_UnitLineUnits_List->Clear();
		}
		ListResearches();
		ListTechages();
		ListGraphics();
		ListSounds();
		ListTerrainRestrictions();
		ListTerrains();
		ListPlayerColors();
		ListTerrainBorders();
		ListGeneral();

		if(Effects_ComboBox_AttributesC->GetCount() > 0)
		{
			Effects_ComboBox_AttributesC->Clear();
		}
		Effects_ComboBox_AttributesC->Append("No Attribute/Invalid Attribute");		// Selection 0
		Effects_ComboBox_AttributesC->Append("0 - Hit Points");		// Selection 1
		Effects_ComboBox_AttributesC->Append("1 - Line of Sight");
		Effects_ComboBox_AttributesC->Append("2 - Garrison Capacity");
		Effects_ComboBox_AttributesC->Append("3 - Unit Size Radius 1");
		Effects_ComboBox_AttributesC->Append("4 - Unit Size Radius 2");
		Effects_ComboBox_AttributesC->Append("5 - Movement Speed");
		Effects_ComboBox_AttributesC->Append("6 - Garrison Recovery Rate");
		Effects_ComboBox_AttributesC->Append("7 - Unknown?");
		Effects_ComboBox_AttributesC->Append("8 - Armor");
		Effects_ComboBox_AttributesC->Append("9 - Attack");
		Effects_ComboBox_AttributesC->Append("10 - Attack Reloading Time");
		Effects_ComboBox_AttributesC->Append("11 - Accuracy Percent");
		Effects_ComboBox_AttributesC->Append("12 - Range");
		Effects_ComboBox_AttributesC->Append("13 - Working Rate");
		Effects_ComboBox_AttributesC->Append("14 - Resource Carriage");
		Effects_ComboBox_AttributesC->Append("15 - Unknown?");
		Effects_ComboBox_AttributesC->Append("16 - Change Projectile Unit To");
		Effects_ComboBox_AttributesC->Append("17 - Unknown Building Mode");
		Effects_ComboBox_AttributesC->Append("18 - Unknown?");
		Effects_ComboBox_AttributesC->Append("19 - Projectile Intelligent Accuracy");
		Effects_ComboBox_AttributesC->Append("20 - Minimum Range");
		Effects_ComboBox_AttributesC->Append("21 - Population Support");
		Effects_ComboBox_AttributesC->Append("22 - Blast Radius");
		Effects_ComboBox_AttributesC->Append("23 - Search Radius");
		Effects_ComboBox_AttributesC->Append("24 - None");
		Effects_ComboBox_AttributesC->Append("25 - None");
		Effects_ComboBox_AttributesC->Append("26 - None");
		Effects_ComboBox_AttributesC->Append("27 - None");
		Effects_ComboBox_AttributesC->Append("28 - None");
		Effects_ComboBox_AttributesC->Append("29 - None");
		Effects_ComboBox_AttributesC->Append("30 - None");
		Effects_ComboBox_AttributesC->Append("31 - None");
		Effects_ComboBox_AttributesC->Append("32 - None");
		Effects_ComboBox_AttributesC->Append("33 - None");
		Effects_ComboBox_AttributesC->Append("34 - None");
		Effects_ComboBox_AttributesC->Append("35 - None");
		Effects_ComboBox_AttributesC->Append("36 - None");
		Effects_ComboBox_AttributesC->Append("37 - None");
		Effects_ComboBox_AttributesC->Append("38 - None");
		Effects_ComboBox_AttributesC->Append("39 - None");
		Effects_ComboBox_AttributesC->Append("40 - None");
		Effects_ComboBox_AttributesC->Append("41 - None");
		Effects_ComboBox_AttributesC->Append("42 - None");
		Effects_ComboBox_AttributesC->Append("43 - None");
		Effects_ComboBox_AttributesC->Append("44 - None");
		Effects_ComboBox_AttributesC->Append("45 - None");
		Effects_ComboBox_AttributesC->Append("46 - None");
		Effects_ComboBox_AttributesC->Append("47 - None");
		Effects_ComboBox_AttributesC->Append("48 - None");
		Effects_ComboBox_AttributesC->Append("49 - None");
		Effects_ComboBox_AttributesC->Append("50 - None");
		Effects_ComboBox_AttributesC->Append("51 - None");
		Effects_ComboBox_AttributesC->Append("52 - None");
		Effects_ComboBox_AttributesC->Append("53 - None");
		Effects_ComboBox_AttributesC->Append("54 - None");
		Effects_ComboBox_AttributesC->Append("55 - None");
		Effects_ComboBox_AttributesC->Append("56 - None");
		Effects_ComboBox_AttributesC->Append("57 - None");
		Effects_ComboBox_AttributesC->Append("58 - None");
		Effects_ComboBox_AttributesC->Append("59 - None");
		Effects_ComboBox_AttributesC->Append("60 - None");
		Effects_ComboBox_AttributesC->Append("61 - None");
		Effects_ComboBox_AttributesC->Append("62 - None");
		Effects_ComboBox_AttributesC->Append("63 - None");
		Effects_ComboBox_AttributesC->Append("64 - None");
		Effects_ComboBox_AttributesC->Append("65 - None");
		Effects_ComboBox_AttributesC->Append("66 - None");
		Effects_ComboBox_AttributesC->Append("67 - None");
		Effects_ComboBox_AttributesC->Append("68 - None");
		Effects_ComboBox_AttributesC->Append("69 - None");
		Effects_ComboBox_AttributesC->Append("70 - None");
		Effects_ComboBox_AttributesC->Append("71 - None");
		Effects_ComboBox_AttributesC->Append("72 - None");
		Effects_ComboBox_AttributesC->Append("73 - None");
		Effects_ComboBox_AttributesC->Append("74 - None");
		Effects_ComboBox_AttributesC->Append("75 - None");
		Effects_ComboBox_AttributesC->Append("76 - None");
		Effects_ComboBox_AttributesC->Append("77 - None");
		Effects_ComboBox_AttributesC->Append("78 - None");
		Effects_ComboBox_AttributesC->Append("79 - None");
		Effects_ComboBox_AttributesC->Append("80 - Boarding Energy Reload Speed");
		Effects_ComboBox_AttributesC->Append("81 - None");
		Effects_ComboBox_AttributesC->Append("82 - None");
		Effects_ComboBox_AttributesC->Append("83 - None");
		Effects_ComboBox_AttributesC->Append("84 - None");
		Effects_ComboBox_AttributesC->Append("85 - None");
		Effects_ComboBox_AttributesC->Append("86 - None");
		Effects_ComboBox_AttributesC->Append("87 - None");
		Effects_ComboBox_AttributesC->Append("88 - None");
		Effects_ComboBox_AttributesC->Append("89 - None");
		Effects_ComboBox_AttributesC->Append("90 - None");
		Effects_ComboBox_AttributesC->Append("91 - None");
		Effects_ComboBox_AttributesC->Append("92 - None");
		Effects_ComboBox_AttributesC->Append("93 - None");
		Effects_ComboBox_AttributesC->Append("94 - None");
		Effects_ComboBox_AttributesC->Append("95 - None");
		Effects_ComboBox_AttributesC->Append("96 - None");
		Effects_ComboBox_AttributesC->Append("97 - None");
		Effects_ComboBox_AttributesC->Append("98 - None");
		Effects_ComboBox_AttributesC->Append("99 - None");
		Effects_ComboBox_AttributesC->Append("100 - Resource Cost");
		Effects_ComboBox_AttributesC->Append("101 - Creation Time");
		Effects_ComboBox_AttributesC->Append("102 - Number of Garrison Arrows");
		Effects_ComboBox_AttributesC->Append("103 - Food Cost");
		if(GameVersion < 4)
		{
			Effects_ComboBox_AttributesC->Append("104 - Wood Cost");
			Effects_ComboBox_AttributesC->Append("105 - Gold Cost");
			Effects_ComboBox_AttributesC->Append("106 - Stone Cost");
		}
		else
		{
			Effects_ComboBox_AttributesC->Append("104 - Carbon Cost");
			Effects_ComboBox_AttributesC->Append("105 - Nova Cost");
			Effects_ComboBox_AttributesC->Append("106 - Ore Cost");
		}
		Effects_ComboBox_AttributesC->Append("107 - OREX Cost?");
		Effects_ComboBox_AttributesC->Append("108 - Healing Rate");	// Selection 109
		Effects_ComboBox_AttributesC->SetSelection(0);

		if(Units_GraphicSet->GetCount() > 0)
		{
			Units_GraphicSet->Clear();
		}
		if(GameVersion < 2)
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
		else if(GameVersion < 4)
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
			// SWGB, forget this
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
		Units_GraphicSet->Append("9 Ask me for more!");
		Units_GraphicSet->SetSelection(0);

		DataOpened = true;
		OnGameVersionChange();

		/*wxCommandEvent UseUndoCommand(wxEVT_COMMAND_MENU_SELECTED, MenuOption_Undo);
		UseUndoCommand.SetId(MenuOption_Undo);
		UseUndoCommand.SetInt(UseUndo);
		ProcessEvent(UseUndoCommand);*/
	}
	SetStatusText("", 0);

	/*Extraction = new wxFileConfig("AGE_Extraction", wxEmptyString, "age2extraction.ini", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	string Place, Data;
	long Location = 0;
	for(long loop = 0;Location <= 21642;loop++)
	{
		Place = "Data/"+lexical_cast<string>(Location)+"-"+lexical_cast<string>(Location+loop);
		Data = "";
		for(long loop2 = 0;loop2 < 40;loop2++)
		{
			if(Location+loop2 < 21642)
			{
				if((short)GenieFile->Unknown1[Location+loop2] >= 0)
				Data += " ";
				if((short)GenieFile->Unknown1[Location+loop2] > -10 && (short)GenieFile->Unknown1[Location+loop2] < 10)
				Data += " ";
				if((short)GenieFile->Unknown1[Location+loop2] > -100 && (short)GenieFile->Unknown1[Location+loop2] < 100)
				Data += " ";
				Data += " "+lexical_cast<string>((short)GenieFile->Unknown1[Location+loop2]);
			}
		}
		Location += 40;
	//	wxMessageBox(Place+Data);
		Extraction->Write(Place, Data);
	}
	delete Extraction;*/

	NeedDat = false;
	SkipOpenDialog = false;

}

void AGE_Frame::OnGameVersionChange()
{
	if(DataOpened)	// Hiding stuff according to game version should be here.
	{
		for(short loop = 64;loop < 84;loop++)
		{
			if(GameVersion >= 3)
			{
				if(ShowUnknowns) Terrains_Unknown10[loop]->Show(true);
			}
			else
			{
				Terrains_Unknown10[loop]->Show(false);
			}
		}
		for(short loop = 4;loop < 6;loop++)
		{
			if(GameVersion >= 2)
			{
				Research_RequiredTechs[loop]->Show(true);
				Research_ComboBox_RequiredTechs[loop]->Show(true);
			}
			else
			{
				Research_RequiredTechs[loop]->Show(false);
				Research_ComboBox_RequiredTechs[loop]->Show(false);
			}
		}
		if(GameVersion != 2)
		{
			Units_Holder_Attribute->Show(true);
			Units_Holder_Civ->Show(true);
		}
		else
		{
			Units_Holder_Attribute->Show(false);
			Units_Holder_Civ->Show(false);
		}

		if(GameVersion >= 2) // AoK ->
		{
			Research_Holder_Civ->Show(true);
			Research_Holder_FullTechMode->Show(true);
			Civs_Holder_TeamBonus->Show(true);
			Terrains_Holder_BlendPriority->Show(true);
			Terrains_Holder_BlendType->Show(true);
			TerRestrict_Holder_Unknown1->Show(true);
			TerRestrict_Holder_Graphics->Show(true);
			TerRestrict_Holder_Amount->Show(true);
			SoundItems_Holder_Civ->Show(true);
			Colors_Holder_Name->Show(false);
			Colors_Holder_Palette->Show(true);
			Colors_Holder_MinimapColor->Show(true);
			Units_StandingGraphic[1]->Show(true);
			Units_ComboBox_StandingGraphic[1]->Show(true);
			Units_TrainSound[1]->Show(true);
			Units_ComboBox_TrainSound[1]->Show(true);
			Units_Holder_Unknown3a->Show(false);
			Units_Holder_SelectionShapeType->Show(true);
			Units_Holder_SelectionEffect->Show(true);
			Units_Holder_EditorSelectionColour->Show(true);
			Units_Holder_ID3->Show(true);
			Units_Holder_GarrisonRecoveryRate->Show(true);
			Units_Holder_MissileGraphicDelay->Show(true);
			Units_Holder_HeroMode->Show(true);
			Units_Holder_GarrisonGraphic->Show(true);
			Units_Holder_AttackMissileDuplicationAmount1->Show(true);
			Units_Holder_AttackMissileDuplicationAmount2->Show(true);
			Units_Holder_AttackMissileDuplicationSpawning->Show(true);
			Units_Holder_AttackMissileDuplicationUnit->Show(true);
			Units_Holder_AttackMissileDuplicationGraphic->Show(true);
			Units_Holder_AnnexUnit1->Show(true);
			Units_Holder_AnnexUnitMisplacement1->Show(true);
			Units_Holder_HeadUnit->Show(true);
			Units_Holder_HeadUnit->Show(true);
			Units_Holder_TransformUnit->Show(true);
			Units_Holder_GarrisonType->Show(true);
			Units_Holder_GarrisonHealRate->Show(true);
			TechTrees_Main->Show(true);
			if(ShowUnknowns)
			{
				SoundItems_Holder_Unknown->Show(true);
				Colors_Holder_UnknownArea->Show(true);
				Units_Holder_Unknown7->Show(true);
				Units_Holder_Unknown8->Show(true);
				Units_Holder_Unknown12->Show(true);
				for(short loop = 1;loop < 17;loop++)
				Units_Unknown16[loop]->Show(true);
				Units_Holder_Unknown26->Show(true);
				Units_Holder_Unknown27->Show(true);
				Units_Holder_Unknown28->Show(true);
				Units_Holder_Unknown29->Show(true);
				Units_Holder_Unknown33->Show(true);
				Units_Holder_Unknown34->Show(true);
				Units_Holder_Unknown35->Show(true);
				Units_Holder_Unknown36->Show(true);
				Units_Holder_Unknown37->Show(true);
				General_Holder_Variables2->Show(true);
			}
		}
		else // <- RoR
		{
			Research_Holder_Civ->Show(false);
			Research_Holder_FullTechMode->Show(false);
			Civs_Holder_TeamBonus->Show(false);
			Terrains_Holder_BlendPriority->Show(false);
			Terrains_Holder_BlendType->Show(false);
			TerRestrict_Holder_Unknown1->Show(false);
			TerRestrict_Holder_Graphics->Show(false);
			TerRestrict_Holder_Amount->Show(false);
			SoundItems_Holder_Civ->Show(false);
			SoundItems_Holder_Unknown->Show(false);
			Colors_Holder_Name->Show(true);
			Colors_Holder_Palette->Show(false);
			Colors_Holder_MinimapColor->Show(false);
			Colors_Holder_UnknownArea->Show(false);
			Units_StandingGraphic[1]->Show(false);
			Units_ComboBox_StandingGraphic[1]->Show(false);
			Units_TrainSound[1]->Show(false);
			Units_ComboBox_TrainSound[1]->Show(false);
			Units_Holder_Unknown7->Show(false);
			Units_Holder_Unknown8->Show(false);
			Units_Holder_SelectionShapeType->Show(false);
			Units_Holder_SelectionEffect->Show(false);
			Units_Holder_EditorSelectionColour->Show(false);
			Units_Holder_ID3->Show(false);
			Units_Holder_Unknown12->Show(false);
			for(short loop = 1;loop < 17;loop++)
			Units_Unknown16[loop]->Show(false);
			Units_Holder_GarrisonRecoveryRate->Show(false);
			Units_Holder_Unknown26->Show(false);
			Units_Holder_Unknown27->Show(false);
			Units_Holder_Unknown28->Show(false);
			Units_Holder_MissileGraphicDelay->Show(false);
			Units_Holder_HeroMode->Show(false);
			Units_Holder_GarrisonGraphic->Show(false);
			Units_Holder_AttackMissileDuplicationAmount1->Show(false);
			Units_Holder_AttackMissileDuplicationAmount2->Show(false);
			Units_Holder_AttackMissileDuplicationSpawning->Show(false);
			Units_Holder_AttackMissileDuplicationUnit->Show(false);
			Units_Holder_AttackMissileDuplicationGraphic->Show(false);
			Units_Holder_Unknown29->Show(false);
			Units_Holder_Unknown33->Show(false);
			Units_Holder_AnnexUnit1->Show(false);
			Units_Holder_AnnexUnitMisplacement1->Show(false);
			Units_Holder_HeadUnit->Show(false);
			Units_Holder_TransformUnit->Show(false);
			Units_Holder_Unknown34->Show(false);
			Units_Holder_GarrisonType->Show(false);
			Units_Holder_GarrisonHealRate->Show(false);
			Units_Holder_Unknown35->Show(false);
			Units_Holder_Unknown36->Show(false);
			Units_Holder_Unknown37->Show(false);
			TechTrees_Main->Show(false);
			General_Holder_Variables2->Show(false);
			if(ShowUnknowns) Units_Holder_Unknown3a->Show(true);
		}
		if(GameVersion >= 4) // SWGB ->
		{
			Research_Holder_Name[1]->Show(true);
			Civs_Holder_Name[1]->Show(true);
			Units_Holder_Name2->Show(true);
			Units_Holder_Unitline->Show(true);
			Units_Holder_MinTechLevel->Show(true);
			UnitLines_Main->Show(true);
			if(ShowUnknowns)
			{
				Civs_Holder_SUnknown1->Show(true);
				Terrains_Holder_SUnknown1->Show(true);
				General_Holder_Variables1->Show(true);
				TechTrees_Ages_Grid_Zeroes2->Show(true);
				TechTrees_Buildings_Grid_Unknown2a2->Show(true);
				TechTrees_Buildings_Grid_Unknown2b2->Show(true);
				TechTrees_Units_Grid_Unknown2a2->Show(true);
				TechTrees_Units_Grid_Unknown2b2->Show(true);
				TechTrees_Researches_Grid_Unknown2a2->Show(true);
				TechTrees_Researches_Grid_Unknown2b2->Show(true);
			}
		}
		else // <- TC
		{
			Research_Holder_Name[1]->Show(false);
			Civs_Holder_Name[1]->Show(false);
			Civs_Holder_SUnknown1->Show(false);
			Terrains_Holder_SUnknown1->Show(false);
			Units_Holder_Name2->Show(false);
			Units_Holder_Unitline->Show(false);
			Units_Holder_MinTechLevel->Show(false);
			General_Holder_Variables1->Show(false);
			UnitLines_Main->Show(false);
			TechTrees_Ages_Grid_Zeroes2->Show(false);
			TechTrees_Buildings_Grid_Unknown2a2->Show(false);
			TechTrees_Buildings_Grid_Unknown2b2->Show(false);
			TechTrees_Units_Grid_Unknown2a2->Show(false);
			TechTrees_Units_Grid_Unknown2b2->Show(false);
			TechTrees_Researches_Grid_Unknown2a2->Show(false);
			TechTrees_Researches_Grid_Unknown2b2->Show(false);
		}
		if(GameVersion >= 3) // TC ->
		{
			Units_Holder_SnowGraphicID->Show(true);
			if(ShowUnknowns)
			{
				Units_Holder_Unknown9->Show(true);
				Units_Unknown20[1]->Show(true);
			}
		}
		else // <- AoK
		{
			Units_Holder_Unknown9->Show(false);
			Units_Unknown20[1]->Show(false);
			Units_Holder_SnowGraphicID->Show(false);
		}
	}

	for(short loop = 0;loop < GenieFile->Civs.size();loop++)
	{
		Units_CivBoxes[loop]->Show(true);
		Units_CivLabels[loop]->Show(true);
		Units_CivLabels[loop]->SetLabel(GenieFile->Civs[loop].Name.substr(0, 2));
	}
	for(short loop = GenieFile->Civs.size();loop < MaxCivs;loop++)
	{
		Units_CivBoxes[loop]->Show(false);
		Units_CivLabels[loop]->Show(false);
	}

//	Every data area should be layouted.
	Civs_Main->Layout();
	Units_Main->Layout();
	Research_Main->Layout();
	Techs_Main->Layout();
	TechTrees_Main->Layout();
	Graphics_Main->Layout();
	Terrains_Main->Layout();
	TerRestrict_Main->Layout();
	Sounds_Main->Layout();
	Colors_Main->Layout();
	UnitLines_Main->Layout();
	Borders_Main->Layout();
	General_Main->Layout();
	Units_Scroller->GetSizer()->FitInside(Units_Scroller);
	Research_Scroller->GetSizer()->FitInside(Research_Scroller);
	TechTrees_Scroller->GetSizer()->FitInside(TechTrees_Scroller);
	Graphics_Scroller->GetSizer()->FitInside(Graphics_Scroller);
	Terrains_Scroller->GetSizer()->FitInside(Terrains_Scroller);
	General_Scroller->GetSizer()->FitInside(General_Scroller);
	Refresh(); // Does this refresh non-visible tabs?
}

void AGE_Frame::OnSave(wxCommandEvent& Event)
{
//	int ErrCode = 0;
	wxCommandEvent Selected;

		AGE_SaveDialog SaveBox(this);
		SaveBox.Path_DatFileLocation->SetFocus();

		SaveBox.DriveLetterBox->ChangeValue(DriveLetter);
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

		if (SaveBox.ShowModal() != wxID_OK)
		{
			return;
		}

		SaveGameVersion = SaveBox.CheckBox_GenieVer->GetSelection();
		SaveDat = SaveBox.CheckBox_DatFileLocation->IsChecked();
		SaveApf = SaveBox.CheckBox_ApfFileLocation->IsChecked();

		SaveDatFileName = SaveBox.Path_DatFileLocation->GetPath();
		SaveApfFileName = SaveBox.Path_ApfFileLocation->GetPath();

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

	SetStatusText("", 0);
}

void AGE_Frame::OnExit(wxCloseEvent& Event)
{
	Config = new wxFileConfig("AdvancedGenieEditor", wxEmptyString, "age2config.ini", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	Config->Write("Interaction/PromptForFilesOnOpen", PromptForFilesOnOpen);
	Config->Write("Interaction/AutoCopy", AutoCopy);
	Config->Write("Interaction/CopyGraphics", CopyGraphics);
	Config->Write("Interaction/AllCivs", Units_SpecialCopy_Civs->GetValue());
	Config->Write("Interaction/EnableIDFix", EnableIDFix);
	Config->Write("Interface/ShowUnknowns", ShowUnknowns);
	Config->Write("Interface/ShowButtons", ShowButtons);
	Config->Write("DefaultFiles/DriveLetter", DriveLetter);
	Config->Write("DefaultFiles/Version", GameVersion);
	Config->Write("DefaultFiles/SaveVersion", SaveGameVersion);
	Config->Write("DefaultFiles/DatUsed", DatUsed);
	Config->Write("DefaultFiles/DatFilename", DatFileName);
	Config->Write("DefaultFiles/ApfFilename", ApfFileName);
	Config->Write("DefaultFiles/SaveDatFilename", SaveDatFileName);
	Config->Write("DefaultFiles/SaveApfFilename", SaveApfFileName);
	Config->Write("DefaultFiles/LangsUsed", LangsUsed);
	Config->Write("DefaultFiles/LangFilename", LangFileName);
	Config->Write("DefaultFiles/LangX1Filename", LangX1FileName);
	Config->Write("DefaultFiles/LangX1P1Filename", LangX1P1FileName);
	Config->Write("DefaultFiles/SaveDat", SaveDat);
	Config->Write("DefaultFiles/SaveApf", SaveApf);
	delete Config;

	delete GenieFile;
	GenieFile = NULL;

	TabBar_Main->Show(false);
	TabBar_Main->Destroy();
	Destroy();
}

void AGE_Frame::OnAutoCopy(wxCommandEvent& Event)
{
	if(Event.GetId() == Units_AutoCopy->GetId())
	{
		AutoCopy = Event.IsChecked();
		Units_CopyTo->Enable(!AutoCopy);
	}
	else if(Event.GetId() == Units_CopyGraphics->GetId())
	{
		CopyGraphics = Event.IsChecked();
	}
	else if(Event.GetId() == Units_CopyTo->GetId())
	{
		UnitsAutoCopy();
	}
	else if(Event.GetId() == Units_SelectAll->GetId())
	{
		for(short loop = 0;loop < GenieFile->Civs.size();loop++)
		Units_CivBoxes[loop]->SetValue(true);
	}
	else if(Event.GetId() == Units_SelectClear->GetId())
	{
		for(short loop = 0;loop < GenieFile->Civs.size();loop++)
		Units_CivBoxes[loop]->SetValue(false);
	}
	else if(Event.GetId() == Units_GraphicSet->GetId())
	{
		short Selection = Units_GraphicSet->GetSelection();
		for(short loop = 0;loop < GenieFile->Civs.size();loop++)
		{
			if((short)GenieFile->Civs[loop].GraphicSet == Selection)
			{
				Units_CivBoxes[loop]->SetValue(true);
			}
			else
			{
				Units_CivBoxes[loop]->SetValue(false);
			}
		}
	}
}

void AGE_Frame::OnMenuOption(wxCommandEvent& Event)
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
			//wxMessageBox(lexical_cast<string>(GetToolBar()->GetToolState(ToolBar_Show)));
			ShowUnknowns = Event.IsChecked();
			if(ShowUnknowns)
			{
				Units_Holder_UnknownArea->Show(true);
				Units_CommandHolder_Data2->Show(true);
				TechTrees_Ages_Holder_Zeroes->Show(true);
				TechTrees_Buildings_Holder_Unknown2a->Show(true);
				TechTrees_Buildings_Holder_Unknown2b->Show(true);
				TechTrees_Units_Holder_Unknown2a->Show(true);
				TechTrees_Units_Holder_Unknown2b->Show(true);
				TechTrees_Researches_Holder_Unknown2a->Show(true);
				TechTrees_Researches_Holder_Unknown2b->Show(true);
				Graphics_Holder_Unknowns->Show(true);
				Graphics_Grid_Deltas_Data2->Show(true);
				Terrains_Holder_UnknownArea->Show(true);
				Borders_Unknonws->Show(true);
				Sounds_Holder_Unknown->Show(true);
				SoundItems_Holder_Unknown->Show(true);
				Colors_Holder_UnknownArea->Show(true);
				General_TopRow->Show(true);
				General_ScrollerWindowsSpace->Show(true);
			}
			else
			{
				Units_Holder_UnknownArea->Show(false);
				Units_CommandHolder_Data2->Show(false);
				TechTrees_Ages_Holder_Zeroes->Show(false);
				TechTrees_Buildings_Holder_Unknown2a->Show(false);
				TechTrees_Buildings_Holder_Unknown2b->Show(false);
				TechTrees_Units_Holder_Unknown2a->Show(false);
				TechTrees_Units_Holder_Unknown2b->Show(false);
				TechTrees_Researches_Holder_Unknown2a->Show(false);
				TechTrees_Researches_Holder_Unknown2b->Show(false);
				Graphics_Holder_Unknowns->Show(false);
				Graphics_Grid_Deltas_Data2->Show(false);
				Terrains_Holder_UnknownArea->Show(false);
				Borders_Unknonws->Show(false);
				Sounds_Holder_Unknown->Show(false);
				SoundItems_Holder_Unknown->Show(false);
				Colors_Holder_UnknownArea->Show(false);
				General_TopRow->Show(false);
				General_ScrollerWindowsSpace->Show(false);
			}
			OnGameVersionChange(); // Does layouting and refreshing and ... check it out.
		}
		break;
		case MenuOption_Buttons:
		{
			ShowButtons = Event.IsChecked();
			if(ShowButtons)
			{
				Civs_Add->Enable(true); // Must copy existing civ over the new one
				Civs_Insert->Enable(true);
				Civs_Delete->Enable(true);
				Terrains_Add->Enable(true);
				Terrains_Insert->Enable(true);
				Terrains_Delete->Enable(true);
			}
			else
			{
				Civs_Add->Enable(false);
				Civs_Insert->Enable(false);
				Civs_Delete->Enable(false);
				Terrains_Add->Enable(false);
				Terrains_Insert->Enable(false);
				Terrains_Delete->Enable(false);
			}
		}
		break;
		case wxID_EXIT:
		{
			Close(true);
		}
		break;
		case MenuOption_Tips:
		{
			string TipText = "Tips\n\n";
			TipText += "You can have multiple search entries separated with \"|\" letter.\n";
			TipText += "Upper search boxes are inclusive and lower ones exclusive.\n";
			TipText += "Example: \"tower|ship|ram\"\n";
			TipText += "You can switch from or finding to and finding with check boxes.\n";
			TipText += "Meaning that every search entry has to match.\n";
			wxMessageBox(TipText);
		}
		break;
		case MenuOption_About:
		{
			AGE_AboutDialog AGEAbout(this);
			AGEAbout.ShowModal();
		}
		break;
		case MenuOption_IDFix:
		{
			EnableIDFix = Event.IsChecked();
			wxMessageBox("Please restart this program.\nI do not recommend disabling index fixes!");
		}
		break;
		case ToolBar_CustomNames:
		{
			Customs = new wxFileConfig("AGE Lists", wxEmptyString, "age2lists.ini", wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
			long ExtraCount = Attacks_ComboBox_Class[0]->GetCount()-32;
			Customs->Write("Count/ExtraCount", ExtraCount);
			wxString MoveHolder = "";
			for(short loop = 0;loop < ExtraCount;loop++)
			{
				MoveHolder = Attacks_ComboBox_Class[0]->GetString(loop+32);
				Customs->Write("Names/"+lexical_cast<string>(loop+31), MoveHolder);
			}
			delete Customs;
			//wxMessageBox("File extracted successfully!");
		}
		break;
		/*case MenuOption_Undo:
		{
			UseUndo = Event.IsChecked();
			if(UseUndo)
			{
				Units_Undo->Enable(true);
				if(DataOpened)
				for(short loop = 0;loop < GenieFile->Civs.size();loop++)
				CivBackup[loop].Units = GenieFile->Civs[loop].Units;
			}
			else
			{
				Units_Undo->Enable(false);
				if(DataOpened)
			//	if(CivBackup)
				delete [] CivBackup;
			}
		}
		break;*/
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

string AGE_Frame::LanguageDllString(int ID)
{
	string Result = "";
	char Buffer[256];

	if(LoadStringA(LanguageDll[2], ID, Buffer, 256) && strlen(Buffer) > 0)
	{
		Result = Buffer;
	}
	else if(LoadStringA(LanguageDll[1], ID, Buffer, 256) && strlen(Buffer) > 0)
	{
		Result = Buffer;
	}
	else if(LoadStringA(LanguageDll[0], ID, Buffer, 256) && strlen(Buffer) > 0)
	{
		Result = Buffer;
	}
	return Result;
}

bool AGE_Frame::SearchMatches(string &CompareText)
{
	bool Matches = false, And[2] = {true,true};
	short Size = 30; // Maximum pieces for search text to be split.
	short Max = Size;
	wxString SearchEnd[Size]; // Parts.

	if(SearchText == "") // If there is no search text, list normally.
	{
		Matches = true;
	}
	else if(CompareText.find(SearchText) != string::npos) // If search text has a match.
	{
		Matches = true;
	}
	else
	{
		size_t Found; // Founding position.
		Found = SearchText.find("|"); // Searching for separation mark in search text.
		if((Found != string::npos) && Found > 0 && 1 < (SearchText.length() - Found)) // Separation mark found and there is search text on its both sides.
		{
			// Splitting of search.
			SearchEnd[0] = SearchText.substr(0, Found); // Cutting the first part.
			SearchEnd[1] = SearchText.substr((Found+1), SearchText.length() - 1); // Cutting the remaining part.

			// Lets look if there are additional separation marks left.
			for(short loop = 2;loop < Size;loop++) // Splits over 2 parts if necessary.
			{
				Found = SearchEnd[loop-1].find("|");
				if((Found != string::npos) && Found > 0 && 1 < (SearchEnd[loop-1].length() - Found))
				{
					SearchEnd[loop] = SearchEnd[loop-1].substr((Found+1), SearchEnd[loop-1].length() - 1);
					SearchEnd[loop-1] = SearchEnd[loop-1].substr(0, Found);
				}
				else
				{
					Size = loop;
					break;
				}
			}

			// Searching for matches.
			for(short loop = 0;loop < Size;loop++)
			{
				if(SearchEnd[loop] != "") // Can match only if not empty.
				{
					if(CompareText.find(SearchEnd[loop]) != string::npos)
					Matches = true;
					else And[0] = false;
				}
			}
			if(UseAnd[0] == true && And[0] == false && Matches == true) Matches = false;
		}
	}

	if(Matches == true)	// We don't need to check for excluding if it's not going to be listed.
	if(ExcludeText == "") // If there is no exclude text, list normally.
	{
		// Do nothing.
	}
	else if(CompareText.find(ExcludeText) != string::npos) // If exclude text has a match.
	{
		Matches = false;
	}
	else
	{
		Size = Max;
		size_t Found; // Founding position.
		Found = ExcludeText.find("|"); // Searching for separation mark in exclude text.
		if((Found != string::npos) && Found > 0 && 1 < (ExcludeText.length() - Found)) // Separation mark found and there is exclude text on its both sides.
		{
			// Splitting of exclude.
			SearchEnd[0] = ExcludeText.substr(0, Found); // Cutting the first part.
			SearchEnd[1] = ExcludeText.substr((Found+1), ExcludeText.length() - 1); // Cutting the remaining part.

			// Lets look if there are additional separation marks left.
			for(short loop = 2;loop < Size;loop++) // Splits over 2 parts if necessary.
			{
				Found = SearchEnd[loop-1].find("|");
				if((Found != string::npos) && Found > 0 && 1 < (SearchEnd[loop-1].length() - Found))
				{
					SearchEnd[loop] = SearchEnd[loop-1].substr((Found+1), SearchEnd[loop-1].length() - 1);
					SearchEnd[loop-1] = SearchEnd[loop-1].substr(0, Found);
				}
				else
				{
					Size = loop;
					break;
				}
			}

			// Searching for matches.
			for(short loop = 0;loop < Size;loop++)
			{
				if(SearchEnd[loop] != "") // Can match only if not empty.
				{
					if(CompareText.find(SearchEnd[loop]) != string::npos)
					Matches = false;
					else And[1] = false;
				}
			}
			if(UseAnd[1] == true && And[1] == false && Matches == false) Matches = true;
		}
	}

	return Matches;
}

//	Following kill focuses are used to update lists in user interface

void AGE_Frame::OnKillFocus_TextControls(wxFocusEvent& Event)
{
	if(Event.GetId() == Effects_E->GetId() || Event.GetId() == Effects_F->GetId())
	{
		if(!Effects_E->IsEmpty() && !Effects_F->IsEmpty()) // if has something, then update float value.
		{
			float Amount = lexical_cast<float>(Effects_E->GetValue());
			short Class = lexical_cast<short>(Effects_F->GetValue());
			if(Amount > -1 && Amount < 256 && Class > -1 && Class < 256) // positive amount 0 to 255
			{
				Effects_D->ChangeValue(lexical_cast<string>(Amount + (Class * 256)));
				wxFocusEvent Temp(wxEVT_KILL_FOCUS);
				Effects_D->OnKillFocus(Temp);
			}
			else if(Amount > -256 && Amount < 0 && Class > -1 && Class < 256) // negative amount -255 to -1
			{
				Effects_D->ChangeValue(lexical_cast<string>(Amount - (Class * 256)));
				wxFocusEvent Temp(wxEVT_KILL_FOCUS);
				Effects_D->OnKillFocus(Temp);
			}
		}
		ListEffects();
	}
	else if(Event.GetId() == Units_Type->GetId())
	{
		if(!Units_Type->IsEmpty())
		{
			((TextCtrl_Byte*)Event.GetEventObject())->OnKillFocus(Event);
			if(!((TextCtrl_Byte*)Event.GetEventObject())->NoLoadList)
			{
				short UnitType = lexical_cast<short>(Units_Type->GetValue());
				switch(UnitType)
				{
					case 10:
					case 20:
					case 25:
					case 30:
					case 40:
					case 60:
					case 70:
					case 80:
					case 90:
					{
						GenieFile->Civs[UnitCivID].Units[UnitID].Type = (char)UnitType;
						if(AutoCopy)
						{
							for(short loop = 0;loop < GenieFile->Civs.size();loop++)
							GenieFile->Civs[loop].Units[UnitID].Type = (char)UnitType;

							UnitsAutoCopy();
						}
					}
					break;
				}
			}
		}
		wxCommandEvent E;
		OnUnitsSelect(E);	// Updates unit layout and unit type combo box.
//		ListUnits(UnitCivID, false);	// For special search filters.
	}
}

void AGE_Frame::OnSelection_ComboBoxes(wxCommandEvent& Event)
{
	if(Event.GetId() == Attacks_ComboBox_Class[2]->GetId())
	{
		short Class = Attacks_ComboBox_Class[2]->GetSelection() - 1;
		if(Class >= 0)
		{
			float Amount = lexical_cast<float>(Effects_E->GetValue());
			if(Amount > -1 && Amount < 256) // positive amount 0 to 255
			{
				Effects_D->ChangeValue(lexical_cast<string>(Amount + (Class * 256)));
			}
			else if(Amount > -256 && Amount < 0) // negative amount -255 to -1
			{
				Effects_D->ChangeValue(lexical_cast<string>(Amount - (Class * 256)));
			}
		}
		else
		{
			Effects_E->ChangeValue("0");
			Effects_F->ChangeValue("0");
			Effects_D->ChangeValue("0");
		}
		wxFocusEvent Temp(wxEVT_KILL_FOCUS);
		Effects_D->OnKillFocus(Temp);

		ListEffects();
	}
	else if(Event.GetId() == Units_ComboBox_Type->GetId())
	{
		short Selection = Units_ComboBox_Type->GetSelection();
		if(Selection == 1)
		{
			GenieFile->Civs[UnitCivID].Units[UnitID].Type = 10;
		}
		else if(Selection == 2)
		{
			GenieFile->Civs[UnitCivID].Units[UnitID].Type = 20;
		}
		else if(Selection == 3)
		{
			GenieFile->Civs[UnitCivID].Units[UnitID].Type = 25;
		}
		else if(Selection == 4)
		{
			GenieFile->Civs[UnitCivID].Units[UnitID].Type = 30;
		}
		else if(Selection == 5)
		{
			GenieFile->Civs[UnitCivID].Units[UnitID].Type = 40;
		}
		else if(Selection == 6)
		{
			GenieFile->Civs[UnitCivID].Units[UnitID].Type = 60;
		}
		else if(Selection == 7)
		{
			GenieFile->Civs[UnitCivID].Units[UnitID].Type = 70;
		}
		else if(Selection == 8)
		{
			GenieFile->Civs[UnitCivID].Units[UnitID].Type = 80;
		}
		else if(Selection == 9)
		{
			GenieFile->Civs[UnitCivID].Units[UnitID].Type = 90;
		}
		if(AutoCopy)
		{
			char UnitType = GenieFile->Civs[UnitCivID].Units[UnitID].Type;
			for(short loop = 0;loop < GenieFile->Civs.size();loop++)
			GenieFile->Civs[loop].Units[UnitID].Type = UnitType;

			UnitsAutoCopy();
		}

		wxCommandEvent E;
		OnUnitsSelect(E);	// Updates unit layout.
//		ListUnits(UnitCivID, false);	// For special search filters.
	}
	else if(Event.GetId() == UnitCommands_ComboBox_Types->GetId())
	{
		short Selection = UnitCommands_ComboBox_Types->GetSelection();
		if(Selection == 1)
		{
			UnitCommands_Type->ChangeValue("3");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 2)
		{
			UnitCommands_Type->ChangeValue("5");
			UnitCommands_SubType->ChangeValue("47");
		}
		else if(Selection == 3)
		{
			UnitCommands_Type->ChangeValue("5");
			UnitCommands_SubType->ChangeValue("79");
		}
		else if(Selection == 4)
		{
			UnitCommands_Type->ChangeValue("5");
			UnitCommands_SubType->ChangeValue("190");
		}
		else if(Selection == 5)
		{
			UnitCommands_Type->ChangeValue("5");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 6)
		{
			UnitCommands_Type->ChangeValue("6");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 7)
		{
			UnitCommands_Type->ChangeValue("7");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 8)
		{
			UnitCommands_Type->ChangeValue("10");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 9)
		{
			UnitCommands_Type->ChangeValue("11");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 10)
		{
			UnitCommands_Type->ChangeValue("12");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 11)
		{
			UnitCommands_Type->ChangeValue("13");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 12)
		{
			UnitCommands_Type->ChangeValue("21");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 12)
		{
			UnitCommands_Type->ChangeValue("21");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 13)
		{
			UnitCommands_Type->ChangeValue("101");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 14)
		{
			UnitCommands_Type->ChangeValue("104");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 15)
		{
			UnitCommands_Type->ChangeValue("105");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 16)
		{
			UnitCommands_Type->ChangeValue("106");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 17)
		{
			UnitCommands_Type->ChangeValue("107");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 18)
		{
			UnitCommands_Type->ChangeValue("109");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 19)
		{
			UnitCommands_Type->ChangeValue("110");
			UnitCommands_SubType->ChangeValue("189");
		}
		else if(Selection == 20)
		{
			UnitCommands_Type->ChangeValue("110");
			UnitCommands_SubType->ChangeValue("190");
		}
		else if(Selection == 21)
		{
			UnitCommands_Type->ChangeValue("110");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 22)
		{
			UnitCommands_Type->ChangeValue("111");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 23)
		{
			UnitCommands_Type->ChangeValue("120");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 24)
		{
			UnitCommands_Type->ChangeValue("121");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 25)
		{
			UnitCommands_Type->ChangeValue("122");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 26)
		{
			UnitCommands_Type->ChangeValue("125");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 27)
		{
			UnitCommands_Type->ChangeValue("131");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 28)
		{
			UnitCommands_Type->ChangeValue("132");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 29)
		{
			UnitCommands_Type->ChangeValue("135");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else if(Selection == 30)
		{
			UnitCommands_Type->ChangeValue("136");
			UnitCommands_SubType->ChangeValue("-1");
		}
		else
		{
			UnitCommands_Type->ChangeValue("-1");
			UnitCommands_SubType->ChangeValue("-1");
		}

		wxFocusEvent Temp(wxEVT_KILL_FOCUS);
		UnitCommands_Type->OnKillFocus(Temp);
		UnitCommands_SubType->OnKillFocus(Temp);

		if(GameVersion > 1)
		{
			ListUnitCommands();
		}
		else
		{
			if(AutoCopy)
			{
				UnitsAutoCopy();
			}
			ListUnitCommands();
		}
	}
	else if(Event.GetId() == TechTrees_ComboBox_Modes[0]->GetId())
	{
		GenieFile->TechTree.BuildingConnections[TTBuildingConnectionID].Mode1 = lexical_cast<long>(TechTrees_ComboBox_Modes[0]->GetSelection());

		wxCommandEvent E;
		OnTTBuildingSelect(E);
	}
	else if(Event.GetId() == TechTrees_ComboBox_Modes[1]->GetId())
	{
		GenieFile->TechTree.BuildingConnections[TTBuildingConnectionID].Mode2 = lexical_cast<long>(TechTrees_ComboBox_Modes[1]->GetSelection());

		wxCommandEvent E;
		OnTTBuildingSelect(E);
	}
	else if(Event.GetId() == TechTrees_ComboBox_Modes[2]->GetId())
	{
		GenieFile->TechTree.UnitConnections[TTUnitConnectionID].Mode1 = lexical_cast<long>(TechTrees_ComboBox_Modes[2]->GetSelection());

		wxCommandEvent E;
		OnTTUnitSelect(E);
	}
	else if(Event.GetId() == TechTrees_ComboBox_Modes[3]->GetId())
	{
		GenieFile->TechTree.UnitConnections[TTUnitConnectionID].Mode2 = lexical_cast<long>(TechTrees_ComboBox_Modes[3]->GetSelection());

		wxCommandEvent E;
		OnTTUnitSelect(E);
	}
	else for(short loop = 0;loop < 2;loop++) // Custom search filters
	{
		if(Event.GetId() == Units_Units_SearchFilters[loop]->GetId())
		{
			ListUnits(UnitCivID, false);
			Units_Units_Search->SetFocus();
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
	}
}

void AGE_Frame::OnKillFocus_Byte(wxFocusEvent& Event)
{
	((TextCtrl_Byte*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Byte*)Event.GetEventObject())->NoLoadList)
	{
		if(Event.GetId() == Civs_GraphicSet->GetId())
		{
			ListCivs();
		}
	}
}

void AGE_Frame::OnKillFocus_ComboBoxByteEffectType(wxFocusEvent& Event)
{
	((ComboBox_Byte_EffectType*)((TextCtrl_Byte*)Event.GetEventObject())->ParentContainer)->OnKillFocus(Event);
	if(!((TextCtrl_Byte*)Event.GetEventObject())->NoLoadList)
	{
		if(Event.GetId() == Effects_Type->GetId())
		{
			ListEffects();
		}
	}
}

void AGE_Frame::OnKillFocus_CheckBoxByte(wxFocusEvent& Event)
{
	((CheckBox_Byte*)((TextCtrl_Byte*)Event.GetEventObject())->ParentContainer)->OnKillFocus(Event);
	if(!((TextCtrl_Byte*)Event.GetEventObject())->NoLoadList)
	{
		if(Event.GetId() == Graphics_AttackSoundUsed->GetId())
		{
			if((GenieFile->Graphics[GraphicID].AttackSounds.size() != GenieFile->Graphics[GraphicID].AngleCount) && GenieFile->Graphics[GraphicID].AttackSoundUsed == 1)
			{
				GenieFile->Graphics[GraphicID].AttackSounds.resize(GenieFile->Graphics[GraphicID].AngleCount);

				wxCommandEvent E;
				OnGraphicsSelect(E);
			}
		}
	}
}

void AGE_Frame::OnKillFocus_ComboBoxShort(wxFocusEvent& Event)
{
	((ComboBox_Short*)((TextCtrl_Short*)Event.GetEventObject())->ParentContainer)->OnKillFocus(Event);
	if(!((TextCtrl_Short*)Event.GetEventObject())->NoLoadList)
	{
		if(Event.GetId() == GraphicDeltas_GraphicID->GetId())
		{
			ListGraphicDeltas();
		}
		else if(Event.GetId() == UnitLineUnits_Units->GetId())
		{
			ListUnitLineUnits();
		}
	}
}

void AGE_Frame::OnKillFocus_ComboBoxLong(wxFocusEvent& Event)
{
	((ComboBox_Long*)((TextCtrl_Long*)Event.GetEventObject())->ParentContainer)->OnKillFocus(Event);
	if(!((TextCtrl_Long*)Event.GetEventObject())->NoLoadList)
	{
		if(Event.GetId() == TechTrees_Ages_Building->GetId())
		{
			ListTTAgesBuildings();
		}
		else if(Event.GetId() == TechTrees_Ages_Unit->GetId())
		{
			ListTTAgesUnits();
		}
		else if(Event.GetId() == TechTrees_Ages_Research->GetId())
		{
			ListTTAgesResearches();
		}
		else if(Event.GetId() == TechTrees_Buildings_ID->GetId())
		{
			ListTTBuildings();
		}
		else if(Event.GetId() == TechTrees_Buildings_Building->GetId())
		{
			ListTTBuildingBuildings();
		}
		else if(Event.GetId() == TechTrees_Buildings_Unit->GetId())
		{
			ListTTBuildingUnits();
		}
		else if(Event.GetId() == TechTrees_Buildings_Research->GetId())
		{
			ListTTBuildingResearches();
		}
		else if(Event.GetId() == TechTrees_Units_ID->GetId())
		{
			ListTTUnits();
		}
		else if(Event.GetId() == TechTrees_Units_Unit->GetId())
		{
			ListTTUnitUnits();
		}
		else if(Event.GetId() == TechTrees_Researches_ID->GetId())
		{
			ListTTResearches();
		}
		else if(Event.GetId() == TechTrees_Researches_Building->GetId())
		{
			ListTTResearchBuildings();
		}
		else if(Event.GetId() == TechTrees_Researches_Unit->GetId())
		{
			ListTTResearchUnits();
		}
		else if(Event.GetId() == TechTrees_Researches_Research->GetId())
		{
			ListTTResearchResearches();
		}
		else if(Event.GetId() == TechTrees_Buildings_UnitOrResearch1->GetId() || Event.GetId() == TechTrees_Buildings_UnitOrResearch2->GetId())
		{
			wxCommandEvent E;
			OnTTBuildingSelect(E);
		}
		else if(Event.GetId() == TechTrees_Units_UnitOrResearch1->GetId() || Event.GetId() == TechTrees_Units_UnitOrResearch2->GetId())
		{
			wxCommandEvent E;
			OnTTUnitSelect(E);
		}
	}
}

void AGE_Frame::OnKillFocus_CheckBoxLong0Y(wxFocusEvent& Event)
{
	((CheckBox_Long_ZeroIsYes*)((TextCtrl_Long*)Event.GetEventObject())->ParentContainer)->OnKillFocus(Event);
	if(!((TextCtrl_Long*)Event.GetEventObject())->NoLoadList)
	{
		if(Event.GetId() == TerRestrict_Unknown1->GetId())
		{
			ListTerrains(false);
		}
	}
}

void AGE_Frame::OnKillFocus_CheckBoxFloat(wxFocusEvent& Event)
{
	((CheckBox_Float*)((TextCtrl_Float*)Event.GetEventObject())->ParentContainer)->OnKillFocus(Event);
	if(!((TextCtrl_Float*)Event.GetEventObject())->NoLoadList)
	{
		if(Event.GetId() == TerRestrict_Accessible->GetId())
		{
			ListTerrains(false);
		}
	}
}

void AGE_Frame::OnKillFocus_AutoCopy_Byte(wxFocusEvent& Event)
{
	((TextCtrl_Byte*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Byte*)Event.GetEventObject())->NoLoadList)
	{
		if(AutoCopy)
		{
			UnitsAutoCopy();
		}
		if(Event.GetId() == DamageGraphics_DamagePercent->GetId())
		{
			ListUnitDamageGraphics();
		}
	}
}

void AGE_Frame::OnKillFocus_AutoCopy_ComboBoxByte(wxFocusEvent& Event)
{
	((ComboBox_Byte*)((TextCtrl_Byte*)Event.GetEventObject())->ParentContainer)->OnKillFocus(Event);
	if(!((TextCtrl_Byte*)Event.GetEventObject())->NoLoadList)
	{
		if(AutoCopy)
		{
			UnitsAutoCopy();
		}
	}
}

void AGE_Frame::OnKillFocus_AutoCopy_CheckBoxBool(wxFocusEvent& Event)
{
	((CheckBox_Bool*)((TextCtrl_Bool*)Event.GetEventObject())->ParentContainer)->OnKillFocus(Event);
	if(!((TextCtrl_Bool*)Event.GetEventObject())->NoLoadList)
	{
		if(AutoCopy)
		{
			UnitsAutoCopy();
		}
	}
}

void AGE_Frame::OnKillFocus_AutoCopy_CheckBoxByte(wxFocusEvent& Event)
{
	((CheckBox_Byte*)((TextCtrl_Byte*)Event.GetEventObject())->ParentContainer)->OnKillFocus(Event);
	if(!((TextCtrl_Byte*)Event.GetEventObject())->NoLoadList)
	{
		if(AutoCopy)
		{
			UnitsAutoCopy();
		}
	}
}

void AGE_Frame::OnKillFocus_Short(wxFocusEvent& Event)
{
	((TextCtrl_Short*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Short*)Event.GetEventObject())->NoLoadList)
	{
		if(Event.GetId() == Effects_A->GetId() || Event.GetId() == Effects_B->GetId() || Event.GetId() == Effects_C->GetId())
		{
			ListEffects();
		}
		else if(Event.GetId() == Borders_BorderFrameID->GetId() || Event.GetId() == Borders_BorderFlag1->GetId() || Event.GetId() == Borders_BorderFlag2->GetId())
		{
			ListTerrainBorderFrames();
		}
	}
}

void AGE_Frame::OnKillFocus_UnShort(wxFocusEvent& Event)
{
	((TextCtrl_UnShort*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_UnShort*)Event.GetEventObject())->NoLoadList)
	{
		if(Event.GetId() == Research_LangDllName->GetId())
		{
			ListResearches();
		}
		else if(Event.GetId() == Research_LangDllDescription->GetId())
		{
			wxCommandEvent E;
			OnResearchSelect(E);
		}
		else if(Event.GetId() == Graphics_AngleCount->GetId())
		{
			if((GenieFile->Graphics[GraphicID].AttackSounds.size() != GenieFile->Graphics[GraphicID].AngleCount) && GenieFile->Graphics[GraphicID].AttackSoundUsed == 1)
			{
				GenieFile->Graphics[GraphicID].AttackSounds.resize(GenieFile->Graphics[GraphicID].AngleCount);

				wxCommandEvent E;
				OnGraphicsSelect(E);
			}
		}
	}
}

void AGE_Frame::OnKillFocus_AutoCopy_Short(wxFocusEvent& Event)
{
	((TextCtrl_Short*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Short*)Event.GetEventObject())->NoLoadList)
	{
		if(AutoCopy)
		{
			UnitsAutoCopy();
		}
		if(Event.GetId() == Attacks_Amount->GetId())
		{
			ListUnitAttacks();
		}
		else if(Event.GetId() == Armors_Amount->GetId())
		{
			ListUnitArmors();
		}
		else if(Event.GetId() == UnitCommands_Type->GetId() || Event.GetId() == UnitCommands_SubType->GetId())
		{
			ListUnitCommands();
		}
	}
}

void AGE_Frame::OnKillFocus_AutoCopy_UnShort(wxFocusEvent& Event)
{
	((TextCtrl_UnShort*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_UnShort*)Event.GetEventObject())->NoLoadList)
	{
		if(AutoCopy)
		{
			UnitsAutoCopy();
		}
		if(Event.GetId() == Units_LanguageDllName->GetId())
		{
			ListUnits(UnitCivID);
		}
		else if(Event.GetId() == Units_LanguageDllCreation->GetId())
		{
			wxCommandEvent E;
			OnUnitsSelect(E);
		}
		else if(Event.GetId() == Units_LanguageDllHelp->GetId())
		{
			wxCommandEvent E;
			OnUnitsSelect(E);
		}
	}
}

void AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort(wxFocusEvent& Event)
{
	((ComboBox_Short*)((TextCtrl_Short*)Event.GetEventObject())->ParentContainer)->OnKillFocus(Event);
	if(!((TextCtrl_Short*)Event.GetEventObject())->NoLoadList)
	{
		if(AutoCopy)
		{
			UnitsAutoCopy();
		}
		if(Event.GetId() == Attacks_Class->GetId())
		{
			ListUnitAttacks();
		}
		else if(Event.GetId() == Armors_Class->GetId())
		{
			ListUnitArmors();
		}
		else if(Event.GetId() == DamageGraphics_GraphicID->GetId())
		{
			ListUnitDamageGraphics();
		}
	}
}

void AGE_Frame::OnKillFocus_AutoCopy_CheckBoxShort(wxFocusEvent& Event)
{
	((CheckBox_Short*)((TextCtrl_Short*)Event.GetEventObject())->ParentContainer)->OnKillFocus(Event);
	if(!((TextCtrl_Short*)Event.GetEventObject())->NoLoadList)
	{
		if(AutoCopy)
		{
			UnitsAutoCopy();
		}
	}
}

void AGE_Frame::OnKillFocus_AutoCopy_CheckBoxShortUnitSheepConversion(wxFocusEvent& Event)
{
	((CheckBox_Short_ZeroIsYes*)((TextCtrl_Short*)Event.GetEventObject())->ParentContainer)->OnKillFocus(Event);
	if(!((TextCtrl_Short*)Event.GetEventObject())->NoLoadList)
	{
		if(AutoCopy)
		{
			UnitsAutoCopy();
		}
	}
}

void AGE_Frame::OnKillFocus_Long(wxFocusEvent& Event)
{
	((TextCtrl_Long*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Long*)Event.GetEventObject())->NoLoadList)
	{
		if(Event.GetId() == TechTrees_Ages_ID->GetId())
		{
			ListTTAgess();
		}
		else if(Event.GetId() == TechTrees_Units_Mode1->GetId() || Event.GetId() == TechTrees_Units_Mode2->GetId())
		{
			wxCommandEvent E;
			OnTTUnitSelect(E);
		}
		else if(Event.GetId() == TechTrees_Buildings_Mode1->GetId() || Event.GetId() == TechTrees_Buildings_Mode2->GetId())
		{
			wxCommandEvent E;
			OnTTBuildingSelect(E);
		}
	}
}

void AGE_Frame::OnKillFocus_AutoCopy_Long(wxFocusEvent& Event)
{
	((TextCtrl_Long*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Long*)Event.GetEventObject())->NoLoadList)
	{
		if(AutoCopy)
		{
			UnitsAutoCopy();
		}
	}
}

void AGE_Frame::OnKillFocus_AutoCopy_ComboBoxLong(wxFocusEvent& Event)
{
	((ComboBox_Long*)((TextCtrl_Long*)Event.GetEventObject())->ParentContainer)->OnKillFocus(Event);
	if(!((TextCtrl_Long*)Event.GetEventObject())->NoLoadList)
	{
		if(AutoCopy)
		{
			UnitsAutoCopy();
		}
	}
}

void AGE_Frame::OnKillFocus_Float(wxFocusEvent& Event)
{
	((TextCtrl_Float*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Float*)Event.GetEventObject())->NoLoadList)
	{
		if(Event.GetId() == Civs_ResourceValue->GetId())
		{
			ListResources();
		}
		else if(Event.GetId() == Effects_D->GetId())
		{
			ListEffects();
		}
	}
}

void AGE_Frame::OnKillFocus_AutoCopy_Float(wxFocusEvent& Event)
{
	((TextCtrl_Float*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_Float*)Event.GetEventObject())->NoLoadList)
	{
		if(AutoCopy)
		{
			UnitsAutoCopy();
		}
	}
}

void AGE_Frame::OnKillFocus_String(wxFocusEvent& Event)
{
	((TextCtrl_String*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_String*)Event.GetEventObject())->NoLoadList)
	{
		string ReducedName;
		if(Event.GetId() == Research_Name[0]->GetId())
		{
			ReducedName = GenieFile->Researchs[ResearchID].Name;
			ReducedName = ReducedName.substr(0, 30);
			GenieFile->Researchs[ResearchID].Name = ReducedName;

			ListResearches();
		}
		else if(Event.GetId() == Research_Name[1]->GetId())
		{
			ReducedName = GenieFile->Researchs[ResearchID].Name2;
			ReducedName = ReducedName.substr(0, 30);
			GenieFile->Researchs[ResearchID].Name2 = ReducedName;

		//	ListResearches();
			wxCommandEvent E;
			OnResearchSelect(E);
		}
		else if(Event.GetId() == Techs_Name->GetId())
		{
			ReducedName = GenieFile->Techages[TechID].Name;
			ReducedName = ReducedName.substr(0, GenieFile->Techages[TechID].getNameSize());
			GenieFile->Techages[TechID].Name = ReducedName;

			ListTechages();
		}
		else if(Event.GetId() == Civs_Name[0]->GetId())
		{
			ReducedName = GenieFile->Civs[CivID].Name;
			ReducedName = ReducedName.substr(0, GenieFile->Civs[CivID].getNameSize());
			GenieFile->Civs[CivID].Name = ReducedName;

			ListCivs();
		}
		else if(Event.GetId() == Civs_Name[1]->GetId())
		{
			ReducedName = GenieFile->Civs[CivID].Name2;
			ReducedName = ReducedName.substr(0, GenieFile->Civs[CivID].getNameSize());
			GenieFile->Civs[CivID].Name2 = ReducedName;

		//	ListCivs();
			wxCommandEvent E;
			OnCivsSelect(E);
		}
		else if(Event.GetId() == Graphics_Name->GetId())
		{
			ReducedName = GenieFile->Graphics[GraphicID].Name;
			ReducedName = ReducedName.substr(0, GenieFile->Graphics[GraphicID].getNameSize());
			GenieFile->Graphics[GraphicID].Name = ReducedName;

			ListGraphics();
		}
		else if(Event.GetId() == Graphics_Name2->GetId())
		{
			ReducedName = GenieFile->Graphics[GraphicID].Name2;
			ReducedName = ReducedName.substr(0, GenieFile->Graphics[GraphicID].getName2Size());
			GenieFile->Graphics[GraphicID].Name2 = ReducedName;

		//	ListGraphics();
			wxCommandEvent E;
			OnGraphicsSelect(E);
		}
		else if(Event.GetId() == Terrains_Name->GetId())
		{
			ReducedName = GenieFile->Terrains[TerrainID].Name;
			ReducedName = ReducedName.substr(0, GenieFile->Terrains[TerrainID].getNameSize());
			GenieFile->Terrains[TerrainID].Name = ReducedName;

			ListTerrains();
		}
		else if(Event.GetId() == Terrains_Name2->GetId())
		{
			ReducedName = GenieFile->Terrains[TerrainID].Name2;
			ReducedName = ReducedName.substr(0, GenieFile->Terrains[TerrainID].getNameSize());
			GenieFile->Terrains[TerrainID].Name2 = ReducedName;

		//	ListTerrains();
			wxCommandEvent E;
			OnTerrainsSelect(E);
		}
		else if(Event.GetId() == SoundItems_Name->GetId())
		{
			ReducedName = GenieFile->Sounds[SoundID].Items[SoundItemID].FileName;
			ReducedName = ReducedName.substr(0, GenieFile->Sounds[SoundID].Items[SoundItemID].getFileNameSize());
			GenieFile->Sounds[SoundID].Items[SoundItemID].FileName = ReducedName;

			ListSoundItems();
		}
		else if(Event.GetId() == Colors_Name->GetId())
		{
			ReducedName = GenieFile->PlayerColours[ColorIDs.Item(0)].Name;
			ReducedName = ReducedName.substr(0, 30);
			GenieFile->PlayerColours[ColorIDs.Item(0)].Name = ReducedName;

			ListPlayerColors();
		}
		else if(Event.GetId() == UnitLines_Name->GetId())
		{
			ReducedName = GenieFile->UnitLines[UnitLineID].Name;
			ReducedName = ReducedName.substr(0, 30);
			GenieFile->UnitLines[UnitLineID].Name = ReducedName;

			ListUnitLines();
		}
		else if(Event.GetId() == Borders_BorderName[0]->GetId())
		{
			ReducedName = GenieFile->TerrainBorders[BorderID].Name;
			ReducedName = ReducedName.substr(0, GenieFile->TerrainBorders[BorderID].getNameSize());
			GenieFile->TerrainBorders[BorderID].Name = ReducedName;

			ListTerrainBorders();
		}
		else if(Event.GetId() == Borders_BorderName[1]->GetId())
		{
			ReducedName = GenieFile->TerrainBorders[BorderID].Name2;
			ReducedName = ReducedName.substr(0, GenieFile->TerrainBorders[BorderID].getNameSize());
			GenieFile->TerrainBorders[BorderID].Name2 = ReducedName;

			ListTerrainBorders();
		}
	}
}

void AGE_Frame::OnKillFocus_AutoCopy_String(wxFocusEvent& Event)
{
	((TextCtrl_String*)Event.GetEventObject())->OnKillFocus(Event);
	if(!((TextCtrl_String*)Event.GetEventObject())->NoLoadList)
	{
		string ReducedName;
		if(AutoCopy)
		{
			UnitsAutoCopy();
		}
		if(Event.GetId() == Units_Name->GetId())
		{
			ReducedName = GenieFile->Civs[UnitCivID].Units[UnitID].Name;
			ReducedName = ReducedName.substr(0, 30);
			GenieFile->Civs[UnitCivID].Units[UnitID].Name = ReducedName;

			ListUnits(UnitCivID);
		}
		else if(Event.GetId() == Units_Name2->GetId())
		{
			ReducedName = GenieFile->Civs[UnitCivID].Units[UnitID].Name2;
			ReducedName = ReducedName.substr(0, 30);
			GenieFile->Civs[UnitCivID].Units[UnitID].Name2 = ReducedName;

			wxCommandEvent E;
			OnUnitsSelect(E);
		}
	}
}

void AGE_Frame::OnUpdate_ComboBoxByteEffectType(wxCommandEvent& Event)
{
	((ComboBox_Byte_EffectType*)Event.GetEventObject())->OnUpdate(Event);
	if(Event.GetId() == Effects_ComboBox_Type->GetId())
	{
		ListEffects();
	}
}

void AGE_Frame::OnUpdate_CheckBoxByte(wxCommandEvent& Event)
{
	((CheckBox_Byte*)Event.GetEventObject())->OnUpdate(Event);
	if(Event.GetId() == Graphics_CheckBox_AttackSoundUsed->GetId())
	{
		if((GenieFile->Graphics[GraphicID].AttackSounds.size() != GenieFile->Graphics[GraphicID].AngleCount) && GenieFile->Graphics[GraphicID].AttackSoundUsed == 1)
		{
			GenieFile->Graphics[GraphicID].AttackSounds.resize(GenieFile->Graphics[GraphicID].AngleCount);

			wxCommandEvent E;
			OnGraphicsSelect(E);
		}
	}
}

void AGE_Frame::OnUpdate_AutoCopy_ComboBoxByte(wxCommandEvent& Event)
{
	((ComboBox_Byte*)Event.GetEventObject())->OnUpdate(Event);
	if(AutoCopy)
	{
		UnitsAutoCopy();
	}
}

void AGE_Frame::OnUpdate_ComboBoxShort(wxCommandEvent& Event)
{
	((ComboBox_Short*)Event.GetEventObject())->OnUpdate(Event);
	if(
		Event.GetId() == Effects_ComboBox_UnitsA->GetId() ||
		Event.GetId() == Effects_ComboBox_ResourcesA->GetId() ||
		Event.GetId() == Effects_ComboBox_ResearchsA->GetId() ||
		Event.GetId() == Units_ComboBox_Class[2]->GetId() ||
		Event.GetId() == Effects_ComboBox_UnitsB->GetId() ||
		Event.GetId() == Effects_ComboBox_ResourcesB->GetId() ||
		Event.GetId() == Effects_ComboBox_AttributesC->GetId()
	)
	{
		ListEffects();
	}
	else if(Event.GetId() == GraphicDeltas_ComboBox_GraphicID->GetId())
	{
		ListGraphicDeltas();
	}
	else if(Event.GetId() == UnitLineUnits_ComboBox_Units->GetId())
	{
		ListUnitLineUnits();
	}
}

void AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort(wxCommandEvent& Event)
{
	((ComboBox_Short*)Event.GetEventObject())->OnUpdate(Event);
	if(AutoCopy)
	{
		UnitsAutoCopy();
	}
	if(Event.GetId() == Attacks_ComboBox_Class[0]->GetId())
	{
		ListUnitAttacks();
	}
	else if(Event.GetId() == Attacks_ComboBox_Class[1]->GetId())
	{
		ListUnitArmors();
	}
	else if(Event.GetId() == DamageGraphics_ComboBox_GraphicID->GetId())
	{
		ListUnitDamageGraphics();
	}
}

void AGE_Frame::OnUpdate_ComboBoxLong(wxCommandEvent& Event)
{
	((ComboBox_Long*)Event.GetEventObject())->OnUpdate(Event);
	if(Event.GetId() == TechTrees_Ages_ComboBox_Building->GetId())
	{
		ListTTAgesBuildings();
	}
	else if(Event.GetId() == TechTrees_Ages_ComboBox_Unit->GetId())
	{
		ListTTAgesUnits();
	}
	else if(Event.GetId() == TechTrees_Ages_ComboBox_Research->GetId())
	{
		ListTTAgesResearches();
	}
	else if(Event.GetId() == TechTrees_Buildings_ComboBox_ID->GetId())
	{
		ListTTBuildings();
	}
	else if(Event.GetId() == TechTrees_Buildings_ComboBox_Building->GetId())
	{
		ListTTBuildingBuildings();
	}
	else if(Event.GetId() == TechTrees_Buildings_ComboBox_Unit->GetId())
	{
		ListTTBuildingUnits();
	}
	else if(Event.GetId() == TechTrees_Buildings_ComboBox_Research->GetId())
	{
		ListTTBuildingResearches();
	}
	else if(Event.GetId() == TechTrees_Units_ComboBox_ID->GetId())
	{
		ListTTUnits();
	}
	else if(Event.GetId() == TechTrees_Units_ComboBox_Unit->GetId())
	{
		ListTTUnitUnits();
	}
	else if(Event.GetId() == TechTrees_Researches_ComboBox_ID->GetId())
	{
		ListTTResearches();
	}
	else if(Event.GetId() == TechTrees_Researches_ComboBox_Building->GetId())
	{
		ListTTResearchBuildings();
	}
	else if(Event.GetId() == TechTrees_Researches_ComboBox_Unit->GetId())
	{
		ListTTResearchUnits();
	}
	else if(Event.GetId() == TechTrees_Researches_ComboBox_Research->GetId())
	{
		ListTTResearchResearches();
	}
}

void AGE_Frame::OnUpdate_CheckBoxLong0Y(wxCommandEvent& Event)
{
	((CheckBox_Long_ZeroIsYes*)Event.GetEventObject())->OnUpdate(Event);
	if(Event.GetId() == TerRestrict_CheckBox_Unknown1->GetId())
	{
		ListTerrains(false);
	}
}

void AGE_Frame::OnUpdate_ComboBoxFloat(wxCommandEvent& Event)
{
	((ComboBox_Float*)Event.GetEventObject())->OnUpdate(Event);
	if(Event.GetId() == Effects_ComboBox_ResearchsD->GetId())
	{
		ListEffects();
	}
}

void AGE_Frame::OnUpdate_CheckBoxFloat(wxCommandEvent& Event)
{
	((CheckBox_Float*)Event.GetEventObject())->OnUpdate(Event);
	if(Event.GetId() == TerRestrict_CheckBox_Accessible->GetId())
	{
		ListTerrains(false);
	}
}

void AGE_Frame::OnUpdate_AutoCopy_ComboBoxLong(wxCommandEvent& Event)
{
	((ComboBox_Long*)Event.GetEventObject())->OnUpdate(Event);
	if(AutoCopy)
	{
		UnitsAutoCopy();
	}
}

void AGE_Frame::OnUpdate_AutoCopy_CheckBoxBool(wxCommandEvent& Event)
{
	((CheckBox_Bool*)Event.GetEventObject())->OnUpdate(Event);
	if(AutoCopy)
	{
		UnitsAutoCopy();
	}
}

void AGE_Frame::OnUpdate_AutoCopy_CheckBoxByte(wxCommandEvent& Event)
{
	((CheckBox_Byte*)Event.GetEventObject())->OnUpdate(Event);
	if(AutoCopy)
	{
		UnitsAutoCopy();
	}
}

void AGE_Frame::OnUpdate_CheckBoxShort(wxCommandEvent& Event)
{
	((CheckBox_Short*)Event.GetEventObject())->OnUpdate(Event);
	if(Event.GetId() == Effects_CheckBox_ModeB->GetId() || Event.GetId() == Effects_CheckBox_ModeC->GetId())
	{
		ListEffects();
	}
}

void AGE_Frame::OnUpdate_AutoCopy_CheckBoxShort(wxCommandEvent& Event)
{
	((CheckBox_Short*)Event.GetEventObject())->OnUpdate(Event);
	if(AutoCopy)
	{
		UnitsAutoCopy();
	}
}

void AGE_Frame::OnUpdate_AutoCopy_CheckBoxShortUnitSheepConversion(wxCommandEvent& Event)
{
	((CheckBox_Short_ZeroIsYes*)Event.GetEventObject())->OnUpdate(Event);
	if(AutoCopy)
	{
		UnitsAutoCopy();
	}
}

AGE_Frame::~AGE_Frame()
{
}
