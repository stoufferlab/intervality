// c++ header files
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
//#include <fstream>

// my header files
#include "option_parser.hpp"

void DBS::Disclaimer(){
  cout << "I hate to break it to you, but you're not using the program correctly." << endl << endl;  
}

void DBS::netfile(){
  cout << "  -f, --netfile\t\tnetwork input file to analyze\n";
  /*
  cout << "               \t\tformat: predator_label prey_label\n";
  cout << "               \t\t        predator_label prey_label\n";
  cout << "               \t\t        ...\n";
  cout << "               \t\t        predator_label prey_label\n";
  */
}

void DBS::sizefile(){
  cout << "  -m, --sizefile\tspecies' size input file to analyze\n";
  /*
  cout << "                \tformat: species_label size\n";
  cout << "                \t        species_label size\n";
  cout << "                \t        ...\n";
  cout << "                \t        species_label size\n";
  */
}

void DBS::seed(){
  cout << "  -s, --seed\t\trandom seed\n";
  //cout << "                  [default: CURRENT_TIME]\n";
}

void DBS::individuals(){
  cout << "  -i, --individuals\tprint out number of gaps for each species\n";
  // [default: NO]\n";
}

void DBS::randomize(){
  cout << "  -r, --randomize\trandomize the sizes before calculating the number of gaps\n";
  //cout << "  -r, --randomize\twhether or not the sizes should be randomized [default: NO]\n";
}

void DBS::help(){
  cout << "      --help\t\tdisplay this help and exit\n";
}

void DBS::HelpV1(char *executable){
  cout << "Usage: " << executable << " [OPTION] -f FILENAME\n\n";
  
  cout << "Options:\n";
  netfile();
  seed();
  help();
  
  exit(1);
}

void DBS::OptionParser(int argc,
                       char *argv[],
                       char*& netfile,
                       //bool &species,
                       unsigned long &seed){

  netfile = NULL;
  //species = false;
  seed = 0;

  for(int i=1;i<argc;++i){
    if(strcmp(argv[i],"-f") == 0 || strcmp(argv[i],"--netfile") == 0){
      netfile = argv[++i];
    }else
      if(strcmp(argv[i],"-s") == 0 || strcmp(argv[i],"--randomseed") == 0){
       	seed = strtol(argv[++i],NULL,10);
      }else
        /*
        if(strcmp(argv[i],"-i") == 0 || strcmp(argv[i],"--individuals") == 0){
          species = true;
        }
        else
        */
          HelpV1(argv[0]);
  }

  if(netfile == NULL){
    HelpV1(argv[0]);
  }
}

void DBS::HelpV2(char *executable){
  //DBS::Disclaimer();

  cout << "Usage: " << executable << " [OPTION] -f FILENAME -m SIZEFILENAME\n\n";

  cout << "Options:\n";
  netfile();
  sizefile();
  randomize();
  individuals();
  seed();
  help();

  exit(1);
}

void DBS::OptionParser(int argc,
                       char *argv[],
                       char*& netfile,
                       char*& sizefile,
                       bool &randomize,
                       bool &species,
                       unsigned long &seed){

  netfile = sizefile = NULL;
  species = randomize = false;
  seed = 0;

  for(int i=1;i<argc;++i){
    if(strcmp(argv[i],"-f") == 0 || strcmp(argv[i],"--netfile") == 0){
      netfile = argv[++i];
    }else
      if(strcmp(argv[i],"-s") == 0 || strcmp(argv[i],"--randomseed") == 0){
        seed = strtol(argv[++i],NULL,10);
      }else
        if(strcmp(argv[i],"-i") == 0 || strcmp(argv[i],"--individuals") == 0){
          species = true;
        }else
          if(strcmp(argv[i],"-m") == 0 || strcmp(argv[i],"--sizefile") == 0){
            sizefile = argv[++i];
          }else
            if(strcmp(argv[i],"-r") == 0 || strcmp(argv[i],"--randomize") == 0){
              randomize = true;
            }else
              HelpV2(argv[0]);
  }

  if(netfile == NULL || sizefile == NULL){
    HelpV2(argv[0]);
  }
}
