#include "../AGE_Frame.h"

//const wxString AGE_Frame::CIVCOUNTWARNING = "Fewer civilizations copied than needed to paste!\nPasting data to extra civilizations from civilization 1!";

void AGE_Frame::OnUnitSubList(wxCommandEvent &event)
{
	short Selection = Units_Civs_List->GetSelection();
	if(Selection == wxNOT_FOUND) return;

	ListUnits(Selection, false);	// List units by selected civ.
}

string AGE_Frame::GetUnitName(int index, short civ, bool Filter)
{
	string Name = "";

	if(dataset->Civs[civ].UnitPointers[index] == 0)
	{
		return "Nonexistent";
	}
	if(Filter)
	{
		int filters = 2;
		short Selection[filters];
		for(size_t loop = 0; loop < filters; ++loop)
		Selection[loop] = Units_SearchFilters[loop]->GetSelection();
		genie::Unit * UnitPointer = &dataset->Civs[civ].Units[index];

		if(Selection[0] > 0)
        for(size_t loop = 0; loop < filters; ++loop)
        {
            short NameSize = Name.size(), NameSize0 = NameSize;
            wxString label = Units_SearchFilters[loop]->GetString(Selection[loop]);
            if(label.compare(Type20[0]) == 0) Name += "T "+FormatInt(UnitPointer->Type);
            else if(label.compare(Type20[1]) == 0) Name += "I1 "+FormatInt(UnitPointer->ID1);
            else if(label.compare(Type20[2]) == 0) Name += "LN "+FormatInt(UnitPointer->LanguageDLLName);
            else if(label.compare(Type20[3]) == 0) Name += "LC "+FormatInt(UnitPointer->LanguageDLLCreation);
            else if(label.compare(Type20[4]) == 0) Name += "C "+FormatInt(UnitPointer->Class);
            else if(label.compare(Type20[5]) == 0) Name += "SG "+FormatInt(UnitPointer->StandingGraphic.first)+" "+FormatInt(UnitPointer->StandingGraphic.second);
            else if(label.compare(Type20[6]) == 0) Name += "DG "+FormatInt(UnitPointer->DyingGraphic.first)+" "+FormatInt(UnitPointer->DyingGraphic.second);
            else if(label.compare(Type20[7]) == 0) Name += "DM "+FormatInt(UnitPointer->DeathMode);
            else if(label.compare(Type20[8]) == 0) Name += "HP "+FormatInt(UnitPointer->HitPoints);
            else if(label.compare(Type20[9]) == 0) Name += "LS "+FormatFloat(UnitPointer->LineOfSight);
            else if(label.compare(Type20[10]) == 0) Name += "GC "+FormatInt(UnitPointer->GarrisonCapacity);
            else if(label.compare(Type20[11]) == 0) Name += "SR "+FormatInt(UnitPointer->CollisionSize.x)+" "+FormatInt(UnitPointer->CollisionSize.y);
            else if(label.compare(Type20[12]) == 0) Name += "B1 "+FormatFloat(UnitPointer->CollisionSize.z);
            else if(label.compare(Type20[13]) == 0) Name += "TS "+FormatInt(UnitPointer->TrainSound.first)+" "+FormatInt(UnitPointer->TrainSound.second);
            else if(label.compare(Type20[14]) == 0) Name += "DU "+FormatInt(UnitPointer->DeadUnitID);
            else if(label.compare(Type20[15]) == 0) Name += "PM "+FormatInt(UnitPointer->PlacementMode);
            else if(label.compare(Type20[16]) == 0) Name += "AM "+FormatInt(UnitPointer->AirMode);
            else if(label.compare(Type20[17]) == 0) Name += "I "+FormatInt(UnitPointer->IconID);
            else if(label.compare(Type20[18]) == 0) Name += "HE "+FormatInt(UnitPointer->HideInEditor);
            else if(label.compare(Type20[19]) == 0) Name += "U1 "+FormatInt(UnitPointer->Unknown1);
            else if(label.compare(Type20[20]) == 0) Name += "E "+FormatInt(UnitPointer->Enabled);
            else if(label.compare(Type20[21]) == 0) Name += "D "+FormatInt(UnitPointer->Disabled);
            else if(label.compare(Type20[22]) == 0) Name += "PBT "+FormatInt(UnitPointer->PlacementSideTerrain.first)+" "+FormatInt(UnitPointer->PlacementSideTerrain.second);
            else if(label.compare(Type20[23]) == 0) Name += "PT "+FormatInt(UnitPointer->PlacementTerrain.first)+" "+FormatInt(UnitPointer->PlacementTerrain.second);
            else if(label.compare(Type20[24]) == 0) Name += "ER "+FormatInt(UnitPointer->ClearanceSize.first)+" "+FormatInt(UnitPointer->ClearanceSize.second);
            else if(label.compare(Type20[25]) == 0) Name += "HM "+FormatInt(UnitPointer->HillMode);
            else if(label.compare(Type20[26]) == 0) Name += "VF "+FormatInt(UnitPointer->VisibleInFog);
            else if(label.compare(Type20[27]) == 0) Name += "TR "+FormatInt(UnitPointer->TerrainRestriction);
            else if(label.compare(Type20[28]) == 0) Name += "FM "+FormatInt(UnitPointer->FlyMode);
            else if(label.compare(Type20[29]) == 0) Name += "RC "+FormatInt(UnitPointer->ResourceCapacity);
            else if(label.compare(Type20[30]) == 0) Name += "RD "+FormatFloat(UnitPointer->ResourceDecay);
            else if(label.compare(Type20[31]) == 0) Name += "BA "+FormatInt(UnitPointer->BlastDefenseLevel);
            else if(label.compare(Type20[32]) == 0) Name += "U2 "+FormatInt(UnitPointer->SubType);
            else if(label.compare(Type20[33]) == 0) Name += "IM "+FormatInt(UnitPointer->InteractionMode);
            else if(label.compare(Type20[34]) == 0) Name += "MM "+FormatInt(UnitPointer->MinimapMode);
            else if(label.compare(Type20[35]) == 0) Name += "CA "+FormatInt(UnitPointer->CommandAttribute);
            else if(label.compare(Type20[36]) == 0) Name += "U3A "+FormatFloat(UnitPointer->Unknown3A);
            else if(label.compare(Type20[37]) == 0) Name += "MC "+FormatInt(UnitPointer->MinimapColor);
            else if(label.compare(Type20[38]) == 0) Name += "LH "+FormatInt(UnitPointer->LanguageDLLHelp);
            else if(label.compare(Type20[39]) == 0) Name += "LT "+FormatInt(UnitPointer->LanguageDLLHotKeyText);
            else if(label.compare(Type20[40]) == 0) Name += "HK "+FormatInt(UnitPointer->HotKey);
            else if(label.compare(Type20[41]) == 0) Name += "US "+FormatInt(UnitPointer->Unselectable);
            else if(label.compare(Type20[42]) == 0) Name += "U6 "+FormatInt(UnitPointer->Unknown6);
            else if(label.compare(Type20[43]) == 0) Name += "U7 "+FormatInt(UnitPointer->Unknown7);
            else if(label.compare(Type20[44]) == 0) Name += "U8 "+FormatInt(UnitPointer->Unknown8);
            else if(label.compare(Type20[45]) == 0) Name += "SM "+FormatInt(UnitPointer->SelectionMask);
            else if(label.compare(Type20[46]) == 0) Name += "ST "+FormatInt(UnitPointer->SelectionShapeType);
            else if(label.compare(Type20[47]) == 0) Name += "SSh "+FormatInt(UnitPointer->SelectionShape);
            else if(label.compare(Type20[48]) == 0) Name += "A "+FormatInt(UnitPointer->Attribute);
            else if(label.compare(Type20[49]) == 0) Name += "Ci "+FormatInt(UnitPointer->Civilization);
            else if(label.compare(Type20[50]) == 0) Name += "No "+FormatInt(UnitPointer->Nothing);
            else if(label.compare(Type20[51]) == 0) Name += "SE "+FormatInt(UnitPointer->SelectionEffect);
            else if(label.compare(Type20[52]) == 0) Name += "EC "+FormatInt(UnitPointer->EditorSelectionColour);
            else if(label.compare(Type20[53]) == 0) Name += "SS "+FormatInt(UnitPointer->SelectionShapeSize.x)+" "+FormatInt(UnitPointer->SelectionShapeSize.y);
            else if(label.compare(Type20[54]) == 0) Name += "B2 "+FormatFloat(UnitPointer->SelectionShapeSize.z);
            else if(label.compare(Type20[55]) == 0) Name += "Ask Tapsa";
            else if(label.compare(Type20[56]) == 0) Name += "DC "+FormatInt(UnitPointer->DamageGraphics.size());
            else if(label.compare(Type20[57]) == 0) Name += "Ask Tapsa";
            else if(label.compare(Type20[58]) == 0) Name += "SSo "+FormatInt(UnitPointer->SelectionSound);
            else if(label.compare(Type20[59]) == 0) Name += "DS "+FormatInt(UnitPointer->DyingSound);
            else if(label.compare(Type20[60]) == 0) Name += "AtM "+FormatInt(UnitPointer->AttackMode);
            else if(label.compare(Type20[61]) == 0) Name += "EM "+FormatInt(UnitPointer->Unknown10);
            else if(label.compare(Type20[62]) == 0) Name += UnitPointer->Name;
            else if(label.compare(Type20[63]) == 0) Name += UnitPointer->Name2;
            else if(label.compare(Type20[64]) == 0) Name += "UL "+FormatInt(UnitPointer->Unitline);
            else if(label.compare(Type20[65]) == 0) Name += "MT "+FormatInt(UnitPointer->MinTechLevel);
            else if(label.compare(Type20[66]) == 0) Name += "I2 "+FormatInt(UnitPointer->ID2);
            else if(label.compare(Type20[67]) == 0) Name += "I3 "+FormatInt(UnitPointer->ID3);
            else if(label.compare(Type20[68]) == 0) Name += "S "+FormatFloat(UnitPointer->Speed);

            if(NameSize == Name.size() && UnitPointer->Type >= 30 && UnitPointer->Type <= 80)
            {
                NameSize = Name.size();
				if(label.compare(Type30[0]) == 0) Name += "WG "+FormatInt(UnitPointer->DeadFish.WalkingGraphic.first)+" "+FormatInt(UnitPointer->DeadFish.WalkingGraphic.second);
				else if(label.compare(Type30[1]) == 0) Name += "RS "+FormatFloat(UnitPointer->DeadFish.RotationSpeed);
				else if(label.compare(Type30[2]) == 0) Name += "U11 "+FormatInt(UnitPointer->DeadFish.Unknown11);
				else if(label.compare(Type30[3]) == 0) Name += "TU "+FormatInt(UnitPointer->DeadFish.TrackingUnit);
				else if(label.compare(Type30[4]) == 0) Name += "UU "+FormatInt(UnitPointer->DeadFish.TrackingUnitUsed);
				else if(label.compare(Type30[5]) == 0) Name += "UD "+FormatFloat(UnitPointer->DeadFish.TrackingUnitDensity);
				else if(label.compare(Type30[6]) == 0) Name += "U16 "+FormatInt(UnitPointer->DeadFish.Unknown16);
				else if(label.compare(Type30[7]) == 0)
				{
					Name += "a"+FormatFloat(UnitPointer->DeadFish.RotationAngles[0]);
					Name += " b"+FormatFloat(UnitPointer->DeadFish.RotationAngles[1]);
					Name += " c"+FormatFloat(UnitPointer->DeadFish.RotationAngles[2]);
					Name += " d"+FormatFloat(UnitPointer->DeadFish.RotationAngles[3]);
					Name += " e"+FormatFloat(UnitPointer->DeadFish.RotationAngles[4]);
				}
            }
            if(NameSize == Name.size() && UnitPointer->Type >= 40 && UnitPointer->Type <= 80)
            {
                NameSize = Name.size();
				if(label.compare(Type40[0]) == 0) Name += "SC "+FormatInt(UnitPointer->Bird.ActionWhenDiscoveredID);
				else if(label.compare(Type40[1]) == 0) Name += "SR "+FormatFloat(UnitPointer->Bird.SearchRadius);
				else if(label.compare(Type40[2]) == 0) Name += "WR "+FormatFloat(UnitPointer->Bird.WorkRate);
				else if(label.compare(Type40[3]) == 0) Name += "DS "+FormatInt(UnitPointer->Bird.DropSite.first)+" "+FormatInt(UnitPointer->Bird.DropSite.second);
				else if(label.compare(Type40[4]) == 0) Name += "VM "+FormatInt(UnitPointer->Bird.TaskSwapID);
				else if(label.compare(Type40[5]) == 0) Name += "AS "+FormatInt(UnitPointer->Bird.AttackSound);
				else if(label.compare(Type40[6]) == 0) Name += "MS "+FormatInt(UnitPointer->Bird.MoveSound);
				else if(label.compare(Type40[7]) == 0) Name += "AM "+FormatInt(UnitPointer->Bird.AnimalMode);
				else if(label.compare(Type40[8]) == 0) Name += "CC "+FormatInt(UnitPointer->Bird.Commands.size());
				else if(label.compare(Type40[9]) == 0) Name += "Ask Tapsa";
			}
            if(NameSize == Name.size() && UnitPointer->Type >= 50 && UnitPointer->Type <= 80)
            {
                NameSize = Name.size();
				if(label.compare(Type50[0]) == 0) Name += "DA "+FormatInt(UnitPointer->Type50.DefaultArmor);
				else if(label.compare(Type50[1]) == 0) Name += "AtC "+FormatInt(UnitPointer->Type50.Attacks.size());
				else if(label.compare(Type50[2]) == 0) for(short i = 0; i < UnitPointer->Type50.Attacks.size(); ++i)
				Name += "c" + FormatInt(UnitPointer->Type50.Attacks[i].Class) + " ";
				else if(label.compare(Type50[3]) == 0) Name += "ArC "+FormatInt(UnitPointer->Type50.Armours.size());
				else if(label.compare(Type50[4]) == 0) for(short i = 0; i < UnitPointer->Type50.Armours.size(); ++i)
				Name += "c" + FormatInt(UnitPointer->Type50.Armours[i].Class) + " ";
				else if(label.compare(Type50[5]) == 0) Name += "TR "+FormatInt(UnitPointer->Type50.TerRestrictionForDmgMultiplying);
				else if(label.compare(Type50[6]) == 0) Name += "MaR "+FormatFloat(UnitPointer->Type50.MaxRange);
				else if(label.compare(Type50[7]) == 0) Name += "BR "+FormatFloat(UnitPointer->Type50.BlastWidth);
				else if(label.compare(Type50[8]) == 0) Name += "RT "+FormatFloat(UnitPointer->Type50.ReloadTime);
				else if(label.compare(Type50[9]) == 0) Name += "PU "+FormatInt(UnitPointer->Type50.ProjectileUnitID);
				else if(label.compare(Type50[10]) == 0) Name += "AP "+FormatInt(UnitPointer->Type50.AccuracyPercent);
				else if(label.compare(Type50[11]) == 0) Name += "TM "+FormatInt(UnitPointer->Type50.TowerMode);
				else if(label.compare(Type50[12]) == 0) Name += "D "+FormatInt(UnitPointer->Type50.FrameDelay);
				else if(label.compare(Type50[13]) == 0)
				{
					Name += "x"+FormatInt(UnitPointer->Type50.GraphicDisplacement[0]);
					Name += " y"+FormatInt(UnitPointer->Type50.GraphicDisplacement[1]);
					Name += " z"+FormatInt(UnitPointer->Type50.GraphicDisplacement[2]);
				}
				else if(label.compare(Type50[14]) == 0) Name += "BL "+FormatInt(UnitPointer->Type50.BlastAttackLevel);
				else if(label.compare(Type50[15]) == 0) Name += "MiR "+FormatFloat(UnitPointer->Type50.MinRange);
				else if(label.compare(Type50[16]) == 0) Name += "AE "+FormatFloat(UnitPointer->Type50.AccuracyDispersion);
				else if(label.compare(Type50[17]) == 0) Name += "AG "+FormatInt(UnitPointer->Type50.AttackGraphic);
				else if(label.compare(Type50[18]) == 0) Name += "DM "+FormatInt(UnitPointer->Type50.DisplayedMeleeArmour);
				else if(label.compare(Type50[19]) == 0) Name += "DP "+FormatInt(UnitPointer->Type50.DisplayedAttack);
				else if(label.compare(Type50[20]) == 0) Name += "DR "+FormatFloat(UnitPointer->Type50.DisplayedRange);
				else if(label.compare(Type50[21]) == 0) Name += "DT "+FormatFloat(UnitPointer->Type50.DisplayedReloadTime);
			}
            if(NameSize == Name.size() && UnitPointer->Type == 60)
            {
                NameSize = Name.size();
				if(label.compare(Type60[0]) == 0) Name += "SM "+FormatInt(UnitPointer->Projectile.StretchMode);
				else if(label.compare(Type60[1]) == 0) Name += "CM "+FormatInt(UnitPointer->Projectile.SmartMode);
				else if(label.compare(Type60[2]) == 0) Name += "DA "+FormatInt(UnitPointer->Projectile.DropAnimationMode);
				else if(label.compare(Type60[3]) == 0) Name += "PM "+FormatInt(UnitPointer->Projectile.PenetrationMode);
				else if(label.compare(Type60[4]) == 0) Name += "U24 "+FormatInt(UnitPointer->Projectile.Unknown24);
				else if(label.compare(Type60[5]) == 0) Name += "PA "+FormatFloat(UnitPointer->Projectile.ProjectileArc);
			}
            if(NameSize == Name.size() && (UnitPointer->Type == 70 || UnitPointer->Type == 80))
            {
                NameSize = Name.size();
				if(label.compare(Type70[0]) == 0) Name += "Ask Tapsa";
				else if(label.compare(Type70[1]) == 0) Name += "TT "+FormatInt(UnitPointer->Creatable.TrainTime);
				else if(label.compare(Type70[2]) == 0) Name += "TL "+FormatInt(UnitPointer->Creatable.TrainLocationID);
				else if(label.compare(Type70[3]) == 0) Name += "B "+FormatInt(UnitPointer->Creatable.ButtonID);
				else if(label.compare(Type70[4]) == 0) Name += "U26 "+FormatInt(UnitPointer->Creatable.Unknown26);
				else if(label.compare(Type70[5]) == 0) Name += "U27 "+FormatInt(UnitPointer->Creatable.Unknown27);
				else if(label.compare(Type70[6]) == 0) Name += "U28 "+FormatInt(UnitPointer->Creatable.CreatableType);
				else if(label.compare(Type70[7]) == 0) Name += "HM "+FormatInt(UnitPointer->Creatable.HeroMode);
				else if(label.compare(Type70[8]) == 0) Name += "GG "+FormatInt(UnitPointer->Creatable.GarrisonGraphic);
				else if(label.compare(Type70[9]) == 0) Name += "Di "+FormatFloat(UnitPointer->Creatable.TotalProjectiles);
				else if(label.compare(Type70[10]) == 0) Name += "Da "+FormatInt(UnitPointer->Creatable.MaxTotalProjectiles);
				else if(label.compare(Type70[11]) == 0)
				{
					Name += "x"+FormatInt(UnitPointer->Creatable.ProjectileSpawningArea[0]);
					Name += " y"+FormatInt(UnitPointer->Creatable.ProjectileSpawningArea[1]);
					Name += " z"+FormatInt(UnitPointer->Creatable.ProjectileSpawningArea[2]);
				}
				else if(label.compare(Type70[12]) == 0) Name += "AP "+FormatInt(UnitPointer->Creatable.SecondaryProjectileUnit);
				else if(label.compare(Type70[13]) == 0) Name += "CG "+FormatInt(UnitPointer->Creatable.SpecialGraphic);
				else if(label.compare(Type70[14]) == 0) Name += "CM "+FormatInt(UnitPointer->Creatable.SpecialAbility);
				else if(label.compare(Type70[15]) == 0) Name += "DP "+FormatInt(UnitPointer->Creatable.DisplayedPierceArmour);
            }
            if(NameSize == Name.size() && UnitPointer->Type == 80)
            {
                NameSize = Name.size();
				if(label.compare(Type80[0]) == 0) Name += "CG "+FormatInt(UnitPointer->Building.ConstructionGraphicID);
				else if(label.compare(Type80[1]) == 0) Name += "SG "+FormatInt(UnitPointer->Building.SnowGraphicID);
				else if(label.compare(Type80[2]) == 0) Name += "AM "+FormatInt(UnitPointer->Building.AdjacentMode);
				else if(label.compare(Type80[3]) == 0) Name += "GA "+FormatInt(UnitPointer->Building.GraphicsAngle);
				else if(label.compare(Type80[4]) == 0) Name += "DB "+FormatInt(UnitPointer->Building.DisappearsWhenBuilt);
				else if(label.compare(Type80[5]) == 0) Name += "SU "+FormatInt(UnitPointer->Building.StackUnitID);
				else if(label.compare(Type80[6]) == 0) Name += "FT "+FormatInt(UnitPointer->Building.FoundationTerrainID);
				else if(label.compare(Type80[7]) == 0) Name += "OT "+FormatInt(UnitPointer->Building.OldTerrainLikeID);
				else if(label.compare(Type80[8]) == 0) Name += "R "+FormatInt(UnitPointer->Building.ResearchID);
				else if(label.compare(Type80[9]) == 0) Name += "U33 "+FormatInt(UnitPointer->Building.Unknown33);
				else if(label.compare(Type80[10]) == 0) Name += "Ask Tapsa";
				else if(label.compare(Type80[11]) == 0) Name += "HU "+FormatInt(UnitPointer->Building.HeadUnit);
				else if(label.compare(Type80[12]) == 0) Name += "TU "+FormatInt(UnitPointer->Building.TransformUnit);
				else if(label.compare(Type80[13]) == 0) Name += "US "+FormatInt(UnitPointer->Building.UnknownSound);
				else if(label.compare(Type80[14]) == 0) Name += "CS "+FormatInt(UnitPointer->Building.ConstructionSound);
				else if(label.compare(Type80[15]) == 0) Name += "GT "+FormatInt(UnitPointer->Building.GarrisonType);
				else if(label.compare(Type80[16]) == 0) Name += "GH "+FormatFloat(UnitPointer->Building.GarrisonHealRate);
				else if(label.compare(Type80[17]) == 0) Name += "U35 "+FormatFloat(UnitPointer->Building.Unknown35);
				else if(label.compare(Type80[18]) == 0) Name += "PU "+FormatInt(UnitPointer->Building.PileUnit);
				else if(label.compare(Type80[19]) == 0) Name += "Ask Tapsa";
			}
            Name += NameSize0 == Name.size() ? "NA, " : ", ";
            if(Selection[1] == 0) break;
		}
	}

//Names:
	if(!LangDLLstring(dataset->Civs[civ].Units[index].LanguageDLLName, 2).empty())
	{
		return Name + string(LangDLLstring(dataset->Civs[civ].Units[index].LanguageDLLName, 64));
	}
//InternalName:
	if(!dataset->Civs[civ].Units[index].Name.empty())
	{
		return Name + dataset->Civs[civ].Units[index].Name;
	}
	return Name + "New Unit";
}

void AGE_Frame::OnUnitsSearch(wxCommandEvent &event)
{
	short Selection = Units_Civs_List->GetSelection();
	if(Selection == wxNOT_FOUND) return;

	How2List = SEARCH;
	ListUnits(Selection, false);
}

void AGE_Frame::ListUnits(short civ, bool all)
{
	InitUnits(civ, all);
	wxTimerEvent E;
	OnUnitsTimer(E);
}

