#include <iostream>
#include "window.hpp"
#include "sprite.hpp"

using namespace std;
using namespace stf;

class Game : public Window
{
    Sprite s = Sprite("sprs/sboard.spr");
public:

    bool onUpdate(const float dt) final
    {
        s.show(renderer, true);
        return true;
    }

    void keyEvents(const int key) final
    {

    }

    void mouseEvents(const MouseRecord &mr) final
    {

    }
};

int main()
{
    return Game().run();
}
