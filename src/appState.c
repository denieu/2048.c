#include "../includes/appState.h"

/*------------------------------------------------------------------------------
 * Retorna o appState default
 *----------------------------------------------------------------------------*/
typeAppState getDefaultAppState(){
  typeAppState defaultAppState = {0};

  defaultAppState.appStatus = STATUS_RUNNING;

  return defaultAppState;
}

/*------------------------------------------------------------------------------
 * Retorna um novo appState com base na ação realizada no appState atual
 *----------------------------------------------------------------------------*/
typeAppState handleUserAction(typeAppState currentAppState){
  return currentAppState;
}