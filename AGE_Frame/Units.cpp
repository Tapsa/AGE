#include "../AGE_Frame.h"

wxString AGE_Frame::GetUnitName(int index, short civ, bool Filter)
{
    wxString Name;

    if(dataset->Civs[civ].UnitPointers[index] == 0)
    {
        return "Nonexistent";
    }
    if(Filter)
    {
        genie::Unit *unit_ptr = &dataset->Civs[civ].Units[index];
        for(auto &f: UnitFilterFunctions)
        {
            short NameSize = Name.size(), NameSize0 = NameSize;
            Name += f(unit_ptr);
            Name += NameSize0 == Name.size() ? "NA, " : ", ";
        }
    }

//Names:
    if(useDynamicName && !TranslatedText(dataset->Civs[civ].Units[index].LanguageDLLName, 2).empty())
    {
        return Name + TranslatedText(dataset->Civs[civ].Units[index].LanguageDLLName, 64);
    }
//InternalName:
    if(!dataset->Civs[civ].Units[index].Name.empty())
    {
        return Name + wxString(dataset->Civs[civ].Units[index].Name);
    }
    return Name + "New Unit";
}

#define UF30 unit_ptr->Type < 30 || unit_ptr->Type > 80 ? "" :
#define UF40 unit_ptr->Type < 40 || unit_ptr->Type > 80 ? "" :
#define UF50 unit_ptr->Type < 50 || unit_ptr->Type > 80 ? "" :
#define UF60 unit_ptr->Type != 60 ? "" :
#define UF70 unit_ptr->Type != 70 && unit_ptr->Type != 80 ? "" :
#define UF80 unit_ptr->Type != 80 ? "" :

void AGE_Frame::PrepUnitSearch()
{
    useDynamicName = true;
    UnitFilterFunctions.clear();
    for(size_t loop = 0; loop < 2; ++loop)
    {
        auto selection = Units_SearchFilters[loop]->GetSelection();
        if(selection < 1) continue;
        wxString label = unit_filters[selection];

        if(label.compare(Type20[0]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "T " + FormatInt(unit_ptr->Type);
        });
        else if(label.compare(Type20[1]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "I1 " + FormatInt(unit_ptr->ID);
        });
        else if(label.compare(Type20[2]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "LN " + FormatInt(unit_ptr->LanguageDLLName);
        });
        else if(label.compare(Type20[3]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "LC " + FormatInt(unit_ptr->LanguageDLLCreation);
        });
        else if(label.compare(Type20[4]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "C " + FormatInt(unit_ptr->Class);
        });
        else if(label.compare(Type20[5]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "SG " + FormatInt(unit_ptr->StandingGraphic.first) + " "
                    + FormatInt(unit_ptr->StandingGraphic.second);
        });
        else if(label.compare(Type20[6]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "DG " + FormatInt(unit_ptr->DyingGraphic) + " "
                    + FormatInt(unit_ptr->UndeadGraphic);
        });
        else if(label.compare(Type20[7]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "DM " + FormatInt(unit_ptr->UndeadMode);
        });
        else if(label.compare(Type20[8]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "HP " + FormatInt(unit_ptr->HitPoints);
        });
        else if(label.compare(Type20[9]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "LS " + FormatFloat(unit_ptr->LineOfSight);
        });
        else if(label.compare(Type20[10]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "GC " + FormatInt(unit_ptr->GarrisonCapacity);
        });
        else if(label.compare(Type20[11]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "SR " + FormatFloat(unit_ptr->Size.x) + " "
                    + FormatFloat(unit_ptr->Size.y);
        });
        else if(label.compare(Type20[12]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "B1 " + FormatFloat(unit_ptr->Size.z);
        });
        else if(label.compare(Type20[13]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "TS " + FormatInt(unit_ptr->TrainSound);
        });
        else if(label.compare(Type20[14]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "VS " + FormatInt(unit_ptr->DamageSound);
        });
        else if(label.compare(Type20[15]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "DU " + FormatInt(unit_ptr->DeadUnitID);
        });
        else if(label.compare(Type20[16]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "BU " + FormatInt(unit_ptr->BloodUnitID);
        });
        else if(label.compare(Type20[17]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "PM " + FormatInt(unit_ptr->SortNumber);
        });
        else if(label.compare(Type20[18]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "AM " + FormatInt(unit_ptr->CanBeBuiltOn);
        });
        else if(label.compare(Type20[19]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "I " + FormatInt(unit_ptr->IconID);
        });
        else if(label.compare(Type20[20]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "HE " + FormatInt(unit_ptr->HideInEditor);
        });
        else if(label.compare(Type20[21]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "U1 " + FormatInt(unit_ptr->OldPortraitPict);
        });
        else if(label.compare(Type20[22]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "E " + FormatInt(unit_ptr->Enabled);
        });
        else if(label.compare(Type20[23]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "D " + FormatInt(unit_ptr->Disabled);
        });
        else if(label.compare(Type20[24]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "PBT " + FormatInt(unit_ptr->PlacementSideTerrain.first) + " "
                    + FormatInt(unit_ptr->PlacementSideTerrain.second);
        });
        else if(label.compare(Type20[25]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "PT " + FormatInt(unit_ptr->PlacementTerrain.first) + " "
                    + FormatInt(unit_ptr->PlacementTerrain.second);
        });
        else if(label.compare(Type20[26]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "ER " + FormatFloat(unit_ptr->ClearanceSize.x) + " "
                    + FormatFloat(unit_ptr->ClearanceSize.y);
        });
        else if(label.compare(Type20[27]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "HM " + FormatInt(unit_ptr->HillMode);
        });
        else if(label.compare(Type20[28]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "VF " + FormatInt(unit_ptr->FogVisibility);
        });
        else if(label.compare(Type20[29]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "TR " + FormatInt(unit_ptr->TerrainRestriction);
        });
        else if(label.compare(Type20[30]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "FM " + FormatInt(unit_ptr->FlyMode);
        });
        else if(label.compare(Type20[31]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "RC " + FormatInt(unit_ptr->ResourceCapacity);
        });
        else if(label.compare(Type20[32]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "RD " + FormatFloat(unit_ptr->ResourceDecay);
        });
        else if(label.compare(Type20[33]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "BA " + FormatInt(unit_ptr->BlastDefenseLevel);
        });
        else if(label.compare(Type20[34]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "U2 " + FormatInt(unit_ptr->CombatLevel);
        });
        else if(label.compare(Type20[35]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "IM " + FormatInt(unit_ptr->InteractionMode);
        });
        else if(label.compare(Type20[36]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "MM " + FormatInt(unit_ptr->MinimapMode);
        });
        else if(label.compare(Type20[37]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "CA " + FormatInt(unit_ptr->InterfaceKind);
        });
        else if(label.compare(Type20[38]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "U3A " + FormatFloat(unit_ptr->MultipleAttributeMode);
        });
        else if(label.compare(Type20[39]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "MC " + FormatInt(unit_ptr->MinimapColor);
        });
        else if(label.compare(Type20[40]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "LH " + FormatInt(unit_ptr->LanguageDLLHelp);
        });
        else if(label.compare(Type20[41]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "LT " + FormatInt(unit_ptr->LanguageDLLHotKeyText);
        });
        else if(label.compare(Type20[42]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "HK " + FormatInt(unit_ptr->HotKey);
        });
        else if(label.compare(Type20[43]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "US " + FormatInt(unit_ptr->Recyclable);
        });
        else if(label.compare(Type20[44]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "IG " + FormatInt(unit_ptr->CanBeGathered);
        });
        else if(label.compare(Type20[45]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "DD " + FormatInt(unit_ptr->CreateDoppelgangerOnDeath);
        });
        else if(label.compare(Type20[46]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "GG " + FormatInt(unit_ptr->ResourceGatherGroup);
        });
        else if(label.compare(Type20[47]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "OM " + FormatInt(unit_ptr->OcclusionMode);
        });
        else if(label.compare(Type20[48]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "OT " + FormatInt(unit_ptr->ObstructionType);
        });
        else if(label.compare(Type20[49]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "OC " + FormatInt(unit_ptr->ObstructionClass);
        });
        else if(label.compare(Type20[50]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "A " + FormatInt(unit_ptr->Trait);
        });
        else if(label.compare(Type20[51]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "Ci " + FormatInt(unit_ptr->Civilization);
        });
        else if(label.compare(Type20[52]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "No " + FormatInt(unit_ptr->Nothing);
        });
        else if(label.compare(Type20[53]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "SE " + FormatInt(unit_ptr->SelectionEffect);
        });
        else if(label.compare(Type20[54]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "EC " + FormatInt(unit_ptr->EditorSelectionColour);
        });
        else if(label.compare(Type20[55]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "SS " + FormatFloat(unit_ptr->OutlineSize.x) + " "
                    + FormatFloat(unit_ptr->OutlineSize.y);
        });
        else if(label.compare(Type20[56]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "B2 " + FormatFloat(unit_ptr->HPBarHeight);
        });
        else if(label.compare(Type20[57]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "Ask Tapsa";
        });
        else if(label.compare(Type20[58]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "DC " + FormatInt(unit_ptr->DamageGraphics.size());
        });
        else if(label.compare(Type20[59]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "Ask Tapsa";
        });
        else if(label.compare(Type20[60]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "SSo " + FormatInt(unit_ptr->SelectionSound);
        });
        else if(label.compare(Type20[61]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "DS " + FormatInt(unit_ptr->DyingSound);
        });
        else if(label.compare(Type20[62]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "AtM " + FormatInt(unit_ptr->OldAttackReaction);
        });
        else if(label.compare(Type20[63]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "EM " + FormatInt(unit_ptr->ConvertTerrain);
        });
        else if(label.compare(Type20[64]) == 0)
        {
            useDynamicName = false;
            continue;
        }
        else if(label.compare(Type20[65]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return wxString(unit_ptr->Name2);
        });
        else if(label.compare(Type20[66]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "UL " + FormatInt(unit_ptr->Unitline);
        });
        else if(label.compare(Type20[67]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "MT " + FormatInt(unit_ptr->MinTechLevel);
        });
        else if(label.compare(Type20[68]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "I2 " + FormatInt(unit_ptr->CopyID);
        });
        else if(label.compare(Type20[69]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "I3 " + FormatInt(unit_ptr->BaseID);
        });
        else if(label.compare(Type20[70]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "S " + FormatFloat(unit_ptr->Speed);
        });
        else if(label.compare(Type20[71]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "TI " + FormatInt(unit_ptr->TelemetryID);
        });

        else if(label.compare(Type30[0]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF30 "WG " + FormatInt(unit_ptr->Moving.WalkingGraphic) + " "
                    + FormatInt(unit_ptr->Moving.RunningGraphic);
        });
        else if(label.compare(Type30[1]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF30 "RS " + FormatFloat(unit_ptr->Moving.RotationSpeed);
        });
        else if(label.compare(Type30[2]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF30 "U11 " + FormatInt(unit_ptr->Moving.OldSizeClass);
        });
        else if(label.compare(Type30[3]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF30 "TU " + FormatInt(unit_ptr->Moving.TrackingUnit);
        });
        else if(label.compare(Type30[4]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF30 "UU " + FormatInt(unit_ptr->Moving.TrackingUnitMode);
        });
        else if(label.compare(Type30[5]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF30 "UD " + FormatFloat(unit_ptr->Moving.TrackingUnitDensity);
        });
        else if(label.compare(Type30[6]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF30 "U16 " + FormatInt(unit_ptr->Moving.OldMoveAlgorithm);
        });
        else if(label.compare(Type30[7]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF30 "r" + FormatFloat(unit_ptr->Moving.TurnRadius)
                    + " s" + FormatFloat(unit_ptr->Moving.TurnRadiusSpeed)
                    + " m" + FormatFloat(unit_ptr->Moving.MaxYawPerSecondMoving)
                    + " t" + FormatFloat(unit_ptr->Moving.StationaryYawRevolutionTime)
                    + " y" + FormatFloat(unit_ptr->Moving.MaxYawPerSecondStationary);
        });

        else if(label.compare(Type40[0]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "SC " + FormatInt(unit_ptr->Action.DefaultTaskID);
        });
        else if(label.compare(Type40[1]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "SR " + FormatFloat(unit_ptr->Action.SearchRadius);
        });
        else if(label.compare(Type40[2]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "WR " + FormatFloat(unit_ptr->Action.WorkRate);
        });
        else if(label.compare(Type40[3]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "DS " + FormatInt(unit_ptr->Action.DropSite.first) + " "
                    + FormatInt(unit_ptr->Action.DropSite.second);
        });
        else if(label.compare(Type40[4]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "VM " + FormatInt(unit_ptr->Action.TaskSwapGroup);
        });
        else if(label.compare(Type40[5]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "AS " + FormatInt(unit_ptr->Action.AttackSound);
        });
        else if(label.compare(Type40[6]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "MS " + FormatInt(unit_ptr->Action.MoveSound);
        });
        else if(label.compare(Type40[7]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "AM " + FormatInt(unit_ptr->Action.RunPattern);
        });
        else if(label.compare(Type40[8]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "CC " + FormatInt(unit_ptr->Action.TaskList.size());
        });
        else if(label.compare(Type40[9]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "Ask Tapsa";
        });

        if(label.compare(Type50[0]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "DA " + FormatInt(unit_ptr->Combat.BaseArmor);
        });
        else if(label.compare(Type50[1]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "AtC " + FormatInt(unit_ptr->Combat.Attacks.size());
        });
        else if(label.compare(Type50[2]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            wxString name = "";
            for(size_t i = 0; i < unit_ptr->Combat.Attacks.size(); ++i)
            name += "c" + FormatInt(unit_ptr->Combat.Attacks[i].Class) + " ";
            return UF50 name;
        });
        else if(label.compare(Type50[3]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "ArC " + FormatInt(unit_ptr->Combat.Armours.size());
        });
        else if(label.compare(Type50[4]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            wxString name = "";
            for(size_t i = 0; i < unit_ptr->Combat.Armours.size(); ++i)
            name += "c" + FormatInt(unit_ptr->Combat.Armours[i].Class) + " ";
            return UF50 name;
        });
        else if(label.compare(Type50[5]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "TR " + FormatInt(unit_ptr->Combat.DefenseTerrainBonus);
        });
        else if(label.compare(Type50[6]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "MaR " + FormatFloat(unit_ptr->Combat.MaxRange);
        });
        else if(label.compare(Type50[7]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "BR " + FormatFloat(unit_ptr->Combat.BlastWidth);
        });
        else if(label.compare(Type50[8]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "RT " + FormatFloat(unit_ptr->Combat.ReloadTime);
        });
        else if(label.compare(Type50[9]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "PU " + FormatInt(unit_ptr->Combat.ProjectileUnitID);
        });
        else if(label.compare(Type50[10]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "AP " + FormatInt(unit_ptr->Combat.AccuracyPercent);
        });
        else if(label.compare(Type50[11]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "TM " + FormatInt(unit_ptr->Combat.BreakOffCombat);
        });
        else if(label.compare(Type50[12]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "D " + FormatInt(unit_ptr->Combat.FrameDelay);
        });
        else if(label.compare(Type50[13]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "x" + FormatFloat(unit_ptr->Combat.GraphicDisplacement[0])
                    + " y" + FormatFloat(unit_ptr->Combat.GraphicDisplacement[1])
                    + " z" + FormatFloat(unit_ptr->Combat.GraphicDisplacement[2]);
        });
        else if(label.compare(Type50[14]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "BL " + FormatInt(unit_ptr->Combat.BlastAttackLevel);
        });
        else if(label.compare(Type50[15]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "MiR " + FormatFloat(unit_ptr->Combat.MinRange);
        });
        else if(label.compare(Type50[16]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "AE " + FormatFloat(unit_ptr->Combat.AccuracyDispersion);
        });
        else if(label.compare(Type50[17]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "AG " + FormatInt(unit_ptr->Combat.AttackGraphic);
        });
        else if(label.compare(Type50[18]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "DM " + FormatInt(unit_ptr->Combat.DisplayedMeleeArmour);
        });
        else if(label.compare(Type50[19]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "DP " + FormatInt(unit_ptr->Combat.DisplayedAttack);
        });
        else if(label.compare(Type50[20]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "DR " + FormatFloat(unit_ptr->Combat.DisplayedRange);
        });
        else if(label.compare(Type50[21]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "DT " + FormatFloat(unit_ptr->Combat.DisplayedReloadTime);
        });

        else if(label.compare(Type60[0]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF60 "SM " + FormatInt(unit_ptr->Missile.ProjectileType);
        });
        else if(label.compare(Type60[1]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF60 "CM " + FormatInt(unit_ptr->Missile.SmartMode);
        });
        else if(label.compare(Type60[2]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF60 "DA " + FormatInt(unit_ptr->Missile.HitMode);
        });
        else if(label.compare(Type60[3]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF60 "PM " + FormatInt(unit_ptr->Missile.VanishMode);
        });
        else if(label.compare(Type60[4]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF60 "U24 " + FormatInt(unit_ptr->Missile.AreaEffectSpecials);
        });
        else if(label.compare(Type60[5]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF60 "PA " + FormatFloat(unit_ptr->Missile.ProjectileArc);
        });

        else if(label.compare(Type70[0]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "Ask Tapsa";
        });
        else if(label.compare(Type70[1]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "TT " + FormatInt(unit_ptr->Creatable.TrainTime);
        });
        else if(label.compare(Type70[2]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "TL " + FormatInt(unit_ptr->Creatable.TrainLocationID);
        });
        else if(label.compare(Type70[3]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "B " + FormatInt(unit_ptr->Creatable.ButtonID);
        });
        else if(label.compare(Type70[4]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "U26 " + FormatFloat(unit_ptr->Creatable.RearAttackModifier);
        });
        else if(label.compare(Type70[5]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "U27 " + FormatFloat(unit_ptr->Creatable.FlankAttackModifier);
        });
        else if(label.compare(Type70[6]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "U28 " + FormatInt(unit_ptr->Creatable.CreatableType);
        });
        else if(label.compare(Type70[7]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "HM " + FormatInt(unit_ptr->Creatable.HeroMode);
        });
        else if(label.compare(Type70[8]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "GG " + FormatInt(unit_ptr->Creatable.GarrisonGraphic);
        });
        else if(label.compare(Type70[9]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "Di " + FormatFloat(unit_ptr->Creatable.TotalProjectiles);
        });
        else if(label.compare(Type70[10]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "Da " + FormatInt(unit_ptr->Creatable.MaxTotalProjectiles);
        });
        else if(label.compare(Type70[11]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "x" + FormatFloat(unit_ptr->Creatable.ProjectileSpawningArea[0])
                    + " y" + FormatFloat(unit_ptr->Creatable.ProjectileSpawningArea[1])
                    + " z" + FormatFloat(unit_ptr->Creatable.ProjectileSpawningArea[2]);
        });
        else if(label.compare(Type70[12]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "AP " + FormatInt(unit_ptr->Creatable.SecondaryProjectileUnit);
        });
        else if(label.compare(Type70[13]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "CG " + FormatInt(unit_ptr->Creatable.SpecialGraphic);
        });
        else if(label.compare(Type70[14]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "CM " + FormatInt(unit_ptr->Creatable.SpecialAbility);
        });
        else if(label.compare(Type70[15]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "DP " + FormatInt(unit_ptr->Creatable.DisplayedPierceArmour);
        });

        else if(label.compare(Type80[0]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "CG " + FormatInt(unit_ptr->Building.ConstructionGraphicID);
        });
        else if(label.compare(Type80[1]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "SG " + FormatInt(unit_ptr->Building.SnowGraphicID);
        });
        else if(label.compare(Type80[2]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "AM " + FormatInt(unit_ptr->Building.AdjacentMode);
        });
        else if(label.compare(Type80[3]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "GA " + FormatInt(unit_ptr->Building.GraphicsAngle);
        });
        else if(label.compare(Type80[4]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "DB " + FormatInt(unit_ptr->Building.DisappearsWhenBuilt);
        });
        else if(label.compare(Type80[5]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "SU " + FormatInt(unit_ptr->Building.StackUnitID);
        });
        else if(label.compare(Type80[6]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "FT " + FormatInt(unit_ptr->Building.FoundationTerrainID);
        });
        else if(label.compare(Type80[7]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "OT " + FormatInt(unit_ptr->Building.OldOverlayID);
        });
        else if(label.compare(Type80[8]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "R " + FormatInt(unit_ptr->Building.TechID);
        });
        else if(label.compare(Type80[9]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "U33 " + FormatInt(unit_ptr->Building.CanBurn);
        });
        else if(label.compare(Type80[10]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "Ask Tapsa";
        });
        else if(label.compare(Type80[11]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "HU " + FormatInt(unit_ptr->Building.HeadUnit);
        });
        else if(label.compare(Type80[12]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "TU " + FormatInt(unit_ptr->Building.TransformUnit);
        });
        else if(label.compare(Type80[13]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "US " + FormatInt(unit_ptr->Building.TransformSound);
        });
        else if(label.compare(Type80[14]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "CS " + FormatInt(unit_ptr->Building.ConstructionSound);
        });
        else if(label.compare(Type80[15]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "GT " + FormatInt(unit_ptr->Building.GarrisonType);
        });
        else if(label.compare(Type80[16]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "GH " + FormatFloat(unit_ptr->Building.GarrisonHealRate);
        });
        else if(label.compare(Type80[17]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "U35 " + FormatFloat(unit_ptr->Building.GarrisonRepairRate);
        });
        else if(label.compare(Type80[18]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "PU " + FormatInt(unit_ptr->Building.PileUnit);
        });
        else if(label.compare(Type80[19]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "Ask Tapsa";
        });
    }
}

void AGE_Frame::OnUnitsSearch(wxCommandEvent&)
{
    short Selection = Units_Civs_List->GetSelection();
    if(Selection == wxNOT_FOUND) return;

    How2List = SEARCH;
    ListUnits(Selection, false);
}

void AGE_Frame::ListUnits(short civ, bool all)
{
    InitUnits(civ, all);
    wxCommandEvent e;
    OnUnitSelect(e);
}

void AGE_Frame::InitUnits(short civ, bool all)
{
    InitSearch(Units_Search->GetValue().MakeLower(), Units_Search_R->GetValue().MakeLower());
    SearchAnd = Units_UseAnd[0]->GetValue();
    ExcludeAnd = Units_UseAnd[1]->GetValue();
    PrepUnitSearch();

    Units_Civs_List->SetSelection(civ);

    Units_ListV->Sweep();
    if(all)
    {
        unit_names.Clear();
        unit_names.Alloc(1 + dataset->Civs.front().Units.size());
        unit_names.Add("-1 - None");
    }

    short matcher = genie::Unit::TreeType;
    switch(Units_FilterSelector->GetSelection())
    {
        case 0: matcher = genie::Unit::DoppelgangerType; break;
        case 1: matcher = genie::Unit::MovingType; break;
        case 2: matcher = genie::Unit::ActionType; break;
        case 3: matcher = genie::Unit::CombatantType; break;
        case 4: matcher = genie::Unit::MissileType; break;
        case 5: matcher = genie::Unit::CreatableType; break;
        case 6: matcher = genie::Unit::BuildingType; break;
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
            unit_names.Add(FormatInt(loop)+" - "+name);
        }
        if(matcher > genie::Unit::DoppelgangerType)
        {
            if(matcher == genie::Unit::MissileType)
            if(dataset->Civs[civ].Units[loop].Type != genie::Unit::MissileType) continue;
            if(dataset->Civs[civ].Units[loop].Type < matcher) continue;
            if(dataset->Civs[civ].Units[loop].Type == genie::Unit::TreeType) continue;
        }
        wxString Name = FormatInt(loop)+" - "+GetUnitName(loop, civ, true);
        if(SearchMatches(" " + Name.Lower() + " "))
        {
            Units_ListV->names.Add(Name);
            Units_ListV->indexes.push_back(loop);
        }
    }

    RefreshList(Units_ListV, &UnitIDs);
    if(all)
    {
        for(auto &list: UnitComboBoxList) list->Flash();
        if(GenieVersion >= genie::GV_AoKA)
        {
            TechTrees_Ages_Items.ItemCombo->Flash();
            TechTrees_Buildings_Items.ItemCombo->Flash();
            TechTrees_Units_Items.ItemCombo->Flash();
            TechTrees_Researches_Items.ItemCombo->Flash();
        }
    }

    SearchAnd = ExcludeAnd = false;
}

void AGE_Frame::OnChooseGraphic(wxCommandEvent&)
{
    if(UnitIDs.size() && dataset && UnitCivID < dataset->Civs.size() && UnitIDs.front() < dataset->Civs[UnitCivID].Units.size())
    {
        museum.datID = loadChosenGraphic(UnitIDs.front());
        museum.slpID = RELOAD;
        if(slp_window) slp_view->Refresh();
    }
}

