#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include "imodel.hpp"
#include "vec2d.hpp"
#include <vector>

using namespace stf;
using namespace stf::smv;

#define EMPTY_CELL 'e'
#define PLAYER1_CELL 'o'
#define PLAYER2_CELL '*'

struct Selector
{
    Vec2d pos { 0, 0 };
    uint8_t sym = EMPTY_CELL;
};

struct Cursor
{
    Selector selectorCell;
    Selector destinationCell;
};

class GameModel : public BaseModel
{

public:
    const Vec2d Size { 8, 8 };

    GameModel();

    void reset();
    void setCursorPosition(const Vec2d& pos);
    void calculateScore();

    inline const Cursor& cursor() const { return m_cursor; }
    inline const uint8_t& player() const { return m_player; }
    inline const uint8_t* board() const { return m_board; }
    inline uint8_t& getCell(const Vec2d& pos) { return m_board[Size.x * pos.y + pos.x]; }
    inline uint8_t opponent() const { return m_player == PLAYER1_CELL ? PLAYER2_CELL : PLAYER1_CELL; }
    inline uint8_t plOneScore() const { return m_plOneScore; }
    inline uint8_t plTwoScore() const { return m_plTwoScore; }
    inline bool isDraw() const { return m_plOneScore == m_plTwoScore; }
    inline void discardSelect() { m_cursor.selectorCell.sym = m_cursor.destinationCell.sym = EMPTY_CELL; }

    std::vector<std::pair<Vec2d,Vec2d>> possibleMoves;

    bool gameIsOver();

    IView* put(IView* sender);


    IView* keyEventsHandler(IView* sender, const int key) final;

    IView* mouseEventsHandler(IView* sender, const MouseRecord& mr) final;

private:

    uint8_t m_board[64];

    Cursor m_cursor;
    uint8_t m_player;
    uint8_t m_plOneScore = 1;
    uint8_t m_plTwoScore = 1;
};

#endif // GAMEMODEL_HPP
