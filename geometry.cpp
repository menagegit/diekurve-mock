#include "geometry.hpp"

#include <stdlib.h>
#include <math.h>
#include <iostream>

/* private class - TODO passage par reference du resultat ok ?
 * sinon on peut retourner par copie mais il faut operator=... */

/* important point :
 * All the geometry implemented in this class is quite useless.
 * When checking the collision between a player (circle) and
 * a trace (rectangle), we can approximate that if a corner of the rectangle
 * is in the circle there is colision else not. This approximation is
 * valid based on the fact that the circle's and the rectangle's dimension
 * are on same order (by construction).
 * It the best choice in this precise case cause it's easier to code and
 * cheaper to compute.
 */

class segment_t
{
public:
    point_t p1, p2;
    segment_t(): p1(), p2() { }
    segment_t(const point_t& p1, const point_t& p2): p1(p1), p2(p2) { }
};

class vector_t
{
public:
    float x, y;

    vector_t(): x(0.0), y(0.0) { }
    vector_t(float xs, float ys, float xe, float ye): x(xe - xs), y(ye - ys) { }
    vector_t(float angle, float lon): x(lon * cos(angle)), y(lon * sin(angle)) { }
    vector_t(const point_t& p1, const point_t& p2): x(p2.x - p1.x), y(p2.y - p1.y) { }

    void mult(float nb, vector_t& dest) const;
    void scalaire(const vector_t& v, float& dest) const;
    float lon() { return sqrt(x * x + y * y); }
    float squared_lon() { return x * x + y * y; }
    void plus(const vector_t& v, vector_t &dest) const;
};

void vector_t::mult(float nb, vector_t &dest) const
{
    dest.x = this->x * nb;
    dest.y = this->y * nb;
}

void vector_t::scalaire(const vector_t &v, float &dest) const
{
    dest = this->x * v.x + this->y * v.y;
}

void vector_t::plus(const vector_t& v, vector_t &dest) const
{
    dest.x = this->x + v.x;
    dest.y = this->y + v.y;
}

void image(const vector_t& v, const point_t& p, point_t& img)
{
    img.x = p.x + v.x;
    img.y = p.y + v.y;
}

