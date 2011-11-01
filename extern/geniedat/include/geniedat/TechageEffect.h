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


#ifndef TECHAGEEFFECT_H
#define TECHAGEEFFECT_H
#include "ISerializable.h"

namespace gdat
{

/// Stores the effect type and its parameters
/// See http://www.digitization.org/wiki/index.php/Genie_technologies#Effects
/// for more details
class TechageEffect : public ISerializable
{

public:
  TechageEffect();
  virtual ~TechageEffect();
    
  void serializeObject(void);
    
  //  DO NOT ALTER THESE! Unless you test that the game won't crash.
  char Type;
  short A;
  short B;
  short C;
  float D;
};

}

#endif // TECHAGEEFFECT_H
