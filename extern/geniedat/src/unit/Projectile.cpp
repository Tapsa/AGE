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


#include "geniedat/unit/Projectile.h"

namespace gdat
{
  
namespace unit
{

Projectile::Projectile() : GraphicDisplacement(getGraphicDisplacementSize())
{
  Unknown20 = 0;
  Unknown20_1 = 0;
  Unknown21 = -1;
  MaxRange = 0;
  BlastRadius = 0;
  ReloadTime1 = 0;
  ProjectileUnitID = -1;
  AccuracyPercent = 0;
  Unknown22 = 0;
  Delay = 0;
  Unknown23 = 0;
  MinRange = 0;
  GarrisonRecoveryRate = 0;
  AttackGraphic = -1;
  DisplayedMeleeArmour = 0;
  DisplayedAttack = 0;
  DisplayedRange = 0;
  ReloadTime2 = 0;
}

Projectile::~Projectile()
{

}

short Projectile::getGraphicDisplacementSize()
{
  return 3;
}

void Projectile::serializeObject(void )
{
  serialize<char>(Unknown20);
  
  if (getGameVersion() >= gdat::GV_TC)
    serialize<char>(Unknown20_1);
  
  serializeSize<unsigned short>(AttackCount, Attacks.size());
  serializeSub<unit::AttackOrArmor>(Attacks, AttackCount);
  
  serializeSize<unsigned short>(ArmourCount, Armours.size());
  serializeSub<unit::AttackOrArmor>(Armours, ArmourCount);
  
  serialize<short>(Unknown21);
  serialize<float>(MaxRange);
  serialize<float>(BlastRadius);
  serialize<float>(ReloadTime1);
  serialize<short>(ProjectileUnitID);
  serialize<char>(AccuracyPercent);
  serialize<short>(Unknown22);
  serialize<short>(Delay);
  serialize<float>(GraphicDisplacement, getGraphicDisplacementSize());
  serialize<char>(Unknown23);
  serialize<float>(MinRange);
  
  if (getGameVersion() >= gdat::GV_AoK)
    serialize<float>(GarrisonRecoveryRate);
  
  serialize<short>(AttackGraphic);
  serialize<short>(DisplayedMeleeArmour);
  serialize<short>(DisplayedAttack);
  serialize<float>(DisplayedRange);
  serialize<float>(ReloadTime2);
}

}

}

