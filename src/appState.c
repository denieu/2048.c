#include "../includes/appState.h"

/*------------------------------------------------------------------------------
 * Retorna o gameState default
 *----------------------------------------------------------------------------*/
type_gameState getDefaultGameState(){
  type_gameState defaultGameState = {0};
  defaultGameState.score = 0;
  defaultGameState.moves = 0;

  //Alocando estrutura das cartas
  for(int card = 1; card <= 11; card++){
    defaultGameState.gameCards[card] = card;
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

  return defaultAppState;
}

/*------------------------------------------------------------------------------
 * Retorna um novo appState com base na ação realizada no appState atual
 *----------------------------------------------------------------------------*/
type_appState handleUserAction(type_appState currentAppState){
  return currentAppState;
}