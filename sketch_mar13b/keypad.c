#include "usb_hid_keys.h"
#include "keypad.h"


int keymap[6][4] = {
    {KEY_PAGEDOWN, KEY_PAGEUP, KEY_HOME, KEY_INSERT},
    {KEY_NUMLOCK, KEY_KPSLASH, KEY_KPASTERISK, KEY_KPMINUS},
    {KEY_KP7, KEY_KP8, KEY_KP9, KEY_KPPLUS},
    {KEY_KP4, KEY_KP5, KEY_KP6, KEY_NONE},
    {KEY_KP1, KEY_KP2, KEY_KP3, KEY_KPENTER},
    {KEY_KP0, KEY_NONE, KEY_KPDOT, KEY_NONE}
};
