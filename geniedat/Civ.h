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


#ifndef CIV_H
#define CIV_H
#include "ISerializable.h"
#include "Unit.h"
#include "GVector.h"

namespace gdat 
{

/// Class holding information about a civilization
class Civ : public ISerializable
{

public:
  Civ();
  Civ(const Civ &other);
  virtual ~Civ();
  
  void serializeObject(void);
  
  /// Always one
  char One;
  
  static const short NAME_LEN = 20;
  
  /// Internal name
  char *Name;
  
  /// MinGameVersion: SWGB
  char *Name2;
  
  /// Number of resources defined for this civilization
  unsigned short ResourceCount;
  
  /// ID of the technology tree for a civ.
  short TechTreeID;
  
  /// ID of the team bonus
  short TeamBonusID; // not in aoe/ror
  
  /// Resources can easily added and removed using this vector.
  std::vector<float> Resources;
  
  char GraphicSet;
  
  typedef GVector<unsigned short, long, Unit> UnitVector;
  
  /// Units defined for this civ.
  UnitVector Units;
  
  short *SUnknown1; // Unknown in >=SWGB (cnt=4)
};

}

#endif // CIV_H
