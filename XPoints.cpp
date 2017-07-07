#include "XPoints.h"

XPoints::XPoints(IntervalTree* T1, int xp, int yl, int yh)
{
  T = T1;
  x = xp;
  isLow = true;
  y = new IntervalNode(T->nil,yl,yh);
}

XPoints::XPoints(IntervalTree* T1, IntervalNode* y1, int xp)
{
  T = T1;
  y = y1;
  isLow = false;
  x = xp;
}

XPoints::~XPoints()
{
  if (isLow == true) {
    delete y;}
}
