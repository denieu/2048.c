/*------------------------------------------------------------------------------
 * 2048.c
 *
 * File: screen.c
 * Author: Daniel Wojcickoski
 * Date: 2021/04/28
 * 
 * MIT License - Copyright (c) 2021 Daniel Wojcickoski
 *----------------------------------------------------------------------------*/
#include "../includes/screen.h"
#include "../includes/screen_components.h"
#include "../includes/logo.h"
#include "../includes/appState.h"

/*------------------------------------------------------------------------------
 * Thread control variables
 *----------------------------------------------------------------------------*/
bool screenIsUpdated = FALSE;
appState_t screenState = {0};

/*------------------------------------------------------------------------------
 * Changes the state of the cursor between visible and invisible
 *----------------------------------------------------------------------------*/
void setCursor(cursorState_e cursorState){
  CONSOLE_CURSOR_INFO info;
  info.dwSize = 100;
  info.bVisible = cursorState;
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

/*------------------------------------------------------------------------------
 * Adjust the terminal buffer to sizeX sizeY
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
 * Print the main menu screen
 *----------------------------------------------------------------------------*/
void screen_mainMenu(appState_t currentAppState){
  int menuXStart = 19;
  menuState_e menuState = currentAppState.screen.menuState;

  print_logoLetter(LOGO_2, menuXStart, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
  print_logoLetter(LOGO_0, menuXStart + 8, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
  print_logoLetter(LOGO_4, menuXStart + 16, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
  print_logoLetter(LOGO_8, menuXStart + 24, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
  print_logoLetter(LOGO_DOT, menuXStart + 31, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
  print_logoLetter(LOGO_C, menuXStart + 34, 3, DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);

  print_menuButton("Continuar", menuXStart + 11, 13, (menuState == STATE_MENU_CONTINUE) ? TRUE : FALSE);
  print_menuButton("Novo Jogo", menuXStart + 11, 15, (menuState == STATE_MENU_NEWGAME) ? TRUE : FALSE);
  print_menuButton("Sair", menuXStart + 11, 17, (menuState == STATE_MENU_EXIT) ? TRUE : FALSE);

  if(currentAppState.screen.menuState == STATE_MENU_CONTINUE_SELECT){
    print_querryUserString("Save a carregar", 27, 14, LIGHTGRAY, DARKGRAY);
  }
}

/*------------------------------------------------------------------------------
 * Paint the screen in game
 *----------------------------------------------------------------------------*/
void screen_inGame(appState_t * currentAppState){
  print_inGameMenu(3, 2);
  print_gameStatus(currentAppState->gameState, 3, 9);
  print_inGameRanking(&currentAppState->leaderboard, 3, 15);

  print_gameBoardEdges(28, 2);
  print_gameBoard(&currentAppState->gameState, 28, 2);

  switch (currentAppState->screen.gameState){
    case STATE_GAME_ESCAPE:
      print_querryUserString(" ", 27, 13, LIGHTRED, LIGHTGRAY);
      print_querryUserString("Sair [S]", 27, 14, LIGHTGRAY, LIGHTRED);
      break;

    case STATE_GAME_NEW:
      print_querryUserString(" ", 27, 13, LIGHTRED, LIGHTGRAY);
      print_querryUserString("Novo Jogo [S]", 27, 14, LIGHTGRAY, LIGHTRED);
      break;

    case STATE_GAME_SAVE:
      print_querryUserString("Nome do save", 27, 13, LIGHTRED, DARKGRAY);
      break;
    
    default: break;
  }
}

/*------------------------------------------------------------------------------
 * Print the end of match screen
 *----------------------------------------------------------------------------*/
void screen_endGame(appState_t * currentAppState){
  print_endGameStatus(currentAppState->gameState.gameStatus, 27, 7);

  print_gameStatus(currentAppState->gameState, 27, 13);

  print_querryUserString("Digite seu nome", 27, 19, LIGHTGRAY, DARKGRAY);
}

/*------------------------------------------------------------------------------
 * Updates the variables used in the thread to print the screen
 *----------------------------------------------------------------------------*/
void updateScreenState(appState_t * newScreenState){
  screenState = *newScreenState;
  screenIsUpdated = FALSE;
}

/*------------------------------------------------------------------------------
 * Thread responsible for showing the components on the screen
 *----------------------------------------------------------------------------*/
void *screenThread(){
  while(TRUE){
    if(screenIsUpdated == FALSE){
      SET_COLOR(DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
      setCursor(CURSOR_HIDDEN);
      SetConsoleTitleW(DEFAULT_SCREEN_TITLE);
      configScreenSize(DEFAULT_SCREEN_X_SIZE, DEFAULT_SCREEN_Y_SIZE);

      if(screenState.screen.lastScreen == SCREEN_NONE){
        configScreenSize(DEFAULT_SCREEN_X_SIZE, DEFAULT_SCREEN_Y_SIZE);
        cr_clearScreen();
      }

      if(screenState.screen.lastScreen != screenState.screen.currentScreen || screenState.screen.forceClear == TRUE){
        cr_clearScreen();
      }

      switch (screenState.screen.currentScreen){
        case SCREEN_MENU: 
        screen_mainMenu(screenState);
          break;

        case SCREEN_GAME:
          screen_inGame(&screenState);
          break;

        case SCREEN_ENDGAME:
          screen_endGame(&screenState);
          setCursor(CURSOR_VISIBLE);
          break;

        case SCREEN_RANKING:
          print_inGameRanking(&screenState.leaderboard, 27, 8);
          break;

        default:
          screenState.screen.currentScreen = SCREEN_MENU;
          break;
      }

      screenIsUpdated = TRUE;
    }

    Sleep(16);
  }
}
