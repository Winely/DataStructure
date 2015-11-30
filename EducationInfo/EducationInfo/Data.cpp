#include "Data.h"

int amount(0);
//对全条信息进行编辑
DATA::DATA() :DATA(0, "", true, 0, ""){ _next = nullptr;  _pre = nullptr; }

void DATA::set(int num, int age, bool isMale, string name, string ideal)
{
	_number = num;
	_age = age;
	_isMale = isMale;
	_name = name;
	_ideal = ideal;
}

void DATA::printData()
{
	cout << _number << '\t'
		<< _name << '\t'
		<< (_isMale?"男":"女") << '\t'
		<< _age << '\t'
		<< _ideal << endl;
}

DATA* DATA::readData()
{
	auto data = new DATA;
	int num, age;
	string sex, name, ideal;
	bool isMale;
	cin >> num >> name >> sex >> age >> ideal;
	isMale = sex.compare("男") == 0 ? true : false;
	data->set(num, age, isMale, name, ideal);
	return data;
}

EDULIST::EDULIST()
{
	_num = 0;
	head = nullptr;
	end = head;
}

DATA* EDULIST::getDataByNum(int pos)
{
	auto p = head;
	if (pos > _num-1) return end;
	for (p = head; pos; p = p->_next) pos--;
	return p;
}

void EDULIST::insertFirst(DATA* data)
{
	head = data;
	end = data;
	_num = 1;
}

void EDULIST::insert()
{
	int pos;
	cout << "请输入你想插入的位置：";
	cin >> pos;
	cout << "请依次输入要插入的考生考号，姓名，性别，年龄及报考类别：" << endl;
	insert(pos, readData());
	print();
	cout << endl;
	_num++;
	return;
}

void EDULIST::insert(int pos, DATA* data)
{
	if (empty())
	{
		insertFirst(data); return;
	}
	if (pos >= _num - 1)		//在尾部添加
	{
		end->_next = data;
		data->_pre = end;
		end = data;
		return;
	}
	auto p = getDataByNum(pos);
	if (p == head) head = data;	//在头部添加
	else p->_pre->_next = data;
	data->_next = p;
	data->_pre = p->_pre;
	p->_pre = data;
	return;
}

void EDULIST::remove(DATA* p)
{
	_num--;
	if (p == head) head = p->_next;
	else p->_pre->_next = p->_next;
	if (p == end) end = p->_pre;
	else p->_next->_pre = p->_pre;
	delete p;
	return;
}

void EDULIST::remove()
{
	int target;
	cout << "请输入要删除的考生考号：";
	cin >> target;
	auto p = find(target);
	if (!p) return;
	cout << "你要删除的考生信息是：";
	p->printData();
	remove(p);
	cout << endl;
	return;
}

void EDULIST::count()
{
	int iMale(0);
	for (auto p = head; p; p = p->_next)
	{
		if (p->_isMale) iMale++;
	}
	cout << "共有" << iMale << "名男性考生，" << _num - iMale << "名女性考生，合计" << _num << "名。" << endl;
	return;
}

DATA* EDULIST::find(int num)
{
	for (auto p = head; p; p = p->_next)
	{
		if (p->_number == num) return p;
	}
	cout << "找不到对象！" << endl;
	return nullptr;
}

void EDULIST::find()
{
	cout << "请输入考生号：";
	int num(0);
	cin >> num;
	auto p = find(num);
	if (p!=nullptr)
	{
		cout << "考号\t姓名\t性别\t年龄\t报考类别" << endl;
		p->printData();
	}
	return;
}

void EDULIST::print()
{
	cout << "考号\t姓名\t性别\t年龄\t报考类别" << endl;
	for (auto p = head; p; p = p->_next)
	{
		p->printData();
	}
}

void EDULIST::push_back()
{
	auto data = readData();
	if (empty())
	{
		insertFirst(data);
	}
	else
	{
		insert(_num++, data);
	}
	return;
}

void EDULIST::set()
{
	DATA* p = nullptr;
	int num;
	while (p == nullptr)
	{
		cout << "请输入想要修改的考生号：";
		cin >> num;
		p = find(num);
	}
	p->printData();
	cout << "修改考号请选1，修改姓名请选2，修改性别请选3，修改年龄请选4，修改报考类别请选5，取消请选0" << endl;
	int operation(0);
	cin >> operation;
	string isMale;
	switch (operation)
	{
	case 0: return;
	case 1:cout << "你想把考号" << p->_number << "修改为：";
		cin >> p->_number;		break;
	case 2:cout << "你想把姓名" << p->_name << "修改为：";
		cin >> p->_name;		break;
	case 3:cout << "你想把性别修改为：";
		cin >> isMale;
		p->_isMale = (isMale.compare("男") == 0) ? true : false;
		break;
	case 4:cout << "你想把年龄" << p->_age << "修改为：";
		cin >> p->_age;			break;
	case 5:cout << "你想把报考类别" << p->_ideal << "修改为：";
		cin >> p->_ideal;		break;
	default:cout << "非法输入，操作已取消。" << endl;
		break;
	}
	cout << "修改成功，当前考生信息为" << endl;
	p->printData();
}

void EDULIST::startUP()
{
	int operation;
	if (empty())
	{
		cout << "请先建立考生信息系统！" << endl;
		cout << "请输入考生人数:";
		cin >> amount;
		cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
		while (amount--) push_back();
		cout << endl;
		print();
	}
	cout << "请选择你的操作：（1为插入，2为删除，3为查找，4为修改，5为统计，6为打印全表，0为取消操作并退出）\n" << endl;
	cout << "请选择您的操作：";
	while (cin >> operation)
	{
		switch (operation)
		{
		case 0:	return;
		case 1: insert();	break;
		case 2: remove();	break;
		case 3: find();		break;
		case 4: set();		break;
		case 5: count();	break;
		case 6: print();	break;
		default: cout << "非法输入！" << endl; 
			break;
		}
		cout << "请选择你的操作：（1为插入，2为删除，3为查找，4为修改，5为统计，6为打印全表，0为取消操作并退出）\n" << endl;
		cout << "请选择您的操作：";
	}
}

int main()
{
	auto edulist = EDULIST();
	edulist.startUP();
	return 0;
}