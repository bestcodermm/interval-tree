#ifndef INTERVALNODE_HEADER
#define INTERVALNODE_HEADER

#include "interval.h"

#define BLACK 0
#define RED 1

/*
struct interval
{
  int low;
  int high;
interval(int l, int h):low(l),high(h){}
};
*/


class IntervalNode
{
 public:
  IntervalNode *left;
  IntervalNode *right;
  IntervalNode *p;
  bool color;
  int key;
  interval* interv;
  int max;
  IntervalNode(IntervalNode *init, int l, int h);
  ~IntervalNode();
};



#endif
