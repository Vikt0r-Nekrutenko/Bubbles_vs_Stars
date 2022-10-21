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
    Selector selectedCell;
    Selector destinationCell;
    Selector *activeCursor = &destinationCell;

    void switchCursor()
    {
        (activeCursor == &selectedCell)
                ? activeCursor = &destinationCell
                : activeCursor = &selectedCell;
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
        m_player = 0;
    }

    inline const Cursor& cursor() const { return m_cursor; }
    inline const uint8_t& player() const { return m_player; }

    IView* keyEventsHandler(IView* sender, const int key) final
    {
        switch (key)
        {
          case 'w': if(m_cursor.activeCursor->pos.y > 0) m_cursor.activeCursor->pos -= Vec2d(0,1); break;
          case 'a': if(m_cursor.activeCursor->pos.x > 0) m_cursor.activeCursor->pos -= Vec2d(1,0); break;
          case 's': if(m_cursor.activeCursor->pos.y < Size.y-1) m_cursor.activeCursor->pos += Vec2d(0,1); break;
          case 'd': if(m_cursor.activeCursor->pos.x < Size.x-1) m_cursor.activeCursor->pos += Vec2d(1,0); break;
          case ' ': m_cursor.switchCursor(); break;
        }
        return nullptr;
    }

    IView* mouseEventsHandler(IView* sender, const MouseRecord& mr) final { return nullptr; }

private:
    uint8_t m_board[64];

    Cursor m_cursor;
    uint8_t m_player = 'o';
};

#endif // GAMEMODEL_HPP
