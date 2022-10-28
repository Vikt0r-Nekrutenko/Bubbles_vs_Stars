#include "gamesavemodel.hpp"
#include "gamemodel.hpp"

GameSaveModel::GameSaveModel(GameModel *model)
    : StackModel("bvss.sdb"), m_model(model) {}

void GameSaveModel::save()
{
    for(int i = 0; i < 64; ++i)
        m_board[i] = m_model->board()[i];
    m_plOneScore = m_model->plOneScore();
    m_plTwoScore = m_model->plTwoScore();
    m_player = m_model->player();
}

void GameSaveModel::load()
{
    pop<GameSaveModel>();

    for(int i = 0; i < 64; ++i)
        m_model->m_board[i] = m_board[i];
    m_model->m_plOneScore = m_plOneScore();
    m_model->m_plTwoScore = m_plTwoScore();
    m_model->m_player = m_player();
}
