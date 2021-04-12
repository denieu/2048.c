#ifndef  MAIN_H
#define  MAIN_H

//Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
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

typedef unsigned char bool;

//Enums
typedef enum enum_appStatus {
  STATUS_OK = 0,
  STATUS_ERROR,
  STATUS_RUNNING,
} enum_appStatus;

typedef enum enum_keys{
  KEY_ENTER = 13,
  KEY_ESCAPE = 27,
  KEY_SPACE = 32,

  KEY_N = 78,
  KEY_S = 83,
  KEY_U = 85,

  KEY_UP = 72,
  KEY_LEFT = 75,
  KEY_RIGHT = 77,
  KEY_DOWN = 80,
} enum_keys;

typedef enum enum_userAction {
  ACTION_NONE = 0,

  ACTION_UP,
  ACTION_DOWN,
  ACTION_LEFT,
  ACTION_RIGTH,
  ACTION_ENTER,
  ACTION_ESCAPE,

  ACTION_GAME_CONTINUE,
  ACTION_GAME_NEW,
  ACTION_GAME_SAVE,
  ACTION_GAME_UNDO,
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

typedef enum enum_screens {
  SCREEN_MENU = 0,
  SCREEN_GAME,
  SCREEN_ENDGAME,
  SCREEN_HELP,
} enum_screens;

typedef enum enum_menuState{
  STATE_MENU_FIRST,
  STATE_MENU_CONTINUE,
  STATE_MENU_NEWGAME,
  STATE_MENU_HELP,
  STATE_MENU_EXIT,
  STATE_MENU_LAST,
} enum_menuState;

//Types
typedef struct type_leaderboard {
  char name[15][11];
  int points[11];
} type_leaderboard;

typedef struct type_gameState {
  int score;
  int moves;
  enum_gameCards gameCards[11];
  enum_gameCards * gameBoard[4][4];
} type_gameState;

typedef struct type_screenState{
  enum_screens currentScreen;
  enum_menuState menuState;
} type_screenState;

typedef struct type_appState {
  enum_appStatus appStatus;
  enum_userAction userAction;
  type_leaderboard leaderboard;
  type_gameState gameState;
  type_screenState screen;
} type_appState;

#endif  /*MAIN_H*/