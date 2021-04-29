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
#include "../includes/conio2.h" //gotoxy, textcolor, textbackground

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

typedef unsigned char bool; //Variavel Booleana, deve receber TRUE ou FALSE

//Macros
#define SET_COLOR(BG, TEXT) \
  textbackground(BG); \
  textcolor(TEXT);

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

  ACTION_PRE_ESCAPE,
  ACTION_NO_ESCAPE,
  ACTION_ESCAPE,

  ACTION_GAME_CONTINUE,
  ACTION_GAME_NEW,

  ACTION_GAME_UNDO,
  
  ACTION_GAME_PRE_SAVE,
  ACTION_GAME_SAVE,
} enum_userAction;

typedef enum enum_gameStatus{
  GAME_RUNNING = 0,
  GAME_LOSE,
  GAME_WIN,
} enum_gameStatus;

typedef enum enum_cursorState {
  CURSOR_HIDDEN = 0,
  CURSOR_VISIBLE,
} enum_cursorState;

typedef enum enum_direction {
  LEFT = 0,
  RIGHT,
} enum_direction;

typedef enum enum_gameCards {
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
} enum_gameCards;

typedef enum enum_screens {
  SCREEN_NONE = -1,
  SCREEN_MENU = 0,
  SCREEN_GAME,
  SCREEN_ENDGAME,
} enum_screens;

typedef enum enum_menuState{
  STATE_MENU_FIRST,
  STATE_MENU_CONTINUE,
  STATE_MENU_NEWGAME,
  STATE_MENU_EXIT,
  STATE_MENU_LAST,
  STATE_MENU_CONTINUE_SELECT,
} enum_menuState;

typedef enum enum_gameState{
  STATE_GAME_NORMAL,
  STATE_GAME_ESCAPE,
  STATE_GAME_SAVE,
} enum_gameState;

//Types
typedef struct type_leaderboard {
  int points[11];
  char name[11][MAX_LEADERBOARD_LENGHT];
} type_leaderboard;

typedef struct type_gameCard {
  COLORS color;
  enum_gameCards exponent;
  int value;
} type_gameCard;

typedef struct type_gameState {
  enum_gameStatus gameStatus;

  int auxScore;
  int lastScore;
  int score;

  int auxMoves;
  int lastMoves;
  int moves;

  type_gameCard gameCards[11];
  type_gameCard * auxGameBoard[4][4];
  type_gameCard * lastGameBoard[4][4];
  type_gameCard * gameBoard[4][4];
} type_gameState;


typedef struct type_gameSave {
  enum_gameStatus gameStatus;
  
  int lastScore;
  int score;
  int lastMoves;
  int moves;

  enum_gameCards lastGameBoard[4][4];
  enum_gameCards gameBoard[4][4];
} type_gameSave;

typedef struct type_screenState {
  enum_screens lastScreen;
  enum_screens currentScreen;
  enum_menuState menuState;
  enum_gameState gameState;

  bool forceClear;
} type_screenState;

typedef struct type_appState {
  enum_appStatus appStatus;
  enum_userAction userAction;
  char userString[22];
  type_leaderboard leaderboard;
  type_gameState gameState;
  type_screenState screen;
} type_appState;

#endif  /*MAIN_H*/
