#include "tview.h"
#define ESC "\033"
using namespace std;
function<void(void)> Tview::onwinch;

Tview::Tview()
{
	struct termios termios_p;
	tcgetattr(0, &termios_p);
	old = termios_p;
	cfmakeraw(&termios_p);
	tcsetattr(0, TCSAFLUSH, &termios_p);
	draw_set_winsize();
	onwinch = bind(&Tview::show, this);
	signal(SIGWINCH, Tview::winch);
}

Tview::~Tview()
{
	tcsetattr(0, TCSAFLUSH, &old);
}

void Tview::runloop()
{
	struct pollfd fds[] = { {0, POLLIN, 0} };
	finished = false;
	int flag = 1;
	while(!finished)
	{
		int n = poll(fds, 1, timer.second * flag);
		flag = 1;
		if (n == 0)
		{
			timer.first();
		}
		else
		{
			flag = 0;
			char buf[1];
			read(0, buf, 1);
			for (auto f : pressed)
			{
				f(buf[0]);
			}
		}
	}
}

void Tview::quit()
{
	finished = true;
}

void Tview::ontimer(const timer_fn f, int time)
{
	timer.first = f;
	timer.second = time;
}

void Tview::onkey(const key_fn k)
{
	pressed.push_back(k);	
}

void Tview::draw_set_winsize()
{
	struct winsize win;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    col = win.ws_col;
    row = win.ws_row;
}
int Tview::get_row()
{
	return row;	
}
int Tview::get_col()
{
    return col;
}
void Tview::winch(int n)
{
	onwinch();
}
void Tview::draw_v_line(int x, int y, int len)
{
	draw_go_to(x, y);
	for (int i = y; i <= len + y; ++i)
	{
		draw_go_to(x, i);
		cout << "|";
	}
}
void Tview::draw_g_line(int x, int y, int len)
{
	draw_go_to(x, y);
	for (int i = x; i <= len + x; ++i)
	{
		draw_go_to(i, y);
		cout << "-";
	}
}
void Tview::draw_frame()
{
    draw_v_line(0, 0, row);
    draw_v_line(col, 0, row);
	draw_g_line(0, 0, col);
	draw_g_line(0, row, col);
    draw_string(0, 0, "+");
    draw_string(col, 0, "+");
    draw_string(col, row, "+");
    draw_string(0, row, "+");
}
void Tview::draw_string(int x, int y, string str)
{
	draw_go_to(x, y);
	cout << str;
}
void Tview::draw_go_to(int x, int y)
{
	printf(ESC "[%d;%dH", y, x);
}
void Tview::draw_clear_all()
{
	printf(ESC "[H");
	printf(ESC "[J");
}

static char* colors[] = { "r", "green", "y", "b", "gray"};

void Tview::draw_set_color(string color)
{
	if (color == "r")
	{
		printf(ESC "[31;1m");
	}
	else if (color == "green")
	{
		printf(ESC "[32;1m");
	}
    else if (color == "y")
    {
		printf(ESC "[33;1m");
    }
    else if (color == "b")
    {
		printf(ESC "[34;1m");
    }
    else if (color == "gray")
    {
		printf(ESC "[30;1m");
    }
}
void Tview::draw_default_color()
{
	printf(ESC "[0m");
}

void Tview::paint(const Coord& c)
{
	draw_set_color("b");
	draw_string(c.x, c.y, "*");
	draw_default_color();
}

void Tview::paint(const DrawSnake& s)
{
	draw_set_color(colors[s.color]);
	bool first = true;
	for (Coord c : s.body) 
	{
		if (!first)
		{
			draw_string(c.x, c.y, "o");
		}
		first = false;
	}
	Coord head = s.body.front();
	string arrow;
	arrow += "><^v"[s.direct];
	draw_string(head.x, head.y, arrow);
	draw_default_color();
}

void Tview::paint(const DrawUpdateSnake& s)
{
	draw_set_color(colors[s.color]);
    draw_string(s.body.x, s.body.y, "o");
	string arrow;
    arrow += "><^v"[s.direct];
    draw_string(s.head.x, s.head.y, arrow);
	if (s.is_tail)
	{
		draw_string(s.tail.x, s.tail.y, " ");
	}
	draw_default_color();
	draw_go_to(0,0);
}
/*void Tview::you_lose()
{
	draw_go_to(col/2, row/2);
	cout << "IDI NAXUI";
}*/
void Tview::show()
{
	setbuf(stdout, NULL);
	draw_clear_all();
	draw_set_winsize();
	draw_frame();
}

