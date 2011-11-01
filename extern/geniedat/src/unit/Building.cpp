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


#include "geniedat/unit/Building.h"

namespace gdat
{
  
namespace unit
{

Building::Building() : Unknown37(UNKNOWN37_SIZE)
{
  ConstructionGraphicID = -1;
  SnowGraphicID = -1;
  Unknown30 = 0;
  Unknown31 = 0;
  StackUnitID = -1;
  TerrainID = -1;
  Unknown32 = -1;
  ResearchID = -1;
  Unknown33 = 0;
  Annexes.resize(BUILDING_ANNEXES_CNT);
  HeadUnit = -1;
  TransformUnit = -1;
  Unknown34 = -1;
  ConstructionSound = -1;
  GarrisonType = 0;
  GarrisonHealRate = 0;
  Unknown35 = 0;
  Unknown36 = -1;
}

Building::~Building()
{

}
void Building::serializeObject(void )
{
  serialize<short>(ConstructionGraphicID);
  
  if (getGameVersion() >= gdat::GV_TC)
    serialize<short>(SnowGraphicID);
  
  serialize<short>(Unknown30);
  serialize<short>(Unknown31);
  serialize<short>(StackUnitID);
  serialize<short>(TerrainID);
  serialize<short>(Unknown32);
  serialize<short>(ResearchID);
  
  if (getGameVersion() >= gdat::GV_AoK)
  {
    serialize<char>(Unknown33);
    serializeSub<unit::BuildingAnnex>(Annexes, 4);
    serialize<short>(HeadUnit);
    serialize<short>(TransformUnit);
    serialize<short>(Unknown34);
  }
  
  serialize<short>(ConstructionSound);
  
  if (getGameVersion() >= gdat::GV_AoK)
  {
    serialize<char>(GarrisonType);
    serialize<float>(GarrisonHealRate);
    serialize<long>(Unknown35);
    serialize<short>(Unknown36);
    serialize<char>(Unknown37, UNKNOWN37_SIZE);
  }
}

}

}

