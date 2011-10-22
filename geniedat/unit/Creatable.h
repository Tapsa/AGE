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


#ifndef CREATABLE_H
#define CREATABLE_H

#include "../ISerializable.h"
#include "../ResourceCost.h"

namespace gdat
{
  
namespace unit
{

class Creatable : public ISerializable
{

public:
  Creatable();
  virtual ~Creatable();
  
  void serializeObject(void);
  
  static short getResourceCostsSize();
  std::vector<ResourceCost> ResourceCosts; //3
  short TrainTime;
  short TrainLocationID;
  char ButtonID;
  char Unknown26;//not in aoe/ror
  
  static const short UNKNOWN27_SIZE = 3;
  std::vector<short> Unknown27; //3 //not in aoe/ror
  char Unknown28;//not in aoe/ror
  char MissileGraphicDelay;//not in aoe/ror
  char HeroMode;//not in aoe/ror
  std::pair<short, short> GarrisonGraphic; //not in aoe/ror
  float AttackMissileDuplicationAmount1;//not in aoe/ror
  char AttackMissileDuplicationAmount2;//not in aoe/ror
  
  static const short AMDBUNKNOWN_SIZE = 3;
  std::vector<float> AttackMissileDuplicationUnknown; //3 //not in aoe/ror
  
  long AttackMissileDuplicationUnit;//not in aoe/ror
  long AttackMissileDuplicationGraphic;//not in aoe/ror
  char Unknown29;//not in aoe/ror
  short DisplayedPierceArmour;
  
};

}

}

#endif // CREATABLE_H
