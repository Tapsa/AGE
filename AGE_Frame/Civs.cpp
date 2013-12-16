#include "../AGE_Frame.h"
using boost::lexical_cast;

void AGE_Frame::OnCivsSearch(wxCommandEvent &Event)
{
	ListCivs(false);
}

string AGE_Frame::GetCivName(short Index)
{
	if(GenieVersion <= genie::GV_TC)
	return GenieFile->Civs[Index].Name+" ("+lexical_cast<string>((short)GenieFile->Civs[Index].GraphicSet)+")";
	else
	return GenieFile->Civs[Index].Name2+" ("+lexical_cast<string>((short)GenieFile->Civs[Index].GraphicSet)+")";
}

void AGE_Frame::ListCivs(bool all)
{
	searchText = Civs_Civs_Search->GetValue().Lower();
	excludeText = Civs_Civs_Search_R->GetValue().Lower();

	auto selections = Civs_Civs_List->GetSelections(Items);
	Civs_Civs_List->Clear();

	wxArrayString names;
	if(all) names.Alloc(GenieFile->Graphics.size());

	for(short loop = 0; loop < GenieFile->Civs.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetCivName(loop);
		if(SearchMatches(Name.Lower()))
		{
			Civs_Civs_List->Append(Name, (void*)&GenieFile->Civs[loop]);
		}
		if(all) names.Add(Name);
	}

	ListingFix(selections, Civs_Civs_List);
	if(all)
	{
		FillLists(CivComboBoxList, names);
		short savedUnitCiv = Units_Civs_List->GetSelection();
		Units_Civs_List->Set(names);
		Units_Civs_List->SetSelection(savedUnitCiv);
	}

	wxCommandEvent E;
	OnCivsSelect(E);
}

void AGE_Frame::OnCivsSelect(wxCommandEvent &Event)
{
	auto selections = Civs_Civs_List->GetSelections(Items);
	if(selections < 1) return;

	CivIDs.resize(selections);
	Civs_One->resize(selections);
	Civs_Name[0]->resize(selections);
	Civs_TechTree->resize(selections);
	if(GenieVersion >= genie::GV_AoK)
	{
		Civs_TeamBonus->resize(selections);
		if(GenieVersion >= genie::GV_SWGB)
		{
			Civs_Name[1]->resize(selections);
			for(short loop = 0; loop < 4; ++loop)
			Civs_SUnknown1[loop]->resize(selections);
		}
	}
	Civs_GraphicSet->resize(selections);

	genie::Civ * CivPointer;
	for(auto sel = selections; sel--> 0;)
	{
		CivPointer = (genie::Civ*)Civs_Civs_List->GetClientData(Items.Item(sel));
		CivIDs[sel] = (CivPointer - (&GenieFile->Civs[0]));

		Civs_One->container[sel] = &CivPointer->One;
		Civs_Name[0]->container[sel] = &CivPointer->Name;
		Civs_TechTree->container[sel] = &CivPointer->TechTreeID;
		if(GenieVersion >= genie::GV_AoK)
		{
			Civs_TeamBonus->container[sel] = &CivPointer->TeamBonusID;
			if(GenieVersion >= genie::GV_SWGB)
			{
				Civs_Name[1]->container[sel] = &CivPointer->Name2;
				for(short loop = 0; loop < 4; ++loop)
				Civs_SUnknown1[loop]->container[sel] = &CivPointer->SUnknown1[loop];
			}
		}
		Civs_GraphicSet->container[sel] = &CivPointer->GraphicSet;
	}

	Civs_One->ChangeValue(lexical_cast<string>((short)CivPointer->One));
	Civs_Name[0]->ChangeValue(CivPointer->Name);
	Civs_TechTree->ChangeValue(lexical_cast<string>(CivPointer->TechTreeID));
	Civs_ComboBox_TechTree->SetSelection(CivPointer->TechTreeID + 1);
	if(GenieVersion >= genie::GV_AoK)
	{
		Civs_TeamBonus->ChangeValue(lexical_cast<string>(CivPointer->TeamBonusID));
		Civs_ComboBox_TeamBonus->SetSelection(CivPointer->TeamBonusID + 1);
		if(GenieVersion >= genie::GV_SWGB)
		{
			Civs_Name[1]->ChangeValue(CivPointer->Name2);
			for(short loop = 0; loop < 4; ++loop)
			Civs_SUnknown1[loop]->ChangeValue(lexical_cast<string>(CivPointer->SUnknown1[loop]));
		}
	}
	Civs_GraphicSet->ChangeValue(lexical_cast<string>((short)CivPointer->GraphicSet));
	ListResources();
}

