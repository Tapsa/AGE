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


#include "geniedat/Unit.h"


namespace gdat
{
 
Unit::Unit() : Unknown2(UNKNOWN_2_SIZE), HotKey(getHotKeySize()), 
               Unknown9(getUnknown9Size())
{
//    Type 10+

  Type = UT_EyeCandy;
  NameLength = 9;
  ID1 = -1;
  LanguageDllName = 5000;
  LanguageDllCreation = 6000;
  Class = -1;
  StandingGraphic.first = -1;
  StandingGraphic.second = -1;
  DyingGraphic.first = -1;
  DyingGraphic.second = -1;
  DeathMode = 0;
  HitPoints = 1;
  LineOfSight = 2;
  GarrisonCapacity = 0;
  SizeRadius.first = 0;
  SizeRadius.second = 0;
  HPBarHeight1 = 0;
  TrainSound.first = -1;
  TrainSound.second = -1;
  DeadUnitID = -1;
  PlacementMode = 0;
  AirMode = 0;
  IconID = -1;
  HideInEditor = 0;
  Unknown1 = -1;
  Enabled = 0;
  PlacementBypassTerrain.first = -1;
  PlacementBypassTerrain.second = -1;
  PlacementTerrain.first = -1;
  PlacementTerrain.second = -1;
  EditorRadius.first = 0;
  EditorRadius.second = 0;
  BuildingMode = 0;
  VisibleInFog = 0;
  TerrainRestriction = 0;
  FlyMode = 0;
  ResourceCapacity = 0;
  ResourceDecay = 0;
  InteractionMode = 0;
  MinimapMode = 0;
  CommandAttribute = 0;
  Unknown3 = 0;
  Unknown3a = 0;
  LanguageDllHelp = 39464;
  Unknown4 = 0;
  Unknown5 = 0;
  Unselectable = 0;
  Unknown6 = 0;
  Unknown7 = 0;
  Unknown8 = 0;
  SelectionMask = 0;
  SelectionShapeType = 0;
  SelectionShape = 0;
  SelectionEffect = 1;
  EditorSelectionColour = 52;
  SelectionRadius.first = 0;
  SelectionRadius.second = 0;
  HPBarHeight2 = 0;
  ResourceStorage.resize(RESOURCE_STORAGE_CNT);
  SelectionSound = -1;
  DyingSound = -1;
  AttackSound = -1;
  Name = "New Unit";
  NameLength2 = 9;
  Name2 = "New Unit";
  Unitline = -1;
  MinTechLevel = -1;
  ID2 = -1;
  ID3 = -1;

//  Type 20+

  Speed = 1;

  DeadFish = 0;
  Bird = 0;
  Projectile = 0;
  ProjectileOnly = 0;
  Creatable = 0;
  Building = 0;
}

  
Unit::Unit(const gdat::Unit& other): ISerializable(other)
{
  *this = other;
}

Unit::~Unit()
{
  delete DeadFish;
  delete Bird;
  delete Projectile;
  delete ProjectileOnly;
  delete Creatable;
  delete Building;
}

Unit & Unit::operator=(const Unit &other)
{
  Type = other.Type;
  NameLength = other.NameLength;
  ID1 = other.ID1;
  LanguageDllName = other.LanguageDllName;
  LanguageDllCreation = other.LanguageDllCreation;
  Class = other.Class;
  
  StandingGraphic = other.StandingGraphic;
  TrainSound = other.TrainSound;
  
  DyingGraphic = other.DyingGraphic;
  DeathMode = other.DeathMode;
  HitPoints = other.HitPoints;
  LineOfSight = other.LineOfSight;
  GarrisonCapacity = other.GarrisonCapacity;
  SizeRadius = other.SizeRadius;
  HPBarHeight1 = other.HPBarHeight1;
  DeadUnitID = other.DeadUnitID;
  PlacementMode = other.PlacementMode;
  AirMode = other.AirMode;
  IconID = other.IconID;
  HideInEditor = other.HideInEditor;
  Unknown1 = other.Unknown1;         // Always -1
  Enabled = other.Enabled; //bool in aoe/ror
  PlacementBypassTerrain = other.PlacementBypassTerrain;
  PlacementTerrain = other.PlacementTerrain;
  EditorRadius = other.EditorRadius;
  BuildingMode = other.BuildingMode;
  VisibleInFog = other.VisibleInFog;
  TerrainRestriction = other.TerrainRestriction;
  FlyMode = other.FlyMode;
  ResourceCapacity = other.ResourceCapacity;
  ResourceDecay = other.ResourceDecay;
  Unknown2 = other.Unknown2;
  InteractionMode = other.InteractionMode;
  MinimapMode = other.MinimapMode;
  CommandAttribute = other.CommandAttribute;// Page for Build button: 2 = Page 1, 10 = Page 2, ?11 = Page 3?
  Unknown3 = other.Unknown3;
  Unknown3a = other.Unknown3a;//only in aoe/ror
  LanguageDllHelp = other.LanguageDllHelp;
  HotKey = other.HotKey;
  Unknown4 = other.Unknown4;
  Unknown5 = other.Unknown5;
  Unselectable = other.Unselectable;
  Unknown6 = other.Unknown6;
  Unknown7 = other.Unknown7;// not in aoe/ror
  Unknown8 = other.Unknown8;// not in aoe/ror
  SelectionMask = other.SelectionMask;
  SelectionShapeType = other.SelectionShapeType;
  SelectionShape = other.SelectionShape;
  Unknown9 = other.Unknown9;
  
  SelectionEffect = other.SelectionEffect;
  EditorSelectionColour = other.EditorSelectionColour;
  SelectionRadius = other.SelectionRadius;
  HPBarHeight2 = other.HPBarHeight2;
  ResourceStorage = other.ResourceStorage; 
  DamageGraphicCount = other.DamageGraphicCount;
  DamageGraphics = other.DamageGraphics;
  SelectionSound = other.SelectionSound;
  DyingSound = other.DyingSound;
  AttackSound = other.AttackSound;
  Name = other.Name;
  NameLength2 = other.NameLength2;
  Name2 = other.Name2;
  Unitline = other.Unitline;
  MinTechLevel = other.MinTechLevel;
  ID2 = other.ID2;
  ID3 = other.ID3;//not in aoe/ror

//      Type 20+

  Speed = other.Speed;

  if (other.DeadFish)
    DeadFish = new unit::DeadFish(*other.DeadFish);
  else
    DeadFish = 0;
  
  if (other.Bird)
    Bird = new unit::Bird(*other.Bird);
  else
    Bird = 0;

  if (other.Projectile)
    Projectile = new unit::Projectile(*other.Projectile);
  else
    Projectile = 0;
  
  if (other.ProjectileOnly)
    ProjectileOnly = new unit::ProjectileOnly(*other.ProjectileOnly);
  else
    ProjectileOnly = 0;

  if (other.Creatable)
    Creatable = new unit::Creatable(*other.Creatable);
  else
    Creatable = 0;

  if (other.Building)
    Building = new unit::Building(*other.Building);
  else
    Building = 0;
  
  return *this;
}

char Unit::getType(void) const
{
  return Type;
}

void Unit::setType(char type)
{
  if (type != Type)
  {
    // Deleting unused properties
    switch (type)
    {
      case UT_EyeCandy:
      case UT_Flag:
      case UT_25:
      case UT_AoeTrees:
        delete DeadFish;
        DeadFish = 0;
      
      case UT_Dead_Fish:
        delete Bird;
        Bird = 0;
        
      case UT_Bird:
        delete Projectile;
        Projectile = 0;
        
      case UT_Projectile:
        delete Creatable;
        Creatable = 0;
        
      case UT_Creatable:
        delete Building;
        Building = 0;
        
      default: break;
    }
    
    // Creating necessary properties
    switch (type)
    {
      case UT_Building:
        if (!Building)
          Building = new unit::Building();
        
      case UT_Creatable:
        if (!Creatable)
          Creatable = new unit::Creatable();
        
      case UT_Projectile:
        if (!Projectile)
          Projectile = new unit::Projectile();
        
      case UT_Bird:
        if (!Bird)
          Bird = new unit::Bird();
        
      case UT_Dead_Fish:
        if (!DeadFish)
          DeadFish = new unit::DeadFish();
      break;
      
      case UT_EyeCandy:
      case UT_Flag:
      case UT_25:
      case UT_AoeTrees:
      default: break;
    }
    
    // ProjectileOnly needs extra treatment
    if (type == UT_Projectile)
    {
      if (!ProjectileOnly)
        ProjectileOnly = new unit::ProjectileOnly;
    }
    else
    {
      delete ProjectileOnly;
      ProjectileOnly = 0;
    }
  }
  
  Type = type;
}

short Unit::getHotKeySize()
{
  return 4;
}

short Unit::getUnknown9Size()
{
  if (getGameVersion() >= gdat::GV_TC)
    return 4;
  else 
  {
    if (getGameVersion() <= gdat::GV_RoR)
      return 2;
    else
      return 0;
  }
}

void Unit::serializeType(void)
{
  if (isWriteOperation())
    serialize<char>(Type);
  else
  {
    char type;
    serialize<char>(type);
    setType(type);
  }
}

void Unit::serializeObject(void )
{
  //Type 10+
  serializeType();
  
  serialize<short>(NameLength);
  serialize<short>(ID1);        //TODO: Check
  serialize<short>(LanguageDllName);
  serialize<short>(LanguageDllCreation);
  serialize<short>(Class);
  
  if (getGameVersion() >= gdat::GV_AoK)
    serializePair<short>(StandingGraphic);
  else
    serializePair<short>(StandingGraphic, true);
  
  serializePair<short>(DyingGraphic);
  serialize<char>(DeathMode);
  serialize<short>(HitPoints);
  serialize<float>(LineOfSight);
  serialize<char>(GarrisonCapacity); 
  serializePair<float>(SizeRadius);
  
  serialize<float>(HPBarHeight1);
  
  serializePair<short>(TrainSound, (getGameVersion() >= gdat::GV_AoK) ? false : true);
  serialize<short>(DeadUnitID);
  serialize<char>(PlacementMode);
  serialize<char>(AirMode);
  serialize<short>(IconID);
  serialize<char>(HideInEditor);
  serialize<short>(Unknown1);
  
  if (getGameVersion() >= gdat::GV_AoK)
    serialize<short>(Enabled);
  else
  {
    char enabled = Enabled;
    serialize<char>(enabled);
    Enabled = enabled;
  }
  
  serializePair<short>(PlacementBypassTerrain);
  serializePair<short>(PlacementTerrain);
  serializePair<float>(EditorRadius);
  serialize<char>(BuildingMode);
  serialize<char>(VisibleInFog);
  serialize<short>(TerrainRestriction);
  serialize<char>(FlyMode);
  serialize<short>(ResourceCapacity);
  serialize<float>(ResourceDecay);
  serialize<char>(Unknown2, UNKNOWN_2_SIZE);
  serialize<char>(InteractionMode);
  serialize<char>(MinimapMode);
  
  if (getGameVersion() >= gdat::GV_AoK)// || getGameVersion() == gdat::GV_TC)
    serialize<short>(CommandAttribute);
  else
  {
    char attr = CommandAttribute;
    serialize<char>(attr);
    CommandAttribute = attr;
  }
  
  serialize<float>(Unknown3);
  
  if (getGameVersion() <= gdat::GV_RoR)
    serialize<char>(Unknown3a);
  
  serialize<short>(LanguageDllHelp);
  serialize<short>(HotKey, getHotKeySize());
  serialize<char>(Unknown4);
  serialize<char>(Unknown5);
  serialize<bool>(Unselectable);
  serialize<char>(Unknown6);
  
  if (getGameVersion() >= gdat::GV_AoK)
  {
    serialize<char>(Unknown7);
    serialize<char>(Unknown8);
  }
  
  serialize<char>(SelectionMask);
  
  if (getGameVersion() >= gdat::GV_AoK)
    serialize<char>(SelectionShapeType);
  
  serialize<char>(SelectionShape);
  
  serialize<char>(Unknown9, getUnknown9Size());
  
  if (getGameVersion() >= gdat::GV_AoK)
  {
    serialize<char>(SelectionEffect);
    serialize<char>(EditorSelectionColour);
  }
  
  serializePair<float>(SelectionRadius);
  serialize<float>(HPBarHeight2);
  
  serializeSub<unit::ResourceStorage>(ResourceStorage, 3);
  
  serializeSize<unsigned char>(DamageGraphicCount, DamageGraphics.size());
  serializeSub<unit::DamageGraphic>(DamageGraphics, DamageGraphicCount);
  
  serialize<short>(SelectionSound);
  serialize<short>(DyingSound);
  serialize<short>(AttackSound);
  
  serializeString(Name, NameLength);
  
  if (getGameVersion() >= gdat::GV_SWGB)
  {
    serialize<short>(NameLength2);
    serializeString(Name2, NameLength2);
    
    serialize<short>(Unitline);
    serialize<char>(MinTechLevel);
  }
  
  serialize<short>(ID2);
    
  if (getGameVersion() >= gdat::GV_AoK)
    serialize<short>(ID3);
  
  if (Type == gdat::UT_AoeTrees)
    return;
  
  if (Type >= gdat::UT_Flag)
    serialize<float>(Speed);
  else
    return;
  
  if (DeadFish)
    DeadFish->serializeSubObject(this);
  
  if (Bird)
    Bird->serializeSubObject(this);
  
  if (Projectile)
    Projectile->serializeSubObject(this);
  
  if (ProjectileOnly)
    ProjectileOnly->serializeSubObject(this);
  
  if (Creatable)
    Creatable->serializeSubObject(this);
  
  if (Building)
    Building->serializeSubObject(this);
}

  
}

