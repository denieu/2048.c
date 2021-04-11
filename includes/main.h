#ifndef  MAIN_H
#define  MAIN_H

//Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../includes/conio2.h" //gotoxy, textcolor, textbackground

//Constants
#define FALSE 0
#define TRUE  1

//Screen constants
#define DEFAULT_BG_COLOR BLACK
#define DEFAULT_TEXT_COLOR LIGHTGRAY

#define WIDTH_BUTTON_INGAME 14
#define WIDTH_BUTTON_MENU 16
#define WIDTH_MENU_SELECTOR 3

#define MENU_LOGO_LINES 7
#define MENU_LOGO_COLUMNS 9   

#define GAME_CARD_WIDTH 12
#define GAME_CARD_HEIGHT 7

//App types
typedef unsigned char bool;

typedef enum enum_appStatus {
  STATUS_OK = 0,
  STATUS_ERROR,
  STATUS_RUNNING,
} enum_appStatus;

typedef enum enum_userAction {
  ACTION_NONE = 0,
} enum_userAction;

typedef enum enum_cursorState {
  CURSOR_HIDDEN = 0,
  CURSOR_VISIBLE,
} enum_cursorState;

typedef enum enum_gameCards {
  CARD2 = 1,
  CARD4,
  CARD8,
  CARD16,
  CARD32,
  CARD64,
  CARD128,
  CARD256,
  CARD512,
  CARD1024,
  CARD2048,
} enum_gameCards;

typedef struct type_leaderboard {
  char name[15][10];
  int points[10];
} type_leaderboard;

typedef struct type_gameState {
  int score;
  int moves;
  //COLORS gameCardColors[11];
  enum_gameCards gameCards[11];
  enum_gameCards * gameBoard[4][4];
} type_gameState;

typedef struct type_appState {
  enum_appStatus appStatus;
  enum_userAction userAction;
  type_leaderboard leaderboard;
  type_gameState gameState;
} type_appState;

#endif  /*MAIN_H*/