void AGE_Frame::OnCivsAdd(wxCommandEvent &Event)
{
	if(GenieFile == NULL) return;

	wxBusyCursor WaitCursor;
	genie::Civ Temp;
	Temp.setGameVersion(GenieVersion);
	if(GenieFile->Civs.size() > 0)
	{
		short FillingCiv = (GenieFile->Civs.size() > 1) ? 1 : 0;
		Temp.Resources = GenieFile->Civs[FillingCiv].Resources;
		Temp.UnitPointers = GenieFile->Civs[FillingCiv].UnitPointers;
		Temp.Units = GenieFile->Civs[FillingCiv].Units;
	}
	GenieFile->Civs.push_back(Temp);
	Added = true;
	OnCivCountChange();
	ListUnits(UnitCivID, false);
}

void AGE_Frame::OnCivsInsert(wxCommandEvent &Event)
{
	auto selections = Civs_Civs_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	genie::Civ Temp;
	Temp.setGameVersion(GenieVersion);
	if(GenieFile->Civs.size() > 0)
	{
		short FillingCiv = (GenieFile->Civs.size() > 1) ? 1 : 0;
		Temp.Resources = GenieFile->Civs[FillingCiv].Resources;
		Temp.UnitPointers = GenieFile->Civs[FillingCiv].UnitPointers;
		Temp.Units = GenieFile->Civs[FillingCiv].Units;
	}
	GenieFile->Civs.insert(GenieFile->Civs.begin() + CivIDs[0], Temp);
	OnCivCountChange();
	ListUnits(UnitCivID, false);
}

void AGE_Frame::OnCivsDelete(wxCommandEvent &Event)
{
	auto selections = Civs_Civs_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	DeleteFromList(GenieFile->Civs, CivIDs);
	OnCivCountChange();
	ListUnits(0, false);
}

void AGE_Frame::OnCivsCopy(wxCommandEvent &Event)
{
	auto selections = Civs_Civs_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->Civs, CivIDs, copies->Civ);
}

void AGE_Frame::OnCivsPaste(wxCommandEvent &Event)
{
	auto selections = Civs_Civs_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToList(GenieFile->Civs, CivIDs[0], copies->Civ);
	OnCivCountChange();
	ListUnits(UnitCivID, false);
}

void AGE_Frame::OnCivsPasteInsert(wxCommandEvent &Event)
{
	auto selections = Civs_Civs_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToList(GenieFile->Civs, CivIDs[0], copies->Civ);
	OnCivCountChange();
	ListUnits(UnitCivID, false);
}

void AGE_Frame::OnCivCountChange()
{
	short CivCount = GenieFile->Civs.size();
//	Unit copying fixes.
//	This messes copying if more than one window is opened!
//	copies->Dat.Civs.resize(CivCount);

	if(Units_CivBoxes.size() < CivCount)
	{
		Units_CivBoxes.reserve(CivCount);
		//Units_CivLabels.reserve(CivCount);
		for(short loop = Units_CivBoxes.size(); loop < CivCount; ++loop)
		{
			Units_CivBoxes.push_back(new wxCheckBox(Tab_Units, wxID_ANY, "", wxDefaultPosition, wxSize(30, 20)));
			Units_CivBoxes[loop]->SetValue(true);
			//Units_CivLabels.push_back(new wxStaticText(Tab_Units, wxID_ANY, GenieFile->Civs[loop].Name.substr(0, 2), wxDefaultPosition, wxSize(-1, 15), wxALIGN_CENTER_HORIZONTAL | wxST_NO_AUTORESIZE));
			Units_Holder_TopGrid->Add(Units_CivBoxes[loop], 0, wxEXPAND);
			//Units_Holder_TopGrid->Add(Units_CivLabels[loop], 0, wxEXPAND);
			Connect(Units_CivBoxes[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnAutoCopy));
		}
	}
	else if(Units_CivBoxes.size() > CivCount)
	{
		for(short loop = Units_CivBoxes.size(); loop--> CivCount;)
		{
			Units_CivBoxes[loop]->Destroy();
			//Units_CivLabels[loop]->Destroy();
		}
		Units_CivBoxes.resize(CivCount);
		//Units_CivLabels.resize(CivCount);
	}
	for(short loop = 0; loop < CivCount; ++loop)
	{
		if(GenieVersion <= genie::GV_TC)
		Units_CivBoxes[loop]->SetLabel(GenieFile->Civs[loop].Name.substr(0, 2));
		else
		Units_CivBoxes[loop]->SetLabel(GenieFile->Civs[loop].Name2.substr(0, 2));
	}
	ListCivs();
	Units_DataArea->Layout();
	Refresh();
}

