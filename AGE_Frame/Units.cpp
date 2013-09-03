#include "../AGE_Frame.h"
using boost::lexical_cast;

//const wxString AGE_Frame::CIVCOUNTWARNING = "Fewer civilizations copied than needed to paste!\nPasting data to extra civilizations from civilization 1!";

void AGE_Frame::OnUnitSubList(wxCommandEvent &Event)
{
	short Selection = Units_Civs_List->GetSelection();
	if(Selection == wxNOT_FOUND) return;

	ListUnits(Selection, false);	// List units by selected civ.
}

string AGE_Frame::GetUnitName(short Index, short civ, bool Filter)
{
	string Name = "";

	if(GenieFile->Civs[civ].UnitPointers[Index] == 0)
	{
		return "*Disabled*";
	}
	if(Filter)
	{
		short Selection[2];
		for(short loop = 0; loop < 2; loop++)
		Selection[loop] = Units_Units_SearchFilters[loop]->GetSelection();
		short UnitType = (short)GenieFile->Civs[civ].Units[Index].Type;

		if(Selection[0] > 1)
		for(short loop = 0; loop < 2; loop++)
		{
			switch(Selection[loop])
			{
				case 2: // Type
					Name += "T "+lexical_cast<string>(UnitType);
					break;
				case 3: // Class
					Name += "C "+lexical_cast<string>(GenieFile->Civs[civ].Units[Index].Class);
					break;
				case 4: // Terrain Restriction
					Name += "TR "+lexical_cast<string>(GenieFile->Civs[civ].Units[Index].TerrainRestriction);
					break;
				case 5: // Dead Unit
					Name += "DU "+lexical_cast<string>(GenieFile->Civs[civ].Units[Index].DeadUnitID);
					break;
				case 6: // Max Range
					switch(UnitType)
					{
						case 60:
						case 70:
						case 80:
							Name += "MR "+lexical_cast<string>(GenieFile->Civs[civ].Units[Index].Projectile.MaxRange);
							break;
						default:
							Name += "MR -1";
					}
					break;
				case 7: // Train Location
					switch(UnitType)
					{
						case 70:
						case 80:
							Name += "TL "+lexical_cast<string>(GenieFile->Civs[civ].Units[Index].Creatable.TrainLocationID);
							break;
						default:
							Name += "TL -1";
					}
					break;
				case 8: // Attacks
					switch(UnitType)
					{
						case 60:
						case 70:
						case 80:
							Name += "AtC "+lexical_cast<string>(GenieFile->Civs[civ].Units[Index].Projectile.Attacks.size());
							break;
						default:
							Name += "AtC -1";
					}
					break;
				case 9: // Armors
					switch(UnitType)
					{
						case 60:
						case 70:
						case 80:
							Name += "ArC "+lexical_cast<string>(GenieFile->Civs[civ].Units[Index].Projectile.Armours.size());
							break;
						default:
							Name += "ArC -1";
					}
					break;
				case 10: // Commands
					switch(UnitType)
					{
						case 40:
						case 60:
						case 70:
						case 80:
							if(GenieVersion <= genie::GV_AoKA)
							Name += "CC "+lexical_cast<string>(GenieFile->Civs[civ].Units[Index].Bird.Commands.size());
							else
							Name += "CC "+lexical_cast<string>(GenieFile->UnitHeaders[Index].Commands.size());
							break;
						default:
							Name += "CC -1";
					}
					break;
				case 11: // Pointer
					Name = lexical_cast<string>(GenieFile->Civs[civ].UnitPointers[Index]);
					break;
			}
			Name += ", ";
			if(Selection[loop+1] < 2) break;
		}
		if(Selection[0] == 1) goto InternalName;
	}

	if(!LangDLLstring(GenieFile->Civs[civ].Units[Index].LanguageDLLName, 2).empty())
	{
		return Name + LangDLLstring(GenieFile->Civs[civ].Units[Index].LanguageDLLName, 64);
	}
InternalName:
	if(!GenieFile->Civs[civ].Units[Index].Name.empty())
	{
		return Name + GenieFile->Civs[civ].Units[Index].Name;
	}
	return Name + "New Unit";
}

void AGE_Frame::OnUnitsSearch(wxCommandEvent &Event)
{
	short Selection = Units_Civs_List->GetSelection();
	if(Selection == wxNOT_FOUND) return;

	ListUnits(Selection, false);
}

void AGE_Frame::ListUnits(short civ, bool Sized)
{
	searchText = Units_Units_Search->GetValue().Lower();
	excludeText = Units_Units_Search_R->GetValue().Lower();
	for(short loop = 0; loop < 2; loop++)
	UseAnd[loop] = Units_Units_UseAnd[loop]->GetValue();

	Units_Civs_List->SetSelection(civ);

	auto Selections = Units_Units_List->GetSelections(Items);
	Units_Units_List->Clear();

	std::array<short, 64> SavedIDs;
	if(Sized)
	{
		SavedIDs[0] = Units_ComboBox_DeadUnitID->GetSelection();
		SavedIDs[1] = Units_ComboBox_ProjectileUnitID->GetSelection();
		for(short loop = 0; loop < 2; loop++)
		SavedIDs[loop+2] = Units_ComboBox_DropSite[loop]->GetSelection();
		SavedIDs[4] = Units_ComboBox_AttackMissileDuplicationUnit->GetSelection();
		SavedIDs[5] = Units_ComboBox_TrackingUnit->GetSelection();
		SavedIDs[6] = Units_ComboBox_TrainLocationID->GetSelection();
		SavedIDs[7] = Units_ComboBox_StackUnitID->GetSelection();
		for(short loop = 0; loop < 4; loop++)
		{
			SavedIDs[loop+8] = Units_ComboBox_AnnexUnit[loop]->GetSelection();
			SavedIDs[loop+30] = TechTrees_ComboBox_Unit[loop]->GetSelection();
		}
		SavedIDs[12] = Units_ComboBox_HeadUnit->GetSelection();
		SavedIDs[13] = Units_ComboBox_TransformUnit->GetSelection();
		SavedIDs[14] = Research_ComboBox_ResearchLocation->GetSelection();
		SavedIDs[15] = Effects_ComboBox_UnitsA->GetSelection();
		SavedIDs[16] = Effects_ComboBox_UnitsB->GetSelection();
		SavedIDs[17] = UnitCommands_ComboBox_UnitID->GetSelection();
		SavedIDs[18] = UnitLineUnits_ComboBox_Units->GetSelection();
		SavedIDs[19] = TechTrees_Ages_ComboBox_Building->GetSelection();
		SavedIDs[20] = TechTrees_Ages_ComboBox_Unit->GetSelection();
		SavedIDs[21] = TechTrees_Buildings_ComboBox_ID->GetSelection();
		SavedIDs[22] = TechTrees_Buildings_ComboBox_Building->GetSelection();
		SavedIDs[23] = TechTrees_Buildings_ComboBox_Unit->GetSelection();
		SavedIDs[24] = TechTrees_Units_ComboBox_ID->GetSelection();
		SavedIDs[25] = TechTrees_Units_ComboBox_UpperBuilding->GetSelection();
		SavedIDs[26] = TechTrees_Units_ComboBox_Unit->GetSelection();
		SavedIDs[27] = TechTrees_Researches_ComboBox_UpperBuilding->GetSelection();
		SavedIDs[28] = TechTrees_Researches_ComboBox_Building->GetSelection();
		SavedIDs[29] = TechTrees_Researches_ComboBox_Unit->GetSelection();
		for(short loop = 0; loop < 30; loop++)
		SavedIDs[loop+34] = Terrains_ComboBox_TerrainUnitID[loop]->GetSelection();

		Units_ComboBox_DeadUnitID->Clear();
		Units_ComboBox_ProjectileUnitID->Clear();
		Units_ComboBox_AttackMissileDuplicationUnit->Clear();
		for(short loop = 0; loop < 2; loop++)
		Units_ComboBox_DropSite[loop]->Clear();
		Units_ComboBox_TrackingUnit->Clear();
		Units_ComboBox_TrainLocationID->Clear();
		Units_ComboBox_StackUnitID->Clear();
		for(short loop = 0; loop < 4; loop++)
		{
			Units_ComboBox_AnnexUnit[loop]->Clear();
			TechTrees_ComboBox_Unit[loop]->Clear();
		}
		Units_ComboBox_HeadUnit->Clear();
		Units_ComboBox_TransformUnit->Clear();
		Research_ComboBox_ResearchLocation->Clear();
		Effects_ComboBox_UnitsA->Clear();
		Effects_ComboBox_UnitsB->Clear();
		UnitCommands_ComboBox_UnitID->Clear();
		UnitLineUnits_ComboBox_Units->Clear();
		TechTrees_Ages_ComboBox_Building->Clear();
		TechTrees_Ages_ComboBox_Unit->Clear();
		TechTrees_Buildings_ComboBox_ID->Clear();
		TechTrees_Buildings_ComboBox_Building->Clear();
		TechTrees_Buildings_ComboBox_Unit->Clear();
		TechTrees_Units_ComboBox_ID->Clear();
		TechTrees_Units_ComboBox_UpperBuilding->Clear();
		TechTrees_Units_ComboBox_Unit->Clear();
		TechTrees_Researches_ComboBox_UpperBuilding->Clear();
		TechTrees_Researches_ComboBox_Building->Clear();
		TechTrees_Researches_ComboBox_Unit->Clear();
		for(short loop = 0; loop < 30; loop++)
		Terrains_ComboBox_TerrainUnitID[loop]->Clear();

		for(auto &ID: SavedIDs)
		{
			if(ID == wxNOT_FOUND) ID = 0;
		}

		Units_ComboBox_DeadUnitID->Append("-1 - None");
		Units_ComboBox_ProjectileUnitID->Append("-1 - None");
		Units_ComboBox_AttackMissileDuplicationUnit->Append("-1 - None");
		for(short loop = 0; loop < 2; loop++)
		Units_ComboBox_DropSite[loop]->Append("-1 - None");
		Units_ComboBox_TrackingUnit->Append("-1 - None");
		Units_ComboBox_TrainLocationID->Append("-1 - None");
		Units_ComboBox_StackUnitID->Append("-1 - None");
		for(short loop = 0; loop < 4; loop++)
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
		for(short loop = 0; loop < 30; loop++)
		Terrains_ComboBox_TerrainUnitID[loop]->Append("-1 - None");
	}

	for(short loop = 0; loop < GenieFile->Civs[civ].Units.size(); loop++)
	{
		wxString Name = " "+lexical_cast<string>(loop)+" - "+GetUnitName(loop, civ, true);
		if(SearchMatches(Name.Lower()))
		{
			Units_Units_List->Append(Name, (void*)&GenieFile->Civs[civ].Units[loop]);
		}
		if(Sized)
		{
			Name = " "+lexical_cast<string>(loop)+" - "+GetUnitName(loop, 0);
			Units_ComboBox_DeadUnitID->Append(Name);
			Units_ComboBox_ProjectileUnitID->Append(Name);
			Units_ComboBox_AttackMissileDuplicationUnit->Append(Name);
			for(short loop = 0; loop < 2; loop++)
			Units_ComboBox_DropSite[loop]->Append(Name);
			Units_ComboBox_TrackingUnit->Append(Name);
			Units_ComboBox_TrainLocationID->Append(Name);
			Units_ComboBox_StackUnitID->Append(Name);
			for(short loop = 0; loop < 4; loop++)
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
			for(short loop = 0; loop < 30; loop++)
			Terrains_ComboBox_TerrainUnitID[loop]->Append(Name);
		}
	}

	ListingFix(Selections, Units_Units_List);
	if(Sized)
	{
		Units_ComboBox_DeadUnitID->SetSelection(SavedIDs[0]);
		Units_ComboBox_ProjectileUnitID->SetSelection(SavedIDs[1]);
		for(short loop = 0; loop < 2; loop++)
		Units_ComboBox_DropSite[loop]->SetSelection(SavedIDs[loop+2]);// 2 ja 3
		Units_ComboBox_AttackMissileDuplicationUnit->SetSelection(SavedIDs[4]);
		Units_ComboBox_TrackingUnit->SetSelection(SavedIDs[5]);
		Units_ComboBox_TrainLocationID->SetSelection(SavedIDs[6]);
		Units_ComboBox_StackUnitID->SetSelection(SavedIDs[7]);
		for(short loop = 0; loop < 4; loop++)
		{
			Units_ComboBox_AnnexUnit[loop]->SetSelection(SavedIDs[loop+8]);// 8 - 11
			TechTrees_ComboBox_Unit[loop]->SetSelection(SavedIDs[loop+30]);
		}
		Units_ComboBox_HeadUnit->SetSelection(SavedIDs[12]);
		Units_ComboBox_TransformUnit->SetSelection(SavedIDs[13]);
		Research_ComboBox_ResearchLocation->SetSelection(SavedIDs[14]);
		Effects_ComboBox_UnitsA->SetSelection(SavedIDs[15]);
		Effects_ComboBox_UnitsB->SetSelection(SavedIDs[16]);
		UnitCommands_ComboBox_UnitID->SetSelection(SavedIDs[17]);
		UnitLineUnits_ComboBox_Units->SetSelection(SavedIDs[18]);
		TechTrees_Ages_ComboBox_Building->SetSelection(SavedIDs[19]);
		TechTrees_Ages_ComboBox_Unit->SetSelection(SavedIDs[20]);
		TechTrees_Buildings_ComboBox_ID->SetSelection(SavedIDs[21]);
		TechTrees_Buildings_ComboBox_Building->SetSelection(SavedIDs[22]);
		TechTrees_Buildings_ComboBox_Unit->SetSelection(SavedIDs[23]);
		TechTrees_Units_ComboBox_ID->SetSelection(SavedIDs[24]);
		TechTrees_Units_ComboBox_UpperBuilding->SetSelection(SavedIDs[25]);
		TechTrees_Units_ComboBox_Unit->SetSelection(SavedIDs[26]);
		TechTrees_Researches_ComboBox_UpperBuilding->SetSelection(SavedIDs[27]);
		TechTrees_Researches_ComboBox_Building->SetSelection(SavedIDs[28]);
		TechTrees_Researches_ComboBox_Unit->SetSelection(SavedIDs[29]);
		for(short loop = 0; loop < 30; loop++)
		Terrains_ComboBox_TerrainUnitID[loop]->SetSelection(SavedIDs[loop+34]);
	}

	for(short loop = 0; loop < 2; loop++)
	UseAnd[loop] = false;

	wxCommandEvent E;
	OnUnitsSelect(E);
}

