#include "Common.h"
#include "../AGE_Frame.h"
#include "../EditableVersion.h"

void AGE_Frame::FillListsBasedOnGameVersion()
{
    bool isAoE1DE = GenieVersion >= genie::GV_Tapsa && GenieVersion < genie::GV_LatestTap;
    bool isAoE2DE = GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2;

    task_names.Clear();
    // When changing this, edit all 4 other places too
    task_names.Add("Unused Ability/Invalid Ability");   // Selection 0
    task_names.Add("0: None");
    task_names.Add("1: Move to");
    task_names.Add(GenieVersion < genie::GV_AoKA ? "2: None" : "2: Follow");
    task_names.Add("3: Garrison");
    task_names.Add("4: Explore");
    task_names.Add("5: Gather/Rebuild");
    task_names.Add("6: Deleted (Graze)");
    task_names.Add("7: Combat");
    task_names.Add("8: Shoot");
    task_names.Add("9: Attack");
    task_names.Add("10: Fly");
    task_names.Add("11: Deleted (Scare/Hunt)");
    task_names.Add("12: Unload (Boat-Like)");
    task_names.Add(GenieVersion < genie::GV_AoKA ? "13: None" : "13: Guard");
    task_names.Add(GenieVersion < genie::GV_Cysion || GenieVersion > genie::GV_LatestDE2 ? "14: None" : "14: Unload Over Wall");
    task_names.Add("20: Deleted (Escape)");
    task_names.Add("21: Make");
    task_names.Add("101: Build");
    task_names.Add("102: Make a Unit");
    task_names.Add("103: Make a Tech");
    task_names.Add("104: Convert");
    task_names.Add("105: Heal");
    task_names.Add("106: Repair");
    task_names.Add("107: Get Auto-converted");
    task_names.Add("108: Discovery Artifact");
    task_names.Add("109: Deleted");
    task_names.Add("110: Hunt");
    task_names.Add("111: Trade");
    task_names.Add("120: Generate Wonder Victory");
    if (GenieVersion >= genie::GV_AoKA)
    {
        task_names.Add("121: Deselect when Tasked (Farm)");
        task_names.Add("122: Loot (Gather)");
        task_names.Add("123: Housing");
        task_names.Add("124: Pack");
        task_names.Add("125: Unpack & Attack");
        task_names.Add("130: Deleted");
        task_names.Add("131: Off-Map Trade");
        task_names.Add("132: Pickup Unit");
        task_names.Add("133: Charge Attack");
        task_names.Add("134: Transform Unit");
        task_names.Add("135: Kidnap Unit");
        task_names.Add("136: Deposit Unit");
        task_names.Add("149: Shear");
        if (GenieVersion <= genie::GV_LatestDE2)
        {
            if (GenieVersion == genie::GV_Cysion)
            {
                task_names.Add("150: Regeneration");
                task_names.Add("151: Feitoria Ability");
            }
            else
            {
                task_names.Add("150: Deleted");
                task_names.Add("151: Generate Resources");
                task_names.Add("152: Movement Damage");
                task_names.Add("153: Movable Drop Site");
                task_names.Add("154: Loot");
                task_names.Add("155: Aura");
            }
        }
    }
    Tasks_ActionType_ComboBox->Flash();

    age_names.Clear();
    age_names.Add("Nomad");
    if (GenieVersion >= genie::GV_SWGB)
    {
        age_names.Add("1st Tech Level");
        age_names.Add("2nd Tech Level");
        age_names.Add("3rd Tech Level");
        age_names.Add("4th Tech Level");
        age_names.Add("5th Tech Level");
    }
    else if (GenieVersion >= genie::GV_AoKA)
    {
        age_names.Add("Dark Age");
        age_names.Add("Feudal Age");
        age_names.Add("Castle Age");
        age_names.Add("Imperial Age");
        age_names.Add("Post-Imperial Age");
    }
    else
    {
        age_names.Add("Stone Age");
        age_names.Add("Tool Age");
        age_names.Add("Bronze Age");
        age_names.Add("Iron Age");
        age_names.Add("Post-Iron Age");
    }

    class_names.Clear();
    class_names.Add("No Class/Invalid Class");   // Selection 0
    if (GenieVersion < genie::GV_SWGB)
    {
        class_names.Add("0 - Archer");
        class_names.Add("1 - Artifact");
        class_names.Add("2 - Trade Boat");
        class_names.Add("3 - Building");
        class_names.Add("4 - Civilian");
        class_names.Add("5 - Ocean Fish");
        class_names.Add("6 - Infantry");
        class_names.Add("7 - Berry Bush");
        class_names.Add("8 - Stone Mine");
        class_names.Add("9 - Prey Animal");
        class_names.Add("10 - Predator Animal");
        class_names.Add("11 - Miscellaneous");
        class_names.Add("12 - Cavalry");
        class_names.Add("13 - Siege Weapon");
        class_names.Add("14 - Terrain");
        class_names.Add("15 - Tree");
        class_names.Add("16 - Tree Stump");
        class_names.Add("17 - Healer");
        class_names.Add(GenieVersion < genie::GV_AoKA ? "18 - Priest" : "18 - Monk");
        class_names.Add("19 - Trade Cart");
        class_names.Add("20 - Transport Boat");
        class_names.Add("21 - Fishing Boat");
        class_names.Add("22 - Warship");
        class_names.Add(GenieVersion < genie::GV_AoKA ? "23 - Chariot Archer" : "23 - Conquistador");
        class_names.Add("24 - War Elephant");
        class_names.Add("25 - Hero");
        class_names.Add("26 - Elephant Archer");
        class_names.Add("27 - Wall");
        class_names.Add("28 - Phalanx");
        class_names.Add("29 - Domestic Animal");
        class_names.Add("30 - Flag");
        class_names.Add("31 - Deep Sea Fish");
        class_names.Add("32 - Gold Mine");
        class_names.Add("33 - Shore Fish");
        class_names.Add("34 - Cliff");
        class_names.Add(GenieVersion < genie::GV_AoKA ? "35 - Chariot" : "35 - Petard");
        class_names.Add("36 - Cavalry Archer");
        class_names.Add("37 - Doppelganger");
        class_names.Add("38 - Bird");
        if (GenieVersion < genie::GV_AoKA)
        {
            class_names.Add("39 - Slinger");
        }
        // Above class names are checked for AoE 1
        else
        {
            class_names.Add("39 - Gate");
            class_names.Add("40 - Salvage Pile");
            class_names.Add("41 - Resource Pile");
            class_names.Add("42 - Relic");
            class_names.Add("43 - Monk with Relic");
            class_names.Add("44 - Hand Cannoneer");
            class_names.Add("45 - Two Handed Swordsman");
            class_names.Add("46 - Pikeman");
            class_names.Add("47 - Scout");
            class_names.Add("48 - Ore Mine");
            class_names.Add("49 - Farm");
            class_names.Add("50 - Spearman");
            class_names.Add("51 - Packed Unit");
            class_names.Add("52 - Tower");
            class_names.Add("53 - Boarding Boat");
            class_names.Add("54 - Unpacked Siege Unit");
            class_names.Add("55 - Ballista");
            class_names.Add("56 - Raider");
            class_names.Add("57 - Cavalry Raider");
            class_names.Add("58 - Livestock");
            class_names.Add("59 - King");
            class_names.Add("60 - Misc Building");
            class_names.Add("61 - Controlled Animal");
        }
        // Above class names are checked for AoE 2
    }
    else
    {
        class_names.Add("0 - Unused");   // Selection 1
        class_names.Add("1 - Nerf/Bantha");
        class_names.Add("2 - Fambaa");
        class_names.Add("3 - Unused");
        class_names.Add("4 - Wild Animal");
        class_names.Add("5 - Monster/Trouble");
        class_names.Add("6 - Wall");
        class_names.Add("7 - Farm");
        class_names.Add("8 - Gate");
        class_names.Add("9 - Fortress/A-A Turret");
        class_names.Add("10 - Turret");
        class_names.Add("11 - Cruiser");
        class_names.Add("12 - Unused");
        class_names.Add("13 - Destroyer");
        class_names.Add("14 - Utility Trawler");
        class_names.Add("15 - Frigate 1");
        class_names.Add("16 - A-A Destroyer 1");
        class_names.Add("17 - Transport Ship");
        class_names.Add("18 - Building");
        class_names.Add("19 - Doppelganger");
        class_names.Add("20 - Other/Dead/Projectile");
        class_names.Add("21 - Command Base");
        class_names.Add("22 - Cliff");
        class_names.Add("23 - Fish");
        class_names.Add("24 - Unused");
        class_names.Add("25 - Shore Fish");
        class_names.Add("26 - Game Engine Stuff");
        class_names.Add("27 - Fruit Bush");
        class_names.Add("28 - Holocron");
        class_names.Add("29 - Nova");
        class_names.Add("30 - Ore");
        class_names.Add("31 - Tree/Carbon");
        class_names.Add("32 - Artillery");
        class_names.Add("33 - A-A Mobile");
        class_names.Add("34 - Undeployed Cannon");
        class_names.Add("35 - Pummel");
        class_names.Add("36 - Cannon");
        class_names.Add("37 - Unused");
        class_names.Add("38 - Unused");
        class_names.Add("39 - Frigate 2");
        class_names.Add("40 - A-A Destroyer 2");
        class_names.Add("41 - Unused");
        class_names.Add("42 - Bridge/Eye Candy");
        class_names.Add("43 - Bomber");
        class_names.Add("44 - Bounty Hunter");
        class_names.Add("45 - Cargo Trader");
        class_names.Add("46 - Mixed 1");
        class_names.Add("47 - Scout");
        class_names.Add("48 - Fighter");
        class_names.Add("49 - Grenade Trooper");
        class_names.Add("50 - Jedi");
        class_names.Add("51 - Jedi with Holocron");
        class_names.Add("52 - Trooper");
        class_names.Add("53 - War Machine");
        class_names.Add("54 - Medic");
        class_names.Add("55 - A-A Trooper");
        class_names.Add("56 - Mounted Trooper");
        class_names.Add("57 - Fambaa Shield Generator");
        class_names.Add("58 - Workers");
        class_names.Add("59 - Air Transport");
        class_names.Add("60 - Domestic Animal");
        class_names.Add("61 - Power Droid");
        class_names.Add("62 - Air Cruiser");
        class_names.Add("63 - Geonosian Warrior");
        class_names.Add("64 - Jedi Starfighter");
    }
    Effects_B_ComboBox->Flash();

    effect_attribute_names.Clear();
    effect_attribute_names.Add("No Attribute/Invalid Attribute");     // Selection 0
    effect_attribute_names.Add("0 - Hit Points");     // Selection 1
    effect_attribute_names.Add("1 - Line of Sight");
    effect_attribute_names.Add("2 - Garrison Capacity");
    effect_attribute_names.Add("3 - Unit Size X");
    effect_attribute_names.Add("4 - Unit Size Y");
    effect_attribute_names.Add("5 - Movement Speed (types 20-80)");
    effect_attribute_names.Add("6 - Rotation Speed (types 30-80)");
    effect_attribute_names.Add("7 - Unused");
    if (GenieVersion < genie::GV_AoKA)
    {
        effect_attribute_names.Add("8 - Armor (no multiply, types 50-80)");
        effect_attribute_names.Add("9 - Attack (no multiply, types 50-80)");
    }
    else
    {
        effect_attribute_names.Add("8 - Armor (types 50-80)");
        effect_attribute_names.Add("9 - Attack (types 50-80)");
    }
    effect_attribute_names.Add("10 - Attack Reload Time (types 50-80)");
    effect_attribute_names.Add("11 - Accuracy Percent (types 50-80)");
    effect_attribute_names.Add("12 - Max Range (types 50-80)");
    effect_attribute_names.Add("13 - Work Rate (types 30-80)");
    effect_attribute_names.Add("14 - Carry Capacity");
    effect_attribute_names.Add("15 - Base Armor (types 50-80)");
    effect_attribute_names.Add("16 - Projectile Unit (types 50-80)");
    effect_attribute_names.Add("17 - Icon/Graphics Angle (type 80)");
    effect_attribute_names.Add("18 - Terrain Defense Bonus (always sets, types 50-80)");
    if (GenieVersion >= genie::GV_AoEB)
    {
        effect_attribute_names.Add("19 - Enable Smart Projectiles (type 60)");
    }
    else
    {
        effect_attribute_names.Add("19 - Unused");
    }
    if (GenieVersion >= genie::GV_AoKA)
    {
        effect_attribute_names.Add("20 - Min Range (types 50-80)");
        effect_attribute_names.Add("21 - Amount of 1st resource storage");
        effect_attribute_names.Add("22 - Blast Width (types 50-80)");
        effect_attribute_names.Add("23 - Search Radius (types 40-80)");
        if (isAoE2DE)
        {
            effect_attribute_names.Add("24 - Hidden Damage Resistance (types 50-80)");
            effect_attribute_names.Add("25 - Icon");
            effect_attribute_names.Add("26 - Amount of 2nd resource storage");
            effect_attribute_names.Add("27 - Amount of 3rd resource storage");
            effect_attribute_names.Add("28 - Fog Visibility");
            effect_attribute_names.Add("29 - Occlusion Mode");
            effect_attribute_names.Add("30 - Garrison Type (type 80)");
            effect_attribute_names.Add("31 - Unknown");
            effect_attribute_names.Add("32 - Unit Size Z");
            effect_attribute_names.Add("33 - Can Be Built On");
            effect_attribute_names.Add("34 - Foundation Terrain (type 80)");
            effect_attribute_names.Add("40 - Hero Status (types 70-80)");
            effect_attribute_names.Add("41 - Frame Delay (types 50-80)");
            effect_attribute_names.Add("42 - Train Location (types 70-80)");
            effect_attribute_names.Add("43 - Train Button (types 70-80)");
            effect_attribute_names.Add("44 - Blast Attack Level (types 50-80)");
            effect_attribute_names.Add("45 - Blast Defense Level");
            effect_attribute_names.Add("46 - Shown Attack (types 50-80)");
            effect_attribute_names.Add("47 - Shown Range (types 50-80)");
            effect_attribute_names.Add("48 - Shown Melee Armor (types 50-80)");
            effect_attribute_names.Add("49 - Shown Pierce Armor (types 70-80)");
            effect_attribute_names.Add("50 - Unit Name String");
            effect_attribute_names.Add("51 - Unit Short Description String");
            effect_attribute_names.Add("52 - Unused");
            effect_attribute_names.Add("53 - Terrain Restriction");
            effect_attribute_names.Add("54 - Unit Trait");
            effect_attribute_names.Add("55 - Unit Civilization");
            effect_attribute_names.Add("56 - Unit Trait Piece");
            effect_attribute_names.Add("57 - Dead Unit");
            effect_attribute_names.Add("58 - Hotkey");
            effect_attribute_names.Add("59 - Maximum Charge (types 70-80)");
            effect_attribute_names.Add("60 - Recharge Rate (types 70-80)");
            effect_attribute_names.Add("61 - Charge Event (types 70-80)");
            effect_attribute_names.Add("62 - Charge Type (types 70-80)");
            effect_attribute_names.Add("63 - Combat Ability (types 50-80)");
            effect_attribute_names.Add("64 - Attack Dispersion (types 50-80)");
            effect_attribute_names.Add("65 - Secondary Projectile Unit (types 70-80)");
            effect_attribute_names.Add("66 - Blood Unit");
            effect_attribute_names.Add("67 - Projectile Hit Mode (type 60)");
            effect_attribute_names.Add("68 - Projectile Vanish Mode (type 60)");
            effect_attribute_names.Add("69 - Projectile Arc (type 60)");
            effect_attribute_names.Add("70 - Attack Graphic (types 50-80)");
            effect_attribute_names.Add("71 - Standing Graphic");
            effect_attribute_names.Add("72 - Second Standing Graphic");
            effect_attribute_names.Add("73 - Dying Graphic");
            effect_attribute_names.Add("74 - Undead Graphic");
            effect_attribute_names.Add("75 - Walking Graphic (types 30-80)");
            effect_attribute_names.Add("76 - Running Graphic (types 30-80)");
            effect_attribute_names.Add("77 - Special Graphic (types 70-80)");
        }
        effect_attribute_names.Add("100 - Resource Costs (types 70-80)");
        effect_attribute_names.Add("101 - Train Time (types 70-80)");
        effect_attribute_names.Add("102 - Total Missiles (types 70-80)");
        effect_attribute_names.Add("103 - Food Costs (types 70-80)");
        if (GenieVersion < genie::GV_SWGB)
        {
            effect_attribute_names.Add("104 - Wood Costs (types 70-80)");
            effect_attribute_names.Add("105 - Gold Costs (types 70-80)");
            effect_attribute_names.Add("106 - Stone Costs (types 70-80)");
        }
        else
        {
            effect_attribute_names.Add("104 - Carbon Costs (types 70-80)");
            effect_attribute_names.Add("105 - Nova Costs (types 70-80)");
            effect_attribute_names.Add("106 - Ore Costs (types 70-80)");
        }
        effect_attribute_names.Add("107 - Max Total Missiles (types 70-80)");
        if (GenieVersion >= genie::GV_AoKB)
        {
            effect_attribute_names.Add("108 - Garrison Heal Rate (type 80)");
        }
        if (GenieVersion >= genie::GV_Cysion && GenieVersion <= genie::GV_LatestDE2)
        {
            effect_attribute_names.Add("109 - Regeneration Rate (types 40-80)");
        }
        if (isAoE2DE)
        {
            effect_attribute_names.Add("110 - Population (types 70-80)");
            effect_attribute_names.Add("111 - Minimum Conversion Time Modifier (types 70-80)");
            effect_attribute_names.Add("112 - Maximum Conversion Time Modifier (types 70-80)");
            effect_attribute_names.Add("113 - Conversion Chance Modifier (types 70-80)");
            effect_attribute_names.Add("114 - Formation Category (types 70-80)");
            effect_attribute_names.Add("115 - Area Damage (types 50-80)");
        }
    }
    else
    {
        effect_attribute_names.Add("100 - Resource Costs (types 70-80)");
        if (GenieVersion >= genie::GV_RoR)
        {
            effect_attribute_names.Add("101 - Population (set only)");
        }
    }
    Effects_C_ComboBox->Flash();

    // Special selection logic that takes into account gaps in the list above.
    // Excess items automatically convert into zero within the list.
    if (GenieVersion >= genie::GV_AoKA)
    {
        if (isAoE2DE)
        {
            // Attributes 0 to 34, 40 to 77 and 100 to 115 only.
            SetEffectAttributeChoice = [](LinkedComboBox *linkedComboBox, short value)
            {
                if (value >= 0 && value <= 34)
                {
                    linkedComboBox->SetChoice(value);
                }
                else if (value >= 40 && value <= 77)
                {
                    linkedComboBox->SetChoice(value - 5);
                }
                else if (value >= 100 && value <= 115)
                {
                    linkedComboBox->SetChoice(value - 27);
                }
                else
                {
                    linkedComboBox->SetChoice(-1);
                }
            };
            OnChooseEffectAttribute = [](AGETextCtrl *linkedTextBox, unsigned selection)
            {
                if (selection < 35)
                {
                    linkedTextBox->SetAsText(selection);
                }
                else if (selection < 73)
                {
                    linkedTextBox->SetAsText(selection + 5);
                }
                else if (selection < 89)
                {
                    linkedTextBox->SetAsText(selection + 27);
                }
                else
                {
                    linkedTextBox->ChangeValue("-1");
                }
            };
        }
        else
        {
            // Attributes 0 to 23 and 100 to 109 only.
            SetEffectAttributeChoice = [](LinkedComboBox *linkedComboBox, short value)
            {
                if (value >= 0 && value <= 23)
                {
                    linkedComboBox->SetChoice(value);
                }
                else if (value >= 100 && value <= 109)
                {
                    linkedComboBox->SetChoice(value - 76);
                }
                else
                {
                    linkedComboBox->SetChoice(-1);
                }
            };
            OnChooseEffectAttribute = [](AGETextCtrl *linkedTextBox, unsigned selection)
            {
                if (selection < 24)
                {
                    linkedTextBox->SetAsText(selection);
                }
                else if (selection < 34)
                {
                    linkedTextBox->SetAsText(selection + 76);
                }
                else
                {
                    linkedTextBox->ChangeValue("-1");
                }
            };
        }
    }
    else
    {
        // Attributes 0 to 19 and 100 to 101 only.
        SetEffectAttributeChoice = [](LinkedComboBox *linkedComboBox, short value)
        {
            if (value >= 0 && value <= 19)
            {
                linkedComboBox->SetChoice(value);
            }
            else if (value >= 100 && value <= 101)
            {
                linkedComboBox->SetChoice(value - 80);
            }
            else
            {
                linkedComboBox->SetChoice(-1);
            }
        };
        OnChooseEffectAttribute = [](AGETextCtrl *linkedTextBox, unsigned selection)
        {
            if (selection < 20)
            {
                linkedTextBox->SetAsText(selection);
            }
            else if (selection < 22)
            {
                linkedTextBox->SetAsText(selection + 80);
            }
            else
            {
                linkedTextBox->ChangeValue("-1");
            }
        };
    }

    modify_research_names.Clear();
    if (isAoE2DE || GameVersion == EV_UP)
    {
        modify_research_names.Add("-1 - Set Time");
        modify_research_names.Add("-2 - Add Time");
        modify_research_names.Add("0 - Set Food Cost");
        modify_research_names.Add("1 - Set Wood Cost");
        modify_research_names.Add("2 - Set Stone Cost");
        modify_research_names.Add("3 - Set Gold Cost");
    }
    if (isAoE2DE)
    {
        modify_research_names.Add("4 - Set Research Location");
        modify_research_names.Add("5 - Set Research Button");
        modify_research_names.Add("6 - Set Icon");
        modify_research_names.Add("7 - Set Name");
        modify_research_names.Add("8 - Set Description");
        modify_research_names.Add("9 - Set Stacking");
        modify_research_names.Add("10 - Set Stacking Research Cap");
        modify_research_names.Add("11 - Set Hotkey");
        modify_research_names.Add("12 - Set Enabled");
    }
    if (isAoE2DE || GameVersion == EV_UP)
    {
        modify_research_names.Add("16384 - Add Food Cost");
        modify_research_names.Add("16385 - Add Wood Cost");
        modify_research_names.Add("16386 - Add Stone Cost");
        modify_research_names.Add("16387 - Add Gold Cost");
    }

    graphicset_names.Clear();
    if (GenieVersion < genie::GV_AoKA)
    {
        // AoE
        graphicset_names.Add("0 West Middle Easterns");
        graphicset_names.Add("1 Greeks");
        graphicset_names.Add("2 East Middle Easterns");
        graphicset_names.Add("3 Asians");
        // + RoR
        graphicset_names.Add("4 Romans");
    }
    else if (GenieVersion < genie::GV_SWGB)
    {
        graphicset_names.Add("0 Unused");
        // AoK
        graphicset_names.Add("1 Central Europeans");
        graphicset_names.Add("2 West Europeans");
        graphicset_names.Add("3 East Asians");
        graphicset_names.Add("4 Arabs");
        // + TC
        graphicset_names.Add("5 Americans");
        // + FE
        if (GenieVersion >= genie::GV_Cysion)
        {
            graphicset_names.Add("6 South Europeans");
            graphicset_names.Add("7 Indians");
            graphicset_names.Add("8 East Europeans");
            graphicset_names.Add("9 Africans");
            graphicset_names.Add("10 South East Asians");
            graphicset_names.Add("11 Central Asians");
        }
    }
    else
    {
        // SWGB
        graphicset_names.Add("0 Unused");
        graphicset_names.Add("1 Galactic Empire");
        graphicset_names.Add("2 Gungans");
        graphicset_names.Add("3 Rebels");
        graphicset_names.Add("4 Royal Naboo");
        graphicset_names.Add("5 Trade Federation");
        graphicset_names.Add("6 Wookiees");
        graphicset_names.Add("7 Republic");
        graphicset_names.Add("8 Confederacy");
        graphicset_names.Add("9 Ask Tapsa for more!");
    }
    Units_GraphicSet->Flash();

    effect_type_names.Clear();
    effect_type_names.Add("No Type/Invalid Type");  // Selection 0
    effect_type_names.Add("0 - Attribute Modifier (Set)");  // Selection 1
    effect_type_names.Add("1 - Resource Modifier (Set/+/-)");
    effect_type_names.Add("2 - Enable/Disable Unit");
    effect_type_names.Add("3 - Upgrade Unit");
    effect_type_names.Add("4 - Attribute Modifier (+/-)");
    effect_type_names.Add("5 - Attribute Modifier (Multiply)");
    if (GenieVersion >= genie::GV_AoKA || GenieVersion >= genie::GV_Tapsa && GenieVersion <= genie::GV_LatestTap)
    {
        effect_type_names.Add("6 - Resource Modifier (Multiply)");
    }
    if (isAoE2DE)
    {
        effect_type_names.Add("7 - Spawn Unit");
        effect_type_names.Add("8 - Modify Tech");
    }
    else if (GameVersion == EV_UP)
    {
        effect_type_names.Add("7 - Enable/Disable/Force Multiuse Tech");
        effect_type_names.Add("8 - Modify Tech");
        effect_type_names.Add("9 - Set Player Civ Name");
    }
    if (GenieVersion >= genie::GV_Cysion && GenieVersion <= genie::GV_LatestDE2 || GameVersion == EV_UP)
    {
        effect_type_names.Add("10 - Team Attribute Modifier (Set)");
        effect_type_names.Add("11 - Team Resource Modifier (Set/+/-)");
        effect_type_names.Add("12 - Team Enable/Disable Unit");
        effect_type_names.Add("13 - Team Upgrade Unit");
        effect_type_names.Add("14 - Team Attribute Modifier (+/-)");
        effect_type_names.Add("15 - Team Attribute Modifier (Multiply)");
        effect_type_names.Add("16 - Team Resource Modifier (Multiply)");
    }
    if (isAoE2DE)
    {
        effect_type_names.Add("17 - Team Spawn Unit");
        effect_type_names.Add("18 - Team Modify Tech");
    }
    else if (GameVersion == EV_UP)
    {
        effect_type_names.Add("17 - Team Enable/Disable/Force Multiuse Tech");
        effect_type_names.Add("18 - Team Modify Tech");
        effect_type_names.Add("19 - Team Set Player Civ Name");
    }
    if (isAoE2DE || GameVersion == EV_UP)
    {
        effect_type_names.Add("20 - Enemy Attribute Modifier (Set)");
        effect_type_names.Add("21 - Enemy Resource Modifier (Set/+/-)");
        effect_type_names.Add("22 - Enemy Enable/Disable Unit");
        effect_type_names.Add("23 - Enemy Upgrade Unit");
        effect_type_names.Add("24 - Enemy Attribute Modifier (+/-)");
        effect_type_names.Add("25 - Enemy Attribute Modifier (Multiply)");
        effect_type_names.Add("26 - Enemy Resource Modifier (Multiply)");
    }
    if (isAoE2DE)
    {
        effect_type_names.Add("27 - Enemy Spawn Unit");
        effect_type_names.Add("28 - Enemy Modify Tech");
    }
    else if (GameVersion == EV_UP)
    {
        effect_type_names.Add("27 - Enemy Enable/Disable/Force Multiuse Tech");
        effect_type_names.Add("28 - Enemy Modify Tech");
        effect_type_names.Add("29 - Enemy Set Player Civ Name");
    }
    if (isAoE2DE || GameVersion == EV_UP)
    {
        effect_type_names.Add("30 - Neutral Attribute Modifier (Set)");
        effect_type_names.Add("31 - Neutral Resource Modifier (Set/+/-)");
        effect_type_names.Add("32 - Neutral Enable/Disable Unit");
        effect_type_names.Add("33 - Neutral Upgrade Unit");
        effect_type_names.Add("34 - Neutral Attribute Modifier (+/-)");
        effect_type_names.Add("35 - Neutral Attribute Modifier (Multiply)");
        effect_type_names.Add("36 - Neutral Resource Modifier (Multiply)");
    }
    if (isAoE2DE)
    {
        effect_type_names.Add("37 - Neutral Spawn Unit");
        effect_type_names.Add("38 - Neutral Modify Tech");
    }
    else if (GameVersion == EV_UP)
    {
        effect_type_names.Add("37 - Neutral Enable/Disable/Force Multiuse Tech");
        effect_type_names.Add("38 - Neutral Modify Tech");
        effect_type_names.Add("39 - Neutral Set Player Civ Name");
    }
    if (isAoE2DE)
    {
        effect_type_names.Add("40 - Gaia Attribute Modifier (Set)");
        effect_type_names.Add("41 - Gaia Resource Modifier (Set/+/-)");
        effect_type_names.Add("42 - Gaia Enable/Disable Unit");
        effect_type_names.Add("43 - Gaia Upgrade Unit");
        effect_type_names.Add("44 - Gaia Attribute Modifier (+/-)");
        effect_type_names.Add("45 - Gaia Attribute Modifier (Multiply)");
        effect_type_names.Add("46 - Gaia Resource Modifier (Multiply)");
        effect_type_names.Add("47 - Gaia Spawn Unit");
        effect_type_names.Add("48 - Gaia Modify Tech");
    }
    if (GenieVersion >= genie::GV_AoKA || GenieVersion >= genie::GV_Tapsa && GenieVersion <= genie::GV_LatestTap)
    {
        effect_type_names.Add("101 - Tech Cost Modifier (Set/+/-)");
    }
    effect_type_names.Add("102 - Disable Tech");
    if (GenieVersion >= genie::GV_AoKA || GenieVersion >= genie::GV_Tapsa && GenieVersion <= genie::GV_LatestTap)
    {
        effect_type_names.Add("103 - Tech Time Modifier (Set/+/-)");
    }
    Effects_Type_ComboBox->Flash();

    // Special selection logic that takes into account gaps in the list above.
    if (GenieVersion >= genie::GV_AoKA || GenieVersion >= genie::GV_Tapsa && GenieVersion <= genie::GV_LatestTap)
    {
        if (GenieVersion >= genie::GV_Cysion && GenieVersion <= genie::GV_LatestDE2)
        {
            if (GenieVersion >= genie::GV_C2)
            {
                // Types 0 to 8, 10 to 18, 20 to 28, 30 to 38, 40 to 48 and 101 to 103 only.
                SetEffectTypeChoice = [](LinkedComboBox *linkedComboBox, short value)
                {
                    if (value >= 0 && value <= 8)
                    {
                        linkedComboBox->SetChoice(value);
                    }
                    else if (value >= 10 && value <= 18)
                    {
                        linkedComboBox->SetChoice(value - 1);
                    }
                    else if (value >= 20 && value <= 28)
                    {
                        linkedComboBox->SetChoice(value - 2);
                    }
                    else if (value >= 30 && value <= 38)
                    {
                        linkedComboBox->SetChoice(value - 3);
                    }
                    else if (value >= 40 && value <= 48)
                    {
                        linkedComboBox->SetChoice(value - 4);
                    }
                    else if (value >= 101 && value <= 103)
                    {
                        linkedComboBox->SetChoice(value - 56);
                    }
                    else
                    {
                        linkedComboBox->SetChoice(-1);
                    }
                };
                OnChooseEffectType = [](AGETextCtrl *linkedTextBox, unsigned selection)
                {
                    if (selection < 9)
                    {
                        linkedTextBox->SetAsText(selection);
                    }
                    else if (selection < 18)
                    {
                        linkedTextBox->SetAsText(selection + 1);
                    }
                    else if (selection < 27)
                    {
                        linkedTextBox->SetAsText(selection + 2);
                    }
                    else if (selection < 36)
                    {
                        linkedTextBox->SetAsText(selection + 3);
                    }
                    else if (selection < 45)
                    {
                        linkedTextBox->SetAsText(selection + 4);
                    }
                    else if (selection < 48)
                    {
                        linkedTextBox->SetAsText(selection + 56);
                    }
                    else
                    {
                        linkedTextBox->ChangeValue("255");
                    }
                };
            }
            else
            {
                // Types 0 to 6, 10 to 16 and 101 to 103 only.
                SetEffectTypeChoice = [](LinkedComboBox *linkedComboBox, short value)
                {
                    if (value >= 0 && value <= 6)
                    {
                        linkedComboBox->SetChoice(value);
                    }
                    else if (value >= 10 && value <= 16)
                    {
                        linkedComboBox->SetChoice(value - 3);
                    }
                    else if (value >= 101 && value <= 103)
                    {
                        linkedComboBox->SetChoice(value - 87);
                    }
                    else
                    {
                        linkedComboBox->SetChoice(-1);
                    }
                };
                OnChooseEffectType = [](AGETextCtrl *linkedTextBox, unsigned selection)
                {
                    if (selection < 7)
                    {
                        linkedTextBox->SetAsText(selection);
                    }
                    else if (selection < 14)
                    {
                        linkedTextBox->SetAsText(selection + 3);
                    }
                    else if (selection < 17)
                    {
                        linkedTextBox->SetAsText(selection + 87);
                    }
                    else
                    {
                        linkedTextBox->ChangeValue("255");
                    }
                };
            }
        }
        else if (GameVersion == EV_UP)
        {
            // Types 0 to 39 and 101 to 103 only.
            SetEffectTypeChoice = [](LinkedComboBox *linkedComboBox, short value)
            {
                if (value >= 0 && value <= 39)
                {
                    linkedComboBox->SetChoice(value);
                }
                else if (value >= 101 && value <= 103)
                {
                    linkedComboBox->SetChoice(value - 61);
                }
                else
                {
                    linkedComboBox->SetChoice(-1);
                }
            };
            OnChooseEffectType = [](AGETextCtrl *linkedTextBox, unsigned selection)
            {
                if (selection < 40)
                {
                    linkedTextBox->SetAsText(selection);
                }
                else if (selection < 43)
                {
                    linkedTextBox->SetAsText(selection + 61);
                }
                else
                {
                    linkedTextBox->ChangeValue("255");
                }
            };
        }
        else
        {
            // Types 0 to 6 and 101 to 103 only.
            SetEffectTypeChoice = [](LinkedComboBox *linkedComboBox, short value)
            {
                if (value >= 0 && value <= 6)
                {
                    linkedComboBox->SetChoice(value);
                }
                else if (value >= 101 && value <= 103)
                {
                    linkedComboBox->SetChoice(value - 94);
                }
                else
                {
                    linkedComboBox->SetChoice(-1);
                }
            };
            OnChooseEffectType = [](AGETextCtrl *linkedTextBox, unsigned selection)
            {
                if (selection < 7)
                {
                    linkedTextBox->SetAsText(selection);
                }
                else if (selection < 10)
                {
                    linkedTextBox->SetAsText(selection + 94);
                }
                else
                {
                    linkedTextBox->ChangeValue("255");
                }
            };
        }
    }
    else
    {
        // Types 0 to 5 and 102 only.
        SetEffectTypeChoice = [](LinkedComboBox *linkedComboBox, short value)
        {
            if (value >= 0 && value <= 5)
            {
                linkedComboBox->SetChoice(value);
            }
            else if (value == 102)
            {
                linkedComboBox->SetChoice(value - 96);
            }
            else
            {
                linkedComboBox->SetChoice(-1);
            }
        };
        OnChooseEffectType = [](AGETextCtrl *linkedTextBox, unsigned selection)
        {
            if (selection < 6)
            {
                linkedTextBox->SetAsText(selection);
            }
            else if (selection == 6)
            {
                linkedTextBox->SetAsText(selection + 96);
            }
            else
            {
                linkedTextBox->ChangeValue("255");
            }
        };
    }

    const wxString localFilename = PathCustomNames.empty() ? "AGE3NamesV0006.ini" : PathCustomNames;
    wxFileConfig Customs("", "", localFilename, "", wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
    wxString KeyArmors, KeyTerrainTables, KeyCivResources;

    // The conditions below that compile the default lists for these should match the comparisons here.
    if (GenieVersion < genie::GV_RoR)
    {
        KeyArmors = "AoE";
        KeyTerrainTables = "AoE";
        KeyCivResources = "AoE";
    }
    else if (GenieVersion < genie::GV_AoKE3)
    {
        KeyArmors = "RoR";
        KeyTerrainTables = "AoE";
        KeyCivResources = "RoR";
    }
    else if (GenieVersion < genie::GV_TC)
    {
        KeyArmors = "AoK";
        KeyTerrainTables = "AoK";
        KeyCivResources = "AoK";
    }
    else if (GenieVersion < genie::GV_Cysion)
    {
        KeyArmors = "AoE2TC";
        KeyTerrainTables = "AoE2TC";
        KeyCivResources = "AoE2TC";
    }
    else if (GenieVersion < genie::GV_C2)
    {
        KeyArmors = "AoE2HD";
        KeyTerrainTables = "AoE2HD";
        KeyCivResources = "AoE2HD";
    }
    else if (GenieVersion < genie::GV_SWGB)
    {
        KeyArmors = "AoE2DE";
        KeyTerrainTables = "AoE2DE";
        KeyCivResources = "AoE2DE";
    }
    else if (GenieVersion < genie::GV_CC)
    {
        KeyArmors = "SWGB";
        KeyTerrainTables = "SWGB";
        KeyCivResources = "SWGB";
    }
    else
    {
        KeyArmors = "SWGB";
        KeyTerrainTables = "SWGB";
        KeyCivResources = "SWCC";
    }

    wxString KeyNumArmors = "Counts/Num" + KeyArmors + "Armors";
    wxString KeyNumTerrainTables = "Counts/Num" + KeyTerrainTables + "TerrainTables";
    wxString KeyNumCivResources = "Counts/Num" + KeyCivResources + "CivResources";
    wxString KeyArmorNames = KeyArmors + "ArmorNames/";
    wxString KeyTerrainTableNames = KeyTerrainTables + "TerrainTableNames/";
    wxString KeyCivResourceNames = KeyCivResources + "CivResourceNames/";
    wxString read_buf;
    long NumNames;

    armor_names.clear();
    armor_names.Add("Unused Type/No Type");
    if (Customs.Read(KeyNumArmors, &NumNames, 0))
    {
        for (size_t loop = 0; loop < NumNames; ++loop)
        {
            wxString indexAsText = lexical_cast<std::string>(loop);
            Customs.Read(KeyArmorNames + indexAsText, &read_buf, "Unused");
            armor_names.Add(indexAsText + " - " + read_buf);
        }
    }
    else
    {
        class ArmorWriter
        {
        public:
            ArmorWriter(wxFileConfig &file, wxString &key, wxArrayString &list) :
                index(0), key(key), file(file), list(list) {}
            void Add(wxString name)
            {
                wxString indexAsText = lexical_cast<std::string>(index++);
                file.Write(key + indexAsText, name);
                list.Add(indexAsText + " - " + name);
            }
            long NumNames(void) const { return index; }
        private:
            long index;
            wxString &key;
            wxFileConfig &file;
            wxArrayString &list;
        };

        ArmorWriter names(Customs, KeyArmorNames, armor_names);

        if (GenieVersion < genie::GV_SWGB)
        {
            if (GenieVersion >= genie::GV_AoKE3)
            {
                names.Add("Unused");
                names.Add("Infantry");
                if (GenieVersion >= genie::GV_TC)
                {
                    names.Add("Turtle Ships");
                }
                else
                {
                    names.Add("Unused");
                }
            }
            else
            {
                if (GenieVersion >= genie::GV_RoR)
                {
                    names.Add("Towers & Walls & Fire Galley");
                    names.Add("Towers & Walls & Archers");
                }
                else
                {
                    names.Add("Towers & Walls, Pierce");
                    names.Add("Unused");
                }
                names.Add("Explosion");
            }
            names.Add("Base Pierce");
            names.Add("Base Melee");
            if (GenieVersion >= genie::GV_AoKE3)
            {
                names.Add("War Elephants");
                names.Add("Unused");
                names.Add("Unused");
            }
            else
            {
                names.Add("Unused");
                names.Add("Buildings");
                names.Add("Priests");
            }
            if (GenieVersion >= genie::GV_RoR)
            {
                names.Add("Cavalry");
            }
            else
            {
                names.Add("Unused");
            }
            if (GenieVersion >= genie::GV_AoKE3)
            {
                names.Add("Unused");
                names.Add("Unused");
                names.Add("All Buildings (except Port)");
                names.Add("Unused");
                names.Add("Stone Walls & Gates & Towers");
                if (GenieVersion >= genie::GV_Cysion)
                {
                    names.Add("Predator Animals");
                }
                else
                {
                    names.Add("Unused");
                }
                names.Add("Archers");
                if (GenieVersion >= genie::GV_Cysion || GenieVersion < genie::GV_TC)
                {
                    names.Add("Ships & Saboteur");
                }
                else
                {
                    names.Add("Ships & Saboteur & Camels");
                }
                if (GenieVersion >= genie::GV_Cysion)
                {
                    names.Add("Rams & Trebuchet & Siege Towers");
                }
                else
                {
                    names.Add("Rams & Trebuchet");
                }
                if (GenieVersion >= genie::GV_TC)
                {
                    names.Add("Trees");
                    names.Add("Unique Units (except Turtle Ship)");
                    names.Add("Siege Weapons");
                }
                else
                {
                    names.Add("Unused");
                    names.Add("Unique Units");
                    names.Add("Siege Weapons & Boar");
                }
                names.Add("Standard Buildings");
                if (GenieVersion >= genie::GV_TC)
                {
                    names.Add("Walls & Gates");
                    if (GenieVersion >= genie::GV_Cysion)
                    {
                        names.Add("Gunpowder Units");
                    }
                    else
                    {
                        names.Add("Unused");
                    }
                    names.Add("Hunted Predator Animals");
                    names.Add("Monks");
                    names.Add("Castle");
                    names.Add("Spearmen");
                    names.Add("Cavalry Archers");
                    names.Add("Eagle Warriors");
                    if (GenieVersion >= genie::GV_Cysion)
                    {
                        names.Add("Camels");
                        if (GenieVersion >= genie::GV_C2)
                        {
                            names.Add("Leitis Attack");
                        }
                        else
                        {
                            names.Add("Unused");
                        }
                        names.Add("Condottiero");
                        names.Add("Unused");
                        names.Add("Fishing Ship");
                        names.Add("Mamelukes");
                        if (GenieVersion >= genie::GV_C2)
                        {
                            names.Add("Heroes");
                        }
                    }
                }
            }
            else
            {
                names.Add("Infantry");
                if (GenieVersion >= genie::GV_RoR)
                {
                    names.Add("Towers & Walls");
                    names.Add("Unused");
                    names.Add("Villagers & Gazelles & Medusa");
                }
                else
                {
                    names.Add("Towers & Walls, Melee");
                }
            }
        }
        else // SWGB and CC
        {
            // SWGB & CC
            names.Add("Aircraft");  // Selection 1
            // Airspeeder
            // AIR SHIPS!!!
            // Geonosian Warrior
            // Wild Gungan Flyer
            names.Add("Heavy Assault Machines");    // Selection 2
            // Assault Mech
            // AT-AT
            // Blizzards
            names.Add("Heavy Weapons");
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
            names.Add("Base Ranged/DuraArmor");
            names.Add("Base Melee/Armor");
            names.Add("Jedis & Bounty Hunters");
            // Jedi
            // Jedi with Holocron
            // Bounty Hunter
            names.Add("Assault Machines");
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
            names.Add("Decimators");
            // Assault Mechs
            // Decimator
            // AT-AT
            // Blizzards
            names.Add("Shield & Power Units");
            // Power Cores
            // Shield Wall
            // Shield Generators
            // Droid Storage Facility
            // Power Droids
            // Echo Base Power Generator
            names.Add("Ships");
            // Utility Trawler
            // Frigates
            // Cruisers
            // Destroyers
            // A-A Destroyers
            // Transport Ships
            names.Add("Submarines");
            // Frigates
            // Underwater Prefab Shelters
            // Gungan Buildings
            names.Add("All Buildings");
            // BUILDINGS!!!
            names.Add("Unused");
            names.Add("Defense Buildings");
            // Gate
            // Turrets
            // A-A Turrets
            // Echo Base Ion Cannon
            // Fortress
            // Theed Arch
            names.Add("Troopers");
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
            names.Add("Mounted Troopers");
            // Berserker
            // Scouts
            // Mounted Troopers
            // Anakin's Podracer
            // Landspeeder
            // Sebulba's Podracer
            // Skyhopper
            names.Add("Cruisers");
            // Cruisers
            names.Add("Pummels & Cannons");
            // Undeployed Cannon
            // Pummels
            // Cannon
            names.Add("Unused");
            names.Add("Workers");
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
            names.Add("Destroyers");
            // Destroyers
            names.Add("Standard Buildings");
            // BUILDINGS!!!
            names.Add("Walls & Gates");
            // GATES
            // WALLS
            // Theed Arch
            names.Add("Air Cruisers");
            // Air Cruisers
            // Blockade Runner
            // Star Destroyer
            // Deathstar
            names.Add("Wild Animals");
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
            names.Add("Unused");
            names.Add("Fortress");
            // Fortress
            names.Add("Unused");
            names.Add("Unused");
            names.Add("Unused");
            names.Add("Tame Animals"); // Selection 31
            // Fambaa Shield Generators
            // Wild Fambaa
            // Kaadu
            // Tauntaun
            // Cu-pa
            // Womp Rat
        }

        Customs.Write(KeyNumArmors, names.NumNames());
    }
    Effects_89_Type_CB1->Flash();
    for (size_t loop = 0; loop < 2; ++loop)
    {
        Attacks_Class_ComboBox[loop]->Flash();
    }

    class NameWriter
    {
    public:
        NameWriter(wxFileConfig &file, wxString &key, wxArrayString &list) :
            index(0), key(key), file(file), list(list) {}
        void Add(wxString name)
        {
            wxString line = key + lexical_cast<std::string>(index++);
            file.Write(line, name);
            list.Add(name);
        }
        long NumNames(void) const { return index; }
    private:
        long index;
        wxString &key;
        wxFileConfig &file;
        wxArrayString &list;
    };

    TerrainRestrictionNames.clear();
    if (Customs.Read(KeyNumTerrainTables, &NumNames, 0))
    {
        for (size_t loop = 0; loop < NumNames; ++loop)
        {
            wxString line = KeyTerrainTableNames + lexical_cast<std::string>(loop);
            Customs.Read(line, &read_buf, "Unused");
            TerrainRestrictionNames.Add(read_buf);
        }
    }
    else
    {
        NameWriter names(Customs, KeyTerrainTableNames, TerrainRestrictionNames);

        if (GenieVersion < genie::GV_AoKE3)
        {
            names.Add("Land + water");
            names.Add("Land");
            names.Add("Beach");
            names.Add("Water");
            names.Add("Land, damage 20 %");
            names.Add("Nothing");
            names.Add("Water + beach");
            names.Add("Land + shallows");
            names.Add("Plain");
            names.Add("Land - dirt");
            names.Add("Land + beach");
        }
        else if (GenieVersion < genie::GV_SWGB)
        {
            names.Add("All");
            names.Add("Land + shallows");
            names.Add("Beach");
            names.Add("Water, large wave");
            names.Add("Land");
            names.Add("Nothing");
            names.Add("Water");
            names.Add("All - water, foot dust");
            names.Add("Land - farm");
            names.Add("Nothing");
            names.Add("Land + beach");
            names.Add("Land - farm");
            names.Add("All - bridge, ground impact");
            names.Add("Water, small wave");
            names.Add("All - bridge, arrow decay");
            names.Add("Water, large wave");
            names.Add("Grass + beach");
            names.Add("Water + bridge - beach");
            names.Add("All - bridge, spear decay");
            names.Add("Only water + ice");
            if (GenieVersion >= genie::GV_TC)
            {
                names.Add("All - water, wheel track");
                names.Add("Shallow water");
                if (GenieVersion >= genie::GV_Cysion)
                {
                    names.Add("All - bridge, dart decay");
                    if (GenieVersion >= genie::GV_C2)
                    {
                        names.Add("All - bridge, arrow decay");
                        names.Add("All - bridge, ground impact");
                        names.Add("All - bridge, spear decay");
                        names.Add("All - bridge, dart decay");
                        names.Add("All - bridge, laser impact");
                        names.Add("All - water, cavalry dust");
                        names.Add("All - water, wheel track");
                        names.Add("Water, medium wave");
                        names.Add("All - water, wheel track");
                    }
                }
            }
        }
        else
        {
            names.Add("All");
            names.Add("Land + unbuildable");
            names.Add("Shore");
            names.Add("Water + shore + swamp, large wave");
            names.Add("Land");
            names.Add("Land + shore, bridge, AT-AT steps");
            names.Add("Water + shore + ice2");
            names.Add("Land - water, lava");
            names.Add("Land - water, lava, farm");
            names.Add("Only water");
            names.Add("Land - shore");
            names.Add("Land - water, lava, farm, path");
            names.Add("All - lava, medium impact");
            names.Add("Water, small wave");
            names.Add("All - lava, blowup");
            names.Add("Land + shore, bridge, AT-ST steps");
            names.Add("Grass + shore");
            names.Add("Water - shore + bridge");
            names.Add("All - bridge, lava, arrow/spear");
            names.Add("Land + shore, bridge, big steps");
            names.Add("Land + shore, bridge, wheel marks");
            names.Add("Water - deep water");
            names.Add("All - bridge, lava");
            names.Add("No restriction");
            names.Add("Only water");
            names.Add("Land + shore, bridge, no steps");
            names.Add("Land + shore, bridge, medium steps");
            names.Add("Deep water");
            names.Add("Wasteland");
            names.Add("Only Ice1");
            names.Add("Only Lava");
            names.Add("Only Water2");
            names.Add("Only Rock4");
        }

        Customs.Write(KeyNumTerrainTables, names.NumNames());
    }

    CivilizationResourceNames.clear();
    if (Customs.Read(KeyNumCivResources, &NumNames, 0))
    {
        for (size_t loop = 0; loop < NumNames; ++loop)
        {
            wxString line = KeyCivResourceNames + lexical_cast<std::string>(loop);
            Customs.Read(line, &read_buf, "Unused");
            CivilizationResourceNames.Add(read_buf);
        }
    }
    else
    {
        NameWriter names(Customs, KeyCivResourceNames, CivilizationResourceNames);

        if (GenieVersion < genie::GV_AoKE3)
        {
            names.Add("Food Storage");
            names.Add("Wood Storage");
            names.Add("Stone Storage");
            names.Add("Gold Storage");
            names.Add("Population Headroom");
            names.Add("Conversion Range");
            names.Add("Current Age");
            names.Add("Artifacts Captured");
            names.Add("Unused (Trade Bonus)");
            names.Add("Trade Goods");
            names.Add("Trade Production");
            names.Add("Current Population");
            names.Add("Corpse Decay Time");
            names.Add("Remarkable Discovery");
            names.Add("Ruins Captured");
            names.Add("Meat Storage");
            names.Add("Berry Storage");
            names.Add("Fish Storage");
            names.Add("Unused (Trade Tax)");
            names.Add("Total Units Owned");
            names.Add("Units Killed");
            names.Add("Technology Count");
            names.Add("% Map Explored");
            names.Add("Bronze Age Tech ID");
            names.Add("Iron Age Tech ID");
            names.Add("Tool Age Tech ID");
            names.Add("Attack Warning Sound ID");
            names.Add("Enable Priest Conversion");
            names.Add("Enable Building Conversion");
            names.Add("Bribery (Gold Cost Replace)");
            names.Add("Unused (Building Limit)");
            names.Add("Unused (Food Limit)");
            names.Add("Unit Limit");
            names.Add("Food Maintenance");
            names.Add("Faith");
            names.Add("Faith Recharging Rate");
            names.Add("Farm Food Amount");
            names.Add("Civilian Population");
            names.Add("Unused");
            names.Add("All Techs Achieved");
            names.Add("Military Population");
            names.Add("Conversions");
            names.Add("Standing Wonders");
            names.Add("Razings");
            names.Add("Kill Ratio");
            names.Add("Survival to Finish");
            names.Add("Tribute Inefficiency");
            names.Add("Gold Mining Productivity");
            names.Add("Town Center Unavailable");
            names.Add("Gold Counter");
            names.Add("Reveal Ally");
            names.Add("Unused (Houses)");
            names.Add("Temples");
            names.Add("Tribute Sent");
            names.Add("All Ruins Captured");
            names.Add("All Artifacts Captured");
            if (GenieVersion >= genie::GV_RoR)
            {
                names.Add("Heal Bonus");
                names.Add("Martyrdom");
            }
        }
        else if (GenieVersion < genie::GV_SWGB)
        {
            names.Add("Food Storage");
            names.Add("Wood Storage");
            names.Add("Stone Storage");
            names.Add("Gold Storage");
            names.Add("Population Headroom");
            names.Add("Conversion Range");
            names.Add("Current Age");
            names.Add("Relics Captured");
            names.Add("Unused (Trade Bonus)");
            names.Add("Trade Goods");
            names.Add("Unused (Trade Production)");
            names.Add("Current Population");
            names.Add("Corpse Decay Time");
            names.Add("Remarkable Discovery");
            names.Add("Monuments Captured");
            names.Add("Meat Storage");
            names.Add("Berry Storage");
            names.Add("Fish Storage");
            names.Add("Unused");
            names.Add("Total Units Owned");
            names.Add("Units Killed");
            names.Add("Technology Count");
            names.Add("% Map Explored");
            names.Add("Castle Age Tech ID");
            names.Add("Imperial Age Tech ID");
            names.Add("Feudal Age Tech ID");
            names.Add("Attack Warning Sound ID");
            names.Add("Enable Monk Conversion");
            names.Add("Enable Building Conversion");
            names.Add("Unused");
            names.Add("Unused (Building Limit)");
            names.Add("Unused (Food Limit)");
            names.Add("Bonus Population Cap");
            names.Add("Food Maintenance");
            names.Add("Faith");
            names.Add("Faith Recharging Rate");
            names.Add("Farm Food Amount");
            names.Add("Civilian Population");
            names.Add("Unused");
            names.Add("All Techs Achieved");
            names.Add("Military Population");
            names.Add("Conversions");
            names.Add("Standing Wonders");
            names.Add("Razings");
            names.Add("Kill Ratio");
            names.Add("Survival to Finish");
            names.Add("Tribute Inefficiency");
            names.Add("Gold Mining Productivity");
            names.Add("Town Center Unavailable");
            names.Add("Gold Counter");
            names.Add("Reveal Ally");
            names.Add("Unused (Houses)");
            names.Add("Monasteries");
            names.Add("Tribute Sent");
            names.Add("All Monuments Captured");
            names.Add("All Relics Captured");
            names.Add("Ore Storage");
            names.Add("Kidnap Storage");
            names.Add("Dark Age Tech ID");
            names.Add("Unused (Trade Good Quality)");
            names.Add("Unused (Trade Market Level)");
            names.Add("Unused (Formations)");
            names.Add("Building Housing Rate");
            names.Add("Tax Gather Rate");
            names.Add("Gather Accumulator");
            names.Add("Salvage Decay Rate");
            names.Add("Unused (Allow Formations)");
            names.Add("Can Convert");
            names.Add("Hit Points Killed");
            if (GenieVersion >= genie::GV_C2)
            {
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
            }
            else
            {
                names.Add("Killed P1");
                names.Add("Killed P2");
                names.Add("Killed P3");
                names.Add("Killed P4");
                names.Add("Killed P5");
                names.Add("Killed P6");
                names.Add("Killed P7");
                names.Add("Killed P8");
            }
            names.Add("Conversion Resistance");
            names.Add("Trade Vig Rate");
            names.Add("Stone Mining Productivity");
            names.Add("Queued Units");
            names.Add("Training Count");
            names.Add("Start with Unit 444 (PTWC)");
            names.Add("Boarding Recharge Rate");
            names.Add("Starting Villagers");
            names.Add("Research Cost Modifier");
            names.Add("Research Time Modifier");
            names.Add("Convert Boats");
            names.Add("Fish Trap Food Amount");
            names.Add("Heal Rate Modifier");
            names.Add("Healing Range");
            names.Add("Starting Food");
            names.Add("Starting Wood");
            names.Add("Starting Stone");
            names.Add("Starting Gold");
            names.Add("Enable PTWC / Kidnap / Loot");
            names.Add("Berserker Heal Timer");
            names.Add("Dominant Sheep Control");
            names.Add("Building Cost Sum");
            names.Add("Tech Cost Sum");
            names.Add("Relic Income Sum");
            names.Add("Trade Income Sum");
            if (GenieVersion >= genie::GV_C2)
            {
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
            }
            else
            {
                names.Add("P1 Tribute");
                names.Add("P2 Tribute");
                names.Add("P3 Tribute");
                names.Add("P4 Tribute");
                names.Add("P5 Tribute");
                names.Add("P6 Tribute");
                names.Add("P7 Tribute");
                names.Add("P8 Tribute");
                names.Add("P1 Kill Value");
                names.Add("P2 Kill Value");
                names.Add("P3 Kill Value");
                names.Add("P4 Kill Value");
                names.Add("P5 Kill Value");
                names.Add("P6 Kill Value");
                names.Add("P7 Kill Value");
                names.Add("P8 Kill Value");
                names.Add("P1 Razings");
                names.Add("P2 Razings");
                names.Add("P3 Razings");
                names.Add("P4 Razings");
                names.Add("P5 Razings");
                names.Add("P6 Razings");
                names.Add("P7 Razings");
                names.Add("P8 Razings");
                names.Add("P1 Razing Value");
                names.Add("P2 Razing Value");
                names.Add("P3 Razing Value");
                names.Add("P4 Razing Value");
                names.Add("P5 Razing Value");
                names.Add("P6 Razing Value");
                names.Add("P7 Razing Value");
                names.Add("P8 Razing Value");
            }
            names.Add("Standing Castles");
            names.Add("Hit Points Razed");
            if (GenieVersion >= genie::GV_C2)
            {
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
            }
            else
            {
                names.Add("Kills by P1");
                names.Add("Kills by P2");
                names.Add("Kills by P3");
                names.Add("Kills by P4");
                names.Add("Kills by P5");
                names.Add("Kills by P6");
                names.Add("Kills by P7");
                names.Add("Kills by P8");
                names.Add("Razings by P1");
                names.Add("Razings by P2");
                names.Add("Razings by P3");
                names.Add("Razings by P4");
                names.Add("Razings by P5");
                names.Add("Razings by P6");
                names.Add("Razings by P7");
                names.Add("Razings by P8");
            }
            names.Add("Value Killed by Others");
            names.Add("Value Razed by Others");
            names.Add("Killed by Others");
            names.Add("Razed by Others");
            if (GenieVersion >= genie::GV_C2)
            {
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
                names.Add("Unused");
            }
            else
            {
                names.Add("Tribute from P1");
                names.Add("Tribute from P2");
                names.Add("Tribute from P3");
                names.Add("Tribute from P4");
                names.Add("Tribute from P5");
                names.Add("Tribute from P6");
                names.Add("Tribute from P7");
                names.Add("Tribute from P8");
            }
            names.Add("Value Current Units");
            names.Add("Value Current Buildings");
            names.Add("Food Total");
            names.Add("Wood Total");
            names.Add("Stone Total");
            names.Add("Gold Total");
            names.Add("Total Value of Kills");
            names.Add("Total Tribute Received");
            names.Add("Total Value of Razings");
            names.Add("Total Castles Built");
            names.Add("Total Wonders Built");
            names.Add("Tribute Score");
            names.Add("Convert Min Adjustment");
            names.Add("Convert Max Adjustment");
            names.Add("Convert Resist Min Adjustment");
            names.Add("Convert Resist Max Adjustment");
            names.Add("Convert Building Min");
            names.Add("Convert Building Max");
            names.Add("Convert Building Chance");
            names.Add("Reveal Enemy");
            names.Add("Value Wonders Castles");
            names.Add("Food Score");
            names.Add("Wood Score");
            names.Add("Stone Score");
            names.Add("Gold Score"); // 188 Age of Kings ends here
            if (GenieVersion >= genie::GV_TC)
            {
                names.Add("Chopping Productivity");
                names.Add("Food-gathering Productivity");
                names.Add("Relic Gold Production Rate");
                names.Add("Converted Units Die");
                names.Add("Theocracy");
                names.Add("Crenellations");
                names.Add("Construction Rate Modifier");
                names.Add("Hun Wonder Bonus");
                names.Add("Spies Discount"); // 197 Conquerors ends here
                if (GenieVersion >= genie::GV_Cysion)
                {
                    names.Add("Unused");
                    names.Add("Unused");
                    names.Add("Unused");
                    names.Add("Unused");
                    names.Add("Unused");
                    names.Add("Unused");
                    names.Add("Unused");
                    names.Add("Feitoria Food Productivity");
                    names.Add("Feitoria Wood Productivity");
                    names.Add("Feitoria Stone Productivity");
                    names.Add("Feitoria Gold Productivity"); // 208 African Kingdoms ends here
                    names.Add("Reveal Enemy Town Centers");
                    names.Add("Relics Visible on Map"); // 210 Rise of the Rajas ends here
                    if (GenieVersion >= genie::GV_C2)
                    {
                        names.Add("Higher Elevation Bonus");
                        names.Add("Lower Elevation Bonus");
                        names.Add("Raiding Productivity");
                        names.Add("Mercenary Kipchak Count");
                        names.Add("Mercenary Kipchak Limit");
                        names.Add("Shepherd Productivity");
                        names.Add("Trigger Shared Visibility");
                        names.Add("Early Town Center Limit");
                        names.Add("Fishing Productivity");
                        names.Add("Unused");
                        names.Add("Monument Food Productivity");
                        names.Add("Monument Wood Productivity");
                        names.Add("Monument Stone Productivity");
                        names.Add("Monument Gold Productivity");
                        names.Add("Relic Food Production Rate");
                        names.Add("Villagers Killed By Gaia");
                        names.Add("Villagers Killed By Animals");
                        names.Add("Villagers Killed By AI Players");
                        names.Add("Villagers Killed By Human Players");
                        names.Add("Battle Royale Food Generation");
                        names.Add("Battle Royale Wood Generation");
                        names.Add("Battle Royale Stone Generation");
                        names.Add("Battle Royale Gold Generation");
                        names.Add("Spawn Cap");
                        names.Add("Flemish Militia Population");
                        names.Add("Farming Gold Productivity");
                        names.Add("Folwark Collect Amount");
                        names.Add("Folwark Collect Resource Type");
                        names.Add("Folwark Building ID");
                        names.Add("Units Converted");
                        names.Add("Stone Mining Gold Productivity");
                        names.Add("Workshop Food Generation");
                        names.Add("Workshop Wood Generation");
                        names.Add("Workshop Stone Generation");
                        names.Add("Workshop Gold Generation");
                        names.Add("Total Build Value Units");
                        names.Add("Total Build Value Buildings");
                        names.Add("Total Villagers Created");
                        names.Add("Total Villager Idle Periods");
                        names.Add("Total Villager Idle Seconds"); // 250 Dawn of the Dukes ends here
                        names.Add("Trade Food Percent");
                        names.Add("Trade Wood Percent");
                        names.Add("Trade Stone Percent");
                        names.Add("Livestock Food Productivity");
                        names.Add("Speedup Building Type");
                        names.Add("Speedup Building Range");
                        names.Add("Speedup Percentage");
                        names.Add("Speedup Object Type");
                        names.Add("Speedup Effect Type");
                        names.Add("Speedup Secondary Effect Type");
                        names.Add("Speedup Secondary Percentage");
                        names.Add("Civilization Name Override");
                        names.Add("Starting Scout ID");
                        names.Add("Relic Wood Production Rate");
                        names.Add("Relic Stone Production Rate");
                        names.Add("Chopping Gold Productivity");
                        names.Add("Foraging Wood Productivity");
                        names.Add("Hunter Productivity");
                        names.Add("Technology Reward Effect");
                        names.Add("Unit Repair Cost");
                        names.Add("Building Repair Cost");
                        names.Add("Elevation Higher Damage");
                        names.Add("Elevation Lower Damage");
                        names.Add("Infantry Kill Reward");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Military Can Convert");
                        names.Add("Military Conversion Range");
                        names.Add("Military Conversion Chance");
                        names.Add("Military Conversion Recharge Rate");
                        names.Add("Spawn Inside");
                        names.Add("Cavalry Kill Reward"); // 284
                        names.Add("Shared Visibility");
                        names.Add("Shared Exploration");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Killed Gaia");
                        names.Add("Killed P1");
                        names.Add("Killed P2");
                        names.Add("Killed P3");
                        names.Add("Killed P4");
                        names.Add("Killed P5");
                        names.Add("Killed P6");
                        names.Add("Killed P7");
                        names.Add("Killed P8");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Kills by Gaia");
                        names.Add("Kills by P1");
                        names.Add("Kills by P2");
                        names.Add("Kills by P3");
                        names.Add("Kills by P4");
                        names.Add("Kills by P5");
                        names.Add("Kills by P6");
                        names.Add("Kills by P7");
                        names.Add("Kills by P8");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Gaia Razings");
                        names.Add("P1 Razings");
                        names.Add("P2 Razings");
                        names.Add("P3 Razings");
                        names.Add("P4 Razings");
                        names.Add("P5 Razings");
                        names.Add("P6 Razings");
                        names.Add("P7 Razings");
                        names.Add("P8 Razings");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Razings by Gaia");
                        names.Add("Razings by P1");
                        names.Add("Razings by P2");
                        names.Add("Razings by P3");
                        names.Add("Razings by P4");
                        names.Add("Razings by P5");
                        names.Add("Razings by P6");
                        names.Add("Razings by P7");
                        names.Add("Razings by P8");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Gaia Kill Value");
                        names.Add("P1 Kill Value");
                        names.Add("P2 Kill Value");
                        names.Add("P3 Kill Value");
                        names.Add("P4 Kill Value");
                        names.Add("P5 Kill Value");
                        names.Add("P6 Kill Value");
                        names.Add("P7 Kill Value");
                        names.Add("P8 Kill Value");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Gaia Razing Value");
                        names.Add("P1 Razing Value");
                        names.Add("P2 Razing Value");
                        names.Add("P3 Razing Value");
                        names.Add("P4 Razing Value");
                        names.Add("P5 Razing Value");
                        names.Add("P6 Razing Value");
                        names.Add("P7 Razing Value");
                        names.Add("P8 Razing Value");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Gaia Tribute");
                        names.Add("P1 Tribute");
                        names.Add("P2 Tribute");
                        names.Add("P3 Tribute");
                        names.Add("P4 Tribute");
                        names.Add("P5 Tribute");
                        names.Add("P6 Tribute");
                        names.Add("P7 Tribute");
                        names.Add("P8 Tribute");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Tribute from Gaia");
                        names.Add("Tribute from P1");
                        names.Add("Tribute from P2");
                        names.Add("Tribute from P3");
                        names.Add("Tribute from P4");
                        names.Add("Tribute from P5");
                        names.Add("Tribute from P6");
                        names.Add("Tribute from P7");
                        names.Add("Tribute from P8");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused");
                        names.Add("Unused"); // 499
                    }
                }
            }
        }
        else
        {
            names.Add("Food Storage");
            names.Add("Carbon Storage");
            names.Add("Ore Storage");
            names.Add("Nova Storage");
            names.Add("Population Headroom");
            names.Add("Conversion Range");
            names.Add("Current Tech Level");
            names.Add("Holocrons Captured");
            names.Add("Unused (Trade Bonus)");
            names.Add("Trade Goods");
            names.Add("Recharge Rate of Shields");
            names.Add("Current Population");
            names.Add("Corpse Decay Time");
            names.Add("Remarkable Discovery");
            names.Add("Monuments Captured");
            names.Add("Meat Storage");
            names.Add("Berry Storage");
            names.Add("Fish Storage");
            names.Add("Power Core Range");
            names.Add("Total Units Owned");
            names.Add("Units Killed");
            names.Add("Technology Count");
            names.Add("% Map Explored");
            names.Add("Submarine Detection");
            names.Add("Shield Generator Range");
            names.Add("Unknown");
            names.Add("Drop-off Time of Shields");
            names.Add("Enable Jedi Conversion");
            names.Add("Enable Building Conversion");
            names.Add("Unknown");
            names.Add("Unused (Building Limit)");
            names.Add("Enable A-A Attack for AT-AT");
            names.Add("Bonus Population Cap");
            names.Add("Power Core Shielding");
            names.Add("Force");
            names.Add("Force Recharging Rate");
            names.Add("Farm Food Amount");
            names.Add("Civilian Population");
            names.Add("Shields On for Bombers/Fighters");
            names.Add("All Techs Achieved");
            names.Add("Military Population");
            names.Add("Conversions");
            names.Add("Standing Monuments");
            names.Add("Razings");
            names.Add("Kill Ratio");
            names.Add("Survival to Finish");
            names.Add("Tribute Inefficiency");
            names.Add("Nova Mining Productivity");
            names.Add("Town Center Unavailable");
            names.Add("Gold Counter");
            names.Add("Reveal Ally");
            names.Add("Shielding");
            names.Add("Monasteries");
            names.Add("Tribute Sent");
            names.Add("All Ruins Captured");
            names.Add("All Relics Captured");
            names.Add("Enable Stealth for Masters");
            names.Add("Kidnap Storage");
            names.Add("Masters Can See Hidden Units");
            names.Add("Trade Good Quality");
            names.Add("Trade Market Level");
            names.Add("Unused (Formations)");
            names.Add("Building Housing Rate");
            names.Add("Tax Gather Rate");
            names.Add("Gather Accumulator");
            names.Add("Salvage Decay Rate");
            names.Add("Unused (Allow Formations)");
            names.Add("Can Convert");
            names.Add("Hit Points Killed");
            names.Add("Killed P1");
            names.Add("Killed P2");
            names.Add("Killed P3");
            names.Add("Killed P4");
            names.Add("Killed P5");
            names.Add("Killed P6");
            names.Add("Killed P7");
            names.Add("Killed P8");
            names.Add("Conversion Resistance");
            names.Add("Trade Vig Rate");
            names.Add("Ore Mining Productivity");
            names.Add("Queued Units");
            names.Add("Training Count");
            names.Add("Start with Packed Town Center");
            names.Add("Boarding Recharge Rate");
            names.Add("Starting Villagers");
            names.Add("Tech Cost Modifier");
            names.Add("Tech Time Modifier");
            names.Add("Concentration");
            names.Add("Fish Trap Food Amount");
            names.Add("Medic Healing Rate");
            names.Add("Healing Range");
            names.Add("Starting Food");
            names.Add("Starting Carbon");
            names.Add("Starting Ore");
            names.Add("Starting Nova");
            names.Add("Enable PTWC / Kidnap / Loot");
            names.Add("Berserker Heal Timer");
            names.Add("Dominant Sheep Control");
            names.Add("Object Cost Sum");
            names.Add("Tech Cost Sum");
            names.Add("Holocron Nova Sum");
            names.Add("Trade Income Sum");
            names.Add("P1 Tribute");
            names.Add("P2 Tribute");
            names.Add("P3 Tribute");
            names.Add("P4 Tribute");
            names.Add("P5 Tribute");
            names.Add("P6 Tribute");
            names.Add("P7 Tribute");
            names.Add("P8 Tribute");
            names.Add("P1 Kill Value");
            names.Add("P2 Kill Value");
            names.Add("P3 Kill Value");
            names.Add("P4 Kill Value");
            names.Add("P5 Kill Value");
            names.Add("P6 Kill Value");
            names.Add("P7 Kill Value");
            names.Add("P8 Kill Value");
            names.Add("P1 Razings");
            names.Add("P2 Razings");
            names.Add("P3 Razings");
            names.Add("P4 Razings");
            names.Add("P5 Razings");
            names.Add("P6 Razings");
            names.Add("P7 Razings");
            names.Add("P8 Razings");
            names.Add("P1 Razing Value");
            names.Add("P2 Razing Value");
            names.Add("P3 Razing Value");
            names.Add("P4 Razing Value");
            names.Add("P5 Razing Value");
            names.Add("P6 Razing Value");
            names.Add("P7 Razing Value");
            names.Add("P8 Razing Value");
            names.Add("Standing Fortresses");
            names.Add("Hit Points Razed");
            names.Add("Kills by P1");
            names.Add("Kills by P2");
            names.Add("Kills by P3");
            names.Add("Kills by P4");
            names.Add("Kills by P5");
            names.Add("Kills by P6");
            names.Add("Kills by P7");
            names.Add("Kills by P8");
            names.Add("Razings by P1");
            names.Add("Razings by P2");
            names.Add("Razings by P3");
            names.Add("Razings by P4");
            names.Add("Razings by P5");
            names.Add("Razings by P6");
            names.Add("Razings by P7");
            names.Add("Razings by P8");
            names.Add("Value Killed by Others");
            names.Add("Value Razed by Others");
            names.Add("Killed by Others");
            names.Add("Razed by Others");
            names.Add("Tribute from P1");
            names.Add("Tribute from P2");
            names.Add("Tribute from P3");
            names.Add("Tribute from P4");
            names.Add("Tribute from P5");
            names.Add("Tribute from P6");
            names.Add("Tribute from P7");
            names.Add("Tribute from P8");
            names.Add("Value Current Units");
            names.Add("Value Current Buildings");
            names.Add("Food Total");
            names.Add("Carbon Total");
            names.Add("Ore Total");
            names.Add("Nova Total");
            names.Add("Total Value of Kills");
            names.Add("Total Tribute Received");
            names.Add("Total Value of Razings");
            names.Add("Total Fortresses Built");
            names.Add("Total Monuments Built");
            names.Add("Tribute Score");
            names.Add("Convert Min Adjustment");
            names.Add("Convert Max Adjustment");
            names.Add("Convert Resist Min Adjustment");
            names.Add("Convert Resist Max Adjustment");
            names.Add("Convert Building Min");
            names.Add("Convert Building Max");
            names.Add("Convert Building Chance");
            names.Add("Reveal Enemy");
            names.Add("Value Wonders Castles");
            names.Add("Food Score");
            names.Add("Carbon Score");
            names.Add("Ore Score");
            names.Add("Nova Score");
            names.Add("Carbon Gathering Productivity");
            names.Add("Food-gathering Productivity");
            names.Add("Holocron Nova Production Rate");
            names.Add("Converted Units Die");
            names.Add("Meditation");
            names.Add("Crenellations");
            names.Add("Construction Rate Modifier");
            names.Add("Biological Self Regeneration");
            names.Add("Spies Discount");
            names.Add("Unknown");
            names.Add("Unknown");
            names.Add("Misc Counter 1");
            names.Add("Misc Counter 2");
            names.Add("Misc Counter 3");
            names.Add("Misc Counter 4");
            names.Add("Misc Counter 5");
            names.Add("Unknown");
            names.Add("Unknown");
            names.Add("Unknown");
            names.Add("Unknown");
            names.Add("Unknown");
            if (GenieVersion >= genie::GV_CC)
            {
                names.Add("Unknown");
            }
        }

        Customs.Write(KeyNumCivResources, names.NumNames());
    }

    unit_filters.Clear();
    unit_filters.Add("*Choose*");
    unit_filters.Add("Type");
    unit_filters.Add("ID");
    unit_filters.Add("Language File Name");
    unit_filters.Add("Language File Creation");
    unit_filters.Add("Class");
    unit_filters.Add("Standing Graphics");
    unit_filters.Add("Dying Graphics");
    unit_filters.Add("Undead Mode");
    unit_filters.Add("Hit Points");
    unit_filters.Add("Line of Sight");
    unit_filters.Add("Garrison Capacity");
    unit_filters.Add("Collision Size XY");
    unit_filters.Add("Collision Size Z");
    unit_filters.Add("Train Sound");
    unit_filters.Add("Dead Unit");
    unit_filters.Add("Sort Number");
    unit_filters.Add("Can be Built on");
    unit_filters.Add("Icon");
    unit_filters.Add("Hide in Editor");
    unit_filters.Add("Portrait Picture");
    unit_filters.Add("Available");
    unit_filters.Add("Placement Side Terrain x2");
    unit_filters.Add("Placement Terrain x2");
    unit_filters.Add("Clearance Size XY");
    unit_filters.Add("Hill Mode");
    unit_filters.Add("Fog Visibility");
    unit_filters.Add("Terrain Table");
    unit_filters.Add("Fly Mode");
    unit_filters.Add("Resource Capacity");
    unit_filters.Add("Resource Decay");
    unit_filters.Add("Blast Defense Level");
    unit_filters.Add("Combat Level");
    unit_filters.Add("Interaction Mode");
    unit_filters.Add("Minimap Mode");
    unit_filters.Add("Interface Kind");
    unit_filters.Add("Multiple Attribute Mode");
    unit_filters.Add("Minimap Color");
    unit_filters.Add("Resource Storages");
    unit_filters.Add("Damage Graphic Count");
    unit_filters.Add("Damage Graphics");
    unit_filters.Add("Selection Sound");
    unit_filters.Add("Dying Sound");
    unit_filters.Add("Attack Reaction");
    unit_filters.Add("Convert Terrain");
    unit_filters.Add("Internal Name");
    unit_filters.Add("Internal Name 2");
    if (GenieVersion >= genie::GV_AoEB)
    {
        unit_filters.Add("Language File Help");
        unit_filters.Add("Language File Hot Key Text");
        unit_filters.Add("Hot Key");
        unit_filters.Add("Recyclable");
        unit_filters.Add("Gatherable");
        unit_filters.Add("Doppelganger on Death");
        unit_filters.Add("Gather Group");
        unit_filters.Add("Selection Effect");
        unit_filters.Add("Editor Selection Color");
        unit_filters.Add("Selection Size XY");
        unit_filters.Add("Selection Size Z");
        unit_filters.Add("Copy ID");
        if (GenieVersion >= genie::GV_AoKE3)
        {
            unit_filters.Add("Damage Sound");
            unit_filters.Add("Occlusion Mode");
            if (GenieVersion >= genie::GV_AoKA)
            {
                unit_filters.Add("Base ID");
                if (GenieVersion >= genie::GV_AoK)
                {
                    unit_filters.Add("Disabled");
                    if (GenieVersion >= genie::GV_TC)
                    {
                        unit_filters.Add("Trait");
                        unit_filters.Add("Civilization");
                        unit_filters.Add("Nothing");
                        if (GenieVersion >= genie::GV_SWGB)
                        {
                            unit_filters.Add("Unitline");
                            unit_filters.Add("Min Tech Level");
                        }
                    }
                }
            }
        }
        if (GenieVersion >= genie::GV_AoKA || isAoE1DE)
        {
            unit_filters.Add("Obstruction Type");
            unit_filters.Add("Obstruction Class");
        }
        if (isAoE2DE || isAoE1DE)
        {
            unit_filters.Add("Blood Unit");
        }
    }

    unit_filters.Add("Speed");
    unit_filters.Add("Tracking ID");
    unit_filters.Add("Walking Graphics");
    unit_filters.Add("Rotation Speed");
    unit_filters.Add("Size Class");
    unit_filters.Add("Trailing Unit");
    unit_filters.Add("Trailing Unit Mode");
    unit_filters.Add("Trailing Unit Density");
    unit_filters.Add("Move Algorithm");
    unit_filters.Add("Default Task");
    unit_filters.Add("Search Radius");
    unit_filters.Add("Work Rate");
    unit_filters.Add("Drop Site Count");
    unit_filters.Add("Drop Sites");
    unit_filters.Add("Task Swap Group");
    unit_filters.Add("Attack Sound");
    unit_filters.Add("Move Sound");
    unit_filters.Add("Run Pattern");
    unit_filters.Add("Task Count");
    unit_filters.Add("Tasks");
    unit_filters.Add("Base Armor");
    unit_filters.Add("Attack Count");
    unit_filters.Add("Attacks");
    unit_filters.Add("Armor Count");
    unit_filters.Add("Armors");
    unit_filters.Add("Terrain Defense Bonus");
    unit_filters.Add("Max Range");
    unit_filters.Add("Blast Width");
    unit_filters.Add("Reload Time");
    unit_filters.Add("Projectile Unit");
    unit_filters.Add("Accuracy Percent");
    unit_filters.Add("Break off Combat");
    unit_filters.Add("Frame Delay");
    unit_filters.Add("Graphic Displacement");
    unit_filters.Add("Blast Attack Level");
    unit_filters.Add("Min Range");
    unit_filters.Add("Attack Graphic");
    unit_filters.Add("Displayed Melee Armor");
    unit_filters.Add("Displayed Attack");
    unit_filters.Add("Displayed Range");
    unit_filters.Add("Displayed Reload Time");
    if (GenieVersion >= genie::GV_AoKB)
    {
        unit_filters.Add("Rotation Angles");
        unit_filters.Add("Attack Dispersion");
        if (isAoE2DE)
        {
            unit_filters.Add("Train Wave Works Sound");
            unit_filters.Add("Damage Wave Works Sound");
            unit_filters.Add("Selection Wave Works Sound");
            unit_filters.Add("Dying Wave Works Sound");
            unit_filters.Add("Min Collision Size Multiplier");
            unit_filters.Add("Attack Wave Works Sound");
            unit_filters.Add("Move Wave Works Sound");
            unit_filters.Add("Bonus Damage Resistance");
        }
    }

    unit_filters.Add("Projectile Type");
    unit_filters.Add("Smart Mode");
    unit_filters.Add("Hit Mode");
    unit_filters.Add("Vanish Mode");
    unit_filters.Add("Area Effect Specials");
    unit_filters.Add("Projectile Arc");

    unit_filters.Add("Resource Costs");
    unit_filters.Add("Train Time");
    unit_filters.Add("Train Location");
    unit_filters.Add("Train Button");
    unit_filters.Add("Displayed Pierce Armor");
    if (GenieVersion >= genie::GV_AoKE3)
    {
        unit_filters.Add("Rear Attack Modifier");
        unit_filters.Add("Flank Attack Modifier");
        unit_filters.Add("Creatable Type");
        unit_filters.Add("Total Projectiles");
        unit_filters.Add("Max Total Projectiles");
        unit_filters.Add("Projectile Spawning Area");
        unit_filters.Add("Secondary Projectile Unit");
        unit_filters.Add("Special Graphic");
        unit_filters.Add("Special Ability");
        if (GenieVersion >= genie::GV_AoKB)
        {
            unit_filters.Add("Hero Mode");
            unit_filters.Add("Garrison Graphic");
            if (isAoE2DE)
            {
                unit_filters.Add("Spawning Graphic");
                unit_filters.Add("Upgrade Graphic");
                unit_filters.Add("Max Charge");
                unit_filters.Add("Recharge Rate");
                unit_filters.Add("Charge Event");
                unit_filters.Add("Charge Type");
                unit_filters.Add("Hero Glow Graphic");
                unit_filters.Add("Min Conversion Time Mod");
                unit_filters.Add("Max Conversion Time Mod");
                unit_filters.Add("Conversion Chance Mod");
                unit_filters.Add("Blast Damage");
            }
        }
    }

    unit_filters.Add("Construction Graphic");
    unit_filters.Add("Adjacent Mode");
    unit_filters.Add("Graphics Angle");
    unit_filters.Add("Disappears After Built");
    unit_filters.Add("Stack Unit");
    unit_filters.Add("Foundation Terrain");
    unit_filters.Add("Old Overlay");
    unit_filters.Add("Tech");
    unit_filters.Add("Construction Sound");
    if (GenieVersion >= genie::GV_AoKE3)
    {
        unit_filters.Add("Can Burn");
        unit_filters.Add("Annexes");
        unit_filters.Add("Transform Unit");
        unit_filters.Add("Transform Sound");
        unit_filters.Add("Garrison Type");
        unit_filters.Add("Garrison Heal Rate");
        unit_filters.Add("Garrison Repair Rate");
        unit_filters.Add("Pile Unit");
        unit_filters.Add("Looting Table");
        if (GenieVersion >= genie::GV_AoKA)
        {
            unit_filters.Add("Head Unit");
            if (GenieVersion >= genie::GV_TC)
            {
                unit_filters.Add("Snow Graphic");
                if (isAoE2DE)
                {
                    unit_filters.Add("Foundation Destruction Graphic");
                    unit_filters.Add("Foundation Rubble Graphic");
                    unit_filters.Add("Researching Graphic");
                    unit_filters.Add("Research Completed Graphic");
                    unit_filters.Add("Transform Wave Works Sound");
                    unit_filters.Add("Construction Wave Works Sound");
                }
            }
        }
    }
    unit_filters.Sort();

    research_filters.Clear();
    research_filters.Add("*Choose*");
    research_filters.Add("Lang File Name");
    research_filters.Add("Internal Name");
    research_filters.Add("Required Techs");
    research_filters.Add("Min. Req. Techs");
    research_filters.Add("Research Location");
    research_filters.Add("Research Time");
    research_filters.Add("Effect");
    research_filters.Add("Type");
    research_filters.Add("Icon");
    research_filters.Add("Button");
    research_filters.Add("Lang Help");
    research_filters.Add("Lang Tech Tree");
    research_filters.Add("Hotkey");
    research_filters.Add("Cost Types");
    research_filters.Add("Cost Amounts");
    research_filters.Add("Cost Uses");
    if (GenieVersion >= genie::GV_AoK)
    {
        research_filters.Add("Civilization");
        research_filters.Add("Full Tech Mode");
        if (GenieVersion >= genie::GV_SWGB)
        {
            research_filters.Add("Internal Name 2");
        }
        if (isAoE2DE)
        {
            research_filters.Add("Repeatable");
        }
    }
    research_filters.Sort();

    terrain_filters.Clear();
    terrain_filters.Add("*Choose*");
    terrain_filters.Add("Internal Name");
    terrain_filters.Add("Sprite Name");
    terrain_filters.Add("Sprite");
    terrain_filters.Add("Enabled");
    terrain_filters.Add("Random");
    terrain_filters.Add("Shape Pointer");
    terrain_filters.Add("Sound");
    terrain_filters.Add("Colors");
    terrain_filters.Add("Cliff Colors");
    terrain_filters.Add("Passable Terrain");
    terrain_filters.Add("Impassable Terrain");
    terrain_filters.Add("Frame Count");
    terrain_filters.Add("Angle Count");
    terrain_filters.Add("Terrain to Draw");
    terrain_filters.Add("Terrain Dimensions");
    terrain_filters.Add("Terrain Units Used");
    if (GenieVersion >= genie::GV_AoKB || isAoE1DE)
    {
        terrain_filters.Add("Blend Priority");
        terrain_filters.Add("Blend Type");
    }
    if (isAoE2DE || isAoE1DE)
    {
        terrain_filters.Add("Water");
        terrain_filters.Add("Hide in Editor");
        terrain_filters.Add("Name String");
    }
    if (isAoE2DE)
    {
        terrain_filters.Add("Overlay Mask");
        terrain_filters.Add("Wave Works Stop Sound");
        terrain_filters.Add("Wave Works Sound");
    }
    if (GenieVersion < genie::GV_SWGB)
    {
        terrain_filters.Add("Phantom Variable");
    }
    terrain_filters.Sort();

    graphic_filters.Clear();
    graphic_filters.Add("*Choose*");
    graphic_filters.Add("Internal Name");
    graphic_filters.Add("Sprite Name");
    graphic_filters.Add("Sprite");
    graphic_filters.Add("Disabler");
    graphic_filters.Add("Old Color Flag");
    graphic_filters.Add("Layer");
    graphic_filters.Add("Player Color Forcer");
    graphic_filters.Add("Transparent Picking");
    graphic_filters.Add("Sound");
    graphic_filters.Add("Coordinates");
    graphic_filters.Add("Delta Count");
    graphic_filters.Add("Angle Sounds Used");
    graphic_filters.Add("Angle Sounds");
    graphic_filters.Add("Frames per Angle");
    graphic_filters.Add("Angle Count");
    graphic_filters.Add("New Speed");
    graphic_filters.Add("Animation Duration");
    graphic_filters.Add("Replay Delay");
    graphic_filters.Add("Sequence Type");
    graphic_filters.Add("Mirroring Mode");
    if (isAoE1DE)
    {
        graphic_filters.Add("First Frame");
    }
    if (GenieVersion >= genie::GV_AoKB)
    {
        graphic_filters.Add("Old Editor Flag");
        if (isAoE2DE)
        {
            graphic_filters.Add("Wave Works Sound");
            graphic_filters.Add("Angle Wave Works Sounds");
            graphic_filters.Add("Particle Effect Name");
        }
    }
    graphic_filters.Add("Pointer");
    graphic_filters.Sort();

    soundfile_filters.Clear();
    soundfile_filters.Add("*Choose*");
    soundfile_filters.Add("Filename");
    soundfile_filters.Add("DRS");
    soundfile_filters.Add("Probability");
    if (GenieVersion >= genie::GV_AoKE3)
    {
        soundfile_filters.Add("Civilization");
        soundfile_filters.Add("Icon Set");
    }
    soundfile_filters.Sort();

    for (size_t loop = 0; loop < 2; ++loop)
    {
        Units_Class_ComboBox[loop]->Flash();
        Units_SearchFilters[loop]->Flash();
        Research_SearchFilters[loop]->Flash();
        Terrains_SearchFilters[loop]->Flash();
        Graphics_SearchFilters[loop]->Flash();
        Sounds_Items_SearchFilters[loop]->Flash();
    }
}

void AGE_Frame::LoadLists()
{
    OnCivCountChange();
    ListTerrainRestrictions(true);
    InitPlayerColors();
    InitSounds(true);
    InitGraphics(true);
    ListTerrainNumbers();
    InitTerrains1(true);
    InitTerrainBorders(true);
    ListMapData();
    InitRandomMaps();
    InitTechs(true);
    if (GenieVersion >= genie::GV_SWGB)
    {
        InitUnitLines();
    }
    else
    {
        UnitLines_UnitLines_ListV->Clear();
        UnitLines_UnitLineUnits_ListV->Clear();
    }
    //InitCivs(true);
    InitUnits(GenieVersion < genie::GV_AoKE3, true);
    InitResearches(true);
    if (GenieVersion >= genie::GV_AoKA)
    {
        InitTTAges();
        InitTTBuildings();
        InitTTUnits();
        InitTTResearches();
    }
    else
    {
        TechTrees_MainList_Ages_ListV->Clear();
        TechTrees_Ages_Buildings.List->Clear();
        TechTrees_Ages_Units.List->Clear();
        TechTrees_Ages_Researches.List->Clear();
        TechTrees_MainList_Buildings_ListV->Clear();
        TechTrees_Buildings_Buildings.List->Clear();
        TechTrees_Buildings_Units.List->Clear();
        TechTrees_Buildings_Researches.List->Clear();
        TechTrees_MainList_Units_ListV->Clear();
        TechTrees_Units_Units.List->Clear();
        TechTrees_MainList_Researches_ListV->Clear();
        TechTrees_Researches_Buildings.List->Clear();
        TechTrees_Researches_Units.List->Clear();
        TechTrees_Researches_Researches.List->Clear();
    }
    if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
    {
        InitTerrainBlends();
    }

    wxCommandEvent e;
    OnCivSelect(e);
    OnUnitSelect(e);
    OnResearchSelect(e);
    OnEffectSelect(e);
    OnGraphicSelect(e);
    OnSoundSelect(e);
    OnTerrainSelect(e);
    OnTerrainRestrictionsTerrainSelect(e);
    OnPlayerColorSelect(e);
    if (GenieVersion != genie::GV_TCV && GenieVersion != genie::GV_CCV && GenieVersion != genie::GV_CCV2)
    {
        OnTerrainBorderSelect(e);
    }
    OnRandomMapSelect(e);
    if (GenieVersion >= genie::GV_AoKA)
    {
        OnTTAgeSelect(e);
        OnTTBuildingSelect(e);
        OnTTUnitSelect(e);
        OnTTResearchSelect(e);
        if (GenieVersion >= genie::GV_SWGB)
        {
            OnUnitLineSelect(e);
        }
    }
}

void AGE_Frame::InitSearch(const wxString &yes, const wxString &no)
{
    SearchYes = wxStringTokenize(yes, "|");
    SearchNo = wxStringTokenize(no, "|");
}

bool AGE_Frame::SearchMatches(const wxString &hay)
{
    bool matches = false;

    // If there is no search text, list normally.
    if (SearchYes.empty())
    {
        matches = true;
    }
    else // If search text has a match.
    {
        if (SearchAnd) // All search parts must match.
        {
            matches = true;
            for (const wxString &pin : SearchYes)
                if (wxNOT_FOUND == hay.Find(pin))
                {
                    matches = false;
                    break;
                }
        }
        else // Only one match needed.
        {
            for (const wxString &pin : SearchYes)
                if (wxNOT_FOUND != hay.Find(pin))
                {
                    matches = true;
                    break;
                }
        }
    }

    // We don't need to check for excluding if it's not going to be listed.
    // If there is no exclude text, list normally.
    if (!matches || SearchNo.empty())
    {
        return matches;
    }
    else // If exclude text has a match.
    {
        if (ExcludeAnd) // All search parts must match.
        {
            matches = false;
            for (const wxString &pin : SearchNo)
                if (wxNOT_FOUND == hay.Find(pin))
                {
                    matches = true;
                    break;
                }
        }
        else // Only one match needed.
        {
            for (const wxString &pin : SearchNo)
                if (wxNOT_FOUND != hay.Find(pin))
                {
                    matches = false;
                    break;
                }
        }
    }

    return matches;
}

void AGE_Frame::OnSelection_SearchFilters(wxCommandEvent &event)
{
    for (size_t loop = 0; loop < 2; ++loop) // Custom search filters
    {
        if (event.GetId() == Graphics_SearchFilters[loop]->GetId())
        {
            ListGraphics(false);
            Graphics_Graphics_Search->SetFocus();
        }
        else if (event.GetId() == Terrains_SearchFilters[loop]->GetId())
        {
            ListTerrains1(false);
            Terrains_Terrains_Search->SetFocus();
        }
        else if (event.GetId() == TechTrees_MainList_Units_SearchFilters[loop]->GetId())
        {
            ListTTUnits();
            TechTrees_MainList_Units_Search->SetFocus();
        }
        else if (event.GetId() == TechTrees_MainList_Buildings_SearchFilters[loop]->GetId())
        {
            ListTTBuildings();
            TechTrees_MainList_Buildings_Search->SetFocus();
        }
        else if (event.GetId() == TechTrees_MainList_Researches_SearchFilters[loop]->GetId())
        {
            ListTTResearches();
            TechTrees_MainList_Researches_Search->SetFocus();
        }
        else if (event.GetId() == Research_SearchFilters[loop]->GetId())
        {
            ListResearches(false);
            Research_Research_Search->SetFocus();
        }
        else if (event.GetId() == Sounds_Items_SearchFilters[loop]->GetId())
        {
            ListSoundItems();
            Sounds_Items_Search->SetFocus();
        }
    }
}

void AGE_Frame::RefreshList(ProperList *list, std::vector<int> *oldies)
{
    unsigned long cookie;
    size_t first_visible = list->GetVisibleRowsBegin();
    int first_selected = list->GetFirstSelected(cookie);
    //auto last_item_count = list->GetItemCount();
    size_t name_count = list->names.size();

    //list->SetItemCount(0); // Clears selections and makes all calls to SetItemPosition be ignored.
    list->SetItemCount(name_count);
    if (name_count)
    {
        // Set selections and first visible item.
        if (first_selected == wxNOT_FOUND)
        {
            first_selected = 0;
        }
        list->DeselectAll();
        if (How2List == ListMode::ADD || first_selected >= name_count)
        {
            first_selected = name_count - 1;
        }
        list->ScrollToRow(first_visible);
        if (Reselection && How2List != ListMode::ADD && How2List != ListMode::DEL && oldies)
        {
            // Select old indexes again.
            auto old = oldies->crbegin();
            auto it = list->indexes.crbegin();
            first_selected = 0;
            while (old != oldies->crend() && it != list->indexes.crend())
            {
                if (*it == *old)
                {
                    first_selected = list->indexes.crend() - 1 - it;
                    list->Select(first_selected, true);
                    ++it;
                    ++old;
                }
                else if (*it > *old)
                {
                    ++it;
                }
                else
                {
                    ++old;
                }
            }
        }
        if (!list->GetSelectedCount())
        {
            list->Select(first_selected, true);
        }
        list->EnsureVisible(first_selected);
        if (How2List != ListMode::SEARCH)
        {
            list->SetFocus();
        }
    }

    How2List = ListMode::SEARCH;
    list->Refresh();
}

bool AGE_Frame::Paste11Check(size_t numPastes, size_t numCopies)
{
    bool result = numCopies == numPastes;
    if (!result)
        wxMessageBox(wxString::Format("%u copies, %u selections.\nClick paste tool to switch to sequential paste.", numCopies, numPastes), "Selections Mismatch");
    return result;
}

void AGE_Frame::SearchAllSubVectors(ProperList *list, wxTextCtrl *topSearch, wxTextCtrl *subSearch)
{
    size_t selections = list->GetSelectedCount();
    wxBusyCursor WaitCursor;
    if (selections == 0) return;

    unsigned long cookie;
    std::set<uint32_t> topNums, subNums;
    int last = list->GetFirstSelected(cookie);
    for (size_t loop = 0; loop < selections; ++loop)
    {
        std::string line(list->names[last]);
        last = list->GetNextSelected(cookie);
        size_t found = line.find(" ", 3);
        topNums.insert(lexical_cast<uint32_t>(line.substr(2, found - 2)));
        subNums.insert(lexical_cast<uint32_t>(line.substr(2 + found, line.find(" ", found + 3) - found - 2)));
    }
    wxString topText;
    for (unsigned num : topNums)
    {
        topText += " " + lexical_cast<std::string>(num) + " -|";
    }
    topSearch->SetValue(topText.Truncate(topText.size() - 1));
    if (FilterAllSubs)
    {
        wxString subText;
        for (unsigned num : subNums)
        {
            subText += " " + lexical_cast<std::string>(num) + " -|";
        }
        subSearch->SetValue(subText.Truncate(subText.size() - 1));
    }
}

void AGE_Frame::getSelectedItems(const size_t selections, const ProperList *list, std::vector<int> &indexes)
{
    unsigned long cookie;
    indexes.resize(selections);
    int last = list->GetFirstSelected(cookie);
    for (size_t sel = 0; sel < selections; ++sel)
    {
        indexes[sel] = list->indexes[last];
        last = list->GetNextSelected(cookie);
    }
    SetStatusText("Times listed: " + lexical_cast<std::string>(++times_listed), 2);
}
