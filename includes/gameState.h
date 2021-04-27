/*------------------------------------------------------------------------------
 * 2048.c
 *
 * File: gameState.h
 * Author: Daniel Wojcickoski
 * Date: 2021/04/28
 * 
 * MIT License - Copyright (c) 2021 Daniel Wojcickoski
 *----------------------------------------------------------------------------*/
#ifndef  GAME_STATE_H
#define  GAME_STATE_H

//Includes
#include "../includes/main.h"

//Functions
type_gameState getDefaultGameState();
void newGame(type_appState * appState);
void handleGameAction(type_appState * appState);
void undoGameAction(type_appState * appState);

#endif  /*GAME_STATE_H*/