void AGE_Frame::InitUnits(short civ, bool all)
{
	InitSearch(Units_Search->GetValue().MakeLower(), Units_Search_R->GetValue().MakeLower());
	for(size_t loop = 0; loop < 2; ++loop)
	useAnd[loop] = Units_UseAnd[loop]->GetValue();

	Units_Civs_List->SetSelection(civ);

    Units_ListV->names.clear();
    Units_ListV->indexes.clear();
	if(all)
	{
		AGE_AreaTT84::units.Clear();
		AGE_AreaTT84::units.Alloc(dataset->Civs.front().Units.size());
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
	for(size_t loop = 0; loop < dataset->Civs[civ].Units.size(); ++loop)
	{
        if(all)
        {
            short cult = 0;
            wxString name = GetUnitName(loop, 0);
            while("Nonexistent" == name && ++cult < dataset->Civs.size())
            {
                name = GetUnitName(loop, cult);
            }
            AGE_AreaTT84::units.Add(" "+FormatInt(loop)+" - "+name);
        }
		if(matcher > genie::UT_25)
		{
			if(matcher == genie::UT_Projectile)
			if(dataset->Civs[civ].Units[loop].Type != genie::UT_Projectile) continue;
			if(dataset->Civs[civ].Units[loop].Type < matcher) continue;
			if(dataset->Civs[civ].Units[loop].Type == genie::UT_AoeTrees) continue;
		}
		wxString Name = " "+FormatInt(loop)+" - "+GetUnitName(loop, civ, true)+" ";
		if(SearchMatches(Name.Lower()))
		{
			Units_ListV->names.Add(Name);
            Units_ListV->indexes.push_back(loop);
		}
	}

    virtualListing(Units_ListV);
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

	for(size_t loop = 0; loop < 2; ++loop)
	useAnd[loop] = false;
}

void AGE_Frame::OnChooseGraphic(wxCommandEvent &event)
{
    if(UnitIDs.size() && dataset && UnitCivID < dataset->Civs.size() && UnitIDs.front() < dataset->Civs[UnitCivID].Units.size())
    {
        unitSLP.datID = loadChosenGraphic(UnitIDs.front());
        unitSLP.slpID = -2;
        if(slp_window) slp_view->Refresh();
    }
}

void AGE_Frame::OnUnitsSelect(wxCommandEvent &event)
{
    if(!unitTimer.IsRunning())
        unitTimer.Start(150);
}

//	This links data into user interface
void AGE_Frame::OnUnitsTimer(wxTimerEvent &event)
{
    unitTimer.Stop();
	auto selections = Units_ListV->GetSelectedItemCount();

	wxBusyCursor WaitCursor;
    getSelectedItems(selections, Units_ListV, UnitIDs);
	UnitCivID = Units_Civs_List->GetSelection();

	// Auto-copy stuff
	SelectedCivs.resize(1);
	SelectedCivs.front() = UnitCivID;
	if(AutoCopy)
	{
		for(short civ = 0; civ < dataset->Civs.size(); ++civ)
		{
			// Counts all selected civs and always the one being edited.
			if(Units_CivBoxes[civ]->IsChecked() && civ != UnitCivID)
				SelectedCivs.push_back(civ);
		}
	}

    for(auto &box: uiGroupUnit) box->clear();
    Units_ID1->clear();
    Units_ID2->clear();
    Units_ID3->clear();

	short unitType = -1;
	genie::Unit * UnitPointer = 0;
	for(auto sel = selections; sel--> 0;)
	{
        unitType = -1;
		// This makes auto-copy automatic.
		for(short vecCiv = SelectedCivs.size(); vecCiv--> 0;)
		{
			if(dataset->Civs[SelectedCivs[vecCiv]].UnitPointers[UnitIDs[sel]] == 0) continue;
            UnitCivID = SelectedCivs[vecCiv];
			UnitPointer = &dataset->Civs[UnitCivID].Units[UnitIDs[sel]];
			unitType = (short)UnitPointer->Type;
			// Assing data to editing boxes
			switch(unitType)
			{
				case 80:
				{
					if(CopyGraphics || vecCiv == 0)
					Units_ConstructionGraphicID->prepend(&UnitPointer->Building.ConstructionGraphicID);
					Units_AdjacentMode->prepend(&UnitPointer->Building.AdjacentMode);
					Units_IconAngle->prepend(&UnitPointer->Building.GraphicsAngle);
					Units_DisappearsWhenBuilt->prepend(&UnitPointer->Building.DisappearsWhenBuilt);
					Units_StackUnitID->prepend(&UnitPointer->Building.StackUnitID);
					Units_TerrainID->prepend(&UnitPointer->Building.FoundationTerrainID);
					Units_OldTerrainLikeID->prepend(&UnitPointer->Building.OldTerrainLikeID);
					Units_ResearchID->prepend(&UnitPointer->Building.ResearchID);
					if(GenieVersion >= genie::GV_AoKA)
					{
						if(GenieVersion >= genie::GV_TC)
						{
							if(CopyGraphics || vecCiv == 0)
							Units_SnowGraphicID->prepend(&UnitPointer->Building.SnowGraphicID);
						}
						Units_Unknown33->prepend(&UnitPointer->Building.Unknown33);
						for(size_t loop = 0; loop < 4; ++loop)
						{
							Units_AnnexUnit[loop]->prepend(&UnitPointer->Building.Annexes[loop].UnitID);
							Units_AnnexUnitMisplacement[loop][0]->prepend(&UnitPointer->Building.Annexes[loop].Misplacement.first);
							Units_AnnexUnitMisplacement[loop][1]->prepend(&UnitPointer->Building.Annexes[loop].Misplacement.second);
						}
						Units_HeadUnit->prepend(&UnitPointer->Building.HeadUnit);
						Units_TransformUnit->prepend(&UnitPointer->Building.TransformUnit);
						Units_UnknownSound->prepend(&UnitPointer->Building.UnknownSound);
						Units_GarrisonType->prepend(&UnitPointer->Building.GarrisonType);
						Units_GarrisonHealRate->prepend(&UnitPointer->Building.GarrisonHealRate);
						Units_Unknown35->prepend(&UnitPointer->Building.Unknown35);
						Units_PileUnit->prepend(&UnitPointer->Building.PileUnit);
						for(size_t loop = 0; loop < Units_LootSwitch.size(); ++loop)
						Units_LootSwitch[loop]->prepend(&UnitPointer->Building.LootingTable[loop]);
					}
					Units_ConstructionSound->prepend(&UnitPointer->Building.ConstructionSound);
				}
				case 70:
				{
					for(size_t loop = 0; loop < 3; ++loop)
					{
						Units_CostType[loop]->prepend(&UnitPointer->Creatable.ResourceCosts[loop].Type);
						Units_CostAmount[loop]->prepend(&UnitPointer->Creatable.ResourceCosts[loop].Amount);
						Units_CostUsed[loop]->prepend(&UnitPointer->Creatable.ResourceCosts[loop].Enabled);
					}
					Units_TrainTime->prepend(&UnitPointer->Creatable.TrainTime);
					Units_TrainLocationID->prepend(&UnitPointer->Creatable.TrainLocationID);
					Units_ButtonID->prepend(&UnitPointer->Creatable.ButtonID);
					if(GenieVersion >= genie::GV_AoKA)
					{
						Units_Unknown26->prepend(&UnitPointer->Creatable.Unknown26);
						Units_Unknown27->prepend(&UnitPointer->Creatable.Unknown27);
						Units_UnknownType->prepend(&UnitPointer->Creatable.CreatableType);
						if(GenieVersion >= genie::GV_AoKB)
						{
							Units_HeroMode->prepend(&UnitPointer->Creatable.HeroMode);
							if(CopyGraphics || vecCiv == 0)
							{
								Units_GarrisonGraphic->prepend(&UnitPointer->Creatable.GarrisonGraphic);
							}
						}
						Units_MissileCount->prepend(&UnitPointer->Creatable.TotalProjectiles);
						Units_MissileDuplicationCount->prepend(&UnitPointer->Creatable.MaxTotalProjectiles);
						for(size_t loop = 0; loop < 3; ++loop)
						{
							Units_AttackMissileDuplicationSpawning[loop]->prepend(&UnitPointer->Creatable.ProjectileSpawningArea[loop]);
						}
						Units_AttackMissileDuplicationUnit->prepend(&UnitPointer->Creatable.SecondaryProjectileUnit);
						Units_ChargingGraphic->prepend(&UnitPointer->Creatable.SpecialGraphic);
						Units_ChargingMode->prepend(&UnitPointer->Creatable.SpecialAbility);
					}
					Units_DisplayedPierceArmour->prepend(&UnitPointer->Creatable.DisplayedPierceArmour);
				}
				case 60:
				case 50:
				{
					Units_DefaultArmor->prepend(&UnitPointer->Type50.DefaultArmor);
					Units_TerRestrictionForDmgMultiply->prepend(&UnitPointer->Type50.TerRestrictionForDmgMultiplying);
					Units_MaxRange->prepend(&UnitPointer->Type50.MaxRange);
					Units_BlastWidth->prepend(&UnitPointer->Type50.BlastWidth);
					Units_ReloadTime1->prepend(&UnitPointer->Type50.ReloadTime);
					Units_ProjectileUnitID->prepend(&UnitPointer->Type50.ProjectileUnitID);
					Units_AccuracyPercent->prepend(&UnitPointer->Type50.AccuracyPercent);
					Units_TowerMode->prepend(&UnitPointer->Type50.TowerMode);
					Units_Delay->prepend(&UnitPointer->Type50.FrameDelay);
					for(size_t loop = 0; loop < 3; ++loop)
					{
						Units_GraphicDisplacement[loop]->prepend(&UnitPointer->Type50.GraphicDisplacement[loop]);
					}
					Units_BlastAttackLevel->prepend(&UnitPointer->Type50.BlastAttackLevel);
					Units_MinRange->prepend(&UnitPointer->Type50.MinRange);
					if(GenieVersion >= genie::GV_AoKB)
					{
						Units_AccuracyDispersion->prepend(&UnitPointer->Type50.AccuracyDispersion);
					}
					if(CopyGraphics || vecCiv == 0)
					Units_AttackGraphic->prepend(&UnitPointer->Type50.AttackGraphic);
					Units_DisplayedMeleeArmour->prepend(&UnitPointer->Type50.DisplayedMeleeArmour);
					Units_DisplayedAttack->prepend(&UnitPointer->Type50.DisplayedAttack);
					Units_DisplayedRange->prepend(&UnitPointer->Type50.DisplayedRange);
					Units_ReloadTime2->prepend(&UnitPointer->Type50.DisplayedReloadTime);
				}
				case 40:
				{
					Units_ActionWhenDiscoveredID->prepend(&UnitPointer->Bird.ActionWhenDiscoveredID);
					Units_SearchRadius->prepend(&UnitPointer->Bird.SearchRadius);
					Units_WorkRate->prepend(&UnitPointer->Bird.WorkRate);
					Units_DropSite[0]->prepend(&UnitPointer->Bird.DropSite.first);
					Units_DropSite[1]->prepend(&UnitPointer->Bird.DropSite.second);
					Units_TaskSwapID->prepend(&UnitPointer->Bird.TaskSwapID);
					Units_AttackSound->prepend(&UnitPointer->Bird.AttackSound);
					Units_MoveSound->prepend(&UnitPointer->Bird.MoveSound);
					Units_AnimalMode->prepend(&UnitPointer->Bird.AnimalMode);
				}
				case 30:
				{
					if(CopyGraphics || vecCiv == 0)
					{
						Units_WalkingGraphic[0]->prepend(&UnitPointer->DeadFish.WalkingGraphic.first);
						Units_WalkingGraphic[1]->prepend(&UnitPointer->DeadFish.WalkingGraphic.second);
					}
					Units_RotationSpeed->prepend(&UnitPointer->DeadFish.RotationSpeed);
					Units_Unknown11->prepend(&UnitPointer->DeadFish.Unknown11);
					Units_TrackingUnit->prepend(&UnitPointer->DeadFish.TrackingUnit);
					Units_TrackingUnitUsed->prepend(&UnitPointer->DeadFish.TrackingUnitUsed);
					Units_TrackingUnitDensity->prepend(&UnitPointer->DeadFish.TrackingUnitDensity);
					Units_Unknown16->prepend(&UnitPointer->DeadFish.Unknown16);
					if(GenieVersion >= genie::GV_AoKB)
                    for(size_t loop = 0; loop < Units_RotationAngles.size(); ++loop)
                    Units_RotationAngles[loop]->prepend(&UnitPointer->DeadFish.RotationAngles[loop]);
				}
				case 25:
				case 20:
				{
					Units_Speed->prepend(&UnitPointer->Speed);
				}
				case 90:
				case 15:
				case 10:
                {
                    Units_Type->prepend(&UnitPointer->Type);
                    Units_ID1->prepend(&UnitPointer->ID1);
                    Units_LanguageDLLName->prepend(&UnitPointer->LanguageDLLName);
                    Units_LanguageDLLCreation->prepend(&UnitPointer->LanguageDLLCreation);
                    Units_Class->prepend(&UnitPointer->Class);
                    if(CopyGraphics || vecCiv == 0)
                    {
                        Units_StandingGraphic[0]->prepend(&UnitPointer->StandingGraphic.first);
                        Units_DyingGraphic[0]->prepend(&UnitPointer->DyingGraphic.first);
                        Units_DyingGraphic[1]->prepend(&UnitPointer->DyingGraphic.second);
                        Units_IconID->prepend(&UnitPointer->IconID);
                    }
                    Units_DeathMode->prepend(&UnitPointer->DeathMode);
                    Units_HitPoints->prepend(&UnitPointer->HitPoints);
                    Units_LineOfSight->prepend(&UnitPointer->LineOfSight);
                    Units_GarrisonCapacity->prepend(&UnitPointer->GarrisonCapacity);
                    Units_SizeRadius[0]->prepend(&UnitPointer->CollisionSize.x);
                    Units_SizeRadius[1]->prepend(&UnitPointer->CollisionSize.y);
                    Units_HPBarHeight1->prepend(&UnitPointer->CollisionSize.z);
                    Units_TrainSound[0]->prepend(&UnitPointer->TrainSound.first);
                    Units_DeadUnitID->prepend(&UnitPointer->DeadUnitID);
                    Units_PlacementMode->prepend(&UnitPointer->PlacementMode);
                    Units_AirMode->prepend(&UnitPointer->AirMode);
                    Units_HideInEditor->prepend(&UnitPointer->HideInEditor);
                    Units_Unknown1->prepend(&UnitPointer->Unknown1);
                    Units_PlacementSideTerrain[0]->prepend(&UnitPointer->PlacementSideTerrain.first);
                    Units_PlacementSideTerrain[1]->prepend(&UnitPointer->PlacementSideTerrain.second);
                    Units_PlacementTerrain[0]->prepend(&UnitPointer->PlacementTerrain.first);
                    Units_PlacementTerrain[1]->prepend(&UnitPointer->PlacementTerrain.second);
                    Units_ClearanceSize[0]->prepend(&UnitPointer->ClearanceSize.first);
                    Units_ClearanceSize[1]->prepend(&UnitPointer->ClearanceSize.second);
                    Units_HillMode->prepend(&UnitPointer->HillMode);
                    Units_VisibleInFog->prepend(&UnitPointer->VisibleInFog);
                    Units_TerrainRestriction->prepend(&UnitPointer->TerrainRestriction);
                    Units_FlyMode->prepend(&UnitPointer->FlyMode);
                    Units_ResourceCapacity->prepend(&UnitPointer->ResourceCapacity);
                    Units_ResourceDecay->prepend(&UnitPointer->ResourceDecay);
                    Units_BlastDefenseLevel->prepend(&UnitPointer->BlastDefenseLevel);
                    Units_SubType->prepend(&UnitPointer->SubType);
                    Units_InteractionMode->prepend(&UnitPointer->InteractionMode);
                    Units_MinimapMode->prepend(&UnitPointer->MinimapMode);
                    Units_SelectionEffect->prepend(&UnitPointer->SelectionEffect);
                    Units_EditorSelectionColour->prepend(&UnitPointer->EditorSelectionColour);
                    if(GenieVersion >= genie::GV_AoKA)
                    {
                        Units_TrainSound[1]->prepend(&UnitPointer->TrainSound.second);
                        Units_SelectionMask->prepend(&UnitPointer->SelectionMask);
                        Units_SelectionShapeType->prepend(&UnitPointer->SelectionShapeType);
                        Units_SelectionShape->prepend(&UnitPointer->SelectionShape);
                        Units_ID3->prepend(&UnitPointer->ID3);
                        if(GenieVersion >= genie::GV_AoKB)
                        {
                            if(CopyGraphics || vecCiv == 0)
                            Units_StandingGraphic[1]->prepend(&UnitPointer->StandingGraphic.second);
                            if(GenieVersion >= genie::GV_AoK)
                            {
                                Units_Disabled->prepend(&UnitPointer->Disabled);
                                if(GenieVersion >= genie::GV_TC)
                                {
                                    Units_Attribute->prepend(&UnitPointer->Attribute);
                                    Units_Civ->prepend(&UnitPointer->Civilization);
                                    Units_Nothing->prepend(&UnitPointer->Nothing);
                                    if(GenieVersion >= genie::GV_SWGB)
                                    {
                                        Units_Name2->prepend(&UnitPointer->Name2);
                                        Units_Unitline->prepend(&UnitPointer->Unitline);
                                        Units_MinTechLevel->prepend(&UnitPointer->MinTechLevel);
                                    }
                                }
                            }
                        }
                    }
                    Units_Enabled->prepend(&UnitPointer->Enabled);
                    Units_CommandID->prepend(&UnitPointer->CommandAttribute);
                    Units_Unknown3A->prepend(&UnitPointer->Unknown3A);
                    Units_MinimapColor->prepend(&UnitPointer->MinimapColor);
                    Units_LanguageDLLHelp->prepend(&UnitPointer->LanguageDLLHelp);
                    Units_LanguageDLLHotKeyText->prepend(&UnitPointer->LanguageDLLHotKeyText);
                    Units_HotKey->prepend(&UnitPointer->HotKey);
                    Units_Unselectable->prepend(&UnitPointer->Unselectable);
                    Units_Unknown6->prepend(&UnitPointer->Unknown6);
                    Units_Unknown7->prepend(&UnitPointer->Unknown7);
                    Units_Unknown8->prepend(&UnitPointer->Unknown8);
                    Units_SelectionRadius[0]->prepend(&UnitPointer->SelectionShapeSize.x);
                    Units_SelectionRadius[1]->prepend(&UnitPointer->SelectionShapeSize.y);
                    Units_HPBarHeight2->prepend(&UnitPointer->SelectionShapeSize.z);
                    Units_SelectionSound->prepend(&UnitPointer->SelectionSound);
                    Units_DyingSound->prepend(&UnitPointer->DyingSound);
                    Units_AttackMode->prepend(&UnitPointer->AttackMode);
                    Units_Unknown10->prepend(&UnitPointer->Unknown10);
                    Units_Name->prepend(&UnitPointer->Name);
                    Units_ID2->prepend(&UnitPointer->ID2);
                    for(size_t loop = 0; loop < 3; ++loop)
                    {
                        ResourceStorage_Type[loop]->prepend(&UnitPointer->ResourceStorages[loop].Type);
                        ResourceStorage_Amount[loop]->prepend(&UnitPointer->ResourceStorages[loop].Amount);
                        ResourceStorage_Enabled[loop]->prepend(&UnitPointer->ResourceStorages[loop].Enabled);
                    }
                }
			}
			if(unitType == 60)
			{
				Units_StretchMode->prepend(&UnitPointer->Projectile.StretchMode);
				Units_SmartMode->prepend(&UnitPointer->Projectile.SmartMode);
				Units_DropAnimationMode->prepend(&UnitPointer->Projectile.DropAnimationMode);
				Units_PenetrationMode->prepend(&UnitPointer->Projectile.PenetrationMode);
				Units_Unknown24->prepend(&UnitPointer->Projectile.Unknown24);
				Units_ProjectileArc->prepend(&UnitPointer->Projectile.ProjectileArc);
			}
		}
	}
	SetStatusText("Civilization: "+lexical_cast<string>(UnitCivID)+"    Selections: "+lexical_cast<string>(selections)+"    Selected unit: "+lexical_cast<string>(UnitIDs.front()), 0);

    bool showUnitData = -1 != unitType;
	switch(unitType)
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
    Units_DLL_LanguageName->index = Units_DLL_LanguageHelp->index = 5000;
    Units_DLL_LanguageCreation->index = Units_DLL_LanguageHKText->index = 6000;
    Units_DLL_HotKey4->index = 16000;
    if(UnitPointer)
    {
        if(80 == unitType)
        {
            if(GenieVersion >= genie::GV_AoKA)
            {
                Units_GarrisonType_CheckBox[0]->SetValue(UnitPointer->Building.GarrisonType & 0x01);
                Units_GarrisonType_CheckBox[1]->SetValue(UnitPointer->Building.GarrisonType & 0x02);
                Units_GarrisonType_CheckBox[2]->SetValue(UnitPointer->Building.GarrisonType & 0x04);
                Units_GarrisonType_CheckBox[3]->SetValue(UnitPointer->Building.GarrisonType & 0x08);
                Units_GarrisonType_CheckBox[4]->SetValue(UnitPointer->Building.GarrisonType & 0x10);
                Units_GarrisonType_CheckBox[5]->SetValue(UnitPointer->Building.GarrisonType & 0x20);
                Units_GarrisonType_CheckBox[6]->SetValue(UnitPointer->Building.GarrisonType & 0x40);
                Units_GarrisonType_CheckBox[7]->SetValue(UnitPointer->Building.GarrisonType & 0x80);
            }
        }
        Units_DLL_LanguageName->index = UnitPointer->LanguageDLLName;
        Units_DLL_LanguageCreation->index = UnitPointer->LanguageDLLCreation;
        if(GenieVersion >= genie::GV_AoKA)
        {
            Units_DLL_LanguageHelp->index = UnitPointer->LanguageDLLHelp - 79000;
            Units_DLL_LanguageHKText->index = UnitPointer->LanguageDLLHotKeyText - 140000;
            if(GenieVersion >= genie::GV_TC)
            {
                Units_Attribute_CheckBox[0]->SetValue(UnitPointer->Attribute & 0x01);
                Units_Attribute_CheckBox[1]->SetValue(UnitPointer->Attribute & 0x02);
                Units_Attribute_CheckBox[2]->SetValue(UnitPointer->Attribute & 0x04);
                Units_Attribute_CheckBox[3]->SetValue(UnitPointer->Attribute & 0x08);
                Units_Attribute_CheckBox[4]->SetValue(UnitPointer->Attribute & 0x10);
                Units_Attribute_CheckBox[5]->SetValue(UnitPointer->Attribute & 0x20);
                Units_Attribute_CheckBox[6]->SetValue(UnitPointer->Attribute & 0x40);
                Units_Attribute_CheckBox[7]->SetValue(UnitPointer->Attribute & 0x80);
            }
        }
        else
        {
            Units_DLL_LanguageHelp->index = (uint16_t)UnitPointer->LanguageDLLHelp;
            Units_DLL_LanguageHKText->index = (uint16_t)UnitPointer->LanguageDLLHotKeyText;
        }
        Units_DLL_HotKey4->index = UnitPointer->HotKey;
        if(GenieVersion >= genie::GV_AoKB)
        {
            string newLabel = " ( ", aste = "° ";
            for(size_t loop = 0; loop < Units_RotationAngles.size(); ++loop)
            {
                int angle = UnitPointer->DeadFish.RotationAngles[loop] * 57.2957802;
                if(angle == 0x80000000) newLabel += "max" + aste;
                else newLabel += lexical_cast<string>(angle) + aste;
            }
            Units_RotationAngles_Text->SetLabel(Units_RotationAngles_Label + newLabel + ")");
        }
        visibleUnitCiv->SetLabel(dataset->Civs[UnitCivID].Name);
        if(!palettes.empty() && !palettes.front().empty())
        {
            genie::Color minimap = palettes.front()[(uint8_t)UnitPointer->MinimapColor];
            genie::Color editorSel = palettes.front()[(uint8_t)UnitPointer->EditorSelectionColour];
            setForeAndBackColors(Units_MinimapColor, wxColour(minimap.r, minimap.g, minimap.b));
            setForeAndBackColors(Units_EditorSelectionColour, wxColour(editorSel.r, editorSel.g, editorSel.b));
        }
        if(UnitPointer->Type == 80 && (GenieVersion < genie::GV_SWGB
        ? UnitPointer->Class != 51 && UnitPointer->Class != 54
        : UnitPointer->Class != 34 && UnitPointer->Class != 36))
        {
            int set0 = 50704;
            if(GenieVersion == genie::GV_CC) set0 = 53240;
            iconSLP.slpID = set0 + dataset->Civs[UnitCivID].IconSet;
        }
        else if(GenieVersion == genie::GV_CC)
        {
            iconSLP.slpID = 53250 + dataset->Civs[UnitCivID].IconSet;
        }
        else if(GenieVersion == genie::GV_SWGB)
        {
            iconSLP.slpID = 50733 + dataset->Civs[UnitCivID].IconSet;
        }
        else
        {
            iconSLP.slpID = 50730;
        }
        iconSLP.frameID = UnitPointer->IconID + UnitPointer->Building.GraphicsAngle; // frame
        unitSLP.datID = loadChosenGraphic(UnitIDs.front());
        unitSLP.slpID = -2;
	}
    else
    {
        visibleUnitCiv->SetLabel("None");
        iconSLP.slpID = unitSLP.datID = -1;
    }
    Units_DLL_LanguageName->SetLabel(LangDLLstring(Units_DLL_LanguageName->index, 64));
    Units_DLL_LanguageCreation->SetLabel(LangDLLstring(Units_DLL_LanguageCreation->index, 64));
    Units_DLL_LanguageHelp->SetLabel(LangDLLstring(Units_DLL_LanguageHelp->index, 512));
    Units_LanguageDLLConverter[0]->SetLabel(lexical_cast<string>(Units_DLL_LanguageHelp->index));
    Units_DLL_LanguageHKText->SetLabel(LangDLLstring(Units_DLL_LanguageHKText->index, 64));
    Units_LanguageDLLConverter[1]->SetLabel(lexical_cast<string>(Units_DLL_LanguageHKText->index));
    Units_DLL_HotKey4->SetLabel(LangDLLstring(Units_DLL_HotKey4->index, 16));

    Units_Type_ComboBox->Enable(showUnitData);
    Units_DLL_LanguageName->Enable(showUnitData);
    Units_DLL_LanguageCreation->Enable(showUnitData);
    Units_DLL_LanguageHelp->Enable(showUnitData);
    Units_DLL_LanguageHKText->Enable(showUnitData);
    Units_DLL_HotKey4->Enable(showUnitData);
    Units_LanguageDLLConverter[0]->Enable(showUnitData);
    Units_LanguageDLLConverter[1]->Enable(showUnitData);

	// Don't count disabled units anymore.
	for(size_t loop = SelectedCivs.size(); loop--> 0;)
	{
		if(dataset->Civs[SelectedCivs[loop]].UnitPointers[UnitIDs.front()] == 0)
			SelectedCivs.erase(SelectedCivs.begin() + loop);
	}

	ListUnitDamageGraphics();
	ListUnitAttacks();
	ListUnitArmors();
	if(GenieVersion >= genie::GV_AoK)	// AoK, TC, SWGB or CC
	{
		genie::UnitHeader * UnitHeadPointer;
		for(auto sel = selections; sel--> 0;)
		{
			UnitHeadPointer = &dataset->UnitHeaders[UnitIDs[sel]];

			Units_Exists->prepend(&UnitHeadPointer->Exists);
		}

		Units_UnitHeads_Name->SetLabel(" "+lexical_cast<string>(UnitIDs.front())+" - "+GetUnitName(UnitIDs.front(), 0));
	}
	else	// AoE or RoR
	{
		Units_UnitHeads_Name->SetLabel("");
	}
	ListUnitCommands();

    AGE_SLP::setbearing = 1u;
    for(auto &box: uiGroupUnit) box->update();
    Units_ID1->refill();
    Units_ID2->refill();
    Units_ID3->refill();
	//	Refresh(); // Too much lag.
    Units_IconID_SLP->Refresh();
    if(slp_window) slp_view->Refresh();
}

void AGE_Frame::OnDrawIconSLP(wxPaintEvent &event)
{
    wxBufferedPaintDC dc(Units_IconID_SLP);
    dc.Clear();
    if(iconSLP.slpID == -1)
    {
        dc.DrawLabel("No unit", wxNullBitmap, wxRect(0, 0, 100, 40));
        return;
    }
    if(iconSLP.frameID == -1)
    {
        dc.DrawLabel("No icon", wxNullBitmap, wxRect(0, 0, 100, 40));
        return;
    }
    SLPtoBitMap(&iconSLP);
    if(iconSLP.bitmap.IsOk())
    dc.DrawBitmap(iconSLP.bitmap, 0, 0, true);
    else dc.DrawLabel("!SLP/frame " + FormatInt(iconSLP.slpID), wxNullBitmap, wxRect(0, 0, 100, 40));
}

int AGE_Frame::loadChosenGraphic(unsigned int unitID)
{
    genie::Unit *unit = &dataset->Civs[UnitCivID].Units[unitID];
    if(slp_unit_actions->GetSelection() && CommandIDs.size())
    {
        genie::UnitCommand *action = 0;
        if(GenieVersion >= genie::GV_AoK)
        {
            if(CommandIDs.front() < dataset->UnitHeaders[unitID].Commands.size())
            action = &dataset->UnitHeaders[unitID].Commands[CommandIDs.front()];
        }
        else
        {
            if(CommandIDs.front() < unit->Bird.Commands.size())
            action = &unit->Bird.Commands[CommandIDs.front()];
        }
        if(!action) goto CHOOSE_NORMAL;
        int graphicID;
        switch(slp_unit_actions->GetSelection())
        {
            case 1: graphicID = action->ToolGraphicID; break;
            case 2: graphicID = action->ProceedingGraphicID; break;
            case 3: graphicID = action->ActionGraphicID; break;
            case 4: graphicID = action->CarryingGraphicID; break;
            default: goto CHOOSE_NORMAL;
        }
        if(graphicID != -1 && GenieVersion >= genie::GV_SWGB && unit->Class == 58)
            graphicID += dataset->Civs[UnitCivID].IconSet;
        return graphicID;
    }
CHOOSE_NORMAL:
    switch(slp_radio->GetSelection())
    {
        case 0: return unit->StandingGraphic.first;
        case 1: return unit->StandingGraphic.second;
        case 2: return unit->DyingGraphic.first;
        case 3: return unit->DyingGraphic.second;
        case 4: return unit->DeadFish.WalkingGraphic.first;
        case 5: return unit->DeadFish.WalkingGraphic.second;
        case 6: return unit->Building.ConstructionGraphicID;
        case 7: return unit->Type50.AttackGraphic;
        default: return -1;
    }
}

void AGE_Frame::AddAnnexAndStackGraphics(unsigned int unitID, int offsetX, int offsetY, int apply)
{
    if(unitID >= dataset->Civs[UnitCivID].Units.size()) return;
    unsigned int unitGraphic = -1;
    switch(apply)
    {
        case 0: unitGraphic = loadChosenGraphic(unitID); break;
        case 1:
            if(DamageGraphicIDs.size() && DamageGraphicIDs.front() < dataset->Civs[UnitCivID].Units[unitID].DamageGraphics.size())
            {
                unitGraphic = dataset->Civs[UnitCivID].Units[unitID].DamageGraphics[DamageGraphicIDs.front()].GraphicID;
                if(dataset->Civs[UnitCivID].Units[unitID].DamageGraphics[DamageGraphicIDs.front()].ApplyMode == 2)
                unitSLP.deltas.clear();
                break;
            }
            else return;
        case 2: unitGraphic = dataset->Civs[UnitCivID].Units[unitID].Building.SnowGraphicID; break;
        case 3: unitGraphic = dataset->Civs[UnitCivID].Units[unitID].Creatable.GarrisonGraphic; break;
    }
    if(unitGraphic >= dataset->Graphics.size()) return;
    AGE_SLP baseSLP;
    baseSLP.initStats(unitGraphic, *dataset);
    unitSLP.angleset.insert(baseSLP.angles);
    if(dataset->Graphics[unitGraphic].Deltas.size())
    for(auto const &delta: dataset->Graphics[unitGraphic].Deltas)
    {
        AGE_SLP deltaSLP;
        if(delta.GraphicID < dataset->Graphics.size())
        {
            deltaSLP.initStats(delta.GraphicID, *dataset);
            unitSLP.angleset.insert(deltaSLP.angles);
        }
        else
        {
            deltaSLP = baseSLP;
        }
        deltaSLP.xdelta = delta.DirectionX + offsetX;
        deltaSLP.ydelta = delta.DirectionY + offsetY;
        unitSLP.deltas.insert(make_pair(offsetY, deltaSLP));
    }
    else
    {
        baseSLP.xdelta = offsetX;
        baseSLP.ydelta = offsetY;
        unitSLP.deltas.insert(make_pair(offsetY, baseSLP));
    }
}

void AGE_Frame::CalcAnnexCoords(const genie::unit::BuildingAnnex *annex)
{
    float offsetX = dataset->TerrainBlock.TileHalfWidth * (annex->Misplacement.first + annex->Misplacement.second);
    float offsetY = dataset->TerrainBlock.TileHalfHeight * (-annex->Misplacement.first + annex->Misplacement.second);
    AddAnnexAndStackGraphics(annex->UnitID, offsetX, offsetY);
}

void AGE_Frame::OnUnitsAdd(wxCommandEvent &event)
{
	if(!dataset) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion >= genie::GV_AoK)	// AoK, TC, SWGB or CC
	{
		genie::UnitHeader Temp1;
		Temp1.setGameVersion(GenieVersion);
		dataset->UnitHeaders.push_back(Temp1);
	}

	genie::Unit Temp2;
	Temp2.setGameVersion(GenieVersion);
	for(size_t loop = 0; loop < dataset->Civs.size(); ++loop)
	{
		dataset->Civs[loop].Units.push_back(Temp2);
		dataset->Civs[loop].UnitPointers.push_back(1);
		if(EnableIDFix)
		{
			dataset->Civs[loop].Units[dataset->Civs.front().Units.size()-1].ID1 = (int16_t)(dataset->Civs.front().Units.size()-1); // ID Fix
			dataset->Civs[loop].Units[dataset->Civs.front().Units.size()-1].ID2 = (int16_t)(dataset->Civs.front().Units.size()-1);
			if(GenieVersion >= genie::GV_AoK)
			dataset->Civs[loop].Units[dataset->Civs.front().Units.size()-1].ID3 = (int16_t)(dataset->Civs.front().Units.size()-1);
		}
	}
	How2List = ADD;
	ListUnits(UnitCivID);

	if(GenieVersion < genie::GV_SWGB && dataset->Civs.front().Units.size() > 900) SetStatusText("Units between 900 and 1000 mess up the AI!", 0);
}

void AGE_Frame::OnUnitsInsert(wxCommandEvent &event)
{
	auto selections = Units_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion >= genie::GV_AoK)	// AoK, TC, SWGB or CC
	{
		genie::UnitHeader Temp1;
		Temp1.setGameVersion(GenieVersion);
		dataset->UnitHeaders.insert(dataset->UnitHeaders.begin() + UnitIDs.front(), Temp1);
	}

	genie::Unit Temp2;
	Temp2.setGameVersion(GenieVersion);
	for(size_t loop = 0; loop < dataset->Civs.size(); ++loop)
	{
		dataset->Civs[loop].Units.insert(dataset->Civs[loop].Units.begin() + UnitIDs.front(), Temp2);
		dataset->Civs[loop].UnitPointers.insert(dataset->Civs[loop].UnitPointers.begin() + UnitIDs.front(), 1);
		if(EnableIDFix)
		for(size_t loop2 = UnitIDs.front();loop2 < dataset->Civs.front().Units.size(); ++loop2) // ID Fix
		{
			dataset->Civs[loop].Units[loop2].ID1 = loop2;
			dataset->Civs[loop].Units[loop2].ID2 = loop2;
			if(GenieVersion >= genie::GV_AoK)
			dataset->Civs[loop].Units[loop2].ID3 = loop2;
		}
	}
	How2List = INSNEW;
	ListUnits(UnitCivID);
}

void AGE_Frame::OnUnitsDelete(wxCommandEvent &event)
{
	auto selections = Units_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion >= genie::GV_AoK)
	{
		for(auto loop = selections; loop--> 0;)
		dataset->UnitHeaders.erase(dataset->UnitHeaders.begin() + UnitIDs[loop]);
	}

	for(short civ = 0; civ < dataset->Civs.size(); ++civ)
	{
		for(auto loop = selections; loop--> 0;)
		{
			dataset->Civs[civ].Units.erase(dataset->Civs[civ].Units.begin() + UnitIDs[loop]);
			dataset->Civs[civ].UnitPointers.erase(dataset->Civs[civ].UnitPointers.begin() + UnitIDs[loop]);
		}
		if(EnableIDFix)
		for(size_t loop = UnitIDs.front(); loop < dataset->Civs.front().Units.size(); ++loop) // ID Fix
		{
			dataset->Civs[civ].Units[loop].ID1 = loop;
			dataset->Civs[civ].Units[loop].ID2 = loop;
			if(GenieVersion >= genie::GV_AoK)
			dataset->Civs[civ].Units[loop].ID3 = loop;
		}
	}
	How2List = DEL;
	ListUnits(UnitCivID);
}

void AGE_Frame::OnUnitsCopy(wxCommandEvent &event)
{
	auto selections = Units_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion < genie::GV_AoK)
	{
		copies.Dat.AllCivs |= 0x08;
	}
	else
	{
		copies.Dat.AllCivs &= ~0x08;
		copies.UnitHeader.resize(selections);
		for(size_t loop = 0; loop < selections; ++loop)
		copies.UnitHeader[loop] = dataset->UnitHeaders[UnitIDs[loop]];
	}

	short CivCount = dataset->Civs.size();
	copies.Dat.UnitExists.resize(CivCount);
	if(Units_SpecialCopy_Civs->GetValue()) copies.Dat.AllCivs |= 0x01; else copies.Dat.AllCivs &= ~0x01;
	if(copies.Dat.AllCivs & 0x01)
	{
		copies.Dat.UnitCopies.resize(CivCount);
		for(short civ = 0; civ < CivCount; ++civ)
		{
			copies.Dat.UnitExists[civ].resize(selections);
			copies.Dat.UnitCopies[civ].resize(selections);
			for(size_t loop = 0; loop < selections; ++loop)
			{
				copies.Dat.UnitExists[civ][loop] = (bool)dataset->Civs[civ].UnitPointers[UnitIDs[loop]];
				copies.Dat.UnitCopies[civ][loop] = dataset->Civs[civ].Units[UnitIDs[loop]];
			}
		}
	}
	else
	{
		copies.Dat.UnitGraphics.resize(CivCount);
		for(short civ = 0; civ < CivCount; ++civ)
		{
			copies.Dat.UnitExists[civ].resize(selections);
			if(AutoCopy && !CopyGraphics)
			copies.Dat.UnitGraphics[civ].resize(selections);
			for(size_t loop = 0; loop < selections; ++loop)
			{
				copies.Dat.UnitExists[civ][loop] = (bool)dataset->Civs[civ].UnitPointers[UnitIDs[loop]];
				if(AutoCopy && !CopyGraphics)
				{// Let's copy graphics separately.
					// Collects only graphic data, not all data again.
					UnitsGraphicsCopy(copies.Dat.UnitGraphics[civ][loop], civ, UnitIDs[loop]);
				}
			}
		}
		copies.Dat.UnitCopies.front().resize(selections);
		for(size_t loop = 0; loop < selections; ++loop)
		copies.Dat.UnitCopies.front()[loop] = dataset->Civs[UnitCivID].Units[UnitIDs[loop]];
	}
	Units_ListV->SetFocus();
}

void AGE_Frame::OnAutoCopy(wxCommandEvent &event)
{
	if(event.GetId() == Units_AutoCopy->GetId())
	{
		AutoCopy = event.IsChecked();
		Units_CopyTo->Enable(!AutoCopy);
	}
	else if(event.GetId() == Units_CopyGraphics->GetId())
	{
		CopyGraphics = event.IsChecked();
	}
	else if(event.GetId() == Units_SelectAll->GetId())
	{
		for(size_t loop = 0; loop < dataset->Civs.size(); ++loop)
		Units_CivBoxes[loop]->SetValue(true);
	}
	else if(event.GetId() == Units_SelectClear->GetId())
	{
		for(size_t loop = 0; loop < dataset->Civs.size(); ++loop)
		Units_CivBoxes[loop]->SetValue(false);
	}
	else if(event.GetId() == Units_GraphicSet->GetId())
	{
		short Selection = Units_GraphicSet->GetSelection();
		for(size_t loop = 0; loop < dataset->Civs.size(); ++loop)
		{
			if((short)dataset->Civs[loop].IconSet == Selection)
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
	wxTimerEvent E;
	OnUnitsTimer(E);
}

void AGE_Frame::UnitsAutoCopy(wxCommandEvent &event)
{
	auto selections = Units_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	int edits = 0;
	GraphicCopies graphics;
	for(short civ = 0; civ < dataset->Civs.size(); ++civ)
	{
		if(Units_CivBoxes[civ]->IsChecked() && civ != UnitCivID)
		{
			for(size_t loop = 0; loop < selections; ++loop)
			{
				if(!CopyGraphics)// Let's copy graphics separately.
				UnitsGraphicsCopy(graphics, civ, UnitIDs[loop]);
				dataset->Civs[civ].Units[UnitIDs[loop]] = dataset->Civs[UnitCivID].Units[UnitIDs[loop]];
				if(!CopyGraphics)// Let's paste graphics separately.
				UnitsGraphicsPaste(graphics, civ, UnitIDs[loop]);
			}
			++edits;
		}
	}

	SetStatusText("Manual unit copy", 2);
	SetStatusText("Edits: "+lexical_cast<string>(popUp.unSaved)+" + "+lexical_cast<string>(edits), 3);
	popUp.unSaved += edits;
}

void AGE_Frame::UnitsGraphicsCopy(GraphicCopies &store, short civ, short unit)
{
	store.IconID = dataset->Civs[civ].Units[unit].IconID;// This probably shouldn't be here.
	store.StandingGraphic = dataset->Civs[civ].Units[unit].StandingGraphic;
	store.DyingGraphic = dataset->Civs[civ].Units[unit].DyingGraphic;
	store.DamageGraphics = dataset->Civs[civ].Units[unit].DamageGraphics;
	switch((short)dataset->Civs[civ].Units[unit].Type)
	{
		case 80:
		store.ConstructionGraphicID = dataset->Civs[civ].Units[unit].Building.ConstructionGraphicID;
		store.SnowGraphicID = dataset->Civs[civ].Units[unit].Building.SnowGraphicID;
		case 70:
		store.GarrisonGraphic = dataset->Civs[civ].Units[unit].Creatable.GarrisonGraphic;
		store.SpecialGraphic = dataset->Civs[civ].Units[unit].Creatable.SpecialGraphic;
		case 60:
		case 50:
		store.AttackGraphic = dataset->Civs[civ].Units[unit].Type50.AttackGraphic;
		case 40:
		case 30:
		store.WalkingGraphic = dataset->Civs[civ].Units[unit].DeadFish.WalkingGraphic;
	}
}

void AGE_Frame::OnUnitsSpecialCopy(wxCommandEvent &event)
{
	auto selections = Units_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(Units_SpecialCopy_Civs->GetValue()) copies.Dat.AllCivs |= 0x02; else copies.Dat.AllCivs &= ~0x02;
	if(copies.Dat.AllCivs & 0x02)
	{
		short CivCount = dataset->Civs.size();
		copies.Dat.UnitGraphics.resize(CivCount);
		for(short civ = 0; civ < CivCount; ++civ)
		{
			copies.Dat.UnitGraphics[civ].resize(selections);
			for(size_t loop = 0; loop < selections; ++loop)
			UnitsGraphicsCopy(copies.Dat.UnitGraphics[civ][loop], civ, UnitIDs[loop]);
		}
	}
	else
	{
		copies.Dat.UnitGraphics.front().resize(selections);
		for(size_t loop = 0; loop < selections; ++loop)
		UnitsGraphicsCopy(copies.Dat.UnitGraphics.front()[loop], UnitCivID, UnitIDs[loop]);
	}
	Units_ListV->SetFocus();
}

void AGE_Frame::OnUnitsPaste(wxCommandEvent &event)
{
	if(!Units_ListV->GetSelectedItemCount() || copies.Dat.UnitExists.size() == 0) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(UnitIDs.size(), copies.Dat.UnitExists.front().size()))
		{
			if(GenieVersion >= genie::GV_AoK)
			{
				for(size_t loop = 0; loop < copies.UnitHeader.size(); ++loop)
				{
					copies.UnitHeader[loop].setGameVersion(GenieVersion);
					dataset->UnitHeaders[UnitIDs[loop]] = copies.UnitHeader[loop];
				}
			}

			PasteUnits();
			for(size_t civ = 0; civ < dataset->Civs.size(); ++civ)
			{
				for(size_t loop = 0; loop < copies.Dat.UnitCopies.front().size(); ++loop)
				{
                    size_t paste_pos = UnitIDs[loop];
					dataset->Civs[civ].UnitPointers[paste_pos] = copies.Dat.UnitExists[civ][loop];
					if(EnableIDFix) // ID Fix
					{
						dataset->Civs[civ].Units[paste_pos].ID1 = paste_pos;
						dataset->Civs[civ].Units[paste_pos].ID2 = paste_pos;
						if(GenieVersion >= genie::GV_AoK)
						dataset->Civs[civ].Units[paste_pos].ID3 = paste_pos;
					}
				}
			}
		}
        else return;
	}
	else
	{
		if(GenieVersion >= genie::GV_AoK)
		{
			if(copies.UnitHeader.size()+UnitIDs.front() > dataset->UnitHeaders.size())
			dataset->UnitHeaders.resize(copies.UnitHeader.size()+UnitIDs.front());
			for(size_t loop = 0; loop < copies.UnitHeader.size(); ++loop)
			{
				copies.UnitHeader[loop].setGameVersion(GenieVersion);
				dataset->UnitHeaders[UnitIDs.front()+loop] = copies.UnitHeader[loop];
			}
		}

		if(copies.Dat.UnitCopies.front().size()+UnitIDs.front() > dataset->Civs.front().Units.size())
		for(size_t civ = 0; civ < dataset->Civs.size(); ++civ) // Resize if not enough room.
		{
			dataset->Civs[civ].Units.resize(copies.Dat.UnitCopies.front().size()+UnitIDs.front());
			dataset->Civs[civ].UnitPointers.resize(copies.Dat.UnitCopies.front().size()+UnitIDs.front());
		}
		PasteUnits();
		for(size_t civ = 0; civ < dataset->Civs.size(); ++civ)
		{
			for(size_t loop = 0; loop < copies.Dat.UnitCopies.front().size(); ++loop)
			{
                size_t paste_pos = UnitIDs.front() + loop;
				dataset->Civs[civ].UnitPointers[paste_pos] = copies.Dat.UnitExists[civ][loop];
				if(EnableIDFix) // ID Fix
				{
					dataset->Civs[civ].Units[paste_pos].ID1 = paste_pos;
					dataset->Civs[civ].Units[paste_pos].ID2 = paste_pos;
					if(GenieVersion >= genie::GV_AoK)
					dataset->Civs[civ].Units[paste_pos].ID3 = paste_pos;
				}
			}
		}
	}
	How2List = PASTE;
	ListUnits(UnitCivID);

	SetStatusText("Unit special paste", 2);
	SetStatusText("Edits: "+lexical_cast<string>(popUp.unSaved)+" + "+FormatInt(copies.Dat.UnitCopies.front().size()), 3);
	popUp.unSaved += copies.Dat.UnitCopies.front().size();
}

void AGE_Frame::OnUnitsPasteInsert(wxCommandEvent &event)
{
	if(!Units_ListV->GetSelectedItemCount() || copies.Dat.UnitExists.size() == 0) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion >= genie::GV_AoK)
	{
		genie::UnitHeader Temp1;
		dataset->UnitHeaders.insert(dataset->UnitHeaders.begin() + UnitIDs.front(), copies.UnitHeader.size(), Temp1);
		for(size_t loop = 0; loop < copies.UnitHeader.size(); ++loop)
		{
			copies.UnitHeader[loop].setGameVersion(GenieVersion);
			dataset->UnitHeaders[UnitIDs.front()+loop] = copies.UnitHeader[loop];
		}
	}

	genie::Unit Temp2;
	for(short civ = 0; civ < dataset->Civs.size(); ++civ)
	{
		dataset->Civs[civ].Units.insert(dataset->Civs[civ].Units.begin() + UnitIDs.front(), copies.Dat.UnitCopies.front().size(), Temp2);
		dataset->Civs[civ].UnitPointers.insert(dataset->Civs[civ].UnitPointers.begin() + UnitIDs.front(), copies.Dat.UnitCopies.front().size(), 0);
	}
	PasteUnits();
	for(short civ = 0; civ < dataset->Civs.size(); ++civ)
	{
		for(size_t loop = 0; loop < copies.Dat.UnitCopies.front().size(); ++loop)
		{
			dataset->Civs[civ].UnitPointers[UnitIDs.front()+loop] = (int32_t)copies.Dat.UnitExists[civ][loop];
		}
		if(EnableIDFix) // ID Fix
		for(size_t loop = UnitIDs.front();loop < dataset->Civs.front().Units.size(); ++loop)
		{
			dataset->Civs[civ].Units[loop].ID1 = loop;
			dataset->Civs[civ].Units[loop].ID2 = loop;
			if(GenieVersion >= genie::GV_AoK)
			dataset->Civs[civ].Units[loop].ID3 = loop;
		}
	}
	How2List = INSPASTE;
	ListUnits(UnitCivID);
}

short AGE_Frame::CorrectID(bool OneOnOne, size_t loop)
{
	return OneOnOne ? UnitIDs[loop] : UnitIDs.front() + loop;
}

