/*------------------------------------------------------------------------------
 * 2048.c
 *
 * File: screen_components.c
 * Author: Daniel Wojcickoski
 * Date: 2021/04/28
 * 
 * MIT License - Copyright (c) 2021 Daniel Wojcickoski
 *----------------------------------------------------------------------------*/
#include "../includes/screen_components.h"

/*------------------------------------------------------------------------------
 * Returns the centralized string, based on the size entered
 *----------------------------------------------------------------------------*/
void stringCentrilize(char * string, int maxSize){
  int stringSize = strlen(string);
  char preSpaces[100] = {'\0'};
  char posSpaces[100] = {'\0'};
  char newString[100] = {'\0'};

  int qtdPreSpaces = (maxSize - stringSize) / 2;
  int qtdPosSpaces = (maxSize - stringSize - qtdPreSpaces);

  for(int count = 0; count < qtdPreSpaces ; count++){
    preSpaces[count] = ' ';
  }
  for(int count = 0; count < qtdPosSpaces; count++){
    posSpaces[count] = ' ';
  }

  strcat(newString, preSpaces);
  strcat(newString, string);
  strcat(newString, posSpaces);

  strcpy(string, newString);
}

/*------------------------------------------------------------------------------
 * Print two strings centered on two columns
 *----------------------------------------------------------------------------*/
void printTwoCollumns(char * left, char * right, int leftSize, int rightSize){
  char leftString[100] = {'\0'};
  char rightString[100] = {'\0'};
  char auxString[100] = {'\0'};

  char preSpaces[100] = {'\0'};
  char posSpaces[100] = {'\0'};
  int qtdPreSpaces = leftSize - strlen(left);
  int qtdPosSpaces = rightSize  - strlen(right);

  for(int count = 0; count < qtdPreSpaces ; count++){
    preSpaces[count] = ' ';
  }
  for(int count = 0; count < qtdPosSpaces; count++){
    posSpaces[count] = ' ';
  }
  
  strcpy(leftString, left);
  strcpy(rightString, right);

  sprintf(auxString, "%s%s %s%s", preSpaces, leftString, rightString, posSpaces);

  printf("%s", auxString);
}

/*------------------------------------------------------------------------------
 * Prints a button to menu, selected defines if the button is unselected
 *----------------------------------------------------------------------------*/