void AGE_Frame::OnUnitSelect(wxCommandEvent &event)
{
    auto selections = Units_ListV->GetSelectedCount();

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
    Units_CopyID->clear();
    Units_BaseID->clear();

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
                    Units_OldOverlayID->prepend(&UnitPointer->Building.OldOverlayID);
                    Units_ResearchID->prepend(&UnitPointer->Building.TechID);
                    if(GenieVersion >= genie::GV_AoKE3)
                    {
                        if(GenieVersion >= genie::GV_TC)
                        {
                            if(CopyGraphics || vecCiv == 0)
                            Units_SnowGraphicID->prepend(&UnitPointer->Building.SnowGraphicID);
                        }
                        Units_CanBurn->prepend(&UnitPointer->Building.CanBurn);
                        for(size_t loop = 0; loop < 4; ++loop)
                        {
                            Units_AnnexUnit[loop]->prepend(&UnitPointer->Building.Annexes[loop].UnitID);
                            Units_AnnexUnitMisplacement[loop][0]->prepend(&UnitPointer->Building.Annexes[loop].Misplacement.first);
                            Units_AnnexUnitMisplacement[loop][1]->prepend(&UnitPointer->Building.Annexes[loop].Misplacement.second);
                        }
                        if(GenieVersion >= genie::GV_AoKA)
                        Units_HeadUnit->prepend(&UnitPointer->Building.HeadUnit);
                        Units_TransformUnit->prepend(&UnitPointer->Building.TransformUnit);
                        Units_TransformSound->prepend(&UnitPointer->Building.TransformSound);
                        Units_GarrisonType->prepend(&UnitPointer->Building.GarrisonType);
                        Units_GarrisonHealRate->prepend(&UnitPointer->Building.GarrisonHealRate);
                        Units_GarrisonRepairRate->prepend(&UnitPointer->Building.GarrisonRepairRate);
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
                        Units_CostUsed[loop]->prepend(&UnitPointer->Creatable.ResourceCosts[loop].Paid);
                    }
                    Units_TrainTime->prepend(&UnitPointer->Creatable.TrainTime);
                    Units_TrainLocationID->prepend(&UnitPointer->Creatable.TrainLocationID);
                    Units_ButtonID->prepend(&UnitPointer->Creatable.ButtonID);
                    if(GenieVersion >= genie::GV_AoKE3)
                    {
                        Units_RearAttackModifier->prepend(&UnitPointer->Creatable.RearAttackModifier);
                        Units_FlankAttackModifier->prepend(&UnitPointer->Creatable.FlankAttackModifier);
                        Units_CreatableType->prepend(&UnitPointer->Creatable.CreatableType);
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
                    Units_BaseArmor->prepend(&UnitPointer->Combat.BaseArmor);
                    Units_DefenseTerrainBonus->prepend(&UnitPointer->Combat.DefenseTerrainBonus);
                    Units_MaxRange->prepend(&UnitPointer->Combat.MaxRange);
                    Units_BlastWidth->prepend(&UnitPointer->Combat.BlastWidth);
                    Units_ReloadTime->prepend(&UnitPointer->Combat.ReloadTime);
                    Units_ProjectileUnitID->prepend(&UnitPointer->Combat.ProjectileUnitID);
                    Units_AccuracyPercent->prepend(&UnitPointer->Combat.AccuracyPercent);
                    Units_TowerMode->prepend(&UnitPointer->Combat.BreakOffCombat);
                    Units_Delay->prepend(&UnitPointer->Combat.FrameDelay);
                    for(size_t loop = 0; loop < 3; ++loop)
                    {
                        Units_GraphicDisplacement[loop]->prepend(&UnitPointer->Combat.GraphicDisplacement[loop]);
                    }
                    Units_BlastAttackLevel->prepend(&UnitPointer->Combat.BlastAttackLevel);
                    Units_MinRange->prepend(&UnitPointer->Combat.MinRange);
                    if(GenieVersion >= genie::GV_AoKB)
                    {
                        Units_AccuracyDispersion->prepend(&UnitPointer->Combat.AccuracyDispersion);
                    }
                    if(CopyGraphics || vecCiv == 0)
                    Units_AttackGraphic->prepend(&UnitPointer->Combat.AttackGraphic);
                    Units_DisplayedMeleeArmour->prepend(&UnitPointer->Combat.DisplayedMeleeArmour);
                    Units_DisplayedAttack->prepend(&UnitPointer->Combat.DisplayedAttack);
                    Units_DisplayedRange->prepend(&UnitPointer->Combat.DisplayedRange);
                    Units_DisplayedReloadTime->prepend(&UnitPointer->Combat.DisplayedReloadTime);
                }
                case 40:
                {
                    Units_DefaultTaskID->prepend(&UnitPointer->Action.DefaultTaskID);
                    Units_SearchRadius->prepend(&UnitPointer->Action.SearchRadius);
                    Units_WorkRate->prepend(&UnitPointer->Action.WorkRate);
                    Units_DropSite[0]->prepend(&UnitPointer->Action.DropSite.first);
                    Units_DropSite[1]->prepend(&UnitPointer->Action.DropSite.second);
                    Units_TaskSwapGroup->prepend(&UnitPointer->Action.TaskSwapGroup);
                    Units_AttackSound->prepend(&UnitPointer->Action.AttackSound);
                    Units_MoveSound->prepend(&UnitPointer->Action.MoveSound);
                    Units_RunPattern->prepend(&UnitPointer->Action.RunPattern);
                }
                case 30:
                {
                    if(CopyGraphics || vecCiv == 0)
                    {
                        Units_WalkingGraphic[0]->prepend(&UnitPointer->Moving.WalkingGraphic);
                        Units_WalkingGraphic[1]->prepend(&UnitPointer->Moving.RunningGraphic);
                    }
                    Units_RotationSpeed->prepend(&UnitPointer->Moving.RotationSpeed);
                    Units_SizeClass->prepend(&UnitPointer->Moving.OldSizeClass);
                    Units_TrackingUnit->prepend(&UnitPointer->Moving.TrackingUnit);
                    Units_TrackingUnitMode->prepend(&UnitPointer->Moving.TrackingUnitMode);
                    Units_TrackingUnitDensity->prepend(&UnitPointer->Moving.TrackingUnitDensity);
                    Units_MoveAlgorithm->prepend(&UnitPointer->Moving.OldMoveAlgorithm);
                    if(GenieVersion >= genie::GV_AoKB)
                    {
                        Units_RotationAngles[0]->prepend(&UnitPointer->Moving.TurnRadius);
                        Units_RotationAngles[1]->prepend(&UnitPointer->Moving.TurnRadiusSpeed);
                        Units_RotationAngles[2]->prepend(&UnitPointer->Moving.MaxYawPerSecondMoving);
                        Units_RotationAngles[3]->prepend(&UnitPointer->Moving.StationaryYawRevolutionTime);
                        Units_RotationAngles[4]->prepend(&UnitPointer->Moving.MaxYawPerSecondStationary);
                    }
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
                    Units_ID1->prepend(&UnitPointer->ID);
                    Units_LanguageDLLName->prepend(&UnitPointer->LanguageDLLName);
                    Units_LanguageDLLCreation->prepend(&UnitPointer->LanguageDLLCreation);
                    Units_Class->prepend(&UnitPointer->Class);
                    if(CopyGraphics || vecCiv == 0)
                    {
                        Units_StandingGraphic[0]->prepend(&UnitPointer->StandingGraphic.first);
                        Units_DyingGraphic[0]->prepend(&UnitPointer->DyingGraphic);
                        Units_DyingGraphic[1]->prepend(&UnitPointer->UndeadGraphic);
                        Units_IconID->prepend(&UnitPointer->IconID);
                        Units_Portrait->prepend(&UnitPointer->OldPortraitPict);
                    }
                    Units_UndeadMode->prepend(&UnitPointer->UndeadMode);
                    Units_HitPoints->prepend(&UnitPointer->HitPoints);
                    Units_LineOfSight->prepend(&UnitPointer->LineOfSight);
                    Units_GarrisonCapacity->prepend(&UnitPointer->GarrisonCapacity);
                    Units_SizeRadius[0]->prepend(&UnitPointer->Size.x);
                    Units_SizeRadius[1]->prepend(&UnitPointer->Size.y);
                    Units_HPBarHeight1->prepend(&UnitPointer->Size.z);
                    Units_TrainSound->prepend(&UnitPointer->TrainSound);
                    Units_DeadUnitID->prepend(&UnitPointer->DeadUnitID);
                    Units_SortNumber->prepend(&UnitPointer->SortNumber);
                    Units_CanBeBuiltOn->prepend(&UnitPointer->CanBeBuiltOn);
                    Units_HideInEditor->prepend(&UnitPointer->HideInEditor);
                    Units_PlacementSideTerrain[0]->prepend(&UnitPointer->PlacementSideTerrain.first);
                    Units_PlacementSideTerrain[1]->prepend(&UnitPointer->PlacementSideTerrain.second);
                    Units_PlacementTerrain[0]->prepend(&UnitPointer->PlacementTerrain.first);
                    Units_PlacementTerrain[1]->prepend(&UnitPointer->PlacementTerrain.second);
                    Units_ClearanceSize[0]->prepend(&UnitPointer->ClearanceSize.x);
                    Units_ClearanceSize[1]->prepend(&UnitPointer->ClearanceSize.y);
                    Units_HillMode->prepend(&UnitPointer->HillMode);
                    Units_FogVisibility->prepend(&UnitPointer->FogVisibility);
                    Units_TerrainRestriction->prepend(&UnitPointer->TerrainRestriction);
                    Units_FlyMode->prepend(&UnitPointer->FlyMode);
                    Units_ResourceCapacity->prepend(&UnitPointer->ResourceCapacity);
                    Units_ResourceDecay->prepend(&UnitPointer->ResourceDecay);
                    Units_BlastDefenseLevel->prepend(&UnitPointer->BlastDefenseLevel);
                    Units_CombatLevel->prepend(&UnitPointer->CombatLevel);
                    Units_InteractionMode->prepend(&UnitPointer->InteractionMode);
                    Units_MinimapMode->prepend(&UnitPointer->MinimapMode);
                    Units_SelectionEffect->prepend(&UnitPointer->SelectionEffect);
                    Units_EditorSelectionColour->prepend(&UnitPointer->EditorSelectionColour);
                    if(GenieVersion >= genie::GV_AoKE3)
                    {
                        Units_DamageSound->prepend(&UnitPointer->DamageSound);
                        Units_OcclusionMode->prepend(&UnitPointer->OcclusionMode);
                        if(GenieVersion >= genie::GV_AoKA)
                        {
                            Units_BaseID->prepend(&UnitPointer->BaseID);
                            if(GenieVersion >= genie::GV_AoKB)
                            {
                                if(CopyGraphics || vecCiv == 0)
                                Units_StandingGraphic[1]->prepend(&UnitPointer->StandingGraphic.second);
                                if(GenieVersion >= genie::GV_AoK)
                                {
                                    Units_Disabled->prepend(&UnitPointer->Disabled);
                                    if(GenieVersion >= genie::GV_TC)
                                    {
                                        Units_Trait->prepend(&UnitPointer->Trait);
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
                            OBSTRUCTIONS:
                            Units_ObstructionType->prepend(&UnitPointer->ObstructionType);
                            Units_ObstructionClass->prepend(&UnitPointer->ObstructionClass);
                        }
                    }
                    else if(GenieVersion >= genie::GV_Tapsa && GenieVersion <= genie::GV_LatestTap)
                    {
                        Units_BloodUnitID->prepend(&UnitPointer->BloodUnitID);
                        Units_TelemetryID->prepend(&UnitPointer->TelemetryID);
                        goto OBSTRUCTIONS;
                    }
                    Units_Enabled->prepend(&UnitPointer->Enabled);
                    Units_InterfaceKind->prepend(&UnitPointer->InterfaceKind);
                    Units_MultipleAttributeMode->prepend(&UnitPointer->MultipleAttributeMode);
                    Units_MinimapColor->prepend(&UnitPointer->MinimapColor);
                    Units_LanguageDLLHelp->prepend(&UnitPointer->LanguageDLLHelp);
                    Units_LanguageDLLHotKeyText->prepend(&UnitPointer->LanguageDLLHotKeyText);
                    Units_HotKey->prepend(&UnitPointer->HotKey);
                    Units_Recyclable->prepend(&UnitPointer->Recyclable);
                    Units_TrackAsResource->prepend(&UnitPointer->CanBeGathered);
                    Units_CreateDoppelgangerOnDeath->prepend(&UnitPointer->CreateDoppelgangerOnDeath);
                    Units_ResourceGroup->prepend(&UnitPointer->ResourceGatherGroup);
                    Units_SelectionRadius[0]->prepend(&UnitPointer->OutlineSize.x);
                    Units_SelectionRadius[1]->prepend(&UnitPointer->OutlineSize.y);
                    Units_HPBarHeight2->prepend(&UnitPointer->HPBarHeight);
                    Units_SelectionSound->prepend(&UnitPointer->SelectionSound);
                    Units_DyingSound->prepend(&UnitPointer->DyingSound);
                    Units_AttackReaction->prepend(&UnitPointer->OldAttackReaction);
                    Units_ConvertTerrain->prepend(&UnitPointer->ConvertTerrain);
                    Units_Name->prepend(&UnitPointer->Name);
                    Units_CopyID->prepend(&UnitPointer->CopyID);
                    for(size_t loop = 0; loop < 3; ++loop)
                    {
                        ResourceStorage_Type[loop]->prepend(&UnitPointer->ResourceStorages[loop].Type);
                        ResourceStorage_Amount[loop]->prepend(&UnitPointer->ResourceStorages[loop].Amount);
                        ResourceStorage_Mode[loop]->prepend(&UnitPointer->ResourceStorages[loop].Paid);
                    }
                }
            }
            if(unitType == 60)
            {
                Units_ProjectileType->prepend(&UnitPointer->Missile.ProjectileType);
                Units_SmartMode->prepend(&UnitPointer->Missile.SmartMode);
                Units_HitMode->prepend(&UnitPointer->Missile.HitMode);
                Units_VanishMode->prepend(&UnitPointer->Missile.VanishMode);
                Units_AreaEffectSpecials->prepend(&UnitPointer->Missile.AreaEffectSpecials);
                Units_ProjectileArc->prepend(&UnitPointer->Missile.ProjectileArc);
            }
        }
    }
    SetStatusText("Civilization: "+std::to_string(UnitCivID)+"    Selections: "+std::to_string(selections)+"    Selected unit: "+std::to_string(UnitIDs.front()), 0);

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
                Units_Trait_CheckBox[0]->SetValue(UnitPointer->Trait & 0x01);
                Units_Trait_CheckBox[1]->SetValue(UnitPointer->Trait & 0x02);
                Units_Trait_CheckBox[2]->SetValue(UnitPointer->Trait & 0x04);
                Units_Trait_CheckBox[3]->SetValue(UnitPointer->Trait & 0x08);
                Units_Trait_CheckBox[4]->SetValue(UnitPointer->Trait & 0x10);
                Units_Trait_CheckBox[5]->SetValue(UnitPointer->Trait & 0x20);
                Units_Trait_CheckBox[6]->SetValue(UnitPointer->Trait & 0x40);
                Units_Trait_CheckBox[7]->SetValue(UnitPointer->Trait & 0x80);
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
            string newLabel = " ( ", aste = "°";
            const float closure = 57.2957802f;

            #define UGLY_CODE if(angle == 0x80000000) newLabel += "max" + aste;\
            else newLabel += std::to_string(angle) + aste;

            int angle = UnitPointer->Moving.TurnRadius * closure; UGLY_CODE
            angle = UnitPointer->Moving.TurnRadiusSpeed * closure; UGLY_CODE
            angle = UnitPointer->Moving.MaxYawPerSecondMoving * closure; UGLY_CODE
            angle = UnitPointer->Moving.StationaryYawRevolutionTime * closure; UGLY_CODE
            angle = UnitPointer->Moving.MaxYawPerSecondStationary * closure; UGLY_CODE

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
        museum.datID = loadChosenGraphic(UnitIDs.front());
        museum.slpID = RELOAD;
    }
    else
    {
        visibleUnitCiv->SetLabel("None");
        iconSLP.slpID = museum.datID = -1;
    }
    Units_DLL_LanguageName->SetLabel(TranslatedText(Units_DLL_LanguageName->index, 64));
    Units_DLL_LanguageCreation->SetLabel(TranslatedText(Units_DLL_LanguageCreation->index, 64));
    Units_DLL_LanguageHelp->SetLabel(TranslatedText(Units_DLL_LanguageHelp->index, 512));
    Units_LanguageDLLConverter[0]->SetLabel(std::to_string(Units_DLL_LanguageHelp->index));
    Units_DLL_LanguageHKText->SetLabel(TranslatedText(Units_DLL_LanguageHKText->index, 64));
    Units_LanguageDLLConverter[1]->SetLabel(std::to_string(Units_DLL_LanguageHKText->index));
    Units_DLL_HotKey4->SetLabel(TranslatedText(Units_DLL_HotKey4->index, 16));

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
    if(GenieVersion >= genie::GV_AoK)   // AoK, TC, SWGB or CC
    {
        genie::UnitHeader * UnitHeadPointer;
        for(auto sel = selections; sel--> 0;)
        {
            UnitHeadPointer = &dataset->UnitHeaders[UnitIDs[sel]];

            Units_Exists->prepend(&UnitHeadPointer->Exists);
        }

        Units_UnitHeads_Name->SetLabel(" "+std::to_string(UnitIDs.front())+" - "+GetUnitName(UnitIDs.front(), 0));
    }
    else    // AoE or RoR
    {
        Units_UnitHeads_Name->SetLabel("");
    }
    ListUnitCommands();

    AGE_SLP::setbearing = 1u;
    for(auto &box: uiGroupUnit) box->update();
    Units_ID1->refill();
    Units_CopyID->refill();
    Units_BaseID->refill();
    //  Refresh(); // Too much lag.
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
    if(UseDRS && LoadSLP(&iconSLP)) FrameToBitmap(&iconSLP);
    if(iconSLP.image.IsOk()) {
    dc.DrawBitmap(wxBitmap(iconSLP.image, 24), 0, 0, true);
    }
    else dc.DrawLabel("!SLP/frame " + FormatInt(iconSLP.slpID), wxNullBitmap, wxRect(0, 0, 100, 40));
}

int AGE_Frame::loadChosenGraphic(unsigned int unitID)
{
    genie::Unit *unit = &dataset->Civs[UnitCivID].Units[unitID];
    if(slp_unit_actions->GetSelection() && CommandIDs.size())
    {
        genie::Task *action = 0;
        if(GenieVersion >= genie::GV_AoK)
        {
            if(CommandIDs.front() < dataset->UnitHeaders[unitID].TaskList.size())
            action = &dataset->UnitHeaders[unitID].TaskList[CommandIDs.front()];
        }
        else
        {
            if(CommandIDs.front() < unit->Action.TaskList.size())
            action = &unit->Action.TaskList[CommandIDs.front()];
        }
        if(!action) goto CHOOSE_NORMAL;
        int graphicID;
        switch(slp_unit_actions->GetSelection())
        {
            case 1: graphicID = action->MovingGraphicID; break;
            case 2: graphicID = action->ProceedingGraphicID; break;
            case 3: graphicID = action->WorkingGraphicID; break;
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
        case 2: return unit->DyingGraphic;
        case 3: return unit->UndeadGraphic;
        case 4: return unit->Moving.WalkingGraphic;
        case 5: return unit->Moving.RunningGraphic;
        case 6: return unit->Building.ConstructionGraphicID;
        case 7: return unit->Combat.AttackGraphic;
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
                museum.deltas.clear();
                break;
            }
            else return;
        case 2: unitGraphic = dataset->Civs[UnitCivID].Units[unitID].Building.SnowGraphicID; break;
        case 3: unitGraphic = dataset->Civs[UnitCivID].Units[unitID].Creatable.GarrisonGraphic; break;
    }
    if(unitGraphic >= dataset->Graphics.size()) return;
    AGE_SLP baseSLP;
    bool has_base = initArt(baseSLP, unitGraphic);
    if(has_base) museum.angles = max(museum.angles, baseSLP.angles);
    if(dataset->Graphics[unitGraphic].Deltas.size())
    for(auto const &delta: dataset->Graphics[unitGraphic].Deltas)
    {
        AGE_SLP art;
        if(delta.GraphicID < dataset->Graphics.size())
        {
            if(initArt(art, delta.GraphicID))
            {
                museum.angles = max(museum.angles, art.angles);
            }
            else continue;
        }
        else if(has_base)
        {
            initArt(art, unitGraphic);
        }
        else continue;
        art.xdelta = delta.OffsetX + offsetX;
        art.ydelta = delta.OffsetY + offsetY;
        SetDisplayBearings(art, delta);
        museum.deltas.emplace(make_pair(offsetY, move(art)));
    }
    else if(has_base)
    {
        baseSLP.xdelta = offsetX;
        baseSLP.ydelta = offsetY;
        museum.deltas.emplace(make_pair(offsetY, move(baseSLP)));
    }
}

void AGE_Frame::CalcAnnexCoords(const genie::unit::BuildingAnnex *annex)
{
    float offsetX = dataset->TerrainBlock.TileHalfWidth * (annex->Misplacement.first + annex->Misplacement.second);
    float offsetY = dataset->TerrainBlock.TileHalfHeight * (-annex->Misplacement.first + annex->Misplacement.second);
    AddAnnexAndStackGraphics(annex->UnitID, offsetX, offsetY);
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
    if(dataset)
    {
        // This ensures that proper data pointers are assigned to editing boxes.
        wxCommandEvent e;
        OnUnitSelect(e);
    }
}

void AGE_Frame::UnitsGraphicsCopy(GraphicCopies &store, short civ, short unit)
{
    store.IconID = dataset->Civs[civ].Units[unit].IconID;// This probably shouldn't be here.
    store.StandingGraphic = dataset->Civs[civ].Units[unit].StandingGraphic;
    store.DyingGraphic = dataset->Civs[civ].Units[unit].DyingGraphic;
    store.UndeadGraphic = dataset->Civs[civ].Units[unit].UndeadGraphic;
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
        store.AttackGraphic = dataset->Civs[civ].Units[unit].Combat.AttackGraphic;
        case 40:
        case 30:
        store.WalkingGraphic = dataset->Civs[civ].Units[unit].Moving.WalkingGraphic;
        store.RunningGraphic = dataset->Civs[civ].Units[unit].Moving.RunningGraphic;
    }
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
                            dataset->UnitHeaders[CorrectID(OneOnOne, loop)].TaskList = copies.Dat.UnitCopies[civ][loop].Action.TaskList;
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
                dataset->Civs[civ].Units[CorrectID(OneOnOne, loop)].Action.TaskList = copies.UnitHeader[loop].TaskList;
            }
        }
    }
}

void AGE_Frame::UnitsGraphicsPaste(GraphicCopies &store, short civ, short unit)
{
    dataset->Civs[civ].Units[unit].IconID = store.IconID;
    dataset->Civs[civ].Units[unit].StandingGraphic = store.StandingGraphic;
    dataset->Civs[civ].Units[unit].DyingGraphic = store.DyingGraphic;
    dataset->Civs[civ].Units[unit].UndeadGraphic = store.UndeadGraphic;
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
        dataset->Civs[civ].Units[unit].Combat.AttackGraphic = store.AttackGraphic;
        case 40:
        case 30:
        dataset->Civs[civ].Units[unit].Moving.WalkingGraphic = store.WalkingGraphic;
        dataset->Civs[civ].Units[unit].Moving.RunningGraphic = store.RunningGraphic;
    }
}

//  SubVectors

string AGE_Frame::GetUnitDamageGraphicName(int index)
{
    return std::to_string((short)dataset->Civs[UnitCivID].Units[UnitIDs.front()].DamageGraphics[index].DamagePercent)
    +" % - ID: "+std::to_string(dataset->Civs[UnitCivID].Units[UnitIDs.front()].DamageGraphics[index].GraphicID);
}

void AGE_Frame::OnUnitDamageGraphicsSearch(wxCommandEvent &event)
{
    How2List = SEARCH;
    ListUnitDamageGraphics();
}

void AGE_Frame::ListUnitDamageGraphics()
{
    InitSearch(Units_DamageGraphics_Search->GetValue().MakeLower(), Units_DamageGraphics_Search_R->GetValue().MakeLower());

    Units_DamageGraphics_ListV->Sweep();

    if(Units_ListV->GetSelectedCount()
    && dataset->Civs[UnitCivID].UnitPointers[UnitIDs.front()] != 0)
    {
        Units_DamageGraphics_Add->Enable(true);
        for(size_t loop = 0; loop < dataset->Civs[UnitCivID].Units[UnitIDs.front()].DamageGraphics.size(); ++loop)
        {
            wxString Name = FormatInt(loop)+" - "+GetUnitDamageGraphicName(loop);
            if(SearchMatches(" " + Name.Lower() + " "))
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
    RefreshList(Units_DamageGraphics_ListV, &DamageGraphicIDs);

    wxCommandEvent e;
    OnUnitDamageGraphicSelect(e);
}

void AGE_Frame::OnUnitDamageGraphicSelect(wxCommandEvent &event)
{
    auto selections = Units_DamageGraphics_ListV->GetSelectedCount();
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
                    warning.Append(std::to_string(SelectedCivs[vecCiv])+" ");
                    showWarning = true;
                }
                DamageGraphicPointer = &dataset->Civs[SelectedCivs[vecCiv]].Units[UnitIDs.front()].DamageGraphics[DamageGraphicIDs[sel]];

                DamageGraphics_GraphicID->prepend(&DamageGraphicPointer->GraphicID);
                DamageGraphics_DamagePercent->prepend(&DamageGraphicPointer->DamagePercent);
                DamageGraphics_Useless->prepend(&DamageGraphicPointer->OldApplyMode);
                DamageGraphics_ApplyMode->prepend(&DamageGraphicPointer->ApplyMode);
            }
        }
        if(showWarning)
        {
            warning.Append("\ndiffers from civ "+std::to_string(UnitCivID));
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
    if(!Units_ListV->GetSelectedCount()) return;

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
    if(!Units_DamageGraphics_ListV->GetSelectedCount()) return;

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
    auto selections = Units_DamageGraphics_ListV->GetSelectedCount();
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
    if(!Units_DamageGraphics_ListV->GetSelectedCount()) return;

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
    if(!Units_DamageGraphics_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    if(copies.Dat.AllCivs & 0x10)
    {
        for(size_t civ = 0, copy = 0; civ < dataset->Civs.size(); ++civ)
        {
            if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] == 0)
            {
                // Consume copies.
                if(copies.Dat.UnitDamageGraphicExists[civ] > 255) ++copy;
                continue;
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
    if(!Units_DamageGraphics_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    genie::unit::DamageGraphic Temp;
    if(copies.Dat.AllCivs & 0x10)
    {
        for(short civ = 0, copy = 0; civ < dataset->Civs.size(); ++civ)
        {
            if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] == 0)
            {
                // Consume copies.
                if(copies.Dat.UnitDamageGraphicExists[civ] > 255) ++copy;
                continue;
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
    return "Amount: "+std::to_string(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Combat.Attacks[index].Amount)
    +" - Class "+std::to_string(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Combat.Attacks[index].Class);
}

void AGE_Frame::OnUnitAttacksSearch(wxCommandEvent &event)
{
    How2List = SEARCH;
    ListUnitAttacks();
}

void AGE_Frame::ListUnitAttacks()
{
    InitSearch(Units_Attacks_Search->GetValue().MakeLower(), Units_Attacks_Search_R->GetValue().MakeLower());

    Units_Attacks_ListV->Sweep();

    if(Units_ListV->GetSelectedCount()
    && dataset->Civs[UnitCivID].UnitPointers[UnitIDs.front()] != 0
    && dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type >= 50
    && dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type <= 80)
    {
        Units_Attacks_Add->Enable(true);
        for(size_t loop = 0; loop < dataset->Civs[UnitCivID].Units[UnitIDs.front()].Combat.Attacks.size(); ++loop)
        {
            wxString Name = FormatInt(loop)+" - "+GetUnitAttackName(loop);
            if(SearchMatches(" " + Name.Lower() + " "))
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
    RefreshList(Units_Attacks_ListV, &AttackIDs);

    wxCommandEvent e;
    OnUnitAttackSelect(e);
}

void AGE_Frame::OnUnitAttackSelect(wxCommandEvent &event)
{
    auto selections = Units_Attacks_ListV->GetSelectedCount();
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
                if(sel == 0 && dataset->Civs[SelectedCivs[vecCiv]].Units[UnitIDs.front()].Combat.Attacks.size() != dataset->Civs[UnitCivID].Units[UnitIDs.front()].Combat.Attacks.size())
                {
                    warning.Append(std::to_string(SelectedCivs[vecCiv])+" ");
                    showWarning = true;
                }
                AttackPointer = &dataset->Civs[SelectedCivs[vecCiv]].Units[UnitIDs.front()].Combat.Attacks[AttackIDs[sel]];

                Attacks_Class->prepend(&AttackPointer->Class);
                Attacks_Amount->prepend(&AttackPointer->Amount);
            }
        }
        if(showWarning)
        {
            warning.Append("\ndiffers from civ "+std::to_string(UnitCivID));
            wxMessageBox(warning);
        }
    }
    Attacks_Class->update();
    Attacks_Amount->update();
}

void AGE_Frame::OnUnitAttacksAdd(wxCommandEvent &event)
{
    if(!Units_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    genie::unit::AttackOrArmor Temp;
    Temp.setGameVersion(GenieVersion);
    for(size_t loop = 0; loop < dataset->Civs.size(); ++loop)
    {
        if(dataset->Civs[loop].UnitPointers[UnitIDs.front()] != 0)
        dataset->Civs[loop].Units[UnitIDs.front()].Combat.Attacks.push_back(Temp);
    }
    How2List = ADD;
    ListUnitAttacks();
}

void AGE_Frame::OnUnitAttacksInsert(wxCommandEvent &event)
{
    if(!Units_Attacks_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    genie::unit::AttackOrArmor Temp;
    Temp.setGameVersion(GenieVersion);
    for(size_t loop = 0; loop < dataset->Civs.size(); ++loop)
    {
        if(dataset->Civs[loop].UnitPointers[UnitIDs.front()] != 0)
        dataset->Civs[loop].Units[UnitIDs.front()].Combat.Attacks.insert(dataset->Civs[loop].Units[UnitIDs.front()].Combat.Attacks.begin() + AttackIDs.front(), Temp);
    }
    How2List = INSNEW;
    ListUnitAttacks();
}

void AGE_Frame::OnUnitAttacksDelete(wxCommandEvent &event)
{
    auto selections = Units_Attacks_ListV->GetSelectedCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    for(short civ = 0; civ < dataset->Civs.size(); ++civ)
    {
        if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] != 0)
        if(dataset->Civs[civ].Units[UnitIDs.front()].Combat.Attacks.size())
        for(auto loop = selections; loop--> 0;)
        dataset->Civs[civ].Units[UnitIDs.front()].Combat.Attacks.erase(dataset->Civs[civ].Units[UnitIDs.front()].Combat.Attacks.begin() + AttackIDs[loop]);
    }
    How2List = DEL;
    ListUnitAttacks();
}

void AGE_Frame::OnUnitAttacksCopy(wxCommandEvent &event)
{
    if(!Units_Attacks_ListV->GetSelectedCount()) return;

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
                CopyFromList(dataset->Civs[civ].Units[UnitIDs.front()].Combat.Attacks, AttackIDs, copies.Dat.UnitAttacks[copy]); copy++;
            }
        }
        copies.Dat.UnitAttacks.resize(CivCount);
    }
    else
    {
        CopyFromList(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Combat.Attacks, AttackIDs, copies.Dat.UnitAttacks.front());
    }
    Units_Attacks_ListV->SetFocus();
}

void AGE_Frame::OnUnitAttacksPaste(wxCommandEvent &event)
{
    if(!Units_Attacks_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    if(copies.Dat.AllCivs & 0x20)
    {
        for(size_t civ = 0, copy = 0; civ < dataset->Civs.size(); ++civ)
        {
            if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] == 0)
            {
                // Consume copies.
                if(copies.Dat.UnitAttackExists[civ] > 255) ++copy;
                continue;
            }
            // If the target unit exists then choose from following.
            if(copies.Dat.UnitAttackExists[civ] > 255 && copy < copies.Dat.UnitAttacks.size())
            {
                PasteToList(dataset->Civs[civ].Units[UnitIDs.front()].Combat.Attacks, AttackIDs, copies.Dat.UnitAttacks[copy]); ++copy;
            }
            else
            {
                PasteToList(dataset->Civs[civ].Units[UnitIDs.front()].Combat.Attacks, AttackIDs, copies.Dat.UnitAttacks.front());
            }
        }
    }
    else
    {
        PasteToList(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Combat.Attacks, AttackIDs, copies.Dat.UnitAttacks.front());
    }
    ListUnitAttacks();
}

void AGE_Frame::OnUnitAttacksPasteInsert(wxCommandEvent &event)
{
    if(!Units_Attacks_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    if(copies.Dat.AllCivs & 0x20)
    {
        for(short civ = 0, copy = 0; civ < dataset->Civs.size(); ++civ)
        {
            if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] == 0)
            {
                // Consume copies.
                if(copies.Dat.UnitAttackExists[civ] > 255) ++copy;
                continue;
            }
            // If the target unit exists then choose from following.
            if(copies.Dat.UnitAttackExists[civ] > 255 && copy < copies.Dat.UnitAttacks.size())
            {
                PasteInsertToList(dataset->Civs[civ].Units[UnitIDs.front()].Combat.Attacks, AttackIDs.front(), copies.Dat.UnitAttacks[copy]); copy++;
            }
            else
            {
                PasteInsertToList(dataset->Civs[civ].Units[UnitIDs.front()].Combat.Attacks, AttackIDs.front(), copies.Dat.UnitAttacks.front());
            }
        }
    }
    else
    {
        PasteInsertToList(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Combat.Attacks, AttackIDs.front(), copies.Dat.UnitAttacks.front());
    }
    ListUnitAttacks();
}

void AGE_Frame::OnUnitAttacksCopyToUnits(wxCommandEvent &event)
{
    for(short civ = 0; civ < dataset->Civs.size(); ++civ)
    for(size_t loop=1; loop < UnitIDs.size(); ++loop)
    {
        dataset->Civs[civ].Units[UnitIDs[loop]].Combat.Attacks = dataset->Civs[civ].Units[UnitIDs.front()].Combat.Attacks;
    }
}

string AGE_Frame::GetUnitArmorName(int index)
{
    return "Amount: "+std::to_string(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Combat.Armours[index].Amount)
    +" - Class "+std::to_string(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Combat.Armours[index].Class);
}

void AGE_Frame::OnUnitArmorsSearch(wxCommandEvent &event)
{
    How2List = SEARCH;
    ListUnitArmors();
}

void AGE_Frame::ListUnitArmors()
{
    InitSearch(Units_Armors_Search->GetValue().MakeLower(), Units_Armors_Search_R->GetValue().MakeLower());

    Units_Armors_ListV->Sweep();

    if(Units_ListV->GetSelectedCount()
    && dataset->Civs[UnitCivID].UnitPointers[UnitIDs.front()] != 0
    && dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type >= 50
    && dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type <= 80)
    {
        Units_Armors_Add->Enable(true);
        for(size_t loop = 0; loop < dataset->Civs[UnitCivID].Units[UnitIDs.front()].Combat.Armours.size(); ++loop)
        {
            wxString Name = FormatInt(loop)+" - "+GetUnitArmorName(loop);
            if(SearchMatches(" " + Name.Lower() + " "))
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
    RefreshList(Units_Armors_ListV, &ArmorIDs);

    wxCommandEvent e;
    OnUnitArmorSelect(e);
}

void AGE_Frame::OnUnitArmorSelect(wxCommandEvent &event)
{
    auto selections = Units_Armors_ListV->GetSelectedCount();
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
                if(sel == 0 && dataset->Civs[SelectedCivs[vecCiv]].Units[UnitIDs.front()].Combat.Armours.size() != dataset->Civs[UnitCivID].Units[UnitIDs.front()].Combat.Armours.size())
                {
                    warning.Append(std::to_string(SelectedCivs[vecCiv])+" ");
                    showWarning = true;
                }
                ArmorPointer = &dataset->Civs[SelectedCivs[vecCiv]].Units[UnitIDs.front()].Combat.Armours[ArmorIDs[sel]];

                Armors_Class->prepend(&ArmorPointer->Class);
                Armors_Amount->prepend(&ArmorPointer->Amount);
            }
        }
        if(showWarning)
        {
            warning.Append("\ndiffers from civ "+std::to_string(UnitCivID));
            wxMessageBox(warning);
        }
    }
    Armors_Class->update();
    Armors_Amount->update();
}

void AGE_Frame::OnUnitArmorsAdd(wxCommandEvent &event)
{
    if(!Units_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    genie::unit::AttackOrArmor Temp;
    Temp.setGameVersion(GenieVersion);
    for(size_t loop = 0; loop < dataset->Civs.size(); ++loop)
    {
        if(dataset->Civs[loop].UnitPointers[UnitIDs.front()] != 0)
        dataset->Civs[loop].Units[UnitIDs.front()].Combat.Armours.push_back(Temp);
    }
    How2List = ADD;
    ListUnitArmors();
}

void AGE_Frame::OnUnitArmorsInsert(wxCommandEvent &event)
{
    if(!Units_Armors_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    genie::unit::AttackOrArmor Temp;
    Temp.setGameVersion(GenieVersion);
    for(size_t loop = 0; loop < dataset->Civs.size(); ++loop)
    {
        if(dataset->Civs[loop].UnitPointers[UnitIDs.front()] != 0)
        dataset->Civs[loop].Units[UnitIDs.front()].Combat.Armours.insert(dataset->Civs[loop].Units[UnitIDs.front()].Combat.Armours.begin() + ArmorIDs.front(), Temp);
    }
    How2List = INSNEW;
    ListUnitArmors();
}

void AGE_Frame::OnUnitArmorsDelete(wxCommandEvent &event)
{
    auto selections = Units_Armors_ListV->GetSelectedCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    for(short civ = 0; civ < dataset->Civs.size(); ++civ)
    {
        if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] != 0)
        if(dataset->Civs[civ].Units[UnitIDs.front()].Combat.Armours.size())
        for(auto loop = selections; loop--> 0;)
        dataset->Civs[civ].Units[UnitIDs.front()].Combat.Armours.erase(dataset->Civs[civ].Units[UnitIDs.front()].Combat.Armours.begin() + ArmorIDs[loop]);
    }
    How2List = DEL;
    ListUnitArmors();
}

void AGE_Frame::OnUnitArmorsCopy(wxCommandEvent &event)
{
    if(!Units_Armors_ListV->GetSelectedCount()) return;

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
                CopyFromList(dataset->Civs[civ].Units[UnitIDs.front()].Combat.Armours, ArmorIDs, copies.Dat.UnitArmors[copy]); copy++;
            }
        }
        copies.Dat.UnitArmors.resize(CivCount);
    }
    else
    {
        CopyFromList(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Combat.Armours, ArmorIDs, copies.Dat.UnitArmors.front());
    }
    Units_Armors_ListV->SetFocus();
}

