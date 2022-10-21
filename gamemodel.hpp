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
    Selector selectedCell { {0,0}, 'o' };
    Selector destinationCell;
    Selector *activeCursor = &destinationCell;
};

class GameModel : public BaseModel
{

public:
    const Vec2d Size { 8, 8 };

    GameModel();

    inline const Cursor& cursor() const { return m_cursor; }

    IView* keyEventsHandler(IView* sender, const int key) final
    {
        switch (key)
        {
          case 'w': if(m_cursor.activeCursor->pos.y > 0) m_cursor.activeCursor->pos -= Vec2d(0,1); break;
          case 'a': if(m_cursor.activeCursor->pos.x > 0) m_cursor.activeCursor->pos -= Vec2d(1,0); break;
          case 's': if(m_cursor.activeCursor->pos.y < Size.y-1) m_cursor.activeCursor->pos += Vec2d(0,1); break;
          case 'd': if(m_cursor.activeCursor->pos.x < Size.x-1) m_cursor.activeCursor->pos += Vec2d(1,0); break;
          case ' ': break;
        }
        return nullptr;
    }

    IView* mouseEventsHandler(IView* sender, const MouseRecord& mr) final { return nullptr; }

private:

    Cursor m_cursor;
};

#endif // GAMEMODEL_HPP
