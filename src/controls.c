#include "../includes/controls.h"

//Macros
#define CASE_SELECT(key, action) { \
  case key: \
    userAction = action; \
    break; \
}

/*------------------------------------------------------------------------------
 * Captura e retorna a ação realizada pelo usuario
 *----------------------------------------------------------------------------*/
void captureUserAction(type_appState * appState){
  enum_userAction userAction = 0;
  int keyPressed = 0;
  char string[21] = {'\0'};

  //Se for a tela de fim de jogo deve capturar o nome do usuario
  if(appState->screen.currentScreen == SCREEN_ENDGAME){
    fgets(string, 10, stdin);
    string[strlen(string) - 1] = '\0';
    strcpy(appState->userString, string);

    keyPressed = KEY_ENTER;
  }

  //Busca a string para salvar o arquivo
  else if(appState->screen.currentScreen == SCREEN_GAME && 
          appState->screen.gameState == STATE_GAME_SAVE){
    fgets(string, 10, stdin);
    string[strlen(string) - 1] = '\0';
    strcpy(appState->userString, string);

    userAction = ACTION_GAME_SAVE;
    keyPressed = 0;
  }

  //Busca a string para salvar o arquivo
  else if(appState->screen.currentScreen == SCREEN_MENU && 
          appState->screen.menuState == STATE_MENU_CONTINUE_SELECT){
    fgets(string, 10, stdin);
    string[strlen(string) - 1] = '\0';
    strcpy(appState->userString, string);

    userAction = ACTION_ENTER;
    keyPressed = 0;
  }

  //Confirma o escape
  else if(appState->screen.currentScreen == SCREEN_GAME && 
          appState->screen.gameState == STATE_GAME_ESCAPE){
    keyPressed = getch();

    if(isalpha(keyPressed))
      keyPressed = toupper(keyPressed);

    switch (keyPressed){
      case KEY_S:
        userAction = ACTION_ESCAPE;
        break;
      
      default:
        userAction = ACTION_NO_ESCAPE;
        break;
    }
    
    keyPressed = 0;
  }

  //No caso default somente captura a tecla digitada pelo jogador
  else {
    keyPressed = getch();

    //Deixa o caracter digitado maiusculo
    if(isalpha(keyPressed))
      keyPressed = toupper(keyPressed);
  }

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
      break;

    case SCREEN_ENDGAME:
      switch (keyPressed){
        CASE_SELECT(KEY_ENTER, ACTION_ENTER);
        CASE_SELECT(KEY_ESCAPE, ACTION_ESCAPE);
        default: break;
      }
      break;
    
    default:
      userAction = ACTION_ESCAPE;
      break;
  }

  appState->userAction = userAction;
  return;
}