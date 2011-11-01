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


#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../ISerializable.h"
#include "AttackOrArmor.h"

namespace gdat
{
  
namespace unit
{

class Projectile : public ISerializable
{

public:
  Projectile();
  virtual ~Projectile();
  
  void serializeObject(void);
  
  char Unknown20; //2 //aoe/ror 1, aok 1, tc 2
  char Unknown20_1;
  unsigned short AttackCount;
  std::vector<unit::AttackOrArmor> Attacks;
  unsigned short ArmourCount;
  std::vector<unit::AttackOrArmor> Armours;
  short Unknown21;
  float MaxRange;
  float BlastRadius;
  float ReloadTime1;
  short ProjectileUnitID;
  
  /// Percentage value determining the probability of an attack hiting
  char AccuracyPercent;
  short Unknown22;
  short Delay;
  
  static short getGraphicDisplacementSize();
  std::vector<float> GraphicDisplacement; //3
  
  char Unknown23;
  float MinRange;
  float GarrisonRecoveryRate;
  short AttackGraphic;
  short DisplayedMeleeArmour;
  short DisplayedAttack;
  float DisplayedRange;
  float ReloadTime2;
  
};

}

}

#endif // PROJECTILE_H
