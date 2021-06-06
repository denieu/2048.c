/*------------------------------------------------------------------------------
 * 2048.c
 *
 * File: main.h
 * Author: Daniel Wojcickoski
 * Date: 2021/04/28
 * 
 * MIT License - Copyright (c) 2021 Daniel Wojcickoski
 *----------------------------------------------------------------------------*/
#ifndef  MAIN_H
#define  MAIN_H

//Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <pthread.h>
#include <windows.h>
#include "creact.h"

//Constants
#define FALSE 0
#define TRUE  1
#define NO_CHANGE -2

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

#define DEFAULT_SCREEN_TITLE L"2048c"
#define DEFAULT_SCREEN_X_SIZE 75
#define DEFAULT_SCREEN_Y_SIZE 27

#define MAX_LEADERBOARD_LENGHT 15

typedef unsigned char bool;

//Macros
#define SET_COLOR(BG, TEXT) \
  cr_setColors(BG, TEXT);

//Enums
typedef enum {
  STATUS_OK = 0,
  STATUS_ERROR,
  STATUS_RUNNING,
} appStatus_e;

typedef enum {
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
} keys_e;

typedef enum {
  ACTION_NONE = 0,

  ACTION_UP,
  ACTION_DOWN,
  ACTION_LEFT,
  ACTION_RIGTH,
  ACTION_ENTER,

  ACTION_PRE_ESCAPE,
  ACTION_NO_ESCAPE,
  ACTION_ESCAPE,

  ACTION_GAME_CONTINUE,
  ACTION_GAME_PRE_NEW,
  ACTION_GAME_NEW,

  ACTION_GAME_UNDO,
  
  ACTION_GAME_PRE_SAVE,
  ACTION_GAME_SAVE,
} userAction_e;

typedef enum {
  GAME_RUNNING = 0,
  GAME_LOSE,
  GAME_WIN,
} gameStatus_e;

typedef enum {
  CURSOR_HIDDEN = 0,
  CURSOR_VISIBLE,
} cursorState_e;

typedef enum {
  LEFT = 0,
  RIGHT,
} direction_e;

typedef enum {
  CARDNONE = 0,
  CARD2,
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
} gameCards_e;

typedef enum {
  SCREEN_NONE = -1,
  SCREEN_MENU = 0,
  SCREEN_GAME,
  SCREEN_ENDGAME,
  SCREEN_RANKING,
} screens_e;

typedef enum {
  STATE_MENU_FIRST,
  STATE_MENU_CONTINUE,
  STATE_MENU_NEWGAME,
  STATE_MENU_EXIT,
  STATE_MENU_LAST,
  STATE_MENU_CONTINUE_SELECT,
} menuState_e;

typedef enum {
  STATE_GAME_NORMAL,
  STATE_GAME_ESCAPE,
  STATE_GAME_NEW,
  STATE_GAME_SAVE,
} gameState_e;

//Types
typedef struct {
  int points[11];
  char name[11][MAX_LEADERBOARD_LENGHT];
} leaderboard_t;

typedef struct {
  COLORS color;
  gameCards_e exponent;
  int value;
} gameCard_t;

typedef struct {
  gameStatus_e gameStatus;

  int auxScore;
  int lastScore;
  int score;

  int auxMoves;
  int lastMoves;
  int moves;

  gameCard_t gameCards[11];
  gameCard_t * auxGameBoard[4][4];
  gameCard_t * lastGameBoard[4][4];
  gameCard_t * gameBoard[4][4];
} gameState_t;

typedef struct {
  gameStatus_e gameStatus;
  
  int lastScore;
  int score;
  int lastMoves;
  int moves;

  gameCards_e lastGameBoard[4][4];
  gameCards_e gameBoard[4][4];
} gameSave_t;

typedef struct {
  screens_e lastScreen;
  screens_e currentScreen;
  menuState_e menuState;
  gameState_e gameState;

  bool forceClear;
} screenState_t;

typedef struct {
  appStatus_e appStatus;
  userAction_e userAction;
  char userString[22];
  leaderboard_t leaderboard;
  gameState_t gameState;
  screenState_t screen;
} appState_t;

#endif  /*MAIN_H*/
