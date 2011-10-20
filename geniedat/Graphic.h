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


#ifndef GRAPHIC_H
#define GRAPHIC_H
#include "ISerializable.h"
#include "GraphicDelta.h"
#include "GraphicAttackSound.h"

namespace gdat
{

class Graphic : public ISerializable
{

public:
  Graphic();
  Graphic(const Graphic& other);
  virtual ~Graphic();
  
  void serializeObject(void);
  
  /// Returns the size of Name
  static short getNameSize(void);
  
  /// These two name strings appear to be equal in all graphics, so the 
  /// second one's use is unknown. Like the genie unit's internal name value, 
  /// they are heavily abbreviated, such as "ARRG2NNE" meaning "Archery 
  /// Range Fuedal Age (orth) European"
  std::string Name;
  
  /// Returns the size of Name2
  static short getName2Size(void);
  
  /// See Name
  std::string Name2;
  
  /// SLP resource id
  long SLP;
  
  //TODO
  char Unknown1;
  char Unknown2;
  char FrameType;
  char Unknown3;
  char Unknown4;
  char Replay;
  char Unknown5;
  char Unknown6;
  char Unknown7;
  char Unknown8;
  char Unknown9;
  char Unknown10;
  char Unknown11;
  char Unknown12;
  short SoundID;
  char AttackSoundUsed;
  
  /// Number of frames per angle animation
  unsigned short FrameCount;
  
  /// Number of angles tored in slp and also the number of extra structures.
  /// If there are more than 1 angle, AngleCount/2 - 1 frames will be
  /// mirrored. That means angles starting from south going clockwise to
  /// north are stored and the others will be mirrored.
  unsigned short AngleCount;
  float Unknown13;
  
  /// Frame rate in seconds. (Delay between frames)
  float FrameRate;
  
  float ReplayDelay;
  char SequenceType;
  short ID;
  short Type;//char in aoe/ror
  
  std::vector<GraphicDelta> Deltas;
  std::vector<GraphicAttackSound> AttackSounds;
    
private:
  unsigned short DeltaCount;
  
  static const short NAME_LEN_SWGB = 25;
  
  static const short NAME_LEN = 21;
  static const short NAME_LEN2 = 13;
  
  char *CstrName; //char [21]
  char *CstrName2; //char [13]
};

}

#endif // GRAPHIC_H
