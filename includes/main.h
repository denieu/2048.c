#ifndef  MAIN_H
#define  MAIN_H

//Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Constants
#define FALSE 0
#define TRUE  1

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

typedef struct type_leaderboard {
  int save;
} type_leaderboard;

typedef struct type_gameState {
  int game;
} type_gameState;

typedef struct type_appState {
  enum_appStatus appStatus;
  enum_userAction userAction;
  type_leaderboard leaderboard;
  type_gameState gameState;
} type_appState;

#endif  /*MAIN_H*/