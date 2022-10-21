#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include "iview.hpp"
#include "sprite.hpp"
#include "gamemodel.hpp"

using namespace stf;
using namespace stf::smv;

class GameView : public IView
{
public:
    GameView(BaseModel *model);
    virtual void show(Renderer &renderer)
    {
        m_board.show(renderer, true);
        Vec2d pzero = renderer.Size / 2 - m_board.Size() / 2;

        GameModel *gameModel = static_cast<GameModel*>(m_model);
        Vec2d cursorPos = gameModel->cursor().activeCursor->pos;

        auto cell = [&](const Vec2d pos) -> const Vec2d {
          return pzero + m_board.markers().at(gameModel->Size.x * pos.y + pos.x + 1);
        };

        auto cell1 = [&](size_t i) -> const Vec2d {
          return pzero + m_board.markers().at(i + 1);
        };

        auto drawCell = [&](const Vec2d pos, uint8_t sym) -> void {
            if(sym != 'e')
                renderer.drawPixel(pos, sym);
        };

        for(size_t i = 0; i < size_t(gameModel->Size.x * gameModel->Size.y); ++i) {
          drawCell(cell1(i), gameModel->board()[i]);
        }

//        renderer.drawFrame(cell(cursorPos) - Vec2d(1,0), Vec2d(3,1));
        renderer.drawPixel(cell(cursorPos)-Vec2d(1,0), '+');
        renderer.drawPixel(cell(cursorPos)+Vec2d(1,0), '+');
        drawCell(cell(cursorPos), gameModel->cursor().activeCursor->sym);
    }

private:
    Sprite m_board = Sprite("sprs/sboard.spr");
};

#endif // GAMEVIEW_HPP
