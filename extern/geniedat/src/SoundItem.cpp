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


#include "geniedat/SoundItem.h"
#include <string.h>

namespace gdat
{

SoundItem::SoundItem()
{
  ResourceID = -1;
  Probability = 100;
  Civ = -1;
  Unknown1 = -1;
}

SoundItem::SoundItem(const gdat::SoundItem& other): ISerializable(other)
{
  FileName = other.FileName;
  ResourceID = other.ResourceID;
  Probability = other.Probability;
  Civ = other.Civ;
  Unknown1 = other.Unknown1;
}


SoundItem::~SoundItem()
{
}

short SoundItem::getFileNameSize()
{
  if (getGameVersion() <= gdat::GV_TC)
    return 13;
  else
    return 27;
}

void SoundItem::serializeObject(void )
{
  serializeString(FileName, getFileNameSize());
  
  serialize<long>(ResourceID);
  serialize<short>(Probability);
  
  if (getGameVersion() >= gdat::GV_AoK)
  {
    serialize<short>(Civ);
    serialize<short>(Unknown1);
  }
}


}
