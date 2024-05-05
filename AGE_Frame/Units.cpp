#include "Common.h"
#include "../AGE_Frame.h"
#include "genie/resource/Color.h"

std::vector<std::function<wxString(genie::Unit*)>> UnitFilterFunctions;
bool UseDynamicUnitName;

wxString AGE_Frame::GetUnitName(int index, short civ, bool filter)
{
    if (dataset->Civs[civ].UnitPointers[index] == 0)
    {
        return "Nonexistent";
    }
    wxString name;
    if (filter)
    {
        for (auto &f : UnitFilterFunctions)
        {
            name += f(&dataset->Civs[civ].Units[index]) + ", ";
        }
    }
    if (UseDynamicUnitName)
    {
        wxString DynamicName = TranslatedText(dataset->Civs[civ].Units[index].LanguageDLLName, 64);
        if (!DynamicName.empty())
        {
            return name + DynamicName;
        }
    }
    if (!dataset->Civs[civ].Units[index].Name.empty())
    {
        return name + dataset->Civs[civ].Units[index].Name;
    }
    return name + "New Unit";
}

#define UF30 unit_ptr->Type < 30 || unit_ptr->Type > 80 ? "NA" :
#define UF40 unit_ptr->Type < 40 || unit_ptr->Type > 80 ? "NA" :
#define UF50 unit_ptr->Type < 50 || unit_ptr->Type > 80 ? "NA" :
#define UF60 unit_ptr->Type != 60 ? "NA" :
#define UF70 unit_ptr->Type != 70 && unit_ptr->Type != 80 ? "NA" :
#define UF80 unit_ptr->Type != 80 ? "NA" :

void AGE_Frame::PrepUnitSearch()
{
    UseDynamicUnitName = true;
    UnitFilterFunctions.clear();
    for(size_t loop = 0; loop < 2; ++loop)
    {
        int selection = Units_SearchFilters[loop]->GetSelection();
        if(selection < 1) continue;
        wxString label = unit_filters[selection];

        if (label.compare("Type") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "T " + FormatInt(unit_ptr->Type);
        });
        else if (label.compare("ID") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "I1 " + FormatInt(unit_ptr->ID);
        });
        else if (label.compare("Language File Name") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "LN " + FormatInt(unit_ptr->LanguageDLLName);
        });
        else if (label.compare("Language File Creation") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "LC " + FormatInt(unit_ptr->LanguageDLLCreation);
        });
        else if (label.compare("Class") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "C " + FormatInt(unit_ptr->Class);
        });
        else if (label.compare("Standing Graphics") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "SG " + FormatInt(unit_ptr->StandingGraphic.first) + " "
                    + FormatInt(unit_ptr->StandingGraphic.second);
        });
        else if (label.compare("Dying Graphics") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "DG " + FormatInt(unit_ptr->DyingGraphic) + " "
                    + FormatInt(unit_ptr->UndeadGraphic);
        });
        else if (label.compare("Undead Mode") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "DM " + FormatInt(unit_ptr->UndeadMode);
        });
        else if (label.compare("Hit Points") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "HP " + FormatInt(unit_ptr->HitPoints);
        });
        else if (label.compare("Line of Sight") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "LS " + FormatFloat(unit_ptr->LineOfSight);
        });
        else if (label.compare("Garrison Capacity") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "GC " + FormatInt(unit_ptr->GarrisonCapacity);
        });
        else if (label.compare("Collision Size XY") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "SR " + FormatFloat(unit_ptr->CollisionSize.x) + " "
                    + FormatFloat(unit_ptr->CollisionSize.y);
        });
        else if (label.compare("Collision Size Z") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "B1 " + FormatFloat(unit_ptr->CollisionSize.z);
        });
        else if (label.compare("Train Sound") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "TS " + FormatInt(unit_ptr->TrainSound);
        });
        else if (label.compare("Damage Sound") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "VS " + FormatInt(unit_ptr->DamageSound);
        });
        else if (label.compare("Dead Unit") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "DU " + FormatInt(unit_ptr->DeadUnitID);
        });
        else if (label.compare("Blood Unit") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "BU " + FormatInt(unit_ptr->BloodUnitID);
        });
        else if (label.compare("Sort Number") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "PM " + FormatInt(unit_ptr->SortNumber);
        });
        else if (label.compare("Can be Built on") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "AM " + FormatInt(unit_ptr->CanBeBuiltOn);
        });
        else if (label.compare("Icon") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "I " + FormatInt(unit_ptr->IconID);
        });
        else if (label.compare("Hide in Editor") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "HE " + FormatInt(unit_ptr->HideInEditor);
        });
        else if (label.compare("Portrait Picture") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "U1 " + FormatInt(unit_ptr->OldPortraitPict);
        });
        else if (label.compare("Available") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "E " + FormatInt(unit_ptr->Enabled);
        });
        else if (label.compare("Disabled") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "D " + FormatInt(unit_ptr->Disabled);
        });
        else if (label.compare("Placement Side Terrain x2") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            wxString name = "PBT " + FormatInt(unit_ptr->PlacementSideTerrain.first) +
                " PBT " + FormatInt(unit_ptr->PlacementSideTerrain.second) + " ";
            return name;
        });
        else if (label.compare("Placement Terrain x2") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            wxString name = "PT " + FormatInt(unit_ptr->PlacementTerrain.first) +
                " PT " + FormatInt(unit_ptr->PlacementTerrain.second) + " ";
            return name;
        });
        else if (label.compare("Clearance Size XY") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "ER " + FormatFloat(unit_ptr->ClearanceSize.first) + " "
                    + FormatFloat(unit_ptr->ClearanceSize.second);
        });
        else if (label.compare("Hill Mode") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "HM " + FormatInt(unit_ptr->HillMode);
        });
        else if (label.compare("Fog Visibility") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "VF " + FormatInt(unit_ptr->FogVisibility);
        });
        else if (label.compare("Terrain Table") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "TR " + FormatInt(unit_ptr->TerrainRestriction);
        });
        else if (label.compare("Fly Mode") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "FM " + FormatInt(unit_ptr->FlyMode);
        });
        else if (label.compare("Resource Capacity") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "RC " + FormatInt(unit_ptr->ResourceCapacity);
        });
        else if (label.compare("Resource Decay") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "RD " + FormatFloat(unit_ptr->ResourceDecay);
        });
        else if (label.compare("Blast Defense Level") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "BA " + FormatInt(unit_ptr->BlastDefenseLevel);
        });
        else if (label.compare("Combat Level") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "U2 " + FormatInt(unit_ptr->CombatLevel);
        });
        else if (label.compare("Interaction Mode") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "IM " + FormatInt(unit_ptr->InteractionMode);
        });
        else if (label.compare("Minimap Mode") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "MM " + FormatInt(unit_ptr->MinimapMode);
        });
        else if (label.compare("Interface Kind") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "CA " + FormatInt(unit_ptr->InterfaceKind);
        });
        else if (label.compare("Multiple Attribute Mode") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "U3A " + FormatFloat(unit_ptr->MultipleAttributeMode);
        });
        else if (label.compare("Minimap Color") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "MC " + FormatInt(unit_ptr->MinimapColor);
        });
        else if (label.compare("Language File Help") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "LH " + FormatInt(unit_ptr->LanguageDLLHelp);
        });
        else if (label.compare("Language File Hot Key Text") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "LT " + FormatInt(unit_ptr->LanguageDLLHotKeyText);
        });
        else if (label.compare("Hot Key") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "HK " + FormatInt(unit_ptr->HotKey);
        });
        else if (label.compare("Recyclable") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "US " + FormatInt(unit_ptr->Recyclable);
        });
        else if (label.compare("Gatherable") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "IG " + FormatInt(unit_ptr->EnableAutoGather);
        });
        else if (label.compare("Doppelganger on Death") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "DD " + FormatInt(unit_ptr->CreateDoppelgangerOnDeath);
        });
        else if (label.compare("Gather Group") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "GG " + FormatInt(unit_ptr->ResourceGatherGroup);
        });
        else if (label.compare("Occlusion Mode") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "OM " + FormatInt(unit_ptr->OcclusionMode);
        });
        else if (label.compare("Obstruction Type") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "OT " + FormatInt(unit_ptr->ObstructionType);
        });
        else if (label.compare("Obstruction Class") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "OC " + FormatInt(unit_ptr->ObstructionClass);
        });
        else if (label.compare("Trait") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "A " + FormatInt(unit_ptr->Trait);
        });
        else if (label.compare("Civilization") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "Civ " + FormatInt(unit_ptr->Civilization);
        });
        else if (label.compare("Nothing") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "No " + FormatInt(unit_ptr->Nothing);
        });
        else if (label.compare("Selection Effect") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "SE " + FormatInt(unit_ptr->SelectionEffect);
        });
        else if (label.compare("Editor Selection Color") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "EC " + FormatInt(unit_ptr->EditorSelectionColour);
        });
        else if (label.compare("Selection Size XY") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "OS " + FormatFloat(unit_ptr->OutlineSize.x) + " "
                    + FormatFloat(unit_ptr->OutlineSize.y);
        });
        else if (label.compare("Selection Size Z") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "B2 " + FormatFloat(unit_ptr->OutlineSize.z);
        });
        else if (label.compare("Resource Storages") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            wxString name = "";
            for (size_t i = 0; i < unit_ptr->ResourceStorages.size(); ++i)
            {
                name += "RSD " + FormatInt(unit_ptr->ResourceStorages[i].Type) + " " +
                    FormatInt(unit_ptr->ResourceStorages[i].Amount) + " " +
                    FormatInt(unit_ptr->ResourceStorages[i].Flag) + " ";
            }
            return name;
        });
        else if (label.compare("Damage Graphic Count") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "DC " + FormatInt(unit_ptr->DamageGraphics.size());
        });
        else if (label.compare("Damage Graphics") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            wxString name = "";
            for (size_t i = 0; i < unit_ptr->DamageGraphics.size(); ++i)
            {
                name += "DGD " + FormatInt(unit_ptr->DamageGraphics[i].GraphicID) + " " +
                    FormatInt(unit_ptr->DamageGraphics[i].DamagePercent) + " " +
                    FormatInt(unit_ptr->DamageGraphics[i].ApplyMode) + " ";
            }
            return name.empty() ? "No DGD" : name;
        });
        else if (label.compare("Selection Sound") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "SS " + FormatInt(unit_ptr->SelectionSound);
        });
        else if (label.compare("Dying Sound") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "DS " + FormatInt(unit_ptr->DyingSound);
        });
        else if (label.compare("Attack Reaction") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "AtM " + FormatInt(unit_ptr->OldAttackReaction);
        });
        else if (label.compare("Convert Terrain") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "EM " + FormatInt(unit_ptr->ConvertTerrain);
        });
        else if (label.compare("Internal Name") == 0)
        {
            UseDynamicUnitName = false;
            continue;
        }
        else if (label.compare("Internal Name 2") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return wxString(unit_ptr->Name2);
        });
        else if (label.compare("Unitline") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "UL " + FormatInt(unit_ptr->Unitline);
        });
        else if (label.compare("Min Tech Level") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "MT " + FormatInt(unit_ptr->MinTechLevel);
        });
        else if (label.compare("Copy ID") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "I2 " + FormatInt(unit_ptr->CopyID);
        });
        else if (label.compare("Base ID") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "I3 " + FormatInt(unit_ptr->BaseID);
        });
        else if (label.compare("Speed") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "S " + FormatFloat(unit_ptr->Speed);
        });
        else if (label.compare("Tracking ID") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "TI " + FormatInt(unit_ptr->TelemetryID);
        });
        else if (label.compare("Train Wwise Sound") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "TW " + FormatUnsigned(unit_ptr->WwiseTrainSoundID);
        });
        else if (label.compare("Damage Wwise Sound") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "VW " + FormatUnsigned(unit_ptr->WwiseDamageSoundID);
        });
        else if (label.compare("Selection Wwise Sound") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "SW " + FormatUnsigned(unit_ptr->WwiseSelectionSoundID);
        });
        else if (label.compare("Dying Wwise Sound") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return "DW " + FormatUnsigned(unit_ptr->WwiseDyingSoundID);
        });

        else if (label.compare("Walking Graphics") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF30 "WG " + FormatInt(unit_ptr->DeadFish.WalkingGraphic) + " "
                    + FormatInt(unit_ptr->DeadFish.RunningGraphic);
        });
        else if (label.compare("Rotation Speed") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF30 "RS " + FormatFloat(unit_ptr->DeadFish.RotationSpeed);
        });
        else if (label.compare("Size Class") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF30 "U11 " + FormatInt(unit_ptr->DeadFish.OldSizeClass);
        });
        else if (label.compare("Trailing Unit") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF30 "TU " + FormatInt(unit_ptr->DeadFish.TrackingUnit);
        });
        else if (label.compare("Trailing Unit Mode") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF30 "UU " + FormatInt(unit_ptr->DeadFish.TrackingUnitMode);
        });
        else if (label.compare("Trailing Unit Density") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF30 "UD " + FormatFloat(unit_ptr->DeadFish.TrackingUnitDensity);
        });
        else if (label.compare("Move Algorithm") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF30 "U16 " + FormatInt(unit_ptr->DeadFish.OldMoveAlgorithm);
        });
        else if (label.compare("Rotation Angles") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF30 "r" + FormatFloat(unit_ptr->DeadFish.TurnRadius)
                    + " s" + FormatFloat(unit_ptr->DeadFish.TurnRadiusSpeed)
                    + " m" + FormatFloat(unit_ptr->DeadFish.MaxYawPerSecondMoving)
                    + " t" + FormatFloat(unit_ptr->DeadFish.StationaryYawRevolutionTime)
                    + " y" + FormatFloat(unit_ptr->DeadFish.MaxYawPerSecondStationary);
        });
        else if (label.compare("Min Collision Size Multiplier") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF30 "MK " + FormatFloat(unit_ptr->DeadFish.MinCollisionSizeMultiplier);
        });

        else if (label.compare("Default Task") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "SC " + FormatInt(unit_ptr->Bird.DefaultTaskID);
        });
        else if (label.compare("Search Radius") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "SR " + FormatFloat(unit_ptr->Bird.SearchRadius);
        });
        else if (label.compare("Work Rate") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "WR " + FormatFloat(unit_ptr->Bird.WorkRate);
        });
        else if (label.compare("Drop Site Count") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "DSC " + FormatInt(unit_ptr->Bird.DropSites.size());
        });
        else if (label.compare("Drop Sites") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            wxString name = "";
            for(size_t i = 0; i < unit_ptr->Bird.DropSites.size(); ++i)
            name += "DS" + FormatInt(unit_ptr->Bird.DropSites[i]) + " ";
            return UF40 name;
        });
        else if (label.compare("Task Swap Group") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "VM " + FormatInt(unit_ptr->Bird.TaskSwapGroup);
        });
        else if (label.compare("Attack Sound") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "AS " + FormatInt(unit_ptr->Bird.AttackSound);
        });
        else if (label.compare("Move Sound") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "MS " + FormatInt(unit_ptr->Bird.MoveSound);
        });
        else if (label.compare("Run Pattern") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "AM " + FormatInt(unit_ptr->Bird.RunPattern);
        });
        else if (label.compare("Task Count") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "CC " + FormatInt(unit_ptr->Bird.TaskList.size());
        });
        else if (label.compare("Tasks") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            wxString name = "";
            for (size_t i = 0; i < unit_ptr->Bird.TaskList.size(); ++i)
            {
                name += "TD " + FormatInt(unit_ptr->Bird.TaskList[i].ActionType) + " ";
            }
            return UF40 name.empty() ? "No TD" : name;
        });
        else if (label.compare("Attack Wave Works Sound") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "AW " + FormatUnsigned(unit_ptr->Bird.WwiseAttackSoundID);
        });
        else if (label.compare("Move Wave Works Sound") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF40 "MW " + FormatUnsigned(unit_ptr->Bird.WwiseMoveSoundID);
        });

        if (label.compare("Base Armor") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "DA " + FormatInt(unit_ptr->Type50.BaseArmor);
        });
        else if (label.compare("Attack Count") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "AtC " + FormatInt(unit_ptr->Type50.Attacks.size());
        });
        else if (label.compare("Attacks") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            wxString name = "";
            for(size_t i = 0; i < unit_ptr->Type50.Attacks.size(); ++i)
            name += "C" + FormatInt(unit_ptr->Type50.Attacks[i].Class) + " ";
            return UF50 name.empty() ? "No AtC" : name;
        });
        else if (label.compare("Armor Count") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "ArC " + FormatInt(unit_ptr->Type50.Armours.size());
        });
        else if (label.compare("Armors") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            wxString name = "";
            for(size_t i = 0; i < unit_ptr->Type50.Armours.size(); ++i)
            name += "C" + FormatInt(unit_ptr->Type50.Armours[i].Class) + " ";
            return UF50 name.empty() ? "No ArC" : name;
        });
        else if (label.compare("Terrain Defense Bonus") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "TR " + FormatInt(unit_ptr->Type50.DefenseTerrainBonus);
        });
        else if (label.compare("Max Range") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "MaxR " + FormatFloat(unit_ptr->Type50.MaxRange);
        });
        else if (label.compare("Blast Width") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "BW " + FormatFloat(unit_ptr->Type50.BlastWidth);
        });
        else if (label.compare("Reload Time") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "RT " + FormatFloat(unit_ptr->Type50.ReloadTime);
        });
        else if (label.compare("Projectile Unit") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "PU " + FormatInt(unit_ptr->Type50.ProjectileUnitID);
        });
        else if (label.compare("Accuracy Percent") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "AP " + FormatInt(unit_ptr->Type50.AccuracyPercent);
        });
        else if (label.compare("Break off Combat") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "TM " + FormatInt(unit_ptr->Type50.BreakOffCombat);
        });
        else if (label.compare("Frame Delay") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "D " + FormatInt(unit_ptr->Type50.FrameDelay);
        });
        else if (label.compare("Graphic Displacement") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "x" + FormatFloat(unit_ptr->Type50.GraphicDisplacement[0])
                    + " y" + FormatFloat(unit_ptr->Type50.GraphicDisplacement[1])
                    + " z" + FormatFloat(unit_ptr->Type50.GraphicDisplacement[2]);
        });
        else if (label.compare("Blast Attack Level") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "BL " + FormatInt(unit_ptr->Type50.BlastAttackLevel);
        });
        else if (label.compare("Blast Damage") == 0)
        { 
            UnitFilterFunctions.push_back([this](genie::Unit* unit_ptr)
                {
                    return UF50 "BLD " + FormatFloat(unit_ptr->Type50.BlastDamage);
                });
        }
        else if (label.compare("Min Range") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "MinR " + FormatFloat(unit_ptr->Type50.MinRange);
        });
        else if (label.compare("Attack Dispersion") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "AE " + FormatFloat(unit_ptr->Type50.AccuracyDispersion);
        });
        else if (label.compare("Attack Graphic") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "AG " + FormatInt(unit_ptr->Type50.AttackGraphic);
        });
        else if (label.compare("Displayed Melee Armor") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "DM " + FormatInt(unit_ptr->Type50.DisplayedMeleeArmour);
        });
        else if (label.compare("Displayed Attack") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "DP " + FormatInt(unit_ptr->Type50.DisplayedAttack);
        });
        else if (label.compare("Displayed Range") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "DR " + FormatFloat(unit_ptr->Type50.DisplayedRange);
        });
        else if (label.compare("Displayed Reload Time") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "DT " + FormatFloat(unit_ptr->Type50.DisplayedReloadTime);
        });
        else if (label.compare("Bonus Damage Resistance") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF50 "BR " + FormatFloat(unit_ptr->Type50.BonusDamageResistance);
        });

        else if (label.compare("Projectile Type") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF60 "SM " + FormatInt(unit_ptr->Projectile.ProjectileType);
        });
        else if (label.compare("Smart Mode") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF60 "CM " + FormatInt(unit_ptr->Projectile.SmartMode);
        });
        else if (label.compare("Hit Mode") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF60 "DA " + FormatInt(unit_ptr->Projectile.HitMode);
        });
        else if (label.compare("Vanish Mode") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF60 "PM " + FormatInt(unit_ptr->Projectile.VanishMode);
        });
        else if (label.compare("Area Effect Specials") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF60 "U24 " + FormatInt(unit_ptr->Projectile.AreaEffectSpecials);
        });
        else if (label.compare("Projectile Arc") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF60 "PA " + FormatFloat(unit_ptr->Projectile.ProjectileArc);
        });

        else if (label.compare("Resource Costs") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            wxString name = "";
            for (size_t i = 0; i < unit_ptr->Creatable.ResourceCosts.size(); ++i)
            {
                name += "RCD " + FormatInt(unit_ptr->Creatable.ResourceCosts[i].Type) + " " +
                    FormatInt(unit_ptr->Creatable.ResourceCosts[i].Amount) + " " +
                    FormatInt(unit_ptr->Creatable.ResourceCosts[i].Flag) + " ";
            }
            return UF70 name;
        });
        else if (label.compare("Train Time") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "TT " + FormatInt(unit_ptr->Creatable.TrainTime);
        });
        else if (label.compare("Train Location") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "TL " + FormatInt(unit_ptr->Creatable.TrainLocationID);
        });
        else if (label.compare("Train Button") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "B " + FormatInt(unit_ptr->Creatable.ButtonID);
        });
        else if (label.compare("Rear Attack Modifier") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "RAM " + FormatFloat(unit_ptr->Creatable.RearAttackModifier);
        });
        else if (label.compare("Flank Attack Modifier") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "FAM " + FormatFloat(unit_ptr->Creatable.FlankAttackModifier);
        });
        else if (label.compare("Creatable Type") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "U28 " + FormatInt(unit_ptr->Creatable.CreatableType);
        });
        else if (label.compare("Hero Mode") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "HM " + FormatInt(unit_ptr->Creatable.HeroMode);
        });
        else if (label.compare("Garrison Graphic") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "GG " + FormatInt(unit_ptr->Creatable.GarrisonGraphic);
        });
        else if (label.compare("Total Projectiles") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "TP " + FormatFloat(unit_ptr->Creatable.TotalProjectiles);
        });
        else if (label.compare("Max Total Projectiles") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "MTP " + FormatInt(unit_ptr->Creatable.MaxTotalProjectiles);
        });
        else if (label.compare("Projectile Spawning Area") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "x" + FormatFloat(unit_ptr->Creatable.ProjectileSpawningArea[0])
                    + " y" + FormatFloat(unit_ptr->Creatable.ProjectileSpawningArea[1])
                    + " z" + FormatFloat(unit_ptr->Creatable.ProjectileSpawningArea[2]);
        });
        else if (label.compare("Secondary Projectile Unit") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "AP " + FormatInt(unit_ptr->Creatable.SecondaryProjectileUnit);
        });
        else if (label.compare("Special Graphic") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "CG " + FormatInt(unit_ptr->Creatable.SpecialGraphic);
        });
        else if (label.compare("Special Ability") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "CM " + FormatInt(unit_ptr->Creatable.SpecialAbility);
        });
        else if (label.compare("Displayed Pierce Armor") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "DP " + FormatInt(unit_ptr->Creatable.DisplayedPierceArmour);
        });
        else if (label.compare("Spawning Graphic") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "SpG " + FormatInt(unit_ptr->Creatable.SpawningGraphic);
        });
        else if (label.compare("Upgrade Graphic") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "UpG " + FormatInt(unit_ptr->Creatable.UpgradeGraphic);
        });
        else if (label.compare("Max Charge") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "TC " + FormatInt(unit_ptr->Creatable.MaxCharge);
        });
        else if (label.compare("Recharge Rate") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "RR " + FormatInt(unit_ptr->Creatable.RechargeRate);
        });
        else if (label.compare("Charge Event") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "CE " + FormatInt(unit_ptr->Creatable.ChargeEvent);
        });
        else if (label.compare("Charge Type") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "CT " + FormatInt(unit_ptr->Creatable.ChargeType);
        });
        else if (label.compare("Hero Glow Graphic") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "HGG " + FormatInt(unit_ptr->Creatable.HeroGlowGraphic);
        });
        else if (label.compare("Min Conversion Time Mod") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "MinCT " + FormatInt(unit_ptr->Creatable.MinConversionTimeMod);
        });
        else if (label.compare("Max Conversion Time Mod") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "MaxCT " + FormatInt(unit_ptr->Creatable.MaxConversionTimeMod);
        });
        else if (label.compare("Conversion Chance Mod") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF70 "CCM " + FormatInt(unit_ptr->Creatable.ConversionChanceMod);
        });

        else if (label.compare("Construction Graphic") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "CG " + FormatInt(unit_ptr->Building.ConstructionGraphicID);
        });
        else if (label.compare("Snow Graphic") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "SG " + FormatInt(unit_ptr->Building.SnowGraphicID);
        });
        else if (label.compare("Adjacent Mode") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "AM " + FormatInt(unit_ptr->Building.AdjacentMode);
        });
        else if (label.compare("Graphics Angle") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "GA " + FormatInt(unit_ptr->Building.GraphicsAngle);
        });
        else if (label.compare("Disappears After Built") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "DB " + FormatInt(unit_ptr->Building.DisappearsWhenBuilt);
        });
        else if (label.compare("Stack Unit") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "SU " + FormatInt(unit_ptr->Building.StackUnitID);
        });
        else if (label.compare("Foundation Terrain") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "FT " + FormatInt(unit_ptr->Building.FoundationTerrainID);
        });
        else if (label.compare("Old Overlay") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "OT " + FormatInt(unit_ptr->Building.OldOverlayID);
        });
        else if (label.compare("Tech") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "R " + FormatInt(unit_ptr->Building.TechID);
        });
        else if (label.compare("Can Burn") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "U33 " + FormatInt(unit_ptr->Building.CanBurn);
        });
        else if (label.compare("Annexes") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            wxString name = "";
            for (size_t i = 0; i < unit_ptr->Building.Annexes.size(); ++i)
            {
                name += "AU " + FormatInt(unit_ptr->Building.Annexes[i].UnitID) + " ";
            }
            return UF80 name;
        });
        else if (label.compare("Head Unit") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "HU " + FormatInt(unit_ptr->Building.HeadUnit);
        });
        else if (label.compare("Transform Unit") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "TU " + FormatInt(unit_ptr->Building.TransformUnit);
        });
        else if (label.compare("Transform Sound") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "US " + FormatInt(unit_ptr->Building.TransformSound);
        });
        else if (label.compare("Construction Sound") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "CS " + FormatInt(unit_ptr->Building.ConstructionSound);
        });
        else if (label.compare("Garrison Type") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "GT " + FormatInt(unit_ptr->Building.GarrisonType);
        });
        else if (label.compare("Garrison Heal Rate") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "GH " + FormatFloat(unit_ptr->Building.GarrisonHealRate);
        });
        else if (label.compare("Garrison Repair Rate") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "U35 " + FormatFloat(unit_ptr->Building.GarrisonRepairRate);
        });
        else if (label.compare("Pile Unit") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "PU " + FormatInt(unit_ptr->Building.PileUnit);
        });
        else if (label.compare("Looting Table") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            wxString name = "";
            for (size_t i = 0; i < unit_ptr->Building.LootingTable.size(); ++i)
                name += "LTD " + FormatInt(unit_ptr->Building.LootingTable[i]) + " ";
            return UF80 name;
        });
        else if (label.compare("Transform Wave Works Sound") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "UW " + FormatUnsigned(unit_ptr->Building.WwiseTransformSoundID);
        });
        else if (label.compare("Construction Wave Works Sound") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "CW " + FormatUnsigned(unit_ptr->Building.WwiseConstructionSoundID);
        });
        else if (label.compare("Foundation Destruction Graphic") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "FG " + FormatInt(unit_ptr->Building.DestructionGraphicID);
        });
        else if (label.compare("Foundation Rubble Graphic") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "RG " + FormatInt(unit_ptr->Building.DestructionRubbleGraphicID);
        });
        else if (label.compare("Researching Graphic") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "RPG " + FormatInt(unit_ptr->Building.ResearchingGraphic);
        });
        else if (label.compare("Research Completed Graphic") == 0)
        UnitFilterFunctions.push_back([this](genie::Unit *unit_ptr)
        {
            return UF80 "RCG " + FormatInt(unit_ptr->Building.ResearchCompletedGraphic);
        });
    }
}

