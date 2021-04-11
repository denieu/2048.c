#include "../includes/appState.h"

/*------------------------------------------------------------------------------
 * Retorna o gameState default
 *----------------------------------------------------------------------------*/
type_gameState getDefaultGameState(){
  type_gameState defaultGameState = {0};
  defaultGameState.score = 0;
  defaultGameState.moves = 0;

  //Alocando estrutura das cartas
  for(int card = 0; card < 11; card++){
    defaultGameState.gameCards[card] = card + 1;
  }

  //Zerando tabuleiro de jogo
  for(int count1 = 0; count1 < 4; count1++){
     for(int count2 = 0; count2 < 4; count2++){
      defaultGameState.gameBoard[count1][count2] = NULL;
    }
  }

  return defaultGameState;
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
  defaultAppState.screen.currentScreen = SCREEN_MENU;
  defaultAppState.screen.menuState = STATE_MENU_FIRST + 1;

  return defaultAppState;
}

/*------------------------------------------------------------------------------
 * Retorna um novo appState com base na ação realizada no appState atual
 *----------------------------------------------------------------------------*/
type_appState handleUserAction(type_appState currentAppState){
  type_appState newAppState = currentAppState;

  if(newAppState.userAction != ACTION_NONE){
    switch (newAppState.screen.currentScreen){
      case SCREEN_MENU:
        //Vai uma opção para cima
        if(newAppState.userAction == ACTION_UP){
          newAppState.screen.menuState--;
          if(newAppState.screen.menuState == STATE_MENU_FIRST)
            newAppState.screen.menuState = STATE_MENU_LAST - 1;
        }
        //Vai uma opção para baixo
        else if(newAppState.userAction == ACTION_DOWN){
          newAppState.screen.menuState++;
          if(newAppState.screen.menuState == STATE_MENU_LAST)
            newAppState.screen.menuState = STATE_MENU_FIRST + 1;
        }
        //Realiza a ação descrita no menu
        else if(newAppState.userAction == ACTION_ENTER){
          //Continuar um jogo
          if(newAppState.screen.menuState == STATE_MENU_CONTINUE){

            //Busca um arquivo de save e joga ele para o GameState

            newAppState.screen.currentScreen = SCREEN_GAME;
          }
          //Novo jogo
          else if(newAppState.screen.menuState == STATE_MENU_NEWGAME){
            newAppState.screen.currentScreen = SCREEN_GAME;
          }
          //Abrir a tela de ajuda
          else if(newAppState.screen.menuState == STATE_MENU_HELP){
            newAppState.screen.currentScreen = SCREEN_HELP;
          }
          //Sair da aplicação
          else if(newAppState.screen.menuState == STATE_MENU_EXIT){
            newAppState.appStatus = STATUS_OK;
          }
        }
        //Fecha a aplicação com status ok
        else if(newAppState.userAction == ACTION_ESCAPE){
          newAppState.appStatus = STATUS_OK;
        }
        break;

      case SCREEN_GAME:
        if(newAppState.userAction == ACTION_ESCAPE){
          newAppState.screen.currentScreen = SCREEN_MENU;
        }
        break;

      case SCREEN_ENDGAME:

        break;

      case SCREEN_HELP:
        if(newAppState.userAction == ACTION_ESCAPE){
          newAppState.screen.currentScreen = SCREEN_MENU;
        }
        break;
      
      default:
        newAppState.screen.currentScreen = SCREEN_MENU;
        break;
    }
  }

  return newAppState;
}