void AGE_Frame::OnUnitArmorsPaste(wxCommandEvent &event)
{
    if(!Units_Armors_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    if(copies.Dat.AllCivs & 0x40)
    {
        for(size_t civ = 0, copy = 0; civ < dataset->Civs.size(); ++civ)
        {
            if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] == 0)
            {
                // Consume copies.
                if(copies.Dat.UnitArmorExists[civ] > 255) ++copy;
                continue;
            }
            // If the target unit exists then choose from following.
            if(copies.Dat.UnitArmorExists[civ] > 255 && copy < copies.Dat.UnitArmors.size())
            {
                PasteToList(dataset->Civs[civ].Units[UnitIDs.front()].Combat.Armours, ArmorIDs, copies.Dat.UnitArmors[copy]); ++copy;
            }
            else
            {
                PasteToList(dataset->Civs[civ].Units[UnitIDs.front()].Combat.Armours, ArmorIDs, copies.Dat.UnitArmors.front());
            }
        }
    }
    else
    {
        PasteToList(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Combat.Armours, ArmorIDs, copies.Dat.UnitArmors.front());
    }
    ListUnitArmors();
}

void AGE_Frame::OnUnitArmorsPasteInsert(wxCommandEvent &event)
{
    if(!Units_Armors_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    if(copies.Dat.AllCivs & 0x40)
    {
        for(short civ = 0, copy = 0; civ < dataset->Civs.size(); ++civ)
        {
            if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] == 0)
            {
                // Consume copies.
                if(copies.Dat.UnitArmorExists[civ] > 255) ++copy;
                continue;
            }
            // If the target unit exists then choose from following.
            if(copies.Dat.UnitArmorExists[civ] > 255 && copy < copies.Dat.UnitArmors.size())
            {
                PasteInsertToList(dataset->Civs[civ].Units[UnitIDs.front()].Combat.Armours, ArmorIDs.front(), copies.Dat.UnitArmors[copy]); copy++;
            }
            else
            {
                PasteInsertToList(dataset->Civs[civ].Units[UnitIDs.front()].Combat.Armours, ArmorIDs.front(), copies.Dat.UnitArmors.front());
            }
        }
    }
    else
    {
        PasteInsertToList(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Combat.Armours, ArmorIDs.front(), copies.Dat.UnitArmors.front());
    }
    ListUnitArmors();
}

void AGE_Frame::OnUnitArmorsCopyToUnits(wxCommandEvent &event)
{
    for(short civ = 0; civ < dataset->Civs.size(); ++civ)
    for(size_t loop=1; loop < UnitIDs.size(); ++loop)
    {
        dataset->Civs[civ].Units[UnitIDs[loop]].Combat.Armours = dataset->Civs[civ].Units[UnitIDs.front()].Combat.Armours;
    }
}

//  AoE/TC/SWGB/CC Unit TaskList

wxString AGE_Frame::GetUnitCommandName(int index)
{
    short CommandType = (GenieVersion >= genie::GV_AoK)
        ? dataset->UnitHeaders[UnitIDs.front()].TaskList[index].ActionType
        : dataset->Civs[UnitCivID].Units[UnitIDs.front()].Action.TaskList[index].ActionType;
    switch(CommandType)
    {
        case 0: return task_names[1];
        case 1: return task_names[2];
        case 2: return task_names[3];
        case 3: return task_names[4];
        case 4: return task_names[5];
        case 5: return task_names[6];
        case 6: return task_names[7];
        case 7: return task_names[8];
        case 8: return task_names[9];
        case 9: return task_names[10];
        case 10: return task_names[11];
        case 11: return task_names[12];
        case 12: return task_names[13];
        case 13: return task_names[14];
        case 14: return task_names[15];
        case 20: return task_names[16];
        case 21: return task_names[17];
        case 101: return task_names[18];
        case 102: return task_names[19];
        case 103: return task_names[20];
        case 104: return task_names[21];
        case 105: return task_names[22];
        case 106: return task_names[23];
        case 107: return task_names[24];
        case 108: return task_names[25];
        case 109: return task_names[26];
        case 110: return task_names[27];
        case 111: return task_names[28];
        case 120: return task_names[29];
        case 121: return task_names[30];
        case 122: return task_names[31];
        case 123: return task_names[32];
        case 124: return task_names[33];
        case 125: return task_names[34];
        case 130: return task_names[35];
        case 131: return task_names[36];
        case 132: return task_names[37];
        case 133: return task_names[38];
        case 134: return task_names[39];
        case 135: return task_names[40];
        case 136: return task_names[41];
        case 149: return task_names[42];
        case 150: return task_names[43];
        case 151: return task_names[44];
        default: return "Unk. Type "+std::to_string(CommandType);
    }
}

void AGE_Frame::OnUnitCommandsSearch(wxCommandEvent &event)
{
    How2List = SEARCH;
    ListUnitCommands();
}

void AGE_Frame::ListUnitCommands()
{
    InitSearch(Units_Tasks_Search->GetValue().MakeLower(), Units_Tasks_Search_R->GetValue().MakeLower());

    Units_Tasks_ListV->Sweep();
    action_names.Clear();
    action_names.Add("-1 - None");

    if(GenieVersion >= genie::GV_AoK)   // AoK, TC, SWGB or CC
    {
        if(Units_ListV->GetSelectedCount())
        for(size_t loop = 0; loop < dataset->UnitHeaders[UnitIDs.front()].TaskList.size(); ++loop)
        {
            wxString Name = FormatInt(loop)+" - "+GetUnitCommandName(loop);
            if(dataset->UnitHeaders[UnitIDs.front()].TaskList[loop].ClassID != -1)
            Name += " class "+std::to_string(dataset->UnitHeaders[UnitIDs.front()].TaskList[loop].ClassID);
            else if(dataset->UnitHeaders[UnitIDs.front()].TaskList[loop].UnitID != -1)
            Name += " unit "+std::to_string(dataset->UnitHeaders[UnitIDs.front()].TaskList[loop].UnitID);
            if(SearchMatches(" " + Name.Lower() + " "))
            {
                Units_Tasks_ListV->names.Add(Name);
                Units_Tasks_ListV->indexes.push_back(loop);
            }
            action_names.Add(Name);
        }
    }
    else    // AoE or RoR
    {
        if(Units_ListV->GetSelectedCount()
        && dataset->Civs[UnitCivID].UnitPointers[UnitIDs.front()] != 0
        && dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type >= 40
        && dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type <= 80)
        {
            Units_Tasks_Add->Enable(true);
            for(size_t loop = 0; loop < dataset->Civs[UnitCivID].Units[UnitIDs.front()].Action.TaskList.size(); ++loop)
            {
                wxString Name = FormatInt(loop)+" - "+GetUnitCommandName(loop);
                if(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Action.TaskList[loop].ClassID != -1)
                Name += " class "+std::to_string(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Action.TaskList[loop].ClassID);
                else if(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Action.TaskList[loop].UnitID != -1)
                Name += " unit "+std::to_string(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Action.TaskList[loop].UnitID);
                if(SearchMatches(" " + Name.Lower() + " "))
                {
                    Units_Tasks_ListV->names.Add(Name);
                    Units_Tasks_ListV->indexes.push_back(loop);
                }
                action_names.Add(Name);
            }
        }
        else
        {
            Units_Tasks_Add->Enable(false);
        }
    }
    RefreshList(Units_Tasks_ListV, &CommandIDs);
    Units_DefaultTaskID_ComboBox->Flash();

    wxCommandEvent e;
    OnUnitCommandSelect(e);
}

void AGE_Frame::OnUnitCommandSelect(wxCommandEvent &event)
{
    auto selections = Units_Tasks_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    for(auto &box: uiGroupUnitTask) box->clear();
    Tasks_ID->clear();
    if(selections > 0)
    {
        getSelectedItems(selections, Units_Tasks_ListV, CommandIDs);

        bool showWarning = false;
        wxString warning = "Command count of civs\n";
        genie::Task * task_ptr = 0;
        for(auto sel = selections; sel--> 0;)
        {
            for(short vecCiv = (GenieVersion < genie::GV_AoK) ? SelectedCivs.size() : 1; vecCiv--> 0;)
            {
                if(GenieVersion < genie::GV_AoK)
                {
                    if(sel == 0 && dataset->Civs[SelectedCivs[vecCiv]].Units[UnitIDs.front()].Action.TaskList.size() != dataset->Civs[UnitCivID].Units[UnitIDs.front()].Action.TaskList.size())
                    {
                        warning.Append(std::to_string(SelectedCivs[vecCiv])+" ");
                        showWarning = true;
                    }
                    task_ptr = &dataset->Civs[SelectedCivs[vecCiv]].Units[UnitIDs.front()].Action.TaskList[CommandIDs[sel]];
                }
                else
                {
                    task_ptr = &dataset->UnitHeaders[UnitIDs.front()].TaskList[CommandIDs[sel]];
                }

                Tasks_Type->prepend(&task_ptr->TaskType);
                Tasks_ID->prepend(&task_ptr->ID);
                Tasks_IsDefault->prepend(&task_ptr->IsDefault);
                Tasks_ActionType->prepend(&task_ptr->ActionType);
                Tasks_ClassID->prepend(&task_ptr->ClassID);
                Tasks_UnitID->prepend(&task_ptr->UnitID);
                Tasks_TerrainID->prepend(&task_ptr->TerrainID);
                Tasks_ResourceIn->prepend(&task_ptr->ResourceIn);
                Tasks_ProdResource->prepend(&task_ptr->ResourceMultiplier);
                Tasks_ResourceOut->prepend(&task_ptr->ResourceOut);
                Tasks_Resource->prepend(&task_ptr->UnusedResource);
                Tasks_WorkValue1->prepend(&task_ptr->WorkValue1);
                Tasks_WorkValue2->prepend(&task_ptr->WorkValue2);
                Tasks_WorkRange->prepend(&task_ptr->WorkRange);
                Tasks_AutoSearchTargets->prepend(&task_ptr->AutoSearchTargets);
                Tasks_SearchWaitTime->prepend(&task_ptr->SearchWaitTime);
                Tasks_EnableTargeting->prepend(&task_ptr->EnableTargeting);
                Tasks_CombatLevelFlag->prepend(&task_ptr->CombatLevelFlag);
                Tasks_GatherType->prepend(&task_ptr->GatherType);
                Tasks_WorkFlag2->prepend(&task_ptr->WorkFlag2);
                Tasks_TargetDiplomacy->prepend(&task_ptr->TargetDiplomacy);
                Tasks_CarryCheck->prepend(&task_ptr->CarryCheck);
                Tasks_PickForConstruction->prepend(&task_ptr->PickForConstruction);
                Tasks_Graphics.front()->prepend(&task_ptr->MovingGraphicID);
                Tasks_Graphics[1]->prepend(&task_ptr->ProceedingGraphicID);
                Tasks_Graphics[2]->prepend(&task_ptr->WorkingGraphicID);
                Tasks_Graphics[3]->prepend(&task_ptr->CarryingGraphicID);
                Tasks_Graphics[4]->prepend(&task_ptr->ResourceGatheringSoundID);
                Tasks_Graphics[5]->prepend(&task_ptr->ResourceDepositSoundID);
            }
            if(showWarning)
            {
                warning.Append("\ndiffers from civ "+std::to_string(UnitCivID));
                wxMessageBox(warning);
            }
        }
        if(task_ptr)
        switch(task_ptr->ActionType)
        {
            case 0: Tasks_ActionType_ComboBox->SetSelection(1); break;
            case 1: Tasks_ActionType_ComboBox->SetSelection(2); break;
            case 2: Tasks_ActionType_ComboBox->SetSelection(3); break;
            case 3: Tasks_ActionType_ComboBox->SetSelection(4); break;
            case 4: Tasks_ActionType_ComboBox->SetSelection(5); break;
            case 5: Tasks_ActionType_ComboBox->SetSelection(6); break;
            case 6: Tasks_ActionType_ComboBox->SetSelection(7); break;
            case 7: Tasks_ActionType_ComboBox->SetSelection(8); break;
            case 8: Tasks_ActionType_ComboBox->SetSelection(9); break;
            case 9: Tasks_ActionType_ComboBox->SetSelection(10); break;
            case 10: Tasks_ActionType_ComboBox->SetSelection(11); break;
            case 11: Tasks_ActionType_ComboBox->SetSelection(12); break;
            case 12: Tasks_ActionType_ComboBox->SetSelection(13); break;
            case 13: Tasks_ActionType_ComboBox->SetSelection(14); break;
            case 14: Tasks_ActionType_ComboBox->SetSelection(15); break;
            case 20: Tasks_ActionType_ComboBox->SetSelection(16); break;
            case 21: Tasks_ActionType_ComboBox->SetSelection(17); break;
            case 101: Tasks_ActionType_ComboBox->SetSelection(18); break;
            case 102: Tasks_ActionType_ComboBox->SetSelection(19); break;
            case 103: Tasks_ActionType_ComboBox->SetSelection(20); break;
            case 104: Tasks_ActionType_ComboBox->SetSelection(21); break;
            case 105: Tasks_ActionType_ComboBox->SetSelection(22); break;
            case 106: Tasks_ActionType_ComboBox->SetSelection(23); break;
            case 107: Tasks_ActionType_ComboBox->SetSelection(24); break;
            case 108: Tasks_ActionType_ComboBox->SetSelection(25); break;
            case 109: Tasks_ActionType_ComboBox->SetSelection(26); break;
            case 110: Tasks_ActionType_ComboBox->SetSelection(27); break;
            case 111: Tasks_ActionType_ComboBox->SetSelection(28); break;
            case 120: Tasks_ActionType_ComboBox->SetSelection(29); break;
            case 121: Tasks_ActionType_ComboBox->SetSelection(30); break;
            case 122: Tasks_ActionType_ComboBox->SetSelection(31); break;
            case 123: Tasks_ActionType_ComboBox->SetSelection(32); break;
            case 124: Tasks_ActionType_ComboBox->SetSelection(33); break;
            case 125: Tasks_ActionType_ComboBox->SetSelection(34); break;
            case 130: Tasks_ActionType_ComboBox->SetSelection(35); break;
            case 131: Tasks_ActionType_ComboBox->SetSelection(36); break;
            case 132: Tasks_ActionType_ComboBox->SetSelection(37); break;
            case 133: Tasks_ActionType_ComboBox->SetSelection(38); break;
            case 134: Tasks_ActionType_ComboBox->SetSelection(39); break;
            case 135: Tasks_ActionType_ComboBox->SetSelection(40); break;
            case 136: Tasks_ActionType_ComboBox->SetSelection(41); break;
            case 149: Tasks_ActionType_ComboBox->SetSelection(42); break;
            case 150: Tasks_ActionType_ComboBox->SetSelection(43); break;
            case 151: Tasks_ActionType_ComboBox->SetSelection(44); break;
            default: Tasks_ActionType_ComboBox->SetSelection(0);
        }
    }
    for(auto &box: uiGroupUnitTask) box->update();
    Tasks_ID->refill();
    wxCommandEvent E;
    OnChooseGraphic(E);
}

void AGE_Frame::OnUnitCommandsAdd(wxCommandEvent &event)
{
    if(!Units_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    genie::Task Temp;
    Temp.setGameVersion(GenieVersion);
    if(GenieVersion >= genie::GV_AoK)
    {
        dataset->UnitHeaders[UnitIDs.front()].TaskList.push_back(Temp);
        dataset->UnitHeaders[UnitIDs.front()].TaskList[dataset->UnitHeaders[UnitIDs.front()].TaskList.size()-1].ID = (int16_t)(dataset->UnitHeaders[UnitIDs.front()].TaskList.size()-1); // ID Fix
    }
    else
    {
        for(size_t loop = 0; loop < dataset->Civs.size(); ++loop)
        {
            if(dataset->Civs[loop].UnitPointers[UnitIDs.front()] != 0)
            {
                dataset->Civs[loop].Units[UnitIDs.front()].Action.TaskList.push_back(Temp);
                dataset->Civs[loop].Units[UnitIDs.front()].Action.TaskList[dataset->Civs.front().Units[UnitIDs.front()].Action.TaskList.size()-1].ID = (int16_t)(dataset->Civs.front().Units[UnitIDs.front()].Action.TaskList.size()-1); // ID Fix
            }
        }
    }
    How2List = ADD;
    ListUnitCommands();
}

void AGE_Frame::OnUnitCommandsInsert(wxCommandEvent &event)
{
    if(!Units_Tasks_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    genie::Task Temp;
    Temp.setGameVersion(GenieVersion);
    if(GenieVersion >= genie::GV_AoK)
    {
        dataset->UnitHeaders[UnitIDs.front()].TaskList.insert(dataset->UnitHeaders[UnitIDs.front()].TaskList.begin() + CommandIDs.front(), Temp);
        for(size_t loop2 = CommandIDs.front();loop2 < dataset->UnitHeaders[UnitIDs.front()].TaskList.size(); ++loop2) // ID Fix
        dataset->UnitHeaders[UnitIDs.front()].TaskList[loop2].ID = loop2;
    }
    else
    {
        for(size_t loop = 0; loop < dataset->Civs.size(); ++loop)
        {
            if(dataset->Civs[loop].UnitPointers[UnitIDs.front()] != 0)
            {
                dataset->Civs[loop].Units[UnitIDs.front()].Action.TaskList.insert(dataset->Civs[loop].Units[UnitIDs.front()].Action.TaskList.begin() + CommandIDs.front(), Temp);
                for(size_t loop2 = CommandIDs.front();loop2 < dataset->Civs.front().Units[UnitIDs.front()].Action.TaskList.size(); ++loop2) // ID Fix
                dataset->Civs[loop].Units[UnitIDs.front()].Action.TaskList[loop2].ID = loop2;
            }
        }
    }
    How2List = INSNEW;
    ListUnitCommands();
}

void AGE_Frame::OnUnitCommandsDelete(wxCommandEvent &event)
{
    auto selections = Units_Tasks_ListV->GetSelectedCount();
    if(selections < 1) return;

    wxBusyCursor WaitCursor;
    if(GenieVersion >= genie::GV_AoK)
    {
        for(auto loop = selections; loop--> 0;)
        dataset->UnitHeaders[UnitIDs.front()].TaskList.erase(dataset->UnitHeaders[UnitIDs.front()].TaskList.begin() + CommandIDs[loop]);
        for(size_t loop2 = CommandIDs.front();loop2 < dataset->UnitHeaders[UnitIDs.front()].TaskList.size(); ++loop2) // ID Fix
        dataset->UnitHeaders[UnitIDs.front()].TaskList[loop2].ID = loop2;
    }
    else
    {
        for(short civ = 0; civ < dataset->Civs.size(); ++civ)
        {
            if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] != 0)
            if(dataset->Civs[civ].Units[UnitIDs.front()].Action.TaskList.size())
            {
                for(auto loop = selections; loop--> 0;)
                dataset->Civs[civ].Units[UnitIDs.front()].Action.TaskList.erase(dataset->Civs[civ].Units[UnitIDs.front()].Action.TaskList.begin() + CommandIDs[loop]);
                for(size_t loop2 = CommandIDs.front();loop2 < dataset->Civs.front().Units[UnitIDs.front()].Action.TaskList.size(); ++loop2) // ID Fix
                dataset->Civs[civ].Units[UnitIDs.front()].Action.TaskList[loop2].ID = loop2;
            }
        }
    }
    How2List = DEL;
    ListUnitCommands();
}

void AGE_Frame::OnUnitCommandsCopy(wxCommandEvent &event)
{
    if(!Units_Tasks_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    if(GenieVersion >= genie::GV_AoK)
    {
        copies.Dat.AllCivs |= 0x80;
        copies.Dat.UnitCommandExists.resize(0);
        copies.Dat.UnitCommands.resize(1);
        CopyFromList(dataset->UnitHeaders[UnitIDs.front()].TaskList, CommandIDs, copies.Dat.UnitCommands.front());
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
                CopyFromList(dataset->Civs[civ].Units[UnitIDs.front()].Action.TaskList, CommandIDs, copies.Dat.UnitCommands[copy]); copy++;
            }
        }
        copies.Dat.UnitCommands.resize(CivCount);
    }
    else
    {
        CopyFromList(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Action.TaskList, CommandIDs, copies.Dat.UnitCommands.front());
    }
    Units_Tasks_ListV->SetFocus();
}

void AGE_Frame::OnUnitCommandsPaste(wxCommandEvent &event)
{
    if(!Units_Tasks_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    if(GenieVersion >= genie::GV_AoK)
    {
        PasteToListIDFix(dataset->UnitHeaders[UnitIDs.front()].TaskList, CommandIDs, copies.Dat.UnitCommands.front());
    }
    else if(copies.Dat.AllCivs & 0x80)
    {
        for(size_t civ = 0, copy = 0; civ < dataset->Civs.size(); ++civ)
        {
            if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] == 0)
            {
                // Consume copies.
                if(!copies.Dat.UnitCommandExists.empty() && copies.Dat.UnitCommandExists[civ] > 255) ++copy;
                continue;
            }
            // If the target unit exists then choose from following.
            if(!copies.Dat.UnitCommandExists.empty() && copies.Dat.UnitCommandExists[civ] > 255 && copy < copies.Dat.UnitCommands.size())
            {
                PasteToListIDFix(dataset->Civs[civ].Units[UnitIDs.front()].Action.TaskList, CommandIDs, copies.Dat.UnitCommands[copy]); ++copy;
            }
            else
            {
                PasteToListIDFix(dataset->Civs[civ].Units[UnitIDs.front()].Action.TaskList, CommandIDs, copies.Dat.UnitCommands.front());
            }
        }
    }
    else
    {
        PasteToListIDFix(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Action.TaskList, CommandIDs, copies.Dat.UnitCommands.front());
    }
    ListUnitCommands();
}

void AGE_Frame::OnUnitCommandsPasteInsert(wxCommandEvent &event)
{
    if(!Units_Tasks_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    if(GenieVersion >= genie::GV_AoK)
    {
        PasteInsertToListIDFix(dataset->UnitHeaders[UnitIDs.front()].TaskList, CommandIDs.front(), copies.Dat.UnitCommands.front());
    }
    else if(copies.Dat.AllCivs & 0x80)
    {
        for(short civ = 0, copy = 0; civ < dataset->Civs.size(); ++civ)
        {
            if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] == 0)
            {
                // Consume copies.
                if(!copies.Dat.UnitCommandExists.empty() && copies.Dat.UnitCommandExists[civ] > 255) ++copy;
                continue;
            }
            // If the target unit exists then choose from following.
            if(!copies.Dat.UnitCommandExists.empty() && copies.Dat.UnitCommandExists[civ] > 255 && copy < copies.Dat.UnitCommands.size())
            {
                PasteInsertToListIDFix(dataset->Civs[civ].Units[UnitIDs.front()].Action.TaskList, CommandIDs.front(), copies.Dat.UnitCommands[copy]); copy++;
            }
            else
            {
                PasteInsertToListIDFix(dataset->Civs[civ].Units[UnitIDs.front()].Action.TaskList, CommandIDs.front(), copies.Dat.UnitCommands.front());
            }
        }
    }
    else
    {
        PasteInsertToListIDFix(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Action.TaskList, CommandIDs.front(), copies.Dat.UnitCommands.front());
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
            dataset->Civs[civ].Units[UnitIDs[loop]].Action.TaskList = dataset->Civs[civ].Units[UnitIDs.front()].Action.TaskList;
        }
    }
    else
    {
        for(size_t loop=1; loop < UnitIDs.size(); ++loop)
        {
            dataset->UnitHeaders[UnitIDs[loop]].TaskList = dataset->UnitHeaders[UnitIDs.front()].TaskList;
        }
    }
}

void AGE_Frame::UnitLangDLLConverter(wxCommandEvent &event)
{
    int32_t DLLValue;
    try
    {
        DLLValue = stoi(std::string(static_cast<wxTextCtrl*>(event.GetEventObject())->GetValue()));
    }
    catch(const std::exception&)
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
    wxCommandEvent e;
    OnUnitSelect(e);
}

