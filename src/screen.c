#include "../includes/screen.h"
#include "windows.h" //SetConsoleCursorInfo
#include "../includes/conio2.h" //gotoxy, textcolor, textbackground

//Constants
#define DEFAULT_BG_COLOR BLACK
#define DEFAULT_TEXT_COLOR LIGHTGRAY
#define CHAR_LOGO_LINES 7       //Numero de linhas das letras do logo
const char charLogo2[7][9] = {
  " #####  ",
  "#     # ",
  "      # ",
  " #####  ",
  "#       ",
  "#       ",
  "####### ",
};
const char charLogo0[7][9] = {
  "  ###   ",
  " #   #  ",
  "#     # ",
  "#     # ",
  "#     # ",
  " #   #  ",
  "  ###   ",
};
const char charLogo4[7][9] = {
  "#       ",
  "#    #  ",
  "#    #  ",
  "#    #  ",
  "####### ",
  "     #  ",
  "     #  ",
};
const char charLogo8[7][9] = {
  " #####  ",
  "#     # ",
  "#     # ",
  " #####  ",
  "#     # ",
  "#     # ",
  " #####  ",
};
const char charLogoDot[7][9] = {
  "   ",
  "   ",
  "   ",
  "   ",
  "   ",
  "   ",
  " # ",
};
const char charLogoC[7][9] = {
  "       ",
  " ####  ",
  "#    # ",
  "#      ",
  "#      ",
  "#    # ",
  " ####  ",
};
const char charLogoDefault[7][9] = {
  "####### ",
  "####### ",
  "####### ",
  "####### ",
  "####### ",
  "####### ",
  "####### ",
};

/*------------------------------------------------------------------------------
 * Altera o estado do cursor entre visivel e invisivel
 *----------------------------------------------------------------------------*/
void setCursor(enum_cursorState cursorState){
  CONSOLE_CURSOR_INFO info;
  info.dwSize = 100;
  info.bVisible = cursorState;
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

/*------------------------------------------------------------------------------
 * Printa uma das letras do logo na posição (X, Y)
 *----------------------------------------------------------------------------*/
void print_logoPart(const char letter[][9], int posX, int posY){
    for(int count = 0; count < CHAR_LOGO_LINES; count++){
        gotoxy(posX, posY + count);
        printf("%s", letter[count]);
      }
  }

/*------------------------------------------------------------------------------
 * Printa na posição (X, Y) uma letra do logo, com as cores especificadas
 *----------------------------------------------------------------------------*/
void print_logoLetter(enum_logoChar letter, int posX, int posY, COLORS bgColor, COLORS textColor){
  textbackground(bgColor);
  textcolor(textColor);

  switch (letter){
    case LOGO_2: print_logoPart(charLogo2, posX, posY);
      break;

    case LOGO_0: print_logoPart(charLogo0, posX, posY);
      break;

    case LOGO_4: print_logoPart(charLogo4, posX, posY);
      break;

    case LOGO_8: print_logoPart(charLogo8, posX, posY);
      break;

    case LOGO_DOT: print_logoPart(charLogoDot, posX, posY);
      break;

    case LOGO_C: print_logoPart(charLogoC, posX, posY);
      break;

    default: print_logoPart(charLogoDefault, posX, posY);
      break;
  }

  textbackground(DEFAULT_BG_COLOR);
  textcolor(DEFAULT_TEXT_COLOR);
}

/*------------------------------------------------------------------------------
 * Printa um botão para menu, selected define se o botão está o não selecionado
 *----------------------------------------------------------------------------*/
void print_menuButton(char * placeholder, int posX, int posY, bool selected){
  gotoxy(posX, posY);

  #define buttonWidth 11

  char spaces[buttonWidth] = {0};
  int placeholdSize = strlen(placeholder);
  int numberOfSpaces = (buttonWidth - placeholdSize) / 2;
  for(int count = 0; count < numberOfSpaces ; count++){
    spaces[count] = ' ';
    if(count == numberOfSpaces - 1){
      spaces[count + 1] = '\0';
    }
  }

  printf("+-----------+"); gotoxy(posX, posY + 1);
  printf("|%s%s%s|", spaces, placeholder, spaces); gotoxy(posX, posY + 2);
  printf("+-----------+");
}

/*------------------------------------------------------------------------------
 * Printa a tela do menu principal
 *----------------------------------------------------------------------------*/
void screen_mainMenu(type_appState currentAppState){
  print_logoLetter(LOGO_2, 10, 3, DEFAULT_BG_COLOR, BLUE);
  print_logoLetter(LOGO_0, 18, 3, DEFAULT_BG_COLOR, GREEN);
  print_logoLetter(LOGO_4, 26, 3, DEFAULT_BG_COLOR, CYAN);
  print_logoLetter(LOGO_8, 34, 3, DEFAULT_BG_COLOR, RED);
  print_logoLetter(LOGO_DOT, 41, 3, DEFAULT_BG_COLOR, MAGENTA);
  print_logoLetter(LOGO_C, 44, 3, DEFAULT_BG_COLOR, BROWN);

  print_menuButton("Teste", 24, 11, TRUE);
}

/*------------------------------------------------------------------------------
 * Printa a tela dentro de jogo
 *----------------------------------------------------------------------------*/
void screen_inGame(type_appState currentAppState){

}

/*------------------------------------------------------------------------------
 * Printa a tela atual com base no "currentAppState"
 *----------------------------------------------------------------------------*/
void printAppState(type_appState currentAppState){
  //Esconde o cursos da tela
  setCursor(CURSOR_HIDDEN);

  //Printa tela menu - Raissa
  screen_mainMenu(currentAppState);
  getch();

  clrscr();

  //Printa tela jogo - Daniel
  screen_inGame(currentAppState);
  getch();
  //Printa tela de pausa

  //Printa tela instruções

  //Printa tela fim de partida

}
