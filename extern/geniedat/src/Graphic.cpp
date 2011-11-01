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


#include "geniedat/Graphic.h"
#include <string.h>

#include <iostream>

namespace gdat
{

Graphic::Graphic() : CstrName(0), CstrName2(0)
{
  Name = "New Graphic";
  Name2 = "New Graphic";
  SLP = -1;
  Unknown1 = 0;
  Unknown2 = 0;
  FrameType = 0;
  Unknown3 = 0;
  Unknown4 = 0;
  Replay = 0;
  Unknown5 = 0;
  Unknown6 = 0;
  Unknown7 = 0;
  Unknown8 = 0;
  Unknown9 = 0;
  Unknown10 = 0;
  Unknown11 = 0;
  Unknown12 = 0;
  SoundID = -1;
  AttackSoundUsed = 0;
  FrameCount = 0;
  AngleCount = 0;
  Unknown13 = 0;
  FrameRate = 0;
  ReplayDelay = 0;
  SequenceType = 0;
  ID = -1;
  Type = 0;
}

Graphic::Graphic(const Graphic& other) : ISerializable(other), CstrName(0), CstrName2(0)
{
  *this = other;
}

Graphic::~Graphic()
{
  delete [] CstrName;
  delete [] CstrName2;
}

Graphic &Graphic::operator=(const Graphic &other)
{
  try 
  {
    arraycpy<char>(&CstrName, other.CstrName, NAME_LEN);
    arraycpy<char>(&CstrName2, other.CstrName2, NAME_LEN2);
  }
  catch (std::bad_alloc &e)
  {
    delete [] CstrName;
    delete [] CstrName2;
    throw;
  }
  
  Name = other.Name;
  Name2 = other.Name2;
  
  SLP = other.SLP;
  Unknown1 = other.Unknown1;
  Unknown2 = other.Unknown2;
  FrameType = other.FrameType;
  Unknown3 = other.Unknown3;
  Unknown4 = other.Unknown4;
  Replay = other.Replay;
  Unknown5 = other.Unknown5;
  Unknown6 = other.Unknown6;
  Unknown7 = other.Unknown7;
  Unknown8 = other.Unknown8;
  Unknown9 = other.Unknown9;
  Unknown10 = other.Unknown10;
  Unknown11 = other.Unknown11;
  Unknown12 = other.Unknown12;
  DeltaCount = other.DeltaCount;
  SoundID = other.SoundID;
  AttackSoundUsed = other.AttackSoundUsed;
  FrameCount = other.FrameCount;
  AngleCount = other.AngleCount;
  Unknown13 = other.Unknown13;
  FrameRate = other.FrameRate;
  ReplayDelay = other.ReplayDelay;
  SequenceType = other.SequenceType;
  ID = other.ID;
  Type = other.Type;
  
  Deltas = other.Deltas;
  AttackSounds = other.AttackSounds;
  
  return *this;
}

short Graphic::getNameSize()
{
  if (getGameVersion() <= gdat::GV_TC)
    return NAME_LEN;
  else
    return NAME_LEN_SWGB;
}

short Graphic::getName2Size()
{
  if (getGameVersion() <=gdat::GV_TC)
    return NAME_LEN2;
  else
    return NAME_LEN_SWGB;
}

void Graphic::serializeObject(void )
{ 
  /*
   * Workaround for Name strings, because in RoR, SWGB and TC there are
   * Unknown values after the \0 on some strings. In RoR the size should be
   * ok, but it may not be right in >= SWGB
   */
  if (isWriteOperation())
  {
    if (Name != std::string(CstrName))
      serializeString(Name, getNameSize());
    else
      serialize<char>(&CstrName, getNameSize());
    
    if (Name2 != std::string(CstrName2))
      serializeString(Name2, getName2Size());
    else
      serialize<char>(&CstrName2, getName2Size());
  }
  else
  {
    serialize<char>(&CstrName, getNameSize());
    serialize<char>(&CstrName2, getName2Size());
    
    Name = std::string(CstrName);
    Name2 = std::string(CstrName2);
  }

  serialize<long>(SLP);
  serialize<char>(Unknown1);
  serialize<char>(Unknown2);
  serialize<char>(FrameType);
  serialize<char>(Unknown3);
  serialize<char>(Unknown4);
  serialize<char>(Replay);
  serialize<char>(Unknown5);
  serialize<char>(Unknown6);
  serialize<char>(Unknown7);
  serialize<char>(Unknown8);
  serialize<char>(Unknown9);
  serialize<char>(Unknown10);
  serialize<char>(Unknown11);
  serialize<char>(Unknown12);
  serializeSize<unsigned short>(DeltaCount, Deltas.size());
  serialize<short>(SoundID);
  serialize<char>(AttackSoundUsed);
  serialize<unsigned short>(FrameCount);
  serialize<unsigned short>(AngleCount);
  serialize<float>(Unknown13);
  serialize<float>(FrameRate);
  serialize<float>(ReplayDelay);
  serialize<char>(SequenceType);
  serialize<short>(ID);
  
  if (getGameVersion() >= gdat::GV_AoK)
    serialize<short>(Type);
  else
  {
    char tmp = Type;
    serialize<char>(tmp);
    Type = tmp;
  }
  
  serializeSub<GraphicDelta>(Deltas, DeltaCount);
  
  if (AttackSoundUsed != 0)
  {
    if (ISerializable::isWriteOperation() && 
        AttackSounds.size() > AngleCount)
      std::cerr << "Warning: There'are more GraphicAttackSounds than angles!"
                << std::endl;
                
    serializeSub<GraphicAttackSound>(AttackSounds, AngleCount);
  }
  
}

}
