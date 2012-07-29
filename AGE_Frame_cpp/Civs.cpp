/* AGEFrame_cpp/Civs.cpp */

#include "../AGE_Frame.h"
using boost::lexical_cast;

string AGE_Frame::GetCivName(short &Index)
{
	string Name = "";
	Name = GenieFile->Civs[Index].Name+" ("+lexical_cast<string>((short)GenieFile->Civs[Index].GraphicSet)+")";
	return Name;
}

void AGE_Frame::OnCivsSearch(wxCommandEvent& Event)
{
	ListCivs(false);
}

void AGE_Frame::ListCivs(bool Sized)
{
	string Name;
	SearchText = wxString(Civs_Civs_Search->GetValue()).Lower();
	ExcludeText = wxString(Civs_Civs_Search_R->GetValue()).Lower();
	string CompareText;

	short Selection = Civs_Civs_List->GetSelection();
	if(Civs_Civs_List->GetCount() > 0)
	{
		Civs_Civs_List->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}

	short IDsCount = 4, CivIDs[IDsCount];
	if(Sized)
	{
		CivIDs[0] = Research_ComboBox_Civ->GetSelection();
		CivIDs[1] = Units_Civs_List->GetSelection();
		CivIDs[2] = SoundItems_ComboBox_Civ->GetSelection();
		CivIDs[3] = Units_ComboBox_Civ->GetSelection();

		if(Research_ComboBox_Civ->GetCount() > 0)
		{
			Research_ComboBox_Civ->Clear();
		}
		if(Units_Civs_List->GetCount() > 0)
		{
			Units_Civs_List->Clear();
		}
		if(SoundItems_ComboBox_Civ->GetCount() > 0)
		{
			SoundItems_ComboBox_Civ->Clear();
		}
		if(Units_ComboBox_Civ->GetCount() > 0)
		{
			Units_ComboBox_Civ->Clear();
		}

		for(short loop = 0;loop < IDsCount;loop++)
		{
			if(CivIDs[loop] == wxNOT_FOUND)
			{
				CivIDs[loop] = 0;
			}
		}

		Research_ComboBox_Civ->Append("-1 - None");
		SoundItems_ComboBox_Civ->Append("-1 - None");
		Units_ComboBox_Civ->Append("-1 - None");
	}

	for(short loop = 0;loop < GenieFile->Civs.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetCivName(loop);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText))
		{
			Civs_Civs_List->Append(Name, (void*)&GenieFile->Civs[loop]);
		}
		if(Sized)
		{
			Research_ComboBox_Civ->Append(Name);
			Units_Civs_List->Append(Name);
			SoundItems_ComboBox_Civ->Append(Name);
			Units_ComboBox_Civ->Append(Name);
		}
	}

	Civs_Civs_List->SetSelection(0);
	Civs_Civs_List->SetFirstItem(Selection - 3);
	Civs_Civs_List->SetSelection(Selection);
	if(Sized)
	{
		Research_ComboBox_Civ->SetSelection(CivIDs[0]);
		Units_Civs_List->SetSelection(CivIDs[1]);
		SoundItems_ComboBox_Civ->SetSelection(CivIDs[2]);
		Units_ComboBox_Civ->SetSelection(CivIDs[3]);
	}

	wxCommandEvent E;
	OnCivsSelect(E);
}

void AGE_Frame::OnCivsSelect(wxCommandEvent& Event)
{
	short Selection = Civs_Civs_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = Civs_Civs_List->GetCount() - 1;
			Civs_Civs_List->SetSelection(Selection);
		}
		genie::Civ * CivPointer = (genie::Civ*)Civs_Civs_List->GetClientData(Selection);
		CivID = CivPointer - (&GenieFile->Civs[0]);
		Civs_One->ChangeValue(lexical_cast<string>((short)CivPointer->One));
		Civs_One->Container = &CivPointer->One;
		Civs_Name[0]->ChangeValue(CivPointer->Name);
		Civs_Name[0]->Container = &CivPointer->Name;
		if(GameVersion >= 4)
		{
			Civs_Name[1]->ChangeValue(CivPointer->Name);
			Civs_Name[1]->Container = &CivPointer->Name;
			for(short loop = 0;loop < 4;loop++)
			Civs_SUnknown1[loop]->ChangeValue(lexical_cast<string>(CivPointer->SUnknown1[loop]));
		}
		Civs_TechTree->ChangeValue(lexical_cast<string>(CivPointer->TechTreeID));
		Civs_TechTree->Container = &CivPointer->TechTreeID;
		Civs_ComboBox_TechTree->SetSelection(CivPointer->TechTreeID + 1);
		if(GameVersion >= 2)
		{
			Civs_TeamBonus->ChangeValue(lexical_cast<string>(CivPointer->TeamBonusID));
			Civs_TeamBonus->Container = &CivPointer->TeamBonusID;
		}
		Civs_ComboBox_TeamBonus->SetSelection(CivPointer->TeamBonusID + 1);
		Civs_GraphicSet->ChangeValue(lexical_cast<string>((short)CivPointer->GraphicSet));
		Civs_GraphicSet->Container = &CivPointer->GraphicSet;
		Added = false;
		ListResources();
	}
}

void AGE_Frame::OnCivsAdd(wxCommandEvent& Event)
{
	genie::Civ Temp;
	Temp.Resources.resize(GenieFile->Civs[0].Resources.size());
	Temp.Units.resize(GenieFile->Civs[0].Units.size());
	GenieFile->Civs.push_back(Temp);
	Added = true;
	ListCivs();
}

void AGE_Frame::OnCivsInsert(wxCommandEvent& Event)
{
	short Selection = Civs_Civs_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		genie::Civ Temp;
		Temp.Resources.resize(GenieFile->Civs[0].Resources.size());
		Temp.Units.resize(GenieFile->Civs[0].Units.size());
		GenieFile->Civs.insert(GenieFile->Civs.begin() + CivID, Temp);
		ListCivs();
	}
}

