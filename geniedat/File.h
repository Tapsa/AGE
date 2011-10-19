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


#ifndef FILE_H
#define FILE_H

#include <string>
#include <iostream>

#include <boost/interprocess/streams/vectorstream.hpp>

#include "Types.h"
#include "ISerializable.h"
#include "TerrainRestriction.h"
#include "PlayerColour.h"
#include "Sound.h"
#include "Graphic.h"
#include "Terrain.h"
#include "Techage.h"
#include "UnitHeader.h"
#include "Civ.h"
#include "Research.h"

using std::vector;

namespace gdat
{

class File : public ISerializable
{

public:
  //----------------------------------------------------------------------------
  /// Standard constructor
  //
  File();
  
  //----------------------------------------------------------------------------
  /// Loads the file in constructor
  ///
  /// @param file_name name of the dat file to load
  /// @param gv
  /// @param raw if true, file will be loaded form an uncompressed file
  //
  File(std::string file_name, GameVersion gv, bool raw=false);
  
  //----------------------------------------------------------------------------
  /// Destructor
  //
  virtual ~File();
  
  //----------------------------------------------------------------------------
  /// Set the game version of the dat file to load.
  ///
  /// @param gv Game version
  //
  void setGameVersion(GameVersion gv);
  
  //----------------------------------------------------------------------------
  /// Set the name of the data file to operate on.
  ///
  /// @param file_name file name
  //
  void setFileName(std::string file_name);
  
  //----------------------------------------------------------------------------
  /// Returns name of current file.
  //
  std::string getFileName(void) const;
    
  //----------------------------------------------------------------------------
  /// Loads the data from a file.
  ///
  /// @param file_name if empty or not set, file_name set with setFileName
  ///                  will be used.
  /// @param raw if true load data from a uncompressed file
  //
  void load(std::string file_name="", bool raw=false);
  
  //----------------------------------------------------------------------------
  /// Saves the data to a file.
  ///
  /// @param file_name if empty or not set, file_name set with setFileName
  ///                  will be used.
  /// @param raw if true data is saved uncompressed
  //
  void save(std::string file_name="", bool raw=false);
  
  //----------------------------------------------------------------------------
  /// Uncompress and directly store data to a file.
  //
  void extractRaw(std::string to_file_name);
  
public:
  // File data
  static const short FILE_VERSION_LEN = 8;
 
  vector<long> TerrainRestrictionPointers1;
  vector<long> TerrainRestrictionPointers2;
  vector<TerrainRestriction> TerrainRestrictions;
  
  vector<PlayerColour> PlayerColours;
  
  vector<Sound> Sounds;
  
  std::vector<long> GraphicPointers;
  std::vector<Graphic> Graphics;
        
  static const unsigned short TERRAIN_HEADER_SIZE = 138;
  char *TerrainHeader;
  vector<Terrain> Terrains;
        
  char *TechTree;
  
  vector<Techage> Techages;

  vector<UnitHeader> UnitHeaders;
  
  vector<Civ> Civs;
        
  vector<Research> Researchs;

  char *Unknown1; //[27063]; //89341
  
   //SWGB Unknowns:
  /// Seems to be the CivCount
  short SUnknown1;     
  long SUnknown2;
  long SUnknown3;
  long SUnknown4;
  long SUnknown5;
  
  char *SUnknown6; // 1382
  
  char SUnknown7;
  
protected:
  virtual void serializeObject(void);
  
private:
  
  std::string file_name_;
  std::fstream *file_;
  
  
  char *file_version_;
  
  unsigned short terrain_restriction_count_;
  unsigned short terrain_count_;
  
  unsigned short player_color_count_;
  unsigned short sound_count_;
  unsigned short graphic_count_;
  unsigned long techage_count_;
  unsigned long unit_count_;
  unsigned short civ_count_;
  unsigned short research_count_;
  
  File(const File &other);
  File &operator=(const File &other);
  
  //----------------------------------------------------------------------------
  /// Clears all data.
  //
  void unload(void);
  
  typedef boost::interprocess::basic_vectorstream< std::vector<char> > v_stream;
    
  //TODO: Refactor open/closStream and (de)compress methods
  bool openStream(std::string file_name);
  void closeStream(void);
  
  v_stream* decompress(void);
  void compress(std::istream &istr);
  
  virtual void serializeObject(std::iostream &iostr);
};

}

#endif // FILE_H
