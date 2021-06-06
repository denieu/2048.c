/*------------------------------------------------------------------------------
 * 2048.c
 *
 * File: main.c
 * Author: Daniel Wojcickoski
 * Date: 2021/04/28
 * 
 * MIT License - Copyright (c) 2021 Daniel Wojcickoski
 *----------------------------------------------------------------------------*/
#include "../includes/main.h"
#include "../includes/appState.h"
#include "../includes/controls.h"
#include "../includes/leaderboard.h"
#include "../includes/screen.h"

/*------------------------------------------------------------------------------
 * Main app loop
 *----------------------------------------------------------------------------*/
int main(){
  pthread_t tId;
  appState_t appState = getDefaultAppState();

  pthread_create(&tId, NULL, screenThread, (void *)&tId);
  appState.leaderboard = readLeaderboardFile();

  do{
    updateScreenState(&appState);
    appState.screen.lastScreen = appState.screen.currentScreen;
    appState.screen.forceClear = FALSE;

    captureUserAction(&appState);

    handleUserAction(&appState);
  } while(appState.appStatus == STATUS_RUNNING);

  return appState.appStatus;
}