string AGE_Frame::GetResourceName(short Index)
{
	string Name = "";
	switch(Index)
	{
		case 0: Name = "Food Storage"; break;
		case 1:
			if(GenieVersion <= genie::GV_TC)
			Name = "Wood Storage";
			else
			Name = "Carbon Storage";
			break;
		case 2:
			if(GenieVersion <= genie::GV_TC)
			Name = "Stone Storage";
			else
			Name = "Ore Storage";
			break;
		case 3:
			if(GenieVersion <= genie::GV_TC)
			Name = "Gold Storage ";
			else
			Name = "Nova Storage ";
			break;
		case 4: Name = "Population Headroom"; break;
		case 5:
			if(GenieVersion <= genie::GV_TC)
			Name = "Conversion Range?";
			else
			Name = "Conversion Range";
			break;
		case 6: Name = "Current Age"; break;
		case 7:
			if(GenieVersion <= genie::GV_TC)
			Name = "Relics Captured";
			else
			Name = "Holocrons Captured";
			break;
		case 8: Name = "Trade Bonus"; break;
		case 9: Name = "Trade Goods"; break;
		case 10:
			if(GenieVersion <= genie::GV_TC)
			Name = "Trade Production";
			else
			Name = "Shields' Recharge Rate";
			break;
		case 11: Name = "Population (Both Current and Headroom)"; break;
		case 12: Name = "Corpse Decay Time"; break;
		case 13: Name = "Discovery"; break;
		case 14: Name = "Monuments/Ruins Captured?"; break;
		case 15: Name = "Predator Animal Food"; break;
		case 16: Name = "Crops"; break;
		case 17: Name = "Fish Storage"; break;
		case 18:
			if(GenieVersion <= genie::GV_TC)
			Name = "Unknown";
			else
			Name = "Power Core Range";
			break;
		case 19: Name = "Total Units Owned"; break;
		case 20: Name = "Units Killed"; break;
		case 21: Name = "Research Count"; break;
		case 22: Name = "% Map Explored"; break;
		case 23:
			if(GenieVersion <= genie::GV_TC)
			Name = "Castle Age?";
			else
			Name = "Submarine Detection";
			break;
		case 24:
			if(GenieVersion <= genie::GV_TC)
			Name = "Imperial Age?";
			else
			Name = "Shield Generator Range";
			break;
		case 25: Name = "Feudal Age?"; break;
		case 26:
			if(GenieVersion <= genie::GV_TC)
			Name = "Unknown";
			else
			Name = "Shields' Drop Off Time";
			break;
		case 27:
			if(GenieVersion <= genie::GV_TC)
			Name = "Enable Monk Conversion";
			else
			Name = "Enable Jedi Conversion";
			break;
		case 28: Name = "Enable Building Conversion"; break;
		case 30: Name = "Building Limit"; break;
		case 31:
			if(GenieVersion <= genie::GV_TC)
			Name = "Food Limit";
			else
			Name = "Enable A-A Attack For AT-AT";
			break;
		case 32:
			if(GenieVersion <= genie::GV_RoR)
			Name = "Unit Limit";
			else
			Name = "Bonus Population";
			break;
		case 33:
			if(GenieVersion <= genie::GV_TC)
			Name = "Maintenance";
			else
			Name = "Power Core Shielding";
			break;
		case 34:
			if(GenieVersion <= genie::GV_TC)
			Name = "Faith";
			else
			Name = "Force";
			break;
		case 35:
			if(GenieVersion <= genie::GV_TC)
			Name = "Faith Recharging Rate";
			else
			Name = "Force Recharging Rate";
			break;
		case 36: Name = "Farm Food Amount"; break;
		case 37: Name = "Civilian Units (Villager High)"; break;
		case 38:
			if(GenieVersion <= genie::GV_TC)
			Name = "Unknown";
			else
			Name = "Shields On For Bombers/Fighters";
			break;
		case 39: Name = "All Techs Achieved"; break;
		case 40: Name = "Military Units (Largest Army)"; break;
		case 41: Name = "Units Converted"; break;
		case 42: Name = "Standing? Wonders"; break;
		case 43: Name = "Buildings Razed"; break;
		case 44: Name = "Kill Ratio"; break;
		case 45: Name = "Survival to Finish"; break;
		case 46: Name = "Tribute Fee"; break;
		case 47:
			if(GenieVersion <= genie::GV_TC)
			Name = "Gold Mining Productivity";
			else
			Name = "Nova Mining Productivity";
			break;
		case 48: Name = "Town Center Unavailable"; break;
		case 49: Name = "Gold Counter"; break;
		case 50: Name = "Reveal Ally"; break;
		case 51:
			if(GenieVersion <= genie::GV_TC)
			Name = "Houses (Unused)";
			else
			Name = "Shielding";
			break;
		case 52: Name = "Monastery Count"; break;
		case 53: Name = "Tribute Sent"; break;
		case 54: Name = "All Ruins Have Been Captured"; break;
		case 55: Name = "All Relics Have Been Captured"; break;
		case 56:
			if(GenieVersion <= genie::GV_TC)
			Name = "Loot Storage? Unit Unload Room?";
			else
			Name = "Enable Stealth For Masters";
			break;
		case 57: Name = "Captured Unit"; break;
		case 58:
			if(GenieVersion <= genie::GV_TC)
			Name = "Dark Age?";
			else
			Name = "Masters Can See Hidden Units";
			break;
		case 59: Name = "Trade Good Quality"; break;
		case 60: Name = "Trade Market Level"; break;
		case 61: Name = "Formations"; break;
		case 62: Name = "Building Housing Rate"; break;
		case 63: Name = "Gather Tax Rate"; break;
		case 64: Name = "Gather Accumulator"; break;
		case 65: Name = "Salvage Decay Rate"; break;
		case 66: Name = "Ages? Allow Formations?"; break;
		case 67: Name = "Conversions"; break;
		case 68: Name = "Hit Points Killed (Unused)"; break;
		case 69: Name = "Killed P1"; break;
		case 70: Name = "Killed P2"; break;
		case 71: Name = "Killed P3"; break;
		case 72: Name = "Killed P4"; break;
		case 73: Name = "Killed P5"; break;
		case 74: Name = "Killed P6"; break;
		case 75: Name = "Killed P7"; break;
		case 76: Name = "Killed P8"; break;
		case 77: Name = "Conversion Resistance"; break;
		case 78: Name = "Trade Fee"; break;
		case 79:
			if(GenieVersion <= genie::GV_TC)
			Name = "Stone Mining Productivity";
			else
			Name = "Ore Mining Productivity";
			break;
		case 80: Name = "Queued Units"; break;
		case 81: Name = "Training Count"; break;
		case 82: Name = "Start With Packed Town Center / Raider"; break;
		case 83: Name = "Boarding Recharge Rate"; break;
		case 84: Name = "Starting Villagers"; break;
		case 85: Name = "Researches' Cost Multiplier"; break;
		case 86: Name = "Researches' Time Multiplier"; break;
		case 87:
			if(GenieVersion <= genie::GV_TC)
			Name = "Convert Ships";
			else
			Name = "Concentration";
			break;
		case 88: Name = "Fish Trap Food Amount"; break;
		case 89:
			if(GenieVersion <= genie::GV_TC)
			Name = "Bonus Healing Rate";
			else
			Name = "Medic Healing Rate";
			break;
		case 90: Name = "Healing Range"; break;
		case 91: Name = "Bonus Starting Food"; break;
		case 92:
			if(GenieVersion <= genie::GV_TC)
			Name = "Bonus Starting Wood";
			else
			Name = "Bonus Starting Carbon";
			break;
		case 93:
			if(GenieVersion <= genie::GV_TC)
			Name = "Bonus Starting Stone";
			else
			Name = "Bonus Starting Ore";
			break;
		case 94:
			if(GenieVersion <= genie::GV_TC)
			Name = "Bonus Starting Gold";
			else
			Name = "Bonus Starting Nova";
			break;
		case 95: Name = "Enable Town Center Packing / Raider Ability"; break;
		case 96: Name = "Self Healing Seconds (Berserkers)"; break;
		case 97: Name = "Sheep/Turkey Dominant LOS"; break;
		case 98: Name = "Score: Economy (Object Cost Summation)"; break;
		case 99: Name = "Score: Technology"; break;
		case 100:
			if(GenieVersion <= genie::GV_TC)
			Name = "Relic Gold (Collected)";
			else
			Name = "Holocron Nova (Collected)";
			break;
		case 101: Name = "Trade Profit"; break;
		case 102: Name = "P1 Tribute"; break;
		case 103: Name = "P2 Tribute"; break;
		case 104: Name = "P3 Tribute"; break;
		case 105: Name = "P4 Tribute"; break;
		case 106: Name = "P5 Tribute"; break;
		case 107: Name = "P6 Tribute"; break;
		case 108: Name = "P7 Tribute"; break;
		case 109: Name = "P8 Tribute"; break;
		case 110: Name = "P1 Kill Score"; break;
		case 111: Name = "P2 Kill Score"; break;
		case 112: Name = "P3 Kill Score"; break;
		case 113: Name = "P4 Kill Score"; break;
		case 114: Name = "P5 Kill Score"; break;
		case 115: Name = "P6 Kill Score"; break;
		case 116: Name = "P7 Kill Score"; break;
		case 117: Name = "P8 Kill Score"; break;
		case 118: Name = "P1 Razings"; break;
		case 119: Name = "P2 Razings"; break;
		case 120: Name = "P3 Razings"; break;
		case 121: Name = "P4 Razings"; break;
		case 122: Name = "P5 Razings"; break;
		case 123: Name = "P6 Razings"; break;
		case 124: Name = "P7 Razings"; break;
		case 125: Name = "P8 Razings"; break;
		case 126: Name = "P1 Razing Score"; break;
		case 127: Name = "P2 Razing Score"; break;
		case 128: Name = "P3 Razing Score"; break;
		case 129: Name = "P4 Razing Score"; break;
		case 130: Name = "P5 Razing Score"; break;
		case 131: Name = "P6 Razing Score"; break;
		case 132: Name = "P7 Razing Score"; break;
		case 133: Name = "P8 Razing Score"; break;
		case 134: Name = "Standing Castles"; break;
		case 135: Name = "Hit Points Razings (Unused)"; break;
		case 136: Name = "Kills By P1"; break;
		case 137: Name = "Kills By P2"; break;
		case 138: Name = "Kills By P3"; break;
		case 139: Name = "Kills By P4"; break;
		case 140: Name = "Kills By P5"; break;
		case 141: Name = "Kills By P6"; break;
		case 142: Name = "Kills By P7"; break;
		case 143: Name = "Kills By P8"; break;
		case 144: Name = "Razings By P1"; break;
		case 145: Name = "Razings By P2"; break;
		case 146: Name = "Razings By P3"; break;
		case 147: Name = "Razings By P4"; break;
		case 148: Name = "Razings By P5"; break;
		case 149: Name = "Razings By P6"; break;
		case 150: Name = "Razings By P7"; break;
		case 151: Name = "Razings By P8"; break;
		case 152: Name = "Units Lost Score"; break;
		case 153: Name = "Buildings Lost Score"; break;
		case 154: Name = "Units Lost"; break;
		case 155: Name = "Buildings Lost"; break;
		case 156: Name = "Tribute From P1"; break;
		case 157: Name = "Tribute From P2"; break;
		case 158: Name = "Tribute From P3"; break;
		case 159: Name = "Tribute From P4"; break;
		case 160: Name = "Tribute From P5"; break;
		case 161: Name = "Tribute From P6"; break;
		case 162: Name = "Tribute From P7"; break;
		case 163: Name = "Tribute From P8"; break;
		case 164: Name = "Current Units Score"; break;
		case 165: Name = "Current Buildings Score"; break;
		case 166: Name = "Food Collected"; break;
		case 167:
			if(GenieVersion <= genie::GV_TC)
			Name = "Wood Collected";
			else
			Name = "Carbon Collected";
			break;
		case 168:
			if(GenieVersion <= genie::GV_TC)
			Name = "Stone Collected";
			else
			Name = "Ore Collected";
			break;
		case 169:
			if(GenieVersion <= genie::GV_TC)
			Name = "Gold Collected";
			else
			Name = "Nova Collected";
			break;
		case 170: Name = "Score: Military"; break;
		case 171: Name = "Tribute Received"; break;
		case 172: Name = "Razing Score"; break;
		case 173:
			if(GenieVersion <= genie::GV_TC)
			Name = "Total Castles";
			else
			Name = "Total Fortresses";
			break;
		case 174:
			if(GenieVersion <= genie::GV_TC)
			Name = "Total Wonders";
			else
			Name = "Total Monuments"; break;
		case 175: Name = "Score: Economy (Tribute)"; break;
		case 176: Name = "Convert Min Adjustment"; break;
		case 177: Name = "Convert Max Adjustment"; break;
		case 178: Name = "Convert Resist Min Adjustment"; break;
		case 179: Name = "Convert Resist Max Adjustment"; break;
		case 180: Name = "Convert Building Min"; break;
		case 181: Name = "Convert Building Max"; break;
		case 182: Name = "Convert Building Chance"; break;
		case 183: Name = "Reveal Enemy"; break;
		case 184: Name = "Score: Society"; break;
		case 185: Name = "Food Score"; break;
		case 186:
			if(GenieVersion <= genie::GV_TC)
			Name = "Wood Score";
			else
			Name = "Carbon Score";
			break;
		case 187:
			if(GenieVersion <= genie::GV_TC)
			Name = "Stone Score";
			else
			Name = "Ore Score";
			break;
		case 188:
			if(GenieVersion <= genie::GV_TC)
			Name = "Gold Score";
			else
			Name = "Nova Score";
			break;
		case 189:
			if(GenieVersion <= genie::GV_TC)
			Name = "Chopping Productivity";
			else
			Name = "Carbon Gathering Productivity";
			break;
		case 190: Name = "Food-gathering Productivity"; break;
		case 191:
			if(GenieVersion <= genie::GV_TC)
			Name = "Relic Gold Production Rate";
			else
			Name = "Holocron Nova Production Rate";
			break;
		case 192: Name = "Units Converted By Enemy Die"; break;
		case 193:
			if(GenieVersion <= genie::GV_TC)
			Name = "Theocracy";
			else
			Name = "Meditation";
			break;
		case 194: Name = "Crenellations"; break;
		case 195: Name = "Construction Rate (Except Wonder)"; break;
		case 196:
			if(GenieVersion <= genie::GV_TC)
			Name = "Wonder Bonus";
			else
			Name = "Biological Self Regeneration";
			break;
		case 197: Name = "Spies Discount"; break;
		default: Name = "Unknown";
	}
	return Name;
}

