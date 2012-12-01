#ifndef _intervality_tools_hpp_included_
#define _intervality_tools_hpp_included_

// c++ header files
#include <map>
#include <vector>

// my header files
// N/A

// namespaces
using namespace std;

namespace INTERVALITY {

  vector<int> GapSizes(const vector<int>& links,
		       const vector <int>& position);

  long GapEnergy(const vector<int>& links,
		 const vector<int>& position,int factor);

  long LeastIntervalEnergy(const vector<vector<int> >& links,
			   const vector <int>& position);

  long LeastIntervalEnergySquared(const vector<vector<int> >& links,
				  const vector <int>& position);

  void LeastIntervalSortLinks(vector<vector<int> >& links,
			      const vector <int>& position);

  void SortLinks(vector<int>& links,
		 const vector<int>& position);

  void PrintOrderings(map<vector<int>,long int> bestpositions);

}

#endif
