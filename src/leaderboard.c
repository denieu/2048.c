#include "../includes/leaderboard.h"

/*------------------------------------------------------------------------------
 * Lê e retorna a estrutura salva no arquivo "leaderboard"
 *----------------------------------------------------------------------------*/
type_leaderboard readLeaderboardFile(){
  type_leaderboard leaderboard = { 0 };

  return leaderboard;
}

/*------------------------------------------------------------------------------
 * Escreve a estrutura newLeaderboard no arquivo "leaderboard"
 *----------------------------------------------------------------------------*/
void writeLeaderboardFile(type_leaderboard * newLeaderboard){
  
}

/*------------------------------------------------------------------------------
 * reorganiza a estrutura leaderdearboard em ordem decrescente
 *----------------------------------------------------------------------------*/
void bubbleSortLeaderboard(type_leaderboard * leaderboard){
  int flag = 0, end = 0;

  char auxName[15] = { 0 };
  int auxPoints = 0;

  do{
    flag = 0;

    for(int count = 11; count > end; count--){
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