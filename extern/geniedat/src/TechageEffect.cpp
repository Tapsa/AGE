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


#include "geniedat/TechageEffect.h"

namespace gdat
{

TechageEffect::TechageEffect()
{
  Type = -1;
  A = -1;
  B = -1;
  C = -1;
  D = 0;
}

TechageEffect::~TechageEffect()
{

}

void TechageEffect::serializeObject(void )
{
  serialize<char>(Type);
  serialize<short>(A);
  serialize<short>(B);
  serialize<short>(C);
  serialize<float>(D);
}

}
