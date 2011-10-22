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


#ifndef TERRAIN_H
#define TERRAIN_H
#include "ISerializable.h"

namespace gdat
{

class Terrain : public ISerializable
{

public:
  Terrain();
  virtual ~Terrain();
  
  void serializeObject(void);
  
  short Unknown1;
  short Unknown2; //must be one or the game will crash
  
  static short getNameSize(void);
  
  std::string Name;
  std::string Name2;
  long SLP;
  long Unknown3;
  long SoundID;
  long BlendPriority;//not in aoe/ror
  long BlendType; //not in aoe/ror
  
  static short getColorSize();
  std::vector<char> Colours;
  short Unknown5;
  short Unknown6;
  static const short UNKNOWN7_LEN = 23;
  std::vector<char> Unknown7;
  short FrameCount;
  static const short UNKNOWN8_LEN = 2;
  std::vector<short> Unknown8;
  static const short UNKNOWN9_LEN = 54;
  std::vector<short> Unknown9;
  short TerrainReplacementID;
  static const short TERRAIN_DIMENSIONS_LEN = 2;
  std::pair<short, short> TerrainDimensions;
  static short getUnknown10Size();
  std::vector<char> Unknown10;
  
  static short getTerrainUnitSize();
  std::vector<short> TerrainUnitID;
  std::vector<short> TerrainUnitDensity;
  
  static const short UNKNOWN11_LEN = 30;
  std::vector<char> Unknown11;
  short NumberOfTerrainUnitsUsed;
  
  static const unsigned short SWGBUNKNOWN1_LEN = 24;
  std::vector<char> SWGBUnknown1;
};

}

#endif // TERRAIN_H
