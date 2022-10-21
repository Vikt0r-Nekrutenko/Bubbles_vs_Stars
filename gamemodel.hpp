#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include "imodel.hpp"
#include "vec2d.hpp"

using namespace stf;
using namespace stf::smv;

struct Selector
{
    Vec2d pos { 0, 0 };
    uint8_t sym = 'e';
};

struct Cursor
{
    Selector selectorCell;
    Selector destinationCell;
    Selector *activeCursor = &selectorCell;

    void switchCursor()
    {
        destinationCell.pos = selectorCell.pos = activeCursor->pos;
        (activeCursor == &selectorCell)
                ? activeCursor = &destinationCell
                : activeCursor = &selectorCell;
    }
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
            c = 'e';
        }

        m_board[0] = 'o';
        m_board[63] = '*';

        m_cursor = Cursor();
        m_player = 'o';
    }

    inline const Cursor& cursor() const { return m_cursor; }
    inline const uint8_t& player() const { return m_player; }
    inline const uint8_t* board() const { return m_board; }


    IView* keyEventsHandler(IView* sender, const int key) final
    {
        switch (key)
        {
          case 'w': if(m_cursor.selectorCell.pos.y > 0) m_cursor.selectorCell.pos -= Vec2d(0,1); break;
          case 'a': if(m_cursor.selectorCell.pos.x > 0) m_cursor.selectorCell.pos -= Vec2d(1,0); break;
          case 's': if(m_cursor.selectorCell.pos.y < Size.y-1) m_cursor.selectorCell.pos += Vec2d(0,1); break;
          case 'd': if(m_cursor.selectorCell.pos.x < Size.x-1) m_cursor.selectorCell.pos += Vec2d(1,0); break;
          case ' ':
            if(m_board[Size.x * m_cursor.selectorCell.pos.y + m_cursor.selectorCell.pos.x] == m_player) {
                m_cursor.selectorCell.sym = m_cursor.destinationCell.sym = m_player;
            } else if(m_cursor.destinationCell.sym == m_player &&
                      m_board[Size.x * m_cursor.selectorCell.pos.y + m_cursor.selectorCell.pos.x] == 'e') {
                m_board[Size.x * m_cursor.selectorCell.pos.y + m_cursor.selectorCell.pos.x] = m_player;
                m_cursor.selectorCell.sym = m_cursor.destinationCell.sym = 'e';
            }
            break;
        }
        return nullptr;
    }

    IView* mouseEventsHandler(IView* sender, const MouseRecord& mr) final { return nullptr; }

private:
    uint8_t m_board[64];

    Cursor m_cursor;
    uint8_t m_player;
};

#endif // GAMEMODEL_HPP
