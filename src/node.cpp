#ifndef _node_cpp_included_
#define _node_cpp_included_

// c++ header files
#include <algorithm>
#include <iostream>
#include <vector>

// my header files
#include <node.hpp>

// namespaces
using namespace std;

void Node::AddLinkTo(Node * N){
  LOut.push_back(N);
  N->LIn.push_back(this);
}

void Node::AddLinkFrom(Node * N){
  LIn.push_back(N);
  N->LOut.push_back(this);
}

void Node::RemoveLinkTo(Node * s){
  vector <Node *>::iterator i = find(LOut.begin(),LOut.end(),s);
  if(i!=LOut.end())
    LOut.erase(i);
}

void Node::RemoveLinkFrom(Node * s){
  vector <Node *>::iterator i = find(LIn.begin(),LIn.end(),s);
  if(i!=LIn.end())
    LIn.erase(i);
}

void Node::RemoveOutLinks(){
  vector <Node *>::reverse_iterator i;
  for(i=LOut.rbegin(); i!=LOut.rend(); ++i){
    this -> RemoveLinkTo(*i);
    (*i) -> RemoveLinkFrom(this);
  }
  LOut.clear();
}

void Node::RemoveInLinks(){
  vector <Node *>::reverse_iterator i;
  for(i=LIn.rbegin(); i!=LIn.rend(); ++i){
    this -> RemoveLinkFrom(*i);
    (*i) -> RemoveLinkTo(this);
  }
  LIn.clear();
}

void Node::clear(){
  RemoveOutLinks();
  RemoveInLinks();
}

bool Node::PointsTo(Node * s){
  if(find(LOut.begin(),LOut.end(),s)!=LOut.end())
    return(true);
  return(false);
}

bool Node::PointsFrom(Node * s){
  if(find(LIn.begin(),LIn.end(),s)!=LIn.end())
    return(true);
  return(false);
}

/* this operator checks if two nodes have identical links */
/* NOT if every stored variable is identical between two nodes */
bool Node::operator == (Node n){
  bool equal;
  unsigned int i;

  equal = true;
  if(LIn.size() == n.GetNIn() && LOut.size() == n.GetNOut()){
    for(i=0;i<LIn.size();++i)
      if(!n.PointsFrom(NodeIn(i))){
	equal=false;
	break;
      }
    if(equal)
      for(i=0;i<LOut.size();++i)
	if(!n.PointsTo(NodeOut(i))){
	  equal=false;
	  break;
	}
  }else
    equal=false;
  
  return equal;
}

#endif
