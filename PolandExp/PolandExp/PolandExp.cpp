#include "PolandExp.h"

void ExpTree::skip(ITER it)	//跳过括号
{
	int cnt(1);	//记录括号层数
	while (cnt)
	{
		it++;
		if (*it == '(') cnt++;
		else if (*it == ')') cnt--;
	}
	it++;
}

int ExpTree::convertToInt(ITER begin, ITER end)
{
	int result(0);
	for (auto a = begin; a != end; a++)
		result = result * 10 + *a - 48;
	return result;
}

Node* ExpTree::prase(ITER begin, ITER end)
{
	Node *root = nullptr;
	auto it = begin;
	while (*begin == '(' && *(end - 1) == ')')	//假如恰好是一对括号括起 则去掉最外层括号
	{
		begin++; end--;
	}
	for (it = begin; it != end;it++)
	{
		switch (*it)
		{
		case '(': skip(it); break;
		case '+': root = new Node(PLUS); break;
		case '-': root = new Node(MINUS); break;
		default:break;
		}
	}
	if (!root)
	{
		for (it = begin; it != end; it++)
		{
			switch (*it)
			{
			case '(': skip(it);  break;
			case '*': root = new Node(PLUS); break;
			case '/': root = new Node(MINUS); break;
			default:break;
			}
		}
	}
	if (root)
	{
		root->_left = prase(begin, it);
		root->_right = prase(it + 1, end);
	}
	else
	{
		root = new Node(convertToInt(begin, end));
	}
	return root;
}