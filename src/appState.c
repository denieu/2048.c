/*------------------------------------------------------------------------------
 * 2048.c
 *
 * File: appState.c
 * Author: Daniel Wojcickoski
 * Date: 2021/04/28
 *
 * MIT License - Copyright (c) 2021 Daniel Wojcickoski
 *----------------------------------------------------------------------------*/
#include "../includes/appState.h"
#include "../includes/gameState.h"
#include "../includes/leaderboard.h"
#include "../includes/save.h"

/*------------------------------------------------------------------------------
 * Atualiza as variaveis relativas a tela
 *----------------------------------------------------------------------------*/
void changeScreenState(type_appState * appState, int screen, int menuState, int gameState, int forceClear){
  //Atualiza variaveis de tela
  if(screen != NO_CHANGE){
    appState->screen.lastScreen = appState->screen.currentScreen;
    appState->screen.currentScreen = screen;
  }

  //Atualiza menuState
  if(menuState != NO_CHANGE){
    appState->screen.menuState = menuState;
  }

  //Atualiza menuState
  if(gameState != NO_CHANGE){
    appState->screen.gameState = gameState;
  }

  //Atualiza menuState
  if(forceClear != NO_CHANGE){
    appState->screen.forceClear = forceClear;
  }
}

/*------------------------------------------------------------------------------
 * Retorna o appState default
 *----------------------------------------------------------------------------*/
type_appState getDefaultAppState(){
  type_appState defaultAppState = {0};

  //Variaveis de controle do app
  defaultAppState.appStatus = STATUS_RUNNING;

  //Variaveis de controle do jogo
  defaultAppState.gameState = getDefaultGameState();

  //Variaveis de controle da tela
  defaultAppState.screen.lastScreen = SCREEN_NONE;
  defaultAppState.screen.currentScreen = SCREEN_MENU;
  defaultAppState.screen.menuState = STATE_MENU_FIRST + 1;

  return defaultAppState;
}

/*------------------------------------------------------------------------------
 * Retorna um novo appState com base na ação realizada na tela de menu
 *----------------------------------------------------------------------------*/
void handleMenuAction(type_appState * appState){
  switch (appState->userAction){
    case ACTION_UP:
      appState->screen.menuState--;
      if(appState->screen.menuState == STATE_MENU_FIRST)
        appState->screen.menuState = STATE_MENU_LAST - 1;
      break;

    case ACTION_DOWN:
      appState->screen.menuState++;
      if(appState->screen.menuState == STATE_MENU_LAST)
        appState->screen.menuState = STATE_MENU_FIRST + 1;
      break;

    case ACTION_ENTER:
      switch (appState->screen.menuState){
        case STATE_MENU_CONTINUE:
          changeScreenState(appState, NO_CHANGE, STATE_MENU_CONTINUE_SELECT, NO_CHANGE, NO_CHANGE);
          break;

        case STATE_MENU_CONTINUE_SELECT:
          if(readSaveFile(appState, appState->userString) == TRUE)
            changeScreenState(appState, SCREEN_GAME, STATE_MENU_CONTINUE, NO_CHANGE, NO_CHANGE);
          else
            changeScreenState(appState, NO_CHANGE, STATE_MENU_CONTINUE, NO_CHANGE, TRUE);
          break;

        case STATE_MENU_NEWGAME:
          newGame(appState);
          break;

        case STATE_MENU_EXIT:
          appState->appStatus = STATUS_OK;
          break;

        default:break;
      }
      break;

    case ACTION_ESCAPE:
      appState->appStatus = STATUS_OK;
      break;

    default: break;
  }
}

/*------------------------------------------------------------------------------
 * Retorna um novo appState com base na ação realizada no appState atual
 *----------------------------------------------------------------------------*/
void handleUserAction(type_appState * appState){
  if(appState->userAction != ACTION_NONE){
    switch (appState->screen.currentScreen){
      case SCREEN_MENU:
        appState->screen.lastScreen = SCREEN_MENU;
        handleMenuAction(appState);
        break;

      case SCREEN_GAME:
        appState->screen.lastScreen = SCREEN_GAME;
        switch (appState->userAction){
          case ACTION_UP:
          case ACTION_DOWN:
          case ACTION_LEFT:
          case ACTION_RIGTH:
            handleGameAction(appState);
            break;

          case ACTION_GAME_PRE_NEW:
            changeScreenState(appState, NO_CHANGE, NO_CHANGE, STATE_GAME_NEW, NO_CHANGE);
            break;

          case ACTION_GAME_NEW:
            changeScreenState(appState, NO_CHANGE, NO_CHANGE, STATE_GAME_NORMAL, TRUE);
            newGame(appState);
            break;

          case ACTION_GAME_UNDO:
            undoGameAction(appState);
            break;

          case ACTION_GAME_PRE_SAVE:
            changeScreenState(appState, NO_CHANGE, NO_CHANGE, STATE_GAME_SAVE, NO_CHANGE);
            break;

          case ACTION_GAME_SAVE:
            writeSaveFile(&appState->gameState, appState->userString);
            changeScreenState(appState, NO_CHANGE, NO_CHANGE, STATE_GAME_NORMAL, TRUE);
            break;

          case ACTION_PRE_ESCAPE:
            changeScreenState(appState, NO_CHANGE, NO_CHANGE, STATE_GAME_ESCAPE, NO_CHANGE);
            break;

          case ACTION_ESCAPE:
            changeScreenState(appState, SCREEN_MENU, NO_CHANGE, STATE_GAME_NORMAL, TRUE);
            break;

          case ACTION_NO_ESCAPE:
            changeScreenState(appState, NO_CHANGE, NO_CHANGE, STATE_GAME_NORMAL, TRUE);
            break;

          default:
            changeScreenState(appState, SCREEN_GAME, NO_CHANGE, STATE_GAME_NORMAL, TRUE);
            break;
        }
        break;

      case SCREEN_ENDGAME:
        appState->screen.lastScreen = SCREEN_ENDGAME;
        switch (appState->userAction){
           case ACTION_ENTER:
            //Adiciona o novo resultado a struct leaderboard na ultima posição, que não aparece na tela
            strcpy(appState->leaderboard.name[10], appState->userString);
            appState->leaderboard.points[10] = appState->gameState.score;

            //Organiza a struct em ordem decrescente
            bubbleSortLeaderboard(&appState->leaderboard);

            //Salva a struct em arquivo
            writeLeaderboardFile(&appState->leaderboard);

            changeScreenState(appState, SCREEN_RANKING, NO_CHANGE, NO_CHANGE, NO_CHANGE);
            break;

          case ACTION_ESCAPE:
            changeScreenState(appState, SCREEN_MENU, NO_CHANGE, NO_CHANGE, NO_CHANGE);
            break;

          default: break;
        }
        break;

      case SCREEN_RANKING:
        switch (appState->userAction){
           case ACTION_ENTER:
            changeScreenState(appState, SCREEN_MENU, NO_CHANGE, NO_CHANGE, NO_CHANGE);
            break;

          default: break;
        }
        break;

      default:
        changeScreenState(appState, SCREEN_MENU, NO_CHANGE, NO_CHANGE, NO_CHANGE);
        break;
    }
  }
}
