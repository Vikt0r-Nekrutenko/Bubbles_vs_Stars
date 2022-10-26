#include <iostream>
#include "window.hpp"
#include "gameview.hpp"

using namespace std;
using namespace stf;

class Game : public Window
{
    GameModel gameModel = GameModel();
    GameView gameView = GameView(&gameModel);
    IView *currentView = &gameView;
public:

    bool onUpdate(const float dt) final
    {
        currentView->show(renderer);
        return true;
    }

    void keyEvents(const int key) final
    {
        currentView = currentView->keyEventsHandler(key);
    }

    void mouseEvents(const MouseRecord &mr) final
    {
        currentView = currentView->mouseEventsHandler(mr);
    }
};

int main()
{
    return Game().run();
}