void AGE_Frame::OnCivsDelete(wxCommandEvent& Event)
{
	short Selection = Civs_Civs_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		wxBusyCursor WaitCursor;
		GenieFile->Civs.erase(GenieFile->Civs.begin() + CivID);
		if(Selection == Civs_Civs_List->GetCount() - 1)
		Civs_Civs_List->SetSelection(Selection - 1);
		ListCivs();
	}
}

void AGE_Frame::OnCivsCopy(wxCommandEvent& Event)
{
	short Selection = Civs_Civs_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		CivCopy = *(genie::Civ*)Civs_Civs_List->GetClientData(Selection);
	}
}

void AGE_Frame::OnCivsPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Civs_Civs_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(genie::Civ*)Civs_Civs_List->GetClientData(Selection) = CivCopy;
		ListCivs();
	}
}

string AGE_Frame::GetResourceName(short &Index)
{
	string Name = "";
	if(Index == 0)
	{
		Name = "Food Storage";
	}
	else if(Index == 1)
	{
		if(GameVersion < 4)
		Name = "Wood Storage";
		else
		Name = "Carbon Storage";
	}
	else if(Index == 2)
	{
		if(GameVersion < 4)
		Name = "Stone Storage";
		else
		Name = "Ore Storage";
	}
	else if(Index == 3)
	{
		if(GameVersion < 4)
		Name = "Gold Storage ";
		else
		Name = "Nova Storage ";
	}
	else if(Index == 4)
	{
		Name = "Population Headroom";
	}
	else if(Index == 5)
	{
		if(GameVersion < 4)
		Name = "Conversion Range?";
		else
		Name = "Conversion Range";
	}
	else if(Index == 6)
	{
		Name = "Current Age";
	}
	else if(Index == 7)
	{
		if(GameVersion < 4)
		Name = "Relics Captured";
		else
		Name = "Holocrons Captured";
	}
	else if(Index == 8)
	{
		Name = "Trade Bonus";
	}
	else if(Index == 9)
	{
		Name = "Trade Goods";
	}
	else if(Index == 10)
	{
		if(GameVersion < 4)
		Name = "Trade Production";
		else
		Name = "Shields Recharge Rate";
	}
	else if(Index == 11)
	{
		Name = "Population (Both Current and Headroom)";
	}
	else if(Index == 12)
	{
		Name = "Corpse Decay Time";
	}
	else if(Index == 13)
	{
		Name = "Discovery";
	}
	else if(Index == 14)
	{
		Name = "Monuments/Ruins Captured?";
	}
	else if(Index == 15)
	{
		Name = "Predator Animal Food";
	}
	else if(Index == 16)
	{
		Name = "Crops";
	}
	else if(Index == 17)
	{
		Name = "Fish Storage";
	}
	else if(Index == 18)
	{
		if(GameVersion < 4)
		Name = "Unknown";
		else
		Name = "Power Core Range";
	}
	else if(Index == 19)
	{
		Name = "Total Units Owned";
	}
	else if(Index == 20)
	{
		Name = "Units Killed";
	}
	else if(Index == 21)
	{
		Name = "Research Count";
	}
	else if(Index == 22)
	{
		Name = "% Map Explored";
	}
	else if(Index == 23)
	{
		if(GameVersion < 4)
		Name = "Castle Age?";
		else
		Name = "Submarine Detection";
	}
	else if(Index == 24)
	{
		if(GameVersion < 4)
		Name = "Imperial Age?";
		else
		Name = "Shield Generator Range";
	}
	else if(Index == 25)
	{
		Name = "Feudal Age?";
	}
	else if(Index == 26)
	{
		if(GameVersion < 4)
		Name = "Unknown";
		else
		Name = "Shields' Drop Off Time";
	}
	else if(Index == 27)
	{
		if(GameVersion < 4)
		Name = "Enable Monk Conversion";
		else
		Name = "Enable Jedi Conversion";
	}
	else if(Index == 28)
	{
		Name = "Enable Building Conversion";
	}
	else if(Index == 30)
	{
		Name = "Building Limit";
	}
	else if(Index == 31)
	{
		if(GameVersion < 4)
		Name = "Food Limit";
		else
		Name = "Enable A-A Attack For AT-AT";
	}
	else if(Index == 32)
	{
		if(GameVersion < 2)
		Name = "Unit Limit";
		else
		Name = "Bonus Population";
	}
	else if(Index == 33)
	{
		if(GameVersion < 4)
		Name = "Maintenance";
		else
		Name = "Power Core Shielding";
	}
	else if(Index == 34)
	{
		if(GameVersion < 4)
		Name = "Faith";
		else
		Name = "Force";
	}
	else if(Index == 35)
	{
		if(GameVersion < 4)
		Name = "Faith Recharging Rate";
		else
		Name = "Force Recharging Rate";
	}
	else if(Index == 36)
	{
		Name = "Farm Food Amount";
	}
	else if(Index == 37)
	{
		Name = "Civilian Units (Villager High)";
	}
	else if(Index == 38)
	{
		if(GameVersion < 4)
		Name = "Unknown";
		else
		Name = "Shields On For Bombers/Fighters";
	}
	else if(Index == 39)
	{
		Name = "All Techs Achieved";
	}
	else if(Index == 40)
	{
		Name = "Military Units (Largest Army)";
	}
	else if(Index == 41)
	{
		Name = "Units Converted";
	}
	else if(Index == 42)
	{
		Name = "Standing? Wonders";
	}
	else if(Index == 43)
	{
		Name = "Buildings Razed";
	}
	else if(Index == 44)
	{
		Name = "Kill Ratio";
	}
	else if(Index == 45)
	{
		Name = "Survival to Finish";
	}
	else if(Index == 46)
	{
		Name = "Tribute Fee";
	}
	else if(Index == 47)
	{
		if(GameVersion < 4)
		Name = "Gold Mining Productivity";
		else
		Name = "Nova Mining Productivity";
	}
	else if(Index == 48)
	{
		Name = "Town Center Unavailable";
	}
	else if(Index == 49)
	{
		Name = "Gold Counter";
	}
	else if(Index == 50)
	{
		Name = "Reveal Ally";
	}
	else if(Index == 51)
	{
		if(GameVersion < 4)
		Name = "Houses (Unused)";
		else
		Name = "Shielding";
	}
	else if(Index == 52)
	{
		Name = "Monastery Count";
	}
	else if(Index == 53)
	{
		Name = "Tribute Sent";
	}
	else if(Index == 54)
	{
		Name = "All Ruins Have Been Captured";
	}
	else if(Index == 55)
	{
		Name = "All Relics Have Been Captured";
	}
	else if(Index == 56)
	{
		if(GameVersion < 4)
		Name = "Ore Storage? Unit Unload Room?";
		else
		Name = "Enable Stealth For Masters";
	}
	else if(Index == 57)
	{
		Name = "Captured Unit";
	}
	else if(Index == 58)
	{
		if(GameVersion < 4)
		Name = "Dark Age?";
		else
		Name = "Masters Can See Hidden Units";
	}
	else if(Index == 59)
	{
		Name = "Trade Good Quality";
	}
	else if(Index == 60)
	{
		Name = "Trade Market Level";
	}
	else if(Index == 61)
	{
		Name = "Formations";
	}
	else if(Index == 62)
	{
		Name = "Building Housing Rate";
	}
	else if(Index == 63)
	{
		Name = "Gather Tax Rate";
	}
	else if(Index == 64)
	{
		Name = "Gather Accumulator";
	}
	else if(Index == 65)
	{
		Name = "Salvage Decay Rate";
	}
	else if(Index == 66)
	{
		Name = "Ages? Allow Formations?";
	}
	else if(Index == 67)
	{
		Name = "Conversions";
	}
	else if(Index == 68)
	{
		Name = "Hit Points Killed (Unused)";
	}
	else if(Index == 69)
	{
		Name = "Killed P1";
	}
	else if(Index == 70)
	{
		Name = "Killed P2";
	}
	else if(Index == 71)
	{
		Name = "Killed P3";
	}
	else if(Index == 72)
	{
		Name = "Killed P4";
	}
	else if(Index == 73)
	{
		Name = "Killed P5";
	}
	else if(Index == 74)
	{
		Name = "Killed P6";
	}
	else if(Index == 75)
	{
		Name = "Killed P7";
	}
	else if(Index == 76)
	{
		Name = "Killed P8";
	}
	else if(Index == 77)
	{
		Name = "Conversion Resistance";
	}
	else if(Index == 78)
	{
		Name = "Trade Fee";
	}
	else if(Index == 79)
	{
		if(GameVersion < 4)
		Name = "Stone Mining Productivity";
		else
		Name = "Ore Mining Productivity";
	}
	else if(Index == 80)
	{
		Name = "Queued Units";
	}
	else if(Index == 81)
	{
		Name = "Training Count";
	}
	else if(Index == 82)
	{
		Name = "Start With Packed Town Center / Raider";
	}
	else if(Index == 83)
	{
		Name = "Boarding Recharge Rate";
	}
	else if(Index == 84)
	{
		Name = "Starting Villagers";
	}
	else if(Index == 85)
	{
		Name = "Researches' Cost Multiplier";
	}
	else if(Index == 86)
	{
		Name = "Researches' Time Multiplier";
	}
	else if(Index == 87)
	{
		if(GameVersion < 4)
		Name = "Convert Ships";
		else
		Name = "Concentration";
	}
	else if(Index == 88)
	{
		Name = "Fish Trap Food Amount";
	}
	else if(Index == 89)
	{
		if(GameVersion < 4)
		Name = "Bonus Healing Rate";
		else
		Name = "Medic Healing Rate";
	}
	else if(Index == 90)
	{
		Name = "Healing Range";
	}
	else if(Index == 91)
	{
		Name = "Bonus Starting Food";
	}
	else if(Index == 92)
	{
		if(GameVersion < 4)
		Name = "Bonus Starting Wood";
		else
		Name = "Bonus Starting Carbon";
	}
	else if(Index == 93)
	{
		if(GameVersion < 4)
		Name = "Bonus Starting Stone";
		else
		Name = "Bonus Starting Ore";
	}
	else if(Index == 94)
	{
		if(GameVersion < 4)
		Name = "Bonus Starting Gold";
		else
		Name = "Bonus Starting Nova";
	}
	else if(Index == 95)
	{
		Name = "Enable Town Center Packing / Raider Ability";
	}
	else if(Index == 96)
	{
		Name = "Self Healing Seconds (Berserkers)";
	}
	else if(Index == 97)
	{
		Name = "Sheep/Turkey Dominant LOS";
	}
	else if(Index == 98)
	{
		Name = "Score: Economy (Object Cost Summation)";
	}
	else if(Index == 99)
	{
		Name = "Score: Technology";
	}
	else if(Index == 100)
	{
		if(GameVersion < 4)
		Name = "Relic Gold (Collected)";
		else
		Name = "Holocron Nova (Collected)";
	}
	else if(Index == 101)
	{
		Name = "Trade Profit";
	}
	else if(Index == 102)
	{
		Name = "P1 Tribute";
	}
	else if(Index == 103)
	{
		Name = "P2 Tribute";
	}
	else if(Index == 104)
	{
		Name = "P3 Tribute";
	}
	else if(Index == 105)
	{
		Name = "P4 Tribute";
	}
	else if(Index == 106)
	{
		Name = "P5 Tribute";
	}
	else if(Index == 107)
	{
		Name = "P6 Tribute";
	}
	else if(Index == 108)
	{
		Name = "P7 Tribute";
	}
	else if(Index == 109)
	{
		Name = "P8 Tribute";
	}
	else if(Index == 110)
	{
		Name = "P1 Kill Score";
	}
	else if(Index == 111)
	{
		Name = "P2 Kill Score";
	}
	else if(Index == 112)
	{
		Name = "P3 Kill Score";
	}
	else if(Index == 113)
	{
		Name = "P4 Kill Score";
	}
	else if(Index == 114)
	{
		Name = "P5 Kill Score";
	}
	else if(Index == 115)
	{
		Name = "P6 Kill Score";
	}
	else if(Index == 116)
	{
		Name = "P7 Kill Score";
	}
	else if(Index == 117)
	{
		Name = "P8 Kill Score";
	}
	else if(Index == 118)
	{
		Name = "P1 Razings";
	}
	else if(Index == 119)
	{
		Name = "P2 Razings";
	}
	else if(Index == 120)
	{
		Name = "P3 Razings";
	}
	else if(Index == 121)
	{
		Name = "P4 Razings";
	}
	else if(Index == 122)
	{
		Name = "P5 Razings";
	}
	else if(Index == 123)
	{
		Name = "P6 Razings";
	}
	else if(Index == 124)
	{
		Name = "P7 Razings";
	}
	else if(Index == 125)
	{
		Name = "P8 Razings";
	}
	else if(Index == 126)
	{
		Name = "P1 Razing Score";
	}
	else if(Index == 127)
	{
		Name = "P2 Razing Score";
	}
	else if(Index == 128)
	{
		Name = "P3 Razing Score";
	}
	else if(Index == 129)
	{
		Name = "P4 Razing Score";
	}
	else if(Index == 130)
	{
		Name = "P5 Razing Score";
	}
	else if(Index == 131)
	{
		Name = "P6 Razing Score";
	}
	else if(Index == 132)
	{
		Name = "P7 Razing Score";
	}
	else if(Index == 133)
	{
		Name = "P8 Razing Score";
	}
	else if(Index == 134)
	{
		Name = "Standing Castles";
	}
	else if(Index == 135)
	{
		Name = "Hit Points Razings (Unused)";
	}
	else if(Index == 136)
	{
		Name = "Kills By P1";
	}
	else if(Index == 137)
	{
		Name = "Kills By P2";
	}
	else if(Index == 138)
	{
		Name = "Kills By P3";
	}
	else if(Index == 139)
	{
		Name = "Kills By P4";
	}
	else if(Index == 140)
	{
		Name = "Kills By P5";
	}
	else if(Index == 141)
	{
		Name = "Kills By P6";
	}
	else if(Index == 142)
	{
		Name = "Kills By P7";
	}
	else if(Index == 143)
	{
		Name = "Kills By P8";
	}
	else if(Index == 144)
	{
		Name = "Razings By P1";
	}
	else if(Index == 145)
	{
		Name = "Razings By P2";
	}
	else if(Index == 146)
	{
		Name = "Razings By P3";
	}
	else if(Index == 147)
	{
		Name = "Razings By P4";
	}
	else if(Index == 148)
	{
		Name = "Razings By P5";
	}
	else if(Index == 149)
	{
		Name = "Razings By P6";
	}
	else if(Index == 150)
	{
		Name = "Razings By P7";
	}
	else if(Index == 151)
	{
		Name = "Razings By P8";
	}
	else if(Index == 152)
	{
		Name = "Units Lost Score";
	}
	else if(Index == 153)
	{
		Name = "Buildings Lost Score";
	}
	else if(Index == 154)
	{
		Name = "Units Lost";
	}
	else if(Index == 155)
	{
		Name = "Buildings Lost";
	}
	else if(Index == 156)
	{
		Name = "Tribute From P1";
	}
	else if(Index == 157)
	{
		Name = "Tribute From P2";
	}
	else if(Index == 158)
	{
		Name = "Tribute From P3";
	}
	else if(Index == 159)
	{
		Name = "Tribute From P4";
	}
	else if(Index == 160)
	{
		Name = "Tribute From P5";
	}
	else if(Index == 161)
	{
		Name = "Tribute From P6";
	}
	else if(Index == 162)
	{
		Name = "Tribute From P7";
	}
	else if(Index == 163)
	{
		Name = "Tribute From P8";
	}
	else if(Index == 164)
	{
		Name = "Current Units Score";
	}
	else if(Index == 165)
	{
		Name = "Current Buildings Score";
	}
	else if(Index == 166)
	{
		Name = "Food Collected";
	}
	else if(Index == 167)
	{
		if(GameVersion < 4)
		Name = "Wood Collected";
		else
		Name = "Carbon Collected";
	}
	else if(Index == 168)
	{
		if(GameVersion < 4)
		Name = "Stone Collected";
		else
		Name = "Ore Collected";
	}
	else if(Index == 169)
	{
		if(GameVersion < 4)
		Name = "Gold Collected";
		else
		Name = "Nova Collected";
	}
	else if(Index == 170)
	{
		Name = "Score: Military";
	}
	else if(Index == 171)
	{
		Name = "Tribute Received";
	}
	else if(Index == 172)
	{
		Name = "Razing Score";
	}
	else if(Index == 173)
	{
		if(GameVersion < 4)
		Name = "Total Castles";
		else
		Name = "Total Fortresses";
	}
	else if(Index == 174)
	{
		if(GameVersion < 4)
		Name = "Total Wonders";
		else
		Name = "Total Monuments";
	}
	else if(Index == 175)
	{
		Name = "Score: Economy (Tribute)";
	}
	else if(Index == 176)
	{
		Name = "Convert Min Adjustment";
	}
	else if(Index == 177)
	{
		Name = "Convert Max Adjustment";
	}
	else if(Index == 178)
	{
		Name = "Convert Resist Min Adjustment";
	}
	else if(Index == 179)
	{
		Name = "Convert Resist Max Adjustment";
	}
	else if(Index == 180)
	{
		Name = "Convert Building Min";
	}
	else if(Index == 181)
	{
		Name = "Convert Building Max";
	}
	else if(Index == 182)
	{
		Name = "Convert Building Chance";
	}
	else if(Index == 183)
	{
		Name = "Reveal Enemy";
	}
	else if(Index == 184)
	{
		Name = "Score: Society";
	}
	else if(Index == 185)
	{
		Name = "Food Score";
	}
	else if(Index == 186)
	{
		if(GameVersion < 4)
		Name = "Wood Score";
		else
		Name = "Carbon Score";
	}
	else if(Index == 187)
	{
		if(GameVersion < 4)
		Name = "Stone Score";
		else
		Name = "Ore Score";
	}
	else if(Index == 188)
	{
		if(GameVersion < 4)
		Name = "Gold Score";
		else
		Name = "Nova Score";
	}
	else if(Index == 189)
	{
		if(GameVersion < 4)
		Name = "Chopping Productivity";
		else
		Name = "Carbon Gathering Productivity";
	}
	else if(Index == 190)
	{
		Name = "Food-gathering Productivity";
	}
	else if(Index == 191)
	{
		if(GameVersion < 4)
		Name = "Relic Gold Production Rate";
		else
		Name = "Holocron Nova Production Rate";
	}
	else if(Index == 192)
	{
		Name = "Units Converted By Enemy Die";
	}
	else if(Index == 193)
	{
		if(GameVersion < 4)
		Name = "Theocracy";
		else
		Name = "Meditation";
	}
	else if(Index == 194)
	{
		Name = "Crenellations";
	}
	else if(Index == 195)
	{
		Name = "Construction Rate (Except Wonder)";
	}
	else if(Index == 196)
	{
		if(GameVersion < 4)
		Name = "Wonder Bonus";
		else
		Name = "Biological Self Regeneration";
	}
	else if(Index == 197)
	{
		Name = "Spies Discount";
	}
	else
	{
		Name = "Unknown";
	}
	return Name;
}

