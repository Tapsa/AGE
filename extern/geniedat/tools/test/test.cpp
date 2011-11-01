#include <iostream>
#include <geniedat/File.h>

int main(int argc, char **argv) {
  
  //gdat::File file("empires2_x1_p1.dat", gdat::GV_TC);
  gdat::File file("genie.dat", gdat::GV_SWGB);
  
  
/*  
  short id = 8;
  std::cout << file.Civs[0].Units[id].Name << std::endl;
  std::cout << file.Civs[0].Units[id].DamageGraphics.size() << std::endl;
  std::cout << (short)file.Civs[0].Units[id].DamageGraphicCount << std::endl;
  
  gdat::Unit *obj = &(file.Civs[0].Units[10]);
  
  std::cout << obj - &(file.Civs[0].Units[0]) << std::endl; */
  
  //file.setGameVersion(gdat::GV_TC);
  //file.setFileName("empires2_x1_p1.dat");
  
  //file.load();
/*
  char x;

  //std::cin >> x;

  file.setFileName("x.dat");
  file.save();
 /* 
  
  //std::cout << "\nSaving" << std::endl;
  
  file.setFileName("raw_geniedat.dat");
  file.saveRaw();
 /* file.save();

  std::cout << "\nloading again: \n" << std::endl;
  
  
  //file.setFileName("raw_empires2.dat");
  file.load();
  //*/
  return 0;
}
