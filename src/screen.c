#include "../includes/screen.h"
#include "windows.h" //SetConsoleCursorInfo
#include "../includes/conio2.h" //gotoxy, textcolor, textbackground

/*------------------------------------------------------------------------------
 * Altera o estado do cursor entre visivel e invisivel
 *----------------------------------------------------------------------------*/
void setCursor(enum_cursorState cursorState){
  CONSOLE_CURSOR_INFO info;
  info.dwSize = 100;
  info.bVisible = cursorState;
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

/*------------------------------------------------------------------------------
 * Printa a tela dentro de jogo
 *----------------------------------------------------------------------------*/
void screen_inGame(type_appState currentAppState){
    
}

/*------------------------------------------------------------------------------
 * Printa a tela atual com base no "currentAppState"
 *----------------------------------------------------------------------------*/
void printAppState(type_appState currentAppState){
  //Esconde o cursos da tela
  setCursor(CURSOR_HIDDEN);
  
  //Printa tela menu - Raissa

  //Printa tela jogo - Daniel
  //screen_inGame(currentAppState);

  //Printa tela de pausa

  //Printa tela instruções

  //Printa tela fim de partida

}
