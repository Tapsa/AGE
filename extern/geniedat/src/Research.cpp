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


#include "geniedat/Research.h"

namespace gdat
{

Research::Research() : RequiredTechs(getRequiredTechsSize()), 
                       ResourceCosts(RESOURCE_COST_CNT), 
                       Pointers(getPointersSize()) 
                       
{
  RequiredTechCount = 0;
  Civ = -1;
  FullTechMode = 0;
  ResearchLocation = -1;
  LanguageDllName = 7000;
  LanguageDllDescription = 8000;
  ResearchTime = 0;
  TechageID = -1;
  Type = 0;
  IconID = -1;
  ButtonID = 0;
  NameLength = 13;
  Name = "New Research";
  NameLength2 = 13;
  Name2 = "New Research";
}

Research::~Research()
{
}

short Research::getRequiredTechsSize()
{
  if (getGameVersion() >= gdat::GV_AoK)
    return 6;
  else 
    return 4;
}

short Research::getPointersSize()
{
  return 3;
}

void Research::serializeObject(void )
{
  serialize<short>(RequiredTechs, getRequiredTechsSize());
  
  if (ISerializable::isWriteOperation() 
      && ResourceCosts.size() > RESOURCE_COST_CNT)
    std::cerr << "Warning: There are more ReocourseCosts object than allowed!"
              << std::endl;
              
  serializeSub<ResearchResourceCost>(ResourceCosts, RESOURCE_COST_CNT);
  serialize<short>(RequiredTechCount);
  
  if (getGameVersion() >= gdat::GV_AoK)
  {
    serialize<short>(Civ);
    serialize<short>(FullTechMode);
  }
  
  serialize<short>(ResearchLocation);
  serialize<short>(LanguageDllName);
  serialize<short>(LanguageDllDescription);
  serialize<short>(ResearchTime);
  serialize<short>(TechageID);
  serialize<short>(Type);
  serialize<short>(IconID);
  serialize<char>(ButtonID);
  serialize<long>(Pointers, getPointersSize());
  serialize<short>(NameLength);
  if (NameLength > 0)
    serializeString(Name, NameLength);
  
  if (getGameVersion() >= gdat::GV_SWGB)
  {
    serialize<short>(NameLength2);
    if (NameLength2 > 0)
      serializeString(Name2, NameLength2);
  }
  
}

}
