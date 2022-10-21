#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include "imodel.hpp"
#include "vec2d.hpp"

using namespace stf;
using namespace stf::smv;

class GameModel : public BaseModel
{
    struct Cursor
    {
        Vec2d selectedCell {0,0};
        Vec2d destinationCell {0,0};
    };

public:
    const Vec2d Size { 8, 8 };

    GameModel();

    IView* keyEventsHandler(IView* sender, const int key) final
    {
        switch (key)
        {
          case 'w': if(m_cursor.destinationCell.y > 0) m_cursor.destinationCell -= Vec2d(0,1); break;
          case 'a': if(m_cursor.destinationCell.x > 0) m_cursor.destinationCell -= Vec2d(1,0); break;
          case 's': if(m_cursor.destinationCell.y < Size.y) m_cursor.destinationCell += Vec2d(0,1); break;
          case 'd': if(m_cursor.destinationCell.x < Size.x) m_cursor.destinationCell += Vec2d(1,0); break;
          case ' ': break;
        }
        return nullptr;
    }

    IView* mouseEventsHandler(IView* sender, const MouseRecord& mr) final { return nullptr; }

private:

    Cursor m_cursor;
    uint8_t m_player = 'o';
};

#endif // GAMEMODEL_HPP