float distance(const point_t& p1, const point_t& p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

float distance(const segment_t& seg, const point_t& p)
{
    vector_t vdroite(seg.p1, seg.p2); /* vecteur d1d2 */
    vector_t vd1_pt(seg.p1, p); /* vecteur x1p */
    float dist_d1_p;

    /* projeté orthogonale */
    vdroite.scalaire(vd1_pt, dist_d1_p);

    if(dist_d1_p < 0) /* out of segment, nearer d1(xd1, yd1) */
        { return distance(seg.p1, p); }

    else if(dist_d1_p > vdroite.lon()) /* out of segment, nearer d2(xd2, yd2) */
        { return distance(seg.p2, p); }

    dist_d1_p /= vdroite.lon();

    return sqrt(vd1_pt.squared_lon() - dist_d1_p * dist_d1_p);
}

/* TODO polygon_t, avec colision (cercle) : pour tout les points distance segment > rayon ? */

/* TODO remplacer par celle d'un haut. distance between two points */
/*float points_distance(float x1, float y1, float x2, float y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

static float segment_distance(float xd1, float yd1, float xd2, float yd2, float xp, float yp)
{
    vector_t vdroite(xd1, yd1, xd2, yd2); /* vecteur d1d2 */
  /*  vector_t vd1_pt(xd1, yd1, xp, yp); /* vecteur x1p */
    /*float dist_d1_p;

    /* projeté orthogonale */
/*    vdroite.scalaire(vd1_pt, dist_d1_p);

    if(dist_d1_p < 0) /* out of segment, nearer d1(xd1, yd1) */
  /*      { return points_distance(xd1, yd1, xp, yp); }

    else if(dist_d1_p > vdroite.lon()) /* out of segment, nearer d2(xd2, yd2) */
    /*    { return points_distance(xd2, yd2, xp, yp); }

    dist_d1_p /= vdroite.lon();

    return sqrt(vd1_pt.squared_lon() - dist_d1_p * dist_d1_p);
}*/

/* return the minimum distance between segment d[d1, d2] and point p */
/*static float segment_distance(float xd1, float yd1, float xd2, float yd2, float xp, float yp)
{
    /* d: y = ax + b */
  /*  float a, b, r;

    r = (xp-xd1)*(xd2-xd1) + (yp-yd1)*(yd2-yd1)
        /   ((xd2-xd1)*(xd2-xd1) + (yd2-yd1)*(yd2-yd1));

    if(r <= 0) /* p is on the backward extension of [d1, d2] */
    /*    { return points_distance(xd1, yd1, xp, yp); }
    if(r >= 1) /* p is on the backward extension of [d1, d2] */
      /*  { return points_distance(xd2, yd2, xp, yp); }

    /* projeté orthogonale ... verifier calcul ! */
    /*a = (yd1 - yd2) / (xd1 - xd2);
    b = yd2 - a * xd2;
    std::cout << "deja c'est pas mal !" << std::endl;
    return (abs(a * xp - yp + b)) / (sqrt(a*a + 1));
}*/

inline float f_abs(float f) { return f < 0.0f ? -f:f; }

bool polygon_t::is_coliding(const cercle_t &c) const
{
    list<point_t>::const_iterator it;
    segment_t s;

    // assert list is not empty

    for(it = points.begin(); it != points.end()--; )
    {
        s = segment_t(*it, *(++it));
        if(distance(s, c.get_center()) <= c.get_radius())
            { return true; }
    }
    s = segment_t(points.back(), points.front());
    return distance(s, c.get_center()) <= c.get_radius();
}

rectangle_t::rectangle_t(float x, float y, float lon, float lar, float angle)
{
    /*
     * 3-----2
     * |     |
     * |  X  |
     * |     |
     * 0-----1
     * X(x, y) = middle of the rect
     */

    int i = 0;

    float a = atan(lar / lon);

    float diag = sqrt((lon * lon) + (lar * lar)) / 2.0f;
    point_t p, middle(x, y);
    vector_t v;
    float teta = M_PI + a + angle;

    for(i = 0; i < 4; i += 1)
    {
        v = vector_t(teta, diag);
        image(v, middle, p);

        points.push_back(p); // copy point

        // ok, not that pretty but i don't know how to make it cleaner...
        teta += ((i % 2 == 0) ? (M_PI - 2.0f * a) : 2.0f * a);
    }
}

/*bool rectangle_t::is_coliding(const rectangle_t& r) const
{
	/* TODO prendre en compte l'angle
	if((r.x >= this->x + this->larg)		// trop à droite
		|| (r.x + r.larg <= this->x) 		// trop à gauche
		|| (r.y >= this->y + this->haut)	// trop en bas
		|| (r.y + r.haut <= this->y))		// trop en haut
			{return false; }
	else
		{ return true; }*/
    /*return false;
}*/
/*
bool rectangle_t::is_coliding(const cercle_t& c) const
{
    //std::cout << "point distance: " << points_distance(c.get_x(), c.get_y(), x, y) << "<? " << c.get_radius() << std::endl;
    //return points_distance(c.get_x(), c.get_y(), x, y) < c.get_radius();
    float d = 0;
    int i = 0;

    for(i = 0; i < 4; i += 1)
    {
        //d = segment_distance(coins[i][0], coins[i][1], coins[(i + 1) % 4][0], coins[(i + 1) % 4][1], c.get_x(), c.get_y());
        //std::cout << "d = " << d << std::endl;
        if(d <= c.get_radius())
            { return true; }
    }
    return false;
}*/

bool cercle_t::is_coliding(const rectangle_t& r) const
{
    return r.is_coliding(*this);
}

bool cercle_t::is_coliding(const cercle_t& c) const
{
    // TODO faster implementation if we compare squared values
    return distance(this->center, c.center) <= this->radius + c.radius;
    //return dist2 > ((this->radius + c.radius) * (this->radius + c.radius));
}
