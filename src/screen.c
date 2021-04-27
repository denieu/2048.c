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
 * Ajusta a tela para o tamanho correto
 * para impedir o usuario de redimensionar para um tamanho incorreto
 *----------------------------------------------------------------------------*/
void configScreenSize(int sizeX, int sizeY){
  HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
  SMALL_RECT sr;
  COORD consoleSize;

  consoleSize.X = sizeX;
  consoleSize.Y = sizeY;

  sr.Top = sr.Left = 0;
  sr.Right = consoleSize.X - 1;
  sr.Bottom = consoleSize.Y - 1;

  SetConsoleWindowInfo(console, TRUE, &sr);
  SetConsoleScreenBufferSize(console, consoleSize);
}

/*------------------------------------------------------------------------------
 * Printa a tela do menu principal
 *----------------------------------------------------------------------------*/
void screen_mainMenu(type_appState currentAppState){
  int menuXStart = 19;
  enum_menuState menuState = currentAppState.screen.menuState;

  print_logoLetter(LOGO_2, menuXStart, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
  print_logoLetter(LOGO_0, menuXStart + 8, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
  print_logoLetter(LOGO_4, menuXStart + 16, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
  print_logoLetter(LOGO_8, menuXStart + 24, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
  print_logoLetter(LOGO_DOT, menuXStart + 31, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
  print_logoLetter(LOGO_C, menuXStart + 34, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);

  print_menuButton("Continuar", menuXStart + 11, 13, (menuState == STATE_MENU_CONTINUE) ? TRUE : FALSE);
  print_menuButton("Novo Jogo", menuXStart + 11, 15, (menuState == STATE_MENU_NEWGAME) ? TRUE : FALSE);
  print_menuButton("Ajuda", menuXStart + 11, 17, (menuState == STATE_MENU_HELP) ? TRUE : FALSE);
  print_menuButton("Sair", menuXStart + 11, 19, (menuState == STATE_MENU_EXIT) ? TRUE : FALSE);
}

/*------------------------------------------------------------------------------
 * Printa a tela dentro de jogo
 *----------------------------------------------------------------------------*/
void screen_inGame(type_appState * currentAppState){
  print_inGameMenu(3, 2);
  print_gameStatus(currentAppState->gameState, 3, 9);
  print_inGameRanking(&currentAppState->leaderboard, 3, 15);

  print_gameBoardEdges(28, 2);
  print_gameBoard(&currentAppState->gameState, 28, 2);
}

/*------------------------------------------------------------------------------
 * Printa a tela de fim de partida
 *----------------------------------------------------------------------------*/
void screen_endGame(type_appState * currentAppState){
  print_endGameStatus(currentAppState->gameState.gameStatus, 27, 7);

  print_gameStatus(currentAppState->gameState, 27, 13);

  print_querryUserString("Digite seu nome", 27, 19, LIGHTGRAY, DARKGRAY);
}

/*------------------------------------------------------------------------------
 * Printa a tela atual com base no "currentAppState"
 *----------------------------------------------------------------------------*/
void printAppState(type_appState * currentAppState){
  //Seta as cores para as default
  SET_COLOR(DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);

  //Esconde o cursos da tela
  setCursor(CURSOR_HIDDEN);

  //Seta o titulo do terminal
  SetConsoleTitleW(DEFAULT_SCREEN_TITLE);

  //Isso faz a tela ficar correta após a inicialização do app
  if(currentAppState->screen.lastScreen == SCREEN_NONE){
    configScreenSize(DEFAULT_SCREEN_X_SIZE, DEFAULT_SCREEN_Y_SIZE);
    clrscr();
  }

  //Ajusta o tamanho da tela
  configScreenSize(DEFAULT_SCREEN_X_SIZE, DEFAULT_SCREEN_Y_SIZE);

  //Limpa a tela se a tela mudou
  if(currentAppState->screen.lastScreen != currentAppState->screen.currentScreen ||
     currentAppState->screen.lastPopup != currentAppState->screen.currentPopup)
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
      screen_endGame(currentAppState);
      setCursor(CURSOR_VISIBLE);
      break;

    case SCREEN_HELP:

      break;

    default:
      currentAppState->screen.currentScreen = SCREEN_MENU;
      break;
  }

  switch (currentAppState->screen.currentPopup){
    case POPUP_SAVE:
      print_querryUserString("Nome do save", 27, 13, LIGHTRED, DARKGRAY);
      break;

    case POPUP_ESCAPE:
      print_querryUserString(" ", 27, 13, LIGHTRED, LIGHTGRAY);
      print_querryUserString("Para sair tecle [S]", 27, 14, LIGHTGRAY, LIGHTRED);
      break;
    
    default:
      currentAppState->screen.currentPopup = POPUP_NONE;
      break;
  }
}
