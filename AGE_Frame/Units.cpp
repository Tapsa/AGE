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
    if(!LangDLLstring(dataset->Civs[civ].Units[index].LanguageDLLName, 2).empty())
    {
        return Name + LangDLLstring(dataset->Civs[civ].Units[index].LanguageDLLName, 64);
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
            return "I1 " + FormatInt(unit_ptr->ID1);
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
            return "DG " + FormatInt(unit_ptr->DyingGraphic.first) + " "
                    + FormatInt(unit_ptr->DyingGraphic.second);
        });
        else if(label.compare(Type20[7]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "DM " + FormatInt(unit_ptr->DeathMode);
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
            return "SR " + FormatInt(unit_ptr->CollisionSize.x) + " "
                    + FormatInt(unit_ptr->CollisionSize.y);
        });
        else if(label.compare(Type20[12]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "B1 " + FormatFloat(unit_ptr->CollisionSize.z);
        });
        else if(label.compare(Type20[13]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "TS " + FormatInt(unit_ptr->TrainSound.first) + " "
                    + FormatInt(unit_ptr->TrainSound.second);
        });
        else if(label.compare(Type20[14]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "DU " + FormatInt(unit_ptr->DeadUnitID);
        });
        else if(label.compare(Type20[15]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "PM " + FormatInt(unit_ptr->PlacementMode);
        });
        else if(label.compare(Type20[16]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "AM " + FormatInt(unit_ptr->AirMode);
        });
        else if(label.compare(Type20[17]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "I " + FormatInt(unit_ptr->IconID);
        });
        else if(label.compare(Type20[18]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "HE " + FormatInt(unit_ptr->HideInEditor);
        });
        else if(label.compare(Type20[19]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "U1 " + FormatInt(unit_ptr->Unknown1);
        });
        else if(label.compare(Type20[20]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "E " + FormatInt(unit_ptr->Enabled);
        });
        else if(label.compare(Type20[21]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "D " + FormatInt(unit_ptr->Disabled);
        });
        else if(label.compare(Type20[22]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "PBT " + FormatInt(unit_ptr->PlacementSideTerrain.first) + " "
                    + FormatInt(unit_ptr->PlacementSideTerrain.second);
        });
        else if(label.compare(Type20[23]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "PT " + FormatInt(unit_ptr->PlacementTerrain.first) + " "
                    + FormatInt(unit_ptr->PlacementTerrain.second);
        });
        else if(label.compare(Type20[24]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "ER " + FormatInt(unit_ptr->ClearanceSize.first) + " "
                    + FormatInt(unit_ptr->ClearanceSize.second);
        });
        else if(label.compare(Type20[25]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "HM " + FormatInt(unit_ptr->HillMode);
        });
        else if(label.compare(Type20[26]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "VF " + FormatInt(unit_ptr->VisibleInFog);
        });
        else if(label.compare(Type20[27]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "TR " + FormatInt(unit_ptr->TerrainRestriction);
        });
        else if(label.compare(Type20[28]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "FM " + FormatInt(unit_ptr->FlyMode);
        });
        else if(label.compare(Type20[29]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "RC " + FormatInt(unit_ptr->ResourceCapacity);
        });
        else if(label.compare(Type20[30]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "RD " + FormatFloat(unit_ptr->ResourceDecay);
        });
        else if(label.compare(Type20[31]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "BA " + FormatInt(unit_ptr->BlastDefenseLevel);
        });
        else if(label.compare(Type20[32]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "U2 " + FormatInt(unit_ptr->SubType);
        });
        else if(label.compare(Type20[33]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "IM " + FormatInt(unit_ptr->InteractionMode);
        });
        else if(label.compare(Type20[34]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "MM " + FormatInt(unit_ptr->MinimapMode);
        });
        else if(label.compare(Type20[35]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "CA " + FormatInt(unit_ptr->CommandAttribute);
        });
        else if(label.compare(Type20[36]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "U3A " + FormatFloat(unit_ptr->Unknown3A);
        });
        else if(label.compare(Type20[37]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "MC " + FormatInt(unit_ptr->MinimapColor);
        });
        else if(label.compare(Type20[38]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "LH " + FormatInt(unit_ptr->LanguageDLLHelp);
        });
        else if(label.compare(Type20[39]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "LT " + FormatInt(unit_ptr->LanguageDLLHotKeyText);
        });
        else if(label.compare(Type20[40]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "HK " + FormatInt(unit_ptr->HotKey);
        });
        else if(label.compare(Type20[41]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "US " + FormatInt(unit_ptr->Unselectable);
        });
        else if(label.compare(Type20[42]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "U6 " + FormatInt(unit_ptr->EnableAutoGather);
        });
        else if(label.compare(Type20[43]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "U7 " + FormatInt(unit_ptr->AutoGatherMode);
        });
        else if(label.compare(Type20[44]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "U8 " + FormatInt(unit_ptr->AutoGatherID);
        });
        else if(label.compare(Type20[45]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "SM " + FormatInt(unit_ptr->SelectionMask);
        });
        else if(label.compare(Type20[46]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "ST " + FormatInt(unit_ptr->SelectionShapeType);
        });
        else if(label.compare(Type20[47]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "SSh " + FormatInt(unit_ptr->SelectionShape);
        });
        else if(label.compare(Type20[48]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "A " + FormatInt(unit_ptr->Attribute);
        });
        else if(label.compare(Type20[49]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "Ci " + FormatInt(unit_ptr->Civilization);
        });
        else if(label.compare(Type20[50]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "No " + FormatInt(unit_ptr->Nothing);
        });
        else if(label.compare(Type20[51]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "SE " + FormatInt(unit_ptr->SelectionEffect);
        });
        else if(label.compare(Type20[52]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "EC " + FormatInt(unit_ptr->EditorSelectionColour);
        });
        else if(label.compare(Type20[53]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "SS " + FormatInt(unit_ptr->SelectionShapeSize.x) + " "
                    + FormatInt(unit_ptr->SelectionShapeSize.y);
        });
        else if(label.compare(Type20[54]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "B2 " + FormatFloat(unit_ptr->SelectionShapeSize.z);
        });
        else if(label.compare(Type20[55]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "Ask Tapsa";
        });
        else if(label.compare(Type20[56]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "DC " + FormatInt(unit_ptr->DamageGraphics.size());
        });
        else if(label.compare(Type20[57]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "Ask Tapsa";
        });
        else if(label.compare(Type20[58]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "SSo " + FormatInt(unit_ptr->SelectionSound);
        });
        else if(label.compare(Type20[59]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "DS " + FormatInt(unit_ptr->DyingSound);
        });
        else if(label.compare(Type20[60]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "AtM " + FormatInt(unit_ptr->AttackMode);
        });
        else if(label.compare(Type20[61]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "EM " + FormatInt(unit_ptr->Unknown10);
        });
        else if(label.compare(Type20[62]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return wxString(unit_ptr->Name);
        });
        else if(label.compare(Type20[63]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return wxString(unit_ptr->Name2);
        });
        else if(label.compare(Type20[64]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "UL " + FormatInt(unit_ptr->Unitline);
        });
        else if(label.compare(Type20[65]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "MT " + FormatInt(unit_ptr->MinTechLevel);
        });
        else if(label.compare(Type20[66]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "I2 " + FormatInt(unit_ptr->ID2);
        });
        else if(label.compare(Type20[67]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "I3 " + FormatInt(unit_ptr->ID3);
        });
        else if(label.compare(Type20[68]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "S " + FormatFloat(unit_ptr->Speed);
        });

        else if(label.compare(Type30[0]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF30 "WG " + FormatInt(unit_ptr->DeadFish.WalkingGraphic.first) + " "
                    + FormatInt(unit_ptr->DeadFish.WalkingGraphic.second);
        });
        else if(label.compare(Type30[1]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF30 "RS " + FormatFloat(unit_ptr->DeadFish.RotationSpeed);
        });
        else if(label.compare(Type30[2]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF30 "U11 " + FormatInt(unit_ptr->DeadFish.Unknown11);
        });
        else if(label.compare(Type30[3]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF30 "TU " + FormatInt(unit_ptr->DeadFish.TrackingUnit);
        });
        else if(label.compare(Type30[4]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF30 "UU " + FormatInt(unit_ptr->DeadFish.TrackingUnitUsed);
        });
        else if(label.compare(Type30[5]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF30 "UD " + FormatFloat(unit_ptr->DeadFish.TrackingUnitDensity);
        });
        else if(label.compare(Type30[6]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF30 "U16 " + FormatInt(unit_ptr->DeadFish.Unknown16);
        });
        else if(label.compare(Type30[7]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF30 "a" + FormatFloat(unit_ptr->DeadFish.RotationAngles[0])
                    + " b" + FormatFloat(unit_ptr->DeadFish.RotationAngles[1])
                    + " c" + FormatFloat(unit_ptr->DeadFish.RotationAngles[2])
                    + " d" + FormatFloat(unit_ptr->DeadFish.RotationAngles[3])
                    + " e" + FormatFloat(unit_ptr->DeadFish.RotationAngles[4]);
        });

        else if(label.compare(Type40[0]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "SC " + FormatInt(unit_ptr->Bird.ActionWhenDiscoveredID);
        });
        else if(label.compare(Type40[1]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "SR " + FormatFloat(unit_ptr->Bird.SearchRadius);
        });
        else if(label.compare(Type40[2]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "WR " + FormatFloat(unit_ptr->Bird.WorkRate);
        });
        else if(label.compare(Type40[3]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "DS " + FormatInt(unit_ptr->Bird.DropSite.first) + " "
                    + FormatInt(unit_ptr->Bird.DropSite.second);
        });
        else if(label.compare(Type40[4]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "VM " + FormatInt(unit_ptr->Bird.TaskSwapID);
        });
        else if(label.compare(Type40[5]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "AS " + FormatInt(unit_ptr->Bird.AttackSound);
        });
        else if(label.compare(Type40[6]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "MS " + FormatInt(unit_ptr->Bird.MoveSound);
        });
        else if(label.compare(Type40[7]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "AM " + FormatInt(unit_ptr->Bird.AnimalMode);
        });
        else if(label.compare(Type40[8]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "CC " + FormatInt(unit_ptr->Bird.Commands.size());
        });
        else if(label.compare(Type40[9]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "Ask Tapsa";
        });

        if(label.compare(Type50[0]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "DA " + FormatInt(unit_ptr->Type50.DefaultArmor);
        });
        else if(label.compare(Type50[1]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "AtC " + FormatInt(unit_ptr->Type50.Attacks.size());
        });
        else if(label.compare(Type50[2]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            wxString name = "";
            for(size_t i = 0; i < unit_ptr->Type50.Attacks.size(); ++i)
            name += "c" + FormatInt(unit_ptr->Type50.Attacks[i].Class) + " ";
            return UF50 name;
        });
        else if(label.compare(Type50[3]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "ArC " + FormatInt(unit_ptr->Type50.Armours.size());
        });
        else if(label.compare(Type50[4]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            wxString name = "";
            for(size_t i = 0; i < unit_ptr->Type50.Armours.size(); ++i)
            name += "c" + FormatInt(unit_ptr->Type50.Armours[i].Class) + " ";
            return UF50 name;
        });
        else if(label.compare(Type50[5]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "TR " + FormatInt(unit_ptr->Type50.TerRestrictionForDmgMultiplying);
        });
        else if(label.compare(Type50[6]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "MaR " + FormatFloat(unit_ptr->Type50.MaxRange);
        });
        else if(label.compare(Type50[7]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "BR " + FormatFloat(unit_ptr->Type50.BlastWidth);
        });
        else if(label.compare(Type50[8]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "RT " + FormatFloat(unit_ptr->Type50.ReloadTime);
        });
        else if(label.compare(Type50[9]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "PU " + FormatInt(unit_ptr->Type50.ProjectileUnitID);
        });
        else if(label.compare(Type50[10]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "AP " + FormatInt(unit_ptr->Type50.AccuracyPercent);
        });
        else if(label.compare(Type50[11]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "TM " + FormatInt(unit_ptr->Type50.TowerMode);
        });
        else if(label.compare(Type50[12]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "D " + FormatInt(unit_ptr->Type50.FrameDelay);
        });
        else if(label.compare(Type50[13]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "x" + FormatFloat(unit_ptr->Type50.GraphicDisplacement[0])
                    + " y" + FormatFloat(unit_ptr->Type50.GraphicDisplacement[1])
                    + " z" + FormatFloat(unit_ptr->Type50.GraphicDisplacement[2]);
        });
        else if(label.compare(Type50[14]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "BL " + FormatInt(unit_ptr->Type50.BlastAttackLevel);
        });
        else if(label.compare(Type50[15]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "MiR " + FormatFloat(unit_ptr->Type50.MinRange);
        });
        else if(label.compare(Type50[16]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "AE " + FormatFloat(unit_ptr->Type50.AccuracyDispersion);
        });
        else if(label.compare(Type50[17]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "AG " + FormatInt(unit_ptr->Type50.AttackGraphic);
        });
        else if(label.compare(Type50[18]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "DM " + FormatInt(unit_ptr->Type50.DisplayedMeleeArmour);
        });
        else if(label.compare(Type50[19]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "DP " + FormatInt(unit_ptr->Type50.DisplayedAttack);
        });
        else if(label.compare(Type50[20]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "DR " + FormatFloat(unit_ptr->Type50.DisplayedRange);
        });
        else if(label.compare(Type50[21]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "DT " + FormatFloat(unit_ptr->Type50.DisplayedReloadTime);
        });

        else if(label.compare(Type60[0]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF60 "SM " + FormatInt(unit_ptr->Projectile.StretchMode);
        });
        else if(label.compare(Type60[1]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF60 "CM " + FormatInt(unit_ptr->Projectile.SmartMode);
        });
        else if(label.compare(Type60[2]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF60 "DA " + FormatInt(unit_ptr->Projectile.DropAnimationMode);
        });
        else if(label.compare(Type60[3]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF60 "PM " + FormatInt(unit_ptr->Projectile.PenetrationMode);
        });
        else if(label.compare(Type60[4]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF60 "U24 " + FormatInt(unit_ptr->Projectile.Unknown24);
        });
        else if(label.compare(Type60[5]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF60 "PA " + FormatFloat(unit_ptr->Projectile.ProjectileArc);
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
            return UF70 "U26 " + FormatFloat(unit_ptr->Creatable.Unknown26);
        });
        else if(label.compare(Type70[5]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "U27 " + FormatFloat(unit_ptr->Creatable.Unknown27);
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
            return UF80 "OT " + FormatInt(unit_ptr->Building.OldTerrainLikeID);
        });
        else if(label.compare(Type80[8]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "R " + FormatInt(unit_ptr->Building.ResearchID);
        });
        else if(label.compare(Type80[9]) == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "U33 " + FormatInt(unit_ptr->Building.Unknown33);
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
            return UF80 "US " + FormatInt(unit_ptr->Building.UnknownSound);
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
            return UF80 "U35 " + FormatFloat(unit_ptr->Building.Unknown35);
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
            unit_names.Add(FormatInt(loop)+" - "+name);
        }
        if(matcher > genie::UT_25)
        {
            if(matcher == genie::UT_Projectile)
            if(dataset->Civs[civ].Units[loop].Type != genie::UT_Projectile) continue;
            if(dataset->Civs[civ].Units[loop].Type < matcher) continue;
            if(dataset->Civs[civ].Units[loop].Type == genie::UT_AoeTrees) continue;
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
        unitSLP.datID = loadChosenGraphic(UnitIDs.front());
        unitSLP.slpID = -2;
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
                    if(GenieVersion >= genie::GV_AoKE3)
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
                        if(GenieVersion >= genie::GV_AoKA)
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
                    if(GenieVersion >= genie::GV_AoKE3)
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
                    if(GenieVersion >= genie::GV_AoKE3)
                    {
                        Units_TrainSound[1]->prepend(&UnitPointer->TrainSound.second);
                        Units_SelectionMask->prepend(&UnitPointer->SelectionMask);
                        if(GenieVersion >= genie::GV_AoKA)
                        {
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
                    }
                    Units_Enabled->prepend(&UnitPointer->Enabled);
                    Units_CommandID->prepend(&UnitPointer->CommandAttribute);
                    Units_Unknown3A->prepend(&UnitPointer->Unknown3A);
                    Units_MinimapColor->prepend(&UnitPointer->MinimapColor);
                    Units_LanguageDLLHelp->prepend(&UnitPointer->LanguageDLLHelp);
                    Units_LanguageDLLHotKeyText->prepend(&UnitPointer->LanguageDLLHotKeyText);
                    Units_HotKey->prepend(&UnitPointer->HotKey);
                    Units_Unselectable->prepend(&UnitPointer->Unselectable);
                    Units_Unknown6->prepend(&UnitPointer->EnableAutoGather);
                    Units_Unknown7->prepend(&UnitPointer->AutoGatherMode);
                    Units_Unknown8->prepend(&UnitPointer->AutoGatherID);
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
            string newLabel = " ( ", aste = "� ";
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
    if(GenieVersion >= genie::GV_AoK)   // AoK, TC, SWGB or CC
    {
        genie::UnitHeader * UnitHeadPointer;
        for(auto sel = selections; sel--> 0;)
        {
            UnitHeadPointer = &dataset->UnitHeaders[UnitIDs[sel]];

            Units_Exists->prepend(&UnitHeadPointer->Exists);
        }

        Units_UnitHeads_Name->SetLabel(" "+lexical_cast<string>(UnitIDs.front())+" - "+GetUnitName(UnitIDs.front(), 0));
    }
    else    // AoE or RoR
    {
        Units_UnitHeads_Name->SetLabel("");
    }
    ListUnitCommands();

    AGE_SLP::setbearing = 1u;
    for(auto &box: uiGroupUnit) box->update();
    Units_ID1->refill();
    Units_ID2->refill();
    Units_ID3->refill();
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
    bool has_base = baseSLP.initStats(unitGraphic, *dataset);
    if(has_base) unitSLP.angleset.insert(baseSLP.angles);
    if(dataset->Graphics[unitGraphic].Deltas.size())
    for(auto const &delta: dataset->Graphics[unitGraphic].Deltas)
    {
        AGE_SLP deltaSLP;
        if(delta.GraphicID < dataset->Graphics.size())
        {
            if(deltaSLP.initStats(delta.GraphicID, *dataset))
            {
                unitSLP.angleset.insert(deltaSLP.angles);
            }
            else continue;
        }
        else if(has_base)
        {
            deltaSLP = baseSLP;
        }
        else continue;
        deltaSLP.xdelta = delta.DirectionX + offsetX;
        deltaSLP.ydelta = delta.DirectionY + offsetY;
        SetDisplayBearings(deltaSLP, delta);
        unitSLP.deltas.insert(make_pair(offsetY, deltaSLP));
    }
    else if(has_base)
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
    wxCommandEvent e;
    OnUnitSelect(e);
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

//  SubVectors

string AGE_Frame::GetUnitDamageGraphicName(int index)
{
    return lexical_cast<string>((short)dataset->Civs[UnitCivID].Units[UnitIDs.front()].DamageGraphics[index].DamagePercent)
    +" % - ID: "+lexical_cast<string>(dataset->Civs[UnitCivID].Units[UnitIDs.front()].DamageGraphics[index].GraphicID);
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
    return "Amount: "+lexical_cast<string>(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type50.Attacks[index].Amount)
    +" - Class "+lexical_cast<string>(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type50.Attacks[index].Class);
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
        for(size_t loop = 0; loop < dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type50.Attacks.size(); ++loop)
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
    if(!Units_ListV->GetSelectedCount()) return;

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
    if(!Units_Attacks_ListV->GetSelectedCount()) return;

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
    auto selections = Units_Attacks_ListV->GetSelectedCount();
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
    +" - Class "+lexical_cast<string>(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type50.Armours[index].Class);
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
        for(size_t loop = 0; loop < dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type50.Armours.size(); ++loop)
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
    if(!Units_ListV->GetSelectedCount()) return;

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
    if(!Units_Armors_ListV->GetSelectedCount()) return;

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
    auto selections = Units_Armors_ListV->GetSelectedCount();
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

//  AoE/TC/SWGB/CC Unit Commands

wxString AGE_Frame::GetUnitCommandName(int index)
{
    short CommandType = (GenieVersion >= genie::GV_AoK) ? dataset->UnitHeaders[UnitIDs.front()].Commands[index].Type : dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.Commands[index].Type;
    switch(CommandType)
    {
        case 1: return action_type_names[1];
        case 2: return action_type_names[2];
        case 3: return action_type_names[3];
        case 4: return action_type_names[4];
        case 5: return action_type_names[5];
        case 6: return action_type_names[6];
        case 7: return action_type_names[7];
        case 8: return action_type_names[8];
        case 10: return action_type_names[9];
        case 11: return action_type_names[10];
        case 12: return action_type_names[11];
        case 13: return action_type_names[12];
        case 14: return action_type_names[13];
        case 20: return action_type_names[14];
        case 21: return action_type_names[15];
        case 101: return action_type_names[16];
        case 102: return action_type_names[17];
        case 103: return action_type_names[18];
        case 104: return action_type_names[19];
        case 105: return action_type_names[20];
        case 106: return action_type_names[21];
        case 107: return action_type_names[22];
        case 108: return action_type_names[23];
        case 109: return action_type_names[24];
        case 110: return action_type_names[25];
        case 111: return action_type_names[26];
        case 120: return action_type_names[27];
        case 121: return action_type_names[28];
        case 122: return action_type_names[29];
        case 123: return action_type_names[30];
        case 124: return action_type_names[31];
        case 125: return action_type_names[32];
        case 130: return action_type_names[33];
        case 131: return action_type_names[34];
        case 132: return action_type_names[35];
        case 133: return action_type_names[36];
        case 134: return action_type_names[37];
        case 135: return action_type_names[38];
        case 136: return action_type_names[39];
        case 149: return action_type_names[40];
        case 150: return action_type_names[41];
        case 151: return action_type_names[42];
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

    Units_UnitCommands_ListV->Sweep();
    action_names.Clear();
    action_names.Add("-1 - None");

    if(GenieVersion >= genie::GV_AoK)   // AoK, TC, SWGB or CC
    {
        if(Units_ListV->GetSelectedCount())
        for(size_t loop = 0; loop < dataset->UnitHeaders[UnitIDs.front()].Commands.size(); ++loop)
        {
            wxString Name = FormatInt(loop)+" - "+GetUnitCommandName(loop);
            if(dataset->UnitHeaders[UnitIDs.front()].Commands[loop].ClassID != -1)
            Name += " class "+lexical_cast<string>(dataset->UnitHeaders[UnitIDs.front()].Commands[loop].ClassID);
            else if(dataset->UnitHeaders[UnitIDs.front()].Commands[loop].UnitID != -1)
            Name += " unit "+lexical_cast<string>(dataset->UnitHeaders[UnitIDs.front()].Commands[loop].UnitID);
            if(SearchMatches(" " + Name.Lower() + " "))
            {
                Units_UnitCommands_ListV->names.Add(Name);
                Units_UnitCommands_ListV->indexes.push_back(loop);
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
            Units_UnitCommands_Add->Enable(true);
            for(size_t loop = 0; loop < dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.Commands.size(); ++loop)
            {
                wxString Name = FormatInt(loop)+" - "+GetUnitCommandName(loop);
                if(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.Commands[loop].ClassID != -1)
                Name += " class "+lexical_cast<string>(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.Commands[loop].ClassID);
                else if(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.Commands[loop].UnitID != -1)
                Name += " unit "+lexical_cast<string>(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.Commands[loop].UnitID);
                if(SearchMatches(" " + Name.Lower() + " "))
                {
                    Units_UnitCommands_ListV->names.Add(Name);
                    Units_UnitCommands_ListV->indexes.push_back(loop);
                }
                action_names.Add(Name);
            }
        }
        else
        {
            Units_UnitCommands_Add->Enable(false);
        }
    }
    RefreshList(Units_UnitCommands_ListV, &CommandIDs);
    Units_ActionWhenDiscoveredID_ComboBox->Flash();

    wxCommandEvent e;
    OnUnitCommandSelect(e);
}

void AGE_Frame::OnUnitCommandSelect(wxCommandEvent &event)
{
    auto selections = Units_UnitCommands_ListV->GetSelectedCount();
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
    if(!Units_ListV->GetSelectedCount()) return;

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
    if(!Units_UnitCommands_ListV->GetSelectedCount()) return;

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
    auto selections = Units_UnitCommands_ListV->GetSelectedCount();
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
    if(!Units_UnitCommands_ListV->GetSelectedCount()) return;

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
    if(!Units_UnitCommands_ListV->GetSelectedCount()) return;

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
                if(copies.Dat.UnitCommandExists[civ] > 255) ++copy;
                continue;
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
    if(!Units_UnitCommands_ListV->GetSelectedCount()) return;

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
                if(copies.Dat.UnitCommandExists[civ] > 255) ++copy;
                continue;
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
        DLLValue = lexical_cast<int32_t>(static_cast<wxTextCtrl*>(event.GetEventObject())->GetValue());
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
    Units_Civs_List = new AGEComboBox(Tab_Units, &civ_names_only);
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
    Units_SpecialCopy_Civs->SetToolTip("Whether buttons of units operate on all civilizations or just on the selected one\nNote that adding, inserting and deleting units always affect all civilizations!");

    unit_filter_options.Add("Types 10, 15, 90, 20+");
    unit_filter_options.Add("Types 30+");
    unit_filter_options.Add("Types 40+");
    unit_filter_options.Add("Types 50+");
    unit_filter_options.Add("Type 60");
    unit_filter_options.Add("Types 70+");
    unit_filter_options.Add("Type 80");
    Units_FilterSelector->Flash();

    Units_DataArea = new wxBoxSizer(wxVERTICAL);
    Units_Top_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_TopGrid_Holder = new wxWrapSizer();
    Units_AutoCopy = new wxCheckBox(Tab_Units, wxID_ANY, "Automatically");
    Units_AutoCopy->SetToolTip("It is safer to copy automatically than manually.");
    Units_CopyTo = new wxButton(Tab_Units, wxID_ANY, "Copy", wxDefaultPosition, wxSize(40, -1));
    Units_CopyGraphics = new wxCheckBox(Tab_Units, wxID_ANY, "Including graphics");
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
    Units_Type_ComboBox = new AGEComboBox(Tab_Units, &unit_type_names, AGETextCtrl::LARGE, 0);
    Units_Class = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Tab_Units);
    Units_Class->SetToolTip("Determines many things and works in conjunction with other variables");
    Units_Class_ComboBox[0] = new ComboBox_Plus1(Tab_Units, Units_Class, &class_names);
    Units_Scroller = new wxScrolled<APanel>(Tab_Units, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxTAB_TRAVERSAL);
    Units_ScrollSpace = new wxBoxSizer(wxVERTICAL);
    Units_TypeArea_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_LangDLLArea_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Language Files");
    Units_GraphicsArea_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Graphics");
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
    Units_AB1_Grid = new wxGridSizer(4, 5, 5);
    Units_A1_Grid = new wxBoxSizer(wxHORIZONTAL);
    Units_A2_Grid = new wxBoxSizer(wxHORIZONTAL);
    Units_A3_Grid = new wxBoxSizer(wxHORIZONTAL);
    Units_A4_Grid = new wxBoxSizer(wxHORIZONTAL);
    Units_A5_Grid = new wxGridSizer(4, 0, 5);
    Units_A6_Grid = new wxBoxSizer(wxHORIZONTAL);
    Units_AM1_Grid = new wxGridSizer(5, 5, 5);
    wxBoxSizer *Units_DropSite_Holder = new wxBoxSizer(wxVERTICAL);
    Units_AS_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_AS1_Grid = new wxBoxSizer(wxHORIZONTAL);
    Units_LangRegular_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_LangHotKey_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_AttributesTracking_Grid = new wxBoxSizer(wxHORIZONTAL);
    Units_AttributesTrain1_Grid = new wxBoxSizer(wxHORIZONTAL);
    Units_SoundsArea_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Sounds (that only you hear)");
    Units_SoundsArea1_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_SoundsArea2_Grid = new wxBoxSizer(wxHORIZONTAL);
    Units_UnknownArea_Holder = new wxFlexGridSizer(2, 5, 5);
    Units_Type10plusUnknownArea_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Type 10+ Unknowns (All Units)");
    Units_Type30plusUnknownArea_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Type 30+ Unknowns (Dead/Fish)");
    Units_Type70plusUnknownArea_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Type 70+ Unknowns (Creatable)");
    Units_Type80plusUnknownArea_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Type 80+ Unknowns (Building)");
    Units_CommandsArea_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Actions (Shared by all civilizations since Age of Empires II)");

//  Invisible Holder Windows
//  Type 10+

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

//  Type 20+

    Units_Speed_Holder = new wxBoxSizer(wxVERTICAL);

//  Type 30+

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

//  Type 40+

    Units_ActionWhenDiscoveredID_Holder = new wxBoxSizer(wxVERTICAL);
    Units_SearchRadius_Holder = new wxBoxSizer(wxVERTICAL);
    Units_WorkRate_Holder = new wxBoxSizer(wxVERTICAL);
    Units_DropSite_Grid = new wxGridSizer(2, 0, 5);
    Units_TaskSwapID_Holder = new wxBoxSizer(wxVERTICAL);
    Units_AttackSound_Holder = new wxBoxSizer(wxVERTICAL);
    Units_MoveSound_Holder = new wxBoxSizer(wxVERTICAL);
    Units_AnimalMode_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_Exists_Holder = new wxBoxSizer(wxVERTICAL);

//  Type 50+

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

//  Type 60 only

    Units_StretchMode_Holder = new wxBoxSizer(wxVERTICAL);
    Units_SmartMode_Holder = new wxBoxSizer(wxVERTICAL);
    Units_DropAnimationMode_Holder = new wxBoxSizer(wxVERTICAL);
    Units_PenetrationMode_Holder = new wxBoxSizer(wxVERTICAL);
    Units_Unknown24_Holder = new wxBoxSizer(wxVERTICAL);
    Units_ProjectileArc_Holder = new wxBoxSizer(wxVERTICAL);

//  Type 70+

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

//  Data Container Names
//  Type 10+

    Units_ID1_Text = new SolidText(Tab_Units, "ID 1 ");
    Units_LanguageDLLName_Text = new SolidText(Units_Scroller, " Language File Name *");
    Units_LanguageDLLCreation_Text = new SolidText(Units_Scroller, " Language File Creation");
    Units_Class_Text = new SolidText(Tab_Units, "  Class * ");
    Units_StandingGraphic_Text = new SolidText(Units_Scroller, " Standing Graphics *");
    Units_DyingGraphic_Text = new SolidText(Units_Scroller, " Dying Graphics");
    Units_HitPoints_Text = new SolidText(Units_Scroller, " Hit Points *");
    Units_LineOfSight_Text = new SolidText(Units_Scroller, " Line Of Sight *");
    Units_GarrisonCapacity_Text = new SolidText(Units_Scroller, " Garrison Capacity *");
    Units_SizeRadius_Text = new SolidText(Units_Scroller, " Collision Size XY & Z *");
    Units_TrainSound_Text = new SolidText(Units_Scroller, " Train Sound ");
    Units_DeadUnitID_Text = new SolidText(Units_Scroller, " Dead Unit");
    Units_PlacementMode_Text = new SolidText(Units_Scroller, " Unknown Mode *");
    Units_IconID_Text = new SolidText(Units_Scroller, " Icon *");
    Units_Unknown1_Text = new SolidText(Units_Scroller, " Unknown 1 ");
    Units_PlacementSideTerrain_Text = new SolidText(Units_Scroller, " Placement Side Terrain *");
    Units_PlacementTerrain_Text = new SolidText(Units_Scroller, " Placement Terrain");
    Units_ClearanceSize_Text = new SolidText(Units_Scroller, " Clearance Size XY");
    Units_HillMode_Text = new SolidText(Units_Scroller, " Hill Mode *");
    Units_TerrainRestriction_Text = new SolidText(Units_Scroller, " Terrain Restriction ");
    Units_ResourceCapacity_Text = new SolidText(Units_Scroller, " Resource Capacity ");
    Units_ResourceDecay_Text = new SolidText(Units_Scroller, " Resource Decay *");
    Units_BlastDefenseLevel_Text = new SolidText(Units_Scroller, " Blast Defense Level *");
    Units_SubType_Text = new SolidText(Units_Scroller, " Sub Type *");
    Units_InteractionMode_Text = new SolidText(Units_Scroller, " Interaction Mode *");
    Units_MinimapMode_Text = new SolidText(Units_Scroller, " Minimap Mode *");
    Units_CommandID_Text = new SolidText(Units_Scroller, " Command ID *");
    Units_Unknown3A_Text = new SolidText(Units_Scroller, " Unknown 3A *");
    Units_MinimapColor_Text = new SolidText(Units_Scroller, " Minimap Color *");
    Units_LanguageDLLHelp_Text = new SolidText(Units_Scroller, " Language File Help *");
    Units_LanguageDLLConverter_Text[0] = new SolidText(Units_Scroller, " Help Converter *");
    Units_LanguageDLLConverter_Text[1] = new SolidText(Units_Scroller, " Hotkey Text Converter *");
    Units_LanguageDLLHotKeyText_Text = new SolidText(Units_Scroller, " Lang File Hotkey Text *");
    Units_HotKey_Text = new SolidText(Units_Scroller, " Hotkey *");
    Units_Unknown6_Text = new SolidText(Units_Scroller, " Auto Gather On *");
    Units_Unknown7_Text = new SolidText(Units_Scroller, " AG Mode *");
    Units_Unknown8_Text = new SolidText(Units_Scroller, " Auto Gather ID *");
    Units_SelectionMask_Text = new SolidText(Units_Scroller, " Selection Mask *");
    Units_SelectionShapeType_Text = new SolidText(Units_Scroller, " Selection Shape Type *");
    Units_SelectionShape_Text = new SolidText(Units_Scroller, " Selection Shape *");
    Units_Attribute_Text = new SolidText(Units_Scroller, " Unit Attribute *");
    Units_Civ_Text = new SolidText(Units_Scroller, " Civilization");
    Units_Nothing_Text = new SolidText(Units_Scroller, " Attribute Piece *");
    Units_SelectionEffect_Text = new SolidText(Units_Scroller, " Selection Effect *");
    Units_EditorSelectionColour_Text = new SolidText(Units_Scroller, " Editor Selection Color *");
    Units_SelectionRadius_Text = new SolidText(Units_Scroller, " Selection Shape Size XY & Z *");
    ResourceStorage_Type_Text = new SolidText(Units_Scroller, "Type", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(90, -1));
    ResourceStorage_Amount_Text = new SolidText(Units_Scroller, "Amount", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(90, -1));
    ResourceStorage_Enabled_Text = new SolidText(Units_Scroller, "Store Mode *", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(90, -1));
    Units_SelectionSound_Text = new SolidText(Units_Scroller, " Selection Sound ");
    Units_DyingSound_Text = new SolidText(Units_Scroller, " Dying Sound ");
    Units_AttackMode_Text = new SolidText(Units_Scroller, " Attack Mode? *");
    Units_Unknown10_Text = new SolidText(Units_Scroller, " Edible Meat? *");
    Units_Name_Text = new SolidText(Tab_Units, " Name ");
    Units_Name2_Text = new SolidText(Tab_Units, " Name 2 ");
    Units_Unitline_Text = new SolidText(Units_Scroller, " AI Unitline");
    Units_MinTechLevel_Text = new SolidText(Units_Scroller, " Min Tech Level");
    Units_ID2_Text = new SolidText(Tab_Units, "ID 2 ");
    Units_ID3_Text = new SolidText(Tab_Units, "ID 3 ");

//  Type 20+

    Units_Speed_Text = new SolidText(Units_Scroller, " Speed ");

//  Type 30+

    Units_WalkingGraphic_Text = new SolidText(Units_Scroller, " Walking and Running Graphics");
    Units_RotationSpeed_Text = new SolidText(Units_Scroller, " Rotation Speed *");
    Units_Unknown11_Text = new SolidText(Units_Scroller, " Unknown 11");
    Units_TrackingUnit_Text = new SolidText(Units_Scroller, " Tracking Unit ");
    Units_TrackingUnitUsed_Text = new SolidText(Units_Scroller, " Tracking Unit Mode *");
    Units_TrackingUnitDensity_Text = new SolidText(Units_Scroller, " Tracking Unit Density *");
    Units_Unknown16_Text = new SolidText(Units_Scroller, " Unknown 16");
    Units_RotationAngles_Label = " Rotations in Radians *";
    Units_RotationAngles_Text = new SolidText(Units_Scroller, Units_RotationAngles_Label);

//  Type 40+

    Units_SearchRadius_Text = new SolidText(Units_Scroller, " Search Radius ");
    Units_WorkRate_Text = new SolidText(Units_Scroller, " Work Rate ");
    Units_DropSite_Text = new SolidText(Units_Scroller, " Drop Site *");
    Units_TaskSwapID_Text = new SolidText(Units_Scroller, " Task Swap ID *");
    Units_AttackSound_Text = new SolidText(Units_Scroller, " Attack Sound");
    Units_MoveSound_Text = new SolidText(Units_Scroller, " Move Sound");
    Units_Exists_Text = new SolidText(Units_Scroller, " Exists");

//  Type 50+

    Units_DefaultArmor_Text = new SolidText(Units_Scroller, " Default Armor *");
    Units_TerRestrictionForDmgMultiply_Text = new SolidText(Units_Scroller, " Terrain Restriction *");
    Units_MaxRange_Text = new SolidText(Units_Scroller, " Max Range");
    Units_BlastWidth_Text = new SolidText(Units_Scroller, " Blast Width *");
    Units_ReloadTime1_Text = new SolidText(Units_Scroller, " Reload Time");
    Units_ProjectileUnitID_Text = new SolidText(Units_Scroller, " Projectile Unit");
    Units_AccuracyPercent_Text = new SolidText(Units_Scroller, " Accuracy Percent");
    Units_Delay_Text = new SolidText(Units_Scroller, " Frame Delay *");
    Units_GraphicDisplacement_Text = new SolidText(Units_Scroller, " Graphic Displacement XYZ *");
    Units_BlastAttackLevel_Text = new SolidText(Units_Scroller, " Blast Attack Level *");
    Units_MinRange_Text = new SolidText(Units_Scroller, " Min Range");
    Units_AccuracyDispersion_Text = new SolidText(Units_Scroller, " Attack Dispersion *");
    Units_AttackGraphic_Text = new SolidText(Units_Scroller, " Attack Graphic");
    Units_DisplayedMeleeArmour_Text = new SolidText(Units_Scroller, " Displayed Melee Armor");
    Units_DisplayedAttack_Text = new SolidText(Units_Scroller, " Displayed Attack");
    Units_DisplayedRange_Text = new SolidText(Units_Scroller, " Displayed Range");
    Units_ReloadTime2_Text = new SolidText(Units_Scroller, " Displayed Reload Time");

//  Type 60 only

    Units_StretchMode_Text = new SolidText(Units_Scroller, " Stretch Mode *");
    Units_SmartMode_Text = new SolidText(Units_Scroller, " Smart Mode *");
    Units_DropAnimationMode_Text = new SolidText(Units_Scroller, " Drop Animation Mode *");
    Units_PenetrationMode_Text = new SolidText(Units_Scroller, " Penetration Mode *");
    Units_Unknown24_Text = new SolidText(Units_Scroller, " Unknown 24 *");
    Units_ProjectileArc_Text = new SolidText(Units_Scroller, " Projectile Arc ");

//  Type 70+

    Units_CostType_Text = new SolidText(Units_Scroller, "Type", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(90, -1));
    Units_CostAmount_Text = new SolidText(Units_Scroller, "Amount", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(90, -1));
    Units_CostUsed_Text = new SolidText(Units_Scroller, "Is Paid", wxALIGN_RIGHT | wxST_NO_AUTORESIZE, wxSize(90, -1));
    Units_TrainTime_Text = new SolidText(Units_Scroller, " Train Time");
    Units_TrainLocationID_Text = new SolidText(Units_Scroller, " Train Location");
    Units_ButtonID_Text = new SolidText(Units_Scroller, " Train Button *");
    Units_Unknown26_Text = new SolidText(Units_Scroller, " Unknown 26 ");
    Units_Unknown27_Text = new SolidText(Units_Scroller, " Unknown 27 ");
    Units_UnknownType_Text = new SolidText(Units_Scroller, " Creatable Type *");
    Units_GarrisonGraphic_Text = new SolidText(Units_Scroller, " Garrison Graphic ");
    Units_MissileCount_Text = new SolidText(Units_Scroller, " Total Projectiles *");
    Units_MissileDuplicationCount_Text = new SolidText(Units_Scroller, " Max Total Projectiles *");
    Units_AttackMissileDuplicationSpawning_Text = new SolidText(Units_Scroller, " Projectile Spawning Area *");
    Units_AttackMissileDuplicationUnit_Text = new SolidText(Units_Scroller, " Secondary Projectile Unit *");
    Units_ChargingGraphic_Text = new SolidText(Units_Scroller, " Special Graphic *");
    Units_ChargingMode_Text = new SolidText(Units_Scroller, " Special Ability *");
    Units_DisplayedPierceArmour_Text = new SolidText(Units_Scroller, " Displayed Pierce Armor ");

//  Type 80

    Units_ConstructionGraphicID_Text = new SolidText(Units_Scroller, " Construction Graphic ");
    Units_SnowGraphicID_Text = new SolidText(Units_Scroller, " Snow Graphic ");
    Units_IconAngle_Text = new SolidText(Units_Scroller, " Angle *");
    Units_StackUnitID_Text = new SolidText(Units_Scroller, " Stack Unit *");
    Units_TerrainID_Text = new SolidText(Units_Scroller, " Foundation Terrain *");
    Units_OldTerrainLikeID_Text = new SolidText(Units_Scroller, " Old Road *");
    Units_ResearchID_Text = new SolidText(Units_Scroller, " Initiates Research *");
    Units_Unknown33_Text = new SolidText(Units_Scroller, " Unknown 33 *");
    Units_AnnexUnit_Text = new SolidText(Units_Scroller, " Annex Units");
    Units_AnnexUnitMisplacement_Text = new SolidText(Units_Scroller, " Annex Units Misplacement");
    Units_HeadUnit_Text = new SolidText(Units_Scroller, " Head Unit *");
    Units_TransformUnit_Text = new SolidText(Units_Scroller, " Transform Unit *");
    Units_UnknownSound_Text = new SolidText(Units_Scroller, " Unknown Sound *");
    Units_ConstructionSound_Text = new SolidText(Units_Scroller, " Construction Sound ");
    Units_GarrisonType_Text = new SolidText(Units_Scroller, " Garrison Type *");
    Units_GarrisonHealRate_Text = new SolidText(Units_Scroller, " Garrison Heal Rate *");
    Units_Unknown35_Text = new SolidText(Units_Scroller, " Unknown 35 *");
    Units_PileUnit_Text = new SolidText(Units_Scroller, " Pile Unit *");
    Units_LootSwitch_Text = new SolidText(Units_Scroller, " Looting Table *");

//  Data Containers

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
    Units_DamageGraphics_ListV = new ProperList(Units_Scroller, wxSize(140, 100));
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
    DamageGraphics_GraphicID_Text = new SolidText(Units_Scroller, " Graphic ");
    DamageGraphics_GraphicID = AGETextCtrl::init(CShort, &uiGroupUnitDmgGraphic, this, &popUp, Units_Scroller);
    DamageGraphics_GraphicID_ComboBox = new ComboBox_Plus1(Units_Scroller, DamageGraphics_GraphicID, &graphic_names);
    GraphicComboBoxList.push_back(DamageGraphics_GraphicID_ComboBox);
    DamageGraphics_DamagePercent_Holder = new wxBoxSizer(wxVERTICAL);
    DamageGraphics_DamagePercent_Text = new SolidText(Units_Scroller, " Damage Percent ");
    DamageGraphics_DamagePercent = AGETextCtrl::init(CByte, &uiGroupUnitDmgGraphic, this, &popUp, Units_Scroller);
    DamageGraphics_ApplyMode_Holder = new wxBoxSizer(wxVERTICAL);
    DamageGraphics_ApplyMode_Text = new SolidText(Units_Scroller, " Old Unknown Mode *");
    DamageGraphics_ApplyMode = AGETextCtrl::init(CByte, &uiGroupUnitDmgGraphic, this, &popUp, Units_Scroller);
    DamageGraphics_ApplyMode->SetToolTip("Replaced in memory by the 2nd Unknown Mode");
    DamageGraphics_Unknown2_Holder = new wxBoxSizer(wxVERTICAL);
    DamageGraphics_Unknown2_Text = new SolidText(Units_Scroller, " Unknown Mode *");
    DamageGraphics_Unknown2 = AGETextCtrl::init(CByte, &uiGroupUnitDmgGraphic, this, &popUp, Units_Scroller);
    DamageGraphics_Unknown2->SetToolTip("Old false notes. This is not apply mode.\n0 Adds graphics on top (flames on buildings)\n1 Adds graphics on top randomly\n2 Replaces original graphics (damaged walls)");

    Units_IconID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
    Units_IconID->SetToolTip("Download Turtle Pack from AoKH to add more than 127 icons.");
    Units_IconID_SLP = new APanel(Units_Scroller, wxSize(55, 50));
    Units_IconAngle = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller, AGETextCtrl::SMALL);
    Units_IconAngle->SetToolTip("Tech attribute 17 changes this\n0 Default\n1+ Use icon from 2nd age etc\nIn AoE 1 can be used to set the unit\nhave icon graphics of later ages straight in stone age");
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
    Units_Attacks_Insert = new wxButton(Units_Scroller, wxID_ANY, "Insert New", wxDefaultPosition, wxSize(10, -1));
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
    Units_Armors_ListV = new ProperList(Units_Scroller, wxSize(140, 100));
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
    Armors_Amount_Text = new SolidText(Units_Scroller, " Amount");
    Armors_Amount = AGETextCtrl::init(CShort, NULL, this, &popUp, Units_Scroller);
    Armors_Class_Holder = new wxBoxSizer(wxVERTICAL);
    Armors_Class_Text = new SolidText(Units_Scroller, " Type *");
    Armors_Class = AGETextCtrl::init(CShort, NULL, this, &popUp, Units_Scroller);
    Armors_Class->SetToolTip("Attack class from which this unit can take damage\nYou can make your own classes");
    Attacks_Class_ComboBox[1] = new ComboBox_Plus1(Units_Scroller, Armors_Class, &armor_names);

    Units_DefaultArmor = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_DefaultArmor->SetToolTip("This armor is used for all attack types that do not have corresponding armor type\nCan be negative only in The Conquerors and later games");
    Units_TerRestrictionForDmgMultiply = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_TerRestrictionForDmgMultiply->SetToolTip("Receive damage based on which terrain this unit stands on\nTech attribute 18 changes this\nThe damage received by this unit is\nmultiplied by the accessible values on\nthe specified terrain restriction");
    Units_TerRestrictionForDmgMultiply_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_TerRestrictionForDmgMultiply, &restriction_names);
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
    Units_DeathMode->SetToolTip("After 1st dying graphic:\n0 transform into dead unit\n1 show 2nd dying graphic");
    Units_DeathMode_CheckBox = new CheckBox_2State(Units_Scroller, "Death Mode *", Units_DeathMode);
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
    Units_VisibleInFog_Text = new SolidText(Units_Scroller, " Fog Visibility *");
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
    Units_Unknown7->SetToolTip("Create doppleganger on death.\n0 none\n1 normal\n2 when dying");
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
    Units_Civ_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_Civ, &civ_names);
    CivComboBoxList.push_back(Units_Civ_ComboBox);
    Units_Nothing = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_Nothing->SetToolTip("This is actually leftover from attribute+civ variable\nProbably useless");
    Units_DeadUnitID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_DeadUnitID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_DeadUnitID, &unit_names);
    UnitComboBoxList.push_back(Units_DeadUnitID_ComboBox);
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
    Units_TerrainRestriction_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_TerrainRestriction, &restriction_names);
    TerrainRestrictionComboBoxList.push_back(Units_TerrainRestriction_ComboBox);
    Units_TerrainID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_TerrainID->SetToolTip("Terrain produced under a building when completed");
    Units_TerrainID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_TerrainID, &terrain_names);
    TerrainComboBoxList.push_back(Units_TerrainID_ComboBox);
    Units_OldTerrainLikeID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_OldTerrainLikeID->SetToolTip("ES forgot to remove this before AoE was released.\nThis points to removed data block\nthat was like terrain borders.\nYou could build roads back in 1996.");
    Units_ResearchID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_ResearchID->SetToolTip("Causes that research to be researched when the building is created");
    Units_ResearchID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_ResearchID, &research_names);
    ResearchComboBoxList.push_back(Units_ResearchID_ComboBox);
    Units_ActionWhenDiscoveredID_Text = new SolidText(Units_Scroller, " Action When Discovered *");
    Units_ActionWhenDiscoveredID = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_ActionWhenDiscoveredID->SetToolTip("When this unit is met by some player unit\nthe unit action ID specified here will be executed.\nTo get the unit auto-converted to enemy,\nuse unit command 107, which sheep and monument have\nAll somehow auto-convertible units have this set to 0\nMost other units have -1");
    Units_ActionWhenDiscoveredID_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_ActionWhenDiscoveredID, &action_names);
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Units_DropSite[loop] = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
        Units_DropSite[loop]->SetToolTip("Giving a villager's drop site to a cart-like unit\ncan allow you to have mobile resource-gatherers,\nsimilar to those in Age of Mythology.");
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
    Units_TrackingUnit_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_TrackingUnit, &unit_names);
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
        ResourceStorage_Enabled[loop] = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
        ResourceStorage_Enabled[loop]->SetToolTip("0 Decayable resource\n1 Stored after death also\n2 Resets on dying, enables instantly\n4 Resets on dying, enables on completion\nUP: 8 Stored on completion and stays after death");
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
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Units_TrainSound[loop] = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
        Units_TrainSound_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, Units_TrainSound[loop], &sound_names);
        SoundComboBoxList.push_back(Units_TrainSound_ComboBox[loop]);
    }
    Units_AttackSound = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_AttackSound_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_AttackSound, &sound_names);
    SoundComboBoxList.push_back(Units_AttackSound_ComboBox);
    Units_MoveSound = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_MoveSound_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_MoveSound, &sound_names);
    SoundComboBoxList.push_back(Units_MoveSound_ComboBox);
    Units_ConstructionSound = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_ConstructionSound_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_ConstructionSound, &sound_names);
    SoundComboBoxList.push_back(Units_ConstructionSound_ComboBox);
    Units_UnknownSound = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_UnknownSound->SetToolTip("Possibly related to transforming");
    Units_UnknownSound_ComboBox = new ComboBox_Plus1(Units_Scroller, Units_UnknownSound, &sound_names);
    SoundComboBoxList.push_back(Units_UnknownSound_ComboBox);

    Units_Unknown1 = AGETextCtrl::init(CShort, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_Unknown3A = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_Unknown3A->SetToolTip("Seems to be 1 on more or less living things\nProbably the old population counter");

    Units_Unknown11 = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_Unknown16 = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);

    Units_Unknown26 = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_Unknown27 = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);

    Units_Unknown33 = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_Unknown33->SetToolTip("Seems to be obsolete");
    Units_Unknown35 = AGETextCtrl::init(CFloat, &uiGroupUnit, this, &popUp, Units_Scroller);
    Units_Unknown35->SetToolTip("Seems to be obsolete\nWas probably related to garrisoning");

    Units_CommandHolder_Lists = new wxBoxSizer(wxVERTICAL);
    Units_UnitHeads_Name = new SolidText(Units_Scroller, "Unit Header");
    Units_UnitCommands_Search = new wxTextCtrl(Units_Scroller, wxID_ANY);
    Units_UnitCommands_Search_R = new wxTextCtrl(Units_Scroller, wxID_ANY);
    Units_UnitCommands_ListV = new ProperList(Units_Scroller, wxSize(140, 190));
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
    Unit_Command_Known1 = new wxBoxSizer(wxHORIZONTAL);
    Unit_Command_Known2 = new wxGridSizer(3, 5, 5);
    Unit_Command_Known3 = new wxBoxSizer(wxHORIZONTAL);
    Unit_Command_Known4 = new wxGridSizer(3, 5, 5);
    Unit_Command_Unknowns = new wxGridSizer(4, 5, 5);
    Units_Exists = AGETextCtrl::init(CByte, &uiGroupUnit, this, &popUp, Units_Scroller);
    wxArrayString action_choices;
    action_choices.Add("None");
    action_choices.Add("Tool");
    action_choices.Add("Proceed");
    action_choices.Add("Action");
    action_choices.Add("Carry");
    slp_unit_actions = new wxRadioBox(Units_Scroller, wxID_ANY, "SLP view", wxDefaultPosition, wxDefaultSize, action_choices, 0, wxVERTICAL);

    UnitCommands_One_Holder = new wxBoxSizer(wxVERTICAL);
    UnitCommands_One_Text = new SolidText(Units_Scroller, " Enabled ");
    UnitCommands_One = AGETextCtrl::init(CShort, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
    UnitCommands_ID_Holder = new wxBoxSizer(wxVERTICAL);
    UnitCommands_ID_Text = new SolidText(Units_Scroller, " ID ");
    UnitCommands_ID = AGETextCtrl::init(CShort, 0, this, &popUp, Units_Scroller);
    UnitCommands_Type_Holder = new wxBoxSizer(wxVERTICAL);
    UnitCommands_Type_Text = new SolidText(Units_Scroller, " Action Type");
    UnitCommands_Type = AGETextCtrl::init(CShort, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
    UnitCommands_Type_ComboBox = new AGEComboBox(Units_Scroller, &action_type_names, AGETextCtrl::GIANT, 0);
    UnitCommands_ClassID_Holder = new wxBoxSizer(wxVERTICAL);
    UnitCommands_ClassID_Text = new SolidText(Units_Scroller, " Class");
    UnitCommands_ClassID = AGETextCtrl::init(CShort, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
    Units_Class_ComboBox[1] = new ComboBox_Plus1(Units_Scroller, UnitCommands_ClassID, &class_names);
    UnitCommands_UnitID_Holder = new wxBoxSizer(wxVERTICAL);
    UnitCommands_UnitID_Text = new SolidText(Units_Scroller, " Unit");
    UnitCommands_UnitID = AGETextCtrl::init(CShort, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
    UnitCommands_UnitID_ComboBox = new ComboBox_Plus1(Units_Scroller, UnitCommands_UnitID, &unit_names);
    UnitComboBoxList.push_back(UnitCommands_UnitID_ComboBox);
    UnitCommands_TerrainID_Holder = new wxBoxSizer(wxVERTICAL);
    UnitCommands_TerrainID_Text = new SolidText(Units_Scroller, " Terrain");
    UnitCommands_TerrainID = AGETextCtrl::init(CShort, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
    UnitCommands_TerrainID_ComboBox = new ComboBox_Plus1(Units_Scroller, UnitCommands_TerrainID, &terrain_names);
    TerrainComboBoxList.push_back(UnitCommands_TerrainID_ComboBox);
    UnitCommands_ResourceIn_Holder = new wxBoxSizer(wxVERTICAL);
    UnitCommands_ResourceIn_Text = new SolidText(Units_Scroller, " Resource In *");
    UnitCommands_ResourceIn = AGETextCtrl::init(CShort, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
    UnitCommands_ResourceIn->SetToolTip("Carry resource");
    UnitCommands_ResourceIn_ComboBox = new ComboBox_Plus1(Units_Scroller, UnitCommands_ResourceIn, &resource_names);
    ResourceComboBoxList.push_back(UnitCommands_ResourceIn_ComboBox);
    UnitCommands_ProductivityResource_Holder = new wxBoxSizer(wxVERTICAL);
    UnitCommands_ProductivityResource_Text = new SolidText(Units_Scroller, " Productivity Resource *");
    UnitCommands_ProductivityResource = AGETextCtrl::init(CShort, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
    UnitCommands_ProductivityResource->SetToolTip("Resource that multiplies the amount you can gather");
    UnitCommands_ProductivityResource_ComboBox = new ComboBox_Plus1(Units_Scroller, UnitCommands_ProductivityResource, &resource_names);
    ResourceComboBoxList.push_back(UnitCommands_ProductivityResource_ComboBox);
    UnitCommands_ResourceOut_Holder = new wxBoxSizer(wxVERTICAL);
    UnitCommands_ResourceOut_Text = new SolidText(Units_Scroller, " Resource Out *");
    UnitCommands_ResourceOut = AGETextCtrl::init(CShort, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
    UnitCommands_ResourceOut->SetToolTip("Drop resource");
    UnitCommands_ResourceOut_ComboBox = new ComboBox_Plus1(Units_Scroller, UnitCommands_ResourceOut, &resource_names);
    ResourceComboBoxList.push_back(UnitCommands_ResourceOut_ComboBox);
    UnitCommands_Resource_Holder = new wxBoxSizer(wxVERTICAL);
    UnitCommands_Resource_Text = new SolidText(Units_Scroller, " Resource");
    UnitCommands_Resource = AGETextCtrl::init(CShort, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
    UnitCommands_Resource_ComboBox = new ComboBox_Plus1(Units_Scroller, UnitCommands_Resource, &resource_names);
    ResourceComboBoxList.push_back(UnitCommands_Resource_ComboBox);
    UnitCommands_WorkRateMultiplier_Holder = new wxBoxSizer(wxVERTICAL);
    UnitCommands_WorkRateMultiplier_Text = new SolidText(Units_Scroller, " Quantity");
    UnitCommands_WorkRateMultiplier = AGETextCtrl::init(CFloat, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
    UnitCommands_ExecutionRadius_Holder = new wxBoxSizer(wxVERTICAL);
    UnitCommands_ExecutionRadius_Text = new SolidText(Units_Scroller, " Execution Radius");
    UnitCommands_ExecutionRadius = AGETextCtrl::init(CFloat, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
    UnitCommands_ExtraRange_Holder = new wxBoxSizer(wxVERTICAL);
    UnitCommands_ExtraRange_Text = new SolidText(Units_Scroller, " Extra Range");
    UnitCommands_ExtraRange = AGETextCtrl::init(CFloat, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
    for(size_t loop = 0; loop < UnitCommands_Graphics.size(); ++loop)
    {
        UnitCommands_Graphics_Holder[loop] = new wxBoxSizer(wxVERTICAL);
        UnitCommands_Graphics[loop] = AGETextCtrl::init(CShort, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
    }
    for(size_t loop = 0; loop < 4; ++loop)
    {
        UnitCommands_Graphics_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, UnitCommands_Graphics[loop], &graphic_names);
        GraphicComboBoxList.push_back(UnitCommands_Graphics_ComboBox[loop]);
    }
    for(size_t loop = 4; loop < 6; ++loop)
    {
        UnitCommands_Graphics_ComboBox[loop] = new ComboBox_Plus1(Units_Scroller, UnitCommands_Graphics[loop], &sound_names);
        SoundComboBoxList.push_back(UnitCommands_Graphics_ComboBox[loop]);
    }
    UnitCommands_Graphics_Text[0] = new SolidText(Units_Scroller, " Tool Graphic *");
    UnitCommands_Graphics[0]->SetToolTip("Used when walking with a tool, but carrying no resources");
    UnitCommands_Graphics_Text[1] = new SolidText(Units_Scroller, " Proceeding Graphic *");
    UnitCommands_Graphics[1]->SetToolTip("Used when proceeding to gather a resource or attack");
    UnitCommands_Graphics_Text[2] = new SolidText(Units_Scroller, " Action Graphic *");
    UnitCommands_Graphics[2]->SetToolTip("Used when actually gathering a resource or attacking/converting");
    UnitCommands_Graphics_Text[3] = new SolidText(Units_Scroller, " Carrying Graphic *");
    UnitCommands_Graphics[3]->SetToolTip("Used when carrying a resource");
    UnitCommands_Graphics_Text[4] = new SolidText(Units_Scroller, " Execution Sound *");
    UnitCommands_Graphics[4]->SetToolTip("Example: Plays when lumberjack starts chopping wood");
    UnitCommands_Graphics_Text[5] = new SolidText(Units_Scroller, " Resource Deposit Sound *");
    UnitCommands_Graphics[5]->SetToolTip("Example: Plays when lumberjack drops his wood into TC");
    UnitCommands_Unknown1_Holder = new wxBoxSizer(wxVERTICAL);
    UnitCommands_Unknown1_Text = new SolidText(Units_Scroller, " Unknown 1");
    UnitCommands_Unknown1 = AGETextCtrl::init(CByte, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
    UnitCommands_Unknown4_Holder = new wxBoxSizer(wxVERTICAL);
    UnitCommands_Unknown4_Text = new SolidText(Units_Scroller, " Unknown 4");
    UnitCommands_Unknown4 = AGETextCtrl::init(CByte, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
    UnitCommands_Unknown5_Holder = new wxBoxSizer(wxVERTICAL);
    UnitCommands_Unknown5_Text = new SolidText(Units_Scroller, " Scaring Radius");
    UnitCommands_Unknown5 = AGETextCtrl::init(CFloat, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
    UnitCommands_SelectionEnabler_Holder = new wxBoxSizer(wxVERTICAL);
    UnitCommands_SelectionEnabler_Text = new SolidText(Units_Scroller, " Selection Enabler *");
    UnitCommands_SelectionEnabler = AGETextCtrl::init(CByte, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
    UnitCommands_SelectionEnabler->SetToolTip("1 Allows units to select their targets\n2 ?");
    UnitCommands_Unknown7_Holder = new wxBoxSizer(wxVERTICAL);
    UnitCommands_Unknown7_Text = new SolidText(Units_Scroller, " Unknown 7");
    UnitCommands_Unknown7 = AGETextCtrl::init(CByte, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
    UnitCommands_Unknown8_Holder = new wxBoxSizer(wxVERTICAL);
    UnitCommands_Unknown8_Text = new SolidText(Units_Scroller, " Plunder Source *");
    UnitCommands_Unknown8 = AGETextCtrl::init(CShort, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
    UnitCommands_Unknown8->SetToolTip("0 Plunder from resource\n1 Plunder from players\n2 Raider thing?");
    UnitCommands_Unknown9_Holder = new wxBoxSizer(wxVERTICAL);
    UnitCommands_Unknown9_Text = new SolidText(Units_Scroller, " Unknown 9");
    UnitCommands_Unknown9 = AGETextCtrl::init(CShort, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
    UnitCommands_SelectionMode_Holder = new wxBoxSizer(wxVERTICAL);
    UnitCommands_SelectionMode_Text = new SolidText(Units_Scroller, " Selection Mode *");
    UnitCommands_SelectionMode = AGETextCtrl::init(CByte, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
    UnitCommands_SelectionMode->SetToolTip("Determines what you can select as targets\n0, 7+ All objects\n1 Your objects only\n2 Neutral and enemy objects only\n3 Gaia only\n4 Gaia, your and ally objects only\n5 Gaia, neutral and enemy objects only\n6 All but your objects");
    UnitCommands_RightClickMode_Holder = new wxBoxSizer(wxVERTICAL);
    UnitCommands_RightClickMode_Text = new SolidText(Units_Scroller, " Right Click Mode *");
    UnitCommands_RightClickMode = AGETextCtrl::init(CByte, &uiGroupUnitCommand, this, &popUp, Units_Scroller);
    UnitCommands_RightClickMode->SetToolTip("0 - Right-click target can be any object as defined by the Selection Mode.\n1 - Only the specified unit/class can be targeted using right-click.");
    UnitCommands_Unknown12_Holder = new wxBoxSizer(wxVERTICAL);
    UnitCommands_Unknown12_Text = new SolidText(Units_Scroller, " Unknown 12");
    UnitCommands_Unknown12 = AGETextCtrl::init(CByte, &uiGroupUnitCommand, this, &popUp, Units_Scroller);

//  UnitControls actual interface

    unit_type_names.Add("No Type/Invalid Type");
    unit_type_names.Add("10 - Eye Candy");
    unit_type_names.Add("15 - Tree (AoK)");
    unit_type_names.Add("20 - Flag");
    unit_type_names.Add("25 - Doppleganger");
    unit_type_names.Add("30 - Dead/Fish");
    unit_type_names.Add("40 - Bird");
    unit_type_names.Add("50 - Unknown");
    unit_type_names.Add("60 - Projectile");
    unit_type_names.Add("70 - Living");
    unit_type_names.Add("80 - Building");
    unit_type_names.Add("90 - Tree (AoE)");
    Units_Type_ComboBox->Flash();

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
    Type20.Add("EnableAutoGather");
    Type20.Add("AutoGatherMode");
    Type20.Add("AutoGatherID");
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

//  Type 10+

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

//  Type 20+

    Units_Speed_Holder->Add(Units_Speed_Text);

//  Type 30+

    Units_RotationSpeed_Holder->Add(Units_RotationSpeed_Text);
    Units_Unknown11_Holder->Add(Units_Unknown11_Text);
    Units_TrackingUnit_Holder->Add(Units_TrackingUnit_Text);
    Units_TrackingUnitUsed_Holder->Add(Units_TrackingUnitUsed_Text);
    Units_TrackingUnitDensity_Holder->Add(Units_TrackingUnitDensity_Text);
    Units_Unknown16_Holder->Add(Units_Unknown16_Text);
    Units_RotationAngles_Holder->Add(Units_RotationAngles_Text);

//  Type 40+

    Units_SearchRadius_Holder->Add(Units_SearchRadius_Text);
    Units_WorkRate_Holder->Add(Units_WorkRate_Text);
    Units_DropSite_Holder->Add(Units_DropSite_Text);
    Units_TaskSwapID_Holder->Add(Units_TaskSwapID_Text);
    Units_AttackSound_Holder->Add(Units_AttackSound_Text);
    Units_MoveSound_Holder->Add(Units_MoveSound_Text);
    Units_Exists_Holder->Add(Units_Exists_Text);

//  Type 50+

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

//  Type 60 only

    Units_StretchMode_Holder->Add(Units_StretchMode_Text);
    Units_SmartMode_Holder->Add(Units_SmartMode_Text);
    Units_DropAnimationMode_Holder->Add(Units_DropAnimationMode_Text);
    Units_PenetrationMode_Holder->Add(Units_PenetrationMode_Text);
    Units_Unknown24_Holder->Add(Units_Unknown24_Text);
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
    Units_Unknown26_Holder->Add(Units_Unknown26_Text);
    Units_Unknown27_Holder->Add(Units_Unknown27_Text);
    Units_UnknownType_Holder->Add(Units_UnknownType_Text);
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

//  Type 10+

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
    Units_PlacementSideTerrain_Holder->Add(Units_PlacementSideTerrainGrid_Holder);
    for(size_t loop = 0; loop < 2; ++loop)
    Units_PlacementTerrainGrid_Holder->Add(Units_PlacementTerrain[loop], 0, wxEXPAND);
    for(size_t loop = 0; loop < 2; ++loop)
    Units_PlacementTerrainGrid_Holder->Add(Units_PlacementTerrain_ComboBox[loop]);
    Units_PlacementTerrain_Holder->Add(Units_PlacementTerrainGrid_Holder);
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

//  Type 20+

    Units_Speed_Holder->Add(Units_Speed, 0, wxEXPAND);

//  Type 30+

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

//  Type 40+

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

//  Type 50+

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

//  Type 60 only

    Units_StretchMode_Holder->Add(Units_StretchMode, 0, wxEXPAND);
    Units_SmartMode_Holder->Add(Units_SmartMode, 0, wxEXPAND);
    Units_DropAnimationMode_Holder->Add(Units_DropAnimationMode, 0, wxEXPAND);
    Units_PenetrationMode_Holder->Add(Units_PenetrationMode, 0, wxEXPAND);
    Units_Unknown24_Holder->Add(Units_Unknown24, 0, wxEXPAND);
    Units_ProjectileArc_Holder->Add(Units_ProjectileArc, 0, wxEXPAND);

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

//  Type 80

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
    Units_Attacks_Holder_Data->Add(Units_DisplayedAttack_Holder);
    Units_Attacks_Holder_Data->Add(Units_Delay_Holder);
    Units_Attacks_Holder_Data->Add(Units_AccuracyPercent_Holder);
    Units_Attacks_Holder_Data->Add(Units_AccuracyDispersion_Holder);
    Units_Attacks_Holder_Data->Add(Units_ReloadTime1_Holder);
    Units_Attacks_Holder_Data->Add(Units_ReloadTime2_Holder);
    Units_Attacks_Holder_Data->Add(Units_BlastWidth_Holder);
    Units_Attacks_Holder_Data->Add(Units_BlastAttackLevel_Holder);

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

    Units_P1->Add(Units_ProjectileUnitID_Holder, 0, wxRIGHT, 5);
    Units_P1->Add(Units_AttackMissileDuplicationUnit_Holder, 0, wxRIGHT, 5);
    Units_P1->Add(Units_MissileCount_Holder, 0, wxRIGHT, 5);
    Units_P1->Add(Units_MissileDuplicationCount_Holder);
    Units_P2->Add(Units_AttackMissileDuplicationSpawning_Holder, 0, wxRIGHT, 5);
    Units_P2->Add(Units_GraphicDisplacement_Holder);

    Units_P3->Add(Units_StretchMode_Holder, 0, wxRIGHT, 5);
    Units_P3->Add(Units_SmartMode_Holder, 0, wxRIGHT, 5);
    Units_P3->Add(Units_DropAnimationMode_Holder, 0, wxRIGHT, 5);
    Units_P3->Add(Units_PenetrationMode_Holder, 0, wxRIGHT, 5);
    Units_P3->Add(Units_Unknown24_Holder);
    Units_ProjectileArea_Holder->Add(Units_P1, 0, wxBOTTOM, 5);
    Units_ProjectileArea_Holder->Add(Units_P2, 0, wxBOTTOM, 5);
    Units_ProjectileArea_Holder->Add(Units_P3, 0, wxBOTTOM, 5);
    Units_ProjectileArea_Holder->Add(Units_ProjectileArc_Holder, 0, wxBOTTOM, 5);

    Units_AB1_Grid->Add(Units_Enabled_Holder);
    Units_AB1_Grid->Add(Units_Disabled_Holder);
    Units_AB1_Grid->Add(Units_DeathMode_Holder);
    Units_AB1_Grid->Add(Units_HideInEditor_Holder);
    Units_AB1_Grid->Add(Units_AirMode_Holder);
    Units_AB1_Grid->Add(Units_FlyMode_Holder);
    Units_AB1_Grid->Add(Units_AnimalMode_Holder);
    Units_AB1_Grid->Add(Units_TowerMode_Holder);
    Units_AB1_Grid->Add(Units_AdjacentMode_Holder);
    Units_AB1_Grid->Add(Units_Unknown31b_Holder);
    Units_AB1_Grid->Add(Units_HeroMode_Holder);

    Units_AM1_Grid->Add(Units_PlacementMode_Holder);
    Units_AM1_Grid->Add(Units_HillMode_Holder);
    Units_AM1_Grid->Add(Units_VisibleInFog_Holder);
    Units_AM1_Grid->Add(Units_SubType_Holder);
    Units_AM1_Grid->Add(Units_InteractionMode_Holder);
    Units_AM1_Grid->Add(Units_MinimapMode_Holder);
    Units_AM1_Grid->Add(Units_MinimapColor_Holder);
    Units_AM1_Grid->Add(Units_Unknown6_Holder);
    Units_AM1_Grid->Add(Units_Unknown7_Holder);
    Units_AM1_Grid->Add(Units_Unknown8_Holder);
    Units_AM1_Grid->Add(Units_AttackMode_Holder);
    Units_AM1_Grid->Add(Units_Unknown10_Holder);
    Units_AM1_Grid->Add(Units_TaskSwapID_Holder);
    Units_AM1_Grid->Add(Units_UnknownType_Holder);
    Units_AM1_Grid->Add(Units_ChargingMode_Holder);

    Units_A2_Grid->Add(Units_Attribute_Holder);
    Units_DropSite_Holder->Add(Units_DropSite_Grid);
    Units_AS_Holder->Add(Units_SizeRadius_Holder, 0, wxRIGHT, 5);
    Units_AS_Holder->Add(Units_ClearanceSize_Holder);
    Units_AS1_Grid->Add(Units_Unselectable_Holder, 0, wxRIGHT, 5);
    Units_AS1_Grid->Add(Units_SelectionMask_Holder, 0, wxRIGHT, 5);
    Units_AS1_Grid->Add(Units_SelectionShapeType_Holder, 0, wxRIGHT, 5);
    Units_AS1_Grid->Add(Units_SelectionShape_Holder, 0, wxRIGHT, 5);
    Units_AS1_Grid->Add(Units_SelectionEffect_Holder);
    Units_ResourceStorageHeader_Holder->Add(Units_ResourceStorage_Texts);
    for(auto &sizer: Units_ResourceStorage_Holder)
    Units_ResourceStorageHeader_Holder->Add(sizer, 0, wxLEFT, 5);
    Units_A2_Grid->Add(Units_Civ_Holder, 0, wxLEFT, 5);
    Units_A2_Grid->Add(Units_Nothing_Holder, 0, wxLEFT, 5);
    Units_A1_Grid->Add(Units_DeadUnitID_Holder);
    Units_A1_Grid->Add(Units_Unitline_Holder, 0, wxLEFT, 5);
    Units_A1_Grid->Add(Units_MinTechLevel_Holder, 0, wxLEFT, 5);
    Units_A4_Grid->Add(Units_PlacementTerrain_Holder, 0, wxRIGHT, 5);
    Units_A4_Grid->Add(Units_PlacementSideTerrain_Holder);
    Units_A5_Grid->Add(Units_TerrainRestriction_Holder);
    Units_AttributesTracking_Grid->Add(Units_TrackingUnit_Holder);
    Units_AttributesTracking_Grid->Add(Units_TrackingUnitUsed_Holder, 0, wxLEFT, 5);
    Units_AttributesTracking_Grid->Add(Units_TrackingUnitDensity_Holder, 0, wxLEFT, 5);
    Units_CostHeader_Holder->Add(Unit_Cost_Texts);
    for(auto &sizer: Unit_Cost_Sizers)
    Units_CostHeader_Holder->Add(sizer, 0, wxLEFT, 5);
    Units_AttributesTrain1_Grid->Add(Units_CommandID_Holder);
    Units_AttributesTrain1_Grid->Add(Units_TrainTime_Holder, 0, wxLEFT, 5);
    Units_AttributesTrain1_Grid->Add(Units_TrainLocationID_Holder, 0, wxLEFT, 5);
    Units_A3_Grid->Add(Units_StackUnitID_Holder);
    Units_A5_Grid->Add(Units_TerrainID_Holder);
    Units_A5_Grid->Add(Units_OldTerrainLikeID_Holder);
    Units_A5_Grid->Add(Units_ResearchID_Holder);
    Units_A6_Grid->Add(Units_ActionWhenDiscoveredID_Holder);
    Units_A6_Grid->Add(Units_DropSite_Holder, 0, wxLEFT, 5);
    Units_A3_Grid->Add(Units_HeadUnit_Holder, 0, wxLEFT, 5);
    Units_A3_Grid->Add(Units_TransformUnit_Holder, 0, wxLEFT, 5);
    Units_A3_Grid->Add(Units_PileUnit_Holder, 0, wxLEFT, 5);
    Units_AttributesTrain1_Grid->Add(Units_ButtonID_Holder, 0, wxLEFT, 5);

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
    Units_Attributes_Holder->Add(Units_EditorSelectionColour_Holder, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_AttributesTracking_Grid, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_RotationAngles_Holder, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_AttributesTrain1_Grid, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_ResourceStorageHeader_Holder, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_CostHeader_Holder, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_A3_Grid, 0, wxTOP, 5);
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
    Units_CommandHolder_Lists->Add(slp_unit_actions, 0, wxTOP, 5);

    Unit_Command_Known1->Add(UnitCommands_Type_Holder, 0, wxLEFT, 5);
    Unit_Command_Known1->Add(UnitCommands_One_Holder, 0, wxLEFT, 5);
    Unit_Command_Known1->Add(UnitCommands_ID_Holder, 0, wxLEFT, 5);
    Unit_Command_Known2->Add(UnitCommands_ClassID_Holder);
    Unit_Command_Known2->Add(UnitCommands_UnitID_Holder);
    Unit_Command_Known2->Add(UnitCommands_TerrainID_Holder);
    Unit_Command_Known2->Add(UnitCommands_ResourceIn_Holder);
    Unit_Command_Known2->Add(UnitCommands_ProductivityResource_Holder);
    Unit_Command_Known2->Add(UnitCommands_ResourceOut_Holder);
    Unit_Command_Known3->Add(UnitCommands_Resource_Holder, 0, wxLEFT, 5);
    Unit_Command_Known3->Add(UnitCommands_WorkRateMultiplier_Holder, 0, wxLEFT, 5);
    Unit_Command_Known3->Add(UnitCommands_ExecutionRadius_Holder, 0, wxLEFT, 5);
    Unit_Command_Known3->Add(UnitCommands_ExtraRange_Holder, 0, wxLEFT, 5);

    for(size_t loop = 0; loop < UnitCommands_Graphics.size(); ++loop)
    {
        UnitCommands_Graphics_Holder[loop]->Add(UnitCommands_Graphics_Text[loop]);
        UnitCommands_Graphics_Holder[loop]->Add(UnitCommands_Graphics[loop], 0, wxEXPAND);
        UnitCommands_Graphics_Holder[loop]->Add(UnitCommands_Graphics_ComboBox[loop]);
        Unit_Command_Known4->Add(UnitCommands_Graphics_Holder[loop]);
    }

    Unit_Command_Unknowns->Add(UnitCommands_Unknown1_Holder);
    Unit_Command_Unknowns->Add(UnitCommands_Unknown4_Holder);
    Unit_Command_Unknowns->Add(UnitCommands_Unknown5_Holder);
    Unit_Command_Unknowns->Add(UnitCommands_SelectionEnabler_Holder);
    Unit_Command_Unknowns->Add(UnitCommands_Unknown7_Holder);
    Unit_Command_Unknowns->Add(UnitCommands_Unknown8_Holder);
    Unit_Command_Unknowns->Add(UnitCommands_Unknown9_Holder);
    Unit_Command_Unknowns->Add(UnitCommands_SelectionMode_Holder);
    Unit_Command_Unknowns->Add(UnitCommands_RightClickMode_Holder);
    Unit_Command_Unknowns->Add(UnitCommands_Unknown12_Holder);

    Units_CommandHolder_Data->Add(Unit_Command_Known1);
    Units_CommandHolder_Data->Add(Unit_Command_Known2, 0, wxTOP | wxLEFT, 5);
    Units_CommandHolder_Data->Add(Unit_Command_Known3, 0, wxTOP, 5);
    Units_CommandHolder_Data->Add(Unit_Command_Known4, 0, wxTOP | wxLEFT, 5);
    Units_CommandHolder_Data->Add(Unit_Command_Unknowns, 0, wxTOP | wxLEFT, 5);

    Units_CommandsArea_Holder->Add(Units_CommandHolder_Lists, 1, wxEXPAND);
    Units_CommandsArea_Holder->Add(Units_CommandHolder_Data, 3, wxEXPAND, 5);

    Units_UnknownArea_Holder->Add(Units_Type10plusUnknownArea_Holder);
    Units_UnknownArea_Holder->Add(Units_Type30plusUnknownArea_Holder);
    Units_UnknownArea_Holder->Add(Units_Type70plusUnknownArea_Holder);
    Units_UnknownArea_Holder->Add(Units_Type80plusUnknownArea_Holder);

    Units_ScrollSpace->Add(Units_LangDLLArea_Holder, 0, wxEXPAND);
    Units_ScrollSpace->Add(Units_GraphicsArea_Holder, 0, wxEXPAND | wxTOP, 5);
    Units_ScrollSpace->Add(Units_StatsArea_Holder, 0, wxEXPAND | wxTOP, 5);
    Units_ScrollSpace->Add(Units_ProjectileArea_Holder, 0, wxEXPAND | wxTOP, 5);
    Units_ScrollSpace->Add(Units_Attributes_Holder, 0, wxEXPAND | wxTOP, 5);
    Units_ScrollSpace->Add(Units_SoundsArea_Holder, 0, wxEXPAND | wxTOP, 5);
    Units_ScrollSpace->Add(Units_UnknownArea_Holder, 0, wxEXPAND | wxTOP, 5);
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

    Units_UnitCommands_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnUnitCommandSelect, this);
    Units_UnitCommands_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnUnitCommandsSearch, this);
    Units_UnitCommands_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnUnitCommandsSearch, this);
    Units_UnitCommands_Add->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitCommandsAdd, this);
    Units_UnitCommands_Insert->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitCommandsInsert, this);
    Units_UnitCommands_Delete->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitCommandsDelete, this);
    Units_UnitCommands_Copy->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitCommandsCopy, this);
    Units_UnitCommands_Paste->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitCommandsPaste, this);
    Units_UnitCommands_PasteInsert->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitCommandsPasteInsert, this);
    Units_UnitCommands_CopyToUnits->Bind(wxEVT_BUTTON, &AGE_Frame::OnUnitCommandsCopyToUnits, this);
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
    Units_Type_ComboBox->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);

    Units_Name->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_Name2->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_LanguageDLLName->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_LanguageDLLCreation->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_HotKey->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_LanguageDLLHelp->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_LanguageDLLHotKeyText->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_Attribute->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_GarrisonType->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);

    DamageGraphics_GraphicID->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    DamageGraphics_GraphicID_ComboBox->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    DamageGraphics_DamagePercent->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    DamageGraphics_ApplyMode->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Attacks_Class->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Attacks_Amount->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Armors_Class->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Armors_Amount->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    for(size_t loop = 0; loop < 2; ++loop)
    Attacks_Class_ComboBox[loop]->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);

    UnitCommands_Type->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    UnitCommands_ProductivityResource->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    UnitCommands_Type_ComboBox->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    for(size_t loop = 0; loop < 8; ++loop)
    {
        Units_Attribute_CheckBox[loop]->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnUpdateCheck_UnitAttribute, this);
        Units_GarrisonType_CheckBox[loop]->Bind(wxEVT_CHECKBOX, &AGE_Frame::OnUpdateCheck_UnitGarrisonType, this);
    }
    Units_IconID->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_IconAngle->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_IconID_SLP->Bind(wxEVT_PAINT, &AGE_Frame::OnDrawIconSLP, this);
    Units_IconID_SLP->Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent&){});

    // To make SLP view refresh.
    Units_ConstructionGraphicID->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_SnowGraphicID->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_GarrisonGraphic->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_ChargingGraphic->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_AttackGraphic->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_WalkingGraphic[0]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_WalkingGraphic[1]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_StandingGraphic[0]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_StandingGraphic[1]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_DyingGraphic[0]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_DyingGraphic[1]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    UnitCommands_Graphics[0]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    UnitCommands_Graphics[1]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    UnitCommands_Graphics[2]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    UnitCommands_Graphics[3]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
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
    UnitCommands_Graphics_ComboBox[0]->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    UnitCommands_Graphics_ComboBox[1]->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    UnitCommands_Graphics_ComboBox[2]->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    UnitCommands_Graphics_ComboBox[3]->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    Units_SizeRadius[0]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_SizeRadius[1]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_ClearanceSize[0]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_ClearanceSize[1]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_SelectionRadius[0]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    Units_SelectionRadius[1]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    for(size_t loop = 0; loop < 4; ++loop)
    {
        Units_AnnexUnitMisplacement[loop][0]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
        Units_AnnexUnitMisplacement[loop][1]->Bind(wxEVT_KILL_FOCUS, &AGE_Frame::OnKillFocus_Units, this);
    }
}

void AGE_Frame::OnKillFocus_Units(wxFocusEvent &event)
{
    event.Skip();
    if(static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() != 0) return;
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
        wxCommandEvent e;
        OnUnitSelect(e);
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
        wxCommandEvent e;
        OnUnitSelect(e);    // Updates unit layout.
//      ListUnits(UnitCivID, false);    // For special search filters.
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
