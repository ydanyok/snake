#pragma once

#include <termios.h>
#include <poll.h>
#include <string>
#include <cstdio>
#include <functional>
#include <signal.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/ioctl.h>
#include "view.h"
using namespace std;
class Tview : public View
{
public:
	Tview();
	~Tview();
	void show();
	void paint(const Coord& r);//rabbit
    void paint(const DrawSnake& s);//snake
    void paint(const DrawUpdateSnake& s);
	int get_row();
	int get_col();
	void ontimer(const timer_fn, int time);
	void onkey(const key_fn);
	void runloop();
	void quit();
        //void you_lose();

private:
	bool finished;
	int row;
	int col;
	struct termios old;
	list<key_fn> pressed;
	pair<timer_fn, int> timer;
	static function<void(void)> onwinch;
	static void winch(int n);
	void draw_set_winsize();
	void draw_set_color(string color);
	void draw_default_color();
	void draw_string(int x, int y, string str);
	void draw_v_line(int x, int y, int len);
	void draw_g_line(int x, int y, int len);
	void draw_frame();
	void draw_go_to(int x, int y);
	void draw_clear_all();
};
