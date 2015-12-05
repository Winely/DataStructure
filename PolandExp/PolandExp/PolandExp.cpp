#include "PolandExp.h"
#define L cout<<'('
#define R cout<<')'

void ExpTree::skip(ITER &it)	//跳过括号
{
	int cnt(1);	//记录括号层数
	while (cnt)
	{
		it--;
		if (*it == ')') cnt++;
		else if (*it == '(') cnt--;
	}
}

int ExpTree::convertToInt(ITER begin, ITER end)
{
	int result(0);
	for (auto a = begin+1; a <= end; a++)
		result = result * 10 + *a - 48;
	return result;
}

Node* ExpTree::parse(ITER begin, ITER end)
{
	Node *root = nullptr;
	auto it = begin;
	while (*(begin+1) == '(' && *end == ')')	//假如恰好是一对括号括起 则去掉最外层括号
	{
		begin++; end--;
	}
	for (it = end; it != begin;it--)			//遍历查找加减法
	{
		switch (*it)
		{
		case ')': skip(it); break;
		case '+': root = new Node(PLUS); break;
		case '-': root = new Node(MINUS); break;
		default:break;
		}
		if (root) break;
	}
	if (!root)
	{
		for (it = end; it != begin; it--)
		{
			switch (*it)
			{
			case ')': skip(it);  break;
			case '*': root = new Node(MULTI); break;
			case '/': root = new Node(DIVI); break;
			default:break;
			}
			if (root)break;
		}
	}
	if (root)
	{
		root->_left = parse(begin, it - 1);
		root->_right = parse(it, end);
	}
	else
	{
		root = new Node(convertToInt(begin, end));
	}
	return root;
}

void ExpTree::printLDR(Node* root)	//中序输出
{
	if (root->_data >= 0)	//如果是数字则直接输出
	{
		cout << root->_data; 
		return;
	}
	int lnext = root->_left->_data, rnext = root->_right->_data;
	switch (root->_data)
	{
	case PLUS:		//加法直接输出
		printLDR(root->_left);
		cout << '+';
		printLDR(root->_right); return;
	case MINUS:	
		printLDR(root->_left);
		cout << '-';
		if (rnext == PLUS || rnext == MINUS)//后方为减法则括号输出
		{
			L; printLDR(root->_right); R;
		}
		else printLDR(root->_right);
		return;
	case MULTI: case DIVI:
		if (lnext == PLUS || lnext == MINUS)//前方为加减法括号输出
		{
			L; printLDR(root->_left); R;
		}
		else printLDR(root->_left);
		cout << (root->_data == MULTI ? "*" : "/");
		if (rnext == PLUS || rnext == MINUS || (root->_data == DIVI && rnext == DIVI))
		{
			L; printLDR(root->_right); R;
		}
		else printLDR(root->_right);
		return;
	default:
		break;
	}
}

void ExpTree::printDLR(Node* root)
{
	int data(root->_data);
	if (data >= 0)
	{
		if (data >= 10)
		{
			L; cout << data; R;
		}
		else cout << data;
		return;
	}
	switch (data)
	{
	case PLUS:	cout << '+'; break;
	case MINUS:	cout << '-'; break;
	case MULTI:	cout << '*'; break;
	case DIVI:	cout << '/'; break;
	default:
		break;
	}
	printDLR(root->_left);
	printDLR(root->_right);
}

void ExpTree::printLRD(Node* root)
{
	int data(root->_data);
	if (data >= 0)
	{
		if (data >= 10)
		{
			L; cout << data; R;
		}
		else cout << data;
		return;
	}
	printLRD(root->_left);
	printLRD(root->_right);
	switch (data)
	{
	case PLUS:	cout << '+'; break;
	case MINUS:	cout << '-'; break;
	case MULTI:	cout << '*'; break;
	case DIVI:	cout << '/'; break;
	default:break;
	}
	return;
}

int main()
{
	ExpTree exptree;
	cout << "请输入表达式:\t\t";
	string a;
	cin >> a;
	aa += a;
	exptree.setRoot(exptree.parse(aa.begin(), aa.end()-1));
	cout << endl << "波兰表达式:\t\t";
	exptree.printDLR();
	cout << "中缀表达式:\t\t";
	exptree.printLDR();
	cout << "逆波兰表达式:\t\t";
	exptree.printLRD();
	system("pause");
	return 0;
}