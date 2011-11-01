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


#include "geniedat/unit/Bird.h"

namespace gdat
{
  
namespace unit
{

Bird::Bird()
{
  SheepConversion = -1;
  SearchRadius = 0;
  WorkRate = 0;
  DropSite.first = -1;
  DropSite.second = -1;
  VillagerMode = 0;
  MoveSound = -1;
  StopSound = -1;
  Unknown19 = 0;
}

Bird::~Bird()
{

}
void Bird::serializeObject(void )
{
  serialize<short>(SheepConversion);
  serialize<float>(SearchRadius);
  serialize<float>(WorkRate);
  serializePair<short>(DropSite);
  serialize<char>(VillagerMode);
  serialize<short>(MoveSound);
  serialize<short>(StopSound);
  serialize<char>(Unknown19);
  
  if (getGameVersion() <= gdat::GV_RoR)
  {
    serializeSize<unsigned short>(CommandCount, Commands.size());
    serializeSub<UnitCommand>(Commands, CommandCount);
  }
}

}

}

