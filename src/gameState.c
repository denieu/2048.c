#include "../includes/gameState.h"

/*------------------------------------------------------------------------------
 * Retorna o gameState default
 *----------------------------------------------------------------------------*/
type_gameState getDefaultGameState(){
  type_gameState defaultGameState = {0};

  defaultGameState.gameStatus = GAME_RUNNING;
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
bool verifyFreeHouse(type_gameState * gameState){
  for(int line = 0; line < 4; line++){
    for(int collumn = 0; collumn < 4; collumn++){
      if(gameState->gameBoard[line][collumn] == NULL){
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
    if(verifyFreeHouse(gameState) == FALSE){
      return FALSE;
    }
  }

  //Não havia nenhuma casa livre no tabuleiro
  return FALSE;
}

/*------------------------------------------------------------------------------
 * Verifica se o jogador ganhou, fez 2048
 *
 * Retorna TRUE caso o jogador tenha ganhado
 * Retorna FALSE caso o jogador ainda não tenha ganhado
 *----------------------------------------------------------------------------*/
bool verifyPlayerWin(type_appState * appState){
  for(int line = 0; line < 4; line++){
    for(int collumn = 0; collumn < 4; collumn++){
      if(appState->gameState.gameBoard[line][collumn] != NULL){
        if(*appState->gameState.gameBoard[line][collumn] == appState->gameState.gameCards[10]){
          return TRUE;
        }
      }
    }
  }

  return FALSE;
}

/*------------------------------------------------------------------------------
 * Rotaciona o tabuleiro de jogo para o lado "direction"
 *
 * direction: 0 = Tabuleiro será rotacionado para a direita
 *            1 = Tabuleiro será rotacionado para a esquerda
 *----------------------------------------------------------------------------*/
void rotateGameBoard(type_appState * appState, enum_direction direction){
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
}

/*------------------------------------------------------------------------------
 * Rotaciona o tabuleiro pra cima, dependendo da ação do usuario
 *----------------------------------------------------------------------------*/
void boardRotateUp(type_appState * appState){
  switch (appState->userAction){
    case ACTION_UP: break;
    case ACTION_DOWN:
      rotateGameBoard(appState, LEFT);
      rotateGameBoard(appState, LEFT);
      break;
    case ACTION_LEFT:
      rotateGameBoard(appState, RIGHT);
      break;
    case ACTION_RIGTH:
      rotateGameBoard(appState, LEFT);
      break;
    default: return; break;
  }
}

/*------------------------------------------------------------------------------
 * Rotaciona o tabuleiro pra posição original, dependendo da ação do usuario
 *----------------------------------------------------------------------------*/
void boardRotateOg(type_appState * appState){
  switch (appState->userAction){
    case ACTION_UP: break;
    case ACTION_DOWN:
      rotateGameBoard(appState, LEFT);
      rotateGameBoard(appState, LEFT);
      break;
    case ACTION_LEFT:
      rotateGameBoard(appState, LEFT);
      break;
    case ACTION_RIGTH:
      rotateGameBoard(appState, RIGHT);
      break;
    default: return; break;
  }
}

/*------------------------------------------------------------------------------
 * Faz o movimento pra cima das peças, unindo as necessarias
 *
 * Retorna TRUE caso alguma peça se movimente
 * Retorna FALSE caso nenhuma peça se movimente
 *----------------------------------------------------------------------------*/
bool boardSlideUp(type_appState * appState){
  bool ret = FALSE;
  int flag = 0;

  //Percorre coluna por coluna
  for(int collumn = 0; collumn < 4; collumn++){
    //Percorre da primeira até a penultima linha
    for(int line = 0; line < 3; line++){
      //Verifica se a linha atual é nula
      if(appState->gameState.gameBoard[line][collumn] != NULL){
        //Verifica as proximas linhas se pode unir com a atual
        for(int count = 1; count <=3 ; count++){
          //Se a proxima linha estiver no range valido(<4) e a proxima linha não for nula
          if(line + count < 4 && appState->gameState.gameBoard[line + count][collumn] != NULL){
            //Verifica se a proxima linha é igual a linha atual
            if(*appState->gameState.gameBoard[line][collumn] == *appState->gameState.gameBoard[line + count][collumn]){
              //Se sim incrementa o valor da linha atual,
              //tranforma a proxima linha em nula
              //e continua para verificar a proxima linha
              appState->gameState.gameBoard[line][collumn]++;
              appState->gameState.gameBoard[line + count][collumn] = NULL;

              //Incrementa o score do jogador com o valor da nova peça
              appState->gameState.score += pow(2, *appState->gameState.gameBoard[line][collumn]);

              ret = TRUE;
            }
            break;
          }
        }
      }
    }
  }

  //Joga as peças para cima, deixando os espaçoes nulos em baixo
  for(int collumn = 0; collumn < 4; collumn++){
    do{
      flag = 0;
      for(int line = 3; line > 0 ; line--){
        if(appState->gameState.gameBoard[line][collumn] != NULL){
          for(int count = 1; count <=3 ; count++){
            if(line - count >= 0 && appState->gameState.gameBoard[line - count][collumn] == NULL){
              appState->gameState.gameBoard[line - count][collumn] = appState->gameState.gameBoard[line][collumn];
              appState->gameState.gameBoard[line][collumn] = NULL;
              flag = 1;
              ret = TRUE;
            }
            else {
              break;
            }
          }
        }
      }
    } while(flag == 1);
  }

  return ret;
}

/*------------------------------------------------------------------------------
 * Verifica se em alguma das posições existe um movimento disponivel
 *
 * Retorna TRUE caso exista movimentos disponiveis
 * Retorna FALSE caso não exista movimentos disponiveis
 *----------------------------------------------------------------------------*/
bool verifyPossibleMoves(type_appState * appState){
  type_appState newAppState = *appState;

  for(int count = 0; count < 4; count++){
    //Verifica se fez algum movimento
    if(boardSlideUp(&newAppState) == TRUE){
      //Algum movimento ocorreu
      return TRUE;
    }

    rotateGameBoard(&newAppState, LEFT);
  }

  //Nenhum movimento ocorreu em nenhum posição
  return FALSE;
}

/*------------------------------------------------------------------------------
 * Altera o appState com base na ação realizada dentro do jogo
 *----------------------------------------------------------------------------*/
void handleGameAction(type_appState * appState){
  bool isMoved = FALSE;

  //Rotaciona tabuleiro sempre pra cima para tratar mais facilmente
  boardRotateUp(appState);

  //Une as peças pra cima
  isMoved = boardSlideUp(appState);

  //Retorna o tabuleiro ao estado inicial
  boardRotateOg(appState);

  //Se algum movimento foi feito no tabuleiro
  if(isMoved == TRUE) {
    //Incrementa o numero de movimentos
    appState->gameState.moves++;

    //Verifica se o jogador ganhou
    if(verifyPlayerWin(appState) == TRUE){
      appState->gameState.gameStatus = GAME_WIN;
      appState->screen.currentScreen = SCREEN_ENDGAME;
      return;
    }

    //Adiciona uma nova carta ao tabuleiro para a proxima rodada
    addCardInBoard(&appState->gameState, 10);
  }

  //Não conseguiu jogar verifica se existem casas livres
  if(verifyFreeHouse(&appState->gameState) == FALSE){
    //Verifica se tem alguma jogada possivel
    if(verifyPossibleMoves(appState) == FALSE){
      //Não existem casas livres e não existe nenhuma jogada possivel,
      //encerra o jogo com derrota
      appState->gameState.gameStatus = GAME_LOSE;
      appState->screen.currentScreen = SCREEN_ENDGAME;
      return;
    }
  }
}
