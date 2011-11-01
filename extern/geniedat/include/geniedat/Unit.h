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
#include "unit/DamageGraphic.h"
#include "UnitCommand.h"
#include "unit/AttackOrArmor.h"
#include "ResourceCost.h"
#include "unit/BuildingAnnex.h"
#include "unit/ResourceStorage.h"
#include "unit/DeadFish.h"
#include "unit/Bird.h"
#include "unit/Projectile.h"
#include "unit/ProjectileOnly.h"
#include "unit/Creatable.h"
#include "unit/Building.h"

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
  
  /// Only birds in aoe and ror are of this type.
  UT_Bird = 40,
  
  /// Projectiles
  UT_Projectile = 60,
  
  /// Units that can be created or trained like Army, Villagers and Ships.
  UT_Creatable = 70,
  
  /// Buildings
  UT_Building = 80,
  
  /// Trees in aoe and ror are of this type
  UT_AoeTrees = 90 
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
  
  Unit &operator=(const Unit &other);
  
  virtual void serializeObject(void );
  
  char getType(void) const;
  
  void setType(char type);
  
  
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
  static const unsigned short UNKNOWN_2_SIZE = 2;
  std::vector<char> Unknown2;//2 //blast_type[0]
  char InteractionMode;
  char MinimapMode;
  short CommandAttribute;// Page for Build button: 2 = Page 1, 10 = Page 2, ?11 = Page 3?
  float Unknown3;
  char Unknown3a;//only in aoe/ror
  short LanguageDllHelp;
  
  static short getHotKeySize();
  std::vector<short> HotKey; //4
  char Unknown4;
  char Unknown5;
  bool Unselectable;
  char Unknown6;
  char Unknown7;// not in aoe/ror
  char Unknown8;// not in aoe/ror
  char SelectionMask;
  char SelectionShapeType;
  char SelectionShape;
  static short getUnknown9Size();
  std::vector<char> Unknown9; // 4 //aoe/ror 2, aok 0, tc 4
  char SelectionEffect;
  char EditorSelectionColour;
  std::pair <float, float> SelectionRadius;
  float HPBarHeight2;
  
  static const unsigned short RESOURCE_STORAGE_CNT = 3;
  
  /// Resource cost of a unit TODO (3 different types of resource costs??)
  std::vector<unit::ResourceStorage> ResourceStorage; //3
 
  unsigned char DamageGraphicCount;
  std::vector<unit::DamageGraphic> DamageGraphics;
  
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

  unit::DeadFish *DeadFish;
  
  unit::Bird *Bird;
  
  unit::Projectile *Projectile;
  
  unit::ProjectileOnly *ProjectileOnly;

  unit::Creatable *Creatable;
  
  unit::Building *Building;
  
private:
  /// See enum UnitType
  char Type;
  
  void serializeType(void);
};

}

#endif // UNIT_H
