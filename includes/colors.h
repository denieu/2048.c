#ifndef COLORS_H
#define COLORS_H

//Include
#include <stdio.h>
#include <conio.h>
#ifdef __MINGW32__
#include <windows.h>
#endif

//Types
typedef enum {
  BLACK,
  RED,
  GREEN,
  BROWN,
  BLUE,
  MAGENTA,
  CYAN,
  LIGHTGRAY,
  DARKGRAY,
  LIGHTRED,
  LIGHTGREEN,
  YELLOW,
  LIGHTBLUE,
  LIGHTMAGENTA,
  LIGHTCYAN,
  WHITE,
} COLORS;

//Functions
void cr_resetColors();
void cr_bgColor(COLORS color);
void cr_textColor(COLORS color);
void cr_setColors(COLORS bgColor, COLORS textColor);
void cr_moveCursorXY(int x, int y);
void cr_clearScreen();

#endif /*COLORS_H*/