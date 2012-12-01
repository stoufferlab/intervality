#ifndef _node_hpp_included_
#define _node_hpp_included_

// c++ header files
#include <iostream>
#include <map>
#include <vector>

// my header files
// N/A

// namespaces
using namespace std;

class Node{
public:
  //constructors
  Node() {}
  Node(int l,int i) {Label=l;Index=i;}
  ~Node() {}

  //accessors
  unsigned long GetLabel() {return Label;} 
  unsigned long GetIndex() {return Index;} 
  unsigned int GetNIn() {return LIn.size();} 
  unsigned int GetNOut() {return LOut.size();}
  unsigned int GetDegree() {return (LIn.size()+LOut.size());}

  //accessors to links
  Node * NodeOut(int i){return LOut[i];}
  Node *  NodeIn(int i){return LIn[i];}

  //method
  void SetLabel(unsigned long l) {Label = l;}
  void SetIndex(unsigned long i) {Index = i;}

  void AddLinkTo(Node * s);
  void AddLinkFrom(Node * s);

  void RemoveLinkTo(Node * s);
  void RemoveLinkFrom(Node * s);

  void RemoveOutLinks();
  void RemoveInLinks();

  void clear();

  bool PointsTo(Node * s);
  bool PointsFrom(Node * s);

  //overloaded operators
  bool operator == (Node);

protected:
  unsigned long Label;
  unsigned long Index;
  vector <Node * > LIn;
  vector <Node * > LOut;

};

#endif
