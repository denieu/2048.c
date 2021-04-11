#include "../includes/screen.h"
#include "../includes/screen_components.h"
#include "../includes/logo.h"
#include "windows.h"    

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
 * Printa a tela do menu principal
 *----------------------------------------------------------------------------*/
void screen_mainMenu(type_appState currentAppState){
  int menuXStart = 10;

  print_logoLetter(LOGO_2, menuXStart, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
  print_logoLetter(LOGO_0, menuXStart + 8, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
  print_logoLetter(LOGO_4, menuXStart + 16, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
  print_logoLetter(LOGO_8, menuXStart + 24, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
  print_logoLetter(LOGO_DOT, menuXStart + 31, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
  print_logoLetter(LOGO_C, menuXStart + 34, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);

  print_menuButton("Continuar", menuXStart + 12, 13, FALSE);
  print_menuButton("Novo Jogo", menuXStart + 12, 15, FALSE);
  print_menuButton("Ajuda", menuXStart + 12, 17, FALSE);
  print_menuButton("Sair", menuXStart + 12, 19, FALSE);
}

/*------------------------------------------------------------------------------
 * Printa a tela dentro de jogo
 *----------------------------------------------------------------------------*/
void screen_inGame(type_appState currentAppState){
  print_inGameMenu(2, 2);
  print_gameStatus(currentAppState.gameState, 2, 9);
  print_inGameRanking(currentAppState.leaderboard, 2, 15);
  print_gameBoard(currentAppState.gameState, 27, 2);
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
  clrscr();

  //Printa tela de pausa

  //Printa tela instruções

  //Printa tela fim de partida

}
