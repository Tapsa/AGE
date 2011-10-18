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


#ifndef TECHAGE_H
#define TECHAGE_H
#include "ISerializable.h"
#include "TechageEffect.h"

namespace gdat
{

class Techage : public ISerializable
{

public:
  Techage();
  Techage(const Techage &other);
  virtual ~Techage();
  
  void serializeObject(void);
  
  static const short NAME_LEN = 31;
  
  /// Internal name, changing doesn't effect anything.
  char *Name; //char [31]
  
  std::vector<TechageEffect> Effects;
  
private:
  /// Number of effects
  unsigned short EffectCount;
};

}

#endif // TECHAGE_H
