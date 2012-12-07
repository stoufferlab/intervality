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

// namespaces
using namespace std;

int main(int argc, char *argv[]){
  int i,j,k,l;
  srand(time(NULL));

  if(argc!=3){
      cout << endl << "You have entered an incorrect number of arguments. ";
      cout << "The correct procedure to use this program is:\n\n";
      cout << "$ ./run_intervality empirical_file random_seed" << endl << endl;
      cout << "where: empirical_file is a filename with list of links: predator prey," << endl;
      cout << "       random_seed is an integer random seed" << endl << endl;
      cout << "It will write to standard output the minimum number of gaps for any permutation." << endl << endl;
      exit(0);
  }

  if(strtol(argv[2],NULL,10)!=0)
    srand(strtol(argv[2],NULL,10));

  Network net;
  net.TwoColumn(argv[1]);

  /* 
     control the output and memory footprint with the following
  
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

