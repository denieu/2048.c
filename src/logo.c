/*------------------------------------------------------------------------------
 * 2048.c
 *
 * File: logo.c
 * Author: Daniel Wojcickoski
 * Date: 2021/04/28
 * 
 * MIT License - Copyright (c) 2021 Daniel Wojcickoski
 *----------------------------------------------------------------------------*/
#include "../includes/logo.h"

/*------------------------------------------------------------------------------
 * Macros
 *----------------------------------------------------------------------------*/
#define LOGO_CASE(key, constant) { \
  case key: \
    memcpy(letter, constant, MENU_LOGO_LINES * MENU_LOGO_COLUMNS); \
    break; \
};

/*------------------------------------------------------------------------------
 * Constants
 *----------------------------------------------------------------------------*/
const char charLogo2[MENU_LOGO_LINES][MENU_LOGO_COLUMNS] = {
  " #####  ",
  "#     # ",
  "      # ",
  " #####  ",
  "#       ",
  "#       ",
  "####### ",
};
const char charLogo0[MENU_LOGO_LINES][MENU_LOGO_COLUMNS] = {
  "  ###   ",
  " #   #  ",
  "#     # ",
  "#     # ",
  "#     # ",
  " #   #  ",
  "  ###   ",
};
const char charLogo4[MENU_LOGO_LINES][MENU_LOGO_COLUMNS] = {
  "#       ",
  "#    #  ",
  "#    #  ",
  "#    #  ",
  "####### ",
  "     #  ",
  "     #  ",
};
const char charLogo8[MENU_LOGO_LINES][MENU_LOGO_COLUMNS] = {
  " #####  ",
  "#     # ",
  "#     # ",
  " #####  ",
  "#     # ",
  "#     # ",
  " #####  ",
};
const char charLogoDot[MENU_LOGO_LINES][MENU_LOGO_COLUMNS] = {
  "   ",
  "   ",
  "   ",
  "   ",
  "   ",
  "   ",
  " # ",
};
const char charLogoC[MENU_LOGO_LINES][MENU_LOGO_COLUMNS] = {
  "       ",
  " ####  ",
  "#    # ",
  "#      ",
  "#      ",
  "#    # ",
  " ####  ",
};

/*------------------------------------------------------------------------------
 * Print in the position (X, Y) a letter of the logo, with the specified colors
 *----------------------------------------------------------------------------*/
void print_logoLetter(logoLetters_e selectedLetter, int posX, int posY, COLORS bgColor, COLORS textColor){
  char letter[MENU_LOGO_LINES][MENU_LOGO_COLUMNS] = {0};

  switch (selectedLetter){
    LOGO_CASE(LOGO_2, charLogo2);
    LOGO_CASE(LOGO_0, charLogo0);
    LOGO_CASE(LOGO_4, charLogo4);
    LOGO_CASE(LOGO_8, charLogo8);
    LOGO_CASE(LOGO_DOT, charLogoDot);
    LOGO_CASE(LOGO_C, charLogoC);
    default: return; break;
  }

  SET_COLOR(bgColor, textColor);

  for(int count = 0; count < MENU_LOGO_LINES; count++){
    cr_moveCursorXY(posX, posY + count);
    printf("%s", letter[count]);
  }

  SET_COLOR(DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
}