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


#ifndef PLAYERCOLOUR_H
#define PLAYERCOLOUR_H
#include "ISerializable.h"

namespace gdat
{

class PlayerColour : public ISerializable
{

public:
  PlayerColour();
  PlayerColour(const PlayerColour &other);
  virtual ~PlayerColour();
    
  virtual void serializeObject(void);
  
  static const short NAME_LEN = 30;
  char *Name; // AoE/RoR only char [30]
  long ID;
  
  long Palette; // not in aoe/ror
  long Colour; // short in aoe/ror
  long Unknown1; // not in aoe/ror
  long Unknown2; // not in aoe/ror
  long MinimapColour; // not in aoe/ror
  long Unknown3; // not in aoe/ror
  long Unknown4; // not in aoe/ror
  long Unknown5; // not in aoe/ror
};

}

#endif // PLAYERCOLOUR_H
