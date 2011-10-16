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
  Terrain(const Terrain &other);
  virtual ~Terrain();
  
  void serializeObject(void);
  
  /// Indicates if you can build on it: 0 = no, -1 = yes
  short Unknown1;
  short Unknown2; //must be one or the game will crash
  static const unsigned short NAME_LEN = 13;
  static const unsigned short NAME_LEN_CC = 17;
  char *Name; //char [13]
  char *Name2; //char [13]
  long SLP;
  long Unknown3;
  long SoundID;
  long BlendPriority;//not in aoe/ror
  long BlendType; //not in aoe/ror
  static const short COLOUR_LEN = 3;
  char *Colours;
  short Unknown5;
  short Unknown6;
  static const short UNKNOWN7_LEN = 23;
  char *Unknown7;
  short FrameCount;
  static const short UNKNOWN8_LEN = 2;
  short *Unknown8;
  static const short UNKNOWN9_LEN = 54;
  short *Unknown9;
  short TerrainReplacementID;
  static const short TERRAIN_DIMENSIONS_LEN = 2;
  short *TerrainDimensions;
  static const short UNKNOWN10_LEN = 64;
  static const short UNKNOWN10_P_AOK_LEN = 84; //post aok len
  char *Unknown10;
  static const short TERRAIN_UNIT_LEN = 30;
  short *TerrainUnitID;
  short *TerrainUnitDensity;
  static const short UNKNOWN11_LEN = 30;
  char *Unknown11;
  short NumberOfTerrainUnitsUsed;
  
  static const unsigned short CCUNKNOWN1_LEN = 0x18;
  char *CCUnknown1;
};

}

#endif // TERRAIN_H
