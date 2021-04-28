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
bool readSaveFile(type_appState * appState, const char * filename);
void writeSaveFile(type_gameState * gameState, const char * filename);

#endif  /*SAVE_H*/