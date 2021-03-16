#ifndef  SCREEN_COMPONENTS_H
#define  SCREEN_COMPONENTS_H

//Includes
#include "../includes/main.h"

//Functions
void print_menuButton(char * placeholder, int posX, int posY, bool selected);
void print_inGameMenu(int posX, int posY);
void print_gameStatus(type_gameState gameState, int posX, int posY);
void print_inGameRanking(type_leaderboard * leaderboard, int posX, int posY);
void print_gameBoardEdges(int posX, int posY);
void print_gameBoard(type_gameState * gameState, int posX, int posY);
void print_endGameStatus(enum_gameStatus status, int posX, int posY);
void print_querryUserString(const char * placeholder, int posX, int posY);

#endif  /*SCREEN_COMPONENTS_H*/