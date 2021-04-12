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
  defaultAppState.screen.currentScreen = SCREEN_MENU;
  defaultAppState.screen.menuState = STATE_MENU_FIRST + 1;

  return defaultAppState;
}

/*------------------------------------------------------------------------------
 * Retorna um novo appState com base na ação realizada no appState atual
 *----------------------------------------------------------------------------*/
void handleUserAction(type_appState * appState){
  if(appState->userAction != ACTION_NONE){
    switch (appState->screen.currentScreen){
      case SCREEN_MENU:
        //Vai uma opção para cima
        if(appState->userAction == ACTION_UP){
          appState->screen.menuState--;
          if(appState->screen.menuState == STATE_MENU_FIRST)
            appState->screen.menuState = STATE_MENU_LAST - 1;
        }
        //Vai uma opção para baixo
        else if(appState->userAction == ACTION_DOWN){
          appState->screen.menuState++;
          if(appState->screen.menuState == STATE_MENU_LAST)
            appState->screen.menuState = STATE_MENU_FIRST + 1;
        }
        //Realiza a ação descrita no menu
        else if(appState->userAction == ACTION_ENTER){
          //Continuar um jogo
          if(appState->screen.menuState == STATE_MENU_CONTINUE){

            //Busca um arquivo de save e joga ele para o GameState

            appState->screen.currentScreen = SCREEN_GAME;
          }
          //Novo jogo
          else if(appState->screen.menuState == STATE_MENU_NEWGAME){
            //Seta o estado default inicial do jogo
            appState->gameState = getDefaultGameState();

            //Adiciona as duas cartas inicias ao tabuleiro
            addCardInBoard(&appState->gameState, 0);
            addCardInBoard(&appState->gameState, 0);

            //Redireciona para a tela de jogo
            appState->screen.currentScreen = SCREEN_GAME;
          }
          //Abrir a tela de ajuda
          else if(appState->screen.menuState == STATE_MENU_HELP){
            appState->screen.currentScreen = SCREEN_HELP;
          }
          //Sair da aplicação
          else if(appState->screen.menuState == STATE_MENU_EXIT){
            appState->appStatus = STATUS_OK;
          }
        }
        //Fecha a aplicação com status ok
        else if(appState->userAction == ACTION_ESCAPE){
          appState->appStatus = STATUS_OK;
        }
        break;

      case SCREEN_GAME:
        if(appState->userAction == ACTION_ESCAPE){
          appState->screen.currentScreen = SCREEN_MENU;
        }
        break;

      case SCREEN_ENDGAME:

        break;

      case SCREEN_HELP:
        if(appState->userAction == ACTION_ESCAPE){
          appState->screen.currentScreen = SCREEN_MENU;
        }
        break;

      default:
        appState->screen.currentScreen = SCREEN_MENU;
        break;
    }
  }
}
