#ifndef _network_hpp_included_
#define _network_hpp_included_

// c++ header files
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

// my header files
#include <node.hpp>

// namespaces
using namespace std;

////////////////////////////////////////////////////////
// The class definition of a network
////////////////////////////////////////////////////////

class Network{
protected:
  vector <Node *> NodeList; // a list of nodes
  map <long,long> LabelMap; // translates original labels to in program labels
  map <long,long> ReverseLabelMap; // translates program labels to originals
  int NLinks;               // the number of links in the network
  long LabelCount;          // the number of links in the network
  
public:
  // constructors
  Network(){LabelCount=0;}
  Network(unsigned int size){LabelCount=0;for(unsigned int i=0;i<size;++i) AddNode();}
  virtual ~Network(){clear();}

  //overload access
  Node & operator [] (int i)  {return *NodeList[i];}

  // methods
  void ReIndex();
  void AddNode();
  void DeleteNode(Node * N);
  void MergeNodes(Node * A,Node * B);

  void clear();
  void ClearLinks();

  //accessors
  int size(){return NodeList.size();}
  int GetNLinks(){return NLinks;}
  long GetOriginalLabel(long i){return ReverseLabelMap[i];}

  //load networks from files
  void Adjacency(char *filename);
  void TwoColumn(char *filename);
  void UndirectedTwoColumn(char *filename);

  //print out 'in program' labels against 'input file' labels
  void PrintNodeTranslation();

  //print the network to stdout
  void PrintLinksTwoColumn();
  void PrintLinksAdjacency();

  ////////////////////////////////////////////////////
  // Code to compute intervality of a network ////////
  ////////////////////////////////////////////////////

  void LeastIntervalSwap(vector<vector<int> >& links,vector <int>& position,const unsigned long m,const unsigned long n);
  void LeastIntervalSwap(vector<vector<int> >& links,vector <int>& position);
  void LeastIntervalSwapSubsets(vector<vector<int> >& links,vector <int>& position,const vector<vector<int> >& subsets);
  long LeastIntervalOrdering(bool printProgress,bool trackOrderings);
  long LeastIntervalOrderingReducedPermutations(bool printProgress,bool trackOrderings);
  long LeastIntervalOrderingSquared(bool printProgress,bool trackOrderings);

  void SetupIntervalityVariables(vector<vector<int> >& links,
				 vector<int>& position);

  void SetupIntervalityVariablesSubsets(vector<vector<int> >& links,
					vector<int>& position,
					const vector<vector<int> >& subsets);

  void SimulatedAnnealingIntervalityInitialTemperature(vector<vector<int> >& links,
						       vector<int>& position,
						       long (*energyFunction)(const vector<vector<int> >&,
									      const vector<int>&),
						       long& E,
						       int Nsteps,
						       double& T);

  void SimulatedAnnealingIntervalityMove(vector<vector<int> >& links,
					 vector<int>& position,
					 long (*energyFunction)(const vector<vector<int> >&,
								const vector<int>&),
					 const double T,
					 long& E,
					 long& delE);

  long SimulatedAnnealingIntervality(long (*energyFunction)(const vector<vector<int> >&,
							    const vector<int>&),
				     bool printProgress,
				     bool trackOrderings,
				     bool reducePermutations);

  /////////////////////////////////////////////////////////////////
  // Code to deal with species' body sizes and intervality ////////
  /////////////////////////////////////////////////////////////////

  void ReadBodySizes(char *filename);
  void SetupBodySizePermutation(vector<double>& bodySizePosition);

};

#endif
