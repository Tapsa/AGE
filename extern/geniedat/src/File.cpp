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


#include "geniedat/File.h"

#include <fstream>
#include <vector>

#include <boost/interprocess/streams/vectorstream.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/copy.hpp>

#include "geniedat/Types.h"

namespace gdat
{

//------------------------------------------------------------------------------
File::File() : TerrainHeader(0), TechTree(0), Unknown1(0), SUnknown6(0), 
               file_name_(""), file_(0), file_version_(0)
               
{
  SUnknown1 = -1;
  SUnknown2 = -1;
  SUnknown3 = -1;
  SUnknown4 = -1;
  SUnknown5 = -1;
  SUnknown7 = -1;
}

//------------------------------------------------------------------------------
File::File(std::string file_name, GameVersion gv, bool raw) : TerrainHeader(0),
           TechTree(0), Unknown1(0), SUnknown6(0), file_name_(""), file_(0), 
           file_version_(0)
{
  SUnknown1 = -1;
  SUnknown2 = -1;
  SUnknown3 = -1;
  SUnknown4 = -1;
  SUnknown5 = -1;
  SUnknown7 = -1;
  
  setGameVersion(gv);
  
  try
  {
    load(file_name, raw);
  }
  catch (...)
  {
    closeStream();
    unload();
    
    throw;
  }
}


//------------------------------------------------------------------------------
File::~File()
{
  closeStream();
  
  unload();
}

//------------------------------------------------------------------------------
void File::setGameVersion(gdat::GameVersion gv)
{
  ISerializable::setGameVersion(gv);
}

//------------------------------------------------------------------------------
void File::setFileName(std::string file_name)
{
  file_name_ = file_name;
}

//------------------------------------------------------------------------------
std::string File::getFileName(void ) const
{
  return file_name_;
}


//------------------------------------------------------------------------------
void File::load(std::string file_name, bool raw)
{
  v_stream *buf_stream = 0;
  unload();
  
  ISerializable::setOperationWrite(false);
  
  try 
  {
  
    if (openStream(file_name))
    {
      if (raw)
        serializeObject();
      else
      {
        buf_stream = decompress();
        
        serializeObject(*buf_stream);
        
      }
      
      closeStream();
    }
  }
  catch (...)
  {
    closeStream();
    delete buf_stream;
    throw;
  }

  delete buf_stream;
}

//------------------------------------------------------------------------------
void File::save(std::string file_name, bool raw)
{
  ISerializable::setOperationWrite(true);
  
  try
  {
  
    if (!raw)
    {
      std::vector<char> buf;
      v_stream buf_stream(buf);
        
      serializeObject(buf_stream);
      
      openStream(file_name);
      
      compress(buf_stream);
    }
    else
    {
      openStream(file_name);
      
      serializeObject();
    }
  
  }
  catch (...)
  {
    closeStream();
    throw;
  }
  
  closeStream();
}

//------------------------------------------------------------------------------
void File::extractRaw(std::string to_file_name)
{
  unload();
  
  ISerializable::setOperationWrite(false);
  
  openStream(file_name_);
  
  v_stream *buf_stream = decompress();
  
  std::ofstream file(to_file_name.c_str(), std::ofstream::binary);
  
  boost::iostreams::copy(*buf_stream, file);
  
  delete buf_stream;
  
  file.close();
}

//------------------------------------------------------------------------------
void File::serializeObject(void )
{
  serialize<char>(&file_version_, FILE_VERSION_LEN);
  
  if (getGameVersion() >= gdat::GV_SWGB)
  {
    serialize<short>(SUnknown1);
    serialize<long>(SUnknown2);
    serialize<long>(SUnknown3);
    serialize<long>(SUnknown4);
    serialize<long>(SUnknown5);
    
    std::cout << "Unkown1: " << SUnknown1 << std::endl;
    std::cout << "Unkown2: " << SUnknown2 << std::endl;
    std::cout << "Unkown3: " << SUnknown3 << std::endl;
    std::cout << "Unkown4: " << SUnknown4 << std::endl;
    std::cout << "Unkown5: " << SUnknown5 << std::endl;
  }
  
  serialize<unsigned short>(terrain_restriction_count_);
  serialize<unsigned short>(terrain_count_);
 
  std::cout << file_version_ << std::endl;
  std::cout << "TerRestrictionCount: " <<terrain_restriction_count_ << std::endl;
  std::cout << "TerCount: " << terrain_count_ << std::endl;
  
  serialize<long>(TerrainRestrictionPointers1, terrain_restriction_count_);
  
  if (getGameVersion() >= gdat::GV_AoK)
    serialize<long>(TerrainRestrictionPointers2, terrain_restriction_count_);
  
  TerrainRestriction::setTerrainCount(terrain_count_);
  serializeSub<TerrainRestriction>(TerrainRestrictions, terrain_restriction_count_);
    
  serializeSize<unsigned short>(player_color_count_, PlayerColours.size());
  std::cout << "PlayerColours: " << player_color_count_ << std::endl;
  
  serializeSub<PlayerColour>(PlayerColours, player_color_count_);
  
  serializeSize<unsigned short>(sound_count_, Sounds.size());
  
  std::cout << "Sounds: " << sound_count_ << std::endl;
  
  serializeSub<Sound>(Sounds, sound_count_);
  
  serializeSize<unsigned short>(graphic_count_, GraphicPointers.size());
  serialize<long>(GraphicPointers, graphic_count_);
  serializeSubWithPointers<Graphic>(Graphics, graphic_count_, GraphicPointers);
  std::cout << "Graphics: " << Graphics.size() << std::endl;
  
  serialize<char>(&TerrainHeader, TERRAIN_HEADER_SIZE);
  serializeSub<Terrain>(Terrains, terrain_count_);
  
  
  std::cout << std::hex << getIOStream()->tellg() << std::endl;
  
  switch (getGameVersion()) // is this really the techtree?
  {
    case gdat::GV_AoE: serialize<char>(&TechTree, 33666); break;
    case gdat::GV_RoR: serialize<char>(&TechTree, 41838); break;
    case gdat::GV_AoK: serialize<char>(&TechTree, 35794); break;
    case gdat::GV_TC: serialize<char>(&TechTree, 36230); break;
    case gdat::GV_SWGB: serialize<char>(&TechTree, 0x642A); break; //0x1030a5
    case gdat::GV_CC: serialize<char>(&TechTree, 0x6082); break;
    default: break;
  }
  
  std::cout << std::hex << getIOStream()->tellg() << std::endl;
  
  serialize<unsigned long>(techage_count_);
  
  std::cout << "Techage: " << techage_count_ << std::endl;
  
  serializeSub<Techage>(Techages, techage_count_);
  
  if (getGameVersion() == gdat::GV_SWGB) //pos: 0x111936
    serialize<char>(&SUnknown6, 1380);
  if (getGameVersion() == gdat::GV_CC) //pos: 0x17e864
    serialize<char>(&SUnknown6, 0x646);
  
  
  if (getGameVersion() >= gdat::GV_AoK)
  { 
    serialize<unsigned long>(unit_count_);

    std::cout << "Unitcount: " << unit_count_ << std::endl;
    serializeSub<UnitHeader>(UnitHeaders, unit_count_);
  }
  
  serialize<unsigned short>(civ_count_);
  std::cout << "Civcount: " << civ_count_ << std::endl;
  
  serializeSub<Civ>(Civs, civ_count_);
  
  if (getGameVersion() >= gdat::GV_SWGB)
    serialize<char>(SUnknown7);
  
  serialize<unsigned short>(research_count_);
  
  std::cout << "Researchcount: " << research_count_ << std::endl;
  serializeSub<Research>(Researchs, research_count_);
  
  switch (getGameVersion())
  {
    case gdat::GV_AoK:
      serialize<char>(&Unknown1, 21642); //TODO: maybe team bonus
      break;
  
    case gdat::GV_TC: serialize<char>(&Unknown1,27062); break;
    case gdat::GV_SWGB: serialize<char>(&Unknown1, 89341); break;
    case gdat::GV_CC: serialize<char>(&Unknown1, 116820); break;
    
    default: break;
  }
  
  
  /*
  std::streampos last_pos = getIOStream()->tellg();
  std::cout << "Last pos: " << last_pos << std::endl;
  
  std::streampos pos = getIOStream()->tellg();
  while (getIOStream()->eof() == false)
  {
    pos = getIOStream()->tellg();
    char x;
    getIOStream()->read(&x, 1);
  }
  
  std::cout << pos << std::endl;
  std::cout << "Unkown: "<< pos - last_pos << std::endl; //*/
  
}

//------------------------------------------------------------------------------
void File::unload()
{
  TerrainRestrictionPointers1.clear();
  TerrainRestrictionPointers2.clear();
  TerrainRestrictions.clear();
  PlayerColours.clear();
  Sounds.clear();
  GraphicPointers.clear();
  Graphics.clear();
  Terrains.clear();
  Techages.clear();
  UnitHeaders.clear();
  Civs.clear();
  Researchs.clear();
  
  delete [] file_version_;
  delete [] TerrainHeader;
  delete [] TechTree; 
  delete [] Unknown1;
  delete [] SUnknown6;
  
  file_version_ = 0;
  TerrainHeader = 0;
  TechTree = 0;
  Unknown1 = 0;
  SUnknown6 = 0;
}

//------------------------------------------------------------------------------
bool File::openStream(std::string file_name )
{ 
  if (getGameVersion() == gdat::GV_None)
  {
    std::cerr << "Game version not set!" << std::endl;
    return false;
  }
  
  if (file_name.empty())
  {
    if (file_name_.empty())
    {
      std::cerr << "No file name set!" << std::endl;
      return false;
    }
    else
      file_name = file_name_;
  }
  file_ = new std::fstream();
  file_->exceptions(std::ios::eofbit | std::ios::failbit);
  
  if (ISerializable::isWriteOperation())
  {
    file_->open(file_name.c_str(),
                             std::fstream::binary | std::fstream::out);
  }
  else
  {
    file_ ->open(file_name.c_str(), 
                            std::fstream::binary | std::fstream::in);
  }
  
  file_name_ = file_name;
  
  setIOStream(*file_);

  return true;
}

//------------------------------------------------------------------------------
void File::closeStream(void )
{
  if (file_ && file_->is_open())
    file_->close();
  
  delete file_;
  file_ = 0;
}

//------------------------------------------------------------------------------
File::v_stream* File::decompress(void )
{
  using namespace boost::iostreams;
  
  try
  {
    filtering_streambuf<input> in;
    
    zlib_params para;
    para.window_bits = -15;     //Dunno why, but works (took it from genied2)
    
    in.push(zlib_decompressor(para));
    in.push(*getIOStream());
   
    std::vector<char> buf;
    
    back_insert_device< std::vector<char> > b_ins(buf); 
    
    copy(in, b_ins);
    
    return new v_stream(buf); 
  }
  catch ( const zlib_error &z_err)
  {
    std::cerr << "Zlib decompression failed with error code: "
              <<  z_err.error() << std::endl;
    throw z_err;
  }
  
  return 0;
}

//------------------------------------------------------------------------------
void File::compress(std::istream& istr)
{
  using namespace boost::iostreams;
  
  try
  {
    filtering_streambuf<output> out;
    
    zlib_params param;
    
    param.level = -1;
    param.method = zlib::deflated;
    param.window_bits = -15;
    param.mem_level = 9;
    param.strategy = zlib::default_strategy;
    
    
    out.push(zlib_compressor(param));
    out.push(*getIOStream());
    
    copy(istr, out);
  }
  catch ( const zlib_error &z_err)
  {
    std::cerr << "Zlib compression failed with error code: "
              <<  z_err.error() << std::endl;
    throw z_err;
  }
  
}

//------------------------------------------------------------------------------
void File::serializeObject(std::iostream& iostr)
{
  gdat::ISerializable::serializeObject(iostr);
}

}

