#include "../includes/screen_components.h"
#include "../includes/conio2.h" //gotoxy, textcolor, textbackground
#include "windows.h"

/*------------------------------------------------------------------------------
 * Retorna a string centralizada, com base no tamanho informado
 *----------------------------------------------------------------------------*/
void stringCentrilize(char * string, int maxSize){
  int stringSize = strlen(string);
  char preSpaces[100] = {'\0'};
  char posSpaces[100] = {'\0'};
  char newString[100] = {'\0'};

  for(int count = 0; count < (maxSize - stringSize) / 2; count++){
    preSpaces[count] = ' ';
  }
  for(int count = 0; count < (maxSize - stringSize - strlen(preSpaces)); count++){
    posSpaces[count] = ' ';
  }
  sprintf(newString, "%s%s%s", preSpaces, string, posSpaces);
  strcpy(string, newString);
}

void printTwoCollumns(char * left, char * right, int leftSize, int rightSize){
  char leftString[12] = {'\0'};
  char rightString[12] = {'\0'};

  strcpy(leftString, left); 
  strcpy(rightString, right);

  stringCentrilize(leftString, leftSize); 
  stringCentrilize(rightString, rightSize);

  printf("%s %s", leftString, rightString);
}

/*------------------------------------------------------------------------------
 * Printa um botão para menu, selected define se o botão está o não selecionado
 *----------------------------------------------------------------------------*/
void print_menuButton(char * placeholder, int posX, int posY, bool selected){
  char selection[WIDTH_BUTTON_MENU + 1] = {0};
  int placeholderSize = strlen(placeholder);
  int numberOfSpaces = WIDTH_BUTTON_MENU - placeholderSize - WIDTH_MENU_SELECTOR;

  for(int count = 0; count < numberOfSpaces ; count++)
    selection[count] = ' ';

  selection[numberOfSpaces] = '<';
  selection[numberOfSpaces + 1] = '-';
  selection[numberOfSpaces + 2] = '-';
  selection[numberOfSpaces + 3] = '\0';

  gotoxy(posX, posY);

  if(selected == TRUE)
    textcolor(RED);

  printf("%s%s", placeholder, (selected == TRUE) ? selection : "");

  textbackground(DEFAULT_BG_COLOR);
  textcolor(DEFAULT_TEXT_COLOR);
}

/*------------------------------------------------------------------------------
 * Printa o menu de dentro do jogo
 *----------------------------------------------------------------------------*/
void print_inGameMenu(int posX, int posY){
  gotoxy(posX, posY);
  textbackground(LIGHTGRAY); textcolor(BLACK);
  printTwoCollumns("Tecla", "Acao", 11, 11);

  textbackground(DARKGRAY);textcolor(WHITE);
  gotoxy(posX, posY + 1);
  printTwoCollumns("ESC", "Sair", 11, 11);

  gotoxy(posX, posY + 2);
  printTwoCollumns("N", "Novo Jogo", 11, 11);

  gotoxy(posX, posY + 3);
  printTwoCollumns("S", "Salvar", 11, 11);

  gotoxy(posX, posY + 4);
  printTwoCollumns("B", "Desfazer", 11, 11);

  gotoxy(posX, posY + 5);
  printTwoCollumns("Setas", "Jogar", 11, 11);

  textbackground(DEFAULT_BG_COLOR);
  textcolor(DEFAULT_TEXT_COLOR);
}

/*------------------------------------------------------------------------------
 * Printa o status do jogo, score e movimentos
 *----------------------------------------------------------------------------*/
void print_gameStatus(type_gameState gameState, int posX, int posY){
  char number[10] = {'\0'};

  gotoxy(posX, posY);
  textbackground(LIGHTGRAY);textcolor(BLACK);
  printf("  Score   ");

  textbackground(DEFAULT_BG_COLOR);textcolor(DEFAULT_TEXT_COLOR);
  printf(" ");

  textbackground(LIGHTGRAY);textcolor(BLACK);
  printf(" Movimentos ");

  gotoxy(posX, posY + 1);
  textbackground(DARKGRAY);textcolor(WHITE);
  sprintf(number, "%d", gameState.score);
  stringCentrilize(number, 10);
  printf("%s", number);

  textbackground(DEFAULT_BG_COLOR);textcolor(DEFAULT_TEXT_COLOR);
  printf(" ");

  textbackground(DARKGRAY);textcolor(WHITE);
  sprintf(number, "%d", gameState.moves);
  stringCentrilize(number, 12);
  printf("%s", number);

  textbackground(DEFAULT_BG_COLOR);textcolor(DEFAULT_TEXT_COLOR);
}

/*------------------------------------------------------------------------------
 * Printa o ranking dentro jogo, score e jogadores
 *----------------------------------------------------------------------------*/
void print_inGameRanking(type_leaderboard leaderboard, int posX, int posY){
  char number[15] = {'\0'};
  char name[15] = {'\0'};

  textbackground(LIGHTGRAY);textcolor(BLACK);
  gotoxy(posX, posY);
  printf("        Ranking        ");

  textbackground(DARKGRAY);textcolor(WHITE);
  for(int count = 0;count<10; count++){
    gotoxy(posX, posY+count+1);

    if(leaderboard.points[count] != 0)
      sprintf(number, "%d", leaderboard.points[count]);
    else
      sprintf(number, " ");
    strcpy(name, leaderboard.name[count]);

    printTwoCollumns(number, name, 11, 11);
  }

  textbackground(DEFAULT_BG_COLOR);
  textcolor(DEFAULT_TEXT_COLOR);
}

/*------------------------------------------------------------------------------
 * Printa o tabuleiro do jogo
 *----------------------------------------------------------------------------*/
void print_gameBoard(type_gameState gameState, int posX, int posY){

  textbackground(DEFAULT_BG_COLOR);
  textcolor(DEFAULT_TEXT_COLOR);
}
