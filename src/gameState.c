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

/*------------------------------------------------------------------------------
 * Rotaciona o tabuleiro de jogo "repeat" vezes para o lado "direction"
 *
 * X: Numero de vezes que o tabuleiro sera rotacionado
 * Y: 0 = Tabuleiro será rotacionado para a direita
 *    1 = Tabuleiro será rotacionado para a esquerda
 *----------------------------------------------------------------------------*/
void rotateGameBoard(type_appState * appState, int repeat, enum_direction direction){
  if(repeat > 0){
    type_gameState oldGameState = appState->gameState;
    int position[4] = {3, 2, 1, 0};

    if(direction == LEFT){
      for(int count = 0; count < 4; count++){
          appState->gameState.gameBoard[count][0] = oldGameState.gameBoard[0][position[count]];
          appState->gameState.gameBoard[count][1] = oldGameState.gameBoard[1][position[count]];
          appState->gameState.gameBoard[count][2] = oldGameState.gameBoard[2][position[count]];
          appState->gameState.gameBoard[count][3] = oldGameState.gameBoard[3][position[count]];
      }
    }
    if(direction == RIGHT){
      for(int count = 0; count < 4; count++){
          appState->gameState.gameBoard[count][0] = oldGameState.gameBoard[3][count];
          appState->gameState.gameBoard[count][1] = oldGameState.gameBoard[2][count];
          appState->gameState.gameBoard[count][2] = oldGameState.gameBoard[1][count];
          appState->gameState.gameBoard[count][3] = oldGameState.gameBoard[0][count];
      }
    }
    else {
      return;
    }

    rotateGameBoard(appState, repeat - 1, direction);
  }
}

/*------------------------------------------------------------------------------
 * Altera o appState com base na ação realizada dentro do jogo
 *----------------------------------------------------------------------------*/
void handleGameAction(type_appState * appState){
  //Rotaciona tabuleiro sempre pra cima para tratar mais facilmente
  switch (appState->userAction){
    case ACTION_UP: break;
    case ACTION_DOWN: rotateGameBoard(appState, 2, LEFT);
      break;
    case ACTION_LEFT: rotateGameBoard(appState, 1, RIGHT);
      break;
    case ACTION_RIGTH: rotateGameBoard(appState, 1, LEFT);
      break;
    default: break;
  }

  //Une as peças pra cima


  //Retorna o tabuleiro ao estado inicial
  switch (appState->userAction){
    case ACTION_UP: break;
    case ACTION_DOWN: rotateGameBoard(appState, 2, RIGHT);
      break;
    case ACTION_LEFT: rotateGameBoard(appState, 1, LEFT);
      break;
    case ACTION_RIGTH: rotateGameBoard(appState, 1, RIGHT);
      break;
    default: break;
  }

  //Após a jogada adiciona uma nova carta ao tabuleiro, 10% chance de ser um 4
  addCardInBoard(&appState->gameState, 10);
}
