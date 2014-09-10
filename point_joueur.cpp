#include "point_joueur.hpp"

#include <QDebug>
#include <cstdlib>

int NEXT_ID = 0;

point_joueur_t::point_joueur_t(game_area_t& area,
                               color_t color,
                               keyboard_handler_t& keyboard,
                               int left_k,
                               int right_k):
    id(NEXT_ID), game_area(area), color(color), keyboard(keyboard), left(left_k), right(right_k)
{
    NEXT_ID += 1;
    keyboard.watch_key(left);
    keyboard.watch_key(right);
    random_reset();
}

void point_joueur_t::notify(joueur_event_t event)
{
    std::list<joueur_callback_t>::iterator it;

    for(it = observers[event].begin(); it != observers[event].end(); it++)
        { (*it)(this); }
}

void point_joueur_t::update_turn()
{
    if(keyboard.is_pressed(left))
        { turn_left(); }
    if(keyboard.is_pressed(right))
        { turn_right(); }
}

/* TODO:
 * game area s'abonne au moved des joueurs.
 * on move elle creer un rectangle.
 * translate pour qu'il ne croisent pas avec la position courante
 * ajoute ce rect a la carte...
 */
void point_joueur_t::next_pos()
{
    static int lol = 0;
	this->prev_x = this->x;
	this->prev_y = this->y;

	update_turn();

    if(this->dead)
        { return ; }

    if(lol++ == 0)
        game_area.is_marked(x, y, radius);

    this->x += STEP * cos(angle);
    this->y += STEP * sin(angle);

    if(game_area.is_marked(x, y, radius))
		{ die(); }
    game_area.mark_line(prev_x, prev_y, x, y, radius, angle);

    notify(MOVED);
}

void point_joueur_t::random_reset()
{
    /* always the same */
    dead = false;
    radius = DEFAULT_RADIUS;
    /* random */
    x = 100.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (game_area.get_largeur() - 200.0f)));
    y = 100.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (game_area.get_hauteur() - 200.0f)));
    angle = 0.0f;
    //angle = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.0 * M_PI)));

    //std::cout << x << ", " << y << ", " << angle << std::endl;
}

void point_joueur_t::turn_left()
{
    //qDebug() << "turn left, " << this;
    this->angle += TURNING_ANGLE;
}

void point_joueur_t::turn_right()
{
    //qDebug() << "turn right, " << this;
    this->angle -= TURNING_ANGLE;
}
