#ifndef __OPTION_PARSER_H
#define __OPTION_PARSER_H

// namespaces
using namespace std;

namespace DBS {

  void Disclaimer();
  void netfile();
  void sizefile();
  void seed();
  void individuals();
  void randomize();
  void help();

  void HelpV1(char *exec);
  void HelpV2(char *exec);

  void OptionParser(int argc,
  					char *argv[],
  					char*& netfile,
  				    unsigned long &seed);

  void OptionParser(int argc,
  					char *argv[],
  					char*& netfile,
  					char*& sizefile,
  					bool &randomize,
  					bool &species,
  				    unsigned long &seed);  					

}

#endif
