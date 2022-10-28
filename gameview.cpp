#include "gameview.hpp"

Vec2d pzero{0,0};

auto cell = [](const Sprite& board, const GameModel *gameModel, const Vec2d pos) -> const Vec2d {
    return pzero + board.markers().at(gameModel->Size.x * pos.y + pos.x + 1);
};

auto cell1 = [](const Sprite& board, size_t i) -> const Vec2d {
    return pzero + board.markers().at(i + 1);
};

auto drawCell = [](Renderer &renderer, const Vec2d pos, uint8_t sym) -> void {
    if(sym != EMPTY_CELL)
        renderer.drawPixel(pos, sym);
};

GameView::GameView(BaseModel *model)
    : IView(model) {}

void GameView::drawPlayersScore(Renderer &renderer, GameModel *gameModel) const
{
    renderer.draw(pzero - Vec2d(-2, +2), "Player '%c': %d", PLAYER1_CELL, gameModel->plOneScore());
    renderer.draw(pzero + Vec2d(+21, -2), "Player '%c': %d", PLAYER2_CELL, gameModel->plTwoScore());
}

void GameView::drawPossibleMovesList(Renderer &renderer, GameModel *gameModel) const
{
    int j = 2;
    for(auto &i : gameModel->possibleMoves) {
        renderer.draw({0,j++}, "%c:%d->%c:%d", 'a'+i.first.x, i.first.y, 'a'+i.second.x, i.second.y);
    }
}

void GameView::drawPossibleNextMove(Renderer &renderer, GameModel *gameModel) const
{
    Vec2d destPos = gameModel->cursor().destinationCell.pos;

    for(int y = destPos.y - 2; y < destPos.y + 3; ++y)
        for(int x = destPos.x - 2; x < destPos.x + 3; ++x) {
            if(x >= 0 && y >= 0 && x < gameModel->Size.x && y < gameModel->Size.y)
                if(gameModel->cursor().destinationCell.sym != 'e') {
                    renderer.drawPixel(cell(m_board, gameModel, {x,y}), '.');
                }
        }
}

void GameView::show(Renderer &renderer)
{
    m_board.show(renderer, true);
    pzero = renderer.Size / 2 - m_board.Size() / 2;

    GameModel *gameModel = static_cast<GameModel*>(m_model);
    Vec2d cursorPos = gameModel->cursor().selectorCell.pos;
    Vec2d destPos = gameModel->cursor().destinationCell.pos;

    renderer.drawPixel(pzero + m_board.markers().at(0), gameModel->player());

    drawPlayersScore(renderer, gameModel);
    drawPossibleMovesList(renderer, gameModel);
    drawPossibleNextMove(renderer, gameModel);

    // draw board
    for(size_t i = 0; i < size_t(gameModel->Size.x * gameModel->Size.y); ++i) {
        drawCell(renderer, cell1(m_board, i), gameModel->board()[i]);
    }

    // draw cursors
    if(gameModel->cursor().destinationCell.sym != EMPTY_CELL) {
        renderer.drawPixel(cell(m_board, gameModel, destPos)-Vec2d(1,0), '-');
        renderer.drawPixel(cell(m_board, gameModel, destPos)+Vec2d(1,0), '-');
    }

    renderer.drawPixel(cell(m_board, gameModel, cursorPos)-Vec2d(1,0), '+');
    renderer.drawPixel(cell(m_board, gameModel, cursorPos)+Vec2d(1,0), '+');

    drawCell(renderer, cell(m_board, gameModel, cursorPos), gameModel->cursor().selectorCell.sym);
}

IView *GameView::mouseEventsHandler(const MouseRecord &mr)
{
    Vec2d mp(mr.x, mr.y);
    Vec2d dif = (m_board.Size()-1) / 8;
    Vec2d pos = (mp - pzero) / dif - Vec2d(1,1);

    static_cast<GameModel*>(m_model)->setCursorPosition(pos);
    return m_model->mouseEventsHandler(this, mr);
}
