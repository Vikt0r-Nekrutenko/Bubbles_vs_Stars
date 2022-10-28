#ifndef GAMESAVEMODEL_HPP
#define GAMESAVEMODEL_HPP

#include "stackmodel.hpp"
#include "fields.hpp"

using namespace stf::sdb;

class GameModel;

class GameSaveModel : public StackModel
{
public:
    GameSaveModel(GameModel *model);

private:

    IntVecField m_board = IntVecField(this, 64);
    IntField m_player = IntField(this);
    IntField m_plOneScore = IntField(this);
    IntField m_plTwoScore = IntField(this);

    GameModel *m_model;
};

#endif // GAMESAVEMODEL_HPP
