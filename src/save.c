#include "../includes/save.h"
#include "../includes/gameState.h"

/*------------------------------------------------------------------------------
 * Lê e retorna a estrutura salva no arquivo de save especificado em path
 *----------------------------------------------------------------------------*/
void readSaveFile(type_appState * appState, const char * filename){
  type_gameSave save = {0};
  
  //Abre,le a estrutura save e fecha o arquivo binario
  FILE * saveFile = NULL;
  saveFile = fopen(filename, "rb");

  fread(&save, sizeof(type_gameSave), 1, saveFile);
  
  fclose(saveFile);

  //Seta o estado default inicial do jogo
  appState->gameState = getDefaultGameState();

  //Salva as variaveis do save na estrutura gameState
  appState->gameState.gameStatus = save.gameStatus;
  appState->gameState.lastScore = save.lastScore;
  appState->gameState.score = save.score;
  appState->gameState.lastMoves = save.lastMoves;
  appState->gameState.moves = save.moves;

  //Salva os tabuleiros na estrutura gameSave
  for(int line = 0; line < 4; line++){
    for(int collumn = 0; collumn < 4; collumn++){
      if(save.lastGameBoard[line][collumn] == CARDNONE)
        appState->gameState.lastGameBoard[line][collumn] = NULL;
      else
        appState->gameState.lastGameBoard[line][collumn] = &appState->gameState.gameCards[save.lastGameBoard[line][collumn] - 1];

      if(save.gameBoard[line][collumn] == CARDNONE)
        appState->gameState.gameBoard[line][collumn] = NULL;
      else
        appState->gameState.gameBoard[line][collumn] = &appState->gameState.gameCards[save.gameBoard[line][collumn] - 1];
    }
  }
}

/*------------------------------------------------------------------------------
 * Escreve a estrutura type_gameState no arquivo especificado em path
 *----------------------------------------------------------------------------*/
void writeSaveFile(type_gameState * gameState, const char * filename){
  type_gameSave save = {0};

  //Salva as variaveis de jogo na estrutura gameSave
  save.gameStatus = gameState->gameStatus;
  save.lastScore = gameState->lastScore;
  save.score = gameState->score;
  save.lastMoves = gameState->lastMoves;
  save.moves = gameState->moves;

  //Salva os tabuleiros na estrutura gameSave
  for(int line = 0; line < 4; line++){
    for(int collumn = 0; collumn < 4; collumn++){
      if(gameState->lastGameBoard[line][collumn] != NULL)
        save.lastGameBoard[line][collumn] = gameState->lastGameBoard[line][collumn]->exponent;
      else 
        save.lastGameBoard[line][collumn] = CARDNONE;

      if(gameState->gameBoard[line][collumn] != NULL)
            save.gameBoard[line][collumn] = gameState->gameBoard[line][collumn]->exponent;
      else
        save.gameBoard[line][collumn] = CARDNONE;
    }
  }

  //Abre, escreve na estrutura save e fecha o arquivo binario
  FILE * saveFile = NULL;
  saveFile = fopen(filename, "w+b");

  fwrite(&save, sizeof(type_gameSave), 1, saveFile);

  fclose(saveFile);
}