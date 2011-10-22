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


#ifndef BUILDING_H
#define BUILDING_H

#include "../ISerializable.h"
#include "BuildingAnnex.h"

namespace gdat
{
  
namespace unit
{

class Building : public ISerializable
{

public:
  Building();
  virtual ~Building();
  
  void serializeObject(void);
  
  short ConstructionGraphicID; //aoe/ror
  short SnowGraphicID; //not in aok/aoe/ror
  short Unknown30; // aoe/ror
  short Unknown31; // aoe/ror
  short StackUnitID; // aoe/ror
  short TerrainID; // aoe/ror
  short Unknown32; //aoe/ror
  short ResearchID; // in aoe/ror
  char Unknown33;
  
  static const unsigned short BUILDING_ANNEXES_CNT = 4;
  
  std::vector<unit::BuildingAnnex> Annexes; // 4
  short HeadUnit;
  short TransformUnit;
  short Unknown34;
  short ConstructionSound;//aoe/ror
  char GarrisonType;
  float GarrisonHealRate;
  long Unknown35;
  short Unknown36;
  
  static const unsigned short UNKNOWN37_SIZE = 6;
  std::vector<char> Unknown37; // 6
  
};

}

}

#endif // BUILDING_H
