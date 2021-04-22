#include "../includes/main.h"
#include "../includes/appState.h"
#include "../includes/controls.h"
#include "../includes/leaderboard.h"
#include "../includes/screen.h"
//#include <windows.h>

/*------------------------------------------------------------------------------
 * Loop principal da aplicação
 *----------------------------------------------------------------------------*/
int main(){
/*

  //Seta o tamanho do terminal
  HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
  SMALL_RECT sr;
  COORD consoleSize;

  int terminalX = 73;
  int terminalY = 26;

  consoleSize.X = terminalX; 
  consoleSize.Y = terminalY;

  sr.Top = sr.Left = 0;
  sr.Right = terminalX - 1; 
  sr.Bottom = terminalY - 1;

  SetConsoleWindowInfo(console, TRUE, &sr);
  SetConsoleScreenBufferSize(console, consoleSize);


  //Seta o titulo do terminal
  SetConsoleTitleW(L"2048c");


  //Seta posição do terminal no monitor
  int screenX = GetSystemMetrics(SM_CXSCREEN);
  int screenY = GetSystemMetrics(SM_CYSCREEN);

  int newPosX = (screenX - GetSystemMetrics(SM_CXVSCROLL)) / 2;
  int newPosY = (screenY - GetSystemMetrics(SM_CYVSCROLL)) / 2;

  HWND hWnd = GetConsoleWindow();
  SetWindowPos( hWnd, 0, newPosX / 40, newPosY / 15, 0, 0, SWP_NOSIZE | SWP_NOZORDER );


  printf("X: %d, Y: %d", GetSystemMetrics(SM_CXVSCROLL), GetSystemMetrics(SM_CYVSCROLL));
  getch();

*/

  //Definição estrutura principal, gameState
  type_appState appState = getDefaultAppState();

  //Parse do arquivo de leaderboard
  appState.leaderboard = readLeaderboardFile();

  //Mantem rodando enquanto o appStatus for STATUS_RUNNING
  do{
    //Printa tela com base no appState
    printAppState(&appState);

    //Captura ação do usuario e salva em gameState.userAction
    appState.userAction = captureUserAction(appState);

    //Retorna um novo appState com base na ação do usuario
    handleUserAction(&appState);
  } while(appState.appStatus == STATUS_RUNNING);

  //Retorna appStatus
  return appState.appStatus;
}