void AGE_Frame::OnResourcesSearch(wxCommandEvent &Event)
{
	ListResources(false);
}

void AGE_Frame::ListResources(bool all)
{
	searchText = Civs_Resources_Search->GetValue().Lower();
	excludeText = Civs_Resources_Search_R->GetValue().Lower();

	auto selections = Civs_Resources_List->GetSelections(Items);
	Civs_Resources_List->Clear();

	wxArrayString names;
	if(all) names.Alloc(GenieFile->Civs[CivIDs[0]].Resources.size());

	for(short loop = 0; loop < GenieFile->Civs[CivIDs[0]].Resources.size(); ++loop)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - Value: "+lexical_cast<string>(GenieFile->Civs[CivIDs[0]].Resources[loop])+" - "+GetResourceName(loop);
		if(SearchMatches(Name.Lower()))
		{
			Civs_Resources_List->Append(Name, (void*)&GenieFile->Civs[CivIDs[0]].Resources[loop]);
		}
		if(all) names.Add(" "+lexical_cast<string>(loop)+" - "+GetResourceName(loop));
	}

	ListingFix(selections, Civs_Resources_List);
	if(all) FillLists(ResourceComboBoxList, names);

	wxCommandEvent E;
	OnResourcesSelect(E);
}

void AGE_Frame::OnResourcesSelect(wxCommandEvent &Event)
{
	auto selections = Civs_Resources_List->GetSelections(Items);
	if(selections < 1) return;

	ResourceIDs.resize(selections);
	Civs_ResourceValue->resize(selections);

	float * CivResourcePointer;
	for(auto loop = selections; loop--> 0;)
	{
		CivResourcePointer = (float*)Civs_Resources_List->GetClientData(Items.Item(loop));
		ResourceIDs[loop] = (CivResourcePointer - (&GenieFile->Civs[CivIDs[0]].Resources[0]));
		Civs_ResourceValue->container[loop] = CivResourcePointer;
	}

	Civs_ResourceValue->ChangeValue(lexical_cast<string>(*CivResourcePointer));
}