//	This links data into user interface
void AGE_Frame::OnUnitsSelect(wxCommandEvent &Event)
{
	auto Selections = Units_Units_List->GetSelections(Items);
	if(Selections < 1) return;	// If a unit is selected.

	UnitCivID = Units_Civs_List->GetSelection();

	// Auto-copy stuff
	SelectedCivs.resize(1);
	SelectedCivs[0] = UnitCivID;
	if(AutoCopy)
	{
		for(short civ = 0; civ < GenieFile->Civs.size(); civ++)
		{
			// Counts all selected civs and always the one being edited.
			if(Units_CivBoxes[civ]->IsChecked() && civ != UnitCivID)
				SelectedCivs.push_back(civ);
		}
	}

	UnitIDs.resize(Selections);
	int PointerCount = Selections * SelectedCivs.size();
	Units_Type->resize(PointerCount);
	// Type 80
	Units_AdjacentMode->resize(PointerCount);
	Units_Unknown31->resize(PointerCount);
	Units_Unknown31b->resize(PointerCount);
	Units_StackUnitID->resize(PointerCount);
	Units_TerrainID->resize(PointerCount);
	Units_Unknown32->resize(PointerCount);
	Units_ResearchID->resize(PointerCount);
	if(GenieVersion >= genie::GV_AoKA)
	{
		Units_Unknown33->resize(PointerCount);
		for(short loop = 0; loop < 4; loop++)
		{
			Units_AnnexUnit[loop]->resize(PointerCount);
			Units_AnnexUnitMisplacement[loop][0]->resize(PointerCount);
			Units_AnnexUnitMisplacement[loop][1]->resize(PointerCount);
		}
		Units_HeadUnit->resize(PointerCount);
		Units_TransformUnit->resize(PointerCount);
		Units_Unknown34->resize(PointerCount);
		Units_GarrisonType->resize(PointerCount);
		Units_GarrisonHealRate->resize(PointerCount);
		Units_Unknown35->resize(PointerCount);
		for(short loop = 0; loop < Units_AlfaThingy.size(); loop++)
		Units_AlfaThingy[loop]->resize(PointerCount);
	}
	Units_ConstructionSound->resize(PointerCount);
	// Type 70
	for(short loop = 0; loop < 3; loop++)
	{
		Units_CostType[loop]->resize(PointerCount);
		Units_CostAmount[loop]->resize(PointerCount);
		Units_CostUsed[loop]->resize(PointerCount);
	}
	Units_TrainTime->resize(PointerCount);
	Units_TrainLocationID->resize(PointerCount);
	Units_ButtonID->resize(PointerCount);
	if(GenieVersion >= genie::GV_AoKA)
	{
		Units_Unknown26->resize(PointerCount);
		Units_Unknown27->resize(PointerCount);
		Units_MissileGraphicDelay->resize(PointerCount);
		if(GenieVersion >= genie::GV_AoK)
		{
			Units_HeroMode->resize(PointerCount);
		}
		Units_AttackMissileDuplicationAmount1->resize(PointerCount);
		Units_AttackMissileDuplicationAmount2->resize(PointerCount);
		for(short loop = 0; loop < 3; loop++)
		{
			Units_AttackMissileDuplicationSpawning[loop]->resize(PointerCount);
		}
		Units_AttackMissileDuplicationUnit->resize(PointerCount);
		Units_AttackMissileDuplicationGraphic->resize(PointerCount);
		Units_Unknown29->resize(PointerCount);
	}
	Units_DisplayedPierceArmour->resize(PointerCount);
	// Type 60
	Units_Unknown20[0]->resize(PointerCount);
	Units_Unknown21->resize(PointerCount);
	Units_MaxRange->resize(PointerCount);
	Units_BlastRadius->resize(PointerCount);
	Units_ReloadTime1->resize(PointerCount);
	Units_ProjectileUnitID->resize(PointerCount);
	Units_AccuracyPercent->resize(PointerCount);
	Units_TowerMode->resize(PointerCount);
	Units_Delay->resize(PointerCount);
	for(short loop = 0; loop < 3; loop++)
	{
		Units_GraphicDisplacement[loop]->resize(PointerCount);
	}
	Units_BlastLevel->resize(PointerCount);
	Units_MinRange->resize(PointerCount);
	if(GenieVersion >= genie::GV_AoK)
	{
		if(GenieVersion >= genie::GV_TC)
		{
			Units_Unknown20[1]->resize(PointerCount);
		}
		Units_GarrisonRecoveryRate->resize(PointerCount);
	}
	Units_DisplayedMeleeArmour->resize(PointerCount);
	Units_DisplayedAttack->resize(PointerCount);
	Units_DisplayedRange->resize(PointerCount);
	Units_ReloadTime2->resize(PointerCount);
	// Type 40
	Units_SheepConversion->resize(PointerCount);
	Units_SearchRadius->resize(PointerCount);
	Units_WorkRate->resize(PointerCount);
	Units_DropSite[0]->resize(PointerCount);
	Units_DropSite[1]->resize(PointerCount);
	Units_VillagerMode->resize(PointerCount);
	Units_AttackSound->resize(PointerCount);
	Units_MoveSound->resize(PointerCount);
	Units_AnimalMode->resize(PointerCount);
	// Type 30
	Units_RotationSpeed->resize(PointerCount);
	Units_Unknown11->resize(PointerCount);
	Units_TrackingUnit->resize(PointerCount);
	Units_TrackingUnitUsed->resize(PointerCount);
	Units_TrackingUnitDensity->resize(PointerCount);
	Units_Unknown16->resize(PointerCount);
	if(GenieVersion >= genie::GV_AoK)
	{
		Units_Unknown12->resize(PointerCount);
		for(short loop = 0; loop < Units_Unknown16B.size(); loop++)
		{
			Units_Unknown16B[loop]->resize(PointerCount);
		}
	}
	// Type 20/25
	Units_Speed->resize(PointerCount);
	// Type 10
	Units_ID1->resize(PointerCount);
	Units_LanguageDLLName->resize(PointerCount);
	Units_LanguageDLLCreation->resize(PointerCount);
	Units_Class->resize(PointerCount);
	Units_DeathMode->resize(PointerCount);
	Units_HitPoints->resize(PointerCount);
	Units_LineOfSight->resize(PointerCount);
	Units_GarrisonCapacity->resize(PointerCount);
	Units_SizeRadius[0]->resize(PointerCount);
	Units_SizeRadius[1]->resize(PointerCount);
	Units_HPBarHeight1->resize(PointerCount);
	Units_TrainSound[0]->resize(PointerCount);
	Units_DeadUnitID->resize(PointerCount);
	Units_PlacementMode->resize(PointerCount);
	Units_AirMode->resize(PointerCount);
	Units_HideInEditor->resize(PointerCount);
	Units_Unknown1->resize(PointerCount);
	Units_PlacementBypassTerrain[0]->resize(PointerCount);
	Units_PlacementBypassTerrain[1]->resize(PointerCount);
	Units_PlacementTerrain[0]->resize(PointerCount);
	Units_PlacementTerrain[1]->resize(PointerCount);
	Units_EditorRadius[0]->resize(PointerCount);
	Units_EditorRadius[1]->resize(PointerCount);
	Units_BuildingMode->resize(PointerCount);
	Units_VisibleInFog->resize(PointerCount);
	Units_TerrainRestriction->resize(PointerCount);
	Units_FlyMode->resize(PointerCount);
	Units_ResourceCapacity->resize(PointerCount);
	Units_ResourceDecay->resize(PointerCount);
	Units_BlastType->resize(PointerCount);
	Units_Unknown2->resize(PointerCount);
	Units_InteractionMode->resize(PointerCount);
	Units_MinimapMode->resize(PointerCount);
	Units_SelectionEffect->resize(PointerCount);
	Units_EditorSelectionColour->resize(PointerCount);
	if(GenieVersion >= genie::GV_AoKA)
	{
		Units_TrainSound[1]->resize(PointerCount);
		Units_Unknown7->resize(PointerCount);
		Units_Unknown8->resize(PointerCount);
		Units_SelectionShapeType->resize(PointerCount);
		Units_ID3->resize(PointerCount);
		if(GenieVersion >= genie::GV_TC)
		{
			Units_Attribute->resize(PointerCount);
			Units_Civ->resize(PointerCount);
			Units_Unknown9->resize(PointerCount);
			if(GenieVersion >= genie::GV_SWGB)
			{
				Units_Name2->resize(PointerCount);
				Units_Unitline->resize(PointerCount);
				Units_MinTechLevel->resize(PointerCount);
			}
		}
	}
	Units_Enabled->resize(PointerCount);
	Units_CommandAttribute->resize(PointerCount);
	for(short loop = 0; loop < Units_Unknown3.size(); loop++)
	Units_Unknown3[loop]->resize(PointerCount);
	Units_LanguageDLLHelp->resize(PointerCount);
	Units_LanguageDLLHotKeyText->resize(PointerCount);
	Units_HotKey->resize(PointerCount);
	Units_Unselectable->resize(PointerCount);
	Units_Unknown6->resize(PointerCount);
	Units_SelectionMask->resize(PointerCount);
	Units_SelectionShape->resize(PointerCount);
	Units_SelectionRadius[0]->resize(PointerCount);
	Units_SelectionRadius[1]->resize(PointerCount);
	Units_HPBarHeight2->resize(PointerCount);
	Units_SelectionSound->resize(PointerCount);
	Units_DyingSound->resize(PointerCount);
	Units_AttackMode->resize(PointerCount);
	Units_Name->resize(PointerCount);
	Units_ID2->resize(PointerCount);
	for(short loop = 0; loop < 3; loop++)
	{
		ResourceStorage_Type[loop]->resize(PointerCount);
		ResourceStorage_Amount[loop]->resize(PointerCount);
		ResourceStorage_Enabled[loop]->resize(PointerCount);
	}
	// Type 60 only
	Units_StretchMode->resize(PointerCount);
	Units_CompensationMode->resize(PointerCount);
	Units_DropAnimationMode->resize(PointerCount);
	Units_PenetrationMode->resize(PointerCount);
	Units_Unknown24->resize(PointerCount);
	Units_ProjectileArc->resize(PointerCount);

	// If no graphic copying, only one civ to edit.
	if(!CopyGraphics) PointerCount = Selections;
	Units_IconID->resize(PointerCount);
	Units_ConstructionGraphicID->resize(PointerCount);
	if(GenieVersion >= genie::GV_AoK)
	{
		if(GenieVersion >= genie::GV_TC) Units_SnowGraphicID->resize(PointerCount);
		Units_StandingGraphic[1]->resize(PointerCount);
		Units_GarrisonGraphic[0]->resize(PointerCount);
		Units_GarrisonGraphic[1]->resize(PointerCount);
	}
	Units_AttackGraphic->resize(PointerCount);
	Units_StandingGraphic[0]->resize(PointerCount);
	Units_WalkingGraphic[0]->resize(PointerCount);
	Units_WalkingGraphic[1]->resize(PointerCount);
	Units_DyingGraphic[0]->resize(PointerCount);
	Units_DyingGraphic[1]->resize(PointerCount);

	short UnitType;
	genie::Unit * UnitPointer;
	//wxString locations = "Locations:\n";
	for(auto sel = Selections; sel--> 0;)
	{
		UnitPointer = (genie::Unit*)Units_Units_List->GetClientData(Items.Item(sel));
		UnitIDs[sel] = (UnitPointer - (&GenieFile->Civs[UnitCivID].Units[0]));
		//locations.Append("Unit "+lexical_cast<string>(UnitIDs[sel])+":   ");

		// This makes auto-copy automatic.
		for(short vecCiv = SelectedCivs.size(); vecCiv--> 0;)
		{
			//locations.Append("Vec "+lexical_cast<string>(vecCiv)+", civ "+lexical_cast<string>(SelectedCivs[vecCiv])+"; ");
			UnitPointer = &GenieFile->Civs[SelectedCivs[vecCiv]].Units[UnitIDs[sel]];

			UnitType = (short)UnitPointer->Type;
			// This ensures that the first pointer is always the current civ and its first selection.
			int location = sel + vecCiv * Selections;
			//locations.Append(lexical_cast<string>(location)+" ");
			// Assing data to editing boxes
			Units_Type->container[location] = &UnitPointer->Type;
			//switch(UnitType)
			{
				//case 80:
				{
					if(CopyGraphics || vecCiv == 0)
					Units_ConstructionGraphicID->container[location] = &UnitPointer->Building.ConstructionGraphicID;
					Units_AdjacentMode->container[location] = &UnitPointer->Building.AdjacentMode;
					Units_Unknown31->container[location] = &UnitPointer->Building.Unknown31;
					Units_Unknown31b->container[location] = &UnitPointer->Building.Unknown31b;
					Units_StackUnitID->container[location] = &UnitPointer->Building.StackUnitID;
					Units_TerrainID->container[location] = &UnitPointer->Building.TerrainID;
					Units_Unknown32->container[location] = &UnitPointer->Building.Unknown32;
					Units_ResearchID->container[location] = &UnitPointer->Building.ResearchID;
					if(GenieVersion >= genie::GV_AoKA)
					{
						if(GenieVersion >= genie::GV_TC)
						{
							if(CopyGraphics || vecCiv == 0)
							Units_SnowGraphicID->container[location] = &UnitPointer->Building.SnowGraphicID;
						}
						Units_Unknown33->container[location] = &UnitPointer->Building.Unknown33;
						for(short loop = 0; loop < 4; loop++)
						{
							Units_AnnexUnit[loop]->container[location] = &UnitPointer->Building.Annexes[loop].UnitID;
							Units_AnnexUnitMisplacement[loop][0]->container[location] = &UnitPointer->Building.Annexes[loop].Misplacement.first;
							Units_AnnexUnitMisplacement[loop][1]->container[location] = &UnitPointer->Building.Annexes[loop].Misplacement.second;
						}
						Units_HeadUnit->container[location] = &UnitPointer->Building.HeadUnit;
						Units_TransformUnit->container[location] = &UnitPointer->Building.TransformUnit;
						Units_Unknown34->container[location] = &UnitPointer->Building.Unknown34;
						Units_GarrisonType->container[location] = &UnitPointer->Building.GarrisonType;
						Units_GarrisonHealRate->container[location] = &UnitPointer->Building.GarrisonHealRate;
						Units_Unknown35->container[location] = &UnitPointer->Building.Unknown35;
						for(short loop = 0; loop < Units_AlfaThingy.size(); loop++)
						Units_AlfaThingy[loop]->container[location] = &UnitPointer->Building.AlfaThingy[loop];
					}
					Units_ConstructionSound->container[location] = &UnitPointer->Building.ConstructionSound;
				}
				//case 70:
				{
					for(short loop = 0; loop < 3; loop++)
					{
						Units_CostType[loop]->container[location] = &UnitPointer->Creatable.ResourceCosts[loop].Type;
						Units_CostAmount[loop]->container[location] = &UnitPointer->Creatable.ResourceCosts[loop].Amount;
						Units_CostUsed[loop]->container[location] = &UnitPointer->Creatable.ResourceCosts[loop].Enabled;
					}
					Units_TrainTime->container[location] = &UnitPointer->Creatable.TrainTime;
					Units_TrainLocationID->container[location] = &UnitPointer->Creatable.TrainLocationID;
					Units_ButtonID->container[location] = &UnitPointer->Creatable.ButtonID;
					if(GenieVersion >= genie::GV_AoKA)
					{
						Units_Unknown26->container[location] = &UnitPointer->Creatable.Unknown26;
						Units_Unknown27->container[location] = &UnitPointer->Creatable.Unknown27;
						Units_MissileGraphicDelay->container[location] = &UnitPointer->Creatable.MissileGraphicDelay;
						if(GenieVersion >= genie::GV_AoK)
						{
							Units_HeroMode->container[location] = &UnitPointer->Creatable.HeroMode;
							if(CopyGraphics || vecCiv == 0)
							{
								Units_GarrisonGraphic[0]->container[location] = &UnitPointer->Creatable.GarrisonGraphic.first;
								Units_GarrisonGraphic[1]->container[location] = &UnitPointer->Creatable.GarrisonGraphic.second;
							}
						}
						Units_AttackMissileDuplicationAmount1->container[location] = &UnitPointer->Creatable.AttackMissileDuplicationAmount1;
						Units_AttackMissileDuplicationAmount2->container[location] = &UnitPointer->Creatable.AttackMissileDuplicationAmount2;
						for(short loop = 0; loop < 3; loop++)
						{
							Units_AttackMissileDuplicationSpawning[loop]->container[location] = &UnitPointer->Creatable.AttackMissileDuplicationSpawning[loop];
						}
						Units_AttackMissileDuplicationUnit->container[location] = &UnitPointer->Creatable.AttackMissileDuplicationUnit;
						Units_AttackMissileDuplicationGraphic->container[location] = &UnitPointer->Creatable.AttackMissileDuplicationGraphic;
						Units_Unknown29->container[location] = &UnitPointer->Creatable.Unknown29;
					}
					Units_DisplayedPierceArmour->container[location] = &UnitPointer->Creatable.DisplayedPierceArmour;
				}
				//case 60:
				{
					Units_Unknown20[0]->container[location] = &UnitPointer->Projectile.Unknown20;
					Units_Unknown21->container[location] = &UnitPointer->Projectile.Unknown21;
					Units_MaxRange->container[location] = &UnitPointer->Projectile.MaxRange;
					Units_BlastRadius->container[location] = &UnitPointer->Projectile.BlastRadius;
					Units_ReloadTime1->container[location] = &UnitPointer->Projectile.ReloadTime1;
					Units_ProjectileUnitID->container[location] = &UnitPointer->Projectile.ProjectileUnitID;
					Units_AccuracyPercent->container[location] = &UnitPointer->Projectile.AccuracyPercent;
					Units_TowerMode->container[location] = &UnitPointer->Projectile.TowerMode;
					Units_Delay->container[location] = &UnitPointer->Projectile.Delay;
					for(short loop = 0; loop < 3; loop++)
					{
						Units_GraphicDisplacement[loop]->container[location] = &UnitPointer->Projectile.GraphicDisplacement[loop];
					}
					Units_BlastLevel->container[location] = &UnitPointer->Projectile.Unknown23;
					Units_MinRange->container[location] = &UnitPointer->Projectile.MinRange;
					if(GenieVersion >= genie::GV_AoK)
					{
						if(GenieVersion >= genie::GV_TC)
						{
							Units_Unknown20[1]->container[location] = &UnitPointer->Projectile.Unknown20_1;
						}
						Units_GarrisonRecoveryRate->container[location] = &UnitPointer->Projectile.GarrisonRecoveryRate;
					}
					if(CopyGraphics || vecCiv == 0)
					Units_AttackGraphic->container[location] = &UnitPointer->Projectile.AttackGraphic;
					Units_DisplayedMeleeArmour->container[location] = &UnitPointer->Projectile.DisplayedMeleeArmour;
					Units_DisplayedAttack->container[location] = &UnitPointer->Projectile.DisplayedAttack;
					Units_DisplayedRange->container[location] = &UnitPointer->Projectile.DisplayedRange;
					Units_ReloadTime2->container[location] = &UnitPointer->Projectile.ReloadTime2;
				}
				//case 40:
				{
					Units_SheepConversion->container[location] = &UnitPointer->Bird.SheepConversion;
					Units_SearchRadius->container[location] = &UnitPointer->Bird.SearchRadius;
					Units_WorkRate->container[location] = &UnitPointer->Bird.WorkRate;
					Units_DropSite[0]->container[location] = &UnitPointer->Bird.DropSite.first;
					Units_DropSite[1]->container[location] = &UnitPointer->Bird.DropSite.second;
					Units_VillagerMode->container[location] = &UnitPointer->Bird.VillagerMode;
					Units_AttackSound->container[location] = &UnitPointer->Bird.AttackSound;
					Units_MoveSound->container[location] = &UnitPointer->Bird.MoveSound;
					Units_AnimalMode->container[location] = &UnitPointer->Bird.AnimalMode;
				}
				//case 30:
				{
					if(CopyGraphics || vecCiv == 0)
					{
						Units_WalkingGraphic[0]->container[location] = &UnitPointer->DeadFish.WalkingGraphic.first;
						Units_WalkingGraphic[1]->container[location] = &UnitPointer->DeadFish.WalkingGraphic.second;
					}
					Units_RotationSpeed->container[location] = &UnitPointer->DeadFish.RotationSpeed;
					Units_Unknown11->container[location] = &UnitPointer->DeadFish.Unknown11;
					Units_TrackingUnit->container[location] = &UnitPointer->DeadFish.TrackingUnit;
					Units_TrackingUnitUsed->container[location] = &UnitPointer->DeadFish.TrackingUnitUsed;
					Units_TrackingUnitDensity->container[location] = &UnitPointer->DeadFish.TrackingUnitDensity;
					Units_Unknown16->container[location] = &UnitPointer->DeadFish.Unknown16;
					if(GenieVersion >= genie::GV_AoK)
					{
						Units_Unknown12->container[location] = &UnitPointer->DeadFish.Unknown12;
						for(short loop = 0; loop < Units_Unknown16B.size(); loop++)
						{
							Units_Unknown16B[loop]->container[location] = &UnitPointer->DeadFish.Unknown16B[loop];
						}
					}
				}
				//case 25:
				//case 20:
				{
					Units_Speed->container[location] = &UnitPointer->Speed;
				}
			}
			Units_ID1->container[location] = &UnitPointer->ID1;
			Units_LanguageDLLName->container[location] = &UnitPointer->LanguageDLLName;
			Units_LanguageDLLCreation->container[location] = &UnitPointer->LanguageDLLCreation;
			Units_Class->container[location] = &UnitPointer->Class;
			if(CopyGraphics || vecCiv == 0)
			{
				Units_StandingGraphic[0]->container[location] = &UnitPointer->StandingGraphic.first;
				Units_DyingGraphic[0]->container[location] = &UnitPointer->DyingGraphic.first;
				Units_DyingGraphic[1]->container[location] = &UnitPointer->DyingGraphic.second;
				Units_IconID->container[location] = &UnitPointer->IconID;
			}
			Units_DeathMode->container[location] = &UnitPointer->DeathMode;
			Units_HitPoints->container[location] = &UnitPointer->HitPoints;
			Units_LineOfSight->container[location] = &UnitPointer->LineOfSight;
			Units_GarrisonCapacity->container[location] = &UnitPointer->GarrisonCapacity;
			Units_SizeRadius[0]->container[location] = &UnitPointer->SizeRadius.first;
			Units_SizeRadius[1]->container[location] = &UnitPointer->SizeRadius.second;
			Units_HPBarHeight1->container[location] = &UnitPointer->HPBarHeight1;
			Units_TrainSound[0]->container[location] = &UnitPointer->TrainSound.first;
			Units_DeadUnitID->container[location] = &UnitPointer->DeadUnitID;
			Units_PlacementMode->container[location] = &UnitPointer->PlacementMode;
			Units_AirMode->container[location] = &UnitPointer->AirMode;
			Units_HideInEditor->container[location] = &UnitPointer->HideInEditor;
			Units_Unknown1->container[location] = &UnitPointer->Unknown1;
			Units_PlacementBypassTerrain[0]->container[location] = &UnitPointer->PlacementBypassTerrain.first;
			Units_PlacementBypassTerrain[1]->container[location] = &UnitPointer->PlacementBypassTerrain.second;
			Units_PlacementTerrain[0]->container[location] = &UnitPointer->PlacementTerrain.first;
			Units_PlacementTerrain[1]->container[location] = &UnitPointer->PlacementTerrain.second;
			Units_EditorRadius[0]->container[location] = &UnitPointer->EditorRadius.first;
			Units_EditorRadius[1]->container[location] = &UnitPointer->EditorRadius.second;
			Units_BuildingMode->container[location] = &UnitPointer->BuildingMode;
			Units_VisibleInFog->container[location] = &UnitPointer->VisibleInFog;
			Units_TerrainRestriction->container[location] = &UnitPointer->TerrainRestriction;
			Units_FlyMode->container[location] = &UnitPointer->FlyMode;
			Units_ResourceCapacity->container[location] = &UnitPointer->ResourceCapacity;
			Units_ResourceDecay->container[location] = &UnitPointer->ResourceDecay;
			Units_BlastType->container[location] = &UnitPointer->BlastType;
			Units_Unknown2->container[location] = &UnitPointer->Unknown2;
			Units_InteractionMode->container[location] = &UnitPointer->InteractionMode;
			Units_MinimapMode->container[location] = &UnitPointer->MinimapMode;
			Units_SelectionEffect->container[location] = &UnitPointer->SelectionEffect;
			Units_EditorSelectionColour->container[location] = &UnitPointer->EditorSelectionColour;
			if(GenieVersion >= genie::GV_AoKA)
			{
				Units_TrainSound[1]->container[location] = &UnitPointer->TrainSound.second;
				Units_Unknown7->container[location] = &UnitPointer->Unknown7;
				Units_Unknown8->container[location] = &UnitPointer->Unknown8;
				Units_SelectionShapeType->container[location] = &UnitPointer->SelectionShapeType;
				Units_ID3->container[location] = &UnitPointer->ID3;
			}
			if(GenieVersion >= genie::GV_AoK)
			{
				if(CopyGraphics || vecCiv == 0)
				Units_StandingGraphic[1]->container[location] = &UnitPointer->StandingGraphic.second;
				if(GenieVersion >= genie::GV_TC)
				{
					Units_Attribute->container[location] = &UnitPointer->Attribute;
					Units_Civ->container[location] = &UnitPointer->Civilization;
					Units_Unknown9->container[location] = &UnitPointer->Unknown9;
					if(GenieVersion >= genie::GV_SWGB)
					{
						Units_Name2->container[location] = &UnitPointer->Name2;
						Units_Unitline->container[location] = &UnitPointer->Unitline;
						Units_MinTechLevel->container[location] = &UnitPointer->MinTechLevel;
					}
				}
			}
			Units_Enabled->container[location] = &UnitPointer->Enabled;
			Units_CommandAttribute->container[location] = &UnitPointer->CommandAttribute;
			for(short loop = 0; loop < Units_Unknown3.size(); loop++)
			Units_Unknown3[loop]->container[location] = &UnitPointer->Unknown3[loop];
			Units_LanguageDLLHelp->container[location] = &UnitPointer->LanguageDLLHelp;
			Units_LanguageDLLHotKeyText->container[location] = &UnitPointer->LanguageDLLHotKeyText;
			Units_HotKey->container[location] = &UnitPointer->HotKey;
			Units_Unselectable->container[location] = &UnitPointer->Unselectable;
			Units_Unknown6->container[location] = &UnitPointer->Unknown6;
			Units_SelectionMask->container[location] = &UnitPointer->SelectionMask;
			Units_SelectionShape->container[location] = &UnitPointer->SelectionShape;
			Units_SelectionRadius[0]->container[location] = &UnitPointer->SelectionRadius.first;
			Units_SelectionRadius[1]->container[location] = &UnitPointer->SelectionRadius.second;
			Units_HPBarHeight2->container[location] = &UnitPointer->HPBarHeight2;
			Units_SelectionSound->container[location] = &UnitPointer->SelectionSound;
			Units_DyingSound->container[location] = &UnitPointer->DyingSound;
			Units_AttackMode->container[location] = &UnitPointer->AttackMode;
			Units_Name->container[location] = &UnitPointer->Name;
			Units_ID2->container[location] = &UnitPointer->ID2;
			for(short loop = 0; loop < 3; loop++)
			{
				ResourceStorage_Type[loop]->container[location] = &UnitPointer->ResourceStorages[loop].Type;
				ResourceStorage_Amount[loop]->container[location] = &UnitPointer->ResourceStorages[loop].Amount;
				ResourceStorage_Enabled[loop]->container[location] = &UnitPointer->ResourceStorages[loop].Enabled;
			}

			//if(UnitType == 60)
			{
				Units_StretchMode->container[location] = &UnitPointer->ProjectileOnly.StretchMode;
				Units_CompensationMode->container[location] = &UnitPointer->ProjectileOnly.CompensationMode;
				Units_DropAnimationMode->container[location] = &UnitPointer->ProjectileOnly.DropAnimationMode;
				Units_PenetrationMode->container[location] = &UnitPointer->ProjectileOnly.PenetrationMode;
				Units_Unknown24->container[location] = &UnitPointer->ProjectileOnly.Unknown24;
				Units_ProjectileArc->container[location] = &UnitPointer->ProjectileOnly.ProjectileArc;
			}
		}
		//locations.Append("\n");
	}
	//wxMessageBox(locations);
	SetStatusText("Civilization: "+lexical_cast<string>(UnitCivID)+"    Selections: "+lexical_cast<string>(Selections)+"    Selected unit: "+lexical_cast<string>(UnitIDs[0]), 0);

	Units_Type->ChangeValue(lexical_cast<string>((short)UnitPointer->Type));
	switch(UnitType)
	{
		case 10: Units_ComboBox_Type->SetSelection(1); break;
		case 20: Units_ComboBox_Type->SetSelection(2); break;
		case 25: Units_ComboBox_Type->SetSelection(3); break;
		case 30: Units_ComboBox_Type->SetSelection(4); break;
		case 40: Units_ComboBox_Type->SetSelection(5); break;
		case 60: Units_ComboBox_Type->SetSelection(6); break;
		case 70: Units_ComboBox_Type->SetSelection(7); break;
		case 80: Units_ComboBox_Type->SetSelection(8); break;
		case 90: Units_ComboBox_Type->SetSelection(9); break;
		default: Units_ComboBox_Type->SetSelection(0);
	}

	switch(UnitType) // Enable editing
	{
		case 80:
		{
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
			for(short loop = 0; loop < 4; loop++)
			{
				Units_AnnexUnit[loop]->Enable(true);
				Units_ComboBox_AnnexUnit[loop]->Enable(true);
				for(short loop2 = 0; loop2 < 2; loop2++)
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
			for(short loop = 0; loop < Units_AlfaThingy.size(); loop++)
			Units_AlfaThingy[loop]->Enable(true);

			Units_ConstructionGraphicID->ChangeValue(lexical_cast<string>(UnitPointer->Building.ConstructionGraphicID));
			Units_ComboBox_ConstructionGraphicID->SetSelection(UnitPointer->Building.ConstructionGraphicID + 1);
			Units_AdjacentMode->ChangeValue(lexical_cast<string>(UnitPointer->Building.AdjacentMode));
			Units_CheckBox_AdjacentMode->SetValue((bool)UnitPointer->Building.AdjacentMode);
			Units_Unknown31->ChangeValue(lexical_cast<string>((short)UnitPointer->Building.Unknown31));
			Units_Unknown31b->ChangeValue(lexical_cast<string>((short)UnitPointer->Building.Unknown31b));
			Units_CheckBox_Unknown31b->SetValue((bool)UnitPointer->Building.Unknown31b);
			Units_StackUnitID->ChangeValue(lexical_cast<string>(UnitPointer->Building.StackUnitID));
			Units_ComboBox_StackUnitID->SetSelection(UnitPointer->Building.StackUnitID + 1);
			Units_TerrainID->ChangeValue(lexical_cast<string>(UnitPointer->Building.TerrainID));
			Units_ComboBox_TerrainID->SetSelection(UnitPointer->Building.TerrainID + 1);
			Units_Unknown32->ChangeValue(lexical_cast<string>(UnitPointer->Building.Unknown32));
			Units_ResearchID->ChangeValue(lexical_cast<string>(UnitPointer->Building.ResearchID));
			Units_ComboBox_ResearchID->SetSelection(UnitPointer->Building.ResearchID + 1);
			if(GenieVersion >= genie::GV_AoKA)
			{
				if(GenieVersion >= genie::GV_TC)
				{
					Units_SnowGraphicID->ChangeValue(lexical_cast<string>(UnitPointer->Building.SnowGraphicID));
					Units_ComboBox_SnowGraphicID->SetSelection(UnitPointer->Building.SnowGraphicID + 1);
				}
				Units_Unknown33->ChangeValue(lexical_cast<string>((short)UnitPointer->Building.Unknown33));
				for(short loop = 0; loop < 4; loop++)
				{
					Units_AnnexUnit[loop]->ChangeValue(lexical_cast<string>(UnitPointer->Building.Annexes[loop].UnitID));
					Units_ComboBox_AnnexUnit[loop]->SetSelection(UnitPointer->Building.Annexes[loop].UnitID + 1);
					Units_AnnexUnitMisplacement[loop][0]->ChangeValue(lexical_cast<string>(UnitPointer->Building.Annexes[loop].Misplacement.first));
					Units_AnnexUnitMisplacement[loop][1]->ChangeValue(lexical_cast<string>(UnitPointer->Building.Annexes[loop].Misplacement.second));
				}
				Units_HeadUnit->ChangeValue(lexical_cast<string>(UnitPointer->Building.HeadUnit));
				Units_ComboBox_HeadUnit->SetSelection(UnitPointer->Building.HeadUnit + 1);
				Units_TransformUnit->ChangeValue(lexical_cast<string>(UnitPointer->Building.TransformUnit));
				Units_ComboBox_TransformUnit->SetSelection(UnitPointer->Building.TransformUnit + 1);
				Units_Unknown34->ChangeValue(lexical_cast<string>(UnitPointer->Building.Unknown34));
				Units_GarrisonType->ChangeValue(lexical_cast<string>((short)UnitPointer->Building.GarrisonType));
				Units_ComboBox_GarrisonType->SetSelection(UnitPointer->Building.GarrisonType + 1);
				Units_GarrisonHealRate->ChangeValue(lexical_cast<string>(UnitPointer->Building.GarrisonHealRate));
				Units_Unknown35->ChangeValue(lexical_cast<string>(UnitPointer->Building.Unknown35));
				for(short loop = 0; loop < Units_AlfaThingy.size(); loop++)
				Units_AlfaThingy[loop]->ChangeValue(lexical_cast<string>((short)UnitPointer->Building.AlfaThingy[loop]));
			}
			Units_ConstructionSound->ChangeValue(lexical_cast<string>(UnitPointer->Building.ConstructionSound));
			Units_ComboBox_ConstructionSound->SetSelection(UnitPointer->Building.ConstructionSound + 1);
		}
		case 70:
		{
			for(short loop = 0; loop < 2; loop++)
			{
				Units_GarrisonGraphic[loop]->Enable(true);
				Units_ComboBox_GarrisonGraphic[loop]->Enable(true);
			}
			for(short loop = 0; loop < 3; loop++)
			{
				Units_CostType[loop]->Enable(true);
				Units_ComboBox_CostType[loop]->Enable(true);
				Units_CostAmount[loop]->Enable(true);
				Units_CostUsed[loop]->Enable(true);
				Units_CheckBox_CostUsed[loop]->Enable(true);
				Units_AttackMissileDuplicationSpawning[loop]->Enable(true);
			}
			Units_TrainTime->Enable(true);
			Units_TrainLocationID->Enable(true);
			Units_ComboBox_TrainLocationID->Enable(true);
			Units_ButtonID->Enable(true);
			Units_Unknown26->Enable(true);
			Units_Unknown27->Enable(true);
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

			for(short loop = 0; loop < 3; loop++)
			{
				Units_CostType[loop]->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.ResourceCosts[loop].Type));
				Units_ComboBox_CostType[loop]->SetSelection(UnitPointer->Creatable.ResourceCosts[loop].Type + 1);
				Units_CostAmount[loop]->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.ResourceCosts[loop].Amount));
				Units_CostUsed[loop]->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.ResourceCosts[loop].Enabled));
				Units_CheckBox_CostUsed[loop]->SetValue((bool)UnitPointer->Creatable.ResourceCosts[loop].Enabled);
			}
			Units_TrainTime->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.TrainTime));
			Units_TrainLocationID->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.TrainLocationID));
			Units_ComboBox_TrainLocationID->SetSelection(UnitPointer->Creatable.TrainLocationID + 1);
			Units_ButtonID->ChangeValue(lexical_cast<string>((short)UnitPointer->Creatable.ButtonID));
			if(GenieVersion >= genie::GV_AoKA)
			{
				Units_Unknown26->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.Unknown26));
				Units_Unknown27->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.Unknown27));
				Units_MissileGraphicDelay->ChangeValue(lexical_cast<string>((short)UnitPointer->Creatable.MissileGraphicDelay));
				if(GenieVersion >= genie::GV_AoK)
				{
					Units_HeroMode->ChangeValue(lexical_cast<string>((short)UnitPointer->Creatable.HeroMode));
					Units_CheckBox_HeroMode->SetValue((bool)UnitPointer->Creatable.HeroMode);
					Units_GarrisonGraphic[0]->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.GarrisonGraphic.first));
					Units_ComboBox_GarrisonGraphic[0]->SetSelection(UnitPointer->Creatable.GarrisonGraphic.first + 1);
					Units_GarrisonGraphic[1]->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.GarrisonGraphic.second));
					Units_ComboBox_GarrisonGraphic[1]->SetSelection(UnitPointer->Creatable.GarrisonGraphic.second + 1);
				}
				Units_AttackMissileDuplicationAmount1->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.AttackMissileDuplicationAmount1));
				Units_AttackMissileDuplicationAmount2->ChangeValue(lexical_cast<string>((short)UnitPointer->Creatable.AttackMissileDuplicationAmount2));
				for(short loop = 0; loop < 3; loop++)
				{
					Units_AttackMissileDuplicationSpawning[loop]->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.AttackMissileDuplicationSpawning[loop]));
				}
				Units_AttackMissileDuplicationUnit->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.AttackMissileDuplicationUnit));
				Units_ComboBox_AttackMissileDuplicationUnit->SetSelection(UnitPointer->Creatable.AttackMissileDuplicationUnit + 1);
				Units_AttackMissileDuplicationGraphic->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.AttackMissileDuplicationGraphic));
				Units_ComboBox_AttackMissileDuplicationGraphic->SetSelection(UnitPointer->Creatable.AttackMissileDuplicationGraphic + 1);
				Units_Unknown29->ChangeValue(lexical_cast<string>((short)UnitPointer->Creatable.Unknown29));
			}
			Units_DisplayedPierceArmour->ChangeValue(lexical_cast<string>(UnitPointer->Creatable.DisplayedPierceArmour));
		}
		case 60:
		{
			for(short loop = 0; loop < 2; loop++)
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
			for(short loop = 0; loop < 4; loop++)
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
			for(short loop = 0; loop < 2; loop++)
			Attacks_ComboBox_Class[loop]->Enable(true);
			Attacks_Amount->Enable(true);
			Armors_Class->Enable(true);
			Armors_Amount->Enable(true);

			Units_Unknown20[0]->ChangeValue(lexical_cast<string>((short)UnitPointer->Projectile.Unknown20));
			Units_Unknown21->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.Unknown21));
			Units_MaxRange->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.MaxRange));
			Units_BlastRadius->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.BlastRadius));
			Units_ReloadTime1->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.ReloadTime1));
			Units_ProjectileUnitID->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.ProjectileUnitID));
			Units_ComboBox_ProjectileUnitID->SetSelection(UnitPointer->Projectile.ProjectileUnitID + 1);
			Units_AccuracyPercent->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.AccuracyPercent));
			Units_TowerMode->ChangeValue(lexical_cast<string>((short)UnitPointer->Projectile.TowerMode));
			Units_CheckBox_TowerMode->SetValue((bool)UnitPointer->Projectile.TowerMode);
			Units_Delay->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.Delay));
			for(short loop = 0; loop < 3; loop++)
			{
				Units_GraphicDisplacement[loop]->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.GraphicDisplacement[loop]));
			}
			Units_BlastLevel->ChangeValue(lexical_cast<string>((short)UnitPointer->Projectile.Unknown23));
			Units_MinRange->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.MinRange));
			if(GenieVersion >= genie::GV_AoK)
			{
				if(GenieVersion >= genie::GV_TC)
				{
					Units_Unknown20[1]->ChangeValue(lexical_cast<string>((short)UnitPointer->Projectile.Unknown20_1));
				}
				Units_GarrisonRecoveryRate->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.GarrisonRecoveryRate));
			}
			Units_AttackGraphic->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.AttackGraphic));
			Units_ComboBox_AttackGraphic->SetSelection(UnitPointer->Projectile.AttackGraphic + 1);
			Units_DisplayedMeleeArmour->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.DisplayedMeleeArmour));
			Units_DisplayedAttack->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.DisplayedAttack));
			Units_DisplayedRange->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.DisplayedRange));
			Units_ReloadTime2->ChangeValue(lexical_cast<string>(UnitPointer->Projectile.ReloadTime2));
		}
		case 40:
		{
			Units_SheepConversion->Enable(true);
			Units_CheckBox_SheepConversion->Enable(true);
			Units_SearchRadius->Enable(true);
			Units_WorkRate->Enable(true);
			for(short loop = 0; loop < 2; loop++)
			{
				Units_DropSite[loop]->Enable(true);
				Units_ComboBox_DropSite[loop]->Enable(true);
			}
			Units_VillagerMode->Enable(true);
			Units_AttackSound->Enable(true);
			Units_ComboBox_AttackSound->Enable(true);
			Units_MoveSound->Enable(true);
			Units_ComboBox_MoveSound->Enable(true);
			Units_AnimalMode->Enable(true);
			Units_CheckBox_AnimalMode->Enable(true);

			Units_SheepConversion->ChangeValue(lexical_cast<string>(UnitPointer->Bird.SheepConversion));
			if(UnitPointer->Bird.SheepConversion == 0) Units_CheckBox_SheepConversion->SetValue(true);
			else Units_CheckBox_SheepConversion->SetValue(false);
			Units_SearchRadius->ChangeValue(lexical_cast<string>(UnitPointer->Bird.SearchRadius));
			Units_WorkRate->ChangeValue(lexical_cast<string>(UnitPointer->Bird.WorkRate));
			Units_DropSite[0]->ChangeValue(lexical_cast<string>(UnitPointer->Bird.DropSite.first));
			Units_ComboBox_DropSite[0]->SetSelection(UnitPointer->Bird.DropSite.first + 1);
			Units_DropSite[1]->ChangeValue(lexical_cast<string>(UnitPointer->Bird.DropSite.second));
			Units_ComboBox_DropSite[1]->SetSelection(UnitPointer->Bird.DropSite.second + 1);
			Units_VillagerMode->ChangeValue(lexical_cast<string>((short)UnitPointer->Bird.VillagerMode));
			Units_AttackSound->ChangeValue(lexical_cast<string>(UnitPointer->Bird.AttackSound));
			Units_ComboBox_AttackSound->SetSelection(UnitPointer->Bird.AttackSound + 1);
			Units_MoveSound->ChangeValue(lexical_cast<string>(UnitPointer->Bird.MoveSound));
			Units_ComboBox_MoveSound->SetSelection(UnitPointer->Bird.MoveSound + 1);
			Units_AnimalMode->ChangeValue(lexical_cast<string>((short)UnitPointer->Bird.AnimalMode));
			Units_CheckBox_AnimalMode->SetValue((bool)UnitPointer->Bird.AnimalMode);
		}
		case 30:
		{
			for(short loop = 0; loop < 2; loop++)
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
			Units_Unknown16->Enable(true);
			for(short loop = 0; loop < Units_Unknown16B.size(); loop++)
			Units_Unknown16B[loop]->Enable(true);

			Units_WalkingGraphic[0]->ChangeValue(lexical_cast<string>(UnitPointer->DeadFish.WalkingGraphic.first));
			Units_ComboBox_WalkingGraphic[0]->SetSelection(UnitPointer->DeadFish.WalkingGraphic.first + 1);
			Units_WalkingGraphic[1]->ChangeValue(lexical_cast<string>(UnitPointer->DeadFish.WalkingGraphic.second));
			Units_ComboBox_WalkingGraphic[1]->SetSelection(UnitPointer->DeadFish.WalkingGraphic.second + 1);
			Units_RotationSpeed->ChangeValue(lexical_cast<string>(UnitPointer->DeadFish.RotationSpeed));
			Units_Unknown11->ChangeValue(lexical_cast<string>((short)UnitPointer->DeadFish.Unknown11));
			Units_TrackingUnit->ChangeValue(lexical_cast<string>(UnitPointer->DeadFish.TrackingUnit));
			Units_ComboBox_TrackingUnit->SetSelection(UnitPointer->DeadFish.TrackingUnit + 1);
			Units_TrackingUnitUsed->ChangeValue(lexical_cast<string>((short)UnitPointer->DeadFish.TrackingUnitUsed));
			Units_TrackingUnitDensity->ChangeValue(lexical_cast<string>(UnitPointer->DeadFish.TrackingUnitDensity));
			Units_Unknown16->ChangeValue(lexical_cast<string>((short)UnitPointer->DeadFish.Unknown16));
			if(GenieVersion >= genie::GV_AoK)
			{
				Units_Unknown12->ChangeValue(lexical_cast<string>(UnitPointer->DeadFish.Unknown12));
				for(short loop = 0; loop < Units_Unknown16B.size(); loop++)
				{
					Units_Unknown16B[loop]->ChangeValue(lexical_cast<string>((short)UnitPointer->DeadFish.Unknown16B[loop]));
				}
			}
		}
		case 25:
		case 20:
		{
			Units_Speed->Enable(true);
			Units_Speed->ChangeValue(lexical_cast<string>(UnitPointer->Speed));
		}
	}
	Units_ID1->ChangeValue(lexical_cast<string>(UnitPointer->ID1));
	Units_LanguageDLLName->ChangeValue(lexical_cast<string>(UnitPointer->LanguageDLLName));
	Units_DLL_LanguageName->index = UnitPointer->LanguageDLLName;
	Units_DLL_LanguageName->SetLabel(LangDLLstring(UnitPointer->LanguageDLLName, 64));
	Units_LanguageDLLCreation->ChangeValue(lexical_cast<string>(UnitPointer->LanguageDLLCreation));
	Units_DLL_LanguageCreation->index = UnitPointer->LanguageDLLCreation;
	Units_DLL_LanguageCreation->SetLabel(LangDLLstring(UnitPointer->LanguageDLLCreation, 64));
	Units_Class->ChangeValue(lexical_cast<string>(UnitPointer->Class));
	Units_ComboBox_Class[0]->SetSelection(UnitPointer->Class + 1);
	Units_StandingGraphic[0]->ChangeValue(lexical_cast<string>(UnitPointer->StandingGraphic.first));
	Units_ComboBox_StandingGraphic[0]->SetSelection(UnitPointer->StandingGraphic.first + 1);
	Units_DyingGraphic[0]->ChangeValue(lexical_cast<string>(UnitPointer->DyingGraphic.first));
	Units_ComboBox_DyingGraphic[0]->SetSelection(UnitPointer->DyingGraphic.first + 1);
	Units_DyingGraphic[1]->ChangeValue(lexical_cast<string>(UnitPointer->DyingGraphic.second));
	Units_ComboBox_DyingGraphic[1]->SetSelection(UnitPointer->DyingGraphic.second + 1);
	Units_DeathMode->ChangeValue(lexical_cast<string>((short)UnitPointer->DeathMode));
	Units_CheckBox_DeathMode->SetValue((bool)UnitPointer->DeathMode);
	Units_HitPoints->ChangeValue(lexical_cast<string>(UnitPointer->HitPoints));
	Units_LineOfSight->ChangeValue(lexical_cast<string>(UnitPointer->LineOfSight));
	Units_GarrisonCapacity->ChangeValue(lexical_cast<string>((short)UnitPointer->GarrisonCapacity));
	Units_SizeRadius[0]->ChangeValue(lexical_cast<string>(UnitPointer->SizeRadius.first));
	Units_SizeRadius[1]->ChangeValue(lexical_cast<string>(UnitPointer->SizeRadius.second));
	Units_HPBarHeight1->ChangeValue(lexical_cast<string>(UnitPointer->HPBarHeight1));
	Units_TrainSound[0]->ChangeValue(lexical_cast<string>(UnitPointer->TrainSound.first));
	Units_ComboBox_TrainSound[0]->SetSelection(UnitPointer->TrainSound.first + 1);
	Units_DeadUnitID->ChangeValue(lexical_cast<string>(UnitPointer->DeadUnitID));
	Units_ComboBox_DeadUnitID->SetSelection(UnitPointer->DeadUnitID + 1);
	Units_PlacementMode->ChangeValue(lexical_cast<string>((short)UnitPointer->PlacementMode));
	Units_AirMode->ChangeValue(lexical_cast<string>((short)UnitPointer->AirMode));
	Units_CheckBox_AirMode->SetValue((bool)UnitPointer->AirMode);
	Units_IconID->ChangeValue(lexical_cast<string>(UnitPointer->IconID));
	Units_HideInEditor->ChangeValue(lexical_cast<string>((short)UnitPointer->HideInEditor));
	Units_CheckBox_HideInEditor->SetValue((bool)UnitPointer->HideInEditor);
	Units_Unknown1->ChangeValue(lexical_cast<string>(UnitPointer->Unknown1));
	Units_CheckBox_Enabled->SetValue((bool)UnitPointer->Enabled);
	Units_PlacementBypassTerrain[0]->ChangeValue(lexical_cast<string>(UnitPointer->PlacementBypassTerrain.first));
	Units_ComboBox_PlacementBypassTerrain[0]->SetSelection(UnitPointer->PlacementBypassTerrain.first + 1);
	Units_PlacementBypassTerrain[1]->ChangeValue(lexical_cast<string>(UnitPointer->PlacementBypassTerrain.second));
	Units_ComboBox_PlacementBypassTerrain[1]->SetSelection(UnitPointer->PlacementBypassTerrain.second + 1);
	Units_PlacementTerrain[0]->ChangeValue(lexical_cast<string>(UnitPointer->PlacementTerrain.first));
	Units_ComboBox_PlacementTerrain[0]->SetSelection(UnitPointer->PlacementTerrain.first + 1);
	Units_PlacementTerrain[1]->ChangeValue(lexical_cast<string>(UnitPointer->PlacementTerrain.second));
	Units_ComboBox_PlacementTerrain[1]->SetSelection(UnitPointer->PlacementTerrain.second + 1);
	Units_EditorRadius[0]->ChangeValue(lexical_cast<string>(UnitPointer->EditorRadius.first));
	Units_EditorRadius[1]->ChangeValue(lexical_cast<string>(UnitPointer->EditorRadius.second));
	Units_BuildingMode->ChangeValue(lexical_cast<string>((short)UnitPointer->BuildingMode));
	Units_VisibleInFog->ChangeValue(lexical_cast<string>((short)UnitPointer->VisibleInFog));
	Units_TerrainRestriction->ChangeValue(lexical_cast<string>(UnitPointer->TerrainRestriction));
	Units_ComboBox_TerrainRestriction->SetSelection(UnitPointer->TerrainRestriction + 1);
	Units_FlyMode->ChangeValue(lexical_cast<string>((short)UnitPointer->FlyMode));
	Units_CheckBox_FlyMode->SetValue((bool)UnitPointer->FlyMode);
	Units_ResourceCapacity->ChangeValue(lexical_cast<string>(UnitPointer->ResourceCapacity));
	Units_ResourceDecay->ChangeValue(lexical_cast<string>(UnitPointer->ResourceDecay));
	Units_BlastType->ChangeValue(lexical_cast<string>((short)UnitPointer->BlastType));
	Units_Unknown2->ChangeValue(lexical_cast<string>((short)UnitPointer->Unknown2));
	Units_InteractionMode->ChangeValue(lexical_cast<string>((short)UnitPointer->InteractionMode));
	Units_MinimapMode->ChangeValue(lexical_cast<string>((short)UnitPointer->MinimapMode));
	Units_SelectionEffect->ChangeValue(lexical_cast<string>((short)UnitPointer->SelectionEffect));
	Units_EditorSelectionColour->ChangeValue(lexical_cast<string>((short)UnitPointer->EditorSelectionColour));
	if(GenieVersion >= genie::GV_AoKA)
	{
		Units_DLL_LanguageHelp->index = UnitPointer->LanguageDLLHelp - 79000;
		Units_DLL_LanguageHKText->index = UnitPointer->LanguageDLLHotKeyText - 140000;
		Units_TrainSound[1]->ChangeValue(lexical_cast<string>(UnitPointer->TrainSound.second));
		Units_ComboBox_TrainSound[1]->SetSelection(UnitPointer->TrainSound.second + 1);
		Units_Unknown7->ChangeValue(lexical_cast<string>((short)UnitPointer->Unknown7));
		Units_Unknown8->ChangeValue(lexical_cast<string>((short)UnitPointer->Unknown8));
		Units_SelectionShapeType->ChangeValue(lexical_cast<string>((short)UnitPointer->SelectionShapeType));
		Units_ID3->ChangeValue(lexical_cast<string>(UnitPointer->ID3));
	}
	else
	{
		Units_DLL_LanguageHelp->index = (uint16_t)UnitPointer->LanguageDLLHelp;
		Units_DLL_LanguageHKText->index = (uint16_t)UnitPointer->LanguageDLLHotKeyText;
	}
	if(GenieVersion >= genie::GV_AoK)
	{
		Units_StandingGraphic[1]->ChangeValue(lexical_cast<string>(UnitPointer->StandingGraphic.second));
		Units_ComboBox_StandingGraphic[1]->SetSelection(UnitPointer->StandingGraphic.second + 1);
		Units_Enabled->SetBackgroundColour(wxColour(210, 230, 255));
		Units_Enabled->ChangeValue(lexical_cast<string>(UnitPointer->Enabled));
		if(GenieVersion >= genie::GV_TC)
		{
			Units_Attribute->ChangeValue(lexical_cast<string>((short)UnitPointer->Attribute));
			Units_Civ->ChangeValue(lexical_cast<string>((short)UnitPointer->Civilization));
			Units_ComboBox_Civ->SetSelection(UnitPointer->Civilization + 1);
			Units_Unknown9->ChangeValue(lexical_cast<string>(UnitPointer->Unknown9));
			if(GenieVersion >= genie::GV_SWGB)
			{
				Units_Name2->ChangeValue(lexical_cast<string>(UnitPointer->Name2));
				Units_Unitline->ChangeValue(lexical_cast<string>(UnitPointer->Unitline));
				Units_ComboBox_Unitline->SetSelection(UnitPointer->Unitline + 1);
				Units_MinTechLevel->ChangeValue(lexical_cast<string>((short)UnitPointer->MinTechLevel));
			}
		}
	}
	else
	{
		Units_Enabled->SetBackgroundColour(wxColour(255, 235, 215));
		Units_Enabled->ChangeValue(lexical_cast<string>((short)UnitPointer->Enabled));
	}
	Units_CommandAttribute->ChangeValue(lexical_cast<string>(UnitPointer->CommandAttribute));
	for(short loop = 0; loop < Units_Unknown3.size(); loop++)
	Units_Unknown3[loop]->ChangeValue(lexical_cast<string>((short)UnitPointer->Unknown3[loop]));
	Units_LanguageDLLHelp->ChangeValue(lexical_cast<string>(UnitPointer->LanguageDLLHelp));
	Units_DLL_LanguageHelp->SetLabel(LangDLLstring(Units_DLL_LanguageHelp->index, 512));
	Units_LanguageDLLConverter[0]->SetLabel(lexical_cast<string>(Units_DLL_LanguageHelp->index));
	Units_LanguageDLLHotKeyText->ChangeValue(lexical_cast<string>(UnitPointer->LanguageDLLHotKeyText));
	Units_DLL_LanguageHKText->SetLabel(LangDLLstring(Units_DLL_LanguageHKText->index, 64));
	Units_LanguageDLLConverter[1]->SetLabel(lexical_cast<string>(Units_DLL_LanguageHKText->index));
	Units_HotKey->ChangeValue(lexical_cast<string>(UnitPointer->HotKey));
	Units_DLL_HotKey4->index = UnitPointer->HotKey;
	Units_DLL_HotKey4->SetLabel(LangDLLstring(UnitPointer->HotKey, 16));
	Units_Unselectable->ChangeValue(lexical_cast<string>((short)UnitPointer->Unselectable));
	Units_CheckBox_Unselectable->SetValue((bool)UnitPointer->Unselectable);
	Units_Unknown6->ChangeValue(lexical_cast<string>((short)UnitPointer->Unknown6));
	Units_SelectionMask->ChangeValue(lexical_cast<string>((short)UnitPointer->SelectionMask));
	Units_SelectionShape->ChangeValue(lexical_cast<string>((short)UnitPointer->SelectionShape));
	Units_SelectionRadius[0]->ChangeValue(lexical_cast<string>(UnitPointer->SelectionRadius.first));
	Units_SelectionRadius[1]->ChangeValue(lexical_cast<string>(UnitPointer->SelectionRadius.second));
	Units_HPBarHeight2->ChangeValue(lexical_cast<string>(UnitPointer->HPBarHeight2));
	Units_SelectionSound->ChangeValue(lexical_cast<string>(UnitPointer->SelectionSound));
	Units_ComboBox_SelectionSound->SetSelection(UnitPointer->SelectionSound + 1);
	Units_DyingSound->ChangeValue(lexical_cast<string>(UnitPointer->DyingSound));
	Units_ComboBox_DyingSound->SetSelection(UnitPointer->DyingSound + 1);
	Units_AttackMode->ChangeValue(lexical_cast<string>(UnitPointer->AttackMode));
	Units_Name->ChangeValue(lexical_cast<string>(UnitPointer->Name));
	Units_ID2->ChangeValue(lexical_cast<string>(UnitPointer->ID2));
	for(short loop = 0; loop < 3; loop++)
	{
		ResourceStorage_Type[loop]->ChangeValue(lexical_cast<string>(UnitPointer->ResourceStorages[loop].Type));
		ResourceStorage_Amount[loop]->ChangeValue(lexical_cast<string>(UnitPointer->ResourceStorages[loop].Amount));
		ResourceStorage_Enabled[loop]->ChangeValue(lexical_cast<string>((short)UnitPointer->ResourceStorages[loop].Enabled));
		ResourceStorage_ComboBox_Type[loop]->SetSelection(UnitPointer->ResourceStorages[loop].Type + 1);
	}

	switch(UnitType) // Disable editing
	{
		case 10:
		{
			Units_Speed->Enable(false);
			Units_Speed->ChangeValue("0");
		}
		case 20:
		case 25:
		{
			for(short loop = 0; loop < 2; loop++)
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
			Units_Unknown16->Enable(false);
			Units_Unknown16->ChangeValue("0");
			for(short loop = 0; loop < Units_Unknown16B.size(); loop++)
			{
				Units_Unknown16B[loop]->Enable(false);
				Units_Unknown16B[loop]->ChangeValue("0");
			}
		}
		case 30:
		{
			Units_SheepConversion->Enable(false);
			Units_SheepConversion->ChangeValue("0");
			Units_CheckBox_SheepConversion->Enable(false);
			Units_CheckBox_SheepConversion->SetValue(false);
			Units_SearchRadius->Enable(false);
			Units_SearchRadius->ChangeValue("0");
			Units_WorkRate->Enable(false);
			Units_WorkRate->ChangeValue("0");
			for(short loop = 0; loop < 2; loop++)
			{
				Units_DropSite[loop]->Enable(false);
				Units_DropSite[loop]->ChangeValue("0");
				Units_ComboBox_DropSite[loop]->Enable(false);
				Units_ComboBox_DropSite[loop]->SetSelection(0);
			}
			Units_VillagerMode->Enable(false);
			Units_VillagerMode->ChangeValue("0");
			Units_AttackSound->Enable(false);
			Units_AttackSound->ChangeValue("0");
			Units_ComboBox_AttackSound->Enable(false);
			Units_ComboBox_AttackSound->SetSelection(0);
			Units_MoveSound->Enable(false);
			Units_MoveSound->ChangeValue("0");
			Units_ComboBox_MoveSound->Enable(false);
			Units_ComboBox_MoveSound->SetSelection(0);
			Units_AnimalMode->Enable(false);
			Units_AnimalMode->ChangeValue("0");
			Units_CheckBox_AnimalMode->Enable(false);
			Units_CheckBox_AnimalMode->SetValue(false);
		}
		case 40:
		{
			for(short loop = 0; loop < 2; loop++)
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
			for(short loop = 0; loop < 3; loop++)
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
			for(short loop = 0; loop < 2; loop++)
			Attacks_ComboBox_Class[loop]->Enable(false);
			Attacks_Amount->Enable(false);
			Armors_Class->Enable(false);
			Armors_Amount->Enable(false);
		}
		case 60:
		{
			for(short loop = 0; loop < 2; loop++)
			{
				Units_GarrisonGraphic[loop]->Enable(false);
				Units_GarrisonGraphic[loop]->ChangeValue("0");
				Units_ComboBox_GarrisonGraphic[loop]->Enable(false);
				Units_ComboBox_GarrisonGraphic[loop]->SetSelection(0);
			}
			for(short loop = 0; loop < 3; loop++)
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
			Units_Unknown27->Enable(false);
			Units_Unknown27->ChangeValue("0");
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
		case 70:
		{
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
			for(short loop = 0; loop < 4; loop++)
			{
				Units_AnnexUnit[loop]->Enable(false);
				Units_AnnexUnit[loop]->ChangeValue("0");
				Units_ComboBox_AnnexUnit[loop]->Enable(false);
				Units_ComboBox_AnnexUnit[loop]->SetSelection(0);
				for(short loop2 = 0; loop2 < 2; loop2++)
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
			for(short loop = 0; loop < Units_AlfaThingy.size(); loop++)
			{
				Units_AlfaThingy[loop]->Enable(false);
				Units_AlfaThingy[loop]->ChangeValue("0");
			}
		}
	}

	if(UnitType == 60)
	{
		Units_StretchMode->Enable(true);
		Units_CompensationMode->Enable(true);
		Units_DropAnimationMode->Enable(true);
		Units_PenetrationMode->Enable(true);
		Units_Unknown24->Enable(true);
		Units_ProjectileArc->Enable(true);

		Units_StretchMode->ChangeValue(lexical_cast<string>((short)UnitPointer->ProjectileOnly.StretchMode));
		Units_CompensationMode->ChangeValue(lexical_cast<string>((short)UnitPointer->ProjectileOnly.CompensationMode));
		Units_DropAnimationMode->ChangeValue(lexical_cast<string>((short)UnitPointer->ProjectileOnly.DropAnimationMode));
		Units_PenetrationMode->ChangeValue(lexical_cast<string>((short)UnitPointer->ProjectileOnly.PenetrationMode));
		Units_Unknown24->ChangeValue(lexical_cast<string>((short)UnitPointer->ProjectileOnly.Unknown24));
		Units_ProjectileArc->ChangeValue(lexical_cast<string>(UnitPointer->ProjectileOnly.ProjectileArc));
	}
	else
	{
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

	// Don't count disabled units anymore.
	for(short loop = SelectedCivs.size(); loop--> 0;)
	{
		if(GenieFile->Civs[SelectedCivs[loop]].UnitPointers[UnitIDs[0]] == 0)
			SelectedCivs.erase(SelectedCivs.begin() + loop);
	}

	ListUnitDamageGraphics();
	ListUnitAttacks();
	ListUnitArmors();
	if(GenieVersion >= genie::GV_AoK)	// AoK, TC, SWGB or CC
	{
		Units_Exists->resize(Selections);

		genie::UnitHeader * UnitHeadPointer;
		for(auto sel = Selections; sel--> 0;)
		{
			UnitHeadPointer = &GenieFile->UnitHeaders[UnitIDs[sel]];

			Units_Exists->container[sel] = &UnitHeadPointer->Exists;
		}

		Units_UnitHeads_Name->SetLabel(" "+lexical_cast<string>(UnitIDs[0])+" - "+GetUnitName(UnitIDs[0], 0));
		Units_Exists->ChangeValue(lexical_cast<string>((short)UnitHeadPointer->Exists));
	}
	else	// AoE or RoR
	{
		Units_UnitHeads_Name->SetLabel("");
	}
	ListUnitCommands();
	//	Refresh(); // Too much lag.
}

void AGE_Frame::OnUnitsAdd(wxCommandEvent &Event)
{
	if(GenieFile == NULL) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion >= genie::GV_AoK)	// AoK, TC, SWGB or CC
	{
		genie::UnitHeader Temp1;
		Temp1.setGameVersion(GenieVersion);
		GenieFile->UnitHeaders.push_back(Temp1);
	}

	genie::Unit Temp2;
	Temp2.setGameVersion(GenieVersion);
	for(short loop = 0; loop < GenieFile->Civs.size(); loop++)
	{
		GenieFile->Civs[loop].Units.push_back(Temp2);
		GenieFile->Civs[loop].UnitPointers.push_back(1);
		if(EnableIDFix)
		{
			GenieFile->Civs[loop].Units[GenieFile->Civs[0].Units.size()-1].ID1 = (int16_t)(GenieFile->Civs[0].Units.size()-1); // ID Fix
			GenieFile->Civs[loop].Units[GenieFile->Civs[0].Units.size()-1].ID2 = (int16_t)(GenieFile->Civs[0].Units.size()-1);
			if(GenieVersion >= genie::GV_AoK)
			GenieFile->Civs[loop].Units[GenieFile->Civs[0].Units.size()-1].ID3 = (int16_t)(GenieFile->Civs[0].Units.size()-1);
		}
	}
	Added = true;
	ListUnits(UnitCivID);

	if(GenieVersion <= genie::GV_TC && GenieFile->Civs[0].Units.size() > 900) SetStatusText("Units over 900 mess up the AI!!!", 0);
}

void AGE_Frame::OnUnitsInsert(wxCommandEvent &Event)
{
	auto Selections = Units_Units_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion >= genie::GV_AoK)	// AoK, TC, SWGB or CC
	{
		genie::UnitHeader Temp1;
		Temp1.setGameVersion(GenieVersion);
		GenieFile->UnitHeaders.insert(GenieFile->UnitHeaders.begin() + UnitIDs[0], Temp1);
	}

	genie::Unit Temp2;
	Temp2.setGameVersion(GenieVersion);
	for(short loop = 0; loop < GenieFile->Civs.size(); loop++)
	{
		GenieFile->Civs[loop].Units.insert(GenieFile->Civs[loop].Units.begin() + UnitIDs[0], Temp2);
		GenieFile->Civs[loop].UnitPointers.insert(GenieFile->Civs[loop].UnitPointers.begin() + UnitIDs[0], 1);
		if(EnableIDFix)
		for(short loop2 = UnitIDs[0];loop2 < GenieFile->Civs[0].Units.size(); loop2++) // ID Fix
		{
			GenieFile->Civs[loop].Units[loop2].ID1 = loop2;
			GenieFile->Civs[loop].Units[loop2].ID2 = loop2;
			if(GenieVersion >= genie::GV_AoK)
			GenieFile->Civs[loop].Units[loop2].ID3 = loop2;
		}
	}
	ListUnits(UnitCivID);
}