void AGE_Frame::CreateUnitControls()
{
//  UnitControls new things

    Tab_Units = new APanel(TabBar_Main);

    Units_Main = new wxBoxSizer(wxHORIZONTAL);
    Units_Units = new wxStaticBoxSizer(wxVERTICAL, Tab_Units, "Units");
    //Units_Line = new wxStaticLine(Tab_Units, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL, "");
    Units_Special = new wxBoxSizer(wxHORIZONTAL);
    Units_Civs_List = new AGEComboBox(Tab_Units, &civ_names_only, AGETextCtrl::LARGE, false);
    CivComboBoxList.push_back(Units_Civs_List);
    Units_Search = new wxTextCtrl(Tab_Units, wxID_ANY);
    Units_UseAnd[0] = new wxCheckBox(Tab_Units, wxID_ANY, "And");
    Units_Search_R = new wxTextCtrl(Tab_Units, wxID_ANY);
    Units_UseAnd[1] = new wxCheckBox(Tab_Units, wxID_ANY, "And");
    Units_FilterSelector = new AGEComboBox(Tab_Units, &unit_filter_options);
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Units_Searches[loop] = new wxBoxSizer(wxHORIZONTAL);
        Units_SearchFilters[loop] = new AGEComboBox(Tab_Units, &unit_filters, AGETextCtrl::LARGE);
    }
    Units_ListV = new ProperList(Tab_Units, wxSize(200, 100));
    wxGridSizer *Units_Buttons = new wxGridSizer(3, 0, 0);
    wxBoxSizer *Units_Buttons1 = new wxBoxSizer(wxHORIZONTAL);
    Units_Add = new wxButton(Tab_Units, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    Units_Insert = new wxButton(Tab_Units, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
    Units_Delete = new wxButton(Tab_Units, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    Units_Copy = new wxButton(Tab_Units, wxID_ANY, "Copy *", wxDefaultPosition, wxSize(10, -1));
    Units_Copy->SetToolTip("When \"All civs\" is not selected,\nthis and pasting works just like automatic copy,\n(from current civilization to selected ones)\ntaking \"Including graphics\" option into account");
    Units_Paste = new wxButton(Tab_Units, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    Units_PasteInsert = new wxButton(Tab_Units, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
    Units_Info = new SolidText(Tab_Units, " Info *");
    Units_Info->SetToolTip("Add/Insert/Delete works for all civilizations\n...");
    //Units_Extract = new wxButton(Tab_Units, wxID_ANY, "Extract", wxDefaultPosition, wxSize(10, -1));
    //Units_Extract->Enable(false);
    //Units_Import = new wxButton(Tab_Units, wxID_ANY, "Import", wxDefaultPosition, wxSize(10, -1));
    //Units_Import->Enable(false);
    Units_SpecialCopy = new wxButton(Tab_Units, wxID_ANY, "S copy", wxDefaultPosition, wxSize(10, -1));
    Units_SpecialPaste = new wxButton(Tab_Units, wxID_ANY, "S paste", wxDefaultPosition, wxSize(10, -1));
    Units_Enable = new wxButton(Tab_Units, wxID_ANY, "Exist", wxDefaultPosition, wxSize(10, -1));
    Units_Disable = new wxButton(Tab_Units, wxID_ANY, "Wipe Out", wxDefaultPosition, wxSize(10, -1));
    Units_SpecialCopy_Options = new AGEComboBox(Tab_Units, &specialcopy_names, AGETextCtrl::NORMAL);
    Units_SpecialCopy_Civs = new wxCheckBox(Tab_Units, wxID_ANY, "All civs *");
    Units_SpecialCopy_Civs->SetToolTip("Whether buttons of units operate on all civs or just on the selected one\nNote that adding, inserting and deleting units always affect all civilizations!");

    unit_filter_options.Add("Types 10, 15, 90, 20+");
    unit_filter_options.Add("Types 30+");
    unit_filter_options.Add("Types 40+");
    unit_filter_options.Add("Types 50+");
    unit_filter_options.Add("Type 60");
    unit_filter_options.Add("Types 70+");
    unit_filter_options.Add("Type 80");
    Units_FilterSelector->Flash();

    const wxString autoCopyHelpText = "Every civilization has their own unit data, and by default, only non-graphic data changes are copied to other civilizations.";
    Units_DataArea = new wxBoxSizer(wxVERTICAL);
    Units_Top_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_TopGrid_Holder = new wxWrapSizer();
    Units_AutoCopy = new wxCheckBox(Tab_Units, wxID_ANY, "Automatically");
    Units_AutoCopy->SetToolTip("It is safer to copy automatically than manually.");
    Units_CopyTo = new wxButton(Tab_Units, wxID_ANY, "Copy", wxDefaultPosition, wxSize(40, -1));
    Units_CopyGraphics = new wxCheckBox(Tab_Units, wxID_ANY, "Including graphics");
    Units_CopyGraphics->SetToolTip(autoCopyHelpText);
    Units_CopyToText = new SolidText(Tab_Units, " to selected civilizations: ");
    Units_SelectAll = new wxButton(Tab_Units, wxID_ANY, "All", wxDefaultPosition, wxSize(40, -1));
    Units_SelectClear = new wxButton(Tab_Units, wxID_ANY, "None", wxDefaultPosition, wxSize(40, -1));
    Units_GraphicSetText = new SolidText(Tab_Units, " Graphic set: ");
    Units_GraphicSet = new AGEComboBox(Tab_Units, &graphicset_names, AGETextCtrl::NORMAL);
    visibleUnitCiv = new SolidText(Tab_Units, "Civ ", wxST_NO_AUTORESIZE, wxSize(AGETextCtrl::NORMAL, -1));
    Units_Identity_Holder = new wxStaticBoxSizer(wxVERTICAL, Tab_Units, "");
    Units_Type_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_Type_Text = new SolidText(Tab_Units, "Type ");
    Units_Type = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Tab_Units, AGETextCtrl::SMALL);
    Units_Type_ComboBox = new AGEComboBox(Tab_Units, &unit_type_names, AGETextCtrl::LARGE);
    Units_Class = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Tab_Units);
    Units_Class->SetToolTip("Determines many things and works in conjunction with other variables");
    Units_Class_ComboBox[0] = new ComboBox_Plus1(Tab_Units, Units_Class, &class_names);
    Units_Scroller = new AScrolled(Tab_Units);
    Units_ScrollSpace = new wxBoxSizer(wxVERTICAL);
    Units_TypeArea_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_LangDLLArea_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Language Files");
    Units_GraphicsArea_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Graphics");
    SolidText* autoCopyHelp = new SolidText(Units_Scroller, autoCopyHelpText);
    Units_GraphicsArea1_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_GraphicsArea4_Holder = new wxBoxSizer(wxVERTICAL);
    Units_GraphicsArea5_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_StatsArea_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Statistics");
    Units_StatsArea1A_Sizer = new wxBoxSizer(wxHORIZONTAL);
    Units_StatsArea1B_Sizer = new wxBoxSizer(wxHORIZONTAL);
    Units_StatsAreaGarrison_Grid = new wxBoxSizer(wxHORIZONTAL);
    Units_StatsArea2_Grid = new wxBoxSizer(wxHORIZONTAL);
    Units_ProjectileArea_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Projectiles");
    Units_P1 = new wxBoxSizer(wxHORIZONTAL);
    Units_P2 = new wxBoxSizer(wxHORIZONTAL);
    Units_P3 = new wxBoxSizer(wxHORIZONTAL);
    Units_Attributes_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Attributes");
    Units_AB1_Grid = new wxFlexGridSizer(3, 5, 5);
    Units_A1_Grid = new wxBoxSizer(wxHORIZONTAL);
    Units_A2_Grid = new wxBoxSizer(wxHORIZONTAL);
    Units_A3_Grid = new wxBoxSizer(wxHORIZONTAL);
    Units_A4_Grid = new wxBoxSizer(wxHORIZONTAL);
    Units_A5_Grid = new wxGridSizer(4, 0, 5);
    Units_A6_Grid = new wxBoxSizer(wxHORIZONTAL);
    Units_AM1_Grid = new wxFlexGridSizer(5, 5, 5);
    wxBoxSizer *Units_DropSite_Holder = new wxBoxSizer(wxVERTICAL);
    Units_AS_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_AS1_Grid = new wxBoxSizer(wxHORIZONTAL);
    Units_LangRegular_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_LangHotKey_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_Tracking_Grid = new wxBoxSizer(wxHORIZONTAL);
    Units_Training_Grid = new wxBoxSizer(wxHORIZONTAL);
    Units_SoundsArea_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Sounds (that only you hear)");
    Units_SoundsArea1_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_SoundsArea2_Grid = new wxBoxSizer(wxHORIZONTAL);
    Units_Obsoletes_Holder = new wxFlexGridSizer(5, 5, 5);
    Units_Obsoletes_Area = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Obsolete Variables");
    TasksArea_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Tasks (Shared by all civilizations since Age of Empires II)");

//  Invisible Holder Windows
//  Type 10+

    Units_ID1_Holder = new wxBoxSizer(wxVERTICAL);
    Units_LanguageDLLName_Holder = new wxBoxSizer(wxVERTICAL);
    Units_LanguageDLLCreation_Holder = new wxBoxSizer(wxVERTICAL);
    Units_StandingGraphic_Holder = new wxBoxSizer(wxVERTICAL);
    Units_StandingGraphic_Grid = new wxGridSizer(2, 0, 5);
    Units_DyingGraphic_Holder = new wxBoxSizer(wxVERTICAL);
    Units_DyingGraphic_Grid = new wxGridSizer(2, 0, 5);
    Units_UndeadMode_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_HitPoints_Holder = new wxBoxSizer(wxVERTICAL);
    Units_LineOfSight_Holder = new wxBoxSizer(wxVERTICAL);
    Units_GarrisonCapacity_Holder = new wxBoxSizer(wxVERTICAL);
    Units_SizeRadius_Holder = new wxBoxSizer(wxVERTICAL);
    Units_SizeRadius_Grid = new wxBoxSizer(wxHORIZONTAL);
    Units_TrainSound_Holder = new wxBoxSizer(wxVERTICAL);
    Units_DamageSound_Holder = new wxBoxSizer(wxVERTICAL);
    Units_DeadUnitID_Holder = new wxBoxSizer(wxVERTICAL);
    Units_BloodUnitID_Holder = new wxBoxSizer(wxVERTICAL);
    Units_SortNumber_Holder = new wxBoxSizer(wxVERTICAL);
    Units_CanBeBuiltOn_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_IconID_Holder = new wxBoxSizer(wxVERTICAL);
    wxSizer *Units_IconID_Grid = new wxBoxSizer(wxHORIZONTAL);
    Units_HideInEditor_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_Portrait_Holder = new wxBoxSizer(wxVERTICAL);
    Units_Enabled_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_Disabled_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_PlacementSideTerrain_Holder = new wxBoxSizer(wxVERTICAL);
    Units_PlacementSideTerrainGrid_Holder = new wxGridSizer(2, 0, 5);
    Units_PlacementTerrain_Holder = new wxBoxSizer(wxVERTICAL);
    Units_PlacementTerrainGrid_Holder = new wxGridSizer(2, 0, 5);
    Units_ClearanceSize_Holder = new wxBoxSizer(wxVERTICAL);
    Units_ClearanceSize_Grid = new wxBoxSizer(wxHORIZONTAL);
    Units_HillMode_Holder = new wxBoxSizer(wxVERTICAL);
    Units_FogVisibility_Holder = new wxBoxSizer(wxVERTICAL);
    Units_TerrainRestriction_Holder = new wxBoxSizer(wxVERTICAL);
    Units_FlyMode_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_ResourceCapacity_Holder = new wxBoxSizer(wxVERTICAL);
    Units_ResourceDecay_Holder = new wxBoxSizer(wxVERTICAL);
    Units_BlastDefenseLevel_Holder = new wxBoxSizer(wxVERTICAL);
    Units_CombatLevel_Holder = new wxBoxSizer(wxVERTICAL);
    Units_InteractionMode_Holder = new wxBoxSizer(wxVERTICAL);
    Units_MinimapMode_Holder = new wxBoxSizer(wxVERTICAL);
    Units_InterfaceKind_Holder = new wxBoxSizer(wxVERTICAL);
    Units_MultipleAttributeMode_Holder = new wxBoxSizer(wxVERTICAL);
    Units_MinimapColor_Holder = new wxBoxSizer(wxVERTICAL);
    Units_LanguageDLLHelp_Holder = new wxBoxSizer(wxVERTICAL);
    Units_LanguageDLLConverter_Holder[0] = new wxBoxSizer(wxVERTICAL);
    Units_LanguageDLLConverter_Holder[1] = new wxBoxSizer(wxVERTICAL);
    Units_LanguageDLLHotKeyText_Holder = new wxBoxSizer(wxVERTICAL);
    Units_HotKey_Holder = new wxBoxSizer(wxVERTICAL);
    Units_Recyclable_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_TrackAsResource_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_CreateDoppelgangerOnDeath_Holder = new wxBoxSizer(wxVERTICAL);
    Units_ResourceGroup_Holder = new wxBoxSizer(wxVERTICAL);
    Units_OcclusionMode_Holder = new wxBoxSizer(wxVERTICAL);
    Units_ObstructionType_Holder = new wxBoxSizer(wxVERTICAL);
    Units_ObstructionClass_Holder = new wxBoxSizer(wxVERTICAL);
    Units_Trait_Holder = new wxBoxSizer(wxVERTICAL);
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
    Units_AttackReaction_Holder = new wxBoxSizer(wxVERTICAL);
    Units_ConvertTerrain_Holder = new wxBoxSizer(wxVERTICAL);
    Units_Name_Holder = new wxBoxSizer(wxVERTICAL);
    Units_Name2_Holder = new wxBoxSizer(wxVERTICAL);
    Units_Unitline_Holder = new wxBoxSizer(wxVERTICAL);
    Units_MinTechLevel_Holder = new wxBoxSizer(wxVERTICAL);
    Units_CopyID_Holder = new wxBoxSizer(wxVERTICAL);
    Units_BaseID_Holder = new wxBoxSizer(wxVERTICAL);
    Units_TelemetryID_Holder = new wxBoxSizer(wxVERTICAL);

//  Type 20+

    Units_Speed_Holder = new wxBoxSizer(wxVERTICAL);

//  Type 30+

    Units_WalkingGraphic_Holder = new wxBoxSizer(wxVERTICAL);
    Units_WalkingGraphic_Grid = new wxGridSizer(2, 0, 5);
    Units_RotationSpeed_Holder = new wxBoxSizer(wxVERTICAL);
    Units_SizeClass_Holder = new wxBoxSizer(wxVERTICAL);
    Units_TrackingUnit_Holder = new wxBoxSizer(wxVERTICAL);
    Units_TrackingUnitMode_Holder = new wxBoxSizer(wxVERTICAL);
    Units_TrackingUnitDensity_Holder = new wxBoxSizer(wxVERTICAL);
    Units_MoveAlgorithm_Holder = new wxBoxSizer(wxVERTICAL);
    Units_RotationAngles_Holder = new wxBoxSizer(wxVERTICAL);
    Units_RotationAngles_Grid = new wxFlexGridSizer(5, 0, 5);

//  Type 40+

    Units_DefaultTaskID_Holder = new wxBoxSizer(wxVERTICAL);
    Units_SearchRadius_Holder = new wxBoxSizer(wxVERTICAL);
    Units_WorkRate_Holder = new wxBoxSizer(wxVERTICAL);
    Units_DropSite_Grid = new wxGridSizer(2, 0, 5);
    Units_TaskSwapGroup_Holder = new wxBoxSizer(wxVERTICAL);
    Units_AttackSound_Holder = new wxBoxSizer(wxVERTICAL);
    Units_MoveSound_Holder = new wxBoxSizer(wxVERTICAL);
    Units_RunPattern_Holder = new wxBoxSizer(wxVERTICAL);
    Units_Exists_Holder = new wxBoxSizer(wxVERTICAL);

//  Type 50+

    Units_BaseArmor_Holder = new wxBoxSizer(wxVERTICAL);
    Units_DefenseTerrainBonus_Holder = new wxBoxSizer(wxVERTICAL);
    Units_MaxRange_Holder = new wxBoxSizer(wxVERTICAL);
    Units_BlastWidth_Holder = new wxBoxSizer(wxVERTICAL);
    Units_ReloadTime_Holder = new wxBoxSizer(wxVERTICAL);
    Units_ProjectileUnitID_Holder = new wxBoxSizer(wxVERTICAL);
    Units_AccuracyPercent_Holder = new wxBoxSizer(wxVERTICAL);
    Units_TowerMode_Holder = new wxBoxSizer(wxVERTICAL);
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
    Units_DisplayedReloadTime_Holder = new wxBoxSizer(wxVERTICAL);

//  Type 60 only

    Units_ProjectileType_Holder = new wxBoxSizer(wxVERTICAL);
    Units_SmartMode_Holder = new wxBoxSizer(wxVERTICAL);
    Units_HitMode_Holder = new wxBoxSizer(wxVERTICAL);
    Units_VanishMode_Holder = new wxBoxSizer(wxVERTICAL);
    Units_AreaEffectSpecials_Holder = new wxBoxSizer(wxVERTICAL);
    Units_ProjectileArc_Holder = new wxBoxSizer(wxVERTICAL);

//  Type 70+

    Units_CostHeader_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Costs");
    Unit_Cost_Texts = new wxBoxSizer(wxVERTICAL);
    for(auto &sizer: Unit_Cost_Sizers)
    sizer = new wxBoxSizer(wxVERTICAL);
    Units_TrainTime_Holder = new wxBoxSizer(wxVERTICAL);
    Units_TrainLocationID_Holder = new wxBoxSizer(wxVERTICAL);
    Units_ButtonID_Holder = new wxBoxSizer(wxVERTICAL);
    Units_RearAttackModifier_Holder = new wxBoxSizer(wxVERTICAL);
    Units_FlankAttackModifier_Holder = new wxBoxSizer(wxVERTICAL);
    Units_CreatableType_Holder = new wxBoxSizer(wxVERTICAL);
    Units_HeroMode_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_GarrisonGraphic_Holder = new wxBoxSizer(wxVERTICAL);
    Units_MissileCount_Holder = new wxBoxSizer(wxVERTICAL);
    Units_MissileDuplicationCount_Holder = new wxBoxSizer(wxVERTICAL);
    Units_AttackMissileDuplicationSpawning_Holder = new wxBoxSizer(wxVERTICAL);
    Units_AttackMissileDuplicationSpawning_Grid = new wxBoxSizer(wxHORIZONTAL);
    Units_AttackMissileDuplicationUnit_Holder = new wxBoxSizer(wxVERTICAL);
    Units_ChargingGraphic_Holder = new wxBoxSizer(wxVERTICAL);
    Units_ChargingMode_Holder = new wxBoxSizer(wxVERTICAL);
    Units_DisplayedPierceArmour_Holder = new wxBoxSizer(wxVERTICAL);

//  Type 80

    Units_ConstructionGraphicID_Holder = new wxBoxSizer(wxVERTICAL);
    Units_SnowGraphicID_Holder = new wxBoxSizer(wxVERTICAL);
    Units_AdjacentMode_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_IconAngle_Holder = new wxBoxSizer(wxVERTICAL);
    Units_BuildAndVanish_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_StackUnitID_Holder = new wxBoxSizer(wxVERTICAL);
    Units_TerrainID_Holder = new wxBoxSizer(wxVERTICAL);
    Units_OldOverlayID_Holder = new wxBoxSizer(wxVERTICAL);
    Units_ResearchID_Holder = new wxBoxSizer(wxVERTICAL);
    Units_CanBurn_Holder = new wxBoxSizer(wxVERTICAL);
    Units_AnnexUnit1_Holder = new wxBoxSizer(wxVERTICAL);
    Units_AnnexUnit_Grid = new wxGridSizer(4, 0, 5);
    Units_AnnexUnitMisplacement1_Holder = new wxBoxSizer(wxVERTICAL);
    Units_AnnexUnitMisplacement_Grid = new wxGridSizer(4, 0, 5);
    Units_HeadUnit_Holder = new wxBoxSizer(wxVERTICAL);
    Units_TransformUnit_Holder = new wxBoxSizer(wxVERTICAL);
    Units_TransformSound_Holder = new wxBoxSizer(wxVERTICAL);
    Units_ConstructionSound_Holder = new wxBoxSizer(wxVERTICAL);
    Units_GarrisonType_Holder = new wxBoxSizer(wxVERTICAL);
    Units_GarrisonHealRate_Holder = new wxBoxSizer(wxVERTICAL);
    Units_GarrisonRepairRate_Holder = new wxBoxSizer(wxVERTICAL);
    Units_PileUnit_Holder = new wxBoxSizer(wxVERTICAL);
    Units_LootSwitch_Holder = new wxBoxSizer(wxVERTICAL);
    Units_LootSwitch_Grid = new wxGridSizer(6, 0, 5);

//  Data Container Names
//  Type 10+

    Units_ID1_Text = new SolidText(Tab_Units, " ID");
    Units_LanguageDLLName_Text = new SolidText(Units_Scroller, " Language File Name *");
    Units_LanguageDLLCreation_Text = new SolidText(Units_Scroller, " Language File Creation");
    Units_Class_Text = new SolidText(Tab_Units, "  Class * ");
    Units_StandingGraphic_Text = new SolidText(Units_Scroller, " Standing Graphics *");
    Units_DyingGraphic_Text = new SolidText(Units_Scroller, " Dying and Undead Graphics");
    Units_HitPoints_Text = new SolidText(Units_Scroller, " Hit Points *");
    Units_LineOfSight_Text = new SolidText(Units_Scroller, " Line of Sight *");
    Units_GarrisonCapacity_Text = new SolidText(Units_Scroller, " Garrison Capacity");
    Units_SizeRadius_Text = new SolidText(Units_Scroller, " Collision Size XYZ *");
    Units_TrainSound_Text = new SolidText(Units_Scroller, " Train Sound");
    Units_DamageSound_Text = new SolidText(Units_Scroller, " Damage Sound");
    Units_DeadUnitID_Text = new SolidText(Units_Scroller, " Dead Unit");
    Units_BloodUnitID_Text = new SolidText(Units_Scroller, " Blood Unit");
    Units_SortNumber_Text = new SolidText(Units_Scroller, " Sort Number *");
    Units_IconID_Text = new SolidText(Units_Scroller, " Icon *");
    Units_Portrait_Text = new SolidText(Units_Scroller, " Portrait *");
    Units_PlacementSideTerrain_Text = new SolidText(Units_Scroller, " Placement Side Terrains *");
    Units_PlacementTerrain_Text = new SolidText(Units_Scroller, " Placement Terrains");
    Units_ClearanceSize_Text = new SolidText(Units_Scroller, " Clearance Size XY");
    Units_HillMode_Text = new SolidText(Units_Scroller, " Hill Mode *");
    Units_TerrainRestriction_Text = new SolidText(Units_Scroller, " Terrain Table *");
    Units_ResourceCapacity_Text = new SolidText(Units_Scroller, " Resource Capacity");
    Units_ResourceDecay_Text = new SolidText(Units_Scroller, " Resource Decay *");
    Units_BlastDefenseLevel_Text = new SolidText(Units_Scroller, " Blast Defense Level *");
    Units_CombatLevel_Text = new SolidText(Units_Scroller, " Combat Level *");
    Units_InteractionMode_Text = new SolidText(Units_Scroller, " Interaction Mode *");
    Units_MinimapMode_Text = new SolidText(Units_Scroller, " Minimap Mode *");
    Units_InterfaceKind_Text = new SolidText(Units_Scroller, " Interface Kind *");
    Units_MultipleAttributeMode_Text = new SolidText(Units_Scroller, " Attribute Mode *");
    Units_MinimapColor_Text = new SolidText(Units_Scroller, " Minimap Color *");
    Units_LanguageDLLHelp_Text = new SolidText(Units_Scroller, " Language File Help *");
    Units_LanguageDLLConverter_Text[0] = new SolidText(Units_Scroller, " Help Converter *");
    Units_LanguageDLLConverter_Text[1] = new SolidText(Units_Scroller, " Hotkey Text Converter *");
    Units_LanguageDLLHotKeyText_Text = new SolidText(Units_Scroller, " Lang File Hotkey Text *");
    Units_HotKey_Text = new SolidText(Units_Scroller, " Hotkey *");
    Units_CreateDoppelgangerOnDeath_Text = new SolidText(Units_Scroller, " Doppelganger *");
    Units_ResourceGroup_Text = new SolidText(Units_Scroller, " Gather Group *");
    Units_OcclusionMode_Text = new SolidText(Units_Scroller, " Occlusion Mode *");
    Units_ObstructionType_Text = new SolidText(Units_Scroller, " Obstruction Type *");
    Units_ObstructionClass_Text = new SolidText(Units_Scroller, " Blockage Class *");
    Units_Trait_Text = new SolidText(Units_Scroller, " Unit Trait *");
    Units_Civ_Text = new SolidText(Units_Scroller, " Civilization");
    Units_Nothing_Text = new SolidText(Units_Scroller, " Trait Piece *");
    Units_SelectionEffect_Text = new SolidText(Units_Scroller, " Selection Effect *");
    Units_EditorSelectionColour_Text = new SolidText(Units_Scroller, " Editor Select Color");
    Units_SelectionRadius_Text = new SolidText(Units_Scroller, " Selection Outline Size XYZ *");
    ResourceStorage_Type_Text = new SolidText(Units_Scroller, "Type", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(90, -1));
    ResourceStorage_Amount_Text = new SolidText(Units_Scroller, "Amount", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(90, -1));
    ResourceStorage_Mode_Text = new SolidText(Units_Scroller, "Store Mode *", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(90, -1));
    Units_SelectionSound_Text = new SolidText(Units_Scroller, " Selection Sound");
    Units_DyingSound_Text = new SolidText(Units_Scroller, " Dying Sound");
    Units_AttackReaction_Text = new SolidText(Units_Scroller, " Attack Reaction *");
    Units_ConvertTerrain_Text = new SolidText(Units_Scroller, " Convert Terrain *");
    Units_Name_Text = new SolidText(Tab_Units, " Internal Name");
    Units_Name2_Text = new SolidText(Tab_Units, " Internal Name 2");
    Units_Unitline_Text = new SolidText(Units_Scroller, " AI Unitline");
    Units_MinTechLevel_Text = new SolidText(Units_Scroller, " Min Tech Level");
    Units_CopyID_Text = new SolidText(Tab_Units, " Copy ID");
    Units_BaseID_Text = new SolidText(Tab_Units, " Base ID");
    Units_TelemetryID_Text = new SolidText(Tab_Units, " Tracking ID");

//  Type 20+

    Units_Speed_Text = new SolidText(Units_Scroller, " Speed");

//  Type 30+

    Units_WalkingGraphic_Text = new SolidText(Units_Scroller, " Walking and Running Graphics");
    Units_RotationSpeed_Text = new SolidText(Units_Scroller, " Rotation Speed *");
    Units_SizeClass_Text = new SolidText(Units_Scroller, " Size Class");
    Units_TrackingUnit_Text = new SolidText(Units_Scroller, " Trailing Unit");
    Units_TrackingUnitMode_Text = new SolidText(Units_Scroller, " Trail Mode *");
    Units_TrackingUnitDensity_Text = new SolidText(Units_Scroller, " Trail Density *");
    Units_MoveAlgorithm_Text = new SolidText(Units_Scroller, " Move Algorithm");
    Units_RotationAngles_Label = " Rotation Factors *";
    Units_RotationAngles_Text = new SolidText(Units_Scroller, Units_RotationAngles_Label);
    Units_TurnStats_Text[0] = new SolidText(Units_Scroller, " Turn Radius");
    Units_TurnStats_Text[1] = new SolidText(Units_Scroller, " Turn Radius Speed");
    Units_TurnStats_Text[2] = new SolidText(Units_Scroller, " Max YPS Moving");
    Units_TurnStats_Text[3] = new SolidText(Units_Scroller, " Yaw Round Time");
    Units_TurnStats_Text[4] = new SolidText(Units_Scroller, " Max YPS Stationary");

//  Type 40+

    Units_SearchRadius_Text = new SolidText(Units_Scroller, " Search Radius");
    Units_WorkRate_Text = new SolidText(Units_Scroller, " Work Rate");
    Units_DropSite_Text = new SolidText(Units_Scroller, " Drop Sites *");
    Units_TaskSwapGroup_Text = new SolidText(Units_Scroller, " Task Swap Group *");
    Units_AttackSound_Text = new SolidText(Units_Scroller, " Attack Sound");
    Units_MoveSound_Text = new SolidText(Units_Scroller, " Move Sound");
    Units_Exists_Text = new SolidText(Units_Scroller, " Exists");

//  Type 50+

    Units_BaseArmor_Text = new SolidText(Units_Scroller, " Base Armor *");
    Units_DefenseTerrainBonus_Text = new SolidText(Units_Scroller, " Terrain Defense Bonus *");
    Units_MaxRange_Text = new SolidText(Units_Scroller, " Max Range");
    Units_BlastWidth_Text = new SolidText(Units_Scroller, " Blast Width *");
    Units_ReloadTime_Text = new SolidText(Units_Scroller, " Reload Time");
    Units_ProjectileUnitID_Text = new SolidText(Units_Scroller, " Projectile Unit");
    Units_AccuracyPercent_Text = new SolidText(Units_Scroller, " Accuracy Percent");
    Units_Delay_Text = new SolidText(Units_Scroller, " Frame Delay *");
    Units_GraphicDisplacement_Text = new SolidText(Units_Scroller, " Graphic Displacement XYZ *");
    Units_BlastAttackLevel_Text = new SolidText(Units_Scroller, " Blast Attack Level *");
    Units_MinRange_Text = new SolidText(Units_Scroller, " Min Range");
    Units_AccuracyDispersion_Text = new SolidText(Units_Scroller, " Attack Dispersion *");
    Units_AttackGraphic_Text = new SolidText(Units_Scroller, " Attack Graphic");
    Units_DisplayedMeleeArmour_Text = new SolidText(Units_Scroller, " Shown Melee Armor");
    Units_DisplayedAttack_Text = new SolidText(Units_Scroller, " Shown Attack");
    Units_DisplayedRange_Text = new SolidText(Units_Scroller, " Shown Range");
    Units_DisplayedReloadTime_Text = new SolidText(Units_Scroller, " Shown Reload Time");

//  Type 60 only

    Units_ProjectileType_Text = new SolidText(Units_Scroller, " Projectile Type *");
    Units_SmartMode_Text = new SolidText(Units_Scroller, " Smart Mode *");
    Units_HitMode_Text = new SolidText(Units_Scroller, " Hit Mode *");
    Units_VanishMode_Text = new SolidText(Units_Scroller, " Vanish Mode *");
    Units_AreaEffectSpecials_Text = new SolidText(Units_Scroller, " Area Effects *");
    Units_ProjectileArc_Text = new SolidText(Units_Scroller, " Projectile Arc");

//  Type 70+

    Units_CostType_Text = new SolidText(Units_Scroller, "Type", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(90, -1));
    Units_CostAmount_Text = new SolidText(Units_Scroller, "Amount", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(90, -1));
    Units_CostUsed_Text = new SolidText(Units_Scroller, "Deduct", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(90, -1));
    Units_TrainTime_Text = new SolidText(Units_Scroller, " Train Time");
    Units_TrainLocationID_Text = new SolidText(Units_Scroller, " Train Location");
    Units_ButtonID_Text = new SolidText(Units_Scroller, " Train Button *");
    Units_RearAttackModifier_Text = new SolidText(Units_Scroller, " Backstab Bonus");
    Units_FlankAttackModifier_Text = new SolidText(Units_Scroller, " Flank Bonus");
    Units_CreatableType_Text = new SolidText(Units_Scroller, " Creatable Type *");
    Units_GarrisonGraphic_Text = new SolidText(Units_Scroller, " Garrison Graphic");
    Units_MissileCount_Text = new SolidText(Units_Scroller, " Total Projectiles *");
    Units_MissileDuplicationCount_Text = new SolidText(Units_Scroller, " Max Total Projectiles *");
    Units_AttackMissileDuplicationSpawning_Text = new SolidText(Units_Scroller, " Projectile Spawning Area *");
    Units_AttackMissileDuplicationUnit_Text = new SolidText(Units_Scroller, " Secondary Projectile Unit *");
    Units_ChargingGraphic_Text = new SolidText(Units_Scroller, " Special Graphic *");
    Units_ChargingMode_Text = new SolidText(Units_Scroller, " Special Ability *");
    Units_DisplayedPierceArmour_Text = new SolidText(Units_Scroller, " Shown Pierce Armor");

//  Type 80

    Units_ConstructionGraphicID_Text = new SolidText(Units_Scroller, " Construction Graphic");
    Units_SnowGraphicID_Text = new SolidText(Units_Scroller, " Snow Graphic");
    Units_IconAngle_Text = new SolidText(Units_Scroller, " Angle *");
    Units_StackUnitID_Text = new SolidText(Units_Scroller, " Stack Unit *");
    Units_TerrainID_Text = new SolidText(Units_Scroller, " Foundation Terrain *");
    Units_OldOverlayID_Text = new SolidText(Units_Scroller, " Overlay *");
    Units_ResearchID_Text = new SolidText(Units_Scroller, " Initiates Technology *");
    Units_CanBurn_Text = new SolidText(Units_Scroller, " Can Burn");
    Units_AnnexUnit_Text = new SolidText(Units_Scroller, " Annex Units");
    Units_AnnexUnitMisplacement_Text = new SolidText(Units_Scroller, " Annex Units Misplacement");
    Units_HeadUnit_Text = new SolidText(Units_Scroller, " Head Unit *");
    Units_TransformUnit_Text = new SolidText(Units_Scroller, " Transform Unit *");
    Units_TransformSound_Text = new SolidText(Units_Scroller, " Transform Sound *");
    Units_ConstructionSound_Text = new SolidText(Units_Scroller, " Construction Sound");
    Units_GarrisonType_Text = new SolidText(Units_Scroller, " Garrison Type *");
    Units_GarrisonHealRate_Text = new SolidText(Units_Scroller, " Garrison Heal Rate *");
    Units_GarrisonRepairRate_Text = new SolidText(Units_Scroller, " Garr. Repair Rate");
    Units_PileUnit_Text = new SolidText(Units_Scroller, " Pile Unit *");
    Units_LootSwitch_Text = new SolidText(Units_Scroller, " Looting Table *");

//  Data Containers

    Units_ID1 = AGETextCtrl::init(CShort, 0, this, &popUp, Tab_Units, AGETextCtrl::SMALL);
    Units_CopyID = AGETextCtrl::init(CShort, 0, this, &popUp, Tab_Units, AGETextCtrl::SMALL);
    Units_BaseID = AGETextCtrl::init(CShort, 0, this, &popUp, Tab_Units, AGETextCtrl::SMALL);
    Units_TelemetryID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Tab_Units);
    Units_Name = AGETextCtrl::init(CString, &uiGroupUnit, this, &popUp, Tab_Units, lengthiest);
    Units_Name2 = AGETextCtrl::init(CString, &uiGroupUnit, this, &popUp, Tab_Units, lengthiest);
    Units_LanguageDLLName = AGETextCtrl::init(CUShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_LanguageDLLName->SetToolTip("Usual Unit File Pattern for The Conquerors\nName: 5000-5999\n"
        "Creation: Name +1000\nHotkey: Name +11000\nHelp: Name +100000, in file Name +21000\n"
        "Hotkey Text: Name +150000, in file Name +10000\nTech tree: Name +9000");
    Units_DLL_LanguageName = new TextCtrl_DLL(Units_Scroller, wxSize(AGETextCtrl::GIANT, 25));
    Units_LanguageDLLCreation = AGETextCtrl::init(CUShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_DLL_LanguageCreation = new TextCtrl_DLL(Units_Scroller, wxSize(AGETextCtrl::GIANT, 25));
    Units_HotKey = AGETextCtrl::init(CLong, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_HotKey->SetToolTip("10000 + Language File Creation (usually)");
    Units_DLL_HotKey4 = new TextCtrl_DLL(Units_Scroller, wxSize(AGETextCtrl::GIANT, 25));
    Units_LanguageDLLHelp = AGETextCtrl::init(CLong, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_LanguageDLLHelp->SetToolTip("100000 + Language File Name\nThis is linked to the help text below");
    Units_LanguageDLLConverter[0] = new wxTextCtrl(Units_Scroller, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    Units_LanguageDLLConverter[0]->SetToolTip("Language help text in file\nHit enter to get the correction into dat file");
    Units_DLL_LanguageHelp = new TextCtrl_DLL(Units_Scroller, wxSize(610, 55));
    Units_LanguageDLLHotKeyText = AGETextCtrl::init(CLong, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_LanguageDLLHotKeyText->SetToolTip("150000 + Language File Name\nThis seems to be used only in AoE (not RoR)\nThis language line has other purposes in SWGB and CC");
    Units_LanguageDLLConverter[1] = new wxTextCtrl(Units_Scroller, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    Units_LanguageDLLConverter[1]->SetToolTip("Language hotkey text in file\nHit enter to get the correction into dat file");
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
    Units_DamageGraphics_ListV = new ProperList(Units_Scroller, wxSize(140, 100));
    Units_DamageGraphics_Buttons = new wxGridSizer(3, 0, 0);
    Units_DamageGraphics_Add = new wxButton(Units_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    Units_DamageGraphics_Insert = new wxButton(Units_Scroller, wxID_ANY, "Ins New", wxDefaultPosition, wxSize(10, -1));
    Units_DamageGraphics_Delete = new wxButton(Units_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    Units_DamageGraphics_Copy = new wxButton(Units_Scroller, wxID_ANY, "Copy *", wxDefaultPosition, wxSize(10, -1));
    Units_DamageGraphics_Copy->SetToolTip("When \"All civs\" is not selected,\nthis and pasting works only for current civilization");
    Units_DamageGraphics_Paste = new wxButton(Units_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    Units_DamageGraphics_PasteInsert = new wxButton(Units_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
    Units_DamageGraphics_CopyToUnits = new wxButton(Units_Scroller, wxID_ANY, "Copy all to selected units", wxDefaultPosition, wxSize(10, -1));
    Units_DamageGraphics_Holder_Data = new wxBoxSizer(wxVERTICAL);
    slp_dmg_unit = new wxCheckBox(Units_Scroller, wxID_ANY, "View damage graphics");
    DamageGraphics_GraphicID_Holder = new wxBoxSizer(wxVERTICAL);
    DamageGraphics_GraphicID_Text = new SolidText(Units_Scroller, " Graphic");
    DamageGraphics_GraphicID = AGETextCtrl::init(CShort, &uiGroupUnitDmgGraphic, this, &popUp, Units_Scroller);
    DamageGraphics_GraphicID_ComboBox = new ComboBox_Plus1(Units_Scroller, DamageGraphics_GraphicID, &graphic_names);
    GraphicComboBoxList.push_back(DamageGraphics_GraphicID_ComboBox);
    DamageGraphics_DamagePercent_Holder = new wxBoxSizer(wxVERTICAL);
    DamageGraphics_DamagePercent_Text = new SolidText(Units_Scroller, " Damage Percent");
    DamageGraphics_DamagePercent = AGETextCtrl::init(CByte, &uiGroupUnitDmgGraphic, this, &popUp, Units_Scroller);
    DamageGraphics_ApplyMode_Holder = new wxBoxSizer(wxVERTICAL);
    DamageGraphics_ApplyMode_Text = new SolidText(Units_Scroller, " Apply Mode *");
    DamageGraphics_ApplyMode = AGETextCtrl::init(CByte, &uiGroupUnitDmgGraphic, this, &popUp, Units_Scroller);
    DamageGraphics_ApplyMode->SetToolTip("0   Overlay (flames on buildings)\n1   Overlay randomly\n2   Replace graphics (damaged walls)");
    DamageGraphics_Useless_Holder = new wxBoxSizer(wxVERTICAL);
    DamageGraphics_Useless_Text = new SolidText(Units_Scroller, " Useless *");
    DamageGraphics_Useless = AGETextCtrl::init(CByte, &uiGroupUnitDmgGraphic, this, &popUp, Units_Scroller);
    DamageGraphics_Useless->SetToolTip("Replaced in memory by the Apply Mode");

    Units_IconID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
    Units_IconID->SetToolTip("Download Turtle Pack from AoKH to add more than 127 icons.");
    Units_IconID_SLP = new APanel(Units_Scroller, wxSize(55, 50));
    Units_IconAngle = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
    Units_IconAngle->SetToolTip("Effect attribute 17 changes this\n0   Default\n1+ Use icon from 2nd age etc\nIn AoE 1 can be used to set the unit\nhave icon graphics of later ages straight in stone age");
    Units_ChargingGraphic = AGETextCtrl::init(CLong, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_ChargingGraphic->SetToolTip("Activates depending on special ability");
    Units_ChargingGraphic_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_ChargingGraphic, &graphic_names);
    GraphicComboBoxList.push_back(Units_ChargingGraphic_ComboBox);
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Units_StandingGraphic[loop] = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
        Units_StandingGraphic[loop]->SetToolTip("Half of units in group use 1st,\nthe rest use 2nd");
        Units_StandingGraphic_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_StandingGraphic[loop], &graphic_names);
        GraphicComboBoxList.push_back(Units_StandingGraphic_ComboBox[loop]);
    }
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Units_DyingGraphic[loop] = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
        Units_DyingGraphic_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_DyingGraphic[loop], &graphic_names);
        GraphicComboBoxList.push_back(Units_DyingGraphic_ComboBox[loop]);
    }
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Units_WalkingGraphic[loop] = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
        Units_WalkingGraphic_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_WalkingGraphic[loop], &graphic_names);
        GraphicComboBoxList.push_back(Units_WalkingGraphic_ComboBox[loop]);
    }
    Units_SnowGraphicID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_SnowGraphicID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_SnowGraphicID, &graphic_names);
    GraphicComboBoxList.push_back(Units_SnowGraphicID_ComboBox);
    Units_ConstructionGraphicID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_ConstructionGraphicID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_ConstructionGraphicID, &graphic_names);
    GraphicComboBoxList.push_back(Units_ConstructionGraphicID_ComboBox);
    Units_AttackGraphic = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_AttackGraphic_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_AttackGraphic, &graphic_names);
    GraphicComboBoxList.push_back(Units_AttackGraphic_ComboBox);
    Units_GarrisonGraphic = AGETextCtrl::init(CLong, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_GarrisonGraphic_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_GarrisonGraphic, &graphic_names);
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
    Units_Attacks_ListV = new ProperList(Units_Scroller, wxSize(140, 100));
    Units_Attacks_Buttons = new wxGridSizer(3, 0, 0);
    Units_Attacks_Add = new wxButton(Units_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    Units_Attacks_Insert = new wxButton(Units_Scroller, wxID_ANY, "Ins New", wxDefaultPosition, wxSize(10, -1));
    Units_Attacks_Delete = new wxButton(Units_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    Units_Attacks_Copy = new wxButton(Units_Scroller, wxID_ANY, "Copy *", wxDefaultPosition, wxSize(10, -1));
    Units_Attacks_Copy->SetToolTip("When \"All civs\" is not selected,\nthis and pasting works only for current civilization");
    Units_Attacks_Paste = new wxButton(Units_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    Units_Attacks_PasteInsert = new wxButton(Units_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
    Units_Attacks_CopyToUnits = new wxButton(Units_Scroller, wxID_ANY, "Copy all to selected units", wxDefaultPosition, wxSize(10, -1));
    Units_Attacks_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_Attacks_Holder_Data = new wxFlexGridSizer(2, 5, 5);
    Attacks_Amount_Holder = new wxBoxSizer(wxVERTICAL);
    Attacks_Amount_Text = new SolidText(Units_Scroller, " Amount");
    Attacks_Amount = AGETextCtrl::init(CShort, NULL, this, &popUp, Units_Scroller);
    Attacks_Class_Holder = new wxBoxSizer(wxVERTICAL);
    Attacks_Class_Text = new SolidText(Units_Scroller, " Type *");
    Attacks_Class = AGETextCtrl::init(CShort, NULL, this, &popUp, Units_Scroller);
    Attacks_Class->SetToolTip("Armor class that this unit can damage\nYou can make your own classes");
    Attacks_Class_ComboBox[0] = new ComboBox_Plus1(Units_Scroller, Attacks_Class, &armor_names);

    Units_DisplayedAttack = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_Delay = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_Delay->SetToolTip("Graphical delay in frames before projectile is shot");
    Units_AccuracyPercent = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_AccuracyDispersion = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_AccuracyDispersion->SetToolTip("Arc multiplier of the sector where the projectiles may hit.\nHigher values will make missed hits disperse more.");
    Units_ReloadTime = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_DisplayedReloadTime = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_BlastWidth = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_BlastWidth->SetToolTip("If object has 0 blast radius\nand does not hit the unit it had targeted\nalways does half damage");
    Units_BlastAttackLevel = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_BlastAttackLevel->SetToolTip("Blasts damage units that have higher or same blast armor level\n0   Damages resources also\n1   Damages trees also\n2   Damages nearby units\n3   Damages only targeted unit");

    Units_Armors = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Armors");
    Units_Armors_ListArea = new wxBoxSizer(wxVERTICAL);
    Units_Armors_DataArea = new wxBoxSizer(wxVERTICAL);
    Units_Armors_Search = new wxTextCtrl(Units_Scroller, wxID_ANY);
    Units_Armors_Search_R = new wxTextCtrl(Units_Scroller, wxID_ANY);
    Units_Armors_ListV = new ProperList(Units_Scroller, wxSize(140, 100));
    Units_Armors_Buttons = new wxGridSizer(3, 0, 0);
    Units_Armors_Add = new wxButton(Units_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    Units_Armors_Insert = new wxButton(Units_Scroller, wxID_ANY, "Ins New", wxDefaultPosition, wxSize(10, -1));
    Units_Armors_Delete = new wxButton(Units_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    Units_Armors_Copy = new wxButton(Units_Scroller, wxID_ANY, "Copy *", wxDefaultPosition, wxSize(10, -1));
    Units_Armors_Copy->SetToolTip("When \"All civs\" is not selected,\nthis and pasting works only for current civilization");
    Units_Armors_Paste = new wxButton(Units_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    Units_Armors_PasteInsert = new wxButton(Units_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
    Units_Armors_CopyToUnits = new wxButton(Units_Scroller, wxID_ANY, "Copy all to selected units", wxDefaultPosition, wxSize(10, -1));
    Units_Armors_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_Armors_Holder_Data3 = new wxBoxSizer(wxVERTICAL);
    Armors_Amount_Holder = new wxBoxSizer(wxVERTICAL);
    Armors_Amount_Text = new SolidText(Units_Scroller, " Amount");
    Armors_Amount = AGETextCtrl::init(CShort, NULL, this, &popUp, Units_Scroller);
    Armors_Class_Holder = new wxBoxSizer(wxVERTICAL);
    Armors_Class_Text = new SolidText(Units_Scroller, " Type *");
    Armors_Class = AGETextCtrl::init(CShort, NULL, this, &popUp, Units_Scroller);
    Armors_Class->SetToolTip("Attack class from which this unit can take damage\nYou can make your own classes");
    Attacks_Class_ComboBox[1] = new ComboBox_Plus1(Units_Scroller, Armors_Class, &armor_names);

    Units_BlastDefenseLevel = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_BlastDefenseLevel->SetToolTip("Receive blast damage from units that have lower or same blast attack level");
    Units_BaseArmor = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_BaseArmor->SetToolTip("This armor is used for attack types that have no corresponding armor type\n"
        "Can be negative only in The Conquerors and later games");
    Units_DefenseTerrainBonus = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_DefenseTerrainBonus->SetToolTip("Terrain table ID\n"
        "Receive damage based on which terrain this unit stands on.\nEffect attribute 18 changes this.\n"
        "The damage received by this unit is\nmultiplied by the accessible values on\n"
        "the specified terrain table.");
    Units_DefenseTerrainBonus_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_DefenseTerrainBonus, &restriction_names);
    TerrainRestrictionComboBoxList.push_back(Units_DefenseTerrainBonus_ComboBox);
    Units_DisplayedMeleeArmour = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_DisplayedPierceArmour = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);

    Units_ResourceCapacity = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_ResourceDecay = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_ResourceDecay->SetToolTip("Can alter decay time of corpses\nSet to -1 for never decaying");
    Units_WorkRate = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_GarrisonCapacity = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
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
    Units_GarrisonHealRate->SetToolTip("Healing speed factor of units garrisoned in building");

    Units_ProjectileUnitID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_ProjectileUnitID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_ProjectileUnitID, &unit_names);
    UnitComboBoxList.push_back(Units_ProjectileUnitID_ComboBox);
    Units_AttackMissileDuplicationUnit = AGETextCtrl::init(CLong, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_AttackMissileDuplicationUnit->SetToolTip("Uses its own attack values!");
    Units_AttackMissileDuplicationUnit_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_AttackMissileDuplicationUnit, &unit_names);
    UnitComboBoxList.push_back(Units_AttackMissileDuplicationUnit_ComboBox);
    Units_MissileCount = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_MissileCount->SetToolTip("Total missiles including both normal and duplicated projectiles");
    Units_MissileDuplicationCount = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_MissileDuplicationCount->SetToolTip("Total missiles when garrison capacity is full");
    for(size_t loop = 0; loop < 3; ++loop)
    Units_GraphicDisplacement[loop] = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_GraphicDisplacement[0]->SetToolTip("Left/Right distance");
    Units_GraphicDisplacement[1]->SetToolTip("Spawning distance from the unit");
    Units_GraphicDisplacement[2]->SetToolTip("Height");
    for(size_t loop = 0; loop < 3; ++loop)
    Units_AttackMissileDuplicationSpawning[loop] = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_AttackMissileDuplicationSpawning[0]->SetToolTip("Spawning area's width");
    Units_AttackMissileDuplicationSpawning[1]->SetToolTip("Spawning area's length");
    Units_AttackMissileDuplicationSpawning[2]->SetToolTip("Spawning point's randomness inside the spawning area\n"
        "0   From a single spot\n1   Totally randomly inside the spawning area\n1+ Less randomly");

    Units_ProjectileType = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_ProjectileType->SetToolTip("0   Straight\n1   Homing?"
        ", projectile falls vertically to the bottom of the map\n2   Velocity homing?\n3   Teleporting projectile");
    Units_SmartMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_SmartMode->SetToolTip("Effect attribute 19 changes this\n0   Shoot where the target is now\n"
        "1   Shoot where the target is going to be");
    Units_HitMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_HitMode->SetToolTip("0   Continue after hitting an obstacle\n1   Disappear once an obstacle is hit\n"
        "2   Hit all. Damages target and resting position?");
    Units_VanishMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_VanishMode->SetToolTip("Only affects graphics of the projectile\n0   Stops graphics at target\n"
        "1   Graphics pass through the target instead of stopping");
    Units_AreaEffectSpecials = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_AreaEffectSpecials->SetToolTip("0   Normal\n1   Random (bullets)\n2   Random explosions");
    Units_ProjectileArc = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);

    Units_Enabled = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
    Units_Enabled->SetToolTip("0   Requires a technology to be available\n1   Available without a technology");
    Units_Enabled_CheckBox = new CheckBox_2State(Units_Scroller, "Available *", Units_Enabled);
    Units_Disabled = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
    Units_Disabled->SetToolTip("Not scanned but set to 0\nCan change during gameplay\n"
        "Mostly for different game modes and disables defined in scenarios\n"
        "0   Default\n1   Prevents enabling/disabling with a tech");
    Units_Disabled_CheckBox = new CheckBox_2State(Units_Scroller, "Disabled *", Units_Disabled);
    Units_UndeadMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
    Units_UndeadMode->SetToolTip("After 1st dying graphic:\n0   Transform into dead unit\n1   Show undead graphic");
    Units_UndeadMode_CheckBox = new CheckBox_2State(Units_Scroller, "Undead Mode *", Units_UndeadMode);
    Units_CanBeBuiltOn = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
    Units_CanBeBuiltOn->SetToolTip("0   Default\n1   Graphic stays at highest elevation until destination is reached\n2+ Graphic is not affected by elevation");
    Units_CanBeBuiltOn_CheckBox = new CheckBox_2State(Units_Scroller, "Can be Built on *", Units_CanBeBuiltOn);
    Units_HideInEditor = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
    Units_HideInEditor->SetToolTip("Possible values: 0, 1 and as boolean");
    Units_HideInEditor_CheckBox = new CheckBox_2State(Units_Scroller, "Hide in Editor", Units_HideInEditor);
    Units_FlyMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
    Units_FlyMode->SetToolTip("Controls graphic altitude when teleporting\n0   Stay on ground\n1   Graphics appear higher than the shadow");
    Units_FlyMode_CheckBox = new CheckBox_2State(Units_Scroller, "Fly Mode *", Units_FlyMode);
    Units_Recyclable = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
    Units_Recyclable->SetToolTip("Unselectable\nNot scanned but set to 1 for class 11\nCan change during gameplay");
    Units_Recyclable_CheckBox = new CheckBox_2State(Units_Scroller, "Recyclable *", Units_Recyclable);
    Units_TrackAsResource = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
    Units_TrackAsResource->SetToolTip("Track as Resource\nAllows automatic gathering and handles fog visibility");
    Units_TrackAsResource_CheckBox = new CheckBox_2State(Units_Scroller, "Can be Gathered *", Units_TrackAsResource);
    Units_HeroMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
    Units_HeroMode_CheckBox = new CheckBox_2State(Units_Scroller, "Hero Mode", Units_HeroMode);
    Units_AdjacentMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
    Units_AdjacentMode->SetToolTip("0   Default\n1   Adjacent buildings can change graphics of this unit\nThis changes the graphic angle");
    Units_AdjacentMode_CheckBox = new CheckBox_2State(Units_Scroller, "Adjacent Mode *", Units_AdjacentMode);
    Units_DisappearsWhenBuilt = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
    Units_DisappearsWhenBuilt->SetToolTip("Useful for stack unit placement\n0   Default\n1   Makes the building disappear when built");
    Units_BuildAndVanish_CheckBox = new CheckBox_2State(Units_Scroller, "Built: Vanishes *", Units_DisappearsWhenBuilt);

    Units_SortNumber = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_SortNumber->SetToolTip("Units with low sort numbers are drawn last\n0   Can be placed on top of other units in scenario editor\n5   Cannot be placed on top of other units in scenario editor");
    Units_HillMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_HillMode->SetToolTip("0   No restriction\n1   Cannot place on corners of hills\n2   Can only place on flat land\n3   Allows one elevation difference");
    Units_FogVisibility_Text = new SolidText(Units_Scroller, " Fog Visibility *");
    Units_FogVisibility = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_FogVisibility->SetToolTip("0   Not visible\n1   Always visible\n2   Visible if alive\n3   Inverted visibility\n4   Check doppelganger");
    Units_CombatLevel = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_CombatLevel->SetToolTip("Mainly used in trigger conditions\n0   None\n1   Base\n2   Building\n3   Civilian\n4   Soldier\n5   Priest\n");
    Units_InteractionMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_InteractionMode->SetToolTip("Select Level\n0   None. No interaction.\n"
        "1   Object. Can pick.\n2   Resource. Can select, unable to attack or move.\n"
        "3   Building. Can select and attack, unable to move.\n4   Unit. Can select, attack and move.");
    Units_MinimapMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_MinimapMode->SetToolTip("Draw Level\n0   None. No dot on minimap.\n"
        "1   Unit. Square dot turning white when selected.\n"
        "2   Building. Diamond dot turning white when selected.\n"
        "3   Terrain. Diamond dot keeping color.\n4   Terrain. Larger spot, not following the unit,\n"
        "      no blinking when attacked, everyone can see it.");
    Units_MinimapColor = AGETextCtrl::init(CUByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_MinimapColor->SetToolTip("Minimap modes 3 and 4 allow this to work");
    Units_CreateDoppelgangerOnDeath = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_CreateDoppelgangerOnDeath->SetToolTip("Create doppelganger on death.\n"
        "0   None\n1   After death\n2   When dying");
    Units_ResourceGroup = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_ResourceGroup->SetToolTip("Visible resource group\nNeeds to be gatherable\n"
        "0   Tree\n1   Berry\n2   Fish\n3   Stone/ore\n4   Gold/nova");
    Units_TaskSwapGroup = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_TaskSwapGroup->SetToolTip("When tasking the unit, it will transform into another unit,\n"
        "if the action is not found in this unit, but exists on another unit,\nthat uses the same task swap group.\n"
        "Changes according to task\n1   Male villager\n2   Female villager\n3+ Free slots");
    Units_ChargingMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_ChargingMode->SetToolTip("0   None\nThese work only when facing the hit angle.\n"
        "1   Block\n    Activates special graphic when receiving damage and\n    not pursuing the attacker.\n"
        "    While idle, blocking decreases damage taken by 1/3.\n"
        "2   Counter Charge\n    Activates special graphic when idle and enemy is near.\n"
        "    While idle, attacks back once on first received hit.\n"
        "    Enemy must be unit type 70 and have less than 0.2 max range.\n"
        "3   Charge\n    Activates special graphic when closer than two tiles to the target.\n"
        "    Deals 2X damage on 1st hit.\nPlanned but never implemented ship special attacks:\n"
        "Read the design document of Age of Empires II.\n"
        "These were supposed to be mutually exclusive technologies.\n"
        "4   Ram\n    Charge against another ship, losing some hit points yourself.\n"
        "5   Greek Fire\n    Fry units on ships passing through your sea of fire.\n"
        "6   Board\n    Attach to another ship, resulting in takeover or sinking.");

    Units_Trait = AGETextCtrl::init(CUByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_Trait->SetToolTip("This is a byte of eight booleans\nYou can combine these attributes");
    Units_Trait_Grid = new wxBoxSizer(wxHORIZONTAL);
    for(size_t loop = 0; loop < 8; ++loop)
    Units_Trait_CheckBox[loop] = new wxCheckBox(Units_Scroller, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(15, -1));
    Units_Trait_CheckBox[0]->SetToolTip("Garrison unit");
    Units_Trait_CheckBox[1]->SetToolTip("Ship unit");
    Units_Trait_CheckBox[2]->SetToolTip("SW: Stealth unit");
    Units_Trait_CheckBox[3]->SetToolTip("SW: Detector unit");
    Units_Trait_CheckBox[4]->SetToolTip("SW: Mechanical unit");
    Units_Trait_CheckBox[5]->SetToolTip("SW: Biological unit");
    Units_Trait_CheckBox[6]->SetToolTip("SW: Self-shielding unit");
    Units_Trait_CheckBox[7]->SetToolTip("SW: Invisible unit");
    Units_Civ = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_Civ_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_Civ, &civ_names);
    CivComboBoxList.push_back(Units_Civ_ComboBox);
    Units_Nothing = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_Nothing->SetToolTip("This is actually leftover from attribute+civ variable\nProbably useless");
    Units_DeadUnitID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_DeadUnitID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_DeadUnitID, &unit_names);
    UnitComboBoxList.push_back(Units_DeadUnitID_ComboBox);
    Units_BloodUnitID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_BloodUnitID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_BloodUnitID, &unit_names);
    UnitComboBoxList.push_back(Units_BloodUnitID_ComboBox);
    Units_Unitline = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_Unitline_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_Unitline, &unitline_names);
    Units_MinTechLevel = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_MinTechLevel_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_MinTechLevel, &research_names);
    ResearchComboBoxList.push_back(Units_MinTechLevel_ComboBox);
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Units_PlacementTerrain[loop] = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
        Units_PlacementTerrain_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_PlacementTerrain[loop], &terrain_names);
        TerrainComboBoxList.push_back(Units_PlacementTerrain_ComboBox[loop]);
    }
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Units_PlacementSideTerrain[loop] = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
        Units_PlacementSideTerrain[loop]->SetToolTip("Required terrain on some side");
        Units_PlacementSideTerrain_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_PlacementSideTerrain[loop], &terrain_names);
        TerrainComboBoxList.push_back(Units_PlacementSideTerrain_ComboBox[loop]);
    }
    Units_TerrainRestriction = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_TerrainRestriction->SetToolTip("Must use valid index here (not -1)");
    Units_TerrainRestriction_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_TerrainRestriction, &restriction_names);
    TerrainRestrictionComboBoxList.push_back(Units_TerrainRestriction_ComboBox);
    Units_TerrainID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_TerrainID->SetToolTip("Terrain produced under a building when completed");
    Units_TerrainID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_TerrainID, &terrain_names);
    TerrainComboBoxList.push_back(Units_TerrainID_ComboBox);
    Units_ResearchID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_ResearchID->SetToolTip("Causes that technology to be researched when the building is created");
    Units_ResearchID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_ResearchID, &research_names);
    ResearchComboBoxList.push_back(Units_ResearchID_ComboBox);
    Units_DefaultTaskID_Text = new SolidText(Units_Scroller, " Default Task *");
    Units_DefaultTaskID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_DefaultTaskID->SetToolTip("Unit task ID executed when idle.\nTo get the unit auto-converted to enemy,\nuse unit command 107, which sheep and monument have.");
    Units_DefaultTaskID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_DefaultTaskID, &action_names);
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Units_DropSite[loop] = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
        Units_DropSite[loop]->SetToolTip("Giving to a villager drop site to cart-like unit\ncan allow you to have mobile resource-gatherers,\nsimilar to those in Age of Mythology.");
        Units_DropSite_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_DropSite[loop], &unit_names);
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
    Units_HPBarHeight1->SetToolTip("Setting \"can be built on\" to 1 and this to 0 causes\nfarms to be walkable in AoE/RoR.");
    Units_HPBarHeight2 = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_HPBarHeight2->SetToolTip("Determines HP bar location\nVertical half tile (elevation height?) distance from the top corner?");

    Units_OcclusionMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_OcclusionMode->SetToolTip("Combinable bit field\n0   No outline\n"
        "1   Outline displayed through occlusion\n2   Occludes others\n4   Outline displayed while constructing");
    Units_ObstructionType = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_ObstructionType->SetToolTip("0, 1   Square outline, and passable\n"
        "2   Solid square outline, and has collision box\n3   Square outline, and has collision box\n"
        "4   Is passable, but has no outline\n5   Round outline, and has collision box\n"
        "10   Like 2, designed for mountains");
    Units_ObstructionClass = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_ObstructionClass->SetToolTip("0   Forces default obstruction type\n1   Resource\n2   Unit\n3   Building\n"
        "4   Wall\n5   Gate, allows trespassing\n6   Cliff, blocks walling");
    Units_SelectionEffect = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_SelectionEffect->SetToolTip("0   Has hit point bar\n1   Has hit point bar and outline\n"
        "2   No hit point bar or outline\n3   No hit point bar, but has outline");
    Units_EditorSelectionColour = AGETextCtrl::init(CUByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_TrackingUnit = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_TrackingUnit_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_TrackingUnit, &unit_names);
    UnitComboBoxList.push_back(Units_TrackingUnit_ComboBox);
    Units_TrackingUnitMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_TrackingUnitMode->SetToolTip("0   Not used\n1   Appears while moving and at the start of the game\n"
        "2   Appears while moving, based on density");
    Units_TrackingUnitDensity = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_TrackingUnitDensity->SetToolTip("Only with trail mode 2");
    for(size_t loop = 0; loop < Units_RotationAngles.size(); ++loop)
    Units_RotationAngles[loop] = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
    wxString rot360 = "360 degrees when multiplying with 4th box radian value";
    Units_RotationAngles[2]->SetToolTip(rot360);
    Units_RotationAngles[3]->SetToolTip("Used to get 3rd and 5th box to 360 degrees");
    Units_RotationAngles[4]->SetToolTip(rot360);
    Units_InterfaceKind = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_InterfaceKind->SetToolTip("Unit Level\nClass and this sets the interface for this unit\n0   None\n"
        "1   Resource\n2   Building (build page 1)\n3   Civilian\n4   Soldier\n5   Trade Unit\n6   Priest\n"
        "7   Transport Ship\n8   Relic / Priest with Relic\n9   Fishing Boat\n"
        "10   (A=2&8) Military Building (build page 2)\n11   Shield Building (build page 3)");
    Units_TrainTime = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_TrainLocationID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_TrainLocationID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_TrainLocationID, &unit_names);
    UnitComboBoxList.push_back(Units_TrainLocationID_ComboBox);
    Units_ButtonID = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_ButtonID->SetToolTip("First page (also second in TC) 1-15\nSecond (dock) page 21-35\nThird page same as first (Star Wars)\nFirst page in AoE/RoR 1-10\nSecond page in AoE/RoR 11-20");
    for(size_t loop = 0; loop < 3; ++loop)
    {
        ResourceStorage_Type[loop] = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
        ResourceStorage_Type_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, ResourceStorage_Type[loop], &resource_names);
        ResourceComboBoxList.push_back(ResourceStorage_Type_ComboBox[loop]);
        ResourceStorage_Amount[loop] = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
        ResourceStorage_Mode[loop] = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
        ResourceStorage_Mode[loop]->SetToolTip("Attribute Flag\n0   Keep. Decayable resource.\n"
        "1   Give. Stored after death also.\n2   Give and take. Resets on dying, enables instantly.\n"
        "4   Building. Resets on dying, enables on completion.\nUP: 8   Stored on completion and stays after death");
    }
    for(size_t loop = 0; loop < 3; ++loop)
    {
        Units_CostType[loop] = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
        Units_CostType_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_CostType[loop], &resource_names);
        ResourceComboBoxList.push_back(Units_CostType_ComboBox[loop]);
        Units_CostAmount[loop] = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
        Units_CostUsed[loop] = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
        Units_CostUsed[loop]->SetToolTip("If set to 0 and there is an amount, the amount is required but not paid");
        Units_CostUsed_CheckBox[loop] = new CheckBox_2State(Units_Scroller, "Paid", Units_CostUsed[loop]);
    }
    Units_StackUnitID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_StackUnitID->SetToolTip("Second building to be placed directly on top of this building\nAdditional building gets added every time you load the scenario");
    Units_StackUnitID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_StackUnitID, &unit_names);
    UnitComboBoxList.push_back(Units_StackUnitID_ComboBox);
    Units_HeadUnit = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_HeadUnit->SetToolTip("The building that an annex building is attached to");
    Units_HeadUnit_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_HeadUnit, &unit_names);
    UnitComboBoxList.push_back(Units_HeadUnit_ComboBox);
    Units_TransformUnit = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_TransformUnit->SetToolTip("Determines what the unit changes into when given the order to unpack");
    Units_TransformUnit_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_TransformUnit, &unit_names);
    UnitComboBoxList.push_back(Units_TransformUnit_ComboBox);
    Units_PileUnit = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_PileUnit->SetToolTip("Appears when the building dies\nDoes not appear with delete command");
    Units_PileUnit_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_PileUnit, &unit_names);
    UnitComboBoxList.push_back(Units_PileUnit_ComboBox);
    for(size_t loop = 0; loop < 4; ++loop)
    {
        Units_AnnexUnit[loop] = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
        Units_AnnexUnit_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_AnnexUnit[loop], &unit_names);
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
    Units_SelectionSound_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_SelectionSound, &sound_names);
    SoundComboBoxList.push_back(Units_SelectionSound_ComboBox);
    Units_DyingSound = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_DyingSound_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_DyingSound, &sound_names);
    SoundComboBoxList.push_back(Units_DyingSound_ComboBox);
    Units_TrainSound = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_TrainSound_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_TrainSound, &sound_names);
    SoundComboBoxList.push_back(Units_TrainSound_ComboBox);
    Units_DamageSound = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_DamageSound_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_DamageSound, &sound_names);
    SoundComboBoxList.push_back(Units_DamageSound_ComboBox);
    Units_AttackSound = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_AttackSound_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_AttackSound, &sound_names);
    SoundComboBoxList.push_back(Units_AttackSound_ComboBox);
    Units_MoveSound = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_MoveSound_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_MoveSound, &sound_names);
    SoundComboBoxList.push_back(Units_MoveSound_ComboBox);
    Units_ConstructionSound = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_ConstructionSound_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_ConstructionSound, &sound_names);
    SoundComboBoxList.push_back(Units_ConstructionSound_ComboBox);
    Units_TransformSound = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_TransformSound->SetToolTip("Unused\nDevelopers forgot to implement this?");
    Units_TransformSound_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_TransformSound, &sound_names);
    SoundComboBoxList.push_back(Units_TransformSound_ComboBox);

    Units_Portrait = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_Portrait->SetToolTip("Was probably used similarly to unit icon");
    Units_MultipleAttributeMode = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_MultipleAttributeMode->SetToolTip("1 on more or less living things");
    Units_AttackReaction = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_AttackReaction->SetToolTip("0   None\n1   Run\n2   Run work\n"
        "3   Fight\n4   Fight work\n5   Fight run\n6   Fight run work\n");
    Units_ConvertTerrain = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_ConvertTerrain->SetToolTip("Some alpha feature that let units change terrain under them.\nSpecifically from passable to impassable.");

    Units_SizeClass = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_MoveAlgorithm = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);

    Units_RunPattern_Text = new SolidText(Units_Scroller, " Run Pattern *");
    Units_RunPattern = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_RunPattern->SetToolTip("0   Escape straight\n1   Escape randomly");

    Units_TowerMode_Text = new SolidText(Units_Scroller, " Break off Combat");
    Units_TowerMode = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);

    Units_OldOverlayID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_OldOverlayID->SetToolTip("ES forgot to remove this before AoE was released.\nThis points to removed data block\nthat was like terrain borders.\nYou could build roads back in 1996.");

    Units_RearAttackModifier = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_FlankAttackModifier = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_CreatableType = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_CreatableType->SetToolTip("0   None\n1   Villager\n2   Infantry\n3   Cavalry\n4   Relic\n5   Archer\n6   Monk\n");

    Units_CanBurn = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_GarrisonRepairRate = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);

    TaskHolder_Lists = new wxBoxSizer(wxVERTICAL);
    Units_UnitHeads_Name = new SolidText(Units_Scroller, "Unit Header");
    Units_Tasks_Search = new wxTextCtrl(Units_Scroller, wxID_ANY);
    Units_Tasks_Search_R = new wxTextCtrl(Units_Scroller, wxID_ANY);
    Units_Tasks_ListV = new ProperList(Units_Scroller, wxSize(140, 190));
    Units_Tasks_Buttons = new wxGridSizer(3, 0, 0);
    Units_Tasks_Add = new wxButton(Units_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    Units_Tasks_Insert = new wxButton(Units_Scroller, wxID_ANY, "Ins New", wxDefaultPosition, wxSize(10, -1));
    Units_Tasks_Delete = new wxButton(Units_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    Units_Tasks_Copy = new wxButton(Units_Scroller, wxID_ANY, "Copy *", wxDefaultPosition, wxSize(10, -1));
    Units_Tasks_Copy->SetToolTip("When \"All civs\" is not selected,\nthis and pasting works only for current civilization");
    Units_Tasks_Paste = new wxButton(Units_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    Units_Tasks_PasteInsert = new wxButton(Units_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
    Units_Tasks_CopyToUnits = new wxButton(Units_Scroller, wxID_ANY, "Copy all to selected units", wxDefaultPosition, wxSize(10, -1));
    TaskHolder_Data = new wxBoxSizer(wxVERTICAL);
    Tasks_Known1 = new wxBoxSizer(wxHORIZONTAL);
    Tasks_Known2 = new wxFlexGridSizer(3, 5, 5);
    Tasks_Known3 = new wxBoxSizer(wxHORIZONTAL);
    Tasks_Known4 = new wxFlexGridSizer(3, 5, 5);
    Tasks_Known5 = new wxFlexGridSizer(3, 5, 5);
    Units_Exists = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    wxArrayString action_choices;
    action_choices.Add("None");
    action_choices.Add("Move");
    action_choices.Add("Proceed");
    action_choices.Add("Work");
    action_choices.Add("Carry");
    slp_unit_actions = new wxRadioBox(Units_Scroller, wxID_ANY, "SLP view", wxDefaultPosition, wxDefaultSize, action_choices, 0, wxVERTICAL);

    Tasks_Type_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_Type_Text = new SolidText(Units_Scroller, " Task Type");
    Tasks_Type = AGETextCtrl::init(CShort, &uiGroupUnitTask, this, &popUp, Units_Scroller, AGETextCtrl::MEDIUM);
    Tasks_ID_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_ID_Text = new SolidText(Units_Scroller, " ID");
    Tasks_ID = AGETextCtrl::init(CShort, 0, this, &popUp, Units_Scroller, AGETextCtrl::MEDIUM);
    Tasks_IsDefault_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_IsDefault = AGETextCtrl::init(CByte, &uiGroupUnitTask, this, &popUp, Units_Scroller);
    Tasks_IsDefault->SetToolTip("Basically useless\nUsed to setup task when discovered,\nbut you can directly set it in unit data above");
    Tasks_IsDefault_Text = new CheckBox_2State(Units_Scroller, "Is Default *", Tasks_IsDefault);
    Tasks_ActionType_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_ActionType_Text = new SolidText(Units_Scroller, " Action Type");
    Tasks_ActionType = AGETextCtrl::init(CShort, &uiGroupUnitTask, this, &popUp, Units_Scroller);
    Tasks_ActionType_ComboBox = new AGEComboBox(Units_Scroller, &task_names, AGETextCtrl::GIANT);
    Tasks_ClassID_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_ClassID_Text = new SolidText(Units_Scroller, " Class");
    Tasks_ClassID = AGETextCtrl::init(CShort, &uiGroupUnitTask, this, &popUp, Units_Scroller);
    Units_Class_ComboBox[1] = new ComboBox_Plus1(Units_Scroller, Tasks_ClassID, &class_names);
    Tasks_UnitID_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_UnitID_Text = new SolidText(Units_Scroller, " Unit");
    Tasks_UnitID = AGETextCtrl::init(CShort, &uiGroupUnitTask, this, &popUp, Units_Scroller);
    Tasks_UnitID_ComboBox = new ComboBox_Plus1(Units_Scroller, Tasks_UnitID, &unit_names);
    UnitComboBoxList.push_back(Tasks_UnitID_ComboBox);
    Tasks_TerrainID_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_TerrainID_Text = new SolidText(Units_Scroller, " Terrain");
    Tasks_TerrainID = AGETextCtrl::init(CShort, &uiGroupUnitTask, this, &popUp, Units_Scroller);
    Tasks_TerrainID_ComboBox = new ComboBox_Plus1(Units_Scroller, Tasks_TerrainID, &terrain_names);
    TerrainComboBoxList.push_back(Tasks_TerrainID_ComboBox);
    Tasks_ResourceIn_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_ResourceIn_Text = new SolidText(Units_Scroller, " Resource In *");
    Tasks_ResourceIn = AGETextCtrl::init(CShort, &uiGroupUnitTask, this, &popUp, Units_Scroller);
    Tasks_ResourceIn->SetToolTip("Resource gained by gathering");
    Tasks_ResourceIn_ComboBox = new ComboBox_Plus1(Units_Scroller, Tasks_ResourceIn, &resource_names);
    ResourceComboBoxList.push_back(Tasks_ResourceIn_ComboBox);
    Tasks_ProdResource_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_ProdResource_Text = new SolidText(Units_Scroller, " Productivity Resource *");
    Tasks_ProdResource = AGETextCtrl::init(CShort, &uiGroupUnitTask, this, &popUp, Units_Scroller);
    Tasks_ProdResource->SetToolTip("Resource that multiplies the amount you gather");
    Tasks_ProdResource_ComboBox = new ComboBox_Plus1(Units_Scroller, Tasks_ProdResource, &resource_names);
    ResourceComboBoxList.push_back(Tasks_ProdResource_ComboBox);
    Tasks_ResourceOut_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_ResourceOut_Text = new SolidText(Units_Scroller, " Resource Out *");
    Tasks_ResourceOut = AGETextCtrl::init(CShort, &uiGroupUnitTask, this, &popUp, Units_Scroller);
    Tasks_ResourceOut->SetToolTip("Resource deposited on drop site");
    Tasks_ResourceOut_ComboBox = new ComboBox_Plus1(Units_Scroller, Tasks_ResourceOut, &resource_names);
    ResourceComboBoxList.push_back(Tasks_ResourceOut_ComboBox);
    Tasks_Resource_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_Resource_Text = new SolidText(Units_Scroller, " Unused Resource");
    Tasks_Resource = AGETextCtrl::init(CShort, &uiGroupUnitTask, this, &popUp, Units_Scroller);
    Tasks_Resource_ComboBox = new ComboBox_Plus1(Units_Scroller, Tasks_Resource, &resource_names);
    ResourceComboBoxList.push_back(Tasks_Resource_ComboBox);
    Tasks_WorkValue1_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_WorkValue1_Text = new SolidText(Units_Scroller, " Work Value 1 *");
    Tasks_WorkValue1 = AGETextCtrl::init(CFloat, &uiGroupUnitTask, this, &popUp, Units_Scroller);
    Tasks_WorkValue1->SetToolTip("Work rate modifier\nMinimum conversion time");
    Tasks_WorkValue2_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_WorkValue2_Text = new SolidText(Units_Scroller, " Work Value 2 *");
    Tasks_WorkValue2 = AGETextCtrl::init(CFloat, &uiGroupUnitTask, this, &popUp, Units_Scroller);
    Tasks_WorkValue2->SetToolTip("Maximum conversion time");
    Tasks_WorkRange_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_WorkRange_Text = new SolidText(Units_Scroller, " Work Range");
    Tasks_WorkRange = AGETextCtrl::init(CFloat, &uiGroupUnitTask, this, &popUp, Units_Scroller);
    for(size_t loop = 0; loop < Tasks_Graphics.size(); ++loop)
    {
        Tasks_Graphics_Holder[loop] = new wxBoxSizer(wxVERTICAL);
        Tasks_Graphics[loop] = AGETextCtrl::init(CShort, &uiGroupUnitTask, this, &popUp, Units_Scroller);
    }
    for(size_t loop = 0; loop < 4; ++loop)
    {
        Tasks_Graphics_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Tasks_Graphics[loop], &graphic_names);
        GraphicComboBoxList.push_back(Tasks_Graphics_ComboBox[loop]);
    }
    for(size_t loop = 4; loop < 6; ++loop)
    {
        Tasks_Graphics_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Tasks_Graphics[loop], &sound_names);
        SoundComboBoxList.push_back(Tasks_Graphics_ComboBox[loop]);
    }
    Tasks_Graphics_Text[0] = new SolidText(Units_Scroller, " Moving Graphic *");
    Tasks_Graphics[0]->SetToolTip("Used when walking with a tool, but carrying no resources");
    Tasks_Graphics_Text[1] = new SolidText(Units_Scroller, " Proceeding Graphic *");
    Tasks_Graphics[1]->SetToolTip("Used when proceeding to gather a resource or attack");
    Tasks_Graphics_Text[2] = new SolidText(Units_Scroller, " Working Graphic *");
    Tasks_Graphics[2]->SetToolTip("Used when actually gathering a resource or attacking/converting");
    Tasks_Graphics_Text[3] = new SolidText(Units_Scroller, " Carrying Graphic *");
    Tasks_Graphics[3]->SetToolTip("Used when carrying a resource");
    Tasks_Graphics_Text[4] = new SolidText(Units_Scroller, " Resource Gathering Sound *");
    Tasks_Graphics[4]->SetToolTip("Example: Plays when lumberjack starts chopping wood");
    Tasks_Graphics_Text[5] = new SolidText(Units_Scroller, " Resource Deposit Sound *");
    Tasks_Graphics[5]->SetToolTip("Example: Plays when lumberjack drops his wood into TC");
    Tasks_AutoSearchTargets_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_AutoSearchTargets_Text = new SolidText(Units_Scroller, " Auto Search *");
    Tasks_AutoSearchTargets = AGETextCtrl::init(CByte, &uiGroupUnitTask, this, &popUp, Units_Scroller);
    Tasks_AutoSearchTargets->SetToolTip("If 1, then auto-search for targets");
    Tasks_EnableTargeting_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_EnableTargeting_Text = new SolidText(Units_Scroller, " Enable Targeting *");
    Tasks_EnableTargeting = AGETextCtrl::init(CByte, &uiGroupUnitTask, this, &popUp, Units_Scroller);
    Tasks_EnableTargeting->SetToolTip("AoE alphas: Target choosing based on combat level\n0   No targeting\n1   Allows units to select their targets");
    Tasks_TargetDiplomacy_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_TargetDiplomacy_Text = new SolidText(Units_Scroller, " Target Diplomacy *");
    Tasks_TargetDiplomacy = AGETextCtrl::init(CByte, &uiGroupUnitTask, this, &popUp, Units_Scroller);
    Tasks_TargetDiplomacy->SetToolTip("Owner Type\nDetermines what you can select as targets\n"
        "0, 7+ All objects\n1   Your objects only\n2   Neutral and enemy objects only\n3   Gaia only\n"
        "4   Gaia, your and ally objects only\n5   Gaia, neutral and enemy objects only\n6   All but your objects");
    Tasks_CarryCheck_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_CarryCheck = AGETextCtrl::init(CByte, &uiGroupUnitTask, this, &popUp, Units_Scroller);
    Tasks_CarryCheck->SetToolTip("Holding Attribute\n0   Right-click target is defined by the target diplomacy.\n1   Preceding the above, checks if target has more than 0 resource.");
    Tasks_CarryCheck_Text = new CheckBox_2State(Units_Scroller, "Carry Check *", Tasks_CarryCheck);
    Tasks_PickForConstruction_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_PickForConstruction = AGETextCtrl::init(CByte, &uiGroupUnitTask, this, &popUp, Units_Scroller);
    Tasks_PickForConstruction->SetToolTip("1   Choose this task if targeting a construction");
    Tasks_PickForConstruction_Text = new CheckBox_2State(Units_Scroller, "Building Pick *", Tasks_PickForConstruction);
    Tasks_GatherType_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_GatherType_Text = new SolidText(Units_Scroller, " Gather Type *");
    Tasks_GatherType = AGETextCtrl::init(CShort, &uiGroupUnitTask, this, &popUp, Units_Scroller);
    Tasks_GatherType->SetToolTip("Work Flag 1\nAoE 1: Used when farm is dead but still exists\n0   Plunder from resource\n1   Plunder from players\n2   Raider thing?");
    Tasks_SearchWaitTime_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_SearchWaitTime_Text = new SolidText(Units_Scroller, " Search Wait Time *");
    Tasks_SearchWaitTime = AGETextCtrl::init(CFloat, &uiGroupUnitTask, this, &popUp, Units_Scroller);
    Tasks_SearchWaitTime->SetToolTip("Unused");
    Tasks_CombatLevelFlag_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_CombatLevelFlag = AGETextCtrl::init(CByte, &uiGroupUnitTask, this, &popUp, Units_Scroller);
    Tasks_CombatLevelFlag_Text = new CheckBox_2State(Units_Scroller, "Unused Flag", Tasks_CombatLevelFlag);
    Tasks_WorkFlag2_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_WorkFlag2_Text = new SolidText(Units_Scroller, " Work Flag 2 *");
    Tasks_WorkFlag2 = AGETextCtrl::init(CShort, &uiGroupUnitTask, this, &popUp, Units_Scroller);
    Tasks_WorkFlag2->SetToolTip("Unused");

//  UnitControls actual interface

    unit_type_names.Add("No Type/Invalid Type");
    unit_type_names.Add("10 - Eye Candy");// Static
    unit_type_names.Add("15 - Tree (AoK)");
    unit_type_names.Add("20 - Animated");
    unit_type_names.Add("25 - Doppelganger");
    unit_type_names.Add("30 - Moving");
    unit_type_names.Add("40 - Actor");// Action
    unit_type_names.Add("50 - Superclass");
    unit_type_names.Add("60 - Projectile");
    unit_type_names.Add("70 - Combatant");// Combat
    unit_type_names.Add("80 - Building");
    unit_type_names.Add("90 - Tree (AoE)");
    Units_Type_ComboBox->Flash();

    Type20.Add("Type");
    Type20.Add("ID");
    Type20.Add("Language File Name");
    Type20.Add("Language File Creation");
    Type20.Add("Class");
    Type20.Add("Standing Graphic x2");
    Type20.Add("Dying Graphic x2");
    Type20.Add("Undead Mode");
    Type20.Add("Hit Points");
    Type20.Add("Line of Sight");
    Type20.Add("Garrison Capacity");
    Type20.Add("Collision Size XY");
    Type20.Add("Collision Size Z");
    Type20.Add("Train Sound");
    Type20.Add("Damage Sound");
    Type20.Add("Dead Unit");
    Type20.Add("Blood Unit");
    Type20.Add("Sort Number");
    Type20.Add("Can be Built on");
    Type20.Add("Icon");
    Type20.Add("Hide In Editor");
    Type20.Add("Portrait Picture");
    Type20.Add("Available");
    Type20.Add("Disabled");
    Type20.Add("Placement Side Terrain x2");
    Type20.Add("Placement Terrain x2");
    Type20.Add("Clearance Size XY");
    Type20.Add("Hill Mode");
    Type20.Add("Fog Visibility");
    Type20.Add("Terrain Table");
    Type20.Add("Fly Mode");
    Type20.Add("Resource Capacity");
    Type20.Add("Resource Decay");
    Type20.Add("Blast Defense Level");
    Type20.Add("Combat Level");
    Type20.Add("Interaction Mode");
    Type20.Add("Minimap Mode");
    Type20.Add("Interface Kind");
    Type20.Add("Multiple Attribute Mode");
    Type20.Add("Minimap Color");
    Type20.Add("Language File Help");
    Type20.Add("Language File Hot Key Text");
    Type20.Add("Hot Key");
    Type20.Add("Recyclable");
    Type20.Add("Gatherable");
    Type20.Add("Doppelganger on Death");
    Type20.Add("Gather Group");
    Type20.Add("Occlusion Mode");
    Type20.Add("Obstruction Type");
    Type20.Add("Obstruction Class");
    Type20.Add("Trait");
    Type20.Add("Civilization");
    Type20.Add("Nothing");
    Type20.Add("Selection Effect");
    Type20.Add("Editor Selection Colour");
    Type20.Add("Selection Size XY");
    Type20.Add("Selection Size Z");
    Type20.Add("Resource Storages 21 bytes");
    Type20.Add("Damage Graphic Count");
    Type20.Add("Damage Graphics");
    Type20.Add("Selection Sound");
    Type20.Add("Dying Sound");
    Type20.Add("Attack Reaction");
    Type20.Add("Convert Terrain");
    Type20.Add("Internal Name");
    Type20.Add("Internal Name 2");
    Type20.Add("Unitline");
    Type20.Add("Min Tech Level");
    Type20.Add("Copy ID");
    Type20.Add("Base ID");

    Type20.Add("Speed");
    // Too lazy to change the indexes.
    Type20.Add("Tracking ID");

    Type30.Add("Walking Graphic x2");
    Type30.Add("Rotation Speed");
    Type30.Add("Size Class");
    Type30.Add("Trailing Unit");
    Type30.Add("Trailing Unit Mode");
    Type30.Add("Trailing Unit Density");
    Type30.Add("Move Algorithm");
    Type30.Add("Rotation Angles 5 floats");

    Type40.Add("Default Task");
    Type40.Add("Search Radius");
    Type40.Add("Work Rate");
    Type40.Add("Drop Site x2");
    Type40.Add("Task Swap Group");
    Type40.Add("Attack Sound");
    Type40.Add("Move Sound");
    Type40.Add("Run Pattern");
    Type40.Add("Task Count");
    Type40.Add("Tasks");

    Type50.Add("Base Armor");
    Type50.Add("Attack Count");
    Type50.Add("Attacks");
    Type50.Add("Armor Count");
    Type50.Add("Armors");
    Type50.Add("Terrain Defense Bonus");
    Type50.Add("Max Range");
    Type50.Add("Blast Width");
    Type50.Add("Reload Time");
    Type50.Add("Projectile Unit");
    Type50.Add("Accuracy Percent");
    Type50.Add("Break off Combat");
    Type50.Add("Frame Delay");
    Type50.Add("Graphic Displacement 3 floats");
    Type50.Add("Blast Attack Level");
    Type50.Add("Min Range");
    Type50.Add("Attack Dispersion");
    Type50.Add("Attack Graphic");
    Type50.Add("Displayed Melee Armor");
    Type50.Add("Displayed Attack");
    Type50.Add("Displayed Range");
    Type50.Add("Displayed Reload Time");

    Type60.Add("Projectile Type");
    Type60.Add("Smart Mode");
    Type60.Add("Hit Mode");
    Type60.Add("Vanish Mode");
    Type60.Add("Area Effect Specials");
    Type60.Add("Projectile Arc");

    Type70.Add("Resource Costs 18 bytes");
    Type70.Add("Train Time");
    Type70.Add("Train Location");
    Type70.Add("Train Button");
    Type70.Add("Rear Attack Modifier");
    Type70.Add("Flank Attack Modifier");
    Type70.Add("Creatable Type");
    Type70.Add("Hero Mode");
    Type70.Add("Garrison Graphic");
    Type70.Add("Total Projectiles");
    Type70.Add("Max Total Projectiles");
    Type70.Add("Projectile Spawning Area 3 floats");
    Type70.Add("Secondary Projectile Unit");
    Type70.Add("Special Graphic");
    Type70.Add("Special Ability");
    Type70.Add("Displayed Pierce Armor");

    Type80.Add("Construction Graphic");
    Type80.Add("Snow Graphic");
    Type80.Add("Adjacent Mode");
    Type80.Add("Graphics Angle");
    Type80.Add("Disappears After Built");
    Type80.Add("Stack Unit");
    Type80.Add("Foundation Terrain");
    Type80.Add("Old Overlay");
    Type80.Add("Tech");
    Type80.Add("Can Burn");
    Type80.Add("Annexes 40 bytes");
    Type80.Add("Head Unit");
    Type80.Add("Transform Unit");
    Type80.Add("Transform Sound");
    Type80.Add("Construction Sound");
    Type80.Add("Garrison Type");
    Type80.Add("Garrison Heal Rate");
    Type80.Add("Garrison Repair Rate");
    Type80.Add("Pile Unit");
    Type80.Add("Looting Table 6 bytes");

    specialcopy_names.Add("Special: graphics only");
    Units_SpecialCopy_Options->Flash();

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
    Units_Special->Add(Units_SpecialCopy_Civs, 0, wxLEFT, 2);

    Units_Searches[0]->Add(Units_Search, 1, wxEXPAND);
    Units_Searches[0]->Add(Units_UseAnd[0], 0, wxLEFT, 2);
    Units_Searches[1]->Add(Units_Search_R, 1, wxEXPAND);
    Units_Searches[1]->Add(Units_UseAnd[1], 0, wxLEFT, 2);

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

//  Type 10+

    Units_ID1_Holder->Add(Units_ID1_Text);
    Units_HitPoints_Holder->Add(Units_HitPoints_Text);
    Units_LineOfSight_Holder->Add(Units_LineOfSight_Text);
    Units_GarrisonCapacity_Holder->Add(Units_GarrisonCapacity_Text);
    Units_SizeRadius_Holder->Add(Units_SizeRadius_Text);
    Units_DeadUnitID_Holder->Add(Units_DeadUnitID_Text);
    Units_BloodUnitID_Holder->Add(Units_BloodUnitID_Text);
    Units_SortNumber_Holder->Add(Units_SortNumber_Text);
    Units_IconAngle_Holder->Add(Units_IconID_Text);
    Units_Portrait_Holder->Add(Units_Portrait_Text);
    Units_PlacementSideTerrain_Holder->Add(Units_PlacementSideTerrain_Text);
    Units_PlacementTerrain_Holder->Add(Units_PlacementTerrain_Text);
    Units_ClearanceSize_Holder->Add(Units_ClearanceSize_Text);
    Units_HillMode_Holder->Add(Units_HillMode_Text);
    Units_TerrainRestriction_Holder->Add(Units_TerrainRestriction_Text);
    Units_ResourceCapacity_Holder->Add(Units_ResourceCapacity_Text);
    Units_ResourceDecay_Holder->Add(Units_ResourceDecay_Text);
    Units_BlastDefenseLevel_Holder->Add(Units_BlastDefenseLevel_Text);
    Units_CombatLevel_Holder->Add(Units_CombatLevel_Text);
    Units_InteractionMode_Holder->Add(Units_InteractionMode_Text);
    Units_MinimapMode_Holder->Add(Units_MinimapMode_Text);
    Units_InterfaceKind_Holder->Add(Units_InterfaceKind_Text);
    Units_MultipleAttributeMode_Holder->Add(Units_MultipleAttributeMode_Text);
    Units_MinimapColor_Holder->Add(Units_MinimapColor_Text);
    Units_CreateDoppelgangerOnDeath_Holder->Add(Units_CreateDoppelgangerOnDeath_Text);
    Units_ResourceGroup_Holder->Add(Units_ResourceGroup_Text);
    Units_OcclusionMode_Holder->Add(Units_OcclusionMode_Text);
    Units_ObstructionType_Holder->Add(Units_ObstructionType_Text);
    Units_ObstructionClass_Holder->Add(Units_ObstructionClass_Text);
    Units_Civ_Holder->Add(Units_Civ_Text);
    Units_Nothing_Holder->Add(Units_Nothing_Text);
    Units_Trait_Holder->Add(Units_Trait_Text);
    Units_SelectionEffect_Holder->Add(Units_SelectionEffect_Text);
    Units_EditorSelectionColour_Holder->Add(Units_EditorSelectionColour_Text);
    Units_SelectionRadius_Holder->Add(Units_SelectionRadius_Text);
    Units_SelectionSound_Holder->Add(Units_SelectionSound_Text);
    Units_DyingSound_Holder->Add(Units_DyingSound_Text);
    Units_AttackReaction_Holder->Add(Units_AttackReaction_Text);
    Units_ConvertTerrain_Holder->Add(Units_ConvertTerrain_Text);
    Units_Name_Holder->Add(Units_Name_Text);
    Units_Name2_Holder->Add(Units_Name2_Text);
    Units_Unitline_Holder->Add(Units_Unitline_Text);
    Units_MinTechLevel_Holder->Add(Units_MinTechLevel_Text);
    Units_CopyID_Holder->Add(Units_CopyID_Text);
    Units_BaseID_Holder->Add(Units_BaseID_Text);
    Units_TelemetryID_Holder->Add(Units_TelemetryID_Text);

//  Type 20+

    Units_Speed_Holder->Add(Units_Speed_Text);

//  Type 30+

    Units_RotationSpeed_Holder->Add(Units_RotationSpeed_Text);
    Units_SizeClass_Holder->Add(Units_SizeClass_Text);
    Units_TrackingUnit_Holder->Add(Units_TrackingUnit_Text);
    Units_TrackingUnitMode_Holder->Add(Units_TrackingUnitMode_Text);
    Units_TrackingUnitDensity_Holder->Add(Units_TrackingUnitDensity_Text);
    Units_MoveAlgorithm_Holder->Add(Units_MoveAlgorithm_Text);
    Units_RotationAngles_Holder->Add(Units_RotationAngles_Text);

//  Type 40+

    Units_SearchRadius_Holder->Add(Units_SearchRadius_Text);
    Units_WorkRate_Holder->Add(Units_WorkRate_Text);
    Units_DropSite_Holder->Add(Units_DropSite_Text);
    Units_TaskSwapGroup_Holder->Add(Units_TaskSwapGroup_Text);
    Units_AttackSound_Holder->Add(Units_AttackSound_Text);
    Units_MoveSound_Holder->Add(Units_MoveSound_Text);
    Units_Exists_Holder->Add(Units_Exists_Text);

//  Type 50+

    Units_BaseArmor_Holder->Add(Units_BaseArmor_Text);
    Units_DefenseTerrainBonus_Holder->Add(Units_DefenseTerrainBonus_Text);
    Units_MaxRange_Holder->Add(Units_MaxRange_Text);
    Units_BlastWidth_Holder->Add(Units_BlastWidth_Text);
    Units_ReloadTime_Holder->Add(Units_ReloadTime_Text);
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
    Units_DisplayedReloadTime_Holder->Add(Units_DisplayedReloadTime_Text);

//  Type 60 only

    Units_ProjectileType_Holder->Add(Units_ProjectileType_Text);
    Units_SmartMode_Holder->Add(Units_SmartMode_Text);
    Units_HitMode_Holder->Add(Units_HitMode_Text);
    Units_VanishMode_Holder->Add(Units_VanishMode_Text);
    Units_AreaEffectSpecials_Holder->Add(Units_AreaEffectSpecials_Text);
    Units_ProjectileArc_Holder->Add(Units_ProjectileArc_Text);

//  Type 70+

    Unit_Cost_Texts->Add(Units_CostType_Text);
    Unit_Cost_Texts->AddSpacer(35);
    Unit_Cost_Texts->Add(Units_CostAmount_Text);
    Unit_Cost_Texts->AddSpacer(15);
    Unit_Cost_Texts->Add(Units_CostUsed_Text);
    Units_TrainTime_Holder->Add(Units_TrainTime_Text);
    Units_TrainLocationID_Holder->Add(Units_TrainLocationID_Text);
    Units_ButtonID_Holder->Add(Units_ButtonID_Text);
    Units_RearAttackModifier_Holder->Add(Units_RearAttackModifier_Text);
    Units_FlankAttackModifier_Holder->Add(Units_FlankAttackModifier_Text);
    Units_CreatableType_Holder->Add(Units_CreatableType_Text);
    Units_MissileCount_Holder->Add(Units_MissileCount_Text);
    Units_MissileDuplicationCount_Holder->Add(Units_MissileDuplicationCount_Text);
    Units_AttackMissileDuplicationSpawning_Holder->Add(Units_AttackMissileDuplicationSpawning_Text);
    Units_ChargingMode_Holder->Add(Units_ChargingMode_Text);
    Units_DisplayedPierceArmour_Holder->Add(Units_DisplayedPierceArmour_Text);

//  Type 80

    Units_ConstructionGraphicID_Holder->Add(Units_ConstructionGraphicID_Text);
    Units_SnowGraphicID_Holder->Add(Units_SnowGraphicID_Text);
    Units_IconAngle_Holder->Add(Units_IconAngle_Text, 0, wxTOP, 10);
    Units_StackUnitID_Holder->Add(Units_StackUnitID_Text);
    Units_TerrainID_Holder->Add(Units_TerrainID_Text);
    Units_OldOverlayID_Holder->Add(Units_OldOverlayID_Text);
    Units_ResearchID_Holder->Add(Units_ResearchID_Text);
    Units_CanBurn_Holder->Add(Units_CanBurn_Text);
    Units_AnnexUnit1_Holder->Add(Units_AnnexUnit_Text);
    Units_AnnexUnitMisplacement1_Holder->Add(Units_AnnexUnitMisplacement_Text);
    Units_HeadUnit_Holder->Add(Units_HeadUnit_Text);
    Units_TransformUnit_Holder->Add(Units_TransformUnit_Text);
    Units_TransformSound_Holder->Add(Units_TransformSound_Text);
    Units_ConstructionSound_Holder->Add(Units_ConstructionSound_Text);
    Units_GarrisonHealRate_Holder->Add(Units_GarrisonHealRate_Text);
    Units_GarrisonRepairRate_Holder->Add(Units_GarrisonRepairRate_Text);
    Units_PileUnit_Holder->Add(Units_PileUnit_Text);
    Units_LootSwitch_Holder->Add(Units_LootSwitch_Text);

//  Type 10+

    Units_ID1_Holder->Add(Units_ID1);
    Units_UndeadMode_Holder->Add(Units_UndeadMode);
    Units_UndeadMode_Holder->Add(Units_UndeadMode_CheckBox, 0, wxLEFT, 2);
    Units_HitPoints_Holder->Add(Units_HitPoints);
    Units_LineOfSight_Holder->Add(Units_LineOfSight);
    Units_GarrisonCapacity_Holder->Add(Units_GarrisonCapacity);
    for(size_t loop = 0; loop < 2; ++loop)
    Units_SizeRadius_Grid->Add(Units_SizeRadius[loop]);
    Units_SizeRadius_Grid->Add(Units_HPBarHeight1);
    Units_SizeRadius_Holder->Add(Units_SizeRadius_Grid);
    Units_DeadUnitID_Holder->Add(Units_DeadUnitID, 0, wxEXPAND);
    Units_DeadUnitID_Holder->Add(Units_DeadUnitID_ComboBox);
    Units_BloodUnitID_Holder->Add(Units_BloodUnitID, 0, wxEXPAND);
    Units_BloodUnitID_Holder->Add(Units_BloodUnitID_ComboBox);
    Units_SortNumber_Holder->Add(Units_SortNumber);
    Units_CanBeBuiltOn_Holder->Add(Units_CanBeBuiltOn);
    Units_CanBeBuiltOn_Holder->Add(Units_CanBeBuiltOn_CheckBox, 0, wxLEFT, 2);
    Units_IconID_Holder->Add(Units_IconID);
    Units_HideInEditor_Holder->Add(Units_HideInEditor);
    Units_HideInEditor_Holder->Add(Units_HideInEditor_CheckBox, 0, wxLEFT, 2);
    Units_Portrait_Holder->Add(Units_Portrait);
    Units_Enabled_Holder->Add(Units_Enabled);
    Units_Enabled_Holder->Add(Units_Enabled_CheckBox, 0, wxLEFT, 2);
    Units_Disabled_Holder->Add(Units_Disabled);
    Units_Disabled_Holder->Add(Units_Disabled_CheckBox, 0, wxLEFT, 2);
    for(size_t loop = 0; loop < 2; ++loop)
    Units_PlacementSideTerrainGrid_Holder->Add(Units_PlacementSideTerrain[loop], 0, wxEXPAND);
    for(size_t loop = 0; loop < 2; ++loop)
    Units_PlacementSideTerrainGrid_Holder->Add(Units_PlacementSideTerrain_ComboBox[loop]);
    Units_PlacementSideTerrain_Holder->Add(Units_PlacementSideTerrainGrid_Holder);
    for(size_t loop = 0; loop < 2; ++loop)
    Units_PlacementTerrainGrid_Holder->Add(Units_PlacementTerrain[loop], 0, wxEXPAND);
    for(size_t loop = 0; loop < 2; ++loop)
    Units_PlacementTerrainGrid_Holder->Add(Units_PlacementTerrain_ComboBox[loop]);
    Units_PlacementTerrain_Holder->Add(Units_PlacementTerrainGrid_Holder);
    for(size_t loop = 0; loop < 2; ++loop)
    Units_ClearanceSize_Grid->Add(Units_ClearanceSize[loop]);
    Units_ClearanceSize_Holder->Add(Units_ClearanceSize_Grid);
    Units_HillMode_Holder->Add(Units_HillMode);
    Units_FogVisibility_Holder->Add(Units_FogVisibility_Text);
    Units_FogVisibility_Holder->Add(Units_FogVisibility);
    Units_TerrainRestriction_Holder->Add(Units_TerrainRestriction, 0, wxEXPAND);
    Units_TerrainRestriction_Holder->Add(Units_TerrainRestriction_ComboBox);
    Units_FlyMode_Holder->Add(Units_FlyMode);
    Units_FlyMode_Holder->Add(Units_FlyMode_CheckBox, 0, wxLEFT, 2);
    Units_ResourceCapacity_Holder->Add(Units_ResourceCapacity);
    Units_ResourceDecay_Holder->Add(Units_ResourceDecay);
    Units_BlastDefenseLevel_Holder->Add(Units_BlastDefenseLevel);
    Units_CombatLevel_Holder->Add(Units_CombatLevel);
    Units_InteractionMode_Holder->Add(Units_InteractionMode);
    Units_MinimapMode_Holder->Add(Units_MinimapMode);
    Units_InterfaceKind_Holder->Add(Units_InterfaceKind);
    Units_MultipleAttributeMode_Holder->Add(Units_MultipleAttributeMode);
    Units_MinimapColor_Holder->Add(Units_MinimapColor);
    Units_Recyclable_Holder->Add(Units_Recyclable);
    Units_Recyclable_Holder->Add(Units_Recyclable_CheckBox, 0, wxLEFT, 2);
    Units_TrackAsResource_Holder->Add(Units_TrackAsResource);
    Units_TrackAsResource_Holder->Add(Units_TrackAsResource_CheckBox, 0, wxLEFT, 2);
    Units_CreateDoppelgangerOnDeath_Holder->Add(Units_CreateDoppelgangerOnDeath);
    Units_ResourceGroup_Holder->Add(Units_ResourceGroup);
    Units_OcclusionMode_Holder->Add(Units_OcclusionMode);
    Units_ObstructionType_Holder->Add(Units_ObstructionType);
    Units_ObstructionClass_Holder->Add(Units_ObstructionClass);
    for(size_t loop = 0; loop < 8; ++loop)
    Units_Trait_Grid->Add(Units_Trait_CheckBox[loop]);
    Units_Trait_Holder->Add(Units_Trait, 0, wxEXPAND);
    Units_Trait_Holder->Add(Units_Trait_Grid);
    Units_Civ_Holder->Add(Units_Civ, 0, wxEXPAND);
    Units_Civ_Holder->Add(Units_Civ_ComboBox);
    Units_Nothing_Holder->Add(Units_Nothing);
    Units_SelectionEffect_Holder->Add(Units_SelectionEffect);
    Units_EditorSelectionColour_Holder->Add(Units_EditorSelectionColour, 0, wxEXPAND);
    for(size_t loop = 0; loop < 2; ++loop)
    Units_SelectionRadiusBox->Add(Units_SelectionRadius[loop]);
    Units_SelectionRadiusBox->Add(Units_HPBarHeight2);
    Units_SelectionRadius_Holder->Add(Units_SelectionRadiusBox);
    Units_SelectionSound_Holder->Add(Units_SelectionSound, 0, wxEXPAND);
    Units_SelectionSound_Holder->Add(Units_SelectionSound_ComboBox);
    Units_DyingSound_Holder->Add(Units_DyingSound, 0, wxEXPAND);
    Units_DyingSound_Holder->Add(Units_DyingSound_ComboBox);
    Units_AttackReaction_Holder->Add(Units_AttackReaction);
    Units_ConvertTerrain_Holder->Add(Units_ConvertTerrain);
    Units_Name_Holder->Add(Units_Name);
    Units_Name2_Holder->Add(Units_Name2);
    Units_Unitline_Holder->Add(Units_Unitline, 0, wxEXPAND);
    Units_Unitline_Holder->Add(Units_Unitline_ComboBox);
    Units_MinTechLevel_Holder->Add(Units_MinTechLevel, 0, wxEXPAND);
    Units_MinTechLevel_Holder->Add(Units_MinTechLevel_ComboBox);
    Units_CopyID_Holder->Add(Units_CopyID);
    Units_BaseID_Holder->Add(Units_BaseID);
    Units_TelemetryID_Holder->Add(Units_TelemetryID);

//  Type 20+

    Units_Speed_Holder->Add(Units_Speed);

//  Type 30+

    Units_RotationSpeed_Holder->Add(Units_RotationSpeed);
    Units_SizeClass_Holder->Add(Units_SizeClass);
    Units_TrackingUnit_Holder->Add(Units_TrackingUnit, 0, wxEXPAND);
    Units_TrackingUnit_Holder->Add(Units_TrackingUnit_ComboBox);
    Units_TrackingUnitMode_Holder->Add(Units_TrackingUnitMode, 0, wxEXPAND);
    Units_TrackingUnitDensity_Holder->Add(Units_TrackingUnitDensity, 0, wxEXPAND);
    Units_MoveAlgorithm_Holder->Add(Units_MoveAlgorithm);
    for(size_t loop = 0; loop < Units_RotationAngles.size(); ++loop)
    Units_RotationAngles_Grid->Add(Units_TurnStats_Text[loop]);
    for(size_t loop = 0; loop < Units_RotationAngles.size(); ++loop)
    Units_RotationAngles_Grid->Add(Units_RotationAngles[loop]);
    Units_RotationAngles_Holder->Add(Units_RotationAngles_Grid);

//  Type 40+

    Units_DefaultTaskID_Holder->Add(Units_DefaultTaskID_Text);
    Units_DefaultTaskID_Holder->Add(Units_DefaultTaskID, 0, wxEXPAND);
    Units_DefaultTaskID_Holder->Add(Units_DefaultTaskID_ComboBox);
    Units_SearchRadius_Holder->Add(Units_SearchRadius);
    Units_WorkRate_Holder->Add(Units_WorkRate);
    Units_DropSite_Grid->Add(Units_DropSite[0], 0, wxEXPAND);
    Units_DropSite_Grid->Add(Units_DropSite[1], 0, wxEXPAND);
    Units_DropSite_Grid->Add(Units_DropSite_ComboBox[0]);
    Units_DropSite_Grid->Add(Units_DropSite_ComboBox[1]);
    Units_TaskSwapGroup_Holder->Add(Units_TaskSwapGroup);
    Units_AttackSound_Holder->Add(Units_AttackSound, 0, wxEXPAND);
    Units_AttackSound_Holder->Add(Units_AttackSound_ComboBox);
    Units_MoveSound_Holder->Add(Units_MoveSound, 0, wxEXPAND);
    Units_MoveSound_Holder->Add(Units_MoveSound_ComboBox);
    Units_RunPattern_Holder->Add(Units_RunPattern_Text);
    Units_RunPattern_Holder->Add(Units_RunPattern);
    Units_Exists_Holder->Add(Units_Exists);

//  Type 50+

    Units_BaseArmor_Holder->Add(Units_BaseArmor);
    Units_DefenseTerrainBonus_Holder->Add(Units_DefenseTerrainBonus, 0, wxEXPAND);
    Units_DefenseTerrainBonus_Holder->Add(Units_DefenseTerrainBonus_ComboBox);
    Units_MaxRange_Holder->Add(Units_MaxRange);
    Units_BlastWidth_Holder->Add(Units_BlastWidth);
    Units_ReloadTime_Holder->Add(Units_ReloadTime);
    Units_AccuracyPercent_Holder->Add(Units_AccuracyPercent);
    Units_TowerMode_Holder->Add(Units_TowerMode_Text);
    Units_TowerMode_Holder->Add(Units_TowerMode);
    Units_Delay_Holder->Add(Units_Delay);
    for(size_t loop = 0; loop < 3; ++loop)
    Units_GraphicDisplacement_Grid->Add(Units_GraphicDisplacement[loop]);
    Units_GraphicDisplacement_Holder->Add(Units_GraphicDisplacement_Grid);
    Units_BlastAttackLevel_Holder->Add(Units_BlastAttackLevel);
    Units_MinRange_Holder->Add(Units_MinRange);
    Units_AccuracyDispersion_Holder->Add(Units_AccuracyDispersion);
    Units_AttackGraphic_Holder->Add(Units_AttackGraphic, 0, wxEXPAND);
    Units_AttackGraphic_Holder->Add(Units_AttackGraphic_ComboBox);
    Units_DisplayedMeleeArmour_Holder->Add(Units_DisplayedMeleeArmour);
    Units_DisplayedAttack_Holder->Add(Units_DisplayedAttack);
    Units_DisplayedRange_Holder->Add(Units_DisplayedRange);
    Units_DisplayedReloadTime_Holder->Add(Units_DisplayedReloadTime);

//  Type 60 only

    Units_ProjectileType_Holder->Add(Units_ProjectileType);
    Units_SmartMode_Holder->Add(Units_SmartMode);
    Units_HitMode_Holder->Add(Units_HitMode);
    Units_VanishMode_Holder->Add(Units_VanishMode);
    Units_AreaEffectSpecials_Holder->Add(Units_AreaEffectSpecials);
    Units_ProjectileArc_Holder->Add(Units_ProjectileArc);

//  Type 70+

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
    Units_TrainTime_Holder->Add(Units_TrainTime);
    Units_TrainLocationID_Holder->Add(Units_TrainLocationID, 0, wxEXPAND);
    Units_TrainLocationID_Holder->Add(Units_TrainLocationID_ComboBox);
    Units_ButtonID_Holder->Add(Units_ButtonID);
    Units_RearAttackModifier_Holder->Add(Units_RearAttackModifier);
    Units_FlankAttackModifier_Holder->Add(Units_FlankAttackModifier);
    Units_CreatableType_Holder->Add(Units_CreatableType);
    Units_HeroMode_Holder->Add(Units_HeroMode);
    Units_HeroMode_Holder->Add(Units_HeroMode_CheckBox, 0, wxLEFT, 2);
    Units_MissileCount_Holder->Add(Units_MissileCount);
    Units_MissileDuplicationCount_Holder->Add(Units_MissileDuplicationCount, 0, wxEXPAND);
    for(size_t loop = 0; loop < 3; ++loop)
    Units_AttackMissileDuplicationSpawning_Grid->Add(Units_AttackMissileDuplicationSpawning[loop]);
    Units_AttackMissileDuplicationSpawning_Holder->Add(Units_AttackMissileDuplicationSpawning_Grid);
    Units_ChargingMode_Holder->Add(Units_ChargingMode);
    Units_DisplayedPierceArmour_Holder->Add(Units_DisplayedPierceArmour);

//  Type 80

    Units_ConstructionGraphicID_Holder->Add(Units_ConstructionGraphicID, 0, wxEXPAND);
    Units_ConstructionGraphicID_Holder->Add(Units_ConstructionGraphicID_ComboBox);
    Units_SnowGraphicID_Holder->Add(Units_SnowGraphicID, 0, wxEXPAND);
    Units_SnowGraphicID_Holder->Add(Units_SnowGraphicID_ComboBox);
    Units_AdjacentMode_Holder->Add(Units_AdjacentMode);
    Units_AdjacentMode_Holder->Add(Units_AdjacentMode_CheckBox, 0, wxLEFT, 2);
    Units_BuildAndVanish_Holder->Add(Units_DisappearsWhenBuilt);
    Units_BuildAndVanish_Holder->Add(Units_BuildAndVanish_CheckBox, 0, wxLEFT, 2);
    Units_IconID_Holder->Add(Units_IconAngle);
    Units_StackUnitID_Holder->Add(Units_StackUnitID, 0, wxEXPAND);
    Units_StackUnitID_Holder->Add(Units_StackUnitID_ComboBox);
    Units_TerrainID_Holder->Add(Units_TerrainID, 0, wxEXPAND);
    Units_TerrainID_Holder->Add(Units_TerrainID_ComboBox);
    Units_OldOverlayID_Holder->Add(Units_OldOverlayID);
    Units_ResearchID_Holder->Add(Units_ResearchID, 0, wxEXPAND);
    Units_ResearchID_Holder->Add(Units_ResearchID_ComboBox);
    Units_CanBurn_Holder->Add(Units_CanBurn);
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
    Units_TransformSound_Holder->Add(Units_TransformSound, 0, wxEXPAND);
    Units_TransformSound_Holder->Add(Units_TransformSound_ComboBox);
    Units_ConstructionSound_Holder->Add(Units_ConstructionSound, 0, wxEXPAND);
    Units_ConstructionSound_Holder->Add(Units_ConstructionSound_ComboBox);
    Units_GarrisonHealRate_Holder->Add(Units_GarrisonHealRate);
    Units_GarrisonRepairRate_Holder->Add(Units_GarrisonRepairRate);
    Units_PileUnit_Holder->Add(Units_PileUnit, 0, wxEXPAND);
    Units_PileUnit_Holder->Add(Units_PileUnit_ComboBox);
    for(size_t loop = 0; loop < Units_LootSwitch.size(); ++loop)
    Units_LootSwitch_Grid->Add(Units_LootSwitch[loop]);
    Units_LootSwitch_Holder->Add(Units_LootSwitch_Grid);

    Units_ResourceStorage_Texts->Add(ResourceStorage_Type_Text);
    Units_ResourceStorage_Texts->AddSpacer(35);
    Units_ResourceStorage_Texts->Add(ResourceStorage_Amount_Text);
    Units_ResourceStorage_Texts->AddSpacer(15);
    Units_ResourceStorage_Texts->Add(ResourceStorage_Mode_Text);
    for(size_t loop = 0; loop < 3; ++loop)
    {
        Units_ResourceStorage_Holder[loop]->Add(ResourceStorage_Type[loop], 0, wxEXPAND);
        Units_ResourceStorage_Holder[loop]->Add(ResourceStorage_Type_ComboBox[loop]);
        Units_ResourceStorage_Holder[loop]->Add(ResourceStorage_Amount[loop], 0, wxEXPAND | wxTOP, 5);
        Units_ResourceStorage_Holder[loop]->Add(ResourceStorage_Mode[loop], 0, wxTOP, 5);
    }

    Attacks_Class_Holder->Add(Attacks_Class_Text);
    Attacks_Class_Holder->Add(Attacks_Class, 0, wxEXPAND);
    Attacks_Class_Holder->Add(Attacks_Class_ComboBox[0]);
    Attacks_Amount_Holder->Add(Attacks_Amount_Text);
    Attacks_Amount_Holder->Add(Attacks_Amount);

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
    Armors_Amount_Holder->Add(Armors_Amount);

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

    Tasks_Type_Holder->Add(Tasks_Type_Text);
    Tasks_Type_Holder->Add(Tasks_Type);
    Tasks_ID_Holder->Add(Tasks_ID_Text);
    Tasks_ID_Holder->Add(Tasks_ID);
    Tasks_IsDefault_Holder->Add(Tasks_IsDefault_Text);
    Tasks_IsDefault_Holder->Add(Tasks_IsDefault);
    Tasks_ActionType_Holder->Add(Tasks_ActionType_Text);
    Tasks_ActionType_Holder->Add(Tasks_ActionType, 0, wxEXPAND);
    Tasks_ActionType_Holder->Add(Tasks_ActionType_ComboBox);
    Tasks_ProdResource_Holder->Add(Tasks_ProdResource_Text);
    Tasks_ProdResource_Holder->Add(Tasks_ProdResource, 0, wxEXPAND);
    Tasks_ProdResource_Holder->Add(Tasks_ProdResource_ComboBox);
    Tasks_ClassID_Holder->Add(Tasks_ClassID_Text);
    Tasks_ClassID_Holder->Add(Tasks_ClassID, 0, wxEXPAND);
    Tasks_ClassID_Holder->Add(Units_Class_ComboBox[1]);
    Tasks_UnitID_Holder->Add(Tasks_UnitID_Text);
    Tasks_UnitID_Holder->Add(Tasks_UnitID, 0, wxEXPAND);
    Tasks_UnitID_Holder->Add(Tasks_UnitID_ComboBox);
    Tasks_TerrainID_Holder->Add(Tasks_TerrainID_Text);
    Tasks_TerrainID_Holder->Add(Tasks_TerrainID, 0, wxEXPAND);
    Tasks_TerrainID_Holder->Add(Tasks_TerrainID_ComboBox);
    Tasks_ResourceIn_Holder->Add(Tasks_ResourceIn_Text);
    Tasks_ResourceIn_Holder->Add(Tasks_ResourceIn, 0, wxEXPAND);
    Tasks_ResourceIn_Holder->Add(Tasks_ResourceIn_ComboBox);
    Tasks_ResourceOut_Holder->Add(Tasks_ResourceOut_Text);
    Tasks_ResourceOut_Holder->Add(Tasks_ResourceOut, 0, wxEXPAND);
    Tasks_ResourceOut_Holder->Add(Tasks_ResourceOut_ComboBox);
    Tasks_Resource_Holder->Add(Tasks_Resource_Text);
    Tasks_Resource_Holder->Add(Tasks_Resource, 0, wxEXPAND);
    Tasks_Resource_Holder->Add(Tasks_Resource_ComboBox);
    Tasks_WorkValue1_Holder->Add(Tasks_WorkValue1_Text);
    Tasks_WorkValue1_Holder->Add(Tasks_WorkValue1);
    Tasks_WorkValue2_Holder->Add(Tasks_WorkValue2_Text);
    Tasks_WorkValue2_Holder->Add(Tasks_WorkValue2);
    Tasks_WorkRange_Holder->Add(Tasks_WorkRange_Text);
    Tasks_WorkRange_Holder->Add(Tasks_WorkRange);
    Tasks_AutoSearchTargets_Holder->Add(Tasks_AutoSearchTargets_Text);
    Tasks_AutoSearchTargets_Holder->Add(Tasks_AutoSearchTargets);
    Tasks_SearchWaitTime_Holder->Add(Tasks_SearchWaitTime_Text);
    Tasks_SearchWaitTime_Holder->Add(Tasks_SearchWaitTime);
    Tasks_EnableTargeting_Holder->Add(Tasks_EnableTargeting_Text);
    Tasks_EnableTargeting_Holder->Add(Tasks_EnableTargeting);
    Tasks_CombatLevelFlag_Holder->Add(Tasks_CombatLevelFlag_Text);
    Tasks_CombatLevelFlag_Holder->Add(Tasks_CombatLevelFlag);
    Tasks_GatherType_Holder->Add(Tasks_GatherType_Text);
    Tasks_GatherType_Holder->Add(Tasks_GatherType);
    Tasks_WorkFlag2_Holder->Add(Tasks_WorkFlag2_Text);
    Tasks_WorkFlag2_Holder->Add(Tasks_WorkFlag2);
    Tasks_TargetDiplomacy_Holder->Add(Tasks_TargetDiplomacy_Text);
    Tasks_TargetDiplomacy_Holder->Add(Tasks_TargetDiplomacy);
    Tasks_CarryCheck_Holder->Add(Tasks_CarryCheck_Text);
    Tasks_CarryCheck_Holder->Add(Tasks_CarryCheck);
    Tasks_PickForConstruction_Holder->Add(Tasks_PickForConstruction_Text);
    Tasks_PickForConstruction_Holder->Add(Tasks_PickForConstruction);

    Units_TypeArea_Holder->Add(Units_Name_Holder);
    Units_TypeArea_Holder->Add(Units_Name2_Holder, 0, wxLEFT, 5);
    Units_TypeArea_Holder->Add(Units_ID1_Holder, 0, wxLEFT, 5);
    Units_TypeArea_Holder->Add(Units_CopyID_Holder, 0, wxLEFT, 5);
    Units_TypeArea_Holder->Add(Units_BaseID_Holder, 0, wxLEFT, 5);
    Units_TypeArea_Holder->Add(Units_TelemetryID_Holder, 0, wxLEFT, 5);

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

    Units_LangDLLArea_Holder->Add(Units_LangRegular_Holder);
    Units_LangDLLArea_Holder->Add(Units_LangHotKey_Holder, 0, wxTOP | wxBOTTOM, 5);
    Units_LangDLLArea_Holder->Add(Units_DLL_LanguageHelp, 0, wxEXPAND);
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
    DamageGraphics_Useless_Holder->Add(DamageGraphics_Useless_Text);
    DamageGraphics_Useless_Holder->Add(DamageGraphics_Useless);
    DamageGraphics_DamagePercent_Holder->Add(DamageGraphics_DamagePercent_Text);
    DamageGraphics_DamagePercent_Holder->Add(DamageGraphics_DamagePercent);
    DamageGraphics_ApplyMode_Holder->Add(DamageGraphics_ApplyMode_Text);
    DamageGraphics_ApplyMode_Holder->Add(DamageGraphics_ApplyMode);
    Units_DamageGraphics_Holder_Data->Add(slp_dmg_unit, 0, wxBOTTOM, 5);
    Units_DamageGraphics_Holder_Data->Add(DamageGraphics_GraphicID_Holder);
    Units_DamageGraphics_Holder_Data->Add(DamageGraphics_DamagePercent_Holder, 0, wxTOP, 5);
    Units_DamageGraphics_Holder_Data->Add(DamageGraphics_ApplyMode_Holder, 0, wxTOP, 5);
    Units_DamageGraphics_Holder_Data->Add(DamageGraphics_Useless_Holder, 0, wxTOP, 5);

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
    Units_GraphicsArea_Holder->Add(autoCopyHelp);
    Units_GraphicsArea_Holder->Add(sizer_slp);
    Units_GraphicsArea_Holder->Add(Units_GraphicsArea1_Holder, 0, wxTOP | wxEXPAND, 5);
    Units_GraphicsArea_Holder->Add(Units_GraphicsArea5_Holder, 0, wxTOP, 5);

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
    Units_Attacks_Holder_Data->Add(Units_DisplayedAttack_Holder);
    Units_Attacks_Holder_Data->Add(Units_Delay_Holder);
    Units_Attacks_Holder_Data->Add(Units_AccuracyPercent_Holder);
    Units_Attacks_Holder_Data->Add(Units_AccuracyDispersion_Holder);
    Units_Attacks_Holder_Data->Add(Units_ReloadTime_Holder);
    Units_Attacks_Holder_Data->Add(Units_DisplayedReloadTime_Holder);
    Units_Attacks_Holder_Data->Add(Units_BlastWidth_Holder);
    Units_Attacks_Holder_Data->Add(Units_BlastAttackLevel_Holder);

    Units_Armors_DataArea->Add(Armors_Amount_Holder);
    Units_Armors_DataArea->Add(Armors_Class_Holder, 0, wxTOP, 5);
    Units_Armors_Holder_Data3->Add(Units_BlastDefenseLevel_Holder, 0, wxTOP, 5);
    Units_Armors_Holder_Data3->Add(Units_BaseArmor_Holder, 0, wxTOP, 5);
    Units_Armors_Holder_Data3->Add(Units_DefenseTerrainBonus_Holder, 0, wxTOP, 5);
    Units_Armors_Holder_Data3->Add(Units_DisplayedMeleeArmour_Holder, 0, wxTOP, 5);
    Units_Armors_Holder_Data3->Add(Units_DisplayedPierceArmour_Holder, 0, wxTOP, 5);

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

    Units_StatsArea_Holder->Add(Units_StatsArea1A_Sizer);
    Units_StatsArea_Holder->Add(Units_StatsArea1B_Sizer, 0, wxTOP, 5);
    Units_StatsArea_Holder->Add(Units_Attacks_Holder, 0, wxEXPAND | wxTOP, 5);
    Units_StatsArea_Holder->Add(Units_Armors_Holder, 0, wxEXPAND | wxTOP, 5);
    Units_StatsArea_Holder->Add(Units_StatsArea2_Grid, 0, wxTOP, 5);
    Units_StatsArea_Holder->Add(Units_StatsAreaGarrison_Grid, 0, wxTOP, 5);

    Units_ProjectileUnitID_Holder->Add(Units_ProjectileUnitID_Text);
    Units_ProjectileUnitID_Holder->Add(Units_ProjectileUnitID, 0, wxEXPAND);
    Units_ProjectileUnitID_Holder->Add(Units_ProjectileUnitID_ComboBox);
    Units_AttackMissileDuplicationUnit_Holder->Add(Units_AttackMissileDuplicationUnit_Text);
    Units_AttackMissileDuplicationUnit_Holder->Add(Units_AttackMissileDuplicationUnit, 0, wxEXPAND);
    Units_AttackMissileDuplicationUnit_Holder->Add(Units_AttackMissileDuplicationUnit_ComboBox);
    Units_ChargingGraphic_Holder->Add(Units_ChargingGraphic_Text);
    Units_ChargingGraphic_Holder->Add(Units_ChargingGraphic, 0, wxEXPAND);
    Units_ChargingGraphic_Holder->Add(Units_ChargingGraphic_ComboBox);

    Units_P1->Add(Units_ProjectileUnitID_Holder, 0, wxRIGHT, 5);
    Units_P1->Add(Units_AttackMissileDuplicationUnit_Holder, 0, wxRIGHT, 5);
    Units_P1->Add(Units_MissileCount_Holder, 0, wxRIGHT, 5);
    Units_P1->Add(Units_MissileDuplicationCount_Holder);
    Units_P2->Add(Units_GraphicDisplacement_Holder, 0, wxRIGHT, 5);
    Units_P2->Add(Units_AttackMissileDuplicationSpawning_Holder);

    Units_P3->Add(Units_ProjectileType_Holder, 0, wxRIGHT, 5);
    Units_P3->Add(Units_SmartMode_Holder, 0, wxRIGHT, 5);
    Units_P3->Add(Units_HitMode_Holder, 0, wxRIGHT, 5);
    Units_P3->Add(Units_VanishMode_Holder, 0, wxRIGHT, 5);
    Units_P3->Add(Units_AreaEffectSpecials_Holder);
    Units_ProjectileArea_Holder->Add(Units_P1, 0, wxBOTTOM, 5);
    Units_ProjectileArea_Holder->Add(Units_P2, 0, wxBOTTOM, 5);
    Units_ProjectileArea_Holder->Add(Units_P3, 0, wxBOTTOM, 5);
    Units_ProjectileArea_Holder->Add(Units_ProjectileArc_Holder, 0, wxBOTTOM, 5);

    Units_AB1_Grid->Add(Units_Enabled_Holder);
    Units_AB1_Grid->Add(Units_Disabled_Holder);
    Units_AB1_Grid->Add(Units_UndeadMode_Holder);
    Units_AB1_Grid->Add(Units_CanBeBuiltOn_Holder);
    Units_AB1_Grid->Add(Units_HideInEditor_Holder);
    Units_AB1_Grid->Add(Units_FlyMode_Holder);
    Units_AB1_Grid->Add(Units_Recyclable_Holder);
    Units_AB1_Grid->Add(Units_TrackAsResource_Holder);
    Units_AB1_Grid->Add(Units_HeroMode_Holder);
    Units_AB1_Grid->Add(Units_AdjacentMode_Holder);
    Units_AB1_Grid->Add(Units_BuildAndVanish_Holder);

    Units_AM1_Grid->Add(Units_SortNumber_Holder);
    Units_AM1_Grid->Add(Units_HillMode_Holder);
    Units_AM1_Grid->Add(Units_FogVisibility_Holder);
    Units_AM1_Grid->Add(Units_CombatLevel_Holder);
    Units_AM1_Grid->Add(Units_InteractionMode_Holder);
    Units_AM1_Grid->Add(Units_MinimapMode_Holder);
    Units_AM1_Grid->Add(Units_MinimapColor_Holder);
    Units_AM1_Grid->Add(Units_CreateDoppelgangerOnDeath_Holder);
    Units_AM1_Grid->Add(Units_ResourceGroup_Holder);
    Units_AM1_Grid->Add(Units_TaskSwapGroup_Holder);
    Units_AM1_Grid->Add(Units_ChargingMode_Holder);

    Units_A2_Grid->Add(Units_Trait_Holder);
    Units_DropSite_Holder->Add(Units_DropSite_Grid);
    Units_AS_Holder->Add(Units_SizeRadius_Holder, 0, wxRIGHT, 5);
    Units_AS_Holder->Add(Units_ClearanceSize_Holder);
    Units_AS1_Grid->Add(Units_OcclusionMode_Holder, 0, wxRIGHT, 5);
    Units_AS1_Grid->Add(Units_ObstructionType_Holder, 0, wxRIGHT, 5);
    Units_AS1_Grid->Add(Units_ObstructionClass_Holder, 0, wxRIGHT, 5);
    Units_AS1_Grid->Add(Units_SelectionEffect_Holder, 0, wxRIGHT, 5);
    Units_AS1_Grid->Add(Units_EditorSelectionColour_Holder);
    Units_ResourceStorageHeader_Holder->Add(Units_ResourceStorage_Texts);
    for(auto &sizer: Units_ResourceStorage_Holder)
    Units_ResourceStorageHeader_Holder->Add(sizer, 0, wxLEFT, 5);
    Units_A2_Grid->Add(Units_Civ_Holder, 0, wxLEFT, 5);
    Units_A2_Grid->Add(Units_Nothing_Holder, 0, wxLEFT, 5);
    Units_A1_Grid->Add(Units_DeadUnitID_Holder);
    Units_A1_Grid->Add(Units_BloodUnitID_Holder, 0, wxLEFT, 5);
    Units_A1_Grid->Add(Units_Unitline_Holder, 0, wxLEFT, 5);
    Units_A1_Grid->Add(Units_MinTechLevel_Holder, 0, wxLEFT, 5);
    Units_A4_Grid->Add(Units_PlacementTerrain_Holder, 0, wxRIGHT, 5);
    Units_A4_Grid->Add(Units_PlacementSideTerrain_Holder);
    Units_A5_Grid->Add(Units_TerrainRestriction_Holder);
    Units_Tracking_Grid->Add(Units_TrackingUnit_Holder);
    Units_Tracking_Grid->Add(Units_TrackingUnitMode_Holder, 0, wxLEFT, 5);
    Units_Tracking_Grid->Add(Units_TrackingUnitDensity_Holder, 0, wxLEFT, 5);
    Units_CostHeader_Holder->Add(Unit_Cost_Texts);
    for(auto &sizer: Unit_Cost_Sizers)
    Units_CostHeader_Holder->Add(sizer, 0, wxLEFT, 5);
    Units_Training_Grid->Add(Units_InterfaceKind_Holder);
    Units_Training_Grid->Add(Units_TrainTime_Holder, 0, wxLEFT, 5);
    Units_Training_Grid->Add(Units_TrainLocationID_Holder, 0, wxLEFT, 5);
    Units_A3_Grid->Add(Units_StackUnitID_Holder);
    Units_A5_Grid->Add(Units_TerrainID_Holder);
    Units_A5_Grid->Add(Units_ResearchID_Holder);
    Units_A6_Grid->Add(Units_DefaultTaskID_Holder);
    Units_A6_Grid->Add(Units_DropSite_Holder, 0, wxLEFT, 5);
    Units_A3_Grid->Add(Units_HeadUnit_Holder, 0, wxLEFT, 5);
    Units_A3_Grid->Add(Units_TransformUnit_Holder, 0, wxLEFT, 5);
    Units_A3_Grid->Add(Units_PileUnit_Holder, 0, wxLEFT, 5);
    Units_Training_Grid->Add(Units_ButtonID_Holder, 0, wxLEFT, 5);

    Units_Attributes_Holder->Add(Units_AB1_Grid);
    Units_Attributes_Holder->Add(Units_AM1_Grid, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_A2_Grid, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_A1_Grid, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_A4_Grid, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_A5_Grid, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_A6_Grid, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_AS_Holder, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_SelectionRadius_Holder, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_AS1_Grid, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_Tracking_Grid, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_RotationAngles_Holder, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_Training_Grid, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_ResourceStorageHeader_Holder, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_CostHeader_Holder, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_A3_Grid, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_AnnexUnit1_Holder, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_AnnexUnitMisplacement1_Holder, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_LootSwitch_Holder, 0, wxTOP, 5);

    Units_TrainSound_Holder->Add(Units_TrainSound_Text);
    Units_DamageSound_Holder->Add(Units_DamageSound_Text);
    Units_TrainSound_Holder->Add(Units_TrainSound, 0, wxEXPAND);
    Units_TrainSound_Holder->Add(Units_TrainSound_ComboBox);
    Units_DamageSound_Holder->Add(Units_DamageSound, 0, wxEXPAND);
    Units_DamageSound_Holder->Add(Units_DamageSound_ComboBox);

    Units_SoundsArea1_Holder->Add(Units_SelectionSound_Holder);
    Units_SoundsArea1_Holder->Add(Units_DyingSound_Holder, 0, wxLEFT, 5);
    Units_SoundsArea1_Holder->Add(Units_TrainSound_Holder, 0, wxLEFT, 5);
    Units_SoundsArea1_Holder->Add(Units_DamageSound_Holder, 0, wxLEFT, 5);
    Units_SoundsArea2_Grid->Add(Units_AttackSound_Holder);
    Units_SoundsArea2_Grid->Add(Units_MoveSound_Holder, 0, wxLEFT, 5);
    Units_SoundsArea2_Grid->Add(Units_ConstructionSound_Holder, 0, wxLEFT, 5);
    Units_SoundsArea2_Grid->Add(Units_TransformSound_Holder, 0, wxLEFT, 5);

    Units_SoundsArea_Holder->Add(Units_SoundsArea1_Holder);
    Units_SoundsArea_Holder->Add(Units_SoundsArea2_Grid, 0, wxTOP, 5);

    Units_Obsoletes_Holder->Add(Units_Portrait_Holder);
    Units_Obsoletes_Holder->Add(Units_MultipleAttributeMode_Holder);
    Units_Obsoletes_Holder->Add(Units_AttackReaction_Holder);
    Units_Obsoletes_Holder->Add(Units_ConvertTerrain_Holder);

    Units_Obsoletes_Holder->AddStretchSpacer(1);
    Units_Obsoletes_Holder->Add(Units_SizeClass_Holder);
    Units_Obsoletes_Holder->Add(Units_MoveAlgorithm_Holder);

    Units_Obsoletes_Holder->Add(Units_RunPattern_Holder);

    Units_Obsoletes_Holder->Add(Units_TowerMode_Holder);

    Units_Obsoletes_Holder->Add(Units_OldOverlayID_Holder);
    Units_Obsoletes_Holder->Add(Units_RearAttackModifier_Holder);
    Units_Obsoletes_Holder->Add(Units_FlankAttackModifier_Holder);
    Units_Obsoletes_Holder->Add(Units_CreatableType_Holder);

    Units_Obsoletes_Holder->Add(Units_CanBurn_Holder);
    Units_Obsoletes_Holder->Add(Units_GarrisonRepairRate_Holder);

    Units_Tasks_Buttons->Add(Units_Tasks_Add, 1, wxEXPAND);
    Units_Tasks_Buttons->Add(Units_Tasks_Delete, 1, wxEXPAND);
    Units_Tasks_Buttons->Add(Units_Tasks_Insert, 1, wxEXPAND);
    Units_Tasks_Buttons->Add(Units_Tasks_Copy, 1, wxEXPAND);
    Units_Tasks_Buttons->Add(Units_Tasks_Paste, 1, wxEXPAND);
    Units_Tasks_Buttons->Add(Units_Tasks_PasteInsert, 1, wxEXPAND);

    TaskHolder_Lists->Add(Units_UnitHeads_Name, 0, wxEXPAND | wxBOTTOM, 5);
    TaskHolder_Lists->Add(Units_Tasks_Search, 0, wxEXPAND);
    TaskHolder_Lists->Add(Units_Tasks_Search_R, 0, wxEXPAND);
    TaskHolder_Lists->Add(Units_Tasks_ListV, 0, wxEXPAND | wxBOTTOM | wxTOP, 2);
    TaskHolder_Lists->Add(Units_Tasks_Buttons, 0, wxEXPAND);
    TaskHolder_Lists->Add(Units_Tasks_CopyToUnits, 0, wxEXPAND | wxTOP, 2);
    TaskHolder_Lists->Add(Units_Exists_Holder, 0, wxEXPAND | wxTOP, 5);
    TaskHolder_Lists->Add(slp_unit_actions, 0, wxTOP, 5);

    Tasks_Known1->Add(Tasks_ActionType_Holder, 0, wxLEFT, 5);
    Tasks_Known1->Add(Tasks_Type_Holder, 0, wxLEFT, 5);
    Tasks_Known1->Add(Tasks_ID_Holder, 0, wxLEFT, 5);
    Tasks_Known1->Add(Tasks_IsDefault_Holder, 0, wxLEFT, 5);
    Tasks_Known2->Add(Tasks_ClassID_Holder);
    Tasks_Known2->Add(Tasks_UnitID_Holder);
    Tasks_Known2->Add(Tasks_TerrainID_Holder);
    Tasks_Known2->Add(Tasks_ResourceIn_Holder);
    Tasks_Known2->Add(Tasks_ProdResource_Holder);
    Tasks_Known2->Add(Tasks_ResourceOut_Holder);
    Tasks_Known3->Add(Tasks_Resource_Holder, 0, wxLEFT, 5);
    Tasks_Known3->Add(Tasks_WorkValue1_Holder, 0, wxLEFT, 5);
    Tasks_Known3->Add(Tasks_WorkValue2_Holder, 0, wxLEFT, 5);
    Tasks_Known3->Add(Tasks_WorkRange_Holder, 0, wxLEFT, 5);

    for(size_t loop = 0; loop < Tasks_Graphics.size(); ++loop)
    {
        Tasks_Graphics_Holder[loop]->Add(Tasks_Graphics_Text[loop]);
        Tasks_Graphics_Holder[loop]->Add(Tasks_Graphics[loop], 0, wxEXPAND);
        Tasks_Graphics_Holder[loop]->Add(Tasks_Graphics_ComboBox[loop]);
        Tasks_Known4->Add(Tasks_Graphics_Holder[loop]);
    }

    Tasks_Known5->Add(Tasks_AutoSearchTargets_Holder);
    Tasks_Known5->Add(Tasks_EnableTargeting_Holder);
    Tasks_Known5->Add(Tasks_TargetDiplomacy_Holder);
    Tasks_Known5->Add(Tasks_CarryCheck_Holder);
    Tasks_Known5->Add(Tasks_PickForConstruction_Holder);
    Tasks_Known5->Add(Tasks_GatherType_Holder);
    Tasks_Known5->Add(Tasks_SearchWaitTime_Holder);
    Tasks_Known5->Add(Tasks_CombatLevelFlag_Holder);
    Tasks_Known5->Add(Tasks_WorkFlag2_Holder);

    TaskHolder_Data->Add(Tasks_Known1);
    TaskHolder_Data->Add(Tasks_Known2, 0, wxTOP | wxLEFT, 5);
    TaskHolder_Data->Add(Tasks_Known3, 0, wxTOP, 5);
    TaskHolder_Data->Add(Tasks_Known4, 0, wxTOP | wxLEFT, 5);
    TaskHolder_Data->Add(Tasks_Known5, 0, wxTOP | wxLEFT, 5);

    TasksArea_Holder->Add(TaskHolder_Lists, 1, wxEXPAND);
    TasksArea_Holder->Add(TaskHolder_Data, 3, wxEXPAND, 5);

    Units_Obsoletes_Area->Add(Units_Obsoletes_Holder);

    Units_ScrollSpace->Add(Units_LangDLLArea_Holder, 0, wxEXPAND);
    Units_ScrollSpace->Add(Units_GraphicsArea_Holder, 0, wxEXPAND | wxTOP, 5);
    Units_ScrollSpace->Add(Units_StatsArea_Holder, 0, wxEXPAND | wxTOP, 5);
    Units_ScrollSpace->Add(Units_ProjectileArea_Holder, 0, wxEXPAND | wxTOP, 5);
    Units_ScrollSpace->Add(Units_Attributes_Holder, 0, wxEXPAND | wxTOP, 5);
    Units_ScrollSpace->Add(Units_SoundsArea_Holder, 0, wxEXPAND | wxTOP, 5);
    Units_ScrollSpace->Add(Units_Obsoletes_Area, 0, wxEXPAND | wxTOP, 5);
    Units_ScrollSpace->Add(TasksArea_Holder, 0, wxEXPAND | wxTOP, 5);

    Units_Scroller->SetSizer(Units_ScrollSpace);
    Units_Scroller->SetScrollRate(0, 20);

    Units_Top_Holder->Add(Units_AutoCopy);
    Units_Top_Holder->Add(Units_CopyTo);
    Units_Top_Holder->Add(Units_CopyGraphics, 0, wxLEFT, 5);
    Units_Top_Holder->Add(Units_CopyToText);
    Units_Top_Holder->Add(Units_SelectAll);
    Units_Top_Holder->Add(Units_SelectClear);
    Units_Top_Holder->Add(Units_GraphicSetText);
    Units_Top_Holder->Add(Units_GraphicSet);
    Units_Identity_Holder->Add(Units_Type_Holder);
    Units_Identity_Holder->Add(Units_TypeArea_Holder, 0, wxTOP, 5);

    Units_DataArea->Add(Units_Top_Holder, 0, wxEXPAND | wxTOP, 15);
    Units_DataArea->Add(Units_TopGrid_Holder, 0, wxEXPAND);
    Units_DataArea->Add(Units_Identity_Holder, 0, wxEXPAND);
    Units_DataArea->Add(Units_Scroller, 1, wxEXPAND | wxTOP, 5);

    Units_Main->Add(Units_Units, 21, wxEXPAND | wxALL, 5);
    Units_Main->Add(Units_DataArea, 65, wxEXPAND | wxBOTTOM | wxRIGHT, 5);

    Units_ID1->Enable(false);
    Units_CopyID->Enable(false);
    Units_BaseID->Enable(false);
    Tasks_ID->Enable(false);
    Units_TelemetryID_Holder->Show(false);
    Units_BloodUnitID_Holder->Show(false);

    Tab_Units->SetSizer(Units_Main);

    Units_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnUnitsSearch, this);
    Units_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnUnitsSearch, this);
    Units_FilterSelector->Bind(wxEVT_COMBOBOX, [this](wxCommandEvent&)
    {
        ListUnits(UnitCivID, false);
        Units_Search->SetFocus();
    });
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Units_UseAnd[loop]->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnUnitsSearch, this);
        Units_SearchFilters[loop]->Bind(wxEVT_COMBOBOX, [this](wxCommandEvent&)
        {
            ListUnits(UnitCivID, false);
            Units_Search->SetFocus();
        });
    }
    Units_Civs_List->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUnitsSearch, this);
    Units_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnUnitSelect, this);

    Units_Add->Bind(wxEVT_BUTTON, [this](wxCommandEvent&)
    {
        if(!dataset) return;

        wxBusyCursor WaitCursor;
        if(GenieVersion >= genie::GV_AoK)   // AoK, TC, SWGB or CC
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
            dataset->Civs[loop].Units[dataset->Civs.front().Units.size()-1].ID = (int16_t)(dataset->Civs.front().Units.size()-1); // ID Fix
            dataset->Civs[loop].Units[dataset->Civs.front().Units.size()-1].CopyID = (int16_t)(dataset->Civs.front().Units.size()-1);
            if(GenieVersion >= genie::GV_AoK)
            dataset->Civs[loop].Units[dataset->Civs.front().Units.size()-1].BaseID = (int16_t)(dataset->Civs.front().Units.size()-1);
        }
        How2List = ADD;
        ListUnits(UnitCivID);

        if(GenieVersion < genie::GV_SWGB && dataset->Civs.front().Units.size() > 900) SetStatusText("Units between 900 and 1000 mess up the AI!", 0);
    });

    Units_Insert->Bind(wxEVT_BUTTON, [this](wxCommandEvent&)
    {
        auto selections = Units_ListV->GetSelectedCount();
        if(selections < 1) return;

        wxBusyCursor WaitCursor;
        if(GenieVersion >= genie::GV_AoK)   // AoK, TC, SWGB or CC
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
            for(size_t loop2 = UnitIDs.front();loop2 < dataset->Civs.front().Units.size(); ++loop2) // ID Fix
            {
                dataset->Civs[loop].Units[loop2].ID = loop2;
                dataset->Civs[loop].Units[loop2].CopyID = loop2;
                if(GenieVersion >= genie::GV_AoK)
                dataset->Civs[loop].Units[loop2].BaseID = loop2;
            }
        }
        How2List = INSNEW;
        ListUnits(UnitCivID);
    });

    Units_Delete->Bind(wxEVT_BUTTON, [this](wxCommandEvent&)
    {
        auto selections = Units_ListV->GetSelectedCount();
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
            for(size_t loop = UnitIDs.front(); loop < dataset->Civs.front().Units.size(); ++loop) // ID Fix
            {
                dataset->Civs[civ].Units[loop].ID = loop;
                dataset->Civs[civ].Units[loop].CopyID = loop;
                if(GenieVersion >= genie::GV_AoK)
                dataset->Civs[civ].Units[loop].BaseID = loop;
            }
        }
        How2List = DEL;
        ListUnits(UnitCivID);
    });

    Units_Copy->Bind(wxEVT_BUTTON, [this](wxCommandEvent&)
    {
        auto selections = Units_ListV->GetSelectedCount();
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
    });

    Units_SpecialCopy->Bind(wxEVT_BUTTON, [this](wxCommandEvent&)
    {
        auto selections = Units_ListV->GetSelectedCount();
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
    });

    Units_SpecialPaste->Bind(wxEVT_BUTTON, [this](wxCommandEvent&)
    {
        short CopyCount = copies.Dat.UnitGraphics.front().size();
        if(!Units_ListV->GetSelectedCount() || CopyCount == 0) return;

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
        wxCommandEvent e;
        OnUnitSelect(e);
        Units_ListV->SetFocus();
    });

    Units_Paste->Bind(wxEVT_BUTTON, [this](wxCommandEvent&)
    {
        if(!Units_ListV->GetSelectedCount() || copies.Dat.UnitExists.size() == 0) return;

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

                PasteUnits(true);
                for(size_t civ = 0; civ < dataset->Civs.size(); ++civ)
                {
                    for(size_t loop = 0; loop < copies.Dat.UnitCopies.front().size(); ++loop)
                    {
                        size_t paste_pos = UnitIDs[loop];
                        dataset->Civs[civ].UnitPointers[paste_pos] = copies.Dat.UnitExists[civ][loop];
                        dataset->Civs[civ].Units[paste_pos].ID = paste_pos;
                        dataset->Civs[civ].Units[paste_pos].CopyID = paste_pos;
                        if(GenieVersion >= genie::GV_AoK)
                        dataset->Civs[civ].Units[paste_pos].BaseID = paste_pos;
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
                    dataset->Civs[civ].Units[paste_pos].ID = paste_pos;
                    dataset->Civs[civ].Units[paste_pos].CopyID = paste_pos;
                    if(GenieVersion >= genie::GV_AoK)
                    dataset->Civs[civ].Units[paste_pos].BaseID = paste_pos;
                }
            }
        }
        How2List = PASTE;
        ListUnits(UnitCivID);

        SetStatusText("Unit special paste", 2);
        SetStatusText("Edits: "+std::to_string(popUp.unSaved)+" + "+FormatInt(copies.Dat.UnitCopies.front().size()), 3);
        popUp.unSaved += copies.Dat.UnitCopies.front().size();
    });

    Units_PasteInsert->Bind(wxEVT_BUTTON, [this](wxCommandEvent&)
    {
        if(!Units_ListV->GetSelectedCount() || copies.Dat.UnitExists.size() == 0) return;

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
            for(size_t loop = UnitIDs.front();loop < dataset->Civs.front().Units.size(); ++loop)
            {
                dataset->Civs[civ].Units[loop].ID = loop;
                dataset->Civs[civ].Units[loop].CopyID = loop;
                if(GenieVersion >= genie::GV_AoK)
                dataset->Civs[civ].Units[loop].BaseID = loop;
            }
        }
        How2List = INSPASTE;
        ListUnits(UnitCivID);
    });

    Units_Enable->Bind(wxEVT_BUTTON, [this](wxCommandEvent&)
    {
        auto selections = Units_ListV->GetSelectedCount();
        if(selections < 1) return;

        wxBusyCursor WaitCursor;
        int UnitCivID = Units_Civs_List->GetSelection();
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
                    Attacks = dataset->Civs[civ].Units[UnitIDs[sel]].Combat.Attacks.size();
                    Armors = dataset->Civs[civ].Units[UnitIDs[sel]].Combat.Armours.size();
                    if(GenieVersion < genie::GV_AoK)
                    Commands = dataset->Civs[civ].Units[UnitIDs[sel]].Action.TaskList.size();
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
                    dataset->Civs[civ].Units[UnitIDs[sel]].Combat.Attacks.resize(Attacks);
                    dataset->Civs[civ].Units[UnitIDs[sel]].Combat.Armours.resize(Armors);
                    dataset->Civs[civ].Units[UnitIDs[sel]].Action.TaskList.resize(Commands);
                    dataset->Civs[civ].Units[UnitIDs[sel]].ID = UnitIDs[sel]; // ID Fix
                    dataset->Civs[civ].Units[UnitIDs[sel]].CopyID = UnitIDs[sel];
                    if(GenieVersion >= genie::GV_AoKA)
                    dataset->Civs[civ].Units[UnitIDs[sel]].BaseID = UnitIDs[sel];
                }
            }
            else
            {
                if(dataset->Civs[UnitCivID].UnitPointers[UnitIDs[sel]] == 0)
                {
                    dataset->Civs[UnitCivID].UnitPointers[UnitIDs[sel]] = 1;
                    dataset->Civs[UnitCivID].Units[UnitIDs[sel]].Type = UnitType;
                    dataset->Civs[UnitCivID].Units[UnitIDs[sel]].DamageGraphics.resize(DamageGraphics);
                    dataset->Civs[UnitCivID].Units[UnitIDs[sel]].Combat.Attacks.resize(Attacks);
                    dataset->Civs[UnitCivID].Units[UnitIDs[sel]].Combat.Armours.resize(Armors);
                    dataset->Civs[UnitCivID].Units[UnitIDs[sel]].Action.TaskList.resize(Commands);
                    dataset->Civs[UnitCivID].Units[UnitIDs[sel]].ID = UnitIDs[sel]; // ID Fix
                    dataset->Civs[UnitCivID].Units[UnitIDs[sel]].CopyID = UnitIDs[sel];
                    if(GenieVersion >= genie::GV_AoKA)
                    dataset->Civs[UnitCivID].Units[UnitIDs[sel]].BaseID = UnitIDs[sel];
                }
            }
        }
        How2List = ENABLE;
        ListUnits(UnitCivID);
    });

    Units_Disable->Bind(wxEVT_BUTTON, [this](wxCommandEvent&)
    {
        auto selections = Units_ListV->GetSelectedCount();
        if(selections < 1) return;

        wxBusyCursor WaitCursor;
        int UnitCivID = Units_Civs_List->GetSelection();
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
    });

    Units_Tasks_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnUnitCommandSelect, this);
    Units_Tasks_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnUnitCommandsSearch, this);
    Units_Tasks_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnUnitCommandsSearch, this);
    Units_Tasks_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitCommandsAdd, this);
    Units_Tasks_Insert->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitCommandsInsert, this);
    Units_Tasks_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitCommandsDelete, this);
    Units_Tasks_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitCommandsCopy, this);
    Units_Tasks_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitCommandsPaste, this);
    Units_Tasks_PasteInsert->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitCommandsPasteInsert, this);
    Units_Tasks_CopyToUnits->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitCommandsCopyToUnits, this);
    Units_DamageGraphics_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnUnitDamageGraphicsSearch, this);
    Units_DamageGraphics_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnUnitDamageGraphicsSearch, this);
    Units_DamageGraphics_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnUnitDamageGraphicSelect, this);
    Units_DamageGraphics_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitDamageGraphicsAdd, this);
    Units_DamageGraphics_Insert->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitDamageGraphicsInsert, this);
    Units_DamageGraphics_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitDamageGraphicsDelete, this);
    Units_DamageGraphics_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitDamageGraphicsCopy, this);
    Units_DamageGraphics_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitDamageGraphicsPaste, this);
    Units_DamageGraphics_PasteInsert->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitDamageGraphicsPasteInsert, this);
    Units_DamageGraphics_CopyToUnits->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitDamageGraphicsCopyToUnits, this);
    Units_Attacks_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnUnitAttacksSearch, this);
    Units_Attacks_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnUnitAttacksSearch, this);
    Units_Attacks_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnUnitAttackSelect, this);
    Units_Attacks_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitAttacksAdd, this);
    Units_Attacks_Insert->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitAttacksInsert, this);
    Units_Attacks_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitAttacksDelete, this);
    Units_Attacks_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitAttacksCopy, this);
    Units_Attacks_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitAttacksPaste, this);
    Units_Attacks_PasteInsert->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitAttacksPasteInsert, this);
    Units_Attacks_CopyToUnits->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitAttacksCopyToUnits, this);
    Units_Armors_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnUnitArmorsSearch, this);
    Units_Armors_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnUnitArmorsSearch, this);
    Units_Armors_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnUnitArmorSelect, this);
    Units_Armors_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitArmorsAdd, this);
    Units_Armors_Insert->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitArmorsInsert, this);
    Units_Armors_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitArmorsDelete, this);
    Units_Armors_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitArmorsCopy, this);
    Units_Armors_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitArmorsPaste, this);
    Units_Armors_PasteInsert->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitArmorsPasteInsert, this);
    Units_Armors_CopyToUnits->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitArmorsCopyToUnits, this);
    Units_LanguageDLLConverter[0]->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::UnitLangDLLConverter, this);
    Units_LanguageDLLConverter[1]->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::UnitLangDLLConverter, this);
    slp_radio->Bind(wxEVT_RADIOBOX, &AGE_Frame::OnChooseGraphic, this);
    slp_unit_actions->Bind(wxEVT_RADIOBOX, &AGE_Frame::OnChooseGraphic, this);
    slp_dmg_unit->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnChooseGraphic, this);
    slp_snow->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnChooseGraphic, this);
    slp_garrison->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnChooseGraphic, this);

    Units_DLL_LanguageName->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_LangDLL, this);
    Units_DLL_LanguageCreation->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_LangDLL, this);
    Units_DLL_HotKey4->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_LangDLL, this);
    Units_DLL_LanguageHelp->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_LangDLL, this);
    Units_DLL_LanguageHKText->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_LangDLL, this);

