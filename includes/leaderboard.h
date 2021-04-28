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
type_leaderboard readLeaderboardFile();
void writeLeaderboardFile(type_leaderboard * newSave);
void bubbleSortLeaderboard(type_leaderboard * leaderboard);

#endif  /*LEADERBOARD_H*/