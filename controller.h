#include "model.h"
#include "view.h"

using namespace std::placeholders;

class KeyController
{
public:
	KeyController(Snake* s_, View* v_):
		v(v_), s(s_)
	{
		v->onkey(bind(&KeyController::preset, this, _1));
	}
	void preset(int key)
	{
		Direction direct = s->get_direct();
		switch(key)
		{
			case 'A':
				if (direct != DOWN){
					s->set_direct(UP);
				}
				break;
			case 'B':
				if (direct != UP){
					s->set_direct(DOWN);
				}
				break;
			case 'C':
				if (direct != RIGHT){
					s->set_direct(LEFT);
				}
				break;
			case 'D':
				if (direct != LEFT){
					s->set_direct(RIGHT);
				}
				break;
		}
	}
private:
	View* v;
	Snake* s;
};
