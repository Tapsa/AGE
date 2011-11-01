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


#ifndef RESEARCHRESOURCECOST_H
#define RESEARCHRESOURCECOST_H
#include "ISerializable.h"

namespace gdat
{

/// Holds information about the cost of a research.
class ResearchResourceCost : public ISerializable
{

public:
  ResearchResourceCost();
  virtual ~ResearchResourceCost();
  
  virtual void serializeObject(void);
  
  /// Resource ID TODO add resource ids
  short Type;
  
  short Amount;
  
  /// Bool that determines wheter it is used or not
  char Used; //Here is the difference to resource cost: bool instead of short :/
};

}

#endif // RESOURCECOST_H
