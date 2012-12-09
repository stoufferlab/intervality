/* Daniel B. Stouffer */

// c++ header files
#include <algorithm>
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

  if(argc!=4){
      cout << endl << "You have entered an incorrect number of arguments." << endl << endl;
      cout << "The correct procedure to use this program is: $ ./program empirical_file mass_file random_seed " << endl << endl;
      cout << "Where: empirical_file is a filename with list of links: predator prey," << endl;
      cout << "       mass_file is a filename with a list of species and their masses: label mass," << endl;
      cout << "       random_seed is an integer random seed" << endl;
      cout << "It will write to standard output the number of gaps for the input permutation." << endl << endl;
      exit(0);
  }

  if(strtol(argv[3],NULL,10)!=0)
    srand(strtol(argv[3],NULL,10));

  Network net;
  net.TwoColumn(argv[1]);
  net.ReadBodySizes(argv[2]);

  vector<vector<int> > subsets;

  vector<vector<int> > links;
  vector<int> positions;

  net.SetupIntervalityVariables(links,positions);
  
  vector<double> bodySizePositions(net.size(),-1);
  net.SetupBodySizePermutation(bodySizePositions);

  vector<int> ties;
  double initial_position;
  int base_position;

  for(i=0;i<bodySizePositions.size()-1;++i){
    ties.clear();
    ties.push_back(i);
    initial_position = bodySizePositions[i];
    for(j=i+1;j<bodySizePositions.size();++j){
      if(bodySizePositions[j]==bodySizePositions[i]){
        ties.push_back(j);
      }
    }
    base_position = int(initial_position-(ties.size()-1)*0.5);
    while(ties.size()>0){
      j = rand()%ties.size();
      bodySizePositions[ties[j]] = int(base_position);
      base_position += 1;
      ties[j] = ties.back();
      ties.pop_back();
    }
  }

  for(i=0;i<bodySizePositions.size();++i)
    positions[i] = int(bodySizePositions[i]);
  
  //random_shuffle(positions.begin(),positions.end());
  INTERVALITY::LeastIntervalSortLinks(links,positions);
  long int ngaps = INTERVALITY::LeastIntervalEnergy(links,positions);

  cout << "G_m = " << ngaps << endl;

}

