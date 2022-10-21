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

    }

    IView* mouseEventsHandler(IView* sender, const MouseRecord& mr) final;

private:

    Cursor m_cursor;
    uint8_t m_player = 'o';
};

#endif // GAMEMODEL_HPP