void AGE_Frame::PasteUnits(bool OneOnOne)
{
	// The civ amount of copy data must be set on copying!
	// Otherwise having more than one window open with different civ count creates problems!
	short CivCount = dataset->Civs.size();
	short FillingCiv = (copies.Dat.UnitExists.size() > 1) ? 1 : 0;
	copies.Dat.UnitExists.resize(CivCount, copies.Dat.UnitExists[FillingCiv]);
	if(copies.Dat.AllCivs & 0x01) // Paste from all civs to all civs.
	{
		copies.Dat.UnitCopies.resize(CivCount, copies.Dat.UnitCopies[FillingCiv]);
		for(short civ = 0; civ < CivCount; ++civ)
		{
			for(size_t loop = 0; loop < copies.Dat.UnitCopies.front().size(); ++loop) // selections
			{
				copies.Dat.UnitCopies[civ][loop].setGameVersion(GenieVersion);
				dataset->Civs[civ].Units[CorrectID(OneOnOne, loop)] = copies.Dat.UnitCopies[civ][loop];
			}
		}
	}
	else
	{
		if(AutoCopy) // Paste from one civ to selected civs.
		{
			copies.Dat.UnitGraphics.resize(CivCount, copies.Dat.UnitGraphics[FillingCiv]);
			for(short civ = 0; civ < CivCount; ++civ)
			{
				if(Units_CivBoxes[civ]->IsChecked())
				{
					for(size_t loop = 0; loop < copies.Dat.UnitCopies.front().size(); ++loop)
					{
						copies.Dat.UnitCopies.front()[loop].setGameVersion(GenieVersion);
						dataset->Civs[civ].Units[CorrectID(OneOnOne, loop)] = copies.Dat.UnitCopies.front()[loop];
						if(!CopyGraphics)
						{// Let's paste graphics separately.
							UnitsGraphicsPaste(copies.Dat.UnitGraphics[civ][loop], civ, CorrectID(OneOnOne, loop));
						}
					}
				}
			}
		}
		else // Paste from one civ to another civ.
		{
			for(size_t loop = 0; loop < copies.Dat.UnitCopies.front().size(); ++loop)
			{
				copies.Dat.UnitCopies.front()[loop].setGameVersion(GenieVersion);
				dataset->Civs[UnitCivID].Units[CorrectID(OneOnOne, loop)] = copies.Dat.UnitCopies.front()[loop];
			}
		}
	}
	if(copies.Dat.AllCivs & 0x08) // Paste from AoE to AoK+
	{
		// Paste commands properly
		if(GenieVersion >= genie::GV_AoK)
		{
			if(copies.Dat.AllCivs & 0x01)
			{
				for(size_t loop = 0; loop < copies.Dat.UnitCopies.front().size(); ++loop)
				{
					for(short civ = 0; civ < copies.Dat.UnitCopies.size(); ++civ)
					{
						if(copies.Dat.UnitExists[civ][loop] != 0)
						{
							dataset->UnitHeaders[CorrectID(OneOnOne, loop)].Exists = 1;
							dataset->UnitHeaders[CorrectID(OneOnOne, loop)].Commands = copies.Dat.UnitCopies[civ][loop].Bird.Commands;
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
		for(size_t loop = 0; loop < copies.UnitHeader.size(); ++loop)
		{
			for(short civ = 0; civ < dataset->Civs.size(); ++civ)
			{
				if(dataset->Civs[civ].UnitPointers[CorrectID(OneOnOne, loop)] != 0)
				dataset->Civs[civ].Units[CorrectID(OneOnOne, loop)].Bird.Commands = copies.UnitHeader[loop].Commands;
			}
		}
	}
}

void AGE_Frame::UnitsGraphicsPaste(GraphicCopies &store, short civ, short unit)
{
	dataset->Civs[civ].Units[unit].IconID = store.IconID;
	dataset->Civs[civ].Units[unit].StandingGraphic = store.StandingGraphic;
	dataset->Civs[civ].Units[unit].DyingGraphic = store.DyingGraphic;
	dataset->Civs[civ].Units[unit].DamageGraphics = store.DamageGraphics;
	switch((short)dataset->Civs[civ].Units[unit].Type)
	{
		case 80:
		dataset->Civs[civ].Units[unit].Building.ConstructionGraphicID = store.ConstructionGraphicID;
		dataset->Civs[civ].Units[unit].Building.SnowGraphicID = store.SnowGraphicID;
		case 70:
		dataset->Civs[civ].Units[unit].Creatable.GarrisonGraphic = store.GarrisonGraphic;
		dataset->Civs[civ].Units[unit].Creatable.SpecialGraphic = store.SpecialGraphic;
		case 60:
		case 50:
		dataset->Civs[civ].Units[unit].Type50.AttackGraphic = store.AttackGraphic;
		case 40:
		case 30:
		dataset->Civs[civ].Units[unit].DeadFish.WalkingGraphic = store.WalkingGraphic;
	}
}

void AGE_Frame::OnUnitsSpecialPaste(wxCommandEvent &event)
{
	short CopyCount = copies.Dat.UnitGraphics.front().size();
	if(!Units_ListV->GetSelectedItemCount() || CopyCount == 0) return;

	wxBusyCursor WaitCursor;
	if(Paste11)
	{
		if(Paste11Check(UnitIDs.size(), CopyCount))
		{
			if(copies.Dat.AllCivs & 0x02)
			{
				short CivCount = dataset->Civs.size();
				short FillingCiv = (copies.Dat.UnitGraphics.size() > 1) ? 1 : 0;
				copies.Dat.UnitGraphics.resize(CivCount, copies.Dat.UnitGraphics[FillingCiv]);
				for(short civ = 0; civ < CivCount; ++civ)
				{
					for(size_t loop = 0; loop < CopyCount; ++loop)
					UnitsGraphicsPaste(copies.Dat.UnitGraphics[civ][loop], civ, UnitIDs[loop]);
				}
			}
			else
			{
				for(size_t loop = 0; loop < CopyCount; ++loop)
				UnitsGraphicsPaste(copies.Dat.UnitGraphics.front()[loop], UnitCivID, UnitIDs[loop]);
			}
		}
	}
	else
	{
		if(copies.Dat.UnitGraphics.front().size()+UnitIDs.front() > dataset->Civs.front().Units.size())
		CopyCount -= copies.Dat.UnitGraphics.front().size()+UnitIDs.front() - dataset->Civs.front().Units.size();
		if(copies.Dat.AllCivs & 0x02)
		{
			short CivCount = dataset->Civs.size();
			short FillingCiv = (copies.Dat.UnitGraphics.size() > 1) ? 1 : 0;
			copies.Dat.UnitGraphics.resize(CivCount, copies.Dat.UnitGraphics[FillingCiv]);
			for(short civ = 0; civ < CivCount; ++civ)
			{
				for(size_t loop = 0; loop < CopyCount; ++loop)
				UnitsGraphicsPaste(copies.Dat.UnitGraphics[civ][loop], civ, UnitIDs.front()+loop);
			}
		}
		else
		{
			for(size_t loop = 0; loop < CopyCount; ++loop)
			UnitsGraphicsPaste(copies.Dat.UnitGraphics.front()[loop], UnitCivID, UnitIDs.front()+loop);
		}
	}
	wxTimerEvent E;
	OnUnitsTimer(E);
	Units_ListV->SetFocus();
}

void AGE_Frame::OnUnitsEnable(wxCommandEvent &event)
{
	auto selections = Units_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	for(short sel = 0; sel < selections; ++sel)
	{
		// Find the correct sizes for subvectors.
		short UnitType = 10, DamageGraphics = 0, Attacks = 0, Armors = 0, Commands = 0;
		for(short civ = 0; civ < dataset->Civs.size(); ++civ)
		{
			if(dataset->Civs[civ].UnitPointers[UnitIDs[sel]] != 0)
			{
				UnitType = dataset->Civs[civ].Units[UnitIDs[sel]].Type;
				DamageGraphics = dataset->Civs[civ].Units[UnitIDs[sel]].DamageGraphics.size();
				Attacks = dataset->Civs[civ].Units[UnitIDs[sel]].Type50.Attacks.size();
				Armors = dataset->Civs[civ].Units[UnitIDs[sel]].Type50.Armours.size();
				if(GenieVersion < genie::GV_AoK)
				Commands = dataset->Civs[civ].Units[UnitIDs[sel]].Bird.Commands.size();
				break;
			}
		}
		// All subvectors need to be resized!
		if(Units_SpecialCopy_Civs->GetValue())
		for(short civ = 0; civ < dataset->Civs.size(); ++civ)
		{
			if(dataset->Civs[civ].UnitPointers[UnitIDs[sel]] == 0)
			{
				dataset->Civs[civ].UnitPointers[UnitIDs[sel]] = 1;
				dataset->Civs[civ].Units[UnitIDs[sel]].Type = UnitType;
				dataset->Civs[civ].Units[UnitIDs[sel]].DamageGraphics.resize(DamageGraphics);
				dataset->Civs[civ].Units[UnitIDs[sel]].Type50.Attacks.resize(Attacks);
				dataset->Civs[civ].Units[UnitIDs[sel]].Type50.Armours.resize(Armors);
				dataset->Civs[civ].Units[UnitIDs[sel]].Bird.Commands.resize(Commands);
				dataset->Civs[civ].Units[UnitIDs[sel]].ID1 = UnitIDs[sel]; // ID Fix
				dataset->Civs[civ].Units[UnitIDs[sel]].ID2 = UnitIDs[sel];
				if(GenieVersion >= genie::GV_AoKA)
				dataset->Civs[civ].Units[UnitIDs[sel]].ID3 = UnitIDs[sel];
			}
		}
		else
		{
			if(dataset->Civs[UnitCivID].UnitPointers[UnitIDs[sel]] == 0)
			{
				dataset->Civs[UnitCivID].UnitPointers[UnitIDs[sel]] = 1;
				dataset->Civs[UnitCivID].Units[UnitIDs[sel]].Type = UnitType;
				dataset->Civs[UnitCivID].Units[UnitIDs[sel]].DamageGraphics.resize(DamageGraphics);
				dataset->Civs[UnitCivID].Units[UnitIDs[sel]].Type50.Attacks.resize(Attacks);
				dataset->Civs[UnitCivID].Units[UnitIDs[sel]].Type50.Armours.resize(Armors);
				dataset->Civs[UnitCivID].Units[UnitIDs[sel]].Bird.Commands.resize(Commands);
				dataset->Civs[UnitCivID].Units[UnitIDs[sel]].ID1 = UnitIDs[sel]; // ID Fix
				dataset->Civs[UnitCivID].Units[UnitIDs[sel]].ID2 = UnitIDs[sel];
				if(GenieVersion >= genie::GV_AoKA)
				dataset->Civs[UnitCivID].Units[UnitIDs[sel]].ID3 = UnitIDs[sel];
			}
		}
	}
	How2List = ENABLE;
	ListUnits(UnitCivID);
}

void AGE_Frame::OnUnitsDisable(wxCommandEvent &event)
{
	auto selections = Units_ListV->GetSelectedItemCount();
	if(selections < 1) return;

	wxBusyCursor WaitCursor;
	for(short sel = 0; sel < selections; ++sel)
	{
		if(Units_SpecialCopy_Civs->GetValue())
		for(short civ = 0; civ < dataset->Civs.size(); ++civ)
		dataset->Civs[civ].UnitPointers[UnitIDs[sel]] = 0;
		else
		dataset->Civs[UnitCivID].UnitPointers[UnitIDs[sel]] = 0;
	}
	How2List = ENABLE;
	ListUnits(UnitCivID);
}

//	SubVectors

string AGE_Frame::GetUnitDamageGraphicName(int index)
{
	return lexical_cast<string>((short)dataset->Civs[UnitCivID].Units[UnitIDs.front()].DamageGraphics[index].DamagePercent)
	+" % - ID: "+lexical_cast<string>(dataset->Civs[UnitCivID].Units[UnitIDs.front()].DamageGraphics[index].GraphicID)+" ";
}

void AGE_Frame::OnUnitDamageGraphicsSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListUnitDamageGraphics();
}

void AGE_Frame::ListUnitDamageGraphics()
{
	InitSearch(Units_DamageGraphics_Search->GetValue().MakeLower(), Units_DamageGraphics_Search_R->GetValue().MakeLower());

    Units_DamageGraphics_ListV->names.clear();
    Units_DamageGraphics_ListV->indexes.clear();

	if(Units_ListV->GetSelectedItemCount()
	&& dataset->Civs[UnitCivID].UnitPointers[UnitIDs.front()] != 0)
	{
		Units_DamageGraphics_Add->Enable(true);
		for(size_t loop = 0; loop < dataset->Civs[UnitCivID].Units[UnitIDs.front()].DamageGraphics.size(); ++loop)
		{
			wxString Name = " "+FormatInt(loop)+" - "+GetUnitDamageGraphicName(loop);
			if(SearchMatches(Name.Lower()))
			{
                Units_DamageGraphics_ListV->names.Add(Name);
                Units_DamageGraphics_ListV->indexes.push_back(loop);
			}
		}
	}
	else
	{
		Units_DamageGraphics_Add->Enable(false);
	}
	virtualListing(Units_DamageGraphics_ListV);

	wxTimerEvent E;
	OnUnitDamageGraphicsTimer(E);
}

void AGE_Frame::OnUnitDamageGraphicsSelect(wxCommandEvent &event)
{
    if(!dmgGraphicTimer.IsRunning())
        dmgGraphicTimer.Start(150);
}

void AGE_Frame::OnUnitDamageGraphicsTimer(wxTimerEvent &event)
{
    dmgGraphicTimer.Stop();
	auto selections = Units_DamageGraphics_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    for(auto &box: uiGroupUnitDmgGraphic) box->clear();
	if(selections > 0)
	{
        getSelectedItems(selections, Units_DamageGraphics_ListV, DamageGraphicIDs);
		// This and attacks/armors/commands need a lot of thinking.

		bool showWarning = false;
		wxString warning = "Damage graphic count of civs\n";
		genie::unit::DamageGraphic * DamageGraphicPointer;
		for(auto sel = selections; sel--> 0;)
		{
			for(short vecCiv = (CopyGraphics) ? SelectedCivs.size() : 1; vecCiv--> 0;)
			{
				if(sel == 0 && dataset->Civs[SelectedCivs[vecCiv]].Units[UnitIDs.front()].DamageGraphics.size() != dataset->Civs[UnitCivID].Units[UnitIDs.front()].DamageGraphics.size())
				{
					warning.Append(lexical_cast<string>(SelectedCivs[vecCiv])+" ");
					showWarning = true;
				}
				DamageGraphicPointer = &dataset->Civs[SelectedCivs[vecCiv]].Units[UnitIDs.front()].DamageGraphics[DamageGraphicIDs[sel]];

				DamageGraphics_GraphicID->prepend(&DamageGraphicPointer->GraphicID);
				DamageGraphics_DamagePercent->prepend(&DamageGraphicPointer->DamagePercent);
				DamageGraphics_ApplyMode->prepend(&DamageGraphicPointer->OldApplyMode);
				DamageGraphics_Unknown2->prepend(&DamageGraphicPointer->ApplyMode);
			}
		}
		if(showWarning)
		{
			warning.Append("\ndiffers from civ "+lexical_cast<string>(UnitCivID));
			wxMessageBox(warning);
		}
	}
	for(auto &box: uiGroupUnitDmgGraphic) box->update();
    if(slp_dmg_unit->GetValue())
    {
        wxCommandEvent E;
        OnChooseGraphic(E);
    }
}

void AGE_Frame::OnUnitDamageGraphicsAdd(wxCommandEvent &event)
{
    if(!Units_ListV->GetSelectedItemCount()) return;

	wxBusyCursor WaitCursor;
	genie::unit::DamageGraphic Temp;
	Temp.setGameVersion(GenieVersion);
	for(size_t loop = 0; loop < dataset->Civs.size(); ++loop)
	{
		if(dataset->Civs[loop].UnitPointers[UnitIDs.front()] != 0)
		dataset->Civs[loop].Units[UnitIDs.front()].DamageGraphics.push_back(Temp);
	}
	How2List = ADD;
	ListUnitDamageGraphics();
}

void AGE_Frame::OnUnitDamageGraphicsInsert(wxCommandEvent &event)
{
    if(!Units_DamageGraphics_ListV->GetSelectedItemCount()) return;

	wxBusyCursor WaitCursor;
	genie::unit::DamageGraphic Temp;
	Temp.setGameVersion(GenieVersion);
	for(size_t loop = 0; loop < dataset->Civs.size(); ++loop)
	{
		if(dataset->Civs[loop].UnitPointers[UnitIDs.front()] != 0)
		dataset->Civs[loop].Units[UnitIDs.front()].DamageGraphics.insert(dataset->Civs[loop].Units[UnitIDs.front()].DamageGraphics.begin() + DamageGraphicIDs.front(), Temp);
	}
	How2List = INSNEW;
	ListUnitDamageGraphics();
}

void AGE_Frame::OnUnitDamageGraphicsDelete(wxCommandEvent &event)
{
    auto selections = Units_DamageGraphics_ListV->GetSelectedItemCount();
    if(selections < 1) return;

	wxBusyCursor WaitCursor;
	for(short civ = 0; civ < dataset->Civs.size(); ++civ)
	{
		if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] != 0)
		if(dataset->Civs[civ].Units[UnitIDs.front()].DamageGraphics.size())
		for(auto loop = selections; loop--> 0;)
		dataset->Civs[civ].Units[UnitIDs.front()].DamageGraphics.erase(dataset->Civs[civ].Units[UnitIDs.front()].DamageGraphics.begin() + DamageGraphicIDs[loop]);
	}
	How2List = DEL;
	ListUnitDamageGraphics();
}

void AGE_Frame::OnUnitDamageGraphicsCopy(wxCommandEvent &event)
{
    if(!Units_DamageGraphics_ListV->GetSelectedItemCount()) return;

	wxBusyCursor WaitCursor;
	if(Units_SpecialCopy_Civs->GetValue()) copies.Dat.AllCivs |= 0x10; else copies.Dat.AllCivs &= ~0x10;
	if(copies.Dat.AllCivs & 0x10)
	{
		short CivCount = dataset->Civs.size();
		copies.Dat.UnitDamageGraphicExists.resize(CivCount);
		copies.Dat.UnitDamageGraphics.resize(CivCount);
		for(short civ = 0, copy = 0; civ < dataset->Civs.size(); ++civ)
		{
			if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] == 0)
			{
				// Graphic set info not usefull.
				copies.Dat.UnitDamageGraphicExists[civ] = 255;
				CivCount--;
			}
			else
			{
				// Save info of graphic set to intelligently fill possible gaps when pasting.
				copies.Dat.UnitDamageGraphicExists[civ] = 256 + dataset->Civs[civ].IconSet;
				// Only copy damage graphics from civs which have this unit enabled.
				CopyFromList(dataset->Civs[civ].Units[UnitIDs.front()].DamageGraphics, DamageGraphicIDs, copies.Dat.UnitDamageGraphics[copy]); copy++;
			}
		}
		copies.Dat.UnitDamageGraphics.resize(CivCount);
	}
	else
	{
		CopyFromList(dataset->Civs[UnitCivID].Units[UnitIDs.front()].DamageGraphics, DamageGraphicIDs, copies.Dat.UnitDamageGraphics.front());
	}
	Units_DamageGraphics_ListV->SetFocus();
}

void AGE_Frame::OnUnitDamageGraphicsPaste(wxCommandEvent &event)
{
    if(!Units_DamageGraphics_ListV->GetSelectedItemCount()) return;

    wxBusyCursor WaitCursor;
    if(copies.Dat.AllCivs & 0x10)
    {
        for(size_t civ = 0, copy = 0; civ < dataset->Civs.size(); ++civ)
        {
            if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] == 0)
            {
                // Consume copies.
                if(copies.Dat.UnitDamageGraphicExists[civ] > 255) ++copy; continue;
            }
            // If the target unit exists then choose from following.
            if(copies.Dat.UnitDamageGraphicExists[civ] > 255 && copy < copies.Dat.UnitDamageGraphics.size())
            {
                PasteToList(dataset->Civs[civ].Units[UnitIDs.front()].DamageGraphics, DamageGraphicIDs, copies.Dat.UnitDamageGraphics[copy]); ++copy;
            }
            else
            {
                PasteToList(dataset->Civs[civ].Units[UnitIDs.front()].DamageGraphics, DamageGraphicIDs, copies.Dat.UnitDamageGraphics.front());
            }
        }
    }
    else
    {
        PasteToList(dataset->Civs[UnitCivID].Units[UnitIDs.front()].DamageGraphics, DamageGraphicIDs, copies.Dat.UnitDamageGraphics.front());
    }
    ListUnitDamageGraphics();
}

void AGE_Frame::OnUnitDamageGraphicsPasteInsert(wxCommandEvent &event)
{
    if(!Units_DamageGraphics_ListV->GetSelectedItemCount()) return;

	wxBusyCursor WaitCursor;
	genie::unit::DamageGraphic Temp;
	if(copies.Dat.AllCivs & 0x10)
	{
		for(short civ = 0, copy = 0; civ < dataset->Civs.size(); ++civ)
		{
			if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] == 0)
			{
				// Consume copies.
				if(copies.Dat.UnitDamageGraphicExists[civ] > 255) copy++; continue;
			}
			// If the target unit exists then choose from following.
			if(copies.Dat.UnitDamageGraphicExists[civ] > 255 && copy < copies.Dat.UnitDamageGraphics.size())
			{
				PasteInsertToList(dataset->Civs[civ].Units[UnitIDs.front()].DamageGraphics, DamageGraphicIDs.front(), copies.Dat.UnitDamageGraphics[copy]); copy++;
			}
			else
			{
				PasteInsertToList(dataset->Civs[civ].Units[UnitIDs.front()].DamageGraphics, DamageGraphicIDs.front(), copies.Dat.UnitDamageGraphics.front());
			}
		}
	}
	else
	{
		PasteInsertToList(dataset->Civs[UnitCivID].Units[UnitIDs.front()].DamageGraphics, DamageGraphicIDs.front(), copies.Dat.UnitDamageGraphics.front());
	}
	ListUnitDamageGraphics();
}

void AGE_Frame::OnUnitDamageGraphicsCopyToUnits(wxCommandEvent &event)
{
	for(short civ = 0; civ < dataset->Civs.size(); ++civ)
	for(size_t loop=1; loop < UnitIDs.size(); ++loop)
	{
		dataset->Civs[civ].Units[UnitIDs[loop]].DamageGraphics = dataset->Civs[civ].Units[UnitIDs.front()].DamageGraphics;
	}
}

string AGE_Frame::GetUnitAttackName(int index)
{
	return "Amount: "+lexical_cast<string>(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type50.Attacks[index].Amount)
	+" - Class "+lexical_cast<string>(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type50.Attacks[index].Class)+" ";
}

void AGE_Frame::OnUnitAttacksSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListUnitAttacks();
}

void AGE_Frame::ListUnitAttacks()
{
	InitSearch(Units_Attacks_Search->GetValue().MakeLower(), Units_Attacks_Search_R->GetValue().MakeLower());

    Units_Attacks_ListV->names.clear();
    Units_Attacks_ListV->indexes.clear();

	if(Units_ListV->GetSelectedItemCount()
	&& dataset->Civs[UnitCivID].UnitPointers[UnitIDs.front()] != 0
	&& dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type >= 50
	&& dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type <= 80)
	{
		Units_Attacks_Add->Enable(true);
		for(size_t loop = 0; loop < dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type50.Attacks.size(); ++loop)
		{
			wxString Name = " "+FormatInt(loop)+" - "+GetUnitAttackName(loop);
			if(SearchMatches(Name.Lower()))
			{
                Units_Attacks_ListV->names.Add(Name);
                Units_Attacks_ListV->indexes.push_back(loop);
			}
		}
	}
	else
	{
		Units_Attacks_Add->Enable(false);
	}
	virtualListing(Units_Attacks_ListV);

	wxTimerEvent E;
	OnUnitAttacksTimer(E);
}

void AGE_Frame::OnUnitAttacksSelect(wxCommandEvent &event)
{
    if(!attackTimer.IsRunning())
        attackTimer.Start(150);
}

void AGE_Frame::OnUnitAttacksTimer(wxTimerEvent &event)
{
    attackTimer.Stop();
	auto selections = Units_Attacks_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    Attacks_Class->clear();
    Attacks_Amount->clear();
	if(selections > 0)
	{
        getSelectedItems(selections, Units_Attacks_ListV, AttackIDs);

		bool showWarning = false;
		wxString warning = "Attack count of civs\n";
		genie::unit::AttackOrArmor * AttackPointer;
		for(auto sel = selections; sel--> 0;)
		{
			for(short vecCiv = SelectedCivs.size(); vecCiv--> 0;)
			{
				if(sel == 0 && dataset->Civs[SelectedCivs[vecCiv]].Units[UnitIDs.front()].Type50.Attacks.size() != dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type50.Attacks.size())
				{
					warning.Append(lexical_cast<string>(SelectedCivs[vecCiv])+" ");
					showWarning = true;
				}
				AttackPointer = &dataset->Civs[SelectedCivs[vecCiv]].Units[UnitIDs.front()].Type50.Attacks[AttackIDs[sel]];

				Attacks_Class->prepend(&AttackPointer->Class);
				Attacks_Amount->prepend(&AttackPointer->Amount);
			}
		}
		if(showWarning)
		{
			warning.Append("\ndiffers from civ "+lexical_cast<string>(UnitCivID));
			wxMessageBox(warning);
		}
	}
	Attacks_Class->update();
	Attacks_Amount->update();
}

void AGE_Frame::OnUnitAttacksAdd(wxCommandEvent &event)
{
    if(!Units_ListV->GetSelectedItemCount()) return;

	wxBusyCursor WaitCursor;
	genie::unit::AttackOrArmor Temp;
	Temp.setGameVersion(GenieVersion);
	for(size_t loop = 0; loop < dataset->Civs.size(); ++loop)
	{
		if(dataset->Civs[loop].UnitPointers[UnitIDs.front()] != 0)
		dataset->Civs[loop].Units[UnitIDs.front()].Type50.Attacks.push_back(Temp);
	}
	How2List = ADD;
	ListUnitAttacks();
}

void AGE_Frame::OnUnitAttacksInsert(wxCommandEvent &event)
{
    if(!Units_Attacks_ListV->GetSelectedItemCount()) return;

	wxBusyCursor WaitCursor;
	genie::unit::AttackOrArmor Temp;
	Temp.setGameVersion(GenieVersion);
	for(size_t loop = 0; loop < dataset->Civs.size(); ++loop)
	{
		if(dataset->Civs[loop].UnitPointers[UnitIDs.front()] != 0)
		dataset->Civs[loop].Units[UnitIDs.front()].Type50.Attacks.insert(dataset->Civs[loop].Units[UnitIDs.front()].Type50.Attacks.begin() + AttackIDs.front(), Temp);
	}
	How2List = INSNEW;
	ListUnitAttacks();
}

void AGE_Frame::OnUnitAttacksDelete(wxCommandEvent &event)
{
    auto selections = Units_Attacks_ListV->GetSelectedItemCount();
    if(selections < 1) return;

	wxBusyCursor WaitCursor;
	for(short civ = 0; civ < dataset->Civs.size(); ++civ)
	{
		if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] != 0)
		if(dataset->Civs[civ].Units[UnitIDs.front()].Type50.Attacks.size())
		for(auto loop = selections; loop--> 0;)
		dataset->Civs[civ].Units[UnitIDs.front()].Type50.Attacks.erase(dataset->Civs[civ].Units[UnitIDs.front()].Type50.Attacks.begin() + AttackIDs[loop]);
	}
	How2List = DEL;
	ListUnitAttacks();
}

void AGE_Frame::OnUnitAttacksCopy(wxCommandEvent &event)
{
    if(!Units_Attacks_ListV->GetSelectedItemCount()) return;

	wxBusyCursor WaitCursor;
	if(Units_SpecialCopy_Civs->GetValue()) copies.Dat.AllCivs |= 0x20; else copies.Dat.AllCivs &= ~0x20;
	if(copies.Dat.AllCivs & 0x20)
	{
		short CivCount = dataset->Civs.size();
		copies.Dat.UnitAttackExists.resize(CivCount);
		copies.Dat.UnitAttacks.resize(CivCount);
		for(short civ = 0, copy = 0; civ < dataset->Civs.size(); ++civ)
		{
			if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] == 0)
			{
				// Graphic set info not usefull.
				copies.Dat.UnitAttackExists[civ] = 255;
				CivCount--;
			}
			else
			{
				// Save info of graphic set to intelligently fill possible gaps when pasting.
				copies.Dat.UnitAttackExists[civ] = 256 + dataset->Civs[civ].IconSet;
				// Only copy attacks from civs which have this unit enabled.
				CopyFromList(dataset->Civs[civ].Units[UnitIDs.front()].Type50.Attacks, AttackIDs, copies.Dat.UnitAttacks[copy]); copy++;
			}
		}
		copies.Dat.UnitAttacks.resize(CivCount);
	}
	else
	{
		CopyFromList(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type50.Attacks, AttackIDs, copies.Dat.UnitAttacks.front());
	}
	Units_Attacks_ListV->SetFocus();
}

void AGE_Frame::OnUnitAttacksPaste(wxCommandEvent &event)
{
    if(!Units_Attacks_ListV->GetSelectedItemCount()) return;

    wxBusyCursor WaitCursor;
    if(copies.Dat.AllCivs & 0x20)
    {
        for(size_t civ = 0, copy = 0; civ < dataset->Civs.size(); ++civ)
        {
            if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] == 0)
            {
                // Consume copies.
                if(copies.Dat.UnitAttackExists[civ] > 255) ++copy; continue;
            }
            // If the target unit exists then choose from following.
            if(copies.Dat.UnitAttackExists[civ] > 255 && copy < copies.Dat.UnitAttacks.size())
            {
                PasteToList(dataset->Civs[civ].Units[UnitIDs.front()].Type50.Attacks, AttackIDs, copies.Dat.UnitAttacks[copy]); ++copy;
            }
            else
            {
                PasteToList(dataset->Civs[civ].Units[UnitIDs.front()].Type50.Attacks, AttackIDs, copies.Dat.UnitAttacks.front());
            }
        }
    }
    else
    {
        PasteToList(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type50.Attacks, AttackIDs, copies.Dat.UnitAttacks.front());
    }
    ListUnitAttacks();
}

void AGE_Frame::OnUnitAttacksPasteInsert(wxCommandEvent &event)
{
    if(!Units_Attacks_ListV->GetSelectedItemCount()) return;

	wxBusyCursor WaitCursor;
	if(copies.Dat.AllCivs & 0x20)
	{
		for(short civ = 0, copy = 0; civ < dataset->Civs.size(); ++civ)
		{
			if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] == 0)
			{
				// Consume copies.
				if(copies.Dat.UnitAttackExists[civ] > 255) copy++; continue;
			}
			// If the target unit exists then choose from following.
			if(copies.Dat.UnitAttackExists[civ] > 255 && copy < copies.Dat.UnitAttacks.size())
			{
				PasteInsertToList(dataset->Civs[civ].Units[UnitIDs.front()].Type50.Attacks, AttackIDs.front(), copies.Dat.UnitAttacks[copy]); copy++;
			}
			else
			{
				PasteInsertToList(dataset->Civs[civ].Units[UnitIDs.front()].Type50.Attacks, AttackIDs.front(), copies.Dat.UnitAttacks.front());
			}
		}
	}
	else
	{
		PasteInsertToList(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type50.Attacks, AttackIDs.front(), copies.Dat.UnitAttacks.front());
	}
	ListUnitAttacks();
}

void AGE_Frame::OnUnitAttacksCopyToUnits(wxCommandEvent &event)
{
	for(short civ = 0; civ < dataset->Civs.size(); ++civ)
	for(size_t loop=1; loop < UnitIDs.size(); ++loop)
	{
		dataset->Civs[civ].Units[UnitIDs[loop]].Type50.Attacks = dataset->Civs[civ].Units[UnitIDs.front()].Type50.Attacks;
	}
}

string AGE_Frame::GetUnitArmorName(int index)
{
	return "Amount: "+lexical_cast<string>(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type50.Armours[index].Amount)
	+" - Class "+lexical_cast<string>(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type50.Armours[index].Class)+" ";
}

void AGE_Frame::OnUnitArmorsSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListUnitArmors();
}

void AGE_Frame::ListUnitArmors()
{
	InitSearch(Units_Armors_Search->GetValue().MakeLower(), Units_Armors_Search_R->GetValue().MakeLower());

	Units_Armors_ListV->names.clear();
    Units_Armors_ListV->indexes.clear();

	if(Units_ListV->GetSelectedItemCount()
	&& dataset->Civs[UnitCivID].UnitPointers[UnitIDs.front()] != 0
	&& dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type >= 50
	&& dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type <= 80)
	{
		Units_Armors_Add->Enable(true);
		for(size_t loop = 0; loop < dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type50.Armours.size(); ++loop)
		{
			wxString Name = " "+FormatInt(loop)+" - "+GetUnitArmorName(loop);
			if(SearchMatches(Name.Lower()))
			{
				Units_Armors_ListV->names.Add(Name);
                Units_Armors_ListV->indexes.push_back(loop);
			}
		}
	}
	else
	{
		Units_Armors_Add->Enable(false);
	}
	virtualListing(Units_Armors_ListV);

	wxTimerEvent E;
	OnUnitArmorsTimer(E);
}

void AGE_Frame::OnUnitArmorsSelect(wxCommandEvent &event)
{
    if(!armorTimer.IsRunning())
        armorTimer.Start(150);
}

void AGE_Frame::OnUnitArmorsTimer(wxTimerEvent &event)
{
    armorTimer.Stop();
	auto selections = Units_Armors_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    Armors_Class->clear();
    Armors_Amount->clear();
	if(selections > 0)
	{
        getSelectedItems(selections, Units_Armors_ListV, ArmorIDs);

		bool showWarning = false;
		wxString warning = "Armor count of civs\n";
		genie::unit::AttackOrArmor * ArmorPointer;
		for(auto sel = selections; sel--> 0;)
		{
			for(short vecCiv = SelectedCivs.size(); vecCiv--> 0;)
			{
				if(sel == 0 && dataset->Civs[SelectedCivs[vecCiv]].Units[UnitIDs.front()].Type50.Armours.size() != dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type50.Armours.size())
				{
					warning.Append(lexical_cast<string>(SelectedCivs[vecCiv])+" ");
					showWarning = true;
				}
				ArmorPointer = &dataset->Civs[SelectedCivs[vecCiv]].Units[UnitIDs.front()].Type50.Armours[ArmorIDs[sel]];

				Armors_Class->prepend(&ArmorPointer->Class);
				Armors_Amount->prepend(&ArmorPointer->Amount);
			}
		}
		if(showWarning)
		{
			warning.Append("\ndiffers from civ "+lexical_cast<string>(UnitCivID));
			wxMessageBox(warning);
		}
	}
	Armors_Class->update();
	Armors_Amount->update();
}

void AGE_Frame::OnUnitArmorsAdd(wxCommandEvent &event)
{
    if(!Units_ListV->GetSelectedItemCount()) return;

	wxBusyCursor WaitCursor;
	genie::unit::AttackOrArmor Temp;
	Temp.setGameVersion(GenieVersion);
	for(size_t loop = 0; loop < dataset->Civs.size(); ++loop)
	{
		if(dataset->Civs[loop].UnitPointers[UnitIDs.front()] != 0)
		dataset->Civs[loop].Units[UnitIDs.front()].Type50.Armours.push_back(Temp);
	}
	How2List = ADD;
	ListUnitArmors();
}

void AGE_Frame::OnUnitArmorsInsert(wxCommandEvent &event)
{
    if(!Units_Armors_ListV->GetSelectedItemCount()) return;

	wxBusyCursor WaitCursor;
	genie::unit::AttackOrArmor Temp;
	Temp.setGameVersion(GenieVersion);
	for(size_t loop = 0; loop < dataset->Civs.size(); ++loop)
	{
		if(dataset->Civs[loop].UnitPointers[UnitIDs.front()] != 0)
		dataset->Civs[loop].Units[UnitIDs.front()].Type50.Armours.insert(dataset->Civs[loop].Units[UnitIDs.front()].Type50.Armours.begin() + ArmorIDs.front(), Temp);
	}
	How2List = INSNEW;
	ListUnitArmors();
}

void AGE_Frame::OnUnitArmorsDelete(wxCommandEvent &event)
{
    auto selections = Units_Armors_ListV->GetSelectedItemCount();
    if(selections < 1) return;

	wxBusyCursor WaitCursor;
	for(short civ = 0; civ < dataset->Civs.size(); ++civ)
	{
		if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] != 0)
		if(dataset->Civs[civ].Units[UnitIDs.front()].Type50.Armours.size())
		for(auto loop = selections; loop--> 0;)
		dataset->Civs[civ].Units[UnitIDs.front()].Type50.Armours.erase(dataset->Civs[civ].Units[UnitIDs.front()].Type50.Armours.begin() + ArmorIDs[loop]);
	}
	How2List = DEL;
	ListUnitArmors();
}

void AGE_Frame::OnUnitArmorsCopy(wxCommandEvent &event)
{
    if(!Units_Armors_ListV->GetSelectedItemCount()) return;

	wxBusyCursor WaitCursor;
	if(Units_SpecialCopy_Civs->GetValue()) copies.Dat.AllCivs |= 0x40; else copies.Dat.AllCivs &= ~0x40;
	if(copies.Dat.AllCivs & 0x40)
	{
		short CivCount = dataset->Civs.size();
		copies.Dat.UnitArmorExists.resize(CivCount);
		copies.Dat.UnitArmors.resize(CivCount);
		for(short civ = 0, copy = 0; civ < dataset->Civs.size(); ++civ)
		{
			if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] == 0)
			{
				// Graphic set info not usefull.
				copies.Dat.UnitArmorExists[civ] = 255;
				CivCount--;
			}
			else
			{
				// Save info of graphic set to intelligently fill possible gaps when pasting.
				copies.Dat.UnitArmorExists[civ] = 256 + dataset->Civs[civ].IconSet;
				// Only copy armors from civs which have this unit enabled.
				CopyFromList(dataset->Civs[civ].Units[UnitIDs.front()].Type50.Armours, ArmorIDs, copies.Dat.UnitArmors[copy]); copy++;
			}
		}
		copies.Dat.UnitArmors.resize(CivCount);
	}
	else
	{
		CopyFromList(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type50.Armours, ArmorIDs, copies.Dat.UnitArmors.front());
	}
	Units_Armors_ListV->SetFocus();
}

void AGE_Frame::OnUnitArmorsPaste(wxCommandEvent &event)
{
    if(!Units_Armors_ListV->GetSelectedItemCount()) return;

    wxBusyCursor WaitCursor;
    if(copies.Dat.AllCivs & 0x40)
    {
        for(size_t civ = 0, copy = 0; civ < dataset->Civs.size(); ++civ)
        {
            if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] == 0)
            {
                // Consume copies.
                if(copies.Dat.UnitArmorExists[civ] > 255) ++copy; continue;
            }
            // If the target unit exists then choose from following.
            if(copies.Dat.UnitArmorExists[civ] > 255 && copy < copies.Dat.UnitArmors.size())
            {
                PasteToList(dataset->Civs[civ].Units[UnitIDs.front()].Type50.Armours, ArmorIDs, copies.Dat.UnitArmors[copy]); ++copy;
            }
            else
            {
                PasteToList(dataset->Civs[civ].Units[UnitIDs.front()].Type50.Armours, ArmorIDs, copies.Dat.UnitArmors.front());
            }
        }
    }
    else
    {
        PasteToList(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type50.Armours, ArmorIDs, copies.Dat.UnitArmors.front());
    }
    ListUnitArmors();
}

void AGE_Frame::OnUnitArmorsPasteInsert(wxCommandEvent &event)
{
    if(!Units_Armors_ListV->GetSelectedItemCount()) return;

	wxBusyCursor WaitCursor;
	if(copies.Dat.AllCivs & 0x40)
	{
		for(short civ = 0, copy = 0; civ < dataset->Civs.size(); ++civ)
		{
			if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] == 0)
			{
				// Consume copies.
				if(copies.Dat.UnitArmorExists[civ] > 255) copy++; continue;
			}
			// If the target unit exists then choose from following.
			if(copies.Dat.UnitArmorExists[civ] > 255 && copy < copies.Dat.UnitArmors.size())
			{
				PasteInsertToList(dataset->Civs[civ].Units[UnitIDs.front()].Type50.Armours, ArmorIDs.front(), copies.Dat.UnitArmors[copy]); copy++;
			}
			else
			{
				PasteInsertToList(dataset->Civs[civ].Units[UnitIDs.front()].Type50.Armours, ArmorIDs.front(), copies.Dat.UnitArmors.front());
			}
		}
	}
	else
	{
		PasteInsertToList(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type50.Armours, ArmorIDs.front(), copies.Dat.UnitArmors.front());
	}
	ListUnitArmors();
}

void AGE_Frame::OnUnitArmorsCopyToUnits(wxCommandEvent &event)
{
	for(short civ = 0; civ < dataset->Civs.size(); ++civ)
	for(size_t loop=1; loop < UnitIDs.size(); ++loop)
	{
		dataset->Civs[civ].Units[UnitIDs[loop]].Type50.Armours = dataset->Civs[civ].Units[UnitIDs.front()].Type50.Armours;
	}
}

//	AoE/TC/SWGB/CC Unit Commands

