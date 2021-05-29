/*------------------------------------------------------------------------------
 * 2048.c
 *
 * File: leaderboard.h
 * Author: Daniel Wojcickoski
 * Date: 2021/04/28
 * 
 * MIT License - Copyright (c) 2021 Daniel Wojcickoski
 *----------------------------------------------------------------------------*/
#ifndef  LEADERBOARD_H
#define  LEADERBOARD_H

//Includes
#include "../includes/main.h"

//Constants
#define PATH_LEADERBOARD "leaderboard.txt"

//Functions
leaderboard_t readLeaderboardFile();
void writeLeaderboardFile(leaderboard_t * newSave);
void bubbleSortLeaderboard(leaderboard_t * leaderboard);

#endif  /*LEADERBOARD_H*/