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


#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <iostream>

#include "Types.h"
#include <vector>
#include <string.h>

namespace gdat
{

class ISerializable
{

public:  
  ISerializable();
  virtual ~ISerializable();
  
  virtual void serializeObject(std::iostream &iostr);
  
  void serializeSubObject(ISerializable *const other);
  
  static void setGameVersion(GameVersion gv);
  
protected:
  
  //----------------------------------------------------------------------------
  /// Set wheter to read or write the object.
  ///
  /// @param write if true the serialize method will write an object, else the
  ///              object is read.
  //
  static void setOperationWrite(bool write);
  
  static bool isWriteOperation(void);
  
  
  virtual void serializeObject(void) = 0;
  
  static GameVersion getGameVersion(void);
  
  void setIOStream(std::iostream &iostr);
  std::iostream * getIOStream(void) const;
  
  std::string readString(size_t len, bool cstr=true);
  
  void writeString(std::string str, size_t len=-1, bool cstr=true);

  
  //----------------------------------------------------------------------------
  /// Generic read method for non pointers
  //
  template <typename T>
  T read()
  {
    T ret;

    if (!iostr_->eof())
      iostr_->read(reinterpret_cast<char *>(&ret), sizeof(ret));
    
    return ret;
  }
  
  template <typename T>
  void write(T &data)
  {
    iostr_->write(reinterpret_cast<char *>(&data), sizeof(T)); 
  }

  //----------------------------------------------------------------------------
  /// Generic read method for arrays. It allocates new space if pointer is 0.
  //
  template <typename T>
  void read(T **array, size_t len)
  {   
    if (!iostr_->eof())
    {
      if (*array == 0)
        *array = new T[len];
      
      iostr_->read(reinterpret_cast<char *>(*array), sizeof(T) * len);
    }
  }
  
  //----------------------------------------------------------------------------
  /// Writes an array to file.
  //
  template <typename T>
  void write(T *data, size_t len)
  {
    iostr_->write(reinterpret_cast<char *>(data), sizeof(T) * len);
  }
  
  //----------------------------------------------------------------------------
  /// Reads or writes data dependent on Write_ flag.
  //
  template <typename T>
  void serialize(T &data)
  {
    if (Write_)
      write<T>(data);
    else
      data = read<T>();
  }
  
  //----------------------------------------------------------------------------
  /// Reads or writes an array of data dependent on Write_ flag.
  //
  template <typename T>
  void serialize(T **data, size_t len)
  {
    if (Write_)
      write<T>(*data, len);
    else
      read<T>(data, len);
  }
  
  void serializeString(std::string &str, size_t len, bool cstr = true)
  {
    if (len > 0)
    {
      if (Write_)
        writeString(str, len, cstr);
      else
        str = readString(len, cstr);
    }
  }
  
  //----------------------------------------------------------------------------
  /// Reads or writes an array of data to/from a vector dependent on Write_ flag.
  //
  template <typename T>
  void serialize(std::vector<T> &vec, size_t size)
  {
    if (Write_)
    {
      if (vec.size() != size)
        std::cerr << "Warning!: vector size differs len!" << vec.size() << " " << size <<  std::endl;
      
      for (typename std::vector<T>::iterator it = vec.begin(); it != vec.end(); 
           it ++)
        write<T>(*it);
    }
    else
    {
      vec.resize(size);
      iostr_->read((char*)&vec[0], size * sizeof(T));
    }
  }

  //----------------------------------------------------------------------------
  /// Serializes a collection of objects that inherit from ISerializable.
  //
  template <typename T>
  void serializeSub(std::vector<T> &vec, size_t size)
  {
    if (Write_)
    {
      if (vec.size() != size)
        std::cerr << "Warning!: vector size differs size!" << vec.size() << " " << size <<  std::endl;
      
      for (typename std::vector<T>::iterator it = vec.begin(); it != vec.end();
           it ++)
      {
        dynamic_cast<ISerializable *>(&(*it))->serializeSubObject(this);
      }
    }
    else
    {      
      vec.resize(size);
      
      for (unsigned int i=0; i < size; i++)
      {
        ISerializable *cast_obj = dynamic_cast<ISerializable *>(&vec[i]);
        cast_obj->serializeSubObject(this);
      }
    }
  }
  
  //----------------------------------------------------------------------------
  /// Serialize a vector size number. If size differs, the number will be
  /// updated.
  //
  template <typename T>
  void serializeSize(T &data, size_t size)
  {
    if (Write_)
    {
      if (size != data)
      {
        std::cout << "Vector size differs. This operation is not tested yet!" 
                  << std::endl;
        
        data = size;
      }
      
      write<T>(data);
    }
    else
      data = read<T>();
  }
  
  //----------------------------------------------------------------------------
  /// Necessary for graphic objects. The pointer array contains entries with
  /// value 0. If a pointer is 0, a empty graphic object will be inserted into
  /// the vector.
  //
  template <typename T>
  void serializeSubWithPointers(std::vector<T> &vec, size_t size, 
                                std::vector<long> &pointers)
  {
    if (Write_)
    {
      for (unsigned int i=0; i < size; i++)
      {
        if (pointers[i] != 0)
        {
          dynamic_cast<ISerializable *>(&vec[i])->serializeSubObject(this);
        }
      }
    }
    else
    {
      vec.resize(size);
      
      for (unsigned int i=0; i < size; i++)
      {        
        T *obj = &vec[i]; 
        
        if (pointers[i] != 0)
        {
          ISerializable *cast_obj = dynamic_cast<ISerializable *>(obj);
          cast_obj->serializeSubObject(this);
        }
      }
    }
  }
  
  template <typename T>
  void serializePair(std::pair<T, T> &p, bool only_first=false)
  {
    if (Write_)
    {
      write<T>(p.first);
      
      if (!only_first)
        write<T>(p.second);
    }
    else
    {
      p.first = read<T>();
      
      if (!only_first)
        p.second = read<T>();
    }
  }
  
private:
  std::iostream *iostr_;
  
  static bool Write_;
  
  static GameVersion Game_Version_;
};

//----------------------------------------------------------------------------
/// Copies data from src to dest, but also allocates memory for dest or
/// sets dest to 0 if src is 0.
//
template <typename T>
void arraycpy(T **dest, const T *src, size_t size)
{
  if (src == 0)
    *dest = 0;
  else
  {
    *dest = new T[size];
    memcpy(*dest, src, size * sizeof(T));
  }
}
  
}

#endif // ISERIALIZABLE_H
