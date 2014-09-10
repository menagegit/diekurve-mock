#include "game_view.hpp"
#include "color.hpp"

#include <QPainter>
#include <QPointF>
#include <QRectF>

class draw_command_t
{
protected:
    color_t c;
public:
    explicit draw_command_t(color_t cl): c(cl) { }

    virtual void draw(QPainter& painter) = 0;
    virtual ~draw_command_t() { }
};

class draw_line_t: public draw_command_t
{
private:
    draw_line_t operator=(draw_line_t) { return *this; }
    draw_line_t(const draw_line_t&):draw_command_t( {0, 0, 0, 0} ) { }
protected:
    float x1, y1, x2, y2, thickness; /* start and end coordinates */
public:
    explicit draw_line_t(float a, float b, float c, float d, float thick, color_t cl):
        draw_command_t(cl),
        x1(a), y1(b), x2(c), y2(d), thickness(thick) { }

    virtual void draw(QPainter& painter)
    {
        painter.setPen(QPen(QColor(c.r, c.g, c.b), thickness));
        painter.drawLine(QPointF(x1, y1), QPointF(x2, y2));
    }

    virtual ~draw_line_t() { }
};

class draw_circle_t: public draw_command_t
{
private:
    draw_circle_t operator=(draw_circle_t) { return *this; }
    draw_circle_t(const draw_circle_t&):draw_command_t( {0, 0, 0, 0} ) { }
protected:
    float x, y, rad;
public:
    explicit draw_circle_t(float xp, float yp, float radp, color_t c):
        draw_command_t(c),
        x(xp), y(yp), rad(radp) { }

    virtual void draw(QPainter& painter)
    {
        painter.setPen(QColor(c.r, c.g, c.b));
        painter.setBrush(QBrush(QColor(c.r, c.g, c.b), Qt::SolidPattern));
        painter.drawEllipse(QRectF(x - rad / 2.0f, y - rad / 2.0f, rad, rad));
    }

    virtual ~draw_circle_t() { }
};


class draw_rect_t: public draw_command_t
{
private:
    draw_rect_t operator=(draw_rect_t) { return *this; }
    draw_rect_t(const draw_rect_t&):draw_command_t( {0, 0, 0, 0} ) { }
protected:
    float x, y, lar, hau;
public:
    explicit draw_rect_t(float xp, float yp, float larp, float haup, color_t c):
        draw_command_t(c),
        x(xp), y(yp), lar(larp), hau(haup) { }

    virtual void draw(QPainter& painter)
    {
        painter.setPen(QColor(c.r, c.g, c.b));
        //painter.setBrush(QBrush(QColor(c.r, c.g, c.b), Qt::SolidPattern));
        painter.drawRect(QRectF(x, y, lar, hau));
    }

    virtual ~draw_rect_t() { }
};

/* No concurent access to that class ! */

// TODO la taille du game view n'est pas height width. ca fausse les dessins qui sont
// deplacé vers le bas...

game_view_t::game_view_t(QWidget* parent, int width, int height):
    QWidget(parent),
    to_draw(new std::vector<draw_command_t*>()),
    height(height),
    width(width)
{
    //QPainter painter(this);

    //to_draw.erase(to_draw.begin(), to_draw.end());
    this->setAttribute(Qt::WA_OpaquePaintEvent);
    this->resize(height, width);
    // TODO pourquoi la fenetre est vide ? a cause du layout ?
    //this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    to_draw->push_back(new draw_rect_t(0, 0, width - 1, height - 1, { 255, 0, 0, 0}));
    /*painter.setPen(QColor(255, 0, 0));
    painter.drawRect(0, 0, this->height(), this->width());
    painter.end();*/

    //this->present();
}

bool game_view_t::on_player_move(const point_joueur_t &joueur)
{
    float x = 0, y = 0, prevx = 0, prevy = 0, rad = 0;
    const color_t& c = joueur.get_color();

    joueur.get_pos(x, y, rad);
    joueur.get_prev_pos(prevx, prevy);

    //to_draw->push_back(new draw_circle_t(x, this->height - y, rad * 1.7f, c));
    to_draw->push_back(new draw_line_t(x, this->height - y, prevx, this->height - prevy, rad * 2.0f, c));

    return true;
}

class on_player_move_cb
{
private:
    game_view_t* _ptr;
public:
    on_player_move_cb(game_view_t* ptr): _ptr(ptr) { }

    void operator()(const point_joueur_t* joueur) { _ptr->on_player_move(*joueur); }
};

void game_view_t::add_joueurs(std::list<point_joueur_t*> players)
{
    std::list<point_joueur_t*>::iterator it;

    joueur_callback_t cb = on_player_move_cb(this);
    for(it = players.begin(); it != players.end(); it++)
    {
        (*it)->add_observer(MOVED, cb);
    }
}

void game_view_t::paintEvent(QPaintEvent *)
{
    QPainter painter;
    std::vector<draw_command_t*>::iterator it;
    draw_command_t* tmp = nullptr;

    painter.begin(this);

    painter.setRenderHint(QPainter::Antialiasing);

    it = to_draw->begin();
    while(it != to_draw->end())
    {
        (*it)->draw(painter);
        tmp = *it;
        it = to_draw->erase(it);
        delete(tmp);
    }
    painter.end();
}
