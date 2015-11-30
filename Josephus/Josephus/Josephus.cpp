#include "Josephus.h"

PlayerList::PlayerList(int num)
{
	number = num;
	head = new Player[num];		//用一个数组储存节点类
	for (int i = 0; i < num; i++)
	{
		head[i].setpos(i + 1);
		if (i != num - 1)head[i].setNext(head + i + 1);
		else head[i].setNext(head);	//最末的节点指向头节点
	}
}

void PlayerList::printAlive()
{
	cout << "剩余的生者位置是：";
	for (int i = 0; i < number; i++)	//直接通过数组下标遍历所有player
	{
		if (head[i].isAlive()) cout << '\t' << i + 1;
	}
	cout << endl;
	return;
}

void PlayerList::startGame(int start, int gaps, int k)
{
	int g = gaps, alive = number;
	auto p = head + start - 1;
	for (p = head; p->next()->getpos() != start; p = p->next());
	while (alive>k && alive>0)
	{
		for (g = gaps-1; g > 0; g--) 
			p = p->next();
		auto temp = p->next();
		p->next()->die();
		p->setNext(p->next()->next());
		p = temp;
		alive--;
		cout << "第" << number - alive << "个死者的位置是：\t" << p->getpos() << endl;
	}
	cout << endl;
	cout << "最后剩下" << alive << "个人" << endl;
	printAlive();

}

int main()
{
	int number, start, gaps, k;
	cout << "请输入生死游戏的总人数：";
	cin >> number;
	cout << "请输入游戏开始的位置：\t";
	cin >> start;
	cout << "请输入死亡数字M：\t";
	cin >> gaps;
	cout << "请输入剩余的生者人数K：\t";
	cin >> k;
	auto playerList = PlayerList(number);
	playerList.startGame(start, gaps, k);
	system("pause");
	return 0;
}