void print_menuButton(char * placeholder, int posX, int posY, bool selected){
  char selection[WIDTH_BUTTON_MENU + 1] = {0};
  int placeholderSize = strlen(placeholder);
  int numberOfSpaces = WIDTH_BUTTON_MENU - placeholderSize - WIDTH_MENU_SELECTOR;

  cr_moveCursorXY(posX, posY);

  for(int count = 0; count < numberOfSpaces + 3; count++)
    selection[count] = ' ';

  if(selected == TRUE){
    SET_COLOR(DARKGRAY, WHITE);
    selection[numberOfSpaces] = '<';
    selection[numberOfSpaces + 1] = '-';
    selection[numberOfSpaces + 2] = '-';
  }
  selection[numberOfSpaces + 3] = '\0';

  printf(" %s%s ", placeholder, selection);

  SET_COLOR(DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
}

/*------------------------------------------------------------------------------
 * Print the in-game menu
 *----------------------------------------------------------------------------*/
void print_inGameMenu(int posX, int posY){
  cr_moveCursorXY(posX, posY);
  SET_COLOR(LIGHTGRAY, BLACK);
  printTwoCollumns("Tecla", "Acao", 11, 11);

  SET_COLOR(DARKGRAY, WHITE);
  cr_moveCursorXY(posX, posY + 1);
  printTwoCollumns("ESC", "Sair", 11, 11);

  cr_moveCursorXY(posX, posY + 2);
  printTwoCollumns("N", "Novo Jogo", 11, 11);

  cr_moveCursorXY(posX, posY + 3);
  printTwoCollumns("S", "Salvar", 11, 11);

  cr_moveCursorXY(posX, posY + 4);
  printTwoCollumns("U", "Desfazer", 11, 11);

  cr_moveCursorXY(posX, posY + 5);
  printTwoCollumns("Setas", "Jogar", 11, 11);

  SET_COLOR(DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
}

/*------------------------------------------------------------------------------
 * Print game status, score and moves
 *----------------------------------------------------------------------------*/
void print_gameStatus(gameState_t gameState, int posX, int posY){
  char number[30] = {'\0'};

  cr_moveCursorXY(posX, posY);
  SET_COLOR(LIGHTGRAY, BLACK);
  printf("         Score         ");

  cr_moveCursorXY(posX, posY + 3);
  printf("       Movimentos      ");

  cr_moveCursorXY(posX, posY + 1);
  SET_COLOR(DARKGRAY, WHITE);
  sprintf(number, "%d", gameState.score);
  stringCentrilize(number, 23);
  printf("%s", number);

  cr_moveCursorXY(posX, posY + 4);
  sprintf(number, "%d", gameState.moves);
  stringCentrilize(number, 23);
  printf("%s", number);

  SET_COLOR(DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
}

/*------------------------------------------------------------------------------
 * Printa o ranking dentro jogo, score e jogadores
 *----------------------------------------------------------------------------*/
void print_inGameRanking(leaderboard_t * leaderboard, int posX, int posY){
  char number[15] = {'\0'};
  char name[15] = {'\0'};

  SET_COLOR(LIGHTGRAY, BLACK);
  cr_moveCursorXY(posX, posY);
  printf("        Ranking        ");

  cr_moveCursorXY(posX, posY + 11);
  printf("                       ");

  SET_COLOR(DARKGRAY, WHITE);
  for(int count = 0;count<10; count++){
    cr_moveCursorXY(posX, posY+count+1);

    if(leaderboard->points[count] != 0)
      sprintf(number, "%d", leaderboard->points[count]);
    else
      sprintf(number, " ");
    strcpy(name, leaderboard->name[count]);

    printTwoCollumns(number, name, 7, 15);
  }

  SET_COLOR(DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
}

/*------------------------------------------------------------------------------
 * Print the edge of the board
 *----------------------------------------------------------------------------*/
void print_gameBoardEdges(int posX, int posY){
  SET_COLOR(LIGHTGRAY, BLACK);

  for(int line = 0; line < 5; line++){
    for(int count = 0; count < (GAME_CARD_WIDTH * 4) - 2; count++){
      cr_moveCursorXY(posX + count, posY + (line * (GAME_CARD_HEIGHT - 1)));
      printf(" ");
    }
    for(int count = 0; count < 25; count++){
      cr_moveCursorXY(posX + (line * (GAME_CARD_WIDTH - 1)), posY + count);
      printf("  ");
    }
  }
  SET_COLOR(DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
}

/*------------------------------------------------------------------------------
 * Print a board house
 *----------------------------------------------------------------------------*/
void print_gameCard(gameCard_t * card, int posX, int posY){
  SET_COLOR(card != NULL ? card->color : DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);

  for(int count = 0; count < GAME_CARD_HEIGHT - 2; count++){
    cr_moveCursorXY(posX + 2, posY + 1 + count);
    for(int count2 = 0; count2 < GAME_CARD_WIDTH - 3; count2++){
      printf(" ");
    }
  }

  if(card != NULL){
    cr_moveCursorXY(posX + 2, posY + GAME_CARD_HEIGHT / 2);
    char cardString[GAME_CARD_WIDTH] = {'\0'};
    sprintf(cardString, "%d", card->value);

    stringCentrilize(cardString, GAME_CARD_WIDTH - 3);
    printf("%s", cardString);
  }

  SET_COLOR(DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
}

/*------------------------------------------------------------------------------
 * Print the game board
 *----------------------------------------------------------------------------*/
void print_gameBoard(gameState_t * gameState, int posX, int posY){
  for(int collumn = 0; collumn < 4; collumn++){
    for(int line = 0; line < 4; line++){
      print_gameCard(gameState->gameBoard[line][collumn], posX + collumn * (GAME_CARD_WIDTH - 1), posY + line * (GAME_CARD_HEIGHT - 1));
    }
  }

  SET_COLOR(DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
}

/*------------------------------------------------------------------------------
 * Print the component that informs the player of victory or defeat
 *----------------------------------------------------------------------------*/
void print_endGameStatus(gameStatus_e status, int posX, int posY){
  char spaces[30] = {'\0'};
  char endString[30] = {'\0'};

  cr_bgColor(LIGHTGRAY);
  sprintf(spaces, " ");
  stringCentrilize(spaces, 19);
  
  for(int count = 0; count < 5; count++){
    cr_moveCursorXY(posX, posY + count);
    printf("  ");
    
    cr_moveCursorXY(posX + 21, posY + count);
    printf("  ");

    if(count % 2 == 0){
      cr_moveCursorXY(posX + 2, posY + count);
      printf("%s", spaces);
    }
  }
 
  cr_bgColor(DARKGRAY);
  for(int count = 1; count <= 3; count++){
    cr_moveCursorXY(posX + 2, posY + count);
    printf("%s", spaces);
  }

  if(status == GAME_WIN){
    cr_textColor(LIGHTGREEN);
    sprintf(endString, "Vitoria");
  }
  else if(status == GAME_LOSE){
    cr_textColor(RED);
    sprintf(endString, "Derrota");
  }
  stringCentrilize(endString, 19);

  cr_moveCursorXY(posX + 2, posY + 2);
  printf("%s", endString);

  //Volta para as cores default
  SET_COLOR(DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
}

/*------------------------------------------------------------------------------
 * Print component that asks the user to type something
 *----------------------------------------------------------------------------*/
void print_querryUserString(const char * placeholder, int posX, int posY, COLORS color1, COLORS color2){
  char string[30] = {'\0'};

  cr_moveCursorXY(posX, posY);
  SET_COLOR(color1, BLACK);
  sprintf(string, "%s", placeholder);
  stringCentrilize(string, 23);
  printf("%s", string);

  cr_moveCursorXY(posX, posY + 1);
  SET_COLOR(color2, WHITE);
  sprintf(string, " ");
  stringCentrilize(string, 23);
  printf("%s", string);

  cr_moveCursorXY(posX + 1, posY + 1);
}