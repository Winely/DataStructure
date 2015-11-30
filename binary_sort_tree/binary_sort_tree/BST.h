#include <iostream>
using namespace std;

class BSTNode{
public:
	BSTNode(int x) :_data(x), _right(nullptr), _left(nullptr){}
	BSTNode* left(){ return _left; }
	BSTNode* right(){ return _right; }
	void setleft(BSTNode* p){ _left = p; }
	void setright(BSTNode* p){ _right = p; }
	int data(){ return _data; }
private:
	BSTNode *_left, *_right;
	int _data;
};

class BST{
public:
	BST() :_root(nullptr){}
	BST(BSTNode* p) :_root(p){}
	BSTNode* &search(int x);
	void insert(int x);
	void show(BSTNode* p);

	BSTNode *_root;
};