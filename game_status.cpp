#include "game_status.hpp"

#include "color.hpp"

// TODO change that
color_t colors[8] = {
    red,
    green,
    blue,
    pink,
    purple,
    cyan,
    yellow,
    orange
};

void game_status_t::add_players(list<player_option_t *> options)
{
    list<player_option_t*>::const_iterator it;

    for(it = options.begin(); it != options.end(); ++it)
    {
        players.push_back(new point_joueur_t(game_area,
                                             (*it)->color,
                                             keyboard,
                                             (*it)->left_key,
                                             (*it)->right_key));
    }
    game_view->add_joueurs(players);
}

/*
 * callback =
 * 	pour tout point
		if(point.left_pressed())
			point.turn_left()
		if(point.right_pressed())
			point.turn_right()

		point.next_position();
		dessiner_ligne(point.prev position(), point.position());
		if(point.iddle() == false)
			dessiner_point(point.position()); */
void game_status_t::update_game()
{
    std::list<point_joueur_t*>::iterator it;

    for(it = players.begin(); it != players.end(); it++)
        { (*it)->next_pos(); }

    game_view->present();
}
