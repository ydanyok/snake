#include "model.h"
#include "view.h"

using namespace std::placeholders;

class AiController
{
public:
	AiController(View* v_, Snake* s_, Model* m_):
		v(v_), s(s_), m(m_)
	{

	}
private:
    View* v;
    Snake* s;
	Model* m;
};
