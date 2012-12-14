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
#include <option_parser.hpp>

// namespaces
using namespace std;

int main(int argc, char *argv[]){
  int i,j;
  char* netfile;
  char* sizefile;
  bool randomize,species;
  unsigned long seed;
  DBS::OptionParser(argc,argv,netfile,sizefile,randomize,species,seed);

  if(seed == 0)
    srand(time(NULL));
  else
    srand(seed);

  Network net;
  net.TwoColumn(netfile);
  net.ReadBodySizes(sizefile);

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
  
  if (randomize)
    random_shuffle(positions.begin(),positions.end());

  INTERVALITY::LeastIntervalSortLinks(links,positions);

  if (species == false){
    long int ngaps = INTERVALITY::LeastIntervalEnergy(links,positions);
    cout << "G_m = " << ngaps << endl;
  }else{
    long int ngaps;
    for(i=0;i<net.size();++i){
      if(links[i].size()>0){
        ngaps = (positions[links[i][links[i].size()-1]] - positions[links[i][0]] - 1) - (links[i].size() - 2);
        cout << net.GetOriginalLabel(i) << "\t" << ngaps << endl;
      }else
        cout << net.GetOriginalLabel(i) << "\t" << "0" << endl;
    }
  }
}

