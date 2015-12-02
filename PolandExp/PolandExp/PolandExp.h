#define PLUS	-1	//+
#define MINUS	-2	//-
#define MULTI	-3	//*
#define DIVI	-4	//÷

#include <iostream>
#include <string>
using namespace std;

class Node {
public:
	friend class ExpTree;
	Node(int data):_data(data), _left(nullptr), _right(nullptr){}
private:
	int _data;	//大于等于零表示数值，小于零表示运算符
	Node *_left, *_right;
};

string aa="a";
typedef decltype(aa.begin()) ITER;

class ExpTree{
public:
	ExpTree() :_root(nullptr){}
	void setRoot(Node* root){ _root = root; }
	Node* parse(ITER begin, ITER end);
	void skip(ITER &it); //跳过括号
	int convertToInt(ITER begin, ITER end);
	void printDLR(Node *root);//前序输出
	void printLDR(Node *root);//中序输出
	void printLRD(Node *root);//后序输出
	void printDLR(){ printLRD(_root); cout << endl; }
	void printLDR(){ printLDR(_root); cout << endl; }
	void printLRD(){ printLRD(_root); cout << endl; }
private:
	Node *_root;
};