#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <QWidget>
#include <QPaintEvent>
#include <vector>

#include "point_joueur.hpp"

/*namespace ui {
 * class game_view_t;
 * */

class draw_command_t;

class game_view_t;

class game_view_t: public QWidget
{
    Q_OBJECT
private:
    std::vector<draw_command_t*>* to_draw;
    int height, width;

public:
    game_view_t(QWidget* parent, int width, int height);

    bool on_player_move(const point_joueur_t& joueur);
    void add_joueurs(std::list<point_joueur_t*> players);
    void present() { this->repaint(); }
    void paintEvent(QPaintEvent *);
};

#endif /* GAME_VIEW_HPP */
