#include "../includes/screen.h"
#include "../includes/logo.h"
#include "../includes/conio2.h" //gotoxy, textcolor, textbackground
#include "windows.h"            //SetConsoleCursorInfo

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
 * Printa na posição (X, Y) uma letra do logo, com as cores especificadas
 *----------------------------------------------------------------------------*/
void print_logoLetter(const char letter[][9], int posX, int posY, COLORS bgColor, COLORS textColor){
  textbackground(bgColor);
  textcolor(textColor);

  for(int count = 0; count < CHAR_LOGO_LINES; count++){
    gotoxy(posX, posY + count);
    printf("%s", letter[count]);
  }

  textbackground(DEFAULT_BG_COLOR);
  textcolor(DEFAULT_TEXT_COLOR);
}

/*------------------------------------------------------------------------------
 * Printa um botão para menu, selected define se o botão está o não selecionado
 *----------------------------------------------------------------------------*/
void print_menuButton(char * placeholder, int posX, int posY, bool selected){
  #define buttonWidth 36
  #define selectorWidth 3

  char selection[buttonWidth] = {0};
  int placeholderSize = strlen(placeholder);
  int numberOfSpaces = buttonWidth - placeholderSize - selectorWidth;

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
 * Printa a tela do menu principal
 *----------------------------------------------------------------------------*/
void screen_mainMenu(type_appState currentAppState){
  print_logoLetter(charLogo2, 10, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
  print_logoLetter(charLogo0, 18, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
  print_logoLetter(charLogo4, 26, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
  print_logoLetter(charLogo8, 34, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
  print_logoLetter(charLogoDot, 41, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
  print_logoLetter(charLogoC, 44, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);

  print_menuButton("Continuar", 12, 13, TRUE);
  print_menuButton("Novo Jogo", 12, 15, FALSE);
  print_menuButton("Ajuda", 12, 17, FALSE);
  print_menuButton("Sair", 12, 19, FALSE);
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
