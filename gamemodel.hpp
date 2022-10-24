#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include "imodel.hpp"
#include "vec2d.hpp"

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

    GameModel()
    {
        reset();
    }

    void reset()
    {
        for(uint8_t &c : m_board) {
            c = EMPTY_CELL;
        }

        m_board[0] = PLAYER1_CELL;
        m_board[18] = PLAYER2_CELL;

        m_cursor = Cursor();
        m_player = PLAYER1_CELL;
    }

    inline const Cursor& cursor() const { return m_cursor; }
    inline const uint8_t& player() const { return m_player; }
    inline const uint8_t* board() const { return m_board; }
    inline uint8_t& getCell(const Vec2d& pos) { return m_board[Size.x * pos.y + pos.x]; }
    inline uint8_t opponent() const { return m_player == PLAYER1_CELL ? PLAYER2_CELL : PLAYER1_CELL; }

    IView* put(IView* sender)
    {
        Selector &sc = m_cursor.selectorCell;
        Selector &dc = m_cursor.destinationCell;

        if(getCell(sc.pos) == m_player)
        {
            sc.sym = dc.sym = m_player;
            dc.pos = sc.pos;
        }
        else if(sc.sym == m_player && getCell(sc.pos) == EMPTY_CELL && sc.pos.diff(dc.pos) <= 1.5f)
        {
            getCell(sc.pos) = m_player;
            for(int y = sc.pos.y - 1; y < sc.pos.y + 1; ++y)
                for(int x = sc.pos.x - 1; x < sc.pos.x + 1; ++x) {
                    if(x < 0 && y < 0 && x >= Size.x && y >= Size.y)
                        break;
                    if(getCell({x,y}) == opponent())
                        m_board[Size.x * y + x] = m_player;
                }
            sc.sym = dc.sym = EMPTY_CELL;
            m_player == PLAYER1_CELL ? m_player = PLAYER2_CELL : m_player = PLAYER1_CELL;
        }
        return sender;
    }


    IView* keyEventsHandler(IView* sender, const int key) final
    {
        switch (key)
        {
          case 'w': if(m_cursor.selectorCell.pos.y > 0) m_cursor.selectorCell.pos -= Vec2d(0,1); break;
          case 'a': if(m_cursor.selectorCell.pos.x > 0) m_cursor.selectorCell.pos -= Vec2d(1,0); break;
          case 's': if(m_cursor.selectorCell.pos.y < Size.y-1) m_cursor.selectorCell.pos += Vec2d(0,1); break;
          case 'd': if(m_cursor.selectorCell.pos.x < Size.x-1) m_cursor.selectorCell.pos += Vec2d(1,0); break;
          case ' ': return put(sender);
        }
        return nullptr;
    }

    IView* mouseEventsHandler(IView* sender, const MouseRecord& mr) final {
        return nullptr;
    }

private:
    uint8_t m_board[64];

    Cursor m_cursor;
    uint8_t m_player;
};

#endif // GAMEMODEL_HPP
