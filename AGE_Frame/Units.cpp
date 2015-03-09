#include "../AGE_Frame.h"

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
		int filters = 2;
		short Selection[filters];
		for(short loop = 0; loop < filters; ++loop)
		Selection[loop] = Units_SearchFilters[loop]->GetSelection();
		genie::Unit * UnitPointer = &GenieFile->Civs[civ].Units[Index];
		short UnitType = UnitPointer->Type;

		if(Selection[0] > 0)
		switch(Units_FilterSelector->GetSelection())
		{
			case 0: // Type20
			for(short loop = 0; loop < filters; ++loop)
			{
				switch(Selection[loop])
				{
					case 1: Name += "T "+FormatInt(UnitPointer->Type); break;
					case 2: Name += "NL "+FormatInt(UnitPointer->NameLength); break;
					case 3: Name += "I1 "+FormatInt(UnitPointer->ID1); break;
					case 4: Name += "LN "+FormatInt(UnitPointer->LanguageDLLName); break;
					case 5: Name += "LC "+FormatInt(UnitPointer->LanguageDLLCreation); break;
					case 6: Name += "C "+FormatInt(UnitPointer->Class); break;
					case 7: Name += "SG "+FormatInt(UnitPointer->StandingGraphic.first)+" "+FormatInt(UnitPointer->StandingGraphic.second); break;
					case 8: Name += "DG "+FormatInt(UnitPointer->DyingGraphic.first)+" "+FormatInt(UnitPointer->DyingGraphic.second); break;
					case 9: Name += "DM "+FormatInt(UnitPointer->DeathMode); break;
					case 10: Name += "HP "+FormatInt(UnitPointer->HitPoints); break;
					case 11: Name += "LS "+FormatFloat(UnitPointer->LineOfSight); break;
					case 12: Name += "GC "+FormatInt(UnitPointer->GarrisonCapacity); break;
					case 13: Name += "SR "+FormatInt(UnitPointer->SizeRadius.first)+" "+FormatInt(UnitPointer->SizeRadius.second); break;
					case 14: Name += "B1 "+FormatFloat(UnitPointer->HPBarHeight1); break;
					case 15: Name += "TS "+FormatInt(UnitPointer->TrainSound.first)+" "+FormatInt(UnitPointer->TrainSound.second); break;
					case 16: Name += "DU "+FormatInt(UnitPointer->DeadUnitID); break;
					case 17: Name += "PM "+FormatInt(UnitPointer->PlacementMode); break;
					case 18: Name += "AM "+FormatInt(UnitPointer->AirMode); break;
					case 19: Name += "I "+FormatInt(UnitPointer->IconID); break;
					case 20: Name += "HE "+FormatInt(UnitPointer->HideInEditor); break;
					case 21: Name += "U1 "+FormatInt(UnitPointer->Unknown1); break;
					case 22: Name += "E "+FormatInt(UnitPointer->Enabled); break;
					case 23: Name += "D "+FormatInt(UnitPointer->Disabled); break;
					case 24: Name += "PBT "+FormatInt(UnitPointer->PlacementBypassTerrain.first)+" "+FormatInt(UnitPointer->PlacementBypassTerrain.second); break;
					case 25: Name += "PT "+FormatInt(UnitPointer->PlacementTerrain.first)+" "+FormatInt(UnitPointer->PlacementTerrain.second); break;
					case 26: Name += "ER "+FormatInt(UnitPointer->EditorRadius.first)+" "+FormatInt(UnitPointer->EditorRadius.second); break;
					case 27: Name += "HM "+FormatInt(UnitPointer->HillMode); break;
					case 28: Name += "VF "+FormatInt(UnitPointer->VisibleInFog); break;
					case 29: Name += "TR "+FormatInt(UnitPointer->TerrainRestriction); break;
					case 30: Name += "FM "+FormatInt(UnitPointer->FlyMode); break;
					case 31: Name += "RC "+FormatInt(UnitPointer->ResourceCapacity); break;
					case 32: Name += "RD "+FormatFloat(UnitPointer->ResourceDecay); break;
					case 33: Name += "BT "+FormatInt(UnitPointer->BlastType); break;
					case 34: Name += "U2 "+FormatInt(UnitPointer->Unknown2); break;
					case 35: Name += "IM "+FormatInt(UnitPointer->InteractionMode); break;
					case 36: Name += "MM "+FormatInt(UnitPointer->MinimapMode); break;
					case 37: Name += "CA "+FormatInt(UnitPointer->CommandAttribute); break;
					case 38: Name += "U3A "+FormatFloat(UnitPointer->Unknown3A); break;
					case 39: Name += "MC "+FormatInt(UnitPointer->MinimapColor); break;
					case 40: Name += "LH "+FormatInt(UnitPointer->LanguageDLLHelp); break;
					case 41: Name += "LT "+FormatInt(UnitPointer->LanguageDLLHotKeyText); break;
					case 42: Name += "HK "+FormatInt(UnitPointer->HotKey); break;
					case 43: Name += "US "+FormatInt(UnitPointer->Unselectable); break;
					case 44: Name += "U6 "+FormatInt(UnitPointer->Unknown6); break;
					case 45: Name += "U7 "+FormatInt(UnitPointer->UnknownSelectionMode); break;
					case 46: Name += "U8 "+FormatInt(UnitPointer->Unknown8); break;
					case 47: Name += "SM "+FormatInt(UnitPointer->SelectionMask); break;
					case 48: Name += "ST "+FormatInt(UnitPointer->SelectionShapeType); break;
					case 49: Name += "SSh "+FormatInt(UnitPointer->SelectionShape); break;
					case 50: Name += "A "+FormatInt(UnitPointer->Attribute); break;
					case 51: Name += "Ci "+FormatInt(UnitPointer->Civilization); break;
					case 52: Name += "No "+FormatInt(UnitPointer->Nothing); break;
					case 53: Name += "SE "+FormatInt(UnitPointer->SelectionEffect); break;
					case 54: Name += "EC "+FormatInt(UnitPointer->EditorSelectionColour); break;
					case 55: Name += "SS "+FormatInt(UnitPointer->SelectionRadius.first)+" "+FormatInt(UnitPointer->SelectionRadius.second); break;
					case 56: Name += "B2 "+FormatFloat(UnitPointer->HPBarHeight2); break;
					case 57: Name += "Ask Tapsa"; break;
					case 58: Name += "DC "+FormatInt(UnitPointer->DamageGraphics.size()); break;
					case 59: Name += "Ask Tapsa"; break;
					case 60: Name += "SSo "+FormatInt(UnitPointer->SelectionSound); break;
					case 61: Name += "DS "+FormatInt(UnitPointer->DyingSound); break;
					case 62: Name += "AtM "+FormatInt(UnitPointer->AttackMode); break;
					case 63: Name += "EM "+FormatInt(UnitPointer->EdibleMeat); break;
					case 64: Name += UnitPointer->Name; break;
					case 65: Name += "NL2 "+FormatInt(UnitPointer->NameLength2); break;
					case 66: Name += UnitPointer->Name2; break;
					case 67: Name += "UL "+FormatInt(UnitPointer->Unitline); break;
					case 68: Name += "MT "+FormatInt(UnitPointer->MinTechLevel); break;
					case 69: Name += "I2 "+FormatInt(UnitPointer->ID2); break;
					case 70: Name += "I3 "+FormatInt(UnitPointer->ID3); break;
					case 71: Name += "S "+FormatFloat(UnitPointer->Speed); break;
				}
				Name += ", ";
				if(Selection[loop+1] == 0) break;
			}
			break;
			case 1: // Type30
			for(short loop = 0; loop < filters; ++loop)
			{
				switch(Selection[loop])
				{
					case 1: Name += "WG "+FormatInt(UnitPointer->DeadFish.WalkingGraphic.first)+" "+FormatInt(UnitPointer->DeadFish.WalkingGraphic.second); break;
					case 2: Name += "RS "+FormatFloat(UnitPointer->DeadFish.RotationSpeed); break;
					case 3: Name += "U11 "+FormatInt(UnitPointer->DeadFish.Unknown11); break;
					case 4: Name += "TU "+FormatInt(UnitPointer->DeadFish.TrackingUnit); break;
					case 5: Name += "UU "+FormatInt(UnitPointer->DeadFish.TrackingUnitUsed); break;
					case 6: Name += "UD "+FormatFloat(UnitPointer->DeadFish.TrackingUnitDensity); break;
					case 7: Name += "U16 "+FormatInt(UnitPointer->DeadFish.Unknown16); break;
					case 8: Name += "Ask Tapsa"; break;
				}
				Name += ", ";
				if(Selection[loop+1] == 0) break;
			}
			break;
			case 2: // Type40
			for(short loop = 0; loop < filters; ++loop)
			{
				switch(Selection[loop])
				{
					case 1: Name += "SC "+FormatInt(UnitPointer->Bird.SheepConversion); break;
					case 2: Name += "SR "+FormatFloat(UnitPointer->Bird.SearchRadius); break;
					case 3: Name += "WR "+FormatFloat(UnitPointer->Bird.WorkRate); break;
					case 4: Name += "DS "+FormatInt(UnitPointer->Bird.DropSite.first)+" "+FormatInt(UnitPointer->Bird.DropSite.second); break;
					case 5: Name += "VM "+FormatInt(UnitPointer->Bird.VillagerMode); break;
					case 6: Name += "AS "+FormatInt(UnitPointer->Bird.AttackSound); break;
					case 7: Name += "MS "+FormatInt(UnitPointer->Bird.MoveSound); break;
					case 8: Name += "AM "+FormatInt(UnitPointer->Bird.AnimalMode); break;
					case 9: Name += "CC "+FormatInt(UnitPointer->Bird.Commands.size()); break;
					case 10: Name += "Ask Tapsa"; break;
				}
				Name += ", ";
				if(Selection[loop+1] == 0) break;
			}
			break;
			case 3: // Type50
			for(short loop = 0; loop < filters; ++loop)
			{
				switch(Selection[loop])
				{
					case 1: Name += "DA "+FormatInt(UnitPointer->Type50.DefaultArmor); break;
					case 2: Name += "AtC "+FormatInt(UnitPointer->Type50.Attacks.size()); break;
					case 3: for(short i = 0; i < UnitPointer->Type50.Attacks.size(); ++i)
					Name += "c" + FormatInt(UnitPointer->Type50.Attacks[i].Class) + " "; break;
					case 4: Name += "ArC "+FormatInt(UnitPointer->Type50.Armours.size()); break;
					case 5: for(short i = 0; i < UnitPointer->Type50.Armours.size(); ++i)
					Name += "c" + FormatInt(UnitPointer->Type50.Armours[i].Class) + " "; break;
					case 6: Name += "TR "+FormatInt(UnitPointer->Type50.TerRestrictionForDmgMultiplying); break;
					case 7: Name += "MaR "+FormatFloat(UnitPointer->Type50.MaxRange); break;
					case 8: Name += "BR "+FormatFloat(UnitPointer->Type50.BlastRadius); break;
					case 9: Name += "RT "+FormatFloat(UnitPointer->Type50.ReloadTime); break;
					case 10: Name += "PU "+FormatInt(UnitPointer->Type50.ProjectileUnitID); break;
					case 11: Name += "AP "+FormatInt(UnitPointer->Type50.AccuracyPercent); break;
					case 12: Name += "TM "+FormatInt(UnitPointer->Type50.TowerMode); break;
					case 13: Name += "D "+FormatInt(UnitPointer->Type50.FrameDelay); break;
					case 14: Name += "x"+FormatInt(UnitPointer->Type50.GraphicDisplacement[0]);
						Name += " y"+FormatInt(UnitPointer->Type50.GraphicDisplacement[1]);
						Name += " z"+FormatInt(UnitPointer->Type50.GraphicDisplacement[2]); break;
					case 15: Name += "BL "+FormatInt(UnitPointer->Type50.BlastLevel); break;
					case 16: Name += "MiR "+FormatFloat(UnitPointer->Type50.MinRange); break;
					case 17: Name += "AE "+FormatFloat(UnitPointer->Type50.AccuracyErrorRadius); break;
					case 18: Name += "AG "+FormatInt(UnitPointer->Type50.AttackGraphic); break;
					case 19: Name += "DM "+FormatInt(UnitPointer->Type50.DisplayedMeleeArmour); break;
					case 20: Name += "DP "+FormatInt(UnitPointer->Type50.DisplayedAttack); break;
					case 21: Name += "DR "+FormatFloat(UnitPointer->Type50.DisplayedRange); break;
					case 22: Name += "DT "+FormatFloat(UnitPointer->Type50.DisplayedReloadTime); break;
				}
				Name += ", ";
				if(Selection[loop+1] == 0) break;
			}
			break;
			case 4: // Type60
			for(short loop = 0; loop < filters; ++loop)
			{
				switch(Selection[loop])
				{
					case 1: Name += "SM "+FormatInt(UnitPointer->Projectile.StretchMode); break;
					case 2: Name += "CM "+FormatInt(UnitPointer->Projectile.CompensationMode); break;
					case 3: Name += "DA "+FormatInt(UnitPointer->Projectile.DropAnimationMode); break;
					case 4: Name += "PM "+FormatInt(UnitPointer->Projectile.PenetrationMode); break;
					case 5: Name += "U24 "+FormatInt(UnitPointer->Projectile.Unknown24); break;
					case 6: Name += "PA "+FormatFloat(UnitPointer->Projectile.ProjectileArc); break;
				}
				Name += ", ";
				if(Selection[loop+1] == 0) break;
			}
			break;
			case 5: // Type70
			for(short loop = 0; loop < filters; ++loop)
			{
				switch(Selection[loop])
				{
					case 1: Name += "Ask Tapsa"; break;
					case 2: Name += "TT "+FormatInt(UnitPointer->Creatable.TrainTime); break;
					case 3: Name += "TL "+FormatInt(UnitPointer->Creatable.TrainLocationID); break;
					case 4: Name += "B "+FormatInt(UnitPointer->Creatable.ButtonID); break;
					case 5: Name += "U26 "+FormatInt(UnitPointer->Creatable.Unknown26); break;
					case 6: Name += "U27 "+FormatInt(UnitPointer->Creatable.Unknown27); break;
					case 7: Name += "U28 "+FormatInt(UnitPointer->Creatable.Unknown28); break;
					case 8: Name += "HM "+FormatInt(UnitPointer->Creatable.HeroMode); break;
					case 9: Name += "GG "+FormatInt(UnitPointer->Creatable.GarrisonGraphic); break;
					case 10: Name += "Di "+FormatFloat(UnitPointer->Creatable.DuplicatedMissilesMin); break;
					case 11: Name += "Da "+FormatInt(UnitPointer->Creatable.DuplicatedMissilesMax); break;
					case 12: Name += "x"+FormatInt(UnitPointer->Creatable.MissileSpawningArea[0]);
						Name += " y"+FormatInt(UnitPointer->Creatable.MissileSpawningArea[1]);
						Name += " z"+FormatInt(UnitPointer->Creatable.MissileSpawningArea[2]); break;
					case 13: Name += "AP "+FormatInt(UnitPointer->Creatable.AlternativeProjectileUnit); break;
					case 14: Name += "CG "+FormatInt(UnitPointer->Creatable.ChargingGraphic); break;
					case 15: Name += "CM "+FormatInt(UnitPointer->Creatable.ChargingMode); break;
					case 16: Name += "DP "+FormatInt(UnitPointer->Creatable.DisplayedPierceArmour); break;
				}
				Name += ", ";
				if(Selection[loop+1] == 0) break;
			}
			break;
			case 6: // Type80
			for(short loop = 0; loop < filters; ++loop)
			{
				switch(Selection[loop])
				{
					case 1: Name += "CG "+FormatInt(UnitPointer->Building.ConstructionGraphicID); break;
					case 2: Name += "SG "+FormatInt(UnitPointer->Building.SnowGraphicID); break;
					case 3: Name += "AM "+FormatInt(UnitPointer->Building.AdjacentMode); break;
					case 4: Name += "GA "+FormatInt(UnitPointer->Building.GraphicsAngle); break;
					case 5: Name += "DB "+FormatInt(UnitPointer->Building.DisappearsWhenBuilt); break;
					case 6: Name += "SU "+FormatInt(UnitPointer->Building.StackUnitID); break;
					case 7: Name += "FT "+FormatInt(UnitPointer->Building.FoundationTerrainID); break;
					case 8: Name += "OT "+FormatInt(UnitPointer->Building.OldTerrainLikeID); break;
					case 9: Name += "R "+FormatInt(UnitPointer->Building.ResearchID); break;
					case 10: Name += "U33 "+FormatInt(UnitPointer->Building.Unknown33); break;
					case 11: Name += "Ask Tapsa"; break;
					case 12: Name += "HU "+FormatInt(UnitPointer->Building.HeadUnit); break;
					case 13: Name += "TU "+FormatInt(UnitPointer->Building.TransformUnit); break;
					case 14: Name += "US "+FormatInt(UnitPointer->Building.UnknownSound); break;
					case 15: Name += "CS "+FormatInt(UnitPointer->Building.ConstructionSound); break;
					case 16: Name += "GT "+FormatInt(UnitPointer->Building.GarrisonType); break;
					case 17: Name += "GH "+FormatFloat(UnitPointer->Building.GarrisonHealRate); break;
					case 18: Name += "U35 "+FormatFloat(UnitPointer->Building.Unknown35); break;
					case 19: Name += "PU "+FormatInt(UnitPointer->Building.PileUnit); break;
					case 20: Name += "Ask Tapsa"; break;
				}
				Name += ", ";
				if(Selection[loop+1] == 0) break;
			}
			break;
		}
	}

Names:
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

void AGE_Frame::ListUnits(short civ, bool all)
{
	InitUnits(civ, all);
	wxCommandEvent E;
	OnUnitsSelect(E);
}

void AGE_Frame::InitUnits(short civ, bool all)
{
	searchText = Units_Search->GetValue().Lower();
	excludeText = Units_Search_R->GetValue().Lower();
	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = Units_UseAnd[loop]->GetValue();

	Units_Civs_List->SetSelection(civ);

	list<void*> dataPointers;
	wxArrayString filteredNames;
	if(all)
	{
		AGE_AreaTT84::units.Clear();
		AGE_AreaTT84::units.Alloc(GenieFile->Civs[0].Units.size());
	}

	short matcher = genie::UT_Trees;
	switch(Units_FilterSelector->GetSelection())
	{
		case 0: matcher = genie::UT_25; break;
		case 1: matcher = genie::UT_Dead_Fish; break;
		case 2: matcher = genie::UT_Bird; break;
		case 3: matcher = genie::UT_Unknown; break;
		case 4: matcher = genie::UT_Projectile; break;
		case 5: matcher = genie::UT_Creatable; break;
		case 6: matcher = genie::UT_Building; break;
	}
	for(short loop = 0; loop < GenieFile->Civs[civ].Units.size(); ++loop)
	{
		if(all) AGE_AreaTT84::units.Add(" "+FormatInt(loop)+" - "+GetUnitName(loop, 0));
		if(matcher > genie::UT_25)
		{
			if(matcher == genie::UT_Projectile)
			if(GenieFile->Civs[civ].Units[loop].Type != genie::UT_Projectile) continue;
			if(GenieFile->Civs[civ].Units[loop].Type < matcher) continue;
			if(GenieFile->Civs[civ].Units[loop].Type == genie::UT_AoeTrees) continue;
		}
		wxString Name = " "+FormatInt(loop)+" - "+GetUnitName(loop, civ, true)+" ";
		if(SearchMatches(Name.Lower()))
		{
			filteredNames.Add(Name);
			dataPointers.push_back((void*)&GenieFile->Civs[civ].Units[loop]);
		}
	}

	Listing(Units_List, filteredNames, dataPointers);
	if(all)
	{
		FillLists(UnitComboBoxList, AGE_AreaTT84::units);
		if(GenieVersion >= genie::GV_AoKA)
		{
			TechTrees_Ages_Items.FillItemCombo(TechTrees_Ages_Items.ItemCombo->GetSelection(), true);
			TechTrees_Buildings_Items.FillItemCombo(TechTrees_Buildings_Items.ItemCombo->GetSelection(), true);
			TechTrees_Units_Items.FillItemCombo(TechTrees_Units_Items.ItemCombo->GetSelection(), true);
			TechTrees_Researches_Items.FillItemCombo(TechTrees_Researches_Items.ItemCombo->GetSelection(), true);
		}
	}

	for(short loop = 0; loop < 2; ++loop)
	useAnd[loop] = false;
}

//	This links data into user interface
void AGE_Frame::OnUnitsSelect(wxCommandEvent &Event)
{
	auto selections = Units_List->GetSelections(Items);
	if(selections < 1) return;	// If a unit is selected.

	UnitCivID = Units_Civs_List->GetSelection();

	// Auto-copy stuff
	SelectedCivs.resize(1);
	SelectedCivs[0] = UnitCivID;
	if(AutoCopy)
	{
		for(short civ = 0; civ < GenieFile->Civs.size(); ++civ)
		{
			// Counts all selected civs and always the one being edited.
			if(Units_CivBoxes[civ]->IsChecked() && civ != UnitCivID)
				SelectedCivs.push_back(civ);
		}
	}

	UnitIDs.resize(selections);
	int PointerCount = selections * SelectedCivs.size();
	Units_Type->resize(PointerCount);
	// Type 80
	Units_AdjacentMode->resize(PointerCount);
	Units_IconDisabler->resize(PointerCount);
	Units_DisappearsWhenBuilt->resize(PointerCount);
	Units_StackUnitID->resize(PointerCount);
	Units_TerrainID->resize(PointerCount);
	Units_OldTerrainLikeID->resize(PointerCount);
	Units_ResearchID->resize(PointerCount);
	if(GenieVersion >= genie::GV_AoKA)
	{
		Units_Unknown33->resize(PointerCount);
		for(short loop = 0; loop < 4; ++loop)
		{
			Units_AnnexUnit[loop]->resize(PointerCount);
			Units_AnnexUnitMisplacement[loop][0]->resize(PointerCount);
			Units_AnnexUnitMisplacement[loop][1]->resize(PointerCount);
		}
		Units_HeadUnit->resize(PointerCount);
		Units_TransformUnit->resize(PointerCount);
		Units_UnknownSound->resize(PointerCount);
		Units_GarrisonType->resize(PointerCount);
		Units_GarrisonHealRate->resize(PointerCount);
		Units_Unknown35->resize(PointerCount);
		Units_PileUnit->resize(PointerCount);
		for(short loop = 0; loop < Units_LootSwitch.size(); ++loop)
		Units_LootSwitch[loop]->resize(PointerCount);
	}
	Units_ConstructionSound->resize(PointerCount);
	// Type 70
	for(short loop = 0; loop < 3; ++loop)
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
		Units_Unknown28->resize(PointerCount);
		if(GenieVersion >= genie::GV_AoKB)
		{
			Units_HeroMode->resize(PointerCount);
		}
		Units_AttackMissileDuplicationAmount1->resize(PointerCount);
		Units_AttackMissileDuplicationAmount2->resize(PointerCount);
		for(short loop = 0; loop < 3; ++loop)
		{
			Units_AttackMissileDuplicationSpawning[loop]->resize(PointerCount);
		}
		Units_AttackMissileDuplicationUnit->resize(PointerCount);
		Units_ChargingGraphic->resize(PointerCount);
		Units_ChargingMode->resize(PointerCount);
	}
	Units_DisplayedPierceArmour->resize(PointerCount);
	// Type 50 & 60
	Units_DefaultArmor->resize(PointerCount);
	Units_TerRestrictionForDmgMultiply->resize(PointerCount);
	Units_MaxRange->resize(PointerCount);
	Units_BlastRadius->resize(PointerCount);
	Units_ReloadTime1->resize(PointerCount);
	Units_ProjectileUnitID->resize(PointerCount);
	Units_AccuracyPercent->resize(PointerCount);
	Units_TowerMode->resize(PointerCount);
	Units_Delay->resize(PointerCount);
	for(short loop = 0; loop < 3; ++loop)
	{
		Units_GraphicDisplacement[loop]->resize(PointerCount);
	}
	Units_BlastLevel->resize(PointerCount);
	Units_MinRange->resize(PointerCount);
	if(GenieVersion >= genie::GV_AoKB)
	{
		Units_AccuracyErrorRadius->resize(PointerCount);
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
	if(GenieVersion >= genie::GV_AoKB)
	{
		for(short loop = 0; loop < Units_Unknown16B.size(); ++loop)
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
	Units_HillMode->resize(PointerCount);
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
		Units_SelectionMask->resize(PointerCount);
		Units_SelectionShapeType->resize(PointerCount);
		Units_SelectionShape->resize(PointerCount);
		Units_ID3->resize(PointerCount);
		if(GenieVersion >= genie::GV_AoK)
		{
			Units_Disabled->resize(PointerCount);
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
	}
	Units_Enabled->resize(PointerCount);
	Units_CommandAttribute->resize(PointerCount);
	Units_Unknown3A->resize(PointerCount);
	Units_MinimapColor->resize(PointerCount);
	Units_LanguageDLLHelp->resize(PointerCount);
	Units_LanguageDLLHotKeyText->resize(PointerCount);
	Units_HotKey->resize(PointerCount);
	Units_Unselectable->resize(PointerCount);
	Units_Unknown6->resize(PointerCount);
	Units_Unknown7->resize(PointerCount);
	Units_Unknown8->resize(PointerCount);
	Units_SelectionRadius[0]->resize(PointerCount);
	Units_SelectionRadius[1]->resize(PointerCount);
	Units_HPBarHeight2->resize(PointerCount);
	Units_SelectionSound->resize(PointerCount);
	Units_DyingSound->resize(PointerCount);
	Units_AttackMode->resize(PointerCount);
	Units_EdibleMeat->resize(PointerCount);
	Units_Name->resize(PointerCount);
	Units_ID2->resize(PointerCount);
	for(short loop = 0; loop < 3; ++loop)
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
	if(!CopyGraphics) PointerCount = selections;
	Units_IconID->resize(PointerCount);
	Units_ConstructionGraphicID->resize(PointerCount);
	if(GenieVersion >= genie::GV_AoKB)
	{
		Units_GarrisonGraphic->resize(PointerCount);
		Units_StandingGraphic[1]->resize(PointerCount);
		if(GenieVersion >= genie::GV_TC) Units_SnowGraphicID->resize(PointerCount);
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
	for(auto sel = selections; sel--> 0;)
	{
		UnitPointer = (genie::Unit*)Units_List->GetClientData(Items.Item(sel));
		UnitIDs[sel] = (UnitPointer - (&GenieFile->Civs[UnitCivID].Units[0]));
		//locations.Append("Unit "+lexical_cast<string>(UnitIDs[sel])+":   ");

		// This makes auto-copy automatic.
		for(short vecCiv = SelectedCivs.size(); vecCiv--> 0;)
		{
			//locations.Append("Vec "+lexical_cast<string>(vecCiv)+", civ "+lexical_cast<string>(SelectedCivs[vecCiv])+"; ");
			UnitPointer = &GenieFile->Civs[SelectedCivs[vecCiv]].Units[UnitIDs[sel]];

			UnitType = (short)UnitPointer->Type;
			// This ensures that the first pointer is always the current civ and its first selection.
			int location = sel + vecCiv * selections;
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
					Units_IconDisabler->container[location] = &UnitPointer->Building.GraphicsAngle;
					Units_DisappearsWhenBuilt->container[location] = &UnitPointer->Building.DisappearsWhenBuilt;
					Units_StackUnitID->container[location] = &UnitPointer->Building.StackUnitID;
					Units_TerrainID->container[location] = &UnitPointer->Building.FoundationTerrainID;
					Units_OldTerrainLikeID->container[location] = &UnitPointer->Building.OldTerrainLikeID;
					Units_ResearchID->container[location] = &UnitPointer->Building.ResearchID;
					if(GenieVersion >= genie::GV_AoKA)
					{
						if(GenieVersion >= genie::GV_TC)
						{
							if(CopyGraphics || vecCiv == 0)
							Units_SnowGraphicID->container[location] = &UnitPointer->Building.SnowGraphicID;
						}
						Units_Unknown33->container[location] = &UnitPointer->Building.Unknown33;
						for(short loop = 0; loop < 4; ++loop)
						{
							Units_AnnexUnit[loop]->container[location] = &UnitPointer->Building.Annexes[loop].UnitID;
							Units_AnnexUnitMisplacement[loop][0]->container[location] = &UnitPointer->Building.Annexes[loop].Misplacement.first;
							Units_AnnexUnitMisplacement[loop][1]->container[location] = &UnitPointer->Building.Annexes[loop].Misplacement.second;
						}
						Units_HeadUnit->container[location] = &UnitPointer->Building.HeadUnit;
						Units_TransformUnit->container[location] = &UnitPointer->Building.TransformUnit;
						Units_UnknownSound->container[location] = &UnitPointer->Building.UnknownSound;
						Units_GarrisonType->container[location] = &UnitPointer->Building.GarrisonType;
						Units_GarrisonHealRate->container[location] = &UnitPointer->Building.GarrisonHealRate;
						Units_Unknown35->container[location] = &UnitPointer->Building.Unknown35;
						Units_PileUnit->container[location] = &UnitPointer->Building.PileUnit;
						for(short loop = 0; loop < Units_LootSwitch.size(); ++loop)
						Units_LootSwitch[loop]->container[location] = &UnitPointer->Building.LootingTable[loop];
					}
					Units_ConstructionSound->container[location] = &UnitPointer->Building.ConstructionSound;
				}
				//case 70:
				{
					for(short loop = 0; loop < 3; ++loop)
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
						Units_Unknown28->container[location] = &UnitPointer->Creatable.Unknown28;
						if(GenieVersion >= genie::GV_AoKB)
						{
							Units_HeroMode->container[location] = &UnitPointer->Creatable.HeroMode;
							if(CopyGraphics || vecCiv == 0)
							{
								Units_GarrisonGraphic->container[location] = &UnitPointer->Creatable.GarrisonGraphic;
							}
						}
						Units_AttackMissileDuplicationAmount1->container[location] = &UnitPointer->Creatable.DuplicatedMissilesMin;
						Units_AttackMissileDuplicationAmount2->container[location] = &UnitPointer->Creatable.DuplicatedMissilesMax;
						for(short loop = 0; loop < 3; ++loop)
						{
							Units_AttackMissileDuplicationSpawning[loop]->container[location] = &UnitPointer->Creatable.MissileSpawningArea[loop];
						}
						Units_AttackMissileDuplicationUnit->container[location] = &UnitPointer->Creatable.AlternativeProjectileUnit;
						Units_ChargingGraphic->container[location] = &UnitPointer->Creatable.ChargingGraphic;
						Units_ChargingMode->container[location] = &UnitPointer->Creatable.ChargingMode;
					}
					Units_DisplayedPierceArmour->container[location] = &UnitPointer->Creatable.DisplayedPierceArmour;
				}
				//case 60:
				//case 50:
				{
					Units_DefaultArmor->container[location] = &UnitPointer->Type50.DefaultArmor;
					Units_TerRestrictionForDmgMultiply->container[location] = &UnitPointer->Type50.TerRestrictionForDmgMultiplying;
					Units_MaxRange->container[location] = &UnitPointer->Type50.MaxRange;
					Units_BlastRadius->container[location] = &UnitPointer->Type50.BlastRadius;
					Units_ReloadTime1->container[location] = &UnitPointer->Type50.ReloadTime;
					Units_ProjectileUnitID->container[location] = &UnitPointer->Type50.ProjectileUnitID;
					Units_AccuracyPercent->container[location] = &UnitPointer->Type50.AccuracyPercent;
					Units_TowerMode->container[location] = &UnitPointer->Type50.TowerMode;
					Units_Delay->container[location] = &UnitPointer->Type50.FrameDelay;
					for(short loop = 0; loop < 3; ++loop)
					{
						Units_GraphicDisplacement[loop]->container[location] = &UnitPointer->Type50.GraphicDisplacement[loop];
					}
					Units_BlastLevel->container[location] = &UnitPointer->Type50.BlastLevel;
					Units_MinRange->container[location] = &UnitPointer->Type50.MinRange;
					if(GenieVersion >= genie::GV_AoKB)
					{
						Units_AccuracyErrorRadius->container[location] = &UnitPointer->Type50.AccuracyErrorRadius;
					}
					if(CopyGraphics || vecCiv == 0)
					Units_AttackGraphic->container[location] = &UnitPointer->Type50.AttackGraphic;
					Units_DisplayedMeleeArmour->container[location] = &UnitPointer->Type50.DisplayedMeleeArmour;
					Units_DisplayedAttack->container[location] = &UnitPointer->Type50.DisplayedAttack;
					Units_DisplayedRange->container[location] = &UnitPointer->Type50.DisplayedRange;
					Units_ReloadTime2->container[location] = &UnitPointer->Type50.DisplayedReloadTime;
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
					if(GenieVersion >= genie::GV_AoKB)
					{
						for(short loop = 0; loop < Units_Unknown16B.size(); ++loop)
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
			Units_HillMode->container[location] = &UnitPointer->HillMode;
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
				Units_SelectionMask->container[location] = &UnitPointer->SelectionMask;
				Units_SelectionShapeType->container[location] = &UnitPointer->SelectionShapeType;
				Units_SelectionShape->container[location] = &UnitPointer->SelectionShape;
				Units_ID3->container[location] = &UnitPointer->ID3;
				if(GenieVersion >= genie::GV_AoKB)
				{
					if(CopyGraphics || vecCiv == 0)
					Units_StandingGraphic[1]->container[location] = &UnitPointer->StandingGraphic.second;
					if(GenieVersion >= genie::GV_AoK)
					{
						Units_Disabled->container[location] = &UnitPointer->Disabled;
						if(GenieVersion >= genie::GV_TC)
						{
							Units_Attribute->container[location] = &UnitPointer->Attribute;
							Units_Civ->container[location] = &UnitPointer->Civilization;
							Units_Unknown9->container[location] = &UnitPointer->Nothing;
							if(GenieVersion >= genie::GV_SWGB)
							{
								Units_Name2->container[location] = &UnitPointer->Name2;
								Units_Unitline->container[location] = &UnitPointer->Unitline;
								Units_MinTechLevel->container[location] = &UnitPointer->MinTechLevel;
							}
						}
					}
				}
			}
			Units_Enabled->container[location] = &UnitPointer->Enabled;
			Units_CommandAttribute->container[location] = &UnitPointer->CommandAttribute;
			Units_Unknown3A->container[location] = &UnitPointer->Unknown3A;
			Units_MinimapColor->container[location] = &UnitPointer->MinimapColor;
			Units_LanguageDLLHelp->container[location] = &UnitPointer->LanguageDLLHelp;
			Units_LanguageDLLHotKeyText->container[location] = &UnitPointer->LanguageDLLHotKeyText;
			Units_HotKey->container[location] = &UnitPointer->HotKey;
			Units_Unselectable->container[location] = &UnitPointer->Unselectable;
			Units_Unknown6->container[location] = &UnitPointer->Unknown6;
			Units_Unknown7->container[location] = &UnitPointer->UnknownSelectionMode;
			Units_Unknown8->container[location] = &UnitPointer->Unknown8;
			Units_SelectionRadius[0]->container[location] = &UnitPointer->SelectionRadius.first;
			Units_SelectionRadius[1]->container[location] = &UnitPointer->SelectionRadius.second;
			Units_HPBarHeight2->container[location] = &UnitPointer->HPBarHeight2;
			Units_SelectionSound->container[location] = &UnitPointer->SelectionSound;
			Units_DyingSound->container[location] = &UnitPointer->DyingSound;
			Units_AttackMode->container[location] = &UnitPointer->AttackMode;
			Units_EdibleMeat->container[location] = &UnitPointer->EdibleMeat;
			Units_Name->container[location] = &UnitPointer->Name;
			Units_ID2->container[location] = &UnitPointer->ID2;
			for(short loop = 0; loop < 3; ++loop)
			{
				ResourceStorage_Type[loop]->container[location] = &UnitPointer->ResourceStorages[loop].Type;
				ResourceStorage_Amount[loop]->container[location] = &UnitPointer->ResourceStorages[loop].Amount;
				ResourceStorage_Enabled[loop]->container[location] = &UnitPointer->ResourceStorages[loop].Enabled;
			}

			//if(UnitType == 60)
			{
				Units_StretchMode->container[location] = &UnitPointer->Projectile.StretchMode;
				Units_CompensationMode->container[location] = &UnitPointer->Projectile.CompensationMode;
				Units_DropAnimationMode->container[location] = &UnitPointer->Projectile.DropAnimationMode;
				Units_PenetrationMode->container[location] = &UnitPointer->Projectile.PenetrationMode;
				Units_Unknown24->container[location] = &UnitPointer->Projectile.Unknown24;
				Units_ProjectileArc->container[location] = &UnitPointer->Projectile.ProjectileArc;
			}
		}
		//locations.Append("\n");
	}
	//wxMessageBox(locations);
	SetStatusText("Civilization: "+lexical_cast<string>(UnitCivID)+"    Selections: "+lexical_cast<string>(selections)+"    Selected unit: "+lexical_cast<string>(UnitIDs[0]), 0);

	Units_Type->Update();
	switch(UnitType)
	{
		case 10: Units_Type_ComboBox->SetSelection(1); break;
		case 15: Units_Type_ComboBox->SetSelection(2); break;
		case 20: Units_Type_ComboBox->SetSelection(3); break;
		case 25: Units_Type_ComboBox->SetSelection(4); break;
		case 30: Units_Type_ComboBox->SetSelection(5); break;
		case 40: Units_Type_ComboBox->SetSelection(6); break;
		case 50: Units_Type_ComboBox->SetSelection(7); break;
		case 60: Units_Type_ComboBox->SetSelection(8); break;
		case 70: Units_Type_ComboBox->SetSelection(9); break;
		case 80: Units_Type_ComboBox->SetSelection(10); break;
		case 90: Units_Type_ComboBox->SetSelection(11); break;
		default: Units_Type_ComboBox->SetSelection(0);
	}

	switch(UnitType) // Enable editing
	{
		case 80:
		{
			Units_ConstructionGraphicID->Enable(true);
			Units_ConstructionGraphicID_ComboBox->Enable(true);
			Units_SnowGraphicID->Enable(true);
			Units_SnowGraphicID_ComboBox->Enable(true);
			Units_AdjacentMode->Enable(true);
			Units_AdjacentMode_CheckBox->Enable(true);
			Units_IconDisabler->Enable(true);
			Units_DisappearsWhenBuilt->Enable(true);
			Units_Unknown31b_CheckBox->Enable(true);
			Units_StackUnitID->Enable(true);
			Units_StackUnitID_ComboBox->Enable(true);
			Units_TerrainID->Enable(true);
			Units_TerrainID_ComboBox->Enable(true);
			Units_OldTerrainLikeID->Enable(true);
			Units_ResearchID->Enable(true);
			Units_ResearchID_ComboBox->Enable(true);
			Units_Unknown33->Enable(true);
			for(short loop = 0; loop < 4; ++loop)
			{
				Units_AnnexUnit[loop]->Enable(true);
				Units_AnnexUnit_ComboBox[loop]->Enable(true);
				for(short loop2 = 0; loop2 < 2; ++loop2)
				Units_AnnexUnitMisplacement[loop][loop2]->Enable(true);
			}
			Units_HeadUnit->Enable(true);
			Units_HeadUnit_ComboBox->Enable(true);
			Units_TransformUnit->Enable(true);
			Units_TransformUnit_ComboBox->Enable(true);
			Units_UnknownSound->Enable(true);
			Units_UnknownSound_ComboBox->Enable(true);
			Units_ConstructionSound->Enable(true);
			Units_ConstructionSound_ComboBox->Enable(true);
			Units_GarrisonType->Enable(true);
			for(short loop = 0; loop < 8; ++loop)
			Units_GarrisonType_CheckBox[loop]->Enable(true);
			Units_GarrisonHealRate->Enable(true);
			Units_Unknown35->Enable(true);
			Units_PileUnit->Enable(true);
			Units_PileUnit_ComboBox->Enable(true);
			for(short loop = 0; loop < Units_LootSwitch.size(); ++loop)
			Units_LootSwitch[loop]->Enable(true);

			Units_ConstructionGraphicID->Update();
			Units_AdjacentMode->Update();
			Units_IconDisabler->Update();
			Units_DisappearsWhenBuilt->Update();
			Units_StackUnitID->Update();
			Units_TerrainID->Update();
			Units_OldTerrainLikeID->Update();
			Units_ResearchID->Update();
			if(GenieVersion >= genie::GV_AoKA)
			{
				if(GenieVersion >= genie::GV_TC)
				{
					Units_SnowGraphicID->Update();
				}
				Units_Unknown33->Update();
				for(short loop = 0; loop < 4; ++loop)
				{
					Units_AnnexUnit[loop]->Update();
					Units_AnnexUnitMisplacement[loop][0]->Update();
					Units_AnnexUnitMisplacement[loop][1]->Update();
				}
				Units_HeadUnit->Update();
				Units_TransformUnit->Update();
				Units_UnknownSound->Update();
				Units_GarrisonType->Update();
				Units_GarrisonType_CheckBox[0]->SetValue(UnitPointer->Building.GarrisonType & 0x01);
				Units_GarrisonType_CheckBox[1]->SetValue(UnitPointer->Building.GarrisonType & 0x02);
				Units_GarrisonType_CheckBox[2]->SetValue(UnitPointer->Building.GarrisonType & 0x04);
				Units_GarrisonType_CheckBox[3]->SetValue(UnitPointer->Building.GarrisonType & 0x08);
				Units_GarrisonType_CheckBox[4]->SetValue(UnitPointer->Building.GarrisonType & 0x10);
				Units_GarrisonType_CheckBox[5]->SetValue(UnitPointer->Building.GarrisonType & 0x20);
				Units_GarrisonType_CheckBox[6]->SetValue(UnitPointer->Building.GarrisonType & 0x40);
				Units_GarrisonType_CheckBox[7]->SetValue(UnitPointer->Building.GarrisonType & 0x80);
				Units_GarrisonHealRate->Update();
				Units_Unknown35->Update();
				Units_PileUnit->Update();
				for(short loop = 0; loop < Units_LootSwitch.size(); ++loop)
				Units_LootSwitch[loop]->Update();
			}
			Units_ConstructionSound->Update();
		}
		case 70:
		{
			for(short loop = 0; loop < 3; ++loop)
			{
				Units_CostType[loop]->Enable(true);
				Units_CostType_ComboBox[loop]->Enable(true);
				Units_CostAmount[loop]->Enable(true);
				Units_CostUsed[loop]->Enable(true);
				Units_CostUsed_CheckBox[loop]->Enable(true);
				Units_AttackMissileDuplicationSpawning[loop]->Enable(true);
			}
			Units_GarrisonGraphic->Enable(true);
			Units_GarrisonGraphic_ComboBox->Enable(true);
			Units_TrainTime->Enable(true);
			Units_TrainLocationID->Enable(true);
			Units_TrainLocationID_ComboBox->Enable(true);
			Units_ButtonID->Enable(true);
			Units_Unknown26->Enable(true);
			Units_Unknown27->Enable(true);
			Units_Unknown28->Enable(true);
			Units_HeroMode->Enable(true);
			Units_HeroMode_CheckBox->Enable(true);
			Units_AttackMissileDuplicationAmount1->Enable(true);
			Units_AttackMissileDuplicationAmount2->Enable(true);
			Units_AttackMissileDuplicationUnit->Enable(true);
			Units_AttackMissileDuplicationUnit_ComboBox->Enable(true);
			Units_ChargingGraphic->Enable(true);
			Units_ChargingGraphic_ComboBox->Enable(true);
			Units_ChargingMode->Enable(true);
			Units_DisplayedPierceArmour->Enable(true);

			for(short loop = 0; loop < 3; ++loop)
			{
				Units_CostType[loop]->Update();
				Units_CostAmount[loop]->Update();
				Units_CostUsed[loop]->Update();
			}
			Units_TrainTime->Update();
			Units_TrainLocationID->Update();
			Units_ButtonID->Update();
			if(GenieVersion >= genie::GV_AoKA)
			{
				Units_Unknown26->Update();
				Units_Unknown27->Update();
				Units_Unknown28->Update();
				if(GenieVersion >= genie::GV_AoKB)
				{
					Units_HeroMode->Update();
					Units_GarrisonGraphic->Update();
				}
				Units_AttackMissileDuplicationAmount1->Update();
				Units_AttackMissileDuplicationAmount2->Update();
				for(short loop = 0; loop < 3; ++loop)
				{
					Units_AttackMissileDuplicationSpawning[loop]->Update();
				}
				Units_AttackMissileDuplicationUnit->Update();
				Units_ChargingGraphic->Update();
				Units_ChargingMode->Update();
			}
			Units_DisplayedPierceArmour->Update();
		}
		case 60:
		case 50:
		{
			Units_DefaultArmor->Enable(true);
			Units_TerRestrictionForDmgMultiply->Enable(true);
			Units_TerRestrictionForDmgMultiply_ComboBox->Enable(true);
			Units_MaxRange->Enable(true);
			Units_BlastRadius->Enable(true);
			Units_ReloadTime1->Enable(true);
			Units_ProjectileUnitID->Enable(true);
			Units_ProjectileUnitID_ComboBox->Enable(true);
			Units_AccuracyPercent->Enable(true);
			Units_TowerMode->Enable(true);
			Units_TowerMode_CheckBox->Enable(true);
			Units_Delay->Enable(true);
			for(short loop = 0; loop < 4; ++loop)
			Units_GraphicDisplacement[loop]->Enable(true);
			Units_BlastLevel->Enable(true);
			Units_MinRange->Enable(true);
			Units_AccuracyErrorRadius->Enable(true);
			Units_AttackGraphic->Enable(true);
			Units_AttackGraphic_ComboBox->Enable(true);
			Units_DisplayedMeleeArmour->Enable(true);
			Units_DisplayedAttack->Enable(true);
			Units_DisplayedRange->Enable(true);
			Units_ReloadTime2->Enable(true);

			Attacks_Class->Enable(true);
			for(short loop = 0; loop < 2; ++loop)
			Attacks_Class_ComboBox[loop]->Enable(true);
			Attacks_Amount->Enable(true);
			Armors_Class->Enable(true);
			Armors_Amount->Enable(true);

			Units_DefaultArmor->Update();
			Units_TerRestrictionForDmgMultiply->Update();
			Units_MaxRange->Update();
			Units_BlastRadius->Update();
			Units_ReloadTime1->Update();
			Units_ProjectileUnitID->Update();
			Units_AccuracyPercent->Update();
			Units_TowerMode->Update();
			Units_Delay->Update();
			for(short loop = 0; loop < 3; ++loop)
			{
				Units_GraphicDisplacement[loop]->Update();
			}
			Units_BlastLevel->Update();
			Units_MinRange->Update();
			if(GenieVersion >= genie::GV_AoKB)
			{
				Units_AccuracyErrorRadius->Update();
			}
			Units_AttackGraphic->Update();
			Units_DisplayedMeleeArmour->Update();
			Units_DisplayedAttack->Update();
			Units_DisplayedRange->Update();
			Units_ReloadTime2->Update();
		}
		case 40:
		{
			Units_SheepConversion->Enable(true);
			Units_SheepConversion_CheckBox->Enable(true);
			Units_SearchRadius->Enable(true);
			Units_WorkRate->Enable(true);
			for(short loop = 0; loop < 2; ++loop)
			{
				Units_DropSite[loop]->Enable(true);
				Units_DropSite_ComboBox[loop]->Enable(true);
			}
			Units_VillagerMode->Enable(true);
			Units_AttackSound->Enable(true);
			Units_AttackSound_ComboBox->Enable(true);
			Units_MoveSound->Enable(true);
			Units_MoveSound_ComboBox->Enable(true);
			Units_AnimalMode->Enable(true);
			Units_AnimalMode_CheckBox->Enable(true);

			Units_SheepConversion->Update();
			Units_SearchRadius->Update();
			Units_WorkRate->Update();
			Units_DropSite[0]->Update();
			Units_DropSite[1]->Update();
			Units_VillagerMode->Update();
			Units_AttackSound->Update();
			Units_MoveSound->Update();
			Units_AnimalMode->Update();
		}
		case 30:
		{
			for(short loop = 0; loop < 2; ++loop)
			{
				Units_WalkingGraphic[loop]->Enable(true);
				Units_WalkingGraphic_ComboBox[loop]->Enable(true);
			}
			Units_RotationSpeed->Enable(true);
			Units_Unknown11->Enable(true);
			Units_TrackingUnit->Enable(true);
			Units_TrackingUnit_ComboBox->Enable(true);
			Units_TrackingUnitUsed->Enable(true);
			Units_TrackingUnitDensity->Enable(true);
			Units_Unknown16->Enable(true);
			for(short loop = 0; loop < Units_Unknown16B.size(); ++loop)
			Units_Unknown16B[loop]->Enable(true);

			Units_WalkingGraphic[0]->Update();
			Units_WalkingGraphic[1]->Update();
			Units_RotationSpeed->Update();
			Units_Unknown11->Update();
			Units_TrackingUnit->Update();
			Units_TrackingUnitUsed->Update();
			Units_TrackingUnitDensity->Update();
			Units_Unknown16->Update();
			if(GenieVersion >= genie::GV_AoKB)
			{
				for(short loop = 0; loop < Units_Unknown16B.size(); ++loop)
				{
					Units_Unknown16B[loop]->Update();
				}
			}
		}
		case 25:
		case 20:
		{
			Units_Speed->Enable(true);
			Units_Speed->Update();
		}
		case 90:
		case 15:
		case 10:
		{
			Units_ID1->Update();
			Units_LanguageDLLName->Update();
			Units_DLL_LanguageName->index = UnitPointer->LanguageDLLName;
			Units_DLL_LanguageName->SetLabel(LangDLLstring(UnitPointer->LanguageDLLName, 64));
			Units_LanguageDLLCreation->Update();
			Units_DLL_LanguageCreation->index = UnitPointer->LanguageDLLCreation;
			Units_DLL_LanguageCreation->SetLabel(LangDLLstring(UnitPointer->LanguageDLLCreation, 64));
			Units_Class->Update();
			Units_StandingGraphic[0]->Update();
			Units_DyingGraphic[0]->Update();
			Units_DyingGraphic[1]->Update();
			Units_DeathMode->Update();
			Units_HitPoints->Update();
			Units_LineOfSight->Update();
			Units_GarrisonCapacity->Update();
			Units_SizeRadius[0]->Update();
			Units_SizeRadius[1]->Update();
			Units_HPBarHeight1->Update();
			Units_TrainSound[0]->Update();
			Units_DeadUnitID->Update();
			Units_PlacementMode->Update();
			Units_AirMode->Update();
			Units_IconID->Update();
			Units_HideInEditor->Update();
			Units_Unknown1->Update();
			Units_Enabled->Update();
			Units_PlacementBypassTerrain[0]->Update();
			Units_PlacementBypassTerrain[1]->Update();
			Units_PlacementTerrain[0]->Update();
			Units_PlacementTerrain[1]->Update();
			Units_EditorRadius[0]->Update();
			Units_EditorRadius[1]->Update();
			Units_HillMode->Update();
			Units_VisibleInFog->Update();
			Units_TerrainRestriction->Update();
			Units_FlyMode->Update();
			Units_ResourceCapacity->Update();
			Units_ResourceDecay->Update();
			Units_BlastType->Update();
			Units_Unknown2->Update();
			Units_InteractionMode->Update();
			Units_MinimapMode->Update();
			Units_SelectionEffect->Update();
			Units_EditorSelectionColour->Update();
			if(GenieVersion >= genie::GV_AoKA)
			{
				Units_DLL_LanguageHelp->index = UnitPointer->LanguageDLLHelp - 79000;
				Units_DLL_LanguageHKText->index = UnitPointer->LanguageDLLHotKeyText - 140000;
				Units_TrainSound[1]->Update();
				Units_SelectionMask->Update();
				Units_SelectionShapeType->Update();
				Units_SelectionShape->Update();
				Units_ID3->Update();
				if(GenieVersion >= genie::GV_AoKB)
				{
					Units_StandingGraphic[1]->Update();
					if(GenieVersion >= genie::GV_AoK)
					{
						Units_Disabled->Update();
						if(GenieVersion >= genie::GV_TC)
						{
							Units_Attribute->Update();
							Units_Attribute_CheckBox[0]->SetValue(UnitPointer->Attribute & 0x01);
							Units_Attribute_CheckBox[1]->SetValue(UnitPointer->Attribute & 0x02);
							Units_Attribute_CheckBox[2]->SetValue(UnitPointer->Attribute & 0x04);
							Units_Attribute_CheckBox[3]->SetValue(UnitPointer->Attribute & 0x08);
							Units_Attribute_CheckBox[4]->SetValue(UnitPointer->Attribute & 0x10);
							Units_Attribute_CheckBox[5]->SetValue(UnitPointer->Attribute & 0x20);
							Units_Attribute_CheckBox[6]->SetValue(UnitPointer->Attribute & 0x40);
							Units_Attribute_CheckBox[7]->SetValue(UnitPointer->Attribute & 0x80);
							Units_Civ->Update();
							Units_Unknown9->Update();
							if(GenieVersion >= genie::GV_SWGB)
							{
								Units_Name2->Update();
								Units_Unitline->Update();
								Units_MinTechLevel->Update();
							}
						}
					}
				}
			}
			else
			{
				Units_DLL_LanguageHelp->index = (uint16_t)UnitPointer->LanguageDLLHelp;
				Units_DLL_LanguageHKText->index = (uint16_t)UnitPointer->LanguageDLLHotKeyText;
			}
			Units_CommandAttribute->Update();
			Units_Unknown3A->Update();
			Units_MinimapColor->Update();
			Units_LanguageDLLHelp->Update();
			Units_DLL_LanguageHelp->SetLabel(LangDLLstring(Units_DLL_LanguageHelp->index, 512));
			Units_LanguageDLLConverter[0]->SetLabel(lexical_cast<string>(Units_DLL_LanguageHelp->index));
			Units_LanguageDLLHotKeyText->Update();
			Units_DLL_LanguageHKText->SetLabel(LangDLLstring(Units_DLL_LanguageHKText->index, 64));
			Units_LanguageDLLConverter[1]->SetLabel(lexical_cast<string>(Units_DLL_LanguageHKText->index));
			Units_HotKey->Update();
			Units_DLL_HotKey4->index = UnitPointer->HotKey;
			Units_DLL_HotKey4->SetLabel(LangDLLstring(UnitPointer->HotKey, 16));
			Units_Unselectable->Update();
			Units_Unknown6->Update();
			Units_Unknown7->Update();
			Units_Unknown8->Update();
			Units_SelectionRadius[0]->Update();
			Units_SelectionRadius[1]->Update();
			Units_HPBarHeight2->Update();
			Units_SelectionSound->Update();
			Units_DyingSound->Update();
			Units_AttackMode->Update();
			Units_EdibleMeat->Update();
			Units_Name->Update();
			Units_ID2->Update();
			for(short loop = 0; loop < 3; ++loop)
			{
				ResourceStorage_Type[loop]->Update();
				ResourceStorage_Amount[loop]->Update();
				ResourceStorage_Enabled[loop]->Update();
			}
		}
	}

	bool show = GenieFile->Civs[UnitCivID].UnitPointers[UnitIDs[0]] != 0;
	Units_Type->Enable(show);
	Units_Type_ComboBox->Enable(show);
	Units_LanguageDLLName->Enable(show);
	Units_DLL_LanguageName->Enable(show);
	Units_LanguageDLLCreation->Enable(show);
	Units_DLL_LanguageCreation->Enable(show);
	Units_Class->Enable(show);
	Units_Class_ComboBox[0]->Enable(show);
	Units_StandingGraphic[0]->Enable(show);
	Units_StandingGraphic_ComboBox[0]->Enable(show);
	Units_DyingGraphic[0]->Enable(show);
	Units_DyingGraphic[1]->Enable(show);
	Units_DyingGraphic_ComboBox[0]->Enable(show);
	Units_DyingGraphic_ComboBox[1]->Enable(show);
	Units_DeathMode->Enable(show);
	Units_DeathMode_CheckBox->Enable(show);
	Units_HitPoints->Enable(show);
	Units_LineOfSight->Enable(show);
	Units_GarrisonCapacity->Enable(show);
	Units_SizeRadius[0]->Enable(show);
	Units_SizeRadius[1]->Enable(show);
	Units_HPBarHeight1->Enable(show);
	Units_TrainSound[0]->Enable(show);
	Units_TrainSound_ComboBox[0]->Enable(show);
	Units_DeadUnitID->Enable(show);
	Units_DeadUnitID_ComboBox->Enable(show);
	Units_PlacementMode->Enable(show);
	Units_AirMode->Enable(show);
	Units_AirMode_CheckBox->Enable(show);
	Units_IconID->Enable(show);
	Units_HideInEditor->Enable(show);
	Units_HideInEditor_CheckBox->Enable(show);
	Units_Unknown1->Enable(show);
	Units_Enabled->Enable(show);
	Units_Enabled_CheckBox->Enable(show);
	Units_PlacementBypassTerrain[0]->Enable(show);
	Units_PlacementBypassTerrain[1]->Enable(show);
	Units_PlacementBypassTerrain_ComboBox[0]->Enable(show);
	Units_PlacementBypassTerrain_ComboBox[1]->Enable(show);
	Units_PlacementTerrain[0]->Enable(show);
	Units_PlacementTerrain[1]->Enable(show);
	Units_PlacementTerrain_ComboBox[0]->Enable(show);
	Units_PlacementTerrain_ComboBox[1]->Enable(show);
	Units_EditorRadius[0]->Enable(show);
	Units_EditorRadius[1]->Enable(show);
	Units_HillMode->Enable(show);
	Units_VisibleInFog->Enable(show);
	Units_TerrainRestriction->Enable(show);
	Units_TerrainRestriction_ComboBox->Enable(show);
	Units_FlyMode->Enable(show);
	Units_FlyMode_CheckBox->Enable(show);
	Units_ResourceCapacity->Enable(show);
	Units_ResourceDecay->Enable(show);
	Units_BlastType->Enable(show);
	Units_Unknown2->Enable(show);
	Units_InteractionMode->Enable(show);
	Units_MinimapMode->Enable(show);
	Units_SelectionEffect->Enable(show);
	Units_EditorSelectionColour->Enable(show);
	if(GenieVersion >= genie::GV_AoKA)
	{
		Units_TrainSound[1]->Enable(show);
		Units_TrainSound_ComboBox[1]->Enable(show);
		Units_SelectionMask->Enable(show);
		Units_SelectionShapeType->Enable(show);
		Units_SelectionShape->Enable(show);
		if(GenieVersion >= genie::GV_AoKB)
		{
			Units_StandingGraphic[1]->Enable(show);
			Units_StandingGraphic_ComboBox[1]->Enable(show);
			if(GenieVersion >= genie::GV_AoK)
			{
				Units_Disabled->Enable(show);
				Units_Disabled_CheckBox->Enable(show);
				if(GenieVersion >= genie::GV_TC)
				{
					Units_Attribute->Enable(show);
					Units_Civ->Enable(show);
					Units_Civ_ComboBox->Enable(show);
					Units_Unknown9->Enable(show);
					for(short loop = 0; loop < 8; ++loop)
					Units_Attribute_CheckBox[loop]->Enable(show);
					if(GenieVersion >= genie::GV_SWGB)
					{
						Units_Name2->Enable(show);
						Units_Unitline->Enable(show);
						Units_Unitline_ComboBox->Enable(show);
						Units_MinTechLevel->Enable(show);
						Units_MinTechLevel_ComboBox->Enable(show);
					}
				}
			}
		}
	}
	Units_DLL_LanguageHelp->Enable(show);
	Units_DLL_LanguageHKText->Enable(show);
	Units_CommandAttribute->Enable(show);
	Units_Unknown3A->Enable(show);
	Units_MinimapColor->Enable(show);
	Units_LanguageDLLHelp->Enable(show);
	Units_DLL_LanguageHelp->Enable(show);
	Units_LanguageDLLConverter[0]->Enable(show);
	Units_LanguageDLLHotKeyText->Enable(show);
	Units_DLL_LanguageHKText->Enable(show);
	Units_LanguageDLLConverter[1]->Enable(show);
	Units_HotKey->Enable(show);
	Units_DLL_HotKey4->Enable(show);
	Units_Unselectable->Enable(show);
	Units_Unselectable_CheckBox->Enable(show);
	Units_Unknown6->Enable(show);
	Units_Unknown7->Enable(show);
	Units_Unknown8->Enable(show);
	Units_SelectionRadius[0]->Enable(show);
	Units_SelectionRadius[1]->Enable(show);
	Units_HPBarHeight2->Enable(show);
	Units_SelectionSound->Enable(show);
	Units_SelectionSound_ComboBox->Enable(show);
	Units_DyingSound->Enable(show);
	Units_DyingSound_ComboBox->Enable(show);
	Units_AttackMode->Enable(show);
	Units_EdibleMeat->Enable(show);
	Units_Name->Enable(show);
	for(short loop = 0; loop < 3; ++loop)
	{
		ResourceStorage_Type[loop]->Enable(show);
		ResourceStorage_Type_ComboBox[loop]->Enable(show);
		ResourceStorage_Amount[loop]->Enable(show);
		ResourceStorage_Enabled[loop]->Enable(show);
	}

	switch(UnitType) // Disable editing
	{
		case 10:
		case 15:
		case 90:
		{
			Units_Speed->Enable(false);
			Units_Speed->Clear();
		}
		case 20:
		case 25:
		{
			for(short loop = 0; loop < 2; ++loop)
			{
				Units_WalkingGraphic[loop]->Enable(false);
				Units_WalkingGraphic[loop]->Clear();
				Units_WalkingGraphic_ComboBox[loop]->Enable(false);
				Units_WalkingGraphic_ComboBox[loop]->SetSelection(0);
			}
			Units_RotationSpeed->Enable(false);
			Units_RotationSpeed->Clear();
			Units_Unknown11->Enable(false);
			Units_Unknown11->Clear();
			Units_TrackingUnit->Enable(false);
			Units_TrackingUnit->Clear();
			Units_TrackingUnit_ComboBox->Enable(false);
			Units_TrackingUnit_ComboBox->SetSelection(0);
			Units_TrackingUnitUsed->Enable(false);
			Units_TrackingUnitUsed->Clear();
			Units_TrackingUnitDensity->Enable(false);
			Units_TrackingUnitDensity->Clear();
			Units_Unknown16->Enable(false);
			Units_Unknown16->Clear();
			for(short loop = 0; loop < Units_Unknown16B.size(); ++loop)
			{
				Units_Unknown16B[loop]->Enable(false);
				Units_Unknown16B[loop]->Clear();
			}
		}
		case 30:
		{
			Units_SheepConversion->Enable(false);
			Units_SheepConversion->Clear();
			Units_SheepConversion_CheckBox->Enable(false);
			Units_SheepConversion_CheckBox->SetValue(false);
			Units_SearchRadius->Enable(false);
			Units_SearchRadius->Clear();
			Units_WorkRate->Enable(false);
			Units_WorkRate->Clear();
			for(short loop = 0; loop < 2; ++loop)
			{
				Units_DropSite[loop]->Enable(false);
				Units_DropSite[loop]->Clear();
				Units_DropSite_ComboBox[loop]->Enable(false);
				Units_DropSite_ComboBox[loop]->SetSelection(0);
			}
			Units_VillagerMode->Enable(false);
			Units_VillagerMode->Clear();
			Units_AttackSound->Enable(false);
			Units_AttackSound->Clear();
			Units_AttackSound_ComboBox->Enable(false);
			Units_AttackSound_ComboBox->SetSelection(0);
			Units_MoveSound->Enable(false);
			Units_MoveSound->Clear();
			Units_MoveSound_ComboBox->Enable(false);
			Units_MoveSound_ComboBox->SetSelection(0);
			Units_AnimalMode->Enable(false);
			Units_AnimalMode->Clear();
			Units_AnimalMode_CheckBox->Enable(false);
			Units_AnimalMode_CheckBox->SetValue(false);
		}
		case 40:
		{
			Units_DefaultArmor->Enable(false);
			Units_DefaultArmor->Clear();
			Units_TerRestrictionForDmgMultiply->Enable(false);
			Units_TerRestrictionForDmgMultiply->Clear();
			Units_TerRestrictionForDmgMultiply_ComboBox->Enable(false);
			Units_TerRestrictionForDmgMultiply_ComboBox->SetSelection(0);
			Units_MaxRange->Enable(false);
			Units_MaxRange->Clear();
			Units_BlastRadius->Enable(false);
			Units_BlastRadius->Clear();
			Units_ReloadTime1->Enable(false);
			Units_ReloadTime1->Clear();
			Units_ProjectileUnitID->Enable(false);
			Units_ProjectileUnitID->Clear();
			Units_ProjectileUnitID_ComboBox->Enable(false);
			Units_ProjectileUnitID_ComboBox->SetSelection(0);
			Units_AccuracyPercent->Enable(false);
			Units_AccuracyPercent->Clear();
			Units_TowerMode->Enable(false);
			Units_TowerMode->Clear();
			Units_TowerMode_CheckBox->Enable(false);
			Units_TowerMode_CheckBox->SetValue(false);
			Units_Delay->Enable(false);
			Units_Delay->Clear();
			for(short loop = 0; loop < 3; ++loop)
			{
				Units_GraphicDisplacement[loop]->Enable(false);
				Units_GraphicDisplacement[loop]->Clear();
			}
			Units_BlastLevel->Enable(false);
			Units_BlastLevel->Clear();
			Units_MinRange->Enable(false);
			Units_MinRange->Clear();
			Units_AccuracyErrorRadius->Enable(false);
			Units_AccuracyErrorRadius->Clear();
			Units_AttackGraphic->Enable(false);
			Units_AttackGraphic->Clear();
			Units_AttackGraphic_ComboBox->Enable(false);
			Units_AttackGraphic_ComboBox->SetSelection(0);
			Units_DisplayedMeleeArmour->Enable(false);
			Units_DisplayedMeleeArmour->Clear();
			Units_DisplayedAttack->Enable(false);
			Units_DisplayedAttack->Clear();
			Units_DisplayedRange->Enable(false);
			Units_DisplayedRange->Clear();
			Units_ReloadTime2->Enable(false);
			Units_ReloadTime2->Clear();

			Attacks_Class->Enable(false);
			for(short loop = 0; loop < 2; ++loop)
			Attacks_Class_ComboBox[loop]->Enable(false);
			Attacks_Amount->Enable(false);
			Armors_Class->Enable(false);
			Armors_Amount->Enable(false);
		}
		case 50:
		case 60:
		{
			for(short loop = 0; loop < 3; ++loop)
			{
				Units_CostType[loop]->Enable(false);
				Units_CostType[loop]->Clear();
				Units_CostType_ComboBox[loop]->Enable(false);
				Units_CostType_ComboBox[loop]->SetSelection(0);
				Units_CostAmount[loop]->Enable(false);
				Units_CostAmount[loop]->Clear();
				Units_CostUsed[loop]->Enable(false);
				Units_CostUsed[loop]->Clear();
				Units_CostUsed_CheckBox[loop]->Enable(false);
				Units_CostUsed_CheckBox[loop]->SetValue(false);
				Units_AttackMissileDuplicationSpawning[loop]->Enable(false);
				Units_AttackMissileDuplicationSpawning[loop]->Clear();
			}
			Units_GarrisonGraphic->Enable(false);
			Units_GarrisonGraphic->Clear();
			Units_GarrisonGraphic_ComboBox->Enable(false);
			Units_GarrisonGraphic_ComboBox->SetSelection(0);
			Units_TrainTime->Enable(false);
			Units_TrainTime->Clear();
			Units_TrainLocationID->Enable(false);
			Units_TrainLocationID->Clear();
			Units_TrainLocationID_ComboBox->Enable(false);
			Units_TrainLocationID_ComboBox->SetSelection(0);
			Units_ButtonID->Enable(false);
			Units_ButtonID->Clear();
			Units_Unknown26->Enable(false);
			Units_Unknown26->Clear();
			Units_Unknown27->Enable(false);
			Units_Unknown27->Clear();
			Units_Unknown28->Enable(false);
			Units_Unknown28->Clear();
			Units_HeroMode->Enable(false);
			Units_HeroMode->Clear();
			Units_HeroMode_CheckBox->Enable(false);
			Units_HeroMode_CheckBox->SetValue(false);
			Units_AttackMissileDuplicationAmount1->Enable(false);
			Units_AttackMissileDuplicationAmount1->Clear();
			Units_AttackMissileDuplicationAmount2->Enable(false);
			Units_AttackMissileDuplicationAmount2->Clear();
			Units_AttackMissileDuplicationUnit->Enable(false);
			Units_AttackMissileDuplicationUnit->Clear();
			Units_AttackMissileDuplicationUnit_ComboBox->Enable(false);
			Units_AttackMissileDuplicationUnit_ComboBox->SetSelection(0);
			Units_ChargingGraphic->Enable(false);
			Units_ChargingGraphic->Clear();
			Units_ChargingGraphic_ComboBox->Enable(false);
			Units_ChargingGraphic_ComboBox->SetSelection(0);
			Units_ChargingMode->Enable(false);
			Units_ChargingMode->Clear();
			Units_DisplayedPierceArmour->Enable(false);
			Units_DisplayedPierceArmour->Clear();
		}
		case 70:
		{
			Units_ConstructionGraphicID->Enable(false);
			Units_ConstructionGraphicID->Clear();
			Units_ConstructionGraphicID_ComboBox->Enable(false);
			Units_ConstructionGraphicID_ComboBox->SetSelection(0);
			Units_SnowGraphicID->Enable(false);
			Units_SnowGraphicID->Clear();
			Units_SnowGraphicID_ComboBox->Enable(false);
			Units_SnowGraphicID_ComboBox->SetSelection(0);
			Units_AdjacentMode->Enable(false);
			Units_AdjacentMode->Clear();
			Units_AdjacentMode_CheckBox->Enable(false);
			Units_AdjacentMode_CheckBox->SetValue(false);
			Units_IconDisabler->Enable(false);
			Units_IconDisabler->Clear();
			Units_DisappearsWhenBuilt->Enable(false);
			Units_DisappearsWhenBuilt->Clear();
			Units_Unknown31b_CheckBox->Enable(false);
			Units_Unknown31b_CheckBox->SetValue(false);
			Units_StackUnitID->Enable(false);
			Units_StackUnitID->Clear();
			Units_StackUnitID_ComboBox->Enable(false);
			Units_StackUnitID_ComboBox->SetSelection(0);
			Units_TerrainID->Enable(false);
			Units_TerrainID->Clear();
			Units_TerrainID_ComboBox->Enable(false);
			Units_TerrainID_ComboBox->SetSelection(0);
			Units_OldTerrainLikeID->Enable(false);
			Units_OldTerrainLikeID->Clear();
			Units_ResearchID->Enable(false);
			Units_ResearchID->Clear();
			Units_ResearchID_ComboBox->Enable(false);
			Units_ResearchID_ComboBox->SetSelection(0);
			Units_Unknown33->Enable(false);
			Units_Unknown33->Clear();
			for(short loop = 0; loop < 4; ++loop)
			{
				Units_AnnexUnit[loop]->Enable(false);
				Units_AnnexUnit[loop]->Clear();
				Units_AnnexUnit_ComboBox[loop]->Enable(false);
				Units_AnnexUnit_ComboBox[loop]->SetSelection(0);
				for(short loop2 = 0; loop2 < 2; ++loop2)
				{
					Units_AnnexUnitMisplacement[loop][loop2]->Enable(false);
					Units_AnnexUnitMisplacement[loop][loop2]->Clear();
				}
			}
			Units_HeadUnit->Enable(false);
			Units_HeadUnit->Clear();
			Units_HeadUnit_ComboBox->Enable(false);
			Units_HeadUnit_ComboBox->SetSelection(0);
			Units_TransformUnit->Enable(false);
			Units_TransformUnit->Clear();
			Units_TransformUnit_ComboBox->Enable(false);
			Units_TransformUnit_ComboBox->SetSelection(0);
			Units_UnknownSound->Enable(false);
			Units_UnknownSound->Clear();
			Units_UnknownSound_ComboBox->Enable(false);
			Units_UnknownSound_ComboBox->SetSelection(0);
			Units_ConstructionSound->Enable(false);
			Units_ConstructionSound->Clear();
			Units_ConstructionSound_ComboBox->Enable(false);
			Units_ConstructionSound_ComboBox->SetSelection(0);
			Units_GarrisonType->Enable(false);
			Units_GarrisonType->Clear();
			for(short loop = 0; loop < 8; ++loop)
			{
				Units_GarrisonType_CheckBox[loop]->Enable(false);
				Units_GarrisonType_CheckBox[loop]->SetValue(false);
			}
			Units_GarrisonHealRate->Enable(false);
			Units_GarrisonHealRate->Clear();
			Units_Unknown35->Enable(false);
			Units_Unknown35->Clear();
			Units_PileUnit->Enable(false);
			Units_PileUnit->Clear();
			Units_PileUnit_ComboBox->Enable(false);
			Units_PileUnit_ComboBox->SetSelection(0);
			for(short loop = 0; loop < Units_LootSwitch.size(); ++loop)
			{
				Units_LootSwitch[loop]->Enable(false);
				Units_LootSwitch[loop]->Clear();
			}
		}
	}

	if(UnitType == 60)
	{
		Units_StretchMode->Update();
		Units_CompensationMode->Update();
		Units_DropAnimationMode->Update();
		Units_PenetrationMode->Update();
		Units_Unknown24->Update();
		Units_ProjectileArc->Update();
	}
	else
	{
		Units_StretchMode->Clear();
		Units_CompensationMode->Clear();
		Units_DropAnimationMode->Clear();
		Units_PenetrationMode->Clear();
		Units_Unknown24->Clear();
		Units_ProjectileArc->Clear();
	}
	Units_StretchMode->Enable(UnitType == 60);
	Units_CompensationMode->Enable(UnitType == 60);
	Units_DropAnimationMode->Enable(UnitType == 60);
	Units_PenetrationMode->Enable(UnitType == 60);
	Units_Unknown24->Enable(UnitType == 60);
	Units_ProjectileArc->Enable(UnitType == 60);

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
		Units_Exists->resize(selections);

		genie::UnitHeader * UnitHeadPointer;
		for(auto sel = selections; sel--> 0;)
		{
			UnitHeadPointer = &GenieFile->UnitHeaders[UnitIDs[sel]];

			Units_Exists->container[sel] = &UnitHeadPointer->Exists;
		}

		Units_UnitHeads_Name->SetLabel(" "+lexical_cast<string>(UnitIDs[0])+" - "+GetUnitName(UnitIDs[0], 0));
		Units_Exists->Update();
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
	for(short loop = 0; loop < GenieFile->Civs.size(); ++loop)
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
	auto selections = Units_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion >= genie::GV_AoK)	// AoK, TC, SWGB or CC
	{
		genie::UnitHeader Temp1;
		Temp1.setGameVersion(GenieVersion);
		GenieFile->UnitHeaders.insert(GenieFile->UnitHeaders.begin() + UnitIDs[0], Temp1);
	}

	genie::Unit Temp2;
	Temp2.setGameVersion(GenieVersion);
	for(short loop = 0; loop < GenieFile->Civs.size(); ++loop)
	{
		GenieFile->Civs[loop].Units.insert(GenieFile->Civs[loop].Units.begin() + UnitIDs[0], Temp2);
		GenieFile->Civs[loop].UnitPointers.insert(GenieFile->Civs[loop].UnitPointers.begin() + UnitIDs[0], 1);
		if(EnableIDFix)
		for(short loop2 = UnitIDs[0];loop2 < GenieFile->Civs[0].Units.size(); ++loop2) // ID Fix
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
	auto selections = Units_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion >= genie::GV_AoK)
	{
		for(auto loop = selections; loop--> 0;)
		GenieFile->UnitHeaders.erase(GenieFile->UnitHeaders.begin() + UnitIDs[loop]);
	}

	for(short civ = 0; civ < GenieFile->Civs.size(); ++civ)
	{
		for(auto loop = selections; loop--> 0;)
		{
			GenieFile->Civs[civ].Units.erase(GenieFile->Civs[civ].Units.begin() + UnitIDs[loop]);
			GenieFile->Civs[civ].UnitPointers.erase(GenieFile->Civs[civ].UnitPointers.begin() + UnitIDs[loop]);
		}
		if(EnableIDFix)
		for(short loop = UnitIDs[0]; loop < GenieFile->Civs[0].Units.size(); ++loop) // ID Fix
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
	auto selections = Units_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion < genie::GV_AoK)
	{
		copies->Dat.AllCivs |= 0x08;
	}
	else
	{
		copies->Dat.AllCivs &= ~0x08;
		copies->UnitHeader.resize(selections);
		for(short loop = 0; loop < selections; ++loop)
		copies->UnitHeader[loop] = GenieFile->UnitHeaders[UnitIDs[loop]];
	}

	short CivCount = GenieFile->Civs.size();
	copies->Dat.UnitExists.resize(CivCount);
	if(Units_SpecialCopy_Civs->GetValue()) copies->Dat.AllCivs |= 0x01; else copies->Dat.AllCivs &= ~0x01;
	if(copies->Dat.AllCivs & 0x01)
	{
		copies->Dat.UnitCopies.resize(CivCount);
		for(short civ = 0; civ < CivCount; ++civ)
		{
			copies->Dat.UnitExists[civ].resize(selections);
			copies->Dat.UnitCopies[civ].resize(selections);
			for(short loop = 0; loop < selections; ++loop)
			{
				copies->Dat.UnitExists[civ][loop] = (bool)GenieFile->Civs[civ].UnitPointers[UnitIDs[loop]];
				copies->Dat.UnitCopies[civ][loop] = GenieFile->Civs[civ].Units[UnitIDs[loop]];
			}
		}
	}
	else
	{
		copies->Dat.UnitGraphics.resize(CivCount);
		for(short civ = 0; civ < CivCount; ++civ)
		{
			copies->Dat.UnitExists[civ].resize(selections);
			if(AutoCopy && !CopyGraphics)
			copies->Dat.UnitGraphics[civ].resize(selections);
			for(short loop = 0; loop < selections; ++loop)
			{
				copies->Dat.UnitExists[civ][loop] = (bool)GenieFile->Civs[civ].UnitPointers[UnitIDs[loop]];
				if(AutoCopy && !CopyGraphics)
				{// Let's copy graphics separately.
					// Collects only graphic data, not all data again.
					UnitsGraphicsCopy(copies->Dat.UnitGraphics[civ][loop], civ, UnitIDs[loop]);
				}
			}
		}
		copies->Dat.UnitCopies[0].resize(selections);
		for(short loop = 0; loop < selections; ++loop)
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
		for(short loop = 0; loop < GenieFile->Civs.size(); ++loop)
		Units_CivBoxes[loop]->SetValue(true);
	}
	else if(Event.GetId() == Units_SelectClear->GetId())
	{
		for(short loop = 0; loop < GenieFile->Civs.size(); ++loop)
		Units_CivBoxes[loop]->SetValue(false);
	}
	else if(Event.GetId() == Units_GraphicSet->GetId())
	{
		short Selection = Units_GraphicSet->GetSelection();
		for(short loop = 0; loop < GenieFile->Civs.size(); ++loop)
		{
			if((short)GenieFile->Civs[loop].IconSet == Selection)
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
	auto selections = Units_List->GetSelections(Items);
	if(selections < 1) return;

	GraphicCopies graphics;
	for(short civ = 0; civ < GenieFile->Civs.size(); ++civ)
	{
		if(Units_CivBoxes[civ]->IsChecked() && civ != UnitCivID)
		{
			for(short loop = 0; loop < selections; ++loop)
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
		case 50:
		store.AttackGraphic = GenieFile->Civs[civ].Units[unit].Type50.AttackGraphic;
		case 40:
		case 30:
		store.WalkingGraphic = GenieFile->Civs[civ].Units[unit].DeadFish.WalkingGraphic;
	}
}

void AGE_Frame::OnUnitsSpecialCopy(wxCommandEvent &Event)
{
	auto selections = Units_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Units_SpecialCopy_Civs->GetValue()) copies->Dat.AllCivs |= 0x02; else copies->Dat.AllCivs &= ~0x02;
	if(copies->Dat.AllCivs & 0x02)
	{
		short CivCount = GenieFile->Civs.size();
		copies->Dat.UnitGraphics.resize(CivCount);
		for(short civ = 0; civ < CivCount; ++civ)
		{
			copies->Dat.UnitGraphics[civ].resize(selections);
			for(short loop = 0; loop < selections; ++loop)
			UnitsGraphicsCopy(copies->Dat.UnitGraphics[civ][loop], civ, UnitIDs[loop]);
		}
	}
	else
	{
		copies->Dat.UnitGraphics[0].resize(selections);
		for(short loop = 0; loop < selections; ++loop)
		UnitsGraphicsCopy(copies->Dat.UnitGraphics[0][loop], UnitCivID, UnitIDs[loop]);
	}
}

void AGE_Frame::OnUnitsPaste(wxCommandEvent &Event)
{
	if(Units_List->GetSelections(Items) < 1 || copies->Dat.UnitExists.size() < 1) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion >= genie::GV_AoK)
	{
		if(copies->UnitHeader.size()+UnitIDs[0] > GenieFile->UnitHeaders.size())
		GenieFile->UnitHeaders.resize(copies->UnitHeader.size()+UnitIDs[0]);
		for(short loop = 0; loop < copies->UnitHeader.size(); ++loop)
		{
			copies->UnitHeader[loop].setGameVersion(GenieVersion);
			GenieFile->UnitHeaders[UnitIDs[0]+loop] = copies->UnitHeader[loop];
		}
	}

	if(copies->Dat.UnitCopies[0].size()+UnitIDs[0] > GenieFile->Civs[0].Units.size())
	for(short civ = 0; civ < GenieFile->Civs.size(); ++civ) // Resize if not enough room.
	{
		GenieFile->Civs[civ].Units.resize(copies->Dat.UnitCopies[0].size()+UnitIDs[0]);
		GenieFile->Civs[civ].UnitPointers.resize(copies->Dat.UnitCopies[0].size()+UnitIDs[0]);
	}
	PasteUnits();
	for(short civ = 0; civ < GenieFile->Civs.size(); ++civ)
	{
		for(short loop = 0; loop < copies->Dat.UnitCopies[0].size(); ++loop)
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
	if(Units_List->GetSelections(Items) < 1 || copies->Dat.UnitExists.size() < 1) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion >= genie::GV_AoK)
	{
		genie::UnitHeader Temp1;
		GenieFile->UnitHeaders.insert(GenieFile->UnitHeaders.begin() + UnitIDs[0], copies->UnitHeader.size(), Temp1);
		for(short loop = 0; loop < copies->UnitHeader.size(); ++loop)
		{
			copies->UnitHeader[loop].setGameVersion(GenieVersion);
			GenieFile->UnitHeaders[UnitIDs[0]+loop] = copies->UnitHeader[loop];
		}
	}

	genie::Unit Temp2;
	for(short civ = 0; civ < GenieFile->Civs.size(); ++civ)
	{
		GenieFile->Civs[civ].Units.insert(GenieFile->Civs[civ].Units.begin() + UnitIDs[0], copies->Dat.UnitCopies[0].size(), Temp2);
		GenieFile->Civs[civ].UnitPointers.insert(GenieFile->Civs[civ].UnitPointers.begin() + UnitIDs[0], copies->Dat.UnitCopies[0].size(), 0);
	}
	PasteUnits();
	for(short civ = 0; civ < GenieFile->Civs.size(); ++civ)
	{
		for(short loop = 0; loop < copies->Dat.UnitCopies[0].size(); ++loop)
		{
			GenieFile->Civs[civ].UnitPointers[UnitIDs[0]+loop] = (int32_t)copies->Dat.UnitExists[civ][loop];
		}
		if(EnableIDFix) // ID Fix
		for(short loop = UnitIDs[0];loop < GenieFile->Civs[0].Units.size(); ++loop)
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
		for(short civ = 0; civ < CivCount; ++civ)
		{
			for(short loop = 0; loop < copies->Dat.UnitCopies[0].size(); ++loop) // selections
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
			for(short civ = 0; civ < CivCount; ++civ)
			{
				if(Units_CivBoxes[civ]->IsChecked())
				{
					for(short loop = 0; loop < copies->Dat.UnitCopies[0].size(); ++loop)
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
			for(short loop = 0; loop < copies->Dat.UnitCopies[0].size(); ++loop)
			{
				copies->Dat.UnitCopies[0][loop].setGameVersion(GenieVersion);
				GenieFile->Civs[UnitCivID].Units[UnitIDs[0]+loop] = copies->Dat.UnitCopies[0][loop];
			}
		}
	}
	if(copies->Dat.AllCivs & 0x08) // Paste from AoE to AoK+
	{
		// Paste commands properly
		if(GenieVersion >= genie::GV_AoK)
		{
			if(copies->Dat.AllCivs & 0x01)
			{
				for(short loop = 0; loop < copies->Dat.UnitCopies[0].size(); ++loop)
				{
					for(short civ = 0; civ < copies->Dat.UnitCopies.size(); ++civ)
					{
						if(copies->Dat.UnitExists[civ][loop] != 0)
						{
							GenieFile->UnitHeaders[UnitIDs[0]+loop].Exists = 1;
							GenieFile->UnitHeaders[UnitIDs[0]+loop].Commands = copies->Dat.UnitCopies[civ][loop].Bird.Commands;
							break;
						}
					}
				}
			}
			else
			wxMessageBox("Please select All civs from the bottom!", "Ouch!");
		}
	}
	else if(GenieVersion < genie::GV_AoK) // Paste from AoK+ to AoE
	{
		for(short loop = 0; loop < copies->UnitHeader.size(); ++loop)
		{
			for(short civ = 0; civ < GenieFile->Civs.size(); ++civ)
			{
				if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] != 0)
				GenieFile->Civs[civ].Units[UnitIDs[0]+loop].Bird.Commands = copies->UnitHeader[loop].Commands;
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
		case 50:
		GenieFile->Civs[civ].Units[unit].Type50.AttackGraphic = store.AttackGraphic;
		case 40:
		case 30:
		GenieFile->Civs[civ].Units[unit].DeadFish.WalkingGraphic = store.WalkingGraphic;
	}
}

void AGE_Frame::OnUnitsSpecialPaste(wxCommandEvent &Event)
{
	if(Units_List->GetSelections(Items) < 1) return;

	wxBusyCursor WaitCursor;
	short CopyCount = copies->Dat.UnitGraphics[0].size();
	if(copies->Dat.UnitGraphics[0].size()+UnitIDs[0] > GenieFile->Civs[0].Units.size())
	CopyCount -= copies->Dat.UnitGraphics[0].size()+UnitIDs[0] - GenieFile->Civs[0].Units.size();
	if(copies->Dat.AllCivs & 0x02)
	{
		short CivCount = GenieFile->Civs.size();
		short FillingCiv = (copies->Dat.UnitGraphics.size() > 1) ? 1 : 0;
		copies->Dat.UnitGraphics.resize(CivCount, copies->Dat.UnitGraphics[FillingCiv]);
		for(short civ = 0; civ < CivCount; ++civ)
		{
			for(short loop = 0; loop < CopyCount; ++loop)
			UnitsGraphicsPaste(copies->Dat.UnitGraphics[civ][loop], civ, UnitIDs[0]+loop);
		}
	}
	else
	{
		for(short loop = 0; loop < CopyCount; ++loop)
		UnitsGraphicsPaste(copies->Dat.UnitGraphics[0][loop], UnitCivID, UnitIDs[0]+loop);
	}
	wxCommandEvent E;
	OnUnitsSelect(E);
}

void AGE_Frame::OnUnitsEnable(wxCommandEvent &Event)
{
	auto selections = Units_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	for(short sel = 0; sel < selections; ++sel)
	{
		// Find the correct sizes for subvectors.
		short UnitType = 10, DamageGraphics = 0, Attacks = 0, Armors = 0, Commands = 0;
		for(short civ = 0; civ < GenieFile->Civs.size(); ++civ)
		{
			if(GenieFile->Civs[civ].UnitPointers[UnitIDs[sel]] != 0)
			{
				UnitType = GenieFile->Civs[civ].Units[UnitIDs[sel]].Type;
				DamageGraphics = GenieFile->Civs[civ].Units[UnitIDs[sel]].DamageGraphics.size();
				Attacks = GenieFile->Civs[civ].Units[UnitIDs[sel]].Type50.Attacks.size();
				Armors = GenieFile->Civs[civ].Units[UnitIDs[sel]].Type50.Armours.size();
				if(GenieVersion < genie::GV_AoK)
				Commands = GenieFile->Civs[civ].Units[UnitIDs[sel]].Bird.Commands.size();
				break;
			}
		}
		// All subvectors need to be resized!
		if(Units_SpecialCopy_Civs->GetValue())
		for(short civ = 0; civ < GenieFile->Civs.size(); ++civ)
		{
			if(GenieFile->Civs[civ].UnitPointers[UnitIDs[sel]] == 0)
			{
				GenieFile->Civs[civ].UnitPointers[UnitIDs[sel]] = 1;
				GenieFile->Civs[civ].Units[UnitIDs[sel]].Type = UnitType;
				GenieFile->Civs[civ].Units[UnitIDs[sel]].DamageGraphics.resize(DamageGraphics);
				GenieFile->Civs[civ].Units[UnitIDs[sel]].Type50.Attacks.resize(Attacks);
				GenieFile->Civs[civ].Units[UnitIDs[sel]].Type50.Armours.resize(Armors);
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
				GenieFile->Civs[UnitCivID].Units[UnitIDs[sel]].Type50.Attacks.resize(Attacks);
				GenieFile->Civs[UnitCivID].Units[UnitIDs[sel]].Type50.Armours.resize(Armors);
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
	auto selections = Units_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	for(short sel = 0; sel < selections; ++sel)
	{
		if(Units_SpecialCopy_Civs->GetValue())
		for(short civ = 0; civ < GenieFile->Civs.size(); ++civ)
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

	list<void*> dataPointers;
	wxArrayString filteredNames;

	if(GenieFile->Civs[UnitCivID].UnitPointers[UnitIDs[0]] != 0)
	{
		Units_DamageGraphics_Add->Enable(true);
		for(short loop = 0; loop < GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].DamageGraphics.size(); ++loop)
		{
			wxString Name = " "+FormatInt(loop)+" - "+GetUnitDamageGraphicName(loop);
			if(SearchMatches(Name.Lower()))
			{
				filteredNames.Add(Name);
				dataPointers.push_back((void*)&GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].DamageGraphics[loop]);
			}
		}
	}
	else
	{
		Units_DamageGraphics_Add->Enable(false);
	}
	Listing(Units_DamageGraphics_List, filteredNames, dataPointers);

	wxCommandEvent E;
	OnUnitDamageGraphicsSelect(E);
}

void AGE_Frame::OnUnitDamageGraphicsSelect(wxCommandEvent &Event)
{
	auto selections = Units_DamageGraphics_List->GetSelections(Items);
	if(selections > 0)
	{
		// This and attacks/armors/commands still need a lot of thinking.
		DamageGraphicIDs.resize(selections);
		int PointerCount = (CopyGraphics) ? selections * SelectedCivs.size() : selections;
		DamageGraphics_GraphicID->resize(PointerCount);
		DamageGraphics_DamagePercent->resize(PointerCount);
		DamageGraphics_Unknown1->resize(PointerCount);
		DamageGraphics_Unknown2->resize(PointerCount);

		bool showWarning = false;
		wxString warning = "Damage graphic count of civs\n";
		genie::unit::DamageGraphic * DamageGraphicPointer;
		for(auto sel = selections; sel--> 0;)
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

				int location = sel + vecCiv * selections;
				DamageGraphics_GraphicID->container[location] = &DamageGraphicPointer->GraphicID;
				DamageGraphics_DamagePercent->container[location] = &DamageGraphicPointer->DamagePercent;
				DamageGraphics_Unknown1->container[location] = &DamageGraphicPointer->ApplyMode;
				DamageGraphics_Unknown2->container[location] = &DamageGraphicPointer->Unknown2;
			}
		}
		if(showWarning)
		{
			warning.Append("\ndiffers from civ "+lexical_cast<string>(UnitCivID));
			wxMessageBox(warning);
		}

		DamageGraphics_GraphicID->Update();
		DamageGraphics_DamagePercent->Update();
		DamageGraphics_Unknown1->Update();
		DamageGraphics_Unknown2->Update();
	}
	else
	{
		DamageGraphics_GraphicID->Clear();
		DamageGraphics_GraphicID_ComboBox->SetSelection(0);
		DamageGraphics_DamagePercent->Clear();
		DamageGraphics_Unknown1->Clear();
		DamageGraphics_Unknown2->Clear();
	}
	DamageGraphics_GraphicID->Enable(selections);
	DamageGraphics_GraphicID_ComboBox->Enable(selections);
	DamageGraphics_DamagePercent->Enable(selections);
	DamageGraphics_Unknown1->Enable(selections);
	DamageGraphics_Unknown2->Enable(selections);
}

void AGE_Frame::OnUnitDamageGraphicsAdd(wxCommandEvent &Event)
{
	auto selections = Units_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	genie::unit::DamageGraphic Temp;
	Temp.setGameVersion(GenieVersion);
	for(short loop = 0; loop < GenieFile->Civs.size(); ++loop)
	{
		if(GenieFile->Civs[loop].UnitPointers[UnitIDs[0]] != 0)
		GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics.push_back(Temp);
	}
	Added = true;
	ListUnitDamageGraphics();
}

void AGE_Frame::OnUnitDamageGraphicsInsert(wxCommandEvent &Event)
{
	auto selections = Units_DamageGraphics_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	genie::unit::DamageGraphic Temp;
	Temp.setGameVersion(GenieVersion);
	for(short loop = 0; loop < GenieFile->Civs.size(); ++loop)
	{
		if(GenieFile->Civs[loop].UnitPointers[UnitIDs[0]] != 0)
		GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics.insert(GenieFile->Civs[loop].Units[UnitIDs[0]].DamageGraphics.begin() + DamageGraphicIDs[0], Temp);
	}
	ListUnitDamageGraphics();
}

void AGE_Frame::OnUnitDamageGraphicsDelete(wxCommandEvent &Event)
{
	auto selections = Units_DamageGraphics_List->GetSelections(Items); // Gives the current list selection.
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	for(short civ = 0; civ < GenieFile->Civs.size(); ++civ)
	{
		if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] != 0)
		if(GenieFile->Civs[civ].Units[UnitIDs[0]].DamageGraphics.size())
		for(auto loop = selections; loop--> 0;)
		GenieFile->Civs[civ].Units[UnitIDs[0]].DamageGraphics.erase(GenieFile->Civs[civ].Units[UnitIDs[0]].DamageGraphics.begin() + DamageGraphicIDs[loop]);
	}
	ListUnitDamageGraphics();
}

void AGE_Frame::OnUnitDamageGraphicsCopy(wxCommandEvent &Event)
{
	auto selections = Units_DamageGraphics_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Units_SpecialCopy_Civs->GetValue()) copies->Dat.AllCivs |= 0x10; else copies->Dat.AllCivs &= ~0x10;
	if(copies->Dat.AllCivs & 0x10)
	{
		short CivCount = GenieFile->Civs.size();
		copies->Dat.UnitDamageGraphicExists.resize(CivCount);
		copies->Dat.UnitDamageGraphics.resize(CivCount);
		for(short civ = 0, copy = 0; civ < GenieFile->Civs.size(); ++civ)
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
				copies->Dat.UnitDamageGraphicExists[civ] = 256 + GenieFile->Civs[civ].IconSet;
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
	auto selections = Units_DamageGraphics_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(copies->Dat.AllCivs & 0x10)
	{
		for(short civ = 0, copy = 0; civ < GenieFile->Civs.size(); ++civ)
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
	auto selections = Units_DamageGraphics_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	genie::unit::DamageGraphic Temp;
	if(copies->Dat.AllCivs & 0x10)
	{
		for(short civ = 0, copy = 0; civ < GenieFile->Civs.size(); ++civ)
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
	for(short civ = 0; civ < GenieFile->Civs.size(); ++civ)
	for(short loop=1; loop < UnitIDs.size(); ++loop)
	{
		GenieFile->Civs[civ].Units[UnitIDs[loop]].DamageGraphics = GenieFile->Civs[civ].Units[UnitIDs[0]].DamageGraphics;
	}
}

string AGE_Frame::GetUnitAttackName(short Index)
{
	return "Amount: "+lexical_cast<string>(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type50.Attacks[Index].Amount)
	+" - Class "+lexical_cast<string>(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type50.Attacks[Index].Class)+" ";
}

void AGE_Frame::OnUnitAttacksSearch(wxCommandEvent &Event)
{
	ListUnitAttacks();
}

void AGE_Frame::ListUnitAttacks()
{
	searchText = Units_Attacks_Search->GetValue().Lower();
	excludeText = Units_Attacks_Search_R->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	if(GenieFile->Civs[UnitCivID].UnitPointers[UnitIDs[0]] != 0
	&& GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type >= 50
	&& GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type <= 80)
	{
		Units_Attacks_Add->Enable(true);
		for(short loop = 0; loop < GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type50.Attacks.size(); ++loop)
		{
			wxString Name = " "+FormatInt(loop)+" - "+GetUnitAttackName(loop);
			if(SearchMatches(Name.Lower()))
			{
				filteredNames.Add(Name);
				dataPointers.push_back((void*)&GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type50.Attacks[loop]);
			}
		}
	}
	else
	{
		Units_Attacks_Add->Enable(false);
	}
	Listing(Units_Attacks_List, filteredNames, dataPointers);

	wxCommandEvent E;
	OnUnitAttacksSelect(E);
}

void AGE_Frame::OnUnitAttacksSelect(wxCommandEvent &Event)
{
	auto selections = Units_Attacks_List->GetSelections(Items);
	if(selections > 0)
	{
		AttackIDs.resize(selections);
		int PointerCount = selections * SelectedCivs.size();
		Attacks_Class->resize(PointerCount);
		Attacks_Amount->resize(PointerCount);

		bool showWarning = false;
		wxString warning = "Attack count of civs\n";
		genie::unit::AttackOrArmor * AttackPointer;
		for(auto sel = selections; sel--> 0;)
		{
			AttackPointer = (genie::unit::AttackOrArmor*)Units_Attacks_List->GetClientData(Items.Item(sel));
			AttackIDs[sel] = (AttackPointer - (&GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type50.Attacks[0]));

			for(short vecCiv = SelectedCivs.size(); vecCiv--> 0;)
			{
				if(sel == 0 && GenieFile->Civs[SelectedCivs[vecCiv]].Units[UnitIDs[0]].Type50.Attacks.size() != GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type50.Attacks.size())
				{
					warning.Append(lexical_cast<string>(SelectedCivs[vecCiv])+" ");
					showWarning = true;
				}
				AttackPointer = &GenieFile->Civs[SelectedCivs[vecCiv]].Units[UnitIDs[0]].Type50.Attacks[AttackIDs[sel]];

				int location = sel + vecCiv * selections;
				Attacks_Class->container[location] = &AttackPointer->Class;
				Attacks_Amount->container[location] = &AttackPointer->Amount;
			}
		}
		if(showWarning)
		{
			warning.Append("\ndiffers from civ "+lexical_cast<string>(UnitCivID));
			wxMessageBox(warning);
		}

		Attacks_Class->Update();
		Attacks_Amount->Update();
	}
	else
	{
		Attacks_Class->Clear();
		Attacks_Class_ComboBox[0]->SetSelection(0);
		Attacks_Amount->Clear();
	}
	Attacks_Class->Enable(selections);
	Attacks_Class_ComboBox[0]->Enable(selections);
	Attacks_Amount->Enable(selections);
}

void AGE_Frame::OnUnitAttacksAdd(wxCommandEvent &Event)
{
	auto selections = Units_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	genie::unit::AttackOrArmor Temp;
	Temp.setGameVersion(GenieVersion);
	for(short loop = 0; loop < GenieFile->Civs.size(); ++loop)
	{
		if(GenieFile->Civs[loop].UnitPointers[UnitIDs[0]] != 0)
		GenieFile->Civs[loop].Units[UnitIDs[0]].Type50.Attacks.push_back(Temp);
	}
	Added = true;
	ListUnitAttacks();
}

void AGE_Frame::OnUnitAttacksInsert(wxCommandEvent &Event)
{
	auto selections = Units_Attacks_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	genie::unit::AttackOrArmor Temp;
	Temp.setGameVersion(GenieVersion);
	for(short loop = 0; loop < GenieFile->Civs.size(); ++loop)
	{
		if(GenieFile->Civs[loop].UnitPointers[UnitIDs[0]] != 0)
		GenieFile->Civs[loop].Units[UnitIDs[0]].Type50.Attacks.insert(GenieFile->Civs[loop].Units[UnitIDs[0]].Type50.Attacks.begin() + AttackIDs[0], Temp);
	}
	ListUnitAttacks();
}

void AGE_Frame::OnUnitAttacksDelete(wxCommandEvent &Event)
{
	auto selections = Units_Attacks_List->GetSelections(Items); // Gives the current list selection.
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	for(short civ = 0; civ < GenieFile->Civs.size(); ++civ)
	{
		if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] != 0)
		if(GenieFile->Civs[civ].Units[UnitIDs[0]].Type50.Attacks.size())
		for(auto loop = selections; loop--> 0;)
		GenieFile->Civs[civ].Units[UnitIDs[0]].Type50.Attacks.erase(GenieFile->Civs[civ].Units[UnitIDs[0]].Type50.Attacks.begin() + AttackIDs[loop]);
	}
	ListUnitAttacks();
}

void AGE_Frame::OnUnitAttacksCopy(wxCommandEvent &Event)
{
	auto selections = Units_Attacks_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Units_SpecialCopy_Civs->GetValue()) copies->Dat.AllCivs |= 0x20; else copies->Dat.AllCivs &= ~0x20;
	if(copies->Dat.AllCivs & 0x20)
	{
		short CivCount = GenieFile->Civs.size();
		copies->Dat.UnitAttackExists.resize(CivCount);
		copies->Dat.UnitAttacks.resize(CivCount);
		for(short civ = 0, copy = 0; civ < GenieFile->Civs.size(); ++civ)
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
				copies->Dat.UnitAttackExists[civ] = 256 + GenieFile->Civs[civ].IconSet;
				// Only copy attacks from civs which have this unit enabled.
				CopyFromList(GenieFile->Civs[civ].Units[UnitIDs[0]].Type50.Attacks, AttackIDs, copies->Dat.UnitAttacks[copy]); copy++;
			}
		}
		copies->Dat.UnitAttacks.resize(CivCount);
	}
	else
	{
		CopyFromList(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type50.Attacks, AttackIDs, copies->Dat.UnitAttacks[0]);
	}
}

void AGE_Frame::OnUnitAttacksPaste(wxCommandEvent &Event)
{
	auto selections = Units_Attacks_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(copies->Dat.AllCivs & 0x20)
	{
		for(short civ = 0, copy = 0; civ < GenieFile->Civs.size(); ++civ)
		{
			if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] == 0)
			{
				// Consume copies.
				if(copies->Dat.UnitAttackExists[civ] > 255) copy++; continue;
			}
			// If the target unit exists then choose from following.
			if(copies->Dat.UnitAttackExists[civ] > 255 && copy < copies->Dat.UnitAttacks.size())
			{
				PasteToList(GenieFile->Civs[civ].Units[UnitIDs[0]].Type50.Attacks, AttackIDs[0], copies->Dat.UnitAttacks[copy]); copy++;
			}
			else
			{
				PasteToList(GenieFile->Civs[civ].Units[UnitIDs[0]].Type50.Attacks, AttackIDs[0], copies->Dat.UnitAttacks[0]);
			}
		}
	}
	else
	{
		PasteToList(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type50.Attacks, AttackIDs[0], copies->Dat.UnitAttacks[0]);
	}
	ListUnitAttacks();
}

void AGE_Frame::OnUnitAttacksPasteInsert(wxCommandEvent &Event)
{
	auto selections = Units_Attacks_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(copies->Dat.AllCivs & 0x20)
	{
		for(short civ = 0, copy = 0; civ < GenieFile->Civs.size(); ++civ)
		{
			if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] == 0)
			{
				// Consume copies.
				if(copies->Dat.UnitAttackExists[civ] > 255) copy++; continue;
			}
			// If the target unit exists then choose from following.
			if(copies->Dat.UnitAttackExists[civ] > 255 && copy < copies->Dat.UnitAttacks.size())
			{
				PasteInsertToList(GenieFile->Civs[civ].Units[UnitIDs[0]].Type50.Attacks, AttackIDs[0], copies->Dat.UnitAttacks[copy]); copy++;
			}
			else
			{
				PasteInsertToList(GenieFile->Civs[civ].Units[UnitIDs[0]].Type50.Attacks, AttackIDs[0], copies->Dat.UnitAttacks[0]);
			}
		}
	}
	else
	{
		PasteInsertToList(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type50.Attacks, AttackIDs[0], copies->Dat.UnitAttacks[0]);
	}
	ListUnitAttacks();
}

void AGE_Frame::OnUnitAttacksCopyToUnits(wxCommandEvent &Event)
{
	for(short civ = 0; civ < GenieFile->Civs.size(); ++civ)
	for(short loop=1; loop < UnitIDs.size(); ++loop)
	{
		GenieFile->Civs[civ].Units[UnitIDs[loop]].Type50.Attacks = GenieFile->Civs[civ].Units[UnitIDs[0]].Type50.Attacks;
	}
}

string AGE_Frame::GetUnitArmorName(short Index)
{
	return "Amount: "+lexical_cast<string>(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type50.Armours[Index].Amount)
	+" - Class "+lexical_cast<string>(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type50.Armours[Index].Class)+" ";
}

void AGE_Frame::OnUnitArmorsSearch(wxCommandEvent &Event)
{
	ListUnitArmors();
}

void AGE_Frame::ListUnitArmors()
{
	searchText = Units_Armors_Search->GetValue().Lower();
	excludeText = Units_Armors_Search_R->GetValue().Lower();

	list<void*> dataPointers;
	wxArrayString filteredNames;

	if(GenieFile->Civs[UnitCivID].UnitPointers[UnitIDs[0]] != 0
	&& GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type >= 50
	&& GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type <= 80)
	{
		Units_Armors_Add->Enable(true);
		for(short loop = 0; loop < GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type50.Armours.size(); ++loop)
		{
			wxString Name = " "+FormatInt(loop)+" - "+GetUnitArmorName(loop);
			if(SearchMatches(Name.Lower()))
			{
				filteredNames.Add(Name);
				dataPointers.push_back((void*)&GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type50.Armours[loop]);
			}
		}
	}
	else
	{
		Units_Armors_Add->Enable(false);
	}
	Listing(Units_Armors_List, filteredNames, dataPointers);

	wxCommandEvent E;
	OnUnitArmorsSelect(E);
}

void AGE_Frame::OnUnitArmorsSelect(wxCommandEvent &Event)
{
	auto selections = Units_Armors_List->GetSelections(Items);
	if(selections > 0)
	{
		ArmorIDs.resize(selections);
		int PointerCount = selections * SelectedCivs.size();
		Armors_Class->resize(PointerCount);
		Armors_Amount->resize(PointerCount);

		bool showWarning = false;
		wxString warning = "Armor count of civs\n";
		genie::unit::AttackOrArmor * ArmorPointer;
		for(auto sel = selections; sel--> 0;)
		{
			ArmorPointer = (genie::unit::AttackOrArmor*)Units_Armors_List->GetClientData(Items.Item(sel));
			ArmorIDs[sel] = (ArmorPointer - (&GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type50.Armours[0]));

			for(short vecCiv = SelectedCivs.size(); vecCiv--> 0;)
			{
				if(sel == 0 && GenieFile->Civs[SelectedCivs[vecCiv]].Units[UnitIDs[0]].Type50.Armours.size() != GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type50.Armours.size())
				{
					warning.Append(lexical_cast<string>(SelectedCivs[vecCiv])+" ");
					showWarning = true;
				}
				ArmorPointer = &GenieFile->Civs[SelectedCivs[vecCiv]].Units[UnitIDs[0]].Type50.Armours[ArmorIDs[sel]];

				int location = sel + vecCiv * selections;
				Armors_Class->container[location] = &ArmorPointer->Class;
				Armors_Amount->container[location] = &ArmorPointer->Amount;
			}
		}
		if(showWarning)
		{
			warning.Append("\ndiffers from civ "+lexical_cast<string>(UnitCivID));
			wxMessageBox(warning);
		}

		Armors_Class->Update();
		Armors_Amount->Update();
	}
	else
	{
		Armors_Class->Clear();
		Attacks_Class_ComboBox[1]->SetSelection(0);
		Armors_Amount->Clear();
	}
	Armors_Class->Enable(selections);
	Attacks_Class_ComboBox[1]->Enable(selections);
	Armors_Amount->Enable(selections);
}

void AGE_Frame::OnUnitArmorsAdd(wxCommandEvent &Event)
{
	auto selections = Units_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	genie::unit::AttackOrArmor Temp;
	Temp.setGameVersion(GenieVersion);
	for(short loop = 0; loop < GenieFile->Civs.size(); ++loop)
	{
		if(GenieFile->Civs[loop].UnitPointers[UnitIDs[0]] != 0)
		GenieFile->Civs[loop].Units[UnitIDs[0]].Type50.Armours.push_back(Temp);
	}
	Added = true;
	ListUnitArmors();
}

void AGE_Frame::OnUnitArmorsInsert(wxCommandEvent &Event)
{
	auto selections = Units_Armors_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	genie::unit::AttackOrArmor Temp;
	Temp.setGameVersion(GenieVersion);
	for(short loop = 0; loop < GenieFile->Civs.size(); ++loop)
	{
		if(GenieFile->Civs[loop].UnitPointers[UnitIDs[0]] != 0)
		GenieFile->Civs[loop].Units[UnitIDs[0]].Type50.Armours.insert(GenieFile->Civs[loop].Units[UnitIDs[0]].Type50.Armours.begin() + ArmorIDs[0], Temp);
	}
	ListUnitArmors();
}

void AGE_Frame::OnUnitArmorsDelete(wxCommandEvent &Event)
{
	auto selections = Units_Armors_List->GetSelections(Items); // Gives the current list selection.
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	for(short civ = 0; civ < GenieFile->Civs.size(); ++civ)
	{
		if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] != 0)
		if(GenieFile->Civs[civ].Units[UnitIDs[0]].Type50.Armours.size())
		for(auto loop = selections; loop--> 0;)
		GenieFile->Civs[civ].Units[UnitIDs[0]].Type50.Armours.erase(GenieFile->Civs[civ].Units[UnitIDs[0]].Type50.Armours.begin() + ArmorIDs[loop]);
	}
	ListUnitArmors();
}

void AGE_Frame::OnUnitArmorsCopy(wxCommandEvent &Event)
{
	auto selections = Units_Armors_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Units_SpecialCopy_Civs->GetValue()) copies->Dat.AllCivs |= 0x40; else copies->Dat.AllCivs &= ~0x40;
	if(copies->Dat.AllCivs & 0x40)
	{
		short CivCount = GenieFile->Civs.size();
		copies->Dat.UnitArmorExists.resize(CivCount);
		copies->Dat.UnitArmors.resize(CivCount);
		for(short civ = 0, copy = 0; civ < GenieFile->Civs.size(); ++civ)
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
				copies->Dat.UnitArmorExists[civ] = 256 + GenieFile->Civs[civ].IconSet;
				// Only copy armors from civs which have this unit enabled.
				CopyFromList(GenieFile->Civs[civ].Units[UnitIDs[0]].Type50.Armours, ArmorIDs, copies->Dat.UnitArmors[copy]); copy++;
			}
		}
		copies->Dat.UnitArmors.resize(CivCount);
	}
	else
	{
		CopyFromList(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type50.Armours, ArmorIDs, copies->Dat.UnitArmors[0]);
	}
}

void AGE_Frame::OnUnitArmorsPaste(wxCommandEvent &Event)
{
	auto selections = Units_Armors_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(copies->Dat.AllCivs & 0x40)
	{
		for(short civ = 0, copy = 0; civ < GenieFile->Civs.size(); ++civ)
		{
			if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] == 0)
			{
				// Consume copies.
				if(copies->Dat.UnitArmorExists[civ] > 255) copy++; continue;
			}
			// If the target unit exists then choose from following.
			if(copies->Dat.UnitArmorExists[civ] > 255 && copy < copies->Dat.UnitArmors.size())
			{
				PasteToList(GenieFile->Civs[civ].Units[UnitIDs[0]].Type50.Armours, ArmorIDs[0], copies->Dat.UnitArmors[copy]); copy++;
			}
			else
			{
				PasteToList(GenieFile->Civs[civ].Units[UnitIDs[0]].Type50.Armours, ArmorIDs[0], copies->Dat.UnitArmors[0]);
			}
		}
	}
	else
	{
		PasteToList(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type50.Armours, ArmorIDs[0], copies->Dat.UnitArmors[0]);
	}
	ListUnitArmors();
}

void AGE_Frame::OnUnitArmorsPasteInsert(wxCommandEvent &Event)
{
	auto selections = Units_Armors_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(copies->Dat.AllCivs & 0x40)
	{
		for(short civ = 0, copy = 0; civ < GenieFile->Civs.size(); ++civ)
		{
			if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] == 0)
			{
				// Consume copies.
				if(copies->Dat.UnitArmorExists[civ] > 255) copy++; continue;
			}
			// If the target unit exists then choose from following.
			if(copies->Dat.UnitArmorExists[civ] > 255 && copy < copies->Dat.UnitArmors.size())
			{
				PasteInsertToList(GenieFile->Civs[civ].Units[UnitIDs[0]].Type50.Armours, ArmorIDs[0], copies->Dat.UnitArmors[copy]); copy++;
			}
			else
			{
				PasteInsertToList(GenieFile->Civs[civ].Units[UnitIDs[0]].Type50.Armours, ArmorIDs[0], copies->Dat.UnitArmors[0]);
			}
		}
	}
	else
	{
		PasteInsertToList(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Type50.Armours, ArmorIDs[0], copies->Dat.UnitArmors[0]);
	}
	ListUnitArmors();
}

void AGE_Frame::OnUnitArmorsCopyToUnits(wxCommandEvent &Event)
{
	for(short civ = 0; civ < GenieFile->Civs.size(); ++civ)
	for(short loop=1; loop < UnitIDs.size(); ++loop)
	{
		GenieFile->Civs[civ].Units[UnitIDs[loop]].Type50.Armours = GenieFile->Civs[civ].Units[UnitIDs[0]].Type50.Armours;
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
		CommandSubType = GenieFile->UnitHeaders[UnitIDs[0]].Commands[Index].ResourceProductivityMultiplier;
	}
	else // AoE, RoR
	{
		CommandType = GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Bird.Commands[Index].Type;
		CommandSubType = GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Bird.Commands[Index].ResourceProductivityMultiplier;
	}
	switch(CommandType)
	{
		case 1: return UnitCommands_Type_ComboBox->GetString(1);
		case 2: return UnitCommands_Type_ComboBox->GetString(2);
		case 3: return UnitCommands_Type_ComboBox->GetString(3);
		case 4: return UnitCommands_Type_ComboBox->GetString(4);
		case 5: return UnitCommands_Type_ComboBox->GetString(5);
		case 6: return UnitCommands_Type_ComboBox->GetString(6);
		case 7: return UnitCommands_Type_ComboBox->GetString(7);
		case 8: return UnitCommands_Type_ComboBox->GetString(8);
		case 10: return UnitCommands_Type_ComboBox->GetString(9);
		case 11: return UnitCommands_Type_ComboBox->GetString(10);
		case 12: return UnitCommands_Type_ComboBox->GetString(11);
		case 13: return UnitCommands_Type_ComboBox->GetString(12);
		case 20: return UnitCommands_Type_ComboBox->GetString(13);
		case 21: return UnitCommands_Type_ComboBox->GetString(14);
		case 101: return UnitCommands_Type_ComboBox->GetString(15);
		case 102: return UnitCommands_Type_ComboBox->GetString(16);
		case 103: return UnitCommands_Type_ComboBox->GetString(17);
		case 104: return UnitCommands_Type_ComboBox->GetString(18);
		case 105: return UnitCommands_Type_ComboBox->GetString(19);
		case 106: return UnitCommands_Type_ComboBox->GetString(20);
		case 107: return UnitCommands_Type_ComboBox->GetString(21);
		case 108: return UnitCommands_Type_ComboBox->GetString(22);
		case 109: return UnitCommands_Type_ComboBox->GetString(23);
		case 110: return UnitCommands_Type_ComboBox->GetString(24);
		case 111: return UnitCommands_Type_ComboBox->GetString(25);
		case 120: return UnitCommands_Type_ComboBox->GetString(26);
		case 121: return UnitCommands_Type_ComboBox->GetString(27);
		case 122: return UnitCommands_Type_ComboBox->GetString(28);
		case 123: return UnitCommands_Type_ComboBox->GetString(29);
		case 125: return UnitCommands_Type_ComboBox->GetString(30);
		case 131: return UnitCommands_Type_ComboBox->GetString(31);
		case 132: return UnitCommands_Type_ComboBox->GetString(32);
		case 135: return UnitCommands_Type_ComboBox->GetString(33);
		case 136: return UnitCommands_Type_ComboBox->GetString(34);
		case 149: return UnitCommands_Type_ComboBox->GetString(35);
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

	list<void*> dataPointers;
	wxArrayString filteredNames;

	if(GenieVersion >= genie::GV_AoK)	// AoK, TC, SWGB or CC
	{
		for(short loop = 0; loop < GenieFile->UnitHeaders[UnitIDs[0]].Commands.size(); ++loop)
		{
			wxString Name = " "+FormatInt(loop)+" - "+GetUnitCommandName(loop);
			if(GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop].ClassID != -1)
			Name += " class "+lexical_cast<string>(GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop].ClassID);
			else if(GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop].UnitID != -1)
			Name += " unit "+lexical_cast<string>(GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop].UnitID);
			if(SearchMatches(Name.Lower()))
			{
				filteredNames.Add(Name);
				dataPointers.push_back((void*)&GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop]);
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
			for(short loop = 0; loop < GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Bird.Commands.size(); ++loop)
			{
				wxString Name = " "+FormatInt(loop)+" - "+GetUnitCommandName(loop);
				if(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Bird.Commands[loop].ClassID != -1)
				Name += " class "+lexical_cast<string>(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Bird.Commands[loop].ClassID);
				else if(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Bird.Commands[loop].UnitID != -1)
				Name += " unit "+lexical_cast<string>(GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Bird.Commands[loop].UnitID);
				if(SearchMatches(Name.Lower()))
				{
					filteredNames.Add(Name);
					dataPointers.push_back((void*)&GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Bird.Commands[loop]);
				}
			}
		}
		else
		{
			Units_UnitCommands_Add->Enable(false);
		}
	}
	Listing(Units_UnitCommands_List, filteredNames, dataPointers);

	wxCommandEvent E;
	OnUnitCommandsSelect(E);
}

void AGE_Frame::OnUnitCommandsSelect(wxCommandEvent &Event)
{
	auto selections = Units_UnitCommands_List->GetSelections(Items);
	if(selections > 0)
	{
		CommandIDs.resize(selections);
		int PointerCount = (GenieVersion < genie::GV_AoK) ? selections * SelectedCivs.size() : selections;
		UnitCommands_One->resize(PointerCount);
		UnitCommands_ID->resize(PointerCount);
		UnitCommands_Unknown1->resize(PointerCount);
		UnitCommands_Type->resize(PointerCount);
		UnitCommands_ProductivityResource->resize(PointerCount);
		UnitCommands_ClassID->resize(PointerCount);
		UnitCommands_UnitID->resize(PointerCount);
		UnitCommands_Unknown2->resize(PointerCount);
		UnitCommands_ResourceIn->resize(PointerCount);
		UnitCommands_ResourceOut->resize(PointerCount);
		UnitCommands_Resource->resize(PointerCount);
		UnitCommands_WorkRateMultiplier->resize(PointerCount);
		UnitCommands_ExecutionRadius->resize(PointerCount);
		UnitCommands_ExtraRange->resize(PointerCount);
		UnitCommands_Unknown4->resize(PointerCount);
		UnitCommands_Unknown5->resize(PointerCount);
		UnitCommands_SelectionEnabler->resize(PointerCount);
		UnitCommands_Unknown7->resize(PointerCount);
		UnitCommands_Unknown8->resize(PointerCount);
		UnitCommands_Unknown9->resize(PointerCount);
		UnitCommands_SelectionMode->resize(PointerCount);
		UnitCommands_Unknown11->resize(PointerCount);
		UnitCommands_Unknown12->resize(PointerCount);
		for(short loop = 0; loop < UnitCommands_Graphics.size(); ++loop)
		UnitCommands_Graphics[loop]->resize(PointerCount);

		bool showWarning = false;
		wxString warning = "Command count of civs\n";
		genie::UnitCommand * CommandPointer;
		for(auto sel = selections; sel--> 0;)
		{
			CommandPointer = (genie::UnitCommand*)Units_UnitCommands_List->GetClientData(Items.Item(sel));
			if(GenieVersion < genie::GV_AoK)
			CommandIDs[sel] = (CommandPointer - (&GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].Bird.Commands[0]));
			else
			CommandIDs[sel] = (CommandPointer - (&GenieFile->UnitHeaders[UnitIDs[0]].Commands[0]));

			for(short vecCiv = (GenieVersion < genie::GV_AoK) ? SelectedCivs.size() : 1; vecCiv--> 0;)
			{
				if(GenieVersion < genie::GV_AoK)
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

				int location = sel + vecCiv * selections;
				UnitCommands_One->container[location] = &CommandPointer->One;
				UnitCommands_ID->container[location] = &CommandPointer->ID;
				UnitCommands_Unknown1->container[location] = &CommandPointer->Unknown1;
				UnitCommands_Type->container[location] = &CommandPointer->Type;
				UnitCommands_ClassID->container[location] = &CommandPointer->ClassID;
				UnitCommands_UnitID->container[location] = &CommandPointer->UnitID;
				UnitCommands_Unknown2->container[location] = &CommandPointer->Unknown2;
				UnitCommands_ResourceIn->container[location] = &CommandPointer->ResourceIn;
				UnitCommands_ProductivityResource->container[location] = &CommandPointer->ResourceProductivityMultiplier;
				UnitCommands_ResourceOut->container[location] = &CommandPointer->ResourceOut;
				UnitCommands_Resource->container[location] = &CommandPointer->Resource;
				UnitCommands_WorkRateMultiplier->container[location] = &CommandPointer->WorkRateMultiplier;
				UnitCommands_ExecutionRadius->container[location] = &CommandPointer->ExecutionRadius;
				UnitCommands_ExtraRange->container[location] = &CommandPointer->ExtraRange;
				UnitCommands_Unknown4->container[location] = &CommandPointer->Unknown4;
				UnitCommands_Unknown5->container[location] = &CommandPointer->Unknown5;
				UnitCommands_SelectionEnabler->container[location] = &CommandPointer->SelectionEnabler;
				UnitCommands_Unknown7->container[location] = &CommandPointer->Unknown7;
				UnitCommands_Unknown8->container[location] = &CommandPointer->Unknown8;
				UnitCommands_Unknown9->container[location] = &CommandPointer->Unknown9;
				UnitCommands_SelectionMode->container[location] = &CommandPointer->SelectionMode;
				UnitCommands_Unknown11->container[location] = &CommandPointer->Unknown11;
				UnitCommands_Unknown12->container[location] = &CommandPointer->Unknown12;
				for(short loop = 0; loop < UnitCommands_Graphics.size(); ++loop)
				UnitCommands_Graphics[loop]->container[location] = &CommandPointer->Graphics[loop];
			}
			if(showWarning)
			{
				warning.Append("\ndiffers from civ "+lexical_cast<string>(UnitCivID));
				wxMessageBox(warning);
			}
		}

		UnitCommands_One->Update();
		UnitCommands_ID->Update();
		UnitCommands_Unknown1->Update();
		UnitCommands_Type->Update();
		switch(CommandPointer->Type)
		{
			case 1: UnitCommands_Type_ComboBox->SetSelection(1); break;
			case 2: UnitCommands_Type_ComboBox->SetSelection(2); break;
			case 3: UnitCommands_Type_ComboBox->SetSelection(3); break;
			case 4: UnitCommands_Type_ComboBox->SetSelection(4); break;
			case 5: UnitCommands_Type_ComboBox->SetSelection(5); break;
			case 6: UnitCommands_Type_ComboBox->SetSelection(6); break;
			case 7: UnitCommands_Type_ComboBox->SetSelection(7); break;
			case 8: UnitCommands_Type_ComboBox->SetSelection(8); break;
			case 10: UnitCommands_Type_ComboBox->SetSelection(9); break;
			case 11: UnitCommands_Type_ComboBox->SetSelection(10); break;
			case 12: UnitCommands_Type_ComboBox->SetSelection(11); break;
			case 13: UnitCommands_Type_ComboBox->SetSelection(12); break;
			case 20: UnitCommands_Type_ComboBox->SetSelection(13); break;
			case 21: UnitCommands_Type_ComboBox->SetSelection(14); break;
			case 101: UnitCommands_Type_ComboBox->SetSelection(15); break;
			case 102: UnitCommands_Type_ComboBox->SetSelection(16); break;
			case 103: UnitCommands_Type_ComboBox->SetSelection(17); break;
			case 104: UnitCommands_Type_ComboBox->SetSelection(18); break;
			case 105: UnitCommands_Type_ComboBox->SetSelection(19); break;
			case 106: UnitCommands_Type_ComboBox->SetSelection(20); break;
			case 107: UnitCommands_Type_ComboBox->SetSelection(21); break;
			case 108: UnitCommands_Type_ComboBox->SetSelection(22); break;
			case 109: UnitCommands_Type_ComboBox->SetSelection(23); break;
			case 110: UnitCommands_Type_ComboBox->SetSelection(24); break;
			case 111: UnitCommands_Type_ComboBox->SetSelection(25); break;
			case 120: UnitCommands_Type_ComboBox->SetSelection(26); break;
			case 121: UnitCommands_Type_ComboBox->SetSelection(27); break;
			case 122: UnitCommands_Type_ComboBox->SetSelection(28); break;
			case 123: UnitCommands_Type_ComboBox->SetSelection(29); break;
			case 125: UnitCommands_Type_ComboBox->SetSelection(30); break;
			case 131: UnitCommands_Type_ComboBox->SetSelection(31); break;
			case 132: UnitCommands_Type_ComboBox->SetSelection(32); break;
			case 135: UnitCommands_Type_ComboBox->SetSelection(33); break;
			case 136: UnitCommands_Type_ComboBox->SetSelection(34); break;
			case 149: UnitCommands_Type_ComboBox->SetSelection(35); break;
			default: UnitCommands_Type_ComboBox->SetSelection(0);
		}
		UnitCommands_ClassID->Update();
		UnitCommands_UnitID->Update();
		UnitCommands_Unknown2->Update();
		UnitCommands_ResourceIn->Update();
		UnitCommands_ProductivityResource->Update();
		UnitCommands_ResourceOut->Update();
		UnitCommands_Resource->Update();
		UnitCommands_WorkRateMultiplier->Update();
		UnitCommands_ExecutionRadius->Update();
		UnitCommands_ExtraRange->Update();
		UnitCommands_Unknown4->Update();
		UnitCommands_Unknown5->Update();
		UnitCommands_SelectionEnabler->Update();
		UnitCommands_Unknown7->Update();
		UnitCommands_Unknown8->Update();
		UnitCommands_Unknown9->Update();
		UnitCommands_SelectionMode->Update();
		UnitCommands_Unknown11->Update();
		UnitCommands_Unknown12->Update();
		for(short loop = 0; loop < UnitCommands_Graphics.size(); ++loop)
		{
			UnitCommands_Graphics[loop]->Update();
		}
	}
	else
	{
		UnitCommands_One->Clear();
		UnitCommands_ID->Clear();
		UnitCommands_Unknown1->Clear();
		UnitCommands_Type->Clear();
		UnitCommands_Type_ComboBox->SetSelection(0);
		UnitCommands_ClassID->Clear();
		Units_Class_ComboBox[1]->SetSelection(0);
		UnitCommands_UnitID->Clear();
		UnitCommands_UnitID_ComboBox->SetSelection(0);
		UnitCommands_Unknown2->Clear();
		UnitCommands_ResourceIn->Clear();
		UnitCommands_ResourceIn_ComboBox->SetSelection(0);
		UnitCommands_ProductivityResource->Clear();
		UnitCommands_ProductivityResource_ComboBox->SetSelection(0);
		UnitCommands_ResourceOut->Clear();
		UnitCommands_ResourceOut_ComboBox->SetSelection(0);
		UnitCommands_Resource->Clear();
		UnitCommands_Resource_ComboBox->SetSelection(0);
		UnitCommands_WorkRateMultiplier->Clear();
		UnitCommands_ExecutionRadius->Clear();
		UnitCommands_ExtraRange->Clear();
		UnitCommands_Unknown4->Clear();
		UnitCommands_Unknown5->Clear();
		UnitCommands_SelectionEnabler->Clear();
		UnitCommands_Unknown7->Clear();
		UnitCommands_Unknown8->Clear();
		UnitCommands_Unknown9->Clear();
		UnitCommands_SelectionMode->Clear();
		UnitCommands_Unknown11->Clear();
		UnitCommands_Unknown12->Clear();
		for(short loop = 0; loop < UnitCommands_Graphics.size(); ++loop)
		{
			UnitCommands_Graphics[loop]->Clear();
			UnitCommands_Graphics_ComboBox[loop]->SetSelection(0);
		}
	}
	UnitCommands_One->Enable(selections);
	UnitCommands_Unknown1->Enable(selections);
	UnitCommands_Type->Enable(selections);
	UnitCommands_Type_ComboBox->Enable(selections);
	UnitCommands_ClassID->Enable(selections);
	Units_Class_ComboBox[1]->Enable(selections);
	UnitCommands_UnitID->Enable(selections);
	UnitCommands_UnitID_ComboBox->Enable(selections);
	UnitCommands_Unknown2->Enable(selections);
	UnitCommands_ResourceIn->Enable(selections);
	UnitCommands_ResourceIn_ComboBox->Enable(selections);
	UnitCommands_ProductivityResource->Enable(selections);
	UnitCommands_ProductivityResource_ComboBox->Enable(selections);
	UnitCommands_ResourceOut->Enable(selections);
	UnitCommands_ResourceOut_ComboBox->Enable(selections);
	UnitCommands_Resource->Enable(selections);
	UnitCommands_Resource_ComboBox->Enable(selections);
	UnitCommands_WorkRateMultiplier->Enable(selections);
	UnitCommands_ExecutionRadius->Enable(selections);
	UnitCommands_ExtraRange->Enable(selections);
	UnitCommands_Unknown4->Enable(selections);
	UnitCommands_Unknown5->Enable(selections);
	UnitCommands_SelectionEnabler->Enable(selections);
	UnitCommands_Unknown7->Enable(selections);
	UnitCommands_Unknown8->Enable(selections);
	UnitCommands_Unknown9->Enable(selections);
	UnitCommands_SelectionMode->Enable(selections);
	UnitCommands_Unknown11->Enable(selections);
	UnitCommands_Unknown12->Enable(selections);
	for(short loop = 0; loop < UnitCommands_Graphics.size(); ++loop)
	{
		UnitCommands_Graphics[loop]->Enable(selections);
		UnitCommands_Graphics_ComboBox[loop]->Enable(selections);
	}
}

void AGE_Frame::OnUnitCommandsAdd(wxCommandEvent &Event)
{
	auto selections = Units_List->GetSelections(Items);
	if(selections < 1) return;

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
		for(short loop = 0; loop < GenieFile->Civs.size(); ++loop)
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
	auto selections = Units_UnitCommands_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	genie::UnitCommand Temp;
	Temp.setGameVersion(GenieVersion);
	if(GenieVersion >= genie::GV_AoK)
	{
		GenieFile->UnitHeaders[UnitIDs[0]].Commands.insert(GenieFile->UnitHeaders[UnitIDs[0]].Commands.begin() + CommandIDs[0], Temp);
		if(EnableIDFix)
		for(short loop2 = CommandIDs[0];loop2 < GenieFile->UnitHeaders[UnitIDs[0]].Commands.size(); ++loop2) // ID Fix
		GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].ID = loop2;
	}
	else
	{
		for(short loop = 0; loop < GenieFile->Civs.size(); ++loop)
		{
			if(GenieFile->Civs[loop].UnitPointers[UnitIDs[0]] != 0)
			{
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands.insert(GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands.begin() + CommandIDs[0], Temp);
				if(EnableIDFix)
				for(short loop2 = CommandIDs[0];loop2 < GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands.size(); ++loop2) // ID Fix
				GenieFile->Civs[loop].Units[UnitIDs[0]].Bird.Commands[loop2].ID = loop2;
			}
		}
	}
	ListUnitCommands();
}

void AGE_Frame::OnUnitCommandsDelete(wxCommandEvent &Event)
{
	auto selections = Units_UnitCommands_List->GetSelections(Items); // Gives the current list selection.
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion >= genie::GV_AoK)
	{
		for(auto loop = selections; loop--> 0;)
		GenieFile->UnitHeaders[UnitIDs[0]].Commands.erase(GenieFile->UnitHeaders[UnitIDs[0]].Commands.begin() + CommandIDs[loop]);
		if(EnableIDFix)
		for(short loop2 = CommandIDs[0];loop2 < GenieFile->UnitHeaders[UnitIDs[0]].Commands.size(); ++loop2) // ID Fix
		GenieFile->UnitHeaders[UnitIDs[0]].Commands[loop2].ID = loop2;
	}
	else
	{
		for(short civ = 0; civ < GenieFile->Civs.size(); ++civ)
		{
			if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] != 0)
			if(GenieFile->Civs[civ].Units[UnitIDs[0]].Bird.Commands.size())
			{
				for(auto loop = selections; loop--> 0;)
				GenieFile->Civs[civ].Units[UnitIDs[0]].Bird.Commands.erase(GenieFile->Civs[civ].Units[UnitIDs[0]].Bird.Commands.begin() + CommandIDs[loop]);
				if(EnableIDFix)
				for(short loop2 = CommandIDs[0];loop2 < GenieFile->Civs[0].Units[UnitIDs[0]].Bird.Commands.size(); ++loop2) // ID Fix
				GenieFile->Civs[civ].Units[UnitIDs[0]].Bird.Commands[loop2].ID = loop2;
			}
		}
	}
	ListUnitCommands();
}

void AGE_Frame::OnUnitCommandsCopy(wxCommandEvent &Event)
{
	auto selections = Units_UnitCommands_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion >= genie::GV_AoK)
	{
		copies->Dat.AllCivs |= 0x80;
		copies->Dat.UnitCommandExists.resize(0);
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
		for(short civ = 0, copy = 0; civ < GenieFile->Civs.size(); ++civ)
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
				copies->Dat.UnitCommandExists[civ] = 256 + GenieFile->Civs[civ].IconSet;
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
	auto selections = Units_UnitCommands_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion >= genie::GV_AoK)
	{
		PasteToListIDFix(GenieFile->UnitHeaders[UnitIDs[0]].Commands, CommandIDs[0], copies->Dat.UnitCommands[0]);
	}
	else if(copies->Dat.AllCivs & 0x80)
	{
		for(short civ = 0, copy = 0; civ < GenieFile->Civs.size(); ++civ)
		{
			if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] == 0)
			{
				// Consume copies.
				if(copies->Dat.UnitCommandExists[civ] > 255) copy++; continue;
			}
			// If the target unit exists then choose from following.
			if(copies->Dat.UnitCommandExists.size() > 0 && copies->Dat.UnitCommandExists[civ] > 255 && copy < copies->Dat.UnitCommands.size())
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
	auto selections = Units_UnitCommands_List->GetSelections(Items);
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion >= genie::GV_AoK)
	{
		PasteInsertToListIDFix(GenieFile->UnitHeaders[UnitIDs[0]].Commands, CommandIDs[0], copies->Dat.UnitCommands[0]);
	}
	else if(copies->Dat.AllCivs & 0x80)
	{
		for(short civ = 0, copy = 0; civ < GenieFile->Civs.size(); ++civ)
		{
			if(GenieFile->Civs[civ].UnitPointers[UnitIDs[0]] == 0)
			{
				// Consume copies.
				if(copies->Dat.UnitCommandExists[civ] > 255) copy++; continue;
			}
			// If the target unit exists then choose from following.
			if(copies->Dat.UnitCommandExists.size() > 0 && copies->Dat.UnitCommandExists[civ] > 255 && copy < copies->Dat.UnitCommands.size())
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
	if(GenieVersion < genie::GV_AoK)
	{
		for(short civ = 0; civ < GenieFile->Civs.size(); ++civ)
		for(short loop=1; loop < UnitIDs.size(); ++loop)
		{
			GenieFile->Civs[civ].Units[UnitIDs[loop]].Bird.Commands = GenieFile->Civs[civ].Units[UnitIDs[0]].Bird.Commands;
		}
	}
	else
	{
		for(short loop=1; loop < UnitIDs.size(); ++loop)
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
		if(GenieVersion < genie::GV_AoKA) DLLValue += 0x10000;
		else DLLValue += 79000;
		if(!AutoCopy)
		{
			GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].LanguageDLLHelp = DLLValue;
		}
		else for(short civ = 0; civ < GenieFile->Civs.size(); ++civ)
		{
			GenieFile->Civs[civ].Units[UnitIDs[0]].LanguageDLLHelp = DLLValue;
		}
	}
	else
	{
		if(GenieVersion < genie::GV_AoKA) DLLValue += 0x20000;
		else DLLValue += 140000;
		if(!AutoCopy)
		{
			GenieFile->Civs[UnitCivID].Units[UnitIDs[0]].LanguageDLLHotKeyText = DLLValue;
		}
		else for(short civ = 0; civ < GenieFile->Civs.size(); ++civ)
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
	//Units_Line = new wxStaticLine(Tab_Units, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL, "");
	Units_Special = new wxBoxSizer(wxHORIZONTAL);
	Units_Civs_List = new wxComboBox(Tab_Units, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	Units_Search = new wxTextCtrl(Tab_Units, wxID_ANY);
	Units_UseAnd[0] = new wxCheckBox(Tab_Units, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	Units_Search_R = new wxTextCtrl(Tab_Units, wxID_ANY);
	Units_UseAnd[1] = new wxCheckBox(Tab_Units, wxID_ANY, "And", wxDefaultPosition, wxSize(40, 20));
	Units_FilterSelector = new wxOwnerDrawnComboBox(Tab_Units, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	for(short loop = 0; loop < 2; ++loop)
	{
		Units_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
		Units_SearchFilters[loop] = new wxOwnerDrawnComboBox(Tab_Units, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	}
	Units_List = new wxListBox(Tab_Units, wxID_ANY, wxDefaultPosition, wxSize(200, 100), 0, NULL, wxLB_EXTENDED);
	Units_Buttons[0] = new wxGridSizer(3, 0, 0);
	Units_Buttons[1] = new wxGridSizer(4, 0, 0);
	Units_Add = new wxButton(Tab_Units, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Units_Insert = new wxButton(Tab_Units, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	Units_Delete = new wxButton(Tab_Units, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Units_Copy = new wxButton(Tab_Units, wxID_ANY, "Copy *", wxDefaultPosition, wxSize(5, 20));
	Units_Copy->SetToolTip("When \"All civs\" is not selected,\nthis and pasting works just like automatic copy,\n(from current civilization to selected ones)\ntaking \"Including graphics\" option into account");
	Units_Paste = new wxButton(Tab_Units, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Units_PasteInsert = new wxButton(Tab_Units, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));
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

	Units_FilterSelector->Append("Types 10, 15, 90, 20+");
	Units_FilterSelector->Append("Types 30+");
	Units_FilterSelector->Append("Types 40+");
	Units_FilterSelector->Append("Types 50+");
	Units_FilterSelector->Append("Type 60");
	Units_FilterSelector->Append("Types 70+");
	Units_FilterSelector->Append("Type 80");
	Units_FilterSelector->SetSelection(0);

	Units_DataArea = new wxBoxSizer(wxVERTICAL);
	Units_Top_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_TopGrid_Holder = new wxGridSizer(20, 1, 1);
	Units_AutoCopy = new wxCheckBox(Tab_Units, wxID_ANY, "Automatically", wxDefaultPosition, wxSize(-1, 20));
	Units_CopyTo = new wxButton(Tab_Units, wxID_ANY, "Copy", wxDefaultPosition, wxSize(40, 20));
	Units_CopyGraphics = new wxCheckBox(Tab_Units, wxID_ANY, "Including graphics", wxDefaultPosition, wxSize(-1, 20));
	Units_CopyToText = new wxStaticText(Tab_Units, wxID_ANY, " to selected civilizations: ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Units_SelectAll = new wxButton(Tab_Units, wxID_ANY, "All", wxDefaultPosition, wxSize(40, 20));
	Units_SelectClear = new wxButton(Tab_Units, wxID_ANY, "None", wxDefaultPosition, wxSize(40, 20));
	Units_GraphicSetText = new wxStaticText(Tab_Units, wxID_ANY, " Graphic set: ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Units_GraphicSet = new wxOwnerDrawnComboBox(Tab_Units, wxID_ANY, "", wxDefaultPosition, wxSize(120, 20), 0, NULL, wxCB_READONLY);
	Units_Type_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Tab_Units, "");
	Units_Type_Text = new wxStaticText(Tab_Units, wxID_ANY, "Type ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Type = new TextCtrl_Byte(Tab_Units);
	Units_Type_ComboBox = new wxOwnerDrawnComboBox(Tab_Units, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	Units_Class = new TextCtrl_Short(Tab_Units);
	Units_Class->SetToolTip("Determines many things and works in conjunction with other variables");
	Units_Class_ComboBox[0] = new ComboBox_Plus1(Tab_Units, Units_Class);
	Units_Scroller = new wxScrolledWindow(Tab_Units, wxID_ANY, wxDefaultPosition, wxSize(600, 20), wxVSCROLL | wxTAB_TRAVERSAL);
	Units_ScrollArea = new wxBoxSizer(wxHORIZONTAL);
	Units_ScrollSpace = new wxBoxSizer(wxVERTICAL);
	Units_TypeArea_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Identification");
	Units_LangDLLArea_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Language DLLs");
	Units_GraphicsArea_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Graphics");
	Units_GraphicsArea1_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_GraphicsArea4_Holder = new wxGridSizer(1, 5, 0);
	Units_GraphicsArea5_Holder = new wxGridSizer(4, 0, 5);
	Units_StatsArea_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Statistics");
	Units_StatsArea1_Grid = new wxGridSizer(5, 5, 5);
	Units_StatsAreaGarrison_Grid = new wxGridSizer(4, 5, 5);
	Units_StatsArea2_Grid = new wxGridSizer(4, 5, 5);
	Units_ProjectilesArea_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Projectiles");
	Units_ProjectilesArea1_Grid = new wxGridSizer(5, 5, 5);
	Units_ProjectilesArea2_Grid = new wxGridSizer(4, 5, 5);
	Units_ProjectilesArea3_Grid = new wxGridSizer(4, 5, 5);
	Units_Attributes_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Attributes");
	Units_AttributesBoxes1_Grid = new wxGridSizer(4, 5, 5);
	Units_Attributes1_Grid = new wxGridSizer(4, 0, 5);
	Units_Attributes2_Grid = new wxGridSizer(4, 0, 5);
	Units_AttributesTerrain_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_AttributesTerrain_Grid = new wxGridSizer(4, 5, 5);
	Units_AttributesModes1_Grid = new wxGridSizer(5, 5, 5);
	Units_AttributesDropSite_Holder = new wxBoxSizer(wxVERTICAL);
	Units_AttributesSizes_Holder = new wxGridSizer(3, 0, 5);
	Units_AttributesSelection1_Grid = new wxGridSizer(4, 5, 5);
	Units_LangRegular_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_LangHotKey_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_AttributesTracking_Grid = new wxGridSizer(4, 5, 5);
	Units_AttributesTrain1_Grid = new wxGridSizer(4, 5, 5);
	Units_Attributes3_Grid = new wxGridSizer(4, 5, 5);
	Units_SoundsArea_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Sounds (that only you hear)");
	Units_SoundsArea1_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_SoundsArea2_Grid = new wxGridSizer(4, 5, 5);
	Units_MiscArea_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Miscellaneous");
	Units_HPBars_Grid = new wxGridSizer(4, 5, 5);
	Units_UnknownArea_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Type10plusUnknownArea_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Type 10+ Unknowns (All Units)");
	Units_Type10plusUnknowns_Grid = new wxGridSizer(4, 5, 5);
	Units_Type30plusUnknownArea_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Type 30+ Unknowns (Dead Fish)");
	Units_Type30plusUnknownArea_Grid = new wxGridSizer(4, 5, 5);
	Units_Type70plusUnknownArea_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Type 70+ Unknowns (Creatable)");
	Units_Type70plusUnknownArea_Grid = new wxGridSizer(4, 5, 5);
	Units_Type80plusUnknownArea_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Type 80+ Unknowns (Building)");
	Units_Type80plusUnknownArea_Grid = new wxGridSizer(4, 5, 5);
	Units_CommandsArea_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Actions");

//	Invisible Holder Windows
//	Type 10+

	Units_ID1_Holder = new wxBoxSizer(wxVERTICAL);
	Units_LanguageDLLName_Holder = new wxBoxSizer(wxVERTICAL);
	Units_LanguageDLLCreation_Holder = new wxBoxSizer(wxVERTICAL);
	Units_StandingGraphic_Holder = new wxBoxSizer(wxVERTICAL);
	Units_StandingGraphic_Grid = new wxGridSizer(2, 0, 5);
	Units_DyingGraphic_Holder = new wxBoxSizer(wxVERTICAL);
	Units_DyingGraphic_Grid = new wxGridSizer(2, 0, 5);
	Units_DeathMode_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_HitPoints_Holder = new wxBoxSizer(wxVERTICAL);
	Units_LineOfSight_Holder = new wxBoxSizer(wxVERTICAL);
	Units_GarrisonCapacity_Holder = new wxBoxSizer(wxVERTICAL);
	Units_SizeRadius_Holder = new wxBoxSizer(wxVERTICAL);
	Units_SizeRadius_Grid = new wxGridSizer(2, 0, 0);
	Units_HPBarHeight1_Holder = new wxBoxSizer(wxVERTICAL);
	Units_TrainSound_Holder = new wxBoxSizer(wxVERTICAL);
	Units_TrainSound1_Holder = new wxBoxSizer(wxVERTICAL);
	Units_TrainSound2_Holder = new wxBoxSizer(wxVERTICAL);
	Units_TrainSound3_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_DeadUnitID_Holder = new wxBoxSizer(wxVERTICAL);
	Units_PlacementMode_Holder = new wxBoxSizer(wxVERTICAL);
	Units_AirMode_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_IconID_Holder = new wxBoxSizer(wxVERTICAL);
	Units_IconID_Grid = new wxGridSizer(2, 0, 5);
	Units_HideInEditor_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_Unknown1_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Enabled_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_Disabled_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_PlacementBypassTerrain_Holder = new wxBoxSizer(wxVERTICAL);
	Units_PlacementBypassTerrainGrid_Holder = new wxGridSizer(2, 0, 5);
	Units_PlacementTerrain_Holder = new wxBoxSizer(wxVERTICAL);
	Units_PlacementTerrainGrid_Holder = new wxGridSizer(2, 0, 5);
	Units_EditorRadius_Holder = new wxBoxSizer(wxVERTICAL);
	Units_EditorRadius_Grid = new wxGridSizer(2, 0, 0);
	Units_HillMode_Holder = new wxBoxSizer(wxVERTICAL);
	Units_VisibleInFog_Holder = new wxBoxSizer(wxVERTICAL);
	Units_TerrainRestriction_Holder = new wxBoxSizer(wxVERTICAL);
	Units_FlyMode_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_ResourceCapacity_Holder = new wxBoxSizer(wxVERTICAL);
	Units_ResourceDecay_Holder = new wxBoxSizer(wxVERTICAL);
	Units_BlastType_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Unknown2_Holder = new wxBoxSizer(wxVERTICAL);
	Units_InteractionMode_Holder = new wxBoxSizer(wxVERTICAL);
	Units_MinimapMode_Holder = new wxBoxSizer(wxVERTICAL);
	Units_CommandAttribute_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Unknown3A_Holder = new wxBoxSizer(wxVERTICAL);
	Units_MinimapColor_Holder = new wxBoxSizer(wxVERTICAL);
	Units_LanguageDLLHelp_Holder = new wxBoxSizer(wxVERTICAL);
	Units_LanguageDLLConverter_Holder[0] = new wxBoxSizer(wxVERTICAL);
	Units_LanguageDLLConverter_Holder[1] = new wxBoxSizer(wxVERTICAL);
	Units_LanguageDLLHotKeyText_Holder = new wxBoxSizer(wxVERTICAL);
	Units_HotKey_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Unselectable_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Unknown6_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Unknown7_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Unknown8_Holder = new wxBoxSizer(wxVERTICAL);
	Units_SelectionMask_Holder = new wxBoxSizer(wxVERTICAL);
	Units_SelectionShapeType_Holder = new wxBoxSizer(wxVERTICAL);
	Units_SelectionShape_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Attribute_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Civ_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Unknown9_Holder = new wxBoxSizer(wxVERTICAL);
	Units_SelectionEffect_Holder = new wxBoxSizer(wxVERTICAL);
	Units_EditorSelectionColour_Holder = new wxBoxSizer(wxVERTICAL);
	Units_SelectionRadius_Holder = new wxBoxSizer(wxVERTICAL);
	Units_HPBarHeight2_Holder = new wxBoxSizer(wxVERTICAL);
	Units_ResourceStorageHeader_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Resource Storages");
	Units_ResourceStorage_Grid = new wxGridSizer(3, 0, 5);
	for(short loop = 0; loop < 3; ++loop)
	Units_ResourceStorage_Holder[loop] = new wxBoxSizer(wxHORIZONTAL);
	Units_SelectionSound_Holder = new wxBoxSizer(wxVERTICAL);
	Units_DyingSound_Holder = new wxBoxSizer(wxVERTICAL);
	Units_AttackMode_Holder = new wxBoxSizer(wxVERTICAL);
	Units_EdibleMeat_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Name_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Name2_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Unitline_Holder = new wxBoxSizer(wxVERTICAL);
	Units_MinTechLevel_Holder = new wxBoxSizer(wxVERTICAL);
	Units_ID2_Holder = new wxBoxSizer(wxVERTICAL);
	Units_ID3_Holder = new wxBoxSizer(wxVERTICAL);

//	Type 20+

	Units_Speed_Holder = new wxBoxSizer(wxVERTICAL);

//	Type 30+

	Units_WalkingGraphic_Holder = new wxBoxSizer(wxVERTICAL);
	Units_WalkingGraphic_Grid = new wxGridSizer(2, 0, 5);
	Units_RotationSpeed_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Unknown11_Holder = new wxBoxSizer(wxVERTICAL);
	Units_TrackingUnit_Holder = new wxBoxSizer(wxVERTICAL);
	Units_TrackingUnitUsed_Holder = new wxBoxSizer(wxVERTICAL);
	Units_TrackingUnitUsedBox_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_TrackingUnitDensity_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Unknown16_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Unknown16B_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Unknown16B_Grid = new wxGridSizer(5, 5, 5);

//	Type 40+

	Units_SheepConversion_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_SearchRadius_Holder = new wxBoxSizer(wxVERTICAL);
	Units_WorkRate_Holder = new wxBoxSizer(wxVERTICAL);
	Units_DropSite_Grid = new wxGridSizer(4, 0, 5);
	Units_VillagerMode_Holder = new wxBoxSizer(wxVERTICAL);
	Units_AttackSound_Holder = new wxBoxSizer(wxVERTICAL);
	Units_MoveSound_Holder = new wxBoxSizer(wxVERTICAL);
	Units_AnimalMode_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_Exists_Holder = new wxBoxSizer(wxVERTICAL);

//	Type 50+

	Units_DefaultArmor_Holder = new wxBoxSizer(wxVERTICAL);
	Units_TerRestrictionForDmgMultiply_Holder = new wxBoxSizer(wxVERTICAL);
	Units_MaxRange_Holder = new wxBoxSizer(wxVERTICAL);
	Units_BlastRadius_Holder = new wxBoxSizer(wxVERTICAL);
	Units_ReloadTime1_Holder = new wxBoxSizer(wxVERTICAL);
	Units_ProjectileUnitID_Holder = new wxBoxSizer(wxVERTICAL);
	Units_AccuracyPercent_Holder = new wxBoxSizer(wxVERTICAL);
	Units_TowerMode_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_Delay_Holder = new wxBoxSizer(wxVERTICAL);
	Units_GraphicDisplacement_Holder = new wxBoxSizer(wxVERTICAL);
	Units_GraphicDisplacement_Grid = new wxGridSizer(4, 5, 5);
	Units_BlastLevel_Holder = new wxBoxSizer(wxVERTICAL);
	Units_MinRange_Holder = new wxBoxSizer(wxVERTICAL);
	Units_AccuracyErrorRadius_Holder = new wxBoxSizer(wxVERTICAL);
	Units_AttackGraphic_Holder = new wxBoxSizer(wxVERTICAL);
	Units_DisplayedMeleeArmour_Holder = new wxBoxSizer(wxVERTICAL);
	Units_DisplayedAttack_Holder = new wxBoxSizer(wxVERTICAL);
	Units_DisplayedRange_Holder = new wxBoxSizer(wxVERTICAL);
	Units_ReloadTime2_Holder = new wxBoxSizer(wxVERTICAL);

//	Type 60 only

	Units_StretchMode_Holder = new wxBoxSizer(wxVERTICAL);
	Units_CompensationMode_Holder = new wxBoxSizer(wxVERTICAL);
	Units_DropAnimationMode_Holder = new wxBoxSizer(wxVERTICAL);
	Units_PenetrationMode_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Unknown24_Holder = new wxBoxSizer(wxVERTICAL);
	Units_ProjectileArc_Holder = new wxBoxSizer(wxVERTICAL);

//	Type 70+

	Units_CostHeader_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Costs");
	Units_CostType_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_CostType_Grid = new wxGridSizer(3, 0, 5);
	Units_CostAmount_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_CostUsed_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_TrainTime_Holder = new wxBoxSizer(wxVERTICAL);
	Units_TrainLocationID_Holder = new wxBoxSizer(wxVERTICAL);
	Units_ButtonID_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Unknown26_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Unknown27_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Unknown28_Holder = new wxBoxSizer(wxVERTICAL);
	Units_HeroMode_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_GarrisonGraphic_Holder = new wxBoxSizer(wxVERTICAL);
	Units_GarrisonGraphic_Grid = new wxGridSizer(2, 0, 5);
	Units_AttackMissileDuplicationAmount1_Holder = new wxBoxSizer(wxVERTICAL);
	Units_AttackMissileDuplicationAmount2_Holder = new wxBoxSizer(wxVERTICAL);
	Units_AttackMissileDuplicationSpawning_Holder = new wxBoxSizer(wxVERTICAL);
	Units_AttackMissileDuplicationSpawning_Grid = new wxGridSizer(4, 5, 5);
	Units_AttackMissileDuplicationUnit_Holder = new wxBoxSizer(wxVERTICAL);
	Units_ChargingGraphic_Holder = new wxBoxSizer(wxVERTICAL);
	Units_ChargingMode_Holder = new wxBoxSizer(wxVERTICAL);
	Units_DisplayedPierceArmour_Holder = new wxBoxSizer(wxVERTICAL);

//	Type 80

	Units_ConstructionGraphicID_Holder = new wxBoxSizer(wxVERTICAL);
	Units_SnowGraphicID_Holder = new wxBoxSizer(wxVERTICAL);
	Units_AdjacentMode_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_IconDisabler_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Unknown31b_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_StackUnitID_Holder = new wxBoxSizer(wxVERTICAL);
	Units_TerrainID_Holder = new wxBoxSizer(wxVERTICAL);
	Units_OldTerrainLikeID_Holder = new wxBoxSizer(wxVERTICAL);
	Units_ResearchID_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Unknown33_Holder = new wxBoxSizer(wxVERTICAL);
	Units_AnnexUnit1_Holder = new wxBoxSizer(wxVERTICAL);
	Units_AnnexUnit_Grid = new wxGridSizer(4, 0, 5);
	Units_AnnexUnitMisplacement1_Holder = new wxBoxSizer(wxVERTICAL);
	Units_AnnexUnitMisplacement_Grid = new wxGridSizer(4, 0, 5);
	Units_HeadUnit_Holder = new wxBoxSizer(wxVERTICAL);
	Units_TransformUnit_Holder = new wxBoxSizer(wxVERTICAL);
	Units_UnknownSound_Holder = new wxBoxSizer(wxVERTICAL);
	Units_ConstructionSound_Holder = new wxBoxSizer(wxVERTICAL);
	Units_GarrisonType_Holder = new wxBoxSizer(wxVERTICAL);
	Units_GarrisonHealRate_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Unknown35_Holder = new wxBoxSizer(wxVERTICAL);
	Units_PileUnit_Holder = new wxBoxSizer(wxVERTICAL);
	Units_LootSwitch_Holder = new wxBoxSizer(wxVERTICAL);
	Units_LootSwitch_Grid = new wxGridSizer(6, 0, 5);

//	Data Container Names
//	Type 10+

	Units_ID1_Text = new wxStaticText(Units_Scroller, wxID_ANY, "ID 1 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_LanguageDLLName_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Language DLL Name *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_LanguageDLLCreation_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Language DLL Creation", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Class_Text = new wxStaticText(Tab_Units, wxID_ANY, "Class * ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_StandingGraphic_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Standing Graphics *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_DyingGraphic_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Dying Graphics", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_HitPoints_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Hit Points *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_LineOfSight_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Line Of Sight *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_GarrisonCapacity_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Garrison Capacity *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_SizeRadius_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Size Radius", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_HPBarHeight1_Text = new wxStaticText(Units_Scroller, wxID_ANY, " HP Bar Height 1 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_TrainSound_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Train Sound ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_DeadUnitID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Dead Unit", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_PlacementMode_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Placement Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_IconID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Icon *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown1_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 1 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_PlacementBypassTerrain_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Placement Side Terrain *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_PlacementTerrain_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Placement Terrain", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_EditorRadius_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Editor Radius", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_HillMode_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Hill Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_TerrainRestriction_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Terrain Restriction ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ResourceCapacity_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Resource Capacity ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ResourceDecay_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Resource Decay *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_BlastType_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Blast Type? *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown2_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 2 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_InteractionMode_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Interaction Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_MinimapMode_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Minimap Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_CommandAttribute_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Command Attribute *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown3A_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 3A *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_MinimapColor_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Minimap Color *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_LanguageDLLHelp_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Language DLL Help *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_LanguageDLLConverter_Text[0] = new wxStaticText(Units_Scroller, wxID_ANY, " Help Converter *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_LanguageDLLConverter_Text[1] = new wxStaticText(Units_Scroller, wxID_ANY, " Hotkey Text Converter *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_LanguageDLLHotKeyText_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Language DLL Hotkey Text *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_HotKey_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Hotkey *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown6_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Is a resource? *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown7_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown Selection Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown8_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 8 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_SelectionMask_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Selection Mask *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_SelectionShapeType_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Selection Shape Type *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_SelectionShape_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Selection Shape *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Attribute_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unit Attribute *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Civ_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Civilization", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown9_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Attribute Piece *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_SelectionEffect_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Selection Effect *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_EditorSelectionColour_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Editor Selection Color *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_SelectionRadius_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Selection Radius ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_HPBarHeight2_Text = new wxStaticText(Units_Scroller, wxID_ANY, " HP Bar Height 2 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	ResourceStorage_Type_Text = new wxStaticText(Units_Scroller, wxID_ANY, "Type ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	ResourceStorage_Amount_Text = new wxStaticText(Units_Scroller, wxID_ANY, "Amount ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	ResourceStorage_Enabled_Text = new wxStaticText(Units_Scroller, wxID_ANY, "Enable Mode * ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Units_SelectionSound_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Selection Sound ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_DyingSound_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Dying Sound ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_AttackMode_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Attack Mode? *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_EdibleMeat_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Edible Meat? *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Name_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Name ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Name2_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Name 2 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unitline_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unitline", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_MinTechLevel_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Min Tech Level", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ID2_Text = new wxStaticText(Units_Scroller, wxID_ANY, "ID 2 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ID3_Text = new wxStaticText(Units_Scroller, wxID_ANY, "ID 3 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Type 20+

	Units_Speed_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Speed ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Type 30+

	Units_WalkingGraphic_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Walking and Running Graphics", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_RotationSpeed_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Rotation Speed *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown11_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 11", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_TrackingUnit_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Tracking Unit ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_TrackingUnitUsed_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Tracking Unit Used *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_TrackingUnitDensity_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Tracking Unit Density *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown16_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 16", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown16B_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 16B", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Type 40+

	Units_SearchRadius_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Search Radius ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_WorkRate_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Work Rate ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_DropSite_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Drop Site *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_VillagerMode_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Villager Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_AttackSound_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Attack Sound", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_MoveSound_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Move Sound", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Exists_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Exists", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Type 50+

	Units_DefaultArmor_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Default Armor *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_TerRestrictionForDmgMultiply_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Terrain Restriction *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_MaxRange_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Max Range", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_BlastRadius_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Blast Radius", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ReloadTime1_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Reload Time", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ProjectileUnitID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Projectile Unit", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_AccuracyPercent_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Accuracy Percent", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Delay_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Frame Delay *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_GraphicDisplacement_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Graphic Displacement XYZ *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_BlastLevel_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Blast Level *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_MinRange_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Min Range", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_AccuracyErrorRadius_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Accuracy Error Radius *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_AttackGraphic_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Attack Graphic", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_DisplayedMeleeArmour_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Displayed Melee Armor", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_DisplayedAttack_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Displayed Attack", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_DisplayedRange_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Displayed Range", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ReloadTime2_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Displayed Reload Time", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Type 60 only

	Units_StretchMode_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Stretch Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_CompensationMode_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Compensation Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_DropAnimationMode_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Drop Animation Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_PenetrationMode_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Penetration Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown24_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 24 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ProjectileArc_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Projectile Arc ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Type 70+

	Units_CostType_Text = new wxStaticText(Units_Scroller, wxID_ANY, "Cost Type ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Units_CostAmount_Text = new wxStaticText(Units_Scroller, wxID_ANY, "Cost Amount ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Units_CostUsed_Text = new wxStaticText(Units_Scroller, wxID_ANY, "Cost Used ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Units_TrainTime_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Train Time", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_TrainLocationID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Train Location", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ButtonID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Train Button *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown26_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 26 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown27_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 27 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown28_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 28 *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_GarrisonGraphic_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Garrison Graphic ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_AttackMissileDuplicationAmount1_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Min Dupl. Missiles *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_AttackMissileDuplicationAmount2_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Max Dupl. Missiles *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_AttackMissileDuplicationSpawning_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Missile Spawning Area *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_AttackMissileDuplicationUnit_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Missile Dupl. Unit *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ChargingGraphic_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Charging Graphic *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ChargingMode_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Charging Mode? *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_DisplayedPierceArmour_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Displayed Pierce Armor ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Type 80

	Units_ConstructionGraphicID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Construction Graphic ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_SnowGraphicID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Snow Graphic ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_IconDisabler_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Icon/Graphics SLP Angle *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_StackUnitID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Stack Unit *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_TerrainID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Foundation Terrain *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_OldTerrainLikeID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Old Terrain *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ResearchID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Initiates Research *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown33_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 33", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_AnnexUnit_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Annex Units", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_AnnexUnitMisplacement_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Annex Units Misplacement", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_HeadUnit_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Head Unit *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_TransformUnit_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Transform Unit *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_UnknownSound_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown Sound", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ConstructionSound_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Construction Sound ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_GarrisonType_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Garrison Type *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_GarrisonHealRate_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Garrison Heal Rate *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown35_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Wonder Timer? *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_PileUnit_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Pile Unit *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_LootSwitch_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Looting Table *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Data Containers

	Units_ID1 = new TextCtrl_Short(Units_Scroller, true);
	Units_ID2 = new TextCtrl_Short(Units_Scroller, true);
	Units_ID3 = new TextCtrl_Short(Units_Scroller, true);
	Units_Name = new TextCtrl_String(Units_Scroller, 30);
	Units_Name2 = new TextCtrl_String(Units_Scroller, 30);
	Units_LanguageDLLName = new TextCtrl_UShort(Units_Scroller);
	Units_LanguageDLLName->SetToolTip("Usual Unit DLL Pattern for The Conquerors\nName: 5000-5999\nCreation: Name +1000\nHotkey: Name +11000\nHelp: Name +100000, in DLL Name +21000\nHotkey Text: Name +150000, in DLL Name +10000\nTech tree: Name +9000");
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

	Units_DamageGraphics = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Damage Graphics");
	Units_DamageGraphics_ListArea = new wxBoxSizer(wxVERTICAL);
	Units_DamageGraphics_Search = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_DamageGraphics_Search_R = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_DamageGraphics_List = new wxListBox(Units_Scroller, wxID_ANY, wxDefaultPosition, wxSize(140, 100), 0, NULL, wxLB_EXTENDED);
	Units_DamageGraphics_Buttons = new wxGridSizer(3, 0, 0);
	Units_DamageGraphics_Add = new wxButton(Units_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Units_DamageGraphics_Insert = new wxButton(Units_Scroller, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	Units_DamageGraphics_Delete = new wxButton(Units_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Units_DamageGraphics_Copy = new wxButton(Units_Scroller, wxID_ANY, "Copy *", wxDefaultPosition, wxSize(5, 20));
	Units_DamageGraphics_Copy->SetToolTip("When \"All civs\" is not selected,\nthis and pasting works only for current civilization");
	Units_DamageGraphics_Paste = new wxButton(Units_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Units_DamageGraphics_PasteInsert = new wxButton(Units_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));
	Units_DamageGraphics_CopyToUnits = new wxButton(Units_Scroller, wxID_ANY, "Copy all to selected units", wxDefaultPosition, wxSize(5, 20));
	Units_DamageGraphics_Holder_Data = new wxBoxSizer(wxVERTICAL);
	DamageGraphics_GraphicID_Holder = new wxBoxSizer(wxVERTICAL);
	DamageGraphics_GraphicID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Graphic ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	DamageGraphics_GraphicID = new TextCtrl_Short(Units_Scroller);
	DamageGraphics_GraphicID_ComboBox = new ComboBox_Plus1(Units_Scroller, DamageGraphics_GraphicID);
	GraphicComboBoxList.push_back(DamageGraphics_GraphicID_ComboBox);
	DamageGraphics_DamagePercent_Holder = new wxBoxSizer(wxVERTICAL);
	DamageGraphics_DamagePercent_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Damage Percent ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	DamageGraphics_DamagePercent = new TextCtrl_Byte(Units_Scroller);
	DamageGraphics_Unknown1_Holder = new wxBoxSizer(wxVERTICAL);
	DamageGraphics_Unknown1_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Apply Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	DamageGraphics_Unknown1 = new TextCtrl_Byte(Units_Scroller);
	DamageGraphics_Unknown1->SetToolTip("0 (& 1?) Adds graphics on top (flames on buildings)\n2 Replaces original graphics (damaged walls)");
	DamageGraphics_Unknown2_Holder = new wxBoxSizer(wxVERTICAL);
	DamageGraphics_Unknown2_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 2 ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	DamageGraphics_Unknown2 = new TextCtrl_Byte(Units_Scroller);

	Units_IconID = new TextCtrl_Short(Units_Scroller);
	Units_IconID->SetToolTip("Download Turtle Pack from AoKH to add more than 127 icons.");
	Units_IconDisabler = new TextCtrl_Short(Units_Scroller);
	Units_IconDisabler->SetToolTip("Tech attribute 17 changes this\n0 Default\n1+ Use icon from 2nd age etc\nIn AoE 1 can be used to set the unit\nhave icon graphics of later ages straight in stone age");
	for(short loop = 0; loop < 2; ++loop)
	{
		Units_StandingGraphic[loop] = new TextCtrl_Short(Units_Scroller);
		Units_StandingGraphic[loop]->SetToolTip("Half of units in group use 1st,\nthe rest use 2nd");
		Units_StandingGraphic_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_StandingGraphic[loop]);
		GraphicComboBoxList.push_back(Units_StandingGraphic_ComboBox[loop]);
	}
	for(short loop = 0; loop < 2; ++loop)
	{
		Units_DyingGraphic[loop] = new TextCtrl_Short(Units_Scroller);
		Units_DyingGraphic_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_DyingGraphic[loop]);
		GraphicComboBoxList.push_back(Units_DyingGraphic_ComboBox[loop]);
	}
	for(short loop = 0; loop < 2; ++loop)
	{
		Units_WalkingGraphic[loop] = new TextCtrl_Short(Units_Scroller);
		Units_WalkingGraphic_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_WalkingGraphic[loop]);
		GraphicComboBoxList.push_back(Units_WalkingGraphic_ComboBox[loop]);
	}
	Units_SnowGraphicID = new TextCtrl_Short(Units_Scroller);
	Units_SnowGraphicID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_SnowGraphicID);
	GraphicComboBoxList.push_back(Units_SnowGraphicID_ComboBox);
	Units_ConstructionGraphicID = new TextCtrl_Short(Units_Scroller);
	Units_ConstructionGraphicID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_ConstructionGraphicID);
	GraphicComboBoxList.push_back(Units_ConstructionGraphicID_ComboBox);
	Units_AttackGraphic = new TextCtrl_Short(Units_Scroller);
	Units_AttackGraphic_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_AttackGraphic);
	GraphicComboBoxList.push_back(Units_AttackGraphic_ComboBox);
	Units_GarrisonGraphic = new TextCtrl_Long(Units_Scroller);
	Units_GarrisonGraphic_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_GarrisonGraphic);
	GraphicComboBoxList.push_back(Units_GarrisonGraphic_ComboBox);

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
	Units_Attacks_List = new wxListBox(Units_Scroller, wxID_ANY, wxDefaultPosition, wxSize(140, 100), 0, NULL, wxLB_EXTENDED);
	Units_Attacks_Buttons = new wxGridSizer(3, 0, 0);
	Units_Attacks_Add = new wxButton(Units_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Units_Attacks_Insert = new wxButton(Units_Scroller, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	Units_Attacks_Delete = new wxButton(Units_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Units_Attacks_Copy = new wxButton(Units_Scroller, wxID_ANY, "Copy *", wxDefaultPosition, wxSize(5, 20));
	Units_Attacks_Copy->SetToolTip("When \"All civs\" is not selected,\nthis and pasting works only for current civilization");
	Units_Attacks_Paste = new wxButton(Units_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Units_Attacks_PasteInsert = new wxButton(Units_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));
	Units_Attacks_CopyToUnits = new wxButton(Units_Scroller, wxID_ANY, "Copy all to selected units", wxDefaultPosition, wxSize(5, 20));
	Units_Attacks_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_Attacks_Holder_Data = new wxBoxSizer(wxVERTICAL);
	Units_Attacks_Grid_Data2 = new wxGridSizer(2, 5, 5);
	Attacks_Amount_Holder = new wxBoxSizer(wxVERTICAL);
	Attacks_Amount_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Amount", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Attacks_Amount = new TextCtrl_Short(Units_Scroller);
	Attacks_Class_Holder = new wxBoxSizer(wxVERTICAL);
	Attacks_Class_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Class *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Attacks_Class = new TextCtrl_Short(Units_Scroller);
	Attacks_Class->SetToolTip("Armor class that this unit can damage\nYou can make your own classes");
	Attacks_Class_ComboBox[0] = new ComboBox_Plus1(Units_Scroller, Attacks_Class);

	Units_DisplayedAttack = new TextCtrl_Short(Units_Scroller);
	Units_Delay = new TextCtrl_Short(Units_Scroller);
	Units_Delay->SetToolTip("Graphical delay in frames before projectile is shot");
	Units_AccuracyPercent = new TextCtrl_Short(Units_Scroller);
	Units_AccuracyErrorRadius = new TextCtrl_Float(Units_Scroller);
	Units_AccuracyErrorRadius->SetToolTip("Higher values will make the unit less accurate");
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
	Units_Armors_List = new wxListBox(Units_Scroller, wxID_ANY, wxDefaultPosition, wxSize(140, 100), 0, NULL, wxLB_EXTENDED);
	Units_Armors_Buttons = new wxGridSizer(3, 0, 0);
	Units_Armors_Add = new wxButton(Units_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Units_Armors_Insert = new wxButton(Units_Scroller, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	Units_Armors_Delete = new wxButton(Units_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Units_Armors_Copy = new wxButton(Units_Scroller, wxID_ANY, "Copy *", wxDefaultPosition, wxSize(5, 20));
	Units_Armors_Copy->SetToolTip("When \"All civs\" is not selected,\nthis and pasting works only for current civilization");
	Units_Armors_Paste = new wxButton(Units_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Units_Armors_PasteInsert = new wxButton(Units_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));
	Units_Armors_CopyToUnits = new wxButton(Units_Scroller, wxID_ANY, "Copy all to selected units", wxDefaultPosition, wxSize(5, 20));
	Units_Armors_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_Armors_Holder_Data3 = new wxBoxSizer(wxVERTICAL);
	Armors_Amount_Holder = new wxBoxSizer(wxVERTICAL);
	Armors_Amount_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Amount", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Armors_Amount = new TextCtrl_Short(Units_Scroller);
	Armors_Class_Holder = new wxBoxSizer(wxVERTICAL);
	Armors_Class_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Class *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Armors_Class = new TextCtrl_Short(Units_Scroller);
	Armors_Class->SetToolTip("Attack class from which this unit can take damage\nYou can make your own classes");
	Attacks_Class_ComboBox[1] = new ComboBox_Plus1(Units_Scroller, Armors_Class);

	Units_DefaultArmor = new TextCtrl_Short(Units_Scroller);
	Units_DefaultArmor->SetToolTip("This armor is used for all attack types that do not have corresponding armor type\nCan be negative only in The Conquerors and later games");
	Units_TerRestrictionForDmgMultiply = new TextCtrl_Short(Units_Scroller);
	Units_TerRestrictionForDmgMultiply->SetToolTip("Receive damage based on which terrain this unit stands on\nTech attribute 18 changes this\nThe damage received by this unit is\nmultiplied by the accessible values on\nthe specified terrain restriction");
	Units_TerRestrictionForDmgMultiply_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_TerRestrictionForDmgMultiply);
	TerrainRestrictionComboBoxList.push_back(Units_TerRestrictionForDmgMultiply_ComboBox);
	Units_DisplayedMeleeArmour = new TextCtrl_Short(Units_Scroller);
	Units_DisplayedPierceArmour = new TextCtrl_Short(Units_Scroller);
	Units_ResourceCapacity = new TextCtrl_Short(Units_Scroller);
	Units_ResourceDecay = new TextCtrl_Float(Units_Scroller);
	Units_ResourceDecay->SetToolTip("Can alter corpses' decay time\nSet to -1 for never decaying");
	Units_WorkRate = new TextCtrl_Float(Units_Scroller);
	Units_GarrisonCapacity = new TextCtrl_Byte(Units_Scroller);
	Units_GarrisonCapacity->SetToolTip("If the unit has garrisoned units inside,\ngraphics tab \"New Speed?\" determines its new speed?");
	Units_GarrisonType = new TextCtrl_UByte(Units_Scroller);
	Units_GarrisonType_Grid = new wxGridSizer(8, 0, 0);
	for(short loop = 0; loop < 8; ++loop)
	Units_GarrisonType_CheckBox[loop] = new wxCheckBox(Units_Scroller, wxID_ANY, "", wxDefaultPosition, wxSize(-1, 20));
	Units_GarrisonType_CheckBox[0]->SetToolTip("Villager/Worker");
	Units_GarrisonType_CheckBox[1]->SetToolTip("Infantry");
	Units_GarrisonType_CheckBox[2]->SetToolTip("Cavalry/Mounted");
	Units_GarrisonType_CheckBox[3]->SetToolTip("Monk/Jedi");
	Units_GarrisonType_CheckBox[4]->SetToolTip("SW: Livestock");
	Units_GarrisonHealRate = new TextCtrl_Float(Units_Scroller);
	Units_GarrisonHealRate->SetToolTip("Building's garrisoned units' healing speed factor");

	Units_ProjectileUnitID = new TextCtrl_Short(Units_Scroller);
	Units_ProjectileUnitID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_ProjectileUnitID);
	UnitComboBoxList.push_back(Units_ProjectileUnitID_ComboBox);
	Units_AttackMissileDuplicationUnit = new TextCtrl_Long(Units_Scroller);
	Units_AttackMissileDuplicationUnit->SetToolTip("Uses its own attack values!");
	Units_AttackMissileDuplicationUnit_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_AttackMissileDuplicationUnit);
	UnitComboBoxList.push_back(Units_AttackMissileDuplicationUnit_ComboBox);
	Units_ChargingGraphic = new TextCtrl_Long(Units_Scroller);
	Units_ChargingGraphic->SetToolTip("Used just before the unit reaches its target enemy");
	Units_ChargingGraphic_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_ChargingGraphic);
	GraphicComboBoxList.push_back(Units_ChargingGraphic_ComboBox);
	Units_ChargingMode = new TextCtrl_Byte(Units_Scroller);
	Units_ChargingMode->SetToolTip("0 Default\n3 Unit must walk to enemy when ordered to attack it\nAttack duplication graphics activate too");
	Units_AttackMissileDuplicationAmount1 = new TextCtrl_Float(Units_Scroller);
	Units_AttackMissileDuplicationAmount1->SetToolTip("Duplicated missiles when no units are garrisoned inside");
	Units_AttackMissileDuplicationAmount2 = new TextCtrl_Byte(Units_Scroller);
	Units_AttackMissileDuplicationAmount2->SetToolTip("Maximum duplicated missiles when garrison capacity is full");
	for(short loop = 0; loop < 3; ++loop)
	Units_AttackMissileDuplicationSpawning[loop] = new TextCtrl_Float(Units_Scroller);
	Units_AttackMissileDuplicationSpawning[0]->SetToolTip("Spawning area's width");
	Units_AttackMissileDuplicationSpawning[1]->SetToolTip("Spawning area's length");
	Units_AttackMissileDuplicationSpawning[2]->SetToolTip("Spawning point's randomness inside the spawning area\n0 from a single spot\n1 Totally randomly inside the spawning area\n1+ Less randomly");
	for(short loop = 0; loop < 3; ++loop)
	Units_GraphicDisplacement[loop] = new TextCtrl_Float(Units_Scroller);
	Units_GraphicDisplacement[0]->SetToolTip("Left/Right distance");
	Units_GraphicDisplacement[1]->SetToolTip("Spawning distance from the unit");
	Units_GraphicDisplacement[2]->SetToolTip("Height");

	Units_StretchMode = new TextCtrl_Byte(Units_Scroller);
	Units_StretchMode->SetToolTip("0 Default\n1 Projectile falls vertically to the bottom of the map\n3 Teleporting projectiles");
	Units_CompensationMode = new TextCtrl_Byte(Units_Scroller);
	Units_CompensationMode->SetToolTip("Tech attribute 19 changes this\n0 Shoot where the target is now\n1 Shoot where the target is going to be");
	Units_DropAnimationMode = new TextCtrl_Byte(Units_Scroller);
	Units_DropAnimationMode->SetToolTip("0 Doesn't disappear after hitting the target\n1 Disappears\n2 SWGB artillery fire has this");
	Units_PenetrationMode = new TextCtrl_Byte(Units_Scroller);
	Units_PenetrationMode->SetToolTip("0 Stops the graphics\n1 Graphics pass through the target instead of stopping\nOnly affects the graphics of the projectile");
	Units_Unknown24 = new TextCtrl_Byte(Units_Scroller);
	Units_Unknown24->SetToolTip("Bullets have this as 1");
	Units_ProjectileArc = new TextCtrl_Float(Units_Scroller);

	Units_Enabled = new TextCtrl_Byte(Units_Scroller);
	Units_Enabled->SetToolTip("0 Requires a research to be available\n1 Available without a research");
	Units_Enabled_CheckBox = new CheckBox_2State(Units_Scroller, "No Research *", Units_Enabled);
	Units_Disabled = new TextCtrl_Byte(Units_Scroller);
	Units_Disabled->SetToolTip("0 Default\n1 Prevents enabling/disabling with a tech");
	Units_Disabled_CheckBox = new CheckBox_2State(Units_Scroller, "Disabled *", Units_Disabled);
	Units_DeathMode = new TextCtrl_Byte(Units_Scroller);
	Units_DeathMode->SetToolTip("Reviving does not make it usable");
	Units_DeathMode_CheckBox = new CheckBox_2State(Units_Scroller, "Death: Revives *", Units_DeathMode);
	Units_HideInEditor = new TextCtrl_Byte(Units_Scroller);
	Units_HideInEditor_CheckBox = new CheckBox_2State(Units_Scroller, "Hide in Editor", Units_HideInEditor);
	Units_AirMode = new TextCtrl_Byte(Units_Scroller);
	Units_AirMode->SetToolTip("1 for no footprints");
	Units_AirMode_CheckBox = new CheckBox_2State(Units_Scroller, "Air Mode *", Units_AirMode);
	Units_FlyMode = new TextCtrl_Byte(Units_Scroller);
	Units_FlyMode->SetToolTip("Requires class 22 and air mode 1?\n0 Normal\n1 Graphics appear higher than the shadow");
	Units_FlyMode_CheckBox = new CheckBox_2State(Units_Scroller, "Fly Mode", Units_FlyMode);
	Units_SheepConversion = new TextCtrl_Short(Units_Scroller, true);
	Units_SheepConversion->SetToolTip("To get the unit auto-converted to enemy,\nuse unit command 107, which sheep and monument have\nAll somehow auto-convertible units have this set to 0\nMost other units have -1");
	Units_SheepConversion_CheckBox = new CheckBox_ZeroIsYes(Units_Scroller, "Convert Herd *", Units_SheepConversion);
	Units_AnimalMode = new TextCtrl_Byte(Units_Scroller);
	Units_AnimalMode_CheckBox = new CheckBox_2State(Units_Scroller, "Animal Mode", Units_AnimalMode);
	Units_AdjacentMode = new TextCtrl_Byte(Units_Scroller);
	Units_AdjacentMode->SetToolTip("0 Default\n1 Adjacent buildings can change this unit's graphics");
	Units_AdjacentMode_CheckBox = new CheckBox_2State(Units_Scroller, "Adjacent Mode *", Units_AdjacentMode);
	Units_DisappearsWhenBuilt = new TextCtrl_Byte(Units_Scroller);
	Units_DisappearsWhenBuilt->SetToolTip("Useful for stack unit placement\n0 Default\n1 Makes the building disappear when built");
	Units_Unknown31b_CheckBox = new CheckBox_2State(Units_Scroller, "Built: Vanishes *", Units_DisappearsWhenBuilt);
	Units_TowerMode = new TextCtrl_Byte(Units_Scroller);
	Units_TowerMode_CheckBox = new CheckBox_2State(Units_Scroller, "Tower Mode", Units_TowerMode);
	Units_HeroMode = new TextCtrl_Byte(Units_Scroller);
	Units_HeroMode_CheckBox = new CheckBox_2State(Units_Scroller, "Hero Mode", Units_HeroMode);

	Units_PlacementMode = new TextCtrl_Byte(Units_Scroller);
	Units_PlacementMode->SetToolTip("0 Can be placed on top of other units in scenario editor\n5 Cannot be placed on top of other units in scenario editor");
	Units_HillMode = new TextCtrl_Byte(Units_Scroller);
	Units_HillMode->SetToolTip("0 No restriction\n2 Restricts placement to flat land\n3 Allows placement on hills for the most part");
	Units_VisibleInFog_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Fog Visibility *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_VisibleInFog = new TextCtrl_Byte(Units_Scroller);
	Units_VisibleInFog->SetToolTip("0 Not visible\n1 Visible\n3 Inverted visibility");
	Units_InteractionMode = new TextCtrl_Byte(Units_Scroller);
	Units_InteractionMode->SetToolTip("0 & 1 Unable to select, move or attack\n2 Can select, unable to move or attack\n3 Can select and attack, unable to move\n4 Can select, move and attack\n5+ Select and move?");
	Units_MinimapMode = new TextCtrl_Byte(Units_Scroller);
	Units_MinimapMode->SetToolTip("0 & 6-10 No dot on minimap\n1 Square dot turning white when selected\n2 Diamond dot turning white when selected\n3 Diamond dot keeping color\n4 & 5 Larger spot, not following the unit, no blinking when attacked, everyone can see it\n");
	Units_MinimapColor = new TextCtrl_UByte(Units_Scroller);
	Units_MinimapColor->SetToolTip("Minimap mode 4 allows this to work");
	Units_AttackMode = new TextCtrl_Byte(Units_Scroller);
	Units_AttackMode->SetToolTip("This may be attack mode\n0 No attacck\n1 Attack by following\n2 Run when attacked\n3 ?\n4 Attack\n");
	Units_EdibleMeat = new TextCtrl_Byte(Units_Scroller);
	Units_EdibleMeat->SetToolTip("0 Default\n1 Rotting meat that can be gathered");
	Units_VillagerMode = new TextCtrl_Byte(Units_Scroller);
	Units_VillagerMode->SetToolTip("Changes according to task\n1 Male\n2 Female");

	Units_Attribute = new TextCtrl_UByte(Units_Scroller);
	Units_Attribute->SetToolTip("This is a byte of eight booleans\nYou can combine these attributes");
	Units_Attribute_Grid = new wxGridSizer(8, 0, 0);
	for(short loop = 0; loop < 8; ++loop)
	Units_Attribute_CheckBox[loop] = new wxCheckBox(Units_Scroller, wxID_ANY, "", wxDefaultPosition, wxSize(-1, 20));
	Units_Attribute_CheckBox[0]->SetToolTip("Garrison unit");
	Units_Attribute_CheckBox[1]->SetToolTip("Ship unit");
	Units_Attribute_CheckBox[2]->SetToolTip("SW: Stealth unit");
	Units_Attribute_CheckBox[3]->SetToolTip("SW: Detector unit");
	Units_Attribute_CheckBox[4]->SetToolTip("SW: Mechanical unit");
	Units_Attribute_CheckBox[5]->SetToolTip("SW: Biological unit");
	Units_Attribute_CheckBox[6]->SetToolTip("SW: Self-shielding unit");
	Units_Attribute_CheckBox[7]->SetToolTip("Invisible unit");
	Units_Civ = new TextCtrl_Byte(Units_Scroller);
	Units_Civ_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_Civ);
	CivComboBoxList.push_back(Units_Civ_ComboBox);
	Units_Unknown9 = new TextCtrl_Short(Units_Scroller);
	Units_Unknown9->SetToolTip("This is actually leftover from attribute+civ variable\nProbably useless");
	Units_DeadUnitID = new TextCtrl_Short(Units_Scroller);
	Units_DeadUnitID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_DeadUnitID);
	UnitComboBoxList.push_back(Units_DeadUnitID_ComboBox);
	Units_Unitline = new TextCtrl_Short(Units_Scroller);
	Units_Unitline_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_Unitline);
	Units_MinTechLevel = new TextCtrl_Byte(Units_Scroller);
	Units_MinTechLevel_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_MinTechLevel);
	ResearchComboBoxList.push_back(Units_MinTechLevel_ComboBox);
	for(short loop = 0; loop < 2; ++loop)
	{
		Units_PlacementTerrain[loop] = new TextCtrl_Short(Units_Scroller);
		Units_PlacementTerrain_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_PlacementTerrain[loop]);
		TerrainComboBoxList.push_back(Units_PlacementTerrain_ComboBox[loop]);
	}
	for(short loop = 0; loop < 2; ++loop)
	{
		Units_PlacementBypassTerrain[loop] = new TextCtrl_Short(Units_Scroller);
		Units_PlacementBypassTerrain[loop]->SetToolTip("Required terrain on some side");
		Units_PlacementBypassTerrain_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_PlacementBypassTerrain[loop]);
		TerrainComboBoxList.push_back(Units_PlacementBypassTerrain_ComboBox[loop]);
	}
	Units_TerrainRestriction = new TextCtrl_Short(Units_Scroller);
	Units_TerrainRestriction_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_TerrainRestriction);
	TerrainRestrictionComboBoxList.push_back(Units_TerrainRestriction_ComboBox);
	Units_TerrainID = new TextCtrl_Short(Units_Scroller);
	Units_TerrainID->SetToolTip("Terrain produced under a building when completed");
	Units_TerrainID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_TerrainID);
	TerrainComboBoxList.push_back(Units_TerrainID_ComboBox);
	Units_OldTerrainLikeID = new TextCtrl_Short(Units_Scroller);
	Units_OldTerrainLikeID->SetToolTip("ES forgot to remove this before AoE was released.\nThis points to removed data block\nthat was like terrain borders.\nYou could build roads back in 1996.");
	Units_ResearchID = new TextCtrl_Short(Units_Scroller);
	Units_ResearchID->SetToolTip("Causes that research to be researched when the building is created");
	Units_ResearchID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_ResearchID);
	ResearchComboBoxList.push_back(Units_ResearchID_ComboBox);
	for(short loop = 0; loop < 2; ++loop)
	{
		Units_DropSite[loop] = new TextCtrl_Short(Units_Scroller);
		Units_DropSite[loop]->SetToolTip("Giving a villager's drop site to a cart-like unit\ncan allow you to have mobile resource-gatherers,\nsimilar to those in Age of Mythology.");
		Units_DropSite_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_DropSite[loop]);
		UnitComboBoxList.push_back(Units_DropSite_ComboBox[loop]);
	}
	for(short loop = 0; loop < 2; ++loop)
	Units_SizeRadius[loop] = new TextCtrl_Float(Units_Scroller, true);
	for(short loop = 0; loop < 2; ++loop)
	Units_EditorRadius[loop] = new TextCtrl_Float(Units_Scroller, true);
	Units_SelectionRadiusBox = new wxBoxSizer(wxHORIZONTAL);
	for(short loop = 0; loop < 2; ++loop)
	Units_SelectionRadius[loop] = new TextCtrl_Float(Units_Scroller, true);
	Units_Unselectable = new TextCtrl_Byte(Units_Scroller);
	Units_Unselectable_CheckBox = new CheckBox_2State(Units_Scroller, "Unselectable", Units_Unselectable);
	Units_SelectionMask = new TextCtrl_Byte(Units_Scroller);
	Units_SelectionMask->SetToolTip("Any odd value except 7 - Mask displayed behind buildings\nAny even value except 6, 10 - Mask not displayed\n-1, 7 - Mask partially displayed when in the open\n6, 10 - Building, causes mask to appear on units behind it\n");
	Units_SelectionShapeType = new TextCtrl_Byte(Units_Scroller);
	Units_SelectionShapeType->SetToolTip("Seems to control 3 things\nIf square or round, value 5\nIf real size or selection size is used, value 2\nIf walkable or not, value 0");
	Units_SelectionShape = new TextCtrl_Byte(Units_Scroller);
	Units_SelectionShape->SetToolTip("0 Square\n1+ Round");
	Units_SelectionEffect = new TextCtrl_Byte(Units_Scroller);
	Units_SelectionEffect->SetToolTip("0\n1 HP Bar on, permanent darker outline in editor only\n4 HP Bar off, normal outline\n5, 8-9 HP Bar on\n2 HP Bar on, normal outline\n3 HP Bar off, selection shadow\n6-7 HP Bar off\nNote: this doesn't work with all units");
	Units_EditorSelectionColour = new TextCtrl_UByte(Units_Scroller);
	Units_EditorSelectionColour->SetToolTip("0 most\n-16 fish trap farm\n52 dead farm, OLD-(___)\n116 flare, WHAL1, WHAL2, DOLP, Great-fish\n-123 all fish");
	Units_TrackingUnit = new TextCtrl_Short(Units_Scroller);
	Units_TrackingUnit_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_TrackingUnit);
	UnitComboBoxList.push_back(Units_TrackingUnit_ComboBox);
	Units_TrackingUnitUsed = new TextCtrl_Byte(Units_Scroller);
	Units_TrackingUnitUsed->SetToolTip("-1 unless a tracking unit value is present\n2 all projectiles with a tracking unit");
	Units_TrackingUnitDensity = new TextCtrl_Float(Units_Scroller);
	Units_TrackingUnitDensity->SetToolTip("0 unless tracking unit value is present\n0.5 trade carts\n0.12 MFFFG(projectile)\n0.4 other projectiles");
	Units_CommandAttribute = new TextCtrl_Byte(Units_Scroller);
	Units_CommandAttribute->SetToolTip("Class and this sets the interface for this unit\n0 Actions: Delete, Garrison, Stop | Attributes: Hit Points\n1 Animal\n2 Non-Military Building (build page 1)\n3 Villager\n4 Military Unit\n5 Trading Unit\n6 Monk\n7 Transport Ship\n8 Relic / Monk with Relic\n9 Fishing Ship\n10 Military Building (build page 2)\n11 Shield Building (build page 3)");
	Units_TrainTime = new TextCtrl_Short(Units_Scroller);
	Units_TrainLocationID = new TextCtrl_Short(Units_Scroller);
	Units_TrainLocationID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_TrainLocationID);
	UnitComboBoxList.push_back(Units_TrainLocationID_ComboBox);
	Units_ButtonID = new TextCtrl_Byte(Units_Scroller);
	Units_ButtonID->SetToolTip("First page (also second in TC) 1-15\nSecond (dock) page 21-35\nThird page same as first (Star Wars)\nFirst page in AoE/RoR 1-10\nSecond page in AoE/RoR 11-20");
	for(short loop = 0; loop < 3; ++loop)
	{
		ResourceStorage_Type[loop] = new TextCtrl_Short(Units_Scroller);
		ResourceStorage_Type_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, ResourceStorage_Type[loop]);
		ResourceComboBoxList.push_back(ResourceStorage_Type_ComboBox[loop]);
		ResourceStorage_Amount[loop] = new TextCtrl_Float(Units_Scroller);
		ResourceStorage_Enabled[loop] = new TextCtrl_Byte(Units_Scroller);
		ResourceStorage_Enabled[loop]->SetToolTip("0 Decayable resource\n1 Stored after death also\n2 Resets on dying, enables instantly\n4 Resets on dying, enables on completion");
	}
	for(short loop = 0; loop < 3; ++loop)
	{
		Units_CostType[loop] = new TextCtrl_Short(Units_Scroller);
		Units_CostType_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_CostType[loop]);
		ResourceComboBoxList.push_back(Units_CostType_ComboBox[loop]);
		Units_CostAmount[loop] = new TextCtrl_Short(Units_Scroller);
		Units_CostUsed[loop] = new TextCtrl_Short(Units_Scroller);
		Units_CostUsed[loop]->SetToolTip("If set to 0 and there is an amount, the amount is required but not paid");
		Units_CostUsed_CheckBox[loop] = new CheckBox_2State(Units_Scroller, "Used", Units_CostUsed[loop]);
	}
	Units_StackUnitID = new TextCtrl_Short(Units_Scroller);
	Units_StackUnitID->SetToolTip("Second building to be placed directly on top of this building\nAdditional building gets added every time you load the scenario");
	Units_StackUnitID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_StackUnitID);
	UnitComboBoxList.push_back(Units_StackUnitID_ComboBox);
	Units_HeadUnit = new TextCtrl_Short(Units_Scroller);
	Units_HeadUnit->SetToolTip("The building that an annex building is attached to");
	Units_HeadUnit_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_HeadUnit);
	UnitComboBoxList.push_back(Units_HeadUnit_ComboBox);
	Units_TransformUnit = new TextCtrl_Short(Units_Scroller);
	Units_TransformUnit->SetToolTip("Determines what the unit changes into when given the order to unpack");
	Units_TransformUnit_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_TransformUnit);
	UnitComboBoxList.push_back(Units_TransformUnit_ComboBox);
	Units_PileUnit = new TextCtrl_Short(Units_Scroller);
	Units_PileUnit->SetToolTip("Appears when the building dies\nDoes not appear with delete command");
	Units_PileUnit_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_PileUnit);
	UnitComboBoxList.push_back(Units_PileUnit_ComboBox);
	for(short loop = 0; loop < 4; ++loop)
	{
		Units_AnnexUnit[loop] = new TextCtrl_Short(Units_Scroller);
		Units_AnnexUnit_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_AnnexUnit[loop]);
		UnitComboBoxList.push_back(Units_AnnexUnit_ComboBox[loop]);
	}
	for(short loop = 0; loop < 4; ++loop)
	{
		for(short loop2 = 0; loop2 < 2; ++loop2)
		Units_AnnexUnitMisplacement[loop][loop2] = new TextCtrl_Float(Units_Scroller);
	}
	for(short loop = 0; loop < Units_LootSwitch.size(); ++loop)
	Units_LootSwitch[loop] = new TextCtrl_Byte(Units_Scroller);
	Units_LootSwitch[0]->SetToolTip("Stone Loot Switch");
	Units_LootSwitch[1]->SetToolTip("Wood Loot Switch");
	Units_LootSwitch[2]->SetToolTip("Ore Loot Switch");
	Units_LootSwitch[3]->SetToolTip("Gold Loot Switch");
	Units_LootSwitch[4]->SetToolTip("Food Loot Switch");
	Units_LootSwitch[5]->SetToolTip("Goods Loot Switch");

	Units_SelectionSound = new TextCtrl_Short(Units_Scroller);
	Units_SelectionSound_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_SelectionSound);
	SoundComboBoxList.push_back(Units_SelectionSound_ComboBox);
	Units_DyingSound = new TextCtrl_Short(Units_Scroller);
	Units_DyingSound_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_DyingSound);
	SoundComboBoxList.push_back(Units_DyingSound_ComboBox);
	for(short loop = 0; loop < 2; ++loop)
	{
		Units_TrainSound[loop] = new TextCtrl_Short(Units_Scroller);
		Units_TrainSound_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_TrainSound[loop]);
		SoundComboBoxList.push_back(Units_TrainSound_ComboBox[loop]);
	}
	Units_AttackSound = new TextCtrl_Short(Units_Scroller);
	Units_AttackSound_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_AttackSound);
	SoundComboBoxList.push_back(Units_AttackSound_ComboBox);
	Units_MoveSound = new TextCtrl_Short(Units_Scroller);
	Units_MoveSound_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_MoveSound);
	SoundComboBoxList.push_back(Units_MoveSound_ComboBox);
	Units_ConstructionSound = new TextCtrl_Short(Units_Scroller);
	Units_ConstructionSound_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_ConstructionSound);
	SoundComboBoxList.push_back(Units_ConstructionSound_ComboBox);
	Units_UnknownSound = new TextCtrl_Short(Units_Scroller);
	Units_UnknownSound_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_UnknownSound);
	SoundComboBoxList.push_back(Units_UnknownSound_ComboBox);

	Units_HPBarHeight1 = new TextCtrl_Float(Units_Scroller);
	Units_HPBarHeight1->SetToolTip("Setting \"Air Mode\" to 1 and this to 0 causes farms to be walkable in AoE/RoR");
	Units_HPBarHeight2 = new TextCtrl_Float(Units_Scroller);
	Units_HPBarHeight2->SetToolTip("Vertical distance from ground");

	Units_Unknown1 = new TextCtrl_Short(Units_Scroller);
	Units_BlastType = new TextCtrl_Byte(Units_Scroller);
	Units_BlastType->SetToolTip("0 projectiles, dead units, fish, relics, trees\n0 gates, town center\n0 deer(unmoving), FLDOG\n1 things listed under \"others\" that have multiple rotations\n2 buildings, gates, walls, town centers, fish trap\n3 boar\n3 farm, TWAL\n3 fishing ship, villagers, trade carts, sheep, turkey\n3 (any unit) archers, junk, trade cogs, ships, seige, mounted, deer(regular), monk with relic\n3 monks, BDGAL, ABGAL");
	Units_Unknown2 = new TextCtrl_Byte(Units_Scroller);
	Units_Unknown2->SetToolTip("Action from mouse right-click?\n0 projectiles, dead units, fish, relics, trees\n2 gates, town center\n4 deer(unmoving), FLDOG\n0 things listed under \"others\" that have multiple rotations\n2 buildings, gates, walls, town centers, fish trap\n1 boar\n2 farm, TWAL\n3 fishing ship, villagers, trade carts, sheep, turkey\n4 (any unit) archers, junk, trade cogs, ships, seige, mounted, deer(regular), monk with relic\n5 monks, BDGAL, ABGAL");
	Units_Unknown3A = new TextCtrl_Float(Units_Scroller);
	Units_Unknown3A->SetToolTip("Seems to be 1 on more or less living things");
	Units_Unknown6 = new TextCtrl_Byte(Units_Scroller);
	Units_Unknown6->SetToolTip("Seems to be 1 on all resource deposits");
	Units_Unknown7 = new TextCtrl_Byte(Units_Scroller);
	Units_Unknown7->SetToolTip("Setting to 5 can give a building a round outline,\neven if Selection Shape is set to 0 (square outline)\n0 farm, gate, dead bodies, town center\n2 buildings, gold mine\n3 berserk, flag x\n5 units\n10 mountain(matches selction mask)");
	Units_Unknown8 = new TextCtrl_Byte(Units_Scroller);
	Units_Unknown8->SetToolTip("Depends on unknowns 6 and 7:\nis a resource? and unknown selection mode\n0 wood?\n1 berry\n2 fish\n3 stone/ore deposit\n4 gold/nova deposit\n5 ore (not SW) deposit?");

	Units_Unknown11 = new TextCtrl_Byte(Units_Scroller);
	Units_Unknown16 = new TextCtrl_Byte(Units_Scroller);
	for(short loop = 0; loop < Units_Unknown16B.size(); ++loop)
	Units_Unknown16B[loop] = new TextCtrl_Float(Units_Scroller);

	Units_Unknown26 = new TextCtrl_Long(Units_Scroller);
	Units_Unknown27 = new TextCtrl_Long(Units_Scroller);
	Units_Unknown28 = new TextCtrl_Byte(Units_Scroller);
	Units_Unknown28->SetToolTip("0 projectiles, buildings, dead units, boar\n1 villagers\n2 melee\n3 mounted units\n4 relic cart, relics\n5 archers\n6 monks");

	Units_Unknown33 = new TextCtrl_Byte(Units_Scroller);
	//Units_Unknown33->SetToolTip("0 Default\n1 Counts as player being alive?");
	Units_Unknown35 = new TextCtrl_Float(Units_Scroller);
	Units_Unknown35->SetToolTip("Probably related to garrison heal");

	Units_CommandHolder_Lists = new wxBoxSizer(wxVERTICAL);
	Units_UnitHeads_Name = new wxStaticText(Units_Scroller, wxID_ANY, "Unit Header", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_UnitCommands = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Actions");
	Units_UnitCommands_Search = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_UnitCommands_Search_R = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_UnitCommands_List = new wxListBox(Units_Scroller, wxID_ANY, wxDefaultPosition, wxSize(140, 190), 0, NULL, wxLB_EXTENDED);
	Units_UnitCommands_Buttons = new wxGridSizer(3, 0, 0);
	Units_UnitCommands_Add = new wxButton(Units_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(5, 20));
	Units_UnitCommands_Insert = new wxButton(Units_Scroller, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(5, 20));
	Units_UnitCommands_Delete = new wxButton(Units_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(5, 20));
	Units_UnitCommands_Copy = new wxButton(Units_Scroller, wxID_ANY, "Copy *", wxDefaultPosition, wxSize(5, 20));
	Units_UnitCommands_Copy->SetToolTip("When \"All civs\" is not selected,\nthis and pasting works only for current civilization");
	Units_UnitCommands_Paste = new wxButton(Units_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(5, 20));
	Units_UnitCommands_PasteInsert = new wxButton(Units_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(5, 20));
	Units_UnitCommands_CopyToUnits = new wxButton(Units_Scroller, wxID_ANY, "Copy all to selected units", wxDefaultPosition, wxSize(5, 20));
	Units_CommandHolder_Data = new wxBoxSizer(wxVERTICAL);
	Units_CommandHolder_Data1 = new wxBoxSizer(wxHORIZONTAL);
	Units_CommandHolder_Data2 = new wxBoxSizer(wxVERTICAL);
	Units_CommandHolder_Grid1 = new wxGridSizer(2, 5, 5);
	Units_CommandHolder_Grid2 = new wxGridSizer(2, 5, 5);
	Units_CommandHolder_Grid3 = new wxGridSizer(1, 5, 5);
	Units_Exists = new TextCtrl_Byte(Units_Scroller);

	UnitCommands_1_Holder = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_One_Holder = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_One_Text = new wxStaticText(Units_Scroller, wxID_ANY, "One ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_One = new TextCtrl_Short(Units_Scroller);
	UnitCommands_ID_Holder = new wxBoxSizer(wxHORIZONTAL);
	UnitCommands_ID_Text = new wxStaticText(Units_Scroller, wxID_ANY, "ID ", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_ID = new TextCtrl_Short(Units_Scroller);
	UnitCommands_Type_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Type_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Action Type", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Type = new TextCtrl_Short(Units_Scroller);
	UnitCommands_Type_ComboBox = new wxOwnerDrawnComboBox(Units_Scroller, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY);
	UnitCommands_ClassID_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_ClassID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Class", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_ClassID = new TextCtrl_Short(Units_Scroller);
	Units_Class_ComboBox[1] = new ComboBox_Plus1(Units_Scroller, UnitCommands_ClassID);
	UnitCommands_UnitID_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_UnitID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unit", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_UnitID = new TextCtrl_Short(Units_Scroller);
	UnitCommands_UnitID_ComboBox = new ComboBox_Plus1(Units_Scroller, UnitCommands_UnitID);
	UnitComboBoxList.push_back(UnitCommands_UnitID_ComboBox);
	UnitCommands_Unknown2_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Unknown2_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 2", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown2 = new TextCtrl_Short(Units_Scroller);
	UnitCommands_ResourceIn_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_ResourceIn_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Resource In", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_ResourceIn = new TextCtrl_Short(Units_Scroller);
	UnitCommands_ResourceIn_ComboBox = new ComboBox_Plus1(Units_Scroller, UnitCommands_ResourceIn);
	ResourceComboBoxList.push_back(UnitCommands_ResourceIn_ComboBox);
	UnitCommands_ProductivityResource_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_ProductivityResource_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Productivity Resource *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_ProductivityResource = new TextCtrl_Short(Units_Scroller);
	UnitCommands_ProductivityResource->SetToolTip("Resource that multiplies the amount you can gather");
	UnitCommands_ProductivityResource_ComboBox = new ComboBox_Plus1(Units_Scroller, UnitCommands_ProductivityResource);
	ResourceComboBoxList.push_back(UnitCommands_ProductivityResource_ComboBox);
	UnitCommands_ResourceOut_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_ResourceOut_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Resource Out", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_ResourceOut = new TextCtrl_Short(Units_Scroller);
	UnitCommands_ResourceOut_ComboBox = new ComboBox_Plus1(Units_Scroller, UnitCommands_ResourceOut);
	ResourceComboBoxList.push_back(UnitCommands_ResourceOut_ComboBox);
	UnitCommands_Resource_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Resource_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Resource", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Resource = new TextCtrl_Short(Units_Scroller);
	UnitCommands_Resource_ComboBox = new ComboBox_Plus1(Units_Scroller, UnitCommands_Resource);
	ResourceComboBoxList.push_back(UnitCommands_Resource_ComboBox);
	UnitCommands_WorkRateMultiplier_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_WorkRateMultiplier_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Work Rate Multiplier", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_WorkRateMultiplier = new TextCtrl_Float(Units_Scroller);
	UnitCommands_ExecutionRadius_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_ExecutionRadius_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Execution Radius", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_ExecutionRadius = new TextCtrl_Float(Units_Scroller);
	UnitCommands_ExtraRange_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_ExtraRange_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Extra Range", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_ExtraRange = new TextCtrl_Float(Units_Scroller);
	UnitCommands_Graphics_Grid = new wxGridSizer(3, 5, 5);
	for(short loop = 0; loop < UnitCommands_Graphics.size(); ++loop)
	{
		UnitCommands_Graphics_Holder[loop] = new wxBoxSizer(wxVERTICAL);
		UnitCommands_Graphics[loop] = new TextCtrl_Short(Units_Scroller);
		UnitCommands_Graphics_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, UnitCommands_Graphics[loop]);
	}
	for(short loop = 0; loop < 4; ++loop)
	GraphicComboBoxList.push_back(UnitCommands_Graphics_ComboBox[loop]);
	for(short loop = 4; loop < 6; ++loop)
	SoundComboBoxList.push_back(UnitCommands_Graphics_ComboBox[loop]);
	UnitCommands_Graphics_Text[0] = new wxStaticText(Units_Scroller, wxID_ANY, " Tool Graphic *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Graphics[0]->SetToolTip("Used when walking with a tool, but carrying no resources");
	UnitCommands_Graphics_Text[1] = new wxStaticText(Units_Scroller, wxID_ANY, " Proceeding Graphic *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Graphics[1]->SetToolTip("Used when proceeding to gather a resource or attack");
	UnitCommands_Graphics_Text[2] = new wxStaticText(Units_Scroller, wxID_ANY, " Action Graphic *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Graphics[2]->SetToolTip("Used when actually gathering a resource or attacking/converting");
	UnitCommands_Graphics_Text[3] = new wxStaticText(Units_Scroller, wxID_ANY, " Carrying Graphic *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Graphics[3]->SetToolTip("Used when carrying a resource");
	UnitCommands_Graphics_Text[4] = new wxStaticText(Units_Scroller, wxID_ANY, " Execution Sound *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Graphics[4]->SetToolTip("Example: Plays when lumberjack starts chopping wood");
	UnitCommands_Graphics_Text[5] = new wxStaticText(Units_Scroller, wxID_ANY, " Resource Deposit Sound *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Graphics[5]->SetToolTip("Example: Plays when lumberjack drops his wood into TC");
	UnitCommands_Unknown1_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Unknown1_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 1", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown1 = new TextCtrl_Byte(Units_Scroller);
	UnitCommands_Unknown4_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Unknown4_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 4", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown4 = new TextCtrl_Byte(Units_Scroller);
	UnitCommands_Unknown5_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Unknown5_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 5", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown5 = new TextCtrl_Float(Units_Scroller);
	UnitCommands_SelectionEnabler_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_SelectionEnabler_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Selection Enabler *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_SelectionEnabler = new TextCtrl_Byte(Units_Scroller);
	UnitCommands_SelectionEnabler->SetToolTip("1 Allows units to select their targets\n2 ?");
	UnitCommands_Unknown7_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Unknown7_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 7", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown7 = new TextCtrl_Byte(Units_Scroller);
	UnitCommands_Unknown8_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Unknown8_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Plunder Source *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown8 = new TextCtrl_Short(Units_Scroller);
	UnitCommands_Unknown8->SetToolTip("0 Plunder from resource\n1 Plunder from players\n2 Raider thing?");
	UnitCommands_Unknown9_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Unknown9_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 9", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown9 = new TextCtrl_Short(Units_Scroller);
	UnitCommands_SelectionMode_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_SelectionMode_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Selection Mode *", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_SelectionMode = new TextCtrl_Byte(Units_Scroller);
	UnitCommands_SelectionMode->SetToolTip("Determines what you can select as targets\n0, 7+ All objects\n1 Your objects only\n2 Neutral and enemy objects only\n3 Gaia only\n4 Gaia, your and ally objects only\n5 Gaia, neutral and enemy objects only\n6 All but your objects");
	UnitCommands_Unknown11_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Unknown11_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 11", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown11 = new TextCtrl_Byte(Units_Scroller);
	UnitCommands_Unknown12_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Unknown12_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 12", wxDefaultPosition, wxSize(-1, 15), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown12 = new TextCtrl_Byte(Units_Scroller);

//	UnitControls actual interface

	Units_Type_ComboBox->Append("No Type/Invalid Type");
	Units_Type_ComboBox->Append("10 - Eye Candy");
	Units_Type_ComboBox->Append("15 - Tree (AoK)");
	Units_Type_ComboBox->Append("20 - Flag");
	Units_Type_ComboBox->Append("25 - Doppleganger");
	Units_Type_ComboBox->Append("30 - Dead/Fish");
	Units_Type_ComboBox->Append("40 - Bird");
	Units_Type_ComboBox->Append("50 - Unknown");
	Units_Type_ComboBox->Append("60 - Projectile");
	Units_Type_ComboBox->Append("70 - Living");
	Units_Type_ComboBox->Append("80 - Building");
	Units_Type_ComboBox->Append("90 - Tree (AoE)");
	Units_Type_ComboBox->SetSelection(0);

	Type20.Add("Type");
	Type20.Add("NameLength");
	Type20.Add("ID1");
	Type20.Add("LanguageDLLName");
	Type20.Add("LanguageDLLCreation");
	Type20.Add("Class");
	Type20.Add("StandingGraphic x2");
	Type20.Add("DyingGraphic x2");
	Type20.Add("DeathMode");
	Type20.Add("HitPoints");
	Type20.Add("LineOfSight");
	Type20.Add("GarrisonCapacity");
	Type20.Add("SizeRadius x2");
	Type20.Add("HPBarHeight1");
	Type20.Add("TrainSound x2");
	Type20.Add("DeadUnitID");
	Type20.Add("PlacementMode");
	Type20.Add("AirMode");
	Type20.Add("IconID");
	Type20.Add("HideInEditor");
	Type20.Add("Unknown1");
	Type20.Add("Enabled");
	Type20.Add("Disabled");
	Type20.Add("PlacementBypassTerrain x2");
	Type20.Add("PlacementTerrain x2");
	Type20.Add("EditorRadius x2");
	Type20.Add("HillMode");
	Type20.Add("VisibleInFog");
	Type20.Add("TerrainRestriction");
	Type20.Add("FlyMode");
	Type20.Add("ResourceCapacity");
	Type20.Add("ResourceDecay");
	Type20.Add("BlastType");
	Type20.Add("Unknown2");
	Type20.Add("InteractionMode");
	Type20.Add("MinimapMode");
	Type20.Add("CommandAttribute");
	Type20.Add("Unknown3A");
	Type20.Add("MinimapColor");
	Type20.Add("LanguageDLLHelp");
	Type20.Add("LanguageDLLHotKeyText");
	Type20.Add("HotKey");
	Type20.Add("Unselectable");
	Type20.Add("Unknown6");
	Type20.Add("UnknownSelectionMode");
	Type20.Add("Unknown8");
	Type20.Add("SelectionMask");
	Type20.Add("SelectionShapeType");
	Type20.Add("SelectionShape");
	Type20.Add("Attribute");
	Type20.Add("Civilization");
	Type20.Add("Nothing");
	Type20.Add("SelectionEffect");
	Type20.Add("EditorSelectionColour");
	Type20.Add("SelectionRadius x2");
	Type20.Add("HPBarHeight2");
	Type20.Add("ResourceStorages 21 bytes");
	Type20.Add("DamageGraphicCount");
	Type20.Add("DamageGraphics");
	Type20.Add("SelectionSound");
	Type20.Add("DyingSound");
	Type20.Add("AttackMode");
	Type20.Add("EdibleMeat");
	Type20.Add("Name");
	Type20.Add("NameLength2");
	Type20.Add("Name2");
	Type20.Add("Unitline");
	Type20.Add("MinTechLevel");
	Type20.Add("ID2");
	Type20.Add("ID3");

	Type20.Add("Speed");

	Type30.Add("WalkingGraphic x2");
	Type30.Add("RotationSpeed");
	Type30.Add("Unknown11");
	Type30.Add("TrackingUnit");
	Type30.Add("TrackingUnitUsed");
	Type30.Add("TrackingUnitDensity");
	Type30.Add("Unknown16");
	Type30.Add("Unknown16B 4 floats");

	Type40.Add("SheepConversion");
	Type40.Add("SearchRadius");
	Type40.Add("WorkRate");
	Type40.Add("DropSite x2");
	Type40.Add("VillagerMode");
	Type40.Add("AttackSound");
	Type40.Add("MoveSound");
	Type40.Add("AnimalMode");
	Type40.Add("CommandCount");
	Type40.Add("Commands");

	Type50.Add("DefaultArmor");
	Type50.Add("AttackCount");
	Type50.Add("Attacks");
	Type50.Add("ArmourCount");
	Type50.Add("Armours");
	Type50.Add("TerRestrictionForDmgMultiplying");
	Type50.Add("MaxRange");
	Type50.Add("BlastRadius");
	Type50.Add("ReloadTime");
	Type50.Add("ProjectileUnitID");
	Type50.Add("AccuracyPercent");
	Type50.Add("TowerMode");
	Type50.Add("FrameDelay");
	Type50.Add("GraphicDisplacement 3 floats");
	Type50.Add("BlastLevel");
	Type50.Add("MinRange");
	Type50.Add("AccuracyErrorRadius");
	Type50.Add("AttackGraphic");
	Type50.Add("DisplayedMeleeArmour");
	Type50.Add("DisplayedAttack");
	Type50.Add("DisplayedRange");
	Type50.Add("DisplayedReloadTime");

	Type60.Add("StretchMode");
	Type60.Add("CompensationMode");
	Type60.Add("DropAnimationMode");
	Type60.Add("PenetrationMode");
	Type60.Add("Unknown24");
	Type60.Add("ProjectileArc");

	Type70.Add("ResourceCosts 18 bytes");
	Type70.Add("TrainTime");
	Type70.Add("TrainLocationID");
	Type70.Add("ButtonID");
	Type70.Add("Unknown26");
	Type70.Add("Unknown27");
	Type70.Add("Unknown28");
	Type70.Add("HeroMode");
	Type70.Add("GarrisonGraphic");
	Type70.Add("DuplicatedMissilesMin");
	Type70.Add("DuplicatedMissilesMax");
	Type70.Add("MissileSpawningArea 3 floats");
	Type70.Add("AlternativeProjectileUnit");
	Type70.Add("ChargingGraphic");
	Type70.Add("ChargingMode");
	Type70.Add("DisplayedPierceArmour");

	Type80.Add("ConstructionGraphicID");
	Type80.Add("SnowGraphicID");
	Type80.Add("AdjacentMode");
	Type80.Add("GraphicsAngle");
	Type80.Add("DisappearsWhenBuilt");
	Type80.Add("StackUnitID");
	Type80.Add("FoundationTerrainID");
	Type80.Add("OldTerrainLikeID");
	Type80.Add("ResearchID");
	Type80.Add("Unknown33");
	Type80.Add("Annexes 40 bytes");
	Type80.Add("HeadUnit");
	Type80.Add("TransformUnit");
	Type80.Add("UnknownSound");
	Type80.Add("ConstructionSound");
	Type80.Add("GarrisonType");
	Type80.Add("GarrisonHealRate");
	Type80.Add("Unknown35");
	Type80.Add("PileUnit");
	Type80.Add("LootingTable 6 bytes");

	Units_SpecialCopy_Options->Append("Special: graphics only");
	Units_SpecialCopy_Options->SetSelection(0);

	Units_Buttons[0]->Add(Units_Add, 1, wxEXPAND);
	Units_Buttons[0]->Add(Units_Delete, 1, wxEXPAND);
	Units_Buttons[0]->Add(Units_Insert, 1, wxEXPAND);
	Units_Buttons[0]->Add(Units_Copy, 1, wxEXPAND);
	Units_Buttons[0]->Add(Units_Paste, 1, wxEXPAND);
	Units_Buttons[0]->Add(Units_PasteInsert, 1, wxEXPAND);
	//Units_Buttons[0]->Add(Units_Extract, 1, wxEXPAND);
	//Units_Buttons[0]->Add(Units_Import, 1, wxEXPAND);
	Units_Buttons[0]->Add(Units_Info, 1, wxEXPAND);
	Units_Buttons[1]->Add(Units_SpecialCopy, 1, wxEXPAND);
	Units_Buttons[1]->Add(Units_SpecialPaste, 1, wxEXPAND);
	Units_Buttons[1]->Add(Units_Enable, 1, wxEXPAND);
	Units_Buttons[1]->Add(Units_Disable, 1, wxEXPAND);
	Units_Special->Add(Units_SpecialCopy_Options, 1, wxEXPAND);
	Units_Special->AddSpacer(2);
	Units_Special->Add(Units_SpecialCopy_Civs, 0, wxEXPAND);

	Units_Searches[0]->Add(Units_Search, 1, wxEXPAND);
	Units_Searches[0]->AddSpacer(2);
	Units_Searches[0]->Add(Units_UseAnd[0], 0, wxEXPAND);
	Units_Searches[1]->Add(Units_Search_R, 1, wxEXPAND);
	Units_Searches[1]->AddSpacer(2);
	Units_Searches[1]->Add(Units_UseAnd[1], 0, wxEXPAND);

	Units_Units->Add(Units_Civs_List, 0, wxEXPAND);
	Units_Units->AddSpacer(2);
	for(short loop = 0; loop < 2; ++loop)
	Units_Units->Add(Units_Searches[loop], 0, wxEXPAND);
	Units_Units->Add(Units_FilterSelector, 0, wxEXPAND);
	for(short loop = 0; loop < 2; ++loop)
	Units_Units->Add(Units_SearchFilters[loop], 0, wxEXPAND);
	Units_Units->AddSpacer(2);
	Units_Units->Add(Units_List, 1, wxEXPAND);
	Units_Units->AddSpacer(2);
	Units_Units->Add(Units_Buttons[0], 0, wxEXPAND);
	//Units_Units->Add(Units_Line, 0, wxEXPAND);
	Units_Units->Add(Units_Buttons[1], 0, wxEXPAND);
	Units_Units->AddSpacer(2);
	Units_Units->Add(Units_Special, 0, wxEXPAND);

	Units_ListArea->AddSpacer(5);
	Units_ListArea->Add(Units_Units, 1, wxEXPAND);
	Units_ListArea->AddSpacer(5);

	Units_Type_Holder->Add(Units_Type_Text, 0, wxEXPAND);
	Units_Type_Holder->Add(Units_Type, 1, wxEXPAND);
	Units_Type_Holder->Add(Units_Type_ComboBox, 2, wxEXPAND);
	Units_Type_Holder->AddSpacer(5);
	Units_Type_Holder->Add(Units_Class_Text, 0, wxEXPAND);
	Units_Type_Holder->Add(Units_Class, 1, wxEXPAND);
	Units_Type_Holder->Add(Units_Class_ComboBox[0], 2, wxEXPAND);
	Units_Type_Holder->AddStretchSpacer(1);

//	Type 10+

	Units_ID1_Holder->Add(Units_ID1_Text, 0, wxEXPAND);
	Units_HitPoints_Holder->Add(Units_HitPoints_Text, 0, wxEXPAND);
	Units_LineOfSight_Holder->Add(Units_LineOfSight_Text, 0, wxEXPAND);
	Units_GarrisonCapacity_Holder->Add(Units_GarrisonCapacity_Text, 0, wxEXPAND);
	Units_SizeRadius_Holder->Add(Units_SizeRadius_Text, 0, wxEXPAND);
	Units_HPBarHeight1_Holder->Add(Units_HPBarHeight1_Text, 0, wxEXPAND);
	Units_DeadUnitID_Holder->Add(Units_DeadUnitID_Text, 0, wxEXPAND);
	Units_PlacementMode_Holder->Add(Units_PlacementMode_Text, 0, wxEXPAND);
	Units_IconID_Holder->Add(Units_IconID_Text, 0, wxEXPAND);
	Units_Unknown1_Holder->Add(Units_Unknown1_Text, 0, wxEXPAND);
	Units_PlacementBypassTerrain_Holder->Add(Units_PlacementBypassTerrain_Text, 0, wxEXPAND);
	Units_PlacementTerrain_Holder->Add(Units_PlacementTerrain_Text, 0, wxEXPAND);
	Units_EditorRadius_Holder->Add(Units_EditorRadius_Text, 0, wxEXPAND);
	Units_HillMode_Holder->Add(Units_HillMode_Text, 0, wxEXPAND);
	Units_TerrainRestriction_Holder->Add(Units_TerrainRestriction_Text, 0, wxEXPAND);
	Units_ResourceCapacity_Holder->Add(Units_ResourceCapacity_Text, 0, wxEXPAND);
	Units_ResourceDecay_Holder->Add(Units_ResourceDecay_Text, 0, wxEXPAND);
	Units_BlastType_Holder->Add(Units_BlastType_Text, 0, wxEXPAND);
	Units_Unknown2_Holder->Add(Units_Unknown2_Text, 0, wxEXPAND);
	Units_InteractionMode_Holder->Add(Units_InteractionMode_Text, 0, wxEXPAND);
	Units_MinimapMode_Holder->Add(Units_MinimapMode_Text, 0, wxEXPAND);
	Units_CommandAttribute_Holder->Add(Units_CommandAttribute_Text, 0, wxEXPAND);
	Units_Unknown3A_Holder->Add(Units_Unknown3A_Text, 0, wxEXPAND);
	Units_MinimapColor_Holder->Add(Units_MinimapColor_Text, 0, wxEXPAND);
	Units_Unknown6_Holder->Add(Units_Unknown6_Text, 0, wxEXPAND);
	Units_Unknown7_Holder->Add(Units_Unknown7_Text, 0, wxEXPAND);
	Units_Unknown8_Holder->Add(Units_Unknown8_Text, 0, wxEXPAND);
	Units_SelectionMask_Holder->Add(Units_SelectionMask_Text, 0, wxEXPAND);
	Units_SelectionShapeType_Holder->Add(Units_SelectionShapeType_Text, 0, wxEXPAND);
	Units_SelectionShape_Holder->Add(Units_SelectionShape_Text, 0, wxEXPAND);
	Units_Civ_Holder->Add(Units_Civ_Text, 0, wxEXPAND);
	Units_Unknown9_Holder->Add(Units_Unknown9_Text, 0, wxEXPAND);
	Units_Attribute_Holder->Add(Units_Attribute_Text, 0, wxEXPAND);
	Units_SelectionEffect_Holder->Add(Units_SelectionEffect_Text, 0, wxEXPAND);
	Units_EditorSelectionColour_Holder->Add(Units_EditorSelectionColour_Text, 0, wxEXPAND);
	Units_SelectionRadius_Holder->Add(Units_SelectionRadius_Text, 0, wxEXPAND);
	Units_HPBarHeight2_Holder->Add(Units_HPBarHeight2_Text, 0, wxEXPAND);
	Units_SelectionSound_Holder->Add(Units_SelectionSound_Text, 0, wxEXPAND);
	Units_DyingSound_Holder->Add(Units_DyingSound_Text, 0, wxEXPAND);
	Units_AttackMode_Holder->Add(Units_AttackMode_Text, 0, wxEXPAND);
	Units_EdibleMeat_Holder->Add(Units_EdibleMeat_Text, 0, wxEXPAND);
	Units_Name_Holder->Add(Units_Name_Text, 0, wxEXPAND);
	Units_Name2_Holder->Add(Units_Name2_Text, 0, wxEXPAND);
	Units_Unitline_Holder->Add(Units_Unitline_Text, 0, wxEXPAND);
	Units_MinTechLevel_Holder->Add(Units_MinTechLevel_Text, 0, wxEXPAND);
	Units_ID2_Holder->Add(Units_ID2_Text, 0, wxEXPAND);
	Units_ID3_Holder->Add(Units_ID3_Text, 0, wxEXPAND);

//	Type 20+

	Units_Speed_Holder->Add(Units_Speed_Text, 0, wxEXPAND);

//	Type 30+

	Units_RotationSpeed_Holder->Add(Units_RotationSpeed_Text, 0, wxEXPAND);
	Units_Unknown11_Holder->Add(Units_Unknown11_Text, 0, wxEXPAND);
	Units_TrackingUnit_Holder->Add(Units_TrackingUnit_Text, 0, wxEXPAND);
	Units_TrackingUnitUsed_Holder->Add(Units_TrackingUnitUsed_Text, 0, wxEXPAND);
	Units_TrackingUnitDensity_Holder->Add(Units_TrackingUnitDensity_Text, 0, wxEXPAND);
	Units_Unknown16_Holder->Add(Units_Unknown16_Text, 0, wxEXPAND);
	Units_Unknown16B_Holder->Add(Units_Unknown16B_Text, 0, wxEXPAND);

//	Type 40+

	Units_SearchRadius_Holder->Add(Units_SearchRadius_Text, 0, wxEXPAND);
	Units_WorkRate_Holder->Add(Units_WorkRate_Text, 0, wxEXPAND);
	Units_AttributesDropSite_Holder->Add(Units_DropSite_Text, 0, wxEXPAND);
	Units_VillagerMode_Holder->Add(Units_VillagerMode_Text, 0, wxEXPAND);
	Units_AttackSound_Holder->Add(Units_AttackSound_Text, 0, wxEXPAND);
	Units_MoveSound_Holder->Add(Units_MoveSound_Text, 0, wxEXPAND);
	Units_Exists_Holder->Add(Units_Exists_Text, 0, wxEXPAND);

//	Type 50+

	Units_DefaultArmor_Holder->Add(Units_DefaultArmor_Text, 0, wxEXPAND);
	Units_TerRestrictionForDmgMultiply_Holder->Add(Units_TerRestrictionForDmgMultiply_Text, 0, wxEXPAND);
	Units_MaxRange_Holder->Add(Units_MaxRange_Text, 0, wxEXPAND);
	Units_BlastRadius_Holder->Add(Units_BlastRadius_Text, 0, wxEXPAND);
	Units_ReloadTime1_Holder->Add(Units_ReloadTime1_Text, 0, wxEXPAND);
	Units_AccuracyPercent_Holder->Add(Units_AccuracyPercent_Text, 0, wxEXPAND);
	Units_Delay_Holder->Add(Units_Delay_Text, 0, wxEXPAND);
	Units_GraphicDisplacement_Holder->Add(Units_GraphicDisplacement_Text, 0, wxEXPAND);
	Units_BlastLevel_Holder->Add(Units_BlastLevel_Text, 0, wxEXPAND);
	Units_MinRange_Holder->Add(Units_MinRange_Text, 0, wxEXPAND);
	Units_AccuracyErrorRadius_Holder->Add(Units_AccuracyErrorRadius_Text, 0, wxEXPAND);
	Units_AttackGraphic_Holder->Add(Units_AttackGraphic_Text, 0, wxEXPAND);
	Units_DisplayedMeleeArmour_Holder->Add(Units_DisplayedMeleeArmour_Text, 0, wxEXPAND);
	Units_DisplayedAttack_Holder->Add(Units_DisplayedAttack_Text, 0, wxEXPAND);
	Units_DisplayedRange_Holder->Add(Units_DisplayedRange_Text, 0, wxEXPAND);
	Units_ReloadTime2_Holder->Add(Units_ReloadTime2_Text, 0, wxEXPAND);

//	Type 60 only

	Units_StretchMode_Holder->Add(Units_StretchMode_Text, 0, wxEXPAND);
	Units_CompensationMode_Holder->Add(Units_CompensationMode_Text, 0, wxEXPAND);
	Units_DropAnimationMode_Holder->Add(Units_DropAnimationMode_Text, 0, wxEXPAND);
	Units_PenetrationMode_Holder->Add(Units_PenetrationMode_Text, 0, wxEXPAND);
	Units_Unknown24_Holder->Add(Units_Unknown24_Text, 0, wxEXPAND);
	Units_ProjectileArc_Holder->Add(Units_ProjectileArc_Text, 0, wxEXPAND);

//	Type 70+

	Units_CostType_Holder->Add(Units_CostType_Text, 2, wxEXPAND);
	Units_CostAmount_Holder->Add(Units_CostAmount_Text, 2, wxEXPAND);
	Units_CostUsed_Holder->Add(Units_CostUsed_Text, 2, wxEXPAND);
	Units_TrainTime_Holder->Add(Units_TrainTime_Text, 0, wxEXPAND);
	Units_TrainLocationID_Holder->Add(Units_TrainLocationID_Text, 0, wxEXPAND);
	Units_ButtonID_Holder->Add(Units_ButtonID_Text, 0, wxEXPAND);
	Units_Unknown26_Holder->Add(Units_Unknown26_Text, 0, wxEXPAND);
	Units_Unknown27_Holder->Add(Units_Unknown27_Text, 0, wxEXPAND);
	Units_Unknown28_Holder->Add(Units_Unknown28_Text, 0, wxEXPAND);
	Units_AttackMissileDuplicationAmount1_Holder->Add(Units_AttackMissileDuplicationAmount1_Text, 0, wxEXPAND);
	Units_AttackMissileDuplicationAmount2_Holder->Add(Units_AttackMissileDuplicationAmount2_Text, 0, wxEXPAND);
	Units_AttackMissileDuplicationSpawning_Holder->Add(Units_AttackMissileDuplicationSpawning_Text, 0, wxEXPAND);
	Units_ChargingMode_Holder->Add(Units_ChargingMode_Text, 0, wxEXPAND);
	Units_DisplayedPierceArmour_Holder->Add(Units_DisplayedPierceArmour_Text, 0, wxEXPAND);

//	Type 80

	Units_ConstructionGraphicID_Holder->Add(Units_ConstructionGraphicID_Text, 0, wxEXPAND);
	Units_SnowGraphicID_Holder->Add(Units_SnowGraphicID_Text, 0, wxEXPAND);
	Units_IconDisabler_Holder->Add(Units_IconDisabler_Text, 0, wxEXPAND);
	Units_StackUnitID_Holder->Add(Units_StackUnitID_Text, 0, wxEXPAND);
	Units_TerrainID_Holder->Add(Units_TerrainID_Text, 0, wxEXPAND);
	Units_OldTerrainLikeID_Holder->Add(Units_OldTerrainLikeID_Text, 0, wxEXPAND);
	Units_ResearchID_Holder->Add(Units_ResearchID_Text, 0, wxEXPAND);
	Units_Unknown33_Holder->Add(Units_Unknown33_Text, 0, wxEXPAND);
	Units_AnnexUnit1_Holder->Add(Units_AnnexUnit_Text, 0, wxEXPAND);
	Units_AnnexUnitMisplacement1_Holder->Add(Units_AnnexUnitMisplacement_Text, 0, wxEXPAND);
	Units_HeadUnit_Holder->Add(Units_HeadUnit_Text, 0, wxEXPAND);
	Units_TransformUnit_Holder->Add(Units_TransformUnit_Text, 0, wxEXPAND);
	Units_UnknownSound_Holder->Add(Units_UnknownSound_Text, 0, wxEXPAND);
	Units_ConstructionSound_Holder->Add(Units_ConstructionSound_Text, 0, wxEXPAND);
	Units_GarrisonHealRate_Holder->Add(Units_GarrisonHealRate_Text, 0, wxEXPAND);
	Units_Unknown35_Holder->Add(Units_Unknown35_Text, 0, wxEXPAND);
	Units_PileUnit_Holder->Add(Units_PileUnit_Text, 0, wxEXPAND);
	Units_LootSwitch_Holder->Add(Units_LootSwitch_Text, 0, wxEXPAND);

//	Type 10+

	Units_ID1_Holder->Add(Units_ID1, 1, wxEXPAND);
	Units_DeathMode_Holder->Add(Units_DeathMode, 0, wxEXPAND);
	Units_DeathMode_Holder->AddSpacer(2);
	Units_DeathMode_Holder->Add(Units_DeathMode_CheckBox, 2, wxEXPAND);
	Units_HitPoints_Holder->Add(Units_HitPoints, 1, wxEXPAND);
	Units_LineOfSight_Holder->Add(Units_LineOfSight, 1, wxEXPAND);
	Units_GarrisonCapacity_Holder->Add(Units_GarrisonCapacity, 0, wxEXPAND);
	for(short loop = 0; loop < 2; ++loop)
	Units_SizeRadius_Grid->Add(Units_SizeRadius[loop], 1, wxEXPAND);
	Units_SizeRadius_Holder->Add(Units_SizeRadius_Grid, 1, wxEXPAND);
	Units_HPBarHeight1_Holder->Add(Units_HPBarHeight1, 1, wxEXPAND);
	Units_DeadUnitID_Holder->Add(Units_DeadUnitID, 1, wxEXPAND);
	Units_DeadUnitID_Holder->Add(Units_DeadUnitID_ComboBox, 1, wxEXPAND);
	Units_PlacementMode_Holder->Add(Units_PlacementMode, 0, wxEXPAND);
	Units_AirMode_Holder->Add(Units_AirMode, 0, wxEXPAND);
	Units_AirMode_Holder->AddSpacer(2);
	Units_AirMode_Holder->Add(Units_AirMode_CheckBox, 2, wxEXPAND);
	Units_IconID_Holder->Add(Units_IconID, 0, wxEXPAND);
	Units_HideInEditor_Holder->Add(Units_HideInEditor, 0, wxEXPAND);
	Units_HideInEditor_Holder->AddSpacer(2);
	Units_HideInEditor_Holder->Add(Units_HideInEditor_CheckBox, 2, wxEXPAND);
	Units_Unknown1_Holder->Add(Units_Unknown1, 1, wxEXPAND);
	Units_Enabled_Holder->Add(Units_Enabled, 0, wxEXPAND);
	Units_Enabled_Holder->AddSpacer(2);
	Units_Enabled_Holder->Add(Units_Enabled_CheckBox, 2, wxEXPAND);
	Units_Disabled_Holder->Add(Units_Disabled, 0, wxEXPAND);
	Units_Disabled_Holder->AddSpacer(2);
	Units_Disabled_Holder->Add(Units_Disabled_CheckBox, 2, wxEXPAND);
	for(short loop = 0; loop < 2; ++loop)
	Units_PlacementBypassTerrainGrid_Holder->Add(Units_PlacementBypassTerrain[loop], 1, wxEXPAND);
	for(short loop = 0; loop < 2; ++loop)
	Units_PlacementBypassTerrainGrid_Holder->Add(Units_PlacementBypassTerrain_ComboBox[loop], 1, wxEXPAND);
	Units_PlacementBypassTerrain_Holder->Add(Units_PlacementBypassTerrainGrid_Holder, 0, wxEXPAND);
	for(short loop = 0; loop < 2; ++loop)
	Units_PlacementTerrainGrid_Holder->Add(Units_PlacementTerrain[loop], 1, wxEXPAND);
	for(short loop = 0; loop < 2; ++loop)
	Units_PlacementTerrainGrid_Holder->Add(Units_PlacementTerrain_ComboBox[loop], 1, wxEXPAND);
	Units_PlacementTerrain_Holder->Add(Units_PlacementTerrainGrid_Holder, 0, wxEXPAND);
	for(short loop = 0; loop < 2; ++loop)
	Units_EditorRadius_Grid->Add(Units_EditorRadius[loop], 1, wxEXPAND);
	Units_EditorRadius_Holder->Add(Units_EditorRadius_Grid, 1, wxEXPAND);
	Units_HillMode_Holder->Add(Units_HillMode, 0, wxEXPAND);
	Units_VisibleInFog_Holder->Add(Units_VisibleInFog_Text, 0, wxEXPAND);
	Units_VisibleInFog_Holder->Add(Units_VisibleInFog, 0, wxEXPAND);
	Units_TerrainRestriction_Holder->Add(Units_TerrainRestriction, 1, wxEXPAND);
	Units_TerrainRestriction_Holder->Add(Units_TerrainRestriction_ComboBox, 1, wxEXPAND);
	Units_FlyMode_Holder->Add(Units_FlyMode, 0, wxEXPAND);
	Units_FlyMode_Holder->AddSpacer(2);
	Units_FlyMode_Holder->Add(Units_FlyMode_CheckBox, 2, wxEXPAND);
	Units_ResourceCapacity_Holder->Add(Units_ResourceCapacity, 1, wxEXPAND);
	Units_ResourceDecay_Holder->Add(Units_ResourceDecay, 1, wxEXPAND);
	Units_BlastType_Holder->Add(Units_BlastType, 1, wxEXPAND);
	Units_Unknown2_Holder->Add(Units_Unknown2, 1, wxEXPAND);
	Units_InteractionMode_Holder->Add(Units_InteractionMode, 1, wxEXPAND);
	Units_MinimapMode_Holder->Add(Units_MinimapMode, 1, wxEXPAND);
	Units_CommandAttribute_Holder->Add(Units_CommandAttribute, 0, wxEXPAND);
	Units_Unknown3A_Holder->Add(Units_Unknown3A, 0, wxEXPAND);
	Units_MinimapColor_Holder->Add(Units_MinimapColor, 0, wxEXPAND);
	Units_Unselectable_Holder->Add(Units_Unselectable_CheckBox, 0, wxEXPAND);
	Units_Unselectable_Holder->Add(Units_Unselectable, 1, wxEXPAND);
	Units_Unknown6_Holder->Add(Units_Unknown6, 1, wxEXPAND);
	Units_Unknown7_Holder->Add(Units_Unknown7, 0, wxEXPAND);
	Units_Unknown8_Holder->Add(Units_Unknown8, 1, wxEXPAND);
	Units_SelectionMask_Holder->Add(Units_SelectionMask, 0, wxEXPAND);
	Units_SelectionShapeType_Holder->Add(Units_SelectionShapeType, 0, wxEXPAND);
	Units_SelectionShape_Holder->Add(Units_SelectionShape, 0, wxEXPAND);
	for(short loop = 0; loop < 8; ++loop)
	Units_Attribute_Grid->Add(Units_Attribute_CheckBox[loop], 1, wxEXPAND);
	Units_Attribute_Holder->Add(Units_Attribute, 1, wxEXPAND);
	Units_Attribute_Holder->Add(Units_Attribute_Grid, 1, wxEXPAND);
	Units_Civ_Holder->Add(Units_Civ, 1, wxEXPAND);
	Units_Civ_Holder->Add(Units_Civ_ComboBox, 1, wxEXPAND);
	Units_Unknown9_Holder->Add(Units_Unknown9, 0, wxEXPAND);
	Units_SelectionEffect_Holder->Add(Units_SelectionEffect, 0, wxEXPAND);
	Units_EditorSelectionColour_Holder->Add(Units_EditorSelectionColour, 0, wxEXPAND);
	for(short loop = 0; loop < 2; ++loop)
	Units_SelectionRadiusBox->Add(Units_SelectionRadius[loop], 1, wxEXPAND);
	Units_SelectionRadius_Holder->Add(Units_SelectionRadiusBox, 1, wxEXPAND);
	Units_HPBarHeight2_Holder->Add(Units_HPBarHeight2, 1, wxEXPAND);
	Units_SelectionSound_Holder->Add(Units_SelectionSound, 1, wxEXPAND);
	Units_SelectionSound_Holder->Add(Units_SelectionSound_ComboBox, 1, wxEXPAND);
	Units_DyingSound_Holder->Add(Units_DyingSound, 1, wxEXPAND);
	Units_DyingSound_Holder->Add(Units_DyingSound_ComboBox, 1, wxEXPAND);
	Units_AttackMode_Holder->Add(Units_AttackMode, 0, wxEXPAND);
	Units_EdibleMeat_Holder->Add(Units_EdibleMeat, 0, wxEXPAND);
	Units_Name_Holder->Add(Units_Name, 1, wxEXPAND);
	Units_Name2_Holder->Add(Units_Name2, 1, wxEXPAND);
	Units_Unitline_Holder->Add(Units_Unitline, 1, wxEXPAND);
	Units_Unitline_Holder->Add(Units_Unitline_ComboBox, 1, wxEXPAND);
	Units_MinTechLevel_Holder->Add(Units_MinTechLevel, 0, wxEXPAND);
	Units_MinTechLevel_Holder->Add(Units_MinTechLevel_ComboBox, 0, wxEXPAND);
	Units_ID2_Holder->Add(Units_ID2, 1, wxEXPAND);
	Units_ID3_Holder->Add(Units_ID3, 1, wxEXPAND);

//	Type 20+

	Units_Speed_Holder->Add(Units_Speed, 1, wxEXPAND);

//	Type 30+

	Units_RotationSpeed_Holder->Add(Units_RotationSpeed, 1, wxEXPAND);
	Units_Unknown11_Holder->Add(Units_Unknown11, 1, wxEXPAND);
	Units_TrackingUnit_Holder->Add(Units_TrackingUnit, 1, wxEXPAND);
	Units_TrackingUnit_Holder->Add(Units_TrackingUnit_ComboBox, 1, wxEXPAND);
	Units_TrackingUnitUsedBox_Holder->Add(Units_TrackingUnitUsed, 2, wxEXPAND);
	Units_TrackingUnitUsed_Holder->Add(Units_TrackingUnitUsedBox_Holder, 0, wxEXPAND);
	Units_TrackingUnitDensity_Holder->Add(Units_TrackingUnitDensity, 0, wxEXPAND);
	Units_Unknown16_Holder->Add(Units_Unknown16, 0, wxEXPAND);
	for(short loop = 0; loop < Units_Unknown16B.size(); ++loop)
	Units_Unknown16B_Grid->Add(Units_Unknown16B[loop], 1, wxEXPAND);
	Units_Unknown16B_Holder->Add(Units_Unknown16B_Grid, 0, wxEXPAND);

//	Type 40+

	Units_SheepConversion_Holder->Add(Units_SheepConversion, 0, wxEXPAND);
	Units_SheepConversion_Holder->AddSpacer(2);
	Units_SheepConversion_Holder->Add(Units_SheepConversion_CheckBox, 2, wxEXPAND);
	Units_SearchRadius_Holder->Add(Units_SearchRadius, 1, wxEXPAND);
	Units_WorkRate_Holder->Add(Units_WorkRate, 1, wxEXPAND);
	Units_DropSite_Grid->Add(Units_DropSite[0], 1, wxEXPAND);
	Units_DropSite_Grid->Add(Units_DropSite[1], 1, wxEXPAND);
	Units_DropSite_Grid->AddStretchSpacer(1);
	Units_DropSite_Grid->AddStretchSpacer(1);
	Units_DropSite_Grid->Add(Units_DropSite_ComboBox[0], 2, wxEXPAND);
	Units_DropSite_Grid->Add(Units_DropSite_ComboBox[1], 2, wxEXPAND);
	Units_VillagerMode_Holder->Add(Units_VillagerMode, 1, wxEXPAND);
	Units_AttackSound_Holder->Add(Units_AttackSound, 1, wxEXPAND);
	Units_AttackSound_Holder->Add(Units_AttackSound_ComboBox, 1, wxEXPAND);
	Units_MoveSound_Holder->Add(Units_MoveSound, 1, wxEXPAND);
	Units_MoveSound_Holder->Add(Units_MoveSound_ComboBox, 1, wxEXPAND);
	Units_AnimalMode_Holder->Add(Units_AnimalMode, 0, wxEXPAND);
	Units_AnimalMode_Holder->AddSpacer(2);
	Units_AnimalMode_Holder->Add(Units_AnimalMode_CheckBox, 2, wxEXPAND);
	Units_Exists_Holder->Add(Units_Exists, 1, wxEXPAND);

//	Type 50+

	Units_DefaultArmor_Holder->Add(Units_DefaultArmor, 1, wxEXPAND);
	Units_TerRestrictionForDmgMultiply_Holder->Add(Units_TerRestrictionForDmgMultiply, 1, wxEXPAND);
	Units_TerRestrictionForDmgMultiply_Holder->Add(Units_TerRestrictionForDmgMultiply_ComboBox, 1, wxEXPAND);
	Units_MaxRange_Holder->Add(Units_MaxRange, 1, wxEXPAND);
	Units_BlastRadius_Holder->Add(Units_BlastRadius, 1, wxEXPAND);
	Units_ReloadTime1_Holder->Add(Units_ReloadTime1, 1, wxEXPAND);
	Units_AccuracyPercent_Holder->Add(Units_AccuracyPercent, 1, wxEXPAND);
	Units_TowerMode_Holder->Add(Units_TowerMode, 0, wxEXPAND);
	Units_TowerMode_Holder->AddSpacer(2);
	Units_TowerMode_Holder->Add(Units_TowerMode_CheckBox, 2, wxEXPAND);
	Units_Delay_Holder->Add(Units_Delay, 1, wxEXPAND);
	for(short loop = 0; loop < 3; ++loop)
	Units_GraphicDisplacement_Grid->Add(Units_GraphicDisplacement[loop], 1, wxEXPAND);
	Units_GraphicDisplacement_Holder->Add(Units_GraphicDisplacement_Grid, 1, wxEXPAND);
	Units_BlastLevel_Holder->Add(Units_BlastLevel, 1, wxEXPAND);
	Units_MinRange_Holder->Add(Units_MinRange, 1, wxEXPAND);
	Units_AccuracyErrorRadius_Holder->Add(Units_AccuracyErrorRadius, 0, wxEXPAND);
	Units_AttackGraphic_Holder->Add(Units_AttackGraphic, 1, wxEXPAND);
	Units_AttackGraphic_Holder->Add(Units_AttackGraphic_ComboBox, 1, wxEXPAND);
	Units_DisplayedMeleeArmour_Holder->Add(Units_DisplayedMeleeArmour, 1, wxEXPAND);
	Units_DisplayedAttack_Holder->Add(Units_DisplayedAttack, 1, wxEXPAND);
	Units_DisplayedRange_Holder->Add(Units_DisplayedRange, 1, wxEXPAND);
	Units_ReloadTime2_Holder->Add(Units_ReloadTime2, 1, wxEXPAND);

//	Type 60 only

	Units_StretchMode_Holder->Add(Units_StretchMode, 1, wxEXPAND);
	Units_CompensationMode_Holder->Add(Units_CompensationMode, 1, wxEXPAND);
	Units_DropAnimationMode_Holder->Add(Units_DropAnimationMode, 1, wxEXPAND);
	Units_PenetrationMode_Holder->Add(Units_PenetrationMode, 1, wxEXPAND);
	Units_Unknown24_Holder->Add(Units_Unknown24, 1, wxEXPAND);
	Units_ProjectileArc_Holder->Add(Units_ProjectileArc, 1, wxEXPAND);

//	Type 70+

	for(short loop = 0; loop < 3; ++loop)
	Units_CostType_Grid->Add(Units_CostType[loop], 1, wxEXPAND);
	for(short loop = 0; loop < 3; ++loop)
	Units_CostType_Grid->Add(Units_CostType_ComboBox[loop], 1, wxEXPAND);
	Units_CostType_Holder->Add(Units_CostType_Grid, 12, wxEXPAND);
	Units_CostAmount_Holder->Add(Units_CostAmount[0], 4, wxEXPAND);
	Units_CostAmount_Holder->AddSpacer(5);
	Units_CostAmount_Holder->Add(Units_CostAmount[1], 4, wxEXPAND);
	Units_CostAmount_Holder->AddSpacer(5);
	Units_CostAmount_Holder->Add(Units_CostAmount[2], 4, wxEXPAND);
	Units_CostUsed_Holder->Add(Units_CostUsed[0], 3, wxEXPAND);
	Units_CostUsed_Holder->AddSpacer(2);
	Units_CostUsed_Holder->Add(Units_CostUsed_CheckBox[0], 1, wxEXPAND);
	Units_CostUsed_Holder->AddSpacer(5);
	Units_CostUsed_Holder->Add(Units_CostUsed[1], 3, wxEXPAND);
	Units_CostUsed_Holder->AddSpacer(2);
	Units_CostUsed_Holder->Add(Units_CostUsed_CheckBox[1], 1, wxEXPAND);
	Units_CostUsed_Holder->AddSpacer(5);
	Units_CostUsed_Holder->Add(Units_CostUsed[2], 3, wxEXPAND);
	Units_CostUsed_Holder->AddSpacer(2);
	Units_CostUsed_Holder->Add(Units_CostUsed_CheckBox[2], 1, wxEXPAND);
	Units_TrainTime_Holder->Add(Units_TrainTime, 0, wxEXPAND);
	Units_TrainLocationID_Holder->Add(Units_TrainLocationID, 1, wxEXPAND);
	Units_TrainLocationID_Holder->Add(Units_TrainLocationID_ComboBox, 1, wxEXPAND);
	Units_ButtonID_Holder->Add(Units_ButtonID, 0, wxEXPAND);
	Units_Unknown26_Holder->Add(Units_Unknown26, 1, wxEXPAND);
	Units_Unknown27_Holder->Add(Units_Unknown27, 1, wxEXPAND);
	Units_Unknown28_Holder->Add(Units_Unknown28, 1, wxEXPAND);
	Units_HeroMode_Holder->Add(Units_HeroMode, 0, wxEXPAND);
	Units_HeroMode_Holder->AddSpacer(2);
	Units_HeroMode_Holder->Add(Units_HeroMode_CheckBox, 2, wxEXPAND);
	Units_AttackMissileDuplicationAmount1_Holder->Add(Units_AttackMissileDuplicationAmount1, 1, wxEXPAND);
	Units_AttackMissileDuplicationAmount2_Holder->Add(Units_AttackMissileDuplicationAmount2, 1, wxEXPAND);
	for(short loop = 0; loop < 3; ++loop)
	Units_AttackMissileDuplicationSpawning_Grid->Add(Units_AttackMissileDuplicationSpawning[loop], 1, wxEXPAND);
	Units_AttackMissileDuplicationSpawning_Holder->Add(Units_AttackMissileDuplicationSpawning_Grid, 1, wxEXPAND);
	Units_ChargingMode_Holder->Add(Units_ChargingMode, 0, wxEXPAND);
	Units_DisplayedPierceArmour_Holder->Add(Units_DisplayedPierceArmour, 1, wxEXPAND);

//	Type 80

	Units_ConstructionGraphicID_Holder->Add(Units_ConstructionGraphicID, 1, wxEXPAND);
	Units_ConstructionGraphicID_Holder->Add(Units_ConstructionGraphicID_ComboBox, 1, wxEXPAND);
	Units_SnowGraphicID_Holder->Add(Units_SnowGraphicID, 1, wxEXPAND);
	Units_SnowGraphicID_Holder->Add(Units_SnowGraphicID_ComboBox, 1, wxEXPAND);
	Units_AdjacentMode_Holder->Add(Units_AdjacentMode, 0, wxEXPAND);
	Units_AdjacentMode_Holder->AddSpacer(2);
	Units_AdjacentMode_Holder->Add(Units_AdjacentMode_CheckBox, 2, wxEXPAND);
	Units_Unknown31b_Holder->Add(Units_DisappearsWhenBuilt, 0, wxEXPAND);
	Units_Unknown31b_Holder->AddSpacer(2);
	Units_Unknown31b_Holder->Add(Units_Unknown31b_CheckBox, 2, wxEXPAND);
	Units_IconDisabler_Holder->Add(Units_IconDisabler, 0, wxEXPAND);
	Units_StackUnitID_Holder->Add(Units_StackUnitID, 1, wxEXPAND);
	Units_StackUnitID_Holder->Add(Units_StackUnitID_ComboBox, 1, wxEXPAND);
	Units_TerrainID_Holder->Add(Units_TerrainID, 1, wxEXPAND);
	Units_TerrainID_Holder->Add(Units_TerrainID_ComboBox, 1, wxEXPAND);
	Units_OldTerrainLikeID_Holder->Add(Units_OldTerrainLikeID, 0, wxEXPAND);
	Units_ResearchID_Holder->Add(Units_ResearchID, 1, wxEXPAND);
	Units_ResearchID_Holder->Add(Units_ResearchID_ComboBox, 1, wxEXPAND);
	Units_Unknown33_Holder->Add(Units_Unknown33, 1, wxEXPAND);
	for(short loop = 0; loop < 4; ++loop)
	Units_AnnexUnit_Grid->Add(Units_AnnexUnit[loop], 1, wxEXPAND);
	for(short loop = 0; loop < 4; ++loop)
	Units_AnnexUnit_Grid->Add(Units_AnnexUnit_ComboBox[loop], 1, wxEXPAND);
	Units_AnnexUnit1_Holder->Add(Units_AnnexUnit_Grid, 0, wxEXPAND);
	for(short loop = 0; loop < 4; ++loop)
	Units_AnnexUnitMisplacement_Grid->Add(Units_AnnexUnitMisplacement[loop][0], 1, wxEXPAND);
	for(short loop = 0; loop < 4; ++loop)
	Units_AnnexUnitMisplacement_Grid->Add(Units_AnnexUnitMisplacement[loop][1], 1, wxEXPAND);
	Units_AnnexUnitMisplacement1_Holder->Add(Units_AnnexUnitMisplacement_Grid, 0, wxEXPAND);
	Units_HeadUnit_Holder->Add(Units_HeadUnit, 1, wxEXPAND);
	Units_HeadUnit_Holder->Add(Units_HeadUnit_ComboBox, 1, wxEXPAND);
	Units_TransformUnit_Holder->Add(Units_TransformUnit, 1, wxEXPAND);
	Units_TransformUnit_Holder->Add(Units_TransformUnit_ComboBox, 1, wxEXPAND);
	Units_UnknownSound_Holder->Add(Units_UnknownSound, 1, wxEXPAND);
	Units_UnknownSound_Holder->Add(Units_UnknownSound_ComboBox, 1, wxEXPAND);
	Units_ConstructionSound_Holder->Add(Units_ConstructionSound, 1, wxEXPAND);
	Units_ConstructionSound_Holder->Add(Units_ConstructionSound_ComboBox, 1, wxEXPAND);
	Units_GarrisonHealRate_Holder->Add(Units_GarrisonHealRate, 0, wxEXPAND);
	Units_Unknown35_Holder->Add(Units_Unknown35, 1, wxEXPAND);
	Units_PileUnit_Holder->Add(Units_PileUnit, 1, wxEXPAND);
	Units_PileUnit_Holder->Add(Units_PileUnit_ComboBox, 1, wxEXPAND);
	for(short loop = 0; loop < Units_LootSwitch.size(); ++loop)
	Units_LootSwitch_Grid->Add(Units_LootSwitch[loop], 1, wxEXPAND);
	Units_LootSwitch_Holder->Add(Units_LootSwitch_Grid, 0, wxEXPAND);

	for(short loop = 0; loop < 3; ++loop)
	Units_ResourceStorage_Grid->Add(ResourceStorage_Type[loop], 1, wxEXPAND);
	for(short loop = 0; loop < 3; ++loop)
	Units_ResourceStorage_Grid->Add(ResourceStorage_Type_ComboBox[loop], 1, wxEXPAND);
	Units_ResourceStorage_Holder[0]->Add(ResourceStorage_Type_Text, 2, wxEXPAND);
	Units_ResourceStorage_Holder[0]->Add(Units_ResourceStorage_Grid, 12, wxEXPAND);
	Units_ResourceStorage_Holder[1]->Add(ResourceStorage_Amount_Text, 2, wxEXPAND);
	Units_ResourceStorage_Holder[1]->Add(ResourceStorage_Amount[0], 4, wxEXPAND);
	Units_ResourceStorage_Holder[1]->AddSpacer(5);
	Units_ResourceStorage_Holder[1]->Add(ResourceStorage_Amount[1], 4, wxEXPAND);
	Units_ResourceStorage_Holder[1]->AddSpacer(5);
	Units_ResourceStorage_Holder[1]->Add(ResourceStorage_Amount[2], 4, wxEXPAND);
	Units_ResourceStorage_Holder[2]->Add(ResourceStorage_Enabled_Text, 2, wxEXPAND);
	Units_ResourceStorage_Holder[2]->Add(ResourceStorage_Enabled[0], 4, wxEXPAND);
	Units_ResourceStorage_Holder[2]->AddSpacer(5);
	Units_ResourceStorage_Holder[2]->Add(ResourceStorage_Enabled[1], 4, wxEXPAND);
	Units_ResourceStorage_Holder[2]->AddSpacer(5);
	Units_ResourceStorage_Holder[2]->Add(ResourceStorage_Enabled[2], 4, wxEXPAND);

	Attacks_Class_Holder->Add(Attacks_Class_Text, 0, wxEXPAND);
	Attacks_Class_Holder->Add(Attacks_Class, 1, wxEXPAND);
	Attacks_Class_Holder->Add(Attacks_Class_ComboBox[0], 1, wxEXPAND);
	Attacks_Amount_Holder->Add(Attacks_Amount_Text, 0, wxEXPAND);
	Attacks_Amount_Holder->Add(Attacks_Amount, 1, wxEXPAND);

	Units_Attacks_Buttons->Add(Units_Attacks_Add, 1, wxEXPAND);
	Units_Attacks_Buttons->Add(Units_Attacks_Delete, 1, wxEXPAND);
	Units_Attacks_Buttons->Add(Units_Attacks_Insert, 1, wxEXPAND);
	Units_Attacks_Buttons->Add(Units_Attacks_Copy, 1, wxEXPAND);
	Units_Attacks_Buttons->Add(Units_Attacks_Paste, 1, wxEXPAND);
	Units_Attacks_Buttons->Add(Units_Attacks_PasteInsert, 1, wxEXPAND);

	Units_Attacks_ListArea->Add(Units_Attacks_Search, 0, wxEXPAND);
	Units_Attacks_ListArea->Add(Units_Attacks_Search_R, 0, wxEXPAND);
	Units_Attacks_ListArea->AddSpacer(2);
	Units_Attacks_ListArea->Add(Units_Attacks_List, 1, wxEXPAND);
	Units_Attacks_ListArea->AddSpacer(2);
	Units_Attacks_ListArea->Add(Units_Attacks_Buttons, 0, wxEXPAND);
	Units_Attacks_ListArea->AddSpacer(2);
	Units_Attacks_ListArea->Add(Units_Attacks_CopyToUnits, 0, wxEXPAND);

	Armors_Class_Holder->Add(Armors_Class_Text, 0, wxEXPAND);
	Armors_Class_Holder->Add(Armors_Class, 1, wxEXPAND);
	Armors_Class_Holder->Add(Attacks_Class_ComboBox[1], 1, wxEXPAND);
	Armors_Amount_Holder->Add(Armors_Amount_Text, 0, wxEXPAND);
	Armors_Amount_Holder->Add(Armors_Amount, 1, wxEXPAND);

	Units_Armors_Buttons->Add(Units_Armors_Add, 1, wxEXPAND);
	Units_Armors_Buttons->Add(Units_Armors_Delete, 1, wxEXPAND);
	Units_Armors_Buttons->Add(Units_Armors_Insert, 1, wxEXPAND);
	Units_Armors_Buttons->Add(Units_Armors_Copy, 1, wxEXPAND);
	Units_Armors_Buttons->Add(Units_Armors_Paste, 1, wxEXPAND);
	Units_Armors_Buttons->Add(Units_Armors_PasteInsert, 1, wxEXPAND);

	Units_Armors_ListArea->Add(Units_Armors_Search, 0, wxEXPAND);
	Units_Armors_ListArea->Add(Units_Armors_Search_R, 0, wxEXPAND);
	Units_Armors_ListArea->AddSpacer(2);
	Units_Armors_ListArea->Add(Units_Armors_List, 1, wxEXPAND);
	Units_Armors_ListArea->AddSpacer(2);
	Units_Armors_ListArea->Add(Units_Armors_Buttons, 0, wxEXPAND);
	Units_Armors_ListArea->AddSpacer(2);
	Units_Armors_ListArea->Add(Units_Armors_CopyToUnits, 0, wxEXPAND);

	UnitCommands_One_Holder->Add(UnitCommands_One_Text, 0, wxEXPAND);
	UnitCommands_One_Holder->Add(UnitCommands_One, 1, wxEXPAND);
	UnitCommands_ID_Holder->Add(UnitCommands_ID_Text, 0, wxEXPAND);
	UnitCommands_ID_Holder->Add(UnitCommands_ID, 1, wxEXPAND);
	UnitCommands_Unknown1_Holder->Add(UnitCommands_Unknown1_Text, 0, wxEXPAND);
	UnitCommands_Unknown1_Holder->Add(UnitCommands_Unknown1, 0, wxEXPAND);
	UnitCommands_Type_Holder->Add(UnitCommands_Type_Text, 0, wxEXPAND);
	UnitCommands_Type_Holder->Add(UnitCommands_Type, 0, wxEXPAND);
	UnitCommands_Type_Holder->Add(UnitCommands_Type_ComboBox, 0, wxEXPAND);
	UnitCommands_ProductivityResource_Holder->Add(UnitCommands_ProductivityResource_Text, 0, wxEXPAND);
	UnitCommands_ProductivityResource_Holder->Add(UnitCommands_ProductivityResource, 0, wxEXPAND);
	UnitCommands_ProductivityResource_Holder->Add(UnitCommands_ProductivityResource_ComboBox, 0, wxEXPAND);
	UnitCommands_ClassID_Holder->Add(UnitCommands_ClassID_Text, 0, wxEXPAND);
	UnitCommands_ClassID_Holder->Add(UnitCommands_ClassID, 0, wxEXPAND);
	UnitCommands_ClassID_Holder->Add(Units_Class_ComboBox[1], 0, wxEXPAND);
	UnitCommands_UnitID_Holder->Add(UnitCommands_UnitID_Text, 0, wxEXPAND);
	UnitCommands_UnitID_Holder->Add(UnitCommands_UnitID, 0, wxEXPAND);
	UnitCommands_UnitID_Holder->Add(UnitCommands_UnitID_ComboBox, 0, wxEXPAND);
	UnitCommands_Unknown2_Holder->Add(UnitCommands_Unknown2_Text, 0, wxEXPAND);
	UnitCommands_Unknown2_Holder->Add(UnitCommands_Unknown2, 0, wxEXPAND);
	UnitCommands_ResourceIn_Holder->Add(UnitCommands_ResourceIn_Text, 0, wxEXPAND);
	UnitCommands_ResourceIn_Holder->Add(UnitCommands_ResourceIn, 0, wxEXPAND);
	UnitCommands_ResourceIn_Holder->Add(UnitCommands_ResourceIn_ComboBox, 0, wxEXPAND);
	UnitCommands_ResourceOut_Holder->Add(UnitCommands_ResourceOut_Text, 0, wxEXPAND);
	UnitCommands_ResourceOut_Holder->Add(UnitCommands_ResourceOut, 0, wxEXPAND);
	UnitCommands_ResourceOut_Holder->Add(UnitCommands_ResourceOut_ComboBox, 0, wxEXPAND);
	UnitCommands_Resource_Holder->Add(UnitCommands_Resource_Text, 0, wxEXPAND);
	UnitCommands_Resource_Holder->Add(UnitCommands_Resource, 0, wxEXPAND);
	UnitCommands_Resource_Holder->Add(UnitCommands_Resource_ComboBox, 0, wxEXPAND);
	UnitCommands_WorkRateMultiplier_Holder->Add(UnitCommands_WorkRateMultiplier_Text, 0, wxEXPAND);
	UnitCommands_WorkRateMultiplier_Holder->Add(UnitCommands_WorkRateMultiplier, 0, wxEXPAND);
	UnitCommands_ExecutionRadius_Holder->Add(UnitCommands_ExecutionRadius_Text, 0, wxEXPAND);
	UnitCommands_ExecutionRadius_Holder->Add(UnitCommands_ExecutionRadius, 0, wxEXPAND);
	UnitCommands_ExtraRange_Holder->Add(UnitCommands_ExtraRange_Text, 0, wxEXPAND);
	UnitCommands_ExtraRange_Holder->Add(UnitCommands_ExtraRange, 0, wxEXPAND);
	UnitCommands_Unknown4_Holder->Add(UnitCommands_Unknown4_Text, 0, wxEXPAND);
	UnitCommands_Unknown4_Holder->Add(UnitCommands_Unknown4, 0, wxEXPAND);
	UnitCommands_Unknown5_Holder->Add(UnitCommands_Unknown5_Text, 0, wxEXPAND);
	UnitCommands_Unknown5_Holder->Add(UnitCommands_Unknown5, 0, wxEXPAND);
	UnitCommands_SelectionEnabler_Holder->Add(UnitCommands_SelectionEnabler_Text, 0, wxEXPAND);
	UnitCommands_SelectionEnabler_Holder->Add(UnitCommands_SelectionEnabler, 0, wxEXPAND);
	UnitCommands_Unknown7_Holder->Add(UnitCommands_Unknown7_Text, 0, wxEXPAND);
	UnitCommands_Unknown7_Holder->Add(UnitCommands_Unknown7, 0, wxEXPAND);
	UnitCommands_Unknown8_Holder->Add(UnitCommands_Unknown8_Text, 0, wxEXPAND);
	UnitCommands_Unknown8_Holder->Add(UnitCommands_Unknown8, 0, wxEXPAND);
	UnitCommands_Unknown9_Holder->Add(UnitCommands_Unknown9_Text, 0, wxEXPAND);
	UnitCommands_Unknown9_Holder->Add(UnitCommands_Unknown9, 0, wxEXPAND);
	UnitCommands_SelectionMode_Holder->Add(UnitCommands_SelectionMode_Text, 0, wxEXPAND);
	UnitCommands_SelectionMode_Holder->Add(UnitCommands_SelectionMode, 0, wxEXPAND);
	UnitCommands_Unknown11_Holder->Add(UnitCommands_Unknown11_Text, 0, wxEXPAND);
	UnitCommands_Unknown11_Holder->Add(UnitCommands_Unknown11, 0, wxEXPAND);
	UnitCommands_Unknown12_Holder->Add(UnitCommands_Unknown12_Text, 0, wxEXPAND);
	UnitCommands_Unknown12_Holder->Add(UnitCommands_Unknown12, 0, wxEXPAND);

	for(short loop = 0; loop < UnitCommands_Graphics.size(); ++loop)
	{
		UnitCommands_Graphics_Holder[loop]->Add(UnitCommands_Graphics_Text[loop], 0, wxEXPAND);
		UnitCommands_Graphics_Holder[loop]->Add(UnitCommands_Graphics[loop], 0, wxEXPAND);
		UnitCommands_Graphics_Holder[loop]->Add(UnitCommands_Graphics_ComboBox[loop], 0, wxEXPAND);
		UnitCommands_Graphics_Grid->Add(UnitCommands_Graphics_Holder[loop], 1, wxEXPAND);
	}

	Units_TypeArea_Holder->Add(Units_Name_Holder, 3, wxEXPAND);
	Units_TypeArea_Holder->AddSpacer(5);
	Units_TypeArea_Holder->Add(Units_Name2_Holder, 3, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Units_TypeArea_Holder->AddSpacer(5);
	Units_TypeArea_Holder->Add(Units_ID1_Holder, 1, wxEXPAND);
	Units_TypeArea_Holder->AddSpacer(5);
	Units_TypeArea_Holder->Add(Units_ID2_Holder, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Units_TypeArea_Holder->AddSpacer(5);
	Units_TypeArea_Holder->Add(Units_ID3_Holder, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);

	Units_LanguageDLLName_Holder->Add(Units_LanguageDLLName_Text, 0, wxEXPAND);
	Units_LanguageDLLName_Holder->Add(Units_LanguageDLLName, 1, wxEXPAND);
	Units_LanguageDLLName_Holder->Add(Units_DLL_LanguageName, 1, wxEXPAND);
	Units_LanguageDLLCreation_Holder->Add(Units_LanguageDLLCreation_Text, 0, wxEXPAND);
	Units_LanguageDLLCreation_Holder->Add(Units_LanguageDLLCreation, 1, wxEXPAND);
	Units_LanguageDLLCreation_Holder->Add(Units_DLL_LanguageCreation, 1, wxEXPAND);
	Units_LanguageDLLHelp_Holder->Add(Units_LanguageDLLHelp_Text, 0, wxEXPAND);
	Units_LanguageDLLHelp_Holder->Add(Units_LanguageDLLHelp, 1, wxEXPAND);
	Units_LanguageDLLConverter_Holder[0]->Add(Units_LanguageDLLConverter_Text[0], 0, wxEXPAND);
	Units_LanguageDLLConverter_Holder[0]->Add(Units_LanguageDLLConverter[0], 1, wxEXPAND);
	Units_LanguageDLLHotKeyText_Holder->Add(Units_LanguageDLLHotKeyText_Text, 0, wxEXPAND);
	Units_LanguageDLLHotKeyText_Holder->Add(Units_LanguageDLLHotKeyText, 1, wxEXPAND);
	Units_LanguageDLLConverter_Holder[1]->Add(Units_LanguageDLLConverter_Text[1], 0, wxEXPAND);
	Units_LanguageDLLConverter_Holder[1]->Add(Units_LanguageDLLConverter[1], 1, wxEXPAND);
	Units_HotKey_Holder->Add(Units_HotKey_Text, 0, wxEXPAND);
	Units_HotKey_Holder->Add(Units_HotKey, 1, wxEXPAND);
	Units_HotKey_Holder->Add(Units_DLL_HotKey4, 1, wxEXPAND);

	Units_LangRegular_Holder->Add(Units_LanguageDLLName_Holder, 1, wxEXPAND);
	Units_LangRegular_Holder->AddSpacer(5);
	Units_LangRegular_Holder->Add(Units_LanguageDLLCreation_Holder, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Units_LangRegular_Holder->AddSpacer(5);
	Units_LangRegular_Holder->Add(Units_HotKey_Holder, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Units_LangHotKey_Holder->Add(Units_LanguageDLLHelp_Holder, 1, wxEXPAND);
	Units_LangHotKey_Holder->AddSpacer(5);
	Units_LangHotKey_Holder->Add(Units_LanguageDLLConverter_Holder[0], 1, wxEXPAND);
	Units_LangHotKey_Holder->AddSpacer(5);
	Units_LangHotKey_Holder->Add(Units_LanguageDLLHotKeyText_Holder, 1, wxEXPAND);
	Units_LangHotKey_Holder->AddSpacer(5);
	Units_LangHotKey_Holder->Add(Units_LanguageDLLConverter_Holder[1], 1, wxEXPAND);

	Units_LangDLLArea_Holder->Add(Units_LangRegular_Holder, 0, wxEXPAND);
	Units_LangDLLArea_Holder->AddSpacer(5);
	Units_LangDLLArea_Holder->Add(Units_LangHotKey_Holder, 0, wxEXPAND);
	Units_LangDLLArea_Holder->AddSpacer(5);
	Units_LangDLLArea_Holder->Add(Units_DLL_LanguageHelp, 0, wxEXPAND);
	Units_LangDLLArea_Holder->Add(Units_DLL_LanguageHKText, 0, wxEXPAND);

	Units_StandingGraphic_Grid->Add(Units_StandingGraphic[0], 1, wxEXPAND);
	Units_StandingGraphic_Grid->Add(Units_StandingGraphic[1], 1, wxEXPAND);
	Units_StandingGraphic_Grid->Add(Units_StandingGraphic_ComboBox[0], 1, wxEXPAND);
	Units_StandingGraphic_Grid->Add(Units_StandingGraphic_ComboBox[1], 1, wxEXPAND);
	Units_StandingGraphic_Holder->Add(Units_StandingGraphic_Text, 0, wxEXPAND);
	Units_StandingGraphic_Holder->Add(Units_StandingGraphic_Grid, 0, wxEXPAND);
	Units_GarrisonGraphic_Holder->Add(Units_GarrisonGraphic_Text, 0, wxEXPAND);
	Units_GarrisonGraphic_Holder->Add(Units_GarrisonGraphic, 0, wxEXPAND);
	Units_GarrisonGraphic_Holder->Add(Units_GarrisonGraphic_ComboBox, 0, wxEXPAND);
	Units_WalkingGraphic_Grid->Add(Units_WalkingGraphic[0], 1, wxEXPAND);
	Units_WalkingGraphic_Grid->Add(Units_WalkingGraphic[1], 1, wxEXPAND);
	Units_WalkingGraphic_Grid->Add(Units_WalkingGraphic_ComboBox[0], 1, wxEXPAND);
	Units_WalkingGraphic_Grid->Add(Units_WalkingGraphic_ComboBox[1], 1, wxEXPAND);
	Units_WalkingGraphic_Holder->Add(Units_WalkingGraphic_Text, 0, wxEXPAND);
	Units_WalkingGraphic_Holder->Add(Units_WalkingGraphic_Grid, 0, wxEXPAND);
	Units_DyingGraphic_Grid->Add(Units_DyingGraphic[0], 1, wxEXPAND);
	Units_DyingGraphic_Grid->Add(Units_DyingGraphic[1], 1, wxEXPAND);
	Units_DyingGraphic_Grid->Add(Units_DyingGraphic_ComboBox[0], 1, wxEXPAND);
	Units_DyingGraphic_Grid->Add(Units_DyingGraphic_ComboBox[1], 1, wxEXPAND);
	Units_DyingGraphic_Holder->Add(Units_DyingGraphic_Text, 0, wxEXPAND);
	Units_DyingGraphic_Holder->Add(Units_DyingGraphic_Grid, 0, wxEXPAND);

	Units_IconID_Grid->Add(Units_IconID_Holder, 1, wxEXPAND);
	Units_IconID_Grid->Add(Units_IconDisabler_Holder, 1, wxEXPAND);
	Units_GraphicsArea4_Holder->Add(Units_IconID_Grid, 1, wxEXPAND);
	Units_GraphicsArea4_Holder->Add(Units_StandingGraphic_Holder, 1, wxEXPAND);
	Units_GraphicsArea4_Holder->Add(Units_DyingGraphic_Holder, 1, wxEXPAND);
	Units_GraphicsArea4_Holder->Add(Units_WalkingGraphic_Holder, 1, wxEXPAND);

	Units_GraphicsArea5_Holder->Add(Units_SnowGraphicID_Holder, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Units_GraphicsArea5_Holder->Add(Units_ConstructionGraphicID_Holder, 1, wxEXPAND);
	Units_GraphicsArea5_Holder->Add(Units_AttackGraphic_Holder, 1, wxEXPAND);
	Units_GraphicsArea5_Holder->Add(Units_GarrisonGraphic_Holder, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);

	DamageGraphics_GraphicID_Holder->Add(DamageGraphics_GraphicID_Text, 0, wxEXPAND);
	DamageGraphics_GraphicID_Holder->Add(DamageGraphics_GraphicID, 1, wxEXPAND);
	DamageGraphics_GraphicID_Holder->Add(DamageGraphics_GraphicID_ComboBox, 1, wxEXPAND);
	DamageGraphics_Unknown1_Holder->Add(DamageGraphics_Unknown1_Text, 0, wxEXPAND);
	DamageGraphics_Unknown1_Holder->Add(DamageGraphics_Unknown1, 1, wxEXPAND);
	DamageGraphics_DamagePercent_Holder->Add(DamageGraphics_DamagePercent_Text, 0, wxEXPAND);
	DamageGraphics_DamagePercent_Holder->Add(DamageGraphics_DamagePercent, 1, wxEXPAND);
	DamageGraphics_Unknown2_Holder->Add(DamageGraphics_Unknown2_Text, 0, wxEXPAND);
	DamageGraphics_Unknown2_Holder->Add(DamageGraphics_Unknown2, 1, wxEXPAND);
	Units_DamageGraphics_Holder_Data->Add(DamageGraphics_GraphicID_Holder, 0, wxEXPAND);
	Units_DamageGraphics_Holder_Data->AddSpacer(5);
	Units_DamageGraphics_Holder_Data->Add(DamageGraphics_DamagePercent_Holder, 0, wxEXPAND);
	Units_DamageGraphics_Holder_Data->AddSpacer(5);
	Units_DamageGraphics_Holder_Data->Add(DamageGraphics_Unknown1_Holder, 0, wxEXPAND);
	Units_DamageGraphics_Holder_Data->AddSpacer(5);
	Units_DamageGraphics_Holder_Data->Add(DamageGraphics_Unknown2_Holder, 0, wxEXPAND);

	Units_DamageGraphics_Buttons->Add(Units_DamageGraphics_Add, 1, wxEXPAND);
	Units_DamageGraphics_Buttons->Add(Units_DamageGraphics_Delete, 1, wxEXPAND);
	Units_DamageGraphics_Buttons->Add(Units_DamageGraphics_Insert, 1, wxEXPAND);
	Units_DamageGraphics_Buttons->Add(Units_DamageGraphics_Copy, 1, wxEXPAND);
	Units_DamageGraphics_Buttons->Add(Units_DamageGraphics_Paste, 1, wxEXPAND);
	Units_DamageGraphics_Buttons->Add(Units_DamageGraphics_PasteInsert, 1, wxEXPAND);

	Units_DamageGraphics_ListArea->Add(Units_DamageGraphics_Search, 0, wxEXPAND);
	Units_DamageGraphics_ListArea->Add(Units_DamageGraphics_Search_R, 0, wxEXPAND);
	Units_DamageGraphics_ListArea->AddSpacer(2);
	Units_DamageGraphics_ListArea->Add(Units_DamageGraphics_List, 1, wxEXPAND);
	Units_DamageGraphics_ListArea->AddSpacer(2);
	Units_DamageGraphics_ListArea->Add(Units_DamageGraphics_Buttons, 0, wxEXPAND);
	Units_DamageGraphics_ListArea->AddSpacer(2);
	Units_DamageGraphics_ListArea->Add(Units_DamageGraphics_CopyToUnits, 0, wxEXPAND);

	Units_DamageGraphics->Add(Units_DamageGraphics_ListArea, 1, wxEXPAND);
	Units_DamageGraphics->AddSpacer(5);
	Units_DamageGraphics->Add(Units_DamageGraphics_Holder_Data, 1, wxEXPAND);

	Units_GraphicsArea1_Holder->Add(Units_DamageGraphics, 1, wxEXPAND);
	Units_GraphicsArea1_Holder->AddSpacer(5);
	Units_GraphicsArea1_Holder->Add(Units_GraphicsArea4_Holder, 1, wxEXPAND);

	Units_GraphicsArea_Holder->Add(Units_GraphicsArea1_Holder, 0, wxEXPAND);
	Units_GraphicsArea_Holder->AddSpacer(5);
	Units_GraphicsArea_Holder->Add(Units_GraphicsArea5_Holder, 0, wxEXPAND);

	Units_StatsArea1_Grid->Add(Units_HitPoints_Holder, 1, wxEXPAND);
	Units_StatsArea1_Grid->Add(Units_Speed_Holder, 1, wxEXPAND);
	Units_StatsArea1_Grid->Add(Units_RotationSpeed_Holder, 1, wxEXPAND);
	Units_StatsArea1_Grid->AddStretchSpacer(1);
	Units_StatsArea1_Grid->AddStretchSpacer(1);
	Units_StatsArea1_Grid->Add(Units_LineOfSight_Holder, 1, wxEXPAND);
	Units_StatsArea1_Grid->Add(Units_SearchRadius_Holder, 1, wxEXPAND);
	Units_StatsArea1_Grid->Add(Units_MaxRange_Holder, 1, wxEXPAND);
	Units_StatsArea1_Grid->Add(Units_MinRange_Holder, 1, wxEXPAND);
	Units_StatsArea1_Grid->Add(Units_DisplayedRange_Holder, 1, wxEXPAND);

	Units_Attacks_DataArea->Add(Attacks_Amount_Holder, 0, wxEXPAND);
	Units_Attacks_DataArea->AddSpacer(5);
	Units_Attacks_DataArea->Add(Attacks_Class_Holder, 0, wxEXPAND);
	Units_Attacks_Grid_Data2->Add(Units_DisplayedAttack_Holder, 1, wxEXPAND);
	Units_Attacks_Grid_Data2->Add(Units_Delay_Holder, 1, wxEXPAND);
	Units_Attacks_Grid_Data2->Add(Units_AccuracyPercent_Holder, 1, wxEXPAND);
	Units_Attacks_Grid_Data2->Add(Units_AccuracyErrorRadius_Holder, 1, wxEXPAND);
	Units_Attacks_Grid_Data2->Add(Units_ReloadTime1_Holder, 1, wxEXPAND);
	Units_Attacks_Grid_Data2->Add(Units_ReloadTime2_Holder, 1, wxEXPAND);
	Units_Attacks_Grid_Data2->Add(Units_BlastRadius_Holder, 1, wxEXPAND);
	Units_Attacks_Grid_Data2->Add(Units_BlastLevel_Holder, 1, wxEXPAND);
	Units_Attacks_Holder_Data->AddSpacer(5);
	Units_Attacks_Holder_Data->Add(Units_Attacks_Grid_Data2, 0, wxEXPAND);

	Units_Armors_DataArea->Add(Armors_Amount_Holder, 0, wxEXPAND);
	Units_Armors_DataArea->Add(Armors_Class_Holder, 0, wxEXPAND);
	Units_Armors_Holder_Data3->AddSpacer(5);
	Units_Armors_Holder_Data3->Add(Units_DefaultArmor_Holder, 0, wxEXPAND);
	Units_Armors_Holder_Data3->AddSpacer(5);
	Units_Armors_Holder_Data3->Add(Units_TerRestrictionForDmgMultiply_Holder, 0, wxEXPAND);
	Units_Armors_Holder_Data3->AddSpacer(5);
	Units_Armors_Holder_Data3->Add(Units_DisplayedMeleeArmour_Holder, 0, wxEXPAND);
	Units_Armors_Holder_Data3->AddSpacer(5);
	Units_Armors_Holder_Data3->Add(Units_DisplayedPierceArmour_Holder, 0, wxEXPAND);

	for(short loop = 0; loop < 8; ++loop)
	Units_GarrisonType_Grid->Add(Units_GarrisonType_CheckBox[loop], 1, wxEXPAND);
	Units_GarrisonType_Holder->Add(Units_GarrisonType_Text, 0, wxEXPAND);
	Units_GarrisonType_Holder->Add(Units_GarrisonType, 1, wxEXPAND);
	Units_GarrisonType_Holder->Add(Units_GarrisonType_Grid, 1, wxEXPAND);

	Units_Attacks->Add(Units_Attacks_ListArea, 1, wxEXPAND);
	Units_Attacks->AddSpacer(5);
	Units_Attacks->Add(Units_Attacks_DataArea, 1, wxEXPAND);
	Units_Armors->Add(Units_Armors_ListArea, 1, wxEXPAND);
	Units_Armors->AddSpacer(5);
	Units_Armors->Add(Units_Armors_DataArea, 1, wxEXPAND);
	Units_Attacks_Holder->Add(Units_Attacks, 1, wxEXPAND);
	Units_Attacks_Holder->AddSpacer(5);
	Units_Attacks_Holder->Add(Units_Attacks_Holder_Data, 1, wxEXPAND);
	Units_Armors_Holder->Add(Units_Armors, 2, wxEXPAND);
	Units_Armors_Holder->AddSpacer(5);
	Units_Armors_Holder->Add(Units_Armors_Holder_Data3, 1, wxEXPAND);
	Units_Armors_Holder->AddStretchSpacer(1);
	Units_StatsAreaGarrison_Grid->Add(Units_GarrisonCapacity_Holder, 1, wxEXPAND);
	Units_StatsAreaGarrison_Grid->Add(Units_GarrisonType_Holder, 2, wxEXPAND);
	Units_StatsAreaGarrison_Grid->Add(Units_GarrisonHealRate_Holder, 1, wxEXPAND);
	Units_StatsArea2_Grid->Add(Units_ResourceCapacity_Holder, 1, wxEXPAND);
	Units_StatsArea2_Grid->Add(Units_ResourceDecay_Holder, 1, wxEXPAND);
	Units_StatsArea2_Grid->Add(Units_WorkRate_Holder, 1, wxEXPAND);

	Units_StatsArea_Holder->Add(Units_StatsArea1_Grid, 0, wxEXPAND);
	Units_StatsArea_Holder->AddSpacer(5);
	Units_StatsArea_Holder->Add(Units_Attacks_Holder, 0, wxEXPAND);
	Units_StatsArea_Holder->AddSpacer(5);
	Units_StatsArea_Holder->Add(Units_Armors_Holder, 0, wxEXPAND);
	Units_StatsArea_Holder->AddSpacer(5);
	Units_StatsArea_Holder->Add(Units_StatsArea2_Grid, 0, wxEXPAND);
	Units_StatsArea_Holder->AddSpacer(5);
	Units_StatsArea_Holder->Add(Units_StatsAreaGarrison_Grid, 0, wxEXPAND);


	Units_ProjectileUnitID_Holder->Add(Units_ProjectileUnitID_Text, 0, wxEXPAND);
	Units_ProjectileUnitID_Holder->Add(Units_ProjectileUnitID, 1, wxEXPAND);
	Units_ProjectileUnitID_Holder->Add(Units_ProjectileUnitID_ComboBox, 1, wxEXPAND);
	Units_AttackMissileDuplicationUnit_Holder->Add(Units_AttackMissileDuplicationUnit_Text, 0, wxEXPAND);
	Units_AttackMissileDuplicationUnit_Holder->Add(Units_AttackMissileDuplicationUnit, 1, wxEXPAND);
	Units_AttackMissileDuplicationUnit_Holder->Add(Units_AttackMissileDuplicationUnit_ComboBox, 1, wxEXPAND);
	Units_ChargingGraphic_Holder->Add(Units_ChargingGraphic_Text, 0, wxEXPAND);
	Units_ChargingGraphic_Holder->Add(Units_ChargingGraphic, 1, wxEXPAND);
	Units_ChargingGraphic_Holder->Add(Units_ChargingGraphic_ComboBox, 1, wxEXPAND);

	Units_ProjectilesArea1_Grid->Add(Units_StretchMode_Holder, 1, wxEXPAND);
	Units_ProjectilesArea1_Grid->Add(Units_CompensationMode_Holder, 1, wxEXPAND);
	Units_ProjectilesArea1_Grid->Add(Units_DropAnimationMode_Holder, 1, wxEXPAND);
	Units_ProjectilesArea1_Grid->AddStretchSpacer(1);
	Units_ProjectilesArea1_Grid->AddStretchSpacer(1);
	Units_ProjectilesArea1_Grid->Add(Units_PenetrationMode_Holder, 1, wxEXPAND);
	Units_ProjectilesArea1_Grid->Add(Units_Unknown24_Holder, 1, wxEXPAND);
	Units_ProjectilesArea1_Grid->Add(Units_ProjectileArc_Holder, 1, wxEXPAND);

	Units_ProjectilesArea2_Grid->Add(Units_ProjectileUnitID_Holder, 2, wxEXPAND);
	Units_ProjectilesArea3_Grid->Add(Units_AttackMissileDuplicationAmount1_Holder, 1, wxEXPAND);
	Units_ProjectilesArea3_Grid->Add(Units_AttackMissileDuplicationAmount2_Holder, 1, wxEXPAND);
	Units_ProjectilesArea2_Grid->Add(Units_AttackMissileDuplicationUnit_Holder, 1, wxEXPAND);
	Units_ProjectilesArea2_Grid->Add(Units_ChargingGraphic_Holder, 1, wxEXPAND);
	Units_ProjectilesArea2_Grid->Add(Units_ChargingMode_Holder, 1, wxEXPAND);

	Units_ProjectilesArea_Holder->Add(Units_ProjectilesArea2_Grid, 0, wxEXPAND);
	Units_ProjectilesArea_Holder->AddSpacer(5);
	Units_ProjectilesArea_Holder->Add(Units_ProjectilesArea3_Grid, 0, wxEXPAND);
	Units_ProjectilesArea_Holder->AddSpacer(5);
	Units_ProjectilesArea_Holder->Add(Units_AttackMissileDuplicationSpawning_Holder, 0, wxEXPAND);
	Units_ProjectilesArea_Holder->AddSpacer(5);
	Units_ProjectilesArea_Holder->Add(Units_GraphicDisplacement_Holder, 0, wxEXPAND);
	Units_ProjectilesArea_Holder->AddSpacer(5);
	Units_ProjectilesArea_Holder->Add(Units_ProjectilesArea1_Grid, 0, wxEXPAND);

	Units_AttributesBoxes1_Grid->Add(Units_Enabled_Holder, 1, wxEXPAND);
	Units_AttributesBoxes1_Grid->Add(Units_Disabled_Holder, 1, wxEXPAND);
	Units_AttributesBoxes1_Grid->Add(Units_DeathMode_Holder, 1, wxEXPAND);
	Units_AttributesBoxes1_Grid->Add(Units_HideInEditor_Holder, 1, wxEXPAND);
	Units_AttributesBoxes1_Grid->Add(Units_AirMode_Holder, 1, wxEXPAND);
	Units_AttributesBoxes1_Grid->Add(Units_FlyMode_Holder, 1, wxEXPAND);
	Units_AttributesBoxes1_Grid->Add(Units_SheepConversion_Holder, 1, wxEXPAND);
	Units_AttributesBoxes1_Grid->Add(Units_AnimalMode_Holder, 1, wxEXPAND);
	Units_AttributesBoxes1_Grid->Add(Units_AdjacentMode_Holder, 1, wxEXPAND);
	Units_AttributesBoxes1_Grid->Add(Units_Unknown31b_Holder, 1, wxEXPAND);
	Units_AttributesBoxes1_Grid->Add(Units_TowerMode_Holder, 1, wxEXPAND);
	Units_AttributesBoxes1_Grid->Add(Units_HeroMode_Holder, 1, wxEXPAND);

	Units_AttributesModes1_Grid->Add(Units_PlacementMode_Holder, 1, wxEXPAND);
	Units_AttributesModes1_Grid->Add(Units_HillMode_Holder, 1, wxEXPAND);
	Units_AttributesModes1_Grid->Add(Units_VisibleInFog_Holder, 1, wxEXPAND);
	Units_AttributesModes1_Grid->Add(Units_InteractionMode_Holder, 1, wxEXPAND);
	Units_AttributesModes1_Grid->Add(Units_MinimapMode_Holder, 1, wxEXPAND);
	Units_AttributesModes1_Grid->Add(Units_MinimapColor_Holder, 1, wxEXPAND);
	Units_AttributesModes1_Grid->Add(Units_AttackMode_Holder, 1, wxEXPAND);
	Units_AttributesModes1_Grid->Add(Units_EdibleMeat_Holder, 1, wxEXPAND);
	Units_AttributesModes1_Grid->Add(Units_VillagerMode_Holder, 1, wxEXPAND);

	Units_Attributes2_Grid->Add(Units_Attribute_Holder, 1, wxEXPAND);
	Units_AttributesTerrain_Holder->Add(Units_PlacementTerrain_Holder, 1, wxEXPAND);
	Units_AttributesTerrain_Holder->AddSpacer(5);
	Units_AttributesTerrain_Holder->Add(Units_PlacementBypassTerrain_Holder, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Units_AttributesTerrain_Grid->Add(Units_TerrainRestriction_Holder, 1, wxEXPAND);
	Units_AttributesDropSite_Holder->Add(Units_DropSite_Grid, 0, wxEXPAND);
	Units_AttributesSizes_Holder->Add(Units_SizeRadius_Holder, 1, wxEXPAND);
	Units_AttributesSizes_Holder->Add(Units_EditorRadius_Holder, 1, wxEXPAND);
	Units_AttributesSizes_Holder->Add(Units_SelectionRadius_Holder, 1, wxEXPAND);
	Units_AttributesSelection1_Grid->Add(Units_Unselectable_Holder, 1, wxEXPAND);
	Units_AttributesSelection1_Grid->Add(Units_SelectionMask_Holder, 1, wxEXPAND);
	Units_AttributesSelection1_Grid->Add(Units_SelectionShapeType_Holder, 1, wxEXPAND);
	Units_AttributesSelection1_Grid->Add(Units_SelectionShape_Holder, 1, wxEXPAND);
	Units_AttributesSelection1_Grid->Add(Units_SelectionEffect_Holder, 1, wxEXPAND);
	Units_AttributesSelection1_Grid->Add(Units_EditorSelectionColour_Holder, 1, wxEXPAND);
	Units_ResourceStorageHeader_Holder->Add(Units_ResourceStorage_Holder[0], 0, wxEXPAND);
	Units_ResourceStorageHeader_Holder->AddSpacer(5);
	Units_ResourceStorageHeader_Holder->Add(Units_ResourceStorage_Holder[1], 0, wxEXPAND);
	Units_ResourceStorageHeader_Holder->AddSpacer(5);
	Units_ResourceStorageHeader_Holder->Add(Units_ResourceStorage_Holder[2], 0, wxEXPAND);
	Units_Attributes1_Grid->Add(Units_DeadUnitID_Holder, 1, wxEXPAND);
	Units_Attributes2_Grid->Add(Units_Civ_Holder, 1, wxEXPAND);
	Units_Attributes2_Grid->Add(Units_Unknown9_Holder, 1, wxEXPAND);
	Units_Attributes1_Grid->Add(Units_Unitline_Holder, 1, wxEXPAND);
	Units_Attributes1_Grid->Add(Units_MinTechLevel_Holder, 1, wxEXPAND);
	Units_AttributesTracking_Grid->Add(Units_TrackingUnit_Holder, 1, wxEXPAND);
	Units_AttributesTracking_Grid->Add(Units_TrackingUnitUsed_Holder, 1, wxEXPAND);
	Units_AttributesTracking_Grid->Add(Units_TrackingUnitDensity_Holder, 1, wxEXPAND);
	Units_CostHeader_Holder->Add(Units_CostType_Holder, 0, wxEXPAND);
	Units_CostHeader_Holder->AddSpacer(5);
	Units_CostHeader_Holder->Add(Units_CostAmount_Holder, 0, wxEXPAND);
	Units_CostHeader_Holder->AddSpacer(5);
	Units_CostHeader_Holder->Add(Units_CostUsed_Holder, 0, wxEXPAND);
	Units_AttributesTrain1_Grid->Add(Units_CommandAttribute_Holder, 1, wxEXPAND);
	Units_AttributesTrain1_Grid->Add(Units_TrainTime_Holder, 1, wxEXPAND);
	Units_AttributesTrain1_Grid->Add(Units_TrainLocationID_Holder, 1, wxEXPAND);
	Units_Attributes3_Grid->Add(Units_StackUnitID_Holder, 1, wxEXPAND);
	Units_AttributesTerrain_Grid->Add(Units_TerrainID_Holder, 1, wxEXPAND);
	Units_AttributesTerrain_Grid->Add(Units_OldTerrainLikeID_Holder, 1, wxEXPAND);
	Units_AttributesTerrain_Grid->Add(Units_ResearchID_Holder, 1, wxEXPAND);
	Units_Attributes3_Grid->Add(Units_HeadUnit_Holder, 1, wxEXPAND);
	Units_Attributes3_Grid->Add(Units_TransformUnit_Holder, 1, wxEXPAND);
	Units_Attributes3_Grid->Add(Units_PileUnit_Holder, 1, wxEXPAND);
	Units_AttributesTrain1_Grid->Add(Units_ButtonID_Holder, 1, wxEXPAND);

	Units_Attributes_Holder->Add(Units_AttributesBoxes1_Grid, 0, wxEXPAND);
	Units_Attributes_Holder->AddSpacer(5);
	Units_Attributes_Holder->Add(Units_AttributesModes1_Grid, 0, wxEXPAND);
	Units_Attributes_Holder->AddSpacer(5);
	Units_Attributes_Holder->Add(Units_Attributes2_Grid, 0, wxEXPAND);
	Units_Attributes_Holder->AddSpacer(5);
	Units_Attributes_Holder->Add(Units_Attributes1_Grid, 0, wxEXPAND);
	Units_Attributes_Holder->AddSpacer(5);
	Units_Attributes_Holder->Add(Units_AttributesTerrain_Holder, 0, wxEXPAND);
	Units_Attributes_Holder->AddSpacer(5);
	Units_Attributes_Holder->Add(Units_AttributesTerrain_Grid, 0, wxEXPAND);
	Units_Attributes_Holder->AddSpacer(5);
	Units_Attributes_Holder->Add(Units_AttributesDropSite_Holder, 0, wxEXPAND);
	Units_Attributes_Holder->AddSpacer(5);
	Units_Attributes_Holder->Add(Units_AttributesSizes_Holder, 0, wxEXPAND);
	Units_Attributes_Holder->AddSpacer(5);
	Units_Attributes_Holder->Add(Units_AttributesSelection1_Grid, 0, wxEXPAND);
	Units_Attributes_Holder->AddSpacer(5);
	Units_Attributes_Holder->Add(Units_AttributesTracking_Grid, 0, wxEXPAND);
	Units_Attributes_Holder->AddSpacer(5);
	Units_Attributes_Holder->Add(Units_AttributesTrain1_Grid, 0, wxEXPAND);
	Units_Attributes_Holder->AddSpacer(5);
	Units_Attributes_Holder->Add(Units_ResourceStorageHeader_Holder, 0, wxEXPAND);
	Units_Attributes_Holder->AddSpacer(5);
	Units_Attributes_Holder->Add(Units_CostHeader_Holder, 0, wxEXPAND);
	Units_Attributes_Holder->AddSpacer(5);
	Units_Attributes_Holder->Add(Units_Attributes3_Grid, 0, wxEXPAND);
	Units_Attributes_Holder->AddSpacer(5);
	Units_Attributes_Holder->Add(Units_AnnexUnit1_Holder, 0, wxEXPAND);
	Units_Attributes_Holder->AddSpacer(5);
	Units_Attributes_Holder->Add(Units_AnnexUnitMisplacement1_Holder, 0, wxEXPAND);
	Units_Attributes_Holder->AddSpacer(5);
	Units_Attributes_Holder->Add(Units_LootSwitch_Holder, 0, wxEXPAND);

	Units_TrainSound1_Holder->Add(Units_TrainSound[0], 1, wxEXPAND);
	Units_TrainSound1_Holder->Add(Units_TrainSound_ComboBox[0], 1, wxEXPAND);
	Units_TrainSound2_Holder->Add(Units_TrainSound[1], 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);
	Units_TrainSound2_Holder->Add(Units_TrainSound_ComboBox[1], 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);

	Units_TrainSound3_Holder->Add(Units_TrainSound1_Holder, 1, wxEXPAND);
	Units_TrainSound3_Holder->AddSpacer(5);
	Units_TrainSound3_Holder->Add(Units_TrainSound2_Holder, 1, wxEXPAND);

	Units_TrainSound_Holder->Add(Units_TrainSound_Text, 0, wxEXPAND);
	Units_TrainSound_Holder->Add(Units_TrainSound3_Holder, 1, wxEXPAND);

	Units_SoundsArea1_Holder->Add(Units_SelectionSound_Holder, 1, wxEXPAND);
	Units_SoundsArea1_Holder->AddSpacer(5);
	Units_SoundsArea1_Holder->Add(Units_DyingSound_Holder, 1, wxEXPAND);
	Units_SoundsArea1_Holder->AddSpacer(5);
	Units_SoundsArea1_Holder->Add(Units_TrainSound_Holder, 2, wxEXPAND);
	Units_SoundsArea2_Grid->Add(Units_AttackSound_Holder, 1, wxEXPAND);
	Units_SoundsArea2_Grid->Add(Units_MoveSound_Holder, 1, wxEXPAND);
	Units_SoundsArea2_Grid->Add(Units_ConstructionSound_Holder, 1, wxEXPAND);
	Units_SoundsArea2_Grid->Add(Units_UnknownSound_Holder, 1, wxEXPAND);

	Units_SoundsArea_Holder->Add(Units_SoundsArea1_Holder, 0, wxEXPAND);
	Units_SoundsArea_Holder->AddSpacer(5);
	Units_SoundsArea_Holder->Add(Units_SoundsArea2_Grid, 0, wxEXPAND);

	Units_HPBars_Grid->Add(Units_HPBarHeight1_Holder, 1, wxEXPAND);
	Units_HPBars_Grid->Add(Units_HPBarHeight2_Holder, 1, wxEXPAND);
	Units_MiscArea_Holder->Add(Units_HPBars_Grid, 1, wxEXPAND);

	Units_Type10plusUnknowns_Grid->Add(Units_Unknown1_Holder, 0, wxEXPAND);
	Units_Type10plusUnknowns_Grid->Add(Units_BlastType_Holder, 0, wxEXPAND);
	Units_Type10plusUnknowns_Grid->Add(Units_Unknown2_Holder, 0, wxEXPAND);
	Units_Type10plusUnknowns_Grid->Add(Units_Unknown3A_Holder, 0, wxEXPAND);
	Units_Type10plusUnknowns_Grid->Add(Units_Unknown6_Holder, 0, wxEXPAND);
	Units_Type10plusUnknowns_Grid->Add(Units_Unknown7_Holder, 0, wxEXPAND);
	Units_Type10plusUnknowns_Grid->Add(Units_Unknown8_Holder, 0, wxEXPAND);
	Units_Type10plusUnknownArea_Holder->Add(Units_Type10plusUnknowns_Grid, 0, wxEXPAND);

	Units_Type30plusUnknownArea_Grid->Add(Units_Unknown11_Holder, 0, wxEXPAND);
	Units_Type30plusUnknownArea_Grid->Add(Units_Unknown16_Holder, 0, wxEXPAND);
	Units_Type30plusUnknownArea_Holder->Add(Units_Type30plusUnknownArea_Grid, 0, wxEXPAND);
	Units_Type30plusUnknownArea_Holder->AddSpacer(5);
	Units_Type30plusUnknownArea_Holder->Add(Units_Unknown16B_Holder, 0, wxEXPAND);

	Units_Type70plusUnknownArea_Grid->Add(Units_Unknown26_Holder, 0, wxEXPAND);
	Units_Type70plusUnknownArea_Grid->Add(Units_Unknown27_Holder, 0, wxEXPAND);
	Units_Type70plusUnknownArea_Grid->Add(Units_Unknown28_Holder, 0, wxEXPAND);
	Units_Type70plusUnknownArea_Holder->Add(Units_Type70plusUnknownArea_Grid, 0, wxEXPAND);

	Units_Type80plusUnknownArea_Grid->Add(Units_Unknown33_Holder, 0, wxEXPAND);
	Units_Type80plusUnknownArea_Grid->Add(Units_Unknown35_Holder, 0, wxEXPAND);
	Units_Type80plusUnknownArea_Holder->Add(Units_Type80plusUnknownArea_Grid, 0, wxEXPAND);

	Units_UnitCommands_Buttons->Add(Units_UnitCommands_Add, 1, wxEXPAND);
	Units_UnitCommands_Buttons->Add(Units_UnitCommands_Delete, 1, wxEXPAND);
	Units_UnitCommands_Buttons->Add(Units_UnitCommands_Insert, 1, wxEXPAND);
	Units_UnitCommands_Buttons->Add(Units_UnitCommands_Copy, 1, wxEXPAND);
	Units_UnitCommands_Buttons->Add(Units_UnitCommands_Paste, 1, wxEXPAND);
	Units_UnitCommands_Buttons->Add(Units_UnitCommands_PasteInsert, 1, wxEXPAND);

	Units_UnitCommands->Add(Units_UnitCommands_Search, 0, wxEXPAND);
	Units_UnitCommands->Add(Units_UnitCommands_Search_R, 0, wxEXPAND);
	Units_UnitCommands->AddSpacer(2);
	Units_UnitCommands->Add(Units_UnitCommands_List, 1, wxEXPAND);
	Units_UnitCommands->AddSpacer(2);
	Units_UnitCommands->Add(Units_UnitCommands_Buttons, 0, wxEXPAND);
	Units_UnitCommands->AddSpacer(2);
	Units_UnitCommands->Add(Units_UnitCommands_CopyToUnits, 0, wxEXPAND);

	Units_CommandHolder_Lists->Add(Units_UnitHeads_Name, 0, wxEXPAND);
	Units_CommandHolder_Lists->AddSpacer(5);
	Units_CommandHolder_Lists->Add(Units_UnitCommands, 0, wxEXPAND);
	Units_CommandHolder_Lists->AddSpacer(5);
	Units_CommandHolder_Lists->Add(Units_Exists_Holder, 0, wxEXPAND);

	UnitCommands_1_Holder->Add(UnitCommands_One_Holder, 1, wxEXPAND);
	UnitCommands_1_Holder->AddSpacer(5);
	UnitCommands_1_Holder->Add(UnitCommands_ID_Holder, 1, wxEXPAND);

	Units_CommandHolder_Grid1->Add(UnitCommands_ClassID_Holder, 1, wxEXPAND);
	Units_CommandHolder_Grid1->Add(UnitCommands_UnitID_Holder, 1, wxEXPAND);
	Units_CommandHolder_Grid1->Add(UnitCommands_Unknown2_Holder, 1, wxEXPAND);
	Units_CommandHolder_Grid1->Add(UnitCommands_ResourceIn_Holder, 1, wxEXPAND);
	Units_CommandHolder_Grid1->Add(UnitCommands_ProductivityResource_Holder, 1, wxEXPAND);
	Units_CommandHolder_Grid1->Add(UnitCommands_ResourceOut_Holder, 1, wxEXPAND);
	Units_CommandHolder_Grid1->Add(UnitCommands_Resource_Holder, 1, wxEXPAND);
	Units_CommandHolder_Grid1->Add(UnitCommands_WorkRateMultiplier_Holder, 1, wxEXPAND);
	Units_CommandHolder_Grid2->Add(UnitCommands_ExecutionRadius_Holder, 1, wxEXPAND);
	Units_CommandHolder_Grid2->Add(UnitCommands_ExtraRange_Holder, 1, wxEXPAND);

	Units_CommandHolder_Data2->Add(UnitCommands_1_Holder, 0, wxEXPAND);
	Units_CommandHolder_Data2->AddSpacer(5);
	Units_CommandHolder_Data2->Add(UnitCommands_Type_Holder, 0, wxEXPAND);
	Units_CommandHolder_Data2->AddSpacer(5);
	Units_CommandHolder_Data2->Add(Units_CommandHolder_Grid1, 0, wxEXPAND);
	Units_CommandHolder_Data2->AddSpacer(5);
	Units_CommandHolder_Data2->Add(Units_CommandHolder_Grid2, 0, wxEXPAND);
	Units_CommandHolder_Data2->AddSpacer(5);
	Units_CommandHolder_Grid3->Add(UnitCommands_Unknown1_Holder, 1, wxEXPAND);
	Units_CommandHolder_Grid3->Add(UnitCommands_Unknown4_Holder, 1, wxEXPAND);
	Units_CommandHolder_Grid3->Add(UnitCommands_Unknown5_Holder, 1, wxEXPAND);
	Units_CommandHolder_Grid3->Add(UnitCommands_SelectionEnabler_Holder, 1, wxEXPAND);
	Units_CommandHolder_Grid3->Add(UnitCommands_Unknown7_Holder, 1, wxEXPAND);
	Units_CommandHolder_Grid3->Add(UnitCommands_Unknown8_Holder, 1, wxEXPAND);
	Units_CommandHolder_Grid3->Add(UnitCommands_Unknown9_Holder, 1, wxEXPAND);
	Units_CommandHolder_Grid3->Add(UnitCommands_SelectionMode_Holder, 1, wxEXPAND);
	Units_CommandHolder_Grid3->Add(UnitCommands_Unknown11_Holder, 1, wxEXPAND);
	Units_CommandHolder_Grid3->Add(UnitCommands_Unknown12_Holder, 1, wxEXPAND);

	Units_CommandHolder_Data1->Add(Units_CommandHolder_Data2, 2, wxEXPAND);
	Units_CommandHolder_Data1->AddSpacer(5);
	Units_CommandHolder_Data1->Add(Units_CommandHolder_Grid3, 1, wxEXPAND | wxRESERVE_SPACE_EVEN_IF_HIDDEN);

	Units_CommandHolder_Data->Add(Units_CommandHolder_Data1, 0, wxEXPAND);
	Units_CommandHolder_Data->AddSpacer(5);
	Units_CommandHolder_Data->Add(UnitCommands_Graphics_Grid, 0, wxEXPAND);

	Units_CommandsArea_Holder->Add(Units_CommandHolder_Lists, 1, wxEXPAND);
	Units_CommandsArea_Holder->AddSpacer(5);
	Units_CommandsArea_Holder->Add(Units_CommandHolder_Data, 3, wxEXPAND);

	Units_UnknownArea_Holder->Add(Units_Type10plusUnknownArea_Holder, 0, wxEXPAND);
	Units_UnknownArea_Holder->AddSpacer(5);
	Units_UnknownArea_Holder->Add(Units_Type30plusUnknownArea_Holder, 0, wxEXPAND);
	Units_UnknownArea_Holder->AddSpacer(5);
	Units_UnknownArea_Holder->Add(Units_Type70plusUnknownArea_Holder, 0, wxEXPAND);
	Units_UnknownArea_Holder->AddSpacer(5);
	Units_UnknownArea_Holder->Add(Units_Type80plusUnknownArea_Holder, 0, wxEXPAND);

	Units_ScrollSpace->Add(Units_TypeArea_Holder, 0, wxEXPAND);
	Units_ScrollSpace->AddSpacer(5);
	Units_ScrollSpace->Add(Units_LangDLLArea_Holder, 0, wxEXPAND);
	Units_ScrollSpace->AddSpacer(5);
	Units_ScrollSpace->Add(Units_GraphicsArea_Holder, 0, wxEXPAND);
	Units_ScrollSpace->AddSpacer(5);
	Units_ScrollSpace->Add(Units_StatsArea_Holder, 0, wxEXPAND);
	Units_ScrollSpace->AddSpacer(5);
	Units_ScrollSpace->Add(Units_ProjectilesArea_Holder, 0, wxEXPAND);
	Units_ScrollSpace->AddSpacer(5);
	Units_ScrollSpace->Add(Units_Attributes_Holder, 0, wxEXPAND);
	Units_ScrollSpace->AddSpacer(5);
	Units_ScrollSpace->Add(Units_SoundsArea_Holder, 0, wxEXPAND);
	Units_ScrollSpace->AddSpacer(5);
	Units_ScrollSpace->Add(Units_MiscArea_Holder, 0, wxEXPAND);
	Units_ScrollSpace->AddSpacer(5);
	Units_ScrollSpace->Add(Units_UnknownArea_Holder, 0, wxEXPAND);
	Units_ScrollSpace->AddSpacer(5);
	Units_ScrollSpace->Add(Units_CommandsArea_Holder, 0, wxEXPAND);

	Units_ScrollArea->Add(Units_ScrollSpace, 1, wxEXPAND);
	Units_ScrollArea->AddSpacer(5);
	Units_Scroller->SetSizer(Units_ScrollArea);
	Units_Scroller->SetScrollRate(0, 20);

	Units_Top_Holder->Add(Units_AutoCopy, 0, wxEXPAND);
	Units_Top_Holder->Add(Units_CopyTo, 0, wxEXPAND);
	Units_Top_Holder->AddSpacer(5);
	Units_Top_Holder->Add(Units_CopyGraphics, 0, wxEXPAND);
	Units_Top_Holder->Add(Units_CopyToText, 0, wxEXPAND);
	Units_Top_Holder->Add(Units_SelectAll, 0, wxEXPAND);
	Units_Top_Holder->Add(Units_SelectClear, 0, wxEXPAND);
	Units_Top_Holder->Add(Units_GraphicSetText, 0, wxEXPAND);
	Units_Top_Holder->Add(Units_GraphicSet, 0, wxEXPAND);

	Units_DataArea->AddSpacer(15);
	Units_DataArea->Add(Units_Top_Holder, 0, wxEXPAND);
	Units_DataArea->Add(Units_TopGrid_Holder, 0, wxEXPAND);
	Units_DataArea->Add(Units_Type_Holder, 0, wxEXPAND);
	Units_DataArea->AddSpacer(5);
	Units_DataArea->Add(Units_Scroller, 1, wxEXPAND);
	Units_DataArea->AddSpacer(5);

	Units_Main->AddSpacer(5);
	Units_Main->Add(Units_ListArea, 21, wxEXPAND);
	Units_Main->AddSpacer(5);
	Units_Main->Add(Units_DataArea, 65, wxEXPAND);
	Units_Main->AddSpacer(5);

	if(EnableIDFix)
	{
		Units_ID1->Enable(false);
		Units_ID2->Enable(false);
		Units_ID3->Enable(false);
		UnitCommands_ID->Enable(false);
	}

	Tab_Units->SetSizer(Units_Main);

	Connect(Units_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitsSearch));
	Connect(Units_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitsSearch));
	Connect(Units_FilterSelector->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSelection_SearchFilters));
	for(short loop = 0; loop < 2; ++loop)
	{
		Connect(Units_UseAnd[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsSearch));
		Connect(Units_SearchFilters[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSelection_SearchFilters));
	}
	Connect(Units_Civs_List->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnitSubList));
	Connect(Units_List->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnitsSelect));
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
	Connect(Units_Type_ComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Units));

	Units_Name->Connect(Units_Name->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_Name2->Connect(Units_Name2->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_LanguageDLLName->Connect(Units_LanguageDLLName->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_LanguageDLLCreation->Connect(Units_LanguageDLLCreation->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_HotKey->Connect(Units_HotKey->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_LanguageDLLHelp->Connect(Units_LanguageDLLHelp->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_LanguageDLLHotKeyText->Connect(Units_LanguageDLLHotKeyText->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_Attribute->Connect(Units_Attribute->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_GarrisonType->Connect(Units_GarrisonType->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);

	DamageGraphics_GraphicID->Connect(DamageGraphics_GraphicID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	DamageGraphics_GraphicID_ComboBox->Connect(DamageGraphics_GraphicID_ComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Units), NULL, this);
	DamageGraphics_DamagePercent->Connect(DamageGraphics_DamagePercent->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Attacks_Class->Connect(Attacks_Class->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Attacks_Amount->Connect(Attacks_Amount->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Armors_Class->Connect(Armors_Class->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Armors_Amount->Connect(Armors_Amount->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	for(short loop = 0; loop < 2; ++loop)
	Attacks_Class_ComboBox[loop]->Connect(Attacks_Class_ComboBox[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Units), NULL, this);

	UnitCommands_Type->Connect(UnitCommands_Type->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	UnitCommands_ProductivityResource->Connect(UnitCommands_ProductivityResource->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Connect(UnitCommands_Type_ComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Units));
	for(short loop = 0; loop < 8; ++loop)
	{
		Connect(Units_Attribute_CheckBox[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdateCheck_UnitAttribute));
		Connect(Units_GarrisonType_CheckBox[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdateCheck_UnitGarrisonType));
	}
}

void AGE_Frame::OnKillFocus_Units(wxFocusEvent &Event)
{
	if(((AGETextCtrl*)Event.GetEventObject())->SaveEdits() != 0) return;
	if(Event.GetId() == Units_Name->GetId() || Event.GetId() == Units_LanguageDLLName->GetId())
	{
		ListUnits(UnitCivID);
	}
	else if(Event.GetId() == Units_Type->GetId()
	|| Event.GetId() == Units_Name2->GetId()
	|| Event.GetId() == Units_LanguageDLLCreation->GetId()
	|| Event.GetId() == Units_HotKey->GetId()
	|| Event.GetId() == Units_LanguageDLLHelp->GetId()
	|| Event.GetId() == Units_LanguageDLLHotKeyText->GetId()
	|| Event.GetId() == Units_Attribute->GetId()
	|| Event.GetId() == Units_GarrisonType->GetId())
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
	else if(Event.GetId() == UnitCommands_Type->GetId() || Event.GetId() == UnitCommands_ProductivityResource->GetId())
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
	if(Event.GetId() == Units_Type_ComboBox->GetId())
	{
		switch(Units_Type_ComboBox->GetSelection())
		{
			case 1: Units_Type->ChangeValue("10"); break;
			case 2: Units_Type->ChangeValue("15"); break;
			case 3: Units_Type->ChangeValue("20"); break;
			case 4: Units_Type->ChangeValue("25"); break;
			case 5: Units_Type->ChangeValue("30"); break;
			case 6: Units_Type->ChangeValue("40"); break;
			case 7: Units_Type->ChangeValue("50"); break;
			case 8: Units_Type->ChangeValue("60"); break;
			case 9: Units_Type->ChangeValue("70"); break;
			case 10: Units_Type->ChangeValue("80"); break;
			case 11: Units_Type->ChangeValue("90"); break;
		}
		Units_Type->SaveEdits();
		wxCommandEvent E;
		OnUnitsSelect(E);	// Updates unit layout.
//		ListUnits(UnitCivID, false);	// For special search filters.
		return;
	}
	if(Event.GetId() == UnitCommands_Type_ComboBox->GetId())
	{
		switch(UnitCommands_Type_ComboBox->GetSelection())
		{
			case 1: UnitCommands_Type->ChangeValue("1"); break;
			case 2: UnitCommands_Type->ChangeValue("2"); break;
			case 3: UnitCommands_Type->ChangeValue("3"); break;
			case 4: UnitCommands_Type->ChangeValue("4"); break;
			case 5: UnitCommands_Type->ChangeValue("5"); break;
			case 6: UnitCommands_Type->ChangeValue("6"); break;
			case 7: UnitCommands_Type->ChangeValue("7"); break;
			case 8: UnitCommands_Type->ChangeValue("8"); break;
			case 9: UnitCommands_Type->ChangeValue("10"); break;
			case 10: UnitCommands_Type->ChangeValue("11"); break;
			case 11: UnitCommands_Type->ChangeValue("12"); break;
			case 12: UnitCommands_Type->ChangeValue("13"); break;
			case 13: UnitCommands_Type->ChangeValue("20"); break;
			case 14: UnitCommands_Type->ChangeValue("21"); break;
			case 15: UnitCommands_Type->ChangeValue("101"); break;
			case 16: UnitCommands_Type->ChangeValue("102"); break;
			case 17: UnitCommands_Type->ChangeValue("103"); break;
			case 18: UnitCommands_Type->ChangeValue("104"); break;
			case 19: UnitCommands_Type->ChangeValue("105"); break;
			case 20: UnitCommands_Type->ChangeValue("106"); break;
			case 21: UnitCommands_Type->ChangeValue("107"); break;
			case 22: UnitCommands_Type->ChangeValue("108"); break;
			case 23: UnitCommands_Type->ChangeValue("109"); break;
			case 24: UnitCommands_Type->ChangeValue("110"); break;
			case 25: UnitCommands_Type->ChangeValue("111"); break;
			case 26: UnitCommands_Type->ChangeValue("120"); break;
			case 27: UnitCommands_Type->ChangeValue("121"); break;
			case 28: UnitCommands_Type->ChangeValue("122"); break;
			case 29: UnitCommands_Type->ChangeValue("123"); break;
			case 30: UnitCommands_Type->ChangeValue("125"); break;
			case 31: UnitCommands_Type->ChangeValue("131"); break;
			case 32: UnitCommands_Type->ChangeValue("132"); break;
			case 33: UnitCommands_Type->ChangeValue("135"); break;
			case 34: UnitCommands_Type->ChangeValue("136"); break;
			case 35: UnitCommands_Type->ChangeValue("149"); break;
			default: UnitCommands_Type->ChangeValue("-1");
		}
		UnitCommands_Type->SaveEdits();
		ListUnitCommands();
		return;
	}
	((AGEComboBox*)Event.GetEventObject())->OnUpdate(Event);
	if(Event.GetId() == Attacks_Class_ComboBox[0]->GetId())
	{
		ListUnitAttacks();
	}
	else if(Event.GetId() == Attacks_Class_ComboBox[1]->GetId())
	{
		ListUnitArmors();
	}
	else if(Event.GetId() == DamageGraphics_GraphicID_ComboBox->GetId())
	{
		ListUnitDamageGraphics();
	}
}

void AGE_Frame::OnUpdateCheck_UnitGarrisonType(wxCommandEvent &Event)
{
	if(Units_GarrisonType->container.empty()) return;
	uint8_t type = *(uint8_t*)Units_GarrisonType->container[0];
	Units_GarrisonType_CheckBox[0]->GetValue() ? type |= 0x01 : type &= ~0x01;
	Units_GarrisonType_CheckBox[1]->GetValue() ? type |= 0x02 : type &= ~0x02;
	Units_GarrisonType_CheckBox[2]->GetValue() ? type |= 0x04 : type &= ~0x04;
	Units_GarrisonType_CheckBox[3]->GetValue() ? type |= 0x08 : type &= ~0x08;
	Units_GarrisonType_CheckBox[4]->GetValue() ? type |= 0x10 : type &= ~0x10;
	Units_GarrisonType_CheckBox[5]->GetValue() ? type |= 0x20 : type &= ~0x20;
	Units_GarrisonType_CheckBox[6]->GetValue() ? type |= 0x40 : type &= ~0x40;
	Units_GarrisonType_CheckBox[7]->GetValue() ? type |= 0x80 : type &= ~0x80;
	Units_GarrisonType->ChangeValue(lexical_cast<string>((short)type));
	Units_GarrisonType->SaveEdits();
}

void AGE_Frame::OnUpdateCheck_UnitAttribute(wxCommandEvent &Event)
{
	if(Units_Attribute->container.empty()) return;
	uint8_t attribute = *(uint8_t*)Units_Attribute->container[0];
	Units_Attribute_CheckBox[0]->GetValue() ? attribute |= 0x01 : attribute &= ~0x01;
	Units_Attribute_CheckBox[1]->GetValue() ? attribute |= 0x02 : attribute &= ~0x02;
	Units_Attribute_CheckBox[2]->GetValue() ? attribute |= 0x04 : attribute &= ~0x04;
	Units_Attribute_CheckBox[3]->GetValue() ? attribute |= 0x08 : attribute &= ~0x08;
	Units_Attribute_CheckBox[4]->GetValue() ? attribute |= 0x10 : attribute &= ~0x10;
	Units_Attribute_CheckBox[5]->GetValue() ? attribute |= 0x20 : attribute &= ~0x20;
	Units_Attribute_CheckBox[6]->GetValue() ? attribute |= 0x40 : attribute &= ~0x40;
	Units_Attribute_CheckBox[7]->GetValue() ? attribute |= 0x80 : attribute &= ~0x80;
	Units_Attribute->ChangeValue(lexical_cast<string>((short)attribute));
	Units_Attribute->SaveEdits();
}
