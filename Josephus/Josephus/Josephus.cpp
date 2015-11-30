#include "Josephus.h"

PlayerList::PlayerList(int num)
{
	number = num;
	head = new Player[num];		//��һ�����鴢��ڵ���
	for (int i = 0; i < num; i++)
	{
		head[i].setpos(i + 1);
		if (i != num - 1)head[i].setNext(head + i + 1);
		else head[i].setNext(head);	//��ĩ�Ľڵ�ָ��ͷ�ڵ�
	}
}

void PlayerList::printAlive()
{
	cout << "ʣ�������λ���ǣ�";
	for (int i = 0; i < number; i++)	//ֱ��ͨ�������±��������player
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
		cout << "��" << number - alive << "�����ߵ�λ���ǣ�\t" << p->getpos() << endl;
	}
	cout << endl;
	cout << "���ʣ��" << alive << "����" << endl;
	printAlive();

}

int main()
{
	int number, start, gaps, k;
	cout << "������������Ϸ����������";
	cin >> number;
	cout << "��������Ϸ��ʼ��λ�ã�\t";
	cin >> start;
	cout << "��������������M��\t";
	cin >> gaps;
	cout << "������ʣ�����������K��\t";
	cin >> k;
	auto playerList = PlayerList(number);
	playerList.startGame(start, gaps, k);
	system("pause");
	return 0;
}