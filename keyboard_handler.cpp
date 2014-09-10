#include "keyboard_handler.hpp"

/** key_state_t 's automata **/

class dead_t;
class virgin_t;
class bitch_t;
class forgoten_t;

extern key_state_t* dead;
extern key_state_t* bitch;
extern key_state_t* forgoten;
extern key_state_t* virgin;

class dead_t: public key_state_t
{
public:
    virtual key_state_t* press() { return virgin; }
} dead_i;

class virgin_t: public key_state_t
{
public:
    virtual key_state_t* release() { return forgoten; }
    virtual key_state_t* tick(bool& val) { val = true; return bitch; }
} virgin_i;

class bitch_t: public key_state_t
{
public:
    virtual key_state_t* release() { return dead; }
    virtual key_state_t* tick(bool& val) { val = true; return this; }
} bitch_i;

class forgoten_t: public key_state_t
{
    int nb_pressed;
public:
    virtual key_state_t* pressed() { nb_pressed += 1; return this; }
    virtual key_state_t* tick(bool& val)
    {
        val = true;
        nb_pressed -= 1;
        if(nb_pressed > 0)
            { return this; }
        else
            { nb_pressed = 0; return dead; }
    }
} forgoten_i;

key_state_t* dead = &dead_i;
key_state_t* forgoten = &forgoten_i;
key_state_t* bitch = &bitch_i;
key_state_t* virgin = &virgin_i;

/** keyboard_handler_t 's functions **/

/*void keyboard_handler_t::get_left_right(bool& left, bool& right)
{
    this->left = this->left->tick(left);
    this->right = this->right->tick(right);
}*/

bool keyboard_handler_t::is_pressed(const int& key)
{
    bool is_pressed = false;

    if(watched_keys.find(key) != watched_keys.end())
        { watched_keys[key] = watched_keys[key]->tick(is_pressed); }

    return is_pressed;
}

void keyboard_handler_t::pressed(const int &key)
{
    /*if(key == SDLK_LEFT)
        { left = left->press(); }
    else if(key == SDLK_RIGHT)
        { right = right->press(); }*/

    if(watched_keys.find(key) != watched_keys.end())
        { watched_keys[key] = watched_keys[key]->press(); }
}

void keyboard_handler_t::released(const int& key)
{
    /*if(key == SDLK_LEFT)
        { left = left->release(); }
    if(key == SDLK_RIGHT)
        { right = right->release(); }*/

    if(watched_keys.find(key) != watched_keys.end())
        { watched_keys[key] = watched_keys[key]->release(); }
}
