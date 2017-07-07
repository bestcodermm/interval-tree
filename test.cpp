#include "IntervalTree.h"
#include <iostream>

int main()
{
  IntervalTree* T = new IntervalTree();
  IntervalNode* z1 = new IntervalNode(T->nil,5,6);
  IntervalNode* z2 = new IntervalNode(T->nil,5,9);
  IntervalNode* z3 = new IntervalNode(T->nil,10,12);
  interval* i = new interval(9,10);
  
  T->Insert(z1);
  T->Insert(z2);
  T->Insert(z3);
  T->Search(i);
  T->Delete(z3);
  T->Search(i);
  T->Delete(z2);
  T->Search(i);
  T->Delete(z1);
  T->Search(i);
  delete T;
  delete z1;
  delete z2;
  delete z3;
  delete i;
  return 0;
}