void AGE_Frame::OnUnitsDelete(wxCommandEvent &Event)
{
	auto Selections = Units_Units_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion >= genie::GV_AoK)
	{
		for(auto loop = Selections; loop--> 0;)
		GenieFile->UnitHeaders.erase(GenieFile->UnitHeaders.begin() + UnitIDs[loop]);
	}

	for(short civ = 0; civ < GenieFile->Civs.size(); civ++)
	{
		for(auto loop = Selections; loop--> 0;)
		{
			GenieFile->Civs[civ].Units.erase(GenieFile->Civs[civ].Units.begin() + UnitIDs[loop]);
			GenieFile->Civs[civ].UnitPointers.erase(GenieFile->Civs[civ].UnitPointers.begin() + UnitIDs[loop]);
		}
		if(EnableIDFix)
		for(short loop = UnitIDs[0]; loop < GenieFile->Civs[0].Units.size(); loop++) // ID Fix
		{
			GenieFile->Civs[civ].Units[loop].ID1 = loop;
			GenieFile->Civs[civ].Units[loop].ID2 = loop;
			if(GenieVersion >= genie::GV_AoK)
			GenieFile->Civs[civ].Units[loop].ID3 = loop;
		}
	}
	ListUnits(UnitCivID);
}

void AGE_Frame::OnUnitsCopy(wxCommandEvent &Event)
{
	auto Selections = Units_Units_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion >= genie::GV_AoK)
	{
		copies->UnitHeader.resize(Selections);
		for(short loop = 0; loop < Selections; loop++)
		copies->UnitHeader[loop] = GenieFile->UnitHeaders[UnitIDs[loop]];
	}

	short CivCount = GenieFile->Civs.size();
	copies->Dat.UnitExists.resize(CivCount);
	if(Units_SpecialCopy_Civs->GetValue()) copies->Dat.AllCivs |= 0x01; else copies->Dat.AllCivs &= ~0x01;
	if(copies->Dat.AllCivs & 0x01)
	{
		copies->Dat.UnitCopies.resize(CivCount);
		for(short civ = 0; civ < CivCount; civ++)
		{
			copies->Dat.UnitExists[civ].resize(Selections);
			copies->Dat.UnitCopies[civ].resize(Selections);
			for(short loop = 0; loop < Selections; loop++)
			{
				copies->Dat.UnitExists[civ][loop] = (bool)GenieFile->Civs[civ].UnitPointers[UnitIDs[loop]];
				copies->Dat.UnitCopies[civ][loop] = GenieFile->Civs[civ].Units[UnitIDs[loop]];
			}
		}
	}
	else
	{
		copies->Dat.UnitGraphics.resize(CivCount);
		for(short civ = 0; civ < CivCount; civ++)
		{
			copies->Dat.UnitExists[civ].resize(Selections);
			if(AutoCopy && !CopyGraphics)
			copies->Dat.UnitGraphics[civ].resize(Selections);
			for(short loop = 0; loop < Selections; loop++)
			{
				copies->Dat.UnitExists[civ][loop] = (bool)GenieFile->Civs[civ].UnitPointers[UnitIDs[loop]];
				if(AutoCopy && !CopyGraphics)
				{// Let's copy graphics separately.
					// Collects only graphic data, not all data again.
					UnitsGraphicsCopy(copies->Dat.UnitGraphics[civ][loop], civ, UnitIDs[loop]);
				}
			}
		}
		copies->Dat.UnitCopies[0].resize(Selections);
		for(short loop = 0; loop < Selections; loop++)
		copies->Dat.UnitCopies[0][loop] = GenieFile->Civs[UnitCivID].Units[UnitIDs[loop]];
	}
}

void AGE_Frame::OnAutoCopy(wxCommandEvent &Event)
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
	else if(Event.GetId() == Units_SelectAll->GetId())
	{
		for(short loop = 0; loop < GenieFile->Civs.size(); loop++)
		Units_CivBoxes[loop]->SetValue(true);
	}
	else if(Event.GetId() == Units_SelectClear->GetId())
	{
		for(short loop = 0; loop < GenieFile->Civs.size(); loop++)
		Units_CivBoxes[loop]->SetValue(false);
	}
	else if(Event.GetId() == Units_GraphicSet->GetId())
	{
		short Selection = Units_GraphicSet->GetSelection();
		for(short loop = 0; loop < GenieFile->Civs.size(); loop++)
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
	// This ensures that proper data pointers are assigned to editing boxes.
	// MAKE THIS SO THAT THE SELECTIONS REMAIN!!!
	wxCommandEvent E;
	OnUnitsSelect(E);
}

void AGE_Frame::UnitsAutoCopy(wxCommandEvent &Event)
{
	auto Selections = Units_Units_List->GetSelections(Items);
	if(Selections < 1) return;

	GraphicCopies graphics;
	for(short civ = 0; civ < GenieFile->Civs.size(); civ++)
	{
		if(Units_CivBoxes[civ]->IsChecked() && civ != UnitCivID)
		{
			for(short loop = 0; loop < Selections; loop++)
			{
				if(!CopyGraphics)// Let's copy graphics separately.
				UnitsGraphicsCopy(graphics, civ, UnitIDs[loop]);
				GenieFile->Civs[civ].Units[UnitIDs[loop]] = GenieFile->Civs[UnitCivID].Units[UnitIDs[loop]];
				if(!CopyGraphics)// Let's paste graphics separately.
				UnitsGraphicsPaste(graphics, civ, UnitIDs[loop]);
			}
		}
	}
}

void AGE_Frame::UnitsGraphicsCopy(GraphicCopies &store, short civ, short unit)
{
	store.IconID = GenieFile->Civs[civ].Units[unit].IconID;// This probably shouldn't be here.
	store.StandingGraphic = GenieFile->Civs[civ].Units[unit].StandingGraphic;
	store.DyingGraphic = GenieFile->Civs[civ].Units[unit].DyingGraphic;
	store.DamageGraphics = GenieFile->Civs[civ].Units[unit].DamageGraphics;
	switch((short)GenieFile->Civs[civ].Units[unit].Type)
	{
		case 80:
		store.ConstructionGraphicID = GenieFile->Civs[civ].Units[unit].Building.ConstructionGraphicID;
		store.SnowGraphicID = GenieFile->Civs[civ].Units[unit].Building.SnowGraphicID;
		case 70:
		store.GarrisonGraphic = GenieFile->Civs[civ].Units[unit].Creatable.GarrisonGraphic;
		case 60:
		store.AttackGraphic = GenieFile->Civs[civ].Units[unit].Projectile.AttackGraphic;
		case 40:
		case 30:
		store.WalkingGraphic = GenieFile->Civs[civ].Units[unit].DeadFish.WalkingGraphic;
	}
}

void AGE_Frame::OnUnitsSpecialCopy(wxCommandEvent &Event)
{
	auto Selections = Units_Units_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Units_SpecialCopy_Civs->GetValue()) copies->Dat.AllCivs |= 0x02; else copies->Dat.AllCivs &= ~0x02;
	if(copies->Dat.AllCivs & 0x02)
	{
		short CivCount = GenieFile->Civs.size();
		copies->Dat.UnitGraphics.resize(CivCount);
		for(short civ = 0; civ < CivCount; civ++)
		{
			copies->Dat.UnitGraphics[civ].resize(Selections);
			for(short loop = 0; loop < Selections; loop++)
			UnitsGraphicsCopy(copies->Dat.UnitGraphics[civ][loop], civ, UnitIDs[loop]);
		}
	}
	else
	{
		copies->Dat.UnitGraphics[0].resize(Selections);
		for(short loop = 0; loop < Selections; loop++)
		UnitsGraphicsCopy(copies->Dat.UnitGraphics[0][loop], UnitCivID, UnitIDs[loop]);
	}
}

void AGE_Frame::OnUnitsPaste(wxCommandEvent &Event)
{
	if(Units_Units_List->GetSelections(Items) < 1) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion >= genie::GV_AoK)
	{
		if(copies->UnitHeader.size()+UnitIDs[0] > GenieFile->UnitHeaders.size())
		GenieFile->UnitHeaders.resize(copies->UnitHeader.size()+UnitIDs[0]);
		for(short loop = 0; loop < copies->UnitHeader.size(); loop++)
		{
			copies->UnitHeader[loop].setGameVersion(GenieVersion);
			GenieFile->UnitHeaders[UnitIDs[0]+loop] = copies->UnitHeader[loop];
		}
	}

	if(copies->Dat.UnitCopies[0].size()+UnitIDs[0] > GenieFile->Civs[0].Units.size())
	for(short civ = 0; civ < GenieFile->Civs.size(); civ++) // Resize if not enough room.
	{
		GenieFile->Civs[civ].Units.resize(copies->Dat.UnitCopies[0].size()+UnitIDs[0]);
		GenieFile->Civs[civ].UnitPointers.resize(copies->Dat.UnitCopies[0].size()+UnitIDs[0]);
	}
	PasteUnits();
	for(short civ = 0; civ < GenieFile->Civs.size(); civ++)
	{
		for(short loop = 0; loop < copies->Dat.UnitCopies[0].size(); loop++)
		{
			GenieFile->Civs[civ].UnitPointers[UnitIDs[0]+loop] = (int32_t)copies->Dat.UnitExists[civ][loop];
			if(EnableIDFix) // ID Fix
			{
				GenieFile->Civs[civ].Units[UnitIDs[0]+loop].ID1 = (int16_t)(UnitIDs[0]+loop);
				GenieFile->Civs[civ].Units[UnitIDs[0]+loop].ID2 = (int16_t)(UnitIDs[0]+loop);
				if(GenieVersion >= genie::GV_AoK)
				GenieFile->Civs[civ].Units[UnitIDs[0]+loop].ID3 = (int16_t)(UnitIDs[0]+loop);
			}
		}
	}
	ListUnits(UnitCivID);
}

void AGE_Frame::OnUnitsPasteInsert(wxCommandEvent &Event)
{
	if(Units_Units_List->GetSelections(Items) < 1) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion >= genie::GV_AoK)
	{
		genie::UnitHeader Temp1;
		GenieFile->UnitHeaders.insert(GenieFile->UnitHeaders.begin() + UnitIDs[0], copies->UnitHeader.size(), Temp1);
		for(short loop = 0; loop < copies->UnitHeader.size(); loop++)
		{
			copies->UnitHeader[loop].setGameVersion(GenieVersion);
			GenieFile->UnitHeaders[UnitIDs[0]+loop] = copies->UnitHeader[loop];
		}
	}

	genie::Unit Temp2;
	for(short civ = 0; civ < GenieFile->Civs.size(); civ++)
	{
		GenieFile->Civs[civ].Units.insert(GenieFile->Civs[civ].Units.begin() + UnitIDs[0], copies->Dat.UnitCopies[0].size(), Temp2);
		GenieFile->Civs[civ].UnitPointers.insert(GenieFile->Civs[civ].UnitPointers.begin() + UnitIDs[0], copies->Dat.UnitCopies[0].size(), 0);
	}
	PasteUnits();
	for(short civ = 0; civ < GenieFile->Civs.size(); civ++)
	{
		for(short loop = 0; loop < copies->Dat.UnitCopies[0].size(); loop++)
		{
			GenieFile->Civs[civ].UnitPointers[UnitIDs[0]+loop] = (int32_t)copies->Dat.UnitExists[civ][loop];
		}
		if(EnableIDFix) // ID Fix
		for(short loop = UnitIDs[0];loop < GenieFile->Civs[0].Units.size(); loop++)
		{
			GenieFile->Civs[civ].Units[loop].ID1 = loop;
			GenieFile->Civs[civ].Units[loop].ID2 = loop;
			if(GenieVersion >= genie::GV_AoK)
			GenieFile->Civs[civ].Units[loop].ID3 = loop;
		}
	}
	ListUnits(UnitCivID);
}

void AGE_Frame::PasteUnits()
{
	// The civ amount of copy data must be set on copying!
	// Otherwise having more than one window open with different civ count creates problems!
	short CivCount = GenieFile->Civs.size();
	short FillingCiv = (copies->Dat.UnitExists.size() > 1) ? 1 : 0;
	copies->Dat.UnitExists.resize(CivCount, copies->Dat.UnitExists[FillingCiv]);
	if(copies->Dat.AllCivs & 0x01) // Paste from all civs to all civs.
	{
		copies->Dat.UnitCopies.resize(CivCount, copies->Dat.UnitCopies[FillingCiv]);
		for(short civ = 0; civ < CivCount; civ++)
		{
			for(short loop = 0; loop < copies->Dat.UnitCopies[0].size(); loop++) // Selections
			{
				copies->Dat.UnitCopies[civ][loop].setGameVersion(GenieVersion);
				GenieFile->Civs[civ].Units[UnitIDs[0]+loop] = copies->Dat.UnitCopies[civ][loop];
			}
		}
	}
	else
	{
		if(AutoCopy) // Paste from one civ to selected civs.
		{
			copies->Dat.UnitGraphics.resize(CivCount, copies->Dat.UnitGraphics[FillingCiv]);
			for(short civ = 0; civ < CivCount; civ++)
			{
				if(Units_CivBoxes[civ]->IsChecked())
				{
					for(short loop = 0; loop < copies->Dat.UnitCopies[0].size(); loop++)
					{
						copies->Dat.UnitCopies[0][loop].setGameVersion(GenieVersion);
						GenieFile->Civs[civ].Units[UnitIDs[0]+loop] = copies->Dat.UnitCopies[0][loop];
						if(!CopyGraphics)
						{// Let's paste graphics separately.
							UnitsGraphicsPaste(copies->Dat.UnitGraphics[civ][loop], civ, UnitIDs[0]+loop);
						}
					}
				}
			}
		}
		else // Paste from one civ to another civ.
		{
			for(short loop = 0; loop < copies->Dat.UnitCopies[0].size(); loop++)
			{
				copies->Dat.UnitCopies[0][loop].setGameVersion(GenieVersion);
				GenieFile->Civs[UnitCivID].Units[UnitIDs[0]+loop] = copies->Dat.UnitCopies[0][loop];
			}
		}
	}
}

void AGE_Frame::UnitsGraphicsPaste(GraphicCopies &store, short civ, short unit)
{
	GenieFile->Civs[civ].Units[unit].IconID = store.IconID;
	GenieFile->Civs[civ].Units[unit].StandingGraphic = store.StandingGraphic;
	GenieFile->Civs[civ].Units[unit].DyingGraphic = store.DyingGraphic;
	GenieFile->Civs[civ].Units[unit].DamageGraphics = store.DamageGraphics;
	switch((short)GenieFile->Civs[civ].Units[unit].Type)
	{
		case 80:
		GenieFile->Civs[civ].Units[unit].Building.ConstructionGraphicID = store.ConstructionGraphicID;
		GenieFile->Civs[civ].Units[unit].Building.SnowGraphicID = store.SnowGraphicID;
		case 70:
		GenieFile->Civs[civ].Units[unit].Creatable.GarrisonGraphic = store.GarrisonGraphic;
		case 60:
		GenieFile->Civs[civ].Units[unit].Projectile.AttackGraphic = store.AttackGraphic;
		case 40:
		case 30:
		GenieFile->Civs[civ].Units[unit].DeadFish.WalkingGraphic = store.WalkingGraphic;
	}
}

void AGE_Frame::OnUnitsSpecialPaste(wxCommandEvent &Event)
{
	if(Units_Units_List->GetSelections(Items) < 1) return;

	wxBusyCursor WaitCursor;
	short CopyCount = copies->Dat.UnitGraphics[0].size();
	if(copies->Dat.UnitGraphics[0].size()+UnitIDs[0] > GenieFile->Civs[0].Units.size())
	CopyCount -= copies->Dat.UnitGraphics[0].size()+UnitIDs[0] - GenieFile->Civs[0].Units.size();
	if(copies->Dat.AllCivs & 0x02)
	{
		short CivCount = GenieFile->Civs.size();
		short FillingCiv = (copies->Dat.UnitGraphics.size() > 1) ? 1 : 0;
		copies->Dat.UnitGraphics.resize(CivCount, copies->Dat.UnitGraphics[FillingCiv]);
		for(short civ = 0; civ < CivCount; civ++)
		{
			for(short loop = 0; loop < CopyCount; loop++)
			UnitsGraphicsPaste(copies->Dat.UnitGraphics[civ][loop], civ, UnitIDs[0]+loop);
		}
	}
	else
	{
		for(short loop = 0; loop < CopyCount; loop++)
		UnitsGraphicsPaste(copies->Dat.UnitGraphics[0][loop], UnitCivID, UnitIDs[0]+loop);
	}
	wxCommandEvent E;
	OnUnitsSelect(E);
}

void AGE_Frame::OnUnitsEnable(wxCommandEvent &Event)
{
	auto Selections = Units_Units_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	for(short sel = 0; sel < Selections; sel++)
	{
		// Find the correct sizes for subvectors.
		short UnitType = 10, DamageGraphics = 0, Attacks = 0, Armors = 0, Commands = 0;
		for(short civ = 0; civ < GenieFile->Civs.size(); civ++)
		{
			if(GenieFile->Civs[civ].UnitPointers[UnitIDs[sel]] != 0)
			{
				UnitType = GenieFile->Civs[civ].Units[UnitIDs[sel]].Type;
				DamageGraphics = GenieFile->Civs[civ].Units[UnitIDs[sel]].DamageGraphics.size();
				Attacks = GenieFile->Civs[civ].Units[UnitIDs[sel]].Projectile.Attacks.size();
				Armors = GenieFile->Civs[civ].Units[UnitIDs[sel]].Projectile.Armours.size();
				if(GenieVersion <= genie::GV_AoKA)
				Commands = GenieFile->Civs[civ].Units[UnitIDs[sel]].Bird.Commands.size();
				break;
			}
		}
		// All subvectors need to be resized!
		if(Units_SpecialCopy_Civs->GetValue())
		for(short civ = 0; civ < GenieFile->Civs.size(); civ++)
		{
			if(GenieFile->Civs[civ].UnitPointers[UnitIDs[sel]] == 0)
			{
				GenieFile->Civs[civ].UnitPointers[UnitIDs[sel]] = 1;
				GenieFile->Civs[civ].Units[UnitIDs[sel]].Type = UnitType;
				GenieFile->Civs[civ].Units[UnitIDs[sel]].DamageGraphics.resize(DamageGraphics);
				GenieFile->Civs[civ].Units[UnitIDs[sel]].Projectile.Attacks.resize(Attacks);
				GenieFile->Civs[civ].Units[UnitIDs[sel]].Projectile.Armours.resize(Armors);
				GenieFile->Civs[civ].Units[UnitIDs[sel]].Bird.Commands.resize(Commands);
				GenieFile->Civs[civ].Units[UnitIDs[sel]].ID1 = UnitIDs[sel]; // ID Fix
				GenieFile->Civs[civ].Units[UnitIDs[sel]].ID2 = UnitIDs[sel];
				if(GenieVersion >= genie::GV_AoKA)
				GenieFile->Civs[civ].Units[UnitIDs[sel]].ID3 = UnitIDs[sel];
			}
		}
		else
		{
			if(GenieFile->Civs[UnitCivID].UnitPointers[UnitIDs[sel]] == 0)
			{
				GenieFile->Civs[UnitCivID].UnitPointers[UnitIDs[sel]] = 1;
				GenieFile->Civs[UnitCivID].Units[UnitIDs[sel]].Type = UnitType;
				GenieFile->Civs[UnitCivID].Units[UnitIDs[sel]].DamageGraphics.resize(DamageGraphics);
				GenieFile->Civs[UnitCivID].Units[UnitIDs[sel]].Projectile.Attacks.resize(Attacks);
				GenieFile->Civs[UnitCivID].Units[UnitIDs[sel]].Projectile.Armours.resize(Armors);
				GenieFile->Civs[UnitCivID].Units[UnitIDs[sel]].Bird.Commands.resize(Commands);
				GenieFile->Civs[UnitCivID].Units[UnitIDs[sel]].ID1 = UnitIDs[sel]; // ID Fix
				GenieFile->Civs[UnitCivID].Units[UnitIDs[sel]].ID2 = UnitIDs[sel];
				if(GenieVersion >= genie::GV_AoKA)
				GenieFile->Civs[UnitCivID].Units[UnitIDs[sel]].ID3 = UnitIDs[sel];
			}
		}
	}
	ListUnits(UnitCivID);
}

void AGE_Frame::OnUnitsDisable(wxCommandEvent &Event)
{
	auto Selections = Units_Units_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	for(short sel = 0; sel < Selections; sel++)
	{
		if(Units_SpecialCopy_Civs->GetValue())
		for(short civ = 0; civ < GenieFile->Civs.size(); civ++)
		GenieFile->Civs[civ].UnitPointers[UnitIDs[sel]] = 0;
		else
		GenieFile->Civs[UnitCivID].UnitPointers[UnitIDs[sel]] = 0;
	}
	ListUnits(UnitCivID);
}

//	SubVectors

string AGE_Frame::GetUnitDamageGraphicName(short Index)
{
	return lexical_cast<string>((short)GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].DamageGraphics[Index].DamagePercent)
	+" % - ID: "+lexical_cast<string>(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].DamageGraphics[Index].GraphicID)+" ";
}

void AGE_Frame::OnUnitDamageGraphicsSearch(wxCommandEvent &Event)
{
	ListUnitDamageGraphics();
}

void AGE_Frame::ListUnitDamageGraphics()
{
	searchText = Units_DamageGraphics_Search->GetValue().Lower();
	excludeText = Units_DamageGraphics_Search_R->GetValue().Lower();

	auto Selections = Units_DamageGraphics_List->GetSelections(Items);
	Units_DamageGraphics_List->Clear();

	if(GenieFile->Civs[UnitCivID].UnitPointers[UnitIDs[0]] != 0)
	{
		Units_DamageGraphics_Add->Enable(true);
		for(short loop = 0; loop < GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].DamageGraphics.size(); loop++)
		{
			wxString Name = " "+lexical_cast<string>(loop)+" - "+GetUnitDamageGraphicName(loop);
			if(SearchMatches(Name.Lower()))
			{
				Units_DamageGraphics_List->Append(Name, (void*)&GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].DamageGraphics[loop]);
			}
		}
	}
	else
	{
		Units_DamageGraphics_Add->Enable(false);
	}
	ListingFix(Selections, Units_DamageGraphics_List);

	wxCommandEvent E;
	OnUnitDamageGraphicsSelect(E);
}

void AGE_Frame::OnUnitDamageGraphicsSelect(wxCommandEvent &Event)
{
	auto Selections = Units_DamageGraphics_List->GetSelections(Items);
	if(Selections > 0)
	{
		// This and attacks/armors/commands still need a lot of thinking.
		DamageGraphicIDs.resize(Selections);
		int PointerCount = (CopyGraphics) ? Selections * SelectedCivs.size() : Selections;
		DamageGraphics_GraphicID->resize(PointerCount);
		DamageGraphics_DamagePercent->resize(PointerCount);
		DamageGraphics_Unknown1->resize(PointerCount);
		DamageGraphics_Unknown2->resize(PointerCount);

		bool showWarning = false;
		wxString warning = "Damage graphic count of civs\n";
		genie::unit::DamageGraphic * DamageGraphicPointer;
		for(auto sel = Selections; sel--> 0;)
		{
			DamageGraphicPointer = (genie::unit::DamageGraphic*)Units_DamageGraphics_List->GetClientData(Items.Item(sel));
			DamageGraphicIDs[sel] = (DamageGraphicPointer - (&GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].DamageGraphics[0]));

			for(short vecCiv = (CopyGraphics) ? SelectedCivs.size() : 1; vecCiv--> 0;)
			{
				if(sel == 0 && GenieFile->Civs[SelectedCivs[vecCiv]].Units[UnitIDs[0]].DamageGraphics.size() != GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].DamageGraphics.size())
				{
					warning.Append(lexical_cast<string>(SelectedCivs[vecCiv])+" ");
					showWarning = true;
				}
				DamageGraphicPointer = &GenieFile->Civs[SelectedCivs[vecCiv]].Units[UnitIDs[0]].DamageGraphics[DamageGraphicIDs[sel]];

				int location = sel + vecCiv * Selections;
				DamageGraphics_GraphicID->container[location] = &DamageGraphicPointer->GraphicID;
				DamageGraphics_DamagePercent->container[location] = &DamageGraphicPointer->DamagePercent;
				DamageGraphics_Unknown1->container[location] = &DamageGraphicPointer->Unknown1;
				DamageGraphics_Unknown2->container[location] = &DamageGraphicPointer->Unknown2;
			}
		}
		if(showWarning)
		{
			warning.Append("\ndiffers from civ "+lexical_cast<string>(UnitCivID));
			wxMessageBox(warning);
		}

		DamageGraphics_GraphicID->ChangeValue(lexical_cast<string>(DamageGraphicPointer->GraphicID));
		DamageGraphics_ComboBox_GraphicID->SetSelection(DamageGraphicPointer->GraphicID + 1);
		DamageGraphics_DamagePercent->ChangeValue(lexical_cast<string>((short)DamageGraphicPointer->DamagePercent));
		DamageGraphics_Unknown1->ChangeValue(lexical_cast<string>((short)DamageGraphicPointer->Unknown1));
		DamageGraphics_Unknown2->ChangeValue(lexical_cast<string>((short)DamageGraphicPointer->Unknown2));
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

