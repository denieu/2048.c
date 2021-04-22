#include "../includes/appState.h"
#include "../includes/gameState.h"

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
  defaultAppState.screen.lastScreen = SCREEN_MENU;
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
          //Busca um arquivo de save e joga ele para o GameState

          appState->screen.currentScreen = SCREEN_GAME;
          break;

        case STATE_MENU_NEWGAME:
          //Seta o estado default inicial do jogo
          appState->gameState = getDefaultGameState();

          //Adiciona as duas cartas inicias ao tabuleiro
          addCardInBoard(&appState->gameState, 0);
          addCardInBoard(&appState->gameState, 0);

          //Redireciona para a tela de jogo
          appState->screen.currentScreen = SCREEN_GAME;
          break;

        case STATE_MENU_HELP:
          appState->screen.currentScreen = SCREEN_HELP;
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
            break;

          case ACTION_ESCAPE:
            appState->screen.currentScreen = SCREEN_MENU;
            break;

          default:break;
        }
        break;

      case SCREEN_ENDGAME:
        appState->screen.lastScreen = SCREEN_ENDGAME;
        switch (appState->userAction){
          case ACTION_ESCAPE:
            appState->screen.currentScreen = SCREEN_MENU;
            break;

          default:break;
        }
        break;

      case SCREEN_HELP:
        appState->screen.lastScreen = SCREEN_HELP;
        switch (appState->userAction){
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
