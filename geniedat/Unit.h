/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef UNIT_H
#define UNIT_H
#include "ISerializable.h"
#include "UnitDamageGraphic.h"
#include "UnitCommand.h"
#include "UnitAttackOrArmor.h"
#include "ResourceCost.h"
#include "UnitBuildingAnnex.h"
#include "UnitResourceStorage.h"

namespace gdat
{

/// Available unit types
enum UnitType
{
  /// Basic units like rubble and flares.
  UT_EyeCandy = 10,      
  
  /// With Speed but mostly flags. Purpose of speed is unknown
  UT_Flag = 20,          
  
  /// Only one unit has this type. AOK, DOPL (id 243) same properties as UT_Flag
  UT_25 = 25,
  
  /// Dead and fish units. It seems to be unused in SWGB as units just explode 
  /// and do not leave carcasses. 
  UT_Dead_Fish = 30,
  
  /// Unused in AOK. No information available. 
  UT_40 = 40,
  
  /// Projectiles
  UT_Projectile = 60,
  
  /// Living units
  UT_LivingObject = 70,
  
  /// Buildings
  UT_Building = 80,
  
  /// Unknown
  UT_90 = 90 
};
  
//------------------------------------------------------------------------------
/// Stores properties of genie units.
/// TODO: Split up into multiple parts
//
class Unit : public ISerializable
{
public:
  Unit();
  Unit(const Unit &other);
  virtual ~Unit();
  
  virtual void serializeObject(void );
  
  /// See enum UnitType
  char Type;
  
  /// Length of the internal name
  short NameLength;
  
  short ID1;
  
  /// ID of the name string stored in the language.dll file
  short LanguageDllName;
  
  /// ID of the name string stored in the language.dll file
  short LanguageDllCreation;
  
  /// Class that gives certain properties
  short Class;
  
  /// Default standing graphic
  std::pair<short, short> StandingGraphic;
  
  /// Graphic shown while the units is dying.
  std::pair<short, short> DyingGraphic;
  
  /// TODO
  char DeathMode;
  
  /// Unit's hit points
  short HitPoints;
  
  /// Default line of sight measured in tiles
  float LineOfSight;
  
  /// Maximum number of units that can be garrisonned at the same time.
  char GarrisonCapacity;
  
  /// Area taken by the unit. No other unit can move into this area except
  /// flying units.
  std::pair<float, float> SizeRadius;
  
  float HPBarHeight1;
  
  /// Sound played when the unit is created
  std::pair<short, short> TrainSound;
  
  /// ID of the unit to change to when this one dies.
  short DeadUnitID;
  
  /// TODO
  char PlacementMode;
  
  /// TODO
  char AirMode;
  
  /// ID of the icon shown at the bottom when selected or when building
  short IconID;
  
  /// If true, unit can not be placed in the editor
  char HideInEditor;
  
  /// TODO Unknown
  short Unknown1;         // Always -1
  
  /// TODO
  short Enabled; //bool in aoe/ror
  std::pair <short, short> PlacementBypassTerrain;
  std::pair <short, short> PlacementTerrain;
  std::pair <float, float> EditorRadius;
  char BuildingMode;
  char VisibleInFog;
  
  /// ID of terrain restrictions that are imposed on the unit.
  short TerrainRestriction;
  
  /// Bool which determines wheter the unit can fly.
  char FlyMode;
  
  /// How much resources this unit is able to carry
  short ResourceCapacity;
  
  // TODO
  float ResourceDecay;
  char *Unknown2;//2 //blast_type[0]
  char InteractionMode;
  char MinimapMode;
  short CommandAttribute;// Page for Build button: 2 = Page 1, 10 = Page 2, ?11 = Page 3?
  float Unknown3;
  char Unknown3a;//only in aoe/ror
  short LanguageDllHelp;
  short *HotKey; //4
  char Unknown4;
  char Unknown5;
  bool Unselectable;
  char Unknown6;
  char Unknown7;// not in aoe/ror
  char Unknown8;// not in aoe/ror
  char SelectionMask;
  char SelectionShapeType;
  char SelectionShape;
  char *Unknown9; // 4 //aoe/ror 2, aok 0, tc 4
  char SelectionEffect;
  char EditorSelectionColour;
  std::pair <float, float> SelectionRadius;
  float HPBarHeight2;
  
