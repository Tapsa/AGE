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


#ifndef GVECTOR_H
#define GVECTOR_H
#include <vector>
#include "ISerializable.h"

namespace gdat
{

//------------------------------------------------------------------------------
/// A generic collection for objects stored in arrays with pointers and size
/// in front of them. 
//
template <typename S, typename P, class T>
class GVector : public ISerializable
{

public:
  //----------------------------------------------------------------------------
  //
  GVector() 
  {

  }
  
  //----------------------------------------------------------------------------
  ///
  //
  GVector(const GVector &other)
  {    
    *this = other;
  }
  
  //----------------------------------------------------------------------------
  /// 
  //
  GVector& operator=(const GVector &other)
  {
    size_ = other.size_;
    pointers_ = other.pointers_;
    vec_ = other.vec_;
    
    return *this;
  }
  
  //----------------------------------------------------------------------------
  /// Destructor
  //
  virtual ~GVector() 
  {
  }
  
  virtual void serializeObject(void) 
  {
    serializeSize<S>(size_, pointers_.size());
    serialize<P>(pointers_, size_);
    serializeSubWithPointers<T>(vec_, size_, pointers_);
  }
  
  //----------------------------------------------------------------------------
  /// Get pointer at given index without range check
  //
  P getPointerAt(size_t index)
  {
    return pointers_[index];
  }
  
  //----------------------------------------------------------------------------
  /// Access items at index without range check
  //
  T &operator[](size_t index)
  {
    return vec_[index];
  }
  
  T & at(size_t index)
  {
    return vec_.at(index);
  }
  
  //----------------------------------------------------------------------------
  /// Returns size of the collection
  //
  size_t size(void) const
  {
    return vec_.size();
  }
  
  //----------------------------------------------------------------------------
  /// Clears all data.
  //
  void clear()
  {
    pointers_.clear();   
    
    vec_.clear();
    size_ = 0;
  }
  
  //----------------------------------------------------------------------------
  /// Adds a new object to the end of the collection
  //
  void push_back(T &obj)
  {
    push_back(obj);
    pointers_.push_back(1); //TODO
    size_ ++;
  }
  
  typedef typename std::vector<T *>::iterator iterator;
  
  iterator begin(void)
  {
    return vec_.begin();
  }
  
  iterator end(void)
  {
    return vec_.end();
  }
  
private:
  S size_;
  std::vector<P> pointers_;
  std::vector<T> vec_;
};

}

#endif // GVECTOR_H