//  Listing and Auto-Copy

    Units_Type->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_Type->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_Type_ComboBox->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);

    Units_Name->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_Name->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_Name2->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_Name2->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_LanguageDLLName->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_LanguageDLLName->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_LanguageDLLCreation->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_LanguageDLLCreation->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_HotKey->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_HotKey->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_LanguageDLLHelp->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_LanguageDLLHelp->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_LanguageDLLHotKeyText->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_LanguageDLLHotKeyText->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_Trait->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_Trait->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_GarrisonType->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_GarrisonType->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);

    DamageGraphics_GraphicID->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    DamageGraphics_GraphicID->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    DamageGraphics_GraphicID_ComboBox->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    DamageGraphics_DamagePercent->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    DamageGraphics_DamagePercent->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    DamageGraphics_Useless->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    DamageGraphics_Useless->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Attacks_Class->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Attacks_Class->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Attacks_Amount->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Attacks_Amount->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Armors_Class->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Armors_Class->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Armors_Amount->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Armors_Amount->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    for(size_t loop = 0; loop < 2; ++loop)
    Attacks_Class_ComboBox[loop]->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);

    Tasks_ActionType->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Tasks_ActionType->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Tasks_ProdResource->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Tasks_ProdResource->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Tasks_ActionType_ComboBox->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    for(size_t loop = 0; loop < 8; ++loop)
    {
        Units_Trait_CheckBox[loop]->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnUpdateCheck_UnitAttribute, this);
        Units_GarrisonType_CheckBox[loop]->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnUpdateCheck_UnitGarrisonType, this);
    }
    Units_IconID->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_IconID->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_IconAngle->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_IconAngle->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_IconID_SLP->Bind(wxEVT_PAINT, &AGE_Frame::OnDrawIconSLP, this);
    Units_IconID_SLP->Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent&){});

    // To make SLP view refresh.
    Units_ConstructionGraphicID->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_ConstructionGraphicID->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_SnowGraphicID->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_SnowGraphicID->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_GarrisonGraphic->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_GarrisonGraphic->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_ChargingGraphic->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_ChargingGraphic->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_AttackGraphic->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_AttackGraphic->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_WalkingGraphic[0]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_WalkingGraphic[0]->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_WalkingGraphic[1]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_WalkingGraphic[1]->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_StandingGraphic[0]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_StandingGraphic[0]->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_StandingGraphic[1]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_StandingGraphic[1]->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_DyingGraphic[0]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_DyingGraphic[0]->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_DyingGraphic[1]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_DyingGraphic[1]->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Tasks_Graphics[0]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Tasks_Graphics[0]->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Tasks_Graphics[1]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Tasks_Graphics[1]->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Tasks_Graphics[2]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Tasks_Graphics[2]->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Tasks_Graphics[3]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Tasks_Graphics[3]->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_ConstructionGraphicID_ComboBox->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    Units_SnowGraphicID_ComboBox->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    Units_GarrisonGraphic_ComboBox->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    Units_ChargingGraphic_ComboBox->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    Units_AttackGraphic_ComboBox->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    Units_WalkingGraphic_ComboBox[0]->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    Units_WalkingGraphic_ComboBox[1]->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    Units_StandingGraphic_ComboBox[0]->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    Units_StandingGraphic_ComboBox[1]->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    Units_DyingGraphic_ComboBox[0]->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    Units_DyingGraphic_ComboBox[1]->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    Tasks_Graphics_ComboBox[0]->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    Tasks_Graphics_ComboBox[1]->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    Tasks_Graphics_ComboBox[2]->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    Tasks_Graphics_ComboBox[3]->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    Units_SizeRadius[0]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_SizeRadius[0]->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_SizeRadius[1]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_SizeRadius[1]->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_ClearanceSize[0]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_ClearanceSize[0]->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_ClearanceSize[1]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_ClearanceSize[1]->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_SelectionRadius[0]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_SelectionRadius[0]->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    Units_SelectionRadius[1]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_SelectionRadius[1]->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    for(size_t loop = 0; loop < 4; ++loop)
    {
        Units_AnnexUnitMisplacement[loop][0]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
        Units_AnnexUnitMisplacement[loop][0]->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
        Units_AnnexUnitMisplacement[loop][1]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
        Units_AnnexUnitMisplacement[loop][1]->Bind(wxEVT_TEXT_ENTER, &AGE_Frame::OnEnter_Units, this);
    }
}

