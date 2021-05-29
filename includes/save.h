/*------------------------------------------------------------------------------
 * 2048.c
 *
 * File: save.h
 * Author: Daniel Wojcickoski
 * Date: 2021/04/28
 * 
 * MIT License - Copyright (c) 2021 Daniel Wojcickoski
 *----------------------------------------------------------------------------*/
#ifndef  SAVE_H
#define  SAVE_H

//Includes
#include "../includes/main.h"

//Functions
bool readSaveFile(appState_t * appState, const char * filename);
void writeSaveFile(gameState_t * gameState, const char * filename);

#endif  /*SAVE_H*/