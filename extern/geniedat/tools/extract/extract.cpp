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

#include <iostream>
#include <geniedat/File.h>

/// Usage: gextract file.dat extracted_file.dat
int main(int argc, char **argv)
{
  if (argc != 5)
  {
    std::cout << "Usage: " << argv[0] 
              << " <option> <gameversion > file.dat extracted_file.dat" << std::endl;
    std::cout << "       Where option can be: x for extract raw, sr for "
              << " save raw and sc for save compressed" << std::endl;
    std::cout << "Possible gameversions: aoe, ror, aok, tc, swgb, cc" << std::endl;
    return -1;
  }
  
  gdat::File file;
  
  if (strcmp(argv[2], "aoe") == 0)
    file.setGameVersion(gdat::GV_AoE);
  if (strcmp(argv[2], "ror") == 0)
    file.setGameVersion(gdat::GV_RoR);
  if (strcmp(argv[2], "aok") == 0)
    file.setGameVersion(gdat::GV_AoK);
  if (strcmp(argv[2], "tc") == 0)
    file.setGameVersion(gdat::GV_TC);
  if (strcmp(argv[2], "swgb") == 0)
    file.setGameVersion(gdat::GV_SWGB);
  if (strcmp(argv[2], "cc") == 0)
    file.setGameVersion(gdat::GV_CC);
  
  file.setFileName(std::string(argv[3]));
  
  if (argv[1][0] == 'x')
  {
    std::cout << "extract raw" << std::endl;
    file.extractRaw(std::string(argv[4]));
  }
  else if (argv[1][0] == 's')
  {
    file.load();
    
    file.setFileName(std::string(argv[4]));
    
    if (argv[1][1] == 'r')
      file.save("", true);
    else
      file.save();
  }
             
  return 0;
}