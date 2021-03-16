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
} typeAppStatus;

typedef enum{
  ACTION_NONE = 0,
} typeUserAction;

typedef struct{
  int save;
} typeSave;

typedef struct{
  int game;
} typeGameState;

typedef struct {
  typeAppStatus appStatus;
  typeUserAction userAction;
  typeSave save;
  typeGameState gameState;
} typeAppState;

#endif  /*MAIN_H*/