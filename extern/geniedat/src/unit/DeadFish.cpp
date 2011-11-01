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


#include "geniedat/unit/DeadFish.h"

namespace gdat
{
  
namespace unit
{

DeadFish::DeadFish() : Unknown16(getUnknown16Size())
{
  WalkingGraphic.first = -1;
  WalkingGraphic.second = -1;
  RotationSpeed = 0;
  Unknown11 = 0;
  TrackingUnit = -1;
  TrackingUnitUsed = 0;
  TrackingUnitDensity = 0;
  Unknown12 = 0;
}

DeadFish::~DeadFish()
{

}

short DeadFish::getUnknown16Size()
{
  if (getGameVersion() >= gdat::GV_AoK)
    return 17;
  else
    return 1;
}

void DeadFish::serializeObject(void )
{
  serializePair<short>(WalkingGraphic);
  serialize<float>(RotationSpeed);
  serialize<char>(Unknown11);
  serialize<short>(TrackingUnit);
  serialize<char>(TrackingUnitUsed);
  serialize<float>(TrackingUnitDensity);
  
  if (getGameVersion() >= gdat::GV_AoK)
    serialize<float>(Unknown12);
    
  serialize<char>(Unknown16, getUnknown16Size());
}

}

}

