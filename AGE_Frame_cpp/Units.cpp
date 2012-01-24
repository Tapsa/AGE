/* AGEFrame_cpp/Units.cpp */

#include "../AGE_Frame.h"
using boost::lexical_cast;

void AGE_Frame::OnUnitSubList(wxCommandEvent& Event)
{
	ListUnits(Units_Civs_List->GetSelection(), false);	// List units by selected civ.
}

string AGE_Frame::GetUnitName(short UnitID, short UnitCivID, bool Filter)
{
	string Name = "";
	if(GenieFile->Civs[UnitCivID].UnitPointers[UnitID] == 0)
	{
		Name = "*Disabled*";
	}
	else
	{
		if(Filter)
		{
			short Selection[2];
			for(short loop = 0;loop < 2;loop++)
			Selection[loop] = Units_Units_SearchFilters[loop]->GetSelection();
			
			if(Selection[0] > 1)
			for(short loop = 0;loop < 2;loop++)
			{
				if(Selection[loop] == 2)	// Type
				{
					Name += "T ";
					Name += lexical_cast<string>((short)GenieFile->Civs[UnitCivID].Units[UnitID].Type);
				}
				else if(Selection[loop] == 3)	// Class
				{
					Name += "C ";
					Name += lexical_cast<string>(GenieFile->Civs[UnitCivID].Units[UnitID].Class);
				}
				else if(Selection[loop] == 4)	// Pointer
				{
					Name = lexical_cast<string>(GenieFile->Civs[UnitCivID].UnitPointers[UnitID]);
				}
				Name += ", ";
				if(Selection[loop+1] < 2) break;
			}
			
			if(Selection[0] != 1) Filter = false; // Names
		}
		
		if((LanguageDllString(GenieFile->Civs[UnitCivID].Units[UnitID].LanguageDllName) != "") && (Filter == false))
		{
			Name += LanguageDllString(GenieFile->Civs[UnitCivID].Units[UnitID].LanguageDllName);
		}
		else if(GenieFile->Civs[UnitCivID].Units[UnitID].Name != "")
		{
			Name += GenieFile->Civs[UnitCivID].Units[UnitID].Name;
		}
		else
		{
			Name += "New Unit";
		}
	}
	return Name;
}

void AGE_Frame::OnUnitsSearch(wxCommandEvent& Event)
{
	short Selection = Units_Civs_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		ListUnits(Selection, false);
	}
}

// Following void thing is a series of lists for user interface.
void AGE_Frame::ListUnits(short UnitCivID, bool Sized)
{
	string Name;
	SearchText = wxString(Units_Units_Search->GetValue()).Lower();
	ExcludeText = wxString(Units_Units_Search_R->GetValue()).Lower();
	string CompareText;
	for(short loop = 0;loop < 2;loop++)
	{
		if(Units_Units_UseAnd[loop]->GetValue() == true)
		UseAnd[loop] = true; else UseAnd[loop] = false;
	}
	
	if(UnitCivID == -1) UnitCivID = 0;
	Units_Civs_List->SetSelection(UnitCivID);
	
	short Selection = Units_Units_List->GetSelection();
	if(Units_Units_List->GetCount() > 0)
	{
		Units_Units_List->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	
	short IDsCount = 64, UnitIDs[IDsCount];
	if(Sized)
	{
		UnitIDs[0] = Units_ComboBox_DeadUnitID->GetSelection();
		UnitIDs[1] = Units_ComboBox_ProjectileUnitID->GetSelection();
		for(short loop = 0;loop < 2;loop++)
		UnitIDs[loop+2] = Units_ComboBox_DropSite[loop]->GetSelection();
		UnitIDs[4] = Units_ComboBox_AttackMissileDuplicationUnit->GetSelection();
		UnitIDs[5] = Units_ComboBox_TrackingUnit->GetSelection();
		UnitIDs[6] = Units_ComboBox_TrainLocationID->GetSelection();
		UnitIDs[7] = Units_ComboBox_StackUnitID->GetSelection();
		for(short loop = 0;loop < 4;loop++)
		{
			UnitIDs[loop+8] = Units_ComboBox_AnnexUnit[loop]->GetSelection();
			UnitIDs[loop+30] = TechTrees_ComboBox_Unit[loop]->GetSelection();
		}
		UnitIDs[12] = Units_ComboBox_HeadUnit->GetSelection();
		UnitIDs[13] = Units_ComboBox_TransformUnit->GetSelection();
		UnitIDs[14] = Research_ComboBox_ResearchLocation->GetSelection();
		UnitIDs[15] = Effects_ComboBox_UnitsA->GetSelection();
		UnitIDs[16] = Effects_ComboBox_UnitsB->GetSelection();
		UnitIDs[17] = UnitCommands_ComboBox_UnitID->GetSelection();
		UnitIDs[18] = UnitLineUnits_ComboBox_Units->GetSelection();
		UnitIDs[19] = TechTrees_Ages_ComboBox_Building->GetSelection();
		UnitIDs[20] = TechTrees_Ages_ComboBox_Unit->GetSelection();
		UnitIDs[21] = TechTrees_Buildings_ComboBox_ID->GetSelection();
		UnitIDs[22] = TechTrees_Buildings_ComboBox_Building->GetSelection();
		UnitIDs[23] = TechTrees_Buildings_ComboBox_Unit->GetSelection();
		UnitIDs[24] = TechTrees_Units_ComboBox_ID->GetSelection();
		UnitIDs[25] = TechTrees_Units_ComboBox_UpperBuilding->GetSelection();
		UnitIDs[26] = TechTrees_Units_ComboBox_Unit->GetSelection();
		UnitIDs[27] = TechTrees_Researches_ComboBox_UpperBuilding->GetSelection();
		UnitIDs[28] = TechTrees_Researches_ComboBox_Building->GetSelection();
		UnitIDs[29] = TechTrees_Researches_ComboBox_Unit->GetSelection();
		for(short loop = 0;loop < 30;loop++)
		UnitIDs[loop+34] = Terrains_ComboBox_TerrainUnitID[loop]->GetSelection();
		
		if(Units_ComboBox_DeadUnitID->GetCount() > 0)
		{
			Units_ComboBox_DeadUnitID->Clear();
		}
		if(Units_ComboBox_ProjectileUnitID->GetCount() > 0)
		{
			Units_ComboBox_ProjectileUnitID->Clear();
		}
		if(Units_ComboBox_AttackMissileDuplicationUnit->GetCount() > 0)
		{
			Units_ComboBox_AttackMissileDuplicationUnit->Clear();
		}
		for(short loop = 0;loop < 2;loop++)
		if(Units_ComboBox_DropSite[loop]->GetCount() > 0)
		{
			Units_ComboBox_DropSite[loop]->Clear();
		}
		if(Units_ComboBox_TrackingUnit->GetCount() > 0)
		{
			Units_ComboBox_TrackingUnit->Clear();
		}
		if(Units_ComboBox_TrainLocationID->GetCount() > 0)
		{
			Units_ComboBox_TrainLocationID->Clear();
		}
		if(Units_ComboBox_StackUnitID->GetCount() > 0)
		{
			Units_ComboBox_StackUnitID->Clear();
		}
		for(short loop = 0;loop < 4;loop++)
		{
			if(Units_ComboBox_AnnexUnit[loop]->GetCount() > 0)
			{
				Units_ComboBox_AnnexUnit[loop]->Clear();
			}
			if(TechTrees_ComboBox_Unit[loop]->GetCount() > 0)
			{
				TechTrees_ComboBox_Unit[loop]->Clear();
			}
		}
		if(Units_ComboBox_HeadUnit->GetCount() > 0)
		{
			Units_ComboBox_HeadUnit->Clear();
		}
		if(Units_ComboBox_TransformUnit->GetCount() > 0)
		{
			Units_ComboBox_TransformUnit->Clear();
		}
		if(Research_ComboBox_ResearchLocation->GetCount() > 0)
		{
			Research_ComboBox_ResearchLocation->Clear();
		}
		if(Effects_ComboBox_UnitsA->GetCount() > 0)
		{
			Effects_ComboBox_UnitsA->Clear();
		}
		if(Effects_ComboBox_UnitsB->GetCount() > 0)
		{
			Effects_ComboBox_UnitsB->Clear();
		}
		if(UnitCommands_ComboBox_UnitID->GetCount() > 0)
		{
			UnitCommands_ComboBox_UnitID->Clear();
		}
		if(UnitLineUnits_ComboBox_Units->GetCount() > 0)
		{
			UnitLineUnits_ComboBox_Units->Clear();
		}
		if(TechTrees_Ages_ComboBox_Building->GetCount() > 0)
		{
			TechTrees_Ages_ComboBox_Building->Clear();
		}
		if(TechTrees_Ages_ComboBox_Unit->GetCount() > 0)
		{
			TechTrees_Ages_ComboBox_Unit->Clear();
		}
		if(TechTrees_Buildings_ComboBox_ID->GetCount() > 0)
		{
			TechTrees_Buildings_ComboBox_ID->Clear();
		}
		if(TechTrees_Buildings_ComboBox_Building->GetCount() > 0)
		{
			TechTrees_Buildings_ComboBox_Building->Clear();
		}
		if(TechTrees_Buildings_ComboBox_Unit->GetCount() > 0)
		{
			TechTrees_Buildings_ComboBox_Unit->Clear();
		}
		if(TechTrees_Units_ComboBox_ID->GetCount() > 0)
		{
			TechTrees_Units_ComboBox_ID->Clear();
		}
		if(TechTrees_Units_ComboBox_UpperBuilding->GetCount() > 0)
		{
			TechTrees_Units_ComboBox_UpperBuilding->Clear();
		}
		if(TechTrees_Units_ComboBox_Unit->GetCount() > 0)
		{
			TechTrees_Units_ComboBox_Unit->Clear();
		}
		if(TechTrees_Researches_ComboBox_UpperBuilding->GetCount() > 0)
		{
			TechTrees_Researches_ComboBox_UpperBuilding->Clear();
		}
		if(TechTrees_Researches_ComboBox_Building->GetCount() > 0)
		{
			TechTrees_Researches_ComboBox_Building->Clear();
		}
		if(TechTrees_Researches_ComboBox_Unit->GetCount() > 0)
		{
			TechTrees_Researches_ComboBox_Unit->Clear();
		}
		for(short loop = 0;loop < 30;loop++)
		if(Terrains_ComboBox_TerrainUnitID[loop]->GetCount() > 0)
		{
			Terrains_ComboBox_TerrainUnitID[loop]->Clear();
		}
		
		for(short loop = 0;loop < IDsCount;loop++)
		{
			if(UnitIDs[loop] == wxNOT_FOUND)
			{
				UnitIDs[loop] = 0;
			}
		}
		
		Units_ComboBox_DeadUnitID->Append("-1 - None");
		Units_ComboBox_ProjectileUnitID->Append("-1 - None");
		Units_ComboBox_AttackMissileDuplicationUnit->Append("-1 - None");
		for(short loop = 0;loop < 2;loop++)
		Units_ComboBox_DropSite[loop]->Append("-1 - None");
		Units_ComboBox_TrackingUnit->Append("-1 - None");
		Units_ComboBox_TrainLocationID->Append("-1 - None");
		Units_ComboBox_StackUnitID->Append("-1 - None");
		for(short loop = 0;loop < 4;loop++)
		{
			Units_ComboBox_AnnexUnit[loop]->Append("-1 - None");
			TechTrees_ComboBox_Unit[loop]->Append("-1 - None");
		}
		Units_ComboBox_HeadUnit->Append("-1 - None");
		Units_ComboBox_TransformUnit->Append("-1 - None");
		Research_ComboBox_ResearchLocation->Append("-1 - None");
		Effects_ComboBox_UnitsA->Append("-1 - None");
		Effects_ComboBox_UnitsB->Append("-1 - None");
		UnitCommands_ComboBox_UnitID->Append("-1 - None");
		UnitLineUnits_ComboBox_Units->Append("-1 - None");
		TechTrees_Ages_ComboBox_Building->Append("-1 - None");
		TechTrees_Ages_ComboBox_Unit->Append("-1 - None");
		TechTrees_Buildings_ComboBox_ID->Append("-1 - None");
		TechTrees_Buildings_ComboBox_Building->Append("-1 - None");
		TechTrees_Buildings_ComboBox_Unit->Append("-1 - None");
		TechTrees_Units_ComboBox_ID->Append("-1 - None");
		TechTrees_Units_ComboBox_UpperBuilding->Append("-1 - None");
		TechTrees_Units_ComboBox_Unit->Append("-1 - None");
		TechTrees_Researches_ComboBox_UpperBuilding->Append("-1 - None");
		TechTrees_Researches_ComboBox_Building->Append("-1 - None");
		TechTrees_Researches_ComboBox_Unit->Append("-1 - None");
		for(short loop = 0;loop < 30;loop++)
		Terrains_ComboBox_TerrainUnitID[loop]->Append("-1 - None");
	}
	
	for(short loop = 0;loop < GenieFile->Civs[UnitCivID].Units.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetUnitName(loop, UnitCivID, true);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText) == true)
		{
			Units_Units_List->Append(Name, (void*)&GenieFile->Civs[UnitCivID].Units[loop]);
		}
		if(Sized)
		{
			Name = " "+lexical_cast<string>(loop)+" - "+GetUnitName(loop, 0, false);
			Units_ComboBox_DeadUnitID->Append(Name);
			Units_ComboBox_ProjectileUnitID->Append(Name);
			Units_ComboBox_AttackMissileDuplicationUnit->Append(Name);
			for(short loop = 0;loop < 2;loop++)
			Units_ComboBox_DropSite[loop]->Append(Name);
			Units_ComboBox_TrackingUnit->Append(Name);
			Units_ComboBox_TrainLocationID->Append(Name);
			Units_ComboBox_StackUnitID->Append(Name);
			for(short loop = 0;loop < 4;loop++)
			{
				Units_ComboBox_AnnexUnit[loop]->Append(Name);
				TechTrees_ComboBox_Unit[loop]->Append(Name);
			}
			Units_ComboBox_HeadUnit->Append(Name);
			Units_ComboBox_TransformUnit->Append(Name);
			Research_ComboBox_ResearchLocation->Append(Name);
			Effects_ComboBox_UnitsA->Append(Name);
			Effects_ComboBox_UnitsB->Append(Name);
			UnitCommands_ComboBox_UnitID->Append(Name);
			UnitLineUnits_ComboBox_Units->Append(Name);
			TechTrees_Ages_ComboBox_Building->Append(Name);
			TechTrees_Ages_ComboBox_Unit->Append(Name);
			TechTrees_Buildings_ComboBox_ID->Append(Name);
			TechTrees_Buildings_ComboBox_Building->Append(Name);
			TechTrees_Buildings_ComboBox_Unit->Append(Name);
			TechTrees_Units_ComboBox_ID->Append(Name);
			TechTrees_Units_ComboBox_UpperBuilding->Append(Name);
			TechTrees_Units_ComboBox_Unit->Append(Name);
			TechTrees_Researches_ComboBox_UpperBuilding->Append(Name);
			TechTrees_Researches_ComboBox_Building->Append(Name);
			TechTrees_Researches_ComboBox_Unit->Append(Name);
			for(short loop = 0;loop < 30;loop++)
			Terrains_ComboBox_TerrainUnitID[loop]->Append(Name);
		}
	}
	
	Units_Units_List->SetSelection(0);
	Units_Units_List->SetFirstItem(Selection - 3);
	Units_Units_List->SetSelection(Selection);
	if(Sized)
	{
		Units_ComboBox_DeadUnitID->SetSelection(UnitIDs[0]);
		Units_ComboBox_ProjectileUnitID->SetSelection(UnitIDs[1]);
		for(short loop = 0;loop < 2;loop++)
		Units_ComboBox_DropSite[loop]->SetSelection(UnitIDs[loop+2]);// 2 ja 3
		Units_ComboBox_AttackMissileDuplicationUnit->SetSelection(UnitIDs[4]);
		Units_ComboBox_TrackingUnit->SetSelection(UnitIDs[5]);
		Units_ComboBox_TrainLocationID->SetSelection(UnitIDs[6]);
		Units_ComboBox_StackUnitID->SetSelection(UnitIDs[7]);
		for(short loop = 0;loop < 4;loop++)
		{
			Units_ComboBox_AnnexUnit[loop]->SetSelection(UnitIDs[loop+8]);// 8 - 11
			TechTrees_ComboBox_Unit[loop]->SetSelection(UnitIDs[loop+30]);
		}
		Units_ComboBox_HeadUnit->SetSelection(UnitIDs[12]);
		Units_ComboBox_TransformUnit->SetSelection(UnitIDs[13]);
		Research_ComboBox_ResearchLocation->SetSelection(UnitIDs[14]);
		Effects_ComboBox_UnitsA->SetSelection(UnitIDs[15]);
		Effects_ComboBox_UnitsB->SetSelection(UnitIDs[16]);
		UnitCommands_ComboBox_UnitID->SetSelection(UnitIDs[17]);
		UnitLineUnits_ComboBox_Units->SetSelection(UnitIDs[18]);
		TechTrees_Ages_ComboBox_Building->SetSelection(UnitIDs[19]);
		TechTrees_Ages_ComboBox_Unit->SetSelection(UnitIDs[20]);
		TechTrees_Buildings_ComboBox_ID->SetSelection(UnitIDs[21]);
		TechTrees_Buildings_ComboBox_Building->SetSelection(UnitIDs[22]);
		TechTrees_Buildings_ComboBox_Unit->SetSelection(UnitIDs[23]);
		TechTrees_Units_ComboBox_ID->SetSelection(UnitIDs[24]);
		TechTrees_Units_ComboBox_UpperBuilding->SetSelection(UnitIDs[25]);
		TechTrees_Units_ComboBox_Unit->SetSelection(UnitIDs[26]);
		TechTrees_Researches_ComboBox_UpperBuilding->SetSelection(UnitIDs[27]);
		TechTrees_Researches_ComboBox_Building->SetSelection(UnitIDs[28]);
		TechTrees_Researches_ComboBox_Unit->SetSelection(UnitIDs[29]);
		for(short loop = 0;loop < 30;loop++)
		Terrains_ComboBox_TerrainUnitID[loop]->SetSelection(UnitIDs[loop+34]);
	}
	
	for(short loop = 0;loop < 2;loop++)
	UseAnd[loop] = false;
	
	wxCommandEvent E;
	OnUnitsSelect(E);
}

void AGE_Frame::ListUnitHeads()
{
	string Name;
	short CivSelection = Units_Civs_List->GetSelection();
	short Selection = Units_UnitHeads_List->GetSelection();

	if(CivSelection == -1)
	{
		CivSelection = 0;
	}
	if(Units_UnitHeads_List->GetCount() > 0)
	{
		Units_UnitHeads_List->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	for(short loop = 0;loop < GenieFile->UnitHeaders.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetUnitName(loop, CivSelection, false);
		Units_UnitHeads_List->Append(Name, (void*)&GenieFile->UnitHeaders[loop]);
	}
	Units_UnitHeads_List->SetSelection(Selection);
}

//	This links data into user interface
void AGE_Frame::OnUnitsSelect(wxCommandEvent& Event)
{
	short Selection = Units_Units_List->GetSelection();
	if(Selection != wxNOT_FOUND)	// If a unit is selected.
	{
		if(Added)
		{
			Selection = Units_Units_List->GetCount() - 1;
			Units_Units_List->SetSelection(Selection);
		}
		gdat::Unit * UnitPointer = (gdat::Unit*)Units_Units_List->GetClientData(Selection);
		UnitCivID = Units_Civs_List->GetSelection();
		UnitID = UnitPointer - (&GenieFile->Civs[UnitCivID].Units[0]);

//	Type 10+

		short UnitType = (short)UnitPointer->Type;
		Units_Type->ChangeValue(lexical_cast<string>((short)UnitPointer->Type));
		Units_Type->Container = &UnitPointer->Type;
		switch(UnitType)
		{
			case 10:
				Units_ComboBox_Type->SetSelection(1);
				break;
			case 20:
				Units_ComboBox_Type->SetSelection(2);
				break;
			case 25:
				Units_ComboBox_Type->SetSelection(3);
				break;
			case 30:
				Units_ComboBox_Type->SetSelection(4);
				break;
			case 40:
				Units_ComboBox_Type->SetSelection(5);
				break;
			case 60:
				Units_ComboBox_Type->SetSelection(6);
				break;
			case 70:
				Units_ComboBox_Type->SetSelection(7);
				break;
			case 80:
				Units_ComboBox_Type->SetSelection(8);
				break;
			case 90:
				Units_ComboBox_Type->SetSelection(9);
				break;
			default:
				Units_ComboBox_Type->SetSelection(0);
		}
		Units_ID1->ChangeValue(lexical_cast<string>(UnitPointer->ID1));
		Units_ID1->Container = &UnitPointer->ID1;
		Units_LanguageDllName->ChangeValue(lexical_cast<string>(UnitPointer->LanguageDllName));
		Units_LanguageDllName->Container = &UnitPointer->LanguageDllName;
		Units_DLL_LanguageDllName->SetLabel(LanguageDllString(lexical_cast<unsigned short>(Units_LanguageDllName->GetValue())));
		Units_LanguageDllCreation->ChangeValue(lexical_cast<string>(UnitPointer->LanguageDllCreation));
		Units_LanguageDllCreation->Container = &UnitPointer->LanguageDllCreation;
		Units_DLL_LanguageDllCreation->SetLabel(LanguageDllString(lexical_cast<unsigned short>(Units_LanguageDllCreation->GetValue())));
		Units_Class->ChangeValue(lexical_cast<string>(UnitPointer->Class));
		Units_Class->Container = &UnitPointer->Class;
		Units_ComboBox_Class[0]->SetSelection(UnitPointer->Class + 1);
		Units_StandingGraphic[0]->ChangeValue(lexical_cast<string>(UnitPointer->StandingGraphic.first));
		Units_StandingGraphic[0]->Container = &UnitPointer->StandingGraphic.first;
		Units_ComboBox_StandingGraphic[0]->SetSelection(UnitPointer->StandingGraphic.first + 1);
		Units_DyingGraphic[0]->ChangeValue(lexical_cast<string>(UnitPointer->DyingGraphic.first));
		Units_DyingGraphic[0]->Container = &UnitPointer->DyingGraphic.first;
		Units_ComboBox_DyingGraphic[0]->SetSelection(UnitPointer->DyingGraphic.first + 1);
		Units_DyingGraphic[1]->ChangeValue(lexical_cast<string>(UnitPointer->DyingGraphic.second));
		Units_DyingGraphic[1]->Container = &UnitPointer->DyingGraphic.second;
		Units_ComboBox_DyingGraphic[1]->SetSelection(UnitPointer->DyingGraphic.second + 1);
		Units_DeathMode->ChangeValue(lexical_cast<string>((short)UnitPointer->DeathMode));
		Units_DeathMode->Container = &UnitPointer->DeathMode;
		Units_CheckBox_DeathMode->SetValue((bool)UnitPointer->DeathMode);
		Units_HitPoints->ChangeValue(lexical_cast<string>(UnitPointer->HitPoints));
		Units_HitPoints->Container = &UnitPointer->HitPoints;
		Units_LineOfSight->ChangeValue(lexical_cast<string>(UnitPointer->LineOfSight));
		Units_LineOfSight->Container = &UnitPointer->LineOfSight;
		Units_GarrisonCapacity->ChangeValue(lexical_cast<string>((short)UnitPointer->GarrisonCapacity));
		Units_GarrisonCapacity->Container = &UnitPointer->GarrisonCapacity;
		Units_SizeRadius[0]->ChangeValue(lexical_cast<string>(UnitPointer->SizeRadius.first));
		Units_SizeRadius[0]->Container = &UnitPointer->SizeRadius.first;
		Units_SizeRadius[1]->ChangeValue(lexical_cast<string>(UnitPointer->SizeRadius.second));
		Units_SizeRadius[1]->Container = &UnitPointer->SizeRadius.second;
		Units_HPBarHeight1->ChangeValue(lexical_cast<string>(UnitPointer->HPBarHeight1));
		Units_HPBarHeight1->Container = &UnitPointer->HPBarHeight1;
		Units_TrainSound[0]->ChangeValue(lexical_cast<string>(UnitPointer->TrainSound.first));
		Units_TrainSound[0]->Container = &UnitPointer->TrainSound.first;
		Units_ComboBox_TrainSound[0]->SetSelection(UnitPointer->TrainSound.first + 1);
		Units_DeadUnitID->ChangeValue(lexical_cast<string>(UnitPointer->DeadUnitID));
		Units_DeadUnitID->Container = &UnitPointer->DeadUnitID;
		Units_ComboBox_DeadUnitID->SetSelection(UnitPointer->DeadUnitID + 1);
		Units_PlacementMode->ChangeValue(lexical_cast<string>((short)UnitPointer->PlacementMode));
		Units_PlacementMode->Container = &UnitPointer->PlacementMode;
		Units_AirMode->ChangeValue(lexical_cast<string>((short)UnitPointer->AirMode));
		Units_AirMode->Container = &UnitPointer->AirMode;
		Units_CheckBox_AirMode->SetValue((bool)UnitPointer->AirMode);
		Units_IconID->ChangeValue(lexical_cast<string>(UnitPointer->IconID));
		Units_IconID->Container = &UnitPointer->IconID;
		Units_HideInEditor->ChangeValue(lexical_cast<string>((short)UnitPointer->HideInEditor));
		Units_HideInEditor->Container = &UnitPointer->HideInEditor;
		Units_CheckBox_HideInEditor->SetValue((bool)UnitPointer->HideInEditor);
		Units_Unknown1->ChangeValue(lexical_cast<string>(UnitPointer->Unknown1));
		Units_Unknown1->Container = &UnitPointer->Unknown1;
		Units_CheckBox_Enabled->SetValue((bool)UnitPointer->Enabled);
		Units_PlacementBypassTerrain[0]->ChangeValue(lexical_cast<string>(UnitPointer->PlacementBypassTerrain.first));
		Units_PlacementBypassTerrain[0]->Container = &UnitPointer->PlacementBypassTerrain.first;
		Units_ComboBox_PlacementBypassTerrain[0]->SetSelection(UnitPointer->PlacementBypassTerrain.first + 1);
		Units_PlacementBypassTerrain[1]->ChangeValue(lexical_cast<string>(UnitPointer->PlacementBypassTerrain.second));
		Units_PlacementBypassTerrain[1]->Container = &UnitPointer->PlacementBypassTerrain.second;
		Units_ComboBox_PlacementBypassTerrain[1]->SetSelection(UnitPointer->PlacementBypassTerrain.second + 1);
		Units_PlacementTerrain[0]->ChangeValue(lexical_cast<string>(UnitPointer->PlacementTerrain.first));
		Units_PlacementTerrain[0]->Container = &UnitPointer->PlacementTerrain.first;
		Units_ComboBox_PlacementTerrain[0]->SetSelection(UnitPointer->PlacementTerrain.first + 1);
		Units_PlacementTerrain[1]->ChangeValue(lexical_cast<string>(UnitPointer->PlacementTerrain.second));
		Units_PlacementTerrain[1]->Container = &UnitPointer->PlacementTerrain.second;
		Units_ComboBox_PlacementTerrain[1]->SetSelection(UnitPointer->PlacementTerrain.second + 1);
		Units_EditorRadius[0]->ChangeValue(lexical_cast<string>(UnitPointer->EditorRadius.first));
		Units_EditorRadius[0]->Container = &UnitPointer->EditorRadius.first;
		Units_EditorRadius[1]->ChangeValue(lexical_cast<string>(UnitPointer->EditorRadius.second));
		Units_EditorRadius[1]->Container = &UnitPointer->EditorRadius.second;
		Units_BuildingMode->ChangeValue(lexical_cast<string>((short)UnitPointer->BuildingMode));
		Units_BuildingMode->Container = &UnitPointer->BuildingMode;
		Units_VisibleInFog->ChangeValue(lexical_cast<string>((short)UnitPointer->VisibleInFog));
		Units_VisibleInFog->Container = &UnitPointer->VisibleInFog;
		Units_TerrainRestriction->ChangeValue(lexical_cast<string>(UnitPointer->TerrainRestriction));
		Units_TerrainRestriction->Container = &UnitPointer->TerrainRestriction;
		Units_ComboBox_TerrainRestriction->SetSelection(UnitPointer->TerrainRestriction + 1);
		Units_FlyMode->ChangeValue(lexical_cast<string>((short)UnitPointer->FlyMode));
		Units_FlyMode->Container = &UnitPointer->FlyMode;
		Units_CheckBox_FlyMode->SetValue((bool)UnitPointer->FlyMode);
		Units_ResourceCapacity->ChangeValue(lexical_cast<string>(UnitPointer->ResourceCapacity));
		Units_ResourceCapacity->Container = &UnitPointer->ResourceCapacity;
		Units_ResourceDecay->ChangeValue(lexical_cast<string>(UnitPointer->ResourceDecay));
		Units_ResourceDecay->Container = &UnitPointer->ResourceDecay;
		Units_BlastType->ChangeValue(lexical_cast<string>((short)UnitPointer->BlastType));
		Units_BlastType->Container = &UnitPointer->BlastType;
		Units_Unknown2->ChangeValue(lexical_cast<string>((short)UnitPointer->Unknown2));
		Units_Unknown2->Container = &UnitPointer->Unknown2;
		Units_InteractionMode->ChangeValue(lexical_cast<string>((short)UnitPointer->InteractionMode));
		Units_InteractionMode->Container = &UnitPointer->InteractionMode;
		Units_MinimapMode->ChangeValue(lexical_cast<string>((short)UnitPointer->MinimapMode));
		Units_MinimapMode->Container = &UnitPointer->MinimapMode;
		if(GameVersion >= 2)
		{
			Units_StandingGraphic[1]->ChangeValue(lexical_cast<string>(UnitPointer->StandingGraphic.second));
			Units_StandingGraphic[1]->Container = &UnitPointer->StandingGraphic.second;
			Units_ComboBox_StandingGraphic[1]->SetSelection(UnitPointer->StandingGraphic.second + 1);
			Units_TrainSound[1]->ChangeValue(lexical_cast<string>(UnitPointer->TrainSound.second));
			Units_TrainSound[1]->Container = &UnitPointer->TrainSound.second;
			Units_ComboBox_TrainSound[1]->SetSelection(UnitPointer->TrainSound.second + 1);
			Units_Unknown7->ChangeValue(lexical_cast<string>((short)UnitPointer->Unknown7));
			Units_Unknown7->Container = &UnitPointer->Unknown7;
			Units_Unknown8->ChangeValue(lexical_cast<string>((short)UnitPointer->Unknown8));
			Units_Unknown8->Container = &UnitPointer->Unknown8;
			Units_SelectionShapeType->ChangeValue(lexical_cast<string>((short)UnitPointer->SelectionShapeType));
			Units_SelectionShapeType->Container = &UnitPointer->SelectionShapeType;
			Units_SelectionEffect->ChangeValue(lexical_cast<string>((short)UnitPointer->SelectionEffect));
			Units_SelectionEffect->Container = &UnitPointer->SelectionEffect;
			Units_EditorSelectionColour->ChangeValue(lexical_cast<string>((short)UnitPointer->EditorSelectionColour));
			Units_EditorSelectionColour->Container = &UnitPointer->EditorSelectionColour;
			Units_ID3->ChangeValue(lexical_cast<string>(UnitPointer->ID3));
			Units_ID3->Container = &UnitPointer->ID3;
			Units_Enabled->SetBackgroundColour(wxColour(210, 230, 255));
			Units_Enabled->ChangeValue(lexical_cast<string>(UnitPointer->Enabled));
			Units_CommandAttribute->SetBackgroundColour(wxColour(210, 230, 255));
			Units_CommandAttribute->ChangeValue(lexical_cast<string>(UnitPointer->CommandAttribute));
		}
		else
		{
			Units_Unknown3a->ChangeValue(lexical_cast<string>((short)UnitPointer->Unknown3a));
			Units_Unknown3a->Container = &UnitPointer->Unknown3a;
			Units_Enabled->SetBackgroundColour(wxColour(255, 235, 215));
			Units_Enabled->ChangeValue(lexical_cast<string>((short)UnitPointer->Enabled));
			Units_CommandAttribute->SetBackgroundColour(wxColour(255, 235, 215));
			Units_CommandAttribute->ChangeValue(lexical_cast<string>((short)UnitPointer->CommandAttribute));
		}
		Units_Enabled->Container = &UnitPointer->Enabled;
		Units_CommandAttribute->Container = &UnitPointer->CommandAttribute;
		Units_Unknown3->ChangeValue(lexical_cast<string>(UnitPointer->Unknown3));
		Units_Unknown3->Container = &UnitPointer->Unknown3;
		Units_Unknown3B->ChangeValue(lexical_cast<string>(UnitPointer->Unknown3B));
		Units_Unknown3B->Container = &UnitPointer->Unknown3B;
		Units_LanguageDllHelp->ChangeValue(lexical_cast<string>(UnitPointer->LanguageDllHelp));
		Units_LanguageDllHelp->Container = &UnitPointer->LanguageDllHelp;
		Units_DLL_LanguageDllHelp->SetLabel(LanguageDllString(lexical_cast<unsigned short>(Units_LanguageDllHelp->GetValue())));
		for(short loop = 0;loop < 4;loop++)
		{
			Units_HotKey[loop]->ChangeValue(lexical_cast<string>(UnitPointer->HotKey[loop]));
			Units_HotKey[loop]->Container = &UnitPointer->HotKey[loop];
		}
		Units_DLL_HotKey4->SetLabel(LanguageDllString(lexical_cast<short>(Units_HotKey[3]->GetValue())));
		Units_Unknown4->ChangeValue(lexical_cast<string>((short)UnitPointer->Unknown4));
		Units_Unknown4->Container = &UnitPointer->Unknown4;
		Units_Unknown5->ChangeValue(lexical_cast<string>((short)UnitPointer->Unknown5));
		Units_Unknown5->Container = &UnitPointer->Unknown5;
		Units_Unselectable->ChangeValue(lexical_cast<string>((short)UnitPointer->Unselectable));
		Units_Unselectable->Container = &UnitPointer->Unselectable;
		Units_CheckBox_Unselectable->SetValue((bool)UnitPointer->Unselectable);
		Units_Unknown6->ChangeValue(lexical_cast<string>((short)UnitPointer->Unknown6));
		Units_Unknown6->Container = &UnitPointer->Unknown6;
		Units_SelectionMask->ChangeValue(lexical_cast<string>((short)UnitPointer->SelectionMask));
		Units_SelectionMask->Container = &UnitPointer->SelectionMask;
		Units_SelectionShape->ChangeValue(lexical_cast<string>((short)UnitPointer->SelectionShape));
		Units_SelectionShape->Container = &UnitPointer->SelectionShape;
		if(GameVersion != 2)
		{
			Units_Attribute->ChangeValue(lexical_cast<string>((short)UnitPointer->Attribute));
			Units_Attribute->Container = &UnitPointer->Attribute;
			Units_Civ->ChangeValue(lexical_cast<string>((short)UnitPointer->Civilization));
			Units_Civ->Container = &UnitPointer->Civilization;
			Units_ComboBox_Civ->SetSelection(UnitPointer->Civilization + 1);
		}
		if(GameVersion >= 3)
		for(short loop = 0;loop < 2;loop++)
		{
			Units_Unknown9[loop]->ChangeValue(lexical_cast<string>((short)UnitPointer->Unknown9[loop]));
			Units_Unknown9[loop]->Container = &UnitPointer->Unknown9[loop];
		}
		Units_SelectionRadius[0]->ChangeValue(lexical_cast<string>(UnitPointer->SelectionRadius.first));
		Units_SelectionRadius[0]->Container = &UnitPointer->SelectionRadius.first;
		Units_SelectionRadius[1]->ChangeValue(lexical_cast<string>(UnitPointer->SelectionRadius.second));
		Units_SelectionRadius[1]->Container = &UnitPointer->SelectionRadius.second;
		Units_HPBarHeight2->ChangeValue(lexical_cast<string>(UnitPointer->HPBarHeight2));
		Units_HPBarHeight2->Container = &UnitPointer->HPBarHeight2;
		Units_SelectionSound->ChangeValue(lexical_cast<string>(UnitPointer->SelectionSound));
		Units_SelectionSound->Container = &UnitPointer->SelectionSound;
		Units_ComboBox_SelectionSound->SetSelection(UnitPointer->SelectionSound + 1);
		Units_DyingSound->ChangeValue(lexical_cast<string>(UnitPointer->DyingSound));
		Units_DyingSound->Container = &UnitPointer->DyingSound;
		Units_ComboBox_DyingSound->SetSelection(UnitPointer->DyingSound + 1);
		Units_AttackSound->ChangeValue(lexical_cast<string>(UnitPointer->AttackSound));
		Units_AttackSound->Container = &UnitPointer->AttackSound;
		Units_ComboBox_AttackSound->SetSelection(UnitPointer->AttackSound + 1);
		Units_Name->ChangeValue(lexical_cast<string>(UnitPointer->Name));
		Units_Name->Container = &UnitPointer->Name;
		if(GameVersion >= 4)
		{
			Units_Name2->ChangeValue(lexical_cast<string>(UnitPointer->Name2));
			Units_Name2->Container = &UnitPointer->Name2;
			Units_Unitline->ChangeValue(lexical_cast<string>(UnitPointer->Unitline));
			Units_Unitline->Container = &UnitPointer->Unitline;
			Units_ComboBox_Unitline->SetSelection(UnitPointer->Unitline + 1);
			Units_MinTechLevel->ChangeValue(lexical_cast<string>((short)UnitPointer->MinTechLevel));
			Units_MinTechLevel->Container = &UnitPointer->MinTechLevel;
		}
		Units_ID2->ChangeValue(lexical_cast<string>(UnitPointer->ID2));
		Units_ID2->Container = &UnitPointer->ID2;

//	Type 20+
		
		switch(UnitType)
		{
			case 20:
			case 25:
			case 30:
			case 40:
			case 60:
			case 70:
			case 80:
			Units_Speed->Enable(true);
			Units_Speed->ChangeValue(lexical_cast<string>(UnitPointer->Speed));
			Units_Speed->Container = &UnitPointer->Speed;
			break;
			default:
			Units_Speed->Enable(false);
			Units_Speed->ChangeValue("0");
		}
	
//	Type 30+

		switch(UnitType)
		{
			case 30:
			case 40:
			case 60:
			case 70:
			case 80:
			for(short loop = 0;loop < 2;loop++)
			{
				Units_WalkingGraphic[loop]->Enable(true);
				Units_ComboBox_WalkingGraphic[loop]->Enable(true);
			}
			Units_RotationSpeed->Enable(true);
			Units_Unknown11->Enable(true);
			Units_TrackingUnit->Enable(true);
			Units_ComboBox_TrackingUnit->Enable(true);
			Units_TrackingUnitUsed->Enable(true);
			Units_TrackingUnitDensity->Enable(true);
			Units_Unknown12->Enable(true);
			for(short loop = 0;loop < 17;loop++)
			Units_Unknown16[loop]->Enable(true);

			Units_WalkingGraphic[0]->ChangeValue(lexical_cast<string>(UnitPointer->DeadFish.WalkingGraphic.first));
			Units_WalkingGraphic[0]->Container = &UnitPointer->DeadFish.WalkingGraphic.first;
			Units_ComboBox_WalkingGraphic[0]->SetSelection(UnitPointer->DeadFish.WalkingGraphic.first + 1);
			Units_WalkingGraphic[1]->ChangeValue(lexical_cast<string>(UnitPointer->DeadFish.WalkingGraphic.second));
			Units_WalkingGraphic[1]->Container = &UnitPointer->DeadFish.WalkingGraphic.second;
			Units_ComboBox_WalkingGraphic[1]->SetSelection(UnitPointer->DeadFish.WalkingGraphic.second + 1);
			Units_RotationSpeed->ChangeValue(lexical_cast<string>(UnitPointer->DeadFish.RotationSpeed));
			Units_RotationSpeed->Container = &UnitPointer->DeadFish.RotationSpeed;
			Units_Unknown11->ChangeValue(lexical_cast<string>((short)UnitPointer->DeadFish.Unknown11));
			Units_Unknown11->Container = &UnitPointer->DeadFish.Unknown11;
			Units_TrackingUnit->ChangeValue(lexical_cast<string>(UnitPointer->DeadFish.TrackingUnit));
			Units_TrackingUnit->Container = &UnitPointer->DeadFish.TrackingUnit;
			Units_ComboBox_TrackingUnit->SetSelection(UnitPointer->DeadFish.TrackingUnit + 1);
			Units_TrackingUnitUsed->ChangeValue(lexical_cast<string>((short)UnitPointer->DeadFish.TrackingUnitUsed));
			Units_TrackingUnitUsed->Container = &UnitPointer->DeadFish.TrackingUnitUsed;
			Units_TrackingUnitDensity->ChangeValue(lexical_cast<string>(UnitPointer->DeadFish.TrackingUnitDensity));
			Units_TrackingUnitDensity->Container = &UnitPointer->DeadFish.TrackingUnitDensity;
			if(GameVersion >= 2)
			{
				Units_Unknown12->ChangeValue(lexical_cast<string>(UnitPointer->DeadFish.Unknown12));
				Units_Unknown12->Container = &UnitPointer->DeadFish.Unknown12;
				for(short loop = 0;loop < 17;loop++)
				{
					Units_Unknown16[loop]->ChangeValue(lexical_cast<string>((short)UnitPointer->DeadFish.Unknown16[loop]));
					Units_Unknown16[loop]->Container = &UnitPointer->DeadFish.Unknown16[loop];
				}
			}
			else
			{
				Units_Unknown16[0]->ChangeValue(lexical_cast<string>((short)UnitPointer->DeadFish.Unknown16[0]));
				Units_Unknown16[0]->Container = &UnitPointer->DeadFish.Unknown16[0];
			}
			break;
			default:
			for(short loop = 0;loop < 2;loop++)
			{
				Units_WalkingGraphic[loop]->Enable(false);
				Units_WalkingGraphic[loop]->ChangeValue("0");
				Units_ComboBox_WalkingGraphic[loop]->Enable(false);
				Units_ComboBox_WalkingGraphic[loop]->SetSelection(0);
			}
			Units_RotationSpeed->Enable(false);
			Units_RotationSpeed->ChangeValue("0");
			Units_Unknown11->Enable(false);
			Units_Unknown11->ChangeValue("0");
			Units_TrackingUnit->Enable(false);
			Units_TrackingUnit->ChangeValue("0");
			Units_ComboBox_TrackingUnit->Enable(false);
			Units_ComboBox_TrackingUnit->SetSelection(0);
			Units_TrackingUnitUsed->Enable(false);
			Units_TrackingUnitUsed->ChangeValue("0");
			Units_TrackingUnitDensity->Enable(false);
			Units_TrackingUnitDensity->ChangeValue("0");
			Units_Unknown12->Enable(false);
			Units_Unknown12->ChangeValue("0");
			for(short loop = 0;loop < 17;loop++)
			{
				Units_Unknown16[loop]->Enable(false);
				Units_Unknown16[loop]->ChangeValue("0");
			}
		}
//	Type 40+

		switch(UnitType)
		{
			case 40:
			case 60:
			case 70:
			case 80:
			Units_SheepConversion->Enable(true);
			Units_CheckBox_SheepConversion->Enable(true);
			Units_SearchRadius->Enable(true);
			Units_WorkRate->Enable(true);
			for(short loop = 0;loop < 2;loop++)
			{
				Units_DropSite[loop]->Enable(true);
				Units_ComboBox_DropSite[loop]->Enable(true);
			}
			Units_VillagerMode->Enable(true);
			Units_MoveSound->Enable(true);
			Units_ComboBox_MoveSound->Enable(true);
			Units_StopSound->Enable(true);
			Units_ComboBox_StopSound->Enable(true);
			Units_AnimalMode->Enable(true);
			Units_CheckBox_AnimalMode->Enable(true);

			Units_SheepConversion->ChangeValue(lexical_cast<string>(UnitPointer->Bird.SheepConversion));
			Units_SheepConversion->Container = &UnitPointer->Bird.SheepConversion;
			switch(UnitPointer->Bird.SheepConversion)
			{
				case -1:
				{
					Units_CheckBox_SheepConversion->SetValue(false);
				}
				break;
				case 0:
				{
					Units_CheckBox_SheepConversion->SetValue(true);
				}
				break;
				default:
				{
					Units_CheckBox_SheepConversion->SetValue(false);
				}
			}
			Units_SearchRadius->ChangeValue(lexical_cast<string>(UnitPointer->Bird.SearchRadius));
			Units_SearchRadius->Container = &UnitPointer->Bird.SearchRadius;
			Units_WorkRate->ChangeValue(lexical_cast<string>(UnitPointer->Bird.WorkRate));
			Units_WorkRate->Container = &UnitPointer->Bird.WorkRate;
			Units_DropSite[0]->ChangeValue(lexical_cast<string>(UnitPointer->Bird.DropSite.first));
			Units_DropSite[0]->Container = &UnitPointer->Bird.DropSite.first;
			Units_ComboBox_DropSite[0]->SetSelection(UnitPointer->Bird.DropSite.first + 1);
			Units_DropSite[1]->ChangeValue(lexical_cast<string>(UnitPointer->Bird.DropSite.second));
			Units_DropSite[1]->Container = &UnitPointer->Bird.DropSite.second;
			Units_ComboBox_DropSite[1]->SetSelection(UnitPointer->Bird.DropSite.second + 1);
			Units_VillagerMode->ChangeValue(lexical_cast<string>((short)UnitPointer->Bird.VillagerMode));
			Units_VillagerMode->Container = &UnitPointer->Bird.VillagerMode;
			Units_MoveSound->ChangeValue(lexical_cast<string>(UnitPointer->Bird.MoveSound));
			Units_MoveSound->Container = &UnitPointer->Bird.MoveSound;
			Units_ComboBox_MoveSound->SetSelection(UnitPointer->Bird.MoveSound + 1);
			Units_StopSound->ChangeValue(lexical_cast<string>(UnitPointer->Bird.StopSound));
			Units_StopSound->Container = &UnitPointer->Bird.StopSound;
			Units_ComboBox_StopSound->SetSelection(UnitPointer->Bird.StopSound + 1);
			Units_AnimalMode->ChangeValue(lexical_cast<string>((short)UnitPointer->Bird.AnimalMode));
			Units_AnimalMode->Container = &UnitPointer->Bird.AnimalMode;
			Units_CheckBox_AnimalMode->SetValue((bool)UnitPointer->Bird.AnimalMode);
			break;
			default:
			Units_SheepConversion->Enable(false);
			Units_SheepConversion->ChangeValue("0");
			Units_CheckBox_SheepConversion->Enable(false);
			Units_CheckBox_SheepConversion->SetValue(false);
			Units_SearchRadius->Enable(false);
			Units_SearchRadius->ChangeValue("0");
			Units_WorkRate->Enable(false);
			Units_WorkRate->ChangeValue("0");
			for(short loop = 0;loop < 2;loop++)
			{
				Units_DropSite[loop]->Enable(false);
				Units_DropSite[loop]->ChangeValue("0");
				Units_ComboBox_DropSite[loop]->Enable(false);
				Units_ComboBox_DropSite[loop]->SetSelection(0);
			}
			Units_VillagerMode->Enable(false);
			Units_VillagerMode->ChangeValue("0");
			Units_MoveSound->Enable(false);
			Units_MoveSound->ChangeValue("0");
			Units_ComboBox_MoveSound->Enable(false);
			Units_ComboBox_MoveSound->SetSelection(0);
			Units_StopSound->Enable(false);
			Units_StopSound->ChangeValue("0");
			Units_ComboBox_StopSound->Enable(false);
			Units_ComboBox_StopSound->SetSelection(0);
			Units_AnimalMode->Enable(false);
			Units_AnimalMode->ChangeValue("0");
			Units_CheckBox_AnimalMode->Enable(false);
			Units_CheckBox_AnimalMode->SetValue(false);
		}

//	Type 60+

		switch(UnitType)
		{
			case 60:
			case 70:
			case 80:
			for(short loop = 0;loop < 2;loop++)
			Units_Unknown20[loop]->Enable(true);
			Units_Unknown21->Enable(true);
			Units_MaxRange->Enable(true);
			Units_BlastRadius->Enable(true);
			Units_ReloadTime1->Enable(true);
			Units_ProjectileUnitID->Enable(true);
			Units_ComboBox_ProjectileUnitID->Enable(true);
			Units_AccuracyPercent->Enable(true);
			Units_TowerMode->Enable(true);
			Units_CheckBox_TowerMode->Enable(true);
			Units_Delay->Enable(true);
			for(short loop = 0;loop < 4;loop++)
			Units_GraphicDisplacement[loop]->Enable(true);
			Units_BlastLevel->Enable(true);
			Units_MinRange->Enable(true);
			Units_GarrisonRecoveryRate->Enable(true);
			Units_AttackGraphic->Enable(true);
			Units_ComboBox_AttackGraphic->Enable(true);
			Units_DisplayedMeleeArmour->Enable(true);
			Units_DisplayedAttack->Enable(true);
			Units_DisplayedRange->Enable(true);
			Units_ReloadTime2->Enable(true);
			
			Attacks_Class->Enable(true);
			for(short loop = 0;loop < 2;loop++)
			Attacks_ComboBox_Class[loop]->Enable(true);
			Attacks_Amount->Enable(true);
			Armors_Class->Enable(true);
			Armors_Amount->Enable(true);

			Units_Unknown20[0]->ChangeValue(lexical_cast<string>((short)UnitPointer->Projectile.Unknown20));
			Units_Unknown20[0]->Container = &UnitPointer->Projectile.Unknown20;
			if(GameVersion >= 3)
			{
				Units_Unknown20[1]->ChangeValue(lexical_cast<string>((short)UnitPointer->Projectile.Unknown20_1));
				Units_Unknown20[1]->Container = &UnitPointer->Projectile.Unknown20_1;
			}
			Units_Unknown21->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.Unknown21));
			Units_Unknown21->Container = &UnitPointer->Projectile.Unknown21;
			Units_MaxRange->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.MaxRange));
			Units_MaxRange->Container = &UnitPointer->Projectile.MaxRange;
			Units_BlastRadius->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.BlastRadius));
			Units_BlastRadius->Container = &UnitPointer->Projectile.BlastRadius;
			Units_ReloadTime1->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.ReloadTime1));
			Units_ReloadTime1->Container = &UnitPointer->Projectile.ReloadTime1;
			Units_ProjectileUnitID->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.ProjectileUnitID));
			Units_ProjectileUnitID->Container = &UnitPointer->Projectile.ProjectileUnitID;
			Units_ComboBox_ProjectileUnitID->SetSelection(UnitPointer->Projectile.ProjectileUnitID + 1);
			Units_AccuracyPercent->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.AccuracyPercent));
			Units_AccuracyPercent->Container = &UnitPointer->Projectile.AccuracyPercent;
			Units_TowerMode->ChangeValue(lexical_cast<string>((short)UnitPointer->Projectile.TowerMode));
			Units_TowerMode->Container = &UnitPointer->Projectile.TowerMode;
			Units_CheckBox_TowerMode->SetValue((bool)UnitPointer->Projectile.TowerMode);
			Units_Delay->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.Delay));
			Units_Delay->Container = &UnitPointer->Projectile.Delay;
			for(short loop = 0;loop < 3;loop++)
			{
				Units_GraphicDisplacement[loop]->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.GraphicDisplacement[loop]));
				Units_GraphicDisplacement[loop]->Container = &UnitPointer->Projectile.GraphicDisplacement[loop];
			}
			Units_BlastLevel->ChangeValue(lexical_cast<string>((short)UnitPointer->Projectile.Unknown23));
			Units_BlastLevel->Container = &UnitPointer->Projectile.Unknown23;
			Units_MinRange->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.MinRange));
			Units_MinRange->Container = &UnitPointer->Projectile.MinRange;
			if(GameVersion >= 2)
			{
				Units_GarrisonRecoveryRate->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.GarrisonRecoveryRate));
				Units_GarrisonRecoveryRate->Container = &UnitPointer->Projectile.GarrisonRecoveryRate;
			}
			Units_AttackGraphic->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.AttackGraphic));
			Units_AttackGraphic->Container = &UnitPointer->Projectile.AttackGraphic;
			Units_ComboBox_AttackGraphic->SetSelection(UnitPointer->Projectile.AttackGraphic + 1);
			Units_DisplayedMeleeArmour->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.DisplayedMeleeArmour));
			Units_DisplayedMeleeArmour->Container = &UnitPointer->Projectile.DisplayedMeleeArmour;
			Units_DisplayedAttack->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.DisplayedAttack));
			Units_DisplayedAttack->Container = &UnitPointer->Projectile.DisplayedAttack;
			Units_DisplayedRange->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.DisplayedRange));
			Units_DisplayedRange->Container = &UnitPointer->Projectile.DisplayedRange;
			Units_ReloadTime2->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.ReloadTime2));
			Units_ReloadTime2->Container = &UnitPointer->Projectile.ReloadTime2;
			break;
			default:
			for(short loop = 0;loop < 2;loop++)
			{
				Units_Unknown20[loop]->Enable(false);
				Units_Unknown20[loop]->ChangeValue("0");
			}
			Units_Unknown21->Enable(false);
			Units_Unknown21->ChangeValue("0");
			Units_MaxRange->Enable(false);
			Units_MaxRange->ChangeValue("0");
			Units_BlastRadius->Enable(false);
			Units_BlastRadius->ChangeValue("0");
			Units_ReloadTime1->Enable(false);
			Units_ReloadTime1->ChangeValue("0");
			Units_ProjectileUnitID->Enable(false);
			Units_ProjectileUnitID->ChangeValue("0");
			Units_ComboBox_ProjectileUnitID->Enable(false);
			Units_ComboBox_ProjectileUnitID->SetSelection(0);
			Units_AccuracyPercent->Enable(false);
			Units_AccuracyPercent->ChangeValue("0");
			Units_TowerMode->Enable(false);
			Units_TowerMode->ChangeValue("0");
			Units_CheckBox_TowerMode->Enable(false);
			Units_CheckBox_TowerMode->SetValue(false);
			Units_Delay->Enable(false);
			Units_Delay->ChangeValue("0");
			for(short loop = 0;loop < 3;loop++)
			{
				Units_GraphicDisplacement[loop]->Enable(false);
				Units_GraphicDisplacement[loop]->ChangeValue("0");
			}
			Units_BlastLevel->Enable(false);
			Units_BlastLevel->ChangeValue("0");
			Units_MinRange->Enable(false);
			Units_MinRange->ChangeValue("0");
			Units_GarrisonRecoveryRate->Enable(false);
			Units_GarrisonRecoveryRate->ChangeValue("0");
			Units_AttackGraphic->Enable(false);
			Units_AttackGraphic->ChangeValue("0");
			Units_ComboBox_AttackGraphic->Enable(false);
			Units_ComboBox_AttackGraphic->SetSelection(0);
			Units_DisplayedMeleeArmour->Enable(false);
			Units_DisplayedMeleeArmour->ChangeValue("0");
			Units_DisplayedAttack->Enable(false);
			Units_DisplayedAttack->ChangeValue("0");
			Units_DisplayedRange->Enable(false);
			Units_DisplayedRange->ChangeValue("0");
			Units_ReloadTime2->Enable(false);
			Units_ReloadTime2->ChangeValue("0");
			
			Attacks_Class->Enable(false);
			for(short loop = 0;loop < 2;loop++)
			Attacks_ComboBox_Class[loop]->Enable(false);
			Attacks_Amount->Enable(false);
			Armors_Class->Enable(false);
			Armors_Amount->Enable(false);
		}
		
//	Type 60 only

		switch(UnitType)
		{
			case 60:
			Units_StretchMode->Enable(true);
			Units_CompensationMode->Enable(true);
			Units_DropAnimationMode->Enable(true);
			Units_PenetrationMode->Enable(true);
			Units_Unknown24->Enable(true);
			Units_ProjectileArc->Enable(true);

			Units_StretchMode->ChangeValue(lexical_cast<string>((short)UnitPointer->ProjectileOnly.StretchMode));
			Units_StretchMode->Container = &UnitPointer->ProjectileOnly.StretchMode;
			Units_CompensationMode->ChangeValue(lexical_cast<string>((short)UnitPointer->ProjectileOnly.CompensationMode));
			Units_CompensationMode->Container = &UnitPointer->ProjectileOnly.CompensationMode;
			Units_DropAnimationMode->ChangeValue(lexical_cast<string>((short)UnitPointer->ProjectileOnly.DropAnimationMode));
			Units_DropAnimationMode->Container = &UnitPointer->ProjectileOnly.DropAnimationMode;
			Units_PenetrationMode->ChangeValue(lexical_cast<string>((short)UnitPointer->ProjectileOnly.PenetrationMode));
			Units_PenetrationMode->Container = &UnitPointer->ProjectileOnly.PenetrationMode;
			Units_Unknown24->ChangeValue(lexical_cast<string>((short)UnitPointer->ProjectileOnly.Unknown24));
			Units_Unknown24->Container = &UnitPointer->ProjectileOnly.Unknown24;
			Units_ProjectileArc->ChangeValue(lexical_cast<string>(UnitPointer->ProjectileOnly.ProjectileArc));
			Units_ProjectileArc->Container = &UnitPointer->ProjectileOnly.ProjectileArc;
			break;
			default:
			Units_StretchMode->Enable(false);
			Units_StretchMode->ChangeValue("0");
			Units_CompensationMode->Enable(false);
			Units_CompensationMode->ChangeValue("0");
			Units_DropAnimationMode->Enable(false);
			Units_DropAnimationMode->ChangeValue("0");
			Units_PenetrationMode->Enable(false);
			Units_PenetrationMode->ChangeValue("0");
			Units_Unknown24->Enable(false);
			Units_Unknown24->ChangeValue("0");
			Units_ProjectileArc->Enable(false);
			Units_ProjectileArc->ChangeValue("0");
		}
		
//	Type 70+

		switch(UnitType)
		{
			case 70:
			case 80:
			for(short loop = 0;loop < 2;loop++)
			{
				Units_GarrisonGraphic[loop]->Enable(true);
				Units_ComboBox_GarrisonGraphic[loop]->Enable(true);
			}
			for(short loop = 0;loop < 3;loop++)
			{
				Units_CostType[loop]->Enable(true);
				Units_ComboBox_CostType[loop]->Enable(true);
				Units_CostAmount[loop]->Enable(true);
				Units_CostUsed[loop]->Enable(true);
				Units_CheckBox_CostUsed[loop]->Enable(true);
				Units_Unknown27[loop]->Enable(true);
				Units_AttackMissileDuplicationSpawning[loop]->Enable(true);
			}
			Units_TrainTime->Enable(true);
			Units_TrainLocationID->Enable(true);
			Units_ComboBox_TrainLocationID->Enable(true);
			Units_ButtonID->Enable(true);
			Units_Unknown26->Enable(true);
			Units_Unknown28->Enable(true);
			Units_MissileGraphicDelay->Enable(true);
			Units_HeroMode->Enable(true);
			Units_CheckBox_HeroMode->Enable(true);
			Units_AttackMissileDuplicationAmount1->Enable(true);
			Units_AttackMissileDuplicationAmount2->Enable(true);
			Units_AttackMissileDuplicationUnit->Enable(true);
			Units_ComboBox_AttackMissileDuplicationUnit->Enable(true);
			Units_AttackMissileDuplicationGraphic->Enable(true);
			Units_ComboBox_AttackMissileDuplicationGraphic->Enable(true);
			Units_Unknown29->Enable(true);
			Units_DisplayedPierceArmour->Enable(true);

			for(short loop = 0;loop < 3;loop++)
			{
				Units_CostType[loop]->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.ResourceCosts[loop].Type));
				Units_CostType[loop]->Container = &UnitPointer->Creatable.ResourceCosts[loop].Type;
				Units_ComboBox_CostType[loop]->SetSelection(UnitPointer->Creatable.ResourceCosts[loop].Type + 1);
				Units_CostAmount[loop]->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.ResourceCosts[loop].Amount));
				Units_CostAmount[loop]->Container = &UnitPointer->Creatable.ResourceCosts[loop].Amount;
				Units_CostUsed[loop]->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.ResourceCosts[loop].Enabled));
				Units_CostUsed[loop]->Container = &UnitPointer->Creatable.ResourceCosts[loop].Enabled;
				Units_CheckBox_CostUsed[loop]->SetValue((bool)UnitPointer->Creatable.ResourceCosts[loop].Enabled);
			}
			Units_TrainTime->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.TrainTime));
			Units_TrainTime->Container = &UnitPointer->Creatable.TrainTime;
			Units_TrainLocationID->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.TrainLocationID));
			Units_TrainLocationID->Container = &UnitPointer->Creatable.TrainLocationID;
			Units_ComboBox_TrainLocationID->SetSelection(UnitPointer->Creatable.TrainLocationID + 1);
			Units_ButtonID->ChangeValue(lexical_cast<string>((short)UnitPointer->Creatable.ButtonID));
			Units_ButtonID->Container = &UnitPointer->Creatable.ButtonID;
			if(GameVersion >= 2)
			{
				Units_Unknown26->ChangeValue(lexical_cast<string>((short)UnitPointer->Creatable.Unknown26));
				Units_Unknown26->Container = &UnitPointer->Creatable.Unknown26;
				for(short loop = 0;loop < 3;loop++)
				{
					Units_Unknown27[loop]->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.Unknown27[loop]));
					Units_Unknown27[loop]->Container = &UnitPointer->Creatable.Unknown27[loop];
				}
				Units_Unknown28->ChangeValue(lexical_cast<string>((short)UnitPointer->Creatable.Unknown28));
				Units_Unknown28->Container = &UnitPointer->Creatable.Unknown28;
				Units_MissileGraphicDelay->ChangeValue(lexical_cast<string>((short)UnitPointer->Creatable.MissileGraphicDelay));
				Units_MissileGraphicDelay->Container = &UnitPointer->Creatable.MissileGraphicDelay;
				Units_HeroMode->ChangeValue(lexical_cast<string>((short)UnitPointer->Creatable.HeroMode));
				Units_HeroMode->Container = &UnitPointer->Creatable.HeroMode;
				Units_CheckBox_HeroMode->SetValue((bool)UnitPointer->Creatable.HeroMode);
				Units_GarrisonGraphic[0]->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.GarrisonGraphic.first));
				Units_GarrisonGraphic[0]->Container = &UnitPointer->Creatable.GarrisonGraphic.first;
				Units_ComboBox_GarrisonGraphic[0]->SetSelection(UnitPointer->Creatable.GarrisonGraphic.first + 1);
				Units_GarrisonGraphic[1]->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.GarrisonGraphic.second));
				Units_GarrisonGraphic[1]->Container = &UnitPointer->Creatable.GarrisonGraphic.second;
				Units_ComboBox_GarrisonGraphic[1]->SetSelection(UnitPointer->Creatable.GarrisonGraphic.second + 1);
				Units_AttackMissileDuplicationAmount1->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.AttackMissileDuplicationAmount1));
				Units_AttackMissileDuplicationAmount1->Container = &UnitPointer->Creatable.AttackMissileDuplicationAmount1;
				Units_AttackMissileDuplicationAmount2->ChangeValue(lexical_cast<string>((short)UnitPointer->Creatable.AttackMissileDuplicationAmount2));
				Units_AttackMissileDuplicationAmount2->Container = &UnitPointer->Creatable.AttackMissileDuplicationAmount2;
				for(short loop = 0;loop < 3;loop++)
				{
					Units_AttackMissileDuplicationSpawning[loop]->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.AttackMissileDuplicationSpawning[loop]));
					Units_AttackMissileDuplicationSpawning[loop]->Container = &UnitPointer->Creatable.AttackMissileDuplicationSpawning[loop];
				}
				Units_AttackMissileDuplicationUnit->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.AttackMissileDuplicationUnit));
				Units_AttackMissileDuplicationUnit->Container = &UnitPointer->Creatable.AttackMissileDuplicationUnit;
				Units_ComboBox_AttackMissileDuplicationUnit->SetSelection(UnitPointer->Creatable.AttackMissileDuplicationUnit + 1);
				Units_AttackMissileDuplicationGraphic->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.AttackMissileDuplicationGraphic));
				Units_AttackMissileDuplicationGraphic->Container = &UnitPointer->Creatable.AttackMissileDuplicationGraphic;
				Units_ComboBox_AttackMissileDuplicationGraphic->SetSelection(UnitPointer->Creatable.AttackMissileDuplicationGraphic + 1);
				Units_Unknown29->ChangeValue(lexical_cast<string>((short)UnitPointer->Creatable.Unknown29));
				Units_Unknown29->Container = &UnitPointer->Creatable.Unknown29;
			}
			Units_DisplayedPierceArmour->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.DisplayedPierceArmour));
			Units_DisplayedPierceArmour->Container = &UnitPointer->Creatable.DisplayedPierceArmour;
			break;
			default:
			for(short loop = 0;loop < 2;loop++)
			{
				Units_GarrisonGraphic[loop]->Enable(false);
				Units_GarrisonGraphic[loop]->ChangeValue("0");
				Units_ComboBox_GarrisonGraphic[loop]->Enable(false);
				Units_ComboBox_GarrisonGraphic[loop]->SetSelection(0);
			}
			for(short loop = 0;loop < 3;loop++)
			{
				Units_CostType[loop]->Enable(false);
				Units_CostType[loop]->ChangeValue("0");
				Units_ComboBox_CostType[loop]->Enable(false);
				Units_ComboBox_CostType[loop]->SetSelection(0);
				Units_CostAmount[loop]->Enable(false);
				Units_CostAmount[loop]->ChangeValue("0");
				Units_CostUsed[loop]->Enable(false);
				Units_CostUsed[loop]->ChangeValue("0");
				Units_CheckBox_CostUsed[loop]->Enable(false);
				Units_CheckBox_CostUsed[loop]->SetValue(false);
				Units_Unknown27[loop]->Enable(false);
				Units_Unknown27[loop]->ChangeValue("0");
				Units_AttackMissileDuplicationSpawning[loop]->Enable(false);
				Units_AttackMissileDuplicationSpawning[loop]->ChangeValue("0");
			}
			Units_TrainTime->Enable(false);
			Units_TrainTime->ChangeValue("0");
			Units_TrainLocationID->Enable(false);
			Units_TrainLocationID->ChangeValue("0");
			Units_ComboBox_TrainLocationID->Enable(false);
			Units_ComboBox_TrainLocationID->SetSelection(0);
			Units_ButtonID->Enable(false);
			Units_ButtonID->ChangeValue("0");
			Units_Unknown26->Enable(false);
			Units_Unknown26->ChangeValue("0");
			Units_Unknown28->Enable(false);
			Units_Unknown28->ChangeValue("0");
			Units_MissileGraphicDelay->Enable(false);
			Units_MissileGraphicDelay->ChangeValue("0");
			Units_HeroMode->Enable(false);
			Units_HeroMode->ChangeValue("0");
			Units_CheckBox_HeroMode->Enable(false);
			Units_CheckBox_HeroMode->SetValue(false);
			Units_AttackMissileDuplicationAmount1->Enable(false);
			Units_AttackMissileDuplicationAmount1->ChangeValue("0");
			Units_AttackMissileDuplicationAmount2->Enable(false);
			Units_AttackMissileDuplicationAmount2->ChangeValue("0");
			Units_AttackMissileDuplicationUnit->Enable(false);
			Units_AttackMissileDuplicationUnit->ChangeValue("0");
			Units_ComboBox_AttackMissileDuplicationUnit->Enable(false);
			Units_ComboBox_AttackMissileDuplicationUnit->SetSelection(0);
			Units_AttackMissileDuplicationGraphic->Enable(false);
			Units_AttackMissileDuplicationGraphic->ChangeValue("0");
			Units_ComboBox_AttackMissileDuplicationGraphic->Enable(false);
			Units_ComboBox_AttackMissileDuplicationGraphic->SetSelection(0);
			Units_Unknown29->Enable(false);
			Units_Unknown29->ChangeValue("0");
			Units_DisplayedPierceArmour->Enable(false);
			Units_DisplayedPierceArmour->ChangeValue("0");
		}
		
//	Type 80

		switch(UnitType)
		{
			case 80:
			Units_ConstructionGraphicID->Enable(true);
			Units_ComboBox_ConstructionGraphicID->Enable(true);
			Units_SnowGraphicID->Enable(true);
			Units_ComboBox_SnowGraphicID->Enable(true);
			Units_AdjacentMode->Enable(true);
			Units_CheckBox_AdjacentMode->Enable(true);
			Units_Unknown31->Enable(true);
			Units_Unknown31b->Enable(true);
			Units_CheckBox_Unknown31b->Enable(true);
			Units_StackUnitID->Enable(true);
			Units_ComboBox_StackUnitID->Enable(true);
			Units_TerrainID->Enable(true);
			Units_ComboBox_TerrainID->Enable(true);
			Units_Unknown32->Enable(true);
			Units_ResearchID->Enable(true);
			Units_ComboBox_ResearchID->Enable(true);
			Units_Unknown33->Enable(true);
			for(short loop = 0;loop < 4;loop++)
			{
				Units_AnnexUnit[loop]->Enable(true);
				Units_ComboBox_AnnexUnit[loop]->Enable(true);
				for(short loop2 = 0;loop2 < 2;loop2++)
				Units_AnnexUnitMisplacement[loop][loop2]->Enable(true);
			}
			Units_HeadUnit->Enable(true);
			Units_ComboBox_HeadUnit->Enable(true);
			Units_TransformUnit->Enable(true);
			Units_ComboBox_TransformUnit->Enable(true);
			Units_Unknown34->Enable(true);
			Units_ConstructionSound->Enable(true);
			Units_ComboBox_ConstructionSound->Enable(true);
			Units_GarrisonType->Enable(true);
			Units_ComboBox_GarrisonType->Enable(true);
			Units_GarrisonHealRate->Enable(true);
			Units_Unknown35->Enable(true);
			Units_Unknown36->Enable(true);
			for(short loop = 0;loop < 6;loop++)
			Units_Unknown37[loop]->Enable(true);
			
			Units_ConstructionGraphicID->ChangeValue(lexical_cast<string>(UnitPointer->Building.ConstructionGraphicID));
			Units_ConstructionGraphicID->Container = &UnitPointer->Building.ConstructionGraphicID;
			Units_ComboBox_ConstructionGraphicID->SetSelection(UnitPointer->Building.ConstructionGraphicID + 1);
			if(GameVersion >= 3)
			{
				Units_SnowGraphicID->ChangeValue(lexical_cast<string>(UnitPointer->Building.SnowGraphicID));
				Units_SnowGraphicID->Container = &UnitPointer->Building.SnowGraphicID;
				Units_ComboBox_SnowGraphicID->SetSelection(UnitPointer->Building.SnowGraphicID + 1);
			}
			Units_AdjacentMode->ChangeValue(lexical_cast<string>(UnitPointer->Building.AdjacentMode));
			Units_AdjacentMode->Container = &UnitPointer->Building.AdjacentMode;
			Units_CheckBox_AdjacentMode->SetValue((bool)UnitPointer->Building.AdjacentMode);
			Units_Unknown31->ChangeValue(lexical_cast<string>((short)UnitPointer->Building.Unknown31));
			Units_Unknown31->Container = &UnitPointer->Building.Unknown31;
			Units_Unknown31b->ChangeValue(lexical_cast<string>((short)UnitPointer->Building.Unknown31b));
			Units_Unknown31b->Container = &UnitPointer->Building.Unknown31b;
			Units_CheckBox_Unknown31b->SetValue((bool)UnitPointer->Building.Unknown31b);
			Units_StackUnitID->ChangeValue(lexical_cast<string>(UnitPointer->Building.StackUnitID));
			Units_StackUnitID->Container = &UnitPointer->Building.StackUnitID;
			Units_ComboBox_StackUnitID->SetSelection(UnitPointer->Building.StackUnitID + 1);
			Units_TerrainID->ChangeValue(lexical_cast<string>(UnitPointer->Building.TerrainID));
			Units_TerrainID->Container = &UnitPointer->Building.TerrainID;
			Units_ComboBox_TerrainID->SetSelection(UnitPointer->Building.TerrainID + 1);
			Units_Unknown32->ChangeValue(lexical_cast<string>(UnitPointer->Building.Unknown32));
			Units_Unknown32->Container = &UnitPointer->Building.Unknown32;
			Units_ResearchID->ChangeValue(lexical_cast<string>(UnitPointer->Building.ResearchID));
			Units_ResearchID->Container = &UnitPointer->Building.ResearchID;
			Units_ComboBox_ResearchID->SetSelection(UnitPointer->Building.ResearchID + 1);
			if(GameVersion >= 2)
			{
				Units_Unknown33->ChangeValue(lexical_cast<string>((short)UnitPointer->Building.Unknown33));
				Units_Unknown33->Container = &UnitPointer->Building.Unknown33;
				for(short loop = 0;loop < 4;loop++)
				{
					Units_AnnexUnit[loop]->ChangeValue(lexical_cast<string>(UnitPointer->Building.Annexes[loop].UnitID));
					Units_AnnexUnit[loop]->Container = &UnitPointer->Building.Annexes[loop].UnitID;
					Units_ComboBox_AnnexUnit[loop]->SetSelection(UnitPointer->Building.Annexes[loop].UnitID + 1);
					Units_AnnexUnitMisplacement[loop][0]->ChangeValue(lexical_cast<string>(UnitPointer->Building.Annexes[loop].Misplacement.first));
					Units_AnnexUnitMisplacement[loop][0]->Container = &UnitPointer->Building.Annexes[loop].Misplacement.first;
					Units_AnnexUnitMisplacement[loop][1]->ChangeValue(lexical_cast<string>(UnitPointer->Building.Annexes[loop].Misplacement.second));
					Units_AnnexUnitMisplacement[loop][1]->Container = &UnitPointer->Building.Annexes[loop].Misplacement.second;
				}
				Units_HeadUnit->ChangeValue(lexical_cast<string>(UnitPointer->Building.HeadUnit));
				Units_HeadUnit->Container = &UnitPointer->Building.HeadUnit;
				Units_ComboBox_HeadUnit->SetSelection(UnitPointer->Building.HeadUnit + 1);
				Units_TransformUnit->ChangeValue(lexical_cast<string>(UnitPointer->Building.TransformUnit));
				Units_TransformUnit->Container = &UnitPointer->Building.TransformUnit;
				Units_ComboBox_TransformUnit->SetSelection(UnitPointer->Building.TransformUnit + 1);
				Units_Unknown34->ChangeValue(lexical_cast<string>(UnitPointer->Building.Unknown34));
				Units_Unknown34->Container = &UnitPointer->Building.Unknown34;
				Units_GarrisonType->ChangeValue(lexical_cast<string>((short)UnitPointer->Building.GarrisonType));
				Units_GarrisonType->Container = &UnitPointer->Building.GarrisonType;
				Units_ComboBox_GarrisonType->SetSelection(UnitPointer->Building.GarrisonType + 1);
				Units_GarrisonHealRate->ChangeValue(lexical_cast<string>(UnitPointer->Building.GarrisonHealRate));
				Units_GarrisonHealRate->Container = &UnitPointer->Building.GarrisonHealRate;
				Units_Unknown35->ChangeValue(lexical_cast<string>(UnitPointer->Building.Unknown35));
				Units_Unknown35->Container = &UnitPointer->Building.Unknown35;
				Units_Unknown36->ChangeValue(lexical_cast<string>(UnitPointer->Building.Unknown36));
				Units_Unknown36->Container = &UnitPointer->Building.Unknown36;
				for(short loop = 0;loop < 6;loop++)
				{
					Units_Unknown37[loop]->ChangeValue(lexical_cast<string>((short)UnitPointer->Building.Unknown37[loop]));
					Units_Unknown37[loop]->Container = &UnitPointer->Building.Unknown37[loop];
				}
			}
			Units_ConstructionSound->ChangeValue(lexical_cast<string>(UnitPointer->Building.ConstructionSound));
			Units_ConstructionSound->Container = &UnitPointer->Building.ConstructionSound;
			Units_ComboBox_ConstructionSound->SetSelection(UnitPointer->Building.ConstructionSound + 1);
			break;
			default:
			Units_ConstructionGraphicID->Enable(false);
			Units_ConstructionGraphicID->ChangeValue("0");
			Units_ComboBox_ConstructionGraphicID->Enable(false);
			Units_ComboBox_ConstructionGraphicID->SetSelection(0);
			Units_SnowGraphicID->Enable(false);
			Units_SnowGraphicID->ChangeValue("0");
			Units_ComboBox_SnowGraphicID->Enable(false);
			Units_ComboBox_SnowGraphicID->SetSelection(0);
			Units_AdjacentMode->Enable(false);
			Units_AdjacentMode->ChangeValue("0");
			Units_CheckBox_AdjacentMode->Enable(false);
			Units_CheckBox_AdjacentMode->SetValue(false);
			Units_Unknown31->Enable(false);
			Units_Unknown31->ChangeValue("0");
			Units_Unknown31b->Enable(false);
			Units_Unknown31b->ChangeValue("0");
			Units_CheckBox_Unknown31b->Enable(false);
			Units_CheckBox_Unknown31b->SetValue(false);
			Units_StackUnitID->Enable(false);
			Units_StackUnitID->ChangeValue("0");
			Units_ComboBox_StackUnitID->Enable(false);
			Units_ComboBox_StackUnitID->SetSelection(0);
			Units_TerrainID->Enable(false);
			Units_TerrainID->ChangeValue("0");
			Units_ComboBox_TerrainID->Enable(false);
			Units_ComboBox_TerrainID->SetSelection(0);
			Units_Unknown32->Enable(false);
			Units_Unknown32->ChangeValue("0");
			Units_ResearchID->Enable(false);
			Units_ResearchID->ChangeValue("0");
			Units_ComboBox_ResearchID->Enable(false);
			Units_ComboBox_ResearchID->SetSelection(0);
			Units_Unknown33->Enable(false);
			Units_Unknown33->ChangeValue("0");
			for(short loop = 0;loop < 4;loop++)
			{
				Units_AnnexUnit[loop]->Enable(false);
				Units_AnnexUnit[loop]->ChangeValue("0");
				Units_ComboBox_AnnexUnit[loop]->Enable(false);
				Units_ComboBox_AnnexUnit[loop]->SetSelection(0);
				for(short loop2 = 0;loop2 < 2;loop2++)
				{
					Units_AnnexUnitMisplacement[loop][loop2]->Enable(false);
					Units_AnnexUnitMisplacement[loop][loop2]->ChangeValue("0");
				}
			}
			Units_HeadUnit->Enable(false);
			Units_HeadUnit->ChangeValue("0");
			Units_ComboBox_HeadUnit->Enable(false);
			Units_ComboBox_HeadUnit->SetSelection(0);
			Units_TransformUnit->Enable(false);
			Units_TransformUnit->ChangeValue("0");
			Units_ComboBox_TransformUnit->Enable(false);
			Units_ComboBox_TransformUnit->SetSelection(0);
			Units_Unknown34->Enable(false);
			Units_Unknown34->ChangeValue("0");
			Units_ConstructionSound->Enable(false);
			Units_ConstructionSound->ChangeValue("0");
			Units_ComboBox_ConstructionSound->Enable(false);
			Units_ComboBox_ConstructionSound->SetSelection(0);
			Units_GarrisonType->Enable(false);
			Units_GarrisonType->ChangeValue("0");
			Units_ComboBox_GarrisonType->Enable(false);
			Units_ComboBox_GarrisonType->SetSelection(0);
			Units_GarrisonHealRate->Enable(false);
			Units_GarrisonHealRate->ChangeValue("0");
			Units_Unknown35->Enable(false);
			Units_Unknown35->ChangeValue("0");
			Units_Unknown36->Enable(false);
			Units_Unknown36->ChangeValue("0");
			for(short loop = 0;loop < 6;loop++)
			{
				Units_Unknown37[loop]->Enable(false);
				Units_Unknown37[loop]->ChangeValue("0");
			}
		}
		
		for(short loop = 0;loop < 3;loop++)
		{
			ResourceStorage_Type[loop]->ChangeValue(lexical_cast<string>(UnitPointer->ResourceStorages[loop].Type));
			ResourceStorage_Type[loop]->Container = &UnitPointer->ResourceStorages[loop].Type;
			ResourceStorage_Amount[loop]->ChangeValue(lexical_cast<string>(UnitPointer->ResourceStorages[loop].Amount));
			ResourceStorage_Amount[loop]->Container = &UnitPointer->ResourceStorages[loop].Amount;
			ResourceStorage_Enabled[loop]->ChangeValue(lexical_cast<string>((short)UnitPointer->ResourceStorages[loop].Enabled));
			ResourceStorage_Enabled[loop]->Container = &UnitPointer->ResourceStorages[loop].Enabled;
			ResourceStorage_ComboBox_Type[loop]->SetSelection(UnitPointer->ResourceStorages[loop].Type + 1);
		}
		
		Units_DLL_LanguageDllName->Wrap(Units_DLL_LanguageDllName->GetSize().GetWidth());
		Units_DLL_LanguageDllCreation->Wrap(Units_DLL_LanguageDllCreation->GetSize().GetWidth());
		Units_DLL_LanguageDllHelp->Wrap(Units_DLL_LanguageDllHelp->GetSize().GetWidth());
		Units_DLL_HotKey4->Wrap(Units_DLL_HotKey4->GetSize().GetWidth());
		
		Added = false;
		ListUnitDamageGraphics(UnitID, UnitCivID);
		ListUnitAttacks(UnitID, UnitCivID);
		ListUnitArmors(UnitID, UnitCivID);
		if(GameVersion >= 2)	// AoK, TC, SWGB or CC
		{	// Disabling this (unit headers) doesn't increase search speed.
			Units_UnitHeads_List->SetSelection(UnitID); // Correct selection even when units are search filtered.
			wxCommandEvent E;
			OnUnitHeadsSelect(E);
		}
		else	// AoE or RoR
		{
			Units_UnitHeads_Name->SetLabel("");
			ListUnitCommands(UnitID, UnitCivID);
		}
	//	Refresh(); // Too much lag.
	}
}

void AGE_Frame::OnUnitHeadsSelect(wxCommandEvent& Event)
{
	short Selection = Units_UnitHeads_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		gdat::UnitHeader * UnitHeadPointer = (gdat::UnitHeader*)Units_UnitHeads_List->GetClientData(Selection);
		Units_UnitHeads_Name->SetLabel(" "+lexical_cast<string>(UnitID)+" - "+GetUnitName(UnitID, 0, false));
		Units_Exists->ChangeValue(lexical_cast<string>((short)UnitHeadPointer->Exists));
		Units_Exists->Container = &UnitHeadPointer->Exists;
		ListUnitCommands(UnitID, 0);
	}
}

void AGE_Frame::OnUnitsAdd(wxCommandEvent& Event)
{
	if(GameVersion > 1)	// AoK, TC, SWGB or CC
	{
		gdat::UnitHeader Temp1;
		GenieFile->UnitHeaders.push_back(Temp1);
	}

	gdat::Unit Temp2;
	for(short loop = 0;loop < GenieFile->Civs.size();loop++)
	{
		GenieFile->Civs[loop].Units.push_back(Temp2);
		GenieFile->Civs[loop].UnitPointers.push_back(1);
		GenieFile->Civs[loop].Units[GenieFile->Civs[0].Units.size() - 1].ID1 = lexical_cast<short>(GenieFile->Civs[0].Units.size() - 1);	//	ID Fix
		GenieFile->Civs[loop].Units[GenieFile->Civs[0].Units.size() - 1].ID2 = lexical_cast<short>(GenieFile->Civs[0].Units.size() - 1);
		if(GameVersion >= 2)
		GenieFile->Civs[loop].Units[GenieFile->Civs[0].Units.size() - 1].ID3 = lexical_cast<short>(GenieFile->Civs[0].Units.size() - 1);
	}
	if(GameVersion > 1)
	{
		ListUnitHeads();
	}
	Added = true;
	ListUnits(UnitCivID);
}

void AGE_Frame::OnUnitsDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	if(GameVersion > 1)
	{
		short Selection = Units_UnitHeads_List->GetSelection();
		if(Selection != wxNOT_FOUND)	// If unit is selected.
		{
			GenieFile->UnitHeaders.erase(GenieFile->UnitHeaders.begin() + UnitID);
		}
	}

	short Selection = Units_Units_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		for(short loop = 0;loop < GenieFile->Civs.size();loop++)
		{
			GenieFile->Civs[loop].Units.erase(GenieFile->Civs[loop].Units.begin() + UnitID);
			GenieFile->Civs[loop].UnitPointers.erase(GenieFile->Civs[loop].UnitPointers.begin() + UnitID);
			for(short loop2 = UnitID;loop2 < GenieFile->Civs[0].Units.size();loop2++)	//	ID Fix
			{
				GenieFile->Civs[loop].Units[loop2].ID1 = lexical_cast<short>(loop2);
				GenieFile->Civs[loop].Units[loop2].ID2 = lexical_cast<short>(loop2);
				if(GameVersion >= 2)
				GenieFile->Civs[loop].Units[loop2].ID3 = lexical_cast<short>(loop2);
			}
		}
		if(GameVersion > 1)
		{
			ListUnitHeads();
		}
		if(Selection == Units_Units_List->GetCount() - 1)
		Units_Units_List->SetSelection(Selection - 1);
		ListUnits(UnitCivID);
	}
}

void AGE_Frame::OnUnitsCopy(wxCommandEvent& Event)
{
	if(GameVersion > 1)
	{
		short Selection = Units_UnitHeads_List->GetSelection();
		if(Selection != wxNOT_FOUND)
		{
			UnitHeaderCopy = *(gdat::UnitHeader*)Units_UnitHeads_List->GetClientData(Selection);
		}
	}

	short Selection = Units_Units_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		RefreshLists = UnitID;
		UnitCopy = GenieFile->Civs[UnitCivID].Units[UnitID];
		if(AutoCopy == MenuOption_Exclude)
		{// Let's copy graphics separately.
			UnitsGraphicsCopy(GenieFile->Civs.size());
		}
	}
}

void AGE_Frame::UnitsGraphicsCopy(short Size, short loop, short Fix)
{
	for(;loop < Size;loop++, Fix++)
	{	// Collects only graphic data, not all data again.
		UnitGraphics[Fix].IconID = GenieFile->Civs[loop].Units[UnitID].IconID;// This probably shouldn't be here.
		UnitGraphics[Fix].StandingGraphic = GenieFile->Civs[loop].Units[UnitID].StandingGraphic;
		UnitGraphics[Fix].DyingGraphic = GenieFile->Civs[loop].Units[UnitID].DyingGraphic;
		UnitGraphics[Fix].DamageGraphicCount = GenieFile->Civs[loop].Units[UnitID].DamageGraphicCount;
		UnitGraphics[Fix].DamageGraphics = GenieFile->Civs[loop].Units[UnitID].DamageGraphics;
		switch((short)GenieFile->Civs[loop].Units[UnitID].Type)
		{
			case 80:
			UnitGraphics[Fix].Building.ConstructionGraphicID = GenieFile->Civs[loop].Units[UnitID].Building.ConstructionGraphicID;
			UnitGraphics[Fix].Building.SnowGraphicID = GenieFile->Civs[loop].Units[UnitID].Building.SnowGraphicID;
			case 70:
			UnitGraphics[Fix].Creatable.GarrisonGraphic = GenieFile->Civs[loop].Units[UnitID].Creatable.GarrisonGraphic;
			case 60:
			UnitGraphics[Fix].Projectile.AttackGraphic = GenieFile->Civs[loop].Units[UnitID].Projectile.AttackGraphic;
			case 40:
			case 30:
			UnitGraphics[Fix].DeadFish.WalkingGraphic = GenieFile->Civs[loop].Units[UnitID].DeadFish.WalkingGraphic;
			break;
		}
	}
}

void AGE_Frame::OnUnitsSpecialCopy(wxCommandEvent& Event)
{
	if(Units_SpecialCopy_Civs->GetValue() == true)
	{
		UnitsGraphicsCopy(GenieFile->Civs.size());
	}
	else
	{
		UnitsGraphicsCopy(UnitCivID+1, UnitCivID, 0);
	}
}

void AGE_Frame::OnUnitsPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	if(GameVersion > 1)
	{
		short Selection = Units_UnitHeads_List->GetSelection();
		if(Selection != wxNOT_FOUND)
		{
			*(gdat::UnitHeader*)Units_UnitHeads_List->GetClientData(Selection) = UnitHeaderCopy;
		}
	}

	short Selection = Units_Units_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(AutoCopy == MenuOption_NoAuto)
		{
			GenieFile->Civs[UnitCivID].Units[UnitID] = UnitCopy;
		}
		else
		{
			for(short loop = 0;loop < GenieFile->Civs.size();loop++)
			GenieFile->Civs[loop].Units[UnitID] = UnitCopy;
			if(AutoCopy == MenuOption_Exclude)
			{// Let's paste graphics separately.
				UnitsGraphicsPaste(GenieFile->Civs.size());
			}
		}
		if(RefreshLists != UnitID)
		{
			for(short loop = 0;loop < GenieFile->Civs.size();loop++)
			{
				GenieFile->Civs[loop].Units[UnitID].ID1 = lexical_cast<short>(UnitID);	//	ID Fix
				GenieFile->Civs[loop].Units[UnitID].ID2 = lexical_cast<short>(UnitID);
				if(GameVersion >= 2)
				GenieFile->Civs[loop].Units[UnitID].ID3 = lexical_cast<short>(UnitID);
			}
			if(GameVersion > 1)
			{
				ListUnitHeads();
			}
			ListUnits(UnitCivID);
		}
	}
}

void AGE_Frame::UnitsGraphicsPaste(short Size, short loop, short Fix)
{
	for(;loop < Size;loop++, Fix++)
	{
		GenieFile->Civs[loop].Units[UnitID].IconID = UnitGraphics[Fix].IconID;
		GenieFile->Civs[loop].Units[UnitID].StandingGraphic = UnitGraphics[Fix].StandingGraphic;
		GenieFile->Civs[loop].Units[UnitID].DyingGraphic = UnitGraphics[Fix].DyingGraphic;
		GenieFile->Civs[loop].Units[UnitID].DamageGraphicCount = UnitGraphics[Fix].DamageGraphicCount;
		GenieFile->Civs[loop].Units[UnitID].DamageGraphics = UnitGraphics[Fix].DamageGraphics;
		switch((short)GenieFile->Civs[loop].Units[UnitID].Type)
		{
			case 80:
			GenieFile->Civs[loop].Units[UnitID].Building.ConstructionGraphicID = UnitGraphics[Fix].Building.ConstructionGraphicID;
			GenieFile->Civs[loop].Units[UnitID].Building.SnowGraphicID = UnitGraphics[Fix].Building.SnowGraphicID;
			case 70:
			GenieFile->Civs[loop].Units[UnitID].Creatable.GarrisonGraphic = UnitGraphics[Fix].Creatable.GarrisonGraphic;
			case 60:
			GenieFile->Civs[loop].Units[UnitID].Projectile.AttackGraphic = UnitGraphics[Fix].Projectile.AttackGraphic;
			case 40:
			case 30:
			GenieFile->Civs[loop].Units[UnitID].DeadFish.WalkingGraphic = UnitGraphics[Fix].DeadFish.WalkingGraphic;
			break;
		}
	}
}

void AGE_Frame::OnUnitsSpecialPaste(wxCommandEvent& Event)
{
	if(Units_SpecialCopy_Civs->GetValue() == true)
	{
		UnitsGraphicsPaste(GenieFile->Civs.size());
	}
	else
	{
		UnitsGraphicsPaste(UnitCivID+1, UnitCivID, 0);
	}
	wxCommandEvent E;
	OnUnitsSelect(E);
}

void AGE_Frame::OnUnitsEnable(wxCommandEvent& Event)
{
	short Selection = Units_Units_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		for(short loop = 0;loop < GenieFile->Civs.size();loop++)
		{
			GenieFile->Civs[loop].UnitPointers[UnitID] = lexical_cast<long>(1);
		}
		ListUnits(UnitCivID);
	}
}

void AGE_Frame::OnUnitsDisable(wxCommandEvent& Event)
{
	short Selection = Units_Units_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		for(short loop = 0;loop < GenieFile->Civs.size();loop++)
		{
			GenieFile->Civs[loop].UnitPointers[UnitID] = lexical_cast<long>(0);
		}
		ListUnits(UnitCivID);
	}
}

//	SubVectors

string AGE_Frame::GetUnitDamageGraphicName(short Index, short UnitCivID, short UnitID)
{
	string Name = "";
	Name += lexical_cast<string>((short)GenieFile->Civs[UnitCivID].Units[UnitID].DamageGraphics[Index].DamagePercent);
	Name += " % - ID: ";
	Name += lexical_cast<string>(GenieFile->Civs[UnitCivID].Units[UnitID].DamageGraphics[Index].GraphicID);
	return Name;
}

void AGE_Frame::OnUnitDamageGraphicsSearch(wxCommandEvent& Event)
{
	ListUnitDamageGraphics(UnitID, UnitCivID);
}

void AGE_Frame::ListUnitDamageGraphics(short Index, short UnitCivID)
{
	string Name;
	SearchText = wxString(Units_DamageGraphics_Search->GetValue()).Lower();
	ExcludeText = wxString(Units_DamageGraphics_Search_R->GetValue()).Lower();
	string CompareText;
	short Selection = Units_DamageGraphics_List->GetSelection();

	if(Units_DamageGraphics_List->GetCount() > 0)
	{
		Units_DamageGraphics_List->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	for(short loop = 0;loop < GenieFile->Civs[UnitCivID].Units[Index].DamageGraphics.size();loop++)
	{
		Name = " "+lexical_cast<string>(loop)+" - "+GetUnitDamageGraphicName(loop, UnitCivID, Index);
		CompareText = wxString(Name).Lower();
		if(SearchMatches(CompareText) == true)
		{
			Units_DamageGraphics_List->Append(Name, (void*)&GenieFile->Civs[UnitCivID].Units[Index].DamageGraphics[loop]);
		}
	}
	Units_DamageGraphics_List->SetSelection(0);
	Units_DamageGraphics_List->SetFirstItem(Selection - 3);
	Units_DamageGraphics_List->SetSelection(Selection);

	wxCommandEvent E;
	OnUnitDamageGraphicsSelect(E);
}

void AGE_Frame::OnUnitDamageGraphicsSelect(wxCommandEvent& Event)
{
	short Selection = Units_DamageGraphics_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = Units_DamageGraphics_List->GetCount() - 1;
			Units_DamageGraphics_List->SetSelection(Selection);
		}
		gdat::unit::DamageGraphic * DamageGraphicPointer = (gdat::unit::DamageGraphic*)Units_DamageGraphics_List->GetClientData(Selection);
		DamageGraphicID = DamageGraphicPointer - (&GenieFile->Civs[UnitCivID].Units[UnitID].DamageGraphics[0]);
		DamageGraphics_GraphicID->ChangeValue(lexical_cast<string>(DamageGraphicPointer->GraphicID));
		DamageGraphics_GraphicID->Container = &DamageGraphicPointer->GraphicID;
		DamageGraphics_ComboBox_GraphicID->SetSelection(DamageGraphicPointer->GraphicID + 1);
		DamageGraphics_DamagePercent->ChangeValue(lexical_cast<string>((short)DamageGraphicPointer->DamagePercent));
		DamageGraphics_DamagePercent->Container = &DamageGraphicPointer->DamagePercent;
		DamageGraphics_Unknown1->ChangeValue(lexical_cast<string>((short)DamageGraphicPointer->Unknown1));
		DamageGraphics_Unknown1->Container = &DamageGraphicPointer->Unknown1;
		DamageGraphics_Unknown2->ChangeValue(lexical_cast<string>((short)DamageGraphicPointer->Unknown2));
		DamageGraphics_Unknown2->Container = &DamageGraphicPointer->Unknown2;
		Added = false;
	}
	else
	{
		DamageGraphics_GraphicID->ChangeValue("0");
		DamageGraphics_ComboBox_GraphicID->SetSelection(0);
		DamageGraphics_DamagePercent->ChangeValue("0");
		DamageGraphics_Unknown1->ChangeValue("0");
		DamageGraphics_Unknown2->ChangeValue("0");
	}
}

void AGE_Frame::OnUnitDamageGraphicsAdd(wxCommandEvent& Event)
{
	short Selection = Units_Units_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		gdat::unit::DamageGraphic Temp;
		for(short loop = 0;loop < GenieFile->Civs.size();loop++)
		{
			GenieFile->Civs[loop].Units[UnitID].DamageGraphics.push_back(Temp);
		}
		Added = true;
		ListUnitDamageGraphics(UnitID, UnitCivID);
	}
}

void AGE_Frame::OnUnitDamageGraphicsDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Units_DamageGraphics_List->GetSelection(); // Gives the current list selection.
	if(Selection != wxNOT_FOUND)
	{
		for(short loop = 0;loop < GenieFile->Civs.size();loop++)
		{
			GenieFile->Civs[loop].Units[UnitID].DamageGraphics.erase(GenieFile->Civs[loop].Units[UnitID].DamageGraphics.begin() + DamageGraphicID);
		}
		if(Selection == Units_DamageGraphics_List->GetCount() - 1)
		Units_DamageGraphics_List->SetSelection(Selection - 1);
		ListUnitDamageGraphics(UnitID, UnitCivID);
	}
}

void AGE_Frame::OnUnitDamageGraphicsCopy(wxCommandEvent& Event)
{
	short Selection = Units_DamageGraphics_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		DamageGraphicCopy = *(gdat::unit::DamageGraphic*)Units_DamageGraphics_List->GetClientData(Selection);
	}
}

void AGE_Frame::OnUnitDamageGraphicsPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Units_DamageGraphics_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(AutoCopy == MenuOption_NoAuto)
			GenieFile->Civs[UnitCivID].Units[UnitID].DamageGraphics[DamageGraphicID] = DamageGraphicCopy;
		else for(short loop = 0;loop < GenieFile->Civs.size();loop++)
		{
			GenieFile->Civs[loop].Units[UnitID].DamageGraphics[DamageGraphicID] = DamageGraphicCopy;
		}
		ListUnitDamageGraphics(UnitID, UnitCivID);
	}
}

string AGE_Frame::GetUnitAttackName(short Index, short UnitCivID, short UnitID)
{
	string Name = "";
	Name += "Amount: ";
	Name += lexical_cast<string>(GenieFile->Civs[UnitCivID].Units[UnitID].Projectile.Attacks[Index].Amount);
	Name += " - Class ";
	Name += lexical_cast<string>(GenieFile->Civs[UnitCivID].Units[UnitID].Projectile.Attacks[Index].Class);
	return Name;
}

void AGE_Frame::OnUnitAttacksSearch(wxCommandEvent& Event)
{
	ListUnitAttacks(UnitID, UnitCivID);
}

void AGE_Frame::ListUnitAttacks(short Index, short UnitCivID)
{
	string Name;
	SearchText = wxString(Units_Attacks_Search->GetValue()).Lower();
	ExcludeText = wxString(Units_Attacks_Search_R->GetValue()).Lower();
	string CompareText;
	short Selection = Units_Attacks_List->GetSelection();

	if(Units_Attacks_List->GetCount() > 0)
	{
		Units_Attacks_List->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	if(GenieFile->Civs[UnitCivID].Units[Index].Type >= 60 && GenieFile->Civs[UnitCivID].Units[Index].Type <= 80)
	{
		Units_Attacks_Add->Enable(true);
		for(short loop = 0;loop < GenieFile->Civs[UnitCivID].Units[Index].Projectile.Attacks.size();loop++)
		{
			Name = " "+lexical_cast<string>(loop)+" - "+GetUnitAttackName(loop, UnitCivID, Index);
			CompareText = wxString(Name).Lower();
			if(SearchMatches(CompareText) == true)
			{
				Units_Attacks_List->Append(Name, (void*)&GenieFile->Civs[UnitCivID].Units[Index].Projectile.Attacks[loop]);
			}
		}
	}
	else
	{
		Units_Attacks_Add->Enable(false);
	}
	Units_Attacks_List->SetSelection(0);
	Units_Attacks_List->SetFirstItem(Selection - 3);
	Units_Attacks_List->SetSelection(Selection);

	wxCommandEvent E;
	OnUnitAttacksSelect(E);
}

void AGE_Frame::OnUnitAttacksSelect(wxCommandEvent& Event)
{
	short Selection = Units_Attacks_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = Units_Attacks_List->GetCount() - 1;
			Units_Attacks_List->SetSelection(Selection);
		}
		gdat::unit::AttackOrArmor * AttackPointer = (gdat::unit::AttackOrArmor*)Units_Attacks_List->GetClientData(Selection);
		AttackID = AttackPointer - (&GenieFile->Civs[UnitCivID].Units[UnitID].Projectile.Attacks[0]);
		Attacks_Class->ChangeValue(lexical_cast<string>(AttackPointer->Class));
		Attacks_Class->Container = &AttackPointer->Class;
		Attacks_ComboBox_Class[0]->SetSelection(0);
		Attacks_ComboBox_Class[0]->SetSelection(AttackPointer->Class + 1);
		Attacks_Amount->ChangeValue(lexical_cast<string>(AttackPointer->Amount));
		Attacks_Amount->Container = &AttackPointer->Amount;
		Added = false;
	}
	else
	{
		Attacks_Class->ChangeValue("0");
		Attacks_ComboBox_Class[0]->SetSelection(0);
		Attacks_Amount->ChangeValue("0");
	}
}

void AGE_Frame::OnUnitAttacksAdd(wxCommandEvent& Event)
{
	short Selection = Units_Units_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		gdat::unit::AttackOrArmor Temp;
		for(short loop = 0;loop < GenieFile->Civs.size();loop++)
		{
			GenieFile->Civs[loop].Units[UnitID].Projectile.Attacks.push_back(Temp);
		}
		Added = true;
		ListUnitAttacks(UnitID, UnitCivID);
	}
}

void AGE_Frame::OnUnitAttacksDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Units_Attacks_List->GetSelection(); // Gives the current list selection.
	if(Selection != wxNOT_FOUND)
	{
		for(short loop = 0;loop < GenieFile->Civs.size();loop++)
		{
			GenieFile->Civs[loop].Units[UnitID].Projectile.Attacks.erase(GenieFile->Civs[loop].Units[UnitID].Projectile.Attacks.begin() + AttackID);
		}
		if(Selection == Units_Attacks_List->GetCount() - 1)
		Units_Attacks_List->SetSelection(Selection - 1);
		ListUnitAttacks(UnitID, UnitCivID);
	}
}

void AGE_Frame::OnUnitAttacksCopy(wxCommandEvent& Event)
{
	short Selection = Units_Attacks_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		AttackCopy = *(gdat::unit::AttackOrArmor*)Units_Attacks_List->GetClientData(Selection);
	}
}

void AGE_Frame::OnUnitAttacksPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Units_Attacks_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(AutoCopy == MenuOption_NoAuto)
			GenieFile->Civs[UnitCivID].Units[UnitID].Projectile.Attacks[AttackID] = AttackCopy;
		else for(short loop = 0;loop < GenieFile->Civs.size();loop++)
		{
			GenieFile->Civs[loop].Units[UnitID].Projectile.Attacks[AttackID] = AttackCopy;
		}
		ListUnitAttacks(UnitID, UnitCivID);
	}
}

string AGE_Frame::GetUnitArmorName(short Index, short UnitCivID, short UnitID)
{
	string Name = "";
	Name += "Amount: ";
	Name += lexical_cast<string>(GenieFile->Civs[UnitCivID].Units[UnitID].Projectile.Armours[Index].Amount);
	Name += " - Class ";
	Name += lexical_cast<string>(GenieFile->Civs[UnitCivID].Units[UnitID].Projectile.Armours[Index].Class);
	return Name;
}

void AGE_Frame::OnUnitArmorsSearch(wxCommandEvent& Event)
{
	ListUnitArmors(UnitID, UnitCivID);
}

void AGE_Frame::ListUnitArmors(short Index, short UnitCivID)
{
	string Name;
	SearchText = wxString(Units_Armors_Search->GetValue()).Lower();
	ExcludeText = wxString(Units_Armors_Search_R->GetValue()).Lower();
	string CompareText;
	short Selection = Units_Armors_List->GetSelection();

	if(Units_Armors_List->GetCount() > 0)
	{
		Units_Armors_List->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	if(GenieFile->Civs[UnitCivID].Units[Index].Type >= 60 && GenieFile->Civs[UnitCivID].Units[Index].Type <= 80)
	{
		Units_Armors_Add->Enable(true);
		for(short loop = 0;loop < GenieFile->Civs[UnitCivID].Units[Index].Projectile.Armours.size();loop++)
		{
			Name = " "+lexical_cast<string>(loop)+" - "+GetUnitArmorName(loop, UnitCivID, Index);
			CompareText = wxString(Name).Lower();
			if(SearchMatches(CompareText) == true)
			{
				Units_Armors_List->Append(Name, (void*)&GenieFile->Civs[UnitCivID].Units[Index].Projectile.Armours[loop]);
			}
		}
	}
	else
	{
		Units_Armors_Add->Enable(false);
	}
	Units_Armors_List->SetSelection(0);
	Units_Armors_List->SetFirstItem(Selection - 3);
	Units_Armors_List->SetSelection(Selection);

	wxCommandEvent E;
	OnUnitArmorsSelect(E);
}

void AGE_Frame::OnUnitArmorsSelect(wxCommandEvent& Event)
{
	short Selection = Units_Armors_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = Units_Armors_List->GetCount() - 1;
			Units_Armors_List->SetSelection(Selection);
		}
		gdat::unit::AttackOrArmor * ArmorPointer = (gdat::unit::AttackOrArmor*)Units_Armors_List->GetClientData(Selection);
		ArmorID = ArmorPointer - (&GenieFile->Civs[UnitCivID].Units[UnitID].Projectile.Armours[0]);
		Armors_Class->ChangeValue(lexical_cast<string>(ArmorPointer->Class));
		Armors_Class->Container = &ArmorPointer->Class;
		Attacks_ComboBox_Class[1]->SetSelection(0);
		Attacks_ComboBox_Class[1]->SetSelection(ArmorPointer->Class + 1);
		Armors_Amount->ChangeValue(lexical_cast<string>(ArmorPointer->Amount));
		Armors_Amount->Container = &ArmorPointer->Amount;
		Added = false;
	}
	else
	{
		Armors_Class->ChangeValue("0");
		Attacks_ComboBox_Class[1]->SetSelection(0);
		Armors_Amount->ChangeValue("0");
	}
}

void AGE_Frame::OnUnitArmorsAdd(wxCommandEvent& Event)
{
	short Selection = Units_Units_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		gdat::unit::AttackOrArmor Temp;
		for(short loop = 0;loop < GenieFile->Civs.size();loop++)
		{
			GenieFile->Civs[loop].Units[UnitID].Projectile.Armours.push_back(Temp);
		}
		Added = true;
		ListUnitArmors(UnitID, UnitCivID);
	}
}

void AGE_Frame::OnUnitArmorsDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Units_Armors_List->GetSelection(); // Gives the current list selection.
	if(Selection != wxNOT_FOUND)
	{
		for(short loop = 0;loop < GenieFile->Civs.size();loop++)
		{
			GenieFile->Civs[loop].Units[UnitID].Projectile.Armours.erase(GenieFile->Civs[loop].Units[UnitID].Projectile.Armours.begin() + ArmorID);
		}
		if(Selection == Units_Armors_List->GetCount() - 1)
		Units_Armors_List->SetSelection(Selection - 1);
		ListUnitArmors(UnitID, UnitCivID);
	}
}

void AGE_Frame::OnUnitArmorsCopy(wxCommandEvent& Event)
{
	short Selection = Units_Armors_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		ArmorCopy = *(gdat::unit::AttackOrArmor*)Units_Armors_List->GetClientData(Selection);
	}
}

void AGE_Frame::OnUnitArmorsPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Units_Armors_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(AutoCopy == MenuOption_NoAuto)
			GenieFile->Civs[UnitCivID].Units[UnitID].Projectile.Armours[ArmorID] = ArmorCopy;
		else for(short loop = 0;loop < GenieFile->Civs.size();loop++)
		{
			GenieFile->Civs[loop].Units[UnitID].Projectile.Armours[ArmorID] = ArmorCopy;
		}
		ListUnitArmors(UnitID, UnitCivID);
	}
}

//	AoE/TC/SWGB/CC Unit Commands

string AGE_Frame::GetUnitCommandName(short Index, short UnitCivID, short UnitID)
{
	string Name = "";
	short CommandType = -1;
	short CommandSubType = -1;
	if(GameVersion > 1)	// AoK, TC, SWGB or CC
	{
		CommandType = GenieFile->UnitHeaders[UnitID].Commands[Index].Type;
		CommandSubType = GenieFile->UnitHeaders[UnitID].Commands[Index].SubType;
	}
	else	// AoE or RoR
	{
		CommandType = GenieFile->Civs[UnitCivID].Units[UnitID].Bird.Commands[Index].Type;
		CommandSubType = GenieFile->Civs[UnitCivID].Units[UnitID].Bird.Commands[Index].SubType;
	}
	if(CommandType == 3 && CommandSubType == -1)
	{
		Name = "Ability to Garrison";
	}
	else if(CommandType == 5 && CommandSubType == 47)
	{
		Name = "Ability to Mine Gold";
	}
	else if(CommandType == 5 && CommandSubType == 79)
	{
		Name = "Ability to Mine Stone";
	}
	else if(CommandType == 5 && CommandSubType == 190)
	{
		Name = "Ability to Fish, Forage, or Farm";
	}
	else if(CommandType == 5 && CommandSubType == -1)
	{
		Name = "Ability to Rebuild";
	}
	else if(CommandType == 6 && CommandSubType == -1)
	{
		Name = "Unknown Animal Ability";
	}
	else if(CommandType == 7 && CommandSubType == -1)
	{
		Name = "Ability to Attack";
	}
	else if(CommandType == 10 && CommandSubType == -1)
	{
		Name = "Ability to Fly";
	}
	else if(CommandType == 11 && CommandSubType == -1)
	{
		Name = "Unknown Predator Animal Ability";
	}
	else if(CommandType == 12 && CommandSubType == -1)
	{
		Name = "Ability to Unload (Boat-Like)";
	}
	else if(CommandType == 13 && CommandSubType == -1)
	{
		Name = "Ability to Auto-Attack";
	}
	else if(CommandType == 21 && CommandSubType == -1)
	{
		Name = "Unknown Farm Ability";
	}
	else if(CommandType == 101 && CommandSubType == -1)
	{
		Name = "Ability to Build";
	}
	else if(CommandType == 104 && CommandSubType == -1)
	{
		Name = "Ability to Convert";
	}
	else if(CommandType == 105 && CommandSubType == -1)
	{
		Name = "Ability to Heal";
	}
	else if(CommandType == 106 && CommandSubType == -1)
	{
		Name = "Ability to Repair";
	}
	else if(CommandType == 107 && CommandSubType == -1)
	{
		Name = "Type 107, Sub -1";
	}
	else if(CommandType == 109 && CommandSubType == -1)
	{
		Name = "Type 109, Sub -1";
	}
	else if(CommandType == 110 && CommandSubType == 189)
	{
		Name = "Ability to Chop Wood";
	}
	else if(CommandType == 110 && CommandSubType == 190)
	{
		Name = "Ability to Hunt Prey Animals";
	}
	else if(CommandType == 110 && CommandSubType == -1)
	{
		Name = "Ability to Hunt Predator Animals";
	}
	else if(CommandType == 111 && CommandSubType == -1)
	{
		Name = "Ability to Trade";
	}
	else if(CommandType == 120 && CommandSubType == -1)
	{
		Name = "Ability to Generate Wonder Victory*";
	}
	else if(CommandType == 121 && CommandSubType == -1)
	{
		Name = "Type 121, Sub -1";
	}
	else if(CommandType == 122 && CommandSubType == -1)
	{
		Name = "Ability to Mine Porex (Ore)";
	}
	else if(CommandType == 125 && CommandSubType == -1)
	{
		Name = "Ability to Unpack & Attack";
	}
	else if(CommandType == 131 && CommandSubType == -1)
	{
		Name = "Type 131, Sub -1";
	}
	else if(CommandType == 132 && CommandSubType == -1)
	{
		Name = "Ability to Pickup Unit";
	}
	else if(CommandType == 135 && CommandSubType == -1)
	{
		Name = "Type 135, Sub -1";
	}
	else if(CommandType == 136 && CommandSubType == -1)
	{
		Name = "Ability to Deposit Unit";
	}
	else
	{
		Name = "Unknown";
	}
	return Name;
}

void AGE_Frame::OnUnitCommandsSearch(wxCommandEvent& Event)
{
	ListUnitCommands(UnitID, UnitCivID);
}

void AGE_Frame::ListUnitCommands(short Index, short UnitCivID)
{
	string Name;
	SearchText = wxString(Units_UnitCommands_Search->GetValue()).Lower();
	ExcludeText = wxString(Units_UnitCommands_Search_R->GetValue()).Lower();
	string CompareText;
	short Selection = Units_UnitCommands_List->GetSelection();

	if(Units_UnitCommands_List->GetCount() > 0)
	{
		Units_UnitCommands_List->Clear();
	}
	if(Selection == wxNOT_FOUND)
	{
		Selection = 0;
	}
	if(GameVersion >= 2)	// AoK, TC, SWGB or CC
	{
		for(short loop = 0;loop < GenieFile->UnitHeaders[Index].Commands.size();loop++)
		{
			Name = " "+lexical_cast<string>(loop)+" - "+GetUnitCommandName(loop, 0, Index);
			CompareText = wxString(Name).Lower();
			if(SearchMatches(CompareText) == true)
			{
				Units_UnitCommands_List->Append(Name, (void*)&GenieFile->UnitHeaders[Index].Commands[loop]);
			}
		}
	}
	else	// AoE or RoR
	{
		if(GenieFile->Civs[UnitCivID].Units[Index].Type >= 40 && GenieFile->Civs[UnitCivID].Units[Index].Type <= 80)
		{
			Units_UnitCommands_Add->Enable(true);
			for(short loop = 0;loop < GenieFile->Civs[UnitCivID].Units[Index].Bird.Commands.size();loop++)
			{
				Name = " "+lexical_cast<string>(loop)+" - "+GetUnitCommandName(loop, UnitCivID, Index);
				CompareText = wxString(Name).Lower();
				if(SearchMatches(CompareText) == true)
				{
					Units_UnitCommands_List->Append(Name, (void*)&GenieFile->Civs[UnitCivID].Units[Index].Bird.Commands[loop]);
				}
			}
		}
		else
		{
			Units_UnitCommands_Add->Enable(false);
		}
	}
	Units_UnitCommands_List->SetSelection(0);
	Units_UnitCommands_List->SetFirstItem(Selection - 3);
	Units_UnitCommands_List->SetSelection(Selection);
	
	wxCommandEvent E;
	OnUnitCommandsSelect(E);
}

void AGE_Frame::OnUnitCommandsSelect(wxCommandEvent& Event)
{
	short Selection = Units_UnitCommands_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(Added)
		{
			Selection = Units_UnitCommands_List->GetCount() - 1;
			Units_UnitCommands_List->SetSelection(Selection);
		}
		gdat::UnitCommand * UnitCommandPointer = (gdat::UnitCommand*)Units_UnitCommands_List->GetClientData(Selection);
		if(GameVersion >= 2)
		{
			CommandID = UnitCommandPointer - (&GenieFile->UnitHeaders[UnitID].Commands[0]);
		}
		else
		{
			CommandID = UnitCommandPointer - (&GenieFile->Civs[UnitCivID].Units[UnitID].Bird.Commands[0]);
		}
		UnitCommands_One->ChangeValue(lexical_cast<string>(UnitCommandPointer->One));
		UnitCommands_One->Container = &UnitCommandPointer->One;
		UnitCommands_ID->ChangeValue(lexical_cast<string>(UnitCommandPointer->ID));
		UnitCommands_ID->Container = &UnitCommandPointer->ID;
		UnitCommands_Unknown1->ChangeValue(lexical_cast<string>((short)UnitCommandPointer->Unknown1));
		UnitCommands_Unknown1->Container = &UnitCommandPointer->Unknown1;
		UnitCommands_Type->ChangeValue(lexical_cast<string>(UnitCommandPointer->Type));
		UnitCommands_Type->Container = &UnitCommandPointer->Type;
		UnitCommands_SubType->ChangeValue(lexical_cast<string>(UnitCommandPointer->SubType));
		UnitCommands_SubType->Container = &UnitCommandPointer->SubType;
		if(UnitCommandPointer->Type == 3 && UnitCommandPointer->SubType == -1)
		{
			UnitCommands_ComboBox_Types->SetSelection(1);
		}
		else if(UnitCommandPointer->Type == 5 && UnitCommandPointer->SubType == 47)
		{
			UnitCommands_ComboBox_Types->SetSelection(2);
		}
		else if(UnitCommandPointer->Type == 5 && UnitCommandPointer->SubType == 79)
		{
			UnitCommands_ComboBox_Types->SetSelection(3);
		}
		else if(UnitCommandPointer->Type == 5 && UnitCommandPointer->SubType == 190)
		{
			UnitCommands_ComboBox_Types->SetSelection(4);
		}
		else if(UnitCommandPointer->Type == 5 && UnitCommandPointer->SubType == -1)
		{
			UnitCommands_ComboBox_Types->SetSelection(5);
		}
		else if(UnitCommandPointer->Type == 6 && UnitCommandPointer->SubType == -1)
		{
			UnitCommands_ComboBox_Types->SetSelection(6);
		}
		else if(UnitCommandPointer->Type == 7 && UnitCommandPointer->SubType == -1)
		{
			UnitCommands_ComboBox_Types->SetSelection(7);
		}
		else if(UnitCommandPointer->Type == 10 && UnitCommandPointer->SubType == -1)
		{
			UnitCommands_ComboBox_Types->SetSelection(8);
		}
		else if(UnitCommandPointer->Type == 11 && UnitCommandPointer->SubType == -1)
		{
			UnitCommands_ComboBox_Types->SetSelection(9);
		}
		else if(UnitCommandPointer->Type == 12 && UnitCommandPointer->SubType == -1)
		{
			UnitCommands_ComboBox_Types->SetSelection(10);
		}
		else if(UnitCommandPointer->Type == 13 && UnitCommandPointer->SubType == -1)
		{
			UnitCommands_ComboBox_Types->SetSelection(11);
		}
		else if(UnitCommandPointer->Type == 21 && UnitCommandPointer->SubType == -1)
		{
			UnitCommands_ComboBox_Types->SetSelection(12);
		}
		else if(UnitCommandPointer->Type == 101 && UnitCommandPointer->SubType == -1)
		{
			UnitCommands_ComboBox_Types->SetSelection(13);
		}
		else if(UnitCommandPointer->Type == 104 && UnitCommandPointer->SubType == -1)
		{
			UnitCommands_ComboBox_Types->SetSelection(14);
		}
		else if(UnitCommandPointer->Type == 105 && UnitCommandPointer->SubType == -1)
		{
			UnitCommands_ComboBox_Types->SetSelection(15);
		}
		else if(UnitCommandPointer->Type == 106 && UnitCommandPointer->SubType == -1)
		{
			UnitCommands_ComboBox_Types->SetSelection(16);
		}
		else if(UnitCommandPointer->Type == 107 && UnitCommandPointer->SubType == -1)
		{
			UnitCommands_ComboBox_Types->SetSelection(17);
		}
		else if(UnitCommandPointer->Type == 109 && UnitCommandPointer->SubType == -1)
		{
			UnitCommands_ComboBox_Types->SetSelection(18);
		}
		else if(UnitCommandPointer->Type == 110 && UnitCommandPointer->SubType == 189)
		{
			UnitCommands_ComboBox_Types->SetSelection(19);
		}
		else if(UnitCommandPointer->Type == 110 && UnitCommandPointer->SubType == 190)
		{
			UnitCommands_ComboBox_Types->SetSelection(20);
		}
		else if(UnitCommandPointer->Type == 110 && UnitCommandPointer->SubType == -1)
		{
			UnitCommands_ComboBox_Types->SetSelection(21);
		}
		else if(UnitCommandPointer->Type == 111 && UnitCommandPointer->SubType == -1)
		{
			UnitCommands_ComboBox_Types->SetSelection(22);
		}
		else if(UnitCommandPointer->Type == 120 && UnitCommandPointer->SubType == -1)
		{
			UnitCommands_ComboBox_Types->SetSelection(23);
		}
		else if(UnitCommandPointer->Type == 121 && UnitCommandPointer->SubType == -1)
		{
			UnitCommands_ComboBox_Types->SetSelection(24);
		}
		else if(UnitCommandPointer->Type == 122 && UnitCommandPointer->SubType == -1)
		{
			UnitCommands_ComboBox_Types->SetSelection(25);
		}
		else if(UnitCommandPointer->Type == 125 && UnitCommandPointer->SubType == -1)
		{
			UnitCommands_ComboBox_Types->SetSelection(26);
		}
		else if(UnitCommandPointer->Type == 131 && UnitCommandPointer->SubType == -1)
		{
			UnitCommands_ComboBox_Types->SetSelection(27);
		}
		else if(UnitCommandPointer->Type == 132 && UnitCommandPointer->SubType == -1)
		{
			UnitCommands_ComboBox_Types->SetSelection(28);
		}
		else if(UnitCommandPointer->Type == 135 && UnitCommandPointer->SubType == -1)
		{
			UnitCommands_ComboBox_Types->SetSelection(29);
		}
		else if(UnitCommandPointer->Type == 136 && UnitCommandPointer->SubType == -1)
		{
			UnitCommands_ComboBox_Types->SetSelection(30);
		}
		else
		{
			UnitCommands_ComboBox_Types->SetSelection(0);
		}
		UnitCommands_ClassID->ChangeValue(lexical_cast<string>(UnitCommandPointer->ClassID));
		UnitCommands_ClassID->Container = &UnitCommandPointer->ClassID;
		Units_ComboBox_Class[1]->SetSelection(UnitCommandPointer->ClassID + 1);
		UnitCommands_UnitID->ChangeValue(lexical_cast<string>(UnitCommandPointer->UnitID));
		UnitCommands_UnitID->Container = &UnitCommandPointer->UnitID;
		UnitCommands_ComboBox_UnitID->SetSelection(UnitCommandPointer->UnitID + 1);
		UnitCommands_Unknown2->ChangeValue(lexical_cast<string>(UnitCommandPointer->Unknown2));
		UnitCommands_Unknown2->Container = &UnitCommandPointer->Unknown2;
		UnitCommands_ResourceIn->ChangeValue(lexical_cast<string>(UnitCommandPointer->ResourceIn));
		UnitCommands_ResourceIn->Container = &UnitCommandPointer->ResourceIn;
		UnitCommands_ComboBox_ResourceIn->SetSelection(UnitCommandPointer->ResourceIn + 1);
		UnitCommands_ResourceOut->ChangeValue(lexical_cast<string>(UnitCommandPointer->ResourceOut));
		UnitCommands_ResourceOut->Container = &UnitCommandPointer->ResourceOut;
		UnitCommands_ComboBox_ResourceOut->SetSelection(UnitCommandPointer->ResourceOut + 1);
		UnitCommands_Unknown3->ChangeValue(lexical_cast<string>(UnitCommandPointer->Unknown3));
		UnitCommands_Unknown3->Container = &UnitCommandPointer->Unknown3;
		UnitCommands_Unknown4->ChangeValue(lexical_cast<string>(UnitCommandPointer->Unknown4));
		UnitCommands_Unknown4->Container = &UnitCommandPointer->Unknown4;
		UnitCommands_ExecutionRadius->ChangeValue(lexical_cast<string>(UnitCommandPointer->ExecutionRadius));
		UnitCommands_ExecutionRadius->Container = &UnitCommandPointer->ExecutionRadius;
		UnitCommands_Unknown5->ChangeValue(lexical_cast<string>(UnitCommandPointer->Unknown5));
		UnitCommands_Unknown5->Container = &UnitCommandPointer->Unknown5;
		UnitCommands_Unknown6->ChangeValue(lexical_cast<string>((short)UnitCommandPointer->Unknown6));
		UnitCommands_Unknown6->Container = &UnitCommandPointer->Unknown6;
		UnitCommands_Unknown7->ChangeValue(lexical_cast<string>(UnitCommandPointer->Unknown7));
		UnitCommands_Unknown7->Container = &UnitCommandPointer->Unknown7;
		UnitCommands_Unknown8->ChangeValue(lexical_cast<string>((short)UnitCommandPointer->Unknown8));
		UnitCommands_Unknown8->Container = &UnitCommandPointer->Unknown8;
		UnitCommands_Unknown9->ChangeValue(lexical_cast<string>((short)UnitCommandPointer->Unknown9));
		UnitCommands_Unknown9->Container = &UnitCommandPointer->Unknown9;
		UnitCommands_Unknown10->ChangeValue(lexical_cast<string>((short)UnitCommandPointer->Unknown10));
		UnitCommands_Unknown10->Container = &UnitCommandPointer->Unknown10;
		UnitCommands_Unknown11->ChangeValue(lexical_cast<string>((short)UnitCommandPointer->Unknown11));
		UnitCommands_Unknown11->Container = &UnitCommandPointer->Unknown11;
		UnitCommands_Unknown12->ChangeValue(lexical_cast<string>(UnitCommandPointer->Unknown12));
		UnitCommands_Unknown12->Container = &UnitCommandPointer->Unknown12;
		UnitCommands_Unknown13->ChangeValue(lexical_cast<string>(UnitCommandPointer->Unknown13));
		UnitCommands_Unknown13->Container = &UnitCommandPointer->Unknown13;
		UnitCommands_Unknown14->ChangeValue(lexical_cast<string>((short)UnitCommandPointer->Unknown14));
		UnitCommands_Unknown14->Container = &UnitCommandPointer->Unknown14;
		for(short loop = 0;loop < 6;loop++)
		{
			UnitCommands_Graphics[loop]->ChangeValue(lexical_cast<string>(UnitCommandPointer->Graphics[loop]));
			UnitCommands_Graphics[loop]->Container = &UnitCommandPointer->Graphics[loop];
			UnitCommands_ComboBox_Graphics[loop]->SetSelection(UnitCommandPointer->Graphics[loop] + 1);
		}
		Added = false;
	}
	else
	{
		UnitCommands_One->ChangeValue("0");
		UnitCommands_ID->ChangeValue("0");
		UnitCommands_Unknown1->ChangeValue("0");
		UnitCommands_Type->ChangeValue("0");
		UnitCommands_ComboBox_Types->SetSelection(0);
		UnitCommands_ClassID->ChangeValue("0");
		Units_ComboBox_Class[1]->SetSelection(0);
		UnitCommands_UnitID->ChangeValue("0");
		UnitCommands_ComboBox_UnitID->SetSelection(0);
		UnitCommands_Unknown2->ChangeValue("0");
		UnitCommands_ResourceIn->ChangeValue("0");
		UnitCommands_ComboBox_ResourceIn->SetSelection(0);
		UnitCommands_SubType->ChangeValue("0");
		UnitCommands_ResourceOut->ChangeValue("0");
		UnitCommands_ComboBox_ResourceOut->SetSelection(0);
		UnitCommands_Unknown3->ChangeValue("0");
		UnitCommands_Unknown4->ChangeValue("0");
		UnitCommands_ExecutionRadius->ChangeValue("0");
		UnitCommands_Unknown5->ChangeValue("0");
		UnitCommands_Unknown6->ChangeValue("0");
		UnitCommands_Unknown7->ChangeValue("0");
		UnitCommands_Unknown8->ChangeValue("0");
		UnitCommands_Unknown9->ChangeValue("0");
		UnitCommands_Unknown10->ChangeValue("0");
		UnitCommands_Unknown11->ChangeValue("0");
		UnitCommands_Unknown12->ChangeValue("0");
		UnitCommands_Unknown13->ChangeValue("0");
		UnitCommands_Unknown14->ChangeValue("0");
		for(short loop = 0;loop < 6;loop++)
		{
			UnitCommands_Graphics[loop]->ChangeValue("0");
			UnitCommands_ComboBox_Graphics[loop]->SetSelection(0);
		}
	}
}

void AGE_Frame::OnUnitCommandsAdd(wxCommandEvent& Event)
{
	gdat::UnitCommand Temp;
	short Selection = Units_Units_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(GameVersion > 1)
		{
			GenieFile->UnitHeaders[UnitID].Commands.push_back(Temp);
			GenieFile->UnitHeaders[UnitID].Commands[GenieFile->UnitHeaders[UnitID].Commands.size() - 1].ID = lexical_cast<short>(GenieFile->UnitHeaders[UnitID].Commands.size() - 1);	//	ID Fix
		}
		else
		{
			for(short loop = 0;loop < GenieFile->Civs.size();loop++)
			{
				GenieFile->Civs[loop].Units[UnitID].Bird.Commands.push_back(Temp);
				GenieFile->Civs[loop].Units[UnitID].Bird.Commands[GenieFile->Civs[0].Units[UnitID].Bird.Commands.size() - 1].ID = lexical_cast<short>(GenieFile->Civs[0].Units[UnitID].Bird.Commands.size() - 1);	//	ID Fix
			}
		}
		Added = true;
		ListUnitCommands(UnitID, UnitCivID);
	}
}

void AGE_Frame::OnUnitCommandsDelete(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Units_UnitCommands_List->GetSelection(); // Gives the current list selection.
	if(Selection != wxNOT_FOUND)
	{
		if(GameVersion > 1)
		{
			GenieFile->UnitHeaders[UnitID].Commands.erase(GenieFile->UnitHeaders[UnitID].Commands.begin() + CommandID);
			for(short loop2 = CommandID;loop2 < GenieFile->UnitHeaders[UnitID].Commands.size();loop2++)	//	ID Fix
			{
				GenieFile->UnitHeaders[UnitID].Commands[loop2].ID = lexical_cast<short>(loop2);
			}
		}
		else
		{
			for(short loop = 0;loop < GenieFile->Civs.size();loop++)
			{
				GenieFile->Civs[loop].Units[UnitID].Bird.Commands.erase(GenieFile->Civs[loop].Units[UnitID].Bird.Commands.begin() + CommandID);
				for(short loop2 = CommandID;loop2 < GenieFile->Civs[0].Units[UnitID].Bird.Commands.size();loop2++)	//	ID Fix
				{
					GenieFile->Civs[loop].Units[UnitID].Bird.Commands[loop2].ID = lexical_cast<short>(loop2);
				}
			}
		}
		if(Selection == Units_UnitCommands_List->GetCount() - 1)
		Units_UnitCommands_List->SetSelection(Selection - 1);
		ListUnitCommands(UnitID, UnitCivID);
	}
}

void AGE_Frame::OnUnitCommandsCopy(wxCommandEvent& Event)
{
	short Selection = Units_UnitCommands_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		UnitCommandCopy = *(gdat::UnitCommand*)Units_UnitCommands_List->GetClientData(Selection);
	}
}

void AGE_Frame::OnUnitCommandsPaste(wxCommandEvent& Event)
{
	wxBusyCursor WaitCursor;
	short Selection = Units_UnitCommands_List->GetSelection();
	if(Selection != wxNOT_FOUND)
	{
		if(GameVersion > 1)
		{
			*(gdat::UnitCommand*)Units_UnitCommands_List->GetClientData(Selection) = UnitCommandCopy;
			GenieFile->UnitHeaders[UnitID].Commands[CommandID].ID = lexical_cast<short>(CommandID);	//	ID Fix
		}
		else
		{
			if(AutoCopy == MenuOption_NoAuto)
				GenieFile->Civs[UnitCivID].Units[UnitID].Bird.Commands[CommandID] = UnitCommandCopy;
			for(short loop = 0;loop < GenieFile->Civs.size();loop++)
			{
				if(AutoCopy != MenuOption_NoAuto)
				GenieFile->Civs[loop].Units[UnitID].Bird.Commands[CommandID] = UnitCommandCopy;
				GenieFile->Civs[loop].Units[UnitID].Bird.Commands[CommandID].ID = lexical_cast<short>(CommandID);	//	ID Fix
			}
		}
		ListUnitCommands(UnitID, UnitCivID);
	}
}

void AGE_Frame::CreateUnitControls()
{
//	UnitControls new things

	Tab_Units = new wxPanel(TabBar_Data, wxID_ANY, wxDefaultPosition, wxSize(0, 20));
	
	Units_Main = new wxBoxSizer(wxHORIZONTAL);
	Units_ListArea = new wxBoxSizer(wxVERTICAL);
	Units_Units = new wxStaticBoxSizer(wxVERTICAL, Tab_Units, "Units");
	Units_Units_Special = new wxBoxSizer(wxHORIZONTAL);
	Units_Civs_List = new wxComboBox(Tab_Units, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	Units_Units_Search = new wxTextCtrl(Tab_Units, wxID_ANY);
	Units_Units_Search_R = new wxTextCtrl(Tab_Units, wxID_ANY);
	for(short loop = 0;loop < 2;loop++)
	{
		Units_Units_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
		Units_Units_SearchFilters[loop] = new wxOwnerDrawnComboBox(Tab_Units, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
		Units_Units_UseAnd[loop] = new wxCheckBox(Tab_Units, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20), 0, wxDefaultValidator);
	}
	Units_Units_List = new wxListBox(Tab_Units, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	Units_Units_Buttons = new wxGridSizer(4, 0, 0);
	Units_Add = new wxButton(Tab_Units, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Units_Delete = new wxButton(Tab_Units, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Units_Copy = new wxButton(Tab_Units, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Units_Paste = new wxButton(Tab_Units, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Units_Enable = new wxButton(Tab_Units, wxID_ANY, "Enable", wxDefaultPosition, wxSize(5, 20));
	Units_Disable = new wxButton(Tab_Units, wxID_ANY, "Disable", wxDefaultPosition, wxSize(5, 20));
	Units_SpecialCopy = new wxButton(Tab_Units, wxID_ANY, "S Copy", wxDefaultPosition, wxSize(5, 20));
	Units_SpecialPaste = new wxButton(Tab_Units, wxID_ANY, "S Paste", wxDefaultPosition, wxSize(5, 20));
	Units_SpecialCopy_Options = new wxOwnerDrawnComboBox(Tab_Units, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	Units_SpecialCopy_Civs = new wxCheckBox(Tab_Units, wxID_ANY, "All Civs", wxDefaultPosition, wxSize(-1, 20), 0, wxDefaultValidator);
//	Units_Undo = new wxButton(Tab_Units, wxID_ANY, "Undo", wxDefaultPosition, wxSize(50, 20));

	Units_DataArea = new wxBoxSizer(wxVERTICAL);
	Units_MainRow1 = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_TopRow = new wxStaticBoxSizer(wxHORIZONTAL, Tab_Units, "Other");
	Units_Holder_Type = new wxBoxSizer(wxHORIZONTAL);
	Units_AutoCopyState = new wxOwnerDrawnComboBox(Tab_Units, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	Units_Scroller = new wxScrolledWindow(Tab_Units, wxID_ANY, wxDefaultPosition, wxSize(0, 20), wxVSCROLL | wxTAB_TRAVERSAL);
	Units_ScrollerWindows = new wxBoxSizer(wxHORIZONTAL);
	Units_ScrollerWindowsSpace = new wxBoxSizer(wxVERTICAL);
	Units_Holder_TypeArea = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Type");
	Units_Holder_TypeArea1 = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_TypeArea2 = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_LangDLLArea = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Language DLLs");
	Units_Holder_GraphicsArea = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Graphics");
	Units_Holder_GraphicsArea1 = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_GraphicsArea2 = new wxGridSizer(4, 0, 5);
	Units_Holder_GraphicsArea3 = new wxGridSizer(4, 0, 5);
	Units_Holder_GraphicsArea4 = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_GraphicsArea5 = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_GraphicsArea6 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_GraphicsArea7 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_StatsArea = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Statistics");
	Units_Grid_StatsArea1 = new wxGridSizer(5, 5, 5);
	Units_Grid_StatsAreaGarrison = new wxGridSizer(4, 5, 5);
	Units_Grid_StatsArea2 = new wxGridSizer(4, 5, 5);
	Units_Holder_ProjectilesArea = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Projectiles");
	Units_Grid_ProjectilesArea1 = new wxGridSizer(4, 5, 5);
	Units_Grid_ProjectilesArea2 = new wxGridSizer(4, 5, 5);
	Units_Grid_ProjectilesArea3 = new wxGridSizer(4, 5, 5);
	Units_Holder_Attributes = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Attributes");
	Units_Grid_AttributesBoxes1 = new wxGridSizer(4, 5, 5);
	Units_Grid_Attributes1 = new wxGridSizer(4, 5, 5);
	Units_Holder_AttributesTerrain = new wxBoxSizer(wxHORIZONTAL);
	Units_Grid_AttributesTerrain = new wxGridSizer(4, 5, 5);
	Units_Grid_AttributesModes1 = new wxGridSizer(4, 5, 5);
	Units_Holder_AttributesDropSite = new wxBoxSizer(wxVERTICAL);
	Units_Holder_AttributesSizes = new wxBoxSizer(wxHORIZONTAL);
	Units_Grid_AttributesSelection1 = new wxGridSizer(4, 5, 5);
	Units_Holder_AttributesHotKey = new wxBoxSizer(wxVERTICAL);
	Units_Grid_AttributesTracking = new wxGridSizer(4, 5, 5);
	Units_Grid_AttributesTrain1 = new wxGridSizer(4, 5, 5);
	Units_Grid_Attributes3 = new wxGridSizer(4, 5, 5);
	Units_Holder_AttributesAnnexUnit = new wxBoxSizer(wxVERTICAL);
	Units_Holder_AttributesAnnexUnit2 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Attributes4 = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_SoundsArea = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Sounds");
	Units_Holder_SoundsArea1 = new wxBoxSizer(wxHORIZONTAL);
	Units_Grid_SoundsArea2 = new wxGridSizer(4, 5, 5);
	Units_Holder_MiscArea = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Miscellaneous");
	Units_Grid_HPBars = new wxGridSizer(4, 5, 5);
	Units_Holder_UnknownArea = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Type10plusUnknownArea = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Type 10+ Unknowns");
	Units_Holder_Type10plusUnknowns1 = new wxBoxSizer(wxHORIZONTAL);
	Units_Grid_Type10plusUnknowns = new wxGridSizer(4, 5, 5);
	Units_Holder_Type30plusUnknownArea = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Type 30+ Unknowns");
	Units_Grid_Type30plusUnknownArea = new wxGridSizer(4, 5, 5);
	Units_Holder_Type60plusUnknownArea = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Type 60+ Unknowns");
	Units_Holder_Type70plusUnknownArea = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Type 70+ Unknowns");
	Units_Grid_Type70plusUnknownArea = new wxGridSizer(4, 5, 5);
	Units_Holder_Type80plusUnknownArea = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Type 80+ Unknowns");
	Units_Grid_Type80plusUnknownArea = new wxGridSizer(4, 5, 5);
	Units_Holder_CommandsArea = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Commands");
	
//	Invisible Holder Windows
//	Type 10+

	Units_Holder_ID1 = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_LanguageDllName = new wxBoxSizer(wxVERTICAL);
	Units_Holder_LanguageDllCreation = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Class = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_StandingGraphic = new wxBoxSizer(wxVERTICAL);
	Units_Holder_DyingGraphic = new wxBoxSizer(wxVERTICAL);
	Units_Holder_DeathMode = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_HitPoints = new wxBoxSizer(wxVERTICAL);
	Units_Holder_LineOfSight = new wxBoxSizer(wxVERTICAL);
	Units_Holder_GarrisonCapacity = new wxBoxSizer(wxVERTICAL);
	Units_Holder_SizeRadius = new wxBoxSizer(wxVERTICAL);
	Units_Grid_SizeRadius = new wxGridSizer(2, 0, 0);
	Units_Holder_HPBarHeight1 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_TrainSound = new wxBoxSizer(wxVERTICAL);
	Units_Holder_TrainSound1 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_TrainSound2 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_TrainSound3 = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_DeadUnitID = new wxBoxSizer(wxVERTICAL);
	Units_Holder_PlacementMode = new wxBoxSizer(wxVERTICAL);
	Units_Holder_AirMode = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_IconID = new wxBoxSizer(wxVERTICAL);
	Units_Holder_HideInEditor = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_Unknown1 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Enabled = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_PlacementBypassTerrain = new wxBoxSizer(wxVERTICAL);
	Units_Holder_PlacementBypassTerrainGrid = new wxGridSizer(2, 0, 5);
	Units_Holder_PlacementTerrain = new wxBoxSizer(wxVERTICAL);
	Units_Holder_PlacementTerrainGrid = new wxGridSizer(2, 0, 5);
	Units_Holder_EditorRadius = new wxBoxSizer(wxVERTICAL);
	Units_Grid_EditorRadius = new wxGridSizer(2, 0, 0);
	Units_Holder_BuildingMode = new wxBoxSizer(wxVERTICAL);
	Units_Holder_VisibleInFog = new wxBoxSizer(wxVERTICAL);
	Units_Holder_TerrainRestriction = new wxBoxSizer(wxVERTICAL);
	Units_Holder_FlyMode = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_ResourceCapacity = new wxBoxSizer(wxVERTICAL);
	Units_Holder_ResourceDecay = new wxBoxSizer(wxVERTICAL);
	Units_Holder_BlastType = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown2 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_InteractionMode = new wxBoxSizer(wxVERTICAL);
	Units_Holder_MinimapMode = new wxBoxSizer(wxVERTICAL);
	Units_Holder_CommandAttribute = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown3 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown3B = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown3a = new wxBoxSizer(wxVERTICAL);
	Units_Holder_LanguageDllHelp = new wxBoxSizer(wxVERTICAL);
	Units_Grid_HotKey = new wxGridSizer(5, 0, 0);
	Units_Holder_Unknown4 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown5 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unselectable = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown6 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown7 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown8 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_SelectionMask = new wxBoxSizer(wxVERTICAL);
	Units_Holder_SelectionShapeType = new wxBoxSizer(wxVERTICAL);
	Units_Holder_SelectionShape = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Attribute = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Civ = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown9 = new wxBoxSizer(wxVERTICAL);
	Units_Grid_Unknown9 = new wxGridSizer(3, 0, 0);
	Units_Holder_SelectionEffect = new wxBoxSizer(wxVERTICAL);
	Units_Holder_EditorSelectionColour = new wxBoxSizer(wxVERTICAL);
	Units_Holder_SelectionRadius = new wxBoxSizer(wxVERTICAL);
	Units_Holder_HPBarHeight2 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_ResourceStorageHeader = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Resource Storages");
	Units_Grid_ResourceStorage = new wxGridSizer(3, 0, 5);
	for(short loop = 0;loop < 3;loop++)
	Units_Holder_ResourceStorage[loop] = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_SelectionSound = new wxBoxSizer(wxVERTICAL);
	Units_Holder_DyingSound = new wxBoxSizer(wxVERTICAL);
	Units_Holder_AttackSound = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Name = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Name2 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unitline = new wxBoxSizer(wxVERTICAL);
	Units_Holder_MinTechLevel = new wxBoxSizer(wxVERTICAL);
	Units_Holder_ID2 = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_ID3 = new wxBoxSizer(wxHORIZONTAL);

//	Type 20+

	Units_Holder_Speed = new wxBoxSizer(wxVERTICAL);

//	Type 30+

	Units_Holder_WalkingGraphic = new wxBoxSizer(wxVERTICAL);
	Units_Holder_RotationSpeed = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown11 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_TrackingUnit = new wxBoxSizer(wxVERTICAL);
	Units_Holder_TrackingUnitUsed = new wxBoxSizer(wxVERTICAL);
	Units_Holder_TrackingUnitUsedBox = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_TrackingUnitDensity = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown12 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown16 = new wxBoxSizer(wxVERTICAL);
	Units_Grid_Unknown16 = new wxGridSizer(10, 0, 0);

//	Type 40+

	Units_Holder_SheepConversion = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_SearchRadius = new wxBoxSizer(wxVERTICAL);
	Units_Holder_WorkRate = new wxBoxSizer(wxVERTICAL);
	Units_Grid_DropSite = new wxGridSizer(4, 0, 5);
	Units_Holder_VillagerMode = new wxBoxSizer(wxVERTICAL);
	Units_Holder_MoveSound = new wxBoxSizer(wxVERTICAL);
	Units_Holder_StopSound = new wxBoxSizer(wxVERTICAL);
	Units_Holder_AnimalMode = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_Exists = new wxBoxSizer(wxVERTICAL);

//	Type 60+

	Units_Holder_Unknown20 = new wxBoxSizer(wxVERTICAL);
	Units_Grid_Unknown20 = new wxGridSizer(2, 0, 0);
	Units_Holder_Unknown21 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_MaxRange = new wxBoxSizer(wxVERTICAL);
	Units_Holder_BlastRadius = new wxBoxSizer(wxVERTICAL);
	Units_Holder_ReloadTime1 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_ProjectileUnitID = new wxBoxSizer(wxVERTICAL);
	Units_Holder_AccuracyPercent = new wxBoxSizer(wxVERTICAL);
	Units_Holder_TowerMode = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_Delay = new wxBoxSizer(wxVERTICAL);
	Units_Holder_GraphicDisplacement = new wxBoxSizer(wxVERTICAL);
	Units_Grid_GraphicDisplacement = new wxGridSizer(4, 5, 5);
	Units_Holder_BlastLevel = new wxBoxSizer(wxVERTICAL);
	Units_Holder_MinRange = new wxBoxSizer(wxVERTICAL);
	Units_Holder_GarrisonRecoveryRate = new wxBoxSizer(wxVERTICAL);
	Units_Holder_AttackGraphic = new wxBoxSizer(wxVERTICAL);
	Units_Holder_DisplayedMeleeArmour = new wxBoxSizer(wxVERTICAL);
	Units_Holder_DisplayedAttack = new wxBoxSizer(wxVERTICAL);
	Units_Holder_DisplayedRange = new wxBoxSizer(wxVERTICAL);
	Units_Holder_ReloadTime2 = new wxBoxSizer(wxVERTICAL);

//	Type 60 only

	Units_Holder_StretchMode = new wxBoxSizer(wxVERTICAL);
	Units_Holder_CompensationMode = new wxBoxSizer(wxVERTICAL);
	Units_Holder_DropAnimationMode = new wxBoxSizer(wxVERTICAL);
	Units_Holder_PenetrationMode = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown24 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_ProjectileArc = new wxBoxSizer(wxVERTICAL);

//	Type 70+

	Units_Holder_CostHeader = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Costs");
	Units_Holder_CostType = new wxBoxSizer(wxHORIZONTAL);
	Units_Grid_CostType = new wxGridSizer(3, 0, 5);
	Units_Holder_CostAmount = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_CostUsed = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_TrainTime = new wxBoxSizer(wxVERTICAL);
	Units_Holder_TrainLocationID = new wxBoxSizer(wxVERTICAL);
	Units_Holder_ButtonID = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown26 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown27 = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_Unknown28 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_MissileGraphicDelay = new wxBoxSizer(wxVERTICAL);
	Units_Holder_HeroMode = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_GarrisonGraphic = new wxBoxSizer(wxVERTICAL);
	Units_Holder_AttackMissileDuplicationAmount1 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_AttackMissileDuplicationAmount2 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_AttackMissileDuplicationSpawning = new wxBoxSizer(wxVERTICAL);
	Units_Grid_AttackMissileDuplicationSpawning = new wxGridSizer(4, 5, 5);
	Units_Holder_AttackMissileDuplicationUnit = new wxBoxSizer(wxVERTICAL);
	Units_Holder_AttackMissileDuplicationGraphic = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown29 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_DisplayedPierceArmour = new wxBoxSizer(wxVERTICAL);

//	Type 80

	Units_Holder_ConstructionGraphicID = new wxBoxSizer(wxVERTICAL);
	Units_Holder_SnowGraphicID = new wxBoxSizer(wxVERTICAL);
	Units_Holder_AdjacentMode = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_Unknown31 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown31b = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown31bsub = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_StackUnitID = new wxBoxSizer(wxVERTICAL);
	Units_Holder_TerrainID = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown32 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_ResearchID = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown33 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_AnnexUnit1 = new wxBoxSizer(wxVERTICAL);
	Units_Grid_AnnexUnit = new wxGridSizer(4, 0, 5);
	Units_Holder_AnnexUnitMisplacement1 = new wxBoxSizer(wxVERTICAL);
	Units_Grid_AnnexUnitMisplacement = new wxGridSizer(4, 0, 5);
	Units_Holder_HeadUnit = new wxBoxSizer(wxVERTICAL);
	Units_Holder_TransformUnit = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown34 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_ConstructionSound = new wxBoxSizer(wxVERTICAL);
	Units_Holder_GarrisonType = new wxBoxSizer(wxVERTICAL);
//	Units_Holder_GarrisonType1 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_GarrisonHealRate = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown35 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown36 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown37 = new wxBoxSizer(wxHORIZONTAL);

//	Data Container Names
//	Type 10+

	Units_Text_Type = new wxStaticText(Tab_Units, wxID_ANY, "Type ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_ID1 = new wxStaticText(Units_Scroller, wxID_ANY, "ID 1 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_LanguageDllName = new wxStaticText(Units_Scroller, wxID_ANY, " Language Dll Name ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_LanguageDllCreation = new wxStaticText(Units_Scroller, wxID_ANY, " Language Dll Creation ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Class = new wxStaticText(Units_Scroller, wxID_ANY, "Class * ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_StandingGraphic = new wxStaticText(Units_Scroller, wxID_ANY, " Standing Graphic ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_DyingGraphic = new wxStaticText(Units_Scroller, wxID_ANY, " Dying Graphic ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_HitPoints = new wxStaticText(Units_Scroller, wxID_ANY, " Hit Points *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_LineOfSight = new wxStaticText(Units_Scroller, wxID_ANY, " Line Of Sight *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_GarrisonCapacity = new wxStaticText(Units_Scroller, wxID_ANY, " Garrison Capacity *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_SizeRadius = new wxStaticText(Units_Scroller, wxID_ANY, " Size Radius", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_HPBarHeight1 = new wxStaticText(Units_Scroller, wxID_ANY, " HP Bar Height 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_TrainSound = new wxStaticText(Units_Scroller, wxID_ANY, " Train Sound ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_DeadUnitID = new wxStaticText(Units_Scroller, wxID_ANY, " Dead Unit", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_PlacementMode = new wxStaticText(Units_Scroller, wxID_ANY, " Placement Mode", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_IconID = new wxStaticText(Units_Scroller, wxID_ANY, " Icon ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown1 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 1 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_PlacementBypassTerrain = new wxStaticText(Units_Scroller, wxID_ANY, " Placement Bypass Terrain *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_PlacementTerrain = new wxStaticText(Units_Scroller, wxID_ANY, " Placement Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_EditorRadius = new wxStaticText(Units_Scroller, wxID_ANY, " Editor Radius", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_BuildingMode = new wxStaticText(Units_Scroller, wxID_ANY, " Building Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_TerrainRestriction = new wxStaticText(Units_Scroller, wxID_ANY, " Terrain Restriction ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_ResourceCapacity = new wxStaticText(Units_Scroller, wxID_ANY, " Resource Capacity ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_ResourceDecay = new wxStaticText(Units_Scroller, wxID_ANY, " Resource Decay *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_BlastType = new wxStaticText(Units_Scroller, wxID_ANY, " Blast Type *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown2 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 2 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_InteractionMode = new wxStaticText(Units_Scroller, wxID_ANY, " Interaction Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_MinimapMode = new wxStaticText(Units_Scroller, wxID_ANY, " Minimap Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_CommandAttribute = new wxStaticText(Units_Scroller, wxID_ANY, " Command Attribute *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown3 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 3", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown3B = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 3B", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown3a = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 3a", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_LanguageDllHelp = new wxStaticText(Units_Scroller, wxID_ANY, " Language Dll Help ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_HotKey = new wxStaticText(Units_Scroller, wxID_ANY, " Hot Key", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown4 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 4 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown5 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 5 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown6 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 6 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown7 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 7 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown8 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 8 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_SelectionMask = new wxStaticText(Units_Scroller, wxID_ANY, " Selection Mask *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_SelectionShapeType = new wxStaticText(Units_Scroller, wxID_ANY, " Selection Shape Type ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_SelectionShape = new wxStaticText(Units_Scroller, wxID_ANY, " Selection Shape *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Attribute = new wxStaticText(Units_Scroller, wxID_ANY, " Unit Attribute *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Civ = new wxStaticText(Units_Scroller, wxID_ANY, " Civilization", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown9 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 9", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_SelectionEffect = new wxStaticText(Units_Scroller, wxID_ANY, " Selection Effect *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_EditorSelectionColour = new wxStaticText(Units_Scroller, wxID_ANY, " Editor Selection Color *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_SelectionRadius = new wxStaticText(Units_Scroller, wxID_ANY, " Selection Radius ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_HPBarHeight2 = new wxStaticText(Units_Scroller, wxID_ANY, " HP Bar Height 2 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	ResourceStorage_Text_Type = new wxStaticText(Units_Scroller, wxID_ANY, "Type ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	ResourceStorage_Text_Amount = new wxStaticText(Units_Scroller, wxID_ANY, "Amount ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	ResourceStorage_Text_Enabled = new wxStaticText(Units_Scroller, wxID_ANY, "Enable Mode * ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Units_Text_SelectionSound = new wxStaticText(Units_Scroller, wxID_ANY, " Selection Sound ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_DyingSound = new wxStaticText(Units_Scroller, wxID_ANY, " Dying Sound ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_AttackSound = new wxStaticText(Units_Scroller, wxID_ANY, " Attack Sound ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Name = new wxStaticText(Units_Scroller, wxID_ANY, " Name ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Name2 = new wxStaticText(Units_Scroller, wxID_ANY, " Name 2 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unitline = new wxStaticText(Units_Scroller, wxID_ANY, " Unitline", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_MinTechLevel = new wxStaticText(Units_Scroller, wxID_ANY, " Min Tech Level", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_ID2 = new wxStaticText(Units_Scroller, wxID_ANY, "ID 2 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_ID3 = new wxStaticText(Units_Scroller, wxID_ANY, "ID 3 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Type 20+

	Units_Text_Speed = new wxStaticText(Units_Scroller, wxID_ANY, " Speed ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Type 30+

	Units_Text_WalkingGraphic = new wxStaticText(Units_Scroller, wxID_ANY, " Walking Graphic ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_RotationSpeed = new wxStaticText(Units_Scroller, wxID_ANY, " Rotation Speed *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown11 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 11", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_TrackingUnit = new wxStaticText(Units_Scroller, wxID_ANY, " Tracking Unit ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_TrackingUnitUsed = new wxStaticText(Units_Scroller, wxID_ANY, " Tracking Unit Used *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_TrackingUnitDensity = new wxStaticText(Units_Scroller, wxID_ANY, " Tracking Unit Density *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown12 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 12", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown16 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 16", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Type 40+

	Units_Text_SearchRadius = new wxStaticText(Units_Scroller, wxID_ANY, " Search Radius ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_WorkRate = new wxStaticText(Units_Scroller, wxID_ANY, " Work Rate ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_DropSite = new wxStaticText(Units_Scroller, wxID_ANY, " Drop Site *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_VillagerMode = new wxStaticText(Units_Scroller, wxID_ANY, " Villager Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_MoveSound = new wxStaticText(Units_Scroller, wxID_ANY, " Move Sound ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_StopSound = new wxStaticText(Units_Scroller, wxID_ANY, " Stop Sound ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Exists = new wxStaticText(Units_Scroller, wxID_ANY, " Exists", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Type 60+

	Units_Text_Unknown20 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 20", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown21 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 21 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_MaxRange = new wxStaticText(Units_Scroller, wxID_ANY, " Max Range ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_BlastRadius = new wxStaticText(Units_Scroller, wxID_ANY, " Blast Radius ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_ReloadTime1 = new wxStaticText(Units_Scroller, wxID_ANY, " Reload Time 1 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_ProjectileUnitID = new wxStaticText(Units_Scroller, wxID_ANY, " Projectile Unit ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_AccuracyPercent = new wxStaticText(Units_Scroller, wxID_ANY, " Accuracy Percent ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Delay = new wxStaticText(Units_Scroller, wxID_ANY, " Delay *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_GraphicDisplacement = new wxStaticText(Units_Scroller, wxID_ANY, " Graphic Displacement XYZ *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_BlastLevel = new wxStaticText(Units_Scroller, wxID_ANY, " Blast Level *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_MinRange = new wxStaticText(Units_Scroller, wxID_ANY, " Min Range ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_GarrisonRecoveryRate = new wxStaticText(Units_Scroller, wxID_ANY, " Garrison Recovery Rate *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_AttackGraphic = new wxStaticText(Units_Scroller, wxID_ANY, " Attack Graphic ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_DisplayedMeleeArmour = new wxStaticText(Units_Scroller, wxID_ANY, " Displayed Melee Armour ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_DisplayedAttack = new wxStaticText(Units_Scroller, wxID_ANY, " Displayed Attack ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_DisplayedRange = new wxStaticText(Units_Scroller, wxID_ANY, " Displayed Range ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_ReloadTime2 = new wxStaticText(Units_Scroller, wxID_ANY, " Reload Time 2 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Type 60 only

	Units_Text_StretchMode = new wxStaticText(Units_Scroller, wxID_ANY, " Stretch Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_CompensationMode = new wxStaticText(Units_Scroller, wxID_ANY, " Compensation Mode ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_DropAnimationMode = new wxStaticText(Units_Scroller, wxID_ANY, " Drop Animation Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_PenetrationMode = new wxStaticText(Units_Scroller, wxID_ANY, " Penetration Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown24 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 24 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_ProjectileArc = new wxStaticText(Units_Scroller, wxID_ANY, " Projectile Arc ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Type 70+

	Units_Text_CostType = new wxStaticText(Units_Scroller, wxID_ANY, "Cost Type ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Units_Text_CostAmount = new wxStaticText(Units_Scroller, wxID_ANY, "Cost Amount ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Units_Text_CostUsed = new wxStaticText(Units_Scroller, wxID_ANY, "Cost Used ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Units_Text_TrainTime = new wxStaticText(Units_Scroller, wxID_ANY, " Train Time", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_TrainLocationID = new wxStaticText(Units_Scroller, wxID_ANY, " Train Location", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_ButtonID = new wxStaticText(Units_Scroller, wxID_ANY, " Train Button *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown26 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 26 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown27 = new wxStaticText(Units_Scroller, wxID_ANY, "Unknown 27 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown28 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 28 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_MissileGraphicDelay = new wxStaticText(Units_Scroller, wxID_ANY, " Missile Graphic Delay *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_GarrisonGraphic = new wxStaticText(Units_Scroller, wxID_ANY, " Garrison Graphic ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_AttackMissileDuplicationAmount1 = new wxStaticText(Units_Scroller, wxID_ANY, " Min Dupl. Missiles *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_AttackMissileDuplicationAmount2 = new wxStaticText(Units_Scroller, wxID_ANY, " Max Dupl. Missiles *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_AttackMissileDuplicationSpawning = new wxStaticText(Units_Scroller, wxID_ANY, " Missile Spawning Area *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_AttackMissileDuplicationUnit = new wxStaticText(Units_Scroller, wxID_ANY, " Missile Dupl. Unit *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_AttackMissileDuplicationGraphic = new wxStaticText(Units_Scroller, wxID_ANY, " Missile Dupl. Graphic", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown29 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 29 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_DisplayedPierceArmour = new wxStaticText(Units_Scroller, wxID_ANY, " Displayed Pierce Armour ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Type 80

	Units_Text_ConstructionGraphicID = new wxStaticText(Units_Scroller, wxID_ANY, " Construction Graphic ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_SnowGraphicID = new wxStaticText(Units_Scroller, wxID_ANY, " Snow Graphic ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown31 = new wxStaticText(Units_Scroller, wxID_ANY, " Icon Disabler? *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown31b = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 31B *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_StackUnitID = new wxStaticText(Units_Scroller, wxID_ANY, " Stack Unit *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_TerrainID = new wxStaticText(Units_Scroller, wxID_ANY, " Terrain *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown32 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 32 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_ResearchID = new wxStaticText(Units_Scroller, wxID_ANY, " Initiates Research", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown33 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 33 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_AnnexUnit = new wxStaticText(Units_Scroller, wxID_ANY, " Annex Units", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_AnnexUnitMisplacement = new wxStaticText(Units_Scroller, wxID_ANY, " Annex Units Misplacement", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_HeadUnit = new wxStaticText(Units_Scroller, wxID_ANY, " Head Unit *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_TransformUnit = new wxStaticText(Units_Scroller, wxID_ANY, " Transform Unit *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown34 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 34 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_ConstructionSound = new wxStaticText(Units_Scroller, wxID_ANY, " Construction Sound ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_GarrisonType = new wxStaticText(Units_Scroller, wxID_ANY, " Garrison Type ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_GarrisonHealRate = new wxStaticText(Units_Scroller, wxID_ANY, " Garrison Heal Rate *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown35 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 35 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown36 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 36 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown37 = new wxStaticText(Units_Scroller, wxID_ANY, "Unknown 37 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Data Containers
//	Type 10+

	for(short loop = 0;loop < 2;loop++)
	{
		Units_StandingGraphic[loop] = new TextCtrl_Short(Units_Scroller, "0", NULL);
		Units_ComboBox_StandingGraphic[loop] = new ComboBox_Short(Units_Scroller, Units_StandingGraphic[loop]);
		Units_DyingGraphic[loop] = new TextCtrl_Short(Units_Scroller, "0", NULL);
		Units_ComboBox_DyingGraphic[loop] = new ComboBox_Short(Units_Scroller, Units_DyingGraphic[loop]);
		Units_SizeRadius[loop] = new TextCtrl_Float(Units_Scroller, "0", NULL);
		Units_TrainSound[loop] = new TextCtrl_Short(Units_Scroller, "0", NULL);
		Units_ComboBox_TrainSound[loop] = new ComboBox_Short(Units_Scroller, Units_TrainSound[loop]);
		Units_PlacementBypassTerrain[loop] = new TextCtrl_Short(Units_Scroller, "0", NULL);
		Units_PlacementBypassTerrain[loop]->SetToolTip("Required terrain on some side");
		Units_ComboBox_PlacementBypassTerrain[loop] = new ComboBox_Short(Units_Scroller, Units_PlacementBypassTerrain[loop]);
		Units_PlacementTerrain[loop] = new TextCtrl_Short(Units_Scroller, "0", NULL);
		Units_ComboBox_PlacementTerrain[loop] = new ComboBox_Short(Units_Scroller, Units_PlacementTerrain[loop]);
		Units_EditorRadius[loop] = new TextCtrl_Float(Units_Scroller, "0", NULL);
		Units_SelectionRadius[loop] = new TextCtrl_Float(Units_Scroller, "0", NULL);
		Units_Unknown9[loop] = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	}
	for(short loop = 0;loop < 3;loop++)
	{
		ResourceStorage_Type[loop] = new TextCtrl_Short(Units_Scroller, "0", NULL);
		ResourceStorage_ComboBox_Type[loop] = new ComboBox_Short(Units_Scroller, ResourceStorage_Type[loop]);
		ResourceStorage_Amount[loop] = new TextCtrl_Float(Units_Scroller, "0", NULL);
		ResourceStorage_Enabled[loop] = new TextCtrl_Byte(Units_Scroller, "0", NULL);
		ResourceStorage_Enabled[loop]->SetToolTip("0 Decayable resource\n1 Stored after death also\n2 Resets on dying, enables instantly\n4 Resets on dying, enables on completion");
	}
	for(short loop = 0;loop < 4;loop++)
	{
		Units_HotKey[loop] = new TextCtrl_Short(Units_Scroller, "0", NULL);
	}
	Units_BlastType = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_Unknown2 = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_BlastType->SetToolTip("0 projectiles, dead units, fish, relics, trees\n0 gates, town center\n0 deer(unmoving), FLDOG\n1 things listed under \"others\" that have multiple rotations\n2 buildings, gates, walls, town centers, fish trap\n3 boar\n3 farm, TWAL\n3 fishing ship, villagers, trade carts, sheep, turkey\n3 (any unit) archers, junk, trade cogs, ships, seige, mounted, deer(regular), monk with relic\n3 monks, BDGAL, ABGAL");
	Units_Unknown2->SetToolTip("0 projectiles, dead units, fish, relics, trees\n2 gates, town center\n4 deer(unmoving), FLDOG\n0 things listed under \"others\" that have multiple rotations\n2 buildings, gates, walls, town centers, fish trap\n1 boar\n2 farm, TWAL\n3 fishing ship, villagers, trade carts, sheep, turkey\n4 (any unit) archers, junk, trade cogs, ships, seige, mounted, deer(regular), monk with relic\n5 monks, BDGAL, ABGAL");
	Units_Attribute = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_Attribute->SetToolTip("0 Default\n1, 3, 5 Allows units to garrison inside\n2 Causes the unit not to join formations\nStar Wars:\n4 Stealth unit\n8 Detector unit\n16 Mechanical unit\n32 Biological unit\n64 Self-shielding unit");
	Units_Civ = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_ComboBox_Civ = new ComboBox_Byte(Units_Scroller, Units_Civ);
	Units_Type = new TextCtrl_Byte(Tab_Units, "0", NULL);
	Units_ComboBox_Type = new wxOwnerDrawnComboBox(Tab_Units, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	Units_ID1 = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_LanguageDllName = new TextCtrl_UnShort(Units_Scroller, "0", NULL);
	Units_DLL_LanguageDllName = new wxStaticText(Units_Scroller, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), wxALIGN_CENTRE | wxST_NO_AUTORESIZE | wxALIGN_CENTRE_HORIZONTAL);
	Units_LanguageDllCreation = new TextCtrl_UnShort(Units_Scroller, "0", NULL);
	Units_DLL_LanguageDllCreation = new wxStaticText(Units_Scroller, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), wxALIGN_CENTRE | wxST_NO_AUTORESIZE | wxALIGN_CENTRE_HORIZONTAL);
	Units_Class = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_Class->SetToolTip("Determines many things and works in conjunction with other variables");
	Units_ComboBox_Class[0] = new ComboBox_Short(Units_Scroller, Units_Class);
	Units_DeathMode = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_DeathMode->SetToolTip("Reviving does not make it usable");
	Units_CheckBox_DeathMode = new CheckBox_Byte(Units_Scroller, "Death: Revives *", Units_DeathMode);
	Units_HitPoints = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_HitPoints->SetToolTip("-1 Instantly dying unit");
	Units_LineOfSight = new TextCtrl_Float(Units_Scroller, "0", NULL);
	Units_LineOfSight->SetToolTip("Maximum (effective) value is 20");
	Units_GarrisonCapacity = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_GarrisonCapacity->SetToolTip("If the unit has garrisoned units inside,\ngraphics tab \"New Speed?\" determines its new speed?");
	Units_HPBarHeight1 = new TextCtrl_Float(Units_Scroller, "0", NULL);
	Units_DeadUnitID = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_ComboBox_DeadUnitID = new ComboBox_Short(Units_Scroller, Units_DeadUnitID);
	Units_PlacementMode = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_AirMode = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_AirMode->SetToolTip("1 for no footprints");
	Units_CheckBox_AirMode = new CheckBox_Byte(Units_Scroller, "Air Mode *", Units_AirMode);
	Units_IconID = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_HideInEditor = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_CheckBox_HideInEditor = new CheckBox_Byte(Units_Scroller, "Hide In Editor", Units_HideInEditor);
	Units_Unknown1 = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_Enabled = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_Enabled->SetToolTip("0 Requires a research to be available\n1 Available without a research");
	Units_CheckBox_Enabled = new CheckBox_Short(Units_Scroller, "No Research *", Units_Enabled);
	Units_BuildingMode = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_BuildingMode->SetToolTip("0 non buildings, gates, farms, walls, towers\n2 town center, trade workshop, CLF01, port\n3 any building");
	Units_VisibleInFog = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_VisibleInFog->SetToolTip("0 Not visible\n1 Visible\n3 Inverted visibility");
	Units_Text_VisibleInFog = new wxStaticText(Units_Scroller, wxID_ANY, " Fog Visibility *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_TerrainRestriction = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_ComboBox_TerrainRestriction = new ComboBox_Short(Units_Scroller, Units_TerrainRestriction);
	Units_FlyMode = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_FlyMode->SetToolTip("Requires class 22 and air mode 1?\n0 Normal\n1 Graphics appear higher than the shadow");
	Units_CheckBox_FlyMode = new CheckBox_Byte(Units_Scroller, "Fly Mode", Units_FlyMode);
	Units_ResourceCapacity = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_ResourceDecay = new TextCtrl_Float(Units_Scroller, "0", NULL);
	Units_ResourceDecay->SetToolTip("Can alter corpses' decay time\nSet to -1 for never decaying");
	Units_InteractionMode = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_InteractionMode->SetToolTip("0 and 1 Unable to select, move or attack\n2 Can select, unable to move or attack\n3 Can select and attack, unable to move\n4 Can select, move and attack\n5+ Select and move?");
	Units_MinimapMode = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_MinimapMode->SetToolTip("0 and 6-10 No dot on minimap\n1 Square dot turning white when selected\n2 Diamond dot turning white when selected\n3 Diamond dot keeping color\n4 and 5 Larger spot, not following the unit, no blinking when attacked, everyone can see it\n");
	Units_CommandAttribute = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_CommandAttribute->SetToolTip("Class and this sets the interface for this unit\n0 Commands: Delete, Garrison, Stop | Attributes: Hit Points\n1 Animal\n2 Non-Military Building (build page 1)\n3 Villager\n4 Military Unit\n5 Trading Unit\n6 Monk\n7 Transport Ship\n8 Relic / Monk with Relic\n9 Fishing Ship\n10 Military Building (build page 2)\n11 Shield Building (build page 3)");
	Units_Unknown3 = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_Unknown3B = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_Unknown3a = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_LanguageDllHelp = new TextCtrl_UnShort(Units_Scroller, "0", NULL);
	Units_DLL_LanguageDllHelp = new wxStaticText(Units_Scroller, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), wxALIGN_CENTRE | wxST_NO_AUTORESIZE | wxALIGN_CENTRE_HORIZONTAL);
	Units_DLL_HotKey4 = new wxStaticText(Units_Scroller, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), wxALIGN_CENTRE | wxST_NO_AUTORESIZE | wxALIGN_CENTRE_HORIZONTAL);
	Units_Unknown4 = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_Unknown5 = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_Unselectable = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_CheckBox_Unselectable = new CheckBox_Byte(Units_Scroller, "Unselectable", Units_Unselectable);
	Units_Unknown6 = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_Unknown7 = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_Unknown7->SetToolTip("Setting to 5 can give a building a round outline,\neven if Selection Shape is set to 0 (square outline)\n0 farm, gate, dead bodies, town center\n2 buildings, gold mine\n3 berserk, flag x\n5 units\n10 mountain(matches selction mask)");
	Units_Unknown8 = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_SelectionMask = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_SelectionMask->SetToolTip("Any odd value except 7 - Mask displayed behind buildings\nAny even value except 6, 10 - Mask not displayed\n-1, 7 - Mask partially displayed when in the open\n6, 10 - Building, causes mask to appear on units behind it\n");
	Units_SelectionShapeType = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_SelectionShape = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_SelectionShape->SetToolTip("0 Square\n1+ Round");
	Units_SelectionEffect = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_SelectionEffect->SetToolTip("0\n1 HP Bar on, permanent darker outline in editor only\n4 HP Bar off, normal outline\n5, 8-9 HP Bar on\n2 HP Bar on, normal outline\n3 HP Bar off, selection shadow\n6-7 HP Bar off\nNote: this doesn't work with all units");
	Units_EditorSelectionColour = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_EditorSelectionColour->SetToolTip("0 most\n-16 fish trap farm\n52 dead farm, OLD-(___)\n116 flare, WHAL1, WHAL2, DOLP, Great-fish\n-123 all fish");
	Units_SelectionRadiusBox = new wxBoxSizer(wxHORIZONTAL);
	Units_HPBarHeight2 = new TextCtrl_Float(Units_Scroller, "0", NULL);
	Units_HPBarHeight2->SetToolTip("Vertical distance from ground");
	Units_SelectionSound = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_ComboBox_SelectionSound = new ComboBox_Short(Units_Scroller, Units_SelectionSound);
	Units_DyingSound = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_ComboBox_DyingSound = new ComboBox_Short(Units_Scroller, Units_DyingSound);
	Units_AttackSound = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_ComboBox_AttackSound = new ComboBox_Short(Units_Scroller, Units_AttackSound);
	Units_Name = new TextCtrl_String(Units_Scroller, "0", NULL);
	Units_Name2 = new TextCtrl_String(Units_Scroller, "0", NULL);
	Units_Unitline = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_ComboBox_Unitline = new ComboBox_Short(Units_Scroller, Units_Unitline);
	Units_MinTechLevel = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_ID2 = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_ID3 = new TextCtrl_Short(Units_Scroller, "0", NULL);

//	Type 20+

	Units_Speed = new TextCtrl_Float(Units_Scroller, "0", NULL);

//	Type 30+

	for(short loop = 0;loop < 2;loop++)
	{
		Units_WalkingGraphic[loop] = new TextCtrl_Short(Units_Scroller, "0", NULL);
		Units_ComboBox_WalkingGraphic[loop] = new ComboBox_Short(Units_Scroller, Units_WalkingGraphic[loop]);
	}
	Units_RotationSpeed = new TextCtrl_Float(Units_Scroller, "0", NULL);
	Units_RotationSpeed->SetToolTip("Makes it slower");
	Units_Unknown11 = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_TrackingUnit = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_ComboBox_TrackingUnit = new ComboBox_Short(Units_Scroller, Units_TrackingUnit);
	Units_TrackingUnitUsed = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_TrackingUnitUsed->SetToolTip("-1 unless a tracking unit value is present\n2 all projectiles with a tracking unit");
	Units_TrackingUnitDensity = new TextCtrl_Float(Units_Scroller, "0", NULL);
	Units_TrackingUnitDensity->SetToolTip("0 unless tracking unit value is present\n0.5 trade carts\n0.12 MFFFG(projectile)\n0.4 other projectiles");
	Units_Unknown12 = new TextCtrl_Float(Units_Scroller, "0", NULL);
	for(short loop = 0;loop < 17;loop++)
	Units_Unknown16[loop] = new TextCtrl_Byte(Units_Scroller, "0", NULL);

//	Type 40+

	Units_SheepConversion = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_SheepConversion->SetToolTip("No most\nYes junk, farm, deer, fish trap, wonder, STRBO, sheep, birds, boar, monument, wild horse");
	Units_CheckBox_SheepConversion = new CheckBox_Short_ZeroIsYes(Units_Scroller, "Convert Herd *", Units_SheepConversion);
	Units_SearchRadius = new TextCtrl_Float(Units_Scroller, "0", NULL);
	Units_WorkRate = new TextCtrl_Float(Units_Scroller, "0", NULL);
	for(short loop = 0;loop < 2;loop++)
	{
		Units_DropSite[loop] = new TextCtrl_Short(Units_Scroller, "0", NULL);
		Units_DropSite[loop]->SetToolTip("Giving a villager's drop site to a cart-like unit\ncan allow you to have mobile resource-gatherers,\nsimilar to those in Age of Mythology.");
		Units_ComboBox_DropSite[loop] = new ComboBox_Short(Units_Scroller, Units_DropSite[loop]);
	}
	Units_VillagerMode = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_VillagerMode->SetToolTip("Changes according to task\n1 Male\n2 Female");
	Units_MoveSound = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_ComboBox_MoveSound = new ComboBox_Short(Units_Scroller, Units_MoveSound);
	Units_StopSound = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_ComboBox_StopSound = new ComboBox_Short(Units_Scroller, Units_StopSound);
	Units_AnimalMode = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_CheckBox_AnimalMode = new CheckBox_Byte(Units_Scroller, "Animal Mode", Units_AnimalMode);
	Units_Exists = new TextCtrl_Byte(Units_Scroller, "0", NULL);

//	Type 60+

	for(short loop = 0;loop < 2;loop++)
	Units_Unknown20[loop] = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_Unknown21 = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_Unknown21->SetToolTip("-1 unit\n4 building");
	Units_MaxRange = new TextCtrl_Float(Units_Scroller, "0", NULL);
	Units_BlastRadius = new TextCtrl_Float(Units_Scroller, "0", NULL);
	Units_ReloadTime1 = new TextCtrl_Float(Units_Scroller, "0", NULL);
	Units_ProjectileUnitID = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_ComboBox_ProjectileUnitID = new ComboBox_Short(Units_Scroller, Units_ProjectileUnitID);
	Units_AccuracyPercent = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_TowerMode = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_CheckBox_TowerMode = new CheckBox_Byte(Units_Scroller, "Tower Mode", Units_TowerMode);
	Units_Delay = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_Delay->SetToolTip("Can increase time between serial shots?\n0 projectile, buildings, melee, villager\n3 chu ko nu\n4 gun\n5 archers\n6 trebuchet, mameluke\n7 bombard cannon, scorpion\n8 Charlemangne\n10 cavalry archers\n12 throwing axeman");
	for(short loop = 0;loop < 3;loop++)
	Units_GraphicDisplacement[loop] = new TextCtrl_Float(Units_Scroller, "0", NULL);
	Units_GraphicDisplacement[0]->SetToolTip("Left/Right distance");
	Units_GraphicDisplacement[1]->SetToolTip("Spawning distance from the unit");
	Units_GraphicDisplacement[2]->SetToolTip("Height");
	Units_BlastLevel = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_BlastLevel->SetToolTip("How blast radius affects units\n0 Damages resources also\n1 Damages trees also\n2 Damages nearby units\n3 Damages only targeted unit");
	Units_MinRange = new TextCtrl_Float(Units_Scroller, "0", NULL);
	Units_GarrisonRecoveryRate = new TextCtrl_Float(Units_Scroller, "0", NULL);
	Units_GarrisonRecoveryRate->SetToolTip("Healing speed factor when garrisoned into something");
	Units_AttackGraphic = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_ComboBox_AttackGraphic = new ComboBox_Short(Units_Scroller, Units_AttackGraphic);
	Units_DisplayedMeleeArmour = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_DisplayedAttack = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_DisplayedRange = new TextCtrl_Float(Units_Scroller, "0", NULL);
	Units_ReloadTime2 = new TextCtrl_Float(Units_Scroller, "0", NULL);

//	Type 60 only

	Units_StretchMode = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_StretchMode->SetToolTip("0 Default\n1 Projectile falls vertically to the bottom of the map");
	Units_CompensationMode = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_DropAnimationMode = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_DropAnimationMode->SetToolTip("0 Doesn't disappear after hitting the target\n1 Disappears");
	Units_PenetrationMode = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_PenetrationMode->SetToolTip("0 Stops the graphics\n1 Graphics pass through the target instead of stopping\nOnly affects the graphics of the projectile");
	Units_Unknown24 = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_ProjectileArc = new TextCtrl_Float(Units_Scroller, "0", NULL);

//	Type 70+

	for(short loop = 0;loop < 2;loop++)
	{
		Units_GarrisonGraphic[loop] = new TextCtrl_Short(Units_Scroller, "0", NULL);
		Units_ComboBox_GarrisonGraphic[loop] = new ComboBox_Short(Units_Scroller, Units_GarrisonGraphic[loop]);
	}
	for(short loop = 0;loop < 3;loop++)
	{
		Units_CostType[loop] = new TextCtrl_Short(Units_Scroller, "0", NULL);
		Units_ComboBox_CostType[loop] = new ComboBox_Short(Units_Scroller, Units_CostType[loop]);
		Units_CostAmount[loop] = new TextCtrl_Short(Units_Scroller, "0", NULL);
		Units_CostUsed[loop] = new TextCtrl_Short(Units_Scroller, "0", NULL);
		Units_CheckBox_CostUsed[loop] = new CheckBox_Short(Units_Scroller, "Used", Units_CostUsed[loop]);
		Units_Unknown27[loop] = new TextCtrl_Short(Units_Scroller, "0", NULL);
		Units_AttackMissileDuplicationSpawning[loop] = new TextCtrl_Float(Units_Scroller, "0", NULL);
	}
	Units_AttackMissileDuplicationSpawning[0]->SetToolTip("Spawning area's width");
	Units_AttackMissileDuplicationSpawning[1]->SetToolTip("Spawning area's length");
	Units_AttackMissileDuplicationSpawning[2]->SetToolTip("Spawning point's randomness inside the spawning area\n0 From a single spot\n1 Totally randomly inside the spawning area\n1+ Less randomly");
	Units_TrainTime = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_TrainLocationID = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_ComboBox_TrainLocationID = new ComboBox_Short(Units_Scroller, Units_TrainLocationID);
	Units_ButtonID = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_ButtonID->SetToolTip("First page (also second in TC) 1-15\nSecond page 21-35\nThird page ?-?");
	Units_Unknown26 = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_Unknown28 = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_MissileGraphicDelay = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_MissileGraphicDelay->SetToolTip("0 projectiles, buildings, dead units, boar\n1 villagers\n2 melee\n3 mounted units\n4 relic cart, relics\n5 archers\n6 monks");
	Units_HeroMode = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_CheckBox_HeroMode = new CheckBox_Byte(Units_Scroller, "Hero Mode", Units_HeroMode);
	Units_AttackMissileDuplicationAmount1 = new TextCtrl_Float(Units_Scroller, "0", NULL);
	Units_AttackMissileDuplicationAmount1->SetToolTip("Duplicated missiles when no units are garrisoned inside");
	Units_AttackMissileDuplicationAmount2 = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_AttackMissileDuplicationAmount2->SetToolTip("Maximum duplicated missiles when garrison capacity is full");
	Units_AttackMissileDuplicationUnit = new TextCtrl_Long(Units_Scroller, "0", NULL);
	Units_AttackMissileDuplicationUnit->SetToolTip("Uses its own attack values!");
	Units_ComboBox_AttackMissileDuplicationUnit = new ComboBox_Long(Units_Scroller, Units_AttackMissileDuplicationUnit);
	Units_AttackMissileDuplicationGraphic = new TextCtrl_Long(Units_Scroller, "0", NULL);
	Units_ComboBox_AttackMissileDuplicationGraphic = new ComboBox_Long(Units_Scroller, Units_AttackMissileDuplicationGraphic);
	Units_Unknown29 = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_Unknown29->SetToolTip("0 Default\n3 Unit must walk to enemy when ordered to attack it");

	Units_DisplayedPierceArmour = new TextCtrl_Short(Units_Scroller, "0", NULL);

//	Type 80

	Units_ConstructionGraphicID = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_ComboBox_ConstructionGraphicID = new ComboBox_Short(Units_Scroller, Units_ConstructionGraphicID);
	Units_SnowGraphicID = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_ComboBox_SnowGraphicID = new ComboBox_Short(Units_Scroller, Units_SnowGraphicID);
	Units_AdjacentMode = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_AdjacentMode->SetToolTip("0 Default\n1 Adjacent buildings can change this unit's graphics");
	Units_CheckBox_AdjacentMode = new CheckBox_Short(Units_Scroller, "Adjacent Mode *", Units_AdjacentMode);
	Units_Unknown31 = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_Unknown31->SetToolTip("0 Default\n1+ Black icon");
	Units_Unknown31b = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_Unknown31b->SetToolTip("If a building is walkable underneath it?\n0 Default\n1 Makes the building disappear? some gates, town centers, docks\nSW: also some shield generators, power cores");
	Units_CheckBox_Unknown31b = new CheckBox_Byte(Units_Scroller, "Yes *", Units_Unknown31b);
	Units_StackUnitID = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_StackUnitID->SetToolTip("Second building to be placed directly on top of this building\nAdditional building gets added every time you load the scenario");
	Units_ComboBox_StackUnitID = new ComboBox_Short(Units_Scroller, Units_StackUnitID);
	Units_TerrainID = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_TerrainID->SetToolTip("Terrain produced under a building when completed");
	Units_ComboBox_TerrainID = new ComboBox_Short(Units_Scroller, Units_TerrainID);
	Units_Unknown32 = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_ResearchID = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_ComboBox_ResearchID = new ComboBox_Short(Units_Scroller, Units_ResearchID);
	Units_Unknown33 = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	for(short loop = 0;loop < 4;loop++)
	{
		Units_AnnexUnit[loop] = new TextCtrl_Short(Units_Scroller, "0", NULL);
		Units_ComboBox_AnnexUnit[loop] = new ComboBox_Short(Units_Scroller, Units_AnnexUnit[loop]);
	}
	for(short loop = 0;loop < 4;loop++)
	{
		for(short loop2 = 0;loop2 < 2;loop2++)
		Units_AnnexUnitMisplacement[loop][loop2] = new TextCtrl_Float(Units_Scroller, "0", NULL);
	}
	Units_HeadUnit = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_HeadUnit->SetToolTip("The building that an annex building is attached to");
	Units_ComboBox_HeadUnit = new ComboBox_Short(Units_Scroller, Units_HeadUnit);
	Units_TransformUnit = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_TransformUnit->SetToolTip("Determines what the unit changes into when given the order to unpack");
	Units_ComboBox_TransformUnit = new ComboBox_Short(Units_Scroller, Units_TransformUnit);
	Units_Unknown34 = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_ConstructionSound = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_ComboBox_ConstructionSound = new ComboBox_Short(Units_Scroller, Units_ConstructionSound);
	Units_GarrisonType = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_ComboBox_GarrisonType = new ComboBox_Byte(Units_Scroller, Units_GarrisonType);
	Units_GarrisonHealRate = new TextCtrl_Float(Units_Scroller, "0", NULL);
	Units_GarrisonHealRate->SetToolTip("Building's garrisoned units' healing speed factor");
	Units_Unknown35 = new TextCtrl_Long(Units_Scroller, "0", NULL);
	Units_Unknown36 = new TextCtrl_Short(Units_Scroller, "0", NULL);
	for(short loop = 0;loop < 6;loop++)
	Units_Unknown37[loop] = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	
	Units_Holder_DamageGraphics = new wxGridSizer(4, 5, 5);
	Units_Holder_DamageGraphics_Data = new wxBoxSizer(wxVERTICAL);
	DamageGraphics_Holder_GraphicID = new wxBoxSizer(wxVERTICAL);
	DamageGraphics_Holder_DamagePercent = new wxBoxSizer(wxVERTICAL);
	DamageGraphics_Holder_Unknown1 = new wxBoxSizer(wxVERTICAL);
	DamageGraphics_Holder_Unknown2 = new wxBoxSizer(wxVERTICAL);
	DamageGraphics_Text_GraphicID = new wxStaticText(Units_Scroller, wxID_ANY, " Graphic ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	DamageGraphics_Text_DamagePercent = new wxStaticText(Units_Scroller, wxID_ANY, " Damage Percent ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	DamageGraphics_Text_Unknown1 = new wxStaticText(Units_Scroller, wxID_ANY, " Apply Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	DamageGraphics_Text_Unknown2 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 2 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	DamageGraphics_GraphicID = new TextCtrl_Short(Units_Scroller, "0", NULL);
	DamageGraphics_ComboBox_GraphicID = new ComboBox_Short(Units_Scroller, DamageGraphics_GraphicID);
	DamageGraphics_DamagePercent = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	DamageGraphics_Unknown1 = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	DamageGraphics_Unknown1->SetToolTip("0 Adds graphics on top (flames on buildings)\n2 Replaces original graphics (damaged walls)");
	DamageGraphics_Unknown2 = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	Units_DamageGraphics = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Damage Graphics");
	Units_DamageGraphics_Search = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_DamageGraphics_Search_R = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_DamageGraphics_List = new wxListBox(Units_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	Units_DamageGraphics_Buttons = new wxGridSizer(2, 0, 0);
	Units_DamageGraphics_Add = new wxButton(Units_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Units_DamageGraphics_Delete = new wxButton(Units_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Units_DamageGraphics_Copy = new wxButton(Units_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Units_DamageGraphics_Paste = new wxButton(Units_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	
	Units_Holder_Attacks = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_Attacks_Data = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Attacks_Data1 = new wxBoxSizer(wxHORIZONTAL);
	Units_Grid_Attacks_Data2 = new wxGridSizer(3, 5, 5);
	Attacks_Holder_Class = new wxBoxSizer(wxVERTICAL);
	Attacks_Holder_Class1 = new wxBoxSizer(wxHORIZONTAL);
	Attacks_Holder_Amount = new wxBoxSizer(wxVERTICAL);
	Attacks_Text_Class = new wxStaticText(Units_Scroller, wxID_ANY, " Class *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Attacks_Text_Amount = new wxStaticText(Units_Scroller, wxID_ANY, " Amount", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Attacks_Class = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Attacks_Class->SetToolTip("Armor class that this unit can damage\nYou can make your own classes");
	Attacks_ComboBox_Class[0] = new ComboBox_Short(Units_Scroller, Attacks_Class);
	Attacks_Amount = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_Attacks = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Attacks");
	Units_Attacks_Search = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_Attacks_Search_R = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_Attacks_List = new wxListBox(Units_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	Units_Attacks_Buttons = new wxGridSizer(2, 0, 0);
	Units_Attacks_Add = new wxButton(Units_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Units_Attacks_Delete = new wxButton(Units_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Units_Attacks_Copy = new wxButton(Units_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Units_Attacks_Paste = new wxButton(Units_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));	
	
	Units_Holder_Armors = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_Armors_Data = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Armors_Data1 = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_Armors_Data2 = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_Armors_Data3 = new wxBoxSizer(wxVERTICAL);
	Armors_Holder_Class = new wxBoxSizer(wxVERTICAL);
	Armors_Holder_Class1 = new wxBoxSizer(wxHORIZONTAL);
	Armors_Holder_Amount = new wxBoxSizer(wxVERTICAL);
	Armors_Text_Class = new wxStaticText(Units_Scroller, wxID_ANY, " Class *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Armors_Text_Amount = new wxStaticText(Units_Scroller, wxID_ANY, " Amount", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Armors_Class = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Armors_Class->SetToolTip("Attack class from which this unit can take damage\nYou can make your own classes");
	Attacks_ComboBox_Class[1] = new ComboBox_Short(Units_Scroller, Armors_Class);
	Armors_Amount = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_Armors = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Armors");
	Units_Armors_Search = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_Armors_Search_R = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_Armors_List = new wxListBox(Units_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	Units_Armors_Buttons = new wxGridSizer(2, 0, 0);
	Units_Armors_Add = new wxButton(Units_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Units_Armors_Delete = new wxButton(Units_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Units_Armors_Copy = new wxButton(Units_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Units_Armors_Paste = new wxButton(Units_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));

	Units_CommandHolder_Lists = new wxBoxSizer(wxVERTICAL);
	Units_UnitHeads = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "");
	Units_UnitHeads_Name = new wxStaticText(Units_Scroller, wxID_ANY, "Unit Header", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_UnitHeads_List = new wxListBox(Units_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100));
	Units_UnitCommands = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Commands");
	Units_UnitCommands_Search = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_UnitCommands_Search_R = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_UnitCommands_List = new wxListBox(Units_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 190));
	Units_UnitCommands_Buttons = new wxGridSizer(2, 0, 0);
	Units_UnitCommands_Add = new wxButton(Units_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Units_UnitCommands_Delete = new wxButton(Units_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Units_UnitCommands_Copy = new wxButton(Units_Scroller, wxID_ANY, "Copy", wxDefaultPosition, wxSize(5, 20));
	Units_UnitCommands_Paste = new wxButton(Units_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Units_CommandHolder_Data = new wxBoxSizer(wxHORIZONTAL);
	Units_CommandHolder_Data1 = new wxBoxSizer(wxVERTICAL);
	Units_CommandHolder_Data2 = new wxBoxSizer(wxVERTICAL);

	UnitCommands_Holder_One = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_Holder_ID = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_Holder_1 = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_Holder_Unknown1 = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_Holder_Type = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Holder_SubType = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Holder_Types = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_Holder_2 = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_Holder_Resources = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_Holder_ClassID = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Holder_UnitID = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Holder_Unknown2 = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_Holder_ResourceIn = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Holder_ResourceOut = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Holder_Unknown3 = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_Holder_Unknown4 = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_Holder_ExecutionRadius = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_Holder_Unknown5 = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_Holder_Unknown6 = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_Holder_Unknown7 = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_Holder_Unknown8 = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_Holder_Unknown9 = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_Holder_Unknown10 = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_Holder_Unknown11 = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_Holder_Unknown12 = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_Holder_Unknown13 = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_Holder_Unknown14 = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_Holder_Graphics = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Holder_GraphicsGrid = new wxGridSizer(2, 2, 2);
	
	UnitCommands_Text_One = new wxStaticText(Units_Scroller, wxID_ANY, "One ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	UnitCommands_Text_ID = new wxStaticText(Units_Scroller, wxID_ANY, "ID ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	UnitCommands_Text_Unknown1 = new wxStaticText(Units_Scroller, wxID_ANY, "Unknown 1 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	UnitCommands_Text_Type = new wxStaticText(Units_Scroller, wxID_ANY, " Type", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Text_ClassID = new wxStaticText(Units_Scroller, wxID_ANY, " Class", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Text_UnitID = new wxStaticText(Units_Scroller, wxID_ANY, " Unit", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Text_Unknown2 = new wxStaticText(Units_Scroller, wxID_ANY, "Unknown 2 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	UnitCommands_Text_ResourceIn = new wxStaticText(Units_Scroller, wxID_ANY, " Resource In", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Text_SubType = new wxStaticText(Units_Scroller, wxID_ANY, " Sub Type", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Text_ResourceOut = new wxStaticText(Units_Scroller, wxID_ANY, " Resource Out", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Text_Unknown3 = new wxStaticText(Units_Scroller, wxID_ANY, "Unknown 3 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	UnitCommands_Text_Unknown4 = new wxStaticText(Units_Scroller, wxID_ANY, "Unknown 4 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	UnitCommands_Text_ExecutionRadius = new wxStaticText(Units_Scroller, wxID_ANY, "Execution Radius ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Text_Unknown5 = new wxStaticText(Units_Scroller, wxID_ANY, "Unknown 5 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	UnitCommands_Text_Unknown6 = new wxStaticText(Units_Scroller, wxID_ANY, "Unknown 6 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	UnitCommands_Text_Unknown7 = new wxStaticText(Units_Scroller, wxID_ANY, "Unknown 7 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	UnitCommands_Text_Unknown8 = new wxStaticText(Units_Scroller, wxID_ANY, "Unknown 8 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	UnitCommands_Text_Unknown9 = new wxStaticText(Units_Scroller, wxID_ANY, "Unknown 9 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	UnitCommands_Text_Unknown10 = new wxStaticText(Units_Scroller, wxID_ANY, "Unknown 10 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	UnitCommands_Text_Unknown11 = new wxStaticText(Units_Scroller, wxID_ANY, "Unknown 11 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	UnitCommands_Text_Unknown12 = new wxStaticText(Units_Scroller, wxID_ANY, "Unknown 12 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	UnitCommands_Text_Unknown13 = new wxStaticText(Units_Scroller, wxID_ANY, "Unknown 13 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	UnitCommands_Text_Unknown14 = new wxStaticText(Units_Scroller, wxID_ANY, "Unknown 14 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	UnitCommands_Text_Graphics = new wxStaticText(Units_Scroller, wxID_ANY, " Graphics", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

	UnitCommands_One = new TextCtrl_Short(Units_Scroller, "0", NULL);
	UnitCommands_ID = new TextCtrl_Short(Units_Scroller, "0", NULL);
	UnitCommands_Unknown1 = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	UnitCommands_Type = new TextCtrl_Short(Units_Scroller, "0", NULL);
	UnitCommands_ComboBox_Types = new wxOwnerDrawnComboBox(Units_Scroller, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	UnitCommands_ClassID = new TextCtrl_Short(Units_Scroller, "0", NULL);
	Units_ComboBox_Class[1] = new ComboBox_Short(Units_Scroller, UnitCommands_ClassID);
	UnitCommands_UnitID = new TextCtrl_Short(Units_Scroller, "0", NULL);
	UnitCommands_ComboBox_UnitID = new ComboBox_Short(Units_Scroller, UnitCommands_UnitID);
	UnitCommands_Unknown2 = new TextCtrl_Short(Units_Scroller, "0", NULL);
	UnitCommands_ResourceIn = new TextCtrl_Short(Units_Scroller, "0", NULL);
	UnitCommands_ComboBox_ResourceIn = new ComboBox_Short(Units_Scroller, UnitCommands_ResourceIn);
	UnitCommands_SubType = new TextCtrl_Short(Units_Scroller, "0", NULL);
	UnitCommands_ResourceOut = new TextCtrl_Short(Units_Scroller, "0", NULL);
	UnitCommands_ComboBox_ResourceOut = new ComboBox_Short(Units_Scroller, UnitCommands_ResourceOut);
	UnitCommands_Unknown3 = new TextCtrl_Short(Units_Scroller, "0", NULL);
	UnitCommands_Unknown4 = new TextCtrl_Float(Units_Scroller, "0", NULL);
	UnitCommands_ExecutionRadius = new TextCtrl_Float(Units_Scroller, "0", NULL);
	UnitCommands_Unknown5 = new TextCtrl_Float(Units_Scroller, "0", NULL);
	UnitCommands_Unknown6 = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	UnitCommands_Unknown7 = new TextCtrl_Float(Units_Scroller, "0", NULL);
	UnitCommands_Unknown8 = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	UnitCommands_Unknown9 = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	UnitCommands_Unknown10 = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	UnitCommands_Unknown11 = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	UnitCommands_Unknown12 = new TextCtrl_Short(Units_Scroller, "0", NULL);
	UnitCommands_Unknown13 = new TextCtrl_Short(Units_Scroller, "0", NULL);
	UnitCommands_Unknown14 = new TextCtrl_Byte(Units_Scroller, "0", NULL);
	for(short loop = 0;loop < 6;loop++)
	{
		UnitCommands_Graphics[loop] = new TextCtrl_Short(Units_Scroller, "0", NULL);
		UnitCommands_ComboBox_Graphics[loop] = new ComboBox_Short(Units_Scroller, UnitCommands_Graphics[loop]);
	}

//	UnitControls actual interface

	Units_ComboBox_Type->Append("No Type/Invalid Type");
	Units_ComboBox_Type->Append("10 - Eye Candy");
	Units_ComboBox_Type->Append("20 - Flag");
	Units_ComboBox_Type->Append("25 - Doppleganger");
	Units_ComboBox_Type->Append("30 - Dead Unit/Fish Unit");
	Units_ComboBox_Type->Append("40 - Bird");
	Units_ComboBox_Type->Append("60 - Projectile");
	Units_ComboBox_Type->Append("70 - Living Unit");
	Units_ComboBox_Type->Append("80 - Building");
	Units_ComboBox_Type->Append("90 - Tree");
	Units_ComboBox_Type->SetSelection(0);
	
	Units_SpecialCopy_Options->Append("Special: Graphics Only");
	Units_SpecialCopy_Options->SetSelection(0);
	
	Units_AutoCopyState->Append("Auto-copy: Disabled");
	Units_AutoCopyState->Append("Auto-copy: Include graphics");
	Units_AutoCopyState->Append("Auto-copy: Exclude graphics");
	
	Units_Units_Buttons->Add(Units_Add, 1, wxEXPAND);
	Units_Units_Buttons->Add(Units_Delete, 1, wxEXPAND);
	Units_Units_Buttons->Add(Units_Copy, 1, wxEXPAND);
	Units_Units_Buttons->Add(Units_Paste, 1, wxEXPAND);
	Units_Units_Buttons->Add(Units_Enable, 1, wxEXPAND);
	Units_Units_Buttons->Add(Units_Disable, 1, wxEXPAND);
	Units_Units_Buttons->Add(Units_SpecialCopy, 1, wxEXPAND);
	Units_Units_Buttons->Add(Units_SpecialPaste, 1, wxEXPAND);
	Units_Units_Special->Add(Units_SpecialCopy_Options, 1, wxEXPAND);
	Units_Units_Special->Add(2, -1);
	Units_Units_Special->Add(Units_SpecialCopy_Civs, 0, wxEXPAND);

	Units_Units_Searches[0]->Add(Units_Units_Search, 1, wxEXPAND);
	Units_Units_Searches[0]->Add(2, -1);
	Units_Units_Searches[0]->Add(Units_Units_UseAnd[0], 0, wxEXPAND);
	Units_Units_Searches[1]->Add(Units_Units_Search_R, 1, wxEXPAND);
	Units_Units_Searches[1]->Add(2, -1);
	Units_Units_Searches[1]->Add(Units_Units_UseAnd[1], 0, wxEXPAND);
	
	Units_Units->Add(Units_Civs_List, 0, wxEXPAND);
	Units_Units->Add(-1, 2);
	for(short loop = 0;loop < 2;loop++)
	Units_Units->Add(Units_Units_Searches[loop], 0, wxEXPAND);
	for(short loop = 0;loop < 2;loop++)
	Units_Units->Add(Units_Units_SearchFilters[loop], 0, wxEXPAND);
	Units_Units->Add(-1, 2);
	Units_Units->Add(Units_Units_List, 1, wxEXPAND);
	Units_Units->Add(-1, 2);
	Units_Units->Add(Units_Units_Buttons, 0, wxEXPAND);
	Units_Units->Add(-1, 2);
	Units_Units->Add(Units_Units_Special, 0, wxEXPAND);
	
	Units_ListArea->Add(-1, 10);
	Units_ListArea->Add(Units_Units, 1, wxEXPAND);
	Units_ListArea->Add(-1, 10);
	
	Units_Holder_Type->Add(Units_Text_Type, 0, wxEXPAND);
	Units_Holder_Type->Add(Units_Type, 1, wxEXPAND);
	Units_Holder_Type->Add(Units_ComboBox_Type, 2, wxEXPAND);

//	Type 10+

	Units_Holder_ID1->Add(Units_Text_ID1, 0, wxEXPAND);
	Units_Holder_LanguageDllName->Add(Units_Text_LanguageDllName, 0, wxEXPAND);
	Units_Holder_LanguageDllCreation->Add(Units_Text_LanguageDllCreation, 0, wxEXPAND);
	Units_Holder_Class->Add(Units_Text_Class, 0, wxEXPAND);
	Units_Holder_HitPoints->Add(Units_Text_HitPoints, 0, wxEXPAND);
	Units_Holder_LineOfSight->Add(Units_Text_LineOfSight, 0, wxEXPAND);
	Units_Holder_GarrisonCapacity->Add(Units_Text_GarrisonCapacity, 0, wxEXPAND);
	Units_Holder_SizeRadius->Add(Units_Text_SizeRadius, 0, wxEXPAND);
	Units_Holder_HPBarHeight1->Add(Units_Text_HPBarHeight1, 0, wxEXPAND);
	Units_Holder_DeadUnitID->Add(Units_Text_DeadUnitID, 0, wxEXPAND);
	Units_Holder_PlacementMode->Add(Units_Text_PlacementMode, 0, wxEXPAND);
	Units_Holder_IconID->Add(Units_Text_IconID, 0, wxEXPAND);
	Units_Holder_Unknown1->Add(Units_Text_Unknown1, 0, wxEXPAND);
	Units_Holder_PlacementBypassTerrain->Add(Units_Text_PlacementBypassTerrain, 0, wxEXPAND);
	Units_Holder_PlacementTerrain->Add(Units_Text_PlacementTerrain, 0, wxEXPAND);
	Units_Holder_EditorRadius->Add(Units_Text_EditorRadius, 0, wxEXPAND);
	Units_Holder_BuildingMode->Add(Units_Text_BuildingMode, 0, wxEXPAND);
	Units_Holder_TerrainRestriction->Add(Units_Text_TerrainRestriction, 0, wxEXPAND);
	Units_Holder_ResourceCapacity->Add(Units_Text_ResourceCapacity, 0, wxEXPAND);
	Units_Holder_ResourceDecay->Add(Units_Text_ResourceDecay, 0, wxEXPAND);
	Units_Holder_BlastType->Add(Units_Text_BlastType, 0, wxEXPAND);
	Units_Holder_Unknown2->Add(Units_Text_Unknown2, 0, wxEXPAND);
	Units_Holder_InteractionMode->Add(Units_Text_InteractionMode, 0, wxEXPAND);
	Units_Holder_MinimapMode->Add(Units_Text_MinimapMode, 0, wxEXPAND);
	Units_Holder_CommandAttribute->Add(Units_Text_CommandAttribute, 0, wxEXPAND);
	Units_Holder_Unknown3->Add(Units_Text_Unknown3, 0, wxEXPAND);
	Units_Holder_Unknown3B->Add(Units_Text_Unknown3B, 0, wxEXPAND);
	Units_Holder_Unknown3a->Add(Units_Text_Unknown3a, 0, wxEXPAND);
	Units_Holder_LanguageDllHelp->Add(Units_Text_LanguageDllHelp, 0, wxEXPAND);
	Units_Holder_AttributesHotKey->Add(Units_Text_HotKey, 0, wxEXPAND);
	Units_Holder_Unknown4->Add(Units_Text_Unknown4, 0, wxEXPAND);
	Units_Holder_Unknown5->Add(Units_Text_Unknown5, 0, wxEXPAND);
	Units_Holder_Unknown6->Add(Units_Text_Unknown6, 0, wxEXPAND);
	Units_Holder_Unknown7->Add(Units_Text_Unknown7, 0, wxEXPAND);
	Units_Holder_Unknown8->Add(Units_Text_Unknown8, 0, wxEXPAND);
	Units_Holder_SelectionMask->Add(Units_Text_SelectionMask, 0, wxEXPAND);
	Units_Holder_SelectionShapeType->Add(Units_Text_SelectionShapeType, 0, wxEXPAND);
	Units_Holder_SelectionShape->Add(Units_Text_SelectionShape, 0, wxEXPAND);
	Units_Holder_Civ->Add(Units_Text_Civ, 0, wxEXPAND);
	Units_Holder_Unknown9->Add(Units_Text_Unknown9, 0, wxEXPAND);
	Units_Holder_Attribute->Add(Units_Text_Attribute, 0, wxEXPAND);
	Units_Holder_SelectionEffect->Add(Units_Text_SelectionEffect, 0, wxEXPAND);
	Units_Holder_EditorSelectionColour->Add(Units_Text_EditorSelectionColour, 0, wxEXPAND);
	Units_Holder_SelectionRadius->Add(Units_Text_SelectionRadius, 0, wxEXPAND);
	Units_Holder_HPBarHeight2->Add(Units_Text_HPBarHeight2, 0, wxEXPAND);
	Units_Holder_SelectionSound->Add(Units_Text_SelectionSound, 0, wxEXPAND);
	Units_Holder_DyingSound->Add(Units_Text_DyingSound, 0, wxEXPAND);
	Units_Holder_AttackSound->Add(Units_Text_AttackSound, 0, wxEXPAND);
	Units_Holder_Name->Add(Units_Text_Name, 0, wxEXPAND);
	Units_Holder_Name2->Add(Units_Text_Name2, 0, wxEXPAND);
	Units_Holder_Unitline->Add(Units_Text_Unitline, 0, wxEXPAND);
	Units_Holder_MinTechLevel->Add(Units_Text_MinTechLevel, 0, wxEXPAND);
	Units_Holder_ID2->Add(Units_Text_ID2, 0, wxEXPAND);
	Units_Holder_ID3->Add(Units_Text_ID3, 0, wxEXPAND);

//	Type 20+

	Units_Holder_Speed->Add(Units_Text_Speed, 0, wxEXPAND);

//	Type 30+

	Units_Holder_RotationSpeed->Add(Units_Text_RotationSpeed, 0, wxEXPAND);
	Units_Holder_Unknown11->Add(Units_Text_Unknown11, 0, wxEXPAND);
	Units_Holder_TrackingUnit->Add(Units_Text_TrackingUnit, 0, wxEXPAND);
	Units_Holder_TrackingUnitUsed->Add(Units_Text_TrackingUnitUsed, 0, wxEXPAND);
	Units_Holder_TrackingUnitDensity->Add(Units_Text_TrackingUnitDensity, 0, wxEXPAND);
	Units_Holder_Unknown12->Add(Units_Text_Unknown12, 0, wxEXPAND);
	Units_Holder_Unknown16->Add(Units_Text_Unknown16, 0, wxEXPAND);

//	Type 40+

	Units_Holder_SearchRadius->Add(Units_Text_SearchRadius, 0, wxEXPAND);
	Units_Holder_WorkRate->Add(Units_Text_WorkRate, 0, wxEXPAND);
	Units_Holder_AttributesDropSite->Add(Units_Text_DropSite, 0, wxEXPAND);
	Units_Holder_VillagerMode->Add(Units_Text_VillagerMode, 0, wxEXPAND);
	Units_Holder_MoveSound->Add(Units_Text_MoveSound, 0, wxEXPAND);
	Units_Holder_StopSound->Add(Units_Text_StopSound, 0, wxEXPAND);
	Units_Holder_Exists->Add(Units_Text_Exists, 0, wxEXPAND);

//	Type 60+

	Units_Holder_Unknown20->Add(Units_Text_Unknown20, 0, wxEXPAND);
	Units_Holder_Unknown21->Add(Units_Text_Unknown21, 0, wxEXPAND);
	Units_Holder_MaxRange->Add(Units_Text_MaxRange, 0, wxEXPAND);
	Units_Holder_BlastRadius->Add(Units_Text_BlastRadius, 0, wxEXPAND);
	Units_Holder_ReloadTime1->Add(Units_Text_ReloadTime1, 0, wxEXPAND);
	Units_Holder_AccuracyPercent->Add(Units_Text_AccuracyPercent, 0, wxEXPAND);
	Units_Holder_Delay->Add(Units_Text_Delay, 0, wxEXPAND);
	Units_Holder_GraphicDisplacement->Add(Units_Text_GraphicDisplacement, 0, wxEXPAND);
	Units_Holder_BlastLevel->Add(Units_Text_BlastLevel, 0, wxEXPAND);
	Units_Holder_MinRange->Add(Units_Text_MinRange, 0, wxEXPAND);
	Units_Holder_GarrisonRecoveryRate->Add(Units_Text_GarrisonRecoveryRate, 0, wxEXPAND);
	Units_Holder_AttackGraphic->Add(Units_Text_AttackGraphic, 0, wxEXPAND);
	Units_Holder_DisplayedMeleeArmour->Add(Units_Text_DisplayedMeleeArmour, 0, wxEXPAND);
	Units_Holder_DisplayedAttack->Add(Units_Text_DisplayedAttack, 0, wxEXPAND);
	Units_Holder_DisplayedRange->Add(Units_Text_DisplayedRange, 0, wxEXPAND);
	Units_Holder_ReloadTime2->Add(Units_Text_ReloadTime2, 0, wxEXPAND);

//	Type 60 only

	Units_Holder_StretchMode->Add(Units_Text_StretchMode, 0, wxEXPAND);
	Units_Holder_CompensationMode->Add(Units_Text_CompensationMode, 0, wxEXPAND);
	Units_Holder_DropAnimationMode->Add(Units_Text_DropAnimationMode, 0, wxEXPAND);
	Units_Holder_PenetrationMode->Add(Units_Text_PenetrationMode, 0, wxEXPAND);
	Units_Holder_Unknown24->Add(Units_Text_Unknown24, 0, wxEXPAND);
	Units_Holder_ProjectileArc->Add(Units_Text_ProjectileArc, 0, wxEXPAND);

//	Type 70+

	Units_Holder_CostType->Add(Units_Text_CostType, 2, wxEXPAND);
	Units_Holder_CostAmount->Add(Units_Text_CostAmount, 2, wxEXPAND);
	Units_Holder_CostUsed->Add(Units_Text_CostUsed, 2, wxEXPAND);
	Units_Holder_TrainTime->Add(Units_Text_TrainTime, 0, wxEXPAND);
	Units_Holder_TrainLocationID->Add(Units_Text_TrainLocationID, 0, wxEXPAND);
	Units_Holder_ButtonID->Add(Units_Text_ButtonID, 0, wxEXPAND);
	Units_Holder_Unknown26->Add(Units_Text_Unknown26, 0, wxEXPAND);
	Units_Holder_Unknown27->Add(Units_Text_Unknown27, 0, wxEXPAND);
	Units_Holder_Unknown28->Add(Units_Text_Unknown28, 0, wxEXPAND);
	Units_Holder_MissileGraphicDelay->Add(Units_Text_MissileGraphicDelay, 0, wxEXPAND);
	Units_Holder_AttackMissileDuplicationAmount1->Add(Units_Text_AttackMissileDuplicationAmount1, 0, wxEXPAND);
	Units_Holder_AttackMissileDuplicationAmount2->Add(Units_Text_AttackMissileDuplicationAmount2, 0, wxEXPAND);
	Units_Holder_AttackMissileDuplicationSpawning->Add(Units_Text_AttackMissileDuplicationSpawning, 0, wxEXPAND);
	Units_Holder_Unknown29->Add(Units_Text_Unknown29, 0, wxEXPAND);
	Units_Holder_DisplayedPierceArmour->Add(Units_Text_DisplayedPierceArmour, 0, wxEXPAND);

//	Type 80

	Units_Holder_ConstructionGraphicID->Add(Units_Text_ConstructionGraphicID, 0, wxEXPAND);
	Units_Holder_SnowGraphicID->Add(Units_Text_SnowGraphicID, 0, wxEXPAND);
	Units_Holder_Unknown31->Add(Units_Text_Unknown31, 0, wxEXPAND);
	Units_Holder_Unknown31b->Add(Units_Text_Unknown31b, 0, wxEXPAND);
	Units_Holder_StackUnitID->Add(Units_Text_StackUnitID, 0, wxEXPAND);
	Units_Holder_TerrainID->Add(Units_Text_TerrainID, 0, wxEXPAND);
	Units_Holder_Unknown32->Add(Units_Text_Unknown32, 0, wxEXPAND);
	Units_Holder_ResearchID->Add(Units_Text_ResearchID, 0, wxEXPAND);
	Units_Holder_Unknown33->Add(Units_Text_Unknown33, 0, wxEXPAND);
	Units_Holder_AnnexUnit1->Add(Units_Text_AnnexUnit, 0, wxEXPAND);
	Units_Holder_AnnexUnitMisplacement1->Add(Units_Text_AnnexUnitMisplacement, 0, wxEXPAND);
	Units_Holder_HeadUnit->Add(Units_Text_HeadUnit, 0, wxEXPAND);
	Units_Holder_TransformUnit->Add(Units_Text_TransformUnit, 0, wxEXPAND);
	Units_Holder_Unknown34->Add(Units_Text_Unknown34, 0, wxEXPAND);
	Units_Holder_ConstructionSound->Add(Units_Text_ConstructionSound, 0, wxEXPAND);
	Units_Holder_GarrisonHealRate->Add(Units_Text_GarrisonHealRate, 0, wxEXPAND);
	Units_Holder_Unknown35->Add(Units_Text_Unknown35, 0, wxEXPAND);
	Units_Holder_Unknown36->Add(Units_Text_Unknown36, 0, wxEXPAND);
	Units_Holder_Unknown37->Add(Units_Text_Unknown37, 0, wxEXPAND);
	
//	Type 10+

	Units_Holder_ID1->Add(Units_ID1, 1, wxEXPAND);
	Units_Holder_LanguageDllName->Add(Units_LanguageDllName, 1, wxEXPAND);
	Units_Holder_LanguageDllName->Add(Units_DLL_LanguageDllName, 2, wxEXPAND);
	Units_Holder_LanguageDllCreation->Add(Units_LanguageDllCreation, 1, wxEXPAND);
	Units_Holder_LanguageDllCreation->Add(Units_DLL_LanguageDllCreation, 2, wxEXPAND);
	Units_Holder_Class->Add(Units_Class, 1, wxEXPAND);
	Units_Holder_Class->Add(Units_ComboBox_Class[0], 2, wxEXPAND);
	Units_Holder_DeathMode->Add(Units_DeathMode, 1, wxEXPAND);
	Units_Holder_DeathMode->Add(2, -1);
	Units_Holder_DeathMode->Add(Units_CheckBox_DeathMode, 2, wxEXPAND);
	Units_Holder_HitPoints->Add(Units_HitPoints, 1, wxEXPAND);
	Units_Holder_LineOfSight->Add(Units_LineOfSight, 1, wxEXPAND);
	Units_Holder_GarrisonCapacity->Add(Units_GarrisonCapacity, 0, wxEXPAND);
	for(short loop = 0;loop < 2;loop++)
	Units_Grid_SizeRadius->Add(Units_SizeRadius[loop], 1, wxEXPAND);
	Units_Holder_SizeRadius->Add(Units_Grid_SizeRadius, 1, wxEXPAND);
	Units_Holder_HPBarHeight1->Add(Units_HPBarHeight1, 1, wxEXPAND);
	Units_Holder_DeadUnitID->Add(Units_DeadUnitID, 1, wxEXPAND);
	Units_Holder_DeadUnitID->Add(Units_ComboBox_DeadUnitID, 1, wxEXPAND);
	Units_Holder_PlacementMode->Add(Units_PlacementMode, 0, wxEXPAND);
	Units_Holder_AirMode->Add(Units_AirMode, 1, wxEXPAND);
	Units_Holder_AirMode->Add(2, -1);
	Units_Holder_AirMode->Add(Units_CheckBox_AirMode, 2, wxEXPAND);
	Units_Holder_IconID->Add(Units_IconID, 0, wxEXPAND);
	Units_Holder_HideInEditor->Add(Units_HideInEditor, 1, wxEXPAND);
	Units_Holder_HideInEditor->Add(2, -1);
	Units_Holder_HideInEditor->Add(Units_CheckBox_HideInEditor, 2, wxEXPAND);
	Units_Holder_Unknown1->Add(Units_Unknown1, 1, wxEXPAND);
	Units_Holder_Enabled->Add(Units_Enabled, 1, wxEXPAND);
	Units_Holder_Enabled->Add(2, -1);
	Units_Holder_Enabled->Add(Units_CheckBox_Enabled, 2, wxEXPAND);
	for(short loop = 0;loop < 2;loop++)
	Units_Holder_PlacementBypassTerrainGrid->Add(Units_PlacementBypassTerrain[loop], 1, wxEXPAND);
	for(short loop = 0;loop < 2;loop++)
	Units_Holder_PlacementBypassTerrainGrid->Add(Units_ComboBox_PlacementBypassTerrain[loop], 1, wxEXPAND);
	Units_Holder_PlacementBypassTerrain->Add(Units_Holder_PlacementBypassTerrainGrid, 0, wxEXPAND);
	for(short loop = 0;loop < 2;loop++)
	Units_Holder_PlacementTerrainGrid->Add(Units_PlacementTerrain[loop], 1, wxEXPAND);
	for(short loop = 0;loop < 2;loop++)
	Units_Holder_PlacementTerrainGrid->Add(Units_ComboBox_PlacementTerrain[loop], 1, wxEXPAND);
	Units_Holder_PlacementTerrain->Add(Units_Holder_PlacementTerrainGrid, 0, wxEXPAND);
	for(short loop = 0;loop < 2;loop++)
	Units_Grid_EditorRadius->Add(Units_EditorRadius[loop], 1, wxEXPAND);
	Units_Holder_EditorRadius->Add(Units_Grid_EditorRadius, 1, wxEXPAND);
	Units_Holder_BuildingMode->Add(Units_BuildingMode, 0, wxEXPAND);
	Units_Holder_VisibleInFog->Add(Units_Text_VisibleInFog, 0, wxEXPAND);
	Units_Holder_VisibleInFog->Add(Units_VisibleInFog, 0, wxEXPAND);
	Units_Holder_TerrainRestriction->Add(Units_TerrainRestriction, 1, wxEXPAND);
	Units_Holder_TerrainRestriction->Add(Units_ComboBox_TerrainRestriction, 1, wxEXPAND);
	Units_Holder_FlyMode->Add(Units_FlyMode, 1, wxEXPAND);
	Units_Holder_FlyMode->Add(2, -1);
	Units_Holder_FlyMode->Add(Units_CheckBox_FlyMode, 2, wxEXPAND);
	Units_Holder_ResourceCapacity->Add(Units_ResourceCapacity, 1, wxEXPAND);
	Units_Holder_ResourceDecay->Add(Units_ResourceDecay, 1, wxEXPAND);
	Units_Holder_BlastType->Add(Units_BlastType, 1, wxEXPAND);
	Units_Holder_Unknown2->Add(Units_Unknown2, 1, wxEXPAND);
	Units_Holder_InteractionMode->Add(Units_InteractionMode, 1, wxEXPAND);
	Units_Holder_MinimapMode->Add(Units_MinimapMode, 1, wxEXPAND);
	Units_Holder_CommandAttribute->Add(Units_CommandAttribute, 0, wxEXPAND);
	Units_Holder_Unknown3->Add(Units_Unknown3, 1, wxEXPAND);
	Units_Holder_Unknown3B->Add(Units_Unknown3B, 1, wxEXPAND);
	Units_Holder_Unknown3a->Add(Units_Unknown3a, 1, wxEXPAND);
	Units_Holder_LanguageDllHelp->Add(Units_LanguageDllHelp, 1, wxEXPAND);
	Units_Holder_LanguageDllHelp->Add(Units_DLL_LanguageDllHelp, 2, wxEXPAND);
	for(short loop = 0;loop < 4;loop++)
	Units_Grid_HotKey->Add(Units_HotKey[loop], 1, wxEXPAND);
	Units_Grid_HotKey->Add(Units_DLL_HotKey4, 1, wxEXPAND);
	Units_Holder_Unknown4->Add(Units_Unknown4, 1, wxEXPAND);
	Units_Holder_Unknown5->Add(Units_Unknown5, 1, wxEXPAND);
	Units_Holder_Unselectable->Add(Units_CheckBox_Unselectable, 0, wxEXPAND);
	Units_Holder_Unselectable->Add(Units_Unselectable, 1, wxEXPAND);
	Units_Holder_Unknown6->Add(Units_Unknown6, 1, wxEXPAND);
	Units_Holder_Unknown7->Add(Units_Unknown7, 0, wxEXPAND);
	Units_Holder_Unknown8->Add(Units_Unknown8, 1, wxEXPAND);
	Units_Holder_SelectionMask->Add(Units_SelectionMask, 0, wxEXPAND);
	Units_Holder_SelectionShapeType->Add(Units_SelectionShapeType, 0, wxEXPAND);
	Units_Holder_SelectionShape->Add(Units_SelectionShape, 0, wxEXPAND);
	Units_Holder_Attribute->Add(Units_Attribute, 1, wxEXPAND);
	Units_Holder_Civ->Add(Units_Civ, 1, wxEXPAND);
	Units_Holder_Civ->Add(Units_ComboBox_Civ, 1, wxEXPAND);
	for(short loop = 0;loop < 2;loop++)
	Units_Grid_Unknown9->Add(Units_Unknown9[loop], 1, wxEXPAND);
	Units_Holder_Unknown9->Add(Units_Grid_Unknown9, 0, wxEXPAND);
	Units_Holder_SelectionEffect->Add(Units_SelectionEffect, 0, wxEXPAND);
	Units_Holder_EditorSelectionColour->Add(Units_EditorSelectionColour, 0, wxEXPAND);
	for(short loop = 0;loop < 2;loop++)
	Units_SelectionRadiusBox->Add(Units_SelectionRadius[loop], 1, wxEXPAND);
	Units_Holder_SelectionRadius->Add(Units_SelectionRadiusBox, 1, wxEXPAND);
	Units_Holder_HPBarHeight2->Add(Units_HPBarHeight2, 1, wxEXPAND);
	Units_Holder_SelectionSound->Add(Units_SelectionSound, 1, wxEXPAND);
	Units_Holder_SelectionSound->Add(Units_ComboBox_SelectionSound, 1, wxEXPAND);
	Units_Holder_DyingSound->Add(Units_DyingSound, 1, wxEXPAND);
	Units_Holder_DyingSound->Add(Units_ComboBox_DyingSound, 1, wxEXPAND);
	Units_Holder_AttackSound->Add(Units_AttackSound, 1, wxEXPAND);
	Units_Holder_AttackSound->Add(Units_ComboBox_AttackSound, 1, wxEXPAND);
	Units_Holder_Name->Add(Units_Name, 1, wxEXPAND);
	Units_Holder_Name2->Add(Units_Name2, 1, wxEXPAND);
	Units_Holder_Unitline->Add(Units_Unitline, 1, wxEXPAND);
	Units_Holder_Unitline->Add(Units_ComboBox_Unitline, 1, wxEXPAND);
	Units_Holder_MinTechLevel->Add(Units_MinTechLevel, 0, wxEXPAND);
	Units_Holder_ID2->Add(Units_ID2, 1, wxEXPAND);
	Units_Holder_ID3->Add(Units_ID3, 1, wxEXPAND);

//	Type 20+

	Units_Holder_Speed->Add(Units_Speed, 1, wxEXPAND);

//	Type 30+

	Units_Holder_RotationSpeed->Add(Units_RotationSpeed, 1, wxEXPAND);
	Units_Holder_Unknown11->Add(Units_Unknown11, 1, wxEXPAND);
	Units_Holder_TrackingUnit->Add(Units_TrackingUnit, 1, wxEXPAND);
	Units_Holder_TrackingUnit->Add(Units_ComboBox_TrackingUnit, 1, wxEXPAND);
	Units_Holder_TrackingUnitUsedBox->Add(Units_TrackingUnitUsed, 2, wxEXPAND);
	Units_Holder_TrackingUnitUsed->Add(Units_Holder_TrackingUnitUsedBox, 0, wxEXPAND);
	Units_Holder_TrackingUnitDensity->Add(Units_TrackingUnitDensity, 0, wxEXPAND);
	Units_Holder_Unknown12->Add(Units_Unknown12, 1, wxEXPAND);
	for(short loop = 0;loop < 17;loop++)
	Units_Grid_Unknown16->Add(Units_Unknown16[loop], 1, wxEXPAND);
	Units_Holder_Unknown16->Add(Units_Grid_Unknown16, 0, wxEXPAND);

//	Type 40+

	Units_Holder_SheepConversion->Add(Units_SheepConversion, 1, wxEXPAND);
	Units_Holder_SheepConversion->Add(2, -1);
	Units_Holder_SheepConversion->Add(Units_CheckBox_SheepConversion, 2, wxEXPAND);
	Units_Holder_SearchRadius->Add(Units_SearchRadius, 1, wxEXPAND);
	Units_Holder_WorkRate->Add(Units_WorkRate, 1, wxEXPAND);
	Units_Grid_DropSite->Add(Units_DropSite[0], 1, wxEXPAND);
	Units_Grid_DropSite->Add(Units_DropSite[1], 1, wxEXPAND);
	Units_Grid_DropSite->AddStretchSpacer(1);
	Units_Grid_DropSite->AddStretchSpacer(1);
	Units_Grid_DropSite->Add(Units_ComboBox_DropSite[0], 2, wxEXPAND);
	Units_Grid_DropSite->Add(Units_ComboBox_DropSite[1], 2, wxEXPAND);
	Units_Holder_VillagerMode->Add(Units_VillagerMode, 1, wxEXPAND);
	Units_Holder_MoveSound->Add(Units_MoveSound, 1, wxEXPAND);
	Units_Holder_MoveSound->Add(Units_ComboBox_MoveSound, 1, wxEXPAND);
	Units_Holder_StopSound->Add(Units_StopSound, 1, wxEXPAND);
	Units_Holder_StopSound->Add(Units_ComboBox_StopSound, 1, wxEXPAND);
	Units_Holder_AnimalMode->Add(Units_AnimalMode, 1, wxEXPAND);
	Units_Holder_AnimalMode->Add(2, -1);
	Units_Holder_AnimalMode->Add(Units_CheckBox_AnimalMode, 2, wxEXPAND);
	Units_Holder_Exists->Add(Units_Exists, 1, wxEXPAND);

//	Type 60+

	for(short loop = 0;loop < 2;loop++)
	Units_Grid_Unknown20->Add(Units_Unknown20[loop], 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Units_Holder_Unknown20->Add(Units_Grid_Unknown20, 0, wxEXPAND);
	Units_Holder_Unknown21->Add(Units_Unknown21, 1, wxEXPAND);
	Units_Holder_MaxRange->Add(Units_MaxRange, 1, wxEXPAND);
	Units_Holder_BlastRadius->Add(Units_BlastRadius, 1, wxEXPAND);
	Units_Holder_ReloadTime1->Add(Units_ReloadTime1, 1, wxEXPAND);
	Units_Holder_AccuracyPercent->Add(Units_AccuracyPercent, 1, wxEXPAND);
	Units_Holder_TowerMode->Add(Units_TowerMode, 1, wxEXPAND);
	Units_Holder_TowerMode->Add(2, -1);
	Units_Holder_TowerMode->Add(Units_CheckBox_TowerMode, 2, wxEXPAND);
	Units_Holder_Delay->Add(Units_Delay, 1, wxEXPAND);
	for(short loop = 0;loop < 3;loop++)
	Units_Grid_GraphicDisplacement->Add(Units_GraphicDisplacement[loop], 1, wxEXPAND);
	Units_Holder_GraphicDisplacement->Add(Units_Grid_GraphicDisplacement, 1, wxEXPAND);
	Units_Holder_BlastLevel->Add(Units_BlastLevel, 1, wxEXPAND);
	Units_Holder_MinRange->Add(Units_MinRange, 1, wxEXPAND);
	Units_Holder_GarrisonRecoveryRate->Add(Units_GarrisonRecoveryRate, 0, wxEXPAND);
	Units_Holder_AttackGraphic->Add(Units_AttackGraphic, 1, wxEXPAND);
	Units_Holder_AttackGraphic->Add(Units_ComboBox_AttackGraphic, 1, wxEXPAND);
	Units_Holder_DisplayedMeleeArmour->Add(Units_DisplayedMeleeArmour, 1, wxEXPAND);
	Units_Holder_DisplayedAttack->Add(Units_DisplayedAttack, 1, wxEXPAND);
	Units_Holder_DisplayedRange->Add(Units_DisplayedRange, 1, wxEXPAND);
	Units_Holder_ReloadTime2->Add(Units_ReloadTime2, 1, wxEXPAND);

//	Type 60 only

	Units_Holder_StretchMode->Add(Units_StretchMode, 1, wxEXPAND);
	Units_Holder_CompensationMode->Add(Units_CompensationMode, 1, wxEXPAND);
	Units_Holder_DropAnimationMode->Add(Units_DropAnimationMode, 1, wxEXPAND);
	Units_Holder_PenetrationMode->Add(Units_PenetrationMode, 1, wxEXPAND);
	Units_Holder_Unknown24->Add(Units_Unknown24, 1, wxEXPAND);
	Units_Holder_ProjectileArc->Add(Units_ProjectileArc, 1, wxEXPAND);

//	Type 70+

	for(short loop = 0;loop < 3;loop++)
	Units_Grid_CostType->Add(Units_CostType[loop], 1, wxEXPAND);
	for(short loop = 0;loop < 3;loop++)
	Units_Grid_CostType->Add(Units_ComboBox_CostType[loop], 1, wxEXPAND);
	Units_Holder_CostType->Add(Units_Grid_CostType, 12, wxEXPAND);
	Units_Holder_CostAmount->Add(Units_CostAmount[0], 4, wxEXPAND);
	Units_Holder_CostAmount->Add(5, -1);
	Units_Holder_CostAmount->Add(Units_CostAmount[1], 4, wxEXPAND);
	Units_Holder_CostAmount->Add(5, -1);
	Units_Holder_CostAmount->Add(Units_CostAmount[2], 4, wxEXPAND);
	Units_Holder_CostUsed->Add(Units_CostUsed[0], 3, wxEXPAND);
	Units_Holder_CostUsed->Add(2, -1);
	Units_Holder_CostUsed->Add(Units_CheckBox_CostUsed[0], 1, wxEXPAND);
	Units_Holder_CostUsed->Add(5, -1);
	Units_Holder_CostUsed->Add(Units_CostUsed[1], 3, wxEXPAND);
	Units_Holder_CostUsed->Add(2, -1);
	Units_Holder_CostUsed->Add(Units_CheckBox_CostUsed[1], 1, wxEXPAND);
	Units_Holder_CostUsed->Add(5, -1);
	Units_Holder_CostUsed->Add(Units_CostUsed[2], 3, wxEXPAND);
	Units_Holder_CostUsed->Add(2, -1);
	Units_Holder_CostUsed->Add(Units_CheckBox_CostUsed[2], 1, wxEXPAND);
	Units_Holder_TrainTime->Add(Units_TrainTime, 0, wxEXPAND);
	Units_Holder_TrainLocationID->Add(Units_TrainLocationID, 1, wxEXPAND);
	Units_Holder_TrainLocationID->Add(Units_ComboBox_TrainLocationID, 1, wxEXPAND);
	Units_Holder_ButtonID->Add(Units_ButtonID, 0, wxEXPAND);
	Units_Holder_Unknown26->Add(Units_Unknown26, 1, wxEXPAND);
	for(short loop = 0;loop < 3;loop++)
	Units_Holder_Unknown27->Add(Units_Unknown27[loop], 1, wxEXPAND);
	Units_Holder_Unknown28->Add(Units_Unknown28, 1, wxEXPAND);
	Units_Holder_MissileGraphicDelay->Add(Units_MissileGraphicDelay, 1, wxEXPAND);
	Units_Holder_HeroMode->Add(Units_HeroMode, 1, wxEXPAND);
	Units_Holder_HeroMode->Add(2, -1);
	Units_Holder_HeroMode->Add(Units_CheckBox_HeroMode, 2, wxEXPAND);
	Units_Holder_AttackMissileDuplicationAmount1->Add(Units_AttackMissileDuplicationAmount1, 1, wxEXPAND);
	Units_Holder_AttackMissileDuplicationAmount2->Add(Units_AttackMissileDuplicationAmount2, 1, wxEXPAND);
	for(short loop = 0;loop < 3;loop++)
	Units_Grid_AttackMissileDuplicationSpawning->Add(Units_AttackMissileDuplicationSpawning[loop], 1, wxEXPAND);
	Units_Holder_AttackMissileDuplicationSpawning->Add(Units_Grid_AttackMissileDuplicationSpawning, 1, wxEXPAND);
	Units_Holder_Unknown29->Add(Units_Unknown29, 1, wxEXPAND);
	Units_Holder_DisplayedPierceArmour->Add(Units_DisplayedPierceArmour, 1, wxEXPAND);

//	Type 80

	Units_Holder_ConstructionGraphicID->Add(Units_ConstructionGraphicID, 1, wxEXPAND);
	Units_Holder_ConstructionGraphicID->Add(Units_ComboBox_ConstructionGraphicID, 1, wxEXPAND);
	Units_Holder_SnowGraphicID->Add(Units_SnowGraphicID, 1, wxEXPAND);
	Units_Holder_SnowGraphicID->Add(Units_ComboBox_SnowGraphicID, 1, wxEXPAND);
	Units_Holder_AdjacentMode->Add(Units_AdjacentMode, 1, wxEXPAND);
	Units_Holder_AdjacentMode->Add(2, -1);
	Units_Holder_AdjacentMode->Add(Units_CheckBox_AdjacentMode, 2, wxEXPAND);
	Units_Holder_Unknown31->Add(Units_Unknown31, 1, wxEXPAND);
	Units_Holder_Unknown31bsub->Add(Units_Unknown31b, 1, wxEXPAND);
	Units_Holder_Unknown31bsub->Add(2, -1);
	Units_Holder_Unknown31bsub->Add(Units_CheckBox_Unknown31b, 2, wxEXPAND);
	Units_Holder_Unknown31b->Add(Units_Holder_Unknown31bsub, 0, wxEXPAND);
	Units_Holder_StackUnitID->Add(Units_StackUnitID, 1, wxEXPAND);
	Units_Holder_StackUnitID->Add(Units_ComboBox_StackUnitID, 1, wxEXPAND);
	Units_Holder_TerrainID->Add(Units_TerrainID, 1, wxEXPAND);
	Units_Holder_TerrainID->Add(Units_ComboBox_TerrainID, 1, wxEXPAND);
	Units_Holder_Unknown32->Add(Units_Unknown32, 1, wxEXPAND);
	Units_Holder_ResearchID->Add(Units_ResearchID, 1, wxEXPAND);
	Units_Holder_ResearchID->Add(Units_ComboBox_ResearchID, 1, wxEXPAND);
	Units_Holder_Unknown33->Add(Units_Unknown33, 1, wxEXPAND);
	for(short loop = 0;loop < 4;loop++)
	Units_Grid_AnnexUnit->Add(Units_AnnexUnit[loop], 1, wxEXPAND);
	for(short loop = 0;loop < 4;loop++)
	Units_Grid_AnnexUnit->Add(Units_ComboBox_AnnexUnit[loop], 1, wxEXPAND);
	Units_Holder_AnnexUnit1->Add(Units_Grid_AnnexUnit, 0, wxEXPAND);
	for(short loop = 0;loop < 4;loop++)
	Units_Grid_AnnexUnitMisplacement->Add(Units_AnnexUnitMisplacement[loop][0], 1, wxEXPAND);
	for(short loop = 0;loop < 4;loop++)
	Units_Grid_AnnexUnitMisplacement->Add(Units_AnnexUnitMisplacement[loop][1], 1, wxEXPAND);
	Units_Holder_AnnexUnitMisplacement1->Add(Units_Grid_AnnexUnitMisplacement, 0, wxEXPAND);
	Units_Holder_HeadUnit->Add(Units_HeadUnit, 1, wxEXPAND);
	Units_Holder_HeadUnit->Add(Units_ComboBox_HeadUnit, 1, wxEXPAND);
	Units_Holder_TransformUnit->Add(Units_TransformUnit, 1, wxEXPAND);
	Units_Holder_TransformUnit->Add(Units_ComboBox_TransformUnit, 1, wxEXPAND);
	Units_Holder_Unknown34->Add(Units_Unknown34, 1, wxEXPAND);
	Units_Holder_ConstructionSound->Add(Units_ConstructionSound, 1, wxEXPAND);
	Units_Holder_ConstructionSound->Add(Units_ComboBox_ConstructionSound, 1, wxEXPAND);
	Units_Holder_GarrisonHealRate->Add(Units_GarrisonHealRate, 0, wxEXPAND);
	Units_Holder_Unknown35->Add(Units_Unknown35, 1, wxEXPAND);
	Units_Holder_Unknown36->Add(Units_Unknown36, 1, wxEXPAND);
	for(short loop = 0;loop < 6;loop++)
	Units_Holder_Unknown37->Add(Units_Unknown37[loop], 1, wxEXPAND);
	
	for(short loop = 0;loop < 3;loop++)
	Units_Grid_ResourceStorage->Add(ResourceStorage_Type[loop], 1, wxEXPAND);
	for(short loop = 0;loop < 3;loop++)
	Units_Grid_ResourceStorage->Add(ResourceStorage_ComboBox_Type[loop], 1, wxEXPAND);
	Units_Holder_ResourceStorage[0]->Add(ResourceStorage_Text_Type, 2, wxEXPAND);
	Units_Holder_ResourceStorage[0]->Add(Units_Grid_ResourceStorage, 12, wxEXPAND);
	Units_Holder_ResourceStorage[1]->Add(ResourceStorage_Text_Amount, 2, wxEXPAND);
	Units_Holder_ResourceStorage[1]->Add(ResourceStorage_Amount[0], 4, wxEXPAND);
	Units_Holder_ResourceStorage[1]->Add(5, 5);
	Units_Holder_ResourceStorage[1]->Add(ResourceStorage_Amount[1], 4, wxEXPAND);
	Units_Holder_ResourceStorage[1]->Add(5, 5);
	Units_Holder_ResourceStorage[1]->Add(ResourceStorage_Amount[2], 4, wxEXPAND);
	Units_Holder_ResourceStorage[2]->Add(ResourceStorage_Text_Enabled, 2, wxEXPAND);
	Units_Holder_ResourceStorage[2]->Add(ResourceStorage_Enabled[0], 4, wxEXPAND);
	Units_Holder_ResourceStorage[2]->Add(5, 5);
	Units_Holder_ResourceStorage[2]->Add(ResourceStorage_Enabled[1], 4, wxEXPAND);
	Units_Holder_ResourceStorage[2]->Add(5, 5);
	Units_Holder_ResourceStorage[2]->Add(ResourceStorage_Enabled[2], 4, wxEXPAND);
	
	Attacks_Holder_Class1->Add(Attacks_Class, 1, wxEXPAND);
	Attacks_Holder_Class1->Add(Attacks_ComboBox_Class[0], 2, wxEXPAND);
	Attacks_Holder_Class->Add(Attacks_Text_Class, 0, wxEXPAND);
	Attacks_Holder_Class->Add(Attacks_Holder_Class1, 1, wxEXPAND);
	Attacks_Holder_Amount->Add(Attacks_Text_Amount, 0, wxEXPAND);
	Attacks_Holder_Amount->Add(Attacks_Amount, 1, wxEXPAND);
	
	Units_Attacks_Buttons->Add(Units_Attacks_Add, 1, wxEXPAND);
	Units_Attacks_Buttons->Add(Units_Attacks_Delete, 1, wxEXPAND);
	Units_Attacks_Buttons->Add(Units_Attacks_Copy, 1, wxEXPAND);
	Units_Attacks_Buttons->Add(Units_Attacks_Paste, 1, wxEXPAND);
	
	Units_Attacks->Add(Units_Attacks_Search, 0, wxEXPAND);
	Units_Attacks->Add(Units_Attacks_Search_R, 0, wxEXPAND);
	Units_Attacks->Add(-1, 2);
	Units_Attacks->Add(Units_Attacks_List, 1, wxEXPAND);
	Units_Attacks->Add(-1, 2);
	Units_Attacks->Add(Units_Attacks_Buttons, 0, wxEXPAND);
	
	Armors_Holder_Class1->Add(Armors_Class, 1, wxEXPAND);
	Armors_Holder_Class1->Add(Attacks_ComboBox_Class[1], 2, wxEXPAND);
	Armors_Holder_Class->Add(Armors_Text_Class, 0, wxEXPAND);
	Armors_Holder_Class->Add(Armors_Holder_Class1, 1, wxEXPAND);
	Armors_Holder_Amount->Add(Armors_Text_Amount, 0, wxEXPAND);
	Armors_Holder_Amount->Add(Armors_Amount, 1, wxEXPAND);
	
	Units_Armors_Buttons->Add(Units_Armors_Add, 1, wxEXPAND);
	Units_Armors_Buttons->Add(Units_Armors_Delete, 1, wxEXPAND);
	Units_Armors_Buttons->Add(Units_Armors_Copy, 1, wxEXPAND);
	Units_Armors_Buttons->Add(Units_Armors_Paste, 1, wxEXPAND);
	
	Units_Armors->Add(Units_Armors_Search, 0, wxEXPAND);
	Units_Armors->Add(Units_Armors_Search_R, 0, wxEXPAND);
	Units_Armors->Add(-1, 2);
	Units_Armors->Add(Units_Armors_List, 1, wxEXPAND);
	Units_Armors->Add(-1, 2);
	Units_Armors->Add(Units_Armors_Buttons, 0, wxEXPAND);
	
	UnitCommands_Holder_One->Add(UnitCommands_Text_One, 0, wxEXPAND);
	UnitCommands_Holder_One->Add(UnitCommands_One, 1, wxEXPAND);
	UnitCommands_Holder_ID->Add(UnitCommands_Text_ID, 0, wxEXPAND);
	UnitCommands_Holder_ID->Add(UnitCommands_ID, 1, wxEXPAND);
	UnitCommands_Holder_Unknown1->Add(UnitCommands_Text_Unknown1, 0, wxEXPAND);
	UnitCommands_Holder_Unknown1->Add(UnitCommands_Unknown1, 1, wxEXPAND);
	UnitCommands_Holder_Type->Add(UnitCommands_Text_Type, 0, wxEXPAND);
	UnitCommands_Holder_Type->Add(UnitCommands_Type, 1, wxEXPAND);
	UnitCommands_Holder_SubType->Add(UnitCommands_Text_SubType, 0, wxEXPAND);
	UnitCommands_Holder_SubType->Add(UnitCommands_SubType, 1, wxEXPAND);
	UnitCommands_Holder_ClassID->Add(UnitCommands_Text_ClassID, 0, wxEXPAND);
	UnitCommands_Holder_ClassID->Add(UnitCommands_ClassID, 1, wxEXPAND);
	UnitCommands_Holder_ClassID->Add(Units_ComboBox_Class[1], 1, wxEXPAND);
	UnitCommands_Holder_UnitID->Add(UnitCommands_Text_UnitID, 0, wxEXPAND);
	UnitCommands_Holder_UnitID->Add(UnitCommands_UnitID, 1, wxEXPAND);
	UnitCommands_Holder_UnitID->Add(UnitCommands_ComboBox_UnitID, 1, wxEXPAND);
	UnitCommands_Holder_Unknown2->Add(UnitCommands_Text_Unknown2, 0, wxEXPAND);
	UnitCommands_Holder_Unknown2->Add(UnitCommands_Unknown2, 1, wxEXPAND);
	UnitCommands_Holder_ResourceIn->Add(UnitCommands_Text_ResourceIn, 0, wxEXPAND);
	UnitCommands_Holder_ResourceIn->Add(UnitCommands_ResourceIn, 1, wxEXPAND);
	UnitCommands_Holder_ResourceIn->Add(UnitCommands_ComboBox_ResourceIn, 1, wxEXPAND);
	UnitCommands_Holder_ResourceOut->Add(UnitCommands_Text_ResourceOut, 0, wxEXPAND);
	UnitCommands_Holder_ResourceOut->Add(UnitCommands_ResourceOut, 1, wxEXPAND);
	UnitCommands_Holder_ResourceOut->Add(UnitCommands_ComboBox_ResourceOut, 1, wxEXPAND);
	UnitCommands_Holder_Unknown3->Add(UnitCommands_Text_Unknown3, 0, wxEXPAND);
	UnitCommands_Holder_Unknown3->Add(UnitCommands_Unknown3, 1, wxEXPAND);
	UnitCommands_Holder_Unknown4->Add(UnitCommands_Text_Unknown4, 0, wxEXPAND);
	UnitCommands_Holder_Unknown4->Add(UnitCommands_Unknown4, 1, wxEXPAND);
	UnitCommands_Holder_ExecutionRadius->Add(UnitCommands_Text_ExecutionRadius, 0, wxEXPAND);
	UnitCommands_Holder_ExecutionRadius->Add(UnitCommands_ExecutionRadius, 1, wxEXPAND);
	UnitCommands_Holder_Unknown5->Add(UnitCommands_Text_Unknown5, 0, wxEXPAND);
	UnitCommands_Holder_Unknown5->Add(UnitCommands_Unknown5, 1, wxEXPAND);
	UnitCommands_Holder_Unknown6->Add(UnitCommands_Text_Unknown6, 0, wxEXPAND);
	UnitCommands_Holder_Unknown6->Add(UnitCommands_Unknown6, 1, wxEXPAND);
	UnitCommands_Holder_Unknown7->Add(UnitCommands_Text_Unknown7, 0, wxEXPAND);
	UnitCommands_Holder_Unknown7->Add(UnitCommands_Unknown7, 1, wxEXPAND);
	UnitCommands_Holder_Unknown8->Add(UnitCommands_Text_Unknown8, 0, wxEXPAND);
	UnitCommands_Holder_Unknown8->Add(UnitCommands_Unknown8, 1, wxEXPAND);
	UnitCommands_Holder_Unknown9->Add(UnitCommands_Text_Unknown9, 0, wxEXPAND);
	UnitCommands_Holder_Unknown9->Add(UnitCommands_Unknown9, 1, wxEXPAND);
	UnitCommands_Holder_Unknown10->Add(UnitCommands_Text_Unknown10, 0, wxEXPAND);
	UnitCommands_Holder_Unknown10->Add(UnitCommands_Unknown10, 1, wxEXPAND);
	UnitCommands_Holder_Unknown11->Add(UnitCommands_Text_Unknown11, 0, wxEXPAND);
	UnitCommands_Holder_Unknown11->Add(UnitCommands_Unknown11, 1, wxEXPAND);
	UnitCommands_Holder_Unknown12->Add(UnitCommands_Text_Unknown12, 0, wxEXPAND);
	UnitCommands_Holder_Unknown12->Add(UnitCommands_Unknown12, 1, wxEXPAND);
	UnitCommands_Holder_Unknown13->Add(UnitCommands_Text_Unknown13, 0, wxEXPAND);
	UnitCommands_Holder_Unknown13->Add(UnitCommands_Unknown13, 1, wxEXPAND);
	UnitCommands_Holder_Unknown14->Add(UnitCommands_Text_Unknown14, 0, wxEXPAND);
	UnitCommands_Holder_Unknown14->Add(UnitCommands_Unknown14, 1, wxEXPAND);
	for(short loop = 0;loop < 2;loop++)
	UnitCommands_Holder_GraphicsGrid->Add(UnitCommands_Graphics[loop], 1, wxEXPAND);
	for(short loop = 0;loop < 2;loop++)
	UnitCommands_Holder_GraphicsGrid->Add(UnitCommands_ComboBox_Graphics[loop], 1, wxEXPAND);
	for(short loop = 2;loop < 4;loop++)
	UnitCommands_Holder_GraphicsGrid->Add(UnitCommands_Graphics[loop], 1, wxEXPAND);
	for(short loop = 2;loop < 4;loop++)
	UnitCommands_Holder_GraphicsGrid->Add(UnitCommands_ComboBox_Graphics[loop], 1, wxEXPAND);
	for(short loop = 4;loop < 6;loop++)
	UnitCommands_Holder_GraphicsGrid->Add(UnitCommands_Graphics[loop], 1, wxEXPAND);
	for(short loop = 4;loop < 6;loop++)
	UnitCommands_Holder_GraphicsGrid->Add(UnitCommands_ComboBox_Graphics[loop], 1, wxEXPAND);
	UnitCommands_Holder_Graphics->Add(UnitCommands_Text_Graphics, 1, wxEXPAND);
	UnitCommands_Holder_Graphics->Add(UnitCommands_Holder_GraphicsGrid, 0, wxEXPAND);
	
	Units_Holder_TypeArea1->Add(Units_Holder_Class, 3, wxEXPAND);
	Units_Holder_TypeArea2->Add(Units_Holder_Name, 2, wxEXPAND);
	Units_Holder_TypeArea2->Add(5, -1);
	Units_Holder_TypeArea2->Add(Units_Holder_Name2, 2, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Units_Holder_TypeArea1->Add(5, -1);
	Units_Holder_TypeArea1->Add(Units_Holder_ID1, 1, wxEXPAND);
	Units_Holder_TypeArea1->Add(5, -1);
	Units_Holder_TypeArea1->Add(Units_Holder_ID2, 1, wxEXPAND);
	Units_Holder_TypeArea1->Add(5, -1);
	Units_Holder_TypeArea1->Add(Units_Holder_ID3, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	
	Units_Holder_TypeArea->Add(Units_Holder_TypeArea1, 0, wxEXPAND);
	Units_Holder_TypeArea->Add(5, 5);
	Units_Holder_TypeArea->Add(Units_Holder_TypeArea2, 0, wxEXPAND);
	
	Units_Holder_LangDLLArea->Add(Units_Holder_LanguageDllName, 1, wxEXPAND);
	Units_Holder_LangDLLArea->Add(5, 5);
	Units_Holder_LangDLLArea->Add(Units_Holder_LanguageDllCreation, 1, wxEXPAND);
	Units_Holder_LangDLLArea->Add(5, 5);
	Units_Holder_LangDLLArea->Add(Units_Holder_LanguageDllHelp, 1, wxEXPAND);
	
	for(short loop = 0;loop < 2;loop++)
	Units_Holder_GraphicsArea2->Add(Units_StandingGraphic[loop], 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	for(short loop = 0;loop < 2;loop++)
	Units_Holder_GraphicsArea2->Add(Units_GarrisonGraphic[loop], 1, wxEXPAND);
	for(short loop = 0;loop < 2;loop++)
	Units_Holder_GraphicsArea2->Add(Units_ComboBox_StandingGraphic[loop], 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	for(short loop = 0;loop < 2;loop++)
	Units_Holder_GraphicsArea2->Add(Units_ComboBox_GarrisonGraphic[loop], 1, wxEXPAND);
	for(short loop = 0;loop < 2;loop++)
	Units_Holder_GraphicsArea3->Add(Units_WalkingGraphic[loop], 1, wxEXPAND);
	for(short loop = 0;loop < 2;loop++)
	Units_Holder_GraphicsArea3->Add(Units_DyingGraphic[loop], 1, wxEXPAND);
	for(short loop = 0;loop < 2;loop++)
	Units_Holder_GraphicsArea3->Add(Units_ComboBox_WalkingGraphic[loop], 1, wxEXPAND);
	for(short loop = 0;loop < 2;loop++)
	Units_Holder_GraphicsArea3->Add(Units_ComboBox_DyingGraphic[loop], 1, wxEXPAND);
	Units_Holder_StandingGraphic->Add(Units_Text_StandingGraphic, 0, wxEXPAND);
	Units_Holder_GarrisonGraphic->Add(Units_Text_GarrisonGraphic, 0, wxEXPAND);
	Units_Holder_WalkingGraphic->Add(Units_Text_WalkingGraphic, 0, wxEXPAND);
	Units_Holder_DyingGraphic->Add(Units_Text_DyingGraphic, 0, wxEXPAND);
	
	Units_Holder_GraphicsArea1->Add(Units_Holder_IconID, 1, wxEXPAND);
	Units_Holder_GraphicsArea1->Add(5, 5);
	Units_Holder_GraphicsArea1->Add(Units_Holder_ConstructionGraphicID, 1, wxEXPAND);
	Units_Holder_GraphicsArea1->Add(5, 5);
	Units_Holder_GraphicsArea1->Add(Units_Holder_SnowGraphicID, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Units_Holder_GraphicsArea1->Add(5, 5);
	Units_Holder_GraphicsArea1->Add(Units_Holder_AttackGraphic, 1, wxEXPAND);
	Units_Holder_GraphicsArea4->Add(Units_Holder_StandingGraphic, 1, wxEXPAND);
	Units_Holder_GraphicsArea4->Add(5, 5);
	Units_Holder_GraphicsArea4->Add(Units_Holder_GarrisonGraphic, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Units_Holder_GraphicsArea5->Add(Units_Holder_WalkingGraphic, 1, wxEXPAND);
	Units_Holder_GraphicsArea5->Add(5, 5);
	Units_Holder_GraphicsArea5->Add(Units_Holder_DyingGraphic, 1, wxEXPAND);
	
	Units_Holder_GraphicsArea6->Add(Units_Holder_GraphicsArea4, 0, wxEXPAND);
	Units_Holder_GraphicsArea6->Add(5, 5);
	Units_Holder_GraphicsArea6->Add(Units_Holder_GraphicsArea2, 0, wxEXPAND);
	Units_Holder_GraphicsArea7->Add(Units_Holder_GraphicsArea5, 0, wxEXPAND);
	Units_Holder_GraphicsArea7->Add(5, 5);
	Units_Holder_GraphicsArea7->Add(Units_Holder_GraphicsArea3, 0, wxEXPAND);
	
	DamageGraphics_Holder_GraphicID->Add(DamageGraphics_Text_GraphicID, 0, wxEXPAND);
	DamageGraphics_Holder_GraphicID->Add(DamageGraphics_GraphicID, 1, wxEXPAND);
	DamageGraphics_Holder_GraphicID->Add(DamageGraphics_ComboBox_GraphicID, 1, wxEXPAND);
	DamageGraphics_Holder_Unknown1->Add(DamageGraphics_Text_Unknown1, 0, wxEXPAND);
	DamageGraphics_Holder_Unknown1->Add(DamageGraphics_Unknown1, 1, wxEXPAND);
	DamageGraphics_Holder_DamagePercent->Add(DamageGraphics_Text_DamagePercent, 0, wxEXPAND);
	DamageGraphics_Holder_DamagePercent->Add(DamageGraphics_DamagePercent, 1, wxEXPAND);
	DamageGraphics_Holder_Unknown2->Add(DamageGraphics_Text_Unknown2, 0, wxEXPAND);
	DamageGraphics_Holder_Unknown2->Add(DamageGraphics_Unknown2, 1, wxEXPAND);
	Units_Holder_DamageGraphics_Data->Add(-1, 5);
	Units_Holder_DamageGraphics_Data->Add(DamageGraphics_Holder_GraphicID, 0, wxEXPAND);
	Units_Holder_DamageGraphics_Data->Add(-1, 5);
	Units_Holder_DamageGraphics_Data->Add(DamageGraphics_Holder_DamagePercent, 0, wxEXPAND);
	Units_Holder_DamageGraphics_Data->Add(-1, 5);
	Units_Holder_DamageGraphics_Data->Add(DamageGraphics_Holder_Unknown1, 0, wxEXPAND);
	Units_Holder_DamageGraphics_Data->Add(-1, 5);
	Units_Holder_DamageGraphics_Data->Add(DamageGraphics_Holder_Unknown2, 0, wxEXPAND);
	
	Units_DamageGraphics_Buttons->Add(Units_DamageGraphics_Add, 1, wxEXPAND);
	Units_DamageGraphics_Buttons->Add(Units_DamageGraphics_Delete, 1, wxEXPAND);
	Units_DamageGraphics_Buttons->Add(Units_DamageGraphics_Copy, 1, wxEXPAND);
	Units_DamageGraphics_Buttons->Add(Units_DamageGraphics_Paste, 1, wxEXPAND);
	
	Units_DamageGraphics->Add(Units_DamageGraphics_Search, 0, wxEXPAND);
	Units_DamageGraphics->Add(Units_DamageGraphics_Search_R, 0, wxEXPAND);
	Units_DamageGraphics->Add(-1, 2);
	Units_DamageGraphics->Add(Units_DamageGraphics_List, 1, wxEXPAND);
	Units_DamageGraphics->Add(-1, 2);
	Units_DamageGraphics->Add(Units_DamageGraphics_Buttons, 0, wxEXPAND);

	Units_Holder_DamageGraphics->Add(Units_DamageGraphics, 1, wxEXPAND);
	Units_Holder_DamageGraphics->Add(Units_Holder_DamageGraphics_Data, 1, wxEXPAND);
	Units_Holder_DamageGraphics->AddStretchSpacer(2);
	
	Units_Holder_GraphicsArea->Add(Units_Holder_GraphicsArea1, 0, wxEXPAND);
	Units_Holder_GraphicsArea->Add(5, 5);
	Units_Holder_GraphicsArea->Add(Units_Holder_GraphicsArea6, 0, wxEXPAND);
	Units_Holder_GraphicsArea->Add(5, 5);
	Units_Holder_GraphicsArea->Add(Units_Holder_GraphicsArea7, 0, wxEXPAND);
	Units_Holder_GraphicsArea->Add(5, 5);
	Units_Holder_GraphicsArea->Add(Units_Holder_DamageGraphics, 0, wxEXPAND);
	
	Units_Grid_StatsArea1->Add(Units_Holder_HitPoints, 1, wxEXPAND);
	Units_Grid_StatsArea1->Add(Units_Holder_Speed, 1, wxEXPAND);
	Units_Grid_StatsArea1->Add(Units_Holder_RotationSpeed, 1, wxEXPAND);
	Units_Grid_StatsArea1->AddStretchSpacer(1);
	Units_Grid_StatsArea1->AddStretchSpacer(1);
	Units_Grid_StatsArea1->Add(Units_Holder_LineOfSight, 1, wxEXPAND);
	Units_Grid_StatsArea1->Add(Units_Holder_SearchRadius, 1, wxEXPAND);
	Units_Grid_StatsArea1->Add(Units_Holder_MaxRange, 1, wxEXPAND);
	Units_Grid_StatsArea1->Add(Units_Holder_MinRange, 1, wxEXPAND);
	Units_Grid_StatsArea1->Add(Units_Holder_DisplayedRange, 1, wxEXPAND);
	
	Units_Holder_Attacks_Data1->Add(Attacks_Holder_Amount, 1, wxEXPAND);
	Units_Holder_Attacks_Data1->Add(5, 5);
	Units_Holder_Attacks_Data1->Add(Attacks_Holder_Class, 3, wxEXPAND);
	Units_Holder_Attacks_Data1->Add(5, 5);
	Units_Grid_Attacks_Data2->Add(Units_Holder_AccuracyPercent, 1, wxEXPAND);
	Units_Grid_Attacks_Data2->Add(Units_Holder_DisplayedAttack, 1, wxEXPAND);
	Units_Grid_Attacks_Data2->Add(Units_Holder_Delay, 1, wxEXPAND);
	Units_Grid_Attacks_Data2->Add(Units_Holder_ReloadTime1, 1, wxEXPAND);
	Units_Grid_Attacks_Data2->Add(Units_Holder_ReloadTime2, 1, wxEXPAND);
	Units_Grid_Attacks_Data2->AddStretchSpacer(1);
	Units_Grid_Attacks_Data2->Add(Units_Holder_BlastRadius, 1, wxEXPAND);
	Units_Grid_Attacks_Data2->Add(Units_Holder_BlastLevel, 1, wxEXPAND);
	
	Units_Holder_Attacks_Data->Add(Units_Holder_Attacks_Data1, 0, wxEXPAND);
	Units_Holder_Attacks_Data->Add(5, 5);
	Units_Holder_Attacks_Data->Add(Units_Grid_Attacks_Data2, 0, wxEXPAND);
	
	Units_Holder_Armors_Data1->Add(Armors_Holder_Amount, 1, wxEXPAND);
	Units_Holder_Armors_Data1->Add(5, 5);
	Units_Holder_Armors_Data1->Add(Armors_Holder_Class, 3, wxEXPAND);
	Units_Holder_Armors_Data1->Add(5, 5);
	Units_Holder_Armors_Data3->Add(Units_Holder_DisplayedMeleeArmour, 0, wxEXPAND);
	Units_Holder_Armors_Data3->Add(5, 5);
	Units_Holder_Armors_Data3->Add(Units_Holder_DisplayedPierceArmour, 0, wxEXPAND);
	
	Units_Holder_Armors_Data2->Add(Units_Holder_Armors_Data3, 1, wxEXPAND);
	Units_Holder_Armors_Data2->AddStretchSpacer(2);
	
	Units_Holder_Armors_Data->Add(Units_Holder_Armors_Data1, 0, wxEXPAND);
	Units_Holder_Armors_Data->Add(5, 5);
	Units_Holder_Armors_Data->Add(Units_Holder_Armors_Data2, 0, wxEXPAND);

	Units_Holder_GarrisonType->Add(Units_Text_GarrisonType, 0, wxEXPAND);
	Units_Holder_GarrisonType->Add(Units_GarrisonType, 1, wxEXPAND);
	Units_Holder_GarrisonType->Add(Units_ComboBox_GarrisonType, 1, wxEXPAND);

	Units_Holder_Attacks->Add(Units_Attacks, 1, wxEXPAND);
	Units_Holder_Attacks->Add(5, 5);
	Units_Holder_Attacks->Add(Units_Holder_Attacks_Data, 3, wxEXPAND);
	Units_Holder_Armors->Add(Units_Armors, 1, wxEXPAND);
	Units_Holder_Armors->Add(5, 5);
	Units_Holder_Armors->Add(Units_Holder_Armors_Data, 3, wxEXPAND);
	Units_Grid_StatsAreaGarrison->Add(Units_Holder_GarrisonCapacity, 1, wxEXPAND);
	Units_Grid_StatsAreaGarrison->Add(Units_Holder_GarrisonType, 2, wxEXPAND);
	Units_Grid_StatsAreaGarrison->Add(Units_Holder_GarrisonHealRate, 1, wxEXPAND);
	Units_Grid_StatsAreaGarrison->Add(Units_Holder_GarrisonRecoveryRate, 1, wxEXPAND);
	Units_Grid_StatsArea2->Add(Units_Holder_ResourceCapacity, 1, wxEXPAND);
	Units_Grid_StatsArea2->Add(Units_Holder_ResourceDecay, 1, wxEXPAND);
	Units_Grid_StatsArea2->Add(Units_Holder_WorkRate, 1, wxEXPAND);
	
	Units_Holder_StatsArea->Add(Units_Grid_StatsArea1, 0, wxEXPAND);
	Units_Holder_StatsArea->Add(-1, 5);
	Units_Holder_StatsArea->Add(Units_Holder_Attacks, 0, wxEXPAND);
	Units_Holder_StatsArea->Add(-1, 5);
	Units_Holder_StatsArea->Add(Units_Holder_Armors, 0, wxEXPAND);
	Units_Holder_StatsArea->Add(-1, 5);
	Units_Holder_StatsArea->Add(Units_Grid_StatsAreaGarrison, 0, wxEXPAND);
	Units_Holder_StatsArea->Add(-1, 5);
	Units_Holder_StatsArea->Add(Units_Grid_StatsArea2, 0, wxEXPAND);
	
	
	Units_Holder_ProjectileUnitID->Add(Units_Text_ProjectileUnitID, 0, wxEXPAND);
	Units_Holder_ProjectileUnitID->Add(Units_ProjectileUnitID, 1, wxEXPAND);
	Units_Holder_ProjectileUnitID->Add(Units_ComboBox_ProjectileUnitID, 1, wxEXPAND);
	Units_Holder_AttackMissileDuplicationUnit->Add(Units_Text_AttackMissileDuplicationUnit, 0, wxEXPAND);
	Units_Holder_AttackMissileDuplicationUnit->Add(Units_AttackMissileDuplicationUnit, 1, wxEXPAND);
	Units_Holder_AttackMissileDuplicationUnit->Add(Units_ComboBox_AttackMissileDuplicationUnit, 1, wxEXPAND);
	Units_Holder_AttackMissileDuplicationGraphic->Add(Units_Text_AttackMissileDuplicationGraphic, 0, wxEXPAND);
	Units_Holder_AttackMissileDuplicationGraphic->Add(Units_AttackMissileDuplicationGraphic, 1, wxEXPAND);
	Units_Holder_AttackMissileDuplicationGraphic->Add(Units_ComboBox_AttackMissileDuplicationGraphic, 1, wxEXPAND);

	Units_Grid_ProjectilesArea1->Add(Units_Holder_ProjectileArc, 1, wxEXPAND);
	Units_Grid_ProjectilesArea1->Add(Units_Holder_StretchMode, 1, wxEXPAND);
	Units_Grid_ProjectilesArea1->Add(Units_Holder_CompensationMode, 1, wxEXPAND);
	Units_Grid_ProjectilesArea1->AddStretchSpacer(1);
	Units_Grid_ProjectilesArea1->Add(Units_Holder_DropAnimationMode, 1, wxEXPAND);
	Units_Grid_ProjectilesArea1->Add(Units_Holder_PenetrationMode, 1, wxEXPAND);
	Units_Grid_ProjectilesArea1->Add(Units_Holder_Unknown24, 1, wxEXPAND);
	Units_Grid_ProjectilesArea2->Add(Units_Holder_ProjectileUnitID, 2, wxEXPAND);
	Units_Grid_ProjectilesArea3->Add(Units_Holder_MissileGraphicDelay, 1, wxEXPAND);
	Units_Grid_ProjectilesArea3->Add(Units_Holder_AttackMissileDuplicationAmount1, 1, wxEXPAND);
	Units_Grid_ProjectilesArea3->Add(Units_Holder_AttackMissileDuplicationAmount2, 1, wxEXPAND);
	Units_Grid_ProjectilesArea2->Add(Units_Holder_AttackMissileDuplicationUnit, 1, wxEXPAND);
	Units_Grid_ProjectilesArea2->Add(Units_Holder_AttackMissileDuplicationGraphic, 1, wxEXPAND);
	
	Units_Holder_ProjectilesArea->Add(Units_Grid_ProjectilesArea2, 0, wxEXPAND);
	Units_Holder_ProjectilesArea->Add(-1, 5);
	Units_Holder_ProjectilesArea->Add(Units_Grid_ProjectilesArea3, 0, wxEXPAND);
	Units_Holder_ProjectilesArea->Add(-1, 5);
	Units_Holder_ProjectilesArea->Add(Units_Holder_AttackMissileDuplicationSpawning, 0, wxEXPAND);
	Units_Holder_ProjectilesArea->Add(-1, 5);
	Units_Holder_ProjectilesArea->Add(Units_Holder_GraphicDisplacement, 0, wxEXPAND);
	Units_Holder_ProjectilesArea->Add(-1, 5);
	Units_Holder_ProjectilesArea->Add(Units_Grid_ProjectilesArea1, 0, wxEXPAND);
	
	Units_Grid_AttributesBoxes1->Add(Units_Holder_Enabled, 1, wxEXPAND);
	Units_Grid_AttributesBoxes1->Add(Units_Holder_HideInEditor, 1, wxEXPAND);
	Units_Grid_AttributesModes1->Add(Units_Holder_VisibleInFog, 1, wxEXPAND);
	Units_Grid_AttributesBoxes1->Add(Units_Holder_DeathMode, 1, wxEXPAND);
	Units_Grid_AttributesBoxes1->Add(Units_Holder_HeroMode, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Units_Grid_AttributesBoxes1->Add(Units_Holder_AirMode, 1, wxEXPAND);
	Units_Grid_AttributesBoxes1->Add(Units_Holder_FlyMode, 1, wxEXPAND);
	Units_Grid_AttributesBoxes1->Add(Units_Holder_SheepConversion, 1, wxEXPAND);
	Units_Grid_AttributesBoxes1->Add(Units_Holder_AnimalMode, 1, wxEXPAND);
	Units_Grid_AttributesBoxes1->Add(Units_Holder_TowerMode, 1, wxEXPAND);
	Units_Grid_AttributesBoxes1->Add(Units_Holder_AdjacentMode, 1, wxEXPAND);
	Units_Grid_AttributesModes1->Add(Units_Holder_BuildingMode, 1, wxEXPAND);
	Units_Grid_AttributesModes1->Add(Units_Holder_PlacementMode, 1, wxEXPAND);
	Units_Grid_AttributesModes1->Add(Units_Holder_InteractionMode, 1, wxEXPAND);
	Units_Grid_AttributesModes1->Add(Units_Holder_MinimapMode, 1, wxEXPAND);
	Units_Grid_AttributesModes1->Add(Units_Holder_VillagerMode, 1, wxEXPAND);
	Units_Grid_AttributesModes1->Add(Units_Holder_BlastType, 1, wxEXPAND);
	Units_Grid_AttributesModes1->Add(Units_Holder_Unknown2, 1, wxEXPAND);
	Units_Grid_AttributesModes1->Add(Units_Holder_Attribute, 1, wxEXPAND);
	Units_Grid_AttributesModes1->Add(Units_Holder_MinTechLevel, 1, wxEXPAND);
	Units_Holder_AttributesTerrain->Add(Units_Holder_PlacementTerrain, 1, wxEXPAND);
	Units_Holder_AttributesTerrain->Add(5, -1);
	Units_Holder_AttributesTerrain->Add(Units_Holder_PlacementBypassTerrain, 1, wxEXPAND);
	Units_Grid_AttributesTerrain->Add(Units_Holder_TerrainRestriction, 1, wxEXPAND);
	Units_Holder_AttributesDropSite->Add(Units_Grid_DropSite, 0, wxEXPAND);
	Units_Holder_AttributesSizes->Add(Units_Holder_SizeRadius, 1, wxEXPAND);
	Units_Holder_AttributesSizes->Add(5, -1);
	Units_Holder_AttributesSizes->Add(Units_Holder_EditorRadius, 1, wxEXPAND);
	Units_Holder_AttributesSizes->Add(5, -1);
	Units_Holder_AttributesSizes->Add(Units_Holder_SelectionRadius, 1, wxEXPAND);
	Units_Grid_AttributesSelection1->Add(Units_Holder_Unselectable, 1, wxEXPAND);
	Units_Grid_AttributesSelection1->Add(Units_Holder_SelectionMask, 1, wxEXPAND);
	Units_Grid_AttributesSelection1->Add(Units_Holder_SelectionShape, 1, wxEXPAND);
	Units_Grid_AttributesSelection1->Add(Units_Holder_SelectionShapeType, 1, wxEXPAND);
	Units_Grid_AttributesSelection1->Add(Units_Holder_SelectionEffect, 1, wxEXPAND);
	Units_Grid_AttributesSelection1->Add(Units_Holder_EditorSelectionColour, 1, wxEXPAND);
	Units_Holder_ResourceStorageHeader->Add(Units_Holder_ResourceStorage[0], 0, wxEXPAND);
	Units_Holder_ResourceStorageHeader->Add(5, 5);
	Units_Holder_ResourceStorageHeader->Add(Units_Holder_ResourceStorage[1], 0, wxEXPAND);
	Units_Holder_ResourceStorageHeader->Add(5, 5);
	Units_Holder_ResourceStorageHeader->Add(Units_Holder_ResourceStorage[2], 0, wxEXPAND);
	Units_Grid_Attributes1->Add(Units_Holder_DeadUnitID, 1, wxEXPAND);
	Units_Grid_Attributes1->Add(Units_Holder_ResearchID, 1, wxEXPAND);
	Units_Grid_Attributes1->Add(Units_Holder_Civ, 1, wxEXPAND);
	Units_Grid_Attributes1->Add(Units_Holder_Unitline, 1, wxEXPAND);
	Units_Holder_AttributesHotKey->Add(Units_Grid_HotKey, 0, wxEXPAND);
	Units_Grid_AttributesTracking->Add(Units_Holder_TrackingUnit, 1, wxEXPAND);
	Units_Grid_AttributesTracking->Add(Units_Holder_TrackingUnitUsed, 1, wxEXPAND);
	Units_Grid_AttributesTracking->Add(Units_Holder_TrackingUnitDensity, 1, wxEXPAND);
	Units_Holder_CostHeader->Add(Units_Holder_CostType, 0, wxEXPAND);
	Units_Holder_CostHeader->Add(5, 5);
	Units_Holder_CostHeader->Add(Units_Holder_CostAmount, 0, wxEXPAND);
	Units_Holder_CostHeader->Add(5, 5);
	Units_Holder_CostHeader->Add(Units_Holder_CostUsed, 0, wxEXPAND);
	Units_Grid_AttributesTrain1->Add(Units_Holder_TrainLocationID, 1, wxEXPAND);
	Units_Grid_AttributesTrain1->Add(Units_Holder_TrainTime, 1, wxEXPAND);
	Units_Grid_AttributesTrain1->Add(Units_Holder_CommandAttribute, 1, wxEXPAND);
	Units_Grid_Attributes3->Add(Units_Holder_StackUnitID, 1, wxEXPAND);
	Units_Grid_AttributesTerrain->Add(Units_Holder_TerrainID, 1, wxEXPAND);
	Units_Holder_AttributesAnnexUnit->Add(Units_Holder_AnnexUnit1, 0, wxEXPAND);
	Units_Holder_AttributesAnnexUnit2->Add(Units_Holder_AnnexUnitMisplacement1, 0, wxEXPAND);
	Units_Grid_Attributes3->Add(Units_Holder_HeadUnit, 1, wxEXPAND);
	Units_Grid_Attributes3->Add(Units_Holder_TransformUnit, 1, wxEXPAND);
	Units_Grid_AttributesTrain1->Add(Units_Holder_ButtonID, 1, wxEXPAND);
	
	Units_Holder_Attributes->Add(Units_Grid_AttributesBoxes1, 0, wxEXPAND);
	Units_Holder_Attributes->Add(-1, 5);
	Units_Holder_Attributes->Add(Units_Grid_AttributesModes1, 0, wxEXPAND);
	Units_Holder_Attributes->Add(-1, 5);
	Units_Holder_Attributes->Add(Units_Grid_Attributes1, 0, wxEXPAND);
	Units_Holder_Attributes->Add(-1, 5);
	Units_Holder_Attributes->Add(Units_Holder_AttributesTerrain, 0, wxEXPAND);
	Units_Holder_Attributes->Add(-1, 5);
	Units_Holder_Attributes->Add(Units_Grid_AttributesTerrain, 0, wxEXPAND);
	Units_Holder_Attributes->Add(-1, 5);
	Units_Holder_Attributes->Add(Units_Holder_AttributesDropSite, 0, wxEXPAND);
	Units_Holder_Attributes->Add(-1, 5);
	Units_Holder_Attributes->Add(Units_Holder_AttributesSizes, 0, wxEXPAND);
	Units_Holder_Attributes->Add(-1, 5);
	Units_Holder_Attributes->Add(Units_Grid_AttributesSelection1, 0, wxEXPAND);
	Units_Holder_Attributes->Add(-1, 5);
	Units_Holder_Attributes->Add(Units_Grid_AttributesTrain1, 0, wxEXPAND);
	Units_Holder_Attributes->Add(-1, 5);
	Units_Holder_Attributes->Add(Units_Holder_CostHeader, 0, wxEXPAND);
	Units_Holder_Attributes->Add(-1, 5);
	Units_Holder_Attributes->Add(Units_Holder_ResourceStorageHeader, 0, wxEXPAND);
	Units_Holder_Attributes->Add(-1, 5);
	Units_Holder_Attributes->Add(Units_Holder_AttributesHotKey, 0, wxEXPAND);
	Units_Holder_Attributes->Add(-1, 5);
	Units_Holder_Attributes->Add(Units_Grid_AttributesTracking, 0, wxEXPAND);
	Units_Holder_Attributes->Add(-1, 5);
	Units_Holder_Attributes->Add(Units_Grid_Attributes3, 0, wxEXPAND);
	Units_Holder_Attributes->Add(-1, 5);
	Units_Holder_Attributes->Add(Units_Holder_AttributesAnnexUnit, 0, wxEXPAND);
	Units_Holder_Attributes->Add(-1, 5);
	Units_Holder_Attributes->Add(Units_Holder_AttributesAnnexUnit2, 0, wxEXPAND);
	Units_Holder_Attributes->Add(-1, 5);
	Units_Holder_Attributes->Add(Units_Holder_Attributes4, 0, wxEXPAND);
	
	Units_Holder_TrainSound1->Add(Units_TrainSound[0], 1, wxEXPAND);
	Units_Holder_TrainSound1->Add(Units_ComboBox_TrainSound[0], 1, wxEXPAND);
	Units_Holder_TrainSound2->Add(Units_TrainSound[1], 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Units_Holder_TrainSound2->Add(Units_ComboBox_TrainSound[1], 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	
	Units_Holder_TrainSound3->Add(Units_Holder_TrainSound1, 1, wxEXPAND);
	Units_Holder_TrainSound3->Add(5, 5);
	Units_Holder_TrainSound3->Add(Units_Holder_TrainSound2, 1, wxEXPAND);
	
	Units_Holder_TrainSound->Add(Units_Text_TrainSound, 0, wxEXPAND);
	Units_Holder_TrainSound->Add(Units_Holder_TrainSound3, 1, wxEXPAND);
	
	Units_Holder_SoundsArea1->Add(Units_Holder_ConstructionSound, 1, wxEXPAND);
	Units_Holder_SoundsArea1->Add(5, 5);
	Units_Holder_SoundsArea1->Add(Units_Holder_TrainSound, 2, wxEXPAND);
	Units_Holder_SoundsArea1->Add(5, 5);
	Units_Holder_SoundsArea1->Add(Units_Holder_SelectionSound, 1, wxEXPAND);
	Units_Grid_SoundsArea2->Add(Units_Holder_AttackSound, 1, wxEXPAND);
	Units_Grid_SoundsArea2->Add(Units_Holder_MoveSound, 1, wxEXPAND);
	Units_Grid_SoundsArea2->Add(Units_Holder_StopSound, 1, wxEXPAND);
	Units_Grid_SoundsArea2->Add(Units_Holder_DyingSound, 1, wxEXPAND);
	
	Units_Holder_SoundsArea->Add(Units_Holder_SoundsArea1, 0, wxEXPAND);
	Units_Holder_SoundsArea->Add(5, 5);
	Units_Holder_SoundsArea->Add(Units_Grid_SoundsArea2, 0, wxEXPAND);
	
	Units_Grid_HPBars->Add(Units_Holder_HPBarHeight1, 1, wxEXPAND);
	Units_Grid_HPBars->Add(Units_Holder_HPBarHeight2, 1, wxEXPAND);
	Units_Holder_MiscArea->Add(Units_Grid_HPBars, 1, wxEXPAND);
	
	Units_Holder_Type10plusUnknowns1->Add(Units_Holder_Unknown9, 2, wxEXPAND);
	Units_Holder_Type10plusUnknowns1->AddStretchSpacer(2);

	Units_Grid_Type10plusUnknowns->Add(Units_Holder_Unknown1, 0, wxEXPAND);
	Units_Grid_Type10plusUnknowns->Add(Units_Holder_Unknown3, 0, wxEXPAND);
	Units_Grid_Type10plusUnknowns->Add(Units_Holder_Unknown3B, 0, wxEXPAND);
	Units_Grid_Type10plusUnknowns->Add(Units_Holder_Unknown3a, 0, wxEXPAND);
	Units_Grid_Type10plusUnknowns->Add(Units_Holder_Unknown4, 0, wxEXPAND);
	Units_Grid_Type10plusUnknowns->Add(Units_Holder_Unknown5, 0, wxEXPAND);
	Units_Grid_Type10plusUnknowns->Add(Units_Holder_Unknown6, 0, wxEXPAND);
	Units_Grid_Type10plusUnknowns->Add(Units_Holder_Unknown7, 0, wxEXPAND);
	Units_Grid_Type10plusUnknowns->Add(Units_Holder_Unknown8, 0, wxEXPAND);
	Units_Holder_Type10plusUnknownArea->Add(Units_Holder_Type10plusUnknowns1, 0, wxEXPAND);
	Units_Holder_Type10plusUnknownArea->Add(-1, 5);
	Units_Holder_Type10plusUnknownArea->Add(Units_Grid_Type10plusUnknowns, 0, wxEXPAND);

	Units_Grid_Type30plusUnknownArea->Add(Units_Holder_Unknown11, 0, wxEXPAND);
	Units_Grid_Type30plusUnknownArea->Add(Units_Holder_Unknown12, 0, wxEXPAND);
	Units_Holder_Type30plusUnknownArea->Add(Units_Holder_Unknown16, 0, wxEXPAND);
	Units_Holder_Type30plusUnknownArea->Add(-1, 5);
	Units_Holder_Type30plusUnknownArea->Add(Units_Grid_Type30plusUnknownArea, 0, wxEXPAND);

	Units_Holder_Type60plusUnknownArea->Add(Units_Holder_Unknown20, 2, wxEXPAND);
	Units_Holder_Type60plusUnknownArea->Add(5, -1);
	Units_Holder_Type60plusUnknownArea->Add(Units_Holder_Unknown21, 1, wxEXPAND);
	Units_Holder_Type60plusUnknownArea->AddStretchSpacer(1);

	Units_Grid_Type70plusUnknownArea->Add(Units_Holder_Unknown26, 0, wxEXPAND);
	Units_Grid_Type70plusUnknownArea->Add(Units_Holder_Unknown28, 0, wxEXPAND);
	Units_Grid_Type70plusUnknownArea->Add(Units_Holder_Unknown29, 0, wxEXPAND);
	Units_Holder_Type70plusUnknownArea->Add(Units_Holder_Unknown27, 0, wxEXPAND);
	Units_Holder_Type70plusUnknownArea->Add(-1, 5);
	Units_Holder_Type70plusUnknownArea->Add(Units_Grid_Type70plusUnknownArea, 0, wxEXPAND);

	Units_Grid_Type80plusUnknownArea->Add(Units_Holder_Unknown31, 0, wxEXPAND);
	Units_Grid_Type80plusUnknownArea->Add(Units_Holder_Unknown31b, 0, wxEXPAND);
	Units_Grid_Type80plusUnknownArea->Add(Units_Holder_Unknown32, 0, wxEXPAND);
	Units_Grid_Type80plusUnknownArea->Add(Units_Holder_Unknown33, 0, wxEXPAND);
	Units_Grid_Type80plusUnknownArea->Add(Units_Holder_Unknown34, 0, wxEXPAND);
	Units_Grid_Type80plusUnknownArea->Add(Units_Holder_Unknown35, 0, wxEXPAND);
	Units_Grid_Type80plusUnknownArea->Add(Units_Holder_Unknown36, 0, wxEXPAND);
	Units_Holder_Type80plusUnknownArea->Add(Units_Holder_Unknown37, 0, wxEXPAND);
	Units_Holder_Type80plusUnknownArea->Add(-1, 5);
	Units_Holder_Type80plusUnknownArea->Add(Units_Grid_Type80plusUnknownArea, 0, wxEXPAND);

	Units_UnitHeads->Add(Units_UnitHeads_List, 1, wxEXPAND);
	Units_UnitCommands_Buttons->Add(Units_UnitCommands_Add, 1, wxEXPAND);
	Units_UnitCommands_Buttons->Add(Units_UnitCommands_Delete, 1, wxEXPAND);
	Units_UnitCommands_Buttons->Add(Units_UnitCommands_Copy, 1, wxEXPAND);
	Units_UnitCommands_Buttons->Add(Units_UnitCommands_Paste, 1, wxEXPAND);
	
	Units_UnitCommands->Add(Units_UnitCommands_Search, 0, wxEXPAND);
	Units_UnitCommands->Add(Units_UnitCommands_Search_R, 0, wxEXPAND);
	Units_UnitCommands->Add(-1, 2);
	Units_UnitCommands->Add(Units_UnitCommands_List, 1, wxEXPAND);
	Units_UnitCommands->Add(-1, 2);
	Units_UnitCommands->Add(Units_UnitCommands_Buttons, 0, wxEXPAND);
	
	Units_CommandHolder_Lists->Add(Units_UnitHeads_Name, 0, wxEXPAND);
	Units_CommandHolder_Lists->Add(Units_UnitHeads, 0, wxEXPAND);
	Units_CommandHolder_Lists->Add(5, 5);
	Units_CommandHolder_Lists->Add(Units_UnitCommands, 0, wxEXPAND);
	Units_CommandHolder_Lists->Add(5, 5);
	Units_CommandHolder_Lists->Add(Units_Holder_Exists, 0, wxEXPAND);
	
	UnitCommands_Holder_1->Add(UnitCommands_Holder_ID, 1, wxEXPAND);
	UnitCommands_Holder_1->Add(5, 5);
	UnitCommands_Holder_1->Add(UnitCommands_Holder_One, 1, wxEXPAND);
	
	UnitCommands_Holder_Types->Add(UnitCommands_Holder_Type, 1, wxEXPAND);
	UnitCommands_Holder_Types->Add(5, -1);
	UnitCommands_Holder_Types->Add(UnitCommands_Holder_SubType, 1, wxEXPAND);
	UnitCommands_Holder_2->Add(UnitCommands_Holder_ClassID, 1, wxEXPAND);
	UnitCommands_Holder_2->Add(5, -1);
	UnitCommands_Holder_2->Add(UnitCommands_Holder_UnitID, 1, wxEXPAND);
	UnitCommands_Holder_Resources->Add(UnitCommands_Holder_ResourceIn, 1, wxEXPAND);
	UnitCommands_Holder_Resources->Add(5, -1);
	UnitCommands_Holder_Resources->Add(UnitCommands_Holder_ResourceOut, 1, wxEXPAND);
	
	Units_CommandHolder_Data1->Add(UnitCommands_Holder_1, 0, wxEXPAND);
	Units_CommandHolder_Data1->Add(-1, 5);
	Units_CommandHolder_Data1->Add(UnitCommands_Holder_Types, 0, wxEXPAND);
	Units_CommandHolder_Data1->Add(UnitCommands_ComboBox_Types, 0, wxEXPAND);
	Units_CommandHolder_Data1->Add(-1, 5);
	Units_CommandHolder_Data1->Add(UnitCommands_Holder_2, 0, wxEXPAND);
	Units_CommandHolder_Data1->Add(-1, 5);
	Units_CommandHolder_Data1->Add(UnitCommands_Holder_Resources, 0, wxEXPAND);
	Units_CommandHolder_Data1->Add(-1, 5);
	Units_CommandHolder_Data1->Add(UnitCommands_Holder_ExecutionRadius, 0, wxEXPAND);
	Units_CommandHolder_Data1->Add(-1, 5);
	Units_CommandHolder_Data1->Add(UnitCommands_Holder_Graphics, 0, wxEXPAND);
	Units_CommandHolder_Data2->Add(UnitCommands_Holder_Unknown1, 0, wxEXPAND);
	Units_CommandHolder_Data2->Add(-1, 5);
	Units_CommandHolder_Data2->Add(UnitCommands_Holder_Unknown2, 0, wxEXPAND);
	Units_CommandHolder_Data2->Add(-1, 5);
	Units_CommandHolder_Data2->Add(UnitCommands_Holder_Unknown3, 0, wxEXPAND);
	Units_CommandHolder_Data2->Add(-1, 5);
	Units_CommandHolder_Data2->Add(UnitCommands_Holder_Unknown4, 0, wxEXPAND);
	Units_CommandHolder_Data2->Add(-1, 5);
	Units_CommandHolder_Data2->Add(UnitCommands_Holder_Unknown5, 0, wxEXPAND);
	Units_CommandHolder_Data2->Add(-1, 5);
	Units_CommandHolder_Data2->Add(UnitCommands_Holder_Unknown6, 0, wxEXPAND);
	Units_CommandHolder_Data2->Add(-1, 5);
	Units_CommandHolder_Data2->Add(UnitCommands_Holder_Unknown7, 0, wxEXPAND);
	Units_CommandHolder_Data2->Add(-1, 5);
	Units_CommandHolder_Data2->Add(UnitCommands_Holder_Unknown8, 0, wxEXPAND);
	Units_CommandHolder_Data2->Add(-1, 5);
	Units_CommandHolder_Data2->Add(UnitCommands_Holder_Unknown9, 0, wxEXPAND);
	Units_CommandHolder_Data2->Add(-1, 5);
	Units_CommandHolder_Data2->Add(UnitCommands_Holder_Unknown10, 0, wxEXPAND);
	Units_CommandHolder_Data2->Add(-1, 5);
	Units_CommandHolder_Data2->Add(UnitCommands_Holder_Unknown11, 0, wxEXPAND);
	Units_CommandHolder_Data2->Add(-1, 5);
	Units_CommandHolder_Data2->Add(UnitCommands_Holder_Unknown12, 0, wxEXPAND);
	Units_CommandHolder_Data2->Add(-1, 5);
	Units_CommandHolder_Data2->Add(UnitCommands_Holder_Unknown13, 0, wxEXPAND);
	Units_CommandHolder_Data2->Add(-1, 5);
	Units_CommandHolder_Data2->Add(UnitCommands_Holder_Unknown14, 0, wxEXPAND);
	
	Units_CommandHolder_Data->Add(Units_CommandHolder_Data1, 3, wxEXPAND);
	Units_CommandHolder_Data->Add(5, -1);
	Units_CommandHolder_Data->Add(Units_CommandHolder_Data2, 2, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	
	Units_Holder_CommandsArea->Add(Units_CommandHolder_Lists, 1, wxEXPAND);
	Units_Holder_CommandsArea->Add(5, -1);
	Units_Holder_CommandsArea->Add(Units_CommandHolder_Data, 3, wxEXPAND);
	
	Units_Holder_UnknownArea->Add(Units_Holder_Type10plusUnknownArea, 0, wxEXPAND);
	Units_Holder_UnknownArea->Add(-1, 5);
	Units_Holder_UnknownArea->Add(Units_Holder_Type30plusUnknownArea, 0, wxEXPAND);
	Units_Holder_UnknownArea->Add(-1, 5);
	Units_Holder_UnknownArea->Add(Units_Holder_Type60plusUnknownArea, 0, wxEXPAND);
	Units_Holder_UnknownArea->Add(-1, 5);
	Units_Holder_UnknownArea->Add(Units_Holder_Type70plusUnknownArea, 0, wxEXPAND);
	Units_Holder_UnknownArea->Add(-1, 5);
	Units_Holder_UnknownArea->Add(Units_Holder_Type80plusUnknownArea, 0, wxEXPAND);
	
	Units_ScrollerWindowsSpace->Add(Units_Holder_TypeArea, 0, wxEXPAND);
	Units_ScrollerWindowsSpace->Add(-1, 10);
	Units_ScrollerWindowsSpace->Add(Units_Holder_LangDLLArea, 0, wxEXPAND);
	Units_ScrollerWindowsSpace->Add(-1, 10);
	Units_ScrollerWindowsSpace->Add(Units_Holder_GraphicsArea, 0, wxEXPAND);
	Units_ScrollerWindowsSpace->Add(-1, 10);
	Units_ScrollerWindowsSpace->Add(Units_Holder_StatsArea, 0, wxEXPAND);
	Units_ScrollerWindowsSpace->Add(-1, 10);
	Units_ScrollerWindowsSpace->Add(Units_Holder_ProjectilesArea, 0, wxEXPAND);
	Units_ScrollerWindowsSpace->Add(-1, 10);
	Units_ScrollerWindowsSpace->Add(Units_Holder_Attributes, 0, wxEXPAND);
	Units_ScrollerWindowsSpace->Add(-1, 10);
	Units_ScrollerWindowsSpace->Add(Units_Holder_SoundsArea, 0, wxEXPAND);
	Units_ScrollerWindowsSpace->Add(-1, 10);
	Units_ScrollerWindowsSpace->Add(Units_Holder_MiscArea, 0, wxEXPAND);
	Units_ScrollerWindowsSpace->Add(-1, 10);
	Units_ScrollerWindowsSpace->Add(Units_Holder_UnknownArea, 0, wxEXPAND);
	Units_ScrollerWindowsSpace->Add(-1, 10);
	Units_ScrollerWindowsSpace->Add(Units_Holder_CommandsArea, 0, wxEXPAND);
	
	Units_ScrollerWindows->Add(Units_ScrollerWindowsSpace, 1, wxEXPAND);
	Units_ScrollerWindows->Add(5, -1);
	
	Units_Scroller->SetSizer(Units_ScrollerWindows);
	Units_Scroller->SetScrollRate(0, 20);
	
	Units_Holder_TopRow->Add(Units_Holder_Type, 3, wxEXPAND);
	Units_Holder_TopRow->Add(15, -1);
	Units_Holder_TopRow->Add(Units_AutoCopyState, 2, wxEXPAND);
	Units_Holder_TopRow->AddStretchSpacer(1);
//	Units_Holder_TopRow->Add(Units_Undo, 0, wxEXPAND);

	Units_MainRow1->Add(Units_Holder_TopRow, 1);
	
	Units_DataArea->Add(-1, 10);
	Units_DataArea->Add(Units_MainRow1, 0, wxEXPAND);
	Units_DataArea->Add(-1, 5);
	Units_DataArea->Add(Units_Scroller, 1, wxEXPAND);
	Units_DataArea->Add(-1, 10);
	
	Units_Main->Add(10, -1);
	Units_Main->Add(Units_ListArea, 1, wxEXPAND);
	Units_Main->Add(10, -1);
	Units_Main->Add(Units_DataArea, 3, wxEXPAND);
	Units_Main->Add(10, -1);

	Units_UnitHeads_List->Enable(false);
	Units_UnitHeads->Show(false);
	AutoCopySettings();
	Units_ID1->Enable(false);
	Units_ID2->Enable(false);
	Units_ID3->Enable(false);
	UnitCommands_ID->Enable(false);

	Tab_Units->SetSizer(Units_Main);
	
	Connect(Units_Units_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitsSearch));
	Connect(Units_Units_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitsSearch));
	for(short loop = 0;loop < 2;loop++)
	{
		Connect(Units_Units_UseAnd[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsSearch));
		Connect(Units_Units_SearchFilters[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSelection_ComboBoxes));
	}
	Connect(Units_AutoCopyState->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::AutoCopyComboBox));
	Connect(Units_Civs_List->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnitSubList));
	Connect(Units_Units_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnitsSelect));
	Connect(Units_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsAdd));
	Connect(Units_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsDelete));
	Connect(Units_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsCopy));
	Connect(Units_SpecialCopy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsSpecialCopy));
	Connect(Units_SpecialPaste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsSpecialPaste));
	Connect(Units_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsPaste));
	Connect(Units_Enable->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsEnable));
	Connect(Units_Disable->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsDisable));
//	Connect(Units_Undo->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUndoing));
	Connect(Units_UnitCommands_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnitCommandsSelect));
	Connect(Units_UnitCommands_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitCommandsSearch));
	Connect(Units_UnitCommands_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitCommandsSearch));
	Connect(Units_UnitCommands_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitCommandsAdd));
	Connect(Units_UnitCommands_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitCommandsDelete));
	Connect(Units_UnitCommands_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitCommandsCopy));
	Connect(Units_UnitCommands_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitCommandsPaste));
	Connect(Units_DamageGraphics_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsSearch));
	Connect(Units_DamageGraphics_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsSearch));
	Connect(Units_DamageGraphics_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsSelect));
	Connect(Units_DamageGraphics_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsAdd));
	Connect(Units_DamageGraphics_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsDelete));
	Connect(Units_DamageGraphics_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsCopy));
	Connect(Units_DamageGraphics_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsPaste));
	Connect(Units_Attacks_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksSearch));
	Connect(Units_Attacks_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksSearch));
	Connect(Units_Attacks_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksSelect));
	Connect(Units_Attacks_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksAdd));
	Connect(Units_Attacks_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksDelete));
	Connect(Units_Attacks_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksCopy));
	Connect(Units_Attacks_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksPaste));
	Connect(Units_Armors_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsSearch));
	Connect(Units_Armors_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsSearch));
	Connect(Units_Armors_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsSelect));
	Connect(Units_Armors_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsAdd));
	Connect(Units_Armors_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsDelete));
	Connect(Units_Armors_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsCopy));
	Connect(Units_Armors_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsPaste));
	Connect(UnitCommands_ComboBox_Types->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSelection_ComboBoxes));
	
//	Listing and Auto Copy

	Units_Type->Connect(Units_Type->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_TextControls), NULL, this);
	Connect(Units_ComboBox_Type->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSelection_ComboBoxes));

	for(short loop = 0;loop < 2;loop++)
	{
		Units_Unknown20[loop]->Connect(Units_Unknown20[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	}
	Units_BlastType->Connect(Units_BlastType->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_Unknown2->Connect(Units_Unknown2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_DeathMode->Connect(Units_DeathMode->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_CheckBoxByte), NULL, this);
	Units_GarrisonCapacity->Connect(Units_GarrisonCapacity->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_PlacementMode->Connect(Units_PlacementMode->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_AirMode->Connect(Units_AirMode->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_CheckBoxByte), NULL, this);
	Units_HideInEditor->Connect(Units_HideInEditor->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_CheckBoxByte), NULL, this);
	Units_BuildingMode->Connect(Units_BuildingMode->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_CheckBoxByte), NULL, this);
	Units_VisibleInFog->Connect(Units_VisibleInFog->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_FlyMode->Connect(Units_FlyMode->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_CheckBoxByte), NULL, this);
	Units_InteractionMode->Connect(Units_InteractionMode->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_MinimapMode->Connect(Units_MinimapMode->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_Unknown3a->Connect(Units_Unknown3a->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_Unknown4->Connect(Units_Unknown4->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_Unknown5->Connect(Units_Unknown5->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_Unknown6->Connect(Units_Unknown6->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_Unknown7->Connect(Units_Unknown7->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_Unknown8->Connect(Units_Unknown8->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_SelectionMask->Connect(Units_SelectionMask->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_SelectionShapeType->Connect(Units_SelectionShapeType->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_SelectionShape->Connect(Units_SelectionShape->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_Attribute->Connect(Units_Attribute->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_Civ->Connect(Units_Civ->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxByte), NULL, this);
	for(short loop = 0;loop < 2;loop++)
	Units_Unknown9[loop]->Connect(Units_Unknown9[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_SelectionEffect->Connect(Units_SelectionEffect->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_EditorSelectionColour->Connect(Units_EditorSelectionColour->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_MinTechLevel->Connect(Units_MinTechLevel->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_Unknown11->Connect(Units_Unknown11->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_TrackingUnitUsed->Connect(Units_TrackingUnitUsed->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	for(short loop = 0;loop < 17;loop++)
	Units_Unknown16[loop]->Connect(Units_Unknown16[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_VillagerMode->Connect(Units_VillagerMode->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_AnimalMode->Connect(Units_AnimalMode->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_CheckBoxByte), NULL, this);
	Units_AccuracyPercent->Connect(Units_AccuracyPercent->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
	Units_BlastLevel->Connect(Units_BlastLevel->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_StretchMode->Connect(Units_StretchMode->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_CompensationMode->Connect(Units_CompensationMode->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_DropAnimationMode->Connect(Units_DropAnimationMode->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_PenetrationMode->Connect(Units_PenetrationMode->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_Unknown24->Connect(Units_Unknown24->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_ButtonID->Connect(Units_ButtonID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_Unknown26->Connect(Units_Unknown26->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_Unknown28->Connect(Units_Unknown28->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_MissileGraphicDelay->Connect(Units_MissileGraphicDelay->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_HeroMode->Connect(Units_HeroMode->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_CheckBoxByte), NULL, this);
	Units_AttackMissileDuplicationAmount2->Connect(Units_AttackMissileDuplicationAmount2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_Unknown29->Connect(Units_Unknown29->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_Unknown33->Connect(Units_Unknown33->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_GarrisonType->Connect(Units_GarrisonType->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxByte), NULL, this);
	for(short loop = 0;loop < 6;loop++)
	Units_Unknown37[loop]->Connect(Units_Unknown37[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);

	for(short loop = 0;loop < 2;loop++)
	{
		Units_StandingGraphic[loop]->Connect(Units_StandingGraphic[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
		Units_DyingGraphic[loop]->Connect(Units_DyingGraphic[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
		Units_TrainSound[loop]->Connect(Units_TrainSound[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
		Units_PlacementBypassTerrain[loop]->Connect(Units_PlacementBypassTerrain[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
		Units_PlacementTerrain[loop]->Connect(Units_PlacementTerrain[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
		Units_WalkingGraphic[loop]->Connect(Units_WalkingGraphic[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
		Units_DropSite[loop]->Connect(Units_DropSite[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
		Units_GarrisonGraphic[loop]->Connect(Units_GarrisonGraphic[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	}
	for(short loop = 0;loop < 3;loop++)
	{
		Units_CostType[loop]->Connect(Units_CostType[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
		Units_CostAmount[loop]->Connect(Units_CostAmount[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
		Units_CostUsed[loop]->Connect(Units_CostUsed[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_CheckBoxShort), NULL, this);
		Units_Unknown27[loop]->Connect(Units_Unknown27[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
	}
	for(short loop = 0;loop < 4;loop++)
	{
		Units_HotKey[loop]->Connect(Units_HotKey[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
		Units_AnnexUnit[loop]->Connect(Units_AnnexUnit[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	}
	Units_LanguageDllName->Connect(Units_LanguageDllName->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_UnShort), NULL, this);
	Units_LanguageDllCreation->Connect(Units_LanguageDllCreation->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_UnShort), NULL, this);
	Units_Class->Connect(Units_Class->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	Units_HitPoints->Connect(Units_HitPoints->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
	Units_DeadUnitID->Connect(Units_DeadUnitID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	Units_IconID->Connect(Units_IconID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
	Units_Unknown1->Connect(Units_Unknown1->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
	Units_Enabled->Connect(Units_Enabled->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_CheckBoxShort), NULL, this);
	Units_TerrainRestriction->Connect(Units_TerrainRestriction->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	Units_ResourceCapacity->Connect(Units_ResourceCapacity->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
	Units_CommandAttribute->Connect(Units_CommandAttribute->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
	Units_LanguageDllHelp->Connect(Units_LanguageDllHelp->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_UnShort), NULL, this);
	Units_SelectionSound->Connect(Units_SelectionSound->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	Units_DyingSound->Connect(Units_DyingSound->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	Units_AttackSound->Connect(Units_AttackSound->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	Units_Unitline->Connect(Units_Unitline->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	Units_TrackingUnit->Connect(Units_TrackingUnit->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	Units_SheepConversion->Connect(Units_SheepConversion->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_CheckBoxShortUnitSheepConversion), NULL, this);
	Units_MoveSound->Connect(Units_MoveSound->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	Units_StopSound->Connect(Units_StopSound->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	Units_Unknown21->Connect(Units_Unknown21->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
	Units_ProjectileUnitID->Connect(Units_ProjectileUnitID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	Units_TowerMode->Connect(Units_TowerMode->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_CheckBoxByte), NULL, this);
	Units_Delay->Connect(Units_Delay->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
	Units_AttackGraphic->Connect(Units_AttackGraphic->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	Units_DisplayedMeleeArmour->Connect(Units_DisplayedMeleeArmour->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
	Units_DisplayedAttack->Connect(Units_DisplayedAttack->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
	Units_TrainTime->Connect(Units_TrainTime->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
	Units_TrainLocationID->Connect(Units_TrainLocationID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	Units_DisplayedPierceArmour->Connect(Units_DisplayedPierceArmour->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
	Units_ConstructionGraphicID->Connect(Units_ConstructionGraphicID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	Units_SnowGraphicID->Connect(Units_SnowGraphicID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	Units_AdjacentMode->Connect(Units_AdjacentMode->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_CheckBoxShort), NULL, this);
	Units_Unknown31->Connect(Units_Unknown31->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	Units_Unknown31b->Connect(Units_Unknown31b->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_CheckBoxByte), NULL, this);
	Units_StackUnitID->Connect(Units_StackUnitID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	Units_TerrainID->Connect(Units_TerrainID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	Units_Unknown32->Connect(Units_Unknown32->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
	Units_ResearchID->Connect(Units_ResearchID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	Units_HeadUnit->Connect(Units_HeadUnit->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	Units_TransformUnit->Connect(Units_TransformUnit->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	Units_Unknown34->Connect(Units_Unknown34->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
	Units_ConstructionSound->Connect(Units_ConstructionSound->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	Units_Unknown36->Connect(Units_Unknown36->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);

	for(short loop = 0;loop < 2;loop++)
	{
		Units_SizeRadius[loop]->Connect(Units_SizeRadius[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
		Units_EditorRadius[loop]->Connect(Units_EditorRadius[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
		Units_SelectionRadius[loop]->Connect(Units_SelectionRadius[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
	}
	for(short loop = 0;loop < 3;loop++)
	{
		Units_GraphicDisplacement[loop]->Connect(Units_GraphicDisplacement[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
		Units_AttackMissileDuplicationSpawning[loop]->Connect(Units_AttackMissileDuplicationSpawning[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
	}
	for(short loop = 0;loop < 4;loop++)
	{
		for(short loop2 = 0;loop2 < 2;loop2++)
		Units_AnnexUnitMisplacement[loop][loop2]->Connect(Units_AnnexUnitMisplacement[loop][loop2]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
	}
	Units_LineOfSight->Connect(Units_LineOfSight->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
	Units_HPBarHeight1->Connect(Units_HPBarHeight1->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
	Units_ResourceDecay->Connect(Units_ResourceDecay->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
	Units_Unknown3->Connect(Units_Unknown3->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
	Units_Unknown3B->Connect(Units_Unknown3B->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
	Units_HPBarHeight2->Connect(Units_HPBarHeight2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
	Units_Speed->Connect(Units_Speed->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
	Units_RotationSpeed->Connect(Units_RotationSpeed->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
	Units_TrackingUnitDensity->Connect(Units_TrackingUnitDensity->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
	Units_Unknown12->Connect(Units_Unknown12->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
	Units_SearchRadius->Connect(Units_SearchRadius->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
	Units_WorkRate->Connect(Units_WorkRate->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
	Units_MaxRange->Connect(Units_MaxRange->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
	Units_BlastRadius->Connect(Units_BlastRadius->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
	Units_ReloadTime1->Connect(Units_ReloadTime1->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
	Units_MinRange->Connect(Units_MinRange->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
	Units_GarrisonRecoveryRate->Connect(Units_GarrisonRecoveryRate->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
	Units_DisplayedRange->Connect(Units_DisplayedRange->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
	Units_ReloadTime2->Connect(Units_ReloadTime2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
	Units_ProjectileArc->Connect(Units_ProjectileArc->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
	Units_AttackMissileDuplicationAmount1->Connect(Units_AttackMissileDuplicationAmount1->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
	Units_GarrisonHealRate->Connect(Units_GarrisonHealRate->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);

	Units_Unselectable->Connect(Units_Unselectable->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_CheckBoxByte), NULL, this);
	
	Units_AttackMissileDuplicationUnit->Connect(Units_AttackMissileDuplicationUnit->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxLong), NULL, this);
	Units_AttackMissileDuplicationGraphic->Connect(Units_AttackMissileDuplicationGraphic->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxLong), NULL, this);
	Units_Unknown35->Connect(Units_Unknown35->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Long), NULL, this);

	Units_Name->Connect(Units_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_String), NULL, this);
	Units_Name2->Connect(Units_Name2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_String), NULL, this);

	for(short loop = 0;loop < 3;loop++)
	{
		ResourceStorage_Type[loop]->Connect(ResourceStorage_Type[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
		ResourceStorage_Amount[loop]->Connect(ResourceStorage_Amount[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
		ResourceStorage_Enabled[loop]->Connect(ResourceStorage_Enabled[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	}

	DamageGraphics_GraphicID->Connect(DamageGraphics_GraphicID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	DamageGraphics_DamagePercent->Connect(DamageGraphics_DamagePercent->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	DamageGraphics_Unknown1->Connect(DamageGraphics_Unknown1->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	DamageGraphics_Unknown2->Connect(DamageGraphics_Unknown2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	
	Attacks_Class->Connect(Attacks_Class->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	Attacks_Amount->Connect(Attacks_Amount->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
	Armors_Class->Connect(Armors_Class->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	Armors_Amount->Connect(Armors_Amount->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);

	UnitCommands_One->Connect(UnitCommands_One->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
	UnitCommands_Type->Connect(UnitCommands_Type->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
	UnitCommands_SubType->Connect(UnitCommands_SubType->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
	UnitCommands_ClassID->Connect(UnitCommands_ClassID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	UnitCommands_UnitID->Connect(UnitCommands_UnitID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	UnitCommands_Unknown2->Connect(UnitCommands_Unknown2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
	UnitCommands_ResourceIn->Connect(UnitCommands_ResourceIn->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	UnitCommands_ResourceOut->Connect(UnitCommands_ResourceOut->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);
	UnitCommands_Unknown3->Connect(UnitCommands_Unknown3->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
	UnitCommands_Unknown12->Connect(UnitCommands_Unknown12->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
	UnitCommands_Unknown13->Connect(UnitCommands_Unknown13->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Short), NULL, this);
	for(short loop = 0;loop < 6;loop++)
	UnitCommands_Graphics[loop]->Connect(UnitCommands_Graphics[loop]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_ComboBoxShort), NULL, this);

	UnitCommands_Unknown4->Connect(UnitCommands_Unknown4->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
	UnitCommands_ExecutionRadius->Connect(UnitCommands_ExecutionRadius->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
	UnitCommands_Unknown5->Connect(UnitCommands_Unknown5->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
	UnitCommands_Unknown7->Connect(UnitCommands_Unknown7->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Float), NULL, this);
	
	UnitCommands_Unknown1->Connect(UnitCommands_Unknown1->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	UnitCommands_Unknown6->Connect(UnitCommands_Unknown6->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	UnitCommands_Unknown8->Connect(UnitCommands_Unknown8->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	UnitCommands_Unknown9->Connect(UnitCommands_Unknown9->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	UnitCommands_Unknown10->Connect(UnitCommands_Unknown10->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	UnitCommands_Unknown11->Connect(UnitCommands_Unknown11->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);
	UnitCommands_Unknown14->Connect(UnitCommands_Unknown14->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_AutoCopy_Byte), NULL, this);

//	Combo/Check Boxes updating AutoCopy linkings

	for(short loop = 0;loop < 2;loop++)
	{
		Units_ComboBox_StandingGraphic[loop]->Connect(Units_ComboBox_StandingGraphic[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
		Units_ComboBox_DyingGraphic[loop]->Connect(Units_ComboBox_DyingGraphic[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
		Units_ComboBox_TrainSound[loop]->Connect(Units_ComboBox_TrainSound[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
		Units_ComboBox_PlacementBypassTerrain[loop]->Connect(Units_ComboBox_PlacementBypassTerrain[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
		Units_ComboBox_PlacementTerrain[loop]->Connect(Units_ComboBox_PlacementTerrain[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
		Units_ComboBox_WalkingGraphic[loop]->Connect(Units_ComboBox_WalkingGraphic[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
		Units_ComboBox_DropSite[loop]->Connect(Units_ComboBox_DropSite[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
		Units_ComboBox_GarrisonGraphic[loop]->Connect(Units_ComboBox_GarrisonGraphic[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
		Units_ComboBox_Class[loop]->Connect(Units_ComboBox_Class[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
		Attacks_ComboBox_Class[loop]->Connect(Attacks_ComboBox_Class[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
	}
	for(short loop = 0;loop < 3;loop++)
	{
		Units_ComboBox_CostType[loop]->Connect(Units_ComboBox_CostType[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
		ResourceStorage_ComboBox_Type[loop]->Connect(ResourceStorage_ComboBox_Type[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
		Units_CheckBox_CostUsed[loop]->Connect(Units_CheckBox_CostUsed[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_CheckBoxShort), NULL, this);
	}
	for(short loop = 0;loop < 4;loop++)
	{
		Units_ComboBox_AnnexUnit[loop]->Connect(Units_ComboBox_AnnexUnit[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
	}
	for(short loop = 0;loop < 6;loop++)
	{
		UnitCommands_ComboBox_Graphics[loop]->Connect(UnitCommands_ComboBox_Graphics[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
	}
	Units_ComboBox_GarrisonType->Connect(Units_ComboBox_GarrisonType->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxByte), NULL, this);
	Units_ComboBox_DeadUnitID->Connect(Units_ComboBox_DeadUnitID->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
	Units_ComboBox_TerrainRestriction->Connect(Units_ComboBox_TerrainRestriction->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
	Units_ComboBox_SelectionSound->Connect(Units_ComboBox_SelectionSound->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
	Units_ComboBox_DyingSound->Connect(Units_ComboBox_DyingSound->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
	Units_ComboBox_AttackSound->Connect(Units_ComboBox_AttackSound->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
	Units_ComboBox_Unitline->Connect(Units_ComboBox_Unitline->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
	Units_ComboBox_TrackingUnit->Connect(Units_ComboBox_TrackingUnit->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
	Units_ComboBox_MoveSound->Connect(Units_ComboBox_MoveSound->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
	Units_ComboBox_StopSound->Connect(Units_ComboBox_StopSound->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
	Units_ComboBox_ProjectileUnitID->Connect(Units_ComboBox_ProjectileUnitID->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
	Units_ComboBox_AttackGraphic->Connect(Units_ComboBox_AttackGraphic->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
	Units_ComboBox_TrainLocationID->Connect(Units_ComboBox_TrainLocationID->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
	Units_ComboBox_ConstructionGraphicID->Connect(Units_ComboBox_ConstructionGraphicID->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
	Units_ComboBox_SnowGraphicID->Connect(Units_ComboBox_SnowGraphicID->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
	Units_ComboBox_StackUnitID->Connect(Units_ComboBox_StackUnitID->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
	Units_ComboBox_TerrainID->Connect(Units_ComboBox_TerrainID->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
	Units_ComboBox_ResearchID->Connect(Units_ComboBox_ResearchID->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
	Units_ComboBox_HeadUnit->Connect(Units_ComboBox_HeadUnit->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
	Units_ComboBox_TransformUnit->Connect(Units_ComboBox_TransformUnit->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
	Units_ComboBox_ConstructionSound->Connect(Units_ComboBox_ConstructionSound->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
	Units_ComboBox_AttackMissileDuplicationUnit->Connect(Units_ComboBox_AttackMissileDuplicationUnit->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxLong), NULL, this);
	Units_ComboBox_AttackMissileDuplicationGraphic->Connect(Units_ComboBox_AttackMissileDuplicationGraphic->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxLong), NULL, this);
	Units_ComboBox_Civ->Connect(Units_ComboBox_Civ->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxByte), NULL, this);
	DamageGraphics_ComboBox_GraphicID->Connect(DamageGraphics_ComboBox_GraphicID->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
	UnitCommands_ComboBox_UnitID->Connect(UnitCommands_ComboBox_UnitID->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
	UnitCommands_ComboBox_ResourceIn->Connect(UnitCommands_ComboBox_ResourceIn->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);
	UnitCommands_ComboBox_ResourceOut->Connect(UnitCommands_ComboBox_ResourceOut->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_ComboBoxShort), NULL, this);

	Units_CheckBox_DeathMode->Connect(Units_CheckBox_DeathMode->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_CheckBoxByte), NULL, this);
	Units_CheckBox_AirMode->Connect(Units_CheckBox_AirMode->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_CheckBoxByte), NULL, this);
	Units_CheckBox_HideInEditor->Connect(Units_CheckBox_HideInEditor->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_CheckBoxByte), NULL, this);
	Units_CheckBox_FlyMode->Connect(Units_CheckBox_FlyMode->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_CheckBoxByte), NULL, this);
	Units_CheckBox_HeroMode->Connect(Units_CheckBox_HeroMode->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_CheckBoxByte), NULL, this);
	Units_CheckBox_Enabled->Connect(Units_CheckBox_Enabled->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_CheckBoxShort), NULL, this);
	Units_CheckBox_SheepConversion->Connect(Units_CheckBox_SheepConversion->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_CheckBoxShortUnitSheepConversion), NULL, this);
	Units_CheckBox_Unselectable->Connect(Units_CheckBox_Unselectable->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_CheckBoxByte), NULL, this);
	Units_CheckBox_AnimalMode->Connect(Units_CheckBox_AnimalMode->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_CheckBoxByte), NULL, this);
	Units_CheckBox_TowerMode->Connect(Units_CheckBox_TowerMode->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_CheckBoxByte), NULL, this);
	Units_CheckBox_AdjacentMode->Connect(Units_CheckBox_AdjacentMode->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_CheckBoxShort), NULL, this);
	Units_CheckBox_Unknown31b->Connect(Units_CheckBox_Unknown31b->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdate_AutoCopy_CheckBoxByte), NULL, this);

}

void AGE_Frame::AutoCopySettings()
{
	if(AutoCopy == MenuOption_NoAuto)
	{
		Units_AutoCopyState->SetSelection(0);
	}
	else if(AutoCopy == MenuOption_Include)
	{
		Units_AutoCopyState->SetSelection(1);
	}
	else if(AutoCopy == MenuOption_Exclude)
	{
		Units_AutoCopyState->SetSelection(2);
	}
}

void AGE_Frame::AutoCopyComboBox(wxCommandEvent& Event)
{
	switch(Units_AutoCopyState->GetSelection())
	{
		case 0:
			AutoCopy = MenuOption_NoAuto;
			break;
		case 1:
			AutoCopy = MenuOption_Include;
			break;
		case 2:
			AutoCopy = MenuOption_Exclude;
			break;
	}
	SubMenu_CivAutoCopy->Check(AutoCopy, true);
}
