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


#include "geniedat/PlayerColour.h"
#include <string.h>

namespace gdat
{

PlayerColour::PlayerColour() : Name(0)
{
  ID = -1;
  Palette = 0;
  Colour = 0;
  Unknown1 = 0;
  Unknown2 = 0;
  MinimapColour = 0;
  Unknown3 = 0;
  Unknown4 = 0;
  Unknown5 = 0;
}

PlayerColour::PlayerColour(const gdat::PlayerColour& other) 
              : ISerializable(other), Name(0)
{
  try 
  {
    arraycpy<char>(&Name, other.Name, NAME_LEN);
  }
  catch (std::bad_alloc &e)
  {
    delete [] Name;
    throw;
  }
  
  ID = other.ID;
  Palette = other.Palette;
  Colour = other.Colour;
  Unknown1 = other.Unknown1;
  Unknown2 = other.Unknown2;
  MinimapColour = other.MinimapColour;
  Unknown3 = other.Unknown3;
  Unknown4 = other.Unknown4;
  Unknown5 = other.Unknown5;
}


PlayerColour::~PlayerColour()
{
  delete [] Name;
}

void PlayerColour::serializeObject(void )
{
  if (getGameVersion() < gdat::GV_AoK)
    serialize<char>(&Name, NAME_LEN);
  
  serialize<long>(ID);
  
  if (getGameVersion() < gdat::GV_AoK)
  {
    short col_short = Colour;
    serialize<short>(col_short);
    Colour = col_short;
  }
  else
  {
    serialize<long>(Palette);
    serialize<long>(Colour);
    serialize<long>(Unknown1);
    serialize<long>(Unknown2);
    serialize<long>(MinimapColour);
    serialize<long>(Unknown3);
    serialize<long>(Unknown4);
    serialize<long>(Unknown5);
  }
}


}
