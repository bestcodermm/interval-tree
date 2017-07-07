#include "XPoints.h"
#include <vector>
#include <algorithm>

using namespace std;

bool CompareX(XPoints* X1, XPoints* X2)
{
  return (X1->x < X2->x);
}

int main()
{
  IntervalTree* T = new IntervalTree();
  vector<XPoints*> XVector; 
  int N = 1;
  int rect[1][4] = {{5,6,9,10}};     //Define the rectangle information    //the format is {x_low,x_high,y_low,y_high}
		 
  for (int i=0;i<N;i++) {
    int coord[4];
    for (int j=0;j<4;j++){
      coord[j] = rect[i][j];}
    XPoints* X1 = new XPoints(T,coord[0],coord[2],coord[3]);
    XPoints* X2 = new XPoints(T,X1->y,coord[1]);
    XVector.push_back(X1);
    XVector.push_back(X2);
  }
  sort(XVector.begin(),XVector.end(),CompareX);  // algorithm::sort performs n*log(n) complexity
  
  for (unsigned t=0;t<XVector.size();t++) {
    if (XVector[t]->isLow == true) {
      
      if (T->Search(XVector[t]->y) == 1) {
	for (unsigned t=0;t<XVector.size();t++) {
	  delete XVector[t];
	}
	return 1;
      }
      else if (T->Search(XVector[t]->y) == 0) {
	T->Insert(XVector[t]->y);
      }
    }
    else {
      T->Delete(XVector[t]->y);
    }
  }
  
  for (unsigned t=0;t<XVector.size();t++) {
    delete XVector[t];
  }
  cout<<"NO OVERLAP!"<<endl;
  return 0;
}
