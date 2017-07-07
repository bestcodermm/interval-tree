#include "IntervalTree.h"

int Max(int a, int b, int c)
{
  if (a>b)
    return a>c ? a:c;
  else
    return b>c ? b:c;
}

IntervalTree::IntervalTree()
{
  nil = new IntervalNode(NULL,-1,-1);
  root = nil;
}



/********************************************************************************/



IntervalTree::~IntervalTree()
{
  delete nil;
}



/********************************************************************************/


void IntervalTree::LeftRotate(IntervalNode *x)
{
  IntervalNode *y = x->right;
  x->right = y->left;
  if (y->left != nil){
    y->left->p = x;}
  y->p = x->p;    // link x's parent to y
  
  if (x->p == nil) {
    root = y;}  // special case: x is the root

  else if (x == x->p->left) {
    x->p->left = y;}
  
  else {
    x->p->right = y;}

  y->left = x;
  x->p = y;

  //update the additional info
  y->max = x->max;
  x->max = Max(x->interv->high,x->left->max,x->right->max);
}


/********************************************************************************/


void IntervalTree::RightRotate(IntervalNode *x)
{
  IntervalNode *y = x->left;
  x->left = y->right;
  if (y->right != nil) {
    y->right->p = x;}
  
  y->p = x->p;
  
  if (x->p == nil) {  //special case: the x is the root
    root = y;}
  
  else if (x == x->p->right) {
    x->p->right = y;}

  else {
    x->p->left = y;}
  
  //update the max information
  y->max = x->max;
  x->max = Max(x->interv->high,x->left->max,x->right->max);
}


/********************************************************************************/

void IntervalTree::InsertFixup(IntervalNode *z)
{
  IntervalNode *y;
  while (z->p->color == RED) {
    if (z->p == z->p->p->left) {
      y = z->p->p->right;  // y is the uncle of the z
      
      if (y->color == RED) {  //case 1 : y is RED
	z->p->color = BLACK;
	y->color = BLACK;
	z->p->p->color = RED;
	z = z->p->p;}

      else { 
	if (z == z->p->right) { //case 2
	  z = z->p;
	  LeftRotate(z);}
	z->p->color = BLACK;  //case 3
	z->p->p->color = RED;
	RightRotate(z->p->p);}
    }

    else if (z->p == z->p->p->right) {   //
      y = z->p->p->left;
      if (y->color == RED) {
	z->p->color = BLACK;
	y->color = BLACK;
	z->p->p->color = RED;
	z = z->p->p;}
      else {
	if (z == z->p->left) {
	  z = z->p;
	  RightRotate(z);}
	z->p->color = BLACK;
	z->p->p->color = RED;
	LeftRotate(z->p->p);}  
    }
  }
  root->color = BLACK;
}


/********************************************************************************/



void IntervalTree::Insert(IntervalNode *z)
{
  IntervalNode *y = nil;
  IntervalNode *x = root;
  while (x!=nil) {
    x->max = max(x->max, z->max);
    y = x;
    if (z->key < x->key){
      x = x->left;}
    else {
      x = x->right;}
  }
  z->p = y;
  if (y == nil) {
    root = z;}
  else if (z->key < y->key) {
    y->left = z;}
  else {
    y->right = z;}
  z->left = nil;
  z->right = nil;
  z->color = RED;
  InsertFixup(z);
}


/********************************************************************************/



void IntervalTree::DeleteFixup(IntervalNode *x)
{
  IntervalNode *w;
  
  while ( (x!=root) && (x->color == BLACK) ) {
    if (x == x->p->left) {
      w = x->p->right;
      
      if (w->color == RED) {   //case 1: x's sibling w is red
	w->color = BLACK; 
	x->p->color = RED;
	LeftRotate(x->p);
	w = x->p->right;  //turn to case 2, 3, 4
      }

      if ((w->left->color == BLACK) && (w->right->color == BLACK)) {  //case 2: x's sibling w is black, and both w's children are black
	w->color = RED;
	x = x->p;
      }

      else {
	if (w->right->color == BLACK) {  //case 3: x's sibling w is black, w's left child is red and right child is black
	  w->left->color = BLACK;
	  w->color = RED;
	  RightRotate(w);
	  w = x->p->right;
	}
	w->color = x->p->color;
	x->p->color = BLACK;
	w->right->color = BLACK;
	LeftRotate(x->p);
	x = root;
      }	
    }

    else if (x == x->p->right){
      w = x->p->left;
      if (w->color == RED) { //case 1
	w->color = BLACK;
	x->p->color = RED;
	RightRotate(x->p);
	w = x->p->left;
      }
      
      if ((w->right->color == BLACK) && (w->left->color == BLACK)) { //case 2
	w->color = RED;
	x = x->p;
      }
      
      else {
	if (w->left->color == BLACK) { //case 3
	  w->right->color = BLACK;
	  w->color = RED;
	  LeftRotate(w);
	  w = x->p->left;
	}
	x->color = x->p->color;
	x->p->color = BLACK;
	w->left->color = BLACK;
	RightRotate(x->p);
	x = root;
      }
    }
  }
  x->color = BLACK;
}


