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
    void show(Renderer &renderer) override
    {
        m_board.show(renderer, true);
        pzero = renderer.Size / 2 - m_board.Size() / 2;

        GameModel *gameModel = static_cast<GameModel*>(m_model);
        Vec2d cursorPos = gameModel->cursor().selectorCell.pos;
        Vec2d destPos = gameModel->cursor().destinationCell.pos;

        auto cell = [&](const Vec2d pos) -> const Vec2d {
            int n = gameModel->Size.x * pos.y + pos.x + 1;
            if(n < 0 || n >= (int)m_board.markers().size())
                return {-1,-1};
          return pzero + m_board.markers().at(n);
        };

        auto cell1 = [&](size_t i) -> const Vec2d {
          return pzero + m_board.markers().at(i + 1);
        };

        auto drawCell = [&](const Vec2d pos, uint8_t sym) -> void {
            if(sym != EMPTY_CELL)
                renderer.drawPixel(pos, sym);
        };

        renderer.drawPixel(pzero + m_board.markers().at(0), gameModel->player());
        renderer.draw(pzero - Vec2d(-2, +2), "Player '%c': %d", PLAYER1_CELL, gameModel->plOneScore());
        renderer.draw(pzero + Vec2d(+21, -2), "Player '%c': %d", PLAYER2_CELL, gameModel->plTwoScore());

        int j = 2;
        for(auto &i : gameModel->possibleMoves) {
            renderer.draw({0,j++}, "%c:%d->%c:%d", 'a'+i.first.x, i.first.y, 'a'+i.second.x, i.second.y);
        }

        for(int y = destPos.y - 2; y < destPos.y + 3; ++y)
            for(int x = destPos.x - 2; x < destPos.x + 3; ++x) {
                if(x >= 0 && y >= 0 && x < gameModel->Size.x && y < gameModel->Size.y)
                    if(gameModel->cursor().destinationCell.sym != 'e') {
                        renderer.drawPixel(cell({x,y}), '.');
                    }
            }

        for(size_t i = 0; i < size_t(gameModel->Size.x * gameModel->Size.y); ++i) {
          drawCell(cell1(i), gameModel->board()[i]);
        }

        renderer.drawPixel(cell(destPos)-Vec2d(1,0), '-');
        renderer.drawPixel(cell(destPos)+Vec2d(1,0), '-');

        renderer.drawPixel(cell(cursorPos)-Vec2d(1,0), '+');
        renderer.drawPixel(cell(cursorPos)+Vec2d(1,0), '+');

        drawCell(cell(cursorPos), gameModel->cursor().selectorCell.sym);
    }
    Vec2d pzero{0,0};
    IView* mouseEventsHandler(const stf::MouseRecord& mr) override
    {
        Vec2d mp(mr.x, mr.y);
        Vec2d dif = (m_board.Size()-1) / 8;
        Vec2d pos = (mp - pzero) / dif - Vec2d(1,1);

        static_cast<GameModel*>(m_model)->setCursorPosition(pos);
        return m_model->mouseEventsHandler(this, mr);
    }

private:
    Sprite m_board = Sprite("sprs/sboard.spr");
};

#endif // GAMEVIEW_HPP