void AGE_Frame::OnResourcesSearch(wxCommandEvent& Event)
{
	ListResources(false);
}

void AGE_Frame::ListResources(bool Sized)
{
	string Name;
	SearchText = wxString(Civs_Resources_Search->GetValue()).Lower();
	ExcludeText = wxString(Civs_Resources_Search_R->GetValue()).Lower();
	string CompareText;

	short Selection = Civs_Resources_List->GetSelection();
	if(Civs_Resources_List->GetCount() > 0)
	{
		Civs_Resources_List->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}

	short IDsCount = 13, ResourceIDs[IDsCount];
	if(Sized)
	{
		for(short loop = 0;loop < 3;loop++)
		{
			ResourceIDs[loop] = Units_ComboBox_CostType[loop]->GetSelection();
			ResourceIDs[loop+3] = ResourceStorage_ComboBox_Type[loop]->GetSelection();
			ResourceIDs[loop+8] = Research_ComboBox_Resources[loop]->GetSelection();
		}
		ResourceIDs[6] = UnitCommands_ComboBox_ResourceIn->GetSelection();
		ResourceIDs[7] = UnitCommands_ComboBox_ResourceOut->GetSelection();
		ResourceIDs[11] = Effects_ComboBox_ResourcesA->GetSelection();
		ResourceIDs[12] = Effects_ComboBox_ResourcesB->GetSelection();

		for(short loop = 0;loop < 3;loop++)
		{
			if(Units_ComboBox_CostType[loop]->GetCount() > 0)
			{
				Units_ComboBox_CostType[loop]->Clear();
			}
			if(ResourceStorage_ComboBox_Type[loop]->GetCount() > 0)
			{
				ResourceStorage_ComboBox_Type[loop]->Clear();
			}
			if(Research_ComboBox_Resources[loop]->GetCount() > 0)
			{
				Research_ComboBox_Resources[loop]->Clear();
			}
		}
		if(UnitCommands_ComboBox_ResourceIn->GetCount() > 0)
		{
			UnitCommands_ComboBox_ResourceIn->Clear();
		}
		if(UnitCommands_ComboBox_ResourceOut->GetCount() > 0)
		{
			UnitCommands_ComboBox_ResourceOut->Clear();
		}
		if(Effects_ComboBox_ResourcesA->GetCount() > 0)
		{
			Effects_ComboBox_ResourcesA->Clear();
		}
		if(Effects_ComboBox_ResourcesB->GetCount() > 0)
		{
			Effects_ComboBox_ResourcesB->Clear();
		}

		for(short loop = 0;loop < IDsCount;loop++)
		{
			if(ResourceIDs[loop] == wxNOT_FOUND)
			{
				ResourceIDs[loop] = 0;
			}
		}

		for(short loop = 0;loop < 3;loop++)
		{
			Units_ComboBox_CostType[loop]->Append("-1 - None");
			ResourceStorage_ComboBox_Type[loop]->Append("-1 - None");
			Research_ComboBox_Resources[loop]->Append("-1 - None");
		}
		UnitCommands_ComboBox_ResourceIn->Append("-1 - None");
		UnitCommands_ComboBox_ResourceOut->Append("-1 - None");
		Effects_ComboBox_ResourcesA->Append("-1 - None");
		Effects_ComboBox_ResourcesB->Append("-1 - None");
	}

	for(short loop = 0;loop < GenieFile->Civs[CivID].Resources.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - Value: "+lexical_cast<string>(GenieFile->Civs[CivID].Resources[loop])+" - "+GetResourceName(loop);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText))
		{
			Civs_Resources_List->Append(Name, (void*)&GenieFile->Civs[CivID].Resources[loop]);
		}
		if(Sized)
		{
			Name = " "+lexical_cast<string>(loop)+" - "+GetResourceName(loop);
			for(short loop = 0;loop < 3;loop++)
			{
				Units_ComboBox_CostType[loop]->Append(Name);
				ResourceStorage_ComboBox_Type[loop]->Append(Name);
				Research_ComboBox_Resources[loop]->Append(Name);
			}
			UnitCommands_ComboBox_ResourceIn->Append(Name);
			UnitCommands_ComboBox_ResourceOut->Append(Name);
			Effects_ComboBox_ResourcesA->Append(Name);
			Effects_ComboBox_ResourcesB->Append(Name);
		}
	}

	Civs_Resources_List->SetSelection(0);
	Civs_Resources_List->SetFirstItem(Selection - 3);
	Civs_Resources_List->SetSelection(Selection);
	if(Sized)
	{
		for(short loop = 0;loop < 3;loop++)
		{
			Units_ComboBox_CostType[loop]->SetSelection(ResourceIDs[loop]);
			ResourceStorage_ComboBox_Type[loop]->SetSelection(ResourceIDs[loop+3]);
			Research_ComboBox_Resources[loop]->SetSelection(ResourceIDs[loop+8]);
		}
		UnitCommands_ComboBox_ResourceIn->SetSelection(ResourceIDs[6]);
		UnitCommands_ComboBox_ResourceOut->SetSelection(ResourceIDs[7]);
		Effects_ComboBox_ResourcesA->SetSelection(ResourceIDs[11]);
		Effects_ComboBox_ResourcesB->SetSelection(ResourceIDs[12]);
	}

	wxCommandEvent E;
	OnResourcesSelect(E);
}