void AGE_Frame::OnResourcesAdd(wxCommandEvent &Event)
{
	auto selections = Civs_Civs_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	for(short loop = 0; loop < GenieFile->Civs.size(); ++loop)
	GenieFile->Civs[loop].Resources.push_back(0);
	Added = true;
	ListResources();
}

void AGE_Frame::OnResourcesInsert(wxCommandEvent &Event)
{
	auto selections = Civs_Resources_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	for(short loop = 0; loop < GenieFile->Civs.size(); ++loop)
	GenieFile->Civs[loop].Resources.insert(GenieFile->Civs[loop].Resources.begin() + ResourceIDs[0], 0);
	ListResources();
}

void AGE_Frame::OnResourcesDelete(wxCommandEvent &Event)
{
	auto selections = Civs_Resources_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	for(short loop2 = 0; loop2 < GenieFile->Civs.size(); ++loop2)
	{
		for(auto loop = selections; loop--> 0;)
		GenieFile->Civs[loop2].Resources.erase(GenieFile->Civs[loop2].Resources.begin() + ResourceIDs[loop]);
	}
	ListResources();
}

void AGE_Frame::OnResourcesCopy(wxCommandEvent &Event)
{
	auto selections = Civs_Resources_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	CopyFromList(GenieFile->Civs[CivIDs[0]].Resources, ResourceIDs, copies->Resource);
}

