#include "endview.hpp"
#include "gamemodel.hpp"
#include "menuview.hpp"

EndView::EndView(GameModel* model)
  : IView(model)
{
    if(model->isDraw()) {
        model->gameOverHandler({0,0}, 'd');
    } else {
        model->player() == PLAYER1_CELL
                ? model->gameOverHandler({1,0}, model->opponent())
                : model->gameOverHandler({0,1}, model->opponent());
    }
    model->story.save();
}

void EndView::show(Renderer& renderer)
{
  IView::show(renderer);
  if(static_cast<GameModel*>(m_model)->isDraw()) {
    Vec2d p { renderer.Size / 2 - Vec2d(2, 0) };
    renderer.drawText(p, "DRAW!");
  } else {
    m_end.show(renderer, true);
    renderer.drawPixel(renderer.Size / 2 - m_end.Size() / 2 + m_end.markers().at(0), static_cast<GameModel*>(m_model)->opponent());
  }
}

IView* EndView::keyEventsHandler(const int)
{
  static_cast<GameModel*>(m_model)->reset();
  return new MenuView(static_cast<GameModel*>(m_model));
}