void AGE_Frame::OnResourcesSelect(wxCommandEvent& Event)
{
	short Selection = Civs_Resources_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = Civs_Resources_List->GetCount() - 1;
			Civs_Resources_List->SetSelection(Selection);
		}
		float * CivResourcePointer = (float*)Civs_Resources_List->GetClientData(Selection);
		ResourceID = CivResourcePointer - (&GenieFile->Civs[CivID].Resources[0]);
		Civs_ResourceValue->ChangeValue(lexical_cast<string>(*CivResourcePointer));
		Civs_ResourceValue->Container = CivResourcePointer;
		Added = false;
	}
}

void AGE_Frame::OnResourcesAdd(wxCommandEvent& Event)
{
	short Selection = Civs_Civs_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		float Temp = 0;
		for(short loop = 0;loop < GenieFile->Civs.size();loop++)
		GenieFile->Civs[loop].Resources.push_back(Temp);
		Added = true;
		ListResources();
	}
}

void AGE_Frame::OnResourcesInsert(wxCommandEvent& Event)
{
	short Selection = Civs_Resources_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		float Temp = 0;
		for(short loop = 0;loop < GenieFile->Civs.size();loop++)
		GenieFile->Civs[loop].Resources.insert(GenieFile->Civs[loop].Resources.begin() + ResourceID, Temp);
		ListResources();
	}
}

