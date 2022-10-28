#include <iostream>
#include "window.hpp"
#include "menuview.hpp"
#include "gamemodel.hpp"

using namespace std;
using namespace stf;

class Game : public Window
{
    GameModel gameModel = GameModel();
    MenuView menuView = MenuView(&gameModel);
    IView *currentView = &menuView;
public:

    bool onUpdate(const float) final
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
