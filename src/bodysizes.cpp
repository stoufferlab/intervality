#ifndef _bodysizes_cpp_included_
#define _bodysizes_cpp_included_

// c++ header files
#include <map>
#include <algorithm>

// my header files
#include <network.hpp>

// namespaces
using namespace std;

/* 
  Read in species id's and a corresponding double for its "body size" 
*/
void Network::ReadBodySizes(char *filename){
  unsigned long species;
  double size;
  ifstream infile;

  infile.open(filename);
  while(infile >> species >> size){
    NodeList[LabelMap[species]]->SetBodySize(size);
  }
  infile.close();
}

void Network::SetupBodySizePermutation(vector<double>& bodySizePosition){
  unsigned long i,j,k,l;
  vector <int> y;

  y.clear();
  for(i=0;i<NodeList.size();++i)
    y.push_back(i);
  random_shuffle(y.begin(),y.end());

  for(i=0;i<y.size();++i){
    k = i;
    for(j=i+1;j<y.size();++j)
      if(NodeList[y[j]]->GetBodySize() < NodeList[y[k]]->GetBodySize())
	k = j;

    j = y[i];
    y[i] = y[k];
    y[k] = j;
  }

  i=0;
  while(i<bodySizePosition.size()){
    k = l = i;
    while(i<y.size()-1 && NodeList[y[i]]->GetBodySize() == NodeList[y[i+1]]->GetBodySize()){
      k += i+1;
      ++i;
    }
    for(j=l;j<=i;++j)
      bodySizePosition[y[j]] = k/double(i+1-l)+1;
    ++i;
  }

}

#endif