void AGE_Frame::OnSaveEdits_Units(int id)
{
    if(id == Units_Name->GetId() || id == Units_LanguageDLLName->GetId())
    {
        ListUnits(UnitCivID);
    }
    else if(id == Units_Type->GetId()
    || id == Units_Name2->GetId()
    || id == Units_LanguageDLLCreation->GetId()
    || id == Units_HotKey->GetId()
    || id == Units_LanguageDLLHelp->GetId()
    || id == Units_LanguageDLLHotKeyText->GetId()
    || id == Units_Trait->GetId()
    || id == Units_GarrisonType->GetId()
    || id == Units_IconID->GetId()
    || id == Units_IconAngle->GetId())
    {
        wxCommandEvent e;
        OnUnitSelect(e);
    }
    else if(id == Attacks_Amount->GetId() || id == Attacks_Class->GetId())
    {
        ListUnitAttacks();
    }
    else if(id == Armors_Amount->GetId() || id == Armors_Class->GetId())
    {
        ListUnitArmors();
    }
    else if(id == Tasks_ActionType->GetId() || id == Tasks_ProdResource->GetId())
    {
        ListUnitCommands();
    }
    else if(id == DamageGraphics_GraphicID->GetId()
    || id == DamageGraphics_DamagePercent->GetId())
    {
        ListUnitDamageGraphics();
    }
    else
    {
        wxCommandEvent E;
        OnChooseGraphic(E);
    }
}

