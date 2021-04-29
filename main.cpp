#include <iostream>
#include <string>
#include "tview.h"
#include "view.h"
#include "model.h"
#include "controller.h"
#include "ai_controller.h"

using namespace std;
using namespace std::placeholders;

class Quiter
{
public:
	Quiter(View* myv)
	{
		v = myv;
		v->onkey(bind(&Quiter::key_pressed, this, _1));
	}
	void key_pressed(int key)
	{
		if (key == 'q')
		{
			v->quit();
		}
	}
	View* v;
};

int main() {
	Tview v;
	Model m(&v);
	KeyController c (&m.get_snakes().front(), &v);
	AiController ai (&v, &m.create_snake(), &m);
	Quiter q(&v);
	v.show();
	for (auto& rabbit : m.get_rabbits())
	{
		v.paint(rabbit.get_coord());
	}
	int i = 0;
	for (auto& snake : m.get_snakes())
	{
		DrawSnake draw_snake;
		draw_snake.body = snake.get_body();
		draw_snake.direct = snake.get_direct();
		draw_snake.color = i;
		i++;
		v.paint(draw_snake);
	}
	v.runloop();
	getchar();
	return 0;
}
