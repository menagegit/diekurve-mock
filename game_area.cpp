#include "game_area.hpp"

#include <stdlib.h>
#include <math.h>

#include <iostream>

// TODO destructors + hide copy constructor and copy operator

game_area_t::game_area_t(int larg, int haut): larg(larg), haut(haut), max_form_size(10.0f)
{
    int i = 0, j = 0;

    marked_forms = new std::list<geometric_form_t*>**[larg];

    for(i = 0; i < larg; i++)
    {
        marked_forms[i] = new std::list<geometric_form_t*>*[haut];
        for(j = 0; j < haut; j++)
        {
            marked_forms[i][j] = new std::list<geometric_form_t*>();
        }
    }
}

void game_area_t::mark_line(float sx, float sy, float ex, float ey, float lar, float angle)
{
    float middlex = (sx + ex) / 2.0f;
    float middley = (sy + ey) / 2.0f;
    int index_mx = static_cast<int> (middlex);
    int index_my = static_cast<int> (middley);
    point_t p1(sx, sy), p2(ex, ey);

    if(middlex < 0.0f || middlex >= this->larg || middley < 0.0f || middley >= this->haut)
        { return; }

    float lon = distance(p1, p2);
    rectangle_t* rect = new rectangle_t(middlex, middley, lon, lar * 2, angle);

    //rect->print();

    this->marked_forms[index_mx][index_my]->push_back(rect);
}

bool game_area_t::is_marked(float x, float y, float radius)
{
    // TODO split in two functions ?
	int i, j, startx, starty, endx, endy;
    cercle_t c(x, y, radius);

    // out of area
    if(x - radius < 0 || x + radius >= larg || y - radius < 0 || y + radius >= haut)
        { return true; }

    //c.print();

    // collapse with a trace
    startx = x - max_form_size - radius < 0 ? 0 : x - max_form_size - radius;
    starty = y - max_form_size - radius < 0 ? 0 : y - max_form_size - radius;
    endx = x + max_form_size + radius > larg ? larg : x + max_form_size + radius;
    endy = y + max_form_size + radius > haut ? haut : y + max_form_size + radius;

	for(i = startx; i < endx; i++)
	{
		for(j = starty; j < endy; j++)
		{
			std::list<geometric_form_t*>::const_iterator it;
			for(it = marked_forms[i][j]->begin(); it != marked_forms[i][j]->end(); it++)
            {
				if((*it)->is_coliding(c))
                    { return true; }
			}
		}
	}
	return false;
}
