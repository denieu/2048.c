#ifndef  GAME_STATE_H
#define  GAME_STATE_H

//Includes
#include "../includes/main.h"

//Functions
type_gameState getDefaultGameState();
bool addCardInBoard(type_gameState * gameState, int chanceToDouble);

#endif  /*GAME_STATE_H*/