void AGE_Frame::OnUnitDamageGraphicsAdd(wxCommandEvent &Event)
{
	auto Selections = Units_Units_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	genie::unit::DamageGraphic Temp;
	Temp.setGameVersion(GenieVersion);
	for(short loop = 0; loop < GenieFile->Civs.size(); loop++)
	{
		if(GenieFile->Civs[loop].UnitPointers[UnitIDs[0]] != 0)
		GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics.push_back(Temp);
	}
	Added = true;
	ListUnitDamageGraphics();
}

void AGE_Frame::OnUnitDamageGraphicsInsert(wxCommandEvent &Event)
{
	auto Selections = Units_DamageGraphics_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	genie::unit::DamageGraphic Temp;
	Temp.setGameVersion(GenieVersion);
	for(short loop = 0; loop < GenieFile->Civs.size(); loop++)
	{
		if(GenieFile->Civs[loop].UnitPointers[UnitIDs[0]] != 0)
		GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics.insert(GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics.begin() + DamageGraphicIDs[0], Temp);
	}
	ListUnitDamageGraphics();
}

void AGE_Frame::OnUnitDamageGraphicsDelete(wxCommandEvent &Event)
{
	auto Selections = Units_DamageGraphics_List->GetSelections(Items); // Gives the current list selection.
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	for(short civ = 0; civ < GenieFile->Civs.size(); civ++)
	{
		if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] != 0)
		for(auto loop = Selections; loop--> 0;)
		GenieFile->Civs[civ].Units[UnitIDs[0]].DamageGraphics.erase(GenieFile->Civs[civ].Units[UnitIDs[0]].DamageGraphics.begin() + DamageGraphicIDs[loop]);
	}
	ListUnitDamageGraphics();
}

void AGE_Frame::OnUnitDamageGraphicsCopy(wxCommandEvent &Event)
{
	auto Selections = Units_DamageGraphics_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Units_SpecialCopy_Civs->GetValue()) copies->Dat.AllCivs |= 0x10; else copies->Dat.AllCivs &= ~0x10;
	if(copies->Dat.AllCivs & 0x10)
	{
		short CivCount = GenieFile->Civs.size();
		copies->Dat.UnitDamageGraphicExists.resize(CivCount);
		copies->Dat.UnitDamageGraphics.resize(CivCount);
		for(short civ = 0, copy = 0; civ < GenieFile->Civs.size(); civ++)
		{
			if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] == 0)
			{
				// Graphic set info not usefull.
				copies->Dat.UnitDamageGraphicExists[civ] = 255;
				CivCount--;
			}
			else
			{
				// Save info of graphic set to intelligently fill possible gaps when pasting.
				copies->Dat.UnitDamageGraphicExists[civ] = 256 + GenieFile->Civs[civ].GraphicSet;
				// Only copy damage graphics from civs which have this unit enabled.
				CopyFromList(GenieFile->Civs[civ].Units[UnitIDs[0]].DamageGraphics, DamageGraphicIDs, copies->Dat.UnitDamageGraphics[copy]); copy++;
			}
		}
		copies->Dat.UnitDamageGraphics.resize(CivCount);
	}
	else
	{
		CopyFromList(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].DamageGraphics, DamageGraphicIDs, copies->Dat.UnitDamageGraphics[0]);
	}
}

void AGE_Frame::OnUnitDamageGraphicsPaste(wxCommandEvent &Event)
{
	auto Selections = Units_DamageGraphics_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	if(copies->Dat.AllCivs & 0x10)
	{
		for(short civ = 0, copy = 0; civ < GenieFile->Civs.size(); civ++)
		{
			if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] == 0)
			{
				// Consume copies.
				if(copies->Dat.UnitDamageGraphicExists[civ] > 255) copy++; continue;
			}
			// If the target unit exists then choose from following.
			if(copies->Dat.UnitDamageGraphicExists[civ] > 255 && copy < copies->Dat.UnitDamageGraphics.size())
			{
				PasteToList(GenieFile->Civs[civ].Units[UnitIDs[0]].DamageGraphics, DamageGraphicIDs[0], copies->Dat.UnitDamageGraphics[copy]); copy++;
			}
			else
			{
				PasteToList(GenieFile->Civs[civ].Units[UnitIDs[0]].DamageGraphics, DamageGraphicIDs[0], copies->Dat.UnitDamageGraphics[0]);
			}
		}
	}
	else
	{
		PasteToList(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].DamageGraphics, DamageGraphicIDs[0], copies->Dat.UnitDamageGraphics[0]);
	}
	ListUnitDamageGraphics();
}

void AGE_Frame::OnUnitDamageGraphicsPasteInsert(wxCommandEvent &Event)
{
	auto Selections = Units_DamageGraphics_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	genie::unit::DamageGraphic Temp;
	if(copies->Dat.AllCivs & 0x10)
	{
		for(short civ = 0, copy = 0; civ < GenieFile->Civs.size(); civ++)
		{
			if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] == 0)
			{
				// Consume copies.
				if(copies->Dat.UnitDamageGraphicExists[civ] > 255) copy++; continue;
			}
			// If the target unit exists then choose from following.
			if(copies->Dat.UnitDamageGraphicExists[civ] > 255 && copy < copies->Dat.UnitDamageGraphics.size())
			{
				PasteInsertToList(GenieFile->Civs[civ].Units[UnitIDs[0]].DamageGraphics, DamageGraphicIDs[0], copies->Dat.UnitDamageGraphics[copy]); copy++;
			}
			else
			{
				PasteInsertToList(GenieFile->Civs[civ].Units[UnitIDs[0]].DamageGraphics, DamageGraphicIDs[0], copies->Dat.UnitDamageGraphics[0]);
			}
		}
	}
	else
	{
		PasteInsertToList(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].DamageGraphics, DamageGraphicIDs[0], copies->Dat.UnitDamageGraphics[0]);
	}
	ListUnitDamageGraphics();
}

void AGE_Frame::OnUnitDamageGraphicsCopyToUnits(wxCommandEvent &Event)
{
	for(short civ = 0; civ < GenieFile->Civs.size(); civ++)
	for(short loop=1; loop < UnitIDs.size(); loop++)
	{
		GenieFile->Civs[civ].Units[UnitIDs[loop]].DamageGraphics = GenieFile->Civs[civ].Units[UnitIDs[0]].DamageGraphics;
	}
}

string AGE_Frame::GetUnitAttackName(short Index)
{
	return "Amount: "+lexical_cast<string>(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Projectile.Attacks[Index].Amount)
	+" - Class "+lexical_cast<string>(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Projectile.Attacks[Index].Class)+" ";
}

void AGE_Frame::OnUnitAttacksSearch(wxCommandEvent &Event)
{
	ListUnitAttacks();
}

void AGE_Frame::ListUnitAttacks()
{
	searchText = Units_Attacks_Search->GetValue().Lower();
	excludeText = Units_Attacks_Search_R->GetValue().Lower();

	auto Selections = Units_Attacks_List->GetSelections(Items);
	Units_Attacks_List->Clear();

	if(GenieFile->Civs[UnitCivID].UnitPointers[UnitIDs[0]] != 0
	&& GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type >= 60
	&& GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type <= 80)
	{
		Units_Attacks_Add->Enable(true);
		for(short loop = 0; loop < GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Projectile.Attacks.size(); loop++)
		{
			wxString Name = " "+lexical_cast<string>(loop)+" - "+GetUnitAttackName(loop);
			if(SearchMatches(Name.Lower()))
			{
				Units_Attacks_List->Append(Name, (void*)&GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Projectile.Attacks[loop]);
			}
		}
	}
	else
	{
		Units_Attacks_Add->Enable(false);
	}
	ListingFix(Selections, Units_Attacks_List);

	wxCommandEvent E;
	OnUnitAttacksSelect(E);
}

void AGE_Frame::OnUnitAttacksSelect(wxCommandEvent &Event)
{
	auto Selections = Units_Attacks_List->GetSelections(Items);
	if(Selections > 0)
	{
		AttackIDs.resize(Selections);
		int PointerCount = Selections * SelectedCivs.size();
		Attacks_Class->resize(PointerCount);
		Attacks_Amount->resize(PointerCount);

		bool showWarning = false;
		wxString warning = "Attack count of civs\n";
		genie::unit::AttackOrArmor * AttackPointer;
		for(auto sel = Selections; sel--> 0;)
		{
			AttackPointer = (genie::unit::AttackOrArmor*)Units_Attacks_List->GetClientData(Items.Item(sel));
			AttackIDs[sel] = (AttackPointer - (&GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Projectile.Attacks[0]));

			for(short vecCiv = SelectedCivs.size(); vecCiv--> 0;)
			{
				if(sel == 0 && GenieFile->Civs[SelectedCivs[vecCiv]].Units[UnitIDs[0]].Projectile.Attacks.size() != GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Projectile.Attacks.size())
				{
					warning.Append(lexical_cast<string>(SelectedCivs[vecCiv])+" ");
					showWarning = true;
				}
				AttackPointer = &GenieFile->Civs[SelectedCivs[vecCiv]].Units[UnitIDs[0]].Projectile.Attacks[AttackIDs[sel]];

				int location = sel + vecCiv * Selections;
				Attacks_Class->container[location] = &AttackPointer->Class;
				Attacks_Amount->container[location] = &AttackPointer->Amount;
			}
		}
		if(showWarning)
		{
			warning.Append("\ndiffers from civ "+lexical_cast<string>(UnitCivID));
			wxMessageBox(warning);
		}

		Attacks_Class->ChangeValue(lexical_cast<string>(AttackPointer->Class));
		Attacks_ComboBox_Class[0]->SetSelection(0);
		Attacks_ComboBox_Class[0]->SetSelection(AttackPointer->Class + 1);
		Attacks_Amount->ChangeValue(lexical_cast<string>(AttackPointer->Amount));
	}
	else
	{
		Attacks_Class->ChangeValue("0");
		Attacks_ComboBox_Class[0]->SetSelection(0);
		Attacks_Amount->ChangeValue("0");
	}
}

void AGE_Frame::OnUnitAttacksAdd(wxCommandEvent &Event)
{
	auto Selections = Units_Units_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	genie::unit::AttackOrArmor Temp;
	Temp.setGameVersion(GenieVersion);
	for(short loop = 0; loop < GenieFile->Civs.size(); loop++)
	{
		if(GenieFile->Civs[loop].UnitPointers[UnitIDs[0]] != 0)
		GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Attacks.push_back(Temp);
	}
	Added = true;
	ListUnitAttacks();
}

void AGE_Frame::OnUnitAttacksInsert(wxCommandEvent &Event)
{
	auto Selections = Units_Attacks_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	genie::unit::AttackOrArmor Temp;
	Temp.setGameVersion(GenieVersion);
	for(short loop = 0; loop < GenieFile->Civs.size(); loop++)
	{
		if(GenieFile->Civs[loop].UnitPointers[UnitIDs[0]] != 0)
		GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Attacks.insert(GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Attacks.begin() + AttackIDs[0], Temp);
	}
	ListUnitAttacks();
}

void AGE_Frame::OnUnitAttacksDelete(wxCommandEvent &Event)
{
	auto Selections = Units_Attacks_List->GetSelections(Items); // Gives the current list selection.
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	for(short civ = 0; civ < GenieFile->Civs.size(); civ++)
	{
		if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] != 0)
		for(auto loop = Selections; loop--> 0;)
		GenieFile->Civs[civ].Units[UnitIDs[0]].Projectile.Attacks.erase(GenieFile->Civs[civ].Units[UnitIDs[0]].Projectile.Attacks.begin() + AttackIDs[loop]);
	}
	ListUnitAttacks();
}

void AGE_Frame::OnUnitAttacksCopy(wxCommandEvent &Event)
{
	auto Selections = Units_Attacks_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Units_SpecialCopy_Civs->GetValue()) copies->Dat.AllCivs |= 0x20; else copies->Dat.AllCivs &= ~0x20;
	if(copies->Dat.AllCivs & 0x20)
	{
		short CivCount = GenieFile->Civs.size();
		copies->Dat.UnitAttackExists.resize(CivCount);
		copies->Dat.UnitAttacks.resize(CivCount);
		for(short civ = 0, copy = 0; civ < GenieFile->Civs.size(); civ++)
		{
			if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] == 0)
			{
				// Graphic set info not usefull.
				copies->Dat.UnitAttackExists[civ] = 255;
				CivCount--;
			}
			else
			{
				// Save info of graphic set to intelligently fill possible gaps when pasting.
				copies->Dat.UnitAttackExists[civ] = 256 + GenieFile->Civs[civ].GraphicSet;
				// Only copy attacks from civs which have this unit enabled.
				CopyFromList(GenieFile->Civs[civ].Units[UnitIDs[0]].Projectile.Attacks, AttackIDs, copies->Dat.UnitAttacks[copy]); copy++;
			}
		}
		copies->Dat.UnitAttacks.resize(CivCount);
	}
	else
	{
		CopyFromList(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Projectile.Attacks, AttackIDs, copies->Dat.UnitAttacks[0]);
	}
}

void AGE_Frame::OnUnitAttacksPaste(wxCommandEvent &Event)
{
	auto Selections = Units_Attacks_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	if(copies->Dat.AllCivs & 0x20)
	{
		for(short civ = 0, copy = 0; civ < GenieFile->Civs.size(); civ++)
		{
			if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] == 0)
			{
				// Consume copies.
				if(copies->Dat.UnitAttackExists[civ] > 255) copy++; continue;
			}
			// If the target unit exists then choose from following.
			if(copies->Dat.UnitAttackExists[civ] > 255 && copy < copies->Dat.UnitAttacks.size())
			{
				PasteToList(GenieFile->Civs[civ].Units[UnitIDs[0]].Projectile.Attacks, AttackIDs[0], copies->Dat.UnitAttacks[copy]); copy++;
			}
			else
			{
				PasteToList(GenieFile->Civs[civ].Units[UnitIDs[0]].Projectile.Attacks, AttackIDs[0], copies->Dat.UnitAttacks[0]);
			}
		}
	}
	else
	{
		PasteToList(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Projectile.Attacks, AttackIDs[0], copies->Dat.UnitAttacks[0]);
	}
	ListUnitAttacks();
}

void AGE_Frame::OnUnitAttacksPasteInsert(wxCommandEvent &Event)
{
	auto Selections = Units_Attacks_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	if(copies->Dat.AllCivs & 0x20)
	{
		for(short civ = 0, copy = 0; civ < GenieFile->Civs.size(); civ++)
		{
			if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] == 0)
			{
				// Consume copies.
				if(copies->Dat.UnitAttackExists[civ] > 255) copy++; continue;
			}
			// If the target unit exists then choose from following.
			if(copies->Dat.UnitAttackExists[civ] > 255 && copy < copies->Dat.UnitAttacks.size())
			{
				PasteInsertToList(GenieFile->Civs[civ].Units[UnitIDs[0]].Projectile.Attacks, AttackIDs[0], copies->Dat.UnitAttacks[copy]); copy++;
			}
			else
			{
				PasteInsertToList(GenieFile->Civs[civ].Units[UnitIDs[0]].Projectile.Attacks, AttackIDs[0], copies->Dat.UnitAttacks[0]);
			}
		}
	}
	else
	{
		PasteInsertToList(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Projectile.Attacks, AttackIDs[0], copies->Dat.UnitAttacks[0]);
	}
	ListUnitAttacks();
}

void AGE_Frame::OnUnitAttacksCopyToUnits(wxCommandEvent &Event)
{
	for(short civ = 0; civ < GenieFile->Civs.size(); civ++)
	for(short loop=1; loop < UnitIDs.size(); loop++)
	{
		GenieFile->Civs[civ].Units[UnitIDs[loop]].Projectile.Attacks = GenieFile->Civs[civ].Units[UnitIDs[0]].Projectile.Attacks;
	}
}

string AGE_Frame::GetUnitArmorName(short Index)
{
	return "Amount: "+lexical_cast<string>(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Projectile.Armours[Index].Amount)
	+" - Class "+lexical_cast<string>(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Projectile.Armours[Index].Class)+" ";
}

void AGE_Frame::OnUnitArmorsSearch(wxCommandEvent &Event)
{
	ListUnitArmors();
}

void AGE_Frame::ListUnitArmors()
{
	searchText = Units_Armors_Search->GetValue().Lower();
	excludeText = Units_Armors_Search_R->GetValue().Lower();

	auto Selections = Units_Armors_List->GetSelections(Items);
	Units_Armors_List->Clear();

	if(GenieFile->Civs[UnitCivID].UnitPointers[UnitIDs[0]] != 0
	&& GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type >= 60
	&& GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type <= 80)
	{
		Units_Armors_Add->Enable(true);
		for(short loop = 0; loop < GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Projectile.Armours.size(); loop++)
		{
			wxString Name = " "+lexical_cast<string>(loop)+" - "+GetUnitArmorName(loop);
			if(SearchMatches(Name.Lower()))
			{
				Units_Armors_List->Append(Name, (void*)&GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Projectile.Armours[loop]);
			}
		}
	}
	else
	{
		Units_Armors_Add->Enable(false);
	}
	ListingFix(Selections, Units_Armors_List);

	wxCommandEvent E;
	OnUnitArmorsSelect(E);
}

void AGE_Frame::OnUnitArmorsSelect(wxCommandEvent &Event)
{
	auto Selections = Units_Armors_List->GetSelections(Items);
	if(Selections > 0)
	{
		ArmorIDs.resize(Selections);
		int PointerCount = Selections * SelectedCivs.size();
		Armors_Class->resize(PointerCount);
		Armors_Amount->resize(PointerCount);

		bool showWarning = false;
		wxString warning = "Armor count of civs\n";
		genie::unit::AttackOrArmor * ArmorPointer;
		for(auto sel = Selections; sel--> 0;)
		{
			ArmorPointer = (genie::unit::AttackOrArmor*)Units_Armors_List->GetClientData(Items.Item(sel));
			ArmorIDs[sel] = (ArmorPointer - (&GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Projectile.Armours[0]));

			for(short vecCiv = SelectedCivs.size(); vecCiv--> 0;)
			{
				if(sel == 0 && GenieFile->Civs[SelectedCivs[vecCiv]].Units[UnitIDs[0]].Projectile.Armours.size() != GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Projectile.Armours.size())
				{
					warning.Append(lexical_cast<string>(SelectedCivs[vecCiv])+" ");
					showWarning = true;
				}
				ArmorPointer = &GenieFile->Civs[SelectedCivs[vecCiv]].Units[UnitIDs[0]].Projectile.Armours[ArmorIDs[sel]];

				int location = sel + vecCiv * Selections;
				Armors_Class->container[location] = &ArmorPointer->Class;
				Armors_Amount->container[location] = &ArmorPointer->Amount;
			}
		}
		if(showWarning)
		{
			warning.Append("\ndiffers from civ "+lexical_cast<string>(UnitCivID));
			wxMessageBox(warning);
		}

		Armors_Class->ChangeValue(lexical_cast<string>(ArmorPointer->Class));
		Attacks_ComboBox_Class[1]->SetSelection(0);
		Attacks_ComboBox_Class[1]->SetSelection(ArmorPointer->Class + 1);
		Armors_Amount->ChangeValue(lexical_cast<string>(ArmorPointer->Amount));
	}
	else
	{
		Armors_Class->ChangeValue("0");
		Attacks_ComboBox_Class[1]->SetSelection(0);
		Armors_Amount->ChangeValue("0");
	}
}

void AGE_Frame::OnUnitArmorsAdd(wxCommandEvent &Event)
{
	auto Selections = Units_Units_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	genie::unit::AttackOrArmor Temp;
	Temp.setGameVersion(GenieVersion);
	for(short loop = 0; loop < GenieFile->Civs.size(); loop++)
	{
		if(GenieFile->Civs[loop].UnitPointers[UnitIDs[0]] != 0)
		GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Armours.push_back(Temp);
	}
	Added = true;
	ListUnitArmors();
}

void AGE_Frame::OnUnitArmorsInsert(wxCommandEvent &Event)
{
	auto Selections = Units_Armors_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	genie::unit::AttackOrArmor Temp;
	Temp.setGameVersion(GenieVersion);
	for(short loop = 0; loop < GenieFile->Civs.size(); loop++)
	{
		if(GenieFile->Civs[loop].UnitPointers[UnitIDs[0]] != 0)
		GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Armours.insert(GenieFile->Civs[loop].Units[UnitIDs[0]].Projectile.Armours.begin() + ArmorIDs[0], Temp);
	}
	ListUnitArmors();
}

void AGE_Frame::OnUnitArmorsDelete(wxCommandEvent &Event)
{
	auto Selections = Units_Armors_List->GetSelections(Items); // Gives the current list selection.
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	for(short civ = 0; civ < GenieFile->Civs.size(); civ++)
	{
		if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] != 0)
		for(auto loop = Selections; loop--> 0;)
		GenieFile->Civs[civ].Units[UnitIDs[0]].Projectile.Armours.erase(GenieFile->Civs[civ].Units[UnitIDs[0]].Projectile.Armours.begin() + ArmorIDs[loop]);
	}
	ListUnitArmors();
}

void AGE_Frame::OnUnitArmorsCopy(wxCommandEvent &Event)
{
	auto Selections = Units_Armors_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Units_SpecialCopy_Civs->GetValue()) copies->Dat.AllCivs |= 0x40; else copies->Dat.AllCivs &= ~0x40;
	if(copies->Dat.AllCivs & 0x40)
	{
		short CivCount = GenieFile->Civs.size();
		copies->Dat.UnitArmorExists.resize(CivCount);
		copies->Dat.UnitArmors.resize(CivCount);
		for(short civ = 0, copy = 0; civ < GenieFile->Civs.size(); civ++)
		{
			if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] == 0)
			{
				// Graphic set info not usefull.
				copies->Dat.UnitArmorExists[civ] = 255;
				CivCount--;
			}
			else
			{
				// Save info of graphic set to intelligently fill possible gaps when pasting.
				copies->Dat.UnitArmorExists[civ] = 256 + GenieFile->Civs[civ].GraphicSet;
				// Only copy armors from civs which have this unit enabled.
				CopyFromList(GenieFile->Civs[civ].Units[UnitIDs[0]].Projectile.Armours, ArmorIDs, copies->Dat.UnitArmors[copy]); copy++;
			}
		}
		copies->Dat.UnitArmors.resize(CivCount);
	}
	else
	{
		CopyFromList(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Projectile.Armours, ArmorIDs, copies->Dat.UnitArmors[0]);
	}
}

void AGE_Frame::OnUnitArmorsPaste(wxCommandEvent &Event)
{
	auto Selections = Units_Armors_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	if(copies->Dat.AllCivs & 0x40)
	{
		for(short civ = 0, copy = 0; civ < GenieFile->Civs.size(); civ++)
		{
			if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] == 0)
			{
				// Consume copies.
				if(copies->Dat.UnitArmorExists[civ] > 255) copy++; continue;
			}
			// If the target unit exists then choose from following.
			if(copies->Dat.UnitArmorExists[civ] > 255 && copy < copies->Dat.UnitArmors.size())
			{
				PasteToList(GenieFile->Civs[civ].Units[UnitIDs[0]].Projectile.Armours, ArmorIDs[0], copies->Dat.UnitArmors[copy]); copy++;
			}
			else
			{
				PasteToList(GenieFile->Civs[civ].Units[UnitIDs[0]].Projectile.Armours, ArmorIDs[0], copies->Dat.UnitArmors[0]);
			}
		}
	}
	else
	{
		PasteToList(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Projectile.Armours, ArmorIDs[0], copies->Dat.UnitArmors[0]);
	}
	ListUnitArmors();
}

void AGE_Frame::OnUnitArmorsPasteInsert(wxCommandEvent &Event)
{
	auto Selections = Units_Armors_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	if(copies->Dat.AllCivs & 0x40)
	{
		for(short civ = 0, copy = 0; civ < GenieFile->Civs.size(); civ++)
		{
			if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] == 0)
			{
				// Consume copies.
				if(copies->Dat.UnitArmorExists[civ] > 255) copy++; continue;
			}
			// If the target unit exists then choose from following.
			if(copies->Dat.UnitArmorExists[civ] > 255 && copy < copies->Dat.UnitArmors.size())
			{
				PasteInsertToList(GenieFile->Civs[civ].Units[UnitIDs[0]].Projectile.Armours, ArmorIDs[0], copies->Dat.UnitArmors[copy]); copy++;
			}
			else
			{
				PasteInsertToList(GenieFile->Civs[civ].Units[UnitIDs[0]].Projectile.Armours, ArmorIDs[0], copies->Dat.UnitArmors[0]);
			}
		}
	}
	else
	{
		PasteInsertToList(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Projectile.Armours, ArmorIDs[0], copies->Dat.UnitArmors[0]);
	}
	ListUnitArmors();
}

void AGE_Frame::OnUnitArmorsCopyToUnits(wxCommandEvent &Event)
{
	for(short civ = 0; civ < GenieFile->Civs.size(); civ++)
	for(short loop=1; loop < UnitIDs.size(); loop++)
	{
		GenieFile->Civs[civ].Units[UnitIDs[loop]].Projectile.Armours = GenieFile->Civs[civ].Units[UnitIDs[0]].Projectile.Armours;
	}
}

//	AoE/TC/SWGB/CC Unit Commands

wxString AGE_Frame::GetUnitCommandName(short Index)
{
	short CommandType = -1;
	short CommandSubType = -1;
	if(GenieVersion >= genie::GV_AoK) // AoK, TC, SWGB, CC
	{
		CommandType = GenieFile->UnitHeaders[UnitIDs[0]].Commands[Index].Type;
		CommandSubType = GenieFile->UnitHeaders[UnitIDs[0]].Commands[Index].SubType;
	}
	else // AoE, RoR
	{
		CommandType = GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Bird.Commands[Index].Type;
		CommandSubType = GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Bird.Commands[Index].SubType;
	}
	switch(CommandType)
	{
		case 3: return UnitCommands_ComboBox_Type->GetString(1);
		case 5: return UnitCommands_ComboBox_Type->GetString(2);
		case 6: return UnitCommands_ComboBox_Type->GetString(3);
		case 7: return UnitCommands_ComboBox_Type->GetString(4);
		case 10: return UnitCommands_ComboBox_Type->GetString(5);
		case 11: return UnitCommands_ComboBox_Type->GetString(6);
		case 12: return UnitCommands_ComboBox_Type->GetString(7);
		case 13: return UnitCommands_ComboBox_Type->GetString(8);
		case 21: return UnitCommands_ComboBox_Type->GetString(9);
		case 101: return UnitCommands_ComboBox_Type->GetString(10);
		case 104: return UnitCommands_ComboBox_Type->GetString(11);
		case 105: return UnitCommands_ComboBox_Type->GetString(12);
		case 106: return UnitCommands_ComboBox_Type->GetString(13);
		case 107: return UnitCommands_ComboBox_Type->GetString(14);
		case 109: return UnitCommands_ComboBox_Type->GetString(15);
		case 110: return UnitCommands_ComboBox_Type->GetString(16);
		case 111: return UnitCommands_ComboBox_Type->GetString(17);
		case 120: return UnitCommands_ComboBox_Type->GetString(18);
		case 121: return UnitCommands_ComboBox_Type->GetString(19);
		case 122: return UnitCommands_ComboBox_Type->GetString(20);
		case 125: return UnitCommands_ComboBox_Type->GetString(21);
		case 131: return UnitCommands_ComboBox_Type->GetString(22);
		case 132: return UnitCommands_ComboBox_Type->GetString(23);
		case 135: return UnitCommands_ComboBox_Type->GetString(24);
		case 136: return UnitCommands_ComboBox_Type->GetString(25);
		default: return "Unk. Type "+lexical_cast<string>(CommandType)+", Sub "+lexical_cast<string>(CommandSubType);
	}
}

void AGE_Frame::OnUnitCommandsSearch(wxCommandEvent &Event)
{
	ListUnitCommands();
}

void AGE_Frame::ListUnitCommands()
{
	searchText = Units_UnitCommands_Search->GetValue().Lower();
	excludeText = Units_UnitCommands_Search_R->GetValue().Lower();

	auto Selections = Units_UnitCommands_List->GetSelections(Items);
	Units_UnitCommands_List->Clear();

	if(GenieVersion >= genie::GV_AoK)	// AoK, TC, SWGB or CC
	{
		for(short loop = 0; loop < GenieFile->UnitHeaders[UnitIDs[0]].Commands.size(); loop++)
		{
			wxString Name = " "+lexical_cast<string>(loop)+" - "+GetUnitCommandName(loop);
			if(SearchMatches(Name.Lower()))
			{
				Units_UnitCommands_List->Append(Name, (void*)&GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop]);
			}
		}
	}
	else	// AoE or RoR
	{
		if(GenieFile->Civs[UnitCivID].UnitPointers[UnitIDs[0]] != 0
		&& GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type >= 40
		&& GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type <= 80)
		{
			Units_UnitCommands_Add->Enable(true);
			for(short loop = 0; loop < GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Bird.Commands.size(); loop++)
			{
				wxString Name = " "+lexical_cast<string>(loop)+" - "+GetUnitCommandName(loop);
				if(SearchMatches(Name.Lower()))
				{
					Units_UnitCommands_List->Append(Name, (void*)&GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Bird.Commands[loop]);
				}
			}
		}
		else
		{
			Units_UnitCommands_Add->Enable(false);
		}
	}
	ListingFix(Selections, Units_UnitCommands_List);

	wxCommandEvent E;
	OnUnitCommandsSelect(E);
}

