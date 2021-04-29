#pragma once
#include <iterator>
#include <ctime>
#include <iostream>
#include <list>
#include <unistd.h>
using namespace std;
class View;
struct Coord
{
	int x;
	int y;
};
class Rabbit
{
public:
	Rabbit(int x, int y);
	Coord get_coord() const;
private:
	Coord c;
};
enum Direction {LEFT, RIGHT, UP, DOWN};
class Snake
{
public:
	Snake();
	Snake(Coord begin, int len, int style);
	list<Coord> get_body() const;
	Coord get_head() const;
	Coord get_tail() const;
	int get_style() const;
	Direction get_direct() const;
	void set_direct(Direction direct);
	void erase_tail();
	void push_cell(Coord c);
	void inc_dec_head(string flag, char obj);
	void inc_dec_tail(string flag, char obj);
private:
	list<Coord> body;
	Coord head;
	Direction direct;
	int style;
};
class Model
{
public:
	Model(View* myview);
	list<Rabbit>& get_rabbits();
	list<Snake>& get_snakes();
	void tick();
	Snake& create_snake();
private:
	View* view;
	list<Rabbit> rabbits; 
	list<Snake> snakes;
	void updatestate(Snake& s);
	void updatestate(list<Rabbit>& r);
	list<Rabbit>::const_iterator find_rabbit(Coord coord);
};
