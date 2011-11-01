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


#include "geniedat/UnitCommand.h"

namespace gdat
{

UnitCommand::UnitCommand() : Graphics(getGraphicsSize())
{
  One = 0;
  ID = -1;
  Unknown1 = 0;
  Type = 7;
  ClassID = -1;
  UnitID = -1;
  Unknown2 = -1;
  ResourceIn = -1;
  SubType = -1;
  ResourceOut = -1;
  Unknown3 = -1;
  Unknown4 = 0;
  ExecutionRadius = 0;
  Unknown5 = 0;
  Unknown6 = 1;
  Unknown7 = 3;
  Unknown8 = 1;
  Unknown9 = 1;
  Unknown10 = 1;
  Unknown11 = 0;
  Unknown12 = 0;
  Unknown13 = 5;
  Unknown14 = 9;
}

UnitCommand::~UnitCommand()
{
}

short UnitCommand::getGraphicsSize(void)
{
  return 6;
}

void UnitCommand::serializeObject(void )
{
  serialize<short>(One);
  serialize<short>(ID);
  serialize<char>(Unknown1);
  serialize<short>(Type);
  serialize<short>(ClassID);
  serialize<short>(UnitID);
  serialize<short>(Unknown2);
  serialize<short>(ResourceIn);
  serialize<short>(SubType);
  serialize<short>(ResourceOut);
  serialize<short>(Unknown3);
  serialize<float>(Unknown4);
  serialize<float>(ExecutionRadius);
  serialize<float>(Unknown5);
  serialize<char>(Unknown6);
  serialize<float>(Unknown7);
  serialize<char>(Unknown8);
  serialize<char>(Unknown9);
  serialize<char>(Unknown10);
  serialize<char>(Unknown11);
  serialize<short>(Unknown12);
  serialize<short>(Unknown13);
  serialize<char>(Unknown14);
  serialize<short>(Graphics, getGraphicsSize());
}


}
