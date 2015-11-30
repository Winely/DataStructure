#include "Data.h"

int amount(0);
//��ȫ����Ϣ���б༭
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
		<< (_isMale?"��":"Ů") << '\t'
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
	isMale = sex.compare("��") == 0 ? true : false;
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
	cout << "��������������λ�ã�";
	cin >> pos;
	cout << "����������Ҫ����Ŀ������ţ��������Ա����估�������" << endl;
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
	if (pos >= _num - 1)		//��β�����
	{
		end->_next = data;
		data->_pre = end;
		end = data;
		return;
	}
	auto p = getDataByNum(pos);
	if (p == head) head = data;	//��ͷ�����
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
	cout << "������Ҫɾ���Ŀ������ţ�";
	cin >> target;
	auto p = find(target);
	if (!p) return;
	cout << "��Ҫɾ���Ŀ�����Ϣ�ǣ�";
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
	cout << "����" << iMale << "�����Կ�����" << _num - iMale << "��Ů�Կ������ϼ�" << _num << "����" << endl;
	return;
}

DATA* EDULIST::find(int num)
{
	for (auto p = head; p; p = p->_next)
	{
		if (p->_number == num) return p;
	}
	cout << "�Ҳ�������" << endl;
	return nullptr;
}

void EDULIST::find()
{
	cout << "�����뿼���ţ�";
	int num(0);
	cin >> num;
	auto p = find(num);
	if (p!=nullptr)
	{
		cout << "����\t����\t�Ա�\t����\t�������" << endl;
		p->printData();
	}
	return;
}

void EDULIST::print()
{
	cout << "����\t����\t�Ա�\t����\t�������" << endl;
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
		cout << "��������Ҫ�޸ĵĿ����ţ�";
		cin >> num;
		p = find(num);
	}
	p->printData();
	cout << "�޸Ŀ�����ѡ1���޸�������ѡ2���޸��Ա���ѡ3���޸�������ѡ4���޸ı��������ѡ5��ȡ����ѡ0" << endl;
	int operation(0);
	cin >> operation;
	string isMale;
	switch (operation)
	{
	case 0: return;
	case 1:cout << "����ѿ���" << p->_number << "�޸�Ϊ��";
		cin >> p->_number;		break;
	case 2:cout << "���������" << p->_name << "�޸�Ϊ��";
		cin >> p->_name;		break;
	case 3:cout << "������Ա��޸�Ϊ��";
		cin >> isMale;
		p->_isMale = (isMale.compare("��") == 0) ? true : false;
		break;
	case 4:cout << "���������" << p->_age << "�޸�Ϊ��";
		cin >> p->_age;			break;
	case 5:cout << "����ѱ������" << p->_ideal << "�޸�Ϊ��";
		cin >> p->_ideal;		break;
	default:cout << "�Ƿ����룬������ȡ����" << endl;
		break;
	}
	cout << "�޸ĳɹ�����ǰ������ϢΪ" << endl;
	p->printData();
}

void EDULIST::startUP()
{
	int operation;
	if (empty())
	{
		cout << "���Ƚ���������Ϣϵͳ��" << endl;
		cout << "�����뿼������:";
		cin >> amount;
		cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
		while (amount--) push_back();
		cout << endl;
		print();
	}
	cout << "��ѡ����Ĳ�������1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�6Ϊ��ӡȫ��0Ϊȡ���������˳���\n" << endl;
	cout << "��ѡ�����Ĳ�����";
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
		default: cout << "�Ƿ����룡" << endl; 
			break;
		}
		cout << "��ѡ����Ĳ�������1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�6Ϊ��ӡȫ��0Ϊȡ���������˳���\n" << endl;
		cout << "��ѡ�����Ĳ�����";
	}
}

int main()
{
	auto edulist = EDULIST();
	edulist.startUP();
	return 0;
}