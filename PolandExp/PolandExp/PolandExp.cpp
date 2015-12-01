#include "PolandExp.h"

void ExpTree::skip(ITER &it)	//��������
{
	int cnt(1);	//��¼���Ų���
	while (cnt)
	{
		it++;
		if (*it == '(') cnt++;
		else if (*it == ')') cnt--;
	}
}

int ExpTree::convertToInt(ITER begin, ITER end)
{
	int result(0);
	for (auto a = begin; a != end; a++)
		result = result * 10 + *a - 48;
	return result;
}

Node* ExpTree::parse(ITER begin, ITER end)
{
	Node *root = nullptr;
	auto it = begin;
	while (*begin == '(' && *(end - 1) == ')')	//����ǡ����һ���������� ��ȥ�����������
	{
		begin++; end--;
	}
	for (it = begin; it != end;it++)			//�������ҼӼ���
	{
		switch (*it)
		{
		case '(': skip(it); break;
		case '+': root = new Node(PLUS); break;
		case '-': root = new Node(MINUS); break;
		default:break;
		}
		if (root) break;
	}
	if (!root)
	{
		for (it = begin; it != end; it++)
		{
			switch (*it)
			{
			case '(': skip(it);  break;
			case '*': root = new Node(MULTI); break;
			case '/': root = new Node(DIVI); break;
			default:break;
			}
			if (root)break;
		}
	}
	if (root)
	{
		root->_left = parse(begin, it);
		root->_right = parse(it + 1, end);
	}
	else
	{
		root = new Node(convertToInt(begin, end));
	}
	return root;
}

void ExpTree::printLDR(Node* root)
{
	if (root->_data >= 0)	//�����������ֱ�����
	{
		cout << root->_data; 
		return;
	}
	switch (root->_data)
	{
	case PLUS: case MINUS:	//�Ӽ�����಻�������
		printLDR(root->_left);
		cout << ((root->_data == PLUS) ? "+" : "-");
		printLDR(root->_right);
		return;
	case MULTI: case DIVI:	//�˳�������Ҫ������
		if (root->_left->_data == PLUS || root->_left->_data == MINUS)
		{
			cout << "(";
			printLDR(root->_left);
			cout << ")";
		}
		else printLDR(root->_left);
		cout << ((root->_data == MULTI) ? "*" : "/");
		if (root->_right->_data == PLUS || root->_right->_data == MINUS)
		{
			cout << "(";
			printLDR(root->_right);
			cout << ")";
		}
		else printLDR(root->_right);
		return;
	default:
		break;
	}
}

int main()
{
	ExpTree exptree;
	cout << "Please input the expression: \t";
	cin >> aa;
	exptree.setRoot(exptree.parse(aa.begin(), aa.end()));
	cout << "The expression is:\t\t";
	exptree.printLDR();
	system("pause");
	return 0;
}