#ifndef INTERNALTREE_HEADER
#define INTERNALTREE_HEADER

#include <iostream>
#include "interval.h"
#include "IntervalNode.h"

using namespace std;



#define BLACK 0
#define RED 1



class IntervalTree
{
 public:
  IntervalNode *root;
  IntervalNode *nil;
  IntervalTree();
  ~IntervalTree();
  void LeftRotate(IntervalNode *x);
  void RightRotate(IntervalNode *x);
  void Insert(IntervalNode *x);
  void InsertFixup(IntervalNode *z);
  // void Transplant(IntervalNode *x, IntervalNode *y);
  void DeleteFixup(IntervalNode *x);
  void Transplant(IntervalNode* u,IntervalNode* v);
  IntervalNode* TreeMinimum(IntervalNode* x);
  IntervalNode* TreeSuccessor(IntervalNode* x);
  void Delete(IntervalNode *x);
  int Search(IntervalNode* t); //returns 1 if find overlap, return 0 if not
};

#endif 
