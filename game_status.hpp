#ifndef GAME_STATUS_HPP
#define GAME_STATUS_HPP

#include <list>

#include "game_view.hpp"
#include "game_area.hpp"
#include "point_joueur.hpp"
#include "keyboard_handler.hpp"

using namespace std;

struct player_option_t
{
    color_t color;
    int left_key, right_key;
};

class game_status_t
{
private:
    game_view_t* game_view;
    game_area_t game_area;
    keyboard_handler_t keyboard;
    std::list<point_joueur_t*> players;
public:
    explicit game_status_t(int larg, int haut, game_view_t* view):
        game_view(view), game_area(larg, haut), keyboard(), players() { }

    void add_players(list<player_option_t *> options);

    // TODO changer le get keyboard en pressed et released
    void update_game();
    keyboard_handler_t& get_keyboard() { return keyboard; }
};

#endif /* GAME_STATUS_HPP */