/********************************************************************************/



IntervalNode* IntervalTree::TreeMinimum(IntervalNode *x)
{
  while (x->left != nil){
    x = x->left;}
  return x;
}


/********************************************************************************/



IntervalNode* IntervalTree::TreeSuccessor(IntervalNode *x)
{
  if (x->right != nil) {
    return TreeMinimum(x->right);
  }
  IntervalNode *y = x->p;
  while ((y != NULL) && (x==y->right)) {
    x = y;
    y = y->p;
  }
  return y;
}


/********************************************************************************/


void IntervalTree::Transplant(IntervalNode* u,IntervalNode* v)
{
  if (u->p == nil){
    root = v;}
  else if (u == u->p->left) {
    u->p->left = v;}
  else {
    u->p->right = v;}
  v->p = u->p;
}


/********************************************************************************/

/*
void IntervalTree::Delete(IntervalNode* z)
{
  IntervalNode *x, *y, *pa;
  if ( (z->left == nil) || (z->right == nil) ){
    y = z;
    pa = y->p;
    pa->max = pa->interv->high;
    pa = pa->p;
    while (pa->max == y->max) {
      pa->max = Max(pa->max, pa->left->max, pa->right->max);
      pa = pa->p;}
  }
  else {
    y = TreeSuccessor(z);}
  
  //update the max information
  pa = pa->p;
  pa->max = pa->interv->high;
  pa = pa->p;
  while (pa->max == y->max){
    pa->max = Max(pa->max,pa->left->max,pa->right->max);
    pa = pa->p;}
  
  //delete the y node
  if (y->left != nil) {
    x = y->left;}
  else {
    x = y->right;}
  x->p = y->p;
  if (y->p == nil) {
    root = x;}
  else if (y == y->p->left) {
    y->p->left = x;}
  else {
    y->p->right = x;}

  //replace
  if (y != z){
    z->interv = y->interv;
    z->key = y->key;
    z->max = y->max;
    pa = z->p;
    while (pa->max < z->max){
      pa->max = z->max;
      pa = pa->p;}
  }

  if (y->color == BLACK){
    DeleteFixup(x);}
   
    }*/

void IntervalTree::Delete(IntervalNode *z)
{
  IntervalNode* y = z;
  IntervalNode* x;
  bool y_original_color = z->color;
  if (z->left == nil) {
    x = z->right;
    if ((z != root) && (z->p->max == z->interv->high)) {
      z->p->max = Max(z->p->left->max,z->p->interv->high,z->right->max);}
    else if (z == root) {
      nil->max = -1;}
    IntervalNode* r = z->p;
    while ((r != root) && (r != nil)){
      r->max = Max(r->interv->high,z->right->max,z->left->max);
      r = r->p;}     //update the max information
    Transplant(z,z->right);
  }
  else if (z->right == nil) {
    x = z->left;
    if (z->p->max == z->interv->high) {
      z->p->max = Max(z->p->left->max,z->p->interv->high,z->right->max);} 
    IntervalNode* r = z->p;
    while (r != root) {
      r->max = Max(r->interv->high,z->right->max,z->left->max);
      r = r->p;}   //update the max information
    Transplant(z,z->left);}
  else {
    y = TreeMinimum(z->right);
    y_original_color = y->color;
    x = y->right;
    if (y->p == z){
      x->p = y;}
    else {
      Transplant(y,y->right);
      y->right = z->right;
      y->right->p = y;}
    if (y->max < z->left->max) {
      y->max = z->left->max;}
    Transplant(z,y);
    y->left = z->left;
    y->left->p = y;
    y->color = z->color;
    IntervalNode *r = y;
    while (r != root) {
      r->max = Max(r->interv->high,r->left->max,r->right->max);}
  }
  if (y_original_color == 0) {
    DeleteFixup(x);}
}


/********************************************************************************/


int IntervalTree::Search(IntervalNode* t)
{
  interval* i = t->interv;
  IntervalNode* x= root;
  while ((x!=nil) && ((x->interv->high < i->low) || (x->interv->low > i->high))) {
    if ((x->left != nil) && (x->left->max >= i->low)) {
      x = x->left;}
    else {
      x = x->right;}
  }
  if (x == nil) {
    //cout<<"No overlap!"<<endl;
    return 0;}
  else {
    cout<<"Found overlaps!"<<endl;
    return 1;}
    
}
