#include "../includes/logo.h"

//Constants
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
 * Printa na posição (X, Y) uma letra do logo, com as cores especificadas
 *----------------------------------------------------------------------------*/
void print_logoLetter(enum_logoLetters selectedLetter, int posX, int posY, COLORS bgColor, COLORS textColor){
  char letter[MENU_LOGO_LINES][MENU_LOGO_COLUMNS] = {0};

  switch (selectedLetter){
    case LOGO_2: memcpy(letter, charLogo2, MENU_LOGO_LINES * MENU_LOGO_COLUMNS);
      break;
    case LOGO_0: memcpy(letter, charLogo0, MENU_LOGO_LINES * MENU_LOGO_COLUMNS);
      break;
    case LOGO_4: memcpy(letter, charLogo4, MENU_LOGO_LINES * MENU_LOGO_COLUMNS);
      break;
    case LOGO_8: memcpy(letter, charLogo8, MENU_LOGO_LINES * MENU_LOGO_COLUMNS);
      break;
    case LOGO_DOT: memcpy(letter, charLogoDot, MENU_LOGO_LINES * MENU_LOGO_COLUMNS);
      break;
    case LOGO_C: memcpy(letter, charLogoC, MENU_LOGO_LINES * MENU_LOGO_COLUMNS);
      break;
    default:
      return;
      break;
  }

  SET_COLOR(bgColor, textColor);

  for(int count = 0; count < MENU_LOGO_LINES; count++){
    gotoxy(posX, posY + count);
    printf("%s", letter[count]);
  }

  SET_COLOR(DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
}