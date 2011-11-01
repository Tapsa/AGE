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


#include "geniedat/GraphicDelta.h"

namespace gdat
{

GraphicDelta::GraphicDelta()
{
  GraphicID = -1;
  Unknown1 = 0;
  Unknown2 = 0;
  Unknown3 = 0;
  DirectionX = 0;
  DirectionY = 0;
  Unknown4 = -1;
  Unknown5 = 0;
}

GraphicDelta::~GraphicDelta()
{

}

void GraphicDelta::serializeObject(void )
{
  serialize<short>(GraphicID);
  serialize<short>(Unknown1);
  serialize<short>(Unknown2);
  serialize<short>(Unknown3);
  serialize<short>(DirectionX);
  serialize<short>(DirectionY);
  serialize<short>(Unknown4);
  serialize<short>(Unknown5);
}

}
