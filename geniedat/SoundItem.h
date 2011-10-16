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


#ifndef SOUNDITEM_H
#define SOUNDITEM_H
#include "ISerializable.h"

namespace gdat
{

class SoundItem : public ISerializable
{

public:
    SoundItem();
    SoundItem(const SoundItem &other);
    virtual ~SoundItem();
    
    void serializeObject(void);
    
    static const short FILE_NAME_LEN_AGE = 13;
    static const short FILE_NAME_LEN = 27;
    
    /// File name of the resource
    /// 13 in games <= TC and 27 in games >= SWGB
    char *FileName; //char 27
    
    /// ID of the resource in the drs file
    long ResourceID;
    
    /// Probability out of 100 that this item will be played
    short Probability;
    short Civ;//not in aoe/ror
    short Unknown1;//not in aoe/ror
};

}

#endif // SOUNDITEM_H
