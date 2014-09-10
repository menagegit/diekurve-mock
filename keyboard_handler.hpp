#ifndef KEYBOARD_HANDLER_HPP
#define KEYBOARD_HANDLER_HPP

#include <QDebug>
#include <map>

/* TODO BUG : les operations sur la state machine doivent etre atomique ?
 * car acces concurent... que des acces ecriture/lecture pour l'instant... */

class key_state_t
{
public:
    virtual key_state_t* press() { return this; }
    virtual key_state_t* release() { return this; }
    virtual key_state_t* tick(bool& val) { val = false; return this; }
};

extern key_state_t* dead;

class keyboard_handler_t
{
private:
    std::map<const int, key_state_t*> watched_keys;
public:
    keyboard_handler_t(): watched_keys() { }

    /* coportement plus compliquer ici ! quand on watch une key deja watched, elle retorune automatiquement a dead... */
    void watch_key(int& key) { watched_keys[key] = dead; }

    bool is_pressed(const int& key);
    void pressed(const int& key);
    void released(const int& key);
};

#endif /* KEYBOARD_HANDLER_HPP */
