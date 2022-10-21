#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include "iview.hpp"
#include "sprite.hpp"

using namespace stf;
using namespace stf::smv;

class GameView : public IView
{
public:
    GameView(BaseModel *model);
    virtual void show(Renderer &renderer)
    {
        m_board.show(renderer, true);
    }

private:
    Sprite m_board = Sprite("sprs/sboard.spr");
};

#endif // GAMEVIEW_HPP