void AGE_Frame::OnUnitsSearch(wxCommandEvent&)
{
    short Selection = Units_Civs_List->GetSelection();
    if(Selection == wxNOT_FOUND) return;

    How2List = ListMode::SEARCH;
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
        case 3: matcher = genie::UT_Combatant; break;
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
            while("Nonexistent" == name && ++cult < dataset->Civs.size() && loop < dataset->Civs[cult].Units.size())
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
        wxString name = FormatInt(loop)+" - "+GetUnitName(loop, civ, true);
        if(SearchMatches(" " + name.Lower() + " "))
        {
            Units_ListV->names.Add(name);
            Units_ListV->indexes.push_back(loop);
        }
    }

    RefreshList(Units_ListV, &UnitIDs);
    if(all)
    {
        for (AGEComboBox *list : UnitComboBoxList)
        {
            list->Flash();
        }
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
        museum.reload();
        if(slp_window) slp_view->Refresh();
    }
}

void AGE_Frame::OnUnitSelect(wxCommandEvent &event)
{
    size_t selections = Units_ListV->GetSelectedCount();

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

    for (AGETextCtrl *box : uiGroupUnit) box->clear();
    Units_ID1->clear();
    Units_CopyID->clear();
    Units_BaseID->clear();

    short unitType = -1;
    genie::Unit * UnitPointer = 0;
    for(size_t sel = selections; sel--> 0;)
    {
        unitType = -1;
        // This makes auto-copy automatic.
        for(short vecCiv = SelectedCivs.size(); vecCiv--> 0;)
        {
            if (dataset->Civs[SelectedCivs[vecCiv]].Units.size() <= UnitIDs[sel] ||
                dataset->Civs[SelectedCivs[vecCiv]].UnitPointers[UnitIDs[sel]] == 0)
            {
                continue;
            }
            UnitCivID = SelectedCivs[vecCiv];
            UnitPointer = &dataset->Civs[UnitCivID].Units[UnitIDs[sel]];
            unitType = (short)UnitPointer->Type;
            // Assing data to editing boxes
            switch(unitType)
            {
                case 80:
                {
                    if(CopyGraphics || vecCiv == 0)
                    {
                        Units_ConstructionGraphicID->prepend(&UnitPointer->Building.ConstructionGraphicID);
                    }
                    Units_AdjacentMode->prepend(&UnitPointer->Building.AdjacentMode);
                    Units_IconAngle->prepend(&UnitPointer->Building.GraphicsAngle);
                    Units_DisappearsWhenBuilt->prepend(&UnitPointer->Building.DisappearsWhenBuilt);
                    Units_StackUnitID->prepend(&UnitPointer->Building.StackUnitID);
                    Units_TerrainID->prepend(&UnitPointer->Building.FoundationTerrainID);
                    Units_OldOverlayID->prepend(&UnitPointer->Building.OldOverlayID);
                    Units_ResearchID->prepend(&UnitPointer->Building.TechID);
                    Units_ConstructionSound->prepend(&UnitPointer->Building.ConstructionSound);
                    if(GenieVersion >= genie::GV_AoKE3)
                    {
                        Units_CanBurn->prepend(&UnitPointer->Building.CanBurn);
                        for(size_t loop = 0; loop < 4; ++loop)
                        {
                            Units_AnnexUnit[loop]->prepend(&UnitPointer->Building.Annexes[loop].UnitID);
                            Units_AnnexUnitMisplacement[loop][0]->prepend(&UnitPointer->Building.Annexes[loop].Misplacement.first);
                            Units_AnnexUnitMisplacement[loop][1]->prepend(&UnitPointer->Building.Annexes[loop].Misplacement.second);
                        }
                        Units_TransformUnit->prepend(&UnitPointer->Building.TransformUnit);
                        Units_TransformSound->prepend(&UnitPointer->Building.TransformSound);
                        Units_GarrisonType->prepend(&UnitPointer->Building.GarrisonType);
                        Units_GarrisonHealRate->prepend(&UnitPointer->Building.GarrisonHealRate);
                        Units_GarrisonRepairRate->prepend(&UnitPointer->Building.GarrisonRepairRate);
                        Units_PileUnit->prepend(&UnitPointer->Building.PileUnit);
                        for(size_t loop = 0; loop < Units_LootSwitch.size(); ++loop)
                        Units_LootSwitch[loop]->prepend(&UnitPointer->Building.LootingTable[loop]);
                        if(GenieVersion >= genie::GV_AoKA)
                        {
                            Units_HeadUnit->prepend(&UnitPointer->Building.HeadUnit);
                            if(GenieVersion >= genie::GV_TC)
                            {
                                if(CopyGraphics || vecCiv == 0)
                                {
                                    Units_SnowGraphicID->prepend(&UnitPointer->Building.SnowGraphicID);
                                }
                                if(GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
                                {
                                    if(CopyGraphics || vecCiv == 0)
                                    {
                                        Units_DestructionGraphicID->prepend(&UnitPointer->Building.DestructionGraphicID);
                                        Units_DestructionRubbleGraphicID->prepend(&UnitPointer->Building.DestructionRubbleGraphicID);
                                        Units_ResearchingGraphic->prepend(&UnitPointer->Building.ResearchingGraphic);
                                        Units_ResearchCompletedGraphic->prepend(&UnitPointer->Building.ResearchCompletedGraphic);
                                    }
                                    Units_WwiseTransformSound->prepend(&UnitPointer->Building.WwiseTransformSoundID);
                                    Units_WwiseConstructionSound->prepend(&UnitPointer->Building.WwiseConstructionSoundID);
                                }
                            }
                        }
                    }
                }
                case 70:
                {
                    for(size_t loop = 0; loop < 3; ++loop)
                    {
                        Units_CostType[loop]->prepend(&UnitPointer->Creatable.ResourceCosts[loop].Type);
                        Units_CostAmount[loop]->prepend(&UnitPointer->Creatable.ResourceCosts[loop].Amount);
                        Units_CostUsed[loop]->prepend(&UnitPointer->Creatable.ResourceCosts[loop].Flag);
                    }
                    Units_TrainTime->prepend(&UnitPointer->Creatable.TrainTime);
                    Units_TrainLocationID->prepend(&UnitPointer->Creatable.TrainLocationID);
                    Units_ButtonID->prepend(&UnitPointer->Creatable.ButtonID);
                    Units_DisplayedPierceArmour->prepend(&UnitPointer->Creatable.DisplayedPierceArmour);
                    if(GenieVersion >= genie::GV_AoKE3)
                    {
                        Units_RearAttackModifier->prepend(&UnitPointer->Creatable.RearAttackModifier);
                        Units_FlankAttackModifier->prepend(&UnitPointer->Creatable.FlankAttackModifier);
                        Units_CreatableType->prepend(&UnitPointer->Creatable.CreatableType);
                        Units_MissileCount->prepend(&UnitPointer->Creatable.TotalProjectiles);
                        Units_MissileDuplicationCount->prepend(&UnitPointer->Creatable.MaxTotalProjectiles);
                        for(size_t loop = 0; loop < 3; ++loop)
                        {
                            Units_AttackMissileDuplicationSpawning[loop]->prepend(&UnitPointer->Creatable.ProjectileSpawningArea[loop]);
                        }
                        Units_AttackMissileDuplicationUnit->prepend(&UnitPointer->Creatable.SecondaryProjectileUnit);
                        if(CopyGraphics || vecCiv == 0)
                        {
                            Units_ChargingGraphic->prepend(&UnitPointer->Creatable.SpecialGraphic);
                        }
                        Units_ChargingMode->prepend(&UnitPointer->Creatable.SpecialAbility);
                        if(GenieVersion >= genie::GV_AoKB)
                        {
                            Units_HeroMode->prepend(&UnitPointer->Creatable.HeroMode);
                            if(CopyGraphics || vecCiv == 0)
                            {
                                Units_GarrisonGraphic->prepend(&UnitPointer->Creatable.GarrisonGraphic);
                                if(GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
                                {
                                    Units_SpawningGraphic->prepend(&UnitPointer->Creatable.SpawningGraphic);
                                    Units_UpgradeGraphic->prepend(&UnitPointer->Creatable.UpgradeGraphic);
                                    Units_HeroGlowGraphic->prepend(&UnitPointer->Creatable.HeroGlowGraphic);
                                }
                            }
                            if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
                            {
                                Units_MaxCharge->prepend(&UnitPointer->Creatable.MaxCharge);
                                Units_RechargeRate->prepend(&UnitPointer->Creatable.RechargeRate);
                                Units_ChargeEvent->prepend(&UnitPointer->Creatable.ChargeEvent);
                                Units_ChargeType->prepend(&UnitPointer->Creatable.ChargeType);
                                Units_MinConversionTimeMod->prepend(&UnitPointer->Creatable.MinConversionTimeMod);
                                Units_MaxConversionTimeMod->prepend(&UnitPointer->Creatable.MaxConversionTimeMod);
                                Units_ConversionChanceMod->prepend(&UnitPointer->Creatable.ConversionChanceMod);
                            }
                        }
                    }
                }
                case 60:
                case 50:
                {
                    Units_BaseArmor->prepend(&UnitPointer->Type50.BaseArmor);
                    Units_DefenseTerrainBonus->prepend(&UnitPointer->Type50.DefenseTerrainBonus);
                    Units_MaxRange->prepend(&UnitPointer->Type50.MaxRange);
                    Units_BlastWidth->prepend(&UnitPointer->Type50.BlastWidth);
                    Units_ReloadTime->prepend(&UnitPointer->Type50.ReloadTime);
                    Units_ProjectileUnitID->prepend(&UnitPointer->Type50.ProjectileUnitID);
                    Units_AccuracyPercent->prepend(&UnitPointer->Type50.AccuracyPercent);
                    Units_TowerMode->prepend(&UnitPointer->Type50.BreakOffCombat);
                    Units_Delay->prepend(&UnitPointer->Type50.FrameDelay);
                    for(size_t loop = 0; loop < 3; ++loop)
                    {
                        Units_GraphicDisplacement[loop]->prepend(&UnitPointer->Type50.GraphicDisplacement[loop]);
                    }
                    Units_BlastAttackLevel->prepend(&UnitPointer->Type50.BlastAttackLevel);
                    Units_MinRange->prepend(&UnitPointer->Type50.MinRange);
                    if(CopyGraphics || vecCiv == 0)
                    {
                        Units_AttackGraphic->prepend(&UnitPointer->Type50.AttackGraphic);
                    }
                    Units_DisplayedMeleeArmour->prepend(&UnitPointer->Type50.DisplayedMeleeArmour);
                    Units_DisplayedAttack->prepend(&UnitPointer->Type50.DisplayedAttack);
                    Units_DisplayedRange->prepend(&UnitPointer->Type50.DisplayedRange);
                    Units_DisplayedReloadTime->prepend(&UnitPointer->Type50.DisplayedReloadTime);
                    if(GenieVersion >= genie::GV_AoKB)
                    {
                        Units_AccuracyDispersion->prepend(&UnitPointer->Type50.AccuracyDispersion);
                        if(GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
                        {
                            Units_BonusDamageResistance->prepend(&UnitPointer->Type50.BonusDamageResistance);
                            Units_BlastDamage->prepend(&UnitPointer->Type50.BlastDamage);
                        }
                    }
                }
                case 40:
                {
                    Units_DefaultTaskID->prepend(&UnitPointer->Bird.DefaultTaskID);
                    Units_SearchRadius->prepend(&UnitPointer->Bird.SearchRadius);
                    Units_WorkRate->prepend(&UnitPointer->Bird.WorkRate);
                    Units_TaskSwapGroup->prepend(&UnitPointer->Bird.TaskSwapGroup);
                    Units_AttackSound->prepend(&UnitPointer->Bird.AttackSound);
                    Units_MoveSound->prepend(&UnitPointer->Bird.MoveSound);
                    Units_RunPattern->prepend(&UnitPointer->Bird.RunPattern);
                    if(GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
                    {
                        Units_WwiseAttackSound->prepend(&UnitPointer->Bird.WwiseAttackSoundID);
                        Units_WwiseMoveSound->prepend(&UnitPointer->Bird.WwiseMoveSoundID);
                    }
                }
                case 30:
                {
                    if(CopyGraphics || vecCiv == 0)
                    {
                        Units_WalkingGraphic[0]->prepend(&UnitPointer->DeadFish.WalkingGraphic);
                        Units_WalkingGraphic[1]->prepend(&UnitPointer->DeadFish.RunningGraphic);
                    }
                    Units_RotationSpeed->prepend(&UnitPointer->DeadFish.RotationSpeed);
                    Units_SizeClass->prepend(&UnitPointer->DeadFish.OldSizeClass);
                    Units_TrackingUnit->prepend(&UnitPointer->DeadFish.TrackingUnit);
                    Units_TrackingUnitMode->prepend(&UnitPointer->DeadFish.TrackingUnitMode);
                    Units_TrackingUnitDensity->prepend(&UnitPointer->DeadFish.TrackingUnitDensity);
                    Units_MoveAlgorithm->prepend(&UnitPointer->DeadFish.OldMoveAlgorithm);
                    if(GenieVersion >= genie::GV_AoKB)
                    {
                        Units_RotationAngles[0]->prepend(&UnitPointer->DeadFish.TurnRadius);
                        Units_RotationAngles[1]->prepend(&UnitPointer->DeadFish.TurnRadiusSpeed);
                        Units_RotationAngles[2]->prepend(&UnitPointer->DeadFish.MaxYawPerSecondMoving);
                        Units_RotationAngles[3]->prepend(&UnitPointer->DeadFish.StationaryYawRevolutionTime);
                        Units_RotationAngles[4]->prepend(&UnitPointer->DeadFish.MaxYawPerSecondStationary);
                        if(GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
                        {
                            Units_MinCollisionSizeMultiplier->prepend(&UnitPointer->DeadFish.MinCollisionSizeMultiplier);
                        }
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
                    Units_SizeRadius[0]->prepend(&UnitPointer->CollisionSize.x);
                    Units_SizeRadius[1]->prepend(&UnitPointer->CollisionSize.y);
                    Units_SizeRadius[2]->prepend(&UnitPointer->CollisionSize.z);
                    Units_TrainSound->prepend(&UnitPointer->TrainSound);
                    Units_DeadUnitID->prepend(&UnitPointer->DeadUnitID);
                    Units_SortNumber->prepend(&UnitPointer->SortNumber);
                    Units_CanBeBuiltOn->prepend(&UnitPointer->CanBeBuiltOn);
                    Units_HideInEditor->prepend(&UnitPointer->HideInEditor);
                    Units_PlacementSideTerrain[0]->prepend(&UnitPointer->PlacementSideTerrain.first);
                    Units_PlacementSideTerrain[1]->prepend(&UnitPointer->PlacementSideTerrain.second);
                    Units_PlacementTerrain[0]->prepend(&UnitPointer->PlacementTerrain.first);
                    Units_PlacementTerrain[1]->prepend(&UnitPointer->PlacementTerrain.second);
                    Units_ClearanceSize[0]->prepend(&UnitPointer->ClearanceSize.first);
                    Units_ClearanceSize[1]->prepend(&UnitPointer->ClearanceSize.second);
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
                    Units_Enabled->prepend(&UnitPointer->Enabled);
                    Units_InterfaceKind->prepend(&UnitPointer->InterfaceKind);
                    Units_MultipleAttributeMode->prepend(&UnitPointer->MultipleAttributeMode);
                    Units_MinimapColor->prepend(&UnitPointer->MinimapColor);
                    Units_LanguageDLLHelp->prepend(&UnitPointer->LanguageDLLHelp);
                    Units_LanguageDLLHotKeyText->prepend(&UnitPointer->LanguageDLLHotKeyText);
                    Units_HotKey->prepend(&UnitPointer->HotKey);
                    Units_Recyclable->prepend(&UnitPointer->Recyclable);
                    Units_TrackAsResource->prepend(&UnitPointer->EnableAutoGather);
                    Units_CreateDoppelgangerOnDeath->prepend(&UnitPointer->CreateDoppelgangerOnDeath);
                    Units_ResourceGroup->prepend(&UnitPointer->ResourceGatherGroup);
                    Units_SelectionRadius[0]->prepend(&UnitPointer->OutlineSize.x);
                    Units_SelectionRadius[1]->prepend(&UnitPointer->OutlineSize.y);
                    Units_SelectionRadius[2]->prepend(&UnitPointer->OutlineSize.z);
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
                        ResourceStorage_Mode[loop]->prepend(&UnitPointer->ResourceStorages[loop].Flag);
                    }
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
                                {
                                    Units_StandingGraphic[1]->prepend(&UnitPointer->StandingGraphic.second);
                                }
                                if(GenieVersion >= genie::GV_AoK)
                                {
                                    Units_Disabled->prepend(&UnitPointer->Disabled);
                                    if(GenieVersion >= genie::GV_TC)
                                    {
                                        Units_Trait->prepend(&UnitPointer->Trait);
                                        Units_Civ->prepend(&UnitPointer->Civilization);
                                        Units_Nothing->prepend(&UnitPointer->Nothing);
                                        if(GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
                                        {
                                            Units_WwiseTrainSound->prepend(&UnitPointer->WwiseTrainSoundID);
                                            Units_WwiseDamageSound->prepend(&UnitPointer->WwiseDamageSoundID);
                                            Units_WwiseSelectionSound->prepend(&UnitPointer->WwiseSelectionSoundID);
                                            Units_WwiseDyingSound->prepend(&UnitPointer->WwiseDyingSoundID);
                                            Units_BloodUnitID->prepend(&UnitPointer->BloodUnitID);
                                        }
                                        else if(GenieVersion >= genie::GV_SWGB)
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
                }
            }
            if(unitType == 60)
            {
                Units_ProjectileType->prepend(&UnitPointer->Projectile.ProjectileType);
                Units_SmartMode->prepend(&UnitPointer->Projectile.SmartMode);
                Units_HitMode->prepend(&UnitPointer->Projectile.HitMode);
                Units_VanishMode->prepend(&UnitPointer->Projectile.VanishMode);
                Units_AreaEffectSpecials->prepend(&UnitPointer->Projectile.AreaEffectSpecials);
                Units_ProjectileArc->prepend(&UnitPointer->Projectile.ProjectileArc);
            }
        }
    }
    SetStatusText(wxString::Format("Civilization: %d    Selections: %zu    Selected unit: %d",
        UnitCivID, selections, selections > 0 ? UnitIDs.front() : -1), 0);

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
            std::string newLabel = " ( ", aste = "° ";
            const float closure = 57.2957802f;

            #define UGLY_CODE if(angle == 0x80000000) newLabel += "max" + aste;\
            else newLabel += lexical_cast<std::string>(angle) + aste;

            int angle = UnitPointer->DeadFish.TurnRadius * closure; UGLY_CODE
            angle = UnitPointer->DeadFish.TurnRadiusSpeed * closure; UGLY_CODE
            angle = UnitPointer->DeadFish.MaxYawPerSecondMoving * closure; UGLY_CODE
            angle = UnitPointer->DeadFish.StationaryYawRevolutionTime * closure; UGLY_CODE
            angle = UnitPointer->DeadFish.MaxYawPerSecondStationary * closure; UGLY_CODE

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
            if(GenieVersion >= genie::GV_CC) set0 = 53240;
            iconSLP.slpID = set0 + dataset->Civs[UnitCivID].IconSet;
        }
        else if(GenieVersion >= genie::GV_CC)
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
        museum.reload();
    }
    else
    {
        visibleUnitCiv->SetLabel("None");
        iconSLP.slpID = museum.datID = -1;
    }
    Units_DLL_LanguageName->SetLabel(TranslatedText(Units_DLL_LanguageName->index, 64));
    Units_DLL_LanguageCreation->SetLabel(TranslatedText(Units_DLL_LanguageCreation->index, 64));
    Units_DLL_LanguageHelp->SetLabel(TranslatedText(Units_DLL_LanguageHelp->index, 512));
    Units_LanguageDLLConverter[0]->SetLabel(lexical_cast<std::string>(Units_DLL_LanguageHelp->index));
    Units_DLL_LanguageHKText->SetLabel(TranslatedText(Units_DLL_LanguageHKText->index, 64));
    Units_LanguageDLLConverter[1]->SetLabel(lexical_cast<std::string>(Units_DLL_LanguageHKText->index));
    Units_DLL_HotKey4->SetLabel(TranslatedText(Units_DLL_HotKey4->index, 16));

    Units_Type_ComboBox->Enable(showUnitData);
    Units_DLL_LanguageName->Enable(showUnitData);
    Units_DLL_LanguageCreation->Enable(showUnitData);
    Units_DLL_LanguageHelp->Enable(showUnitData);
    Units_DLL_LanguageHKText->Enable(showUnitData);
    Units_DLL_HotKey4->Enable(showUnitData);
    Units_LanguageDLLConverter[0]->Enable(showUnitData);
    Units_LanguageDLLConverter[1]->Enable(showUnitData);

    if (selections > 0)
    {
        // Don't count disabled units anymore.
        for (size_t loop = SelectedCivs.size(); loop-- > 0;)
        {
            if (dataset->Civs[SelectedCivs[loop]].Units.size() <= UnitIDs.front() ||
                dataset->Civs[SelectedCivs[loop]].UnitPointers[UnitIDs.front()] == 0)
            {
                SelectedCivs.erase(SelectedCivs.begin() + loop);
            }
        }
    }
    else
    {
        SelectedCivs.clear();
    }

    ListUnitDamageGraphics();
    ListUnitAttacks();
    ListUnitArmors();
    // AoK, TC, SWGB or CC
    if (selections > 0 && GenieVersion >= genie::GV_AoK && (GenieVersion < genie::GV_C15 || GenieVersion > genie::GV_LatestDE2))
    {
        genie::UnitHeader * UnitHeadPointer;
        for(size_t sel = selections; sel--> 0;)
        {
            UnitHeadPointer = &dataset->UnitHeaders[UnitIDs[sel]];

            Units_Exists->prepend(&UnitHeadPointer->Exists);
        }

        Units_UnitHeads_Name->SetLabel(" "+lexical_cast<std::string>(UnitIDs.front())+" - "+GetUnitName(UnitIDs.front(), 0));
    }
    else    // AoE or RoR
    {
        Units_UnitHeads_Name->SetLabel("");
    }
    ListUnitCommands();
    ListUnitDropSites();

    setbearing = 1u;
    for (AGETextCtrl *box : uiGroupUnit) box->update();
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
    if(iconSLP.bitmap.IsOk())
    dc.DrawBitmap(iconSLP.bitmap, 0, 0, true);
    else dc.DrawLabel("!SLP/frame " + FormatInt(iconSLP.slpID), wxNullBitmap, wxRect(0, 0, 100, 40));
}

int AGE_Frame::loadChosenGraphic(unsigned int unitID)
{
    genie::Unit *unit = &dataset->Civs[UnitCivID].Units[unitID];
    if(slp_unit_actions->GetSelection() && CommandIDs.size())
    {
        genie::Task *action = 0;
        if(GenieVersion >= genie::GV_AoK && (GenieVersion < genie::GV_C15 || GenieVersion > genie::GV_LatestDE2))
        {
            if(CommandIDs.front() < dataset->UnitHeaders[unitID].TaskList.size())
            action = &dataset->UnitHeaders[unitID].TaskList[CommandIDs.front()];
        }
        else
        {
            if(CommandIDs.front() < unit->Bird.TaskList.size())
            action = &unit->Bird.TaskList[CommandIDs.front()];
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
        case 4: return unit->DeadFish.WalkingGraphic;
        case 5: return unit->DeadFish.RunningGraphic;
        case 6: return unit->Building.ConstructionGraphicID;
        case 7: return unit->Type50.AttackGraphic;
        default: return -1;
    }
}

void AGE_Frame::AddAnnexAndStackGraphics(unsigned int unitID, int offsetX, int offsetY, int apply)
{
    if(unitID >= dataset->Civs[UnitCivID].Units.size()) return;
    unsigned unitGraphic = static_cast<unsigned>(-1);
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
    if(has_base) museum.angles = std::max(museum.angles, baseSLP.angles);
    if(dataset->Graphics[unitGraphic].Deltas.size())
    for(genie::GraphicDelta const &delta: dataset->Graphics[unitGraphic].Deltas)
    {
        AGE_SLP art;
        if(delta.GraphicID < dataset->Graphics.size())
        {
            if(initArt(art, delta.GraphicID))
            {
                museum.angles = std::max(museum.angles, art.angles);
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
        museum.deltas.emplace(std::move(std::make_pair(offsetY, std::move(art))));
    }
    else if(has_base)
    {
        baseSLP.xdelta = offsetX;
        baseSLP.ydelta = offsetY;
        museum.deltas.emplace(std::move(std::make_pair(offsetY, std::move(baseSLP))));
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
        store.DestructionGraphicID = dataset->Civs[civ].Units[unit].Building.DestructionGraphicID;
        store.DestructionRubbleGraphicID = dataset->Civs[civ].Units[unit].Building.DestructionRubbleGraphicID;
        store.ResearchingGraphic = dataset->Civs[civ].Units[unit].Building.ResearchingGraphic;
        store.ResearchCompletedGraphic = dataset->Civs[civ].Units[unit].Building.ResearchCompletedGraphic;
        case 70:
        store.GarrisonGraphic = dataset->Civs[civ].Units[unit].Creatable.GarrisonGraphic;
        store.SpecialGraphic = dataset->Civs[civ].Units[unit].Creatable.SpecialGraphic;
        store.SpawningGraphic = dataset->Civs[civ].Units[unit].Creatable.SpawningGraphic;
        store.UpgradeGraphic = dataset->Civs[civ].Units[unit].Creatable.UpgradeGraphic;
        store.HeroGlowGraphic = dataset->Civs[civ].Units[unit].Creatable.HeroGlowGraphic;
        case 60:
        case 50:
        store.AttackGraphic = dataset->Civs[civ].Units[unit].Type50.AttackGraphic;
        case 40:
        case 30:
        store.WalkingGraphic = dataset->Civs[civ].Units[unit].DeadFish.WalkingGraphic;
        store.RunningGraphic = dataset->Civs[civ].Units[unit].DeadFish.RunningGraphic;
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
        if(GenieVersion >= genie::GV_AoK && (GenieVersion < genie::GV_C15 || GenieVersion > genie::GV_LatestDE2))
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
                            dataset->UnitHeaders[CorrectID(OneOnOne, loop)].TaskList = copies.Dat.UnitCopies[civ][loop].Bird.TaskList;
                            break;
                        }
                    }
                }
            }
            else
            wxMessageBox("Please select All civs from the bottom!", "Ouch!");
        }
    }
    else if(GenieVersion < genie::GV_AoK || GenieVersion >= genie::GV_C15 && GenieVersion <= genie::GV_LatestDE2) // Paste from AoK+ to AoE
    {
        for(size_t loop = 0; loop < copies.UnitHeader.size(); ++loop)
        {
            for(short civ = 0; civ < dataset->Civs.size(); ++civ)
            {
                if(dataset->Civs[civ].UnitPointers[CorrectID(OneOnOne, loop)] != 0)
                dataset->Civs[civ].Units[CorrectID(OneOnOne, loop)].Bird.TaskList = copies.UnitHeader[loop].TaskList;
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
        dataset->Civs[civ].Units[unit].Building.DestructionGraphicID = store.DestructionGraphicID;
        dataset->Civs[civ].Units[unit].Building.DestructionRubbleGraphicID = store.DestructionRubbleGraphicID;
        dataset->Civs[civ].Units[unit].Building.ResearchingGraphic = store.ResearchingGraphic;
        dataset->Civs[civ].Units[unit].Building.ResearchCompletedGraphic = store.ResearchCompletedGraphic;
        case 70:
        dataset->Civs[civ].Units[unit].Creatable.GarrisonGraphic = store.GarrisonGraphic;
        dataset->Civs[civ].Units[unit].Creatable.SpecialGraphic = store.SpecialGraphic;
        dataset->Civs[civ].Units[unit].Creatable.SpawningGraphic = store.SpawningGraphic;
        dataset->Civs[civ].Units[unit].Creatable.UpgradeGraphic = store.UpgradeGraphic;
        dataset->Civs[civ].Units[unit].Creatable.HeroGlowGraphic = store.HeroGlowGraphic;
        case 60:
        case 50:
        dataset->Civs[civ].Units[unit].Type50.AttackGraphic = store.AttackGraphic;
        case 40:
        case 30:
        dataset->Civs[civ].Units[unit].DeadFish.WalkingGraphic = store.WalkingGraphic;
        dataset->Civs[civ].Units[unit].DeadFish.RunningGraphic = store.RunningGraphic;
    }
}

//  SubVectors

wxString AGE_Frame::GetUnitDamageGraphicName(int index)
{
    return lexical_cast<std::string>((short)dataset->Civs[UnitCivID].Units[UnitIDs.front()].DamageGraphics[index].DamagePercent)
    +" % - ID: "+lexical_cast<std::string>(dataset->Civs[UnitCivID].Units[UnitIDs.front()].DamageGraphics[index].GraphicID);
}

void AGE_Frame::OnUnitDamageGraphicsSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
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
    size_t selections = Units_DamageGraphics_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    for (AGETextCtrl *box : uiGroupUnitDmgGraphic) box->clear();
    if(selections > 0)
    {
        getSelectedItems(selections, Units_DamageGraphics_ListV, DamageGraphicIDs);
        // This and attacks/armors/commands need a lot of thinking.

        bool showWarning = false;
        wxString warning = "Damage graphic count of civs\n";
        genie::unit::DamageGraphic * DamageGraphicPointer;
        for(size_t sel = selections; sel--> 0;)
        {
            for(short vecCiv = (CopyGraphics) ? SelectedCivs.size() : 1; vecCiv--> 0;)
            {
                if(sel == 0 && dataset->Civs[SelectedCivs[vecCiv]].Units[UnitIDs.front()].DamageGraphics.size() != dataset->Civs[UnitCivID].Units[UnitIDs.front()].DamageGraphics.size())
                {
                    warning.Append(lexical_cast<std::string>(SelectedCivs[vecCiv])+" ");
                    showWarning = true;
                }
                DamageGraphicPointer = &dataset->Civs[SelectedCivs[vecCiv]].Units[UnitIDs.front()].DamageGraphics[DamageGraphicIDs[sel]];

                DamageGraphics_GraphicID->prepend(&DamageGraphicPointer->GraphicID);
                DamageGraphics_DamagePercent->prepend(&DamageGraphicPointer->DamagePercent);
                DamageGraphics_ApplyMode->prepend(&DamageGraphicPointer->ApplyMode);
            }
        }
        if(showWarning)
        {
            warning.Append("\ndiffers from civ "+lexical_cast<std::string>(UnitCivID));
            wxMessageBox(warning);
        }
    }
    for (AGETextCtrl *box : uiGroupUnitDmgGraphic) box->update();
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
    How2List = ListMode::ADD;
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
    How2List = ListMode::INSNEW;
    ListUnitDamageGraphics();
}

void AGE_Frame::OnUnitDamageGraphicsDelete(wxCommandEvent &event)
{
    size_t selections = Units_DamageGraphics_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    for(short civ = 0; civ < dataset->Civs.size(); ++civ)
    {
        if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] != 0)
        if(dataset->Civs[civ].Units[UnitIDs.front()].DamageGraphics.size())
        DeleteFromList(dataset->Civs[civ].Units[UnitIDs.front()].DamageGraphics, DamageGraphicIDs);
    }
    ListUnitDamageGraphics();
}

void AGE_Frame::OnUnitDamageGraphicsCopy(wxCommandEvent &event)
{
    if(!Units_DamageGraphics_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    if (Units_SpecialCopy_Civs->GetValue())
    {
        copies.Dat.AllCivs |= 0x10;
    }
    else copies.Dat.AllCivs &= ~0x10;
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

void AGE_Frame::OnUnitDropSitesSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
    ListUnitDropSites();
}

void AGE_Frame::ListUnitDropSites()
{
    InitSearch(Units_DropSites_Search->GetValue().MakeLower(), Units_DropSites_Search_R->GetValue().MakeLower());

    Units_DropSites_ListV->Sweep();

    if (Units_ListV->GetSelectedCount()
        && dataset->Civs[UnitCivID].UnitPointers[UnitIDs.front()] != 0
        && dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type >= 40
        && dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type <= 80)
    {
        Units_DropSites_Add->Enable(true);
        for (size_t loop = 0; loop < dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.DropSites.size(); ++loop)
        {
            wxString Name = FormatInt(loop) + " - " + GetUnitLineUnitName(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.DropSites[loop]);
            if (SearchMatches(" " + Name.Lower() + " "))
            {
                Units_DropSites_ListV->names.Add(Name);
                Units_DropSites_ListV->indexes.push_back(loop);
            }
        }
    }
    else
    {
        Units_DropSites_Add->Enable(false);
    }
    RefreshList(Units_DropSites_ListV, &DropSiteIDs);

    wxCommandEvent e;
    OnUnitDropSiteSelect(e);
}

void AGE_Frame::OnUnitDropSiteSelect(wxCommandEvent &event)
{
    size_t selections = Units_DropSites_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    DropSites_UnitID->clear();
    if (selections > 0)
    {
        getSelectedItems(selections, Units_DropSites_ListV, DropSiteIDs);

        bool showWarning = false;
        wxString warning = "Drop site count of civs\n";
        short * DropSitePointer;
        for (size_t sel = selections; sel-- > 0;)
        {
            for (short vecCiv = SelectedCivs.size(); vecCiv-- > 0;)
            {
                if (sel == 0 && dataset->Civs[SelectedCivs[vecCiv]].Units[UnitIDs.front()].Bird.DropSites.size() != dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.DropSites.size())
                {
                    warning.Append(lexical_cast<std::string>(SelectedCivs[vecCiv]) + " ");
                    showWarning = true;
                }
                DropSitePointer = &dataset->Civs[SelectedCivs[vecCiv]].Units[UnitIDs.front()].Bird.DropSites[DropSiteIDs[sel]];
                DropSites_UnitID->prepend(DropSitePointer);
            }
        }
        if (showWarning)
        {
            warning.Append("\ndiffers from civ " + lexical_cast<std::string>(UnitCivID));
            wxMessageBox(warning);
        }
    }
    DropSites_UnitID->update();
}

wxString AGE_Frame::GetUnitAttackName(int index)
{
    return "Amount: "+lexical_cast<std::string>(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type50.Attacks[index].Amount)
    +" - Class "+lexical_cast<std::string>(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type50.Attacks[index].Class);
}

void AGE_Frame::OnUnitAttacksSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
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
    size_t selections = Units_Attacks_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    Attacks_Class->clear();
    Attacks_Amount->clear();
    if(selections > 0)
    {
        getSelectedItems(selections, Units_Attacks_ListV, AttackIDs);

        bool showWarning = false;
        wxString warning = "Attack count of civs\n";
        genie::unit::AttackOrArmor * AttackPointer;
        for(size_t sel = selections; sel--> 0;)
        {
            for(short vecCiv = SelectedCivs.size(); vecCiv--> 0;)
            {
                if(sel == 0 && dataset->Civs[SelectedCivs[vecCiv]].Units[UnitIDs.front()].Type50.Attacks.size() != dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type50.Attacks.size())
                {
                    warning.Append(lexical_cast<std::string>(SelectedCivs[vecCiv])+" ");
                    showWarning = true;
                }
                AttackPointer = &dataset->Civs[SelectedCivs[vecCiv]].Units[UnitIDs.front()].Type50.Attacks[AttackIDs[sel]];

                Attacks_Class->prepend(&AttackPointer->Class);
                Attacks_Amount->prepend(&AttackPointer->Amount);
            }
        }
        if(showWarning)
        {
            warning.Append("\ndiffers from civ "+lexical_cast<std::string>(UnitCivID));
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
    How2List = ListMode::ADD;
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
    How2List = ListMode::INSNEW;
    ListUnitAttacks();
}

void AGE_Frame::OnUnitAttacksDelete(wxCommandEvent &event)
{
    size_t selections = Units_Attacks_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    for(short civ = 0; civ < dataset->Civs.size(); ++civ)
    {
        if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] != 0)
        if(dataset->Civs[civ].Units[UnitIDs.front()].Type50.Attacks.size())
        DeleteFromList(dataset->Civs[civ].Units[UnitIDs.front()].Type50.Attacks, AttackIDs);
    }
    ListUnitAttacks();
}

void AGE_Frame::OnUnitAttacksCopy(wxCommandEvent &event)
{
    if(!Units_Attacks_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    if (Units_SpecialCopy_Civs->GetValue())
    {
        copies.Dat.AllCivs |= 0x20;
    }
    else copies.Dat.AllCivs &= ~0x20;
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

wxString AGE_Frame::GetUnitArmorName(int index)
{
    return "Amount: "+lexical_cast<std::string>(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type50.Armours[index].Amount)
    +" - Class "+lexical_cast<std::string>(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type50.Armours[index].Class);
}

void AGE_Frame::OnUnitArmorsSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
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
    size_t selections = Units_Armors_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    Armors_Class->clear();
    Armors_Amount->clear();
    if(selections > 0)
    {
        getSelectedItems(selections, Units_Armors_ListV, ArmorIDs);

        bool showWarning = false;
        wxString warning = "Armor count of civs\n";
        genie::unit::AttackOrArmor * ArmorPointer;
        for(size_t sel = selections; sel--> 0;)
        {
            for(short vecCiv = SelectedCivs.size(); vecCiv--> 0;)
            {
                if(sel == 0 && dataset->Civs[SelectedCivs[vecCiv]].Units[UnitIDs.front()].Type50.Armours.size() != dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type50.Armours.size())
                {
                    warning.Append(lexical_cast<std::string>(SelectedCivs[vecCiv])+" ");
                    showWarning = true;
                }
                ArmorPointer = &dataset->Civs[SelectedCivs[vecCiv]].Units[UnitIDs.front()].Type50.Armours[ArmorIDs[sel]];

                Armors_Class->prepend(&ArmorPointer->Class);
                Armors_Amount->prepend(&ArmorPointer->Amount);
            }
        }
        if(showWarning)
        {
            warning.Append("\ndiffers from civ "+lexical_cast<std::string>(UnitCivID));
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
    How2List = ListMode::ADD;
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
    How2List = ListMode::INSNEW;
    ListUnitArmors();
}

void AGE_Frame::OnUnitArmorsDelete(wxCommandEvent &event)
{
    size_t selections = Units_Armors_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    for(short civ = 0; civ < dataset->Civs.size(); ++civ)
    {
        if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] != 0)
        if(dataset->Civs[civ].Units[UnitIDs.front()].Type50.Armours.size())
        DeleteFromList(dataset->Civs[civ].Units[UnitIDs.front()].Type50.Armours, ArmorIDs);
    }
    ListUnitArmors();
}

void AGE_Frame::OnUnitArmorsCopy(wxCommandEvent &event)
{
    if(!Units_Armors_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    if (Units_SpecialCopy_Civs->GetValue())
    {
        copies.Dat.AllCivs |= 0x40;
    }
    else copies.Dat.AllCivs &= ~0x40;
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

//  AoE/TC/SWGB/CC Unit TaskList

wxString AGE_Frame::GetUnitCommandName(int index)
{
    short CommandType = (GenieVersion >= genie::GV_AoK && (GenieVersion < genie::GV_C15 || GenieVersion > genie::GV_LatestDE2))
        ? dataset->UnitHeaders[UnitIDs.front()].TaskList[index].ActionType
        : dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.TaskList[index].ActionType;
    size_t taskNameId;
    switch(CommandType)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14: taskNameId = CommandType + 1; break;
        case 20:
        case 21: taskNameId = CommandType - 4; break;
        case 101:
        case 102:
        case 103:
        case 104:
        case 105:
        case 106:
        case 107:
        case 108:
        case 109:
        case 110:
        case 111: taskNameId = CommandType - 83; break;
        case 120:
        case 121:
        case 122:
        case 123:
        case 124:
        case 125: taskNameId = CommandType - 91; break;
        case 130:
        case 131:
        case 132:
        case 133:
        case 134:
        case 135:
        case 136: taskNameId = CommandType - 95; break;
        case 149:
        case 150:
        case 151:
        case 152:
        case 153:
        case 154:
        case 155: taskNameId = CommandType - 107; break;
        default: taskNameId = task_names.size();
    }
    if (taskNameId < task_names.size())
    {
        return task_names[taskNameId];
    }
    else
    {
        return "Unk. Type " + lexical_cast<std::string>(CommandType);
    }
}

void AGE_Frame::OnUnitCommandsSearch(wxCommandEvent &event)
{
    How2List = ListMode::SEARCH;
    ListUnitCommands();
}

void AGE_Frame::ListUnitCommands()
{
    InitSearch(Units_Tasks_Search->GetValue().MakeLower(), Units_Tasks_Search_R->GetValue().MakeLower());

    Units_Tasks_ListV->Sweep();
    action_names.Clear();
    action_names.Add("-1 - None");

    // AoK, TC, SWGB or CC
    if(GenieVersion >= genie::GV_AoK && (GenieVersion < genie::GV_C15 || GenieVersion > genie::GV_LatestDE2))
    {
        if(Units_ListV->GetSelectedCount())
        for(size_t loop = 0; loop < dataset->UnitHeaders[UnitIDs.front()].TaskList.size(); ++loop)
        {
            wxString Name = FormatInt(loop)+" - "+GetUnitCommandName(loop);
            if(dataset->UnitHeaders[UnitIDs.front()].TaskList[loop].ClassID != -1)
            Name += " class "+lexical_cast<std::string>(dataset->UnitHeaders[UnitIDs.front()].TaskList[loop].ClassID);
            else if(dataset->UnitHeaders[UnitIDs.front()].TaskList[loop].UnitID != -1)
            Name += " unit "+lexical_cast<std::string>(dataset->UnitHeaders[UnitIDs.front()].TaskList[loop].UnitID);
            if(SearchMatches(" " + Name.Lower() + " "))
            {
                Units_Tasks_ListV->names.Add(Name);
                Units_Tasks_ListV->indexes.push_back(loop);
            }
            action_names.Add(Name);
        }
    }
    else    // AoE or RoR or AoK DE
    {
        if(Units_ListV->GetSelectedCount()
        && dataset->Civs[UnitCivID].UnitPointers[UnitIDs.front()] != 0
        && dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type >= 40
        && dataset->Civs[UnitCivID].Units[UnitIDs.front()].Type <= 80)
        {
            Units_Tasks_Add->Enable(true);
            for(size_t loop = 0; loop < dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.TaskList.size(); ++loop)
            {
                wxString Name = FormatInt(loop)+" - "+GetUnitCommandName(loop);
                if(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.TaskList[loop].ClassID != -1)
                Name += " class "+lexical_cast<std::string>(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.TaskList[loop].ClassID);
                else if(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.TaskList[loop].UnitID != -1)
                Name += " unit "+lexical_cast<std::string>(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.TaskList[loop].UnitID);
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
    size_t selections = Units_Tasks_ListV->GetSelectedCount();
    wxBusyCursor WaitCursor;
    for (AGETextCtrl *box : uiGroupUnitTask)
    {
        box->clear();
    }
    Tasks_ID->clear();
    genie::Task *task_ptr = nullptr;
    if(selections > 0)
    {
        getSelectedItems(selections, Units_Tasks_ListV, CommandIDs);

        bool showWarning = false;
        bool uniqueTasks = (GenieVersion < genie::GV_AoK || GenieVersion >= genie::GV_C15 && GenieVersion <= genie::GV_LatestDE2);
        wxString warning = "Command count of civs\n";
        for(size_t sel = selections; sel--> 0;)
        {
            for(short vecCiv = uniqueTasks ? SelectedCivs.size() : 1; vecCiv--> 0;)
            {
                if(uniqueTasks)
                {
                    if(sel == 0 && dataset->Civs[SelectedCivs[vecCiv]].Units[UnitIDs.front()].Bird.TaskList.size() != dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.TaskList.size())
                    {
                        warning.Append(lexical_cast<std::string>(SelectedCivs[vecCiv])+" ");
                        showWarning = true;
                    }
                    task_ptr = &dataset->Civs[SelectedCivs[vecCiv]].Units[UnitIDs.front()].Bird.TaskList[CommandIDs[sel]];
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
                Tasks_Graphics[0]->prepend(&task_ptr->MovingGraphicID);
                Tasks_Graphics[1]->prepend(&task_ptr->ProceedingGraphicID);
                Tasks_Graphics[2]->prepend(&task_ptr->WorkingGraphicID);
                Tasks_Graphics[3]->prepend(&task_ptr->CarryingGraphicID);
                Tasks_Graphics[4]->prepend(&task_ptr->ResourceGatheringSoundID);
                Tasks_Graphics[5]->prepend(&task_ptr->ResourceDepositSoundID);
                if(GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
                {
                    Tasks_WwiseResourceGatheringSound->prepend(&task_ptr->WwiseResourceGatheringSoundID);
                    Tasks_WwiseResourceDepositSound->prepend(&task_ptr->WwiseResourceDepositSoundID);
                }
            }
            if(showWarning)
            {
                warning.Append("\ndiffers from civ "+lexical_cast<std::string>(UnitCivID));
                wxMessageBox(warning);
            }
        }
    }
    for (AGETextCtrl *box : uiGroupUnitTask)
    {
        box->update();
    }
    Tasks_ID->refill();
    if (task_ptr != nullptr)
    {
        if (task_ptr->ActionType >= 0 && task_ptr->ActionType <= 14)
        {
            Tasks_ActionType_ComboBox->SetChoice(task_ptr->ActionType);
        }
        else if (task_ptr->ActionType >= 20 && task_ptr->ActionType <= 21)
        {
            Tasks_ActionType_ComboBox->SetChoice(task_ptr->ActionType - 5);
        }
        else if (task_ptr->ActionType >= 101 && task_ptr->ActionType <= 111)
        {
            Tasks_ActionType_ComboBox->SetChoice(task_ptr->ActionType - 84);
        }
        else if (task_ptr->ActionType >= 120 && task_ptr->ActionType <= 125)
        {
            Tasks_ActionType_ComboBox->SetChoice(task_ptr->ActionType - 92);
        }
        else if (task_ptr->ActionType >= 130 && task_ptr->ActionType <= 136)
        {
            Tasks_ActionType_ComboBox->SetChoice(task_ptr->ActionType - 96);
        }
        else if (task_ptr->ActionType >= 149 && task_ptr->ActionType <= 155)
        {
            Tasks_ActionType_ComboBox->SetChoice(task_ptr->ActionType - 108);
        }
        else
        {
            Tasks_ActionType_ComboBox->SetChoice(-1);
        }
    }
    wxCommandEvent E;
    OnChooseGraphic(E);
}

void AGE_Frame::OnUnitCommandsAdd(wxCommandEvent &event)
{
    if(!Units_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    genie::Task Temp;
    Temp.setGameVersion(GenieVersion);
    if(GenieVersion >= genie::GV_AoK && (GenieVersion < genie::GV_C15 || GenieVersion > genie::GV_LatestDE2))
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
                dataset->Civs[loop].Units[UnitIDs.front()].Bird.TaskList.push_back(Temp);
                dataset->Civs[loop].Units[UnitIDs.front()].Bird.TaskList[dataset->Civs.front().Units[UnitIDs.front()].Bird.TaskList.size()-1].ID = (int16_t)(dataset->Civs.front().Units[UnitIDs.front()].Bird.TaskList.size()-1); // ID Fix
            }
        }
    }
    How2List = ListMode::ADD;
    ListUnitCommands();
}

void AGE_Frame::OnUnitCommandsInsert(wxCommandEvent &event)
{
    if(!Units_Tasks_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    genie::Task Temp;
    Temp.setGameVersion(GenieVersion);
    if(GenieVersion >= genie::GV_AoK && (GenieVersion < genie::GV_C15 || GenieVersion > genie::GV_LatestDE2))
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
                dataset->Civs[loop].Units[UnitIDs.front()].Bird.TaskList.insert(dataset->Civs[loop].Units[UnitIDs.front()].Bird.TaskList.begin() + CommandIDs.front(), Temp);
                for(size_t loop2 = CommandIDs.front();loop2 < dataset->Civs.front().Units[UnitIDs.front()].Bird.TaskList.size(); ++loop2) // ID Fix
                dataset->Civs[loop].Units[UnitIDs.front()].Bird.TaskList[loop2].ID = loop2;
            }
        }
    }
    How2List = ListMode::INSNEW;
    ListUnitCommands();
}

void AGE_Frame::OnUnitCommandsDelete(wxCommandEvent &event)
{
    size_t selections = Units_Tasks_ListV->GetSelectedCount();
    if (!selections) return;

    wxBusyCursor WaitCursor;
    if(GenieVersion >= genie::GV_AoK && (GenieVersion < genie::GV_C15 || GenieVersion > genie::GV_LatestDE2))
    {
        DeleteFromListIDFix(dataset->UnitHeaders[UnitIDs.front()].TaskList, CommandIDs);
    }
    else
    {
        for(short civ = 0; civ < dataset->Civs.size(); ++civ)
        {
            if(dataset->Civs[civ].UnitPointers[UnitIDs.front()] != 0)
            if(dataset->Civs[civ].Units[UnitIDs.front()].Bird.TaskList.size())
            {
                DeleteFromListIDFix(dataset->Civs[civ].Units[UnitIDs.front()].Bird.TaskList, CommandIDs);
            }
        }
    }
    ListUnitCommands();
}

void AGE_Frame::OnUnitCommandsCopy(wxCommandEvent &event)
{
    if(!Units_Tasks_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    if(GenieVersion >= genie::GV_AoK && (GenieVersion < genie::GV_C15 || GenieVersion > genie::GV_LatestDE2))
    {
        copies.Dat.AllCivs |= 0x80;
        copies.Dat.UnitCommandExists.resize(0);
        copies.Dat.UnitCommands.resize(1);
        CopyFromList(dataset->UnitHeaders[UnitIDs.front()].TaskList, CommandIDs, copies.Dat.UnitCommands.front());
        return;
    }
    if (Units_SpecialCopy_Civs->GetValue())
    {
        copies.Dat.AllCivs |= 0x80;
    }
    else copies.Dat.AllCivs &= ~0x80;
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
                CopyFromList(dataset->Civs[civ].Units[UnitIDs.front()].Bird.TaskList, CommandIDs, copies.Dat.UnitCommands[copy]); copy++;
            }
        }
        copies.Dat.UnitCommands.resize(CivCount);
    }
    else
    {
        CopyFromList(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.TaskList, CommandIDs, copies.Dat.UnitCommands.front());
    }
    Units_Tasks_ListV->SetFocus();
}

void AGE_Frame::OnUnitCommandsPaste(wxCommandEvent &event)
{
    if(!Units_Tasks_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    if(GenieVersion >= genie::GV_AoK && (GenieVersion < genie::GV_C15 || GenieVersion > genie::GV_LatestDE2))
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
                PasteToListIDFix(dataset->Civs[civ].Units[UnitIDs.front()].Bird.TaskList, CommandIDs, copies.Dat.UnitCommands[copy]); ++copy;
            }
            else
            {
                PasteToListIDFix(dataset->Civs[civ].Units[UnitIDs.front()].Bird.TaskList, CommandIDs, copies.Dat.UnitCommands.front());
            }
        }
    }
    else
    {
        PasteToListIDFix(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.TaskList, CommandIDs, copies.Dat.UnitCommands.front());
    }
    ListUnitCommands();
}

void AGE_Frame::OnUnitCommandsPasteInsert(wxCommandEvent &event)
{
    if(!Units_Tasks_ListV->GetSelectedCount()) return;

    wxBusyCursor WaitCursor;
    if(GenieVersion >= genie::GV_AoK && (GenieVersion < genie::GV_C15 || GenieVersion > genie::GV_LatestDE2))
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
                PasteInsertToListIDFix(dataset->Civs[civ].Units[UnitIDs.front()].Bird.TaskList, CommandIDs.front(), copies.Dat.UnitCommands[copy]); copy++;
            }
            else
            {
                PasteInsertToListIDFix(dataset->Civs[civ].Units[UnitIDs.front()].Bird.TaskList, CommandIDs.front(), copies.Dat.UnitCommands.front());
            }
        }
    }
    else
    {
        PasteInsertToListIDFix(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.TaskList, CommandIDs.front(), copies.Dat.UnitCommands.front());
    }
    ListUnitCommands();
}

