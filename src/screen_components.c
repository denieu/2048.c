#include "../includes/screen_components.h"
#include "../includes/conio2.h" //gotoxy, textcolor, textbackground
#include "windows.h"  

/*------------------------------------------------------------------------------
 * Printa um botão para menu, selected define se o botão está o não selecionado
 *----------------------------------------------------------------------------*/
void print_menuButton(char * placeholder, int posX, int posY, bool selected){
  char selection[WIDTH_BUTTON_MENU + 1] = {0};
  int placeholderSize = strlen(placeholder);
  int numberOfSpaces = WIDTH_BUTTON_MENU - placeholderSize - WIDTH_MENU_SELECTOR;

  for(int count = 0; count < numberOfSpaces ; count++)
    selection[count] = ' ';

  selection[numberOfSpaces] = '<';
  selection[numberOfSpaces + 1] = '-';
  selection[numberOfSpaces + 2] = '-';
  selection[numberOfSpaces + 3] = '\0';

  gotoxy(posX, posY);

  if(selected == TRUE)
    textcolor(RED);

  printf("%s%s", placeholder, (selected == TRUE) ? selection : ""); 

  textbackground(DEFAULT_BG_COLOR);
  textcolor(DEFAULT_TEXT_COLOR);
}

/*------------------------------------------------------------------------------
 * Printa a tela dentro de jogo
 *----------------------------------------------------------------------------*/
void print_inGameButton(char * placeholder, int posX, int posY){
  char border[WIDTH_BUTTON_INGAME] = {0};
  char spaces[WIDTH_BUTTON_INGAME] = {0};
  int placeholderSize = strlen(placeholder);
  int numberOfSpaces = (WIDTH_BUTTON_INGAME - placeholderSize) / 2;

  for(int count = 0; count < WIDTH_BUTTON_INGAME ; count++)
    border[count] = '-';

  for(int count = 0; count < numberOfSpaces ; count++)
    spaces[count] = ' ';

  gotoxy(posX, posY);

  printf("%s%s\n", spaces, placeholder);
  printf("%s", border);

  textbackground(DEFAULT_BG_COLOR);
  textcolor(DEFAULT_TEXT_COLOR);
}