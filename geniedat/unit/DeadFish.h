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


#ifndef DEADFISH_H
#define DEADFISH_H

#include "../ISerializable.h"

namespace gdat
{
  
namespace unit
{

/// Attributes for Unit of type >= DeadFish.
class DeadFish : public ISerializable
{

public:
  DeadFish();
  virtual ~DeadFish();
  
  void serializeObject(void);
  
  std::pair<short, short> WalkingGraphic;
  float RotationSpeed;
  char Unknown11;
  short TrackingUnit;
  char TrackingUnitUsed;//short
  float TrackingUnitDensity;
  float Unknown12;//not in aoe/ror
  
  static short getUnknown16Size();
  std::vector<char> Unknown16; //17 //4 short, float, 3 short aoe/ror 1 char
};

}

}

#endif // DEADFISH_H