void AGE_Frame::OnUnitCommandsCopyToUnits(wxCommandEvent &event)
{
    if(GenieVersion < genie::GV_AoK || GenieVersion >= genie::GV_C15 && GenieVersion <= genie::GV_LatestDE2)
    {
        for(short civ = 0; civ < dataset->Civs.size(); ++civ)
        for(size_t loop=1; loop < UnitIDs.size(); ++loop)
        {
            dataset->Civs[civ].Units[UnitIDs[loop]].Bird.TaskList = dataset->Civs[civ].Units[UnitIDs.front()].Bird.TaskList;
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
        DLLValue = lexical_cast<int32_t>(static_cast<wxTextCtrl*>(event.GetEventObject())->GetValue());
    }
    catch(const bad_lexical_cast&)
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

    Tab_Units = new ATabPage(TabBar_Main);

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
    Units_ListV = new ProperList(Tab_Units, ASize(200, 100));
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
    Units_Type = new NumberControl(CUByte, Tab_Units, this, &uiGroupUnit, false, AGETextCtrl::SMALL);
    Units_Type_ComboBox = new AGEComboBox(Tab_Units, &unit_type_names, AGETextCtrl::LARGE);
    Units_Class = new NumberControl(CShort, Tab_Units, this, &uiGroupUnit);
    Units_Class->SetToolTip("Determines many things and works in conjunction with other variables");
    Units_Class_ComboBox[0] = new LinkedComboBox(Tab_Units, Units_Class, &class_names);
    Units_Scroller = new AScrolled(Tab_Units);
    Units_ScrollSpace = new wxBoxSizer(wxVERTICAL);
    Units_TypeArea_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_LangDLLArea_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Language Files");
    Units_GraphicsArea_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Graphics");
    SolidText* autoCopyHelp = new SolidText(Units_Scroller, autoCopyHelpText);
    Units_GraphicsArea1_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_GraphicsArea4_Holder = new wxBoxSizer(wxVERTICAL);
    Units_GraphicsArea5_Holder = new wxFlexGridSizer(4, 5, 5);
    Units_StatsArea_Holder = new wxStaticBoxSizer(wxVERTICAL, Units_Scroller, "Statistics");
    Units_StatsArea1A_Sizer = new wxBoxSizer(wxHORIZONTAL);
    Units_StatsArea1B_Sizer = new wxBoxSizer(wxHORIZONTAL);
    Units_Garrison_Grid = new wxFlexGridSizer(3, 0, 5);
    Units_Resource_Grid = new wxFlexGridSizer(6, 0, 5);
    Units_Charge_Grid = new wxFlexGridSizer(4, 0, 5);
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
    Units_AM1_Grid = new wxFlexGridSizer(5, 5, 5);
    Units_AS_Holder = new wxBoxSizer(wxHORIZONTAL);
    Units_AS2_Holder = new wxBoxSizer(wxHORIZONTAL);
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
    TasksArea_Holder = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Tasks (Shared by all civilizations in legacy Age of Empires II and Star Wars Galactic Battlegrounds)");

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
    Units_SizeRadius_Holder = new wxBoxSizer(wxVERTICAL);
    Units_SizeRadius_Grid = new wxBoxSizer(wxHORIZONTAL);
    Units_MinCollisionSizeMultiplier_Holder = new wxBoxSizer(wxVERTICAL);
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
    for (wxBoxSizer *&sizer : Units_ResourceStorage_Holder)
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
    Units_TaskSwapGroup_Holder = new wxBoxSizer(wxVERTICAL);
    Units_AttackSound_Holder = new wxBoxSizer(wxVERTICAL);
    Units_MoveSound_Holder = new wxBoxSizer(wxVERTICAL);
    Units_RunPattern_Holder = new wxBoxSizer(wxVERTICAL);
    Units_Exists_Holder = new wxBoxSizer(wxVERTICAL);

//  Type 50+

    Units_BaseArmor_Holder = new wxBoxSizer(wxVERTICAL);
    Units_DefenseTerrainBonus_Holder = new wxBoxSizer(wxVERTICAL);
    Units_BonusDamageResistance_Holder = new wxBoxSizer(wxVERTICAL);
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
    Units_BlastDamage_Holder = new wxBoxSizer(wxVERTICAL);
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
    for (wxBoxSizer *&sizer : Unit_Cost_Sizers)
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
    Units_SpawningGraphic_Holder = new wxBoxSizer(wxVERTICAL);
    Units_UpgradeGraphic_Holder = new wxBoxSizer(wxVERTICAL);
    Units_HeroGlowGraphic_Holder = new wxBoxSizer(wxVERTICAL);

//  Type 80

    Units_ConstructionGraphicID_Holder = new wxBoxSizer(wxVERTICAL);
    Units_SnowGraphicID_Holder = new wxBoxSizer(wxVERTICAL);
    Units_DestructionGraphicID_Holder = new wxBoxSizer(wxVERTICAL);
    Units_DestructionRubbleGraphicID_Holder = new wxBoxSizer(wxVERTICAL);
    Units_ResearchingGraphic_Holder = new wxBoxSizer(wxVERTICAL);
    Units_ResearchCompletedGraphic_Holder = new wxBoxSizer(wxVERTICAL);
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
    Units_MinCollisionSizeMultiplier_Text = new SolidText(Units_Scroller, " Min CS Multiplier *");
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
    Units_BlastDefenseLevel_Text = new SolidText(Units_Scroller, " Blast Defense *");
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
    Units_TaskSwapGroup_Text = new SolidText(Units_Scroller, " Task Swap Group *");
    Units_AttackSound_Text = new SolidText(Units_Scroller, " Attack Sound");
    Units_MoveSound_Text = new SolidText(Units_Scroller, " Move Sound");
    Units_Exists_Text = new SolidText(Units_Scroller, " Exists");

//  Type 50+

    Units_BaseArmor_Text = new SolidText(Units_Scroller, " Base Armor *");
    Units_DefenseTerrainBonus_Text = new SolidText(Units_Scroller, " Terrain Defense Bonus *");
    Units_BonusDamageResistance_Text = new SolidText(Units_Scroller, " Bonus Damage Resist *");
    Units_MaxRange_Text = new SolidText(Units_Scroller, " Max Range");
    Units_BlastWidth_Text = new SolidText(Units_Scroller, " Blast Width *");
    Units_ReloadTime_Text = new SolidText(Units_Scroller, " Reload Time");
    Units_ProjectileUnitID_Text = new SolidText(Units_Scroller, " Projectile Unit");
    Units_AccuracyPercent_Text = new SolidText(Units_Scroller, " Accuracy Percent");
    Units_Delay_Text = new SolidText(Units_Scroller, " Frame Delay *");
    Units_GraphicDisplacement_Text = new SolidText(Units_Scroller, " Graphic Displacement XYZ *");
    Units_BlastAttackLevel_Text = new SolidText(Units_Scroller, " Blast Attack Level *");
    Units_BlastDamage_Text = new SolidText(Units_Scroller, " Blast Damage *");
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
    Units_SpawningGraphic_Text = new SolidText(Units_Scroller, " Spawning Graphic");
    Units_UpgradeGraphic_Text = new SolidText(Units_Scroller, " Upgrade Graphic");
    Units_HeroGlowGraphic_Text = new SolidText(Units_Scroller, " Hero Glow Graphic");
    Units_MaxCharge_Text = new SolidText(Units_Scroller, " Max Charge");
    Units_RechargeRate_Text = new SolidText(Units_Scroller, " Recharge Rate");
    Units_ChargeEvent_Text = new SolidText(Units_Scroller, " Charge Event *");
    Units_ChargeType_Text = new SolidText(Units_Scroller, " Charge Type *");
    Units_MinConversionTimeMod_Text = new SolidText(Units_Scroller, " Min Conv Time *");
    Units_MaxConversionTimeMod_Text = new SolidText(Units_Scroller, " Max Conv Time *");
    Units_ConversionChanceMod_Text = new SolidText(Units_Scroller, " Conv Chance *");

//  Type 80

    Units_ConstructionGraphicID_Text = new SolidText(Units_Scroller, " Construction Graphic");
    Units_SnowGraphicID_Text = new SolidText(Units_Scroller, " Snow Graphic");
    Units_DestructionGraphicID_Text = new SolidText(Units_Scroller, " Destruction Graphic");
    Units_DestructionRubbleGraphicID_Text = new SolidText(Units_Scroller, " Destruction Rubble Graphic");
    Units_ResearchingGraphic_Text = new SolidText(Units_Scroller, " Researching Graphic");
    Units_ResearchCompletedGraphic_Text = new SolidText(Units_Scroller, " Research Completed Graphic");
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

    Units_ID1 = new NumberControl(CShort, Tab_Units, this, nullptr, true, AGETextCtrl::SMALL);
    Units_CopyID = new NumberControl(CShort, Tab_Units, this, nullptr, true, AGETextCtrl::SMALL);
    Units_BaseID = new NumberControl(CShort, Tab_Units, this, nullptr, true, AGETextCtrl::SMALL);
    Units_TelemetryID = new NumberControl(CShort, Tab_Units, this, &uiGroupUnit);
    Units_Name = new StringControl(Tab_Units, this, &uiGroupUnit, maxStringlength, false);
    Units_Name2 = new StringControl(Tab_Units, this, &uiGroupUnit, maxStringlength, false);
    Units_LanguageDLLName = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit, false);
    Units_LanguageDLLName->SetToolTip("Usual Unit File Pattern for The Conquerors\nName: 5000-5999\n"
        "Creation: Name +1000\nHotkey: Name +11000\nHelp: Name +100000, in file Name +21000\n"
        "Hotkey Text: Name +150000, in file Name +10000\nTech tree: Name +9000");
    Units_DLL_LanguageName = new TextIndexControl(Units_Scroller, ASize(200, 25));
    Units_LanguageDLLCreation = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit, false);
    Units_DLL_LanguageCreation = new TextIndexControl(Units_Scroller, ASize(200, 25));
    Units_HotKey = new NumberControl(CLong, Units_Scroller, this, &uiGroupUnit, false);
    Units_HotKey->SetToolTip("10000 + Language File Creation (usually)");
    Units_DLL_HotKey4 = new TextIndexControl(Units_Scroller, ASize(200, 25));
    Units_LanguageDLLHelp = new NumberControl(CLong, Units_Scroller, this, &uiGroupUnit, false);
    Units_LanguageDLLHelp->SetToolTip("100000 + Language File Name\nThis is linked to the help text below");
    Units_LanguageDLLConverter[0] = new wxTextCtrl(Units_Scroller, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    Units_LanguageDLLConverter[0]->SetToolTip("Language help text in file\nHit enter to get the correction into dat file");
    Units_DLL_LanguageHelp = new TextIndexControl(Units_Scroller, ASize(610, 55));
    Units_LanguageDLLHotKeyText = new NumberControl(CLong, Units_Scroller, this, &uiGroupUnit, false);
    Units_LanguageDLLHotKeyText->SetToolTip("150000 + Language File Name\nThis seems to be used only in AoE (not RoR)\nThis language line has other purposes in SWGB and CC");
    Units_LanguageDLLConverter[1] = new wxTextCtrl(Units_Scroller, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    Units_LanguageDLLConverter[1]->SetToolTip("Language hotkey text in file\nHit enter to get the correction into dat file");
    Units_DLL_LanguageHKText = new TextIndexControl(Units_Scroller, ASize(610, 25));

    wxArrayString choices;
    choices.Add("Stand 1");
    choices.Add("Stand 2");
    choices.Add("Dying 1");
    choices.Add("Dying 2");
    choices.Add("Walk");
    choices.Add("Run");
    choices.Add("Build");
    choices.Add("Attack");
    slp_radio = new wxRadioBox(Units_Scroller, wxID_ANY, "Sprite view", wxDefaultPosition, wxDefaultSize, choices);
    slp_snow = new wxCheckBox(Units_Scroller, wxID_ANY, "Snow");
    slp_garrison = new wxCheckBox(Units_Scroller, wxID_ANY, "Housed");
    wxSizer *sizer_slp = new wxBoxSizer(wxHORIZONTAL);
    wxSizer *sizer_slp2 = new wxBoxSizer(wxVERTICAL);
    Units_DamageGraphics = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Damage Graphics");
    Units_DamageGraphics_ListArea = new wxBoxSizer(wxVERTICAL);
    Units_DamageGraphics_Search = new wxTextCtrl(Units_Scroller, wxID_ANY);
    Units_DamageGraphics_Search_R = new wxTextCtrl(Units_Scroller, wxID_ANY);
    Units_DamageGraphics_ListV = new ProperList(Units_Scroller, ASize(140, 100));
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
    DamageGraphics_GraphicID = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnitDmgGraphic, false);
    DamageGraphics_GraphicID_ComboBox = new LinkedComboBox(Units_Scroller, DamageGraphics_GraphicID, &graphic_names, false);
    GraphicComboBoxList.push_back(DamageGraphics_GraphicID_ComboBox);
    DamageGraphics_DamagePercent_Holder = new wxBoxSizer(wxVERTICAL);
    DamageGraphics_DamagePercent_Text = new SolidText(Units_Scroller, " Damage Percent");
    DamageGraphics_DamagePercent = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnitDmgGraphic, false);
    DamageGraphics_ApplyMode_Holder = new wxBoxSizer(wxVERTICAL);
    DamageGraphics_ApplyMode_Text = new SolidText(Units_Scroller, " Apply Mode *");
    DamageGraphics_ApplyMode = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnitDmgGraphic);
    DamageGraphics_ApplyMode->SetToolTip("0   Overlay (flames on buildings)\n1   Overlay randomly\n2   Replace graphics (damaged walls)");

    Units_IconID = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit, false, AGETextCtrl::SMALL);
    Units_IconID->SetToolTip("Download Turtle Pack from AoKH to add more than 127 icons.");
    Units_IconID_SLP = new APanel(Units_Scroller, ASize(55, 50));
    Units_IconAngle = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit, false, AGETextCtrl::SMALL);
    Units_IconAngle->SetToolTip("Effect attribute 17 changes this\n0   Default\n1+ Use icon from 2nd age etc\nIn AoE 1 can be used to set the unit\nhave icon graphics of later ages straight in stone age");
    Units_ChargingGraphic = new NumberControl(CLong, Units_Scroller, this, &uiGroupUnit, false);
    Units_ChargingGraphic->SetToolTip("Activates depending on special ability");
    Units_ChargingGraphic_ComboBox = new LinkedComboBox(Units_Scroller, Units_ChargingGraphic, &graphic_names, false);
    GraphicComboBoxList.push_back(Units_ChargingGraphic_ComboBox);
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Units_StandingGraphic[loop] = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit, false);
        Units_StandingGraphic[loop]->SetToolTip("Half of units in group use 1st,\nthe rest use 2nd");
        Units_StandingGraphic_ComboBox[loop] = new LinkedComboBox(Units_Scroller, Units_StandingGraphic[loop], &graphic_names, false);
        GraphicComboBoxList.push_back(Units_StandingGraphic_ComboBox[loop]);
    }
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Units_DyingGraphic[loop] = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit, false);
        Units_DyingGraphic_ComboBox[loop] = new LinkedComboBox(Units_Scroller, Units_DyingGraphic[loop], &graphic_names, false);
        GraphicComboBoxList.push_back(Units_DyingGraphic_ComboBox[loop]);
    }
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Units_WalkingGraphic[loop] = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit, false);
        Units_WalkingGraphic_ComboBox[loop] = new LinkedComboBox(Units_Scroller, Units_WalkingGraphic[loop], &graphic_names, false);
        GraphicComboBoxList.push_back(Units_WalkingGraphic_ComboBox[loop]);
    }
    Units_SnowGraphicID = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit, false);
    Units_SnowGraphicID_ComboBox = new LinkedComboBox(Units_Scroller, Units_SnowGraphicID, &graphic_names, false);
    GraphicComboBoxList.push_back(Units_SnowGraphicID_ComboBox);
    Units_ConstructionGraphicID = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit, false);
    Units_ConstructionGraphicID_ComboBox = new LinkedComboBox(Units_Scroller, Units_ConstructionGraphicID, &graphic_names, false);
    GraphicComboBoxList.push_back(Units_ConstructionGraphicID_ComboBox);
    Units_AttackGraphic = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit, false);
    Units_AttackGraphic_ComboBox = new LinkedComboBox(Units_Scroller, Units_AttackGraphic, &graphic_names, false);
    GraphicComboBoxList.push_back(Units_AttackGraphic_ComboBox);
    Units_GarrisonGraphic = new NumberControl(CLong, Units_Scroller, this, &uiGroupUnit, false);
    Units_GarrisonGraphic_ComboBox = new LinkedComboBox(Units_Scroller, Units_GarrisonGraphic, &graphic_names, false);
    GraphicComboBoxList.push_back(Units_GarrisonGraphic_ComboBox);
    Units_DestructionGraphicID = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit, false);
    Units_DestructionGraphicID_ComboBox = new LinkedComboBox(Units_Scroller, Units_DestructionGraphicID, &graphic_names, false);
    GraphicComboBoxList.push_back(Units_DestructionGraphicID_ComboBox);
    Units_DestructionRubbleGraphicID = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit, false);
    Units_DestructionRubbleGraphicID_ComboBox = new LinkedComboBox(Units_Scroller, Units_DestructionRubbleGraphicID, &graphic_names, false);
    GraphicComboBoxList.push_back(Units_DestructionRubbleGraphicID_ComboBox);
    Units_SpawningGraphic = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit, false);
    Units_SpawningGraphic_ComboBox = new LinkedComboBox(Units_Scroller, Units_SpawningGraphic, &graphic_names, false);
    GraphicComboBoxList.push_back(Units_SpawningGraphic_ComboBox);
    Units_UpgradeGraphic = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit, false);
    Units_UpgradeGraphic_ComboBox = new LinkedComboBox(Units_Scroller, Units_UpgradeGraphic, &graphic_names, false);
    GraphicComboBoxList.push_back(Units_UpgradeGraphic_ComboBox);
    Units_HeroGlowGraphic = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit, false);
    Units_HeroGlowGraphic_ComboBox = new LinkedComboBox(Units_Scroller, Units_HeroGlowGraphic, &graphic_names, false);
    GraphicComboBoxList.push_back(Units_HeroGlowGraphic_ComboBox);
    Units_ResearchingGraphic = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit, false);
    Units_ResearchingGraphic_ComboBox = new LinkedComboBox(Units_Scroller, Units_ResearchingGraphic, &graphic_names, false);
    GraphicComboBoxList.push_back(Units_ResearchingGraphic_ComboBox);
    Units_ResearchCompletedGraphic = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit, false);
    Units_ResearchCompletedGraphic_ComboBox = new LinkedComboBox(Units_Scroller, Units_ResearchCompletedGraphic, &graphic_names, false);
    GraphicComboBoxList.push_back(Units_ResearchCompletedGraphic_ComboBox);

    Units_HitPoints = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_HitPoints->SetToolTip("-1 Instantly dying unit");
    Units_Speed = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_RotationSpeed = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_RotationSpeed->SetToolTip("Makes it slower");
    Units_LineOfSight = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_LineOfSight->SetToolTip("Maximum (effective) value is 20");
    Units_SearchRadius = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_MaxRange = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_MinRange = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_DisplayedRange = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);

    Units_Attacks = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Attacks");
    Units_Attacks_ListArea = new wxBoxSizer(wxVERTICAL);
    Units_Attacks_DataArea = new wxBoxSizer(wxVERTICAL);
    Units_Attacks_Search = new wxTextCtrl(Units_Scroller, wxID_ANY);
    Units_Attacks_Search_R = new wxTextCtrl(Units_Scroller, wxID_ANY);
    Units_Attacks_ListV = new ProperList(Units_Scroller, ASize(140, 100));
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
    Attacks_Amount = new NumberControl(CShort, Units_Scroller, this, nullptr, false);
    Attacks_Class_Holder = new wxBoxSizer(wxVERTICAL);
    Attacks_Class_Text = new SolidText(Units_Scroller, " Type *");
    Attacks_Class = new NumberControl(CShort, Units_Scroller, this, nullptr, false);
    Attacks_Class->SetToolTip("Armor class that this unit can damage\nYou can make your own classes");
    Attacks_Class_ComboBox[0] = new LinkedComboBox(Units_Scroller, Attacks_Class, &armor_names, false);

    Units_DisplayedAttack = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_Delay = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_Delay->SetToolTip("Graphical delay in frames before projectile is shot");
    Units_AccuracyPercent = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_AccuracyDispersion = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_AccuracyDispersion->SetToolTip("Arc multiplier of the sector where the projectiles may hit.\nHigher values will make missed hits disperse more.");
    Units_ReloadTime = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_DisplayedReloadTime = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_BlastWidth = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_BlastWidth->SetToolTip("If object has 0 blast radius\nand does not hit the unit it had targeted\nalways does half damage");
    Units_BlastAttackLevel = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_BlastAttackLevel->SetToolTip("Blasts damage units that have higher or same blast armor level\n0   Damages resources also\n1   Damages trees also\n2   Damages nearby units\n3   Damages only targeted unit");
    Units_BlastDamage = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_BlastDamage->SetToolTip("Area damage. If the value is above 0, it's a multiplier applied to the base attack. If the value is negative, it does a fixed amount of damage.");

    Units_Armors = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Armors");
    Units_Armors_ListArea = new wxBoxSizer(wxVERTICAL);
    Units_Armors_DataArea = new wxBoxSizer(wxVERTICAL);
    Units_Armors_Search = new wxTextCtrl(Units_Scroller, wxID_ANY);
    Units_Armors_Search_R = new wxTextCtrl(Units_Scroller, wxID_ANY);
    Units_Armors_ListV = new ProperList(Units_Scroller, ASize(140, 100));
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
    Units_Defense_Holder = new wxFlexGridSizer(2, 5, 5);
    Armors_Amount_Holder = new wxBoxSizer(wxVERTICAL);
    Armors_Amount_Text = new SolidText(Units_Scroller, " Amount");
    Armors_Amount = new NumberControl(CShort, Units_Scroller, this, nullptr, false);
    Armors_Class_Holder = new wxBoxSizer(wxVERTICAL);
    Armors_Class_Text = new SolidText(Units_Scroller, " Type *");
    Armors_Class = new NumberControl(CShort, Units_Scroller, this, nullptr, false);
    Armors_Class->SetToolTip("Attack class from which this unit can take damage\nYou can make your own classes");
    Attacks_Class_ComboBox[1] = new LinkedComboBox(Units_Scroller, Armors_Class, &armor_names, false);

    Units_BlastDefenseLevel = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_BlastDefenseLevel->SetToolTip("Receive blast damage from units that have lower or same blast attack level");
    Units_BonusDamageResistance = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_BonusDamageResistance->SetToolTip("Damage resistance for bonus armors (all but 3, 4, and 31)");
    Units_BaseArmor = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_BaseArmor->SetToolTip("This armor is used for attack types that have no corresponding armor type\n"
        "Can be negative only in The Conquerors and later games");
    Units_DefenseTerrainBonus = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_DefenseTerrainBonus->SetToolTip("Terrain table ID\n"
        "Receive damage based on which terrain this unit stands on.\nEffect attribute 18 changes this.\n"
        "The damage received by this unit is\nmultiplied by the accessible values on\n"
        "the specified terrain table.");
    Units_DefenseTerrainBonus_ComboBox = new LinkedComboBox(Units_Scroller, Units_DefenseTerrainBonus, &restriction_names);
    TerrainRestrictionComboBoxList.push_back(Units_DefenseTerrainBonus_ComboBox);
    Units_DisplayedMeleeArmour = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_DisplayedPierceArmour = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);

    Units_ResourceCapacity = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_ResourceDecay = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_ResourceDecay->SetToolTip("Can alter decay time of corpses\nSet to -1 for never decaying");
    Units_WorkRate = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_MinConversionTimeMod = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_MinConversionTimeMod->SetToolTip("Modifier to the minimum time it can take to convert this unit.");
    Units_MaxConversionTimeMod = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_MaxConversionTimeMod->SetToolTip("Modifier to the maximum time it can take to convert this unit.");
    Units_ConversionChanceMod = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_ConversionChanceMod->SetToolTip("Modifier to the overall chance it takes to convert this unit.");
    Units_GarrisonCapacity = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_GarrisonType = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit, false);
    Units_GarrisonType->SetToolTip("You can garrison any type,\nif you add the garrison action targeting this class/unit,\nbut you may need to hold the alt key while choosing to garrison.");
    Units_GarrisonType_Grid = new wxBoxSizer(wxHORIZONTAL);
    for(size_t loop = 0; loop < 8; ++loop)
    Units_GarrisonType_CheckBox[loop] = new wxCheckBox(Units_Scroller, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(15, -1));
    Units_GarrisonType_CheckBox[0]->SetToolTip("Villager/Worker");
    Units_GarrisonType_CheckBox[1]->SetToolTip("Infantry");
    Units_GarrisonType_CheckBox[2]->SetToolTip("Cavalry/Mounted");
    Units_GarrisonType_CheckBox[3]->SetToolTip("Monk/Jedi");
    Units_GarrisonType_CheckBox[4]->SetToolTip("SW: Livestock");
    Units_GarrisonHealRate = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_GarrisonHealRate->SetToolTip("Healing speed factor of units garrisoned in building");
    Units_MaxCharge = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_RechargeRate = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_ChargeEvent = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_ChargeEvent->SetToolTip("1   Deduct 1 from the charge when attack animation completes");
    Units_ChargeType = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_ChargeType->SetToolTip("1   Attack\n2   Hit Points");

    Units_ProjectileUnitID = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_ProjectileUnitID_ComboBox = new LinkedComboBox(Units_Scroller, Units_ProjectileUnitID, &unit_names);
    UnitComboBoxList.push_back(Units_ProjectileUnitID_ComboBox);
    Units_AttackMissileDuplicationUnit = new NumberControl(CLong, Units_Scroller, this, &uiGroupUnit);
    Units_AttackMissileDuplicationUnit->SetToolTip("Uses its own attack values!");
    Units_AttackMissileDuplicationUnit_ComboBox = new LinkedComboBox(Units_Scroller, Units_AttackMissileDuplicationUnit, &unit_names);
    UnitComboBoxList.push_back(Units_AttackMissileDuplicationUnit_ComboBox);
    Units_MissileCount = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_MissileCount->SetToolTip("Total missiles including both normal and duplicated projectiles");
    Units_MissileDuplicationCount = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_MissileDuplicationCount->SetToolTip("Total missiles when garrison capacity is full");
    for(size_t loop = 0; loop < 3; ++loop)
    Units_GraphicDisplacement[loop] = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_GraphicDisplacement[0]->SetToolTip("Left/Right distance");
    Units_GraphicDisplacement[1]->SetToolTip("Spawning distance from the unit");
    Units_GraphicDisplacement[2]->SetToolTip("Height");
    for(size_t loop = 0; loop < 3; ++loop)
    Units_AttackMissileDuplicationSpawning[loop] = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_AttackMissileDuplicationSpawning[0]->SetToolTip("Spawning area's width");
    Units_AttackMissileDuplicationSpawning[1]->SetToolTip("Spawning area's length");
    Units_AttackMissileDuplicationSpawning[2]->SetToolTip("Spawning point's randomness inside the spawning area\n"
        "0   From a single spot\n1   Totally randomly inside the spawning area\n1+ Less randomly");

    Units_ProjectileType = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_ProjectileType->SetToolTip("0   Straight\n1   Homing?"
        ", projectile falls vertically to the bottom of the map\n2   Velocity homing?\n3   Teleporting projectile");
    Units_SmartMode = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_SmartMode->SetToolTip("Effect attribute 19 changes this\n0   Shoot where the target is now\n"
        "1   Shoot where the target is going to be");
    Units_HitMode = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_HitMode->SetToolTip("0   Continue after hitting an obstacle\n1   Disappear once an obstacle is hit\n"
        "2   Hit all. Damages target and resting position?");
    Units_VanishMode = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_VanishMode->SetToolTip("Only affects graphics of the projectile\n0   Stops graphics at target\n"
        "1   Graphics pass through the target instead of stopping");
    Units_AreaEffectSpecials = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_AreaEffectSpecials->SetToolTip("0   Normal\n1   Random (bullets)\n2   Random explosions");
    Units_ProjectileArc = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);

    Units_Enabled = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit, true, AGETextCtrl::SMALL);
    Units_Enabled->SetToolTip("0   Requires a technology to be available\n1   Available without a technology");
    Units_Enabled_CheckBox = new LinkedCheckBox(Units_Scroller, "Available *", Units_Enabled);
    Units_Disabled = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit, true, AGETextCtrl::SMALL);
    Units_Disabled->SetToolTip("Not scanned but set to 0\nCan change during gameplay\n"
        "Mostly for different game modes and disables defined in scenarios\n"
        "0   Default\n1   Prevents enabling/disabling with a tech");
    Units_Disabled_CheckBox = new LinkedCheckBox(Units_Scroller, "Disabled *", Units_Disabled);
    Units_UndeadMode = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit, true, AGETextCtrl::SMALL);
    Units_UndeadMode->SetToolTip("After 1st dying graphic:\n0   Transform into dead unit\n1   Show undead graphic");
    Units_UndeadMode_CheckBox = new LinkedCheckBox(Units_Scroller, "Undead Mode *", Units_UndeadMode);
    Units_CanBeBuiltOn = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit, true, AGETextCtrl::SMALL);
    Units_CanBeBuiltOn->SetToolTip("0   Default\n1   Graphic stays at highest elevation until destination is reached\n2+ Graphic is not affected by elevation");
    Units_CanBeBuiltOn_CheckBox = new LinkedCheckBox(Units_Scroller, "Can be Built on *", Units_CanBeBuiltOn);
    Units_HideInEditor = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit, true, AGETextCtrl::SMALL);
    Units_HideInEditor->SetToolTip("Possible values: 0, 1 and as boolean\nAoE2DE: 2 Show in others tab in scenario editor");
    Units_HideInEditor_CheckBox = new LinkedCheckBox(Units_Scroller, "Hide in Editor *", Units_HideInEditor);
    Units_FlyMode = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit, true, AGETextCtrl::SMALL);
    Units_FlyMode->SetToolTip("Controls graphic altitude when teleporting\n0   Stay on ground\n1   Graphics appear higher than the shadow");
    Units_FlyMode_CheckBox = new LinkedCheckBox(Units_Scroller, "Fly Mode *", Units_FlyMode);
    Units_Recyclable = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit, true, AGETextCtrl::SMALL);
    Units_Recyclable->SetToolTip("Unselectable\nNot scanned but set to 1 for class 11\nCan change during gameplay");
    Units_Recyclable_CheckBox = new LinkedCheckBox(Units_Scroller, "Recyclable *", Units_Recyclable);
    Units_TrackAsResource = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit, true, AGETextCtrl::SMALL);
    Units_TrackAsResource->SetToolTip("Track as Resource\nAllows automatic gathering and handles fog visibility");
    Units_TrackAsResource_CheckBox = new LinkedCheckBox(Units_Scroller, "Can be Gathered *", Units_TrackAsResource);
    Units_HeroMode = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit, true, AGETextCtrl::SMALL);
    Units_HeroMode_CheckBox = new LinkedCheckBox(Units_Scroller, "Hero Mode", Units_HeroMode);
    Units_AdjacentMode = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit, true, AGETextCtrl::SMALL);
    Units_AdjacentMode->SetToolTip("0   Default\n1   Adjacent buildings can change graphics of this unit\nThis changes the graphic angle");
    Units_AdjacentMode_CheckBox = new LinkedCheckBox(Units_Scroller, "Adjacent Mode *", Units_AdjacentMode);
    Units_DisappearsWhenBuilt = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit, true, AGETextCtrl::SMALL);
    Units_DisappearsWhenBuilt->SetToolTip("Useful for stack unit placement\n0   Default\n1   Makes the building disappear when built");
    Units_BuildAndVanish_CheckBox = new LinkedCheckBox(Units_Scroller, "Built: Vanishes *", Units_DisappearsWhenBuilt);

    Units_SortNumber = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_SortNumber->SetToolTip("Units with low sort numbers are drawn last\n0   Can be placed on top of other units in scenario editor\n5   Cannot be placed on top of other units in scenario editor");
    Units_HillMode = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_HillMode->SetToolTip("0   No restriction\n1   Cannot place on corners of hills\n2   Can only place on flat land\n3   Allows one elevation difference");
    Units_FogVisibility_Text = new SolidText(Units_Scroller, " Fog Visibility *");
    Units_FogVisibility = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_FogVisibility->SetToolTip("0   Not visible\n1   Always visible\n2   Visible if alive\n3   Inverted visibility\n4   Check doppelganger");
    Units_CombatLevel = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_CombatLevel->SetToolTip("Mainly used in trigger conditions\n0   None\n1   Base\n2   Building\n3   Civilian\n4   Soldier\n5   Priest\n");
    Units_InteractionMode = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_InteractionMode->SetToolTip("Select Level\n0   None. No interaction.\n"
        "1   Object. Can pick.\n2   Resource. Can select, unable to attack or move.\n"
        "3   Building. Can select and attack, unable to move.\n4   Unit. Can select, attack and move.");
    Units_MinimapMode = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_MinimapMode->SetToolTip("Draw Level\n0   None. No dot on minimap.\n"
        "1   Unit. Square dot turning white when selected.\n"
        "2   Building. Diamond dot turning white when selected.\n"
        "3   Terrain. Diamond dot keeping color.\n4   Terrain. Larger spot, not following the unit,\n"
        "      no blinking when attacked, everyone can see it.");
    Units_MinimapColor = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_MinimapColor->SetToolTip("Minimap modes 3 and 4 allow this to work");
    Units_CreateDoppelgangerOnDeath = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_CreateDoppelgangerOnDeath->SetToolTip("Create doppelganger on death.\n"
        "0   None\n1   After death\n2   When dying");
    Units_ResourceGroup = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_ResourceGroup->SetToolTip("Visible resource group\nNeeds to be gatherable\n"
        "0   Tree\n1   Berry\n2   Fish\n3   Stone/ore\n4   Gold/nova");
    Units_TaskSwapGroup = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_TaskSwapGroup->SetToolTip("When tasking the unit, it will transform into another unit,\n"
        "if the action is not found in this unit, but exists on another unit,\nthat uses the same task swap group.\n"
        "Changes according to task\n1   Male villager\n2   Female villager\n3+ Free slots");
    Units_ChargingMode = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
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

    Units_Trait = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit, false);
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
    Units_Civ = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_Civ_ComboBox = new LinkedComboBox(Units_Scroller, Units_Civ, &civ_names);
    CivComboBoxList.push_back(Units_Civ_ComboBox);
    Units_Nothing = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_Nothing->SetToolTip("This is actually leftover from attribute+civ variable\nProbably useless");
    Units_DeadUnitID = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_DeadUnitID_ComboBox = new LinkedComboBox(Units_Scroller, Units_DeadUnitID, &unit_names);
    UnitComboBoxList.push_back(Units_DeadUnitID_ComboBox);
    Units_BloodUnitID = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_BloodUnitID_ComboBox = new LinkedComboBox(Units_Scroller, Units_BloodUnitID, &unit_names);
    UnitComboBoxList.push_back(Units_BloodUnitID_ComboBox);
    Units_Unitline = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_Unitline_ComboBox = new LinkedComboBox(Units_Scroller, Units_Unitline, &unitline_names);
    Units_MinTechLevel = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_MinTechLevel_ComboBox = new LinkedComboBox(Units_Scroller, Units_MinTechLevel, &research_names);
    ResearchComboBoxList.push_back(Units_MinTechLevel_ComboBox);
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Units_PlacementTerrain[loop] = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
        Units_PlacementTerrain_ComboBox[loop] = new LinkedComboBox(Units_Scroller, Units_PlacementTerrain[loop], &terrain_names);
        TerrainComboBoxList.push_back(Units_PlacementTerrain_ComboBox[loop]);
    }
    for(size_t loop = 0; loop < 2; ++loop)
    {
        Units_PlacementSideTerrain[loop] = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
        Units_PlacementSideTerrain[loop]->SetToolTip("Required terrain on some side");
        Units_PlacementSideTerrain_ComboBox[loop] = new LinkedComboBox(Units_Scroller, Units_PlacementSideTerrain[loop], &terrain_names);
        TerrainComboBoxList.push_back(Units_PlacementSideTerrain_ComboBox[loop]);
    }
    Units_TerrainRestriction = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_TerrainRestriction->SetToolTip("Must use valid index here (not -1)");
    Units_TerrainRestriction_ComboBox = new LinkedComboBox(Units_Scroller, Units_TerrainRestriction, &restriction_names);
    TerrainRestrictionComboBoxList.push_back(Units_TerrainRestriction_ComboBox);
    Units_TerrainID = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_TerrainID->SetToolTip("Terrain produced under a building when completed");
    Units_TerrainID_ComboBox = new LinkedComboBox(Units_Scroller, Units_TerrainID, &terrain_names);
    TerrainComboBoxList.push_back(Units_TerrainID_ComboBox);
    Units_ResearchID = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_ResearchID->SetToolTip("Causes that technology to be researched when the building is created");
    Units_ResearchID_ComboBox = new LinkedComboBox(Units_Scroller, Units_ResearchID, &research_names);
    ResearchComboBoxList.push_back(Units_ResearchID_ComboBox);
    Units_DefaultTaskID_Text = new SolidText(Units_Scroller, " Default Task *");
    Units_DefaultTaskID = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_DefaultTaskID->SetToolTip("Unit task ID executed when idle.\nTo get the unit auto-converted to enemy,\nuse unit command 107, which sheep and monument have.");
    Units_DefaultTaskID_ComboBox = new LinkedComboBox(Units_Scroller, Units_DefaultTaskID, &action_names);

    Units_DropSites = new wxStaticBoxSizer(wxHORIZONTAL, Units_Scroller, "Drop Sites");
    Units_DropSites_ListArea = new wxBoxSizer(wxVERTICAL);
    Units_DropSites_Search = new wxTextCtrl(Units_Scroller, wxID_ANY);
    Units_DropSites_Search_R = new wxTextCtrl(Units_Scroller, wxID_ANY);
    Units_DropSites_ListV = new ProperList(Units_Scroller, ASize(140, 100));
    Units_DropSites_Buttons_Upper = new wxBoxSizer(wxHORIZONTAL);
    Units_DropSites_Buttons_Lower = new wxBoxSizer(wxHORIZONTAL);
    Units_DropSites_Add = new wxButton(Units_Scroller, wxID_ANY, "Add", wxDefaultPosition, wxSize(10, -1));
    Units_DropSites_Insert = new wxButton(Units_Scroller, wxID_ANY, "Ins New", wxDefaultPosition, wxSize(10, -1));
    Units_DropSites_Delete = new wxButton(Units_Scroller, wxID_ANY, "Delete", wxDefaultPosition, wxSize(10, -1));
    Units_DropSites_Copy = new wxButton(Units_Scroller, wxID_ANY, "Copy *", wxDefaultPosition, wxSize(10, -1));
    Units_DropSites_Copy->SetToolTip("When \"All civs\" is not selected,\nthis and pasting works only for current civilization");
    Units_DropSites_Paste = new wxButton(Units_Scroller, wxID_ANY, "Paste", wxDefaultPosition, wxSize(10, -1));
    Units_DropSites_PasteInsert = new wxButton(Units_Scroller, wxID_ANY, "Ins Copies", wxDefaultPosition, wxSize(10, -1));
    Units_DropSites_CopyToUnits = new wxButton(Units_Scroller, wxID_ANY, "Copy all to selected units", wxDefaultPosition, wxSize(10, -1));
    DropSites_UnitID_Holder = new wxBoxSizer(wxVERTICAL);
    DropSites_UnitID_Text = new SolidText(Units_Scroller, " Unit *");
    DropSites_UnitID = new NumberControl(CShort, Units_Scroller, this, nullptr, false);
    DropSites_UnitID->SetToolTip("Giving to a villager drop site to cart-like unit\ncan allow you to have mobile resource-gatherers,\nsimilar to those in Age of Mythology.");
    DropSites_UnitID_ComboBox = new LinkedComboBox(Units_Scroller, DropSites_UnitID, &unit_names, false);
    UnitComboBoxList.push_back(DropSites_UnitID_ComboBox);

    for (size_t loop = 0; loop < 3; ++loop)
    Units_SizeRadius[loop] = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit, loop == 2);
    Units_MinCollisionSizeMultiplier = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_MinCollisionSizeMultiplier->SetToolTip("Scales collision size under certain circumstances.");
    Units_SelectionRadiusBox = new wxBoxSizer(wxHORIZONTAL);
    for(size_t loop = 0; loop < 3; ++loop)
    Units_SelectionRadius[loop] = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit, loop == 2);
    for(size_t loop = 0; loop < 2; ++loop)
    Units_ClearanceSize[loop] = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit, false);
    Units_SizeRadius[2]->SetToolTip("Setting \"can be built on\" to 1 and this to 0 causes\nfarms to be walkable in AoE/RoR.");
    Units_SelectionRadius[2]->SetToolTip("Determines HP bar location\nVertical half tile (elevation height?) distance from the top corner?");

    Units_OcclusionMode = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_OcclusionMode->SetToolTip("Combinable bit field\n0   No outline\n"
        "1   Outline displayed through occlusion\n2   Occludes others\n4   Outline displayed while constructing");
    Units_ObstructionType = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_ObstructionType->SetToolTip("0, 1   Square outline, and passable\n"
        "2   Solid square outline, and has collision box\n3   Square outline, and has collision box\n"
        "4   Is passable, but has no outline\n5   Round outline, and has collision box\n"
        "10   Like 2, designed for mountains");
    Units_ObstructionClass = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_ObstructionClass->SetToolTip("0   Forces default obstruction type\n1   Resource\n2   Unit\n3   Building\n"
        "4   Wall\n5   Gate, allows trespassing\n6   Cliff, blocks walling");
    Units_SelectionEffect = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_SelectionEffect->SetToolTip("0   Has hit point bar\n1   Has hit point bar and outline\n"
        "2   No hit point bar or outline\n3   No hit point bar, but has outline");
    Units_EditorSelectionColour = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_TrackingUnit = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_TrackingUnit_ComboBox = new LinkedComboBox(Units_Scroller, Units_TrackingUnit, &unit_names);
    UnitComboBoxList.push_back(Units_TrackingUnit_ComboBox);
    Units_TrackingUnitMode = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_TrackingUnitMode->SetToolTip("0   Not used\n1   Appears while moving and at the start of the game\n"
        "2   Appears while moving, based on density");
    Units_TrackingUnitDensity = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_TrackingUnitDensity->SetToolTip("Only with trail mode 2");
    for(size_t loop = 0; loop < Units_RotationAngles.size(); ++loop)
    Units_RotationAngles[loop] = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    wxString rot360 = "360 degrees when multiplying with 4th box radian value";
    Units_RotationAngles[2]->SetToolTip(rot360);
    Units_RotationAngles[3]->SetToolTip("Used to get 3rd and 5th box to 360 degrees");
    Units_RotationAngles[4]->SetToolTip(rot360);
    Units_InterfaceKind = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_InterfaceKind->SetToolTip("Unit Level\nClass and this sets the interface for this unit\n0   None\n"
        "1   Resource\n2   Building (build page 1)\n3   Civilian\n4   Soldier\n5   Trade Unit\n6   Priest\n"
        "7   Transport Ship\n8   Relic / Priest with Relic\n9   Fishing Boat\n"
        "10   (A=2&8) Military Building (build page 2)\n11   Shield Building (build page 3)");
    Units_TrainTime = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_TrainLocationID = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_TrainLocationID_ComboBox = new LinkedComboBox(Units_Scroller, Units_TrainLocationID, &unit_names);
    UnitComboBoxList.push_back(Units_TrainLocationID_ComboBox);
    Units_ButtonID = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_ButtonID->SetToolTip("First page (also second in TC) 1-15\nSecond (dock) page 21-35\nThird page same as first (Star Wars)\nFirst page in AoE/RoR 1-10\nSecond page in AoE/RoR 11-20");
    for(size_t loop = 0; loop < 3; ++loop)
    {
        ResourceStorage_Type[loop] = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
        ResourceStorage_Type_ComboBox[loop] = new LinkedComboBox(Units_Scroller, ResourceStorage_Type[loop], &resource_names);
        ResourceComboBoxList.push_back(ResourceStorage_Type_ComboBox[loop]);
        ResourceStorage_Amount[loop] = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
        ResourceStorage_Mode[loop] = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
        ResourceStorage_Mode[loop]->SetToolTip("Attribute Flag\n0   Keep. Decayable resource.\n"
        "1   Give. Stored after death also.\n2   Give and take. Resets on dying, enables instantly.\n"
        "4   Building. Resets on dying, enables on completion.\nUP: 8   Stored on completion and stays after death.\n"
        "AoE2DE: 32   Stored throughout dying animation.");
    }
    for(size_t loop = 0; loop < 3; ++loop)
    {
        Units_CostType[loop] = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
        Units_CostType_ComboBox[loop] = new LinkedComboBox(Units_Scroller, Units_CostType[loop], &resource_names);
        ResourceComboBoxList.push_back(Units_CostType_ComboBox[loop]);
        Units_CostAmount[loop] = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
        Units_CostUsed[loop] = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
        Units_CostUsed[loop]->SetToolTip("If set to 0 and there is an amount, the amount is required but not paid");
        Units_CostUsed_CheckBox[loop] = new LinkedCheckBox(Units_Scroller, "Paid", Units_CostUsed[loop]);
    }
    Units_StackUnitID = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_StackUnitID->SetToolTip("Second building to be placed directly on top of this building\nAdditional building gets added every time you load the scenario");
    Units_StackUnitID_ComboBox = new LinkedComboBox(Units_Scroller, Units_StackUnitID, &unit_names);
    UnitComboBoxList.push_back(Units_StackUnitID_ComboBox);
    Units_HeadUnit = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_HeadUnit->SetToolTip("The building that an annex building is attached to");
    Units_HeadUnit_ComboBox = new LinkedComboBox(Units_Scroller, Units_HeadUnit, &unit_names);
    UnitComboBoxList.push_back(Units_HeadUnit_ComboBox);
    Units_TransformUnit = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_TransformUnit->SetToolTip("Determines what the unit changes into when given the order to unpack");
    Units_TransformUnit_ComboBox = new LinkedComboBox(Units_Scroller, Units_TransformUnit, &unit_names);
    UnitComboBoxList.push_back(Units_TransformUnit_ComboBox);
    Units_PileUnit = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_PileUnit->SetToolTip("Appears when the building dies\nDoes not appear with delete command");
    Units_PileUnit_ComboBox = new LinkedComboBox(Units_Scroller, Units_PileUnit, &unit_names);
    UnitComboBoxList.push_back(Units_PileUnit_ComboBox);
    for(size_t loop = 0; loop < 4; ++loop)
    {
        Units_AnnexUnit[loop] = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
        Units_AnnexUnit_ComboBox[loop] = new LinkedComboBox(Units_Scroller, Units_AnnexUnit[loop], &unit_names);
        UnitComboBoxList.push_back(Units_AnnexUnit_ComboBox[loop]);
    }
    for(size_t loop = 0; loop < 4; ++loop)
    {
        for(size_t loop2 = 0; loop2 < 2; ++loop2)
        Units_AnnexUnitMisplacement[loop][loop2] = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit, false, AGETextCtrl::LARGE);
    }
    for(size_t loop = 0; loop < Units_LootSwitch.size(); ++loop)
    Units_LootSwitch[loop] = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit, true, AGETextCtrl::SMALL);
    Units_LootSwitch[0]->SetToolTip("Stone Loot Switch");
    Units_LootSwitch[1]->SetToolTip("Wood Loot Switch");
    Units_LootSwitch[2]->SetToolTip("Ore Loot Switch");
    Units_LootSwitch[3]->SetToolTip("Gold Loot Switch");
    Units_LootSwitch[4]->SetToolTip("Food Loot Switch");
    Units_LootSwitch[5]->SetToolTip("Goods Loot Switch");

    Units_WwiseSelectionSound = new NumberControl(CULong, Units_Scroller, this, &uiGroupUnit);
    Units_SelectionSound = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_SelectionSound_ComboBox = new LinkedComboBox(Units_Scroller, Units_SelectionSound, &sound_names);
    SoundComboBoxList.push_back(Units_SelectionSound_ComboBox);
    Units_WwiseDyingSound = new NumberControl(CULong, Units_Scroller, this, &uiGroupUnit);
    Units_DyingSound = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_DyingSound_ComboBox = new LinkedComboBox(Units_Scroller, Units_DyingSound, &sound_names);
    SoundComboBoxList.push_back(Units_DyingSound_ComboBox);
    Units_WwiseTrainSound = new NumberControl(CULong, Units_Scroller, this, &uiGroupUnit);
    Units_TrainSound = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_TrainSound_ComboBox = new LinkedComboBox(Units_Scroller, Units_TrainSound, &sound_names);
    SoundComboBoxList.push_back(Units_TrainSound_ComboBox);
    Units_WwiseDamageSound = new NumberControl(CULong, Units_Scroller, this, &uiGroupUnit);
    Units_DamageSound = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_DamageSound_ComboBox = new LinkedComboBox(Units_Scroller, Units_DamageSound, &sound_names);
    SoundComboBoxList.push_back(Units_DamageSound_ComboBox);
    Units_WwiseAttackSound = new NumberControl(CULong, Units_Scroller, this, &uiGroupUnit);
    Units_AttackSound = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_AttackSound_ComboBox = new LinkedComboBox(Units_Scroller, Units_AttackSound, &sound_names);
    SoundComboBoxList.push_back(Units_AttackSound_ComboBox);
    Units_WwiseMoveSound = new NumberControl(CULong, Units_Scroller, this, &uiGroupUnit);
    Units_MoveSound = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_MoveSound_ComboBox = new LinkedComboBox(Units_Scroller, Units_MoveSound, &sound_names);
    SoundComboBoxList.push_back(Units_MoveSound_ComboBox);
    Units_WwiseConstructionSound = new NumberControl(CULong, Units_Scroller, this, &uiGroupUnit);
    Units_ConstructionSound = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_ConstructionSound_ComboBox = new LinkedComboBox(Units_Scroller, Units_ConstructionSound, &sound_names);
    SoundComboBoxList.push_back(Units_ConstructionSound_ComboBox);
    Units_WwiseTransformSound = new NumberControl(CULong, Units_Scroller, this, &uiGroupUnit);
    Units_TransformSound = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_TransformSound->SetToolTip("Unused\nDevelopers forgot to implement this?");
    Units_TransformSound_ComboBox = new LinkedComboBox(Units_Scroller, Units_TransformSound, &sound_names);
    SoundComboBoxList.push_back(Units_TransformSound_ComboBox);

    Units_Portrait = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_Portrait->SetToolTip("Was probably used similarly to unit icon");
    Units_MultipleAttributeMode = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_MultipleAttributeMode->SetToolTip("1 on more or less living things");
    Units_AttackReaction = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_AttackReaction->SetToolTip("0   None\n1   Run\n2   Run work\n"
        "3   Fight\n4   Fight work\n5   Fight run\n6   Fight run work\n");
    Units_ConvertTerrain = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_ConvertTerrain->SetToolTip("Some alpha feature that let units change terrain under them.\nSpecifically from passable to impassable.");

    Units_SizeClass = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_MoveAlgorithm = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);

    Units_RunPattern_Text = new SolidText(Units_Scroller, " Run Pattern *");
    Units_RunPattern = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_RunPattern->SetToolTip("0   Escape straight\n1   Escape randomly");

    Units_TowerMode_Text = new SolidText(Units_Scroller, " Break off Combat");
    Units_TowerMode = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);

    Units_OldOverlayID = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnit);
    Units_OldOverlayID->SetToolTip("ES forgot to remove this before AoE was released.\nThis points to removed data block\nthat was like terrain borders.\nYou could build roads back in 1996.");

    Units_RearAttackModifier = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_FlankAttackModifier = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);
    Units_CreatableType = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_CreatableType->SetToolTip("0   None\n1   Villager\n2   Infantry\n3   Cavalry\n4   Relic\n5   Archer\n6   Monk\n");

    Units_CanBurn = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    Units_GarrisonRepairRate = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnit);

    TaskHolder_Lists = new wxBoxSizer(wxVERTICAL);
    Units_UnitHeads_Name = new SolidText(Units_Scroller, "Unit Header");
    Units_Tasks_Search = new wxTextCtrl(Units_Scroller, wxID_ANY);
    Units_Tasks_Search_R = new wxTextCtrl(Units_Scroller, wxID_ANY);
    Units_Tasks_ListV = new ProperList(Units_Scroller, ASize(140, 190));
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
    Units_Exists = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnit);
    wxArrayString action_choices;
    action_choices.Add("None");
    action_choices.Add("Move");
    action_choices.Add("Proceed");
    action_choices.Add("Work");
    action_choices.Add("Carry");
    slp_unit_actions = new wxRadioBox(Units_Scroller, wxID_ANY, "Sprite view", wxDefaultPosition, wxDefaultSize, action_choices, 0, wxVERTICAL);

    Tasks_Type_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_Type_Text = new SolidText(Units_Scroller, " Task Type");
    Tasks_Type = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnitTask, true, AGETextCtrl::MEDIUM);
    Tasks_ID_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_ID_Text = new SolidText(Units_Scroller, " ID");
    Tasks_ID = new NumberControl(CShort, Units_Scroller, this, nullptr, true, AGETextCtrl::MEDIUM);
    Tasks_IsDefault_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_IsDefault = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnitTask);
    Tasks_IsDefault->SetToolTip("Basically useless\nUsed to setup task when discovered,\nbut you can directly set it in unit data above");
    Tasks_IsDefault_Text = new LinkedCheckBox(Units_Scroller, "Is Default *", Tasks_IsDefault);
    Tasks_ActionType_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_ActionType_Text = new SolidText(Units_Scroller, " Action Type");
    Tasks_ActionType = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnitTask, false);
    Tasks_ActionType_ComboBox = new LinkedComboBox(Units_Scroller, Tasks_ActionType, &task_names, false, AGETextCtrl::GIANT);
    Tasks_ClassID_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_ClassID_Text = new SolidText(Units_Scroller, " Class");
    Tasks_ClassID = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnitTask);
    Units_Class_ComboBox[1] = new LinkedComboBox(Units_Scroller, Tasks_ClassID, &class_names);
    Tasks_UnitID_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_UnitID_Text = new SolidText(Units_Scroller, " Unit");
    Tasks_UnitID = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnitTask);
    Tasks_UnitID_ComboBox = new LinkedComboBox(Units_Scroller, Tasks_UnitID, &unit_names);
    UnitComboBoxList.push_back(Tasks_UnitID_ComboBox);
    Tasks_TerrainID_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_TerrainID_Text = new SolidText(Units_Scroller, " Terrain");
    Tasks_TerrainID = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnitTask);
    Tasks_TerrainID_ComboBox = new LinkedComboBox(Units_Scroller, Tasks_TerrainID, &terrain_names);
    TerrainComboBoxList.push_back(Tasks_TerrainID_ComboBox);
    Tasks_ResourceIn_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_ResourceIn_Text = new SolidText(Units_Scroller, " Resource In *");
    Tasks_ResourceIn = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnitTask);
    Tasks_ResourceIn->SetToolTip("Resource gained by gathering");
    Tasks_ResourceIn_ComboBox = new LinkedComboBox(Units_Scroller, Tasks_ResourceIn, &resource_names);
    ResourceComboBoxList.push_back(Tasks_ResourceIn_ComboBox);
    Tasks_ProdResource_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_ProdResource_Text = new SolidText(Units_Scroller, " Productivity Resource *");
    Tasks_ProdResource = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnitTask, false);
    Tasks_ProdResource->SetToolTip("Resource that multiplies the amount you gather");
    Tasks_ProdResource_ComboBox = new LinkedComboBox(Units_Scroller, Tasks_ProdResource, &resource_names);
    ResourceComboBoxList.push_back(Tasks_ProdResource_ComboBox);
    Tasks_ResourceOut_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_ResourceOut_Text = new SolidText(Units_Scroller, " Resource Out *");
    Tasks_ResourceOut = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnitTask);
    Tasks_ResourceOut->SetToolTip("Resource deposited on drop site");
    Tasks_ResourceOut_ComboBox = new LinkedComboBox(Units_Scroller, Tasks_ResourceOut, &resource_names);
    ResourceComboBoxList.push_back(Tasks_ResourceOut_ComboBox);
    Tasks_Resource_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_Resource_Text = new SolidText(Units_Scroller, " Unused Resource");
    Tasks_Resource = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnitTask);
    Tasks_Resource_ComboBox = new LinkedComboBox(Units_Scroller, Tasks_Resource, &resource_names);
    ResourceComboBoxList.push_back(Tasks_Resource_ComboBox);
    Tasks_WorkValue1_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_WorkValue1_Text = new SolidText(Units_Scroller, " Work Value 1 *");
    Tasks_WorkValue1 = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnitTask);
    Tasks_WorkValue1->SetToolTip("Work rate modifier\nMinimum conversion time");
    Tasks_WorkValue2_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_WorkValue2_Text = new SolidText(Units_Scroller, " Work Value 2 *");
    Tasks_WorkValue2 = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnitTask);
    Tasks_WorkValue2->SetToolTip("Maximum conversion time");
    Tasks_WorkRange_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_WorkRange_Text = new SolidText(Units_Scroller, " Work Range");
    Tasks_WorkRange = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnitTask);
    for(size_t loop = 0; loop < Tasks_Graphics.size(); ++loop)
    {
        Tasks_Graphics_Holder[loop] = new wxBoxSizer(wxVERTICAL);
        Tasks_Graphics[loop] = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnitTask, false, AGETextCtrl::SMALL);
    }
    for(size_t loop = 0; loop < 4; ++loop)
    {
        Tasks_Graphics_ComboBox[loop] = new LinkedComboBox(Units_Scroller, Tasks_Graphics[loop], &graphic_names, false);
        GraphicComboBoxList.push_back(Tasks_Graphics_ComboBox[loop]);
    }
    for(size_t loop = 4; loop < 6; ++loop)
    {
        Tasks_Graphics_ComboBox[loop] = new LinkedComboBox(Units_Scroller, Tasks_Graphics[loop], &sound_names);
        SoundComboBoxList.push_back(Tasks_Graphics_ComboBox[loop]);
    }
    Tasks_WwiseResourceGatheringSound = new NumberControl(CULong, Units_Scroller, this, &uiGroupUnitTask);
    Tasks_WwiseResourceDepositSound = new NumberControl(CULong, Units_Scroller, this, &uiGroupUnitTask);
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
    Tasks_AutoSearchTargets = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnitTask);
    Tasks_AutoSearchTargets->SetToolTip("If 1, then auto-search for targets");
    Tasks_EnableTargeting_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_EnableTargeting_Text = new SolidText(Units_Scroller, " Enable Targeting *");
    Tasks_EnableTargeting = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnitTask);
    Tasks_EnableTargeting->SetToolTip("AoE alphas: Target choosing based on combat level\n0   No targeting\n1   Allows units to select their targets");
    Tasks_TargetDiplomacy_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_TargetDiplomacy_Text = new SolidText(Units_Scroller, " Target Diplomacy *");
    Tasks_TargetDiplomacy = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnitTask);
    Tasks_TargetDiplomacy->SetToolTip("Owner Type\nDetermines what you can select as targets\n"
        "0, 7+ All objects\n1   Your objects only\n2   Neutral and enemy objects only\n3   Gaia only\n"
        "4   Gaia, your and ally objects only\n5   Gaia, neutral and enemy objects only\n6   All but your objects");
    Tasks_CarryCheck_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_CarryCheck = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnitTask);
    Tasks_CarryCheck->SetToolTip("Holding Attribute\n0   Right-click target is defined by the target diplomacy.\n1   Preceding the above, checks if target has more than 0 resource.");
    Tasks_CarryCheck_Text = new LinkedCheckBox(Units_Scroller, "Carry Check *", Tasks_CarryCheck);
    Tasks_PickForConstruction_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_PickForConstruction = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnitTask);
    Tasks_PickForConstruction->SetToolTip("1   Choose this task if targeting a construction");
    Tasks_PickForConstruction_Text = new LinkedCheckBox(Units_Scroller, "Building Pick *", Tasks_PickForConstruction);
    Tasks_GatherType_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_GatherType_Text = new SolidText(Units_Scroller, " Gather Type *");
    Tasks_GatherType = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnitTask);
    Tasks_GatherType->SetToolTip("Work Flag 1\nAoE 1: Used when farm is dead but still exists\n0   Plunder from resource\n1   Plunder from players\n2   Raider thing?");
    Tasks_SearchWaitTime_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_SearchWaitTime_Text = new SolidText(Units_Scroller, " Search Wait Time *");
    Tasks_SearchWaitTime = new NumberControl(CFloat, Units_Scroller, this, &uiGroupUnitTask);
    Tasks_SearchWaitTime->SetToolTip("Unused");
    Tasks_CombatLevelFlag_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_CombatLevelFlag = new NumberControl(CUByte, Units_Scroller, this, &uiGroupUnitTask);
    Tasks_CombatLevelFlag_Text = new LinkedCheckBox(Units_Scroller, "Unused Flag", Tasks_CombatLevelFlag);
    Tasks_WorkFlag2_Holder = new wxBoxSizer(wxVERTICAL);
    Tasks_WorkFlag2_Text = new SolidText(Units_Scroller, " Work Flag 2 *");
    Tasks_WorkFlag2 = new NumberControl(CShort, Units_Scroller, this, &uiGroupUnitTask);
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
    Units_SizeRadius_Holder->Add(Units_SizeRadius_Text);
    Units_MinCollisionSizeMultiplier_Holder->Add(Units_MinCollisionSizeMultiplier_Text);
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
    Units_TaskSwapGroup_Holder->Add(Units_TaskSwapGroup_Text);
    Units_AttackSound_Holder->Add(Units_AttackSound_Text);
    Units_MoveSound_Holder->Add(Units_MoveSound_Text);
    Units_Exists_Holder->Add(Units_Exists_Text);

