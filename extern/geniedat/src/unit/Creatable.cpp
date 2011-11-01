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


#include "geniedat/unit/Creatable.h"

namespace gdat
{
  
namespace unit
{

Creatable::Creatable() : ResourceCosts(getResourceCostsSize()),
                         Unknown27(UNKNOWN27_SIZE),
                         AttackMissileDuplicationUnknown(AMDBUNKNOWN_SIZE)
{
  TrainTime = 0;
  TrainLocationID = -1;
  ButtonID = 0;
  Unknown26 = 0;
  Unknown28 = 0;
  MissileGraphicDelay = 0;
  HeroMode = 0;
  GarrisonGraphic.first = -1;
  GarrisonGraphic.second = -1;
  AttackMissileDuplicationAmount1 = 1;
  AttackMissileDuplicationAmount2 = 1;
  AttackMissileDuplicationUnit = -1;
  AttackMissileDuplicationGraphic = -1;
  Unknown29 = 0;
  DisplayedPierceArmour = 0;
}

Creatable::~Creatable()
{

}

short Creatable::getResourceCostsSize()
{
  return 3;
}

void Creatable::serializeObject(void )
{
  serializeSub<ResourceCost>(ResourceCosts, getResourceCostsSize());
  serialize<short>(TrainTime);
  serialize<short>(TrainLocationID);
  serialize<char>(ButtonID);
  
  if (getGameVersion() >= gdat::GV_AoK)
  {
    serialize<char>(Unknown26);
    serialize<short>(Unknown27, UNKNOWN27_SIZE);
    serialize<char>(Unknown28);
    serialize<char>(MissileGraphicDelay);
    serialize<char>(HeroMode);
    serializePair<short>(GarrisonGraphic);
    serialize<float>(AttackMissileDuplicationAmount1);
    serialize<char>(AttackMissileDuplicationAmount2);
    serialize<float>(AttackMissileDuplicationUnknown, AMDBUNKNOWN_SIZE);
    serialize<long>(AttackMissileDuplicationUnit);
    serialize<long>(AttackMissileDuplicationGraphic);
    serialize<char>(Unknown29);
  }
  
  serialize<short>(DisplayedPierceArmour);
}

}

}

