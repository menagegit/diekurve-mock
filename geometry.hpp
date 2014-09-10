#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <iostream>
#include <list>

using namespace std;

class rectangle_t;
class cercle_t;
class point_t;

/* helper functions */
float distance(const point_t&, const point_t&);

class point_t
{
public:
    float x, y;

    point_t(): x(0.0f), y(0.0f) { }
    point_t(float x, float y): x(x), y(y) { }
};

class geometric_form_t
{
protected:
public:
    virtual bool is_coliding(const cercle_t& c) const = 0;

    virtual void print() { }
};

class polygon_t: public geometric_form_t
{
protected:
    list<point_t> points;

public:
    polygon_t(): points() { /*list<point_t>::const_iterator it = points.begin();*/ }

    //virtual bool is_coliding(const polygon_t &p) const = 0;
    virtual bool is_coliding(const cercle_t &c) const;
};

class rectangle_t: public polygon_t
{
public:
	rectangle_t(float x, float y, float lar, float hau, float angle);

    //virtual bool is_coliding(const rectangle_t& r) const;
    //virtual bool is_coliding(const cercle_t& c) const;


    /*output geogebra format...
     * void print() {
        static int nb = 0;
        char name = 'A';
        list<point_t>::const_iterator it;
        for(it = points.begin(); it != points.end(); it++)
        {
            std::cout << "<element type=\"point\" label=\"" << name++ << nb << "\">" << std::endl;
            std::cout << "<show object=\"true\" label=\"true\"/>" << std::endl;
            std::cout << "<objColor r=\"0\" g=\"0\" b=\"255\" alpha=\"0\"/>" << std::endl;
            std::cout << "<layer val=\"0\"/>" << std::endl;
            std::cout << "<labelMode val=\"0\"/>" << std::endl;
            std::cout << "<animation step=\"0.1\" speed=\"1\" type=\"1\" playing=\"false\"/>" << std::endl;
            std::cout << "<coords x=\"" << it->x << "\" y=\"" << it->y << "\" z=\"1\"/>" << std::endl;
            std::cout << "<pointSize val=\"3\"/>" << std::endl;
            std::cout << "<pointStyle val=\"0\"/>" << std::endl;
            std::cout << "</element>" << std::endl;
        }
        nb += 1;
    }*/
};

class cercle_t: public geometric_form_t
{
private:
    point_t center;
    float radius;
public:
    cercle_t(float x, float y, float rad): center(x, y), radius(rad) { }

    float get_radius() const { return radius; }
    const point_t& get_center() const { return center; }

    virtual bool is_coliding(const rectangle_t& r) const;
    virtual bool is_coliding(const cercle_t& c) const;

    /*void print()
    {
        static int nb = 0;

        std::cout << "<element type=\"point\" label=\"cp" << nb << "\">" << std::endl;
        std::cout << "<show object=\"true\" label=\"true\"/>" << std::endl;
        std::cout << "<objColor r=\"0\" g=\"0\" b=\"255\" alpha=\"0\"/>" << std::endl;
        std::cout << "<layer val=\"0\"/>" << std::endl;
        std::cout << "<labelMode val=\"0\"/>" << std::endl;
        std::cout << "<animation step=\"0.1\" speed=\"1\" type=\"1\" playing=\"false\"/>" << std::endl;
        std::cout << "<coords x=\"" << center.x << "\" y=\"" << center.y << "\" z=\"1\"/>" << std::endl;
        std::cout << "<pointSize val=\"3\"/>" << std::endl;
        std::cout << "<pointStyle val=\"0\"/>" << std::endl;
        std::cout << "</element>" << std::endl;
        std::cout << "<command name=\"Circle\">";
        std::cout << "    <input a0=\"cp" << nb << "\" a1=\"" << radius << "\"/>";
        std::cout << "    <output a0=\"c" << nb << "\"/>";
        std::cout << "</command>";
        std::cout << "<element type=\"conic\" label=\"c" << nb << "\">";
        std::cout << "    <show object=\"true\" label=\"false\"/>";
        std::cout << "    <objColor r=\"0\" g=\"0\" b=\"0\" alpha=\"0\"/>";
        std::cout << "    <layer val=\"0\"/>";
        std::cout << "    <labelMode val=\"0\"/>";
        std::cout << "    <lineStyle thickness=\"2\" type=\"0\" typeHidden=\"1\"/>";
        std::cout << "    <eigenvectors  x0=\"1\" y0=\"0\" z0=\"1.0\" x1=\"0\" y1=\"1\" z1=\"1.0\"/>";
        std::cout << "    <matrix A0=\"1\" A1=\"1\" A2=\"158966.655473\" A3=\"0\" A4=\"-373.543\" A5=\"-139.432\"/>";
        std::cout << "    <eqnStyle style=\"specific\"/>";
        std::cout << "</element>";
        nb +=1;
    }*/
};

#endif /* GEOMETRY_HPP */
