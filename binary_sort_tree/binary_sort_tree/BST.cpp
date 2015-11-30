#include "BST.h"
#include <stack>

BSTNode* &BST::search(int x)
{
	auto p = _root;
	while (p && p->data() != x)
	{
		if (p->data() > x) p = p->left();
		else if (p->data() < x) p = p->right();
	}
	return p;
}

void BST::insert(int x)
{
	if (!_root) { _root = new BSTNode(x); return; }
	auto p = _root;
	while (p&&p->data() != x)
	{
		if (p->data()>x)
		{
			if (!p->left()){
				p->setleft(new BSTNode(x)); break;
			}
			else p = p->left();
		}
		else 
		{
			if (!p->right()){
				p->setright(new BSTNode(x)); break;
			}
			else p = p->right();
		}
	}
}

void BST::show(BSTNode* p)
{
	if (!p) return;
	show(p->left());
	cout << p->data()<<' ';
	show(p->right());
	return;
}

int main()
{
	BST bst;
	cout << "**                 Binary Sort Tree                **" << endl;
	cout << "=====================================================" << endl;
	cout << "**            1 --- Generate a tree                **" << endl;
	cout << "**            2 --- Insert a key                   **" << endl;
	cout << "**            3 --- Search a key                   **" << endl;
	cout << "**            4 --- Exit                           **" << endl;
	cout << "=====================================================" << endl;
	int select, num;
	while (1)
	{
		cout << "Please select:";
		cin.clear();
		cin.sync(); 
		cin >> select;
		switch (select)
		{
		case 1:
			cout << "Please input keys to generate a binary sort tree:" << endl;
			cin >> num;
			bst._root = new BSTNode(num);
			while (cin >> num) bst.insert(num);		//逐个插入节点
			cout << "Here is the new tree:" << endl;
			bst.show(bst._root);					//中序输出
			cout << endl << endl; break;
		case 2:
			cout << "Please input key:";
			cin >> num;
			bst.insert(num);
			cout << "Here is the new tree:" << endl;
			bst.show(bst._root);
			cout << endl << endl; break;
		case 3:
			cout << "Please input key:";
			cin >> num;
			if (bst.search(num)) cout << "Succeed in searching the key " << num << endl;
			else cout << "Failed searching the key " << num << endl; 
			cout << endl; break;
		case 4:return 0;
		default:cout << "Error selection. Please try again." << endl;
			break;
		}
	}
	return 0;
}