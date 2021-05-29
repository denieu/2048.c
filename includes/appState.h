/*------------------------------------------------------------------------------
 * 2048.c
 *
 * File: appState.h
 * Author: Daniel Wojcickoski
 * Date: 2021/04/28
 * 
 * MIT License - Copyright (c) 2021 Daniel Wojcickoski
 *----------------------------------------------------------------------------*/
#ifndef  APP_STATE_H
#define  APP_STATE_H

//Includes
#include "../includes/main.h"

//Functions
appState_t getDefaultAppState();
void handleUserAction(appState_t * appState);

#endif  /*APP_STATE_H*/