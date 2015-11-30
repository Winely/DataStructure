// 1452764 何冬怡
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
	void printData();	//输出单条信息
	DATA* readData();
private:
	int _number;		//准考证号
	int _age;			//年龄
	bool _isMale;		//性别
	string _name;		//姓名
	string _ideal;		//志愿
	DATA *_next, *_pre;
};

class EDULIST: public DATA{
public:
	EDULIST();
	//~EDULIST();
	bool empty(){ return !(_num); }
	void startUP();
	void print();					//输出全表单
	void push_back();
	DATA* getDataByNum(int num);	//索引
	void insert(int, DATA*);		//插入
	void insert();
	void insertFirst(DATA*);
	void remove(DATA*);				//删除
	void remove();
	void count();					//统计
	void find();					//查找
	DATA* find(int num);
	void set();						//设置
private:
	int _num;						//储存信息的条数
	DATA *head, *end;				//链表头尾
};