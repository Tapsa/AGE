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


#include "geniedat/Civ.h"

namespace gdat
{

Civ::Civ()
{
  One = 1;
  Name = "New Civilization";
  Name2 = "New Civilization";
  TechTreeID = -1;
  TeamBonusID = -1;
  GraphicSet = 0;
  SUnknown1.resize(4);
}

Civ::~Civ()
{
}

short Civ::getNameSize(void)
{
  return 20;
}

void Civ::serializeObject(void )
{
  serialize<char>(One);
  serializeString(Name, getNameSize());
  serializeSize<unsigned short>(ResourceCount, Resources.size());
  serialize<short>(TechTreeID);
  
  if (getGameVersion() >= gdat::GV_AoK)
    serialize<short>(TeamBonusID);
  
  if (getGameVersion() >= gdat::GV_SWGB)
  {
    serializeString(Name2, getNameSize());
    serialize<short>(SUnknown1, 4);
  }
  
  serialize<float>(Resources, ResourceCount);
  
  serialize<char>(GraphicSet);
  
  serializeSize<unsigned short>(UnitCount, UnitPointers.size());
  serialize<long>(UnitPointers, UnitCount);
  serializeSubWithPointers<Unit>(Units, UnitCount, UnitPointers);
}

}
