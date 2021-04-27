#include "../includes/save.h"
#include "../includes/gameState.h"

/*------------------------------------------------------------------------------
 * Transfere a estrutura type_gameSAve para dentro do appState
 *----------------------------------------------------------------------------*/
void saveToAppState(type_appState * appState, type_gameSave * gameSave){
  //Seta o estado default inicial do jogo
  appState->gameState = getDefaultGameState();

  //Salva as variaveis do save na estrutura gameState
  appState->gameState.gameStatus = gameSave->gameStatus;
  appState->gameState.lastScore = gameSave->lastScore;
  appState->gameState.score = gameSave->score;
  appState->gameState.lastMoves = gameSave->lastMoves;
  appState->gameState.moves = gameSave->moves;

  //Salva os tabuleiros na estrutura gameSave
  for(int line = 0; line < 4; line++){
    for(int collumn = 0; collumn < 4; collumn++){
      if(gameSave->lastGameBoard[line][collumn] == CARDNONE)
        appState->gameState.lastGameBoard[line][collumn] = NULL;
      else
        appState->gameState.lastGameBoard[line][collumn] = &appState->gameState.gameCards[gameSave->lastGameBoard[line][collumn] - 1];

      if(gameSave->gameBoard[line][collumn] == CARDNONE)
        appState->gameState.gameBoard[line][collumn] = NULL;
      else
        appState->gameState.gameBoard[line][collumn] = &appState->gameState.gameCards[gameSave->gameBoard[line][collumn] - 1];
    }
  }
}

/*------------------------------------------------------------------------------
 * Transfere a estrutura type_gameState para dentro do gameSave
 *----------------------------------------------------------------------------*/
void gameStateToSave(type_gameSave * gameSave, type_gameState * gameState){
  //Salva as variaveis de jogo na estrutura gameSave
  gameSave->gameStatus = gameState->gameStatus;
  gameSave->lastScore = gameState->lastScore;
  gameSave->score = gameState->score;
  gameSave->lastMoves = gameState->lastMoves;
  gameSave->moves = gameState->moves;

  //Salva os tabuleiros na estrutura gameSave
  for(int line = 0; line < 4; line++){
    for(int collumn = 0; collumn < 4; collumn++){
      if(gameState->lastGameBoard[line][collumn] != NULL)
        gameSave->lastGameBoard[line][collumn] = gameState->lastGameBoard[line][collumn]->exponent;
      else 
        gameSave->lastGameBoard[line][collumn] = CARDNONE;

      if(gameState->gameBoard[line][collumn] != NULL)
        gameSave->gameBoard[line][collumn] = gameState->gameBoard[line][collumn]->exponent;
      else
        gameSave->gameBoard[line][collumn] = CARDNONE;
    }
  }
}

/*------------------------------------------------------------------------------
 * Lê e retorna a estrutura salva no arquivo de save especificado em path
 *----------------------------------------------------------------------------*/
bool readSaveFile(type_appState * appState, const char * filename){
  type_gameSave save = {0};
  
  //Abre,le a estrutura save e fecha o arquivo binario
  FILE * saveFile = NULL;
  saveFile = fopen(filename, "rb");

  if(saveFile == NULL)
    return FALSE;

  fread(&save, sizeof(type_gameSave), 1, saveFile);
  
  fclose(saveFile);

  saveToAppState(appState, &save);
  
  return TRUE;
}

/*------------------------------------------------------------------------------
 * Escreve a estrutura type_gameState no arquivo especificado em path
 *----------------------------------------------------------------------------*/
void writeSaveFile(type_gameState * gameState, const char * filename){
  type_gameSave save = {0};

  gameStateToSave(&save, gameState);

  //Abre, escreve na estrutura save e fecha o arquivo binario
  FILE * saveFile = NULL;
  saveFile = fopen(filename, "w+b");

  fwrite(&save, sizeof(type_gameSave), 1, saveFile);

  fclose(saveFile);
}