/*------------------------------------------------------------------------------
 * 2048.c
 *
 * File: save.c
 * Author: Daniel Wojcickoski
 * Date: 2021/04/28
 * 
 * MIT License - Copyright (c) 2021 Daniel Wojcickoski
 *----------------------------------------------------------------------------*/
#include "../includes/save.h"
#include "../includes/gameState.h"

/*------------------------------------------------------------------------------
 * Transfer the gameSave_t structure into the appState
 *----------------------------------------------------------------------------*/
void saveToAppState(appState_t * appState, gameSave_t * gameSave){
  appState->gameState = getDefaultGameState();

  appState->gameState.gameStatus = gameSave->gameStatus;
  appState->gameState.lastScore = gameSave->lastScore;
  appState->gameState.score = gameSave->score;
  appState->gameState.lastMoves = gameSave->lastMoves;
  appState->gameState.moves = gameSave->moves;

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
 * Transfer the gameState_t structure into the gameSave
 *----------------------------------------------------------------------------*/
void gameStateToSave(gameSave_t * gameSave, gameState_t * gameState){
  gameSave->gameStatus = gameState->gameStatus;
  gameSave->lastScore = gameState->lastScore;
  gameSave->score = gameState->score;
  gameSave->lastMoves = gameState->lastMoves;
  gameSave->moves = gameState->moves;

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
 * Reads and returns the structure saved in the save file specified in path
 *----------------------------------------------------------------------------*/
bool readSaveFile(appState_t * appState, const char * filename){
  gameSave_t save = {0};
  
  FILE * saveFile = NULL;
  saveFile = fopen(filename, "rb");

  if(saveFile == NULL)
    return FALSE;

  fread(&save, sizeof(gameSave_t), 1, saveFile);
  
  fclose(saveFile);

  saveToAppState(appState, &save);
  
  return TRUE;
}

/*------------------------------------------------------------------------------
 * Writes the gameState_t structure to the file specified in path
 *----------------------------------------------------------------------------*/
void writeSaveFile(gameState_t * gameState, const char * filename){
  gameSave_t save = {0};

  gameStateToSave(&save, gameState);

  FILE * saveFile = NULL;
  saveFile = fopen(filename, "w+b");

  fwrite(&save, sizeof(gameSave_t), 1, saveFile);

  fclose(saveFile);
}