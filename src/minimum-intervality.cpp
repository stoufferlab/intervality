/* Daniel B. Stouffer */

// c++ header files
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>

// my header files
#include <node.hpp>
#include <network.hpp>
#include <intervality_tools.hpp>
#include <option_parser.hpp>

// namespaces
using namespace std;

int main(int argc, char *argv[]){
  char* netfile;
  unsigned long seed;
  DBS::OptionParser(argc,argv,netfile,seed);

  if(seed == 0)
    srand(time(NULL));
  else
    srand(seed);

  Network net;
  net.TwoColumn(netfile);

  /* 
     !!!!! IMPORTANT !!!!!
     you control the output and memory footprint with the following
  
     1) printProgress: whether or not to print out periodic updates of
     simulated annealing

     2) trackOrderings: whether or not to keep track of the number of
     optimal orderings
  */

  bool printProgress = true;
  bool trackOrderings = true;
  long int ngaps = net.LeastIntervalOrdering(printProgress, trackOrderings);

  cout << "G_hat = " << ngaps << endl;
}