void AGE_Frame::OnResourcesDelete(wxCommandEvent& Event)
{
	short Selection = Civs_Resources_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		wxBusyCursor WaitCursor;
		for(short loop = 0;loop < GenieFile->Civs.size();loop++)
		GenieFile->Civs[loop].Resources.erase(GenieFile->Civs[loop].Resources.begin() + ResourceID);
		if(Selection == Civs_Resources_List->GetCount() - 1)
		Civs_Resources_List->SetSelection(Selection - 1);
		ListResources();
	}
}

void AGE_Frame::OnResourcesCopy(wxCommandEvent& Event)
{
	short Selection = Civs_Resources_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		ResourceCopy = *(float*)Civs_Resources_List->GetClientData(Selection);
	}
}

void AGE_Frame::OnResourcesPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Civs_Resources_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		*(float*)Civs_Resources_List->GetClientData(Selection) = ResourceCopy;
		ListResources();
	}
}

void AGE_Frame::OnResourcesCopyToAll(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Civs_Resources_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		float Copy = GenieFile->Civs[CivID].Resources[ResourceID];
		for(short loop = 0;loop < GenieFile->Civs.size();loop++)
		GenieFile->Civs[loop].Resources[ResourceID] = Copy;
	}
}

void AGE_Frame::CreateCivControls()
{

	Civs_Main = new wxBoxSizer(wxHORIZONTAL);
	Civs_ListArea = new wxBoxSizer(wxVERTICAL);
	Civs_Civs_Buttons = new wxGridSizer(3, 0, 0);
	Tab_Civs = new wxPanel(TabBar_Data, wxID_ANY, wxDefaultPosition, wxSize(0, 20));

	Civs_Civs = new wxStaticBoxSizer(wxVERTICAL, Tab_Civs, "Civilizations");
	Civs_Civs_Search = new wxTextCtrl(Tab_Civs, wxID_ANY);
	Civs_Civs_Search_R = new wxTextCtrl(Tab_Civs, wxID_ANY);
	Civs_Civs_List = new wxListBox(Tab_Civs, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	Civs_Add = new wxButton(Tab_Civs, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Civs_Insert = new wxButton(Tab_Civs, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	Civs_Delete = new wxButton(Tab_Civs, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Civs_Copy = new wxButton(Tab_Civs, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Civs_Paste = new wxButton(Tab_Civs, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));

	Civs_DataArea = new wxBoxSizer(wxVERTICAL);
	Civs_DataGrid1 = new wxGridSizer(2, 0, 5);
	Civs_DataGrid2 = new wxGridSizer(2, 0, 5);
	Civs_DataGrid3 = new wxGridSizer(2, 0, 0);
	Civs_Holder_One = new wxBoxSizer(wxVERTICAL);
	Civs_Text_One = new wxStaticText(Tab_Civs, wxID_ANY, " Always One", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Civs_One = new TextCtrl_Byte(Tab_Civs, "0", NULL);
	Civs_Holder_Name[0] = new wxBoxSizer(wxVERTICAL);
	Civs_Text_Name[0] = new wxStaticText(Tab_Civs, wxID_ANY, " Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Civs_Name[0] = new TextCtrl_String(Tab_Civs, "0", NULL);
	Civs_Holder_Name[1] = new wxBoxSizer(wxVERTICAL);
	Civs_Text_Name[1] = new wxStaticText(Tab_Civs, wxID_ANY, " Name 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Civs_Name[1] = new TextCtrl_String(Tab_Civs, "0", NULL);
	Civs_Holder_TechTree = new wxBoxSizer(wxVERTICAL);
	Civs_Text_TechTree = new wxStaticText(Tab_Civs, wxID_ANY, " Technology Tree", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Civs_TechTree = new TextCtrl_Short(Tab_Civs, "0", NULL);
	Civs_Holder_SUnknown1 = new wxBoxSizer(wxVERTICAL);
	Civs_Text_SUnknown1 = new wxStaticText(Tab_Civs, wxID_ANY, " Unique Units / Researches", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0;loop < 4;loop++)
	Civs_SUnknown1[loop] = new TextCtrl_Short(Tab_Civs, "0", NULL);
	Civs_ComboBox_TechTree = new ComboBox_Short(Tab_Civs, Civs_TechTree);
	Civs_Holder_TeamBonus = new wxBoxSizer(wxVERTICAL);
	Civs_Text_TeamBonus = new wxStaticText(Tab_Civs, wxID_ANY, " Team Bonus", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Civs_TeamBonus = new TextCtrl_Short(Tab_Civs, "0", NULL);
	Civs_ComboBox_TeamBonus = new ComboBox_Short(Tab_Civs, Civs_TeamBonus);
	Civs_Holder_GraphicSet = new wxBoxSizer(wxVERTICAL);
	Civs_Text_GraphicSet = new wxStaticText(Tab_Civs, wxID_ANY, " Graphic Set", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Civs_GraphicSet = new TextCtrl_Byte(Tab_Civs, "0", NULL);

	Civs_Holder_Resources = new wxBoxSizer(wxVERTICAL);
	Civs_Resources = new wxStaticBoxSizer(wxVERTICAL, Tab_Civs, "Initial Resources");
	Civs_Resources_Search = new wxTextCtrl(Tab_Civs, wxID_ANY);
	Civs_Resources_Search_R = new wxTextCtrl(Tab_Civs, wxID_ANY);
	Civs_Resources_List = new wxListBox(Tab_Civs, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	Civs_Resources_Buttons = new wxGridSizer(3, 0, 0);
	Resources_Add = new wxButton(Tab_Civs, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Resources_Insert = new wxButton(Tab_Civs, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	Resources_Delete = new wxButton(Tab_Civs, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Resources_Copy = new wxButton(Tab_Civs, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Resources_Paste = new wxButton(Tab_Civs, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Resources_CopyToAll = new wxButton(Tab_Civs, wxID_ANY, "Copy to all civs", wxDefaultPosition, wxSize(5, 20));
	Civs_Resources_Data = new wxBoxSizer(wxVERTICAL);
	Civs_Holder_ResourceValue = new wxBoxSizer(wxVERTICAL);
	Civs_Text_ResourceValue = new wxStaticText(Tab_Civs, wxID_ANY, " Resource Value", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Civs_ResourceValue = new TextCtrl_Float(Tab_Civs, "0", NULL);
	Civs_Holder_Resources_Link = new wxHyperlinkCtrl(Tab_Civs, wxID_ANY, "GenieWiki Resource List", "http://www.digitization.org/wiki/index.php?title=Resource");

	Civs_Civs_Buttons->Add(Civs_Add, 1, wxEXPAND);
	Civs_Civs_Buttons->Add(Civs_Insert, 1, wxEXPAND);
	Civs_Civs_Buttons->Add(Civs_Delete, 1, wxEXPAND);
	Civs_Civs_Buttons->Add(Civs_Copy, 1, wxEXPAND);
	Civs_Civs_Buttons->Add(Civs_Paste, 1, wxEXPAND);

	Civs_Civs->Add(Civs_Civs_Search, 0, wxEXPAND);
	Civs_Civs->Add(Civs_Civs_Search_R, 0, wxEXPAND);
	Civs_Civs->Add(-1, 2);
	Civs_Civs->Add(Civs_Civs_List, 1, wxEXPAND);
	Civs_Civs->Add(-1, 2);
	Civs_Civs->Add(Civs_Civs_Buttons, 0, wxEXPAND);

	Civs_ListArea->Add(-1, 10);
	Civs_ListArea->Add(Civs_Civs, 1, wxEXPAND);
	Civs_ListArea->Add(-1, 10);

	Civs_Holder_One->Add(Civs_Text_One, 0, wxEXPAND);
	Civs_Holder_One->Add(Civs_One, 1, wxEXPAND);
	for(short loop = 0;loop < 2;loop++){
	Civs_Holder_Name[loop]->Add(Civs_Text_Name[loop], 0, wxEXPAND);
	Civs_Holder_Name[loop]->Add(Civs_Name[loop], 1, wxEXPAND);}
	Civs_Holder_SUnknown1->Add(Civs_Text_SUnknown1, 0, wxEXPAND);
	Civs_Holder_SUnknown1->Add(Civs_DataGrid3, 1, wxEXPAND);
	for(short loop = 0;loop < 4;loop++)
	Civs_DataGrid3->Add(Civs_SUnknown1[loop], 1, wxEXPAND);
	Civs_Holder_TechTree->Add(Civs_Text_TechTree, 0, wxEXPAND);
	Civs_Holder_TechTree->Add(Civs_TechTree, 1, wxEXPAND);
	Civs_Holder_TechTree->Add(Civs_ComboBox_TechTree, 1, wxEXPAND);
	Civs_Holder_TeamBonus->Add(Civs_Text_TeamBonus, 0, wxEXPAND);
	Civs_Holder_TeamBonus->Add(Civs_TeamBonus, 1, wxEXPAND);
	Civs_Holder_TeamBonus->Add(Civs_ComboBox_TeamBonus, 1, wxEXPAND);
	Civs_Holder_GraphicSet->Add(Civs_Text_GraphicSet, 0, wxEXPAND);
	Civs_Holder_GraphicSet->Add(Civs_GraphicSet, 1, wxEXPAND);

	Civs_DataGrid1->Add(Civs_Holder_GraphicSet, 1, wxEXPAND);
	Civs_DataGrid1->Add(Civs_Holder_One, 1, wxEXPAND);
	Civs_DataGrid2->Add(Civs_Holder_TechTree, 1, wxEXPAND);
	Civs_DataGrid2->Add(Civs_Holder_TeamBonus, 1, wxEXPAND);

	Civs_DataArea->Add(-1, 10);
	Civs_DataArea->Add(Civs_Holder_Name[0], 0, wxEXPAND);
	Civs_DataArea->Add(Civs_Holder_Name[1], 0, wxEXPAND);
	Civs_DataArea->Add(-1, 5);
	Civs_DataArea->Add(Civs_DataGrid1, 0, wxEXPAND);
	Civs_DataArea->Add(-1, 5);
	Civs_DataArea->Add(Civs_DataGrid2, 0, wxEXPAND);
	Civs_DataArea->Add(-1, 5);
	Civs_DataArea->Add(Civs_Holder_SUnknown1, 0, wxEXPAND);

	Civs_Resources_Buttons->Add(Resources_Add, 1, wxEXPAND);
	Civs_Resources_Buttons->Add(Resources_Insert, 1, wxEXPAND);
	Civs_Resources_Buttons->Add(Resources_Delete, 1, wxEXPAND);
	Civs_Resources_Buttons->Add(Resources_Copy, 1, wxEXPAND);
	Civs_Resources_Buttons->Add(Resources_Paste, 1, wxEXPAND);
	Civs_Resources_Buttons->Add(Resources_CopyToAll, 1, wxEXPAND);

	Civs_Holder_ResourceValue->Add(Civs_Text_ResourceValue, 0, wxEXPAND);
	Civs_Holder_ResourceValue->Add(Civs_ResourceValue, 1, wxEXPAND);

	Civs_Resources_Data->Add(Civs_Holder_ResourceValue, 0, wxEXPAND);

	Civs_Resources->Add(Civs_Resources_Search, 0, wxEXPAND);
	Civs_Resources->Add(Civs_Resources_Search_R, 0, wxEXPAND);
	Civs_Resources->Add(Civs_Resources_Data, 0, wxEXPAND);
	Civs_Resources->Add(Civs_Resources_List, 1, wxEXPAND);
	Civs_Resources->Add(Civs_Resources_Buttons, 0, wxEXPAND);

	Civs_Holder_Resources->Add(-1, 10);
	Civs_Holder_Resources->Add(Civs_Resources, 1, wxEXPAND);
	Civs_Holder_Resources->Add(Civs_Holder_Resources_Link, 0, wxEXPAND);
	Civs_Holder_Resources->Add(-1, 10);

	Civs_Main->Add(10, -1);
	Civs_Main->Add(Civs_ListArea, 2, wxEXPAND);
	Civs_Main->Add(10, -1);
	Civs_Main->Add(Civs_DataArea, 3, wxEXPAND);
	Civs_Main->Add(10, -1);
	Civs_Main->Add(Civs_Holder_Resources, 3, wxEXPAND);
	Civs_Main->Add(10, -1);

	Tab_Civs->SetSizer(Civs_Main);

	Connect(Civs_Civs_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnCivsSearch));
	Connect(Civs_Civs_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnCivsSearch));
	Connect(Civs_Civs_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnCivsSelect));
	Connect(Civs_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnCivsAdd));
	Connect(Civs_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnCivsInsert));
	Connect(Civs_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnCivsDelete));
	Connect(Civs_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnCivsCopy));
	Connect(Civs_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnCivsPaste));
	Connect(Civs_Resources_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnResourcesSearch));
	Connect(Civs_Resources_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnResourcesSearch));
	Connect(Civs_Resources_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnResourcesSelect));
	Connect(Resources_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResourcesCopy));
	Connect(Resources_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResourcesPaste));
	Connect(Resources_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResourcesAdd));
	Connect(Resources_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResourcesInsert));
	Connect(Resources_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResourcesDelete));
	Connect(Resources_CopyToAll->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResourcesCopyToAll));

	for(short loop = 0;loop < 2;loop++)
	Civs_Name[loop]->Connect(Civs_Name[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_String), NULL, this);
	Civs_GraphicSet->Connect(Civs_GraphicSet->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Byte), NULL, this);
	Civs_ResourceValue->Connect(Civs_ResourceValue->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Float), NULL, this);

}
