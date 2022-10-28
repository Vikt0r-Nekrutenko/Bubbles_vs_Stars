#include "gamesavemodel.hpp"

GameSaveModel::GameSaveModel(GameModel *model)
    : StackModel("bvss.sdb"), m_model(model) {}