void AGE_Frame::OnUnitCommandsSelect(wxCommandEvent &Event)
{
	auto Selections = Units_UnitCommands_List->GetSelections(Items);
	if(Selections > 0)
	{
		CommandIDs.resize(Selections);
		int PointerCount = (GenieVersion <= genie::GV_AoKA) ? Selections * SelectedCivs.size() : Selections;
		UnitCommands_One->resize(PointerCount);
		UnitCommands_ID->resize(PointerCount);
		UnitCommands_Unknown1->resize(PointerCount);
		UnitCommands_Type->resize(PointerCount);
		UnitCommands_SubType->resize(PointerCount);
		UnitCommands_ClassID->resize(PointerCount);
		UnitCommands_UnitID->resize(PointerCount);
		UnitCommands_Unknown2->resize(PointerCount);
		UnitCommands_ResourceIn->resize(PointerCount);
		UnitCommands_ResourceOut->resize(PointerCount);
		UnitCommands_Unknown3->resize(PointerCount);
		UnitCommands_WorkRateMultiplier->resize(PointerCount);
		UnitCommands_ExecutionRadius->resize(PointerCount);
		UnitCommands_ExtraRange->resize(PointerCount);
		UnitCommands_Unknown4->resize(PointerCount);
		UnitCommands_Unknown5->resize(PointerCount);
		UnitCommands_Unknown6->resize(PointerCount);
		UnitCommands_Unknown7->resize(PointerCount);
		UnitCommands_Unknown8->resize(PointerCount);
		UnitCommands_Unknown9->resize(PointerCount);
		UnitCommands_Unknown10->resize(PointerCount);
		UnitCommands_Unknown11->resize(PointerCount);
		for(short loop = 0; loop < UnitCommands_Graphics.size(); loop++)
		UnitCommands_Graphics[loop]->resize(PointerCount);

		bool showWarning = false;
		wxString warning = "Command count of civs\n";
		genie::UnitCommand * CommandPointer;
		for(auto sel = Selections; sel--> 0;)
		{
			CommandPointer = (genie::UnitCommand*)Units_UnitCommands_List->GetClientData(Items.Item(sel));
			if(GenieVersion <= genie::GV_AoKA)
			CommandIDs[sel] = (CommandPointer - (&GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Bird.Commands[0]));
			else
			CommandIDs[sel] = (CommandPointer - (&GenieFile->UnitHeaders[UnitIDs[0]].Commands[0]));

			for(short vecCiv = (GenieVersion <= genie::GV_AoKA) ? SelectedCivs.size() : 1; vecCiv--> 0;)
			{
				if(GenieVersion <= genie::GV_AoKA)
				{
					if(sel == 0 && GenieFile->Civs[SelectedCivs[vecCiv]].Units[UnitIDs[0]].Bird.Commands.size() != GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Bird.Commands.size())
					{
						warning.Append(lexical_cast<string>(SelectedCivs[vecCiv])+" ");
						showWarning = true;
					}
					CommandPointer = &GenieFile->Civs[SelectedCivs[vecCiv]].Units[UnitIDs[0]].Bird.Commands[CommandIDs[sel]];
				}
				else
				{
					CommandPointer = &GenieFile->UnitHeaders[UnitIDs[0]].Commands[CommandIDs[sel]];
				}

				int location = sel + vecCiv * Selections;
				UnitCommands_One->container[location] = &CommandPointer->One;
				UnitCommands_ID->container[location] = &CommandPointer->ID;
				UnitCommands_Unknown1->container[location] = &CommandPointer->Unknown1;
				UnitCommands_Type->container[location] = &CommandPointer->Type;
				UnitCommands_SubType->container[location] = &CommandPointer->SubType;
				UnitCommands_ClassID->container[location] = &CommandPointer->ClassID;
				UnitCommands_UnitID->container[location] = &CommandPointer->UnitID;
				UnitCommands_Unknown2->container[location] = &CommandPointer->Unknown2;
				UnitCommands_ResourceIn->container[location] = &CommandPointer->ResourceIn;
				UnitCommands_ResourceOut->container[location] = &CommandPointer->ResourceOut;
				UnitCommands_Unknown3->container[location] = &CommandPointer->Unknown3;
				UnitCommands_WorkRateMultiplier->container[location] = &CommandPointer->WorkRateMultiplier;
				UnitCommands_ExecutionRadius->container[location] = &CommandPointer->ExecutionRadius;
				UnitCommands_ExtraRange->container[location] = &CommandPointer->ExtraRange;
				UnitCommands_Unknown4->container[location] = &CommandPointer->Unknown4;
				UnitCommands_Unknown5->container[location] = &CommandPointer->Unknown5;
				UnitCommands_Unknown6->container[location] = &CommandPointer->Unknown6;
				UnitCommands_Unknown7->container[location] = &CommandPointer->Unknown7;
				UnitCommands_Unknown8->container[location] = &CommandPointer->Unknown8;
				UnitCommands_Unknown9->container[location] = &CommandPointer->Unknown9;
				UnitCommands_Unknown10->container[location] = &CommandPointer->Unknown10;
				UnitCommands_Unknown11->container[location] = &CommandPointer->Unknown11;
				for(short loop = 0; loop < UnitCommands_Graphics.size(); loop++)
				UnitCommands_Graphics[loop]->container[location] = &CommandPointer->Graphics[loop];
			}
			if(showWarning)
			{
				warning.Append("\ndiffers from civ "+lexical_cast<string>(UnitCivID));
				wxMessageBox(warning);
			}
		}

		UnitCommands_One->ChangeValue(lexical_cast<string>(CommandPointer->One));
		UnitCommands_ID->ChangeValue(lexical_cast<string>(CommandPointer->ID));
		UnitCommands_Unknown1->ChangeValue(lexical_cast<string>((short)CommandPointer->Unknown1));
		UnitCommands_Type->ChangeValue(lexical_cast<string>(CommandPointer->Type));
		switch(CommandPointer->Type)
		{
			case 3: UnitCommands_ComboBox_Type->SetSelection(1); break;
			case 5: UnitCommands_ComboBox_Type->SetSelection(2); break;
			case 6: UnitCommands_ComboBox_Type->SetSelection(3); break;
			case 7: UnitCommands_ComboBox_Type->SetSelection(4); break;
			case 10: UnitCommands_ComboBox_Type->SetSelection(5); break;
			case 11: UnitCommands_ComboBox_Type->SetSelection(6); break;
			case 12: UnitCommands_ComboBox_Type->SetSelection(7); break;
			case 13: UnitCommands_ComboBox_Type->SetSelection(8); break;
			case 21: UnitCommands_ComboBox_Type->SetSelection(9); break;
			case 101: UnitCommands_ComboBox_Type->SetSelection(10); break;
			case 104: UnitCommands_ComboBox_Type->SetSelection(11); break;
			case 105: UnitCommands_ComboBox_Type->SetSelection(12); break;
			case 106: UnitCommands_ComboBox_Type->SetSelection(13); break;
			case 107: UnitCommands_ComboBox_Type->SetSelection(14); break;
			case 109: UnitCommands_ComboBox_Type->SetSelection(15); break;
			case 110: UnitCommands_ComboBox_Type->SetSelection(16); break;
			case 111: UnitCommands_ComboBox_Type->SetSelection(17); break;
			case 120: UnitCommands_ComboBox_Type->SetSelection(18); break;
			case 121: UnitCommands_ComboBox_Type->SetSelection(19); break;
			case 122: UnitCommands_ComboBox_Type->SetSelection(20); break;
			case 125: UnitCommands_ComboBox_Type->SetSelection(21); break;
			case 131: UnitCommands_ComboBox_Type->SetSelection(22); break;
			case 132: UnitCommands_ComboBox_Type->SetSelection(23); break;
			case 135: UnitCommands_ComboBox_Type->SetSelection(24); break;
			case 136: UnitCommands_ComboBox_Type->SetSelection(25); break;
			default: UnitCommands_ComboBox_Type->SetSelection(0);
		}
		UnitCommands_ClassID->ChangeValue(lexical_cast<string>(CommandPointer->ClassID));
		Units_ComboBox_Class[1]->SetSelection(CommandPointer->ClassID + 1);
		UnitCommands_UnitID->ChangeValue(lexical_cast<string>(CommandPointer->UnitID));
		UnitCommands_ComboBox_UnitID->SetSelection(CommandPointer->UnitID + 1);
		UnitCommands_Unknown2->ChangeValue(lexical_cast<string>(CommandPointer->Unknown2));
		UnitCommands_ResourceIn->ChangeValue(lexical_cast<string>(CommandPointer->ResourceIn));
		UnitCommands_ComboBox_ResourceIn->SetSelection(CommandPointer->ResourceIn + 1);
		UnitCommands_SubType->ChangeValue(lexical_cast<string>(CommandPointer->SubType));
		UnitCommands_ComboBox_SubType->SetSelection(CommandPointer->SubType + 1);
		UnitCommands_ResourceOut->ChangeValue(lexical_cast<string>(CommandPointer->ResourceOut));
		UnitCommands_ComboBox_ResourceOut->SetSelection(CommandPointer->ResourceOut + 1);
		UnitCommands_Unknown3->ChangeValue(lexical_cast<string>(CommandPointer->Unknown3));
		UnitCommands_ComboBox_Unknown3->SetSelection(CommandPointer->Unknown3 + 1);
		UnitCommands_WorkRateMultiplier->ChangeValue(lexical_cast<string>(CommandPointer->WorkRateMultiplier));
		UnitCommands_ExecutionRadius->ChangeValue(lexical_cast<string>(CommandPointer->ExecutionRadius));
		UnitCommands_ExtraRange->ChangeValue(lexical_cast<string>(CommandPointer->ExtraRange));
		UnitCommands_Unknown4->ChangeValue(lexical_cast<string>((short)CommandPointer->Unknown4));
		UnitCommands_Unknown5->ChangeValue(lexical_cast<string>(CommandPointer->Unknown5));
		UnitCommands_Unknown6->ChangeValue(lexical_cast<string>((short)CommandPointer->Unknown6));
		UnitCommands_Unknown7->ChangeValue(lexical_cast<string>((short)CommandPointer->Unknown7));
		UnitCommands_Unknown8->ChangeValue(lexical_cast<string>(CommandPointer->Unknown8));
		UnitCommands_Unknown9->ChangeValue(lexical_cast<string>((short)CommandPointer->Unknown9));
		UnitCommands_Unknown10->ChangeValue(lexical_cast<string>((short)CommandPointer->Unknown10));
		UnitCommands_Unknown11->ChangeValue(lexical_cast<string>((short)CommandPointer->Unknown11));
		for(short loop = 0; loop < UnitCommands_Graphics.size(); loop++)
		{
			UnitCommands_Graphics[loop]->ChangeValue(lexical_cast<string>(CommandPointer->Graphics[loop]));
			UnitCommands_ComboBox_Graphics[loop]->SetSelection(CommandPointer->Graphics[loop] + 1);
		}
	}
	else
	{
		UnitCommands_One->ChangeValue("0");
		UnitCommands_ID->ChangeValue("0");
		UnitCommands_Unknown1->ChangeValue("0");
		UnitCommands_Type->ChangeValue("0");
		UnitCommands_ComboBox_Type->SetSelection(0);
		UnitCommands_ClassID->ChangeValue("0");
		Units_ComboBox_Class[1]->SetSelection(0);
		UnitCommands_UnitID->ChangeValue("0");
		UnitCommands_ComboBox_UnitID->SetSelection(0);
		UnitCommands_Unknown2->ChangeValue("0");
		UnitCommands_ResourceIn->ChangeValue("0");
		UnitCommands_ComboBox_ResourceIn->SetSelection(0);
		UnitCommands_SubType->ChangeValue("0");
		UnitCommands_ComboBox_SubType->SetSelection(0);
		UnitCommands_ResourceOut->ChangeValue("0");
		UnitCommands_ComboBox_ResourceOut->SetSelection(0);
		UnitCommands_Unknown3->ChangeValue("0");
		UnitCommands_ComboBox_Unknown3->SetSelection(0);
		UnitCommands_WorkRateMultiplier->ChangeValue("0");
		UnitCommands_ExecutionRadius->ChangeValue("0");
		UnitCommands_ExtraRange->ChangeValue("0");
		UnitCommands_Unknown4->ChangeValue("0");
		UnitCommands_Unknown5->ChangeValue("0");
		UnitCommands_Unknown6->ChangeValue("0");
		UnitCommands_Unknown7->ChangeValue("0");
		UnitCommands_Unknown8->ChangeValue("0");
		UnitCommands_Unknown9->ChangeValue("0");
		UnitCommands_Unknown10->ChangeValue("0");
		UnitCommands_Unknown11->ChangeValue("0");
		for(short loop = 0; loop < UnitCommands_Graphics.size(); loop++)
		{
			UnitCommands_Graphics[loop]->ChangeValue("0");
			UnitCommands_ComboBox_Graphics[loop]->SetSelection(0);
		}
	}
}

void AGE_Frame::OnUnitCommandsAdd(wxCommandEvent &Event)
{
	auto Selections = Units_Units_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	genie::UnitCommand Temp;
	Temp.setGameVersion(GenieVersion);
	if(GenieVersion >= genie::GV_AoK)
	{
		GenieFile->UnitHeaders[UnitIDs[0]].Commands.push_back(Temp);
		if(EnableIDFix)
		GenieFile->UnitHeaders[UnitIDs[0]].Commands[GenieFile->UnitHeaders[UnitIDs[0]].Commands.size()-1].ID = (int16_t)(GenieFile->UnitHeaders[UnitIDs[0]].Commands.size()-1); // ID Fix
	}
	else
	{
		for(short loop = 0; loop < GenieFile->Civs.size(); loop++)
		{
			if(GenieFile->Civs[loop].UnitPointers[UnitIDs[0]] != 0)
			{
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands.push_back(Temp);
				if(EnableIDFix)
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands.size()-1].ID = (int16_t)(GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands.size()-1); // ID Fix
			}
		}
	}
	Added = true;
	ListUnitCommands();
}

void AGE_Frame::OnUnitCommandsInsert(wxCommandEvent &Event)
{
	auto Selections = Units_UnitCommands_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	genie::UnitCommand Temp;
	Temp.setGameVersion(GenieVersion);
	if(GenieVersion >= genie::GV_AoK)
	{
		GenieFile->UnitHeaders[UnitIDs[0]].Commands.insert(GenieFile->UnitHeaders[UnitIDs[0]].Commands.begin() + CommandIDs[0], Temp);
		if(EnableIDFix)
		for(short loop2 = CommandIDs[0];loop2 < GenieFile->UnitHeaders[UnitIDs[0]].Commands.size(); loop2++) // ID Fix
		GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].ID = loop2;
	}
	else
	{
		for(short loop = 0; loop < GenieFile->Civs.size(); loop++)
		{
			if(GenieFile->Civs[loop].UnitPointers[UnitIDs[0]] != 0)
			{
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands.insert(GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands.begin() + CommandIDs[0], Temp);
				if(EnableIDFix)
				for(short loop2 = CommandIDs[0];loop2 < GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands.size(); loop2++) // ID Fix
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].ID = loop2;
			}
		}
	}
	ListUnitCommands();
}

void AGE_Frame::OnUnitCommandsDelete(wxCommandEvent &Event)
{
	auto Selections = Units_UnitCommands_List->GetSelections(Items); // Gives the current list selection.
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion >= genie::GV_AoK)
	{
		for(auto loop = Selections; loop--> 0;)
		GenieFile->UnitHeaders[UnitIDs[0]].Commands.erase(GenieFile->UnitHeaders[UnitIDs[0]].Commands.begin() + CommandIDs[loop]);
		if(EnableIDFix)
		for(short loop2 = CommandIDs[0];loop2 < GenieFile->UnitHeaders[UnitIDs[0]].Commands.size(); loop2++) // ID Fix
		GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].ID = loop2;
	}
	else
	{
		for(short civ = 0; civ < GenieFile->Civs.size(); civ++)
		{
			if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] != 0)
			{
				for(auto loop = Selections; loop--> 0;)
				GenieFile->Civs[civ].Units[UnitIDs[0]].Bird.Commands.erase(GenieFile->Civs[civ].Units[UnitIDs[0]].Bird.Commands.begin() + CommandIDs[loop]);
				if(EnableIDFix)
				for(short loop2 = CommandIDs[0];loop2 < GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands.size(); loop2++) // ID Fix
				GenieFile->Civs[civ].Units[UnitIDs[0]].Bird.Commands[loop2].ID = loop2;
			}
		}
	}
	ListUnitCommands();
}

void AGE_Frame::OnUnitCommandsCopy(wxCommandEvent &Event)
{
	auto Selections = Units_UnitCommands_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion >= genie::GV_AoK)
	{
		copies->Dat.AllCivs |= 0x80;
		copies->Dat.UnitCommands.resize(1);
		CopyFromList(GenieFile->UnitHeaders[UnitIDs[0]].Commands, CommandIDs, copies->Dat.UnitCommands[0]);
		return;
	}
	if(Units_SpecialCopy_Civs->GetValue()) copies->Dat.AllCivs |= 0x80; else copies->Dat.AllCivs &= ~0x80;
	if(copies->Dat.AllCivs & 0x80)
	{
		short CivCount = GenieFile->Civs.size();
		copies->Dat.UnitCommandExists.resize(CivCount);
		copies->Dat.UnitCommands.resize(CivCount);
		for(short civ = 0, copy = 0; civ < GenieFile->Civs.size(); civ++)
		{
			if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] == 0)
			{
				// Graphic set info not usefull.
				copies->Dat.UnitCommandExists[civ] = 255;
				CivCount--;
			}
			else
			{
				// Save info of graphic set to intelligently fill possible gaps when pasting.
				copies->Dat.UnitCommandExists[civ] = 256 + GenieFile->Civs[civ].GraphicSet;
				// Only copy commands from civs which have this unit enabled.
				CopyFromList(GenieFile->Civs[civ].Units[UnitIDs[0]].Bird.Commands, CommandIDs, copies->Dat.UnitCommands[copy]); copy++;
			}
		}
		copies->Dat.UnitCommands.resize(CivCount);
	}
	else
	{
		CopyFromList(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Bird.Commands, CommandIDs, copies->Dat.UnitCommands[0]);
	}
}

void AGE_Frame::OnUnitCommandsPaste(wxCommandEvent &Event)
{
	auto Selections = Units_UnitCommands_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion >= genie::GV_AoK)
	{
		PasteToListIDFix(GenieFile->UnitHeaders[UnitIDs[0]].Commands, CommandIDs[0], copies->Dat.UnitCommands[0]);
	}
	else if(copies->Dat.AllCivs & 0x80)
	{
		for(short civ = 0, copy = 0; civ < GenieFile->Civs.size(); civ++)
		{
			if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] == 0)
			{
				// Consume copies.
				if(copies->Dat.UnitCommandExists[civ] > 255) copy++; continue;
			}
			// If the target unit exists then choose from following.
			if(copies->Dat.UnitCommandExists[civ] > 255 && copy < copies->Dat.UnitCommands.size())
			{
				PasteToListIDFix(GenieFile->Civs[civ].Units[UnitIDs[0]].Bird.Commands, CommandIDs[0], copies->Dat.UnitCommands[copy]); copy++;
			}
			else
			{
				PasteToListIDFix(GenieFile->Civs[civ].Units[UnitIDs[0]].Bird.Commands, CommandIDs[0], copies->Dat.UnitCommands[0]);
			}
		}
	}
	else
	{
		PasteToListIDFix(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Bird.Commands, CommandIDs[0], copies->Dat.UnitCommands[0]);
	}
	ListUnitCommands();
}

void AGE_Frame::OnUnitCommandsPasteInsert(wxCommandEvent &Event)
{
	auto Selections = Units_UnitCommands_List->GetSelections(Items);
	if(Selections < 1) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion >= genie::GV_AoK)
	{
		PasteInsertToListIDFix(GenieFile->UnitHeaders[UnitIDs[0]].Commands, CommandIDs[0], copies->Dat.UnitCommands[0]);
	}
	else if(copies->Dat.AllCivs & 0x80)
	{
		for(short civ = 0, copy = 0; civ < GenieFile->Civs.size(); civ++)
		{
			if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] == 0)
			{
				// Consume copies.
				if(copies->Dat.UnitCommandExists[civ] > 255) copy++; continue;
			}
			// If the target unit exists then choose from following.
			if(copies->Dat.UnitCommandExists[civ] > 255 && copy < copies->Dat.UnitCommands.size())
			{
				PasteInsertToListIDFix(GenieFile->Civs[civ].Units[UnitIDs[0]].Bird.Commands, CommandIDs[0], copies->Dat.UnitCommands[copy]); copy++;
			}
			else
			{
				PasteInsertToListIDFix(GenieFile->Civs[civ].Units[UnitIDs[0]].Bird.Commands, CommandIDs[0], copies->Dat.UnitCommands[0]);
			}
		}
	}
	else
	{
		PasteInsertToListIDFix(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Bird.Commands, CommandIDs[0], copies->Dat.UnitCommands[0]);
	}
	ListUnitCommands();
}

void AGE_Frame::OnUnitCommandsCopyToUnits(wxCommandEvent &Event)
{
	if(GenieVersion <= genie::GV_AoKA)
	{
		for(short civ = 0; civ < GenieFile->Civs.size(); civ++)
		for(short loop=1; loop < UnitIDs.size(); loop++)
		{
			GenieFile->Civs[civ].Units[UnitIDs[loop]].Bird.Commands = GenieFile->Civs[civ].Units[UnitIDs[0]].Bird.Commands;
		}
	}
	else
	{
		for(short loop=1; loop < UnitIDs.size(); loop++)
		{
			GenieFile->UnitHeaders[UnitIDs[loop]].Commands = GenieFile->UnitHeaders[UnitIDs[0]].Commands;
		}
	}
}

void AGE_Frame::UnitLangDLLConverter(wxCommandEvent &Event)
{
	int32_t DLLValue;
	try
	{
		DLLValue = lexical_cast<int32_t>(((wxTextCtrl*)Event.GetEventObject())->GetValue());
	}
	catch(bad_lexical_cast e)
	{
		wxMessageBox("Incorrect input!");
		return;
	}
	if(Event.GetId() == Units_LanguageDLLConverter[0]->GetId())
	{
		if(GenieVersion <= genie::GV_RoR) DLLValue += 0x10000;
		else DLLValue += 79000;
		if(!AutoCopy)
		{
			GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].LanguageDLLHelp = DLLValue;
		}
		else for(short civ = 0; civ < GenieFile->Civs.size(); civ++)
		{
			GenieFile->Civs[civ].Units[UnitIDs[0]].LanguageDLLHelp = DLLValue;
		}
	}
	else
	{
		if(GenieVersion <= genie::GV_RoR) DLLValue += 0x20000;
		else DLLValue += 140000;
		if(!AutoCopy)
		{
			GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].LanguageDLLHotKeyText = DLLValue;
		}
		else for(short civ = 0; civ < GenieFile->Civs.size(); civ++)
		{
			GenieFile->Civs[civ].Units[UnitIDs[0]].LanguageDLLHotKeyText = DLLValue;
		}
	}
	wxCommandEvent E;
	OnUnitsSelect(E);
}

