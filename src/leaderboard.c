/*------------------------------------------------------------------------------
 * 2048.c
 *
 * File: leaderboard.c
 * Author: Daniel Wojcickoski
 * Date: 2021/04/28
 * 
 * MIT License - Copyright (c) 2021 Daniel Wojcickoski
 *----------------------------------------------------------------------------*/
#include "../includes/leaderboard.h"

/*------------------------------------------------------------------------------
 * Reads and returns the structure saved in the "leaderboard" file
 *----------------------------------------------------------------------------*/
leaderboard_t readLeaderboardFile(){
  leaderboard_t leaderboard = { 0 };
  char auxName[255] = {0};

  FILE * leaderboardFile = NULL;
  leaderboardFile = fopen(PATH_LEADERBOARD, "rt");
  if(leaderboardFile == NULL)
    return leaderboard;

  for(int count = 0; count < 10; count++){
    fscanf(leaderboardFile, "%d", &leaderboard.points[count]);
    fgets(auxName, 255, leaderboardFile);
    
    strncpy(leaderboard.name[count], &auxName[1], MAX_LEADERBOARD_LENGHT);

    //Adicionando o \0 para ter certeza que não ficou com o tamanho maior que o esperado no programa
    leaderboard.name[count][strlen(leaderboard.name[count]) - 1] = '\0';
    leaderboard.name[count][MAX_LEADERBOARD_LENGHT - 1] = '\0';
  }

  fclose(leaderboardFile);
  return leaderboard;
}

/*------------------------------------------------------------------------------
 * Write the new Leaderboard structure in the "leaderboard" file
 *----------------------------------------------------------------------------*/
void writeLeaderboardFile(leaderboard_t * leaderboard){
  FILE *leaderboardFile = NULL;
  leaderboardFile = fopen(PATH_LEADERBOARD, "w+");

  for(int count = 0; count < 10; count++){
    fprintf(leaderboardFile, "%d\t%s\n", leaderboard->points[count], leaderboard->name[count]);
  }

  fclose(leaderboardFile);
}

/*------------------------------------------------------------------------------
 * Rearranges the leaderboard structure in descending order
 *----------------------------------------------------------------------------*/
void bubbleSortLeaderboard(leaderboard_t * leaderboard){
  int flag = 0, end = 0;

  char auxName[MAX_LEADERBOARD_LENGHT + 1] = { 0 };
  int auxPoints = 0;

  do{
    flag = 0;

    for(int count = 10; count > end; count--){
      if(leaderboard->points[count] > leaderboard->points[count - 1]){
        strcpy(auxName, leaderboard->name[count]);
        auxPoints = leaderboard->points[count];

        strcpy(leaderboard->name[count], leaderboard->name[count - 1]);
        leaderboard->points[count] = leaderboard->points[count - 1];

        strcpy(leaderboard->name[count - 1], auxName);
        leaderboard->points[count - 1] = auxPoints;
        flag = 1;
      }
    }

    end++;
  } while(flag == 1);
}
