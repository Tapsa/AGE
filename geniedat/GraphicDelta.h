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


#ifndef GRAPHICDELTA_H
#define GRAPHICDELTA_H
#include "ISerializable.h"

namespace gdat
{

class GraphicDelta : public ISerializable
{

public:
  GraphicDelta();
  virtual ~GraphicDelta();
  
  void serializeObject(void);
  
  short GraphicID;
  short Unknown1;
  short Unknown2;
  short Unknown3;
  short DirectionX; //In Pixels?
  short DirectionY; //In Pixels?
  short Unknown4;
  short Unknown5;
};

}

#endif // GRAPHICDELTA_H
