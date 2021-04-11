#include "../includes/controls.h"

/*------------------------------------------------------------------------------
 * Captura e retorna a ação realizada pelo usuario
 *----------------------------------------------------------------------------*/
enum_userAction captureUserAction(type_appState currentAppState){
  enum_userAction userAction = {0};
  int keyPressed = getch();

  //Captura a ação com base na tela atual
  switch (currentAppState.screen.currentScreen){
    case SCREEN_MENU:
      if(keyPressed == KEY_UP){
        userAction = ACTION_UP;
      }
      else if(keyPressed == KEY_DOWN){
        userAction = ACTION_DOWN;
      }
      else if(keyPressed == KEY_ENTER){
        userAction = ACTION_ENTER;
      }
      else if(keyPressed == KEY_ESCAPE){
        userAction = ACTION_ESCAPE;
      }
      break;
      
    case SCREEN_GAME:
      if(keyPressed == KEY_UP){
        userAction = ACTION_UP;
      }
      else if(keyPressed == KEY_LEFT){
        userAction = ACTION_LEFT;
      }
      else if(keyPressed == KEY_RIGHT){
        userAction = ACTION_RIGTH;
      }
      else if(keyPressed == KEY_DOWN){
        userAction = ACTION_DOWN;
      }
      else if(keyPressed == KEY_N){
        userAction = ACTION_GAME_NEW;
      }
      else if(keyPressed == KEY_S){
        userAction = ACTION_GAME_SAVE;
      }
      else if(keyPressed == KEY_U){
        userAction = ACTION_GAME_UNDO;
      }
      else if(keyPressed == KEY_ESCAPE){
        userAction = ACTION_ESCAPE;
      }
      break;

    case SCREEN_ENDGAME:
    
      break;

    case SCREEN_HELP:
      if(keyPressed == KEY_ENTER){
        userAction = ACTION_ESCAPE;
      }
      else if(keyPressed == KEY_ESCAPE){
        userAction = ACTION_ESCAPE;
      }
      break;
    
    default:
      userAction = ACTION_ESCAPE;
      break;
  }

  return userAction;
}