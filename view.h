#pragma once

#include "model.h"
#include <functional>

using timer_fn = function<void(void)>;
using key_fn = function<void(int)>;

struct DrawUpdateSnake
{
	Coord head;
	Coord tail;
	Coord body;
	Direction direct;
	int color;
	bool is_tail;
};

struct DrawSnake
{
	list<Coord> body;
	Direction direct;
	int color;
};

class View
{
public:
	View(){}
	virtual void show(void) = 0;
	virtual void paint(const Coord& r) = 0;//rabbit
	virtual void paint(const DrawSnake& s) = 0;//snake
	virtual void paint(const DrawUpdateSnake& s) = 0;
	virtual int get_col() = 0;
	virtual int get_row() = 0;
	virtual void ontimer(const timer_fn, int time) = 0;
	virtual void onkey(const key_fn) = 0;
	virtual void runloop() = 0;
	virtual void quit() = 0;
	//virtual void you_lose() = 0;
};
