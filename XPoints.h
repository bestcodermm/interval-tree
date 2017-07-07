#ifndef XPOINTS_HEADER
#define XPOINTS_HEADER

#include "IntervalNode.h"
#include "IntervalTree.h"

class XPoints
{
 public:
  IntervalTree* T;
  int x;
  bool isLow;  //true then is the x low point, false is the x high point
  IntervalNode* y;
  XPoints(IntervalTree* T1, int xp , int yl, int yh);
  XPoints(IntervalTree* T1, IntervalNode* y1, int xp);
  ~XPoints();
};

#endif
