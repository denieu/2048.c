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
  enum_menuState menuState = currentAppState.screen.menuState;

  print_logoLetter(LOGO_2, menuXStart, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
  print_logoLetter(LOGO_0, menuXStart + 8, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
  print_logoLetter(LOGO_4, menuXStart + 16, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
  print_logoLetter(LOGO_8, menuXStart + 24, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
  print_logoLetter(LOGO_DOT, menuXStart + 31, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
  print_logoLetter(LOGO_C, menuXStart + 34, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);

  print_menuButton("Continuar", menuXStart + 12, 13, (menuState == STATE_MENU_CONTINUE) ? TRUE : FALSE);
  print_menuButton("Novo Jogo", menuXStart + 12, 15, (menuState == STATE_MENU_NEWGAME) ? TRUE : FALSE);
  print_menuButton("Ajuda", menuXStart + 12, 17, (menuState == STATE_MENU_HELP) ? TRUE : FALSE);
  print_menuButton("Sair", menuXStart + 12, 19, (menuState == STATE_MENU_EXIT) ? TRUE : FALSE);
}

/*------------------------------------------------------------------------------
 * Printa a tela dentro de jogo
 *----------------------------------------------------------------------------*/
void screen_inGame(type_appState * currentAppState){
  print_inGameMenu(2, 2);
  print_gameStatus(currentAppState->gameState, 2, 9);
  print_inGameRanking(currentAppState->leaderboard, 2, 15);

  print_gameBoardEdges(27, 2);
  print_gameBoard(&currentAppState->gameState, 27, 2);
}

/*------------------------------------------------------------------------------
 * Printa a tela atual com base no "currentAppState"
 *----------------------------------------------------------------------------*/
void printAppState(type_appState * currentAppState){
  //Esconde o cursos da tela
  setCursor(CURSOR_HIDDEN);

  //Limpa a tela
  clrscr();

  //Mostra a tela correta relativa a currentScreen
  switch (currentAppState->screen.currentScreen){
    case SCREEN_MENU:
      screen_mainMenu(*currentAppState);
      break;

    case SCREEN_GAME:
      screen_inGame(currentAppState);
      break;

    case SCREEN_ENDGAME:
      printf("Esta eh a tela de fim provisoria");
      break;

    case SCREEN_HELP:

      break;

    default:
      currentAppState->screen.currentScreen = SCREEN_MENU;
      break;
  }
}
