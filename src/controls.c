#include "../includes/controls.h"

//Macros
#define CASE_SELECT(key, action) { \
  case key: \
    userAction = action; \
    break; \
}
#define CASE_DEFAULT(action) { \
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
 * Captura e retorna a ação realizada pelo usuario
 *----------------------------------------------------------------------------*/
void captureUserAction(type_appState * appState){
  enum_userAction userAction = 0;
  int keyPressed = 0;
  char string[21] = {'\0'};

  //Momentos onde é necessario capturar uma string ao inves de uma tecla
  if( (appState->screen.currentScreen == SCREEN_ENDGAME) ||
      (appState->screen.menuState == STATE_MENU_CONTINUE_SELECT) ||
      (appState->screen.gameState == STATE_GAME_SAVE) ){
    fgets(string, 10, stdin);
    string[strlen(string) - 1] = '\0';
    strcpy(appState->userString, string);

    if(appState->screen.gameState == STATE_GAME_SAVE)
      userAction = ACTION_GAME_SAVE;
    else
      userAction = ACTION_ENTER;
  }
  else{
    GETCH_UPPER();

    //Captura a ação com base na tela atual
    switch (appState->screen.currentScreen){
      case SCREEN_MENU:
        switch (keyPressed){
          CASE_SELECT(KEY_UP, ACTION_UP);
          CASE_SELECT(KEY_DOWN, ACTION_DOWN);
          CASE_SELECT(KEY_ENTER, ACTION_ENTER);
          CASE_SELECT(KEY_ESCAPE, ACTION_ESCAPE);
          default: break;
        }
        break;
        
      case SCREEN_GAME:
        if(appState->screen.gameState == STATE_GAME_ESCAPE){
          switch (keyPressed){
            CASE_SELECT(KEY_S, ACTION_ESCAPE);
            CASE_DEFAULT(ACTION_NO_ESCAPE);
          }
        }
        else {
          switch (keyPressed){
            CASE_SELECT(KEY_UP, ACTION_UP);
            CASE_SELECT(KEY_LEFT, ACTION_LEFT);
            CASE_SELECT(KEY_RIGHT, ACTION_RIGTH);
            CASE_SELECT(KEY_DOWN, ACTION_DOWN);
            CASE_SELECT(KEY_N, ACTION_GAME_NEW);
            CASE_SELECT(KEY_S, ACTION_GAME_PRE_SAVE);
            CASE_SELECT(KEY_U, ACTION_GAME_UNDO);
            CASE_SELECT(KEY_ESCAPE, ACTION_PRE_ESCAPE);
            default: break;
          }
        }
        break;
      
      CASE_DEFAULT(ACTION_ESCAPE);
    }
  }

  appState->userAction = userAction;
  return;
}