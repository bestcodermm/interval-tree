#include "IntervalNode.h"

IntervalNode::IntervalNode(IntervalNode *init, int l, int h)
{
  left = init;
  right = init;
  p = init;
  interv = new interval(l,h);
  key = l;
  max = h;
  color = BLACK;
}

IntervalNode::~IntervalNode()
{
  delete interv;
}
