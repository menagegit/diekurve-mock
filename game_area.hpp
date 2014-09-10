#ifndef GAME_AREA_HPP
#define GAME_AREA_HPP

#include <list>

#include "geometry.hpp"

class game_area_t
{
private:
	int larg, haut;
	float max_form_size;
	std::list<geometric_form_t*>*** marked_forms;

public:
	game_area_t(int larg, int haut);

    int get_hauteur() const { return haut; }
    int get_largeur() const { return larg; }
	void mark_line(float sx, float sy, float ex, float ey, float lar, float angle);
	bool is_marked(float pos, float lar, float radius);
};

#endif /* POINT_JOUEUR_HPP */