wxString AGE_Frame::GetUnitCommandName(int index)
{
	short CommandType = (GenieVersion >= genie::GV_AoK) ? dataset->UnitHeaders[UnitIDs.front()].Commands[index].Type : dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.Commands[index].Type;
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
		case 14: return UnitCommands_Type_ComboBox->GetString(13);
		case 20: return UnitCommands_Type_ComboBox->GetString(14);
		case 21: return UnitCommands_Type_ComboBox->GetString(15);
		case 101: return UnitCommands_Type_ComboBox->GetString(16);
		case 102: return UnitCommands_Type_ComboBox->GetString(17);
		case 103: return UnitCommands_Type_ComboBox->GetString(18);
		case 104: return UnitCommands_Type_ComboBox->GetString(19);
		case 105: return UnitCommands_Type_ComboBox->GetString(20);
		case 106: return UnitCommands_Type_ComboBox->GetString(21);
		case 107: return UnitCommands_Type_ComboBox->GetString(22);
		case 108: return UnitCommands_Type_ComboBox->GetString(23);
		case 109: return UnitCommands_Type_ComboBox->GetString(24);
		case 110: return UnitCommands_Type_ComboBox->GetString(25);
		case 111: return UnitCommands_Type_ComboBox->GetString(26);
		case 120: return UnitCommands_Type_ComboBox->GetString(27);
		case 121: return UnitCommands_Type_ComboBox->GetString(28);
		case 122: return UnitCommands_Type_ComboBox->GetString(29);
		case 123: return UnitCommands_Type_ComboBox->GetString(30);
		case 124: return UnitCommands_Type_ComboBox->GetString(31);
		case 125: return UnitCommands_Type_ComboBox->GetString(32);
		case 130: return UnitCommands_Type_ComboBox->GetString(33);
		case 131: return UnitCommands_Type_ComboBox->GetString(34);
		case 132: return UnitCommands_Type_ComboBox->GetString(35);
		case 133: return UnitCommands_Type_ComboBox->GetString(36);
		case 134: return UnitCommands_Type_ComboBox->GetString(37);
		case 135: return UnitCommands_Type_ComboBox->GetString(38);
		case 136: return UnitCommands_Type_ComboBox->GetString(39);
		case 149: return UnitCommands_Type_ComboBox->GetString(40);
		case 150: return UnitCommands_Type_ComboBox->GetString(41);
		case 151: return UnitCommands_Type_ComboBox->GetString(42);
		default: return "Unk. Type "+lexical_cast<string>(CommandType);
	}
}

void AGE_Frame::OnUnitCommandsSearch(wxCommandEvent &event)
{
	How2List = SEARCH;
	ListUnitCommands();
}

void AGE_Frame::ListUnitCommands()
{
	InitSearch(Units_UnitCommands_Search->GetValue().MakeLower(), Units_UnitCommands_Search_R->GetValue().MakeLower());

	Units_UnitCommands_ListV->names.clear();
    Units_UnitCommands_ListV->indexes.clear();
    wxArrayString names;

	if(GenieVersion >= genie::GV_AoK)	// AoK, TC, SWGB or CC
	{
        if(Units_ListV->GetSelectedItemCount())
		for(size_t loop = 0; loop < dataset->UnitHeaders[UnitIDs.front()].Commands.size(); ++loop)
		{
			wxString Name = " "+FormatInt(loop)+" - "+GetUnitCommandName(loop);
			if(dataset->UnitHeaders[UnitIDs.front()].Commands[loop].ClassID != -1)
			Name += " class "+lexical_cast<string>(dataset->UnitHeaders[UnitIDs.front()].Commands[loop].ClassID);
			else if(dataset->UnitHeaders[UnitIDs.front()].Commands[loop].UnitID != -1)
			Name += " unit "+lexical_cast<string>(dataset->UnitHeaders[UnitIDs.front()].Commands[loop].UnitID);
			if(SearchMatches(Name.Lower()))
			{
				Units_UnitCommands_ListV->names.Add(Name);
                Units_UnitCommands_ListV->indexes.push_back(loop);
			}
            names.Add(Name);
		}
	}
	else	// AoE or RoR
	{
		if(Units_ListV->GetSelectedItemCount()
		&& dataset->Civs[UnitCivID].UnitPointers[UnitIDs.front()] != 0
		&& dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type >= 40
		&& dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type <= 80)
		{
			Units_UnitCommands_Add->Enable(true);
			for(size_t loop = 0; loop < dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.Commands.size(); ++loop)
			{
				wxString Name = " "+FormatInt(loop)+" - "+GetUnitCommandName(loop);
				if(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.Commands[loop].ClassID != -1)
				Name += " class "+lexical_cast<string>(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.Commands[loop].ClassID);
				else if(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.Commands[loop].UnitID != -1)
				Name += " unit "+lexical_cast<string>(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.Commands[loop].UnitID);
				if(SearchMatches(Name.Lower()))
				{
					Units_UnitCommands_ListV->names.Add(Name);
                    Units_UnitCommands_ListV->indexes.push_back(loop);
				}
                names.Add(Name);
			}
		}
		else
		{
			Units_UnitCommands_Add->Enable(false);
		}
	}
	virtualListing(Units_UnitCommands_ListV);
    vector<ComboBox_Plus1*> boxlist{Units_ActionWhenDiscoveredID_ComboBox};
    FillLists(boxlist, names);

	wxTimerEvent E;
	OnUnitCommandsTimer(E);
}

void AGE_Frame::OnUnitCommandsSelect(wxCommandEvent &event)
{
    if(!actionTimer.IsRunning())
        actionTimer.Start(150);
}

void AGE_Frame::OnUnitCommandsTimer(wxTimerEvent &event)
{
    actionTimer.Stop();
	auto selections = Units_UnitCommands_ListV->GetSelectedItemCount();
    wxBusyCursor WaitCursor;
    for(auto &box: uiGroupUnitCommand) box->clear();
    UnitCommands_ID->clear();
	if(selections > 0)
	{
        getSelectedItems(selections, Units_UnitCommands_ListV, CommandIDs);

		bool showWarning = false;
		wxString warning = "Command count of civs\n";
		genie::UnitCommand * CommandPointer = 0;
		for(auto sel = selections; sel--> 0;)
		{
			for(short vecCiv = (GenieVersion < genie::GV_AoK) ? SelectedCivs.size() : 1; vecCiv--> 0;)
			{
				if(GenieVersion < genie::GV_AoK)
				{
					if(sel == 0 && dataset->Civs[SelectedCivs[vecCiv]].Units[UnitIDs.front()].Bird.Commands.size() != dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.Commands.size())
					{
						warning.Append(lexical_cast<string>(SelectedCivs[vecCiv])+" ");
						showWarning = true;
					}
					CommandPointer = &dataset->Civs[SelectedCivs[vecCiv]].Units[UnitIDs.front()].Bird.Commands[CommandIDs[sel]];
				}
				else
				{
					CommandPointer = &dataset->UnitHeaders[UnitIDs.front()].Commands[CommandIDs[sel]];
				}

				UnitCommands_One->prepend(&CommandPointer->Enabled);
				UnitCommands_ID->prepend(&CommandPointer->ID);
				UnitCommands_Unknown1->prepend(&CommandPointer->Unknown1);
				UnitCommands_Type->prepend(&CommandPointer->Type);
				UnitCommands_ClassID->prepend(&CommandPointer->ClassID);
				UnitCommands_UnitID->prepend(&CommandPointer->UnitID);
				UnitCommands_TerrainID->prepend(&CommandPointer->TerrainID);
				UnitCommands_ResourceIn->prepend(&CommandPointer->ResourceIn);
				UnitCommands_ProductivityResource->prepend(&CommandPointer->ResourceProductivityMultiplier);
				UnitCommands_ResourceOut->prepend(&CommandPointer->ResourceOut);
				UnitCommands_Resource->prepend(&CommandPointer->Resource);
				UnitCommands_WorkRateMultiplier->prepend(&CommandPointer->Quantity);
				UnitCommands_ExecutionRadius->prepend(&CommandPointer->ExecutionRadius);
				UnitCommands_ExtraRange->prepend(&CommandPointer->ExtraRange);
				UnitCommands_Unknown4->prepend(&CommandPointer->Unknown4);
				UnitCommands_Unknown5->prepend(&CommandPointer->Unknown5);
				UnitCommands_SelectionEnabler->prepend(&CommandPointer->SelectionEnabler);
				UnitCommands_Unknown7->prepend(&CommandPointer->Unknown7);
				UnitCommands_Unknown8->prepend(&CommandPointer->PlunderSource);
				UnitCommands_Unknown9->prepend(&CommandPointer->Unknown9);
				UnitCommands_SelectionMode->prepend(&CommandPointer->SelectionMode);
				UnitCommands_RightClickMode->prepend(&CommandPointer->RightClickMode);
				UnitCommands_Unknown12->prepend(&CommandPointer->Unknown12);
				UnitCommands_Graphics.front()->prepend(&CommandPointer->ToolGraphicID);
				UnitCommands_Graphics[1]->prepend(&CommandPointer->ProceedingGraphicID);
				UnitCommands_Graphics[2]->prepend(&CommandPointer->ActionGraphicID);
				UnitCommands_Graphics[3]->prepend(&CommandPointer->CarryingGraphicID);
				UnitCommands_Graphics[4]->prepend(&CommandPointer->ExecutionSoundID);
				UnitCommands_Graphics[5]->prepend(&CommandPointer->ResourceDepositSoundID);
			}
			if(showWarning)
			{
				warning.Append("\ndiffers from civ "+lexical_cast<string>(UnitCivID));
				wxMessageBox(warning);
			}
		}
        if(CommandPointer)
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
			case 14: UnitCommands_Type_ComboBox->SetSelection(13); break;
			case 20: UnitCommands_Type_ComboBox->SetSelection(14); break;
			case 21: UnitCommands_Type_ComboBox->SetSelection(15); break;
			case 101: UnitCommands_Type_ComboBox->SetSelection(16); break;
			case 102: UnitCommands_Type_ComboBox->SetSelection(17); break;
			case 103: UnitCommands_Type_ComboBox->SetSelection(18); break;
			case 104: UnitCommands_Type_ComboBox->SetSelection(19); break;
			case 105: UnitCommands_Type_ComboBox->SetSelection(20); break;
			case 106: UnitCommands_Type_ComboBox->SetSelection(21); break;
			case 107: UnitCommands_Type_ComboBox->SetSelection(22); break;
			case 108: UnitCommands_Type_ComboBox->SetSelection(23); break;
			case 109: UnitCommands_Type_ComboBox->SetSelection(24); break;
			case 110: UnitCommands_Type_ComboBox->SetSelection(25); break;
			case 111: UnitCommands_Type_ComboBox->SetSelection(26); break;
			case 120: UnitCommands_Type_ComboBox->SetSelection(27); break;
			case 121: UnitCommands_Type_ComboBox->SetSelection(28); break;
			case 122: UnitCommands_Type_ComboBox->SetSelection(29); break;
			case 123: UnitCommands_Type_ComboBox->SetSelection(30); break;
			case 124: UnitCommands_Type_ComboBox->SetSelection(31); break;
			case 125: UnitCommands_Type_ComboBox->SetSelection(32); break;
			case 130: UnitCommands_Type_ComboBox->SetSelection(33); break;
			case 131: UnitCommands_Type_ComboBox->SetSelection(34); break;
			case 132: UnitCommands_Type_ComboBox->SetSelection(35); break;
			case 133: UnitCommands_Type_ComboBox->SetSelection(36); break;
			case 134: UnitCommands_Type_ComboBox->SetSelection(37); break;
			case 135: UnitCommands_Type_ComboBox->SetSelection(38); break;
			case 136: UnitCommands_Type_ComboBox->SetSelection(39); break;
			case 149: UnitCommands_Type_ComboBox->SetSelection(40); break;
			case 150: UnitCommands_Type_ComboBox->SetSelection(41); break;
			case 151: UnitCommands_Type_ComboBox->SetSelection(42); break;
			default: UnitCommands_Type_ComboBox->SetSelection(0);
		}
	}
    for(auto &box: uiGroupUnitCommand) box->update();
    UnitCommands_ID->refill();
    wxCommandEvent E;
    OnChooseGraphic(E);
}

void AGE_Frame::OnUnitCommandsAdd(wxCommandEvent &event)
{
    if(!Units_ListV->GetSelectedItemCount()) return;

	wxBusyCursor WaitCursor;
	genie::UnitCommand Temp;
	Temp.setGameVersion(GenieVersion);
	if(GenieVersion >= genie::GV_AoK)
	{
		dataset->UnitHeaders[UnitIDs.front()].Commands.push_back(Temp);
		if(EnableIDFix)
		dataset->UnitHeaders[UnitIDs.front()].Commands[dataset->UnitHeaders[UnitIDs.front()].Commands.size()-1].ID = (int16_t)(dataset->UnitHeaders[UnitIDs.front()].Commands.size()-1); // ID Fix
	}
	else
	{
		for(size_t loop = 0; loop < dataset->Civs.size(); ++loop)
		{
			if(dataset->Civs[loop].UnitPointers[UnitIDs.front()] != 0)
			{
				dataset->Civs[loop].Units[UnitIDs.front()].Bird.Commands.push_back(Temp);
				if(EnableIDFix)
				dataset->Civs[loop].Units[UnitIDs.front()].Bird.Commands[dataset->Civs.front().Units[UnitIDs.front()].Bird.Commands.size()-1].ID = (int16_t)(dataset->Civs.front().Units[UnitIDs.front()].Bird.Commands.size()-1); // ID Fix
			}
		}
	}
	How2List = ADD;
	ListUnitCommands();
}

void AGE_Frame::OnUnitCommandsInsert(wxCommandEvent &event)
{
    if(!Units_UnitCommands_ListV->GetSelectedItemCount()) return;

	wxBusyCursor WaitCursor;
	genie::UnitCommand Temp;
	Temp.setGameVersion(GenieVersion);
	if(GenieVersion >= genie::GV_AoK)
	{
		dataset->UnitHeaders[UnitIDs.front()].Commands.insert(dataset->UnitHeaders[UnitIDs.front()].Commands.begin() + CommandIDs.front(), Temp);
		if(EnableIDFix)
		for(size_t loop2 = CommandIDs.front();loop2 < dataset->UnitHeaders[UnitIDs.front()].Commands.size(); ++loop2) // ID Fix
		dataset->UnitHeaders[UnitIDs.front()].Commands[loop2].ID = loop2;
	}
	else
	{
		for(size_t loop = 0; loop < dataset->Civs.size(); ++loop)
		{
			if(dataset->Civs[loop].UnitPointers[UnitIDs.front()] != 0)
			{
				dataset->Civs[loop].Units[UnitIDs.front()].Bird.Commands.insert(dataset->Civs[loop].Units[UnitIDs.front()].Bird.Commands.begin() + CommandIDs.front(), Temp);
				if(EnableIDFix)
				for(size_t loop2 = CommandIDs.front();loop2 < dataset->Civs.front().Units[UnitIDs.front()].Bird.Commands.size(); ++loop2) // ID Fix
				dataset->Civs[loop].Units[UnitIDs.front()].Bird.Commands[loop2].ID = loop2;
			}
		}
	}
	How2List = INSNEW;
	ListUnitCommands();
}

void AGE_Frame::OnUnitCommandsDelete(wxCommandEvent &event)
{
    auto selections = Units_UnitCommands_ListV->GetSelectedItemCount();
    if(selections < 1) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion >= genie::GV_AoK)
	{
		for(auto loop = selections; loop--> 0;)
		dataset->UnitHeaders[UnitIDs.front()].Commands.erase(dataset->UnitHeaders[UnitIDs.front()].Commands.begin() + CommandIDs[loop]);
		if(EnableIDFix)
		for(size_t loop2 = CommandIDs.front();loop2 < dataset->UnitHeaders[UnitIDs.front()].Commands.size(); ++loop2) // ID Fix
		dataset->UnitHeaders[UnitIDs.front()].Commands[loop2].ID = loop2;
	}
	else
	{
		for(short civ = 0; civ < dataset->Civs.size(); ++civ)
		{
			if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] != 0)
			if(dataset->Civs[civ].Units[UnitIDs.front()].Bird.Commands.size())
			{
				for(auto loop = selections; loop--> 0;)
				dataset->Civs[civ].Units[UnitIDs.front()].Bird.Commands.erase(dataset->Civs[civ].Units[UnitIDs.front()].Bird.Commands.begin() + CommandIDs[loop]);
				if(EnableIDFix)
				for(size_t loop2 = CommandIDs.front();loop2 < dataset->Civs.front().Units[UnitIDs.front()].Bird.Commands.size(); ++loop2) // ID Fix
				dataset->Civs[civ].Units[UnitIDs.front()].Bird.Commands[loop2].ID = loop2;
			}
		}
	}
	How2List = DEL;
	ListUnitCommands();
}

void AGE_Frame::OnUnitCommandsCopy(wxCommandEvent &event)
{
    if(!Units_UnitCommands_ListV->GetSelectedItemCount()) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion >= genie::GV_AoK)
	{
		copies.Dat.AllCivs |= 0x80;
		copies.Dat.UnitCommandExists.resize(0);
		copies.Dat.UnitCommands.resize(1);
		CopyFromList(dataset->UnitHeaders[UnitIDs.front()].Commands, CommandIDs, copies.Dat.UnitCommands.front());
		return;
	}
	if(Units_SpecialCopy_Civs->GetValue()) copies.Dat.AllCivs |= 0x80; else copies.Dat.AllCivs &= ~0x80;
	if(copies.Dat.AllCivs & 0x80)
	{
		short CivCount = dataset->Civs.size();
		copies.Dat.UnitCommandExists.resize(CivCount);
		copies.Dat.UnitCommands.resize(CivCount);
		for(short civ = 0, copy = 0; civ < dataset->Civs.size(); ++civ)
		{
			if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] == 0)
			{
				// Graphic set info not usefull.
				copies.Dat.UnitCommandExists[civ] = 255;
				CivCount--;
			}
			else
			{
				// Save info of graphic set to intelligently fill possible gaps when pasting.
				copies.Dat.UnitCommandExists[civ] = 256 + dataset->Civs[civ].IconSet;
				// Only copy commands from civs which have this unit enabled.
				CopyFromList(dataset->Civs[civ].Units[UnitIDs.front()].Bird.Commands, CommandIDs, copies.Dat.UnitCommands[copy]); copy++;
			}
		}
		copies.Dat.UnitCommands.resize(CivCount);
	}
	else
	{
		CopyFromList(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.Commands, CommandIDs, copies.Dat.UnitCommands.front());
	}
	Units_UnitCommands_ListV->SetFocus();
}

void AGE_Frame::OnUnitCommandsPaste(wxCommandEvent &event)
{
    if(!Units_UnitCommands_ListV->GetSelectedItemCount()) return;

    wxBusyCursor WaitCursor;
    if(GenieVersion >= genie::GV_AoK)
    {
        PasteToListIDFix(dataset->UnitHeaders[UnitIDs.front()].Commands, CommandIDs, copies.Dat.UnitCommands.front());
    }
    else if(copies.Dat.AllCivs & 0x80)
    {
        for(size_t civ = 0, copy = 0; civ < dataset->Civs.size(); ++civ)
        {
            if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] == 0)
            {
                // Consume copies.
                if(copies.Dat.UnitCommandExists[civ] > 255) ++copy; continue;
            }
            // If the target unit exists then choose from following.
            if(copies.Dat.UnitCommandExists.size() > 0 && copies.Dat.UnitCommandExists[civ] > 255 && copy < copies.Dat.UnitCommands.size())
            {
                PasteToListIDFix(dataset->Civs[civ].Units[UnitIDs.front()].Bird.Commands, CommandIDs, copies.Dat.UnitCommands[copy]); ++copy;
            }
            else
            {
                PasteToListIDFix(dataset->Civs[civ].Units[UnitIDs.front()].Bird.Commands, CommandIDs, copies.Dat.UnitCommands.front());
            }
        }
    }
    else
    {
        PasteToListIDFix(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.Commands, CommandIDs, copies.Dat.UnitCommands.front());
    }
    ListUnitCommands();
}

void AGE_Frame::OnUnitCommandsPasteInsert(wxCommandEvent &event)
{
    if(!Units_UnitCommands_ListV->GetSelectedItemCount()) return;

	wxBusyCursor WaitCursor;
	if(GenieVersion >= genie::GV_AoK)
	{
		PasteInsertToListIDFix(dataset->UnitHeaders[UnitIDs.front()].Commands, CommandIDs.front(), copies.Dat.UnitCommands.front());
	}
	else if(copies.Dat.AllCivs & 0x80)
	{
		for(short civ = 0, copy = 0; civ < dataset->Civs.size(); ++civ)
		{
			if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] == 0)
			{
				// Consume copies.
				if(copies.Dat.UnitCommandExists[civ] > 255) copy++; continue;
			}
			// If the target unit exists then choose from following.
			if(copies.Dat.UnitCommandExists.size() > 0 && copies.Dat.UnitCommandExists[civ] > 255 && copy < copies.Dat.UnitCommands.size())
			{
				PasteInsertToListIDFix(dataset->Civs[civ].Units[UnitIDs.front()].Bird.Commands, CommandIDs.front(), copies.Dat.UnitCommands[copy]); copy++;
			}
			else
			{
				PasteInsertToListIDFix(dataset->Civs[civ].Units[UnitIDs.front()].Bird.Commands, CommandIDs.front(), copies.Dat.UnitCommands.front());
			}
		}
	}
	else
	{
		PasteInsertToListIDFix(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.Commands, CommandIDs.front(), copies.Dat.UnitCommands.front());
	}
	ListUnitCommands();
}

void AGE_Frame::OnUnitCommandsCopyToUnits(wxCommandEvent &event)
{
	if(GenieVersion < genie::GV_AoK)
	{
		for(short civ = 0; civ < dataset->Civs.size(); ++civ)
		for(size_t loop=1; loop < UnitIDs.size(); ++loop)
		{
			dataset->Civs[civ].Units[UnitIDs[loop]].Bird.Commands = dataset->Civs[civ].Units[UnitIDs.front()].Bird.Commands;
		}
	}
	else
	{
		for(size_t loop=1; loop < UnitIDs.size(); ++loop)
		{
			dataset->UnitHeaders[UnitIDs[loop]].Commands = dataset->UnitHeaders[UnitIDs.front()].Commands;
		}
	}
}

void AGE_Frame::UnitLangDLLConverter(wxCommandEvent &event)
{
	int32_t DLLValue;
	try
	{
		DLLValue = lexical_cast<int32_t>(((wxTextCtrl*)event.GetEventObject())->GetValue());
	}
	catch(bad_lexical_cast e)
	{
		wxMessageBox("Incorrect input!");
		return;
	}
	if(event.GetId() == Units_LanguageDLLConverter[0]->GetId())
	{
		if(GenieVersion < genie::GV_AoKA) DLLValue += 0x10000;
		else DLLValue += 79000;
		if(!AutoCopy)
		{
			dataset->Civs[UnitCivID].Units[UnitIDs.front()].LanguageDLLHelp = DLLValue;
		}
		else for(short civ = 0; civ < dataset->Civs.size(); ++civ)
		{
			dataset->Civs[civ].Units[UnitIDs.front()].LanguageDLLHelp = DLLValue;
		}
	}
	else
	{
		if(GenieVersion < genie::GV_AoKA) DLLValue += 0x20000;
		else DLLValue += 140000;
		if(!AutoCopy)
		{
			dataset->Civs[UnitCivID].Units[UnitIDs.front()].LanguageDLLHotKeyText = DLLValue;
		}
		else for(short civ = 0; civ < dataset->Civs.size(); ++civ)
		{
			dataset->Civs[civ].Units[UnitIDs.front()].LanguageDLLHotKeyText = DLLValue;
		}
	}
	wxTimerEvent E;
	OnUnitsTimer(E);
}