void AGE_Frame::CreateUnitControls()
{
//	UnitControls new things

	Tab_Units = new wxPanel(TabBar_Main, wxID_ANY, wxDefaultPosition, wxSize(0, 20));

	Units_Main = new wxBoxSizer(wxHORIZONTAL);
	Units_ListArea = new wxBoxSizer(wxVERTICAL);
	Units_Units = new wxStaticBoxSizer(wxVERTICAL, Tab_Units, "Units");
	//Units_Units_Line = new wxStaticLine(Tab_Units, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL, "");
	Units_Units_Special = new wxBoxSizer(wxHORIZONTAL);
	Units_Civs_List = new wxComboBox(Tab_Units, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	Units_Units_Search = new wxTextCtrl(Tab_Units, wxID_ANY);
	Units_Units_UseAnd[0] = new wxCheckBox(Tab_Units, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	Units_Units_Search_R = new wxTextCtrl(Tab_Units, wxID_ANY);
	Units_Units_UseAnd[1] = new wxCheckBox(Tab_Units, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	for(short loop = 0; loop < 2; loop++)
	{
		Units_Units_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
		Units_Units_SearchFilters[loop] = new wxOwnerDrawnComboBox(Tab_Units, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	}
	Units_Units_List = new wxListBox(Tab_Units, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	Units_Units_Buttons[0] = new wxGridSizer(3, 0, 0);
	Units_Units_Buttons[1] = new wxGridSizer(4, 0, 0);
	Units_Add = new wxButton(Tab_Units, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Units_Insert = new wxButton(Tab_Units, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	Units_Delete = new wxButton(Tab_Units, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Units_Copy = new wxButton(Tab_Units, wxID_ANY, "Copy *", wxDefaultPosition, wxSize(5, 20));
	Units_Copy->SetToolTip("When \"All civs\" is not selected,\nthis and pasting works just like automatic copy,\n(from current civilization to selected ones)\ntaking \"Including graphics\" option into account");
	Units_Paste = new wxButton(Tab_Units, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Units_PasteInsert = new wxButton(Tab_Units, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));
	Units_Info = new wxStaticText(Tab_Units, wxID_ANY, " Info *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Info->SetToolTip("Add/Insert/Delete works for all civilizations\n...");
	//Units_Extract = new wxButton(Tab_Units, wxID_ANY, "Extract", wxDefaultPosition, wxSize(5, 20));
	//Units_Extract->Enable(false);
	//Units_Import = new wxButton(Tab_Units, wxID_ANY, "Import", wxDefaultPosition, wxSize(5, 20));
	//Units_Import->Enable(false);
	Units_SpecialCopy = new wxButton(Tab_Units, wxID_ANY, "S copy", wxDefaultPosition, wxSize(5, 20));
	Units_SpecialPaste = new wxButton(Tab_Units, wxID_ANY, "S paste", wxDefaultPosition, wxSize(5, 20));
	Units_Enable = new wxButton(Tab_Units, wxID_ANY, "Enable", wxDefaultPosition, wxSize(5, 20));
	Units_Disable = new wxButton(Tab_Units, wxID_ANY, "Disable", wxDefaultPosition, wxSize(5, 20));
	Units_SpecialCopy_Options = new wxOwnerDrawnComboBox(Tab_Units, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	Units_SpecialCopy_Civs = new wxCheckBox(Tab_Units, wxID_ANY, "All civs *", wxDefaultPosition, wxSize(-1, 20));
	Units_SpecialCopy_Civs->SetToolTip("Whether buttons of units operate on all civilizations or just on the selected one\nNote that adding, inserting and deleting units always affect all civilizations!");

	Units_DataArea = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Top = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_TopGrid = new wxGridSizer(20, 1, 1);
	Units_AutoCopy = new wxCheckBox(Tab_Units, wxID_ANY, "Automatically", wxDefaultPosition, wxSize(-1, 20));
	Units_CopyTo = new wxButton(Tab_Units, wxID_ANY, "Copy", wxDefaultPosition, wxSize(40, 20));
	Units_CopyGraphics = new wxCheckBox(Tab_Units, wxID_ANY, "Including graphics", wxDefaultPosition, wxSize(-1, 20));
	Units_CopyToText = new wxStaticText(Tab_Units, wxID_ANY, " To selected civilizations: ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Units_SelectAll = new wxButton(Tab_Units, wxID_ANY, "All", wxDefaultPosition, wxSize(40, 20));
	Units_SelectClear = new wxButton(Tab_Units, wxID_ANY, "None", wxDefaultPosition, wxSize(40, 20));
	Units_GraphicSetText = new wxStaticText(Tab_Units, wxID_ANY, " Graphic set: ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Units_GraphicSet = new wxOwnerDrawnComboBox(Tab_Units, wxID_ANY, "", wxDefaultPosition, wxSize(120, 20), 0, NULL, wxCB_READONLY);
	Units_Holder_Type = new wxStaticBoxSizer(wxHORIZONTAL, Tab_Units, "");
	Units_Text_Type = new wxStaticText(Tab_Units, wxID_ANY, "Type ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Type = new TextCtrl_Byte(Tab_Units);
	Units_ComboBox_Type = new wxOwnerDrawnComboBox(Tab_Units, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	Units_Scroller = new wxScrolledWindow(Tab_Units, wxID_ANY, wxDefaultPosition, wxSize(0, 20), wxVSCROLL | wxTAB_TRAVERSAL);
	Units_ScrollerWindows = new wxBoxSizer(wxHORIZONTAL);
	Units_ScrollerWindowsSpace = new wxBoxSizer(wxVERTICAL);
	Units_Holder_TypeArea = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Type");
	Units_Holder_TypeArea1 = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_TypeArea2 = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_LangDLLArea = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Language DLLs");
	Units_Holder_GraphicsArea = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Graphics");
	Units_Holder_GraphicsArea1 = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_GraphicsArea4 = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_GraphicsArea5 = new wxBoxSizer(wxHORIZONTAL);
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
	Units_Holder_LangRegular = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_LangHotKey = new wxBoxSizer(wxHORIZONTAL);
	Units_Grid_AttributesTracking = new wxGridSizer(4, 5, 5);
	Units_Grid_AttributesTrain1 = new wxGridSizer(4, 5, 5);
	Units_Grid_Attributes3 = new wxGridSizer(4, 5, 5);
	Units_Holder_SoundsArea = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Sounds (that only you hear)");
	Units_Holder_SoundsArea1 = new wxBoxSizer(wxHORIZONTAL);
	Units_Grid_SoundsArea2 = new wxGridSizer(4, 5, 5);
	Units_Holder_MiscArea = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Miscellaneous");
	Units_Grid_HPBars = new wxGridSizer(4, 5, 5);
	Units_Holder_UnknownArea = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Type10plusUnknownArea = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Type 10+ Unknowns (All Units)");
	Units_Grid_Type10plusUnknowns = new wxGridSizer(4, 5, 5);
	Units_Holder_Type30plusUnknownArea = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Type 30+ Unknowns (Dead Fish)");
	Units_Grid_Type30plusUnknownArea = new wxGridSizer(4, 5, 5);
	Units_Holder_Type60plusUnknownArea = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Type 60+ Unknowns (Projectile)");
	Units_Holder_Type70plusUnknownArea = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Type 70+ Unknowns (Creatable)");
	Units_Grid_Type70plusUnknownArea = new wxGridSizer(4, 5, 5);
	Units_Holder_Type80plusUnknownArea = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Type 80+ Unknowns (Building)");
	Units_Grid_Type80plusUnknownArea = new wxGridSizer(4, 5, 5);
	Units_Holder_CommandsArea = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Commands");

//	Invisible Holder Windows
//	Type 10+

	Units_Holder_ID1 = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_LanguageDLLName = new wxBoxSizer(wxVERTICAL);
	Units_Holder_LanguageDLLCreation = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Class = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_StandingGraphic = new wxBoxSizer(wxVERTICAL);
	Units_Grid_StandingGraphic = new wxGridSizer(2, 0, 5);
	Units_Holder_DyingGraphic = new wxBoxSizer(wxVERTICAL);
	Units_Grid_DyingGraphic = new wxGridSizer(2, 0, 5);
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
	Units_Grid_Unknown3 = new wxGridSizer(4, 0, 0);
	Units_Holder_LanguageDLLHelp = new wxBoxSizer(wxVERTICAL);
	Units_Holder_LanguageDLLConverter[0] = new wxBoxSizer(wxVERTICAL);
	Units_Holder_LanguageDLLConverter[1] = new wxBoxSizer(wxVERTICAL);
	Units_Holder_LanguageDLLHotKeyText = new wxBoxSizer(wxVERTICAL);
	Units_Holder_HotKey = new wxBoxSizer(wxVERTICAL);
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
	Units_Holder_SelectionEffect = new wxBoxSizer(wxVERTICAL);
	Units_Holder_EditorSelectionColour = new wxBoxSizer(wxVERTICAL);
	Units_Holder_SelectionRadius = new wxBoxSizer(wxVERTICAL);
	Units_Holder_HPBarHeight2 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_ResourceStorageHeader = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Resource Storages");
	Units_Grid_ResourceStorage = new wxGridSizer(3, 0, 5);
	for(short loop = 0; loop < 3; loop++)
	Units_Holder_ResourceStorage[loop] = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_SelectionSound = new wxBoxSizer(wxVERTICAL);
	Units_Holder_DyingSound = new wxBoxSizer(wxVERTICAL);
	Units_Holder_AttackMode = new wxBoxSizer(wxVERTICAL);
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
	Units_Grid_WalkingGraphic = new wxGridSizer(2, 0, 5);
	Units_Holder_RotationSpeed = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown11 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_TrackingUnit = new wxBoxSizer(wxVERTICAL);
	Units_Holder_TrackingUnitUsed = new wxBoxSizer(wxVERTICAL);
	Units_Holder_TrackingUnitUsedBox = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_TrackingUnitDensity = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown12 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown16 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown16B = new wxBoxSizer(wxVERTICAL);
	Units_Grid_Unknown16B = new wxGridSizer(4, 5, 5);

//	Type 40+

	Units_Holder_SheepConversion = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_SearchRadius = new wxBoxSizer(wxVERTICAL);
	Units_Holder_WorkRate = new wxBoxSizer(wxVERTICAL);
	Units_Grid_DropSite = new wxGridSizer(4, 0, 5);
	Units_Holder_VillagerMode = new wxBoxSizer(wxVERTICAL);
	Units_Holder_AttackSound = new wxBoxSizer(wxVERTICAL);
	Units_Holder_MoveSound = new wxBoxSizer(wxVERTICAL);
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
	Units_Holder_Unknown27 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_MissileGraphicDelay = new wxBoxSizer(wxVERTICAL);
	Units_Holder_HeroMode = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_GarrisonGraphic = new wxBoxSizer(wxVERTICAL);
	Units_Grid_GarrisonGraphic = new wxGridSizer(2, 0, 5);
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
	Units_Holder_GarrisonHealRate = new wxBoxSizer(wxVERTICAL);
	Units_Holder_Unknown35 = new wxBoxSizer(wxVERTICAL);
	Units_Holder_AlfaThingy = new wxBoxSizer(wxVERTICAL);
	Units_Grid_AlfaThingy = new wxGridSizer(4, 0, 5);

//	Data Container Names
//	Type 10+

	Units_Text_ID1 = new wxStaticText(Units_Scroller, wxID_ANY, "ID 1 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_LanguageDLLName = new wxStaticText(Units_Scroller, wxID_ANY, " Language DLL Name *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_LanguageDLLCreation = new wxStaticText(Units_Scroller, wxID_ANY, " Language DLL Creation", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Class = new wxStaticText(Units_Scroller, wxID_ANY, "Class * ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_StandingGraphic = new wxStaticText(Units_Scroller, wxID_ANY, " Standing Graphic ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_DyingGraphic = new wxStaticText(Units_Scroller, wxID_ANY, " Dying Graphic ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_HitPoints = new wxStaticText(Units_Scroller, wxID_ANY, " Hit Points *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_LineOfSight = new wxStaticText(Units_Scroller, wxID_ANY, " Line Of Sight *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_GarrisonCapacity = new wxStaticText(Units_Scroller, wxID_ANY, " Garrison Capacity *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_SizeRadius = new wxStaticText(Units_Scroller, wxID_ANY, " Size Radius", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_HPBarHeight1 = new wxStaticText(Units_Scroller, wxID_ANY, " HP Bar Height 1 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_TrainSound = new wxStaticText(Units_Scroller, wxID_ANY, " Train Sound ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_DeadUnitID = new wxStaticText(Units_Scroller, wxID_ANY, " Dead Unit", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_PlacementMode = new wxStaticText(Units_Scroller, wxID_ANY, " Placement Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_IconID = new wxStaticText(Units_Scroller, wxID_ANY, " Icon *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
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
	Units_Text_LanguageDLLHelp = new wxStaticText(Units_Scroller, wxID_ANY, " Language DLL Help *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_LanguageDLLConverter[0] = new wxStaticText(Units_Scroller, wxID_ANY, " Help Converter *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_LanguageDLLConverter[1] = new wxStaticText(Units_Scroller, wxID_ANY, " Hotkey Text Converter *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_LanguageDLLHotKeyText = new wxStaticText(Units_Scroller, wxID_ANY, " Language DLL Hotkey Text *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_HotKey = new wxStaticText(Units_Scroller, wxID_ANY, " Hotkey *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown6 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 6 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
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
	Units_Text_AttackMode = new wxStaticText(Units_Scroller, wxID_ANY, " Attack Mode? *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
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
	Units_Text_Unknown16B = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 16B", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Type 40+

	Units_Text_SearchRadius = new wxStaticText(Units_Scroller, wxID_ANY, " Search Radius ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_WorkRate = new wxStaticText(Units_Scroller, wxID_ANY, " Work Rate ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_DropSite = new wxStaticText(Units_Scroller, wxID_ANY, " Drop Site *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_VillagerMode = new wxStaticText(Units_Scroller, wxID_ANY, " Villager Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_AttackSound = new wxStaticText(Units_Scroller, wxID_ANY, " Attack Sound", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_MoveSound = new wxStaticText(Units_Scroller, wxID_ANY, " Move Sound", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Exists = new wxStaticText(Units_Scroller, wxID_ANY, " Exists", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Type 60+

	Units_Text_Unknown20 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 20 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
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
	Units_Text_GarrisonRecoveryRate = new wxStaticText(Units_Scroller, wxID_ANY, " Accuracy Error Radius *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
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
	Units_Text_Unknown27 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 27 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
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
	Units_Text_ResearchID = new wxStaticText(Units_Scroller, wxID_ANY, " Initiates Research *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown33 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 33 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_AnnexUnit = new wxStaticText(Units_Scroller, wxID_ANY, " Annex Units", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_AnnexUnitMisplacement = new wxStaticText(Units_Scroller, wxID_ANY, " Annex Units Misplacement", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_HeadUnit = new wxStaticText(Units_Scroller, wxID_ANY, " Head Unit *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_TransformUnit = new wxStaticText(Units_Scroller, wxID_ANY, " Transform Unit *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown34 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 34 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_ConstructionSound = new wxStaticText(Units_Scroller, wxID_ANY, " Construction Sound ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_GarrisonType = new wxStaticText(Units_Scroller, wxID_ANY, " Garrison Type ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_GarrisonHealRate = new wxStaticText(Units_Scroller, wxID_ANY, " Garrison Heal Rate *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_Unknown35 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 35", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Text_AlfaThingy = new wxStaticText(Units_Scroller, wxID_ANY, " Related to Annexes? Widespread usage in AoK Alpha 09.07.0222", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Data Containers

	Units_Class = new TextCtrl_Short(Units_Scroller);
	Units_Class->SetToolTip("Determines many things and works in conjunction with other variables");
	Units_ComboBox_Class[0] = new ComboBox_Plus1(Units_Scroller, Units_Class);
	Units_ID1 = new TextCtrl_Short(Units_Scroller);
	Units_ID2 = new TextCtrl_Short(Units_Scroller);
	Units_ID3 = new TextCtrl_Short(Units_Scroller);
	Units_Name = new TextCtrl_String(Units_Scroller, 30);
	Units_Name2 = new TextCtrl_String(Units_Scroller, 30);
	Units_LanguageDLLName = new TextCtrl_UShort(Units_Scroller);
	Units_LanguageDLLName->SetToolTip("Usual Unit DLL Pattern for The Conquerors\nName: 5000-5999\nCreation: Name +1000\nHotkey: Name +11000\nHelp: Name +100000, in DLL Name +21000\nHotkey Text: Name +150000, in DLL Name +10000\nSomething: Name +9000");
	Units_DLL_LanguageName = new TextCtrl_DLL(Units_Scroller, wxSize(0, 20));
	Units_LanguageDLLCreation = new TextCtrl_UShort(Units_Scroller);
	Units_DLL_LanguageCreation = new TextCtrl_DLL(Units_Scroller, wxSize(0, 20));
	Units_HotKey = new TextCtrl_Long(Units_Scroller);
	Units_HotKey->SetToolTip("10000 + Language DLL Creation (usually)");
	Units_DLL_HotKey4 = new TextCtrl_DLL(Units_Scroller, wxSize(0, 20));
	Units_LanguageDLLHelp = new TextCtrl_Long(Units_Scroller);
	Units_LanguageDLLHelp->SetToolTip("100000 + Language DLL Name\nThis is probably linked to the help text below");
	Units_LanguageDLLConverter[0] = new wxTextCtrl(Units_Scroller, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	Units_LanguageDLLConverter[0]->SetToolTip("Language help text in DLL\nHit enter to get the correction into dat file");
	Units_DLL_LanguageHelp = new TextCtrl_DLL(Units_Scroller, wxSize(0, 55));
	Units_LanguageDLLHotKeyText = new TextCtrl_Long(Units_Scroller);
	Units_LanguageDLLHotKeyText->SetToolTip("150000 + Language DLL Name\nThis seems to be used only in AoE (not RoR)\nThis language line has other purposes in SWGB and CC");
	Units_LanguageDLLConverter[1] = new wxTextCtrl(Units_Scroller, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	Units_LanguageDLLConverter[1]->SetToolTip("Language hotkey text in DLL\nHit enter to get the correction into dat file");
	Units_DLL_LanguageHKText = new TextCtrl_DLL(Units_Scroller, wxSize(0, 20));

	Units_IconID = new TextCtrl_Short(Units_Scroller);
	Units_IconID->SetToolTip("Download Turtle Pack from AoKH to add more than 127 icons.");
	Units_ConstructionGraphicID = new TextCtrl_Short(Units_Scroller);
	Units_ComboBox_ConstructionGraphicID = new ComboBox_Plus1(Units_Scroller, Units_ConstructionGraphicID);
	Units_SnowGraphicID = new TextCtrl_Short(Units_Scroller);
	Units_ComboBox_SnowGraphicID = new ComboBox_Plus1(Units_Scroller, Units_SnowGraphicID);
	Units_AttackGraphic = new TextCtrl_Short(Units_Scroller);
	Units_ComboBox_AttackGraphic = new ComboBox_Plus1(Units_Scroller, Units_AttackGraphic);
	for(short loop = 0; loop < 2; loop++)
	{
		Units_StandingGraphic[loop] = new TextCtrl_Short(Units_Scroller);
		Units_ComboBox_StandingGraphic[loop] = new ComboBox_Plus1(Units_Scroller, Units_StandingGraphic[loop]);
	}
	for(short loop = 0; loop < 2; loop++)
	{
		Units_GarrisonGraphic[loop] = new TextCtrl_Short(Units_Scroller);
		Units_ComboBox_GarrisonGraphic[loop] = new ComboBox_Plus1(Units_Scroller, Units_GarrisonGraphic[loop]);
	}
	for(short loop = 0; loop < 2; loop++)
	{
		Units_WalkingGraphic[loop] = new TextCtrl_Short(Units_Scroller);
		Units_ComboBox_WalkingGraphic[loop] = new ComboBox_Plus1(Units_Scroller, Units_WalkingGraphic[loop]);
	}
	for(short loop = 0; loop < 2; loop++)
	{
		Units_DyingGraphic[loop] = new TextCtrl_Short(Units_Scroller);
		Units_ComboBox_DyingGraphic[loop] = new ComboBox_Plus1(Units_Scroller, Units_DyingGraphic[loop]);
	}

	Units_DamageGraphics = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Damage Graphics");
	Units_DamageGraphics_ListArea = new wxBoxSizer(wxVERTICAL);
	Units_DamageGraphics_Search = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_DamageGraphics_Search_R = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_DamageGraphics_List = new wxListBox(Units_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	Units_DamageGraphics_Buttons = new wxGridSizer(3, 0, 0);
	Units_DamageGraphics_Add = new wxButton(Units_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Units_DamageGraphics_Insert = new wxButton(Units_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	Units_DamageGraphics_Delete = new wxButton(Units_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Units_DamageGraphics_Copy = new wxButton(Units_Scroller, wxID_ANY, "Copy *", wxDefaultPosition, wxSize(5, 20));
	Units_DamageGraphics_Copy->SetToolTip("When \"All civs\" is not selected,\nthis and pasting works only for current civilization");
	Units_DamageGraphics_Paste = new wxButton(Units_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Units_DamageGraphics_PasteInsert = new wxButton(Units_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));
	Units_DamageGraphics_CopyToUnits = new wxButton(Units_Scroller, wxID_ANY, "Copy all to selected units", wxDefaultPosition, wxSize(5, 20));
	Units_Holder_DamageGraphics = new wxGridSizer(2, 5, 5);
	Units_Holder_DamageGraphics_Data = new wxBoxSizer(wxVERTICAL);
	DamageGraphics_Holder_GraphicID = new wxBoxSizer(wxVERTICAL);
	DamageGraphics_Text_GraphicID = new wxStaticText(Units_Scroller, wxID_ANY, " Graphic ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	DamageGraphics_GraphicID = new TextCtrl_Short(Units_Scroller);
	DamageGraphics_ComboBox_GraphicID = new ComboBox_Plus1(Units_Scroller, DamageGraphics_GraphicID);
	DamageGraphics_Holder_DamagePercent = new wxBoxSizer(wxVERTICAL);
	DamageGraphics_Text_DamagePercent = new wxStaticText(Units_Scroller, wxID_ANY, " Damage Percent ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	DamageGraphics_DamagePercent = new TextCtrl_Byte(Units_Scroller);
	DamageGraphics_Holder_Unknown1 = new wxBoxSizer(wxVERTICAL);
	DamageGraphics_Text_Unknown1 = new wxStaticText(Units_Scroller, wxID_ANY, " Apply Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	DamageGraphics_Unknown1 = new TextCtrl_Byte(Units_Scroller);
	DamageGraphics_Unknown1->SetToolTip("0 (& 1?) Adds graphics on top (flames on buildings)\n2 Replaces original graphics (damaged walls)");
	DamageGraphics_Holder_Unknown2 = new wxBoxSizer(wxVERTICAL);
	DamageGraphics_Text_Unknown2 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 2 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	DamageGraphics_Unknown2 = new TextCtrl_Byte(Units_Scroller);

	Units_HitPoints = new TextCtrl_Short(Units_Scroller);
	Units_HitPoints->SetToolTip("-1 Instantly dying unit");
	Units_Speed = new TextCtrl_Float(Units_Scroller);
	Units_RotationSpeed = new TextCtrl_Float(Units_Scroller);
	Units_RotationSpeed->SetToolTip("Makes it slower");
	Units_LineOfSight = new TextCtrl_Float(Units_Scroller);
	Units_LineOfSight->SetToolTip("Maximum (effective) value is 20");
	Units_SearchRadius = new TextCtrl_Float(Units_Scroller);
	Units_MaxRange = new TextCtrl_Float(Units_Scroller);
	Units_MinRange = new TextCtrl_Float(Units_Scroller);
	Units_DisplayedRange = new TextCtrl_Float(Units_Scroller);

	Units_Attacks = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Attacks");
	Units_Attacks_ListArea = new wxBoxSizer(wxVERTICAL);
	Units_Attacks_DataArea = new wxBoxSizer(wxVERTICAL);
	Units_Attacks_Search = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_Attacks_Search_R = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_Attacks_List = new wxListBox(Units_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	Units_Attacks_Buttons = new wxGridSizer(3, 0, 0);
	Units_Attacks_Add = new wxButton(Units_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Units_Attacks_Insert = new wxButton(Units_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	Units_Attacks_Delete = new wxButton(Units_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Units_Attacks_Copy = new wxButton(Units_Scroller, wxID_ANY, "Copy *", wxDefaultPosition, wxSize(5, 20));
	Units_Attacks_Copy->SetToolTip("When \"All civs\" is not selected,\nthis and pasting works only for current civilization");
	Units_Attacks_Paste = new wxButton(Units_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Units_Attacks_PasteInsert = new wxButton(Units_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));
	Units_Attacks_CopyToUnits = new wxButton(Units_Scroller, wxID_ANY, "Copy all to selected units", wxDefaultPosition, wxSize(5, 20));
	Units_Holder_Attacks = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_Attacks_Data = new wxBoxSizer(wxVERTICAL);
	Units_Grid_Attacks_Data2 = new wxGridSizer(2, 5, 5);
	Attacks_Holder_Amount = new wxBoxSizer(wxVERTICAL);
	Attacks_Text_Amount = new wxStaticText(Units_Scroller, wxID_ANY, " Amount", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Attacks_Amount = new TextCtrl_Short(Units_Scroller);
	Attacks_Holder_Class = new wxBoxSizer(wxVERTICAL);
	Attacks_Text_Class = new wxStaticText(Units_Scroller, wxID_ANY, " Class *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Attacks_Class = new TextCtrl_Short(Units_Scroller);
	Attacks_Class->SetToolTip("Armor class that this unit can damage\nYou can make your own classes");
	Attacks_ComboBox_Class[0] = new ComboBox_Plus1(Units_Scroller, Attacks_Class);

	Units_DisplayedAttack = new TextCtrl_Short(Units_Scroller);
	Units_Delay = new TextCtrl_Short(Units_Scroller);
	Units_Delay->SetToolTip("Graphical delay in frames before projectile is shot");
	Units_AccuracyPercent = new TextCtrl_Short(Units_Scroller);
	Units_GarrisonRecoveryRate = new TextCtrl_Float(Units_Scroller);
	Units_GarrisonRecoveryRate->SetToolTip("Higher values will make the unit less accurate");
	Units_ReloadTime1 = new TextCtrl_Float(Units_Scroller);
	Units_ReloadTime2 = new TextCtrl_Float(Units_Scroller);
	Units_BlastRadius = new TextCtrl_Float(Units_Scroller);
	Units_BlastLevel = new TextCtrl_Byte(Units_Scroller);
	Units_BlastLevel->SetToolTip("How blast radius affects units\n0 Damages resources also\n1 Damages trees also\n2 Damages nearby units\n3 Damages only targeted unit");

	Units_Armors = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Armors");
	Units_Armors_ListArea = new wxBoxSizer(wxVERTICAL);
	Units_Armors_DataArea = new wxBoxSizer(wxVERTICAL);
	Units_Armors_Search = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_Armors_Search_R = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_Armors_List = new wxListBox(Units_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 100), 0, NULL, wxLB_EXTENDED);
	Units_Armors_Buttons = new wxGridSizer(3, 0, 0);
	Units_Armors_Add = new wxButton(Units_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Units_Armors_Insert = new wxButton(Units_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	Units_Armors_Delete = new wxButton(Units_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Units_Armors_Copy = new wxButton(Units_Scroller, wxID_ANY, "Copy *", wxDefaultPosition, wxSize(5, 20));
	Units_Armors_Copy->SetToolTip("When \"All civs\" is not selected,\nthis and pasting works only for current civilization");
	Units_Armors_Paste = new wxButton(Units_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Units_Armors_PasteInsert = new wxButton(Units_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));
	Units_Armors_CopyToUnits = new wxButton(Units_Scroller, wxID_ANY, "Copy all to selected units", wxDefaultPosition, wxSize(5, 20));
	Units_Holder_Armors = new wxBoxSizer(wxHORIZONTAL);
	Units_Holder_Armors_Data3 = new wxBoxSizer(wxVERTICAL);
	Armors_Holder_Amount = new wxBoxSizer(wxVERTICAL);
	Armors_Text_Amount = new wxStaticText(Units_Scroller, wxID_ANY, " Amount", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Armors_Amount = new TextCtrl_Short(Units_Scroller);
	Armors_Holder_Class = new wxBoxSizer(wxVERTICAL);
	Armors_Text_Class = new wxStaticText(Units_Scroller, wxID_ANY, " Class *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Armors_Class = new TextCtrl_Short(Units_Scroller);
	Armors_Class->SetToolTip("Attack class from which this unit can take damage\nYou can make your own classes");
	Attacks_ComboBox_Class[1] = new ComboBox_Plus1(Units_Scroller, Armors_Class);

	Units_DisplayedMeleeArmour = new TextCtrl_Short(Units_Scroller);
	Units_DisplayedPierceArmour = new TextCtrl_Short(Units_Scroller);
	Units_GarrisonCapacity = new TextCtrl_Byte(Units_Scroller);
	Units_GarrisonCapacity->SetToolTip("If the unit has garrisoned units inside,\ngraphics tab \"New Speed?\" determines its new speed?");
	Units_GarrisonType = new TextCtrl_Byte(Units_Scroller);
	Units_ComboBox_GarrisonType = new ComboBox_Plus1(Units_Scroller, Units_GarrisonType);
	Units_GarrisonHealRate = new TextCtrl_Float(Units_Scroller);
	Units_GarrisonHealRate->SetToolTip("Building's garrisoned units' healing speed factor");
	Units_ResourceCapacity = new TextCtrl_Short(Units_Scroller);
	Units_ResourceDecay = new TextCtrl_Float(Units_Scroller);
	Units_ResourceDecay->SetToolTip("Can alter corpses' decay time\nSet to -1 for never decaying");
	Units_WorkRate = new TextCtrl_Float(Units_Scroller);

	Units_ProjectileUnitID = new TextCtrl_Short(Units_Scroller);
	Units_ComboBox_ProjectileUnitID = new ComboBox_Plus1(Units_Scroller, Units_ProjectileUnitID);
	Units_AttackMissileDuplicationUnit = new TextCtrl_Long(Units_Scroller);
	Units_AttackMissileDuplicationUnit->SetToolTip("Uses its own attack values!");
	Units_ComboBox_AttackMissileDuplicationUnit = new ComboBox_Plus1(Units_Scroller, Units_AttackMissileDuplicationUnit);
	Units_AttackMissileDuplicationGraphic = new TextCtrl_Long(Units_Scroller);
	Units_ComboBox_AttackMissileDuplicationGraphic = new ComboBox_Plus1(Units_Scroller, Units_AttackMissileDuplicationGraphic);
	Units_MissileGraphicDelay = new TextCtrl_Byte(Units_Scroller);
	Units_MissileGraphicDelay->SetToolTip("0 projectiles, buildings, dead units, boar\n1 villagers\n2 melee\n3 mounted units\n4 relic cart, relics\n5 archers\n6 monks");
	Units_AttackMissileDuplicationAmount1 = new TextCtrl_Float(Units_Scroller);
	Units_AttackMissileDuplicationAmount1->SetToolTip("Duplicated missiles when no units are garrisoned inside");
	Units_AttackMissileDuplicationAmount2 = new TextCtrl_Byte(Units_Scroller);
	Units_AttackMissileDuplicationAmount2->SetToolTip("Maximum duplicated missiles when garrison capacity is full");
	for(short loop = 0; loop < 3; loop++)
	Units_AttackMissileDuplicationSpawning[loop] = new TextCtrl_Float(Units_Scroller);
	Units_AttackMissileDuplicationSpawning[0]->SetToolTip("Spawning area's width");
	Units_AttackMissileDuplicationSpawning[1]->SetToolTip("Spawning area's length");
	Units_AttackMissileDuplicationSpawning[2]->SetToolTip("Spawning point's randomness inside the spawning area\n0 From a single spot\n1 Totally randomly inside the spawning area\n1+ Less randomly");
	for(short loop = 0; loop < 3; loop++)
	Units_GraphicDisplacement[loop] = new TextCtrl_Float(Units_Scroller);
	Units_GraphicDisplacement[0]->SetToolTip("Left/Right distance");
	Units_GraphicDisplacement[1]->SetToolTip("Spawning distance from the unit");
	Units_GraphicDisplacement[2]->SetToolTip("Height");
	Units_ProjectileArc = new TextCtrl_Float(Units_Scroller);
	Units_StretchMode = new TextCtrl_Byte(Units_Scroller);
	Units_StretchMode->SetToolTip("0 Default\n1 Projectile falls vertically to the bottom of the map");
	Units_CompensationMode = new TextCtrl_Byte(Units_Scroller);
	Units_DropAnimationMode = new TextCtrl_Byte(Units_Scroller);
	Units_DropAnimationMode->SetToolTip("0 Doesn't disappear after hitting the target\n1 Disappears");
	Units_PenetrationMode = new TextCtrl_Byte(Units_Scroller);
	Units_PenetrationMode->SetToolTip("0 Stops the graphics\n1 Graphics pass through the target instead of stopping\nOnly affects the graphics of the projectile");
	Units_Unknown24 = new TextCtrl_Byte(Units_Scroller);

	Units_Enabled = new TextCtrl_Short(Units_Scroller);
	Units_Enabled->SetToolTip("0 Requires a research to be available\n1 Available without a research");
	Units_CheckBox_Enabled = new CheckBox_2State(Units_Scroller, "No Research *", Units_Enabled);
	Units_HideInEditor = new TextCtrl_Byte(Units_Scroller);
	Units_CheckBox_HideInEditor = new CheckBox_2State(Units_Scroller, "Hide In Editor", Units_HideInEditor);
	Units_DeathMode = new TextCtrl_Byte(Units_Scroller);
	Units_DeathMode->SetToolTip("Reviving does not make it usable");
	Units_CheckBox_DeathMode = new CheckBox_2State(Units_Scroller, "Death: Revives *", Units_DeathMode);
	Units_HeroMode = new TextCtrl_Byte(Units_Scroller);
	Units_CheckBox_HeroMode = new CheckBox_2State(Units_Scroller, "Hero Mode", Units_HeroMode);
	Units_AirMode = new TextCtrl_Byte(Units_Scroller);
	Units_AirMode->SetToolTip("1 for no footprints");
	Units_CheckBox_AirMode = new CheckBox_2State(Units_Scroller, "Air Mode *", Units_AirMode);
	Units_FlyMode = new TextCtrl_Byte(Units_Scroller);
	Units_FlyMode->SetToolTip("Requires class 22 and air mode 1?\n0 Normal\n1 Graphics appear higher than the shadow");
	Units_CheckBox_FlyMode = new CheckBox_2State(Units_Scroller, "Fly Mode", Units_FlyMode);
	Units_SheepConversion = new TextCtrl_Short(Units_Scroller);
	Units_SheepConversion->SetToolTip("To get the unit auto-converted to enemy,\nuse unit command 107, which sheep and monument have\nAll somehow auto-convertible units have this set to 0\nMost other units have -1");
	Units_CheckBox_SheepConversion = new CheckBox_ZeroIsYes(Units_Scroller, "Convert Herd *", Units_SheepConversion);
	Units_AnimalMode = new TextCtrl_Byte(Units_Scroller);
	Units_CheckBox_AnimalMode = new CheckBox_2State(Units_Scroller, "Animal Mode", Units_AnimalMode);
	Units_TowerMode = new TextCtrl_Byte(Units_Scroller);
	Units_CheckBox_TowerMode = new CheckBox_2State(Units_Scroller, "Tower Mode", Units_TowerMode);
	Units_AdjacentMode = new TextCtrl_Short(Units_Scroller);
	Units_AdjacentMode->SetToolTip("0 Default\n1 Adjacent buildings can change this unit's graphics");
	Units_CheckBox_AdjacentMode = new CheckBox_2State(Units_Scroller, "Adjacent Mode *", Units_AdjacentMode);
	Units_Text_VisibleInFog = new wxStaticText(Units_Scroller, wxID_ANY, " Fog Visibility *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_VisibleInFog = new TextCtrl_Byte(Units_Scroller);
	Units_VisibleInFog->SetToolTip("0 Not visible\n1 Visible\n3 Inverted visibility");
	Units_BuildingMode = new TextCtrl_Byte(Units_Scroller);
	Units_BuildingMode->SetToolTip("0 non buildings, gates, farms, walls, towers\n2 town center, trade workshop, CLF01, port\n3 any building");
	Units_PlacementMode = new TextCtrl_Byte(Units_Scroller);
	Units_PlacementMode->SetToolTip("0 Can be placed on top of other units in scenario editor\n5 Cannot be placed on top of other units in scenario editor");
	Units_InteractionMode = new TextCtrl_Byte(Units_Scroller);
	Units_InteractionMode->SetToolTip("0 & 1 Unable to select, move or attack\n2 Can select, unable to move or attack\n3 Can select and attack, unable to move\n4 Can select, move and attack\n5+ Select and move?");
	Units_MinimapMode = new TextCtrl_Byte(Units_Scroller);
	Units_MinimapMode->SetToolTip("0 & 6-10 No dot on minimap\n1 Square dot turning white when selected\n2 Diamond dot turning white when selected\n3 Diamond dot keeping color\n4 & 5 Larger spot, not following the unit, no blinking when attacked, everyone can see it\n");
	Units_VillagerMode = new TextCtrl_Byte(Units_Scroller);
	Units_VillagerMode->SetToolTip("Changes according to task\n1 Male\n2 Female");
	Units_BlastType = new TextCtrl_Byte(Units_Scroller);
	Units_BlastType->SetToolTip("0 projectiles, dead units, fish, relics, trees\n0 gates, town center\n0 deer(unmoving), FLDOG\n1 things listed under \"others\" that have multiple rotations\n2 buildings, gates, walls, town centers, fish trap\n3 boar\n3 farm, TWAL\n3 fishing ship, villagers, trade carts, sheep, turkey\n3 (any unit) archers, junk, trade cogs, ships, seige, mounted, deer(regular), monk with relic\n3 monks, BDGAL, ABGAL");
	Units_Unknown2 = new TextCtrl_Byte(Units_Scroller);
	Units_Unknown2->SetToolTip("Action from mouse right-click?\n0 projectiles, dead units, fish, relics, trees\n2 gates, town center\n4 deer(unmoving), FLDOG\n0 things listed under \"others\" that have multiple rotations\n2 buildings, gates, walls, town centers, fish trap\n1 boar\n2 farm, TWAL\n3 fishing ship, villagers, trade carts, sheep, turkey\n4 (any unit) archers, junk, trade cogs, ships, seige, mounted, deer(regular), monk with relic\n5 monks, BDGAL, ABGAL");
	Units_Attribute = new TextCtrl_Byte(Units_Scroller);
	Units_Attribute->SetToolTip("This looks like one byte of eight booleans\nYou can probably combine these attributes\n0 Default\n(1st bit) 1, 3, 5 Allows units to garrison inside\n(2nd bit) 2 Causes the unit not to join formations\nStar Wars:\n(3rd bit) 4 Stealth unit\n(4th bit) 8 Detector unit\n(5th bit) 16 Mechanical unit\n(6th bit) 32 Biological unit\n(7th bit) 64 Self-shielding unit");
	Units_MinTechLevel = new TextCtrl_Byte(Units_Scroller);
	Units_DeadUnitID = new TextCtrl_Short(Units_Scroller);
	Units_ComboBox_DeadUnitID = new ComboBox_Plus1(Units_Scroller, Units_DeadUnitID);
	Units_ResearchID = new TextCtrl_Short(Units_Scroller);
	Units_ResearchID->SetToolTip("Causes that research to be researched when the building is created");
	Units_ComboBox_ResearchID = new ComboBox_Plus1(Units_Scroller, Units_ResearchID);
	Units_Civ = new TextCtrl_Byte(Units_Scroller);
	Units_ComboBox_Civ = new ComboBox_Plus1(Units_Scroller, Units_Civ);
	Units_Unitline = new TextCtrl_Short(Units_Scroller);
	Units_ComboBox_Unitline = new ComboBox_Plus1(Units_Scroller, Units_Unitline);
	for(short loop = 0; loop < 2; loop++)
	{
		Units_PlacementTerrain[loop] = new TextCtrl_Short(Units_Scroller);
		Units_ComboBox_PlacementTerrain[loop] = new ComboBox_Plus1(Units_Scroller, Units_PlacementTerrain[loop]);
	}
	for(short loop = 0; loop < 2; loop++)
	{
		Units_PlacementBypassTerrain[loop] = new TextCtrl_Short(Units_Scroller);
		Units_PlacementBypassTerrain[loop]->SetToolTip("Required terrain on some side");
		Units_ComboBox_PlacementBypassTerrain[loop] = new ComboBox_Plus1(Units_Scroller, Units_PlacementBypassTerrain[loop]);
	}
	Units_TerrainRestriction = new TextCtrl_Short(Units_Scroller);
	Units_ComboBox_TerrainRestriction = new ComboBox_Plus1(Units_Scroller, Units_TerrainRestriction);
	Units_TerrainID = new TextCtrl_Short(Units_Scroller);
	Units_TerrainID->SetToolTip("Terrain produced under a building when completed");
	Units_ComboBox_TerrainID = new ComboBox_Plus1(Units_Scroller, Units_TerrainID);
	for(short loop = 0; loop < 2; loop++)
	{
		Units_DropSite[loop] = new TextCtrl_Short(Units_Scroller);
		Units_DropSite[loop]->SetToolTip("Giving a villager's drop site to a cart-like unit\ncan allow you to have mobile resource-gatherers,\nsimilar to those in Age of Mythology.");
		Units_ComboBox_DropSite[loop] = new ComboBox_Plus1(Units_Scroller, Units_DropSite[loop]);
	}
	for(short loop = 0; loop < 2; loop++)
	Units_SizeRadius[loop] = new TextCtrl_Float(Units_Scroller);
	for(short loop = 0; loop < 2; loop++)
	Units_EditorRadius[loop] = new TextCtrl_Float(Units_Scroller);
	Units_SelectionRadiusBox = new wxBoxSizer(wxHORIZONTAL);
	for(short loop = 0; loop < 2; loop++)
	Units_SelectionRadius[loop] = new TextCtrl_Float(Units_Scroller);
	Units_Unselectable = new TextCtrl_Byte(Units_Scroller);
	Units_CheckBox_Unselectable = new CheckBox_2State(Units_Scroller, "Unselectable", Units_Unselectable);
	Units_SelectionMask = new TextCtrl_Byte(Units_Scroller);
	Units_SelectionMask->SetToolTip("Any odd value except 7 - Mask displayed behind buildings\nAny even value except 6, 10 - Mask not displayed\n-1, 7 - Mask partially displayed when in the open\n6, 10 - Building, causes mask to appear on units behind it\n");
	Units_SelectionShape = new TextCtrl_Byte(Units_Scroller);
	Units_SelectionShape->SetToolTip("0 Square\n1+ Round");
	Units_SelectionShapeType = new TextCtrl_Byte(Units_Scroller);
	Units_SelectionEffect = new TextCtrl_Byte(Units_Scroller);
	Units_SelectionEffect->SetToolTip("0\n1 HP Bar on, permanent darker outline in editor only\n4 HP Bar off, normal outline\n5, 8-9 HP Bar on\n2 HP Bar on, normal outline\n3 HP Bar off, selection shadow\n6-7 HP Bar off\nNote: this doesn't work with all units");
	Units_EditorSelectionColour = new TextCtrl_Byte(Units_Scroller);
	Units_EditorSelectionColour->SetToolTip("0 most\n-16 fish trap farm\n52 dead farm, OLD-(___)\n116 flare, WHAL1, WHAL2, DOLP, Great-fish\n-123 all fish");
	Units_TrainLocationID = new TextCtrl_Short(Units_Scroller);
	Units_ComboBox_TrainLocationID = new ComboBox_Plus1(Units_Scroller, Units_TrainLocationID);
	Units_TrainTime = new TextCtrl_Short(Units_Scroller);
	Units_CommandAttribute = new TextCtrl_Short(Units_Scroller);
	Units_CommandAttribute->SetToolTip("Class and this sets the interface for this unit\n0 Commands: Delete, Garrison, Stop | Attributes: Hit Points\n1 Animal\n2 Non-Military Building (build page 1)\n3 Villager\n4 Military Unit\n5 Trading Unit\n6 Monk\n7 Transport Ship\n8 Relic / Monk with Relic\n9 Fishing Ship\n10 Military Building (build page 2)\n11 Shield Building (build page 3)");
	Units_ButtonID = new TextCtrl_Byte(Units_Scroller);
	Units_ButtonID->SetToolTip("First page (also second in TC) 1-15\nSecond (dock) page 21-35\nThird page same as first (Star Wars)\nFirst page in AoE/RoR 1-10\nSecond page in AoE/RoR 11-20");
	for(short loop = 0; loop < 3; loop++)
	{
		Units_CostType[loop] = new TextCtrl_Short(Units_Scroller);
		Units_ComboBox_CostType[loop] = new ComboBox_Plus1(Units_Scroller, Units_CostType[loop]);
		Units_CostAmount[loop] = new TextCtrl_Short(Units_Scroller);
		Units_CostUsed[loop] = new TextCtrl_Short(Units_Scroller);
		Units_CostUsed[loop]->SetToolTip("If set to 0 and there is an amount, the amount is required but not paid");
		Units_CheckBox_CostUsed[loop] = new CheckBox_2State(Units_Scroller, "Used", Units_CostUsed[loop]);
	}
	for(short loop = 0; loop < 3; loop++)
	{
		ResourceStorage_Type[loop] = new TextCtrl_Short(Units_Scroller);
		ResourceStorage_ComboBox_Type[loop] = new ComboBox_Plus1(Units_Scroller, ResourceStorage_Type[loop]);
		ResourceStorage_Amount[loop] = new TextCtrl_Float(Units_Scroller);
		ResourceStorage_Enabled[loop] = new TextCtrl_Byte(Units_Scroller);
		ResourceStorage_Enabled[loop]->SetToolTip("0 Decayable resource\n1 Stored after death also\n2 Resets on dying, enables instantly\n4 Resets on dying, enables on completion");
	}
	for(short loop = 0; loop < 4; loop++)
	Units_TrackingUnit = new TextCtrl_Short(Units_Scroller);
	Units_ComboBox_TrackingUnit = new ComboBox_Plus1(Units_Scroller, Units_TrackingUnit);
	Units_TrackingUnitUsed = new TextCtrl_Byte(Units_Scroller);
	Units_TrackingUnitUsed->SetToolTip("-1 unless a tracking unit value is present\n2 all projectiles with a tracking unit");
	Units_TrackingUnitDensity = new TextCtrl_Float(Units_Scroller);
	Units_TrackingUnitDensity->SetToolTip("0 unless tracking unit value is present\n0.5 trade carts\n0.12 MFFFG(projectile)\n0.4 other projectiles");
	Units_StackUnitID = new TextCtrl_Short(Units_Scroller);
	Units_StackUnitID->SetToolTip("Second building to be placed directly on top of this building\nAdditional building gets added every time you load the scenario");
	Units_ComboBox_StackUnitID = new ComboBox_Plus1(Units_Scroller, Units_StackUnitID);
	Units_HeadUnit = new TextCtrl_Short(Units_Scroller);
	Units_HeadUnit->SetToolTip("The building that an annex building is attached to");
	Units_ComboBox_HeadUnit = new ComboBox_Plus1(Units_Scroller, Units_HeadUnit);
	Units_TransformUnit = new TextCtrl_Short(Units_Scroller);
	Units_TransformUnit->SetToolTip("Determines what the unit changes into when given the order to unpack");
	Units_ComboBox_TransformUnit = new ComboBox_Plus1(Units_Scroller, Units_TransformUnit);
	for(short loop = 0; loop < 4; loop++)
	{
		Units_AnnexUnit[loop] = new TextCtrl_Short(Units_Scroller);
		Units_ComboBox_AnnexUnit[loop] = new ComboBox_Plus1(Units_Scroller, Units_AnnexUnit[loop]);
	}
	for(short loop = 0; loop < 4; loop++)
	{
		for(short loop2 = 0; loop2 < 2; loop2++)
		Units_AnnexUnitMisplacement[loop][loop2] = new TextCtrl_Float(Units_Scroller);
	}
	for(short loop = 0; loop < Units_AlfaThingy.size(); loop++)
	Units_AlfaThingy[loop] = new TextCtrl_Byte(Units_Scroller);

	Units_ConstructionSound = new TextCtrl_Short(Units_Scroller);
	Units_ComboBox_ConstructionSound = new ComboBox_Plus1(Units_Scroller, Units_ConstructionSound);
	for(short loop = 0; loop < 2; loop++)
	{
		Units_TrainSound[loop] = new TextCtrl_Short(Units_Scroller);
		Units_ComboBox_TrainSound[loop] = new ComboBox_Plus1(Units_Scroller, Units_TrainSound[loop]);
	}
	Units_SelectionSound = new TextCtrl_Short(Units_Scroller);
	Units_ComboBox_SelectionSound = new ComboBox_Plus1(Units_Scroller, Units_SelectionSound);
	Units_AttackMode = new TextCtrl_Short(Units_Scroller);
	Units_AttackMode->SetToolTip("This may be attack mode\n0 No attacck\n1 Attack by following\n2 Run when attacked\n3 ?\n4 Attack\n");
	Units_AttackSound = new TextCtrl_Short(Units_Scroller);
	Units_ComboBox_AttackSound = new ComboBox_Plus1(Units_Scroller, Units_AttackSound);
	Units_MoveSound = new TextCtrl_Short(Units_Scroller);
	Units_ComboBox_MoveSound = new ComboBox_Plus1(Units_Scroller, Units_MoveSound);
	Units_DyingSound = new TextCtrl_Short(Units_Scroller);
	Units_ComboBox_DyingSound = new ComboBox_Plus1(Units_Scroller, Units_DyingSound);

	Units_HPBarHeight1 = new TextCtrl_Float(Units_Scroller);
	Units_HPBarHeight1->SetToolTip("Setting \"Air Mode\" to 1 and this to 0 causes farms to be walkable in AoE/RoR");
	Units_HPBarHeight2 = new TextCtrl_Float(Units_Scroller);
	Units_HPBarHeight2->SetToolTip("Vertical distance from ground");

	Units_Unknown1 = new TextCtrl_Short(Units_Scroller);
	for(short loop = 0; loop < Units_Unknown3.size(); loop++)
	Units_Unknown3[loop] = new TextCtrl_Byte(Units_Scroller);
	Units_Unknown6 = new TextCtrl_Byte(Units_Scroller);
	Units_Unknown6->SetToolTip("Seems to be 1 on all resource deposits");
	Units_Unknown7 = new TextCtrl_Byte(Units_Scroller);
	Units_Unknown7->SetToolTip("Setting to 5 can give a building a round outline,\neven if Selection Shape is set to 0 (square outline)\n0 farm, gate, dead bodies, town center\n2 buildings, gold mine\n3 berserk, flag x\n5 units\n10 mountain(matches selction mask)");
	Units_Unknown8 = new TextCtrl_Byte(Units_Scroller);
	Units_Unknown9 = new TextCtrl_Short(Units_Scroller);

	Units_Unknown11 = new TextCtrl_Byte(Units_Scroller);
	Units_Unknown12 = new TextCtrl_Float(Units_Scroller);
	Units_Unknown16 = new TextCtrl_Byte(Units_Scroller);
	for(short loop = 0; loop < Units_Unknown16B.size(); loop++)
	Units_Unknown16B[loop] = new TextCtrl_Byte(Units_Scroller);

	for(short loop = 0; loop < 2; loop++)
	{
		Units_Unknown20[loop] = new TextCtrl_Byte(Units_Scroller);
		Units_Unknown20[loop]->SetToolTip("These may be one variable in AoK and above (-24 & 3 = 1000)");
	}
	Units_Unknown21 = new TextCtrl_Short(Units_Scroller);
	Units_Unknown21->SetToolTip("-1 Unit\n4 Building\n6 Dock\n10 Wall");

	Units_Unknown26 = new TextCtrl_Long(Units_Scroller);
	Units_Unknown27 = new TextCtrl_Long(Units_Scroller);
	Units_Unknown29 = new TextCtrl_Byte(Units_Scroller);
	Units_Unknown29->SetToolTip("0 Default\n3 Unit must walk to enemy when ordered to attack it");

	Units_Unknown31 = new TextCtrl_Byte(Units_Scroller);
	Units_Unknown31->SetToolTip("0 Default\n1+ Black icon");
	Units_Unknown31b = new TextCtrl_Byte(Units_Scroller);
	Units_Unknown31b->SetToolTip("If a building is walkable underneath it?\n0 Default\n1 Makes the building disappear? some gates, town centers, docks\nSW: also some shield generators, power cores");
	Units_CheckBox_Unknown31b = new CheckBox_2State(Units_Scroller, "Yes *", Units_Unknown31b);
	Units_Unknown32 = new TextCtrl_Short(Units_Scroller);
	Units_Unknown33 = new TextCtrl_Byte(Units_Scroller);
	Units_Unknown34 = new TextCtrl_Short(Units_Scroller);
	Units_Unknown35 = new TextCtrl_Long(Units_Scroller);

	Units_CommandHolder_Lists = new wxBoxSizer(wxVERTICAL);
	Units_UnitHeads_Name = new wxStaticText(Units_Scroller, wxID_ANY, "Unit Header", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_UnitCommands = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Commands");
	Units_UnitCommands_Search = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_UnitCommands_Search_R = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_UnitCommands_List = new wxListBox(Units_Scroller, wxID_ANY, wxDefaultPosition, wxSize(10, 190), 0, NULL, wxLB_EXTENDED);
	Units_UnitCommands_Buttons = new wxGridSizer(3, 0, 0);
	Units_UnitCommands_Add = new wxButton(Units_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Units_UnitCommands_Insert = new wxButton(Units_Scroller, wxID_ANY, "Insert", wxDefaultPosition, wxSize(5, 20));
	Units_UnitCommands_Delete = new wxButton(Units_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Units_UnitCommands_Copy = new wxButton(Units_Scroller, wxID_ANY, "Copy *", wxDefaultPosition, wxSize(5, 20));
	Units_UnitCommands_Copy->SetToolTip("When \"All civs\" is not selected,\nthis and pasting works only for current civilization");
	Units_UnitCommands_Paste = new wxButton(Units_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Units_UnitCommands_PasteInsert = new wxButton(Units_Scroller, wxID_ANY, "PasteInsert", wxDefaultPosition, wxSize(5, 20));
	Units_UnitCommands_CopyToUnits = new wxButton(Units_Scroller, wxID_ANY, "Copy all to selected units", wxDefaultPosition, wxSize(5, 20));
	Units_CommandHolder_Data = new wxBoxSizer(wxVERTICAL);
	Units_CommandHolder_Data1 = new wxBoxSizer(wxHORIZONTAL);
	Units_CommandHolder_Data2 = new wxBoxSizer(wxVERTICAL);
	Units_CommandHolder_Grid1 = new wxGridSizer(2, 5, 5);
	Units_CommandHolder_Grid2 = new wxGridSizer(2, 5, 5);
	Units_CommandHolder_Grid3 = new wxGridSizer(1, 5, 5);
	Units_Exists = new TextCtrl_Byte(Units_Scroller);

	UnitCommands_Holder_1 = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_Holder_One = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_Text_One = new wxStaticText(Units_Scroller, wxID_ANY, "One ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_One = new TextCtrl_Short(Units_Scroller);
	UnitCommands_Holder_ID = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_Text_ID = new wxStaticText(Units_Scroller, wxID_ANY, "ID ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_ID = new TextCtrl_Short(Units_Scroller);
	UnitCommands_Holder_Type = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Text_Type = new wxStaticText(Units_Scroller, wxID_ANY, " Type", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Type = new TextCtrl_Short(Units_Scroller);
	UnitCommands_ComboBox_Type = new wxOwnerDrawnComboBox(Units_Scroller, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	UnitCommands_Holder_ClassID = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Text_ClassID = new wxStaticText(Units_Scroller, wxID_ANY, " Class", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_ClassID = new TextCtrl_Short(Units_Scroller);
	Units_ComboBox_Class[1] = new ComboBox_Plus1(Units_Scroller, UnitCommands_ClassID);
	UnitCommands_Holder_UnitID = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Text_UnitID = new wxStaticText(Units_Scroller, wxID_ANY, " Unit", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_UnitID = new TextCtrl_Short(Units_Scroller);
	UnitCommands_ComboBox_UnitID = new ComboBox_Plus1(Units_Scroller, UnitCommands_UnitID);
	UnitCommands_Holder_Unknown2 = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Text_Unknown2 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown2 = new TextCtrl_Short(Units_Scroller);
	UnitCommands_Holder_ResourceIn = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Text_ResourceIn = new wxStaticText(Units_Scroller, wxID_ANY, " Resource In", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_ResourceIn = new TextCtrl_Short(Units_Scroller);
	UnitCommands_ComboBox_ResourceIn = new ComboBox_Plus1(Units_Scroller, UnitCommands_ResourceIn);
	UnitCommands_Holder_SubType = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Text_SubType = new wxStaticText(Units_Scroller, wxID_ANY, " Productivity Resource *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_SubType = new TextCtrl_Short(Units_Scroller);
	UnitCommands_SubType->SetToolTip("Resource that multiplies the amount you can gather");
	UnitCommands_ComboBox_SubType = new ComboBox_Plus1(Units_Scroller, UnitCommands_SubType);
	UnitCommands_Holder_ResourceOut = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Text_ResourceOut = new wxStaticText(Units_Scroller, wxID_ANY, " Resource Out", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_ResourceOut = new TextCtrl_Short(Units_Scroller);
	UnitCommands_ComboBox_ResourceOut = new ComboBox_Plus1(Units_Scroller, UnitCommands_ResourceOut);
	UnitCommands_Holder_Unknown3 = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Text_Unknown3 = new wxStaticText(Units_Scroller, wxID_ANY, " Resource", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown3 = new TextCtrl_Short(Units_Scroller);
	UnitCommands_ComboBox_Unknown3 = new ComboBox_Plus1(Units_Scroller, UnitCommands_Unknown3);
	UnitCommands_Holder_WorkRateMultiplier = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Text_WorkRateMultiplier = new wxStaticText(Units_Scroller, wxID_ANY, " Work Rate Multiplier", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_WorkRateMultiplier = new TextCtrl_Float(Units_Scroller);
	UnitCommands_Holder_ExecutionRadius = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Text_ExecutionRadius = new wxStaticText(Units_Scroller, wxID_ANY, " Execution Radius", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_ExecutionRadius = new TextCtrl_Float(Units_Scroller);
	UnitCommands_Holder_ExtraRange = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Text_ExtraRange = new wxStaticText(Units_Scroller, wxID_ANY, " Extra Range", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_ExtraRange = new TextCtrl_Float(Units_Scroller);
	UnitCommands_Grid_Graphics = new wxGridSizer(3, 5, 5);
	for(short loop = 0; loop < UnitCommands_Graphics.size(); loop++)
	{
		UnitCommands_Holder_Graphics[loop] = new wxBoxSizer(wxVERTICAL);
		UnitCommands_Graphics[loop] = new TextCtrl_Short(Units_Scroller);
		UnitCommands_ComboBox_Graphics[loop] = new ComboBox_Plus1(Units_Scroller, UnitCommands_Graphics[loop]);
	}
	UnitCommands_Text_Graphics[0] = new wxStaticText(Units_Scroller, wxID_ANY, " Tool Graphic *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Graphics[0]->SetToolTip("Used when walking with a tool, but carrying no resources");
	UnitCommands_Text_Graphics[1] = new wxStaticText(Units_Scroller, wxID_ANY, " Proceeding Graphic *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Graphics[1]->SetToolTip("Used when proceeding to gather a resource or attack");
	UnitCommands_Text_Graphics[2] = new wxStaticText(Units_Scroller, wxID_ANY, " Action Graphic *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Graphics[2]->SetToolTip("Used when actually gathering a resource or attacking/converting");
	UnitCommands_Text_Graphics[3] = new wxStaticText(Units_Scroller, wxID_ANY, " Carrying Graphic *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Graphics[3]->SetToolTip("Used when carrying a resource");
	UnitCommands_Text_Graphics[4] = new wxStaticText(Units_Scroller, wxID_ANY, " Execution Sound *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Graphics[4]->SetToolTip("Example: Plays when lumberjack starts chopping wood");
	UnitCommands_Text_Graphics[5] = new wxStaticText(Units_Scroller, wxID_ANY, " Resource Deposit Sound *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Graphics[5]->SetToolTip("Example: Plays when lumberjack drops his wood into TC");
	UnitCommands_Holder_Unknown1 = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Text_Unknown1 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown1 = new TextCtrl_Byte(Units_Scroller);
	UnitCommands_Holder_Unknown4 = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Text_Unknown4 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 4", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown4 = new TextCtrl_Byte(Units_Scroller);
	UnitCommands_Holder_Unknown5 = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Text_Unknown5 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 5", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown5 = new TextCtrl_Float(Units_Scroller);
	UnitCommands_Holder_Unknown6 = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Text_Unknown6 = new wxStaticText(Units_Scroller, wxID_ANY, " Selection Enabler *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown6 = new TextCtrl_Byte(Units_Scroller);
	UnitCommands_Unknown6->SetToolTip("1 Allows units to select their targets\n2 ?");
	UnitCommands_Holder_Unknown7 = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Text_Unknown7 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 7", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown7 = new TextCtrl_Byte(Units_Scroller);
	UnitCommands_Holder_Unknown8 = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Text_Unknown8 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 8", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown8 = new TextCtrl_Long(Units_Scroller);
	UnitCommands_Holder_Unknown9 = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Text_Unknown9 = new wxStaticText(Units_Scroller, wxID_ANY, " Selection Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown9 = new TextCtrl_Byte(Units_Scroller);
	UnitCommands_Unknown9->SetToolTip("Determines what you can select as targets\n0, 7+ All objects\n1 Your objects only\n2 Neutral and enemy objects only\n3 Nothing\n4 Gaia, your and ally objects only\n5 Gaia, neutral and enemy objects only\n6 All but your objects");
	UnitCommands_Holder_Unknown10 = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Text_Unknown10 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 10", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown10 = new TextCtrl_Byte(Units_Scroller);
	UnitCommands_Holder_Unknown11 = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Text_Unknown11 = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 11", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown11 = new TextCtrl_Byte(Units_Scroller);

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

	Units_SpecialCopy_Options->Append("Special: graphics only");
	Units_SpecialCopy_Options->SetSelection(0);

	Units_Units_Buttons[0]->Add(Units_Add, 1, wxEXPAND);
	Units_Units_Buttons[0]->Add(Units_Insert, 1, wxEXPAND);
	Units_Units_Buttons[0]->Add(Units_Delete, 1, wxEXPAND);
	Units_Units_Buttons[0]->Add(Units_Copy, 1, wxEXPAND);
	Units_Units_Buttons[0]->Add(Units_Paste, 1, wxEXPAND);
	Units_Units_Buttons[0]->Add(Units_PasteInsert, 1, wxEXPAND);
	//Units_Units_Buttons[0]->Add(Units_Extract, 1, wxEXPAND);
	//Units_Units_Buttons[0]->Add(Units_Import, 1, wxEXPAND);
	Units_Units_Buttons[0]->Add(Units_Info, 1, wxEXPAND);
	Units_Units_Buttons[1]->Add(Units_SpecialCopy, 1, wxEXPAND);
	Units_Units_Buttons[1]->Add(Units_SpecialPaste, 1, wxEXPAND);
	Units_Units_Buttons[1]->Add(Units_Enable, 1, wxEXPAND);
	Units_Units_Buttons[1]->Add(Units_Disable, 1, wxEXPAND);
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
	for(short loop = 0; loop < 2; loop++)
	Units_Units->Add(Units_Units_Searches[loop], 0, wxEXPAND);
	for(short loop = 0; loop < 2; loop++)
	Units_Units->Add(Units_Units_SearchFilters[loop], 0, wxEXPAND);
	Units_Units->Add(-1, 2);
	Units_Units->Add(Units_Units_List, 1, wxEXPAND);
	Units_Units->Add(-1, 2);
	Units_Units->Add(Units_Units_Buttons[0], 0, wxEXPAND);
	//Units_Units->Add(Units_Units_Line, 0, wxEXPAND);
	Units_Units->Add(Units_Units_Buttons[1], 0, wxEXPAND);
	Units_Units->Add(-1, 2);
	Units_Units->Add(Units_Units_Special, 0, wxEXPAND);

	Units_ListArea->Add(-1, 10);
	Units_ListArea->Add(Units_Units, 1, wxEXPAND);
	Units_ListArea->Add(-1, 10);

	Units_Holder_Type->Add(Units_Text_Type, 0, wxEXPAND);
	Units_Holder_Type->Add(Units_Type, 1, wxEXPAND);
	Units_Holder_Type->Add(Units_ComboBox_Type, 2, wxEXPAND);
	Units_Holder_Type->AddStretchSpacer(4);

//	Type 10+

	Units_Holder_ID1->Add(Units_Text_ID1, 0, wxEXPAND);
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
	Units_Holder_AttackMode->Add(Units_Text_AttackMode, 0, wxEXPAND);
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
	Units_Holder_Unknown16B->Add(Units_Text_Unknown16B, 0, wxEXPAND);

//	Type 40+

	Units_Holder_SearchRadius->Add(Units_Text_SearchRadius, 0, wxEXPAND);
	Units_Holder_WorkRate->Add(Units_Text_WorkRate, 0, wxEXPAND);
	Units_Holder_AttributesDropSite->Add(Units_Text_DropSite, 0, wxEXPAND);
	Units_Holder_VillagerMode->Add(Units_Text_VillagerMode, 0, wxEXPAND);
	Units_Holder_AttackSound->Add(Units_Text_AttackSound, 0, wxEXPAND);
	Units_Holder_MoveSound->Add(Units_Text_MoveSound, 0, wxEXPAND);
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
	Units_Holder_AlfaThingy->Add(Units_Text_AlfaThingy, 0, wxEXPAND);

//	Type 10+

	Units_Holder_ID1->Add(Units_ID1, 1, wxEXPAND);
	Units_Holder_Class->Add(Units_Class, 1, wxEXPAND);
	Units_Holder_Class->Add(Units_ComboBox_Class[0], 2, wxEXPAND);
	Units_Holder_DeathMode->Add(Units_DeathMode, 1, wxEXPAND);
	Units_Holder_DeathMode->Add(2, -1);
	Units_Holder_DeathMode->Add(Units_CheckBox_DeathMode, 2, wxEXPAND);
	Units_Holder_HitPoints->Add(Units_HitPoints, 1, wxEXPAND);
	Units_Holder_LineOfSight->Add(Units_LineOfSight, 1, wxEXPAND);
	Units_Holder_GarrisonCapacity->Add(Units_GarrisonCapacity, 0, wxEXPAND);
	for(short loop = 0; loop < 2; loop++)
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
	for(short loop = 0; loop < 2; loop++)
	Units_Holder_PlacementBypassTerrainGrid->Add(Units_PlacementBypassTerrain[loop], 1, wxEXPAND);
	for(short loop = 0; loop < 2; loop++)
	Units_Holder_PlacementBypassTerrainGrid->Add(Units_ComboBox_PlacementBypassTerrain[loop], 1, wxEXPAND);
	Units_Holder_PlacementBypassTerrain->Add(Units_Holder_PlacementBypassTerrainGrid, 0, wxEXPAND);
	for(short loop = 0; loop < 2; loop++)
	Units_Holder_PlacementTerrainGrid->Add(Units_PlacementTerrain[loop], 1, wxEXPAND);
	for(short loop = 0; loop < 2; loop++)
	Units_Holder_PlacementTerrainGrid->Add(Units_ComboBox_PlacementTerrain[loop], 1, wxEXPAND);
	Units_Holder_PlacementTerrain->Add(Units_Holder_PlacementTerrainGrid, 0, wxEXPAND);
	for(short loop = 0; loop < 2; loop++)
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
	for(short loop = 0; loop < Units_Unknown3.size(); loop++)
	Units_Grid_Unknown3->Add(Units_Unknown3[loop], 1, wxEXPAND);
	Units_Holder_Unknown3->Add(Units_Grid_Unknown3, 0, wxEXPAND);
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
	Units_Holder_Unknown9->Add(Units_Unknown9, 0, wxEXPAND);
	Units_Holder_SelectionEffect->Add(Units_SelectionEffect, 0, wxEXPAND);
	Units_Holder_EditorSelectionColour->Add(Units_EditorSelectionColour, 0, wxEXPAND);
	for(short loop = 0; loop < 2; loop++)
	Units_SelectionRadiusBox->Add(Units_SelectionRadius[loop], 1, wxEXPAND);
	Units_Holder_SelectionRadius->Add(Units_SelectionRadiusBox, 1, wxEXPAND);
	Units_Holder_HPBarHeight2->Add(Units_HPBarHeight2, 1, wxEXPAND);
	Units_Holder_SelectionSound->Add(Units_SelectionSound, 1, wxEXPAND);
	Units_Holder_SelectionSound->Add(Units_ComboBox_SelectionSound, 1, wxEXPAND);
	Units_Holder_DyingSound->Add(Units_DyingSound, 1, wxEXPAND);
	Units_Holder_DyingSound->Add(Units_ComboBox_DyingSound, 1, wxEXPAND);
	Units_Holder_AttackMode->Add(Units_AttackMode, 0, wxEXPAND);
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
	Units_Holder_Unknown16->Add(Units_Unknown16, 0, wxEXPAND);
	for(short loop = 0; loop < Units_Unknown16B.size(); loop++)
	Units_Grid_Unknown16B->Add(Units_Unknown16B[loop], 1, wxEXPAND);
	Units_Holder_Unknown16B->Add(Units_Grid_Unknown16B, 0, wxEXPAND);

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
	Units_Holder_AttackSound->Add(Units_AttackSound, 1, wxEXPAND);
	Units_Holder_AttackSound->Add(Units_ComboBox_AttackSound, 1, wxEXPAND);
	Units_Holder_MoveSound->Add(Units_MoveSound, 1, wxEXPAND);
	Units_Holder_MoveSound->Add(Units_ComboBox_MoveSound, 1, wxEXPAND);
	Units_Holder_AnimalMode->Add(Units_AnimalMode, 1, wxEXPAND);
	Units_Holder_AnimalMode->Add(2, -1);
	Units_Holder_AnimalMode->Add(Units_CheckBox_AnimalMode, 2, wxEXPAND);
	Units_Holder_Exists->Add(Units_Exists, 1, wxEXPAND);

//	Type 60+

	for(short loop = 0; loop < 2; loop++)
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
	for(short loop = 0; loop < 3; loop++)
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

	for(short loop = 0; loop < 3; loop++)
	Units_Grid_CostType->Add(Units_CostType[loop], 1, wxEXPAND);
	for(short loop = 0; loop < 3; loop++)
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
	Units_Holder_Unknown27->Add(Units_Unknown27, 1, wxEXPAND);
	Units_Holder_MissileGraphicDelay->Add(Units_MissileGraphicDelay, 1, wxEXPAND);
	Units_Holder_HeroMode->Add(Units_HeroMode, 1, wxEXPAND);
	Units_Holder_HeroMode->Add(2, -1);
	Units_Holder_HeroMode->Add(Units_CheckBox_HeroMode, 2, wxEXPAND);
	Units_Holder_AttackMissileDuplicationAmount1->Add(Units_AttackMissileDuplicationAmount1, 1, wxEXPAND);
	Units_Holder_AttackMissileDuplicationAmount2->Add(Units_AttackMissileDuplicationAmount2, 1, wxEXPAND);
	for(short loop = 0; loop < 3; loop++)
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
	for(short loop = 0; loop < 4; loop++)
	Units_Grid_AnnexUnit->Add(Units_AnnexUnit[loop], 1, wxEXPAND);
	for(short loop = 0; loop < 4; loop++)
	Units_Grid_AnnexUnit->Add(Units_ComboBox_AnnexUnit[loop], 1, wxEXPAND);
	Units_Holder_AnnexUnit1->Add(Units_Grid_AnnexUnit, 0, wxEXPAND);
	for(short loop = 0; loop < 4; loop++)
	Units_Grid_AnnexUnitMisplacement->Add(Units_AnnexUnitMisplacement[loop][0], 1, wxEXPAND);
	for(short loop = 0; loop < 4; loop++)
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
	for(short loop = 0; loop < Units_AlfaThingy.size(); loop += 2)
	Units_Grid_AlfaThingy->Add(Units_AlfaThingy[loop], 1, wxEXPAND);
	for(short loop = 1; loop < Units_AlfaThingy.size(); loop += 2)
	Units_Grid_AlfaThingy->Add(Units_AlfaThingy[loop], 1, wxEXPAND);
	Units_Holder_AlfaThingy->Add(Units_Grid_AlfaThingy, 0, wxEXPAND);

	for(short loop = 0; loop < 3; loop++)
	Units_Grid_ResourceStorage->Add(ResourceStorage_Type[loop], 1, wxEXPAND);
	for(short loop = 0; loop < 3; loop++)
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

	Attacks_Holder_Class->Add(Attacks_Text_Class, 0, wxEXPAND);
	Attacks_Holder_Class->Add(Attacks_Class, 1, wxEXPAND);
	Attacks_Holder_Class->Add(Attacks_ComboBox_Class[0], 1, wxEXPAND);
	Attacks_Holder_Amount->Add(Attacks_Text_Amount, 0, wxEXPAND);
	Attacks_Holder_Amount->Add(Attacks_Amount, 1, wxEXPAND);

	Units_Attacks_Buttons->Add(Units_Attacks_Add, 1, wxEXPAND);
	Units_Attacks_Buttons->Add(Units_Attacks_Insert, 1, wxEXPAND);
	Units_Attacks_Buttons->Add(Units_Attacks_Delete, 1, wxEXPAND);
	Units_Attacks_Buttons->Add(Units_Attacks_Copy, 1, wxEXPAND);
	Units_Attacks_Buttons->Add(Units_Attacks_Paste, 1, wxEXPAND);
	Units_Attacks_Buttons->Add(Units_Attacks_PasteInsert, 1, wxEXPAND);

	Units_Attacks_ListArea->Add(Units_Attacks_Search, 0, wxEXPAND);
	Units_Attacks_ListArea->Add(Units_Attacks_Search_R, 0, wxEXPAND);
	Units_Attacks_ListArea->Add(-1, 2);
	Units_Attacks_ListArea->Add(Units_Attacks_List, 1, wxEXPAND);
	Units_Attacks_ListArea->Add(-1, 2);
	Units_Attacks_ListArea->Add(Units_Attacks_Buttons, 0, wxEXPAND);
	Units_Attacks_ListArea->Add(-1, 2);
	Units_Attacks_ListArea->Add(Units_Attacks_CopyToUnits, 0, wxEXPAND);

	Armors_Holder_Class->Add(Armors_Text_Class, 0, wxEXPAND);
	Armors_Holder_Class->Add(Armors_Class, 1, wxEXPAND);
	Armors_Holder_Class->Add(Attacks_ComboBox_Class[1], 1, wxEXPAND);
	Armors_Holder_Amount->Add(Armors_Text_Amount, 0, wxEXPAND);
	Armors_Holder_Amount->Add(Armors_Amount, 1, wxEXPAND);

	Units_Armors_Buttons->Add(Units_Armors_Add, 1, wxEXPAND);
	Units_Armors_Buttons->Add(Units_Armors_Insert, 1, wxEXPAND);
	Units_Armors_Buttons->Add(Units_Armors_Delete, 1, wxEXPAND);
	Units_Armors_Buttons->Add(Units_Armors_Copy, 1, wxEXPAND);
	Units_Armors_Buttons->Add(Units_Armors_Paste, 1, wxEXPAND);
	Units_Armors_Buttons->Add(Units_Armors_PasteInsert, 1, wxEXPAND);

	Units_Armors_ListArea->Add(Units_Armors_Search, 0, wxEXPAND);
	Units_Armors_ListArea->Add(Units_Armors_Search_R, 0, wxEXPAND);
	Units_Armors_ListArea->Add(-1, 2);
	Units_Armors_ListArea->Add(Units_Armors_List, 1, wxEXPAND);
	Units_Armors_ListArea->Add(-1, 2);
	Units_Armors_ListArea->Add(Units_Armors_Buttons, 0, wxEXPAND);
	Units_Armors_ListArea->Add(-1, 2);
	Units_Armors_ListArea->Add(Units_Armors_CopyToUnits, 0, wxEXPAND);

	UnitCommands_Holder_One->Add(UnitCommands_Text_One, 0, wxEXPAND);
	UnitCommands_Holder_One->Add(UnitCommands_One, 1, wxEXPAND);
	UnitCommands_Holder_ID->Add(UnitCommands_Text_ID, 0, wxEXPAND);
	UnitCommands_Holder_ID->Add(UnitCommands_ID, 1, wxEXPAND);
	UnitCommands_Holder_Unknown1->Add(UnitCommands_Text_Unknown1, 0, wxEXPAND);
	UnitCommands_Holder_Unknown1->Add(UnitCommands_Unknown1, 0, wxEXPAND);
	UnitCommands_Holder_Type->Add(UnitCommands_Text_Type, 0, wxEXPAND);
	UnitCommands_Holder_Type->Add(UnitCommands_Type, 0, wxEXPAND);
	UnitCommands_Holder_Type->Add(UnitCommands_ComboBox_Type, 0, wxEXPAND);
	UnitCommands_Holder_SubType->Add(UnitCommands_Text_SubType, 0, wxEXPAND);
	UnitCommands_Holder_SubType->Add(UnitCommands_SubType, 0, wxEXPAND);
	UnitCommands_Holder_SubType->Add(UnitCommands_ComboBox_SubType, 0, wxEXPAND);
	UnitCommands_Holder_ClassID->Add(UnitCommands_Text_ClassID, 0, wxEXPAND);
	UnitCommands_Holder_ClassID->Add(UnitCommands_ClassID, 0, wxEXPAND);
	UnitCommands_Holder_ClassID->Add(Units_ComboBox_Class[1], 0, wxEXPAND);
	UnitCommands_Holder_UnitID->Add(UnitCommands_Text_UnitID, 0, wxEXPAND);
	UnitCommands_Holder_UnitID->Add(UnitCommands_UnitID, 0, wxEXPAND);
	UnitCommands_Holder_UnitID->Add(UnitCommands_ComboBox_UnitID, 0, wxEXPAND);
	UnitCommands_Holder_Unknown2->Add(UnitCommands_Text_Unknown2, 0, wxEXPAND);
	UnitCommands_Holder_Unknown2->Add(UnitCommands_Unknown2, 0, wxEXPAND);
	UnitCommands_Holder_ResourceIn->Add(UnitCommands_Text_ResourceIn, 0, wxEXPAND);
	UnitCommands_Holder_ResourceIn->Add(UnitCommands_ResourceIn, 0, wxEXPAND);
	UnitCommands_Holder_ResourceIn->Add(UnitCommands_ComboBox_ResourceIn, 0, wxEXPAND);
	UnitCommands_Holder_ResourceOut->Add(UnitCommands_Text_ResourceOut, 0, wxEXPAND);
	UnitCommands_Holder_ResourceOut->Add(UnitCommands_ResourceOut, 0, wxEXPAND);
	UnitCommands_Holder_ResourceOut->Add(UnitCommands_ComboBox_ResourceOut, 0, wxEXPAND);
	UnitCommands_Holder_Unknown3->Add(UnitCommands_Text_Unknown3, 0, wxEXPAND);
	UnitCommands_Holder_Unknown3->Add(UnitCommands_Unknown3, 0, wxEXPAND);
	UnitCommands_Holder_Unknown3->Add(UnitCommands_ComboBox_Unknown3, 0, wxEXPAND);
	UnitCommands_Holder_WorkRateMultiplier->Add(UnitCommands_Text_WorkRateMultiplier, 0, wxEXPAND);
	UnitCommands_Holder_WorkRateMultiplier->Add(UnitCommands_WorkRateMultiplier, 0, wxEXPAND);
	UnitCommands_Holder_ExecutionRadius->Add(UnitCommands_Text_ExecutionRadius, 0, wxEXPAND);
	UnitCommands_Holder_ExecutionRadius->Add(UnitCommands_ExecutionRadius, 0, wxEXPAND);
	UnitCommands_Holder_ExtraRange->Add(UnitCommands_Text_ExtraRange, 0, wxEXPAND);
	UnitCommands_Holder_ExtraRange->Add(UnitCommands_ExtraRange, 0, wxEXPAND);
	UnitCommands_Holder_Unknown4->Add(UnitCommands_Text_Unknown4, 0, wxEXPAND);
	UnitCommands_Holder_Unknown4->Add(UnitCommands_Unknown4, 0, wxEXPAND);
	UnitCommands_Holder_Unknown5->Add(UnitCommands_Text_Unknown5, 0, wxEXPAND);
	UnitCommands_Holder_Unknown5->Add(UnitCommands_Unknown5, 0, wxEXPAND);
	UnitCommands_Holder_Unknown6->Add(UnitCommands_Text_Unknown6, 0, wxEXPAND);
	UnitCommands_Holder_Unknown6->Add(UnitCommands_Unknown6, 0, wxEXPAND);
	UnitCommands_Holder_Unknown7->Add(UnitCommands_Text_Unknown7, 0, wxEXPAND);
	UnitCommands_Holder_Unknown7->Add(UnitCommands_Unknown7, 0, wxEXPAND);
	UnitCommands_Holder_Unknown8->Add(UnitCommands_Text_Unknown8, 0, wxEXPAND);
	UnitCommands_Holder_Unknown8->Add(UnitCommands_Unknown8, 0, wxEXPAND);
	UnitCommands_Holder_Unknown9->Add(UnitCommands_Text_Unknown9, 0, wxEXPAND);
	UnitCommands_Holder_Unknown9->Add(UnitCommands_Unknown9, 0, wxEXPAND);
	UnitCommands_Holder_Unknown10->Add(UnitCommands_Text_Unknown10, 0, wxEXPAND);
	UnitCommands_Holder_Unknown10->Add(UnitCommands_Unknown10, 0, wxEXPAND);
	UnitCommands_Holder_Unknown11->Add(UnitCommands_Text_Unknown11, 0, wxEXPAND);
	UnitCommands_Holder_Unknown11->Add(UnitCommands_Unknown11, 0, wxEXPAND);

	for(short loop = 0; loop < UnitCommands_Graphics.size(); loop++)
	{
		UnitCommands_Holder_Graphics[loop]->Add(UnitCommands_Text_Graphics[loop], 0, wxEXPAND);
		UnitCommands_Holder_Graphics[loop]->Add(UnitCommands_Graphics[loop], 0, wxEXPAND);
		UnitCommands_Holder_Graphics[loop]->Add(UnitCommands_ComboBox_Graphics[loop], 0, wxEXPAND);
		UnitCommands_Grid_Graphics->Add(UnitCommands_Holder_Graphics[loop], 1, wxEXPAND);
	}

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

	Units_Holder_LanguageDLLName->Add(Units_Text_LanguageDLLName, 0, wxEXPAND);
	Units_Holder_LanguageDLLName->Add(Units_LanguageDLLName, 1, wxEXPAND);
	Units_Holder_LanguageDLLName->Add(Units_DLL_LanguageName, 1, wxEXPAND);
	Units_Holder_LanguageDLLCreation->Add(Units_Text_LanguageDLLCreation, 0, wxEXPAND);
	Units_Holder_LanguageDLLCreation->Add(Units_LanguageDLLCreation, 1, wxEXPAND);
	Units_Holder_LanguageDLLCreation->Add(Units_DLL_LanguageCreation, 1, wxEXPAND);
	Units_Holder_LanguageDLLHelp->Add(Units_Text_LanguageDLLHelp, 0, wxEXPAND);
	Units_Holder_LanguageDLLHelp->Add(Units_LanguageDLLHelp, 1, wxEXPAND);
	Units_Holder_LanguageDLLConverter[0]->Add(Units_Text_LanguageDLLConverter[0], 0, wxEXPAND);
	Units_Holder_LanguageDLLConverter[0]->Add(Units_LanguageDLLConverter[0], 1, wxEXPAND);
	Units_Holder_LanguageDLLHotKeyText->Add(Units_Text_LanguageDLLHotKeyText, 0, wxEXPAND);
	Units_Holder_LanguageDLLHotKeyText->Add(Units_LanguageDLLHotKeyText, 1, wxEXPAND);
	Units_Holder_LanguageDLLConverter[1]->Add(Units_Text_LanguageDLLConverter[1], 0, wxEXPAND);
	Units_Holder_LanguageDLLConverter[1]->Add(Units_LanguageDLLConverter[1], 1, wxEXPAND);
	Units_Holder_HotKey->Add(Units_Text_HotKey, 0, wxEXPAND);
	Units_Holder_HotKey->Add(Units_HotKey, 1, wxEXPAND);
	Units_Holder_HotKey->Add(Units_DLL_HotKey4, 1, wxEXPAND);

	Units_Holder_LangRegular->Add(Units_Holder_LanguageDLLName, 1, wxEXPAND);
	Units_Holder_LangRegular->Add(5, -1);
	Units_Holder_LangRegular->Add(Units_Holder_LanguageDLLCreation, 1, wxEXPAND);
	Units_Holder_LangRegular->Add(5, -1);
	Units_Holder_LangRegular->Add(Units_Holder_HotKey, 1, wxEXPAND);
	Units_Holder_LangHotKey->Add(Units_Holder_LanguageDLLHelp, 1, wxEXPAND);
	Units_Holder_LangHotKey->Add(5, -1);
	Units_Holder_LangHotKey->Add(Units_Holder_LanguageDLLConverter[0], 1, wxEXPAND);
	Units_Holder_LangHotKey->Add(5, -1);
	Units_Holder_LangHotKey->Add(Units_Holder_LanguageDLLHotKeyText, 1, wxEXPAND);
	Units_Holder_LangHotKey->Add(5, -1);
	Units_Holder_LangHotKey->Add(Units_Holder_LanguageDLLConverter[1], 1, wxEXPAND);

	Units_Holder_LangDLLArea->Add(Units_Holder_LangRegular, 0, wxEXPAND);
	Units_Holder_LangDLLArea->Add(-1, 5);
	Units_Holder_LangDLLArea->Add(Units_Holder_LangHotKey, 0, wxEXPAND);
	Units_Holder_LangDLLArea->Add(-1, 5);
	Units_Holder_LangDLLArea->Add(Units_DLL_LanguageHelp, 0, wxEXPAND);
	Units_Holder_LangDLLArea->Add(Units_DLL_LanguageHKText, 0, wxEXPAND);

	Units_Grid_StandingGraphic->Add(Units_StandingGraphic[0], 1, wxEXPAND);
	Units_Grid_StandingGraphic->Add(Units_StandingGraphic[1], 1, wxEXPAND);
	Units_Grid_StandingGraphic->Add(Units_ComboBox_StandingGraphic[0], 1, wxEXPAND);
	Units_Grid_StandingGraphic->Add(Units_ComboBox_StandingGraphic[1], 1, wxEXPAND);
	Units_Holder_StandingGraphic->Add(Units_Text_StandingGraphic, 0, wxEXPAND);
	Units_Holder_StandingGraphic->Add(Units_Grid_StandingGraphic, 0, wxEXPAND);
	Units_Grid_GarrisonGraphic->Add(Units_GarrisonGraphic[0], 1, wxEXPAND);
	Units_Grid_GarrisonGraphic->Add(Units_GarrisonGraphic[1], 1, wxEXPAND);
	Units_Grid_GarrisonGraphic->Add(Units_ComboBox_GarrisonGraphic[0], 1, wxEXPAND);
	Units_Grid_GarrisonGraphic->Add(Units_ComboBox_GarrisonGraphic[1], 1, wxEXPAND);
	Units_Holder_GarrisonGraphic->Add(Units_Text_GarrisonGraphic, 0, wxEXPAND);
	Units_Holder_GarrisonGraphic->Add(Units_Grid_GarrisonGraphic, 0, wxEXPAND);
	Units_Grid_WalkingGraphic->Add(Units_WalkingGraphic[0], 1, wxEXPAND);
	Units_Grid_WalkingGraphic->Add(Units_WalkingGraphic[1], 1, wxEXPAND);
	Units_Grid_WalkingGraphic->Add(Units_ComboBox_WalkingGraphic[0], 1, wxEXPAND);
	Units_Grid_WalkingGraphic->Add(Units_ComboBox_WalkingGraphic[1], 1, wxEXPAND);
	Units_Holder_WalkingGraphic->Add(Units_Text_WalkingGraphic, 0, wxEXPAND);
	Units_Holder_WalkingGraphic->Add(Units_Grid_WalkingGraphic, 0, wxEXPAND);
	Units_Grid_DyingGraphic->Add(Units_DyingGraphic[0], 1, wxEXPAND);
	Units_Grid_DyingGraphic->Add(Units_DyingGraphic[1], 1, wxEXPAND);
	Units_Grid_DyingGraphic->Add(Units_ComboBox_DyingGraphic[0], 1, wxEXPAND);
	Units_Grid_DyingGraphic->Add(Units_ComboBox_DyingGraphic[1], 1, wxEXPAND);
	Units_Holder_DyingGraphic->Add(Units_Text_DyingGraphic, 0, wxEXPAND);
	Units_Holder_DyingGraphic->Add(Units_Grid_DyingGraphic, 0, wxEXPAND);

	Units_Holder_GraphicsArea1->Add(Units_Holder_IconID, 1, wxEXPAND);
	Units_Holder_GraphicsArea1->Add(5, -1);
	Units_Holder_GraphicsArea1->Add(Units_Holder_ConstructionGraphicID, 1, wxEXPAND);
	Units_Holder_GraphicsArea1->Add(5, -1);
	Units_Holder_GraphicsArea1->Add(Units_Holder_SnowGraphicID, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Units_Holder_GraphicsArea1->Add(5, -1);
	Units_Holder_GraphicsArea1->Add(Units_Holder_AttackGraphic, 1, wxEXPAND);
	Units_Holder_GraphicsArea4->Add(Units_Holder_StandingGraphic, 1, wxEXPAND);
	Units_Holder_GraphicsArea4->Add(5, -1);
	Units_Holder_GraphicsArea4->Add(Units_Holder_GarrisonGraphic, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Units_Holder_GraphicsArea5->Add(Units_Holder_WalkingGraphic, 1, wxEXPAND);
	Units_Holder_GraphicsArea5->Add(5, -1);
	Units_Holder_GraphicsArea5->Add(Units_Holder_DyingGraphic, 1, wxEXPAND);

	DamageGraphics_Holder_GraphicID->Add(DamageGraphics_Text_GraphicID, 0, wxEXPAND);
	DamageGraphics_Holder_GraphicID->Add(DamageGraphics_GraphicID, 1, wxEXPAND);
	DamageGraphics_Holder_GraphicID->Add(DamageGraphics_ComboBox_GraphicID, 1, wxEXPAND);
	DamageGraphics_Holder_Unknown1->Add(DamageGraphics_Text_Unknown1, 0, wxEXPAND);
	DamageGraphics_Holder_Unknown1->Add(DamageGraphics_Unknown1, 1, wxEXPAND);
	DamageGraphics_Holder_DamagePercent->Add(DamageGraphics_Text_DamagePercent, 0, wxEXPAND);
	DamageGraphics_Holder_DamagePercent->Add(DamageGraphics_DamagePercent, 1, wxEXPAND);
	DamageGraphics_Holder_Unknown2->Add(DamageGraphics_Text_Unknown2, 0, wxEXPAND);
	DamageGraphics_Holder_Unknown2->Add(DamageGraphics_Unknown2, 1, wxEXPAND);
	Units_Holder_DamageGraphics_Data->Add(DamageGraphics_Holder_GraphicID, 0, wxEXPAND);
	Units_Holder_DamageGraphics_Data->Add(-1, 5);
	Units_Holder_DamageGraphics_Data->Add(DamageGraphics_Holder_DamagePercent, 0, wxEXPAND);
	Units_Holder_DamageGraphics_Data->Add(-1, 5);
	Units_Holder_DamageGraphics_Data->Add(DamageGraphics_Holder_Unknown1, 0, wxEXPAND);
	Units_Holder_DamageGraphics_Data->Add(-1, 5);
	Units_Holder_DamageGraphics_Data->Add(DamageGraphics_Holder_Unknown2, 0, wxEXPAND);

	Units_DamageGraphics_Buttons->Add(Units_DamageGraphics_Add, 1, wxEXPAND);
	Units_DamageGraphics_Buttons->Add(Units_DamageGraphics_Insert, 1, wxEXPAND);
	Units_DamageGraphics_Buttons->Add(Units_DamageGraphics_Delete, 1, wxEXPAND);
	Units_DamageGraphics_Buttons->Add(Units_DamageGraphics_Copy, 1, wxEXPAND);
	Units_DamageGraphics_Buttons->Add(Units_DamageGraphics_Paste, 1, wxEXPAND);
	Units_DamageGraphics_Buttons->Add(Units_DamageGraphics_PasteInsert, 1, wxEXPAND);

	Units_DamageGraphics_ListArea->Add(Units_DamageGraphics_Search, 0, wxEXPAND);
	Units_DamageGraphics_ListArea->Add(Units_DamageGraphics_Search_R, 0, wxEXPAND);
	Units_DamageGraphics_ListArea->Add(-1, 2);
	Units_DamageGraphics_ListArea->Add(Units_DamageGraphics_List, 1, wxEXPAND);
	Units_DamageGraphics_ListArea->Add(-1, 2);
	Units_DamageGraphics_ListArea->Add(Units_DamageGraphics_Buttons, 0, wxEXPAND);
	Units_DamageGraphics_ListArea->Add(-1, 2);
	Units_DamageGraphics_ListArea->Add(Units_DamageGraphics_CopyToUnits, 0, wxEXPAND);

	Units_DamageGraphics->Add(Units_DamageGraphics_ListArea, 1, wxEXPAND);
	Units_DamageGraphics->Add(5, -1);
	Units_DamageGraphics->Add(Units_Holder_DamageGraphics_Data, 1, wxEXPAND);
	Units_Holder_DamageGraphics->Add(Units_DamageGraphics, 1, wxEXPAND);

	Units_Holder_GraphicsArea->Add(Units_Holder_GraphicsArea1, 0, wxEXPAND);
	Units_Holder_GraphicsArea->Add(-1, 5);
	Units_Holder_GraphicsArea->Add(Units_Holder_GraphicsArea4, 0, wxEXPAND);
	Units_Holder_GraphicsArea->Add(-1, 5);
	Units_Holder_GraphicsArea->Add(Units_Holder_GraphicsArea5, 0, wxEXPAND);
	Units_Holder_GraphicsArea->Add(-1, 5);
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

	Units_Attacks_DataArea->Add(Attacks_Holder_Amount, 0, wxEXPAND);
	Units_Attacks_DataArea->Add(-1, 5);
	Units_Attacks_DataArea->Add(Attacks_Holder_Class, 0, wxEXPAND);
	Units_Grid_Attacks_Data2->Add(Units_Holder_DisplayedAttack, 1, wxEXPAND);
	Units_Grid_Attacks_Data2->Add(Units_Holder_Delay, 1, wxEXPAND);
	Units_Grid_Attacks_Data2->Add(Units_Holder_AccuracyPercent, 1, wxEXPAND);
	Units_Grid_Attacks_Data2->Add(Units_Holder_GarrisonRecoveryRate, 1, wxEXPAND);
	Units_Grid_Attacks_Data2->Add(Units_Holder_ReloadTime1, 1, wxEXPAND);
	Units_Grid_Attacks_Data2->Add(Units_Holder_ReloadTime2, 1, wxEXPAND);
	Units_Grid_Attacks_Data2->Add(Units_Holder_BlastRadius, 1, wxEXPAND);
	Units_Grid_Attacks_Data2->Add(Units_Holder_BlastLevel, 1, wxEXPAND);
	Units_Holder_Attacks_Data->Add(-1, 5);
	Units_Holder_Attacks_Data->Add(Units_Grid_Attacks_Data2, 0, wxEXPAND);

	Units_Armors_DataArea->Add(Armors_Holder_Amount, 0, wxEXPAND);
	Units_Armors_DataArea->Add(Armors_Holder_Class, 0, wxEXPAND);
	Units_Holder_Armors_Data3->Add(-1, 5);
	Units_Holder_Armors_Data3->Add(Units_Holder_DisplayedMeleeArmour, 0, wxEXPAND);
	Units_Holder_Armors_Data3->Add(-1, 5);
	Units_Holder_Armors_Data3->Add(Units_Holder_DisplayedPierceArmour, 0, wxEXPAND);

	Units_Holder_GarrisonType->Add(Units_Text_GarrisonType, 0, wxEXPAND);
	Units_Holder_GarrisonType->Add(Units_GarrisonType, 1, wxEXPAND);
	Units_Holder_GarrisonType->Add(Units_ComboBox_GarrisonType, 1, wxEXPAND);

	Units_Attacks->Add(Units_Attacks_ListArea, 1, wxEXPAND);
	Units_Attacks->Add(5, -1);
	Units_Attacks->Add(Units_Attacks_DataArea, 1, wxEXPAND);
	Units_Armors->Add(Units_Armors_ListArea, 1, wxEXPAND);
	Units_Armors->Add(5, -1);
	Units_Armors->Add(Units_Armors_DataArea, 1, wxEXPAND);
	Units_Holder_Attacks->Add(Units_Attacks, 1, wxEXPAND);
	Units_Holder_Attacks->Add(5, -1);
	Units_Holder_Attacks->Add(Units_Holder_Attacks_Data, 1, wxEXPAND);
	Units_Holder_Armors->Add(Units_Armors, 2, wxEXPAND);
	Units_Holder_Armors->Add(5, -1);
	Units_Holder_Armors->Add(Units_Holder_Armors_Data3, 1, wxEXPAND);
	Units_Holder_Armors->AddStretchSpacer(1);
	Units_Grid_StatsAreaGarrison->Add(Units_Holder_GarrisonCapacity, 1, wxEXPAND);
	Units_Grid_StatsAreaGarrison->Add(Units_Holder_GarrisonType, 2, wxEXPAND);
	Units_Grid_StatsAreaGarrison->Add(Units_Holder_GarrisonHealRate, 1, wxEXPAND);
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
	Units_Holder_Attributes->Add(Units_Grid_AttributesTracking, 0, wxEXPAND);
	Units_Holder_Attributes->Add(-1, 5);
	Units_Holder_Attributes->Add(Units_Grid_Attributes3, 0, wxEXPAND);
	Units_Holder_Attributes->Add(-1, 5);
	Units_Holder_Attributes->Add(Units_Holder_AnnexUnit1, 0, wxEXPAND);
	Units_Holder_Attributes->Add(-1, 5);
	Units_Holder_Attributes->Add(Units_Holder_AnnexUnitMisplacement1, 0, wxEXPAND);
	Units_Holder_Attributes->Add(-1, 5);
	Units_Holder_Attributes->Add(Units_Holder_AlfaThingy, 0, wxEXPAND);

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
	Units_Grid_SoundsArea2->Add(Units_Holder_AttackMode, 1, wxEXPAND);
	Units_Grid_SoundsArea2->Add(Units_Holder_AttackSound, 1, wxEXPAND);
	Units_Grid_SoundsArea2->Add(Units_Holder_MoveSound, 1, wxEXPAND);
	Units_Grid_SoundsArea2->Add(Units_Holder_DyingSound, 1, wxEXPAND);

	Units_Holder_SoundsArea->Add(Units_Holder_SoundsArea1, 0, wxEXPAND);
	Units_Holder_SoundsArea->Add(5, 5);
	Units_Holder_SoundsArea->Add(Units_Grid_SoundsArea2, 0, wxEXPAND);

	Units_Grid_HPBars->Add(Units_Holder_HPBarHeight1, 1, wxEXPAND);
	Units_Grid_HPBars->Add(Units_Holder_HPBarHeight2, 1, wxEXPAND);
	Units_Holder_MiscArea->Add(Units_Grid_HPBars, 1, wxEXPAND);

	Units_Grid_Type10plusUnknowns->Add(Units_Holder_Unknown1, 0, wxEXPAND);
	Units_Grid_Type10plusUnknowns->Add(Units_Holder_Unknown3, 0, wxEXPAND);
	Units_Grid_Type10plusUnknowns->Add(Units_Holder_Unknown6, 0, wxEXPAND);
	Units_Grid_Type10plusUnknowns->Add(Units_Holder_Unknown7, 0, wxEXPAND);
	Units_Grid_Type10plusUnknowns->Add(Units_Holder_Unknown8, 0, wxEXPAND);
	Units_Grid_Type10plusUnknowns->Add(Units_Holder_Unknown9, 0, wxEXPAND);
	Units_Holder_Type10plusUnknownArea->Add(Units_Grid_Type10plusUnknowns, 0, wxEXPAND);

	Units_Grid_Type30plusUnknownArea->Add(Units_Holder_Unknown11, 0, wxEXPAND);
	Units_Grid_Type30plusUnknownArea->Add(Units_Holder_Unknown12, 0, wxEXPAND);
	Units_Grid_Type30plusUnknownArea->Add(Units_Holder_Unknown16, 0, wxEXPAND);
	Units_Holder_Type30plusUnknownArea->Add(Units_Grid_Type30plusUnknownArea, 0, wxEXPAND);
	Units_Holder_Type30plusUnknownArea->Add(-1, 5);
	Units_Holder_Type30plusUnknownArea->Add(Units_Holder_Unknown16B, 0, wxEXPAND);

	Units_Holder_Type60plusUnknownArea->Add(Units_Holder_Unknown20, 2, wxEXPAND);
	Units_Holder_Type60plusUnknownArea->Add(5, -1);
	Units_Holder_Type60plusUnknownArea->Add(Units_Holder_Unknown21, 1, wxEXPAND);
	Units_Holder_Type60plusUnknownArea->AddStretchSpacer(1);

	Units_Grid_Type70plusUnknownArea->Add(Units_Holder_Unknown26, 0, wxEXPAND);
	Units_Grid_Type70plusUnknownArea->Add(Units_Holder_Unknown27, 0, wxEXPAND);
	Units_Grid_Type70plusUnknownArea->Add(Units_Holder_Unknown29, 0, wxEXPAND);
	Units_Holder_Type70plusUnknownArea->Add(Units_Grid_Type70plusUnknownArea, 0, wxEXPAND);

	Units_Grid_Type80plusUnknownArea->Add(Units_Holder_Unknown31, 0, wxEXPAND);
	Units_Grid_Type80plusUnknownArea->Add(Units_Holder_Unknown31b, 0, wxEXPAND);
	Units_Grid_Type80plusUnknownArea->Add(Units_Holder_Unknown32, 0, wxEXPAND);
	Units_Grid_Type80plusUnknownArea->Add(Units_Holder_Unknown33, 0, wxEXPAND);
	Units_Grid_Type80plusUnknownArea->Add(Units_Holder_Unknown34, 0, wxEXPAND);
	Units_Grid_Type80plusUnknownArea->Add(Units_Holder_Unknown35, 0, wxEXPAND);
	Units_Holder_Type80plusUnknownArea->Add(Units_Grid_Type80plusUnknownArea, 0, wxEXPAND);

	Units_UnitCommands_Buttons->Add(Units_UnitCommands_Add, 1, wxEXPAND);
	Units_UnitCommands_Buttons->Add(Units_UnitCommands_Insert, 1, wxEXPAND);
	Units_UnitCommands_Buttons->Add(Units_UnitCommands_Delete, 1, wxEXPAND);
	Units_UnitCommands_Buttons->Add(Units_UnitCommands_Copy, 1, wxEXPAND);
	Units_UnitCommands_Buttons->Add(Units_UnitCommands_Paste, 1, wxEXPAND);
	Units_UnitCommands_Buttons->Add(Units_UnitCommands_PasteInsert, 1, wxEXPAND);

	Units_UnitCommands->Add(Units_UnitCommands_Search, 0, wxEXPAND);
	Units_UnitCommands->Add(Units_UnitCommands_Search_R, 0, wxEXPAND);
	Units_UnitCommands->Add(-1, 2);
	Units_UnitCommands->Add(Units_UnitCommands_List, 1, wxEXPAND);
	Units_UnitCommands->Add(-1, 2);
	Units_UnitCommands->Add(Units_UnitCommands_Buttons, 0, wxEXPAND);
	Units_UnitCommands->Add(-1, 2);
	Units_UnitCommands->Add(Units_UnitCommands_CopyToUnits, 0, wxEXPAND);

	Units_CommandHolder_Lists->Add(Units_UnitHeads_Name, 0, wxEXPAND);
	Units_CommandHolder_Lists->Add(-1, 5);
	Units_CommandHolder_Lists->Add(Units_UnitCommands, 0, wxEXPAND);
	Units_CommandHolder_Lists->Add(-1, 5);
	Units_CommandHolder_Lists->Add(Units_Holder_Exists, 0, wxEXPAND);

	UnitCommands_Holder_1->Add(UnitCommands_Holder_One, 1, wxEXPAND);
	UnitCommands_Holder_1->Add(5, -1);
	UnitCommands_Holder_1->Add(UnitCommands_Holder_ID, 1, wxEXPAND);

	Units_CommandHolder_Grid1->Add(UnitCommands_Holder_ClassID, 1, wxEXPAND);
	Units_CommandHolder_Grid1->Add(UnitCommands_Holder_UnitID, 1, wxEXPAND);
	Units_CommandHolder_Grid1->Add(UnitCommands_Holder_Unknown2, 1, wxEXPAND);
	Units_CommandHolder_Grid1->Add(UnitCommands_Holder_ResourceIn, 1, wxEXPAND);
	Units_CommandHolder_Grid1->Add(UnitCommands_Holder_SubType, 1, wxEXPAND);
	Units_CommandHolder_Grid1->Add(UnitCommands_Holder_ResourceOut, 1, wxEXPAND);
	Units_CommandHolder_Grid1->Add(UnitCommands_Holder_Unknown3, 1, wxEXPAND);
	Units_CommandHolder_Grid1->Add(UnitCommands_Holder_WorkRateMultiplier, 1, wxEXPAND);
	Units_CommandHolder_Grid2->Add(UnitCommands_Holder_ExecutionRadius, 1, wxEXPAND);
	Units_CommandHolder_Grid2->Add(UnitCommands_Holder_ExtraRange, 1, wxEXPAND);

	Units_CommandHolder_Data2->Add(UnitCommands_Holder_1, 0, wxEXPAND);
	Units_CommandHolder_Data2->Add(-1, 5);
	Units_CommandHolder_Data2->Add(UnitCommands_Holder_Type, 0, wxEXPAND);
	Units_CommandHolder_Data2->Add(-1, 5);
	Units_CommandHolder_Data2->Add(Units_CommandHolder_Grid1, 0, wxEXPAND);
	Units_CommandHolder_Data2->Add(-1, 5);
	Units_CommandHolder_Data2->Add(Units_CommandHolder_Grid2, 0, wxEXPAND);
	Units_CommandHolder_Data2->Add(-1, 5);
	Units_CommandHolder_Grid3->Add(UnitCommands_Holder_Unknown1, 1, wxEXPAND);
	Units_CommandHolder_Grid3->Add(UnitCommands_Holder_Unknown4, 1, wxEXPAND);
	Units_CommandHolder_Grid3->Add(UnitCommands_Holder_Unknown5, 1, wxEXPAND);
	Units_CommandHolder_Grid3->Add(UnitCommands_Holder_Unknown6, 1, wxEXPAND);
	Units_CommandHolder_Grid3->Add(UnitCommands_Holder_Unknown7, 1, wxEXPAND);
	Units_CommandHolder_Grid3->Add(UnitCommands_Holder_Unknown8, 1, wxEXPAND);
	Units_CommandHolder_Grid3->Add(UnitCommands_Holder_Unknown9, 1, wxEXPAND);
	Units_CommandHolder_Grid3->Add(UnitCommands_Holder_Unknown10, 1, wxEXPAND);
	Units_CommandHolder_Grid3->Add(UnitCommands_Holder_Unknown11, 1, wxEXPAND);

	Units_CommandHolder_Data1->Add(Units_CommandHolder_Data2, 2, wxEXPAND);
	Units_CommandHolder_Data1->Add(5, -1);
	Units_CommandHolder_Data1->Add(Units_CommandHolder_Grid3, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);

	Units_CommandHolder_Data->Add(Units_CommandHolder_Data1, 0, wxEXPAND);
	Units_CommandHolder_Data->Add(-1, 5);
	Units_CommandHolder_Data->Add(UnitCommands_Grid_Graphics, 0, wxEXPAND);

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

	Units_Holder_Top->Add(Units_AutoCopy, 0, wxEXPAND);
	Units_Holder_Top->Add(Units_CopyTo, 0, wxEXPAND);
	Units_Holder_Top->Add(5, -1);
	Units_Holder_Top->Add(Units_CopyGraphics, 0, wxEXPAND);
	Units_Holder_Top->Add(Units_CopyToText, 0, wxEXPAND);
	Units_Holder_Top->Add(Units_SelectAll, 0, wxEXPAND);
	Units_Holder_Top->Add(Units_SelectClear, 0, wxEXPAND);
	Units_Holder_Top->Add(Units_GraphicSetText, 0, wxEXPAND);
	Units_Holder_Top->Add(Units_GraphicSet, 0, wxEXPAND);

	Units_DataArea->Add(-1, 15);
	Units_DataArea->Add(Units_Holder_Top, 0, wxEXPAND);
	Units_DataArea->Add(Units_Holder_TopGrid, 0, wxEXPAND);
	Units_DataArea->Add(Units_Holder_Type, 0, wxEXPAND);
	Units_DataArea->Add(-1, 5);
	Units_DataArea->Add(Units_Scroller, 1, wxEXPAND);
	Units_DataArea->Add(-1, 10);

	Units_Main->Add(10, -1);
	Units_Main->Add(Units_ListArea, 1, wxEXPAND);
	Units_Main->Add(10, -1);
	Units_Main->Add(Units_DataArea, 3, wxEXPAND);
	Units_Main->Add(10, -1);

	if(EnableIDFix)
	{
		Units_ID1->Enable(false);
		Units_ID2->Enable(false);
		Units_ID3->Enable(false);
		UnitCommands_ID->Enable(false);
	}

	Tab_Units->SetSizer(Units_Main);

	Connect(Units_Units_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitsSearch));
	Connect(Units_Units_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitsSearch));
	for(short loop = 0; loop < 2; loop++)
	{
		Connect(Units_Units_UseAnd[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsSearch));
		Connect(Units_Units_SearchFilters[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSelection_SearchFilters));
	}
	Connect(Units_Civs_List->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnitSubList));
	Connect(Units_Units_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnitsSelect));
	Connect(Units_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsAdd));
	Connect(Units_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsInsert));
	Connect(Units_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsDelete));
	Connect(Units_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsCopy));
	Connect(Units_SpecialCopy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsSpecialCopy));
	Connect(Units_SpecialPaste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsSpecialPaste));
	Connect(Units_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsPaste));
	Connect(Units_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsPasteInsert));
	//Connect(Units_Extract->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnExtractUnit));
	//Connect(Units_Import->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnImportUnit));
	Connect(Units_Enable->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsEnable));
	Connect(Units_Disable->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsDisable));
//	Connect(Units_Undo->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUndoing));
	Connect(Units_UnitCommands_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnitCommandsSelect));
	Connect(Units_UnitCommands_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitCommandsSearch));
	Connect(Units_UnitCommands_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitCommandsSearch));
	Connect(Units_UnitCommands_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitCommandsAdd));
	Connect(Units_UnitCommands_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitCommandsInsert));
	Connect(Units_UnitCommands_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitCommandsDelete));
	Connect(Units_UnitCommands_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitCommandsCopy));
	Connect(Units_UnitCommands_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitCommandsPaste));
	Connect(Units_UnitCommands_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitCommandsPasteInsert));
	Connect(Units_UnitCommands_CopyToUnits->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitCommandsCopyToUnits));
	Connect(Units_DamageGraphics_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsSearch));
	Connect(Units_DamageGraphics_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsSearch));
	Connect(Units_DamageGraphics_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsSelect));
	Connect(Units_DamageGraphics_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsAdd));
	Connect(Units_DamageGraphics_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsInsert));
	Connect(Units_DamageGraphics_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsDelete));
	Connect(Units_DamageGraphics_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsCopy));
	Connect(Units_DamageGraphics_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsPaste));
	Connect(Units_DamageGraphics_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsPasteInsert));
	Connect(Units_DamageGraphics_CopyToUnits->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsCopyToUnits));
	Connect(Units_Attacks_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksSearch));
	Connect(Units_Attacks_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksSearch));
	Connect(Units_Attacks_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksSelect));
	Connect(Units_Attacks_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksAdd));
	Connect(Units_Attacks_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksInsert));
	Connect(Units_Attacks_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksDelete));
	Connect(Units_Attacks_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksCopy));
	Connect(Units_Attacks_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksPaste));
	Connect(Units_Attacks_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksPasteInsert));
	Connect(Units_Attacks_CopyToUnits->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksCopyToUnits));
	Connect(Units_Armors_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsSearch));
	Connect(Units_Armors_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsSearch));
	Connect(Units_Armors_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsSelect));
	Connect(Units_Armors_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsAdd));
	Connect(Units_Armors_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsInsert));
	Connect(Units_Armors_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsDelete));
	Connect(Units_Armors_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsCopy));
	Connect(Units_Armors_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsPaste));
	Connect(Units_Armors_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsPasteInsert));
	Connect(Units_Armors_CopyToUnits->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsCopyToUnits));
	Connect(Units_LanguageDLLConverter[0]->GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(AGE_Frame::UnitLangDLLConverter));
	Connect(Units_LanguageDLLConverter[1]->GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(AGE_Frame::UnitLangDLLConverter));

	Units_DLL_LanguageName->Connect(Units_DLL_LanguageName->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_LangDLL), NULL, this);
	Units_DLL_LanguageCreation->Connect(Units_DLL_LanguageCreation->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_LangDLL), NULL, this);
	Units_DLL_HotKey4->Connect(Units_DLL_HotKey4->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_LangDLL), NULL, this);
	Units_DLL_LanguageHelp->Connect(Units_DLL_LanguageHelp->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_LangDLL), NULL, this);
	Units_DLL_LanguageHKText->Connect(Units_DLL_LanguageHKText->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_LangDLL), NULL, this);

//	Listing and Auto-Copy

	Units_Type->Connect(Units_Type->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Connect(Units_ComboBox_Type->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Units));

	Units_Name->Connect(Units_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_Name2->Connect(Units_Name2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_LanguageDLLName->Connect(Units_LanguageDLLName->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_LanguageDLLCreation->Connect(Units_LanguageDLLCreation->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_HotKey->Connect(Units_HotKey->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_LanguageDLLHelp->Connect(Units_LanguageDLLHelp->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_LanguageDLLHotKeyText->Connect(Units_LanguageDLLHotKeyText->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);

	DamageGraphics_GraphicID->Connect(DamageGraphics_GraphicID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	DamageGraphics_ComboBox_GraphicID->Connect(DamageGraphics_ComboBox_GraphicID->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Units), NULL, this);
	DamageGraphics_DamagePercent->Connect(DamageGraphics_DamagePercent->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Attacks_Class->Connect(Attacks_Class->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Attacks_Amount->Connect(Attacks_Amount->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Armors_Class->Connect(Armors_Class->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Armors_Amount->Connect(Armors_Amount->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	for(short loop = 0; loop < 2; loop++)
	Attacks_ComboBox_Class[loop]->Connect(Attacks_ComboBox_Class[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Units), NULL, this);

	UnitCommands_Type->Connect(UnitCommands_Type->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	UnitCommands_SubType->Connect(UnitCommands_SubType->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Connect(UnitCommands_ComboBox_Type->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Units));
}

void AGE_Frame::OnKillFocus_Units(wxFocusEvent &Event)
{
	if(!((AGETextCtrl*)Event.GetEventObject())->SaveEdits()) return;
	if(Event.GetId() == Units_Name->GetId() || Event.GetId() == Units_LanguageDLLName->GetId())
	{
		ListUnits(UnitCivID);
	}
	else if(Event.GetId() == Units_Type->GetId()
	|| Event.GetId() == Units_Name2->GetId()
	|| Event.GetId() == Units_LanguageDLLCreation->GetId()
	|| Event.GetId() == Units_HotKey->GetId()
	|| Event.GetId() == Units_LanguageDLLHelp->GetId()
	|| Event.GetId() == Units_LanguageDLLHotKeyText->GetId())
	{
		wxCommandEvent E;
		OnUnitsSelect(E);
	}
	else if(Event.GetId() == Attacks_Amount->GetId() || Event.GetId() == Attacks_Class->GetId())
	{
		ListUnitAttacks();
	}
	else if(Event.GetId() == Armors_Amount->GetId() || Event.GetId() == Armors_Class->GetId())
	{
		ListUnitArmors();
	}
	else if(Event.GetId() == UnitCommands_Type->GetId() || Event.GetId() == UnitCommands_SubType->GetId())
	{
		ListUnitCommands();
	}
	else if(Event.GetId() == DamageGraphics_DamagePercent->GetId()
	|| Event.GetId() == DamageGraphics_GraphicID->GetId())
	{
		ListUnitDamageGraphics();
	}
	Event.Skip();
}

void AGE_Frame::OnUpdateCombo_Units(wxCommandEvent &Event)
{
	if(Event.GetId() == Units_ComboBox_Type->GetId())
	{
		auto Selection = Units_ComboBox_Type->GetSelection();
		for(int loop = 0; loop < UnitIDs.size(); loop++)
		{
			switch(Selection)
			{
				case 1: GenieFile->Civs[UnitCivID].Units[UnitIDs[loop]].Type = 10; break;
				case 2: GenieFile->Civs[UnitCivID].Units[UnitIDs[loop]].Type = 20; break;
				case 3: GenieFile->Civs[UnitCivID].Units[UnitIDs[loop]].Type = 25; break;
				case 4: GenieFile->Civs[UnitCivID].Units[UnitIDs[loop]].Type = 30; break;
				case 5: GenieFile->Civs[UnitCivID].Units[UnitIDs[loop]].Type = 40; break;
				case 6: GenieFile->Civs[UnitCivID].Units[UnitIDs[loop]].Type = 60; break;
				case 7: GenieFile->Civs[UnitCivID].Units[UnitIDs[loop]].Type = 70; break;
				case 8: GenieFile->Civs[UnitCivID].Units[UnitIDs[loop]].Type = 80; break;
				case 9: GenieFile->Civs[UnitCivID].Units[UnitIDs[loop]].Type = 90; break;
			}
			if(AutoCopy) // Should copy-to-civ selections affect this?
			{
				char UnitType = GenieFile->Civs[UnitCivID].Units[UnitIDs[loop]].Type;
				for(short civ = 0; civ < GenieFile->Civs.size(); civ++)
				GenieFile->Civs[civ].Units[UnitIDs[loop]].Type = UnitType;
			}
		}
		wxCommandEvent E;
		OnUnitsSelect(E);	// Updates unit layout.
//		ListUnits(UnitCivID, false);	// For special search filters.
		return;
	}
	if(Event.GetId() == UnitCommands_ComboBox_Type->GetId())
	{
		switch(UnitCommands_ComboBox_Type->GetSelection())
		{
			case 1: UnitCommands_Type->ChangeValue("3"); break;
			case 2: UnitCommands_Type->ChangeValue("5"); break;
			case 3: UnitCommands_Type->ChangeValue("6"); break;
			case 4: UnitCommands_Type->ChangeValue("7"); break;
			case 5: UnitCommands_Type->ChangeValue("10"); break;
			case 6: UnitCommands_Type->ChangeValue("11"); break;
			case 7: UnitCommands_Type->ChangeValue("12"); break;
			case 8: UnitCommands_Type->ChangeValue("13"); break;
			case 9: UnitCommands_Type->ChangeValue("21"); break;
			case 10: UnitCommands_Type->ChangeValue("101"); break;
			case 11: UnitCommands_Type->ChangeValue("104"); break;
			case 12: UnitCommands_Type->ChangeValue("105"); break;
			case 13: UnitCommands_Type->ChangeValue("106"); break;
			case 14: UnitCommands_Type->ChangeValue("107"); break;
			case 15: UnitCommands_Type->ChangeValue("109"); break;
			case 16: UnitCommands_Type->ChangeValue("110"); break;
			case 17: UnitCommands_Type->ChangeValue("111"); break;
			case 18: UnitCommands_Type->ChangeValue("120"); break;
			case 19: UnitCommands_Type->ChangeValue("121"); break;
			case 20: UnitCommands_Type->ChangeValue("122"); break;
			case 21: UnitCommands_Type->ChangeValue("125"); break;
			case 22: UnitCommands_Type->ChangeValue("131"); break;
			case 23: UnitCommands_Type->ChangeValue("132"); break;
			case 24: UnitCommands_Type->ChangeValue("135"); break;
			case 25: UnitCommands_Type->ChangeValue("136"); break;
			default: UnitCommands_Type->ChangeValue("-1");
		}

		UnitCommands_Type->SaveEdits();

		ListUnitCommands();
		return;
	}
	((AGEComboBox*)Event.GetEventObject())->OnUpdate(Event);
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
