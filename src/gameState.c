/*------------------------------------------------------------------------------
 * 2048.c
 *
 * File: gameState.c
 * Author: Daniel Wojcickoski
 * Date: 2021/04/28
 * 
 * MIT License - Copyright (c) 2021 Daniel Wojcickoski
 *----------------------------------------------------------------------------*/
#include "../includes/gameState.h"

/*------------------------------------------------------------------------------
 * Returns the default gameState
 *----------------------------------------------------------------------------*/
gameState_t getDefaultGameState(){
  gameState_t defaultGameState = {0};

  COLORS gameCardColors[12] = {
    BLUE, GREEN, CYAN, RED, MAGENTA, BROWN,
    DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED
  };

  defaultGameState.gameStatus = GAME_RUNNING;
  defaultGameState.score = 0;
  defaultGameState.moves = 0;

  for(int card = 0; card < 11; card++){
    defaultGameState.gameCards[card].value = pow(2, card + 1);
    defaultGameState.gameCards[card].exponent = card + 1;
    defaultGameState.gameCards[card].color = gameCardColors[card];
  }

  for(int line = 0; line < 4; line++){
     for(int collumn = 0; collumn < 4; collumn++){
      defaultGameState.auxGameBoard[line][collumn] = NULL;
      defaultGameState.lastGameBoard[line][collumn] = NULL;
      defaultGameState.gameBoard[line][collumn] = NULL;
    }
  }

  return defaultGameState;
}

/*------------------------------------------------------------------------------
 * Checks if the current game board has any free spaces
 *
 * Returns TRUE if you have at least one free space
 * Returns FALSE if you don't have any free houses
 *----------------------------------------------------------------------------*/
bool verifyFreeHouse(gameState_t * gameState){
  for(int line = 0; line < 4; line++){
    for(int collumn = 0; collumn < 4; collumn++){
      if(gameState->gameBoard[line][collumn] == NULL){
        return TRUE;
      }
    }
  }
  return FALSE;
}

/*------------------------------------------------------------------------------
 * Adds a piece to the gameBoard game board
 *
 * chanceToDouble:
 * defines the chance (0 - 100%) of doubling the value of the starting piece (from 2 to 4)
 *
 * Returns TRUE if you manage to add the piece to the board
 * Returns FALSE if it fails
 *----------------------------------------------------------------------------*/
bool addCardInBoard(gameState_t * gameState, int chanceToDouble){
  gameCards_e newCardIndex = CARD2 - 1;

  srand(time(NULL));
  if((rand() % 100) <= chanceToDouble && chanceToDouble != 0){
    newCardIndex = CARD4 - 1;
  }

  while(TRUE){
    int house = (rand() % 16);
    int line = house / 4;
    int collumn = house % 4;

    if(gameState->gameBoard[line][collumn] == NULL){
      gameState->gameBoard[line][collumn] = &gameState->gameCards[newCardIndex];
      return TRUE;
    }

    if(verifyFreeHouse(gameState) == FALSE){
      return FALSE;
    }
  }

  return FALSE;
}

/*------------------------------------------------------------------------------
 * Starts a new game, resetting all variables to their initial state
 *----------------------------------------------------------------------------*/
void newGame(appState_t * appState){
  appState->gameState = getDefaultGameState();

  addCardInBoard(&appState->gameState, 0);
  addCardInBoard(&appState->gameState, 0);

  appState->screen.currentScreen = SCREEN_GAME;
}

/*------------------------------------------------------------------------------
 * Checks whether the player won, made 2048
 *
 * Returns TRUE if player has won
 * Returns FALSE if player has not yet won
 *----------------------------------------------------------------------------*/
bool verifyPlayerWin(appState_t * appState){
  for(int line = 0; line < 4; line++){
    for(int collumn = 0; collumn < 4; collumn++){
      if(appState->gameState.gameBoard[line][collumn] != NULL){
        if(appState->gameState.gameBoard[line][collumn]->value == appState->gameState.gameCards[10].value){
          return TRUE;
        }
      }
    }
  }

  return FALSE;
}

/*------------------------------------------------------------------------------
 * Rotates the game board to the "direction" side
 *
 * direction: LEFT = Board will be rotated to the right
 *            RIGHT = Tray will be rotated to the left
 *----------------------------------------------------------------------------*/
void rotateGameBoard(appState_t * appState, direction_e direction){
  gameState_t oldGameState = appState->gameState;
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
 * Rotates the board upwards, depending on the user's action
 *----------------------------------------------------------------------------*/
void boardRotateUp(appState_t * appState){
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
 * Rotates the board to its original position, depending on the user's action
 *----------------------------------------------------------------------------*/
void boardRotateOg(appState_t * appState){
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
 * Move the pieces up, joining the necessary ones
 *
 * Returns TRUE if any part moves
 * Returns FALSE if no part moves
 *----------------------------------------------------------------------------*/
bool boardSlideUp(appState_t * appState){
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
            if(appState->gameState.gameBoard[line][collumn] == appState->gameState.gameBoard[line + count][collumn]){
              //Se sim incrementa o valor da linha atual,
              //tranforma a proxima linha em nula
              //e continua para verificar a proxima linha
              appState->gameState.gameBoard[line][collumn]++;
              appState->gameState.gameBoard[line + count][collumn] = NULL;

              //Incrementa o score do jogador com o valor da nova peça
              appState->gameState.score += appState->gameState.gameBoard[line][collumn]->value;
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
 * Checks if in any of the positions there is a movement available
 *
 * Returns TRUE if there are movements available
 * Returns FALSE if there are no movements available
 *----------------------------------------------------------------------------*/
bool verifyPossibleMoves(appState_t * appState){
  appState_t newAppState = *appState;

  for(int count = 0; count < 4; count++){
    if(boardSlideUp(&newAppState) == TRUE){
      return TRUE;
    }

    rotateGameBoard(&newAppState, LEFT);
  }
  return FALSE;
}

/*------------------------------------------------------------------------------
 * Change the appState based on the action performed within the game
 *----------------------------------------------------------------------------*/
void handleGameAction(appState_t * appState){
  //Auxiliar para verificar se ocorreu alguma ação/movimento no tabuleiro
  bool isMoved = FALSE;

  //Salva os dados atuais nas auxiliares antes do movimento
  appState->gameState.auxScore = appState->gameState.score;
  appState->gameState.auxMoves = appState->gameState.moves;
  for(int line = 0; line < 4; line++){
    for(int collumn = 0; collumn < 4; collumn++){
      appState->gameState.auxGameBoard[line][collumn] = appState->gameState.gameBoard[line][collumn];
    }
  }

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

    //Salva os dados auxiares nas variaveis que salvam o ultimo movimento
    appState->gameState.lastScore = appState->gameState.auxScore;
    appState->gameState.lastMoves = appState->gameState.auxMoves;
    for(int line = 0; line < 4; line++){
      for(int collumn = 0; collumn < 4; collumn++){
        appState->gameState.lastGameBoard[line][collumn] = appState->gameState.auxGameBoard[line][collumn];
      }
    }

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

/*------------------------------------------------------------------------------
 * Undo the last action taken by the user in the game
 *----------------------------------------------------------------------------*/
void undoGameAction(appState_t * appState){
  for(int line = 0; line < 4; line++){
    for(int collumn = 0; collumn < 4; collumn++){
      appState->gameState.gameBoard[line][collumn] = appState->gameState.lastGameBoard[line][collumn];
    }
  }

  appState->gameState.score = appState->gameState.lastScore;
  appState->gameState.moves = appState->gameState.lastMoves;
}