//  Type 50+

    Units_BaseArmor_Holder->Add(Units_BaseArmor_Text);
    Units_DefenseTerrainBonus_Holder->Add(Units_DefenseTerrainBonus_Text);
    Units_BonusDamageResistance_Holder->Add(Units_BonusDamageResistance_Text);
    Units_MaxRange_Holder->Add(Units_MaxRange_Text);
    Units_BlastWidth_Holder->Add(Units_BlastWidth_Text);
    Units_ReloadTime_Holder->Add(Units_ReloadTime_Text);
    Units_AccuracyPercent_Holder->Add(Units_AccuracyPercent_Text);
    Units_Delay_Holder->Add(Units_Delay_Text);
    Units_GraphicDisplacement_Holder->Add(Units_GraphicDisplacement_Text);
    Units_BlastAttackLevel_Holder->Add(Units_BlastAttackLevel_Text);
    Units_BlastDamage_Holder->Add(Units_BlastDamage_Text);
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
    Units_SpawningGraphic_Holder->Add(Units_SpawningGraphic_Text);
    Units_UpgradeGraphic_Holder->Add(Units_UpgradeGraphic_Text);
    Units_HeroGlowGraphic_Holder->Add(Units_HeroGlowGraphic_Text);

//  Type 80

    Units_ConstructionGraphicID_Holder->Add(Units_ConstructionGraphicID_Text);
    Units_SnowGraphicID_Holder->Add(Units_SnowGraphicID_Text);
    Units_DestructionGraphicID_Holder->Add(Units_DestructionGraphicID_Text);
    Units_DestructionRubbleGraphicID_Holder->Add(Units_DestructionRubbleGraphicID_Text);
    Units_ResearchingGraphic_Holder->Add(Units_ResearchingGraphic_Text);
    Units_ResearchCompletedGraphic_Holder->Add(Units_ResearchCompletedGraphic_Text);
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
    Units_GarrisonRepairRate_Holder->Add(Units_GarrisonRepairRate_Text);
    Units_PileUnit_Holder->Add(Units_PileUnit_Text);
    Units_LootSwitch_Holder->Add(Units_LootSwitch_Text);

