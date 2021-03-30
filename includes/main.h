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
typedef enum{
  STATUS_OK = 0,
  STATUS_ERROR,
  STATUS_RUNNING,
} enum_appStatus;

typedef enum{
  ACTION_NONE = 0,
} enum_userAction;

typedef enum {
  CURSOR_HIDDEN = 0,
  CURSOR_VISIBLE,
} enum_cursorState;

typedef struct{
  int save;
} type_leaderboard;

typedef struct{
  int game;
} type_gameState;

typedef struct {
  enum_appStatus appStatus;
  enum_userAction userAction;
  type_leaderboard leaderboard;
  type_gameState gameState;
} type_appState;

#endif  /*MAIN_H*/