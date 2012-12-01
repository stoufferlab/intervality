#ifndef _intervality_run_functions_cpp_included_
#define _intervality_run_functions_cpp_included_

// c++ header files
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>

// my header files
#include <network.hpp>
#include <intervality_tools.hpp>

// namespaces
using namespace std;

// these are the nuts and bolts functions

long Network::LeastIntervalOrdering(bool printProgress,bool trackOrderings){
  long (*energyFunction) (const vector<vector<int> >&, const vector<int>&);
  energyFunction = &INTERVALITY::LeastIntervalEnergy;

  return (SimulatedAnnealingIntervality(energyFunction,printProgress,trackOrderings,false));
}

long Network::LeastIntervalOrderingReducedPermutations(bool printProgress,bool trackOrderings){
  long (*energyFunction) (const vector<vector<int> >&, const vector<int>&);
  energyFunction = &INTERVALITY::LeastIntervalEnergy;

  return (SimulatedAnnealingIntervality(energyFunction,printProgress,trackOrderings,true));
}

long Network::LeastIntervalOrderingSquared(bool printProgress,bool trackOrderings){
  long (*energyFunction) (const vector<vector<int> >&,const vector<int>&);
  energyFunction = &INTERVALITY::LeastIntervalEnergySquared;

  return (SimulatedAnnealingIntervality(energyFunction,printProgress,trackOrderings,false));
}

#endif