void AGE_Frame::OnResourcesPaste(wxCommandEvent &Event)
{
	auto selections = Civs_Resources_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteToListNoGV(GenieFile->Civs[CivIDs[0]].Resources, ResourceIDs[0], copies->Resource);
	ListResources();
}

void AGE_Frame::OnResourcesPasteInsert(wxCommandEvent &Event)
{
	auto selections = Civs_Resources_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	PasteInsertToListNoGV(GenieFile->Civs[CivIDs[0]].Resources, ResourceIDs[0], copies->Resource);
	ListResources();
}

void AGE_Frame::OnResourcesCopyToAll(wxCommandEvent &Event)
{
	auto selections = Civs_Resources_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	for(short loop = 0; loop < selections; ++loop)
	{
		float Copy = GenieFile->Civs[CivIDs[0]].Resources[ResourceIDs[loop]];
		for(short loop2 = 0; loop2 < GenieFile->Civs.size(); ++loop2)
		GenieFile->Civs[loop2].Resources[ResourceIDs[loop]] = Copy;
	}
}

void AGE_Frame::CreateCivControls()
{
	Civs_Main = new wxBoxSizer(wxHORIZONTAL);
	Civs_ListArea = new wxBoxSizer(wxVERTICAL);
	Civs_Civs_Buttons = new wxGridSizer(3, 0, 0);
	Tab_Civs = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));

	Civs_Civs = new wxStaticBoxSizer(wxVERTICAL, Tab_Civs, "Civilizations");
	Civs_Civs_Search = new wxTextCtrl(Tab_Civs, wxID_ANY);
	Civs_Civs_Search_R = new wxTextCtrl(Tab_Civs, wxID_ANY);
	Civs_Civs_List = new wxListBox(Tab_Civs, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	Civs_Add = new wxButton(Tab_Civs, wxID_ANY, "Add *", wxDefaultPosition, wxSize(5, 20));
	Civs_Add->SetToolTip("I highly recommend you to download UserPatch\nfrom xOmicron, if you play The Conquerors.\nWith it you can use added civilizations.\nStar Wars versions can already have more civilizations.");
	Civs_Insert = new wxButton(Tab_Civs, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	Civs_Delete = new wxButton(Tab_Civs, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Civs_Copy = new wxButton(Tab_Civs, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Civs_Paste = new wxButton(Tab_Civs, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Civs_PasteInsert = new wxButton(Tab_Civs, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));

	Civs_DataArea = new wxBoxSizer(wxVERTICAL);
	Civs_DataGrid1 = new wxGridSizer(2, 0, 5);
	Civs_DataGrid2 = new wxGridSizer(2, 0, 5);
	Civs_DataGrid3 = new wxGridSizer(2, 0, 0);
	Civs_Holder_Name[0] = new wxBoxSizer(wxVERTICAL);
	Civs_Text_Name[0] = new wxStaticText(Tab_Civs, wxID_ANY, " Name", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Civs_Name[0] = new TextCtrl_String(Tab_Civs, 20);
	Civs_Holder_Name[1] = new wxBoxSizer(wxVERTICAL);
	Civs_Text_Name[1] = new wxStaticText(Tab_Civs, wxID_ANY, " Name 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Civs_Name[1] = new TextCtrl_String(Tab_Civs, 20);
	Civs_Holder_GraphicSet = new wxBoxSizer(wxVERTICAL);
	Civs_Text_GraphicSet = new wxStaticText(Tab_Civs, wxID_ANY, " Graphic Set *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Civs_GraphicSet = new TextCtrl_Byte(Tab_Civs);
	Civs_GraphicSet->SetToolTip("This doesn't change the graphics");
	Civs_Holder_One = new wxBoxSizer(wxVERTICAL);
	Civs_Text_One = new wxStaticText(Tab_Civs, wxID_ANY, " Always One", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Civs_One = new TextCtrl_Byte(Tab_Civs);
	Civs_Holder_TechTree = new wxBoxSizer(wxVERTICAL);
	Civs_Text_TechTree = new wxStaticText(Tab_Civs, wxID_ANY, " Technology Tree", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Civs_TechTree = new TextCtrl_Short(Tab_Civs);
	Civs_ComboBox_TechTree = new ComboBox_Plus1(Tab_Civs, Civs_TechTree);
	TechComboBoxList.push_back(Civs_ComboBox_TechTree);
	Civs_Holder_TeamBonus = new wxBoxSizer(wxVERTICAL);
	Civs_Text_TeamBonus = new wxStaticText(Tab_Civs, wxID_ANY, " Team Bonus", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Civs_TeamBonus = new TextCtrl_Short(Tab_Civs);
	Civs_ComboBox_TeamBonus = new ComboBox_Plus1(Tab_Civs, Civs_TeamBonus);
	TechComboBoxList.push_back(Civs_ComboBox_TeamBonus);
	Civs_Holder_SUnknown1 = new wxBoxSizer(wxVERTICAL);
	Civs_Text_SUnknown1 = new wxStaticText(Tab_Civs, wxID_ANY, " Unique Units / Researches", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	for(short loop = 0; loop < 4; ++loop)
	Civs_SUnknown1[loop] = new TextCtrl_Short(Tab_Civs);

	Civs_Holder_Resources = new wxBoxSizer(wxVERTICAL);
	Civs_Resources = new wxStaticBoxSizer(wxVERTICAL, Tab_Civs, "Initial Resources");
	Civs_Resources_Search = new wxTextCtrl(Tab_Civs, wxID_ANY);
	Civs_Resources_Search_R = new wxTextCtrl(Tab_Civs, wxID_ANY);
	Civs_Holder_ResourceValue = new wxBoxSizer(wxVERTICAL);
	Civs_Text_ResourceValue = new wxStaticText(Tab_Civs, wxID_ANY, " Resource Value", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Civs_ResourceValue = new TextCtrl_Float(Tab_Civs);
	Civs_Resources_List = new wxListBox(Tab_Civs, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	Civs_Resources_Buttons = new wxGridSizer(3, 0, 0);
	Resources_Add = new wxButton(Tab_Civs, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Resources_Insert = new wxButton(Tab_Civs, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	Resources_Delete = new wxButton(Tab_Civs, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Resources_Copy = new wxButton(Tab_Civs, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Resources_Paste = new wxButton(Tab_Civs, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Resources_PasteInsert = new wxButton(Tab_Civs, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));
	Resources_CopyToAll = new wxButton(Tab_Civs, wxID_ANY, "Copy to all civs", wxDefaultPosition, wxSize(5, 20));
	Civs_Resources_Data = new wxBoxSizer(wxVERTICAL);
	Civs_Holder_Resources_Link = new wxHyperlinkCtrl(Tab_Civs, wxID_ANY, "GenieWiki Resources",
	"http://www.digitization.org/wiki/index.php?title=Resource", wxDefaultPosition, wxSize(5, 20), wxBORDER_NONE|wxHL_CONTEXTMENU|wxHL_ALIGN_LEFT);

	Civs_Civs_Buttons->Add(Civs_Add, 1, wxEXPAND);
	Civs_Civs_Buttons->Add(Civs_Insert, 1, wxEXPAND);
	Civs_Civs_Buttons->Add(Civs_Delete, 1, wxEXPAND);
	Civs_Civs_Buttons->Add(Civs_Copy, 1, wxEXPAND);
	Civs_Civs_Buttons->Add(Civs_Paste, 1, wxEXPAND);
	Civs_Civs_Buttons->Add(Civs_PasteInsert, 1, wxEXPAND);

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
	for(short loop = 0; loop < 2; ++loop){
	Civs_Holder_Name[loop]->Add(Civs_Text_Name[loop], 0, wxEXPAND);
	Civs_Holder_Name[loop]->Add(Civs_Name[loop], 1, wxEXPAND);}
	Civs_Holder_SUnknown1->Add(Civs_Text_SUnknown1, 0, wxEXPAND);
	Civs_Holder_SUnknown1->Add(Civs_DataGrid3, 1, wxEXPAND);
	for(short loop = 0; loop < 4; ++loop)
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
	Civs_Resources_Buttons->Add(Resources_PasteInsert, 1, wxEXPAND);
	Civs_Resources_Buttons->Add(Resources_CopyToAll, 1, wxEXPAND);
	Civs_Resources_Buttons->Add(Civs_Holder_Resources_Link, 1, wxEXPAND);

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
	Connect(Civs_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnCivsPasteInsert));
	Connect(Civs_Resources_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnResourcesSearch));
	Connect(Civs_Resources_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnResourcesSearch));
	Connect(Civs_Resources_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnResourcesSelect));
	Connect(Resources_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResourcesCopy));
	Connect(Resources_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResourcesPaste));
	Connect(Resources_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResourcesPasteInsert));
	Connect(Resources_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResourcesAdd));
	Connect(Resources_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResourcesInsert));
	Connect(Resources_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResourcesDelete));
	Connect(Resources_CopyToAll->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnResourcesCopyToAll));

	for(short loop = 0; loop < 2; ++loop)
	Civs_Name[loop]->Connect(Civs_Name[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Civs), NULL, this);
	Civs_GraphicSet->Connect(Civs_GraphicSet->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Civs), NULL, this);
	Civs_ResourceValue->Connect(Civs_ResourceValue->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Civs), NULL, this);
}

void AGE_Frame::OnKillFocus_Civs(wxFocusEvent &Event)
{
	if(!((AGETextCtrl*)Event.GetEventObject())->SaveEdits()) return;
	if(Event.GetId() == Civs_Name[0]->GetId()
	|| Event.GetId() == Civs_Name[1]->GetId())
	{
		for(auto ID: CivIDs)
		{
			if(GenieVersion <= genie::GV_TC)
			Units_CivBoxes[ID]->SetLabel(GenieFile->Civs[ID].Name.substr(0, 2));
			else
			Units_CivBoxes[ID]->SetLabel(GenieFile->Civs[ID].Name2.substr(0, 2));
		}
		ListCivs();
	}
	else if(Event.GetId() == Civs_GraphicSet->GetId())
	{
		ListCivs();
	}
	else if(Event.GetId() == Civs_ResourceValue->GetId())
	{
		ListResources();
	}
	Event.Skip();
}
