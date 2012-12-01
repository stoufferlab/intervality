#ifndef _intervality_cpp_included_
#define _intervality_cpp_included_

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

/*
Functions to compute intervality of a network

The main components of the calculation (besides the network itself)
are the following two variables:

position: a vector of int of length N (number of species/nodes)

          position[i] = location of species/node i in permutation

links: a vector of vectors of int 

       for each species (node) in the network this is a list of their
       prey (outgoing links), sorted according to location in position
       vector in increasing fashion
*/

// initialize the variables that we will use to optimize intervality
void Network::SetupIntervalityVariables(vector<vector<int> >& links,vector<int>& position){
  unsigned long i,j;
  vector <int> y;

  y.clear();
  position.clear();
  for(i=0;i<NodeList.size();++i){
    position.push_back(i);

    for(j=0;j<NodeList[i]->GetNOut();++j)
      y.push_back(NodeList[i]->NodeOut(j)->GetIndex());
    links.push_back(y);

    y.clear();
  }

  random_shuffle(position.begin(),position.end());
}

/*
  Swap two species in the permutation
*/
void Network::LeastIntervalSwap(vector<vector<int> >& links,vector <int>& position,const unsigned long m,const unsigned long n){
  unsigned long i,p;

  i=position[m];
  position[m]=position[n];
  position[n]=i;

  for(i=0;i<NodeList[m]->GetNIn();++i)
    INTERVALITY::SortLinks(links[NodeList[m]->NodeIn(i)->GetIndex()],position);

  for(i=0;i<NodeList[n]->GetNIn();++i){
    p=NodeList[n]->NodeIn(i)->GetIndex();
    if(!NodeList[p]->PointsTo(NodeList[m]))
       INTERVALITY::SortLinks(links[p],position);
  }
}

/*
  Select two random species in the permutation and swap them
*/
void Network::LeastIntervalSwap(vector<vector<int> >& links,vector <int>& position){
  unsigned long m,n;

  m=rand()%position.size();
  n=rand()%position.size();

  LeastIntervalSwap(links,position,m,n);
}

/*
Determine the starting temperature for the simulated annealing algorithm

Estimate the average energy chance for a random swap and adjust the
temperature such that exp(-delE/T) ~= 0.5 at the start
*/
void Network::SimulatedAnnealingIntervalityInitialTemperature(vector<vector<int> >& links,
								    vector<int>& position,
								    long int (*energyFunction)(const vector<vector<int> >&,
											       const vector<int>&),
								    long& E,
								    int Nsteps,
								    double& T){
  long oldE;
  double avgdelE;

  avgdelE = 0;
  INTERVALITY::LeastIntervalSortLinks(links,position);

  E = energyFunction(links,position);
  for(int i=0;i<Nsteps;++i){
    oldE = E;
    LeastIntervalSwap(links,position);
    E = energyFunction(links,position);
    avgdelE += abs(oldE-E);
  }
  avgdelE /= double(Nsteps);
  T = avgdelE/0.7;

}

// make a swap in the intervality code
void Network::SimulatedAnnealingIntervalityMove(vector<vector<int> >& links,
						      vector<int>& position,
						      long (*energyFunction)(const vector<vector<int> >&,
									     const vector<int>&),
						      const double T,
						      long& E,
						      long& delE){
  long int oldE;

  vector<vector<int> > oldlinks;
  vector<int> oldposition;

  oldposition = position;
  oldlinks = links;
  oldE = E;

  LeastIntervalSwap(links,position);
  E = energyFunction(links,position);
  delE = E-oldE;

  double e=rand()/double(RAND_MAX);
  if(e > exp(-delE/double(T))){
    position = oldposition;
    links = oldlinks;
    E = oldE;
    delE = 0;
  }
}

/*
Use simulated annealing to determine the minimum value of
energyFunction for a given food web/network

Control the memory and output with the following variables:

1) printProgress: whether or not to print out periodic updates of
simulated annealing

2) trackOrderings: whether or not to keep track of the number of
optimal orderings

3) reducePermutations: whether or not to stop tracking how many
optimal orderings there are in order to reduce the memory footprint

*/
long Network::SimulatedAnnealingIntervality(long (*energyFunction)(const vector<vector<int> >&,
									 const vector<int>&),
						  bool printProgress,
						  bool trackOrderings,
						  bool reducePermutations){
  long i,j;
  long E,minE;
  long delE,avgdelE,maxdelE;

  vector<vector<int> > oldlinks,links;
  vector <int> oldposition,position(NodeList.size(),-1);
  SetupIntervalityVariables(links,position);

  long int Nsteps = 1000;
  double T;

  SimulatedAnnealingIntervalityInitialTemperature(links,position,energyFunction,E,Nsteps,T);

  minE = E;

  map<vector<int>,long int> bestpositions;

  long Tsteps = 250*(NodeList.size()*NodeList.size());

  int beginning=0,middle=0,end=0;

  // ****************!!!!!!!!!!!*************
  // YOU PROBABLY WANT TO ADJUST THE FOLLOWING AS THEY ARE JUST
  // INITIAL GUIDES FOR VALUES THAT HAVE WORKED PREVIOUSLY
  // ****************!!!!!!!!!!!*************

  if (energyFunction == &INTERVALITY::LeastIntervalEnergy){
    beginning = 50;
    middle = 50;
    end = 300;
  }else{
    if (energyFunction == &INTERVALITY::LeastIntervalEnergySquared){
      beginning = 50;
      middle = 100;
      end = 500;
    }
  }

  if(printProgress){
    fprintf(stderr, "Time_Step Temp Last_E Average_delE Min_E");
    if(trackOrderings)
      fprintf(stderr, " N_Min_E");
    fprintf(stderr, "\n");
  }

  int earlyExit = 0;
  for(j=0;j<end;++j){
    avgdelE = 0;
    maxdelE = 0;
    for(i=0;i<Tsteps;++i){

      SimulatedAnnealingIntervalityMove(links,position,energyFunction,T,E,delE);
      avgdelE += delE;
      if(delE>maxdelE)
	maxdelE = delE;
      
      if(E<=minE)
	if(E<minE){
	  minE = E;
	  if(trackOrderings){
	    bestpositions.clear();
	    bestpositions[position]++;
	  }
	  //	  if(E==0)
	  //	    break;
	}
      	else{
	  if(trackOrderings)
	    if(!(reducePermutations && bestpositions.size()>=500))
	      bestpositions[position]++;
	}
    }

    // Are we stuck?
    if(avgdelE==0)
      ++earlyExit;
    else
      earlyExit = 0;

    // Have we been stuck 10 times in a row?
    if(earlyExit > 9)
      break;

    if(printProgress){
      fprintf(stderr, "%li %.3f %li %.3e %li", j, T, E, avgdelE/double(Tsteps), minE);

      if(trackOrderings)
        fprintf(stderr, " %li", bestpositions.size());

      fprintf(stderr, "\n");
    }

    if(j>=beginning)
      if(j<middle)
	T*=0.999;
      else
	T*=0.99;
  }

  /*
  if(!printProgress)
    cout << "The minimum number of gaps found was:\t" << minE << ".\n";
  */

  if(trackOrderings)
    INTERVALITY::PrintOrderings(bestpositions);
  
  return(minE);
}

#endif
