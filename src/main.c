#include "../includes/main.h"
#include "../includes/appState.h"
#include "../includes/controls.h"
#include "../includes/leaderboard.h"
#include "../includes/screen.h"

/*------------------------------------------------------------------------------
 * Loop principal da aplicação
 *----------------------------------------------------------------------------*/
int main(){
  //Definição estrutura principal, gameState
  type_appState appState = getDefaultAppState();

  //Parse do arquivo de leaderboard
  appState.leaderboard = readLeaderboardFile();

  //Mantem rodando enquanto o appStatus for STATUS_RUNNING
  do{
    //Printa tela com base no appState
    printAppState(appState);

    //Captura ação do usuario e salva em gameState.userAction
    appState.userAction = captureUserAction(appState);

    //Retorna um novo appState com base na ação do usuario
    handleUserAction(&appState);
  } while(appState.appStatus == STATUS_RUNNING);

  //Retorna appStatus
  return appState.appStatus;
}
