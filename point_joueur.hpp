#ifndef POINT_JOUEUR_HPP
#define POINT_JOUEUR_HPP

#include "game_area.hpp"
#include "keyboard_handler.hpp"
#include "color.hpp"

#include <math.h>
#include <functional>
#include <map>
#include <list>
#include <iostream>

class point_joueur_t;
typedef std::function<void(const point_joueur_t*)> joueur_callback_t;

enum joueur_event_t
{
    MOVED,
    DIED
};

class point_joueur_t
{
private:
	static const constexpr float TURNING_ANGLE = M_PI / 30.0f;
    static const constexpr float STEP = 4.0f;
    static const constexpr float DEFAULT_RADIUS = 3.0f;

	int id;
	game_area_t& game_area;
	float angle;
	float x, y, radius;
	float prev_x, prev_y;
	bool dead;
	std::map<joueur_event_t, std::list<joueur_callback_t>> observers;
    color_t color;
    keyboard_handler_t& keyboard;
    int left, right;

    void notify(joueur_event_t event);
    void update_turn();
	void turn_left();
	void turn_right();
    void die() { dead = true; /*TODO notify(DIE);*/ }
public:
    point_joueur_t(game_area_t&, color_t, keyboard_handler_t&, int, int);

	void get_pos(float& x, float& y, float& radius) const { x = this->x; y = this->y; radius = this->radius; }
	void get_prev_pos(float& prev_x, float& prev_y) const { prev_x = this->prev_x; prev_y = this->prev_y; }
	const color_t& get_color() const { return color; }
	bool is_dead() { return dead; }
	int  get_id() const { return id; }
	void random_reset();
	void next_pos();

	void add_observer(joueur_event_t event, joueur_callback_t cb) { observers[event].push_back(cb);}
};

#endif /* POINT_JOUEUR_HPP */
