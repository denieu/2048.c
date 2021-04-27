#ifndef  SAVE_H
#define  SAVE_H

//Includes
#include "../includes/main.h"

//Functions
void readSaveFile(type_appState * appState, const char * filename);
void writeSaveFile(type_gameState * gameState, const char * filename);

#endif  /*SAVE_H*/