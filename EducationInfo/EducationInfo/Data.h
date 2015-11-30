// 1452764 �ζ���
#include <iostream>
#include <string>
using namespace std;

class EDULIST;

class DATA {
	friend class EDULIST;
public:
	DATA();
	//~DATA();
	DATA(int num, string name, bool isMale, int age, string ideal): 
		_number(num),_name(name), _age(age), _isMale(isMale), _ideal(ideal), _next(nullptr), _pre(nullptr){}
	void set(int num, int age, bool isMale, string name, string ideal);
	void printData();	//���������Ϣ
	DATA* readData();
private:
	int _number;		//׼��֤��
	int _age;			//����
	bool _isMale;		//�Ա�
	string _name;		//����
	string _ideal;		//־Ը
	DATA *_next, *_pre;
};

class EDULIST: public DATA{
public:
	EDULIST();
	//~EDULIST();
	bool empty(){ return !(_num); }
	void startUP();
	void print();					//���ȫ��
	void push_back();
	DATA* getDataByNum(int num);	//����
	void insert(int, DATA*);		//����
	void insert();
	void insertFirst(DATA*);
	void remove(DATA*);				//ɾ��
	void remove();
	void count();					//ͳ��
	void find();					//����
	DATA* find(int num);
	void set();						//����
private:
	int _num;						//������Ϣ������
	DATA *head, *end;				//����ͷβ
};