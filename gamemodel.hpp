#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include "imodel.hpp"
#include "vec2d.hpp"

using namespace stf;
using namespace stf::smv;

class GameModel : public BaseModel
{
public:
    const Vec2d Size { 8, 8 };

    GameModel();

    IView* keyEventsHandler(IView* sender, const int key) final;

    IView* mouseEventsHandler(IView* sender, const MouseRecord& mr) final;

private:

    Vec2d m_cursor;
    uint8_t m_player = 'o';
};

#endif // GAMEMODEL_HPP