//  Type 10+

    Units_ID1_Holder->Add(Units_ID1);
    Units_UndeadMode_Holder->Add(Units_UndeadMode);
    Units_UndeadMode_Holder->Add(Units_UndeadMode_CheckBox, 0, wxLEFT, 2);
    Units_HitPoints_Holder->Add(Units_HitPoints);
    Units_LineOfSight_Holder->Add(Units_LineOfSight);
    for(size_t loop = 0; loop < 3; ++loop)
    Units_SizeRadius_Grid->Add(Units_SizeRadius[loop]);
    Units_MinCollisionSizeMultiplier_Holder->Add(Units_MinCollisionSizeMultiplier);
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
    for(size_t loop = 0; loop < 3; ++loop)
    Units_SelectionRadiusBox->Add(Units_SelectionRadius[loop]);
    Units_SelectionRadius_Holder->Add(Units_SelectionRadiusBox);
    Units_SelectionSound_Holder->Add(Units_WwiseSelectionSound, 0, wxEXPAND);
    Units_SelectionSound_Holder->Add(Units_SelectionSound, 0, wxEXPAND);
    Units_SelectionSound_Holder->Add(Units_SelectionSound_ComboBox);
    Units_DyingSound_Holder->Add(Units_WwiseDyingSound, 0, wxEXPAND);
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
    Units_TaskSwapGroup_Holder->Add(Units_TaskSwapGroup);
    Units_AttackSound_Holder->Add(Units_WwiseAttackSound, 0, wxEXPAND);
    Units_AttackSound_Holder->Add(Units_AttackSound, 0, wxEXPAND);
    Units_AttackSound_Holder->Add(Units_AttackSound_ComboBox);
    Units_MoveSound_Holder->Add(Units_WwiseMoveSound, 0, wxEXPAND);
    Units_MoveSound_Holder->Add(Units_MoveSound, 0, wxEXPAND);
    Units_MoveSound_Holder->Add(Units_MoveSound_ComboBox);
    Units_RunPattern_Holder->Add(Units_RunPattern_Text);
    Units_RunPattern_Holder->Add(Units_RunPattern);
    Units_Exists_Holder->Add(Units_Exists);

