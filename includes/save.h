#ifndef  SAVE_H
#define  SAVE_H

//Includes
#include "../includes/main.h"

//Functions
type_gameState readSaveFile(const char * path);
void writeSaveFile(type_gameState * newSave, const char * path);

#endif  /*SAVE_H*/