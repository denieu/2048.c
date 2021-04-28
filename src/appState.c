#include "../includes/appState.h"
#include "../includes/gameState.h"
#include "../includes/leaderboard.h"
#include "../includes/save.h"

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
          appState->screen.menuState = STATE_MENU_CONTINUE_SELECT;
          break;

        case STATE_MENU_CONTINUE_SELECT:
          appState->screen.menuState = STATE_MENU_CONTINUE;

          if(readSaveFile(appState, appState->userString) == TRUE)
            appState->screen.currentScreen = SCREEN_GAME;
          else
            appState->screen.forceClear = TRUE;
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

    default:
      break;
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
            appState->screen.gameState = STATE_GAME_NORMAL;
            break;

          case ACTION_GAME_NEW:
            newGame(appState);
            break;

          case ACTION_GAME_UNDO:
            undoGameAction(appState);
            break;

          case ACTION_GAME_PRE_SAVE:
            appState->screen.gameState = STATE_GAME_SAVE;
            break;

          case ACTION_GAME_SAVE:
            writeSaveFile(&appState->gameState, appState->userString);
            appState->screen.forceClear = TRUE;
            appState->screen.gameState = STATE_GAME_NORMAL;
            break;

          case ACTION_PRE_ESCAPE:
            appState->screen.gameState = STATE_GAME_ESCAPE;
            break;

          case ACTION_ESCAPE:
            appState->screen.forceClear = TRUE;
            appState->screen.gameState = STATE_GAME_NORMAL;
            appState->screen.currentScreen = SCREEN_MENU;
            break;

          case ACTION_NO_ESCAPE:
            appState->screen.forceClear = TRUE;
            appState->screen.gameState = STATE_GAME_NORMAL;
            break;

          default:
            appState->screen.gameState = STATE_GAME_NORMAL;
            break;
        }
        break;

      case SCREEN_ENDGAME:
        appState->screen.lastScreen = SCREEN_ENDGAME;
        switch (appState->userAction){
           case ACTION_ENTER:
            //Adiciona o novo resultado a struct leaderboard na ultima posição, que não aparece na tela
            strcpy(appState->leaderboard.name[11], appState->userString);
            appState->leaderboard.points[11] = appState->gameState.score;

            //Organiza a struct em ordem decrescente
            bubbleSortLeaderboard(&appState->leaderboard);

            //Salva a struct em arquivo
            writeLeaderboardFile(&appState->leaderboard);

            appState->screen.currentScreen = SCREEN_MENU;
            break;

          case ACTION_ESCAPE:
            appState->screen.currentScreen = SCREEN_MENU;
            break;

          default:break;
        }
        break;

      default:
        appState->screen.currentScreen = SCREEN_MENU;
        break;
    }
  }
}