void AGE_Frame::OnEnter_Units(wxCommandEvent &event)
{
    static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
    OnSaveEdits_Units(event.GetId());
}

void AGE_Frame::OnKillFocus_Units(wxFocusEvent &event)
{
    event.Skip();
    if(static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() != 0) return;
    OnSaveEdits_Units(event.GetId());
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
        wxCommandEvent e;
        OnUnitSelect(e);    // Updates unit layout.
//      ListUnits(UnitCivID, false);    // For special search filters.
        return;
    }
    if(event.GetId() == Tasks_ActionType_ComboBox->GetId())
    {
        switch(Tasks_ActionType_ComboBox->GetSelection())
        {
            case 1: Tasks_ActionType->ChangeValue("0"); break;
            case 2: Tasks_ActionType->ChangeValue("1"); break;
            case 3: Tasks_ActionType->ChangeValue("2"); break;
            case 4: Tasks_ActionType->ChangeValue("3"); break;
            case 5: Tasks_ActionType->ChangeValue("4"); break;
            case 6: Tasks_ActionType->ChangeValue("5"); break;
            case 7: Tasks_ActionType->ChangeValue("6"); break;
            case 8: Tasks_ActionType->ChangeValue("7"); break;
            case 9: Tasks_ActionType->ChangeValue("8"); break;
            case 10: Tasks_ActionType->ChangeValue("9"); break;
            case 11: Tasks_ActionType->ChangeValue("10"); break;
            case 12: Tasks_ActionType->ChangeValue("11"); break;
            case 13: Tasks_ActionType->ChangeValue("12"); break;
            case 14: Tasks_ActionType->ChangeValue("13"); break;
            case 15: Tasks_ActionType->ChangeValue("14"); break;
            case 16: Tasks_ActionType->ChangeValue("20"); break;
            case 17: Tasks_ActionType->ChangeValue("21"); break;
            case 18: Tasks_ActionType->ChangeValue("101"); break;
            case 19: Tasks_ActionType->ChangeValue("102"); break;
            case 20: Tasks_ActionType->ChangeValue("103"); break;
            case 21: Tasks_ActionType->ChangeValue("104"); break;
            case 22: Tasks_ActionType->ChangeValue("105"); break;
            case 23: Tasks_ActionType->ChangeValue("106"); break;
            case 24: Tasks_ActionType->ChangeValue("107"); break;
            case 25: Tasks_ActionType->ChangeValue("108"); break;
            case 26: Tasks_ActionType->ChangeValue("109"); break;
            case 27: Tasks_ActionType->ChangeValue("110"); break;
            case 28: Tasks_ActionType->ChangeValue("111"); break;
            case 29: Tasks_ActionType->ChangeValue("120"); break;
            case 30: Tasks_ActionType->ChangeValue("121"); break;
            case 31: Tasks_ActionType->ChangeValue("122"); break;
            case 32: Tasks_ActionType->ChangeValue("123"); break;
            case 33: Tasks_ActionType->ChangeValue("124"); break;
            case 34: Tasks_ActionType->ChangeValue("125"); break;
            case 35: Tasks_ActionType->ChangeValue("130"); break;
            case 36: Tasks_ActionType->ChangeValue("131"); break;
            case 37: Tasks_ActionType->ChangeValue("132"); break;
            case 38: Tasks_ActionType->ChangeValue("133"); break;
            case 39: Tasks_ActionType->ChangeValue("134"); break;
            case 40: Tasks_ActionType->ChangeValue("135"); break;
            case 41: Tasks_ActionType->ChangeValue("136"); break;
            case 42: Tasks_ActionType->ChangeValue("149"); break;
            case 43: Tasks_ActionType->ChangeValue("150"); break;
            case 44: Tasks_ActionType->ChangeValue("151"); break;
            default: Tasks_ActionType->ChangeValue("-1");
        }
        Tasks_ActionType->SaveEdits();
        ListUnitCommands();
        return;
    }
    static_cast<ComboBox_Plus1*>(event.GetEventObject())->OnChoose(event);
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
        uint8_t type = stoi(std::string(Units_GarrisonType->GetValue()));
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
    catch(const std::exception&)
    {
        Units_GarrisonType->clear();
        Units_GarrisonType->ChangeValue("Error");
    }
}

