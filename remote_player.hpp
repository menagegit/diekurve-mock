#ifndef REMOTE_PLAYER_HPP
#define REMOTE_PLAYER_HPP

#include "point_joueur.hpp"

#include <math.h>

class event_t
{
	friend remote_player_t;
};

class turn_left_event_t: public event_t
{

};

class turn_right_event_t: public event_t
{

};

class die_event_t: public event_t
{

};

class reset_event_t: public event_t
{
private:
	float x, y, angle;
};

/* protocol:
chaque joueur est connecter au multicast des autres.
eds qu'on fait une action, le joueur_point emet un event
le joueurs server est connecté a ces events => il envoit l'event a tout ses colegues
	envoit = 2packet udp (marque 1st and duplicate) avec le temp precis(identique de l'autre coté)
		et un packet id qui est incrementer a chaque fois.
	si packet id est mauvais => resend tout ceux qui ont etait raté.
	
	operations du network :
		reset clock (un universal time <=> le nouveau 0)
		resend

/* une interface par proxy ou une pour tous ?
 * je prefere la 1ere solution... */
class remote_interface_t
{
private:
	player_proxy_t& player_proxy;
public:
	remote_interface_t(player_proxy_t& p): player_proxy(p) { }
	/* 
	how to handle network => boost.asio
	
	subscribe to remote player player
		udp multicast -> s'ajouter comme client...

	on data receive (udp)
		implem du protocol (verif qu'on ne la pas deja recut ect...)
		event_t parsed = parse data(); // comment le faire avec les stubs ? => faut les modif
										// pour qu'il heritent de event...
		player_proxy.trigger(parsed);
	*/
};

class player_proxy_t
{
private:
	point_joueur_t const& player;
public:
	player_proxy_t(point_joueur_t& p): player(p) { /* submit to event */ }
	
	void trigger(turn_left_event_t& event) { player.turn_left(); }
	void trigger(turn_right_event_t& event) { player.turn_right(); }
	void trigger(die_event_t& event) { player.die(); }
	void trigger(reset_event_t& event) { player.reset(event.x, event.y, event.angle); }
};

#endif /* REMOTE_PLAYER_HPP */
