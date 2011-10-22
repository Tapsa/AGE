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


#ifndef DAMAGEGRAPHIC_H
#define DAMAGEGRAPHIC_H
#include "../ISerializable.h"

namespace gdat
{
  
namespace unit
{

class DamageGraphic : public ISerializable
{

public:
  DamageGraphic();
  virtual ~DamageGraphic();
  
  void serializeObject(void);
  
  short GraphicID;
  short DamagePercent;
  char Unknown1;
};

}

}

#endif // UNITDAMAGEGRAPHIC_H