void AGE_Frame::OnUpdateCheck_UnitAttribute(wxCommandEvent &event)
{
    if(Units_Trait->GetValue().empty()) return;
    try
    {
        uint8_t attribute = stoi(std::string(Units_Trait->GetValue()));
        Units_Trait_CheckBox[0]->GetValue() ? attribute |= 0x01 : attribute &= ~0x01;
        Units_Trait_CheckBox[1]->GetValue() ? attribute |= 0x02 : attribute &= ~0x02;
        Units_Trait_CheckBox[2]->GetValue() ? attribute |= 0x04 : attribute &= ~0x04;
        Units_Trait_CheckBox[3]->GetValue() ? attribute |= 0x08 : attribute &= ~0x08;
        Units_Trait_CheckBox[4]->GetValue() ? attribute |= 0x10 : attribute &= ~0x10;
        Units_Trait_CheckBox[5]->GetValue() ? attribute |= 0x20 : attribute &= ~0x20;
        Units_Trait_CheckBox[6]->GetValue() ? attribute |= 0x40 : attribute &= ~0x40;
        Units_Trait_CheckBox[7]->GetValue() ? attribute |= 0x80 : attribute &= ~0x80;
        Units_Trait->ChangeValue(FormatInt(attribute));
        Units_Trait->SaveEdits();
    }
    catch(const std::exception&)
    {
        Units_Trait->clear();
        Units_Trait->ChangeValue("Error");
    }
}