void AGE_Frame::CreateUnitControls()
{
//	UnitControls new things

	Tab_Units = new wxPanel(TabBar_Main);

	Units_Main = new wxBoxSizer(wxHORIZONTAL);
	Units_Units = new wxStaticBoxSizer(wxVERTICAL, Tab_Units, "Units");
	//Units_Line = new wxStaticLine(Tab_Units, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL, "");
	Units_Special = new wxBoxSizer(wxHORIZONTAL);
	Units_Civs_List = new wxComboBox(Tab_Units, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY);
    CivComboBoxListNormal.push_back(Units_Civs_List);
	Units_Search = new wxTextCtrl(Tab_Units, wxID_ANY);
	Units_UseAnd[0] = new wxCheckBox(Tab_Units, wxID_ANY, "And");
	Units_Search_R = new wxTextCtrl(Tab_Units, wxID_ANY);
	Units_UseAnd[1] = new wxCheckBox(Tab_Units, wxID_ANY, "And");
	Units_FilterSelector = new AGEODComboBox(Tab_Units);
	for(size_t loop = 0; loop < 2; ++loop)
	{
		Units_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
		Units_SearchFilters[loop] = new AGEODComboBox(Tab_Units, AGETextCtrl::LARGE, wxCB_SORT);
	}
	Units_ListV = new AGEListView(Tab_Units, wxSize(200, 100));
	wxGridSizer *Units_Buttons = new wxGridSizer(3, 0, 0);
	wxBoxSizer *Units_Buttons1 = new wxBoxSizer(wxHORIZONTAL);
	Units_Add = new wxButton(Tab_Units, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
	Units_Insert = new wxButton(Tab_Units, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
	Units_Delete = new wxButton(Tab_Units, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
	Units_Copy = new wxButton(Tab_Units, wxID_ANY, "Copy *", wxDefaultPosition, wxSize(10, -1));
	Units_Copy->SetToolTip("When \"All civs\" is not selected,\nthis and pasting works just like automatic copy,\n(from current civilization to selected ones)\ntaking \"Including graphics\" option into account");
	Units_Paste = new wxButton(Tab_Units, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
	Units_PasteInsert = new wxButton(Tab_Units, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
	Units_Info = new wxStaticText(Tab_Units, wxID_ANY, " Info *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Info->SetToolTip("Add/Insert/Delete works for all civilizations\n...");
	//Units_Extract = new wxButton(Tab_Units, wxID_ANY, "Extract", wxDefaultPosition, wxSize(10, -1));
	//Units_Extract->Enable(false);
	//Units_Import = new wxButton(Tab_Units, wxID_ANY, "Import", wxDefaultPosition, wxSize(10, -1));
	//Units_Import->Enable(false);
	Units_SpecialCopy = new wxButton(Tab_Units, wxID_ANY, "S copy", wxDefaultPosition, wxSize(10, -1));
	Units_SpecialPaste = new wxButton(Tab_Units, wxID_ANY, "S paste", wxDefaultPosition, wxSize(10, -1));
	Units_Enable = new wxButton(Tab_Units, wxID_ANY, "Exist", wxDefaultPosition, wxSize(10, -1));
	Units_Disable = new wxButton(Tab_Units, wxID_ANY, "Wipe Out", wxDefaultPosition, wxSize(10, -1));
	Units_SpecialCopy_Options = new AGEODComboBox(Tab_Units, AGETextCtrl::NORMAL);
	Units_SpecialCopy_Civs = new wxCheckBox(Tab_Units, wxID_ANY, "All civs *");
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
	Units_TopGrid_Holder = new wxWrapSizer();
	Units_AutoCopy = new wxCheckBox(Tab_Units, wxID_ANY, "Automatically");
	Units_AutoCopy->SetToolTip("It is safer to copy automatically than manually.");
	Units_CopyTo = new wxButton(Tab_Units, wxID_ANY, "Copy", wxDefaultPosition, wxSize(40, -1));
	Units_CopyGraphics = new wxCheckBox(Tab_Units, wxID_ANY, "Including graphics");
	Units_CopyToText = new wxStaticText(Tab_Units, wxID_ANY, " to selected civilizations: ", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Units_SelectAll = new wxButton(Tab_Units, wxID_ANY, "All", wxDefaultPosition, wxSize(40, -1));
	Units_SelectClear = new wxButton(Tab_Units, wxID_ANY, "None", wxDefaultPosition, wxSize(40, -1));
	Units_GraphicSetText = new wxStaticText(Tab_Units, wxID_ANY, " Graphic set: ", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Units_GraphicSet = new AGEODComboBox(Tab_Units, AGETextCtrl::NORMAL);
    visibleUnitCiv = new wxStaticText(Tab_Units, wxID_ANY, "Civ ", wxDefaultPosition, wxSize(AGETextCtrl::NORMAL, -1), wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Identity_Holder = new wxStaticBoxSizer(wxVERTICAL, Tab_Units, "");
	Units_Type_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_Type_Text = new wxStaticText(Tab_Units, wxID_ANY, "Type ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Type = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Tab_Units, AGETextCtrl::SMALL);
	Units_Type_ComboBox = new AGEODComboBox(Tab_Units);
	Units_Class = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Tab_Units);
	Units_Class->SetToolTip("Determines many things and works in conjunction with other variables");
	Units_Class_ComboBox[0] = new ComboBox_Plus1(Tab_Units, Units_Class);
	Units_Scroller = new AGE_Scrolled(Tab_Units);
	Units_ScrollSpace = new wxBoxSizer(wxVERTICAL);
	Units_TypeArea_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_LangDLLArea_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Language DLLs");
	Units_GraphicsArea_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Graphics");
	Units_GraphicsArea1_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_GraphicsArea4_Holder = new wxBoxSizer(wxVERTICAL);
	Units_GraphicsArea5_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_StatsArea_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Statistics");
    Units_StatsArea1A_Sizer = new wxBoxSizer(wxHORIZONTAL);
	Units_StatsArea1B_Sizer = new wxBoxSizer(wxHORIZONTAL);
	Units_StatsAreaGarrison_Grid = new wxBoxSizer(wxHORIZONTAL);
	Units_StatsArea2_Grid = new wxBoxSizer(wxHORIZONTAL);
	Units_ProjectilesArea_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Projectiles");
	Units_ProjectilesArea1_Grid = new wxWrapSizer();
	Units_Attributes_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Attributes");
	Units_AttributesBoxes1_Grid = new wxWrapSizer();
	Units_Attributes1_Grid = new wxWrapSizer();
	Units_Attributes2_Grid = new wxBoxSizer(wxHORIZONTAL);
	Units_AttributesModes1_Grid = new wxWrapSizer();
	wxBoxSizer *Units_DropSite_Holder = new wxBoxSizer(wxVERTICAL);
	Units_AttributesSizes_Holder = new wxWrapSizer();
	Units_AttributesSelection1_Grid = new wxWrapSizer();
	Units_LangRegular_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_LangHotKey_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_AttributesTracking_Grid = new wxBoxSizer(wxHORIZONTAL);
	Units_AttributesTrain1_Grid = new wxBoxSizer(wxHORIZONTAL);
	Units_Attributes3_Grid = new wxBoxSizer(wxHORIZONTAL);
	Units_SoundsArea_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Sounds (that only you hear)");
	Units_SoundsArea1_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_SoundsArea2_Grid = new wxBoxSizer(wxHORIZONTAL);
	Units_UnknownArea_Holder = new wxWrapSizer();
	Units_Type10plusUnknownArea_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Type 10+ Unknowns (All Units)");
	Units_Type30plusUnknownArea_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Type 30+ Unknowns (Dead/Fish)");
	Units_Type70plusUnknownArea_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Type 70+ Unknowns (Creatable)");
	Units_Type80plusUnknownArea_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Type 80+ Unknowns (Building)");
	Units_CommandsArea_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Actions (Shared by all civilizations since Age of Empires II)");

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
	Units_SizeRadius_Grid = new wxBoxSizer(wxHORIZONTAL);
	Units_TrainSound_Holder = new wxBoxSizer(wxVERTICAL);
	Units_TrainSound1_Holder = new wxBoxSizer(wxVERTICAL);
	Units_TrainSound2_Holder = new wxBoxSizer(wxVERTICAL);
	Units_TrainSound3_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_DeadUnitID_Holder = new wxBoxSizer(wxVERTICAL);
	Units_PlacementMode_Holder = new wxBoxSizer(wxVERTICAL);
	Units_AirMode_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_IconID_Holder = new wxBoxSizer(wxVERTICAL);
	wxSizer *Units_IconID_Grid = new wxBoxSizer(wxHORIZONTAL);
	Units_HideInEditor_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_Unknown1_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Enabled_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_Disabled_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_PlacementSideTerrain_Holder = new wxBoxSizer(wxVERTICAL);
	Units_PlacementSideTerrainGrid_Holder = new wxGridSizer(2, 0, 5);
	Units_PlacementTerrain_Holder = new wxBoxSizer(wxVERTICAL);
	Units_PlacementTerrainGrid_Holder = new wxGridSizer(2, 0, 5);
	Units_ClearanceSize_Holder = new wxBoxSizer(wxVERTICAL);
	Units_ClearanceSize_Grid = new wxBoxSizer(wxHORIZONTAL);
	Units_HillMode_Holder = new wxBoxSizer(wxVERTICAL);
	Units_VisibleInFog_Holder = new wxBoxSizer(wxVERTICAL);
	Units_TerrainRestriction_Holder = new wxBoxSizer(wxVERTICAL);
	Units_FlyMode_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_ResourceCapacity_Holder = new wxBoxSizer(wxVERTICAL);
	Units_ResourceDecay_Holder = new wxBoxSizer(wxVERTICAL);
	Units_BlastDefenseLevel_Holder = new wxBoxSizer(wxVERTICAL);
	Units_SubType_Holder = new wxBoxSizer(wxVERTICAL);
	Units_InteractionMode_Holder = new wxBoxSizer(wxVERTICAL);
	Units_MinimapMode_Holder = new wxBoxSizer(wxVERTICAL);
	Units_CommandID_Holder = new wxBoxSizer(wxVERTICAL);
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
	Units_Nothing_Holder = new wxBoxSizer(wxVERTICAL);
	Units_SelectionEffect_Holder = new wxBoxSizer(wxVERTICAL);
	Units_EditorSelectionColour_Holder = new wxBoxSizer(wxVERTICAL);
	Units_SelectionRadius_Holder = new wxBoxSizer(wxVERTICAL);
	Units_ResourceStorageHeader_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Resource Storages");
	Units_ResourceStorage_Texts = new wxBoxSizer(wxVERTICAL);
	for(auto &sizer: Units_ResourceStorage_Holder)
	sizer = new wxBoxSizer(wxVERTICAL);
	Units_SelectionSound_Holder = new wxBoxSizer(wxVERTICAL);
	Units_DyingSound_Holder = new wxBoxSizer(wxVERTICAL);
	Units_AttackMode_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Unknown10_Holder = new wxBoxSizer(wxVERTICAL);
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
	Units_RotationAngles_Holder = new wxBoxSizer(wxVERTICAL);
	Units_RotationAngles_Grid = new wxBoxSizer(wxHORIZONTAL);

//	Type 40+

	Units_ActionWhenDiscoveredID_Holder = new wxBoxSizer(wxVERTICAL);
	Units_SearchRadius_Holder = new wxBoxSizer(wxVERTICAL);
	Units_WorkRate_Holder = new wxBoxSizer(wxVERTICAL);
	Units_DropSite_Grid = new wxGridSizer(2, 0, 5);
	Units_TaskSwapID_Holder = new wxBoxSizer(wxVERTICAL);
	Units_AttackSound_Holder = new wxBoxSizer(wxVERTICAL);
	Units_MoveSound_Holder = new wxBoxSizer(wxVERTICAL);
	Units_AnimalMode_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_Exists_Holder = new wxBoxSizer(wxVERTICAL);

//	Type 50+

	Units_DefaultArmor_Holder = new wxBoxSizer(wxVERTICAL);
	Units_TerRestrictionForDmgMultiply_Holder = new wxBoxSizer(wxVERTICAL);
	Units_MaxRange_Holder = new wxBoxSizer(wxVERTICAL);
	Units_BlastWidth_Holder = new wxBoxSizer(wxVERTICAL);
	Units_ReloadTime1_Holder = new wxBoxSizer(wxVERTICAL);
	Units_ProjectileUnitID_Holder = new wxBoxSizer(wxVERTICAL);
	Units_AccuracyPercent_Holder = new wxBoxSizer(wxVERTICAL);
	Units_TowerMode_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_Delay_Holder = new wxBoxSizer(wxVERTICAL);
	Units_GraphicDisplacement_Holder = new wxBoxSizer(wxVERTICAL);
	Units_GraphicDisplacement_Grid = new wxBoxSizer(wxHORIZONTAL);
	Units_BlastAttackLevel_Holder = new wxBoxSizer(wxVERTICAL);
	Units_MinRange_Holder = new wxBoxSizer(wxVERTICAL);
	Units_AccuracyDispersion_Holder = new wxBoxSizer(wxVERTICAL);
	Units_AttackGraphic_Holder = new wxBoxSizer(wxVERTICAL);
	Units_DisplayedMeleeArmour_Holder = new wxBoxSizer(wxVERTICAL);
	Units_DisplayedAttack_Holder = new wxBoxSizer(wxVERTICAL);
	Units_DisplayedRange_Holder = new wxBoxSizer(wxVERTICAL);
	Units_ReloadTime2_Holder = new wxBoxSizer(wxVERTICAL);

//	Type 60 only

	Units_StretchMode_Holder = new wxBoxSizer(wxVERTICAL);
	Units_SmartMode_Holder = new wxBoxSizer(wxVERTICAL);
	Units_DropAnimationMode_Holder = new wxBoxSizer(wxVERTICAL);
	Units_PenetrationMode_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Unknown24_Holder = new wxBoxSizer(wxVERTICAL);
	Units_ProjectileArc_Holder = new wxBoxSizer(wxVERTICAL);

//	Type 70+

	Units_CostHeader_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Costs");
    Unit_Cost_Texts = new wxBoxSizer(wxVERTICAL);
    for(auto &sizer: Unit_Cost_Sizers)
    sizer = new wxBoxSizer(wxVERTICAL);
	Units_TrainTime_Holder = new wxBoxSizer(wxVERTICAL);
	Units_TrainLocationID_Holder = new wxBoxSizer(wxVERTICAL);
	Units_ButtonID_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Unknown26_Holder = new wxBoxSizer(wxVERTICAL);
	Units_Unknown27_Holder = new wxBoxSizer(wxVERTICAL);
	Units_UnknownType_Holder = new wxBoxSizer(wxVERTICAL);
	Units_HeroMode_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_GarrisonGraphic_Holder = new wxBoxSizer(wxVERTICAL);
	Units_GarrisonGraphic_Grid = new wxGridSizer(2, 0, 5);
	Units_MissileCount_Holder = new wxBoxSizer(wxVERTICAL);
	Units_MissileDuplicationCount_Holder = new wxBoxSizer(wxVERTICAL);
	Units_AttackMissileDuplicationSpawning_Holder = new wxBoxSizer(wxVERTICAL);
	Units_AttackMissileDuplicationSpawning_Grid = new wxBoxSizer(wxHORIZONTAL);
	Units_AttackMissileDuplicationUnit_Holder = new wxBoxSizer(wxVERTICAL);
	Units_ChargingGraphic_Holder = new wxBoxSizer(wxVERTICAL);
	Units_ChargingMode_Holder = new wxBoxSizer(wxVERTICAL);
	Units_DisplayedPierceArmour_Holder = new wxBoxSizer(wxVERTICAL);

//	Type 80

	Units_ConstructionGraphicID_Holder = new wxBoxSizer(wxVERTICAL);
	Units_SnowGraphicID_Holder = new wxBoxSizer(wxVERTICAL);
	Units_AdjacentMode_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_IconAngle_Holder = new wxBoxSizer(wxVERTICAL);
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

	Units_ID1_Text = new wxStaticText(Tab_Units, wxID_ANY, "ID 1 ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_LanguageDLLName_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Language File Name *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_LanguageDLLCreation_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Language File Creation", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Class_Text = new wxStaticText(Tab_Units, wxID_ANY, "  Class * ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_StandingGraphic_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Standing Graphics *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_DyingGraphic_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Dying Graphics", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_HitPoints_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Hit Points *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_LineOfSight_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Line Of Sight *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_GarrisonCapacity_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Garrison Capacity *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_SizeRadius_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Collision Size XY & Z *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_TrainSound_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Train Sound ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_DeadUnitID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Dead Unit", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_PlacementMode_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown Mode *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_IconID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Icon *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown1_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 1 ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_PlacementSideTerrain_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Placement Side Terrain *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_PlacementTerrain_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Placement Terrain", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ClearanceSize_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Clearance Size XY", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_HillMode_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Hill Mode *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_TerrainRestriction_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Terrain Restriction ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ResourceCapacity_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Resource Capacity ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ResourceDecay_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Resource Decay *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_BlastDefenseLevel_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Blast Defense Level *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_SubType_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Sub Type *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_InteractionMode_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Interaction Mode *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_MinimapMode_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Minimap Mode *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_CommandID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Command ID *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown3A_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 3A *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_MinimapColor_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Minimap Color *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_LanguageDLLHelp_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Language File Help *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_LanguageDLLConverter_Text[0] = new wxStaticText(Units_Scroller, wxID_ANY, " Help Converter *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_LanguageDLLConverter_Text[1] = new wxStaticText(Units_Scroller, wxID_ANY, " Hotkey Text Converter *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_LanguageDLLHotKeyText_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Lang File Hotkey Text *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_HotKey_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Hotkey *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown6_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Enable Auto Gather *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown7_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Auto Gather Mode *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown8_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Auto Gather ID *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_SelectionMask_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Selection Mask *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_SelectionShapeType_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Selection Shape Type *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_SelectionShape_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Selection Shape *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Attribute_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unit Attribute *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Civ_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Civilization", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Nothing_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Attribute Piece *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_SelectionEffect_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Selection Effect *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_EditorSelectionColour_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Editor Selection Color *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_SelectionRadius_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Selection Shape Size XY & Z *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	ResourceStorage_Type_Text = new wxStaticText(Units_Scroller, wxID_ANY, "Type", wxDefaultPosition, wxSize(90, -1), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	ResourceStorage_Amount_Text = new wxStaticText(Units_Scroller, wxID_ANY, "Amount", wxDefaultPosition, wxSize(90, -1), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	ResourceStorage_Enabled_Text = new wxStaticText(Units_Scroller, wxID_ANY, "Store Mode *", wxDefaultPosition, wxSize(90, -1), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Units_SelectionSound_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Selection Sound ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_DyingSound_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Dying Sound ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_AttackMode_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Attack Mode? *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown10_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Edible Meat? *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Name_Text = new wxStaticText(Tab_Units, wxID_ANY, " Name ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Name2_Text = new wxStaticText(Tab_Units, wxID_ANY, " Name 2 ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unitline_Text = new wxStaticText(Units_Scroller, wxID_ANY, " AI Unitline", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_MinTechLevel_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Min Tech Level", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ID2_Text = new wxStaticText(Tab_Units, wxID_ANY, "ID 2 ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ID3_Text = new wxStaticText(Tab_Units, wxID_ANY, "ID 3 ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Type 20+

	Units_Speed_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Speed ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Type 30+

	Units_WalkingGraphic_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Walking and Running Graphics", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_RotationSpeed_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Rotation Speed *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown11_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 11", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_TrackingUnit_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Tracking Unit ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_TrackingUnitUsed_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Tracking Unit Mode *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_TrackingUnitDensity_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Tracking Unit Density *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown16_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 16", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_RotationAngles_Label = " Rotations in Radians *";
	Units_RotationAngles_Text = new wxStaticText(Units_Scroller, wxID_ANY, Units_RotationAngles_Label, wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Type 40+

	Units_SearchRadius_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Search Radius ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_WorkRate_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Work Rate ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_DropSite_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Drop Site *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_TaskSwapID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Task Swap ID *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_AttackSound_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Attack Sound", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_MoveSound_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Move Sound", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Exists_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Exists", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Type 50+

	Units_DefaultArmor_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Default Armor *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_TerRestrictionForDmgMultiply_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Terrain Restriction *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_MaxRange_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Max Range", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_BlastWidth_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Blast Width *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ReloadTime1_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Reload Time", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ProjectileUnitID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Projectile Unit", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_AccuracyPercent_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Accuracy Percent", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Delay_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Frame Delay *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_GraphicDisplacement_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Graphic Displacement XYZ *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_BlastAttackLevel_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Blast Attack Level *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_MinRange_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Min Range", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_AccuracyDispersion_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Attack Dispersion *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_AttackGraphic_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Attack Graphic", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_DisplayedMeleeArmour_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Displayed Melee Armor", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_DisplayedAttack_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Displayed Attack", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_DisplayedRange_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Displayed Range", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ReloadTime2_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Displayed Reload Time", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Type 60 only

	Units_StretchMode_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Stretch Mode *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_SmartMode_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Smart Mode *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_DropAnimationMode_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Drop Animation Mode *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_PenetrationMode_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Penetration Mode *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown24_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 24 *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ProjectileArc_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Projectile Arc ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Type 70+

	Units_CostType_Text = new wxStaticText(Units_Scroller, wxID_ANY, "Type", wxDefaultPosition, wxSize(90, -1), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Units_CostAmount_Text = new wxStaticText(Units_Scroller, wxID_ANY, "Amount", wxDefaultPosition, wxSize(90, -1), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Units_CostUsed_Text = new wxStaticText(Units_Scroller, wxID_ANY, "Is Paid", wxDefaultPosition, wxSize(90, -1), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	Units_TrainTime_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Train Time", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_TrainLocationID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Train Location", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ButtonID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Train Button *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown26_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 26 ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown27_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 27 ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_UnknownType_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Creatable Type *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_GarrisonGraphic_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Garrison Graphic ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_MissileCount_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Total Projectiles *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_MissileDuplicationCount_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Max Total Projectiles *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_AttackMissileDuplicationSpawning_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Projectile Spawning Area *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_AttackMissileDuplicationUnit_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Secondary Projectile Unit *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ChargingGraphic_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Special Graphic *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ChargingMode_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Special Ability *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_DisplayedPierceArmour_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Displayed Pierce Armor ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Type 80

	Units_ConstructionGraphicID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Construction Graphic ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_SnowGraphicID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Snow Graphic ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_IconAngle_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Angle *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_StackUnitID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Stack Unit *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_TerrainID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Foundation Terrain *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_OldTerrainLikeID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Old Road *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ResearchID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Initiates Research *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown33_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 33 *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_AnnexUnit_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Annex Units", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_AnnexUnitMisplacement_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Annex Units Misplacement", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_HeadUnit_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Head Unit *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_TransformUnit_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Transform Unit *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_UnknownSound_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown Sound *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_ConstructionSound_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Construction Sound ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_GarrisonType_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Garrison Type *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_GarrisonHealRate_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Garrison Heal Rate *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_Unknown35_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 35 *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_PileUnit_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Pile Unit *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_LootSwitch_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Looting Table *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);

//	Data Containers

	Units_ID1 = AGETextCtrl::init(CShort, 0, this, &popUp, Tab_Units, AGETextCtrl::SMALL);
	Units_ID2 = AGETextCtrl::init(CShort, 0, this, &popUp, Tab_Units, AGETextCtrl::SMALL);
	Units_ID3 = AGETextCtrl::init(CShort, 0, this, &popUp, Tab_Units, AGETextCtrl::SMALL);
	Units_Name = AGETextCtrl::init(CString, &uiGroupUnit, this, &popUp, Tab_Units, 30);
	Units_Name2 = AGETextCtrl::init(CString, &uiGroupUnit, this, &popUp, Tab_Units, 30);
	Units_LanguageDLLName = AGETextCtrl::init(CUShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_LanguageDLLName->SetToolTip("Usual Unit File Pattern for The Conquerors\nName: 5000-5999\nCreation: Name +1000\nHotkey: Name +11000\nHelp: Name +100000, in File Name +21000\nHotkey Text: Name +150000, in File Name +10000\nTech tree: Name +9000");
	Units_DLL_LanguageName = new TextCtrl_DLL(Units_Scroller, wxSize(AGETextCtrl::GIANT, 25));
	Units_LanguageDLLCreation = AGETextCtrl::init(CUShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_DLL_LanguageCreation = new TextCtrl_DLL(Units_Scroller, wxSize(AGETextCtrl::GIANT, 25));
	Units_HotKey = AGETextCtrl::init(CLong, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_HotKey->SetToolTip("10000 + Language File Creation (usually)");
	Units_DLL_HotKey4 = new TextCtrl_DLL(Units_Scroller, wxSize(AGETextCtrl::GIANT, 25));
	Units_LanguageDLLHelp = AGETextCtrl::init(CLong, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_LanguageDLLHelp->SetToolTip("100000 + Language File Name\nThis is linked to the help text below");
	Units_LanguageDLLConverter[0] = new wxTextCtrl(Units_Scroller, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	Units_LanguageDLLConverter[0]->SetToolTip("Language help text in File\nHit enter to get the correction into dat file");
	Units_DLL_LanguageHelp = new TextCtrl_DLL(Units_Scroller, wxSize(610, 55));
	Units_LanguageDLLHotKeyText = AGETextCtrl::init(CLong, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_LanguageDLLHotKeyText->SetToolTip("150000 + Language File Name\nThis seems to be used only in AoE (not RoR)\nThis language line has other purposes in SWGB and CC");
	Units_LanguageDLLConverter[1] = new wxTextCtrl(Units_Scroller, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	Units_LanguageDLLConverter[1]->SetToolTip("Language hotkey text in File\nHit enter to get the correction into dat file");
	Units_DLL_LanguageHKText = new TextCtrl_DLL(Units_Scroller, wxSize(610, 25));

    wxArrayString choices;
    choices.Add("Stand 1");
    choices.Add("Stand 2");
    choices.Add("Dying 1");
    choices.Add("Dying 2");
    choices.Add("Walk");
    choices.Add("Run");
    choices.Add("Build");
    choices.Add("Attack");
    slp_radio = new wxRadioBox(Units_Scroller, wxID_ANY, "SLP view", wxDefaultPosition, wxDefaultSize, choices);
    slp_snow = new wxCheckBox(Units_Scroller, wxID_ANY, "Snow");
    slp_garrison = new wxCheckBox(Units_Scroller, wxID_ANY, "Housed");
    wxSizer *sizer_slp = new wxBoxSizer(wxHORIZONTAL);
    wxSizer *sizer_slp2 = new wxBoxSizer(wxVERTICAL);
	Units_DamageGraphics = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Damage Graphics");
	Units_DamageGraphics_ListArea = new wxBoxSizer(wxVERTICAL);
	Units_DamageGraphics_Search = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_DamageGraphics_Search_R = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_DamageGraphics_ListV = new AGEListView(Units_Scroller, wxSize(140, 100));
	Units_DamageGraphics_Buttons = new wxGridSizer(3, 0, 0);
	Units_DamageGraphics_Add = new wxButton(Units_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
	Units_DamageGraphics_Insert = new wxButton(Units_Scroller, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
	Units_DamageGraphics_Delete = new wxButton(Units_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
	Units_DamageGraphics_Copy = new wxButton(Units_Scroller, wxID_ANY, "Copy *", wxDefaultPosition, wxSize(10, -1));
	Units_DamageGraphics_Copy->SetToolTip("When \"All civs\" is not selected,\nthis and pasting works only for current civilization");
	Units_DamageGraphics_Paste = new wxButton(Units_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
	Units_DamageGraphics_PasteInsert = new wxButton(Units_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
	Units_DamageGraphics_CopyToUnits = new wxButton(Units_Scroller, wxID_ANY, "Copy all to selected units", wxDefaultPosition, wxSize(10, -1));
	Units_DamageGraphics_Holder_Data = new wxBoxSizer(wxVERTICAL);
    slp_dmg_unit = new wxCheckBox(Units_Scroller, wxID_ANY, "View damage graphics");
	DamageGraphics_GraphicID_Holder = new wxBoxSizer(wxVERTICAL);
	DamageGraphics_GraphicID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Graphic ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	DamageGraphics_GraphicID = AGETextCtrl::init(CShort, &uiGroupUnitDmgGraphic, this, &popUp, Units_Scroller);
	DamageGraphics_GraphicID_ComboBox = new ComboBox_Plus1(Units_Scroller, DamageGraphics_GraphicID);
	GraphicComboBoxList.push_back(DamageGraphics_GraphicID_ComboBox);
	DamageGraphics_DamagePercent_Holder = new wxBoxSizer(wxVERTICAL);
	DamageGraphics_DamagePercent_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Damage Percent ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	DamageGraphics_DamagePercent = AGETextCtrl::init(CByte, &uiGroupUnitDmgGraphic, this, &popUp, Units_Scroller);
	DamageGraphics_ApplyMode_Holder = new wxBoxSizer(wxVERTICAL);
	DamageGraphics_ApplyMode_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Old Unknown Mode *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	DamageGraphics_ApplyMode = AGETextCtrl::init(CByte, &uiGroupUnitDmgGraphic, this, &popUp, Units_Scroller);
	DamageGraphics_ApplyMode->SetToolTip("Replaced in memory by the 2nd Unknown Mode");
	DamageGraphics_Unknown2_Holder = new wxBoxSizer(wxVERTICAL);
	DamageGraphics_Unknown2_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown Mode *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	DamageGraphics_Unknown2 = AGETextCtrl::init(CByte, &uiGroupUnitDmgGraphic, this, &popUp, Units_Scroller);
	DamageGraphics_Unknown2->SetToolTip("Old false notes. This is not apply mode.\n0 Adds graphics on top (flames on buildings)\n1 Adds graphics on top randomly\n2 Replaces original graphics (damaged walls)");

	Units_IconID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
	Units_IconID->SetToolTip("Download Turtle Pack from AoKH to add more than 127 icons.");
    Units_IconID_SLP = new wxPanel(Units_Scroller, wxID_ANY, wxDefaultPosition, wxSize(55, 50));
	Units_IconAngle = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
	Units_IconAngle->SetToolTip("Tech attribute 17 changes this\n0 Default\n1+ Use icon from 2nd age etc\nIn AoE 1 can be used to set the unit\nhave icon graphics of later ages straight in stone age");
	Units_ChargingGraphic = AGETextCtrl::init(CLong, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_ChargingGraphic->SetToolTip("Activates depending on special ability");
	Units_ChargingGraphic_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_ChargingGraphic);
	GraphicComboBoxList.push_back(Units_ChargingGraphic_ComboBox);
	for(size_t loop = 0; loop < 2; ++loop)
	{
		Units_StandingGraphic[loop] = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
		Units_StandingGraphic[loop]->SetToolTip("Half of units in group use 1st,\nthe rest use 2nd");
		Units_StandingGraphic_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_StandingGraphic[loop]);
		GraphicComboBoxList.push_back(Units_StandingGraphic_ComboBox[loop]);
	}
	for(size_t loop = 0; loop < 2; ++loop)
	{
		Units_DyingGraphic[loop] = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
		Units_DyingGraphic_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_DyingGraphic[loop]);
		GraphicComboBoxList.push_back(Units_DyingGraphic_ComboBox[loop]);
	}
	for(size_t loop = 0; loop < 2; ++loop)
	{
		Units_WalkingGraphic[loop] = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
		Units_WalkingGraphic_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_WalkingGraphic[loop]);
		GraphicComboBoxList.push_back(Units_WalkingGraphic_ComboBox[loop]);
	}
	Units_SnowGraphicID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_SnowGraphicID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_SnowGraphicID);
	GraphicComboBoxList.push_back(Units_SnowGraphicID_ComboBox);
	Units_ConstructionGraphicID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_ConstructionGraphicID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_ConstructionGraphicID);
	GraphicComboBoxList.push_back(Units_ConstructionGraphicID_ComboBox);
	Units_AttackGraphic = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_AttackGraphic_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_AttackGraphic);
	GraphicComboBoxList.push_back(Units_AttackGraphic_ComboBox);
	Units_GarrisonGraphic = AGETextCtrl::init(CLong, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_GarrisonGraphic_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_GarrisonGraphic);
	GraphicComboBoxList.push_back(Units_GarrisonGraphic_ComboBox);

	Units_HitPoints = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_HitPoints->SetToolTip("-1 Instantly dying unit");
	Units_Speed = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_RotationSpeed = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_RotationSpeed->SetToolTip("Makes it slower");
	Units_LineOfSight = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_LineOfSight->SetToolTip("Maximum (effective) value is 20");
	Units_SearchRadius = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_MaxRange = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_MinRange = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_DisplayedRange = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);

	Units_Attacks = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Attacks");
	Units_Attacks_ListArea = new wxBoxSizer(wxVERTICAL);
	Units_Attacks_DataArea = new wxBoxSizer(wxVERTICAL);
	Units_Attacks_Search = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_Attacks_Search_R = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_Attacks_ListV = new AGEListView(Units_Scroller, wxSize(140, 100));
	Units_Attacks_Buttons = new wxGridSizer(3, 0, 0);
	Units_Attacks_Add = new wxButton(Units_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
	Units_Attacks_Insert = new wxButton(Units_Scroller, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
	Units_Attacks_Delete = new wxButton(Units_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
	Units_Attacks_Copy = new wxButton(Units_Scroller, wxID_ANY, "Copy *", wxDefaultPosition, wxSize(10, -1));
	Units_Attacks_Copy->SetToolTip("When \"All civs\" is not selected,\nthis and pasting works only for current civilization");
	Units_Attacks_Paste = new wxButton(Units_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
	Units_Attacks_PasteInsert = new wxButton(Units_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
	Units_Attacks_CopyToUnits = new wxButton(Units_Scroller, wxID_ANY, "Copy all to selected units", wxDefaultPosition, wxSize(10, -1));
	Units_Attacks_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_Attacks_Holder_Data = new wxWrapSizer();
	Attacks_Amount_Holder = new wxBoxSizer(wxVERTICAL);
	Attacks_Amount_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Amount", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Attacks_Amount = AGETextCtrl::init(CShort, NULL, this, &popUp, Units_Scroller);
	Attacks_Class_Holder = new wxBoxSizer(wxVERTICAL);
	Attacks_Class_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Type *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Attacks_Class = AGETextCtrl::init(CShort, NULL, this, &popUp, Units_Scroller);
	Attacks_Class->SetToolTip("Armor class that this unit can damage\nYou can make your own classes");
	Attacks_Class_ComboBox[0] = new ComboBox_Plus1(Units_Scroller, Attacks_Class);

	Units_DisplayedAttack = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_Delay = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_Delay->SetToolTip("Graphical delay in frames before projectile is shot");
	Units_AccuracyPercent = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_AccuracyDispersion = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_AccuracyDispersion->SetToolTip("Width multiplier of the rectangle where the projectiles may hit.\nHigher values will make the unit less accurate.");
	Units_ReloadTime1 = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_ReloadTime2 = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_BlastWidth = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_BlastWidth->SetToolTip("If object has 0 blast radius\nand does not hit the unit it had targeted\nalways does half damage");
	Units_BlastAttackLevel = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_BlastAttackLevel->SetToolTip("Blasts damage units that have higher or same blast armor level\n0 Damages resources also\n1 Damages trees also\n2 Damages nearby units\n3 Damages only targeted unit");

	Units_Armors = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Armors");
	Units_Armors_ListArea = new wxBoxSizer(wxVERTICAL);
	Units_Armors_DataArea = new wxBoxSizer(wxVERTICAL);
	Units_Armors_Search = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_Armors_Search_R = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_Armors_ListV = new AGEListView(Units_Scroller, wxSize(140, 100));
	Units_Armors_Buttons = new wxGridSizer(3, 0, 0);
	Units_Armors_Add = new wxButton(Units_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
	Units_Armors_Insert = new wxButton(Units_Scroller, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
	Units_Armors_Delete = new wxButton(Units_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
	Units_Armors_Copy = new wxButton(Units_Scroller, wxID_ANY, "Copy *", wxDefaultPosition, wxSize(10, -1));
	Units_Armors_Copy->SetToolTip("When \"All civs\" is not selected,\nthis and pasting works only for current civilization");
	Units_Armors_Paste = new wxButton(Units_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
	Units_Armors_PasteInsert = new wxButton(Units_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
	Units_Armors_CopyToUnits = new wxButton(Units_Scroller, wxID_ANY, "Copy all to selected units", wxDefaultPosition, wxSize(10, -1));
	Units_Armors_Holder = new wxBoxSizer(wxHORIZONTAL);
	Units_Armors_Holder_Data3 = new wxBoxSizer(wxVERTICAL);
	Armors_Amount_Holder = new wxBoxSizer(wxVERTICAL);
	Armors_Amount_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Amount", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Armors_Amount = AGETextCtrl::init(CShort, NULL, this, &popUp, Units_Scroller);
	Armors_Class_Holder = new wxBoxSizer(wxVERTICAL);
	Armors_Class_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Type *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Armors_Class = AGETextCtrl::init(CShort, NULL, this, &popUp, Units_Scroller);
	Armors_Class->SetToolTip("Attack class from which this unit can take damage\nYou can make your own classes");
	Attacks_Class_ComboBox[1] = new ComboBox_Plus1(Units_Scroller, Armors_Class);

	Units_DefaultArmor = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_DefaultArmor->SetToolTip("This armor is used for all attack types that do not have corresponding armor type\nCan be negative only in The Conquerors and later games");
	Units_TerRestrictionForDmgMultiply = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_TerRestrictionForDmgMultiply->SetToolTip("Receive damage based on which terrain this unit stands on\nTech attribute 18 changes this\nThe damage received by this unit is\nmultiplied by the accessible values on\nthe specified terrain restriction");
	Units_TerRestrictionForDmgMultiply_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_TerRestrictionForDmgMultiply);
	TerrainRestrictionComboBoxList.push_back(Units_TerRestrictionForDmgMultiply_ComboBox);
	Units_DisplayedMeleeArmour = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_DisplayedPierceArmour = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_BlastDefenseLevel = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_BlastDefenseLevel->SetToolTip("Receive blast damage from units that have lower or same blast attack level");

	Units_ResourceCapacity = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_ResourceDecay = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_ResourceDecay->SetToolTip("Can alter corpses' decay time\nSet to -1 for never decaying");
	Units_WorkRate = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_GarrisonCapacity = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_GarrisonCapacity->SetToolTip("If the unit has garrisoned units inside,\ngraphics tab \"New Speed?\" determines its new speed?");
	Units_GarrisonType = AGETextCtrl::init(CUByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_GarrisonType->SetToolTip("You can garrison any type,\nif you add the garrison action targeting this class/unit,\nbut you may need to hold the alt key while choosing to garrison.");
	Units_GarrisonType_Grid = new wxBoxSizer(wxHORIZONTAL);
	for(size_t loop = 0; loop < 8; ++loop)
	Units_GarrisonType_CheckBox[loop] = new wxCheckBox(Units_Scroller, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(15, -1));
	Units_GarrisonType_CheckBox[0]->SetToolTip("Villager/Worker");
	Units_GarrisonType_CheckBox[1]->SetToolTip("Infantry");
	Units_GarrisonType_CheckBox[2]->SetToolTip("Cavalry/Mounted");
	Units_GarrisonType_CheckBox[3]->SetToolTip("Monk/Jedi");
	Units_GarrisonType_CheckBox[4]->SetToolTip("SW: Livestock");
	Units_GarrisonHealRate = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_GarrisonHealRate->SetToolTip("Building's garrisoned units' healing speed factor");

	Units_ProjectileUnitID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_ProjectileUnitID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_ProjectileUnitID);
	UnitComboBoxList.push_back(Units_ProjectileUnitID_ComboBox);
	Units_AttackMissileDuplicationUnit = AGETextCtrl::init(CLong, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_AttackMissileDuplicationUnit->SetToolTip("Uses its own attack values!");
	Units_AttackMissileDuplicationUnit_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_AttackMissileDuplicationUnit);
	UnitComboBoxList.push_back(Units_AttackMissileDuplicationUnit_ComboBox);
	Units_MissileCount = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_MissileCount->SetToolTip("Total missiles including both normal and duplicated projectiles");
	Units_MissileDuplicationCount = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_MissileDuplicationCount->SetToolTip("Total missiles when garrison capacity is full");
	for(size_t loop = 0; loop < 3; ++loop)
	Units_AttackMissileDuplicationSpawning[loop] = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_AttackMissileDuplicationSpawning[0]->SetToolTip("Spawning area's width");
	Units_AttackMissileDuplicationSpawning[1]->SetToolTip("Spawning area's length");
	Units_AttackMissileDuplicationSpawning[2]->SetToolTip("Spawning point's randomness inside the spawning area\n0 from a single spot\n1 Totally randomly inside the spawning area\n1+ Less randomly");
	for(size_t loop = 0; loop < 3; ++loop)
	Units_GraphicDisplacement[loop] = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_GraphicDisplacement[0]->SetToolTip("Left/Right distance");
	Units_GraphicDisplacement[1]->SetToolTip("Spawning distance from the unit");
	Units_GraphicDisplacement[2]->SetToolTip("Height");

	Units_StretchMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_StretchMode->SetToolTip("0 Default\n1 Projectile falls vertically to the bottom of the map\n3 Teleporting projectiles");
	Units_SmartMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_SmartMode->SetToolTip("Tech attribute 19 changes this\n0 Shoot where the target is now\n1 Shoot where the target is going to be");
	Units_DropAnimationMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_DropAnimationMode->SetToolTip("0 Doesn't disappear after hitting the target\n1 Disappears\n2 SWGB artillery fire has this");
	Units_PenetrationMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_PenetrationMode->SetToolTip("0 Stops the graphics\n1 Graphics pass through the target instead of stopping\nOnly affects the graphics of the projectile");
	Units_Unknown24 = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_Unknown24->SetToolTip("Bullets have this as 1");
	Units_ProjectileArc = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);

	Units_Enabled = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
	Units_Enabled->SetToolTip("0 Requires a research to be available\n1 Available without a research");
	Units_Enabled_CheckBox = new CheckBox_2State(Units_Scroller, "Available *", Units_Enabled);
	Units_Disabled = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
	Units_Disabled->SetToolTip("Not scanned but set to 0\nProbably changes during gameplay\n0 Default\n1 Prevents enabling/disabling with a tech");
	Units_Disabled_CheckBox = new CheckBox_2State(Units_Scroller, "Disabled *", Units_Disabled);
	Units_DeathMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
	Units_DeathMode->SetToolTip("Upon death instead of transforming into dead unit,\nthe unit plays its idle animation");
	Units_DeathMode_CheckBox = new CheckBox_2State(Units_Scroller, "No Dead Unit *", Units_DeathMode);
	Units_HideInEditor = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
	Units_HideInEditor->SetToolTip("Possible values: 0, 1 and as boolean");
	Units_HideInEditor_CheckBox = new CheckBox_2State(Units_Scroller, "Hide in Editor", Units_HideInEditor);
	Units_AirMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
	Units_AirMode->SetToolTip("0 Default\n1 Graphic stays at higest elevation until destination is reached\n2+ Graphic is not affected by elevation");
	Units_AirMode_CheckBox = new CheckBox_2State(Units_Scroller, "Air Mode *", Units_AirMode);
	Units_FlyMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
	Units_FlyMode->SetToolTip("Requires class 22 and air mode 1?\n0 Normal\n1 Graphics appear higher than the shadow");
	Units_FlyMode_CheckBox = new CheckBox_2State(Units_Scroller, "Fly Mode *", Units_FlyMode);
	Units_AnimalMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
	Units_AnimalMode_CheckBox = new CheckBox_2State(Units_Scroller, "Animal Mode", Units_AnimalMode);
	Units_TowerMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
	Units_TowerMode_CheckBox = new CheckBox_2State(Units_Scroller, "Tower Mode", Units_TowerMode);
	Units_AdjacentMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
	Units_AdjacentMode->SetToolTip("0 Default\n1 Adjacent buildings can change this unit's graphics\nThis changes the graphic angle");
	Units_AdjacentMode_CheckBox = new CheckBox_2State(Units_Scroller, "Adjacent Mode *", Units_AdjacentMode);
	Units_DisappearsWhenBuilt = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
	Units_DisappearsWhenBuilt->SetToolTip("Useful for stack unit placement\n0 Default\n1 Makes the building disappear when built");
	Units_Unknown31b_CheckBox = new CheckBox_2State(Units_Scroller, "Built: Vanishes *", Units_DisappearsWhenBuilt);
	Units_HeroMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
	Units_HeroMode_CheckBox = new CheckBox_2State(Units_Scroller, "Hero Mode", Units_HeroMode);

	Units_PlacementMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_PlacementMode->SetToolTip("Seems to be obsolete, ignore these clues:\n0 Can be placed on top of other units in scenario editor\n5 Cannot be placed on top of other units in scenario editor");
	Units_HillMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_HillMode->SetToolTip("0 No restriction\n1 Cannot place on corners of hills\n2 Can only place on flat land\n3 Allows one elevation difference");
	Units_VisibleInFog_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Fog Visibility *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_VisibleInFog = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_VisibleInFog->SetToolTip("0 Not visible\n1 Visible (acts as boolean unless it is 3)\n3 Inverted visibility");
	Units_SubType = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_SubType->SetToolTip("Mainly used in trigger conditions\n0 Projectile/Dead/Resource\n1 Boar\n2 Building\n3 Civilian\n4 Military\n5 Priest\n");
	Units_InteractionMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_InteractionMode->SetToolTip("0 & 1 Unable to select, move or attack\n2 Can select, unable to move or attack\n3 Can select and attack, unable to move\n4 Can select, move and attack\n5+ Select and move?");
	Units_MinimapMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_MinimapMode->SetToolTip("0 & 5+ No dot on minimap\n1 Square dot turning white when selected\n2 Diamond dot turning white when selected\n3 Diamond dot keeping color\n4 Larger spot, not following the unit, no blinking when attacked, everyone can see it\n");
	Units_MinimapColor = AGETextCtrl::init(CUByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_MinimapColor->SetToolTip("Minimap modes 3 and 4 allow this to work");
	Units_Unknown6 = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_Unknown6->SetToolTip("Seems to be 1 on all resource deposits");
	Units_Unknown7 = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_Unknown7->SetToolTip("0 Default\n1 Resource/Eye Candy\n2 Tree");
	Units_Unknown8 = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_Unknown8->SetToolTip("0 wood?\n1 berry\n2 fish\n3 stone/ore deposit\n4 gold/nova deposit\n5 ore (not SW) deposit?");
	Units_AttackMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_AttackMode->SetToolTip("Seems to be obsolete\nCopied when converting the unit\nThis may be attack mode\n0 No attacck\n1 Attack by following\n2 Run when attacked\n3 ?\n4 Attack\n");
	Units_Unknown10 = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_Unknown10->SetToolTip("Seems to be obsolete\nCopied when converting the unit\n0 Default\n1 Rotting meat that can be gathered");
	Units_TaskSwapID = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_TaskSwapID->SetToolTip("When tasking the unit, it will transform into another unit,\nif the action is not found in this unit, but exists on another unit,\nthat shares the same task swap index.\nChanges according to task\n1 Male villager\n2 Female villager\n3+ Free slots");
	Units_UnknownType = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_UnknownType->SetToolTip("0 building, animal, ship\n1 villager, king\n2 soldier, siege, predator, trader\n3 mounted unit\n4 relic\n5 archer\n6 monk\n21 transport ship");
	Units_ChargingMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_ChargingMode->SetToolTip("0 Default\nThese work only when facing the hit angle.\n1 Block\n  Activates special graphic when receiving damage and not pursuing the attacker.\n  While idle, blocking decreases damage taken by 1/3.\n2 Counter Charge\n  Activates special graphic when idle and enemy is near.\n  While idle, attacks back once on first received hit.\n  Enemy must be unit type 70 and have less than 0.2 max range.\n3 Charge\n  Activates special graphic when closer than two tiles to the target.\n  Deals 2X damage on 1st hit.");

	Units_Attribute = AGETextCtrl::init(CUByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_Attribute->SetToolTip("This is a byte of eight booleans\nYou can combine these attributes");
	Units_Attribute_Grid = new wxBoxSizer(wxHORIZONTAL);
	for(size_t loop = 0; loop < 8; ++loop)
	Units_Attribute_CheckBox[loop] = new wxCheckBox(Units_Scroller, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(15, -1));
	Units_Attribute_CheckBox[0]->SetToolTip("Garrison unit");
	Units_Attribute_CheckBox[1]->SetToolTip("Ship unit");
	Units_Attribute_CheckBox[2]->SetToolTip("SW: Stealth unit");
	Units_Attribute_CheckBox[3]->SetToolTip("SW: Detector unit");
	Units_Attribute_CheckBox[4]->SetToolTip("SW: Mechanical unit");
	Units_Attribute_CheckBox[5]->SetToolTip("SW: Biological unit");
	Units_Attribute_CheckBox[6]->SetToolTip("SW: Self-shielding unit");
	Units_Attribute_CheckBox[7]->SetToolTip("SW: Invisible unit");
	Units_Civ = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_Civ_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_Civ);
	CivComboBoxList.push_back(Units_Civ_ComboBox);
	Units_Nothing = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_Nothing->SetToolTip("This is actually leftover from attribute+civ variable\nProbably useless");
	Units_DeadUnitID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_DeadUnitID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_DeadUnitID);
	UnitComboBoxList.push_back(Units_DeadUnitID_ComboBox);
	Units_Unitline = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_Unitline_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_Unitline);
	Units_MinTechLevel = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_MinTechLevel_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_MinTechLevel);
	ResearchComboBoxList.push_back(Units_MinTechLevel_ComboBox);
	for(size_t loop = 0; loop < 2; ++loop)
	{
		Units_PlacementTerrain[loop] = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
		Units_PlacementTerrain_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_PlacementTerrain[loop]);
		TerrainComboBoxList.push_back(Units_PlacementTerrain_ComboBox[loop]);
	}
	for(size_t loop = 0; loop < 2; ++loop)
	{
		Units_PlacementSideTerrain[loop] = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
		Units_PlacementSideTerrain[loop]->SetToolTip("Required terrain on some side");
		Units_PlacementSideTerrain_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_PlacementSideTerrain[loop]);
		TerrainComboBoxList.push_back(Units_PlacementSideTerrain_ComboBox[loop]);
	}
	Units_TerrainRestriction = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_TerrainRestriction_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_TerrainRestriction);
	TerrainRestrictionComboBoxList.push_back(Units_TerrainRestriction_ComboBox);
	Units_TerrainID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_TerrainID->SetToolTip("Terrain produced under a building when completed");
	Units_TerrainID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_TerrainID);
	TerrainComboBoxList.push_back(Units_TerrainID_ComboBox);
	Units_OldTerrainLikeID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_OldTerrainLikeID->SetToolTip("ES forgot to remove this before AoE was released.\nThis points to removed data block\nthat was like terrain borders.\nYou could build roads back in 1996.");
	Units_ResearchID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_ResearchID->SetToolTip("Causes that research to be researched when the building is created");
	Units_ResearchID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_ResearchID);
	ResearchComboBoxList.push_back(Units_ResearchID_ComboBox);
    Units_ActionWhenDiscoveredID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Action When Discovered *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
    Units_ActionWhenDiscoveredID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_ActionWhenDiscoveredID->SetToolTip("When this unit is met by some player unit\nthe unit action ID specified here will be executed.\nTo get the unit auto-converted to enemy,\nuse unit command 107, which sheep and monument have\nAll somehow auto-convertible units have this set to 0\nMost other units have -1");
    Units_ActionWhenDiscoveredID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_ActionWhenDiscoveredID);
	for(size_t loop = 0; loop < 2; ++loop)
	{
		Units_DropSite[loop] = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
		Units_DropSite[loop]->SetToolTip("Giving a villager's drop site to a cart-like unit\ncan allow you to have mobile resource-gatherers,\nsimilar to those in Age of Mythology.");
		Units_DropSite_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_DropSite[loop]);
		UnitComboBoxList.push_back(Units_DropSite_ComboBox[loop]);
	}

	for(size_t loop = 0; loop < 2; ++loop)
	Units_SizeRadius[loop] = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
	for(size_t loop = 0; loop < 2; ++loop)
	Units_ClearanceSize[loop] = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_SelectionRadiusBox = new wxBoxSizer(wxHORIZONTAL);
	for(size_t loop = 0; loop < 2; ++loop)
	Units_SelectionRadius[loop] = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_HPBarHeight1 = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_HPBarHeight1->SetToolTip("Setting \"Air Mode\" to 1 and this to 0 causes farms to be walkable in AoE/RoR.");
	Units_HPBarHeight2 = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_HPBarHeight2->SetToolTip("Determines HP bar location\nVertical half tile (elevation height?) distance from the top corner?");

	Units_Unselectable = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_Unselectable->SetToolTip("Not scanned but set to 0\nProbably changes during gameplay");
	Units_Unselectable_CheckBox = new CheckBox_2State(Units_Scroller, "Unselectable *", Units_Unselectable);
	Units_SelectionMask = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_SelectionMask->SetToolTip("Any odd value except 7 - Mask displayed behind buildings\nAny even value except 6, 10 - Mask not displayed\n-1, 7 - Mask partially displayed when in the open\n6, 10 - Building, causes mask to appear on units behind it\n");
	Units_SelectionShapeType = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_SelectionShapeType->SetToolTip("Seems to control 3 things\nIf square or round, value 5\nIf real size or selection size is used, value 2\nIf walkable or not, value 0");
	Units_SelectionShape = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_SelectionShape->SetToolTip("0 Square\n1+ Round");
	Units_SelectionEffect = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_SelectionEffect->SetToolTip("0\n1 HP Bar on, permanent darker outline in editor only\n4 HP Bar off, normal outline\n5, 8-9 HP Bar on\n2 HP Bar on, normal outline\n3 HP Bar off, selection shadow\n6-7 HP Bar off\nNote: this doesn't work with all units");
	Units_EditorSelectionColour = AGETextCtrl::init(CUByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_EditorSelectionColour->SetToolTip("0 most\n-16 fish trap farm\n52 dead farm, OLD-(___)\n116 flare, WHAL1, WHAL2, DOLP, Great-fish\n-123 all fish");
	Units_TrackingUnit = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_TrackingUnit_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_TrackingUnit);
	UnitComboBoxList.push_back(Units_TrackingUnit_ComboBox);
	Units_TrackingUnitUsed = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_TrackingUnitUsed->SetToolTip("0 Not used\n1 Appears while moving and at the start of the game\n2 Appears while moving");
	Units_TrackingUnitDensity = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_TrackingUnitDensity->SetToolTip("0 unless tracking unit value is present\n0.5 trade carts\n0.12 MFFFG(projectile)\n0.4 other projectiles");
	for(size_t loop = 0; loop < Units_RotationAngles.size(); ++loop)
	Units_RotationAngles[loop] = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
	wxString rot360 = "360 degrees when multiplying with 4th box radian value";
	Units_RotationAngles[2]->SetToolTip(rot360);
	Units_RotationAngles[3]->SetToolTip("Used to get 3rd and 5th box to 360 degrees");
	Units_RotationAngles[4]->SetToolTip(rot360);
	Units_CommandID = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_CommandID->SetToolTip("Class and this sets the interface for this unit\n0 Flag\n1 Livestock\n2 Civilian Building (build page 1)\n3 Villager\n4 Military Unit\n5 Trade Unit\n6 Monk\n7 Transport Ship\n8 Relic / Monk with Relic\n9 Fishing Ship\n10 Military Building (build page 2)\n11 Shield Building (build page 3)");
	Units_TrainTime = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_TrainLocationID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_TrainLocationID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_TrainLocationID);
	UnitComboBoxList.push_back(Units_TrainLocationID_ComboBox);
	Units_ButtonID = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_ButtonID->SetToolTip("First page (also second in TC) 1-15\nSecond (dock) page 21-35\nThird page same as first (Star Wars)\nFirst page in AoE/RoR 1-10\nSecond page in AoE/RoR 11-20");
	for(size_t loop = 0; loop < 3; ++loop)
	{
		ResourceStorage_Type[loop] = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
		ResourceStorage_Type_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, ResourceStorage_Type[loop]);
		ResourceComboBoxList.push_back(ResourceStorage_Type_ComboBox[loop]);
		ResourceStorage_Amount[loop] = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
		ResourceStorage_Enabled[loop] = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
		ResourceStorage_Enabled[loop]->SetToolTip("0 Decayable resource\n1 Stored after death also\n2 Resets on dying, enables instantly\n4 Resets on dying, enables on completion\nUP: 8 Stored on completion and stays after death");
	}
	for(size_t loop = 0; loop < 3; ++loop)
	{
		Units_CostType[loop] = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
		Units_CostType_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_CostType[loop]);
		ResourceComboBoxList.push_back(Units_CostType_ComboBox[loop]);
		Units_CostAmount[loop] = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
		Units_CostUsed[loop] = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
		Units_CostUsed[loop]->SetToolTip("If set to 0 and there is an amount, the amount is required but not paid");
		Units_CostUsed_CheckBox[loop] = new CheckBox_2State(Units_Scroller, "Paid", Units_CostUsed[loop]);
	}
	Units_StackUnitID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_StackUnitID->SetToolTip("Second building to be placed directly on top of this building\nAdditional building gets added every time you load the scenario");
	Units_StackUnitID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_StackUnitID);
	UnitComboBoxList.push_back(Units_StackUnitID_ComboBox);
	Units_HeadUnit = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_HeadUnit->SetToolTip("The building that an annex building is attached to");
	Units_HeadUnit_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_HeadUnit);
	UnitComboBoxList.push_back(Units_HeadUnit_ComboBox);
	Units_TransformUnit = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_TransformUnit->SetToolTip("Determines what the unit changes into when given the order to unpack");
	Units_TransformUnit_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_TransformUnit);
	UnitComboBoxList.push_back(Units_TransformUnit_ComboBox);
	Units_PileUnit = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_PileUnit->SetToolTip("Appears when the building dies\nDoes not appear with delete command");
	Units_PileUnit_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_PileUnit);
	UnitComboBoxList.push_back(Units_PileUnit_ComboBox);
	for(size_t loop = 0; loop < 4; ++loop)
	{
		Units_AnnexUnit[loop] = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
		Units_AnnexUnit_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_AnnexUnit[loop]);
		UnitComboBoxList.push_back(Units_AnnexUnit_ComboBox[loop]);
	}
	for(size_t loop = 0; loop < 4; ++loop)
	{
		for(size_t loop2 = 0; loop2 < 2; ++loop2)
		Units_AnnexUnitMisplacement[loop][loop2] = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::LARGE);
	}
	for(size_t loop = 0; loop < Units_LootSwitch.size(); ++loop)
	Units_LootSwitch[loop] = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
	Units_LootSwitch[0]->SetToolTip("Stone Loot Switch");
	Units_LootSwitch[1]->SetToolTip("Wood Loot Switch");
	Units_LootSwitch[2]->SetToolTip("Ore Loot Switch");
	Units_LootSwitch[3]->SetToolTip("Gold Loot Switch");
	Units_LootSwitch[4]->SetToolTip("Food Loot Switch");
	Units_LootSwitch[5]->SetToolTip("Goods Loot Switch");

	Units_SelectionSound = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_SelectionSound_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_SelectionSound);
	SoundComboBoxList.push_back(Units_SelectionSound_ComboBox);
	Units_DyingSound = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_DyingSound_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_DyingSound);
	SoundComboBoxList.push_back(Units_DyingSound_ComboBox);
	for(size_t loop = 0; loop < 2; ++loop)
	{
		Units_TrainSound[loop] = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
		Units_TrainSound_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_TrainSound[loop]);
		SoundComboBoxList.push_back(Units_TrainSound_ComboBox[loop]);
	}
	Units_AttackSound = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_AttackSound_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_AttackSound);
	SoundComboBoxList.push_back(Units_AttackSound_ComboBox);
	Units_MoveSound = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_MoveSound_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_MoveSound);
	SoundComboBoxList.push_back(Units_MoveSound_ComboBox);
	Units_ConstructionSound = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_ConstructionSound_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_ConstructionSound);
	SoundComboBoxList.push_back(Units_ConstructionSound_ComboBox);
	Units_UnknownSound = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_UnknownSound->SetToolTip("Possibly related to transforming");
	Units_UnknownSound_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_UnknownSound);
	SoundComboBoxList.push_back(Units_UnknownSound_ComboBox);

	Units_Unknown1 = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_Unknown3A = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_Unknown3A->SetToolTip("Seems to be 1 on more or less living things\nProbably the old population counter");

	Units_Unknown11 = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_Unknown16 = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);

	Units_Unknown26 = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_Unknown27 = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);

	Units_Unknown33 = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_Unknown33->SetToolTip("Seems to be obsolete\nWas possibly related to annexes");
	Units_Unknown35 = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
	Units_Unknown35->SetToolTip("Seems to be obsolete\nWas probably related to garrisoning");

	Units_CommandHolder_Lists = new wxBoxSizer(wxVERTICAL);
	Units_UnitHeads_Name = new wxStaticText(Units_Scroller, wxID_ANY, "Unit Header", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	Units_UnitCommands_Search = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_UnitCommands_Search_R = new wxTextCtrl(Units_Scroller, wxID_ANY);
	Units_UnitCommands_ListV = new AGEListView(Units_Scroller, wxSize(140, 190));
	Units_UnitCommands_Buttons = new wxGridSizer(3, 0, 0);
	Units_UnitCommands_Add = new wxButton(Units_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
	Units_UnitCommands_Insert = new wxButton(Units_Scroller, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
	Units_UnitCommands_Delete = new wxButton(Units_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
	Units_UnitCommands_Copy = new wxButton(Units_Scroller, wxID_ANY, "Copy *", wxDefaultPosition, wxSize(10, -1));
	Units_UnitCommands_Copy->SetToolTip("When \"All civs\" is not selected,\nthis and pasting works only for current civilization");
	Units_UnitCommands_Paste = new wxButton(Units_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
	Units_UnitCommands_PasteInsert = new wxButton(Units_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
	Units_UnitCommands_CopyToUnits = new wxButton(Units_Scroller, wxID_ANY, "Copy all to selected units", wxDefaultPosition, wxSize(10, -1));
	Units_CommandHolder_Data = new wxBoxSizer(wxVERTICAL);
	Unit_Command_Known = new wxWrapSizer();
	Unit_Command_Unknowns = new wxWrapSizer();
	Units_Exists = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    wxArrayString action_choices;
    action_choices.Add("None");
    action_choices.Add("Tool");
    action_choices.Add("Proceed");
    action_choices.Add("Action");
    action_choices.Add("Carry");
    slp_unit_actions = new wxRadioBox(Units_Scroller, wxID_ANY, "SLP view", wxDefaultPosition, wxDefaultSize, action_choices, 0, wxVERTICAL);

	UnitCommands_One_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_One_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Enabled ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_One = AGETextCtrl::init(CShort, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
	UnitCommands_ID_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_ID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " ID ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_ID = AGETextCtrl::init(CShort, 0, this, &popUp, Units_Scroller);
	UnitCommands_Type_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Type_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Action Type", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Type = AGETextCtrl::init(CShort, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
	UnitCommands_Type_ComboBox = new AGEODComboBox(Units_Scroller, AGETextCtrl::GIANT);
	UnitCommands_ClassID_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_ClassID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Class", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_ClassID = AGETextCtrl::init(CShort, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
	Units_Class_ComboBox[1] = new ComboBox_Plus1(Units_Scroller, UnitCommands_ClassID);
	UnitCommands_UnitID_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_UnitID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unit", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_UnitID = AGETextCtrl::init(CShort, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
	UnitCommands_UnitID_ComboBox = new ComboBox_Plus1(Units_Scroller, UnitCommands_UnitID);
	UnitComboBoxList.push_back(UnitCommands_UnitID_ComboBox);
	UnitCommands_TerrainID_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_TerrainID_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Terrain", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_TerrainID = AGETextCtrl::init(CShort, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
    UnitCommands_TerrainID_ComboBox = new ComboBox_Plus1(Units_Scroller, UnitCommands_TerrainID);
	TerrainComboBoxList.push_back(UnitCommands_TerrainID_ComboBox);
	UnitCommands_ResourceIn_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_ResourceIn_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Resource In *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_ResourceIn = AGETextCtrl::init(CShort, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
	UnitCommands_ResourceIn->SetToolTip("Carry resource");
	UnitCommands_ResourceIn_ComboBox = new ComboBox_Plus1(Units_Scroller, UnitCommands_ResourceIn);
	ResourceComboBoxList.push_back(UnitCommands_ResourceIn_ComboBox);
	UnitCommands_ProductivityResource_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_ProductivityResource_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Productivity Resource *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_ProductivityResource = AGETextCtrl::init(CShort, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
	UnitCommands_ProductivityResource->SetToolTip("Resource that multiplies the amount you can gather");
	UnitCommands_ProductivityResource_ComboBox = new ComboBox_Plus1(Units_Scroller, UnitCommands_ProductivityResource);
	ResourceComboBoxList.push_back(UnitCommands_ProductivityResource_ComboBox);
	UnitCommands_ResourceOut_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_ResourceOut_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Resource Out *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_ResourceOut = AGETextCtrl::init(CShort, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
	UnitCommands_ResourceOut->SetToolTip("Drop resource");
	UnitCommands_ResourceOut_ComboBox = new ComboBox_Plus1(Units_Scroller, UnitCommands_ResourceOut);
	ResourceComboBoxList.push_back(UnitCommands_ResourceOut_ComboBox);
	UnitCommands_Resource_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Resource_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Resource", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Resource = AGETextCtrl::init(CShort, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
	UnitCommands_Resource_ComboBox = new ComboBox_Plus1(Units_Scroller, UnitCommands_Resource);
	ResourceComboBoxList.push_back(UnitCommands_Resource_ComboBox);
	UnitCommands_WorkRateMultiplier_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_WorkRateMultiplier_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Quantity", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_WorkRateMultiplier = AGETextCtrl::init(CFloat, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
	UnitCommands_ExecutionRadius_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_ExecutionRadius_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Execution Radius", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_ExecutionRadius = AGETextCtrl::init(CFloat, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
	UnitCommands_ExtraRange_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_ExtraRange_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Extra Range", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_ExtraRange = AGETextCtrl::init(CFloat, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
	for(size_t loop = 0; loop < UnitCommands_Graphics.size(); ++loop)
	{
		UnitCommands_Graphics_Holder[loop] = new wxBoxSizer(wxVERTICAL);
		UnitCommands_Graphics[loop] = AGETextCtrl::init(CShort, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
		UnitCommands_Graphics_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, UnitCommands_Graphics[loop]);
	}
	for(size_t loop = 0; loop < 4; ++loop)
	GraphicComboBoxList.push_back(UnitCommands_Graphics_ComboBox[loop]);
	for(size_t loop = 4; loop < 6; ++loop)
	SoundComboBoxList.push_back(UnitCommands_Graphics_ComboBox[loop]);
	UnitCommands_Graphics_Text[0] = new wxStaticText(Units_Scroller, wxID_ANY, " Tool Graphic *");
	UnitCommands_Graphics[0]->SetToolTip("Used when walking with a tool, but carrying no resources");
	UnitCommands_Graphics_Text[1] = new wxStaticText(Units_Scroller, wxID_ANY, " Proceeding Graphic *");
	UnitCommands_Graphics[1]->SetToolTip("Used when proceeding to gather a resource or attack");
	UnitCommands_Graphics_Text[2] = new wxStaticText(Units_Scroller, wxID_ANY, " Action Graphic *");
	UnitCommands_Graphics[2]->SetToolTip("Used when actually gathering a resource or attacking/converting");
	UnitCommands_Graphics_Text[3] = new wxStaticText(Units_Scroller, wxID_ANY, " Carrying Graphic *");
	UnitCommands_Graphics[3]->SetToolTip("Used when carrying a resource");
	UnitCommands_Graphics_Text[4] = new wxStaticText(Units_Scroller, wxID_ANY, " Execution Sound *");
	UnitCommands_Graphics[4]->SetToolTip("Example: Plays when lumberjack starts chopping wood");
	UnitCommands_Graphics_Text[5] = new wxStaticText(Units_Scroller, wxID_ANY, " Resource Deposit Sound *");
	UnitCommands_Graphics[5]->SetToolTip("Example: Plays when lumberjack drops his wood into TC");
	UnitCommands_Unknown1_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Unknown1_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 1", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown1 = AGETextCtrl::init(CByte, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
	UnitCommands_Unknown4_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Unknown4_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 4", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown4 = AGETextCtrl::init(CByte, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
	UnitCommands_Unknown5_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Unknown5_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Scaring Radius", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown5 = AGETextCtrl::init(CFloat, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
	UnitCommands_SelectionEnabler_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_SelectionEnabler_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Selection Enabler *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_SelectionEnabler = AGETextCtrl::init(CByte, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
	UnitCommands_SelectionEnabler->SetToolTip("1 Allows units to select their targets\n2 ?");
	UnitCommands_Unknown7_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Unknown7_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 7", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown7 = AGETextCtrl::init(CByte, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
	UnitCommands_Unknown8_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Unknown8_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Plunder Source *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown8 = AGETextCtrl::init(CShort, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
	UnitCommands_Unknown8->SetToolTip("0 Plunder from resource\n1 Plunder from players\n2 Raider thing?");
	UnitCommands_Unknown9_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Unknown9_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 9", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown9 = AGETextCtrl::init(CShort, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
	UnitCommands_SelectionMode_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_SelectionMode_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Selection Mode *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_SelectionMode = AGETextCtrl::init(CByte, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
	UnitCommands_SelectionMode->SetToolTip("Determines what you can select as targets\n0, 7+ All objects\n1 Your objects only\n2 Neutral and enemy objects only\n3 Gaia only\n4 Gaia, your and ally objects only\n5 Gaia, neutral and enemy objects only\n6 All but your objects");
	UnitCommands_RightClickMode_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_RightClickMode_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Right Click Mode *", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_RightClickMode = AGETextCtrl::init(CByte, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
	UnitCommands_RightClickMode->SetToolTip("0 - Right-click target can be any object as defined by the Selection Mode.\n1 - Only the specified unit/class can be targeted using right-click.");
	UnitCommands_Unknown12_Holder = new wxBoxSizer(wxVERTICAL);
	UnitCommands_Unknown12_Text = new wxStaticText(Units_Scroller, wxID_ANY, " Unknown 12", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_NO_AUTORESIZE);
	UnitCommands_Unknown12 = AGETextCtrl::init(CByte, &uiGroupUnitCommand, this, &popUp, Units_Scroller);

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
	Type20.Add("PlacementSideTerrain x2");
	Type20.Add("PlacementTerrain x2");
	Type20.Add("ClearanceSize x2");
	Type20.Add("HillMode");
	Type20.Add("VisibleInFog");
	Type20.Add("TerrainRestriction");
	Type20.Add("FlyMode");
	Type20.Add("ResourceCapacity");
	Type20.Add("ResourceDecay");
	Type20.Add("BlastDefenseLevel");
	Type20.Add("SubType");
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
	Type20.Add("Unknown7");
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
	Type20.Add("Unknown10");
	Type20.Add("Name");
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
	Type30.Add("RotationAngles 5 floats");

	Type40.Add("ActionWhenDiscoveredID");
	Type40.Add("SearchRadius");
	Type40.Add("WorkRate");
	Type40.Add("DropSite x2");
	Type40.Add("TaskSwapID");
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
	Type50.Add("BlastWidth");
	Type50.Add("ReloadTime");
	Type50.Add("ProjectileUnitID");
	Type50.Add("AccuracyPercent");
	Type50.Add("TowerMode");
	Type50.Add("FrameDelay");
	Type50.Add("GraphicDisplacement 3 floats");
	Type50.Add("BlastAttackLevel");
	Type50.Add("MinRange");
	Type50.Add("AccuracyDispersion");
	Type50.Add("AttackGraphic");
	Type50.Add("DisplayedMeleeArmour");
	Type50.Add("DisplayedAttack");
	Type50.Add("DisplayedRange");
	Type50.Add("DisplayedReloadTime");

	Type60.Add("StretchMode");
	Type60.Add("SmartMode");
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
	Type70.Add("CreatableType");
	Type70.Add("HeroMode");
	Type70.Add("GarrisonGraphic");
	Type70.Add("TotalProjectiles");
	Type70.Add("MaxTotalProjectiles");
	Type70.Add("ProjectileSpawningArea 3 floats");
	Type70.Add("SecondaryProjectileUnit");
	Type70.Add("SpecialGraphic");
	Type70.Add("SpecialAbility");
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

	Units_Buttons->Add(Units_Add, 1, wxEXPAND);
	Units_Buttons->Add(Units_Delete, 1, wxEXPAND);
	Units_Buttons->Add(Units_Insert, 1, wxEXPAND);
	Units_Buttons->Add(Units_Copy, 1, wxEXPAND);
	Units_Buttons->Add(Units_Paste, 1, wxEXPAND);
	Units_Buttons->Add(Units_PasteInsert, 1, wxEXPAND);
	Units_Buttons->Add(Units_Info, 1, wxEXPAND);
	Units_Buttons1->Add(Units_SpecialCopy, 10, wxEXPAND);
	Units_Buttons1->Add(Units_SpecialPaste, 10, wxEXPAND);
	Units_Buttons1->Add(Units_Enable, 8, wxEXPAND);
	Units_Buttons1->Add(Units_Disable, 12, wxEXPAND);
	Units_Special->Add(Units_SpecialCopy_Options, 1, wxEXPAND);
	Units_Special->Add(Units_SpecialCopy_Civs, 0, wxEXPAND | wxLEFT, 2);

	Units_Searches[0]->Add(Units_Search, 1, wxEXPAND);
	Units_Searches[0]->Add(Units_UseAnd[0], 0, wxEXPAND | wxLEFT, 2);
	Units_Searches[1]->Add(Units_Search_R, 1, wxEXPAND);
	Units_Searches[1]->Add(Units_UseAnd[1], 0, wxEXPAND | wxLEFT, 2);

	Units_Units->Add(Units_Civs_List, 0, wxEXPAND | wxBOTTOM, 2);
	for(size_t loop = 0; loop < 2; ++loop)
	Units_Units->Add(Units_Searches[loop], 0, wxEXPAND);
	Units_Units->Add(Units_FilterSelector, 0, wxEXPAND);
	for(size_t loop = 0; loop < 2; ++loop)
	Units_Units->Add(Units_SearchFilters[loop], 0, wxEXPAND);
	Units_Units->Add(Units_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
	Units_Units->Add(Units_Buttons, 0, wxEXPAND);
	Units_Units->Add(Units_Buttons1, 0, wxEXPAND);
	Units_Units->Add(Units_Special, 0, wxEXPAND | wxTOP, 2);

	Units_Type_Holder->Add(visibleUnitCiv);
	Units_Type_Holder->Add(Units_Type_Text);
	Units_Type_Holder->Add(Units_Type);
	Units_Type_Holder->Add(Units_Type_ComboBox);
	Units_Type_Holder->Add(Units_Class_Text);
	Units_Type_Holder->Add(Units_Class);
	Units_Type_Holder->Add(Units_Class_ComboBox[0]);

//	Type 10+

	Units_ID1_Holder->Add(Units_ID1_Text);
	Units_HitPoints_Holder->Add(Units_HitPoints_Text);
	Units_LineOfSight_Holder->Add(Units_LineOfSight_Text);
	Units_GarrisonCapacity_Holder->Add(Units_GarrisonCapacity_Text);
	Units_SizeRadius_Holder->Add(Units_SizeRadius_Text);
	Units_DeadUnitID_Holder->Add(Units_DeadUnitID_Text);
	Units_PlacementMode_Holder->Add(Units_PlacementMode_Text);
	Units_IconAngle_Holder->Add(Units_IconID_Text);
	Units_Unknown1_Holder->Add(Units_Unknown1_Text);
	Units_PlacementSideTerrain_Holder->Add(Units_PlacementSideTerrain_Text);
	Units_PlacementTerrain_Holder->Add(Units_PlacementTerrain_Text);
	Units_ClearanceSize_Holder->Add(Units_ClearanceSize_Text);
	Units_HillMode_Holder->Add(Units_HillMode_Text);
	Units_TerrainRestriction_Holder->Add(Units_TerrainRestriction_Text);
	Units_ResourceCapacity_Holder->Add(Units_ResourceCapacity_Text);
	Units_ResourceDecay_Holder->Add(Units_ResourceDecay_Text);
	Units_BlastDefenseLevel_Holder->Add(Units_BlastDefenseLevel_Text);
	Units_SubType_Holder->Add(Units_SubType_Text);
	Units_InteractionMode_Holder->Add(Units_InteractionMode_Text);
	Units_MinimapMode_Holder->Add(Units_MinimapMode_Text);
	Units_CommandID_Holder->Add(Units_CommandID_Text);
	Units_Unknown3A_Holder->Add(Units_Unknown3A_Text);
	Units_MinimapColor_Holder->Add(Units_MinimapColor_Text);
	Units_Unknown6_Holder->Add(Units_Unknown6_Text);
	Units_Unknown7_Holder->Add(Units_Unknown7_Text);
	Units_Unknown8_Holder->Add(Units_Unknown8_Text);
	Units_SelectionMask_Holder->Add(Units_SelectionMask_Text);
	Units_SelectionShapeType_Holder->Add(Units_SelectionShapeType_Text);
	Units_SelectionShape_Holder->Add(Units_SelectionShape_Text);
	Units_Civ_Holder->Add(Units_Civ_Text);
	Units_Nothing_Holder->Add(Units_Nothing_Text);
	Units_Attribute_Holder->Add(Units_Attribute_Text);
	Units_SelectionEffect_Holder->Add(Units_SelectionEffect_Text);
	Units_EditorSelectionColour_Holder->Add(Units_EditorSelectionColour_Text);
	Units_SelectionRadius_Holder->Add(Units_SelectionRadius_Text);
	Units_SelectionSound_Holder->Add(Units_SelectionSound_Text);
	Units_DyingSound_Holder->Add(Units_DyingSound_Text);
	Units_AttackMode_Holder->Add(Units_AttackMode_Text);
	Units_Unknown10_Holder->Add(Units_Unknown10_Text);
	Units_Name_Holder->Add(Units_Name_Text);
	Units_Name2_Holder->Add(Units_Name2_Text);
	Units_Unitline_Holder->Add(Units_Unitline_Text);
	Units_MinTechLevel_Holder->Add(Units_MinTechLevel_Text);
	Units_ID2_Holder->Add(Units_ID2_Text);
	Units_ID3_Holder->Add(Units_ID3_Text);

//	Type 20+

	Units_Speed_Holder->Add(Units_Speed_Text);

//	Type 30+

	Units_RotationSpeed_Holder->Add(Units_RotationSpeed_Text);
	Units_Unknown11_Holder->Add(Units_Unknown11_Text);
	Units_TrackingUnit_Holder->Add(Units_TrackingUnit_Text);
	Units_TrackingUnitUsed_Holder->Add(Units_TrackingUnitUsed_Text);
	Units_TrackingUnitDensity_Holder->Add(Units_TrackingUnitDensity_Text);
	Units_Unknown16_Holder->Add(Units_Unknown16_Text);
	Units_RotationAngles_Holder->Add(Units_RotationAngles_Text);

//	Type 40+

	Units_SearchRadius_Holder->Add(Units_SearchRadius_Text);
	Units_WorkRate_Holder->Add(Units_WorkRate_Text);
	Units_DropSite_Holder->Add(Units_DropSite_Text);
	Units_TaskSwapID_Holder->Add(Units_TaskSwapID_Text);
	Units_AttackSound_Holder->Add(Units_AttackSound_Text);
	Units_MoveSound_Holder->Add(Units_MoveSound_Text);
	Units_Exists_Holder->Add(Units_Exists_Text);

//	Type 50+

	Units_DefaultArmor_Holder->Add(Units_DefaultArmor_Text);
	Units_TerRestrictionForDmgMultiply_Holder->Add(Units_TerRestrictionForDmgMultiply_Text);
	Units_MaxRange_Holder->Add(Units_MaxRange_Text);
	Units_BlastWidth_Holder->Add(Units_BlastWidth_Text);
	Units_ReloadTime1_Holder->Add(Units_ReloadTime1_Text);
	Units_AccuracyPercent_Holder->Add(Units_AccuracyPercent_Text);
	Units_Delay_Holder->Add(Units_Delay_Text);
	Units_GraphicDisplacement_Holder->Add(Units_GraphicDisplacement_Text);
	Units_BlastAttackLevel_Holder->Add(Units_BlastAttackLevel_Text);
	Units_MinRange_Holder->Add(Units_MinRange_Text);
	Units_AccuracyDispersion_Holder->Add(Units_AccuracyDispersion_Text);
	Units_AttackGraphic_Holder->Add(Units_AttackGraphic_Text);
	Units_DisplayedMeleeArmour_Holder->Add(Units_DisplayedMeleeArmour_Text);
	Units_DisplayedAttack_Holder->Add(Units_DisplayedAttack_Text);
	Units_DisplayedRange_Holder->Add(Units_DisplayedRange_Text);
	Units_ReloadTime2_Holder->Add(Units_ReloadTime2_Text);

//	Type 60 only

	Units_StretchMode_Holder->Add(Units_StretchMode_Text);
	Units_SmartMode_Holder->Add(Units_SmartMode_Text);
	Units_DropAnimationMode_Holder->Add(Units_DropAnimationMode_Text);
	Units_PenetrationMode_Holder->Add(Units_PenetrationMode_Text);
	Units_Unknown24_Holder->Add(Units_Unknown24_Text);
	Units_ProjectileArc_Holder->Add(Units_ProjectileArc_Text);

//	Type 70+

	Unit_Cost_Texts->Add(Units_CostType_Text);
	Unit_Cost_Texts->AddSpacer(35);
	Unit_Cost_Texts->Add(Units_CostAmount_Text);
	Unit_Cost_Texts->AddSpacer(15);
	Unit_Cost_Texts->Add(Units_CostUsed_Text);
	Units_TrainTime_Holder->Add(Units_TrainTime_Text);
	Units_TrainLocationID_Holder->Add(Units_TrainLocationID_Text);
	Units_ButtonID_Holder->Add(Units_ButtonID_Text);
	Units_Unknown26_Holder->Add(Units_Unknown26_Text);
	Units_Unknown27_Holder->Add(Units_Unknown27_Text);
	Units_UnknownType_Holder->Add(Units_UnknownType_Text);
	Units_MissileCount_Holder->Add(Units_MissileCount_Text);
	Units_MissileDuplicationCount_Holder->Add(Units_MissileDuplicationCount_Text);
	Units_AttackMissileDuplicationSpawning_Holder->Add(Units_AttackMissileDuplicationSpawning_Text);
	Units_ChargingMode_Holder->Add(Units_ChargingMode_Text);
	Units_DisplayedPierceArmour_Holder->Add(Units_DisplayedPierceArmour_Text);

//	Type 80

	Units_ConstructionGraphicID_Holder->Add(Units_ConstructionGraphicID_Text);
	Units_SnowGraphicID_Holder->Add(Units_SnowGraphicID_Text);
	Units_IconAngle_Holder->Add(Units_IconAngle_Text, 0, wxTOP, 10);
	Units_StackUnitID_Holder->Add(Units_StackUnitID_Text);
	Units_TerrainID_Holder->Add(Units_TerrainID_Text);
	Units_OldTerrainLikeID_Holder->Add(Units_OldTerrainLikeID_Text);
	Units_ResearchID_Holder->Add(Units_ResearchID_Text);
	Units_Unknown33_Holder->Add(Units_Unknown33_Text);
	Units_AnnexUnit1_Holder->Add(Units_AnnexUnit_Text);
	Units_AnnexUnitMisplacement1_Holder->Add(Units_AnnexUnitMisplacement_Text);
	Units_HeadUnit_Holder->Add(Units_HeadUnit_Text);
	Units_TransformUnit_Holder->Add(Units_TransformUnit_Text);
	Units_UnknownSound_Holder->Add(Units_UnknownSound_Text);
	Units_ConstructionSound_Holder->Add(Units_ConstructionSound_Text);
	Units_GarrisonHealRate_Holder->Add(Units_GarrisonHealRate_Text);
	Units_Unknown35_Holder->Add(Units_Unknown35_Text);
	Units_PileUnit_Holder->Add(Units_PileUnit_Text);
	Units_LootSwitch_Holder->Add(Units_LootSwitch_Text);

//	Type 10+

	Units_ID1_Holder->Add(Units_ID1, 0, wxEXPAND);
	Units_DeathMode_Holder->Add(Units_DeathMode, 0, wxEXPAND);
	Units_DeathMode_Holder->Add(Units_DeathMode_CheckBox, 2, wxEXPAND | wxLEFT, 2);
	Units_HitPoints_Holder->Add(Units_HitPoints, 0, wxEXPAND);
	Units_LineOfSight_Holder->Add(Units_LineOfSight, 0, wxEXPAND);
	Units_GarrisonCapacity_Holder->Add(Units_GarrisonCapacity, 0, wxEXPAND);
	for(size_t loop = 0; loop < 2; ++loop)
	Units_SizeRadius_Grid->Add(Units_SizeRadius[loop]);
	Units_SizeRadius_Grid->Add(Units_HPBarHeight1, 0, wxEXPAND);
	Units_SizeRadius_Holder->Add(Units_SizeRadius_Grid, 0, wxEXPAND);
	Units_DeadUnitID_Holder->Add(Units_DeadUnitID, 0, wxEXPAND);
	Units_DeadUnitID_Holder->Add(Units_DeadUnitID_ComboBox);
	Units_PlacementMode_Holder->Add(Units_PlacementMode, 0, wxEXPAND);
	Units_AirMode_Holder->Add(Units_AirMode, 0, wxEXPAND);
	Units_AirMode_Holder->Add(Units_AirMode_CheckBox, 2, wxEXPAND | wxLEFT, 2);
	Units_IconID_Holder->Add(Units_IconID);
	Units_HideInEditor_Holder->Add(Units_HideInEditor, 0, wxEXPAND);
	Units_HideInEditor_Holder->Add(Units_HideInEditor_CheckBox, 2, wxEXPAND | wxLEFT, 2);
	Units_Unknown1_Holder->Add(Units_Unknown1, 0, wxEXPAND);
	Units_Enabled_Holder->Add(Units_Enabled, 0, wxEXPAND);
	Units_Enabled_Holder->Add(Units_Enabled_CheckBox, 2, wxEXPAND | wxLEFT, 2);
	Units_Disabled_Holder->Add(Units_Disabled, 0, wxEXPAND);
	Units_Disabled_Holder->Add(Units_Disabled_CheckBox, 2, wxEXPAND | wxLEFT, 2);
	for(size_t loop = 0; loop < 2; ++loop)
	Units_PlacementSideTerrainGrid_Holder->Add(Units_PlacementSideTerrain[loop], 0, wxEXPAND);
	for(size_t loop = 0; loop < 2; ++loop)
	Units_PlacementSideTerrainGrid_Holder->Add(Units_PlacementSideTerrain_ComboBox[loop]);
	Units_PlacementSideTerrain_Holder->Add(Units_PlacementSideTerrainGrid_Holder, 0, wxEXPAND);
	for(size_t loop = 0; loop < 2; ++loop)
	Units_PlacementTerrainGrid_Holder->Add(Units_PlacementTerrain[loop], 0, wxEXPAND);
	for(size_t loop = 0; loop < 2; ++loop)
	Units_PlacementTerrainGrid_Holder->Add(Units_PlacementTerrain_ComboBox[loop]);
	Units_PlacementTerrain_Holder->Add(Units_PlacementTerrainGrid_Holder, 0, wxEXPAND);
	for(size_t loop = 0; loop < 2; ++loop)
	Units_ClearanceSize_Grid->Add(Units_ClearanceSize[loop]);
	Units_ClearanceSize_Holder->Add(Units_ClearanceSize_Grid, 0, wxEXPAND);
	Units_HillMode_Holder->Add(Units_HillMode, 0, wxEXPAND);
	Units_VisibleInFog_Holder->Add(Units_VisibleInFog_Text);
	Units_VisibleInFog_Holder->Add(Units_VisibleInFog, 0, wxEXPAND);
	Units_TerrainRestriction_Holder->Add(Units_TerrainRestriction, 0, wxEXPAND);
	Units_TerrainRestriction_Holder->Add(Units_TerrainRestriction_ComboBox);
	Units_FlyMode_Holder->Add(Units_FlyMode, 0, wxEXPAND);
	Units_FlyMode_Holder->Add(Units_FlyMode_CheckBox, 2, wxEXPAND | wxLEFT, 2);
	Units_ResourceCapacity_Holder->Add(Units_ResourceCapacity, 0, wxEXPAND);
	Units_ResourceDecay_Holder->Add(Units_ResourceDecay, 0, wxEXPAND);
	Units_BlastDefenseLevel_Holder->Add(Units_BlastDefenseLevel, 0, wxEXPAND);
	Units_SubType_Holder->Add(Units_SubType, 0, wxEXPAND);
	Units_InteractionMode_Holder->Add(Units_InteractionMode, 0, wxEXPAND);
	Units_MinimapMode_Holder->Add(Units_MinimapMode, 0, wxEXPAND);
	Units_CommandID_Holder->Add(Units_CommandID, 0, wxEXPAND);
	Units_Unknown3A_Holder->Add(Units_Unknown3A, 0, wxEXPAND);
	Units_MinimapColor_Holder->Add(Units_MinimapColor, 0, wxEXPAND);
	Units_Unselectable_Holder->Add(Units_Unselectable_CheckBox, 0, wxEXPAND);
	Units_Unselectable_Holder->Add(Units_Unselectable, 0, wxEXPAND);
	Units_Unknown6_Holder->Add(Units_Unknown6, 0, wxEXPAND);
	Units_Unknown7_Holder->Add(Units_Unknown7, 0, wxEXPAND);
	Units_Unknown8_Holder->Add(Units_Unknown8, 0, wxEXPAND);
	Units_SelectionMask_Holder->Add(Units_SelectionMask, 0, wxEXPAND);
	Units_SelectionShapeType_Holder->Add(Units_SelectionShapeType, 0, wxEXPAND);
	Units_SelectionShape_Holder->Add(Units_SelectionShape, 0, wxEXPAND);
	for(size_t loop = 0; loop < 8; ++loop)
	Units_Attribute_Grid->Add(Units_Attribute_CheckBox[loop]);
	Units_Attribute_Holder->Add(Units_Attribute, 0, wxEXPAND);
	Units_Attribute_Holder->Add(Units_Attribute_Grid);
	Units_Civ_Holder->Add(Units_Civ, 0, wxEXPAND);
	Units_Civ_Holder->Add(Units_Civ_ComboBox);
	Units_Nothing_Holder->Add(Units_Nothing, 0, wxEXPAND);
	Units_SelectionEffect_Holder->Add(Units_SelectionEffect, 0, wxEXPAND);
	Units_EditorSelectionColour_Holder->Add(Units_EditorSelectionColour, 0, wxEXPAND);
	for(size_t loop = 0; loop < 2; ++loop)
	Units_SelectionRadiusBox->Add(Units_SelectionRadius[loop]);
	Units_SelectionRadiusBox->Add(Units_HPBarHeight2);
	Units_SelectionRadius_Holder->Add(Units_SelectionRadiusBox, 0, wxEXPAND);
	Units_SelectionSound_Holder->Add(Units_SelectionSound, 0, wxEXPAND);
	Units_SelectionSound_Holder->Add(Units_SelectionSound_ComboBox);
	Units_DyingSound_Holder->Add(Units_DyingSound, 0, wxEXPAND);
	Units_DyingSound_Holder->Add(Units_DyingSound_ComboBox);
	Units_AttackMode_Holder->Add(Units_AttackMode, 0, wxEXPAND);
	Units_Unknown10_Holder->Add(Units_Unknown10, 0, wxEXPAND);
	Units_Name_Holder->Add(Units_Name, 0, wxEXPAND);
	Units_Name2_Holder->Add(Units_Name2, 0, wxEXPAND);
	Units_Unitline_Holder->Add(Units_Unitline, 0, wxEXPAND);
	Units_Unitline_Holder->Add(Units_Unitline_ComboBox);
	Units_MinTechLevel_Holder->Add(Units_MinTechLevel, 0, wxEXPAND);
	Units_MinTechLevel_Holder->Add(Units_MinTechLevel_ComboBox);
	Units_ID2_Holder->Add(Units_ID2, 0, wxEXPAND);
	Units_ID3_Holder->Add(Units_ID3, 0, wxEXPAND);

//	Type 20+

	Units_Speed_Holder->Add(Units_Speed, 0, wxEXPAND);

//	Type 30+

	Units_RotationSpeed_Holder->Add(Units_RotationSpeed, 0, wxEXPAND);
	Units_Unknown11_Holder->Add(Units_Unknown11, 0, wxEXPAND);
	Units_TrackingUnit_Holder->Add(Units_TrackingUnit, 0, wxEXPAND);
	Units_TrackingUnit_Holder->Add(Units_TrackingUnit_ComboBox);
	Units_TrackingUnitUsedBox_Holder->Add(Units_TrackingUnitUsed, 2, wxEXPAND);
	Units_TrackingUnitUsed_Holder->Add(Units_TrackingUnitUsedBox_Holder, 0, wxEXPAND);
	Units_TrackingUnitDensity_Holder->Add(Units_TrackingUnitDensity, 0, wxEXPAND);
	Units_Unknown16_Holder->Add(Units_Unknown16, 0, wxEXPAND);
	for(size_t loop = 0; loop < Units_RotationAngles.size(); ++loop)
	Units_RotationAngles_Grid->Add(Units_RotationAngles[loop]);
	Units_RotationAngles_Holder->Add(Units_RotationAngles_Grid, 0, wxEXPAND);

//	Type 40+

	Units_ActionWhenDiscoveredID_Holder->Add(Units_ActionWhenDiscoveredID_Text);
	Units_ActionWhenDiscoveredID_Holder->Add(Units_ActionWhenDiscoveredID, 0, wxEXPAND);
	Units_ActionWhenDiscoveredID_Holder->Add(Units_ActionWhenDiscoveredID_ComboBox);
	Units_SearchRadius_Holder->Add(Units_SearchRadius, 0, wxEXPAND);
	Units_WorkRate_Holder->Add(Units_WorkRate, 0, wxEXPAND);
	Units_DropSite_Grid->Add(Units_DropSite[0], 0, wxEXPAND);
	Units_DropSite_Grid->Add(Units_DropSite[1], 0, wxEXPAND);
	Units_DropSite_Grid->Add(Units_DropSite_ComboBox[0]);
	Units_DropSite_Grid->Add(Units_DropSite_ComboBox[1]);
	Units_TaskSwapID_Holder->Add(Units_TaskSwapID, 0, wxEXPAND);
	Units_AttackSound_Holder->Add(Units_AttackSound, 0, wxEXPAND);
	Units_AttackSound_Holder->Add(Units_AttackSound_ComboBox);
	Units_MoveSound_Holder->Add(Units_MoveSound, 0, wxEXPAND);
	Units_MoveSound_Holder->Add(Units_MoveSound_ComboBox);
	Units_AnimalMode_Holder->Add(Units_AnimalMode, 0, wxEXPAND);
	Units_AnimalMode_Holder->Add(Units_AnimalMode_CheckBox, 2, wxEXPAND | wxLEFT, 2);
	Units_Exists_Holder->Add(Units_Exists, 0, wxEXPAND);

//	Type 50+

	Units_DefaultArmor_Holder->Add(Units_DefaultArmor, 0, wxEXPAND);
	Units_TerRestrictionForDmgMultiply_Holder->Add(Units_TerRestrictionForDmgMultiply, 0, wxEXPAND);
	Units_TerRestrictionForDmgMultiply_Holder->Add(Units_TerRestrictionForDmgMultiply_ComboBox);
	Units_MaxRange_Holder->Add(Units_MaxRange, 0, wxEXPAND);
	Units_BlastWidth_Holder->Add(Units_BlastWidth, 0, wxEXPAND);
	Units_ReloadTime1_Holder->Add(Units_ReloadTime1, 0, wxEXPAND);
	Units_AccuracyPercent_Holder->Add(Units_AccuracyPercent, 0, wxEXPAND);
	Units_TowerMode_Holder->Add(Units_TowerMode, 0, wxEXPAND);
	Units_TowerMode_Holder->Add(Units_TowerMode_CheckBox, 2, wxEXPAND | wxLEFT, 2);
	Units_Delay_Holder->Add(Units_Delay, 0, wxEXPAND);
	for(size_t loop = 0; loop < 3; ++loop)
	Units_GraphicDisplacement_Grid->Add(Units_GraphicDisplacement[loop]);
	Units_GraphicDisplacement_Holder->Add(Units_GraphicDisplacement_Grid, 0, wxEXPAND);
	Units_BlastAttackLevel_Holder->Add(Units_BlastAttackLevel, 0, wxEXPAND);
	Units_MinRange_Holder->Add(Units_MinRange, 0, wxEXPAND);
	Units_AccuracyDispersion_Holder->Add(Units_AccuracyDispersion, 0, wxEXPAND);
	Units_AttackGraphic_Holder->Add(Units_AttackGraphic, 0, wxEXPAND);
	Units_AttackGraphic_Holder->Add(Units_AttackGraphic_ComboBox);
	Units_DisplayedMeleeArmour_Holder->Add(Units_DisplayedMeleeArmour, 0, wxEXPAND);
	Units_DisplayedAttack_Holder->Add(Units_DisplayedAttack, 0, wxEXPAND);
	Units_DisplayedRange_Holder->Add(Units_DisplayedRange, 0, wxEXPAND);
	Units_ReloadTime2_Holder->Add(Units_ReloadTime2, 0, wxEXPAND);

//	Type 60 only

	Units_StretchMode_Holder->Add(Units_StretchMode, 0, wxEXPAND);
	Units_SmartMode_Holder->Add(Units_SmartMode, 0, wxEXPAND);
	Units_DropAnimationMode_Holder->Add(Units_DropAnimationMode, 0, wxEXPAND);
	Units_PenetrationMode_Holder->Add(Units_PenetrationMode, 0, wxEXPAND);
	Units_Unknown24_Holder->Add(Units_Unknown24, 0, wxEXPAND);
	Units_ProjectileArc_Holder->Add(Units_ProjectileArc, 0, wxEXPAND);

//	Type 70+

    for(size_t loop = 0; loop < 3; ++loop)
    {
        wxBoxSizer *sizer_cost = new wxBoxSizer(wxHORIZONTAL);
        sizer_cost->Add(Units_CostUsed[loop]);
        sizer_cost->Add(Units_CostUsed_CheckBox[loop], 0, wxLEFT, 5);
        Unit_Cost_Sizers[loop]->Add(Units_CostType[loop], 0, wxEXPAND);
        Unit_Cost_Sizers[loop]->Add(Units_CostType_ComboBox[loop]);
        Unit_Cost_Sizers[loop]->Add(Units_CostAmount[loop], 0, wxEXPAND | wxTOP, 5);
        Unit_Cost_Sizers[loop]->Add(sizer_cost, 0, wxEXPAND | wxTOP, 5);
    }
	Units_TrainTime_Holder->Add(Units_TrainTime, 0, wxEXPAND);
	Units_TrainLocationID_Holder->Add(Units_TrainLocationID, 0, wxEXPAND);
	Units_TrainLocationID_Holder->Add(Units_TrainLocationID_ComboBox);
	Units_ButtonID_Holder->Add(Units_ButtonID, 0, wxEXPAND);
	Units_Unknown26_Holder->Add(Units_Unknown26, 0, wxEXPAND);
	Units_Unknown27_Holder->Add(Units_Unknown27, 0, wxEXPAND);
	Units_UnknownType_Holder->Add(Units_UnknownType, 0, wxEXPAND);
	Units_HeroMode_Holder->Add(Units_HeroMode, 0, wxEXPAND);
	Units_HeroMode_Holder->Add(Units_HeroMode_CheckBox, 2, wxEXPAND | wxLEFT, 2);
	Units_MissileCount_Holder->Add(Units_MissileCount, 0, wxEXPAND);
	Units_MissileDuplicationCount_Holder->Add(Units_MissileDuplicationCount, 0, wxEXPAND);
	for(size_t loop = 0; loop < 3; ++loop)
	Units_AttackMissileDuplicationSpawning_Grid->Add(Units_AttackMissileDuplicationSpawning[loop]);
	Units_AttackMissileDuplicationSpawning_Holder->Add(Units_AttackMissileDuplicationSpawning_Grid, 0, wxEXPAND);
	Units_ChargingMode_Holder->Add(Units_ChargingMode, 0, wxEXPAND);
	Units_DisplayedPierceArmour_Holder->Add(Units_DisplayedPierceArmour, 0, wxEXPAND);

//	Type 80

	Units_ConstructionGraphicID_Holder->Add(Units_ConstructionGraphicID, 0, wxEXPAND);
	Units_ConstructionGraphicID_Holder->Add(Units_ConstructionGraphicID_ComboBox);
	Units_SnowGraphicID_Holder->Add(Units_SnowGraphicID, 0, wxEXPAND);
	Units_SnowGraphicID_Holder->Add(Units_SnowGraphicID_ComboBox);
	Units_AdjacentMode_Holder->Add(Units_AdjacentMode, 0, wxEXPAND);
	Units_AdjacentMode_Holder->Add(Units_AdjacentMode_CheckBox, 2, wxEXPAND | wxLEFT, 2);
	Units_Unknown31b_Holder->Add(Units_DisappearsWhenBuilt, 0, wxEXPAND);
	Units_Unknown31b_Holder->Add(Units_Unknown31b_CheckBox, 2, wxEXPAND | wxLEFT, 2);
	Units_IconID_Holder->Add(Units_IconAngle);
	Units_StackUnitID_Holder->Add(Units_StackUnitID, 0, wxEXPAND);
	Units_StackUnitID_Holder->Add(Units_StackUnitID_ComboBox);
	Units_TerrainID_Holder->Add(Units_TerrainID, 0, wxEXPAND);
	Units_TerrainID_Holder->Add(Units_TerrainID_ComboBox);
	Units_OldTerrainLikeID_Holder->Add(Units_OldTerrainLikeID, 0, wxEXPAND);
	Units_ResearchID_Holder->Add(Units_ResearchID, 0, wxEXPAND);
	Units_ResearchID_Holder->Add(Units_ResearchID_ComboBox);
	Units_Unknown33_Holder->Add(Units_Unknown33, 0, wxEXPAND);
	for(size_t loop = 0; loop < 4; ++loop)
	Units_AnnexUnit_Grid->Add(Units_AnnexUnit[loop], 0, wxEXPAND);
	for(size_t loop = 0; loop < 4; ++loop)
	Units_AnnexUnit_Grid->Add(Units_AnnexUnit_ComboBox[loop]);
	Units_AnnexUnit1_Holder->Add(Units_AnnexUnit_Grid);
	for(size_t loop = 0; loop < 4; ++loop)
	Units_AnnexUnitMisplacement_Grid->Add(Units_AnnexUnitMisplacement[loop][0]);
	for(size_t loop = 0; loop < 4; ++loop)
	Units_AnnexUnitMisplacement_Grid->Add(Units_AnnexUnitMisplacement[loop][1]);
	Units_AnnexUnitMisplacement1_Holder->Add(Units_AnnexUnitMisplacement_Grid);
	Units_HeadUnit_Holder->Add(Units_HeadUnit, 0, wxEXPAND);
	Units_HeadUnit_Holder->Add(Units_HeadUnit_ComboBox);
	Units_TransformUnit_Holder->Add(Units_TransformUnit, 0, wxEXPAND);
	Units_TransformUnit_Holder->Add(Units_TransformUnit_ComboBox);
	Units_UnknownSound_Holder->Add(Units_UnknownSound, 0, wxEXPAND);
	Units_UnknownSound_Holder->Add(Units_UnknownSound_ComboBox);
	Units_ConstructionSound_Holder->Add(Units_ConstructionSound, 0, wxEXPAND);
	Units_ConstructionSound_Holder->Add(Units_ConstructionSound_ComboBox);
	Units_GarrisonHealRate_Holder->Add(Units_GarrisonHealRate, 0, wxEXPAND);
	Units_Unknown35_Holder->Add(Units_Unknown35, 0, wxEXPAND);
	Units_PileUnit_Holder->Add(Units_PileUnit, 0, wxEXPAND);
	Units_PileUnit_Holder->Add(Units_PileUnit_ComboBox);
	for(size_t loop = 0; loop < Units_LootSwitch.size(); ++loop)
	Units_LootSwitch_Grid->Add(Units_LootSwitch[loop]);
	Units_LootSwitch_Holder->Add(Units_LootSwitch_Grid);

    Units_ResourceStorage_Texts->Add(ResourceStorage_Type_Text);
    Units_ResourceStorage_Texts->AddSpacer(35);
    Units_ResourceStorage_Texts->Add(ResourceStorage_Amount_Text);
    Units_ResourceStorage_Texts->AddSpacer(15);
    Units_ResourceStorage_Texts->Add(ResourceStorage_Enabled_Text);
    for(size_t loop = 0; loop < 3; ++loop)
    {
        Units_ResourceStorage_Holder[loop]->Add(ResourceStorage_Type[loop], 0, wxEXPAND);
        Units_ResourceStorage_Holder[loop]->Add(ResourceStorage_Type_ComboBox[loop]);
        Units_ResourceStorage_Holder[loop]->Add(ResourceStorage_Amount[loop], 0, wxEXPAND | wxTOP, 5);
        Units_ResourceStorage_Holder[loop]->Add(ResourceStorage_Enabled[loop], 0, wxTOP, 5);
    }

	Attacks_Class_Holder->Add(Attacks_Class_Text);
	Attacks_Class_Holder->Add(Attacks_Class, 0, wxEXPAND);
	Attacks_Class_Holder->Add(Attacks_Class_ComboBox[0]);
	Attacks_Amount_Holder->Add(Attacks_Amount_Text);
	Attacks_Amount_Holder->Add(Attacks_Amount, 0, wxEXPAND);

	Units_Attacks_Buttons->Add(Units_Attacks_Add, 1, wxEXPAND);
	Units_Attacks_Buttons->Add(Units_Attacks_Delete, 1, wxEXPAND);
	Units_Attacks_Buttons->Add(Units_Attacks_Insert, 1, wxEXPAND);
	Units_Attacks_Buttons->Add(Units_Attacks_Copy, 1, wxEXPAND);
	Units_Attacks_Buttons->Add(Units_Attacks_Paste, 1, wxEXPAND);
	Units_Attacks_Buttons->Add(Units_Attacks_PasteInsert, 1, wxEXPAND);

	Units_Attacks_ListArea->Add(Units_Attacks_Search, 0, wxEXPAND);
	Units_Attacks_ListArea->Add(Units_Attacks_Search_R, 0, wxEXPAND);
	Units_Attacks_ListArea->Add(Units_Attacks_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
	Units_Attacks_ListArea->Add(Units_Attacks_Buttons, 0, wxEXPAND);
	Units_Attacks_ListArea->Add(Units_Attacks_CopyToUnits, 0, wxEXPAND | wxTOP, 2);

	Armors_Class_Holder->Add(Armors_Class_Text);
	Armors_Class_Holder->Add(Armors_Class, 0, wxEXPAND);
	Armors_Class_Holder->Add(Attacks_Class_ComboBox[1]);
	Armors_Amount_Holder->Add(Armors_Amount_Text);
	Armors_Amount_Holder->Add(Armors_Amount, 0, wxEXPAND);

	Units_Armors_Buttons->Add(Units_Armors_Add, 1, wxEXPAND);
	Units_Armors_Buttons->Add(Units_Armors_Delete, 1, wxEXPAND);
	Units_Armors_Buttons->Add(Units_Armors_Insert, 1, wxEXPAND);
	Units_Armors_Buttons->Add(Units_Armors_Copy, 1, wxEXPAND);
	Units_Armors_Buttons->Add(Units_Armors_Paste, 1, wxEXPAND);
	Units_Armors_Buttons->Add(Units_Armors_PasteInsert, 1, wxEXPAND);

	Units_Armors_ListArea->Add(Units_Armors_Search, 0, wxEXPAND);
	Units_Armors_ListArea->Add(Units_Armors_Search_R, 0, wxEXPAND);
	Units_Armors_ListArea->Add(Units_Armors_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
	Units_Armors_ListArea->Add(Units_Armors_Buttons, 0, wxEXPAND);
	Units_Armors_ListArea->Add(Units_Armors_CopyToUnits, 0, wxEXPAND | wxTOP, 2);

	UnitCommands_One_Holder->Add(UnitCommands_One_Text);
	UnitCommands_One_Holder->Add(UnitCommands_One);
	UnitCommands_ID_Holder->Add(UnitCommands_ID_Text);
	UnitCommands_ID_Holder->Add(UnitCommands_ID);
	UnitCommands_Unknown1_Holder->Add(UnitCommands_Unknown1_Text);
	UnitCommands_Unknown1_Holder->Add(UnitCommands_Unknown1, 0, wxEXPAND);
	UnitCommands_Type_Holder->Add(UnitCommands_Type_Text);
	UnitCommands_Type_Holder->Add(UnitCommands_Type, 0, wxEXPAND);
	UnitCommands_Type_Holder->Add(UnitCommands_Type_ComboBox);
	UnitCommands_ProductivityResource_Holder->Add(UnitCommands_ProductivityResource_Text);
	UnitCommands_ProductivityResource_Holder->Add(UnitCommands_ProductivityResource, 0, wxEXPAND);
	UnitCommands_ProductivityResource_Holder->Add(UnitCommands_ProductivityResource_ComboBox);
	UnitCommands_ClassID_Holder->Add(UnitCommands_ClassID_Text);
	UnitCommands_ClassID_Holder->Add(UnitCommands_ClassID, 0, wxEXPAND);
	UnitCommands_ClassID_Holder->Add(Units_Class_ComboBox[1]);
	UnitCommands_UnitID_Holder->Add(UnitCommands_UnitID_Text);
	UnitCommands_UnitID_Holder->Add(UnitCommands_UnitID, 0, wxEXPAND);
	UnitCommands_UnitID_Holder->Add(UnitCommands_UnitID_ComboBox);
	UnitCommands_TerrainID_Holder->Add(UnitCommands_TerrainID_Text);
	UnitCommands_TerrainID_Holder->Add(UnitCommands_TerrainID, 0, wxEXPAND);
	UnitCommands_TerrainID_Holder->Add(UnitCommands_TerrainID_ComboBox);
	UnitCommands_ResourceIn_Holder->Add(UnitCommands_ResourceIn_Text);
	UnitCommands_ResourceIn_Holder->Add(UnitCommands_ResourceIn, 0, wxEXPAND);
	UnitCommands_ResourceIn_Holder->Add(UnitCommands_ResourceIn_ComboBox);
	UnitCommands_ResourceOut_Holder->Add(UnitCommands_ResourceOut_Text);
	UnitCommands_ResourceOut_Holder->Add(UnitCommands_ResourceOut, 0, wxEXPAND);
	UnitCommands_ResourceOut_Holder->Add(UnitCommands_ResourceOut_ComboBox);
	UnitCommands_Resource_Holder->Add(UnitCommands_Resource_Text);
	UnitCommands_Resource_Holder->Add(UnitCommands_Resource, 0, wxEXPAND);
	UnitCommands_Resource_Holder->Add(UnitCommands_Resource_ComboBox);
	UnitCommands_WorkRateMultiplier_Holder->Add(UnitCommands_WorkRateMultiplier_Text);
	UnitCommands_WorkRateMultiplier_Holder->Add(UnitCommands_WorkRateMultiplier, 0, wxEXPAND);
	UnitCommands_ExecutionRadius_Holder->Add(UnitCommands_ExecutionRadius_Text);
	UnitCommands_ExecutionRadius_Holder->Add(UnitCommands_ExecutionRadius, 0, wxEXPAND);
	UnitCommands_ExtraRange_Holder->Add(UnitCommands_ExtraRange_Text);
	UnitCommands_ExtraRange_Holder->Add(UnitCommands_ExtraRange, 0, wxEXPAND);
	UnitCommands_Unknown4_Holder->Add(UnitCommands_Unknown4_Text);
	UnitCommands_Unknown4_Holder->Add(UnitCommands_Unknown4, 0, wxEXPAND);
	UnitCommands_Unknown5_Holder->Add(UnitCommands_Unknown5_Text);
	UnitCommands_Unknown5_Holder->Add(UnitCommands_Unknown5, 0, wxEXPAND);
	UnitCommands_SelectionEnabler_Holder->Add(UnitCommands_SelectionEnabler_Text);
	UnitCommands_SelectionEnabler_Holder->Add(UnitCommands_SelectionEnabler, 0, wxEXPAND);
	UnitCommands_Unknown7_Holder->Add(UnitCommands_Unknown7_Text);
	UnitCommands_Unknown7_Holder->Add(UnitCommands_Unknown7, 0, wxEXPAND);
	UnitCommands_Unknown8_Holder->Add(UnitCommands_Unknown8_Text);
	UnitCommands_Unknown8_Holder->Add(UnitCommands_Unknown8, 0, wxEXPAND);
	UnitCommands_Unknown9_Holder->Add(UnitCommands_Unknown9_Text);
	UnitCommands_Unknown9_Holder->Add(UnitCommands_Unknown9, 0, wxEXPAND);
	UnitCommands_SelectionMode_Holder->Add(UnitCommands_SelectionMode_Text);
	UnitCommands_SelectionMode_Holder->Add(UnitCommands_SelectionMode, 0, wxEXPAND);
	UnitCommands_RightClickMode_Holder->Add(UnitCommands_RightClickMode_Text);
	UnitCommands_RightClickMode_Holder->Add(UnitCommands_RightClickMode, 0, wxEXPAND);
	UnitCommands_Unknown12_Holder->Add(UnitCommands_Unknown12_Text);
	UnitCommands_Unknown12_Holder->Add(UnitCommands_Unknown12, 0, wxEXPAND);

	Units_TypeArea_Holder->Add(Units_Name_Holder);
	Units_TypeArea_Holder->Add(Units_Name2_Holder, 0, wxLEFT, 5);
	Units_TypeArea_Holder->Add(Units_ID1_Holder, 0, wxLEFT, 5);
	Units_TypeArea_Holder->Add(Units_ID2_Holder, 0, wxLEFT, 5);
	Units_TypeArea_Holder->Add(Units_ID3_Holder, 0, wxLEFT, 5);

	Units_LanguageDLLName_Holder->Add(Units_LanguageDLLName_Text);
	Units_LanguageDLLName_Holder->Add(Units_LanguageDLLName, 0, wxEXPAND);
	Units_LanguageDLLName_Holder->Add(Units_DLL_LanguageName);
	Units_LanguageDLLCreation_Holder->Add(Units_LanguageDLLCreation_Text);
	Units_LanguageDLLCreation_Holder->Add(Units_LanguageDLLCreation, 0, wxEXPAND);
	Units_LanguageDLLCreation_Holder->Add(Units_DLL_LanguageCreation);
	Units_LanguageDLLHelp_Holder->Add(Units_LanguageDLLHelp_Text);
	Units_LanguageDLLHelp_Holder->Add(Units_LanguageDLLHelp, 0, wxEXPAND);
	Units_LanguageDLLConverter_Holder[0]->Add(Units_LanguageDLLConverter_Text[0]);
	Units_LanguageDLLConverter_Holder[0]->Add(Units_LanguageDLLConverter[0], 0, wxEXPAND);
	Units_LanguageDLLHotKeyText_Holder->Add(Units_LanguageDLLHotKeyText_Text);
	Units_LanguageDLLHotKeyText_Holder->Add(Units_LanguageDLLHotKeyText, 0, wxEXPAND);
	Units_LanguageDLLConverter_Holder[1]->Add(Units_LanguageDLLConverter_Text[1]);
	Units_LanguageDLLConverter_Holder[1]->Add(Units_LanguageDLLConverter[1], 0, wxEXPAND);
	Units_HotKey_Holder->Add(Units_HotKey_Text);
	Units_HotKey_Holder->Add(Units_HotKey, 0, wxEXPAND);
	Units_HotKey_Holder->Add(Units_DLL_HotKey4);

	Units_LangRegular_Holder->Add(Units_LanguageDLLName_Holder);
	Units_LangRegular_Holder->Add(Units_LanguageDLLCreation_Holder, 0, wxLEFT, 5);
	Units_LangRegular_Holder->Add(Units_HotKey_Holder, 0, wxLEFT, 5);
	Units_LangHotKey_Holder->Add(Units_LanguageDLLHelp_Holder);
	Units_LangHotKey_Holder->Add(Units_LanguageDLLConverter_Holder[0], 0, wxLEFT, 5);
	Units_LangHotKey_Holder->Add(Units_LanguageDLLHotKeyText_Holder, 0, wxLEFT, 5);
	Units_LangHotKey_Holder->Add(Units_LanguageDLLConverter_Holder[1], 0, wxLEFT, 5);

	Units_LangDLLArea_Holder->Add(Units_LangRegular_Holder, 0, wxEXPAND);
	Units_LangDLLArea_Holder->Add(Units_LangHotKey_Holder, 0, wxEXPAND | wxTOP, 5);
	Units_LangDLLArea_Holder->Add(Units_DLL_LanguageHelp, 0, wxEXPAND | wxTOP, 5);
	Units_LangDLLArea_Holder->Add(Units_DLL_LanguageHKText, 0, wxEXPAND);

	Units_StandingGraphic_Grid->Add(Units_StandingGraphic[0], 0, wxEXPAND);
	Units_StandingGraphic_Grid->Add(Units_StandingGraphic[1], 0, wxEXPAND);
	Units_StandingGraphic_Grid->Add(Units_StandingGraphic_ComboBox[0]);
	Units_StandingGraphic_Grid->Add(Units_StandingGraphic_ComboBox[1]);
	Units_StandingGraphic_Holder->Add(Units_StandingGraphic_Text);
	Units_StandingGraphic_Holder->Add(Units_StandingGraphic_Grid);
	Units_GarrisonGraphic_Holder->Add(Units_GarrisonGraphic_Text);
	Units_GarrisonGraphic_Holder->Add(Units_GarrisonGraphic, 0, wxEXPAND);
	Units_GarrisonGraphic_Holder->Add(Units_GarrisonGraphic_ComboBox);
	Units_WalkingGraphic_Grid->Add(Units_WalkingGraphic[0], 0, wxEXPAND);
	Units_WalkingGraphic_Grid->Add(Units_WalkingGraphic[1], 0, wxEXPAND);
	Units_WalkingGraphic_Grid->Add(Units_WalkingGraphic_ComboBox[0]);
	Units_WalkingGraphic_Grid->Add(Units_WalkingGraphic_ComboBox[1]);
	Units_WalkingGraphic_Holder->Add(Units_WalkingGraphic_Text);
	Units_WalkingGraphic_Holder->Add(Units_WalkingGraphic_Grid);
	Units_DyingGraphic_Grid->Add(Units_DyingGraphic[0], 0, wxEXPAND);
	Units_DyingGraphic_Grid->Add(Units_DyingGraphic[1], 0, wxEXPAND);
	Units_DyingGraphic_Grid->Add(Units_DyingGraphic_ComboBox[0]);
	Units_DyingGraphic_Grid->Add(Units_DyingGraphic_ComboBox[1]);
	Units_DyingGraphic_Holder->Add(Units_DyingGraphic_Text);
	Units_DyingGraphic_Holder->Add(Units_DyingGraphic_Grid);

	Units_IconID_Grid->Add(Units_IconID_SLP);
	Units_IconID_Grid->Add(Units_IconID_Holder, 0, wxTOP | wxLEFT, 5);
	Units_IconID_Grid->Add(Units_IconAngle_Holder, 0, wxRIGHT | wxTOP, 5);
	Units_IconID_Grid->Add(Units_ChargingGraphic_Holder);
	Units_GraphicsArea4_Holder->Add(Units_IconID_Grid);
	Units_GraphicsArea4_Holder->Add(Units_StandingGraphic_Holder);
	Units_GraphicsArea4_Holder->Add(Units_DyingGraphic_Holder);
	Units_GraphicsArea4_Holder->Add(Units_WalkingGraphic_Holder);

	Units_GraphicsArea5_Holder->Add(Units_SnowGraphicID_Holder);
	Units_GraphicsArea5_Holder->Add(Units_ConstructionGraphicID_Holder, 0, wxLEFT, 5);
	Units_GraphicsArea5_Holder->Add(Units_AttackGraphic_Holder, 0, wxLEFT, 5);
	Units_GraphicsArea5_Holder->Add(Units_GarrisonGraphic_Holder, 0, wxLEFT, 5);

	DamageGraphics_GraphicID_Holder->Add(DamageGraphics_GraphicID_Text);
	DamageGraphics_GraphicID_Holder->Add(DamageGraphics_GraphicID, 0, wxEXPAND);
	DamageGraphics_GraphicID_Holder->Add(DamageGraphics_GraphicID_ComboBox);
	DamageGraphics_ApplyMode_Holder->Add(DamageGraphics_ApplyMode_Text);
	DamageGraphics_ApplyMode_Holder->Add(DamageGraphics_ApplyMode, 0, wxEXPAND);
	DamageGraphics_DamagePercent_Holder->Add(DamageGraphics_DamagePercent_Text);
	DamageGraphics_DamagePercent_Holder->Add(DamageGraphics_DamagePercent, 0, wxEXPAND);
	DamageGraphics_Unknown2_Holder->Add(DamageGraphics_Unknown2_Text);
	DamageGraphics_Unknown2_Holder->Add(DamageGraphics_Unknown2, 0, wxEXPAND);
	Units_DamageGraphics_Holder_Data->Add(slp_dmg_unit, 0, wxBOTTOM, 5);
	Units_DamageGraphics_Holder_Data->Add(DamageGraphics_GraphicID_Holder);
	Units_DamageGraphics_Holder_Data->Add(DamageGraphics_DamagePercent_Holder, 0, wxTOP, 5);
	Units_DamageGraphics_Holder_Data->Add(DamageGraphics_ApplyMode_Holder, 0, wxTOP, 5);
	Units_DamageGraphics_Holder_Data->Add(DamageGraphics_Unknown2_Holder, 0, wxTOP, 5);

	Units_DamageGraphics_Buttons->Add(Units_DamageGraphics_Add, 1, wxEXPAND);
	Units_DamageGraphics_Buttons->Add(Units_DamageGraphics_Delete, 1, wxEXPAND);
	Units_DamageGraphics_Buttons->Add(Units_DamageGraphics_Insert, 1, wxEXPAND);
	Units_DamageGraphics_Buttons->Add(Units_DamageGraphics_Copy, 1, wxEXPAND);
	Units_DamageGraphics_Buttons->Add(Units_DamageGraphics_Paste, 1, wxEXPAND);
	Units_DamageGraphics_Buttons->Add(Units_DamageGraphics_PasteInsert, 1, wxEXPAND);

	Units_DamageGraphics_ListArea->Add(Units_DamageGraphics_Search, 0, wxEXPAND);
	Units_DamageGraphics_ListArea->Add(Units_DamageGraphics_Search_R, 0, wxEXPAND);
	Units_DamageGraphics_ListArea->Add(Units_DamageGraphics_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
	Units_DamageGraphics_ListArea->Add(Units_DamageGraphics_Buttons, 0, wxEXPAND);
	Units_DamageGraphics_ListArea->Add(Units_DamageGraphics_CopyToUnits, 0, wxEXPAND | wxTOP, 2);

	Units_DamageGraphics->Add(Units_DamageGraphics_ListArea, 1, wxEXPAND);
	Units_DamageGraphics->Add(Units_DamageGraphics_Holder_Data, 0, wxLEFT, 5);

	Units_GraphicsArea1_Holder->Add(Units_DamageGraphics, 1, wxEXPAND);
	Units_GraphicsArea1_Holder->Add(Units_GraphicsArea4_Holder, 1, wxEXPAND | wxLEFT, 5);

    sizer_slp->Add(slp_radio);
    sizer_slp2->Add(slp_snow, 0, wxTOP, 10);
    sizer_slp2->Add(slp_garrison, 0, wxTOP, 5);
    sizer_slp->Add(sizer_slp2, 0, wxLEFT, 5);
    Units_GraphicsArea_Holder->Add(sizer_slp, 0, wxEXPAND | wxBOTTOM, 5);
	Units_GraphicsArea_Holder->Add(Units_GraphicsArea1_Holder, 0, wxEXPAND);
	Units_GraphicsArea_Holder->Add(Units_GraphicsArea5_Holder, 0, wxEXPAND | wxTOP, 5);

	Units_StatsArea1A_Sizer->Add(Units_HitPoints_Holder);
	Units_StatsArea1A_Sizer->Add(Units_Speed_Holder, 0, wxLEFT, 5);
	Units_StatsArea1A_Sizer->Add(Units_RotationSpeed_Holder, 0, wxLEFT, 5);
	Units_StatsArea1B_Sizer->Add(Units_LineOfSight_Holder);
	Units_StatsArea1B_Sizer->Add(Units_SearchRadius_Holder, 0, wxLEFT, 5);
	Units_StatsArea1B_Sizer->Add(Units_MaxRange_Holder, 0, wxLEFT, 5);
	Units_StatsArea1B_Sizer->Add(Units_MinRange_Holder, 0, wxLEFT, 5);
	Units_StatsArea1B_Sizer->Add(Units_DisplayedRange_Holder, 0, wxLEFT, 5);

	Units_Attacks_DataArea->Add(Attacks_Amount_Holder);
	Units_Attacks_DataArea->Add(Attacks_Class_Holder, 0, wxTOP, 5);
	Units_Attacks_Holder_Data->Add(Units_DisplayedAttack_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_Attacks_Holder_Data->Add(Units_Delay_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_Attacks_Holder_Data->Add(Units_AccuracyPercent_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_Attacks_Holder_Data->Add(Units_AccuracyDispersion_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_Attacks_Holder_Data->Add(Units_ReloadTime1_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_Attacks_Holder_Data->Add(Units_ReloadTime2_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_Attacks_Holder_Data->Add(Units_BlastWidth_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_Attacks_Holder_Data->Add(Units_BlastAttackLevel_Holder, 0, wxTOP, 5);

	Units_Armors_DataArea->Add(Armors_Amount_Holder);
	Units_Armors_DataArea->Add(Armors_Class_Holder, 0, wxTOP, 5);
	Units_Armors_Holder_Data3->Add(Units_DefaultArmor_Holder, 0, wxTOP, 5);
	Units_Armors_Holder_Data3->Add(Units_TerRestrictionForDmgMultiply_Holder, 0, wxTOP, 5);
	Units_Armors_Holder_Data3->Add(Units_DisplayedMeleeArmour_Holder, 0, wxTOP, 5);
	Units_Armors_Holder_Data3->Add(Units_DisplayedPierceArmour_Holder, 0, wxTOP, 5);
	Units_Armors_Holder_Data3->Add(Units_BlastDefenseLevel_Holder, 0, wxTOP, 5);

	for(size_t loop = 0; loop < 8; ++loop)
	Units_GarrisonType_Grid->Add(Units_GarrisonType_CheckBox[loop]);
	Units_GarrisonType_Holder->Add(Units_GarrisonType_Text);
	Units_GarrisonType_Holder->Add(Units_GarrisonType, 0, wxEXPAND);
	Units_GarrisonType_Holder->Add(Units_GarrisonType_Grid);

	Units_Attacks->Add(Units_Attacks_ListArea, 1, wxEXPAND);
	Units_Attacks->Add(Units_Attacks_DataArea, 0, wxLEFT, 5);
	Units_Armors->Add(Units_Armors_ListArea, 1, wxEXPAND);
	Units_Armors->Add(Units_Armors_DataArea, 0, wxLEFT, 5);
	Units_Attacks_Holder->Add(Units_Attacks, 1, wxEXPAND);
	Units_Attacks_Holder->Add(Units_Attacks_Holder_Data, 1, wxEXPAND | wxLEFT, 5);
	Units_Armors_Holder->Add(Units_Armors, 1, wxEXPAND);
	Units_Armors_Holder->Add(Units_Armors_Holder_Data3, 1, wxEXPAND | wxLEFT, 5);
	Units_StatsAreaGarrison_Grid->Add(Units_GarrisonCapacity_Holder);
	Units_StatsAreaGarrison_Grid->Add(Units_GarrisonType_Holder, 0, wxLEFT, 5);
	Units_StatsAreaGarrison_Grid->Add(Units_GarrisonHealRate_Holder, 0, wxLEFT, 5);
	Units_StatsArea2_Grid->Add(Units_ResourceCapacity_Holder);
	Units_StatsArea2_Grid->Add(Units_ResourceDecay_Holder, 0, wxLEFT, 5);
	Units_StatsArea2_Grid->Add(Units_WorkRate_Holder, 0, wxLEFT, 5);

	Units_StatsArea_Holder->Add(Units_StatsArea1A_Sizer, 0, wxEXPAND);
	Units_StatsArea_Holder->Add(Units_StatsArea1B_Sizer, 0, wxEXPAND | wxTOP, 5);
	Units_StatsArea_Holder->Add(Units_Attacks_Holder, 0, wxEXPAND | wxTOP, 5);
	Units_StatsArea_Holder->Add(Units_Armors_Holder, 0, wxEXPAND | wxTOP, 5);
	Units_StatsArea_Holder->Add(Units_StatsArea2_Grid, 0, wxEXPAND | wxTOP, 5);
	Units_StatsArea_Holder->Add(Units_StatsAreaGarrison_Grid, 0, wxEXPAND | wxTOP, 5);

	Units_ProjectileUnitID_Holder->Add(Units_ProjectileUnitID_Text);
	Units_ProjectileUnitID_Holder->Add(Units_ProjectileUnitID, 0, wxEXPAND);
	Units_ProjectileUnitID_Holder->Add(Units_ProjectileUnitID_ComboBox);
	Units_AttackMissileDuplicationUnit_Holder->Add(Units_AttackMissileDuplicationUnit_Text);
	Units_AttackMissileDuplicationUnit_Holder->Add(Units_AttackMissileDuplicationUnit, 0, wxEXPAND);
	Units_AttackMissileDuplicationUnit_Holder->Add(Units_AttackMissileDuplicationUnit_ComboBox);
	Units_ChargingGraphic_Holder->Add(Units_ChargingGraphic_Text);
	Units_ChargingGraphic_Holder->Add(Units_ChargingGraphic, 0, wxEXPAND);
	Units_ChargingGraphic_Holder->Add(Units_ChargingGraphic_ComboBox);

	Units_ProjectilesArea1_Grid->Add(Units_ProjectileUnitID_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_ProjectilesArea1_Grid->Add(Units_AttackMissileDuplicationUnit_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_ProjectilesArea1_Grid->Add(Units_MissileCount_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_ProjectilesArea1_Grid->Add(Units_MissileDuplicationCount_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_ProjectilesArea1_Grid->Add(Units_AttackMissileDuplicationSpawning_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_ProjectilesArea1_Grid->Add(Units_GraphicDisplacement_Holder, 0, wxBOTTOM | wxRIGHT, 5);

	Units_ProjectilesArea1_Grid->Add(Units_StretchMode_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_ProjectilesArea1_Grid->Add(Units_SmartMode_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_ProjectilesArea1_Grid->Add(Units_DropAnimationMode_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_ProjectilesArea1_Grid->Add(Units_PenetrationMode_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_ProjectilesArea1_Grid->Add(Units_Unknown24_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_ProjectilesArea1_Grid->Add(Units_ProjectileArc_Holder, 0, wxBOTTOM, 5);
	Units_ProjectilesArea_Holder->Add(Units_ProjectilesArea1_Grid, 0, wxEXPAND);

	Units_AttributesBoxes1_Grid->Add(Units_Enabled_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_AttributesBoxes1_Grid->Add(Units_Disabled_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_AttributesBoxes1_Grid->Add(Units_DeathMode_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_AttributesBoxes1_Grid->Add(Units_HideInEditor_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_AttributesBoxes1_Grid->Add(Units_AirMode_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_AttributesBoxes1_Grid->Add(Units_FlyMode_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_AttributesBoxes1_Grid->Add(Units_AnimalMode_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_AttributesBoxes1_Grid->Add(Units_TowerMode_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_AttributesBoxes1_Grid->Add(Units_AdjacentMode_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_AttributesBoxes1_Grid->Add(Units_Unknown31b_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_AttributesBoxes1_Grid->Add(Units_HeroMode_Holder, 0, wxBOTTOM, 5);

	Units_AttributesModes1_Grid->Add(Units_PlacementMode_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_AttributesModes1_Grid->Add(Units_HillMode_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_AttributesModes1_Grid->Add(Units_VisibleInFog_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_AttributesModes1_Grid->Add(Units_SubType_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_AttributesModes1_Grid->Add(Units_InteractionMode_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_AttributesModes1_Grid->Add(Units_MinimapMode_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_AttributesModes1_Grid->Add(Units_MinimapColor_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_AttributesModes1_Grid->Add(Units_Unknown6_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_AttributesModes1_Grid->Add(Units_Unknown7_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_AttributesModes1_Grid->Add(Units_Unknown8_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_AttributesModes1_Grid->Add(Units_AttackMode_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_AttributesModes1_Grid->Add(Units_Unknown10_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_AttributesModes1_Grid->Add(Units_TaskSwapID_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_AttributesModes1_Grid->Add(Units_UnknownType_Holder, 0, wxBOTTOM | wxRIGHT, 5);
	Units_AttributesModes1_Grid->Add(Units_ChargingMode_Holder, 0, wxBOTTOM, 5);

	Units_Attributes2_Grid->Add(Units_Attribute_Holder);
	Units_DropSite_Holder->Add(Units_DropSite_Grid, 0, wxEXPAND);
	Units_AttributesSizes_Holder->Add(Units_SizeRadius_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_AttributesSizes_Holder->Add(Units_ClearanceSize_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_AttributesSizes_Holder->Add(Units_SelectionRadius_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_AttributesSelection1_Grid->Add(Units_Unselectable_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_AttributesSelection1_Grid->Add(Units_SelectionMask_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_AttributesSelection1_Grid->Add(Units_SelectionShapeType_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_AttributesSelection1_Grid->Add(Units_SelectionShape_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_AttributesSelection1_Grid->Add(Units_SelectionEffect_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_AttributesSelection1_Grid->Add(Units_EditorSelectionColour_Holder, 0, wxTOP, 5);
    Units_ResourceStorageHeader_Holder->Add(Units_ResourceStorage_Texts);
    for(auto &sizer: Units_ResourceStorage_Holder)
    Units_ResourceStorageHeader_Holder->Add(sizer, 0, wxLEFT, 5);
	Units_Attributes2_Grid->Add(Units_Civ_Holder, 0, wxLEFT, 5);
	Units_Attributes2_Grid->Add(Units_Nothing_Holder, 0, wxLEFT, 5);
	Units_Attributes1_Grid->Add(Units_Attributes2_Grid, 0, wxTOP | wxRIGHT, 5);
	Units_Attributes1_Grid->Add(Units_DeadUnitID_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_Attributes1_Grid->Add(Units_Unitline_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_Attributes1_Grid->Add(Units_MinTechLevel_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_Attributes1_Grid->Add(Units_PlacementTerrain_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_Attributes1_Grid->Add(Units_PlacementSideTerrain_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_Attributes1_Grid->Add(Units_TerrainRestriction_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_AttributesTracking_Grid->Add(Units_TrackingUnit_Holder);
	Units_AttributesTracking_Grid->Add(Units_TrackingUnitUsed_Holder, 0, wxLEFT, 5);
	Units_AttributesTracking_Grid->Add(Units_TrackingUnitDensity_Holder, 0, wxLEFT, 5);
	Units_CostHeader_Holder->Add(Unit_Cost_Texts);
    for(auto &sizer: Unit_Cost_Sizers)
	Units_CostHeader_Holder->Add(sizer, 0, wxLEFT, 5);
	Units_AttributesTrain1_Grid->Add(Units_CommandID_Holder);
	Units_AttributesTrain1_Grid->Add(Units_TrainTime_Holder, 0, wxLEFT, 5);
	Units_AttributesTrain1_Grid->Add(Units_TrainLocationID_Holder, 0, wxLEFT, 5);
	Units_Attributes3_Grid->Add(Units_StackUnitID_Holder);
	Units_Attributes1_Grid->Add(Units_TerrainID_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_Attributes1_Grid->Add(Units_OldTerrainLikeID_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_Attributes1_Grid->Add(Units_ResearchID_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_Attributes1_Grid->Add(Units_ActionWhenDiscoveredID_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_Attributes1_Grid->Add(Units_DropSite_Holder, 0, wxTOP, 5);
	Units_Attributes3_Grid->Add(Units_HeadUnit_Holder, 0, wxLEFT, 5);
	Units_Attributes3_Grid->Add(Units_TransformUnit_Holder, 0, wxLEFT, 5);
	Units_Attributes3_Grid->Add(Units_PileUnit_Holder, 0, wxLEFT, 5);
	Units_AttributesTrain1_Grid->Add(Units_ButtonID_Holder, 0, wxLEFT, 5);

	Units_Attributes_Holder->Add(Units_AttributesBoxes1_Grid, 0, wxEXPAND);
	Units_Attributes_Holder->Add(Units_AttributesModes1_Grid, 0, wxEXPAND);
	Units_Attributes_Holder->Add(Units_Attributes1_Grid, 0, wxEXPAND, 5);
	Units_Attributes_Holder->Add(Units_AttributesSizes_Holder, 0, wxEXPAND, 5);
	Units_Attributes_Holder->Add(Units_AttributesSelection1_Grid, 0, wxEXPAND, 5);
	Units_Attributes_Holder->Add(Units_AttributesTracking_Grid, 0, wxEXPAND | wxTOP, 5);
	Units_Attributes_Holder->Add(Units_RotationAngles_Holder, 0, wxEXPAND | wxTOP, 5);
	Units_Attributes_Holder->Add(Units_AttributesTrain1_Grid, 0, wxEXPAND | wxTOP, 5);
	Units_Attributes_Holder->Add(Units_ResourceStorageHeader_Holder, 0, wxTOP, 5);
	Units_Attributes_Holder->Add(Units_CostHeader_Holder, 0, wxTOP, 5);
	Units_Attributes_Holder->Add(Units_Attributes3_Grid, 0, wxTOP, 5);
	Units_Attributes_Holder->Add(Units_AnnexUnit1_Holder, 0, wxTOP, 5);
	Units_Attributes_Holder->Add(Units_AnnexUnitMisplacement1_Holder, 0, wxTOP, 5);
	Units_Attributes_Holder->Add(Units_LootSwitch_Holder, 0, wxTOP, 5);

	Units_TrainSound1_Holder->Add(Units_TrainSound[0], 0, wxEXPAND);
	Units_TrainSound1_Holder->Add(Units_TrainSound_ComboBox[0]);
	Units_TrainSound2_Holder->Add(Units_TrainSound[1], 0, wxEXPAND);
	Units_TrainSound2_Holder->Add(Units_TrainSound_ComboBox[1]);

	Units_TrainSound3_Holder->Add(Units_TrainSound1_Holder);
	Units_TrainSound3_Holder->Add(Units_TrainSound2_Holder, 0, wxLEFT, 5);

	Units_TrainSound_Holder->Add(Units_TrainSound_Text);
	Units_TrainSound_Holder->Add(Units_TrainSound3_Holder);

	Units_SoundsArea1_Holder->Add(Units_SelectionSound_Holder);
	Units_SoundsArea1_Holder->Add(Units_DyingSound_Holder, 0, wxLEFT, 5);
	Units_SoundsArea1_Holder->Add(Units_TrainSound_Holder, 0, wxLEFT, 5);
	Units_SoundsArea2_Grid->Add(Units_AttackSound_Holder);
	Units_SoundsArea2_Grid->Add(Units_MoveSound_Holder, 0, wxLEFT, 5);
	Units_SoundsArea2_Grid->Add(Units_ConstructionSound_Holder, 0, wxLEFT, 5);
	Units_SoundsArea2_Grid->Add(Units_UnknownSound_Holder, 0, wxLEFT, 5);

	Units_SoundsArea_Holder->Add(Units_SoundsArea1_Holder, 0, wxEXPAND);
	Units_SoundsArea_Holder->Add(Units_SoundsArea2_Grid, 0, wxEXPAND | wxTOP, 5);

	Units_Type10plusUnknownArea_Holder->Add(Units_Unknown1_Holder);
	Units_Type10plusUnknownArea_Holder->Add(Units_Unknown3A_Holder, 0, wxLEFT, 5);

	Units_Type30plusUnknownArea_Holder->Add(Units_Unknown11_Holder);
	Units_Type30plusUnknownArea_Holder->Add(Units_Unknown16_Holder, 0, wxLEFT, 5);

	Units_Type70plusUnknownArea_Holder->Add(Units_Unknown26_Holder);
	Units_Type70plusUnknownArea_Holder->Add(Units_Unknown27_Holder, 0, wxLEFT, 5);

	Units_Type80plusUnknownArea_Holder->Add(Units_Unknown33_Holder);
	Units_Type80plusUnknownArea_Holder->Add(Units_Unknown35_Holder, 0, wxLEFT, 5);

	Units_UnitCommands_Buttons->Add(Units_UnitCommands_Add, 1, wxEXPAND);
	Units_UnitCommands_Buttons->Add(Units_UnitCommands_Delete, 1, wxEXPAND);
	Units_UnitCommands_Buttons->Add(Units_UnitCommands_Insert, 1, wxEXPAND);
	Units_UnitCommands_Buttons->Add(Units_UnitCommands_Copy, 1, wxEXPAND);
	Units_UnitCommands_Buttons->Add(Units_UnitCommands_Paste, 1, wxEXPAND);
	Units_UnitCommands_Buttons->Add(Units_UnitCommands_PasteInsert, 1, wxEXPAND);

	Units_CommandHolder_Lists->Add(Units_UnitHeads_Name, 0, wxEXPAND | wxBOTTOM, 5);
	Units_CommandHolder_Lists->Add(Units_UnitCommands_Search, 0, wxEXPAND);
	Units_CommandHolder_Lists->Add(Units_UnitCommands_Search_R, 0, wxEXPAND);
	Units_CommandHolder_Lists->Add(Units_UnitCommands_ListV, 0, wxEXPAND | wxBOTTOM | wxTOP, 2);
	Units_CommandHolder_Lists->Add(Units_UnitCommands_Buttons, 0, wxEXPAND);
	Units_CommandHolder_Lists->Add(Units_UnitCommands_CopyToUnits, 0, wxEXPAND | wxTOP, 2);
	Units_CommandHolder_Lists->Add(Units_Exists_Holder, 0, wxEXPAND | wxTOP, 5);
	Units_CommandHolder_Lists->Add(slp_unit_actions, 0, wxEXPAND | wxTOP, 5);

    Unit_Command_Known->Add(UnitCommands_Type_Holder, 0, wxLEFT, 5);
    Unit_Command_Known->Add(UnitCommands_One_Holder, 0, wxTOP | wxLEFT, 5);
    Unit_Command_Known->Add(UnitCommands_ID_Holder, 0, wxTOP | wxLEFT, 5);
    Unit_Command_Known->Add(UnitCommands_ClassID_Holder, 0, wxTOP | wxLEFT, 5);
    Unit_Command_Known->Add(UnitCommands_UnitID_Holder, 0, wxTOP | wxLEFT, 5);
    Unit_Command_Known->Add(UnitCommands_TerrainID_Holder, 0, wxTOP | wxLEFT, 5);
    Unit_Command_Known->Add(UnitCommands_ResourceIn_Holder, 0, wxTOP | wxLEFT, 5);
    Unit_Command_Known->Add(UnitCommands_ProductivityResource_Holder, 0, wxTOP | wxLEFT, 5);
    Unit_Command_Known->Add(UnitCommands_ResourceOut_Holder, 0, wxTOP | wxLEFT, 5);
    Unit_Command_Known->Add(UnitCommands_Resource_Holder, 0, wxTOP | wxLEFT, 5);
    Unit_Command_Known->Add(UnitCommands_WorkRateMultiplier_Holder, 0, wxTOP | wxLEFT, 5);
    Unit_Command_Known->Add(UnitCommands_ExecutionRadius_Holder, 0, wxTOP | wxLEFT, 5);
    Unit_Command_Known->Add(UnitCommands_ExtraRange_Holder, 0, wxTOP | wxLEFT, 5);

    for(size_t loop = 0; loop < UnitCommands_Graphics.size(); ++loop)
    {
        UnitCommands_Graphics_Holder[loop]->Add(UnitCommands_Graphics_Text[loop]);
        UnitCommands_Graphics_Holder[loop]->Add(UnitCommands_Graphics[loop], 0, wxEXPAND);
        UnitCommands_Graphics_Holder[loop]->Add(UnitCommands_Graphics_ComboBox[loop]);
        Unit_Command_Known->Add(UnitCommands_Graphics_Holder[loop], 0, wxTOP | wxLEFT, 5);
    }

    Unit_Command_Unknowns->Add(UnitCommands_Unknown1_Holder, 0, wxTOP | wxLEFT, 5);
    Unit_Command_Unknowns->Add(UnitCommands_Unknown4_Holder, 0, wxTOP | wxLEFT, 5);
    Unit_Command_Unknowns->Add(UnitCommands_Unknown5_Holder, 0, wxTOP | wxLEFT, 5);
    Unit_Command_Unknowns->Add(UnitCommands_SelectionEnabler_Holder, 0, wxTOP | wxLEFT, 5);
    Unit_Command_Unknowns->Add(UnitCommands_Unknown7_Holder, 0, wxTOP | wxLEFT, 5);
    Unit_Command_Unknowns->Add(UnitCommands_Unknown8_Holder, 0, wxTOP | wxLEFT, 5);
    Unit_Command_Unknowns->Add(UnitCommands_Unknown9_Holder, 0, wxTOP | wxLEFT, 5);
    Unit_Command_Unknowns->Add(UnitCommands_SelectionMode_Holder, 0, wxTOP | wxLEFT, 5);
    Unit_Command_Unknowns->Add(UnitCommands_RightClickMode_Holder, 0, wxTOP | wxLEFT, 5);
    Unit_Command_Unknowns->Add(UnitCommands_Unknown12_Holder, 0, wxTOP | wxLEFT, 5);

    Units_CommandHolder_Data->Add(Unit_Command_Known, 0, wxEXPAND);
    Units_CommandHolder_Data->Add(Unit_Command_Unknowns, 0, wxEXPAND);

	Units_CommandsArea_Holder->Add(Units_CommandHolder_Lists, 1, wxEXPAND);
	Units_CommandsArea_Holder->Add(Units_CommandHolder_Data, 3, wxEXPAND, 5);

	Units_UnknownArea_Holder->Add(Units_Type10plusUnknownArea_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_UnknownArea_Holder->Add(Units_Type30plusUnknownArea_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_UnknownArea_Holder->Add(Units_Type70plusUnknownArea_Holder, 0, wxTOP | wxRIGHT, 5);
	Units_UnknownArea_Holder->Add(Units_Type80plusUnknownArea_Holder, 0, wxTOP, 5);

	Units_ScrollSpace->Add(Units_LangDLLArea_Holder, 0, wxEXPAND);
	Units_ScrollSpace->Add(Units_GraphicsArea_Holder, 0, wxEXPAND | wxTOP, 5);
	Units_ScrollSpace->Add(Units_StatsArea_Holder, 0, wxEXPAND | wxTOP, 5);
	Units_ScrollSpace->Add(Units_ProjectilesArea_Holder, 0, wxEXPAND | wxTOP, 5);
	Units_ScrollSpace->Add(Units_Attributes_Holder, 0, wxEXPAND | wxTOP, 5);
	Units_ScrollSpace->Add(Units_SoundsArea_Holder, 0, wxEXPAND | wxTOP, 5);
	Units_ScrollSpace->Add(Units_UnknownArea_Holder, 0, wxEXPAND, 5);
	Units_ScrollSpace->Add(Units_CommandsArea_Holder, 0, wxEXPAND | wxTOP, 5);

	Units_Scroller->SetSizer(Units_ScrollSpace);
	Units_Scroller->SetScrollRate(0, 20);

	Units_Top_Holder->Add(Units_AutoCopy, 0, wxEXPAND);
	Units_Top_Holder->Add(Units_CopyTo, 0, wxEXPAND);
	Units_Top_Holder->Add(Units_CopyGraphics, 0, wxEXPAND | wxLEFT, 5);
	Units_Top_Holder->Add(Units_CopyToText);
	Units_Top_Holder->Add(Units_SelectAll, 0, wxEXPAND);
	Units_Top_Holder->Add(Units_SelectClear, 0, wxEXPAND);
	Units_Top_Holder->Add(Units_GraphicSetText);
	Units_Top_Holder->Add(Units_GraphicSet, 0, wxEXPAND);
	Units_Identity_Holder->Add(Units_Type_Holder, 0, wxEXPAND);
	Units_Identity_Holder->Add(Units_TypeArea_Holder, 0, wxEXPAND | wxTOP, 5);

	Units_DataArea->Add(Units_Top_Holder, 0, wxEXPAND | wxTOP, 15);
	Units_DataArea->Add(Units_TopGrid_Holder, 0, wxEXPAND);
	Units_DataArea->Add(Units_Identity_Holder, 0, wxEXPAND);
	Units_DataArea->Add(Units_Scroller, 1, wxEXPAND | wxTOP, 5);

	Units_Main->Add(Units_Units, 21, wxEXPAND | wxALL, 5);
	Units_Main->Add(Units_DataArea, 65, wxEXPAND | wxBOTTOM | wxRIGHT, 5);

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
	for(size_t loop = 0; loop < 2; ++loop)
	{
		Connect(Units_UseAnd[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsSearch));
		Connect(Units_SearchFilters[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnSelection_SearchFilters));
	}
	Connect(Units_Civs_List->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnitSubList));
	Connect(Units_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnitsSelect));
	Connect(Units_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnUnitsSelect));
	Connect(Units_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnUnitsSelect));
	Connect(Units_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsAdd));
	Connect(Units_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsInsert));
	Connect(Units_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsDelete));
	Connect(Units_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsCopy));
	Connect(Units_SpecialCopy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsSpecialCopy));
	Connect(Units_SpecialPaste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsSpecialPaste));
	Connect(Units_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsPaste));
	Connect(Units_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsPasteInsert));
	Connect(Units_Enable->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsEnable));
	Connect(Units_Disable->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitsDisable));
	Connect(Units_UnitCommands_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnitCommandsSelect));
	Connect(Units_UnitCommands_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnUnitCommandsSelect));
	Connect(Units_UnitCommands_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnUnitCommandsSelect));
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
	Connect(Units_DamageGraphics_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsSelect));
	Connect(Units_DamageGraphics_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsSelect));
	Connect(Units_DamageGraphics_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsSelect));
	Connect(Units_DamageGraphics_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsAdd));
	Connect(Units_DamageGraphics_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsInsert));
	Connect(Units_DamageGraphics_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsDelete));
	Connect(Units_DamageGraphics_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsCopy));
	Connect(Units_DamageGraphics_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsPaste));
	Connect(Units_DamageGraphics_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsPasteInsert));
	Connect(Units_DamageGraphics_CopyToUnits->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitDamageGraphicsCopyToUnits));
	Connect(Units_Attacks_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksSearch));
	Connect(Units_Attacks_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksSearch));
	Connect(Units_Attacks_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksSelect));
	Connect(Units_Attacks_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksSelect));
	Connect(Units_Attacks_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksSelect));
	Connect(Units_Attacks_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksAdd));
	Connect(Units_Attacks_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksInsert));
	Connect(Units_Attacks_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksDelete));
	Connect(Units_Attacks_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksCopy));
	Connect(Units_Attacks_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksPaste));
	Connect(Units_Attacks_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksPasteInsert));
	Connect(Units_Attacks_CopyToUnits->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitAttacksCopyToUnits));
	Connect(Units_Armors_Search->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsSearch));
	Connect(Units_Armors_Search_R->GetId(), wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsSearch));
	Connect(Units_Armors_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsSelect));
	Connect(Units_Armors_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsSelect));
	Connect(Units_Armors_ListV->GetId(), wxEVT_COMMAND_LIST_ITEM_FOCUSED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsSelect));
	Connect(Units_Armors_Add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsAdd));
	Connect(Units_Armors_Insert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsInsert));
	Connect(Units_Armors_Delete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsDelete));
	Connect(Units_Armors_Copy->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsCopy));
	Connect(Units_Armors_Paste->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsPaste));
	Connect(Units_Armors_PasteInsert->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsPasteInsert));
	Connect(Units_Armors_CopyToUnits->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AGE_Frame::OnUnitArmorsCopyToUnits));
	Connect(Units_LanguageDLLConverter[0]->GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(AGE_Frame::UnitLangDLLConverter));
	Connect(Units_LanguageDLLConverter[1]->GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(AGE_Frame::UnitLangDLLConverter));
	Connect(slp_radio->GetId(), wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnChooseGraphic));
	Connect(slp_unit_actions->GetId(), wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnChooseGraphic));
	Connect(slp_dmg_unit->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnChooseGraphic));
	Connect(slp_snow->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnChooseGraphic));
	Connect(slp_garrison->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnChooseGraphic));

    unitTimer.Connect(unitTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnUnitsTimer), NULL, this);
    dmgGraphicTimer.Connect(dmgGraphicTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnUnitDamageGraphicsTimer), NULL, this);
    attackTimer.Connect(attackTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnUnitAttacksTimer), NULL, this);
    armorTimer.Connect(armorTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnUnitArmorsTimer), NULL, this);
    actionTimer.Connect(actionTimer.GetId(), wxEVT_TIMER, wxTimerEventHandler(AGE_Frame::OnUnitCommandsTimer), NULL, this);
	Units_DLL_LanguageName->Connect(Units_DLL_LanguageName->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_LangDLL), NULL, this);
	Units_DLL_LanguageCreation->Connect(Units_DLL_LanguageCreation->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_LangDLL), NULL, this);
	Units_DLL_HotKey4->Connect(Units_DLL_HotKey4->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_LangDLL), NULL, this);
	Units_DLL_LanguageHelp->Connect(Units_DLL_LanguageHelp->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_LangDLL), NULL, this);
	Units_DLL_LanguageHKText->Connect(Units_DLL_LanguageHKText->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_LangDLL), NULL, this);

//	Listing and Auto-Copy

	Units_Type->Connect(Units_Type->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Connect(Units_Type_ComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Units));
	Connect(Units_Type_ComboBox->GetId(), wxEVT_MOUSEWHEEL, wxMouseEventHandler(AGE_Frame::wheelParent));

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
	DamageGraphics_ApplyMode->Connect(DamageGraphics_ApplyMode->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Attacks_Class->Connect(Attacks_Class->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Attacks_Amount->Connect(Attacks_Amount->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Armors_Class->Connect(Armors_Class->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Armors_Amount->Connect(Armors_Amount->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	for(size_t loop = 0; loop < 2; ++loop)
	Attacks_Class_ComboBox[loop]->Connect(Attacks_Class_ComboBox[loop]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Units), NULL, this);

	UnitCommands_Type->Connect(UnitCommands_Type->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	UnitCommands_ProductivityResource->Connect(UnitCommands_ProductivityResource->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Connect(UnitCommands_Type_ComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Units));
	Connect(UnitCommands_Type_ComboBox->GetId(), wxEVT_MOUSEWHEEL, wxMouseEventHandler(AGE_Frame::wheelParent));
	for(size_t loop = 0; loop < 8; ++loop)
	{
		Connect(Units_Attribute_CheckBox[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdateCheck_UnitAttribute));
		Connect(Units_GarrisonType_CheckBox[loop]->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AGE_Frame::OnUpdateCheck_UnitGarrisonType));
	}
	Units_IconID->Connect(Units_IconID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_IconAngle->Connect(Units_IconAngle->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_IconID_SLP->Connect(Units_IconID_SLP->GetId(), wxEVT_PAINT, wxPaintEventHandler(AGE_Frame::OnDrawIconSLP), NULL, this);
    Units_IconID_SLP->Connect(Units_IconID_SLP->GetId(), wxEVT_ERASE_BACKGROUND, wxEraseEventHandler(AGE_Frame::OnGraphicErase), NULL, this);

    // To make SLP view refresh.
	Units_ConstructionGraphicID->Connect(Units_ConstructionGraphicID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_SnowGraphicID->Connect(Units_SnowGraphicID->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_GarrisonGraphic->Connect(Units_GarrisonGraphic->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_ChargingGraphic->Connect(Units_ChargingGraphic->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_AttackGraphic->Connect(Units_AttackGraphic->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_WalkingGraphic[0]->Connect(Units_WalkingGraphic[0]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_WalkingGraphic[1]->Connect(Units_WalkingGraphic[1]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_StandingGraphic[0]->Connect(Units_StandingGraphic[0]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_StandingGraphic[1]->Connect(Units_StandingGraphic[1]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_DyingGraphic[0]->Connect(Units_DyingGraphic[0]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_DyingGraphic[1]->Connect(Units_DyingGraphic[1]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	UnitCommands_Graphics[0]->Connect(UnitCommands_Graphics[0]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	UnitCommands_Graphics[1]->Connect(UnitCommands_Graphics[1]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	UnitCommands_Graphics[2]->Connect(UnitCommands_Graphics[2]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	UnitCommands_Graphics[3]->Connect(UnitCommands_Graphics[3]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_ConstructionGraphicID_ComboBox->Connect(Units_ConstructionGraphicID_ComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Units), NULL, this);
	Units_SnowGraphicID_ComboBox->Connect(Units_SnowGraphicID_ComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Units), NULL, this);
	Units_GarrisonGraphic_ComboBox->Connect(Units_GarrisonGraphic_ComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Units), NULL, this);
	Units_ChargingGraphic_ComboBox->Connect(Units_ChargingGraphic_ComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Units), NULL, this);
	Units_AttackGraphic_ComboBox->Connect(Units_AttackGraphic_ComboBox->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Units), NULL, this);
	Units_WalkingGraphic_ComboBox[0]->Connect(Units_WalkingGraphic_ComboBox[0]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Units), NULL, this);
	Units_WalkingGraphic_ComboBox[1]->Connect(Units_WalkingGraphic_ComboBox[1]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Units), NULL, this);
	Units_StandingGraphic_ComboBox[0]->Connect(Units_StandingGraphic_ComboBox[0]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Units), NULL, this);
	Units_StandingGraphic_ComboBox[1]->Connect(Units_StandingGraphic_ComboBox[1]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Units), NULL, this);
	Units_DyingGraphic_ComboBox[0]->Connect(Units_DyingGraphic_ComboBox[0]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Units), NULL, this);
	Units_DyingGraphic_ComboBox[1]->Connect(Units_DyingGraphic_ComboBox[1]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Units), NULL, this);
	UnitCommands_Graphics_ComboBox[0]->Connect(UnitCommands_Graphics_ComboBox[0]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Units), NULL, this);
	UnitCommands_Graphics_ComboBox[1]->Connect(UnitCommands_Graphics_ComboBox[1]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Units), NULL, this);
	UnitCommands_Graphics_ComboBox[2]->Connect(UnitCommands_Graphics_ComboBox[2]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Units), NULL, this);
	UnitCommands_Graphics_ComboBox[3]->Connect(UnitCommands_Graphics_ComboBox[3]->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AGE_Frame::OnUpdateCombo_Units), NULL, this);
	Units_SizeRadius[0]->Connect(Units_SizeRadius[0]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_SizeRadius[1]->Connect(Units_SizeRadius[1]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_ClearanceSize[0]->Connect(Units_ClearanceSize[0]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_ClearanceSize[1]->Connect(Units_ClearanceSize[1]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_SelectionRadius[0]->Connect(Units_SelectionRadius[0]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
	Units_SelectionRadius[1]->Connect(Units_SelectionRadius[1]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
    for(size_t loop = 0; loop < 4; ++loop)
    {
        Units_AnnexUnitMisplacement[loop][0]->Connect(Units_AnnexUnitMisplacement[loop][0]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
        Units_AnnexUnitMisplacement[loop][1]->Connect(Units_AnnexUnitMisplacement[loop][1]->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(AGE_Frame::OnKillFocus_Units), NULL, this);
    }
}

void AGE_Frame::OnKillFocus_Units(wxFocusEvent &event)
{
	event.Skip();
	if(((AGETextCtrl*)event.GetEventObject())->SaveEdits() != 0) return;
	if(event.GetId() == Units_Name->GetId() || event.GetId() == Units_LanguageDLLName->GetId())
	{
		ListUnits(UnitCivID);
	}
	else if(event.GetId() == Units_Type->GetId()
	|| event.GetId() == Units_Name2->GetId()
	|| event.GetId() == Units_LanguageDLLCreation->GetId()
	|| event.GetId() == Units_HotKey->GetId()
	|| event.GetId() == Units_LanguageDLLHelp->GetId()
	|| event.GetId() == Units_LanguageDLLHotKeyText->GetId()
	|| event.GetId() == Units_Attribute->GetId()
	|| event.GetId() == Units_GarrisonType->GetId()
	|| event.GetId() == Units_IconID->GetId()
	|| event.GetId() == Units_IconAngle->GetId())
	{
		wxTimerEvent E;
		OnUnitsTimer(E);
	}
	else if(event.GetId() == Attacks_Amount->GetId() || event.GetId() == Attacks_Class->GetId())
	{
		ListUnitAttacks();
	}
	else if(event.GetId() == Armors_Amount->GetId() || event.GetId() == Armors_Class->GetId())
	{
		ListUnitArmors();
	}
	else if(event.GetId() == UnitCommands_Type->GetId() || event.GetId() == UnitCommands_ProductivityResource->GetId())
	{
		ListUnitCommands();
	}
	else if(event.GetId() == DamageGraphics_GraphicID->GetId()
    || event.GetId() == DamageGraphics_DamagePercent->GetId())
	{
		ListUnitDamageGraphics();
    }
    else
    {
        wxCommandEvent E;
        OnChooseGraphic(E);
    }
}

void AGE_Frame::OnUpdateCombo_Units(wxCommandEvent &event)
{
	if(event.GetId() == Units_Type_ComboBox->GetId())
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
		wxTimerEvent E;
		OnUnitsTimer(E);	// Updates unit layout.
//		ListUnits(UnitCivID, false);	// For special search filters.
		return;
	}
	if(event.GetId() == UnitCommands_Type_ComboBox->GetId())
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
			case 13: UnitCommands_Type->ChangeValue("14"); break;
			case 14: UnitCommands_Type->ChangeValue("20"); break;
			case 15: UnitCommands_Type->ChangeValue("21"); break;
			case 16: UnitCommands_Type->ChangeValue("101"); break;
			case 17: UnitCommands_Type->ChangeValue("102"); break;
			case 18: UnitCommands_Type->ChangeValue("103"); break;
			case 19: UnitCommands_Type->ChangeValue("104"); break;
			case 20: UnitCommands_Type->ChangeValue("105"); break;
			case 21: UnitCommands_Type->ChangeValue("106"); break;
			case 22: UnitCommands_Type->ChangeValue("107"); break;
			case 23: UnitCommands_Type->ChangeValue("108"); break;
			case 24: UnitCommands_Type->ChangeValue("109"); break;
			case 25: UnitCommands_Type->ChangeValue("110"); break;
			case 26: UnitCommands_Type->ChangeValue("111"); break;
			case 27: UnitCommands_Type->ChangeValue("120"); break;
			case 28: UnitCommands_Type->ChangeValue("121"); break;
			case 29: UnitCommands_Type->ChangeValue("122"); break;
			case 30: UnitCommands_Type->ChangeValue("123"); break;
			case 31: UnitCommands_Type->ChangeValue("124"); break;
			case 32: UnitCommands_Type->ChangeValue("125"); break;
			case 33: UnitCommands_Type->ChangeValue("130"); break;
			case 34: UnitCommands_Type->ChangeValue("131"); break;
			case 35: UnitCommands_Type->ChangeValue("132"); break;
			case 36: UnitCommands_Type->ChangeValue("133"); break;
			case 37: UnitCommands_Type->ChangeValue("134"); break;
			case 38: UnitCommands_Type->ChangeValue("135"); break;
			case 39: UnitCommands_Type->ChangeValue("136"); break;
			case 40: UnitCommands_Type->ChangeValue("149"); break;
			case 41: UnitCommands_Type->ChangeValue("150"); break;
			case 42: UnitCommands_Type->ChangeValue("151"); break;
			default: UnitCommands_Type->ChangeValue("-1");
		}
		UnitCommands_Type->SaveEdits();
		ListUnitCommands();
		return;
	}
	((AGEComboBox*)event.GetEventObject())->OnUpdate(event);
	if(event.GetId() == Attacks_Class_ComboBox[0]->GetId())
	{
		ListUnitAttacks();
	}
	else if(event.GetId() == Attacks_Class_ComboBox[1]->GetId())
	{
		ListUnitArmors();
	}
	else if(event.GetId() == DamageGraphics_GraphicID_ComboBox->GetId())
	{
		ListUnitDamageGraphics();
	}
    else
    {
        wxCommandEvent E;
        OnChooseGraphic(E);
    }
}

void AGE_Frame::OnUpdateCheck_UnitGarrisonType(wxCommandEvent &event)
{
	if(Units_GarrisonType->GetValue().empty()) return;
    try
    {
        uint8_t type = lexical_cast<short>(Units_GarrisonType->GetValue());
        Units_GarrisonType_CheckBox[0]->GetValue() ? type |= 0x01 : type &= ~0x01;
        Units_GarrisonType_CheckBox[1]->GetValue() ? type |= 0x02 : type &= ~0x02;
        Units_GarrisonType_CheckBox[2]->GetValue() ? type |= 0x04 : type &= ~0x04;
        Units_GarrisonType_CheckBox[3]->GetValue() ? type |= 0x08 : type &= ~0x08;
        Units_GarrisonType_CheckBox[4]->GetValue() ? type |= 0x10 : type &= ~0x10;
        Units_GarrisonType_CheckBox[5]->GetValue() ? type |= 0x20 : type &= ~0x20;
        Units_GarrisonType_CheckBox[6]->GetValue() ? type |= 0x40 : type &= ~0x40;
        Units_GarrisonType_CheckBox[7]->GetValue() ? type |= 0x80 : type &= ~0x80;
        Units_GarrisonType->ChangeValue(FormatInt(type));
        Units_GarrisonType->SaveEdits();
    }
    catch(bad_lexical_cast e)
    {
        Units_GarrisonType->clear();
        Units_GarrisonType->ChangeValue("Error");
    }
}

void AGE_Frame::OnUpdateCheck_UnitAttribute(wxCommandEvent &event)
{
	if(Units_Attribute->GetValue().empty()) return;
	try
    {
        uint8_t attribute = lexical_cast<short>(Units_Attribute->GetValue());
        Units_Attribute_CheckBox[0]->GetValue() ? attribute |= 0x01 : attribute &= ~0x01;
        Units_Attribute_CheckBox[1]->GetValue() ? attribute |= 0x02 : attribute &= ~0x02;
        Units_Attribute_CheckBox[2]->GetValue() ? attribute |= 0x04 : attribute &= ~0x04;
        Units_Attribute_CheckBox[3]->GetValue() ? attribute |= 0x08 : attribute &= ~0x08;
        Units_Attribute_CheckBox[4]->GetValue() ? attribute |= 0x10 : attribute &= ~0x10;
        Units_Attribute_CheckBox[5]->GetValue() ? attribute |= 0x20 : attribute &= ~0x20;
        Units_Attribute_CheckBox[6]->GetValue() ? attribute |= 0x40 : attribute &= ~0x40;
        Units_Attribute_CheckBox[7]->GetValue() ? attribute |= 0x80 : attribute &= ~0x80;
        Units_Attribute->ChangeValue(FormatInt(attribute));
        Units_Attribute->SaveEdits();
    }
    catch(bad_lexical_cast e)
    {
        Units_Attribute->clear();
        Units_Attribute->ChangeValue("Error");
    }
}
