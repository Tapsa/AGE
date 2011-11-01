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


#include "geniedat/ISerializable.h"

namespace gdat
{
  
bool ISerializable::Write_ = false;
GameVersion ISerializable::Game_Version_ = GV_None;

//------------------------------------------------------------------------------
ISerializable::ISerializable()
{

}

//------------------------------------------------------------------------------
ISerializable::~ISerializable()
{

}

//------------------------------------------------------------------------------
void ISerializable::setGameVersion(GameVersion gv)
{
  Game_Version_ = gv;
}

//------------------------------------------------------------------------------
GameVersion ISerializable::getGameVersion(void )
{
  return Game_Version_;
}

//------------------------------------------------------------------------------
void ISerializable::setOperationWrite(bool write)
{
  Write_ = write;
}

//------------------------------------------------------------------------------
bool ISerializable::isWriteOperation(void )
{
  return Write_;
}

//------------------------------------------------------------------------------
void ISerializable::setIOStream(std::iostream& iostr)
{
  iostr_ = &iostr;
}

//------------------------------------------------------------------------------
std::iostream* ISerializable::getIOStream(void ) const
{
  return iostr_;
}


//------------------------------------------------------------------------------
void ISerializable::serializeObject(std::iostream &iostr)
{
  iostr_ = &iostr;
  serializeObject();
}

//------------------------------------------------------------------------------
void ISerializable::serializeSubObject(ISerializable * const other)
{
  iostr_ = other->iostr_;
  serializeObject();
}

std::string ISerializable::readString (size_t len)
{
  if (!iostr_->eof())
  {    
    char *buf = 0;
    serialize<char>(&buf, len);
    
    std::string ret(buf, len);
    delete [] buf;
      return ret;
  }

  return "";
}

void ISerializable::writeString(std::string str, size_t len)
{
  char *buf = new char[len];
  
  strncpy(buf, str.c_str(), str.size());
  
  for (unsigned int i=str.size(); i < len; i++)
    buf[i] = 0; // fill up with 0
  
  iostr_->write(buf, len);
  
  delete [] buf;
}



}
