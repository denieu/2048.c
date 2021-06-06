//Includes
#include "../includes/creact.h"

//Variables
#ifdef __MINGW32__
unsigned char _fixed = 0;
#else
unsigned char _fixed = 1;
#endif
unsigned char _textColor = 30;
unsigned char _bgColor = 37;

//Functions
void cr_fixCommands(){
  if(_fixed == 0){
    #ifdef __MINGW32__
      #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
      HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
      if (handle != INVALID_HANDLE_VALUE) {
        DWORD mode = 0;
        if (GetConsoleMode(handle, &mode)) {
          mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
          SetConsoleMode(handle, mode);
        }
      }
      _fixed = 1;
    #endif
  }
}

void _cr_updateColor(){
  cr_fixCommands();
  printf("\e[0;%d;%dm", _bgColor, _textColor);
}

void cr_resetColors(){
  cr_fixCommands();
  printf("\e[0m");
}

void cr_bgColor(COLORS color){
  _bgColor = (color <= 7) ? color + 40 : color - 8 + 100;
  _cr_updateColor();
}

void cr_textColor(COLORS color){
  _textColor = (color <= 7) ? color + 30 : color - 8 + 90;
  _cr_updateColor();
}

void cr_setColors(COLORS bgColor, COLORS textColor){
  _bgColor = (bgColor <= 7) ? bgColor + 40 : bgColor - 8 + 100;
  _textColor = (textColor <= 7) ? textColor + 30 : textColor - 8 + 90;
  _cr_updateColor();
}

void cr_moveCursorXY(int x, int y){
  cr_fixCommands();
  printf("\e[%d;%dH", y, x);
}

void cr_clearScreen(){
  system("cls");
  system("clear");
}