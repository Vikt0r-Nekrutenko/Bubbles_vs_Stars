#include <iostream>
#include "window.hpp"
#include "gameview.hpp"

using namespace std;
using namespace stf;

class Game : public Window
{
    GameModel gameModel = GameModel();
    GameView gameView = GameView(&gameModel);
public:

    bool onUpdate(const float dt) final
    {
        gameView.show(renderer);
        return true;
    }

    void keyEvents(const int key) final
    {
        gameView.keyEventsHandler(key);
    }

    void mouseEvents(const MouseRecord &mr) final
    {
        gameView.mouseEventsHandler(mr);
    }
};

int main()
{
    return Game().run();
}
