/*------------------------------------------------------------------------------
 * 2048.c
 *
 * File: screen.h
 * Author: Daniel Wojcickoski
 * Date: 2021/04/28
 * 
 * MIT License - Copyright (c) 2021 Daniel Wojcickoski
 *----------------------------------------------------------------------------*/
#ifndef  SCREEN_H
#define  SCREEN_H

//Includes
#include "../includes/main.h"

//Functions
void updateScreenState(appState_t * newScreenState);
void *screenThread();

#endif  /*SCREEN_H*/