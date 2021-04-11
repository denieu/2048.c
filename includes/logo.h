#ifndef  LOGO_H
#define  LOGO_H

//Includes
#include "../includes/main.h"
#include "../includes/conio2.h" //gotoxy, textcolor, textbackground

//Types
typedef enum enum_logoLetters{
  LOGO_2 = 0,
  LOGO_0,
  LOGO_4,
  LOGO_8,
  LOGO_DOT,
  LOGO_C,
} enum_logoLetters;

//Functions
void print_logoLetter(enum_logoLetters selectedLetter, int posX, int posY, COLORS bgColor, COLORS textColor);

#endif  /*LOGO_H*/