//  Type 50+

    Units_BaseArmor_Holder->Add(Units_BaseArmor);
    Units_DefenseTerrainBonus_Holder->Add(Units_DefenseTerrainBonus, 0, wxEXPAND);
    Units_DefenseTerrainBonus_Holder->Add(Units_DefenseTerrainBonus_ComboBox);
    Units_BonusDamageResistance_Holder->Add(Units_BonusDamageResistance);
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
    Units_BlastDamage_Holder->Add(Units_BlastDamage);
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
    Units_SpawningGraphic_Holder->Add(Units_SpawningGraphic, 0, wxEXPAND);
    Units_SpawningGraphic_Holder->Add(Units_SpawningGraphic_ComboBox);
    Units_UpgradeGraphic_Holder->Add(Units_UpgradeGraphic, 0, wxEXPAND);
    Units_UpgradeGraphic_Holder->Add(Units_UpgradeGraphic_ComboBox);
    Units_HeroGlowGraphic_Holder->Add(Units_HeroGlowGraphic, 0, wxEXPAND);
    Units_HeroGlowGraphic_Holder->Add(Units_HeroGlowGraphic_ComboBox);

//  Type 80

    Units_ConstructionGraphicID_Holder->Add(Units_ConstructionGraphicID, 0, wxEXPAND);
    Units_ConstructionGraphicID_Holder->Add(Units_ConstructionGraphicID_ComboBox);
    Units_SnowGraphicID_Holder->Add(Units_SnowGraphicID, 0, wxEXPAND);
    Units_SnowGraphicID_Holder->Add(Units_SnowGraphicID_ComboBox);
    Units_DestructionGraphicID_Holder->Add(Units_DestructionGraphicID, 0, wxEXPAND);
    Units_DestructionGraphicID_Holder->Add(Units_DestructionGraphicID_ComboBox);
    Units_DestructionRubbleGraphicID_Holder->Add(Units_DestructionRubbleGraphicID, 0, wxEXPAND);
    Units_DestructionRubbleGraphicID_Holder->Add(Units_DestructionRubbleGraphicID_ComboBox);
    Units_ResearchingGraphic_Holder->Add(Units_ResearchingGraphic, 0, wxEXPAND);
    Units_ResearchingGraphic_Holder->Add(Units_ResearchingGraphic_ComboBox);
    Units_ResearchCompletedGraphic_Holder->Add(Units_ResearchCompletedGraphic, 0, wxEXPAND);
    Units_ResearchCompletedGraphic_Holder->Add(Units_ResearchCompletedGraphic_ComboBox);
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
    Units_TransformSound_Holder->Add(Units_WwiseTransformSound, 0, wxEXPAND);
    Units_TransformSound_Holder->Add(Units_TransformSound, 0, wxEXPAND);
    Units_TransformSound_Holder->Add(Units_TransformSound_ComboBox);
    Units_ConstructionSound_Holder->Add(Units_WwiseConstructionSound, 0, wxEXPAND);
    Units_ConstructionSound_Holder->Add(Units_ConstructionSound, 0, wxEXPAND);
    Units_ConstructionSound_Holder->Add(Units_ConstructionSound_ComboBox);
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
    Units_GraphicsArea5_Holder->Add(Units_ConstructionGraphicID_Holder);
    Units_GraphicsArea5_Holder->Add(Units_AttackGraphic_Holder);
    Units_GraphicsArea5_Holder->Add(Units_GarrisonGraphic_Holder);
    Units_GraphicsArea5_Holder->Add(Units_DestructionGraphicID_Holder);
    Units_GraphicsArea5_Holder->Add(Units_DestructionRubbleGraphicID_Holder);
    Units_GraphicsArea5_Holder->Add(Units_SpawningGraphic_Holder);
    Units_GraphicsArea5_Holder->Add(Units_UpgradeGraphic_Holder);
    Units_GraphicsArea5_Holder->Add(Units_ResearchingGraphic_Holder);
    Units_GraphicsArea5_Holder->Add(Units_ResearchCompletedGraphic_Holder);
    Units_GraphicsArea5_Holder->Add(Units_HeroGlowGraphic_Holder);

    DamageGraphics_GraphicID_Holder->Add(DamageGraphics_GraphicID_Text);
    DamageGraphics_GraphicID_Holder->Add(DamageGraphics_GraphicID, 0, wxEXPAND);
    DamageGraphics_GraphicID_Holder->Add(DamageGraphics_GraphicID_ComboBox);
    DamageGraphics_DamagePercent_Holder->Add(DamageGraphics_DamagePercent_Text);
    DamageGraphics_DamagePercent_Holder->Add(DamageGraphics_DamagePercent);
    DamageGraphics_ApplyMode_Holder->Add(DamageGraphics_ApplyMode_Text);
    DamageGraphics_ApplyMode_Holder->Add(DamageGraphics_ApplyMode);
    Units_DamageGraphics_Holder_Data->Add(slp_dmg_unit, 0, wxBOTTOM, 5);
    Units_DamageGraphics_Holder_Data->Add(DamageGraphics_GraphicID_Holder);
    Units_DamageGraphics_Holder_Data->Add(DamageGraphics_DamagePercent_Holder, 0, wxTOP, 5);
    Units_DamageGraphics_Holder_Data->Add(DamageGraphics_ApplyMode_Holder, 0, wxTOP, 5);

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
    Units_Attacks_Holder_Data->Add(Units_BlastDamage_Holder);

    Units_Armors_DataArea->Add(Armors_Amount_Holder);
    Units_Armors_DataArea->Add(Armors_Class_Holder, 0, wxTOP, 5);
    Units_Defense_Holder->Add(Units_BlastDefenseLevel_Holder);
    Units_Defense_Holder->Add(Units_BonusDamageResistance_Holder);
    Units_Defense_Holder->Add(Units_BaseArmor_Holder);
    Units_Armors_Holder_Data3->Add(Units_Defense_Holder, 0, wxTOP, 5);
    Units_Armors_Holder_Data3->Add(Units_DefenseTerrainBonus_Holder, 0, wxTOP, 5);
    Units_Armors_Holder_Data3->Add(Units_DisplayedMeleeArmour_Holder, 0, wxTOP, 5);
    Units_Armors_Holder_Data3->Add(Units_DisplayedPierceArmour_Holder, 0, wxTOP, 5);

    for(size_t loop = 0; loop < 8; ++loop)
    Units_GarrisonType_Grid->Add(Units_GarrisonType_CheckBox[loop]);
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
    Units_Garrison_Grid->Add(Units_GarrisonCapacity_Text);
    Units_Garrison_Grid->Add(Units_GarrisonType_Text);
    Units_Garrison_Grid->Add(Units_GarrisonHealRate_Text);
    Units_Garrison_Grid->Add(Units_GarrisonCapacity);
    Units_Garrison_Grid->Add(Units_GarrisonType_Holder);
    Units_Garrison_Grid->Add(Units_GarrisonHealRate);
    Units_Resource_Grid->Add(Units_ResourceCapacity_Text);
    Units_Resource_Grid->Add(Units_ResourceDecay_Text);
    Units_Resource_Grid->Add(Units_WorkRate_Text);
    Units_Resource_Grid->Add(Units_MinConversionTimeMod_Text);
    Units_Resource_Grid->Add(Units_MaxConversionTimeMod_Text);
    Units_Resource_Grid->Add(Units_ConversionChanceMod_Text);
    Units_Resource_Grid->Add(Units_ResourceCapacity);
    Units_Resource_Grid->Add(Units_ResourceDecay);
    Units_Resource_Grid->Add(Units_WorkRate);
    Units_Resource_Grid->Add(Units_MinConversionTimeMod);
    Units_Resource_Grid->Add(Units_MaxConversionTimeMod);
    Units_Resource_Grid->Add(Units_ConversionChanceMod);

    Units_Charge_Grid->Add(Units_MaxCharge_Text);
    Units_Charge_Grid->Add(Units_RechargeRate_Text);
    Units_Charge_Grid->Add(Units_ChargeEvent_Text);
    Units_Charge_Grid->Add(Units_ChargeType_Text);
    Units_Charge_Grid->Add(Units_MaxCharge);
    Units_Charge_Grid->Add(Units_RechargeRate);
    Units_Charge_Grid->Add(Units_ChargeEvent);
    Units_Charge_Grid->Add(Units_ChargeType);

    Units_StatsArea_Holder->Add(Units_StatsArea1A_Sizer);
    Units_StatsArea_Holder->Add(Units_StatsArea1B_Sizer, 0, wxTOP, 5);
    Units_StatsArea_Holder->Add(Units_Attacks_Holder, 0, wxEXPAND | wxTOP, 5);
    Units_StatsArea_Holder->Add(Units_Armors_Holder, 0, wxEXPAND | wxTOP, 5);
    Units_StatsArea_Holder->Add(Units_Resource_Grid, 0, wxTOP, 5);
    Units_StatsArea_Holder->Add(Units_Garrison_Grid, 0, wxTOP, 5);
    Units_StatsArea_Holder->Add(Units_Charge_Grid, 0, wxTOP, 5);

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

    DropSites_UnitID_Holder->Add(DropSites_UnitID_Text);
    DropSites_UnitID_Holder->Add(DropSites_UnitID, 0, wxEXPAND);
    DropSites_UnitID_Holder->Add(DropSites_UnitID_ComboBox);

    Units_DropSites_Buttons_Upper->Add(Units_DropSites_Add, 1, wxEXPAND);
    Units_DropSites_Buttons_Upper->Add(Units_DropSites_Delete, 1, wxEXPAND);
    Units_DropSites_Buttons_Upper->Add(Units_DropSites_Insert, 1, wxEXPAND);
    Units_DropSites_Buttons_Lower->Add(Units_DropSites_Copy, 1, wxEXPAND);
    Units_DropSites_Buttons_Lower->Add(Units_DropSites_Paste, 1, wxEXPAND);
    Units_DropSites_Buttons_Lower->Add(Units_DropSites_PasteInsert, 1, wxEXPAND);

    Units_DropSites_ListArea->Add(Units_DropSites_Search, 0, wxEXPAND);
    Units_DropSites_ListArea->Add(Units_DropSites_Search_R, 0, wxEXPAND);
    Units_DropSites_ListArea->Add(Units_DropSites_ListV, 1, wxEXPAND | wxBOTTOM | wxTOP, 2);
    Units_DropSites_ListArea->Add(Units_DropSites_Buttons_Upper, 0, wxEXPAND);
    Units_DropSites_ListArea->Add(Units_DropSites_Buttons_Lower, 0, wxEXPAND);
    Units_DropSites_ListArea->Add(Units_DropSites_CopyToUnits, 0, wxEXPAND | wxTOP, 2);

    Units_DropSites->Add(Units_DropSites_ListArea, 1, wxEXPAND);
    Units_DropSites->Add(DropSites_UnitID_Holder, 0, wxLEFT, 5);

    Units_A2_Grid->Add(Units_Trait_Holder);
    Units_AS_Holder->Add(Units_SizeRadius_Holder);
    Units_AS_Holder->Add(Units_MinCollisionSizeMultiplier_Holder, 0, wxLEFT, 5);
    Units_AS1_Grid->Add(Units_OcclusionMode_Holder, 0, wxRIGHT, 5);
    Units_AS1_Grid->Add(Units_ObstructionType_Holder, 0, wxRIGHT, 5);
    Units_AS1_Grid->Add(Units_ObstructionClass_Holder, 0, wxRIGHT, 5);
    Units_AS1_Grid->Add(Units_SelectionEffect_Holder, 0, wxRIGHT, 5);
    Units_AS1_Grid->Add(Units_EditorSelectionColour_Holder);
    Units_ResourceStorageHeader_Holder->Add(Units_ResourceStorage_Texts);
    for (wxBoxSizer *&sizer : Units_ResourceStorage_Holder)
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
    for (wxBoxSizer *&sizer : Unit_Cost_Sizers)
    Units_CostHeader_Holder->Add(sizer, 0, wxLEFT, 5);
    Units_Training_Grid->Add(Units_InterfaceKind_Holder);
    Units_Training_Grid->Add(Units_TrainTime_Holder, 0, wxLEFT, 5);
    Units_Training_Grid->Add(Units_TrainLocationID_Holder, 0, wxLEFT, 5);
    Units_A3_Grid->Add(Units_StackUnitID_Holder);
    Units_A5_Grid->Add(Units_TerrainID_Holder);
    Units_A5_Grid->Add(Units_ResearchID_Holder);
    Units_A5_Grid->Add(Units_DefaultTaskID_Holder);
    Units_A3_Grid->Add(Units_HeadUnit_Holder, 0, wxLEFT, 5);
    Units_A3_Grid->Add(Units_TransformUnit_Holder, 0, wxLEFT, 5);
    Units_A3_Grid->Add(Units_PileUnit_Holder, 0, wxLEFT, 5);
    Units_Training_Grid->Add(Units_ButtonID_Holder, 0, wxLEFT, 5);
    Units_AS2_Holder->Add(Units_SelectionRadius_Holder);
    Units_AS2_Holder->Add(Units_ClearanceSize_Holder, 0, wxLEFT, 5);

    Units_Attributes_Holder->Add(Units_AB1_Grid);
    Units_Attributes_Holder->Add(Units_AM1_Grid, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_A2_Grid, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_A1_Grid, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_A4_Grid, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_A5_Grid, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_DropSites, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_AS_Holder, 0, wxTOP, 5);
    Units_Attributes_Holder->Add(Units_AS2_Holder, 0, wxTOP, 5);
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
    Units_TrainSound_Holder->Add(Units_WwiseTrainSound, 0, wxEXPAND);
    Units_TrainSound_Holder->Add(Units_TrainSound, 0, wxEXPAND);
    Units_TrainSound_Holder->Add(Units_TrainSound_ComboBox);
    Units_DamageSound_Holder->Add(Units_WwiseDamageSound, 0, wxEXPAND);
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
        if(loop == 4)
        {
            wxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
            sizer->Add(Tasks_Graphics[loop], 1, wxEXPAND);
            sizer->Add(Tasks_WwiseResourceGatheringSound, 2, wxEXPAND);
            Tasks_Graphics_Holder[loop]->Add(sizer, 0, wxEXPAND);
        }
        else if(loop == 5)
        {
            wxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
            sizer->Add(Tasks_Graphics[loop], 1, wxEXPAND);
            sizer->Add(Tasks_WwiseResourceDepositSound, 2, wxEXPAND);
            Tasks_Graphics_Holder[loop]->Add(sizer, 0, wxEXPAND);
        }
        else
        {
            Tasks_Graphics_Holder[loop]->Add(Tasks_Graphics[loop], 0, wxEXPAND);
        }
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
        if(GenieVersion >= genie::GV_AoK && (GenieVersion < genie::GV_C15 || GenieVersion > genie::GV_LatestDE2)) // AoK, TC, SWGB or CC
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
        How2List = ListMode::ADD;
        ListUnits(UnitCivID);

        if(GenieVersion < genie::GV_SWGB && dataset->Civs.front().Units.size() > 900) SetStatusText("Units between 900 and 1000 mess up the AI!", 0);
    });

    Units_Insert->Bind(wxEVT_BUTTON, [this](wxCommandEvent&)
    {
        size_t selections = Units_ListV->GetSelectedCount();
        if (!selections) return;

        wxBusyCursor WaitCursor;
        if(GenieVersion >= genie::GV_AoK && (GenieVersion < genie::GV_C15 || GenieVersion > genie::GV_LatestDE2))   // AoK, TC, SWGB or CC
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
        How2List = ListMode::INSNEW;
        ListUnits(UnitCivID);
    });

    Units_Delete->Bind(wxEVT_BUTTON, [this](wxCommandEvent&)
    {
        size_t selections = Units_ListV->GetSelectedCount();
        if (!selections) return;

        wxBusyCursor WaitCursor;
        if(GenieVersion >= genie::GV_AoK && (GenieVersion < genie::GV_C15 || GenieVersion > genie::GV_LatestDE2))
        {
            DeleteFromList(dataset->UnitHeaders, UnitIDs);
        }

        for (size_t civ = 0; civ < dataset->Civs.size(); ++civ)
        {
            size_t baseId = 0;
            for (size_t copyId = 0, rightId = 0, endId = dataset->Civs[civ].Units.size(), lastId = UnitIDs.size(); copyId < endId; ++copyId)
            {
                if (baseId != static_cast<size_t>(UnitIDs[rightId]))
                {
                    if (baseId != copyId)
                    {
                        dataset->Civs[civ].UnitPointers[baseId] = std::move(dataset->Civs[civ].UnitPointers[copyId]);
                        dataset->Civs[civ].Units[baseId] = std::move(dataset->Civs[civ].Units[copyId]);
                        dataset->Civs[civ].Units[baseId].ID = baseId;
                        dataset->Civs[civ].Units[baseId].CopyID = baseId;
                        dataset->Civs[civ].Units[baseId].BaseID = baseId;
                    }
                    ++baseId;
                }
                else
                {
                    if (rightId < lastId)
                    {
                        ++rightId;
                    }
                }
            }
            dataset->Civs[civ].UnitPointers.resize(baseId);
            dataset->Civs[civ].Units.resize(baseId);
            How2List = ListMode::DEL;
        }
        How2List = ListMode::DEL;
        ListUnits(UnitCivID);
    });

    Units_Copy->Bind(wxEVT_BUTTON, [this](wxCommandEvent&)
    {
        size_t selections = Units_ListV->GetSelectedCount();
        if (!selections) return;

        wxBusyCursor WaitCursor;
        if(GenieVersion < genie::GV_AoK || GenieVersion >= genie::GV_C15 && GenieVersion <= genie::GV_LatestDE2)
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

        size_t CivCount = dataset->Civs.size();
        copies.Dat.UnitExists.resize(CivCount);
        if (Units_SpecialCopy_Civs->GetValue())
        {
            copies.Dat.AllCivs |= 0x01;
        }
        else copies.Dat.AllCivs &= ~0x01;
        if(copies.Dat.AllCivs & 0x01)
        {
            copies.Dat.UnitCopies.resize(CivCount);
            for(size_t civ = 0; civ < CivCount; ++civ)
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
            for(size_t civ = 0; civ < CivCount; ++civ)
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
        size_t selections = Units_ListV->GetSelectedCount();
        if (!selections) return;

        wxBusyCursor WaitCursor;
        if (Units_SpecialCopy_Civs->GetValue())
        {
            copies.Dat.AllCivs |= 0x02;
        }
        else copies.Dat.AllCivs &= ~0x02;
        if(copies.Dat.AllCivs & 0x02)
        {
            size_t CivCount = dataset->Civs.size();
            copies.Dat.UnitGraphics.resize(CivCount);
            for(size_t civ = 0; civ < CivCount; ++civ)
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
        size_t CopyCount = copies.Dat.UnitGraphics.front().size();
        if(!Units_ListV->GetSelectedCount() || CopyCount == 0) return;

        wxBusyCursor WaitCursor;
        if(Paste11)
        {
            if(Paste11Check(UnitIDs.size(), CopyCount))
            {
                if(copies.Dat.AllCivs & 0x02)
                {
                    size_t CivCount = dataset->Civs.size();
                    size_t FillingCiv = (copies.Dat.UnitGraphics.size() > 1) ? 1 : 0;
                    copies.Dat.UnitGraphics.resize(CivCount, copies.Dat.UnitGraphics[FillingCiv]);
                    for(size_t civ = 0; civ < CivCount; ++civ)
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
                size_t CivCount = dataset->Civs.size();
                size_t FillingCiv = (copies.Dat.UnitGraphics.size() > 1) ? 1 : 0;
                copies.Dat.UnitGraphics.resize(CivCount, copies.Dat.UnitGraphics[FillingCiv]);
                for(size_t civ = 0; civ < CivCount; ++civ)
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
        size_t numUnitCopies = copies.Dat.UnitCopies.front().size();
        if(Paste11)
        {
            if(Paste11Check(UnitIDs.size(), copies.Dat.UnitExists.front().size()))
            {
                if(GenieVersion >= genie::GV_AoK && (GenieVersion < genie::GV_C15 || GenieVersion > genie::GV_LatestDE2))
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
                    for(size_t loop = 0; loop < numUnitCopies; ++loop)
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
            if(GenieVersion >= genie::GV_AoK && (GenieVersion < genie::GV_C15 || GenieVersion > genie::GV_LatestDE2))
            {
                if(copies.UnitHeader.size()+UnitIDs.front() > dataset->UnitHeaders.size())
                dataset->UnitHeaders.resize(copies.UnitHeader.size()+UnitIDs.front());
                for(size_t loop = 0; loop < copies.UnitHeader.size(); ++loop)
                {
                    copies.UnitHeader[loop].setGameVersion(GenieVersion);
                    dataset->UnitHeaders[UnitIDs.front()+loop] = copies.UnitHeader[loop];
                }
            }

            if(numUnitCopies+UnitIDs.front() > dataset->Civs.front().Units.size())
            for(size_t civ = 0; civ < dataset->Civs.size(); ++civ) // Resize if not enough room.
            {
                dataset->Civs[civ].Units.resize(numUnitCopies+UnitIDs.front());
                dataset->Civs[civ].UnitPointers.resize(numUnitCopies+UnitIDs.front());
            }
            PasteUnits();
            for(size_t civ = 0; civ < dataset->Civs.size(); ++civ)
            {
                for(size_t loop = 0; loop < numUnitCopies; ++loop)
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
        How2List = ListMode::PASTE;
        ListUnits(UnitCivID);

        SetStatusText("Unit special paste", 2);
        SetStatusText(wxString::Format("Edits: %zu + %zu", popUp.unSaved, numUnitCopies), 3);
        popUp.unSaved += numUnitCopies;
    });

    Units_PasteInsert->Bind(wxEVT_BUTTON, [this](wxCommandEvent&)
    {
        if(!Units_ListV->GetSelectedCount() || copies.Dat.UnitExists.size() == 0) return;

        wxBusyCursor WaitCursor;
        if(GenieVersion >= genie::GV_AoK && (GenieVersion < genie::GV_C15 || GenieVersion > genie::GV_LatestDE2))
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
        size_t numUnitCopies = copies.Dat.UnitCopies.front().size();
        for(size_t civ = 0; civ < dataset->Civs.size(); ++civ)
        {
            dataset->Civs[civ].Units.insert(dataset->Civs[civ].Units.begin() + UnitIDs.front(), numUnitCopies, Temp2);
            dataset->Civs[civ].UnitPointers.insert(dataset->Civs[civ].UnitPointers.begin() + UnitIDs.front(), numUnitCopies, 0);
        }
        PasteUnits();
        for(size_t civ = 0; civ < dataset->Civs.size(); ++civ)
        {
            for(size_t loop = 0; loop < numUnitCopies; ++loop)
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
        How2List = ListMode::INSPASTE;
        ListUnits(UnitCivID);
    });

    Units_Enable->Bind(wxEVT_BUTTON, [this](wxCommandEvent&)
    {
        size_t selections = Units_ListV->GetSelectedCount();
        if (!selections) return;

        wxBusyCursor WaitCursor;
        int UnitCivID = Units_Civs_List->GetSelection();
        for(size_t sel = 0; sel < selections; ++sel)
        {
            // Find the correct sizes for subvectors.
            short UnitType = 10, DamageGraphics = 0, DropSites = 0, Attacks = 0, Armors = 0, Commands = 0;
            for(size_t civ = 0; civ < dataset->Civs.size(); ++civ)
            {
                if(dataset->Civs[civ].UnitPointers[UnitIDs[sel]] != 0)
                {
                    UnitType = dataset->Civs[civ].Units[UnitIDs[sel]].Type;
                    DamageGraphics = dataset->Civs[civ].Units[UnitIDs[sel]].DamageGraphics.size();
                    Attacks = dataset->Civs[civ].Units[UnitIDs[sel]].Type50.Attacks.size();
                    Armors = dataset->Civs[civ].Units[UnitIDs[sel]].Type50.Armours.size();
                    Commands = dataset->Civs[civ].Units[UnitIDs[sel]].Bird.TaskList.size();
                    DropSites = dataset->Civs[civ].Units[UnitIDs[sel]].Bird.DropSites.size();
                    break;
                }
            }
            // All subvectors need to be resized!
            if(Units_SpecialCopy_Civs->GetValue())
            for(size_t civ = 0; civ < dataset->Civs.size(); ++civ)
            {
                if(dataset->Civs[civ].UnitPointers[UnitIDs[sel]] == 0)
                {
                    dataset->Civs[civ].UnitPointers[UnitIDs[sel]] = 1;
                    dataset->Civs[civ].Units[UnitIDs[sel]].Type = UnitType;
                    dataset->Civs[civ].Units[UnitIDs[sel]].DamageGraphics.resize(DamageGraphics);
                    dataset->Civs[civ].Units[UnitIDs[sel]].Type50.Attacks.resize(Attacks);
                    dataset->Civs[civ].Units[UnitIDs[sel]].Type50.Armours.resize(Armors);
                    dataset->Civs[civ].Units[UnitIDs[sel]].Bird.TaskList.resize(Commands);
                    dataset->Civs[civ].Units[UnitIDs[sel]].Bird.DropSites.resize(DropSites);
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
                    dataset->Civs[UnitCivID].Units[UnitIDs[sel]].Type50.Attacks.resize(Attacks);
                    dataset->Civs[UnitCivID].Units[UnitIDs[sel]].Type50.Armours.resize(Armors);
                    dataset->Civs[UnitCivID].Units[UnitIDs[sel]].Bird.TaskList.resize(Commands);
                    dataset->Civs[UnitCivID].Units[UnitIDs[sel]].Bird.DropSites.resize(DropSites);
                    dataset->Civs[UnitCivID].Units[UnitIDs[sel]].ID = UnitIDs[sel]; // ID Fix
                    dataset->Civs[UnitCivID].Units[UnitIDs[sel]].CopyID = UnitIDs[sel];
                    if(GenieVersion >= genie::GV_AoKA)
                    dataset->Civs[UnitCivID].Units[UnitIDs[sel]].BaseID = UnitIDs[sel];
                }
            }
        }
        How2List = ListMode::ENABLE;
        ListUnits(UnitCivID);
    });

    Units_Disable->Bind(wxEVT_BUTTON, [this](wxCommandEvent&)
    {
        size_t selections = Units_ListV->GetSelectedCount();
        if (!selections) return;

        wxBusyCursor WaitCursor;
        int UnitCivID = Units_Civs_List->GetSelection();
        for(size_t sel = 0; sel < selections; ++sel)
        {
            if(Units_SpecialCopy_Civs->GetValue())
            for(size_t civ = 0; civ < dataset->Civs.size(); ++civ)
            dataset->Civs[civ].UnitPointers[UnitIDs[sel]] = 0;
            else
            dataset->Civs[UnitCivID].UnitPointers[UnitIDs[sel]] = 0;
        }
        How2List = ListMode::ENABLE;
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
    Units_DropSites_Search->Bind(wxEVT_TEXT, &AGE_Frame::OnUnitDropSitesSearch, this);
    Units_DropSites_Search_R->Bind(wxEVT_TEXT, &AGE_Frame::OnUnitDropSitesSearch, this);
    Units_DropSites_ListV->Bind(wxEVT_LISTBOX, &AGE_Frame::OnUnitDropSiteSelect, this);
    Units_DropSites_Add->Bind(wxEVT_BUTTON, [this](wxCommandEvent &event)
    {
        if (!Units_ListV->GetSelectedCount()) return;

        wxBusyCursor WaitCursor;
        for (size_t loop = 0; loop < dataset->Civs.size(); ++loop)
        {
            if (dataset->Civs[loop].UnitPointers[UnitIDs.front()] != 0)
            dataset->Civs[loop].Units[UnitIDs.front()].Bird.DropSites.push_back(-1);
        }
        How2List = ListMode::ADD;
        ListUnitDropSites();
    });
    Units_DropSites_Insert->Bind(wxEVT_BUTTON, [this](wxCommandEvent &event)
    {
        if (!Units_DropSites_ListV->GetSelectedCount()) return;

        wxBusyCursor WaitCursor;
        for (size_t loop = 0; loop < dataset->Civs.size(); ++loop)
        {
            if (dataset->Civs[loop].UnitPointers[UnitIDs.front()] != 0)
            dataset->Civs[loop].Units[UnitIDs.front()].Bird.DropSites.insert(dataset->Civs[loop].Units[UnitIDs.front()].Bird.DropSites.begin() + DropSiteIDs.front(), -1);
        }
        How2List = ListMode::INSNEW;
        ListUnitDropSites();
    });
    Units_DropSites_Delete->Bind(wxEVT_BUTTON, [this](wxCommandEvent &event)
    {
        size_t selections = Units_DropSites_ListV->GetSelectedCount();
        if (!selections) return;

        wxBusyCursor WaitCursor;
        for (short civ = 0; civ < dataset->Civs.size(); ++civ)
        {
            if (dataset->Civs[civ].UnitPointers[UnitIDs.front()] != 0)
            if (dataset->Civs[civ].Units[UnitIDs.front()].Bird.DropSites.size())
            DeleteFromList(dataset->Civs[civ].Units[UnitIDs.front()].Bird.DropSites, DropSiteIDs);
        }
        ListUnitDropSites();
    });
    Units_DropSites_Copy->Bind(wxEVT_BUTTON, [this](wxCommandEvent &event)
    {
        if (!Units_DropSites_ListV->GetSelectedCount()) return;

        wxBusyCursor WaitCursor;
        if (Units_SpecialCopy_Civs->GetValue())
        {
            copies.Dat.AllCivs |= 0x100;
        }
        else copies.Dat.AllCivs &= ~0x100;
        if (copies.Dat.AllCivs & 0x100)
        {
            short CivCount = dataset->Civs.size();
            copies.Dat.UnitDropSiteExists.resize(CivCount);
            copies.Dat.UnitDropSites.resize(CivCount);
            for (short civ = 0, copy = 0; civ < dataset->Civs.size(); ++civ)
            {
                if (dataset->Civs[civ].UnitPointers[UnitIDs.front()] == 0)
                {
                    // Graphic set info not usefull.
                    copies.Dat.UnitDropSiteExists[civ] = 255;
                    CivCount--;
                }
                else
                {
                    // Save info of graphic set to intelligently fill possible gaps when pasting.
                    copies.Dat.UnitDropSiteExists[civ] = 256 + dataset->Civs[civ].IconSet;
                    // Only copy drop sites from civs which have this unit enabled.
                    CopyFromList(dataset->Civs[civ].Units[UnitIDs.front()].Bird.DropSites, DropSiteIDs, copies.Dat.UnitDropSites[copy]); copy++;
                }
            }
            copies.Dat.UnitDropSites.resize(CivCount);
        }
        else
        {
            CopyFromList(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.DropSites, DropSiteIDs, copies.Dat.UnitDropSites.front());
        }
        Units_DropSites_ListV->SetFocus();
    });
    Units_DropSites_Paste->Bind(wxEVT_BUTTON, [this](wxCommandEvent &event)
    {
        if (!Units_DropSites_ListV->GetSelectedCount()) return;

        wxBusyCursor WaitCursor;
        if (copies.Dat.AllCivs & 0x100)
        {
            for (size_t civ = 0, copy = 0; civ < dataset->Civs.size(); ++civ)
            {
                if (dataset->Civs[civ].UnitPointers[UnitIDs.front()] == 0)
                {
                    // Consume copies.
                    if (copies.Dat.UnitDropSiteExists[civ] > 255) ++copy;
                    continue;
                }
                // If the target unit exists then choose from following.
                if (copies.Dat.UnitDropSiteExists[civ] > 255 && copy < copies.Dat.UnitDropSites.size())
                {
                    PasteToListNoGV(dataset->Civs[civ].Units[UnitIDs.front()].Bird.DropSites, DropSiteIDs, copies.Dat.UnitDropSites[copy]); ++copy;
                }
                else
                {
                    PasteToListNoGV(dataset->Civs[civ].Units[UnitIDs.front()].Bird.DropSites, DropSiteIDs, copies.Dat.UnitDropSites.front());
                }
            }
        }
        else
        {
            PasteToListNoGV(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.DropSites, DropSiteIDs, copies.Dat.UnitDropSites.front());
        }
        ListUnitDropSites();
    });
    Units_DropSites_PasteInsert->Bind(wxEVT_BUTTON, [this](wxCommandEvent &event)
    {
        if (!Units_DropSites_ListV->GetSelectedCount()) return;

        wxBusyCursor WaitCursor;
        if (copies.Dat.AllCivs & 0x100)
        {
            for (short civ = 0, copy = 0; civ < dataset->Civs.size(); ++civ)
            {
                if (dataset->Civs[civ].UnitPointers[UnitIDs.front()] == 0)
                {
                    // Consume copies.
                    if (copies.Dat.UnitDropSiteExists[civ] > 255) ++copy;
                    continue;
                }
                // If the target unit exists then choose from following.
                if (copies.Dat.UnitDropSiteExists[civ] > 255 && copy < copies.Dat.UnitDropSites.size())
                {
                    PasteInsertToListNoGV(dataset->Civs[civ].Units[UnitIDs.front()].Bird.DropSites, DropSiteIDs.front(), copies.Dat.UnitDropSites[copy]); copy++;
                }
                else
                {
                    PasteInsertToListNoGV(dataset->Civs[civ].Units[UnitIDs.front()].Bird.DropSites, DropSiteIDs.front(), copies.Dat.UnitDropSites.front());
                }
            }
        }
        else
        {
            PasteInsertToListNoGV(dataset->Civs[UnitCivID].Units[UnitIDs.front()].Bird.DropSites, DropSiteIDs.front(), copies.Dat.UnitDropSites.front());
        }
        ListUnitDropSites();
    });
    Units_DropSites_CopyToUnits->Bind(wxEVT_BUTTON, [this](wxCommandEvent &event)
    {
        for (short civ = 0; civ < dataset->Civs.size(); ++civ)
        for (size_t loop = 1; loop < UnitIDs.size(); ++loop)
        {
            dataset->Civs[civ].Units[UnitIDs[loop]].Bird.DropSites = dataset->Civs[civ].Units[UnitIDs.front()].Bird.DropSites;
        }
    });
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

    auto SaveThenSelectUnit = [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        wxCommandEvent e;
        OnUnitSelect(e);
    };
    auto TrySaveThenSelectUnit = [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            wxCommandEvent e;
            OnUnitSelect(e);
        }
    };
    Units_Type->Bind(wxEVT_KILL_FOCUS, TrySaveThenSelectUnit);
    Units_Type->Bind(wxEVT_TEXT_ENTER, SaveThenSelectUnit);
    Units_Type_ComboBox->Bind(wxEVT_COMBOBOX, [this](wxCommandEvent& event)
    {
        switch (event.GetSelection())
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
        OnUnitSelect(e);
    });

    auto SaveThenListUnits = [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        ListUnits(UnitCivID);
    };
    auto TrySaveThenListUnits = [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            ListUnits(UnitCivID);
        }
    };
    Units_Name->Bind(wxEVT_KILL_FOCUS, TrySaveThenListUnits);
    Units_Name->Bind(wxEVT_TEXT_ENTER, SaveThenListUnits);
    Units_Name2->Bind(wxEVT_KILL_FOCUS, TrySaveThenSelectUnit);
    Units_Name2->Bind(wxEVT_TEXT_ENTER, SaveThenSelectUnit);
    Units_LanguageDLLName->Bind(wxEVT_KILL_FOCUS, TrySaveThenListUnits);
    Units_LanguageDLLName->Bind(wxEVT_TEXT_ENTER, SaveThenListUnits);
    Units_LanguageDLLCreation->Bind(wxEVT_KILL_FOCUS, TrySaveThenSelectUnit);
    Units_LanguageDLLCreation->Bind(wxEVT_TEXT_ENTER, SaveThenSelectUnit);
    Units_HotKey->Bind(wxEVT_KILL_FOCUS, TrySaveThenSelectUnit);
    Units_HotKey->Bind(wxEVT_TEXT_ENTER, SaveThenSelectUnit);
    Units_LanguageDLLHelp->Bind(wxEVT_KILL_FOCUS, TrySaveThenSelectUnit);
    Units_LanguageDLLHelp->Bind(wxEVT_TEXT_ENTER, SaveThenSelectUnit);
    Units_LanguageDLLHotKeyText->Bind(wxEVT_KILL_FOCUS, TrySaveThenSelectUnit);
    Units_LanguageDLLHotKeyText->Bind(wxEVT_TEXT_ENTER, SaveThenSelectUnit);
    Units_Trait->Bind(wxEVT_KILL_FOCUS, TrySaveThenSelectUnit);
    Units_Trait->Bind(wxEVT_TEXT_ENTER, SaveThenSelectUnit);
    Units_GarrisonType->Bind(wxEVT_KILL_FOCUS, TrySaveThenSelectUnit);
    Units_GarrisonType->Bind(wxEVT_TEXT_ENTER, SaveThenSelectUnit);

    auto SaveThenListDamageGraphics = [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        ListUnitDamageGraphics();
    };
    auto TrySaveThenListDamageGraphics = [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            ListUnitDamageGraphics();
        }
    };
    DamageGraphics_GraphicID->Bind(wxEVT_KILL_FOCUS, TrySaveThenListDamageGraphics);
    DamageGraphics_GraphicID->Bind(wxEVT_TEXT_ENTER, SaveThenListDamageGraphics);
    DamageGraphics_GraphicID_ComboBox->Bind(wxEVT_COMBOBOX, [this](wxCommandEvent& event)
    {
        static_cast<LinkedComboBox*>(event.GetEventObject())->OnChoose(event);
        ListUnitDamageGraphics();
    });
    DamageGraphics_DamagePercent->Bind(wxEVT_KILL_FOCUS, TrySaveThenListDamageGraphics);
    DamageGraphics_DamagePercent->Bind(wxEVT_TEXT_ENTER, SaveThenListDamageGraphics);
    auto SaveThenRenderUnit = [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        wxCommandEvent E;
        OnChooseGraphic(E);
    };
    auto TrySaveThenRenderUnit = [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            wxCommandEvent E;
            OnChooseGraphic(E);
        }
    };
    DropSites_UnitID->Bind(wxEVT_KILL_FOCUS, [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            ListUnitDropSites();
        }
    });
    DropSites_UnitID->Bind(wxEVT_TEXT_ENTER, [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        ListUnitDropSites();
    });
    DropSites_UnitID_ComboBox->Bind(wxEVT_COMBOBOX, [this](wxCommandEvent& event)
    {
        static_cast<LinkedComboBox*>(event.GetEventObject())->OnChoose(event);
        ListUnitDropSites();
    });
    auto SaveThenListAttacks = [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        ListUnitAttacks();
    };
    auto TrySaveThenListAttacks = [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            ListUnitAttacks();
        }
    };
    Attacks_Class->Bind(wxEVT_KILL_FOCUS, TrySaveThenListAttacks);
    Attacks_Class->Bind(wxEVT_TEXT_ENTER, SaveThenListAttacks);
    Attacks_Amount->Bind(wxEVT_KILL_FOCUS, TrySaveThenListAttacks);
    Attacks_Amount->Bind(wxEVT_TEXT_ENTER, SaveThenListAttacks);
    auto SaveThenListArmors = [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        ListUnitArmors();
    };
    auto TrySaveThenListArmors = [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            ListUnitArmors();
        }
    };
    Armors_Class->Bind(wxEVT_KILL_FOCUS, TrySaveThenListArmors);
    Armors_Class->Bind(wxEVT_TEXT_ENTER, SaveThenListArmors);
    Armors_Amount->Bind(wxEVT_KILL_FOCUS, TrySaveThenListArmors);
    Armors_Amount->Bind(wxEVT_TEXT_ENTER, SaveThenListArmors);
    Attacks_Class_ComboBox[0]->Bind(wxEVT_COMBOBOX, [this](wxCommandEvent& event)
    {
        static_cast<LinkedComboBox*>(event.GetEventObject())->OnChoose(event);
        ListUnitAttacks();
    });
    Attacks_Class_ComboBox[1]->Bind(wxEVT_COMBOBOX, [this](wxCommandEvent& event)
    {
        static_cast<LinkedComboBox*>(event.GetEventObject())->OnChoose(event);
        ListUnitArmors();
    });

    auto SaveThenListTasks = [this](wxCommandEvent& event)
    {
        static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits(true);
        ListUnitCommands();
    };
    auto TrySaveThenListTasks = [this](wxFocusEvent& event)
    {
        event.Skip();
        if (static_cast<AGETextCtrl*>(event.GetEventObject())->SaveEdits() == 0)
        {
            ListUnitCommands();
        }
    };
    Tasks_ActionType->Bind(wxEVT_KILL_FOCUS, TrySaveThenListTasks);
    Tasks_ActionType->Bind(wxEVT_TEXT_ENTER, SaveThenListTasks);
    Tasks_ProdResource->Bind(wxEVT_KILL_FOCUS, TrySaveThenListTasks);
    Tasks_ProdResource->Bind(wxEVT_TEXT_ENTER, SaveThenListTasks);
    Tasks_ActionType_ComboBox->Bind(wxEVT_COMBOBOX, [this](wxCommandEvent& event)
    {
        unsigned selection = static_cast<unsigned>(event.GetSelection() - 1);
        if (selection < 15)
        {
            Tasks_ActionType->SetAsText(selection);
        }
        else if (selection < 17)
        {
            Tasks_ActionType->SetAsText(selection + 5);
        }
        else if (selection < 28)
        {
            Tasks_ActionType->SetAsText(selection + 84);
        }
        else if (selection < 34)
        {
            Tasks_ActionType->SetAsText(selection + 92);
        }
        else if (selection < 41)
        {
            Tasks_ActionType->SetAsText(selection + 96);
        }
        else if (selection < 48)
        {
            Tasks_ActionType->SetAsText(selection + 108);
        }
        else
        {
            Tasks_ActionType->ChangeValue("-1");
        }
        Tasks_ActionType->SaveEdits();
        ListUnitCommands();
    });
    for(size_t loop = 0; loop < 8; ++loop)
    {
        Units_Trait_CheckBox[loop]->Bind(wxEVT_CHECKBOX, [this](wxCommandEvent& event)
        {
            if (Units_Trait->GetValue().empty()) return;
            try
            {
                uint8_t attribute = lexical_cast<short>(Units_Trait->GetValue());
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
            catch (const bad_lexical_cast&)
            {
                Units_Trait->clear();
                Units_Trait->ChangeValue("Error");
            }
        });
        Units_GarrisonType_CheckBox[loop]->Bind(wxEVT_CHECKBOX, [this](wxCommandEvent& event)
        {
            if (Units_GarrisonType->GetValue().empty()) return;
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
            catch (const bad_lexical_cast&)
            {
                Units_GarrisonType->clear();
                Units_GarrisonType->ChangeValue("Error");
            }
        });
    }
    Units_IconID->Bind(wxEVT_KILL_FOCUS, TrySaveThenSelectUnit);
    Units_IconID->Bind(wxEVT_TEXT_ENTER, SaveThenSelectUnit);
    Units_IconAngle->Bind(wxEVT_KILL_FOCUS, TrySaveThenSelectUnit);
    Units_IconAngle->Bind(wxEVT_TEXT_ENTER, SaveThenSelectUnit);
    Units_IconID_SLP->Bind(wxEVT_PAINT, &AGE_Frame::OnDrawIconSLP, this);
    Units_IconID_SLP->Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent&){});

    // To make SLP view refresh.
    Units_ConstructionGraphicID->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Units_ConstructionGraphicID->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Units_SnowGraphicID->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Units_SnowGraphicID->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Units_DestructionGraphicID->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Units_DestructionGraphicID->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Units_DestructionRubbleGraphicID->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Units_DestructionRubbleGraphicID->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Units_SpawningGraphic->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Units_SpawningGraphic->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Units_UpgradeGraphic->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Units_UpgradeGraphic->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Units_HeroGlowGraphic->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Units_HeroGlowGraphic->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Units_ResearchingGraphic->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Units_ResearchingGraphic->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Units_ResearchCompletedGraphic->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Units_ResearchCompletedGraphic->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Units_GarrisonGraphic->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Units_GarrisonGraphic->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Units_ChargingGraphic->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Units_ChargingGraphic->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Units_AttackGraphic->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Units_AttackGraphic->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Units_WalkingGraphic[0]->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Units_WalkingGraphic[0]->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Units_WalkingGraphic[1]->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Units_WalkingGraphic[1]->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Units_StandingGraphic[0]->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Units_StandingGraphic[0]->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Units_StandingGraphic[1]->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Units_StandingGraphic[1]->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Units_DyingGraphic[0]->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Units_DyingGraphic[0]->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Units_DyingGraphic[1]->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Units_DyingGraphic[1]->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Tasks_Graphics[0]->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Tasks_Graphics[0]->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Tasks_Graphics[1]->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Tasks_Graphics[1]->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Tasks_Graphics[2]->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Tasks_Graphics[2]->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Tasks_Graphics[3]->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Tasks_Graphics[3]->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Units_ConstructionGraphicID_ComboBox->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    Units_SnowGraphicID_ComboBox->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    Units_DestructionGraphicID_ComboBox->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    Units_DestructionRubbleGraphicID_ComboBox->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    Units_SpawningGraphic_ComboBox->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    Units_UpgradeGraphic_ComboBox->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    Units_HeroGlowGraphic_ComboBox->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    Units_ResearchingGraphic_ComboBox->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
    Units_ResearchCompletedGraphic_ComboBox->Bind(wxEVT_COMBOBOX, &AGE_Frame::OnUpdateCombo_Units, this);
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
    Units_SizeRadius[0]->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Units_SizeRadius[0]->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Units_SizeRadius[1]->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Units_SizeRadius[1]->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Units_ClearanceSize[0]->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Units_ClearanceSize[0]->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Units_ClearanceSize[1]->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Units_ClearanceSize[1]->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Units_SelectionRadius[0]->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Units_SelectionRadius[0]->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    Units_SelectionRadius[1]->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
    Units_SelectionRadius[1]->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    for(size_t loop = 0; loop < 4; ++loop)
    {
        Units_AnnexUnitMisplacement[loop][0]->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
        Units_AnnexUnitMisplacement[loop][0]->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
        Units_AnnexUnitMisplacement[loop][1]->Bind(wxEVT_KILL_FOCUS, TrySaveThenRenderUnit);
        Units_AnnexUnitMisplacement[loop][1]->Bind(wxEVT_TEXT_ENTER, SaveThenRenderUnit);
    }
}

void AGE_Frame::OnUpdateCombo_Units(wxCommandEvent& event)
{
    static_cast<LinkedComboBox*>(event.GetEventObject())->OnChoose(event);
    wxCommandEvent E;
    OnChooseGraphic(E);
}
