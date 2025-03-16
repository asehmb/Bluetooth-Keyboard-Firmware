

#ifndef KEYPAD_H
#define KEYPAD_H

#define ROWS 6
#define COLS 4
#define DEBOUNCE 4

#define ROW_PINS {4, 5, 6, 7, 8, 9}
#define COL_PINS {15, 14, 16, 10}


#define OLED 1

extern int keymap[ROWS][COLS];  // Declare the keymap variable

#endif