  /// Resource cost of a unit TODO (3 different types of resource costs??)
  std::vector<UnitResourceStorage> ResourceStorage; //3
  //ResourceStorageObject ResourceStorage[3];
  unsigned char DamageGraphicCount;
  std::vector<UnitDamageGraphic> DamageGraphics;
  
  /// Sound that is played when this unit is selected
  short SelectionSound;
  short DyingSound;
  short AttackSound;
  std::string Name;
  short NameLength2;
  std::string Name2;
  
  /// MinGameVersion: SWGB
  short Unitline;
  
  /// MinGameVersion: SWGB
  char MinTechLevel;
  
  short ID2;
  short ID3;//not in aoe/ror

//      Type 20+

  float Speed;

//      Type 30+

  std::pair<short, short> WalkingGraphic;
  float RotationSpeed;
  char Unknown11;
  short TrackingUnit;
  char TrackingUnitUsed;//short
  float TrackingUnitDensity;
  float Unknown12;//not in aoe/ror
  char *Unknown16; //17 //4 short, float, 3 short aoe/ror 1 char

//      Type 40+

  short SheepConversion;//FFFF = No, 0000 = Yes
  float SearchRadius;
  float WorkRate;
  std::pair<short, short> DropSite;
  
  /// If activated unit switches villager types
  char VillagerMode;
  short MoveSound;
  short StopSound;
  char Unknown19;
  unsigned short CommandCount;//only in aoe/ror
  std::vector<UnitCommand> Commands;//only in aoe/ror

//      Type 60+

  char *Unknown20; //2 //aoe/ror 1, aok 1, tc 2
  unsigned short AttackCount;
  std::vector<UnitAttackOrArmor> Attacks;
  unsigned short ArmourCount;
  std::vector<UnitAttackOrArmor> Armours;
  short Unknown21;
  float MaxRange;
  float BlastRadius;
  float ReloadTime1;
  short ProjectileUnitID;
  
  /// Percentage value determining the probability of an attack hiting
  char AccuracyPercent;
  short Unknown22;
  short Delay;
  float *GraphicDisplacement; //3
  char Unknown23;
  float MinRange;
  float GarrisonRecoveryRate;
  short AttackGraphic;
  short DisplayedMeleeArmour;
  short DisplayedAttack;
  float DisplayedRange;
  float ReloadTime2;

//      Type 60 only

  char StretchMode;
  char CompensationMode;
  char DropAnimationMode;
  char PenetrationMode;
  char Unknown24;
  float ProjectileArc;

//      Type 70+

  std::vector<ResourceCost> ResourceCosts; //3
  short TrainTime;
  short TrainLocationID;
  char ButtonID;
  char Unknown26;//not in aoe/ror
  short *Unknown27; //3 //not in aoe/ror
  char Unknown28;//not in aoe/ror
  char MissileGraphicDelay;//not in aoe/ror
  char HeroMode;//not in aoe/ror
  std::pair<short, short> GarrisonGraphic; //not in aoe/ror
  float AttackMissileDuplicationAmount1;//not in aoe/ror
  char AttackMissileDuplicationAmount2;//not in aoe/ror
  float *AttackMissileDuplicationUnknown; //3 //not in aoe/ror
  long AttackMissileDuplicationUnit;//not in aoe/ror
  long AttackMissileDuplicationGraphic;//not in aoe/ror
  char Unknown29;//not in aoe/ror
  short DisplayedPierceArmour;

//      Type 80

  short ConstructionGraphicID; //aoe/ror
  short SnowGraphicID; //not in aok/aoe/ror
  short Unknown30; // aoe/ror
  short Unknown31; // aoe/ror
  short StackUnitID; // aoe/ror
  short TerrainID; // aoe/ror
  short Unknown32; //aoe/ror
  short ResearchID; // in aoe/ror
  char Unknown33;
  //short AnnexUnit[4];
  //float AnnexUnitMisplacement[4][2];
  std::vector<UnitBuildingAnnex> Annexes; // 4
  short HeadUnit;
  short TransformUnit;
  short Unknown34;
  short ConstructionSound;//aoe/ror
  char GarrisonType;
  float GarrisonHealRate;
  long Unknown35;
  short Unknown36;
  char *Unknown37; // 6
};

}

#endif // UNIT_H
