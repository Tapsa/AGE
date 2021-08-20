#include "Common.h"
#include "../AGE_Frame.h"
#include "../EditableVersion.h"

void AGE_Frame::FillListsBasedOnGameVersion()
{
    task_names.Clear();
    // When changing this, edit all 4 other places too
    task_names.Add("Unused Ability/Invalid Ability");   // Selection 0
    task_names.Add("0: None");
    task_names.Add("1: Move to");
    task_names.Add(GenieVersion < genie::GV_AoKA ? "2: None" : "2: Follow");
    task_names.Add("3: Garrison");
    task_names.Add("4: Explore");
    task_names.Add("5: Gather/Rebuild");
    task_names.Add("6: Graze, deleted?");
    task_names.Add("7: Combat");
    task_names.Add("8: Shoot");
    task_names.Add("9: Attack");
    task_names.Add("10: Fly");
    task_names.Add("11: Scare/Hunt, deleted?");
    task_names.Add("12: Unload (Boat-Like)");
    task_names.Add(GenieVersion < genie::GV_AoKA ? "13: None" : "13: Guard");
    task_names.Add(GenieVersion < genie::GV_Cysion || GenieVersion > genie::GV_LatestDE2 ? "14: None" : "14: Siege Tower Ability");
    task_names.Add("20: Escape, deleted?");
    task_names.Add("21: Make");
    //task_names.Add("100: Num"); // Useless
    task_names.Add("101: Build");
    task_names.Add("102: Make a Unit");
    task_names.Add("103: Make a Tech");
    task_names.Add("104: Convert");
    task_names.Add("105: Heal");
    task_names.Add("106: Repair");
    task_names.Add("107: Get Auto-converted");
    task_names.Add("108: Discovery Artifact");
    task_names.Add("109: Unknown, nothing?");
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
        task_names.Add("130: Unknown, nothing?");
        task_names.Add("131: Off-Map Trade");
        task_names.Add("132: Pickup Unit");
        task_names.Add("133: Charge Attack");
        task_names.Add("134: Transform Unit");
        task_names.Add("135: Kidnap Unit");
        task_names.Add("136: Deposit Unit");
        task_names.Add("149: Shear");
        if (GenieVersion >= genie::GV_Cysion && GenieVersion <= genie::GV_LatestDE2)
        {
            task_names.Add("150: Regeneration (obsolete)");
            task_names.Add("151: Feitoria Ability");
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
        class_names.Add("0 - Foot Archer");
        class_names.Add("1 - Artifact");
        class_names.Add("2 - Trade Boat");
        class_names.Add("3 - Building");
        class_names.Add("4 - Civilian");
        class_names.Add("5 - Ocean Fish");
        class_names.Add("6 - Infantry");
        class_names.Add("7 - Berry Bush");
        class_names.Add("8 - Stone Mine");
        class_names.Add("9 - Prey Animal");
        class_names.Add("10 - Wild Animal");
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
        class_names.Add(GenieVersion < genie::GV_AoKA ? "23 - Chariot Archer" : "23 - Conquistador and Arambai");
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
            class_names.Add("45 - Two Handed Swordsman (unused)");
            class_names.Add("46 - Pikeman (unused)");
            class_names.Add("47 - Scout");
            class_names.Add("48 - Ore Mine (removed concept)");
            class_names.Add("49 - Farm");
            class_names.Add("50 - Spearman (unused)");
            class_names.Add("51 - Packed Unit");
            class_names.Add("52 - Tower");
            class_names.Add("53 - Boarding Boat (removed concept)");
            class_names.Add("54 - Unpacked Siege Unit");
            class_names.Add("55 - Ballista/Scorpion");
            class_names.Add("56 - Raider (removed concept)");
            class_names.Add("57 - Cavalry Raider (removed concept)");
            class_names.Add("58 - Livestock");
            class_names.Add("59 - King");
            class_names.Add("60 - Misc Building (unused)");
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
        if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
        {
            effect_attribute_names.Add("24 - Hidden Damage Resistance (types 50-80)");
            effect_attribute_names.Add("25 - Icon");
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
            effect_attribute_names.Add("54 - Unused");
            effect_attribute_names.Add("55 - Unused");
            effect_attribute_names.Add("56 - Unused");
            effect_attribute_names.Add("57 - Dead Unit");
            effect_attribute_names.Add("58 - Hotkey");
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
        if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
        {
            // Attributes 0 to 25, 40 to 58 and 100 to 109 only.
            SetEffectAttributeChoice = [](LinkedComboBox *linkedComboBox, short value)
            {
                if (value >= 0 && value <= 25)
                {
                    linkedComboBox->SetChoice(value);
                }
                else if (value >= 40 && value <= 58)
                {
                    linkedComboBox->SetChoice(value - 14);
                }
                else if (value >= 100 && value <= 109)
                {
                    linkedComboBox->SetChoice(value - 55);
                }
                else
                {
                    linkedComboBox->SetChoice(-1);
                }
            };
            OnChooseEffectAttribute = [](AGETextCtrl *linkedTextBox, unsigned selection)
            {
                if (selection < 26)
                {
                    linkedTextBox->SetAsText(selection);
                }
                else if (selection < 45)
                {
                    linkedTextBox->SetAsText(selection + 14);
                }
                else if (selection < 55)
                {
                    linkedTextBox->SetAsText(selection + 55);
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
    if (GameVersion == EV_UP)
    {
        modify_research_names.Add("-1 - Set Time");
        modify_research_names.Add("-2 - Add Time");
        modify_research_names.Add("0 - Set Food Cost");
        modify_research_names.Add("1 - Set Wood Cost");
        modify_research_names.Add("2 - Set Stone Cost");
        modify_research_names.Add("3 - Set Gold Cost");
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
    if (GenieVersion >= genie::GV_AoKA || GenieVersion < genie::GV_Tapsa && GenieVersion > genie::GV_LatestTap)
    {
        effect_type_names.Add("6 - Resource Modifier (Multiply)");
    }
    if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
    {
        effect_type_names.Add("7 - Spawn Unit");
    }
    if (GameVersion == EV_UP)
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
    if (GameVersion == EV_UP)
    {
        effect_type_names.Add("17 - Team Enable/Disable/Force Multiuse Tech");
        effect_type_names.Add("18 - Team Modify Tech");
        effect_type_names.Add("19 - Team Set Player Civ Name");
        effect_type_names.Add("20 - Enemy Attribute Modifier (Set)");
        effect_type_names.Add("21 - Enemy Resource Modifier (Set/+/-)");
        effect_type_names.Add("22 - Enemy Enable/Disable Unit");
        effect_type_names.Add("23 - Enemy Upgrade Unit");
        effect_type_names.Add("24 - Enemy Attribute Modifier (+/-)");
        effect_type_names.Add("25 - Enemy Attribute Modifier (Multiply)");
        effect_type_names.Add("26 - Enemy Resource Modifier (Multiply)");
        effect_type_names.Add("27 - Enemy Enable/Disable/Force Multiuse Tech");
        effect_type_names.Add("28 - Enemy Modify Tech");
        effect_type_names.Add("29 - Enemy Set Player Civ Name");
        effect_type_names.Add("30 - Neutral Attribute Modifier (Set)");
        effect_type_names.Add("31 - Neutral Resource Modifier (Set/+/-)");
        effect_type_names.Add("32 - Neutral Enable/Disable Unit");
        effect_type_names.Add("33 - Neutral Upgrade Unit");
        effect_type_names.Add("34 - Neutral Attribute Modifier (+/-)");
        effect_type_names.Add("35 - Neutral Attribute Modifier (Multiply)");
        effect_type_names.Add("36 - Neutral Resource Modifier (Multiply)");
        effect_type_names.Add("37 - Neutral Enable/Disable/Force Multiuse Tech");
        effect_type_names.Add("38 - Neutral Modify Tech");
        effect_type_names.Add("39 - Neutral Set Player Civ Name");
    }
    if (GenieVersion >= genie::GV_AoKA || GenieVersion < genie::GV_Tapsa && GenieVersion > genie::GV_LatestTap)
    {
        effect_type_names.Add("101 - Tech Cost Modifier (Set/+/-)");
    }
    effect_type_names.Add("102 - Disable Tech");
    if (GenieVersion >= genie::GV_AoKA || GenieVersion < genie::GV_Tapsa && GenieVersion > genie::GV_LatestTap)
    {
        effect_type_names.Add("103 - Tech Time Modifier (Set/+/-)");
    }
    Effects_Type_ComboBox->Flash();

    // Special selection logic that takes into account gaps in the list above.
    if (GenieVersion >= genie::GV_AoKA || GenieVersion < genie::GV_Tapsa && GenieVersion > genie::GV_LatestTap)
    {
        if (GenieVersion >= genie::GV_Cysion && GenieVersion <= genie::GV_LatestDE2)
        {
            if (GenieVersion >= genie::GV_C2)
            {
                // Types 0 to 7, 10 to 16 and 101 to 103 only.
                SetEffectTypeChoice = [](LinkedComboBox *linkedComboBox, short value)
                {
                    if (value >= 0 && value <= 7)
                    {
                        linkedComboBox->SetChoice(value);
                    }
                    else if (value >= 10 && value <= 16)
                    {
                        linkedComboBox->SetChoice(value - 2);
                    }
                    else if (value >= 101 && value <= 103)
                    {
                        linkedComboBox->SetChoice(value - 86);
                    }
                    else
                    {
                        linkedComboBox->SetChoice(-1);
                    }
                };
                OnChooseEffectType = [](AGETextCtrl *linkedTextBox, unsigned selection)
                {
                    if (selection < 8)
                    {
                        linkedTextBox->SetAsText(selection);
                    }
                    else if (selection < 15)
                    {
                        linkedTextBox->SetAsText(selection + 2);
                    }
                    else if (selection < 18)
                    {
                        linkedTextBox->SetAsText(selection + 86);
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

    wxArrayString DefAoE1Armors, DefAoE2Armors, DefSWGBArmors,
        DefAoE1TerrainRests, DefAoE2TerrainRests, DefSWGBTerrainRests,
        DefRoRCivRes, DefAoKCivRes, DefSWGBCivRes;

    // AoE & RoR
    DefAoE1Armors.Add("0 - Stone Defense & Fire Galley");
    DefAoE1Armors.Add("1 - Stone Defense & Archers");
    DefAoE1Armors.Add("2 - Unused");
    DefAoE1Armors.Add("3 - Base Pierce");
    DefAoE1Armors.Add("4 - Base Melee");
    DefAoE1Armors.Add("5 - Unused");
    DefAoE1Armors.Add("6 - Buildings");
    DefAoE1Armors.Add("7 - Priests");
    DefAoE1Armors.Add("8 - Cavalry");
    DefAoE1Armors.Add("9 - Infantry");
    DefAoE1Armors.Add("10 - Stone Defense");
    DefAoE1Armors.Add("11 - Unused");
    DefAoE1Armors.Add("12 - Villagers & Gazelles & Medusa");
    DefAoE1TerrainRests.Add("Land + water");
    DefAoE1TerrainRests.Add("Land");
    DefAoE1TerrainRests.Add("Beach");
    DefAoE1TerrainRests.Add("Water");
    DefAoE1TerrainRests.Add("Land");
    DefAoE1TerrainRests.Add("Nothing");
    DefAoE1TerrainRests.Add("Water + beach");
    DefAoE1TerrainRests.Add("Land + shallows");
    DefAoE1TerrainRests.Add("Plain");
    DefAoE1TerrainRests.Add("Land - dirt");
    DefAoE1TerrainRests.Add("Land + beach");
    DefRoRCivRes.Add("Food Storage");
    DefRoRCivRes.Add("Wood Storage");
    DefRoRCivRes.Add("Stone Storage");
    DefRoRCivRes.Add("Gold Storage");
    DefRoRCivRes.Add("Population Headroom");// MAX_POP
    DefRoRCivRes.Add("Conversion Range");
    DefRoRCivRes.Add("Current Age");
    DefRoRCivRes.Add("Artifacts Captured");
    DefRoRCivRes.Add("Unused (Trade Bonus)");
    DefRoRCivRes.Add("Trade Goods");
    DefRoRCivRes.Add("Trade Production");
    DefRoRCivRes.Add("Current Population");// POPULATION
    DefRoRCivRes.Add("Corpse Decay Time");
    DefRoRCivRes.Add("Remarkable Discovery");
    DefRoRCivRes.Add("Ruins Captured");
    DefRoRCivRes.Add("Meat Storage");
    DefRoRCivRes.Add("Berry Storage");
    DefRoRCivRes.Add("Fish Storage");
    DefRoRCivRes.Add("Unused (Trade Tax)");
    DefRoRCivRes.Add("Total Units Owned");// TOTAL_UNITS / TOTAL_POP
    DefRoRCivRes.Add("Units Killed");
    DefRoRCivRes.Add("Technology Count");
    DefRoRCivRes.Add("% Map Explored");
    DefRoRCivRes.Add("Bronze Age Tech ID");
    DefRoRCivRes.Add("Iron Age Tech ID");
    DefRoRCivRes.Add("Tool Age Tech ID");
    DefRoRCivRes.Add("Attack Warning Sound ID");
    DefRoRCivRes.Add("Enable Priest Conversion");
    DefRoRCivRes.Add("Enable Building Conversion");
    DefRoRCivRes.Add("Bribery (Gold Replace)");// Allows paying missing cost with gold.
    DefRoRCivRes.Add("Unused (Building Limit)");
    DefRoRCivRes.Add("Unused (Food Limit)");
    DefRoRCivRes.Add("Unit Limit");
    DefRoRCivRes.Add("Food Maintenance");
    DefRoRCivRes.Add("Faith");
    DefRoRCivRes.Add("Faith Recharging Rate");
    DefRoRCivRes.Add("Farm Food Amount");
    DefRoRCivRes.Add("Civilian Population");
    DefRoRCivRes.Add("Unused");
    DefRoRCivRes.Add("All Techs Achieved");
    DefRoRCivRes.Add("Military Population");
    DefRoRCivRes.Add("Conversions");
    DefRoRCivRes.Add("Standing Wonders");
    DefRoRCivRes.Add("Razings");
    DefRoRCivRes.Add("Kill Ratio");
    DefRoRCivRes.Add("Survival to Finish");
    DefRoRCivRes.Add("Tribute Inefficiency");
    DefRoRCivRes.Add("Gold Mining Productivity");
    DefRoRCivRes.Add("Town Center Unavailable");
    DefRoRCivRes.Add("Gold Counter");
    DefRoRCivRes.Add("Reveal Ally");
    DefRoRCivRes.Add("Unused (Houses)");
    DefRoRCivRes.Add("Temples");
    DefRoRCivRes.Add("Tribute Sent");
    DefRoRCivRes.Add("All Ruins Captured");
    DefRoRCivRes.Add("All Artifacts Captured");
    DefRoRCivRes.Add("RoR: Heal Bonus");
    DefRoRCivRes.Add("RoR: Martyrdom");

    // AoK & TC
    DefAoE2Armors.Add("0 - Unused");
    DefAoE2Armors.Add("1 - Infantry");  // Selection 2
    DefAoE2Armors.Add("2 - Turtle Ships");
    DefAoE2Armors.Add("3 - Base Pierce");
    DefAoE2Armors.Add("4 - Base Melee");
    DefAoE2Armors.Add("5 - Elephants");
    DefAoE2Armors.Add("6 - Unused");
    DefAoE2Armors.Add("7 - Unused");
    DefAoE2Armors.Add("8 - Mounted Units except Camels");
    DefAoE2Armors.Add("9 - Unused");
    DefAoE2Armors.Add("10 - Unused");
    DefAoE2Armors.Add("11 - All Buildings");
    DefAoE2Armors.Add("12 - Unused");
    DefAoE2Armors.Add("13 - Stone Defense except Castles");
    DefAoE2Armors.Add("14 - Predator Wild Animals");
    DefAoE2Armors.Add("15 - All Archers (and Mamelukes)");
    DefAoE2Armors.Add("16 - Ships except Fishing Ships");
    DefAoE2Armors.Add("17 - Rams, Unpacked Trebuchet & Siege Towers");
    DefAoE2Armors.Add("18 - Trees");
    DefAoE2Armors.Add("19 - Unique Units (except Imperial camel and Imperial skirmisher)");
    DefAoE2Armors.Add("20 - Siege Weapons");
    DefAoE2Armors.Add("21 - Standard Buildings (ignore building armor)");
    DefAoE2Armors.Add("22 - Walls & Gates");
    DefAoE2Armors.Add("23 - Gunpowder Units");
    DefAoE2Armors.Add("24 - Huntable Wild Animals");
    DefAoE2Armors.Add("25 - Monks");
    DefAoE2Armors.Add("26 - Castles");
    DefAoE2Armors.Add("27 - Spearmen");
    DefAoE2Armors.Add("28 - Mounted Archers");
    DefAoE2Armors.Add("29 - Eagle Warriors");
    DefAoE2Armors.Add("30 - Camels");
    DefAoE2Armors.Add("31 - Standard Melee (ignore melee armor)");
    DefAoE2Armors.Add("32 - Condottieri");
    DefAoE2Armors.Add("33 - Unused");
    DefAoE2Armors.Add("34 - Fishing Ships");
    DefAoE2Armors.Add("35 - Mamelukes");
    DefAoE2Armors.Add("36 - Heroes (unused concept)");
    DefAoE2Armors.Add("37 - Hussite Wagons");
    DefAoE2TerrainRests.Add("All");
    DefAoE2TerrainRests.Add("Land + shallows");
    DefAoE2TerrainRests.Add("Beach");
    DefAoE2TerrainRests.Add("Water");
    DefAoE2TerrainRests.Add("Land");
    DefAoE2TerrainRests.Add("Nothing");
    DefAoE2TerrainRests.Add("Water");
    DefAoE2TerrainRests.Add("All - water");
    DefAoE2TerrainRests.Add("Land - farm");
    DefAoE2TerrainRests.Add("Nothing");
    DefAoE2TerrainRests.Add("Land + beach");
    DefAoE2TerrainRests.Add("Land - farm");
    DefAoE2TerrainRests.Add("All - water bridge");
    DefAoE2TerrainRests.Add("Water");
    DefAoE2TerrainRests.Add("All - water bridge");
    DefAoE2TerrainRests.Add("Water");
    DefAoE2TerrainRests.Add("Grass + beach");
    DefAoE2TerrainRests.Add("Water (+bridge) - beach");
    DefAoE2TerrainRests.Add("All - water bridge");
    DefAoE2TerrainRests.Add("Only water + ice");
    DefAoE2TerrainRests.Add("All - water");
    DefAoE2TerrainRests.Add("Shallow water");
    DefAoKCivRes.Add("Food Storage");
    DefAoKCivRes.Add("Wood Storage");
    DefAoKCivRes.Add("Stone Storage");
    DefAoKCivRes.Add("Gold Storage");
    DefAoKCivRes.Add("Population Headroom");
    DefAoKCivRes.Add("Conversion Range");
    DefAoKCivRes.Add("Current Age");
    DefAoKCivRes.Add("Relics Captured");
    DefAoKCivRes.Add("Unused");
    DefAoKCivRes.Add("Unused");
    DefAoKCivRes.Add("Unused");
    DefAoKCivRes.Add("Current Population");
    DefAoKCivRes.Add("Corpse Decay Time");
    DefAoKCivRes.Add("Unused");
    DefAoKCivRes.Add("Monuments Captured");
    DefAoKCivRes.Add("Meat Storage");
    DefAoKCivRes.Add("Berry Storage");
    DefAoKCivRes.Add("Fish Storage");
    DefAoKCivRes.Add("Unused");
    DefAoKCivRes.Add("Total Units Owned");
    DefAoKCivRes.Add("Units Killed");
    DefAoKCivRes.Add("Technology Count");
    DefAoKCivRes.Add("% Map Explored");
    DefAoKCivRes.Add("Castle Age Tech ID");
    DefAoKCivRes.Add("Imperial Age Tech ID");
    DefAoKCivRes.Add("Feudal Age Tech ID");
    DefAoKCivRes.Add("Attack Warning Sound ID");
    DefAoKCivRes.Add("Enable Monk Conversion");
    DefAoKCivRes.Add("Enable Building Conversion");
    DefAoKCivRes.Add("Unused");
    DefAoKCivRes.Add("Unused");
    DefAoKCivRes.Add("Unused");
    DefAoKCivRes.Add("Bonus Population Cap");
    DefAoKCivRes.Add("Food Maintenance");
    DefAoKCivRes.Add("Faith");
    DefAoKCivRes.Add("Faith Recharging Rate");
    DefAoKCivRes.Add("Farm Food Amount");
    DefAoKCivRes.Add("Civilian Population");
    DefAoKCivRes.Add("Unused");
    DefAoKCivRes.Add("All Techs Achieved");
    DefAoKCivRes.Add("Military Population");
    DefAoKCivRes.Add("Conversions");
    DefAoKCivRes.Add("Standing Wonders");
    DefAoKCivRes.Add("Razings");
    DefAoKCivRes.Add("Kill Ratio");
    DefAoKCivRes.Add("Survival to Finish");
    DefAoKCivRes.Add("Tribute Inefficiency");
    DefAoKCivRes.Add("Gold Mining Productivity");
    DefAoKCivRes.Add("Town Center Unavailable");
    DefAoKCivRes.Add("Gold Counter");
    DefAoKCivRes.Add("Reveal Ally");
    DefAoKCivRes.Add("Unused");
    DefAoKCivRes.Add("Unused");
    DefAoKCivRes.Add("Tribute Sent");
    DefAoKCivRes.Add("All Monuments Captured");
    DefAoKCivRes.Add("All Relics Captured");
    DefAoKCivRes.Add("Ore Storage (unused)");
    DefAoKCivRes.Add("Unused");
    DefAoKCivRes.Add("Dark Age Tech ID");
    DefAoKCivRes.Add("Unused");
    DefAoKCivRes.Add("Unused");
    DefAoKCivRes.Add("Unused (Formations)");
    DefAoKCivRes.Add("Building Housing Rate");
    DefAoKCivRes.Add("Tax Gather Rate");
    DefAoKCivRes.Add("Gather Accumulator");
    DefAoKCivRes.Add("Salvage Decay Rate");
    DefAoKCivRes.Add("Unused (Allow Formations)");
    DefAoKCivRes.Add("Can Convert");
    DefAoKCivRes.Add("Hit Points Killed");
    DefAoKCivRes.Add("Killed P1");
    DefAoKCivRes.Add("Killed P2");
    DefAoKCivRes.Add("Killed P3");
    DefAoKCivRes.Add("Killed P4");
    DefAoKCivRes.Add("Killed P5");
    DefAoKCivRes.Add("Killed P6");
    DefAoKCivRes.Add("Killed P7");
    DefAoKCivRes.Add("Killed P8");
    DefAoKCivRes.Add("Conversion Resistance");
    DefAoKCivRes.Add("Trade Vig Rate");
    DefAoKCivRes.Add("Stone Mining Productivity");
    DefAoKCivRes.Add("Queued Units");
    DefAoKCivRes.Add("Training Count");
    DefAoKCivRes.Add("Start with Packed Town Center (unit 444)");
    DefAoKCivRes.Add("Boarding Recharge Rate (unused concept)");
    DefAoKCivRes.Add("Starting Villagers");
    DefAoKCivRes.Add("Research Cost Modifier");
    DefAoKCivRes.Add("Research Time Modifier");
    DefAoKCivRes.Add("Convert Boats (unused concept)");
    DefAoKCivRes.Add("Fish Trap Food Amount");
    DefAoKCivRes.Add("Heal Rate Modifier");
    DefAoKCivRes.Add("Healing Range"); // 90 alpha ends here
    DefAoKCivRes.Add("Starting Food");
    DefAoKCivRes.Add("Starting Wood");
    DefAoKCivRes.Add("Starting Stone");
    DefAoKCivRes.Add("Starting Gold");
    DefAoKCivRes.Add("Enable PTWC / Kidnap / Loot");
    DefAoKCivRes.Add("Unused");
    DefAoKCivRes.Add("Dominant Sheep Control");
    DefAoKCivRes.Add("Building Cost Sum");
    DefAoKCivRes.Add("Tech Cost Sum");
    DefAoKCivRes.Add("Relic Income Sum");
    DefAoKCivRes.Add("Trade Income Sum");
    DefAoKCivRes.Add("P1 Tribute");
    DefAoKCivRes.Add("P2 Tribute");
    DefAoKCivRes.Add("P3 Tribute");
    DefAoKCivRes.Add("P4 Tribute");
    DefAoKCivRes.Add("P5 Tribute");
    DefAoKCivRes.Add("P6 Tribute");
    DefAoKCivRes.Add("P7 Tribute");
    DefAoKCivRes.Add("P8 Tribute");
    DefAoKCivRes.Add("P1 Kill Value");
    DefAoKCivRes.Add("P2 Kill Value");
    DefAoKCivRes.Add("P3 Kill Value");
    DefAoKCivRes.Add("P4 Kill Value");
    DefAoKCivRes.Add("P5 Kill Value");
    DefAoKCivRes.Add("P6 Kill Value");
    DefAoKCivRes.Add("P7 Kill Value");
    DefAoKCivRes.Add("P8 Kill Value");
    DefAoKCivRes.Add("P1 Razings");
    DefAoKCivRes.Add("P2 Razings");
    DefAoKCivRes.Add("P3 Razings");
    DefAoKCivRes.Add("P4 Razings");
    DefAoKCivRes.Add("P5 Razings");
    DefAoKCivRes.Add("P6 Razings");
    DefAoKCivRes.Add("P7 Razings");
    DefAoKCivRes.Add("P8 Razings");
    DefAoKCivRes.Add("P1 Razing Value");
    DefAoKCivRes.Add("P2 Razing Value");
    DefAoKCivRes.Add("P3 Razing Value");
    DefAoKCivRes.Add("P4 Razing Value");
    DefAoKCivRes.Add("P5 Razing Value");
    DefAoKCivRes.Add("P6 Razing Value");
    DefAoKCivRes.Add("P7 Razing Value");
    DefAoKCivRes.Add("P8 Razing Value");
    DefAoKCivRes.Add("Standing Castles");
    DefAoKCivRes.Add("Hit Points Razed");
    DefAoKCivRes.Add("Kills by P1");
    DefAoKCivRes.Add("Kills by P2");
    DefAoKCivRes.Add("Kills by P3");
    DefAoKCivRes.Add("Kills by P4");
    DefAoKCivRes.Add("Kills by P5");
    DefAoKCivRes.Add("Kills by P6");
    DefAoKCivRes.Add("Kills by P7");
    DefAoKCivRes.Add("Kills by P8");
    DefAoKCivRes.Add("Razings by P1");
    DefAoKCivRes.Add("Razings by P2");
    DefAoKCivRes.Add("Razings by P3");
    DefAoKCivRes.Add("Razings by P4");
    DefAoKCivRes.Add("Razings by P5");
    DefAoKCivRes.Add("Razings by P6");
    DefAoKCivRes.Add("Razings by P7");
    DefAoKCivRes.Add("Razings by P8");
    DefAoKCivRes.Add("Value Killed by Others");
    DefAoKCivRes.Add("Value Razed by Others");
    DefAoKCivRes.Add("Killed by Others");
    DefAoKCivRes.Add("Razed by Others");
    DefAoKCivRes.Add("Tribute from P1");
    DefAoKCivRes.Add("Tribute from P2");
    DefAoKCivRes.Add("Tribute from P3");
    DefAoKCivRes.Add("Tribute from P4");
    DefAoKCivRes.Add("Tribute from P5");
    DefAoKCivRes.Add("Tribute from P6");
    DefAoKCivRes.Add("Tribute from P7");
    DefAoKCivRes.Add("Tribute from P8");
    DefAoKCivRes.Add("Value Current Units");
    DefAoKCivRes.Add("Value Current Buildings");
    DefAoKCivRes.Add("Food Total");
    DefAoKCivRes.Add("Wood Total");
    DefAoKCivRes.Add("Stone Total");
    DefAoKCivRes.Add("Gold Total");
    DefAoKCivRes.Add("Total Value of Kills");
    DefAoKCivRes.Add("Total Tribute Received");
    DefAoKCivRes.Add("Total Value of Razings");
    DefAoKCivRes.Add("Total Castles Built");
    DefAoKCivRes.Add("Total Wonders Built");
    DefAoKCivRes.Add("Tribute Score");
    DefAoKCivRes.Add("Convert Min Adjustment");
    DefAoKCivRes.Add("Convert Max Adjustment");
    DefAoKCivRes.Add("Convert Resist Min Adjustment");
    DefAoKCivRes.Add("Convert Resist Max Adjustment");
    DefAoKCivRes.Add("Convert Building Min");
    DefAoKCivRes.Add("Convert Building Max");
    DefAoKCivRes.Add("Convert Building Chance");
    DefAoKCivRes.Add("Reveal Enemy");
    DefAoKCivRes.Add("Value Wonders Castles"); // 184 beta ends here
    DefAoKCivRes.Add("Food Score");
    DefAoKCivRes.Add("Wood Score");
    DefAoKCivRes.Add("Stone Score");
    DefAoKCivRes.Add("Gold Score");
    DefAoKCivRes.Add("Lumber Productivity");
    DefAoKCivRes.Add("Food-gathering (except Shepherds) Productivity");
    DefAoKCivRes.Add("Relic Gold Production per minute");
    DefAoKCivRes.Add("Converted Units Die (Heresy)");
    DefAoKCivRes.Add("Theocracy");
    DefAoKCivRes.Add("Crenellations");
    DefAoKCivRes.Add("Construction Rate Modifier");
    DefAoKCivRes.Add("Wonders Countdown Extra Time");
    DefAoKCivRes.Add("Spies Discount"); // 197 The Conquerors ends here
    DefAoKCivRes.Add("Unused");
    DefAoKCivRes.Add("Unused");
    DefAoKCivRes.Add("Unused");
    DefAoKCivRes.Add("Unused");
    DefAoKCivRes.Add("Unused");
    DefAoKCivRes.Add("Unused");
    DefAoKCivRes.Add("Unused");
    DefAoKCivRes.Add("Feitoria Food Productivity");
    DefAoKCivRes.Add("Feitoria Wood Productivity");
    DefAoKCivRes.Add("Feitoria Stone Productivity");
    DefAoKCivRes.Add("Feitoria Gold Productivity");
    DefAoKCivRes.Add("Reveal Enemy Starting Town Centers");
    DefAoKCivRes.Add("Reveal Relics Starting Position");
    DefAoKCivRes.Add("Higher Elevation Bonus");
    DefAoKCivRes.Add("Lower Elevation Bonus");
    DefAoKCivRes.Add("Raiding Productivity");
    DefAoKCivRes.Add("Mercenary Kipchak Count");
    DefAoKCivRes.Add("Unused");
    DefAoKCivRes.Add("Shepherd Productivity");
    DefAoKCivRes.Add("Unused");
    DefAoKCivRes.Add("Dark and Feudal Age Town Center Limit");
    DefAoKCivRes.Add("Unused");
    DefAoKCivRes.Add("Unused");
    DefAoKCivRes.Add("Monument Food Productivity");
    DefAoKCivRes.Add("Monument Wood Productivity");
    DefAoKCivRes.Add("Monument Stone Productivity");
    DefAoKCivRes.Add("Monument Gold Productivity");
    DefAoKCivRes.Add("Relic Food Production per minute");
    DefAoKCivRes.Add("Villagers killed by Gaia");
    DefAoKCivRes.Add("Villagers killed by Animals");
    DefAoKCivRes.Add("Villagers killed by AI");
    DefAoKCivRes.Add("Villagers killed by Humans");
    DefAoKCivRes.Add("Food Generation Rate");
    DefAoKCivRes.Add("Wood Generation Rate");
    DefAoKCivRes.Add("Stone Generation Rate");
    DefAoKCivRes.Add("Gold Generation Rate");
    DefAoKCivRes.Add("Spawn Limit (number of buildings allowed to spawn)");
    DefAoKCivRes.Add("Flemish Militia Population");
    DefAoKCivRes.Add("Farmer Gold Generation Productivity");
    DefAoKCivRes.Add("Folwark Collection Amount");
    DefAoKCivRes.Add("Folwark Attribute Type");
    DefAoKCivRes.Add("Folwark Building Type (links Folwark to Mill)");
    DefAoKCivRes.Add("Units Converted");
    DefAoKCivRes.Add("Stone Miner Gold Generation Productivity");
    DefAoKCivRes.Add("Free Transport Ships");
    
    // SWGB & CC
    DefSWGBArmors.Add("0 - Aircraft");  // Selection 1
    // Airspeeder
    // AIR SHIPS!!!
    // Geonosian Warrior
    // Wild Gungan Flyer
    DefSWGBArmors.Add("1 - Heavy Assault Machines");    // Selection 2
    // Assault Mech
    // AT-AT
    // Blizzards
    DefSWGBArmors.Add("2 - Heavy Weapons");
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
    DefSWGBArmors.Add("3 - Base Ranged/DuraArmor");
    DefSWGBArmors.Add("4 - Base Melee/Armor");
    DefSWGBArmors.Add("5 - Jedis & Bounty Hunters");
    // Jedi
    // Jedi with Holocron
    // Bounty Hunter
    DefSWGBArmors.Add("6 - Assault Machines");
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
    DefSWGBArmors.Add("7 - Decimators");
    // Assault Mechs
    // Decimator
    // AT-AT
    // Blizzards
    DefSWGBArmors.Add("8 - Shield & Power Units");
    // Power Cores
    // Shield Wall
    // Shield Generators
    // Droid Storage Facility
    // Power Droids
    // Echo Base Power Generator
    DefSWGBArmors.Add("9 - Ships");
    // Utility Trawler
    // Frigates
    // Cruisers
    // Destroyers
    // A-A Destroyers
    // Transport Ships
    DefSWGBArmors.Add("10 - Submarines");
    // Frigates
    // Underwater Prefab Shelters
    // Gungan Buildings
    DefSWGBArmors.Add("11 - All Buildings");
    // BUILDINGS!!!
    DefSWGBArmors.Add("12 - Unused");
    DefSWGBArmors.Add("13 - Defense Buildings");
    // Gate
    // Turrets
    // A-A Turrets
    // Echo Base Ion Cannon
    // Fortress
    // Theed Arch
    DefSWGBArmors.Add("14 - Troopers");
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
    DefSWGBArmors.Add("15 - Mounted Troopers");
    // Berserker
    // Scouts
    // Mounted Troopers
    // Anakin's Podracer
    // Landspeeder
    // Sebulba's Podracer
    // Skyhopper
    DefSWGBArmors.Add("16 - Cruisers");
    // Cruisers
    DefSWGBArmors.Add("17 - Pummels & Cannons");
    // Undeployed Cannon
    // Pummels
    // Cannon
    DefSWGBArmors.Add("18 - Unused");
    DefSWGBArmors.Add("19 - Workers");
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
    DefSWGBArmors.Add("20 - Destroyers");
    // Destroyers
    DefSWGBArmors.Add("21 - Standard Buildings");
    // BUILDINGS!!!
    DefSWGBArmors.Add("22 - Walls & Gates");
    // GATES
    // WALLS
    // Theed Arch
    DefSWGBArmors.Add("23 - Air Cruisers");
    // Air Cruisers
    // Blockade Runner
    // Star Destroyer
    // Deathstar
    DefSWGBArmors.Add("24 - Wild Animals");
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
    DefSWGBArmors.Add("25 - Unused");
    DefSWGBArmors.Add("26 - Fortress");
    // Fortress
    DefSWGBArmors.Add("27 - Unused");
    DefSWGBArmors.Add("28 - Unused");
    DefSWGBArmors.Add("29 - Unused");
    DefSWGBArmors.Add("30 - Tame Animals"); // Selection 31
    // Fambaa Shield Generators
    // Wild Fambaa
    // Kaadu
    // Tauntaun
    // Cu-pa
    // Womp Rat
    DefSWGBTerrainRests.Add("All");
    DefSWGBTerrainRests.Add("Land + unbuildable");
    DefSWGBTerrainRests.Add("Shore");
    DefSWGBTerrainRests.Add("Water");
    DefSWGBTerrainRests.Add("Land");
    DefSWGBTerrainRests.Add("Land + shore, impassable water");
    DefSWGBTerrainRests.Add("Water + ice2 - swamp");
    DefSWGBTerrainRests.Add("Land - water, lava");
    DefSWGBTerrainRests.Add("Land - water, lava, farm");
    DefSWGBTerrainRests.Add("Only water");
    DefSWGBTerrainRests.Add("Land - shore");
    DefSWGBTerrainRests.Add("Land - water, lava, farm");
    DefSWGBTerrainRests.Add("All - lava");
    DefSWGBTerrainRests.Add("Water");
    DefSWGBTerrainRests.Add("All - lava");
    DefSWGBTerrainRests.Add("Land + shore, impassable water");
    DefSWGBTerrainRests.Add("Grass + shore");
    DefSWGBTerrainRests.Add("Water - shore + impassable water");
    DefSWGBTerrainRests.Add("All - impassable water, lava");
    DefSWGBTerrainRests.Add("Land + shore, impassable water");
    DefSWGBTerrainRests.Add("Land + shore, impassable water");
    DefSWGBTerrainRests.Add("Water - deep water");
    DefSWGBTerrainRests.Add("All - impassable water, lava");
    DefSWGBTerrainRests.Add("No restriction");
    DefSWGBTerrainRests.Add("Only water");
    DefSWGBTerrainRests.Add("Land + shore, impassable water");
    DefSWGBTerrainRests.Add("Land + shore, impassable water");
    DefSWGBTerrainRests.Add("Deep water");
    DefSWGBTerrainRests.Add("Wasteland");
    DefSWGBTerrainRests.Add("Ice");
    DefSWGBTerrainRests.Add("Lava");
    DefSWGBTerrainRests.Add("Water2");
    DefSWGBTerrainRests.Add("Rock4");
    DefSWGBCivRes.Add("Food Storage");
    DefSWGBCivRes.Add("Carbon Storage");
    DefSWGBCivRes.Add("Ore Storage");
    DefSWGBCivRes.Add("Nova Storage");
    DefSWGBCivRes.Add("Population Headroom");
    DefSWGBCivRes.Add("Conversion Range");
    DefSWGBCivRes.Add("Current Tech Level");
    DefSWGBCivRes.Add("Holocrons Captured");
    DefSWGBCivRes.Add("Unused (Trade Bonus)");
    DefSWGBCivRes.Add("Trade Goods");
    DefSWGBCivRes.Add("Recharge Rate of Shields");
    DefSWGBCivRes.Add("Current Population");
    DefSWGBCivRes.Add("Corpse Decay Time");
    DefSWGBCivRes.Add("Remarkable Discovery");
    DefSWGBCivRes.Add("Monuments Captured");
    DefSWGBCivRes.Add("Meat Storage");
    DefSWGBCivRes.Add("Berry Storage");
    DefSWGBCivRes.Add("Fish Storage");
    DefSWGBCivRes.Add("Power Core Range");
    DefSWGBCivRes.Add("Total Units Owned");
    DefSWGBCivRes.Add("Units Killed");
    DefSWGBCivRes.Add("Technology Count");
    DefSWGBCivRes.Add("% Map Explored");
    DefSWGBCivRes.Add("Submarine Detection");
    DefSWGBCivRes.Add("Shield Generator Range");
    DefSWGBCivRes.Add("Unknown");
    DefSWGBCivRes.Add("Drop-off Time of Shields");
    DefSWGBCivRes.Add("Enable Jedi Conversion");
    DefSWGBCivRes.Add("Enable Building Conversion");
    DefSWGBCivRes.Add("Unknown");
    DefSWGBCivRes.Add("Unused (Building Limit)");
    DefSWGBCivRes.Add("Enable A-A Attack for AT-AT");
    DefSWGBCivRes.Add("Bonus Population Cap");
    DefSWGBCivRes.Add("Power Core Shielding");
    DefSWGBCivRes.Add("Force");
    DefSWGBCivRes.Add("Force Recharging Rate");
    DefSWGBCivRes.Add("Farm Food Amount");
    DefSWGBCivRes.Add("Civilian Population");
    DefSWGBCivRes.Add("Shields On for Bombers/Fighters");
    DefSWGBCivRes.Add("All Techs Achieved");
    DefSWGBCivRes.Add("Military Population");
    DefSWGBCivRes.Add("Conversions");
    DefSWGBCivRes.Add("Standing Monuments");
    DefSWGBCivRes.Add("Razings");
    DefSWGBCivRes.Add("Kill Ratio");
    DefSWGBCivRes.Add("Survival to Finish");
    DefSWGBCivRes.Add("Tribute Inefficiency");
    DefSWGBCivRes.Add("Nova Mining Productivity");
    DefSWGBCivRes.Add("Town Center Unavailable");
    DefSWGBCivRes.Add("Gold Counter");
    DefSWGBCivRes.Add("Reveal Ally");
    DefSWGBCivRes.Add("Shielding");
    DefSWGBCivRes.Add("Monasteries");
    DefSWGBCivRes.Add("Tribute Sent");
    DefSWGBCivRes.Add("All Ruins Captured");
    DefSWGBCivRes.Add("All Relics Captured");
    DefSWGBCivRes.Add("Enable Stealth for Masters");
    DefSWGBCivRes.Add("Kidnap Storage");
    DefSWGBCivRes.Add("Masters Can See Hidden Units");
    DefSWGBCivRes.Add("Trade Good Quality");
    DefSWGBCivRes.Add("Trade Market Level");
    DefSWGBCivRes.Add("Unused (Formations)");
    DefSWGBCivRes.Add("Building Housing Rate");
    DefSWGBCivRes.Add("Tax Gather Rate");
    DefSWGBCivRes.Add("Gather Accumulator");
    DefSWGBCivRes.Add("Salvage Decay Rate");
    DefSWGBCivRes.Add("Unused (Allow Formations)");
    DefSWGBCivRes.Add("Can Convert");
    DefSWGBCivRes.Add("Hit Points Killed");
    DefSWGBCivRes.Add("Killed P1");
    DefSWGBCivRes.Add("Killed P2");
    DefSWGBCivRes.Add("Killed P3");
    DefSWGBCivRes.Add("Killed P4");
    DefSWGBCivRes.Add("Killed P5");
    DefSWGBCivRes.Add("Killed P6");
    DefSWGBCivRes.Add("Killed P7");
    DefSWGBCivRes.Add("Killed P8");
    DefSWGBCivRes.Add("Conversion Resistance");
    DefSWGBCivRes.Add("Trade Vig Rate");
    DefSWGBCivRes.Add("Ore Mining Productivity");
    DefSWGBCivRes.Add("Queued Units");
    DefSWGBCivRes.Add("Training Count");
    DefSWGBCivRes.Add("Start with Packed Town Center");
    DefSWGBCivRes.Add("Boarding Recharge Rate");
    DefSWGBCivRes.Add("Starting Villagers");
    DefSWGBCivRes.Add("Tech Cost Modifier");
    DefSWGBCivRes.Add("Tech Time Modifier");
    DefSWGBCivRes.Add("Concentration");
    DefSWGBCivRes.Add("Fish Trap Food Amount");
    DefSWGBCivRes.Add("Medic Healing Rate");
    DefSWGBCivRes.Add("Healing Range");
    DefSWGBCivRes.Add("Starting Food");
    DefSWGBCivRes.Add("Starting Carbon");
    DefSWGBCivRes.Add("Starting Ore");
    DefSWGBCivRes.Add("Starting Nova");
    DefSWGBCivRes.Add("Enable PTWC / Kidnap / Loot");
    DefSWGBCivRes.Add("Berserker Heal Timer");
    DefSWGBCivRes.Add("Dominant Sheep Control");
    DefSWGBCivRes.Add("Object Cost Sum");
    DefSWGBCivRes.Add("Tech Cost Sum");
    DefSWGBCivRes.Add("Holocron Nova Sum");
    DefSWGBCivRes.Add("Trade Income Sum");
    DefSWGBCivRes.Add("P1 Tribute");
    DefSWGBCivRes.Add("P2 Tribute");
    DefSWGBCivRes.Add("P3 Tribute");
    DefSWGBCivRes.Add("P4 Tribute");
    DefSWGBCivRes.Add("P5 Tribute");
    DefSWGBCivRes.Add("P6 Tribute");
    DefSWGBCivRes.Add("P7 Tribute");
    DefSWGBCivRes.Add("P8 Tribute");
    DefSWGBCivRes.Add("P1 Kill Value");
    DefSWGBCivRes.Add("P2 Kill Value");
    DefSWGBCivRes.Add("P3 Kill Value");
    DefSWGBCivRes.Add("P4 Kill Value");
    DefSWGBCivRes.Add("P5 Kill Value");
    DefSWGBCivRes.Add("P6 Kill Value");
    DefSWGBCivRes.Add("P7 Kill Value");
    DefSWGBCivRes.Add("P8 Kill Value");
    DefSWGBCivRes.Add("P1 Razings");
    DefSWGBCivRes.Add("P2 Razings");
    DefSWGBCivRes.Add("P3 Razings");
    DefSWGBCivRes.Add("P4 Razings");
    DefSWGBCivRes.Add("P5 Razings");
    DefSWGBCivRes.Add("P6 Razings");
    DefSWGBCivRes.Add("P7 Razings");
    DefSWGBCivRes.Add("P8 Razings");
    DefSWGBCivRes.Add("P1 Razing Value");
    DefSWGBCivRes.Add("P2 Razing Value");
    DefSWGBCivRes.Add("P3 Razing Value");
    DefSWGBCivRes.Add("P4 Razing Value");
    DefSWGBCivRes.Add("P5 Razing Value");
    DefSWGBCivRes.Add("P6 Razing Value");
    DefSWGBCivRes.Add("P7 Razing Value");
    DefSWGBCivRes.Add("P8 Razing Value");
    DefSWGBCivRes.Add("Standing Fortresses");
    DefSWGBCivRes.Add("Hit Points Razed");
    DefSWGBCivRes.Add("Kills by P1");
    DefSWGBCivRes.Add("Kills by P2");
    DefSWGBCivRes.Add("Kills by P3");
    DefSWGBCivRes.Add("Kills by P4");
    DefSWGBCivRes.Add("Kills by P5");
    DefSWGBCivRes.Add("Kills by P6");
    DefSWGBCivRes.Add("Kills by P7");
    DefSWGBCivRes.Add("Kills by P8");
    DefSWGBCivRes.Add("Razings by P1");
    DefSWGBCivRes.Add("Razings by P2");
    DefSWGBCivRes.Add("Razings by P3");
    DefSWGBCivRes.Add("Razings by P4");
    DefSWGBCivRes.Add("Razings by P5");
    DefSWGBCivRes.Add("Razings by P6");
    DefSWGBCivRes.Add("Razings by P7");
    DefSWGBCivRes.Add("Razings by P8");
    DefSWGBCivRes.Add("Value Killed by Others");
    DefSWGBCivRes.Add("Value Razed by Others");
    DefSWGBCivRes.Add("Killed by Others");
    DefSWGBCivRes.Add("Razed by Others");
    DefSWGBCivRes.Add("Tribute from P1");
    DefSWGBCivRes.Add("Tribute from P2");
    DefSWGBCivRes.Add("Tribute from P3");
    DefSWGBCivRes.Add("Tribute from P4");
    DefSWGBCivRes.Add("Tribute from P5");
    DefSWGBCivRes.Add("Tribute from P6");
    DefSWGBCivRes.Add("Tribute from P7");
    DefSWGBCivRes.Add("Tribute from P8");
    DefSWGBCivRes.Add("Value Current Units");
    DefSWGBCivRes.Add("Value Current Buildings");
    DefSWGBCivRes.Add("Food Total");
    DefSWGBCivRes.Add("Carbon Total");
    DefSWGBCivRes.Add("Ore Total");
    DefSWGBCivRes.Add("Nova Total");
    DefSWGBCivRes.Add("Total Value of Kills");
    DefSWGBCivRes.Add("Total Tribute Received");
    DefSWGBCivRes.Add("Total Value of Razings");
    DefSWGBCivRes.Add("Total Fortresses Built");
    DefSWGBCivRes.Add("Total Monuments Built");
    DefSWGBCivRes.Add("Tribute Score");
    DefSWGBCivRes.Add("Convert Min Adjustment");
    DefSWGBCivRes.Add("Convert Max Adjustment");
    DefSWGBCivRes.Add("Convert Resist Min Adjustment");
    DefSWGBCivRes.Add("Convert Resist Max Adjustment");
    DefSWGBCivRes.Add("Convert Building Min");
    DefSWGBCivRes.Add("Convert Building Max");
    DefSWGBCivRes.Add("Convert Building Chance");
    DefSWGBCivRes.Add("Reveal Enemy");
    DefSWGBCivRes.Add("Value Wonders Castles");
    DefSWGBCivRes.Add("Food Score");
    DefSWGBCivRes.Add("Carbon Score");
    DefSWGBCivRes.Add("Ore Score");
    DefSWGBCivRes.Add("Nova Score");
    DefSWGBCivRes.Add("Carbon Gathering Productivity");
    DefSWGBCivRes.Add("Food-gathering Productivity");
    DefSWGBCivRes.Add("Holocron Nova Production Rate");
    DefSWGBCivRes.Add("Converted Units Die");
    DefSWGBCivRes.Add("Meditation");
    DefSWGBCivRes.Add("Crenellations");
    DefSWGBCivRes.Add("Construction Rate Modifier");
    DefSWGBCivRes.Add("Biological Self Regeneration");
    DefSWGBCivRes.Add("Spies Discount");
    DefSWGBCivRes.Add("Unknown");
    DefSWGBCivRes.Add("Unknown");
    DefSWGBCivRes.Add("Misc Counter 1");
    DefSWGBCivRes.Add("Misc Counter 2");
    DefSWGBCivRes.Add("Misc Counter 3");
    DefSWGBCivRes.Add("Misc Counter 4");
    DefSWGBCivRes.Add("Misc Counter 5");
    DefSWGBCivRes.Add("Unknown");
    DefSWGBCivRes.Add("Unknown");
    DefSWGBCivRes.Add("Unknown");
    DefSWGBCivRes.Add("Unknown");
    DefSWGBCivRes.Add("Unknown");
    DefSWGBCivRes.Add("CC: Unknown");

    wxFileConfig Customs("", "", "AGE3NamesV0004.ini", "", wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
    long AoE1Count, AoE2Count, SWGBCount, AoE1CountTR, AoE2CountTR, SWGBCountTR, RoRCountCR, AoKCountCR, SWGBCountCR;
    if (!Customs.Read("Count/AoE1Count", &AoE1Count, DefAoE1Armors.GetCount()))
        Customs.Write("Count/AoE1Count", (int)DefAoE1Armors.GetCount());
    if (!Customs.Read("Count/AoE2Count", &AoE2Count, DefAoE2Armors.GetCount()))
        Customs.Write("Count/AoE2Count", (int)DefAoE2Armors.GetCount());
    if (!Customs.Read("Count/SWGBCount", &SWGBCount, DefSWGBArmors.GetCount()))
        Customs.Write("Count/SWGBCount", (int)DefSWGBArmors.GetCount());
    if (!Customs.Read("Count/AoE1TerrainRestrictionCount", &AoE1CountTR, DefAoE1TerrainRests.GetCount()))
        Customs.Write("Count/AoE1TerrainRestrictionCount", (int)DefAoE1TerrainRests.GetCount());
    if (!Customs.Read("Count/AoE2TerrainRestrictionCount", &AoE2CountTR, DefAoE2TerrainRests.GetCount()))
        Customs.Write("Count/AoE2TerrainRestrictionCount", (int)DefAoE2TerrainRests.GetCount());
    if (!Customs.Read("Count/SWGBTerrainRestrictionCount", &SWGBCountTR, DefSWGBTerrainRests.GetCount()))
        Customs.Write("Count/SWGBTerrainRestrictionCount", (int)DefSWGBTerrainRests.GetCount());
    if (!Customs.Read("Count/RoRCivResCount", &RoRCountCR, DefRoRCivRes.GetCount()))
        Customs.Write("Count/RoRCivResCount", (int)DefRoRCivRes.GetCount());
    if (!Customs.Read("Count/AoKCivResCount", &AoKCountCR, DefAoKCivRes.GetCount()))
        Customs.Write("Count/AoKCivResCount", (int)DefAoKCivRes.GetCount());
    if (!Customs.Read("Count/SWGBCivResCount", &SWGBCountCR, DefSWGBCivRes.GetCount()))
        Customs.Write("Count/SWGBCivResCount", (int)DefSWGBCivRes.GetCount());
    wxString read_buf;

    armor_names.Clear();
    armor_names.Add("Unused Type/No Type");
    if (GenieVersion < genie::GV_AoKA) // AoE and RoR
    {
        for (size_t loop = 0; loop < AoE1Count; ++loop)
        {
            if (!Customs.Read("AoE1Names/" + lexical_cast<std::string>(loop), &read_buf, DefAoE1Armors[loop]))
                Customs.Write("AoE1Names/" + lexical_cast<std::string>(loop), DefAoE1Armors[loop]);
            armor_names.Add(read_buf);
        }
    }
    else if (GenieVersion < genie::GV_SWGB) // AoK and TC
    {
        for (size_t loop = 0; loop < AoE2Count; ++loop)
        {
            if (!Customs.Read("AoE2Names/" + lexical_cast<std::string>(loop), &read_buf, DefAoE2Armors[loop]))
                Customs.Write("AoE2Names/" + lexical_cast<std::string>(loop), DefAoE2Armors[loop]);
            armor_names.Add(read_buf);
        }
    }
    else // SWGB and CC
    {
        for (size_t loop = 0; loop < SWGBCount; ++loop)
        {
            if (!Customs.Read("SWGBNames/" + lexical_cast<std::string>(loop), &read_buf, DefSWGBArmors[loop]))
                Customs.Write("SWGBNames/" + lexical_cast<std::string>(loop), DefSWGBArmors[loop]);
            armor_names.Add(read_buf);
        }
    }
    Effects_89_Type_CB1->Flash();
    for (size_t loop = 0; loop < 2; ++loop)
    {
        Attacks_Class_ComboBox[loop]->Flash();
    }

    for (size_t loop = 0; loop < AoE1CountTR; ++loop)
    {
        if (!Customs.Read("AoE1TerrainRestrictionNames/" + lexical_cast<std::string>(loop), &read_buf, DefAoE1TerrainRests[loop]))
            Customs.Write("AoE1TerrainRestrictionNames/" + lexical_cast<std::string>(loop), DefAoE1TerrainRests[loop]);
        AoE1TerrainRestrictions.Add(read_buf);
    }
    for (size_t loop = 0; loop < AoE2CountTR; ++loop)
    {
        if (!Customs.Read("AoE2TerrainRestrictionNames/" + lexical_cast<std::string>(loop), &read_buf, DefAoE2TerrainRests[loop]))
            Customs.Write("AoE2TerrainRestrictionNames/" + lexical_cast<std::string>(loop), DefAoE2TerrainRests[loop]);
        AoE2TerrainRestrictions.Add(read_buf);
    }
    for (size_t loop = 0; loop < SWGBCountTR; ++loop)
    {
        if (!Customs.Read("SWGBTerrainRestrictionNames/" + lexical_cast<std::string>(loop), &read_buf, DefSWGBTerrainRests[loop]))
            Customs.Write("SWGBTerrainRestrictionNames/" + lexical_cast<std::string>(loop), DefSWGBTerrainRests[loop]);
        SWGBTerrainRestrictions.Add(read_buf);
    }
    for (size_t loop = 0; loop < RoRCountCR; ++loop)
    {
        if (!Customs.Read("RoRCivResNames/" + lexical_cast<std::string>(loop), &read_buf, DefRoRCivRes[loop]))
            Customs.Write("RoRCivResNames/" + lexical_cast<std::string>(loop), DefRoRCivRes[loop]);
        RoRCivResources.Add(read_buf);
    }
    for (size_t loop = 0; loop < AoKCountCR; ++loop)
    {
        if (!Customs.Read("AoKCivResNames/" + lexical_cast<std::string>(loop), &read_buf, DefAoKCivRes[loop]))
            Customs.Write("AoKCivResNames/" + lexical_cast<std::string>(loop), DefAoKCivRes[loop]);
        AoKCivResources.Add(read_buf);
    }
    for (size_t loop = 0; loop < SWGBCountCR; ++loop)
    {
        if (!Customs.Read("SWGBCivResNames/" + lexical_cast<std::string>(loop), &read_buf, DefSWGBCivRes[loop]))
            Customs.Write("SWGBCivResNames/" + lexical_cast<std::string>(loop), DefSWGBCivRes[loop]);
        SWGBCivResources.Add(read_buf);
    }

    // This is here in case filters will be made game version dependent.
    unit_filters.Clear();
    unit_filters.Add("*Choose*");
    for (wxString &filter : Type20) unit_filters.Add(filter);
    for (wxString &filter : Type30) unit_filters.Add(filter);
    for (wxString &filter : Type40) unit_filters.Add(filter);
    for (wxString &filter : Type50) unit_filters.Add(filter);
    for (wxString &filter : Type60) unit_filters.Add(filter);
    for (wxString &filter : Type70) unit_filters.Add(filter);
    for (wxString &filter : Type80) unit_filters.Add(filter);
    unit_filters.Sort();

    research_filters.Clear();
    research_filters.Add("Lang File Name"); // 0
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
            research_filters.Add("Internal Name 2");
        if (GenieVersion >= genie::GV_C2 && GenieVersion <= genie::GV_LatestDE2)
            research_filters.Add("Repeatable");
    }

    soundfile_filters.Clear();
    soundfile_filters.Add("Filename");   // 0
    soundfile_filters.Add("DRS");
    soundfile_filters.Add("Probability");
    if (GenieVersion >= genie::GV_AoKE3)
    {
        soundfile_filters.Add("Civilization");
        soundfile_filters.Add("Unknown");
    }

    for (size_t loop = 0; loop < 2; ++loop)
    {
        Units_Class_ComboBox[loop]->Flash();
        Units_SearchFilters[loop]->Flash();
        Research_SearchFilters[loop]->Flash();
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
    if (GenieVersion != genie::GV_TCV && GenieVersion != genie::GV_CCV)
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

/*void AGE_Frame::Listing(wxListBox *List, wxArrayString &names, list<void*> &data)
{
    int selections = List->GetSelections(Items);
    int listsize = List->GetCount(); // Size before
    chrono::time_point<chrono::system_clock> startTime = chrono::system_clock::now();
    if(How2List == ADD)
    {
        if(names.size() > listsize)
        {
            List->Append(names.Last());
            SetStatusText("Added 1 visible", 2);
        }
        else
        {
            SetStatusText("Added 1 hidden", 2);
        }
        SetStatusText("Edits: "+lexical_cast<std::string>(popUp.unSaved)+" + 1", 3);
        ++popUp.unSaved;
    }
    else if(How2List == DEL)
    {
        if(20 * selections < listsize)
        {
            for(int sel = Items.size(); sel--> 0;)
            List->Delete(Items.Item(sel));
            SetStatusText("Deleted 1 by 1", 2);
        }
        else
        {
            List->Set(names);
            SetStatusText("Listed all again", 2);
        }
        SetStatusText("Edits: "+lexical_cast<std::string>(popUp.unSaved)+" + "+lexical_cast<std::string>(selections), 3);
        popUp.unSaved += selections;
    }
    else if(How2List == PASTE && Paste11)
    {
        for(int sel = 0; sel < selections; ++sel)
        {
            List->SetString(Items.Item(sel), names[Items.Item(sel)]);
        }
        SetStatusText("Pasted 1 to 1", 2);
        SetStatusText("Edits: "+lexical_cast<std::string>(popUp.unSaved)+" + "+lexical_cast<std::string>(selections), 3);
        popUp.unSaved += selections;
    }
    else
    {
        List->Set(names);
        if(How2List != SEARCH)
        {
            SetStatusText("Listed all again", 2);
            if(How2List == ENABLE)
            {
                SetStatusText("Edits: "+lexical_cast<std::string>(popUp.unSaved)+" + "+lexical_cast<std::string>(selections), 3);
                popUp.unSaved += selections;
            }
            else // Need more input to calculate edits for paste and inserts.
            {
                SetStatusText("Edits: "+lexical_cast<std::string>(popUp.unSaved)+" + 1", 3);
                ++popUp.unSaved;
            }
        }
    }
    bool showTime = ((chrono::duration_cast<chrono::milliseconds>(startTime - endTime)).count() > 1000) ? true : false;
    endTime = chrono::system_clock::now();
    listsize = List->GetCount(); // Size after
    if(listsize == 0) return;

    // Data pointers need to be reassigned always.
    auto it = data.begin();
    for(size_t loop = 0; loop < listsize; ++loop)
    {
        List->SetClientData(loop, *it++);
    }
    if(showTime)
    SetStatusText("Re-listing time: "+lexical_cast<std::string>((chrono::duration_cast<chrono::milliseconds>(endTime - startTime)).count())+" ms", 1);

    // Set selections and first visible item.
    if(How2List != SEARCH)
        List->SetFocus();
    if(selections == 0)
    {
        List->SetSelection(0);
        How2List = SEARCH;
        return;
    }
    if(How2List == ADD || Items.Item(0) >= listsize)
    {
        if(How2List == ADD)
        for(int sel = 0; sel < Items.size(); ++sel)
        List->Deselect(Items.Item(sel));
        //List->SetFirstItem(listsize - 1);
        List->SetSelection(listsize - 1);
        How2List = SEARCH;
        return;
    }
    if(FirstVisible != -1)
    {
        List->SetFirstItem(FirstVisible);
        FirstVisible = -1;
    }
    else
    {
        int first = Items.Item(0) - 3;
        if(first >= 0) List->SetFirstItem(first);
    }
    List->SetSelection(Items.Item(0));
    How2List = SEARCH;
}*/

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
        if (How2List == ADD || first_selected >= name_count)
        {
            first_selected = name_count - 1;
        }
        list->ScrollToRow(first_visible);
        if (Reselection && How2List != ADD && How2List != DEL && oldies)
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
        if (How2List != SEARCH)
        {
            list->SetFocus();
        }
    }

    How2List = SEARCH;
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
