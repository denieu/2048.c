/*------------------------------------------------------------------------------
 * 2048.c
 *
 * File: screen_components.h
 * Author: Daniel Wojcickoski
 * Date: 2021/04/28
 * 
 * MIT License - Copyright (c) 2021 Daniel Wojcickoski
 *----------------------------------------------------------------------------*/
#ifndef  SCREEN_COMPONENTS_H
#define  SCREEN_COMPONENTS_H

//Includes
#include "../includes/main.h"

//Functions
void print_menuButton(char * placeholder, int posX, int posY, bool selected);
void print_inGameMenu(int posX, int posY);
void print_gameStatus(gameState_t gameState, int posX, int posY);
void print_inGameRanking(leaderboard_t * leaderboard, int posX, int posY);
void print_gameBoardEdges(int posX, int posY);
void print_gameBoard(gameState_t * gameState, int posX, int posY);
void print_endGameStatus(gameStatus_e status, int posX, int posY);
void print_querryUserString(const char * placeholder, int posX, int posY, COLORS color1, COLORS color2);

#endif  /*SCREEN_COMPONENTS_H*/