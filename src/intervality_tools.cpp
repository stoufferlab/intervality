#ifndef _intervality_tools_cpp_included_
#define _intervality_tools_cpp_included_

// c++ header files
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>

// my header files
#include <intervality_tools.hpp>

// namespaces
using namespace std;


/*
  Returns a vector with the size for each gap present in 
   species' diets
*/
vector<int> INTERVALITY::GapSizes(const vector<int>& links,const vector <int>& position){
  unsigned int i;
  vector<int> gaps;

  if(links.size()>1){
    gaps.reserve(links.size()-1);

    for(i=0;i<links.size()-1;++i)
      gaps.push_back(position[links[i+1]]-position[links[i]]-1);
  }
  return gaps;
}

/*
  For a given factor, returns the energy associated with gaps 
  as E = sum(g^factor)
*/
long INTERVALITY::GapEnergy(const vector<int>& links,const vector<int>& position,int factor){
  vector<int> gaps = GapSizes(links,position);
  long g = 0;
  for(unsigned int i=0;i<gaps.size();++i)
    g += long(pow(double(gaps[i]),factor));

  return g;
}


/* 
   Cost function for intervality simulated annealing calculations
   Overall cost (energy) for the entire food web is the sum of
     all gaps within all species diets, as measured by how many
     species "wide" the gap is
     For example, if prey are P and non-prey are N
       ---PNP---- has a cost of 1
       ---PNNP--- has a cost of 2
       ---PNPNP-- has a cost of 1 + 1 = 2
       --PNPNNP-- has a cost of 1 + 2 = 3
*/
long INTERVALITY::LeastIntervalEnergy(const vector<vector<int> >& links, const vector <int>& position){
  long E=0;
  unsigned int i;
  int j,k;
  for(i=0;i<links.size();++i){
    if(links[i].size()>0){
      j=links[i][0];
      k=links[i][links[i].size()-1];
      E+=(position[k]-position[j])-(links[i].size()-1);
    }
  }

  return ( E );
}


/* 
   Cost function for intervality simulated annealing calculations
   Overall cost (energy) for the entire food web is the sum of
     the square all gaps within all species diets, as measured 
     by how many species "wide" the gap is
     For example, if prey are P and non-prey are N
       ---PNP---- has a cost of 1^2 = 1
       ---PNNP--- has a cost of 2^2 = 4
       ---PNPNP-- has a cost of 1^2 + 1^2 = 2
       ---PNNNP-- has a cost of 3^2 = 9
       --PNPNNP-- has a cost of 1^2 + 2^2 = 5
*/
long INTERVALITY::LeastIntervalEnergySquared(const vector<vector<int> >& links, const vector <int>& position){
  long E=0;
  unsigned int i;
  for(i=0;i<links.size();++i)
    E += GapEnergy(links[i],position,2);

  return ( E );
}

// Given trophic positions, sort set of outgoing links so that they
// are in order of increasing position for all predators
void INTERVALITY::LeastIntervalSortLinks(vector<vector<int> >& links,const vector <int>& position){
  unsigned int i;

  for(i=0;i<links.size();++i){
    if(links[i].size()>1){
      SortLinks(links[i],position);
    }
  }
}

// Given trophic positions, sort set of outgoing links so that they
// are in order of increasing position
void INTERVALITY::SortLinks(vector<int>& links,const vector<int>& position){
  unsigned int a,b,min,h;

  for(a=0;a<links.size()-1;++a){
    min=a;
    for(b=a+1;b<links.size();++b){
      if(position[links[b]]<position[links[min]])
	min=b;
    }
    if(links[min]!=links[a]){
      h=links[a];
      links[a]=links[min];
      links[min]=h;
    }
  }
}

// given a map of orderings, print them out for accounting purposes
void INTERVALITY::PrintOrderings(map<vector<int>,long int> bestpositions){
    cout << "\nOptimal Orderings.\n";
    map<vector<int>,long int>::iterator bpiterator;
    unsigned int i;

    for(bpiterator = bestpositions.begin(); bpiterator != bestpositions.end(); ++bpiterator){
      for(i=0;i<((bpiterator->first)).size()-1;++i)
        cout << ((bpiterator->first))[i] << " ";
      cout << ((bpiterator->first))[i] << endl;
    }
}


#endif
