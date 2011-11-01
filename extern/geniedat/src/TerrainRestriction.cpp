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


#include "geniedat/TerrainRestriction.h"

#include <iostream>

namespace gdat
{
  
short TerrainRestriction::Terrain_Count_ = 0;

TerrainRestriction::TerrainRestriction()
{
  TerrainAccessible.resize(Terrain_Count_); // Moved from AGE to here.
  TerrainPassGraphics.resize(Terrain_Count_); // Seems to work as supposed.
}

TerrainRestriction::~TerrainRestriction()
{

}

void TerrainRestriction::setTerrainCount(short int Terrain_Count)
{
  Terrain_Count_ = Terrain_Count;
}


void TerrainRestriction::serializeObject(void)
{
  serialize<float>(TerrainAccessible, Terrain_Count_);
  
  if (getGameVersion() >= gdat::GV_AoK)
  {
    serializeSub<TerrainPassGraphic>(TerrainPassGraphics, Terrain_Count_);
  }
}

}
