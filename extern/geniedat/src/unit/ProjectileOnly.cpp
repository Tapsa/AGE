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


#include "geniedat/unit/ProjectileOnly.h"

namespace gdat
{
  
namespace unit
{

ProjectileOnly::ProjectileOnly()
{
  StretchMode = 0;
  CompensationMode = 0;
  DropAnimationMode = 0;
  PenetrationMode = 0;
  Unknown24 = 0;
  ProjectileArc = 0;
}

ProjectileOnly::~ProjectileOnly()
{

}
void ProjectileOnly::serializeObject(void )
{
  serialize<char>(StretchMode);
  serialize<char>(CompensationMode);
  serialize<char>(DropAnimationMode);
  serialize<char>(PenetrationMode);
  serialize<char>(Unknown24);
  serialize<float>(ProjectileArc);
}

}

}

