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
    GameView(BaseModel *model, bool resetTheModel = false);

    void drawPlayersScore(Renderer &renderer, GameModel *gameModel) const;
    void drawPossibleMovesList(Renderer &renderer, GameModel *gameModel) const;
    void drawPossibleNextMove(Renderer &renderer, GameModel *gameModel) const;
    void show(Renderer &renderer) override;

    IView* mouseEventsHandler(const stf::MouseRecord& mr) override;

private:
    Sprite m_board = Sprite("sprs/sboard.spr");
};

#endif // GAMEVIEW_HPP
