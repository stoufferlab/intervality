#ifndef _network_cpp_included_
#define _network_cpp_included_

// c++ header files
#include <iostream>
#include <map>
#include <vector>

// my header files
#include <node.hpp>
#include <network.hpp>

// namespaces
using namespace std;

/* Read in a network from a file which holds data in two columns
   node-from node-to */
void Network::TwoColumn(char *filename){
  unsigned long from,to;
  ifstream infile;
  
  NodeList.clear();
  NLinks = 0;

  LabelMap.clear();
  ReverseLabelMap.clear();
  long nodecount = 0;

  infile.open(filename);
  while(infile >> from >> to){
    if(LabelMap.count(from) == 0){
      LabelMap[from] = nodecount;
      ReverseLabelMap[nodecount] = from;
      AddNode();
      ++nodecount;
    }
    if(LabelMap.count(to) == 0){
      LabelMap[to] = nodecount;
      ReverseLabelMap[nodecount] = to;
      AddNode();
      ++nodecount;
    }

    if(!NodeList[LabelMap[from]]->PointsTo(NodeList[LabelMap[to]])){
      NodeList[LabelMap[from]]->AddLinkTo(NodeList[LabelMap[to]]);
      NLinks += 1;
    }
  }
  infile.close();
}

void Network::PrintLinksTwoColumn(){
  unsigned int i,j;
  for(i=0;i<NodeList.size();++i)
    for(j=0;j<NodeList[i]->GetNOut();++j)
      cout << ReverseLabelMap[NodeList[i]->GetLabel()] << " " << ReverseLabelMap[NodeList[i]->NodeOut(j)->GetLabel()] << endl;
}

void Network::PrintNodeTranslation(){
  unsigned int i;
  cout << "model\tempirical\n";
  for(i=0;i<NodeList.size();++i)
    cout << NodeList[i]->GetLabel()+1 << "\t" << ReverseLabelMap[NodeList[i]->GetLabel()] << endl;
}

/* Each node stores its index in the NodeList; this function reindexes
   nodes in the event that a node is added or removed */
void Network::ReIndex(){
  for(unsigned int i=0;i<NodeList.size();++i)
    NodeList[i]->SetIndex(i);
}

/* Add a node to the network */
void Network::AddNode(){
  Node * N = new Node(LabelCount,NodeList.size());
  LabelCount += 1;
  NodeList.push_back(N);
} 

/* Remove a node from the network */
void Network::DeleteNode(Node * N){
  NLinks -= N->GetNOut();
  NLinks -= N->GetNIn();
  N->clear();

  NodeList.erase(NodeList.begin()+N->GetIndex());
  delete N;

  ReIndex();
} 

/* Merge two nodes in a network */
void Network::MergeNodes(Node * A,Node * B){
  unsigned int i;

  for(i=0;i<B->GetNOut();++i)
    if(!A->PointsTo(B->NodeOut(i))){
      A->AddLinkTo(B->NodeOut(i));
      NLinks += 1;
    }

  for(i=0;i<B->GetNIn();++i)
    if(!A->PointsFrom(B->NodeIn(i))){
      A->AddLinkFrom(B->NodeIn(i));
      NLinks += 1;
    }

  DeleteNode(B);

}

/* Clear the node list */
void Network::clear(){
  vector <Node *>::reverse_iterator i;
  for(i=NodeList.rbegin(); i!=NodeList.rend(); ++i){
    (*i) -> clear();
    delete (*i);
  }
  NodeList.clear();
  LabelCount = 0;
} 

/* Remove all links in the network */
void Network::ClearLinks(){
  vector <Node *>::iterator i;
  for(i=NodeList.begin(); i!=NodeList.end(); ++i){
    (*i) -> clear(); 
  }
  NLinks=0;
}

#endif
