#ifndef PAUSEMENUVIEW_HPP
#define PAUSEMENUVIEW_HPP

#include "menuview.hpp"

class PauseMenuView : public MenuView
{
  public:
  PauseMenuView(GameModel* model);
  ~PauseMenuView() override = default;
  IView* menuSelectConfirm() final;
};


#endif // PAUSEMENUVIEW_HPP
