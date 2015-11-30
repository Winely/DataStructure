#include <iostream>
using namespace std;
class Player{
public:
	Player(){ _alive = true; }
	Player(int position) :_pos(position), _alive(true), _next(nullptr){}
	Player* next(){ return _next; }
	void setNext(Player* p){ _next = p; };
	void die(){ _alive = false; }
	void setpos(int position){ _pos = position; }
	int getpos(){ return _pos; }
	bool isAlive(){ return _alive; }
private:
	int _pos;
	bool _alive;
	Player* _next;
};

class PlayerList{
public:
	PlayerList();
	PlayerList(int num);
	void startGame(int start, int gaps, int k);
	void printAlive();
private:
	Player *head;
	int number;
};
