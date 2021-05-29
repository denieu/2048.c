/*------------------------------------------------------------------------------
 * 2048.c
 *
 * File: controls.c
 * Author: Daniel Wojcickoski
 * Date: 2021/04/28
 * 
 * MIT License - Copyright (c) 2021 Daniel Wojcickoski
 *----------------------------------------------------------------------------*/
#include "../includes/controls.h"

/*------------------------------------------------------------------------------
 * Macros
 *----------------------------------------------------------------------------*/
#define CASE_USER_ACTION(key, action) { \
  case key: \
    userAction = action; \
    break; \
}
#define CASE_USER_ACTION_DEFAULT(action) { \
  default: \
    userAction = action; \
    break; \
}
#define GETCH_UPPER() { \
  keyPressed = getch(); \
  if(isalpha(keyPressed)) \
    keyPressed = toupper(keyPressed); \
}

/*------------------------------------------------------------------------------
 * Capture and return the action taken by the user
 *----------------------------------------------------------------------------*/
void captureUserAction(appState_t * appState){
  userAction_e userAction = 0;
  int keyPressed = 0;
  char string[22] = {'\0'};

  if( (appState->screen.currentScreen == SCREEN_ENDGAME) ||
      (appState->screen.menuState == STATE_MENU_CONTINUE_SELECT) ||
      (appState->screen.gameState == STATE_GAME_SAVE) ){
    fgets(string, MAX_LEADERBOARD_LENGHT + 1, stdin);
    string[strlen(string) - 1] = '\0';
    strcpy(appState->userString, string);

    if(appState->screen.gameState == STATE_GAME_SAVE)
      userAction = ACTION_GAME_SAVE;
    else
      userAction = ACTION_ENTER;
  }
  else{
    GETCH_UPPER();

    switch (appState->screen.currentScreen){
      case SCREEN_MENU:
        switch (keyPressed){
          CASE_USER_ACTION(KEY_UP, ACTION_UP);
          CASE_USER_ACTION(KEY_DOWN, ACTION_DOWN);
          CASE_USER_ACTION(KEY_ENTER, ACTION_ENTER);
          CASE_USER_ACTION(KEY_ESCAPE, ACTION_ESCAPE);
          default: break;
        }
        break;
        
      case SCREEN_GAME:
        if(appState->screen.gameState == STATE_GAME_ESCAPE){
          switch (keyPressed){
            CASE_USER_ACTION(KEY_S, ACTION_ESCAPE);
            CASE_USER_ACTION_DEFAULT(ACTION_NO_ESCAPE);
          }
        }
        else if(appState->screen.gameState == STATE_GAME_NEW){
          switch (keyPressed){
            CASE_USER_ACTION(KEY_S, ACTION_GAME_NEW);
            CASE_USER_ACTION_DEFAULT(ACTION_NO_ESCAPE);
          }
        }
        else {
          switch (keyPressed){
            CASE_USER_ACTION(KEY_UP, ACTION_UP);
            CASE_USER_ACTION(KEY_LEFT, ACTION_LEFT);
            CASE_USER_ACTION(KEY_RIGHT, ACTION_RIGTH);
            CASE_USER_ACTION(KEY_DOWN, ACTION_DOWN);
            CASE_USER_ACTION(KEY_N, ACTION_GAME_PRE_NEW);
            CASE_USER_ACTION(KEY_S, ACTION_GAME_PRE_SAVE);
            CASE_USER_ACTION(KEY_U, ACTION_GAME_UNDO);
            CASE_USER_ACTION(KEY_ESCAPE, ACTION_PRE_ESCAPE);
            default: break;
          }
        }
        break;
        
      case SCREEN_RANKING:
        userAction = ACTION_ENTER;
        break;
      
      CASE_USER_ACTION_DEFAULT(ACTION_ESCAPE);
    }
  }

  appState->userAction = userAction;
  return;
}