#include "../includes/gameState.h"

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
 * Verifica se o tabuleiro de jogo atual possui alguma casa livre
 *
 * Retorna TRUE caso tenha pelo menos uma casa livre
 * Retorna FALSE caso não tenha nenhuma casa livre
 *----------------------------------------------------------------------------*/
bool verifyFreeHouse(type_gameState gameState){
  for(int line = 0; line < 4; line++){
    for(int collumn = 0; collumn < 4; collumn++){
      if(gameState.gameBoard[line][collumn] == NULL){
        //O tabuleiro possui pelo menos uma casa livre
        return TRUE;
      }
    }
  }

  //O tabuleiro não possui nenhuma casa livre
  return FALSE;
}

/*------------------------------------------------------------------------------
 * Adiciona uma peça ao tabuleiro de jogo gameBoard
 *
 * chanceToDouble:
 *   define a chance(0 - 100%) de dobrar o valor da peça inicial(de 2 para 4)
 *
 * Retorna TRUE caso consiga adicionar a peça ao tabuleiro
 * Retorna FALSE caso não consiga
 *----------------------------------------------------------------------------*/
bool addCardInBoard(type_gameState * gameState, int chanceToDouble){
  //O valor default é o da carta 2
  enum_gameCards newCardIndex = CARD2 - 1;

  //Verifica com base em chanceToDouble se pode dobrar o valor da carta
  srand(time(NULL));
  if((rand() % 100) <= chanceToDouble && chanceToDouble != 0){
    newCardIndex = CARD4 - 1;
  }

  while(TRUE){
    //Coloca em uma casa aleatoria o valor newCardValue
    int house = (rand() % 16);
    int line = house / 4;
    int collumn = house % 4;

    //Verifica se é uma casa livre
    if(gameState->gameBoard[line][collumn] == NULL){
      gameState->gameBoard[line][collumn] = &gameState->gameCards[newCardIndex];
      return TRUE;
    }

    //Verifica se o tabuleiro ainda possui alguma casa livre
    if(verifyFreeHouse(*gameState) == FALSE){
      //Não havia nenhuma casa livre no tabuleiro
      return FALSE;
    }
  }

  //Não havia nenhuma casa livre no tabuleiro
  return FALSE;
}

void toUp(type_appState * appState){
  for(int collumn = 0; collumn < 4; collumn++){
    for(int line = 3; line > 0; line--){
      // Caso essa linha não seja vazia
      if(appState->gameState.gameBoard[line][collumn] != NULL){

        //Joga pra cima o que der
        if(appState->gameState.gameBoard[line - 1][collumn] == NULL){
          appState->gameState.gameBoard[line - 1][collumn] = appState->gameState.gameBoard[line][collumn];
          appState->gameState.gameBoard[line][collumn] = NULL;
        }
      }
    }
  }
}

void toDown(type_appState * appState){
  for(int collumn = 0; collumn < 4; collumn++){
    for(int line = 0; line < 3; line++){
      // Caso essa linha não seja vazia
      if(appState->gameState.gameBoard[line][collumn] != NULL){

        //Joga pra baixo o que der
        if(appState->gameState.gameBoard[line + 1][collumn] == NULL){
          appState->gameState.gameBoard[line + 1][collumn] = appState->gameState.gameBoard[line][collumn];
          appState->gameState.gameBoard[line][collumn] = NULL;
        }
      }
    }
  }
}

/*------------------------------------------------------------------------------
 * Altera o appState com base na ação realizada dentro do jogo
 *----------------------------------------------------------------------------*/
void handleGameAction(type_appState * appState){
  switch (appState->userAction){
    case ACTION_UP:
      for(int collumn = 0; collumn < 4; collumn++){
        for(int line = 1; line < 4; line++){
          toUp(appState);

          if(appState->gameState.gameBoard[line][collumn] != NULL){
            if(*appState->gameState.gameBoard[line - 1][collumn] == *appState->gameState.gameBoard[line][collumn]){
              int newValue = *appState->gameState.gameBoard[line - 1][collumn];
              appState->gameState.gameBoard[line - 1][collumn] = &appState->gameState.gameCards[newValue];
              appState->gameState.gameBoard[line][collumn] = NULL;

              toUp(appState);
              line--;
              continue;
            }
          }
        }
      }
      break;

    case ACTION_DOWN:
      for(int collumn = 0; collumn < 4; collumn++){
        for(int line = 2; line >= 0; line--){
          toDown(appState);

          if(appState->gameState.gameBoard[line][collumn] != NULL){
            if(*appState->gameState.gameBoard[line + 1][collumn] == *appState->gameState.gameBoard[line][collumn]){
              int newValue = *appState->gameState.gameBoard[line + 1][collumn];
              appState->gameState.gameBoard[line + 1][collumn] = &appState->gameState.gameCards[newValue];
              appState->gameState.gameBoard[line][collumn] = NULL;

              toDown(appState);
              line++;
              continue;
            }
          }
        }
      }
      break;

    case ACTION_LEFT:

      break;

    case ACTION_RIGTH:

      break;

    default:
      return;
      break;
  }
  addCardInBoard(&appState->gameState, 10);
}
