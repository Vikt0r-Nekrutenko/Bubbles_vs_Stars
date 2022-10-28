#include "gamemodel.hpp"
#include "endview.hpp"
#include "pausemenuview.hpp"

GameModel::GameModel()
{
    reset();
}

void GameModel::reset()
{
    for(uint8_t &c : m_board) {
        c = EMPTY_CELL;
    }

    m_board[9] = PLAYER1_CELL;
    m_board[54] = PLAYER2_CELL;

    m_cursor = Cursor();
    m_player = PLAYER1_CELL;

    gameIsOver();
}

void GameModel::setCursorPosition(const Vec2d &pos)
{
    if(pos.x >= 0 && pos.y >= 0 && pos.x < Size.x && pos.y < Size.y) {
        m_cursor.selectorCell.pos = pos;
    }
}

void GameModel::calculateScore()
{
    m_plOneScore = m_plTwoScore = 0;

    for(auto i : m_board) {
        if(i == PLAYER1_CELL)
            ++m_plOneScore;
        else if(i == PLAYER2_CELL)
            ++m_plTwoScore;
    }
}

bool GameModel::gameIsOver()
{
    possibleMoves.clear();

    for(int y1 = 0; y1 < Size.y; ++y1) {
        for(int x1 = 0; x1 < Size.x; ++x1) {
            if(m_board[Size.x * y1 + x1] != m_player || m_board[Size.x * y1 + x1] == 'e')
                continue;
            for(int y2 = y1-2; y2 < y1 + 3; ++y2) {
                for(int x2 = x1-2; x2 < x1 + 3; ++x2) {
                    if(x2 < 0 || y2 < 0 || x2 >= Size.x || y2 >= Size.y)
                        continue;
                    if(m_board[Size.x * y2 + x2] == 'e')
                        possibleMoves.push_back({{x1,y1},{x2,y2}});
                }
            }
        }
    }
    return possibleMoves.empty();
}

IView *GameModel::put(IView *sender)
{
    Selector &sc = m_cursor.selectorCell;
    Selector &dc = m_cursor.destinationCell;

    if(getCell(sc.pos) == m_player)
    {
        sc.sym = dc.sym = m_player;
        dc.pos = sc.pos;
    }
    else if(sc.sym == m_player && getCell(sc.pos) == EMPTY_CELL && sc.pos.diff(dc.pos) <= 2.9f)
    {
        getCell(sc.pos) = m_player;
        for(int y = sc.pos.y - 1; y < sc.pos.y + 2; ++y)
            for(int x = sc.pos.x - 1; x < sc.pos.x + 2; ++x) {
                if(x < 0 && y < 0 && x >= Size.x && y >= Size.y)
                    break;
                if(getCell({x,y}) == opponent())
                    m_board[Size.x * y + x] = m_player;
            }
        sc.sym = dc.sym = EMPTY_CELL;
        m_player == PLAYER1_CELL ? m_player = PLAYER2_CELL : m_player = PLAYER1_CELL;
        calculateScore();
        if(gameIsOver())
            return new EndView(this);
    }

    return sender;
}

IView *GameModel::keyEventsHandler(IView *sender, const int key)
{
    switch (key)
    {
    case 'w': if(m_cursor.selectorCell.pos.y > 0) m_cursor.selectorCell.pos -= Vec2d(0,1); break;
    case 'a': if(m_cursor.selectorCell.pos.x > 0) m_cursor.selectorCell.pos -= Vec2d(1,0); break;
    case 's': if(m_cursor.selectorCell.pos.y < Size.y-1) m_cursor.selectorCell.pos += Vec2d(0,1); break;
    case 'd': if(m_cursor.selectorCell.pos.x < Size.x-1) m_cursor.selectorCell.pos += Vec2d(1,0); break;
    case 'q': return new PauseMenuView(this);
    case 'x': discardSelect(); break;
    case ' ': return put(sender);
    }
    return sender;
}

IView *GameModel::mouseEventsHandler(IView *sender, const MouseRecord &mr) {
    if(mr.type == MouseInputType::leftPressed) {
        return put(sender);
    }
    return sender;
}
