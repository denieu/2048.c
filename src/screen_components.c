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
  printTwoCollumns("U", "Desfazer", 11, 11);

  gotoxy(posX, posY + 5);
  printTwoCollumns("Setas", "Jogar", 11, 11);

  textbackground(DEFAULT_BG_COLOR);
  textcolor(DEFAULT_TEXT_COLOR);
}

/*------------------------------------------------------------------------------
 * Printa o status do jogo, score e movimentos
 *----------------------------------------------------------------------------*/
void print_gameStatus(type_gameState gameState, int posX, int posY){
  char number[30] = {'\0'};

  gotoxy(posX, posY);
  textbackground(LIGHTGRAY);textcolor(BLACK);
  printf("         Score         ");
  
  gotoxy(posX, posY + 1);
  textbackground(DARKGRAY);textcolor(WHITE);
  sprintf(number, "%d", gameState.score);
  stringCentrilize(number, 23);
  printf("%s", number);

  gotoxy(posX, posY + 3);
  textbackground(LIGHTGRAY);textcolor(BLACK);
  printf("       Movimentos      ");

  gotoxy(posX, posY + 4);
  textbackground(DARKGRAY);textcolor(WHITE);
  sprintf(number, "%d", gameState.moves);
  stringCentrilize(number, 23);
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
  for(int count = 0;count<11; count++){
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
 * Printa um casa do tabuleiro
 *----------------------------------------------------------------------------*/
void print_gameCard(enum_gameCards * card, int posX, int posY){
  COLORS gameCardColors[11] = {
    BLUE, GREEN, CYAN, RED, MAGENTA, BROWN,
    DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED
  };

  textbackground(LIGHTGRAY);textcolor(BLACK);
  //Borda superior
  for(int count = 0; count < GAME_CARD_WIDTH; count++){
    gotoxy(posX + count, posY);
    printf(" ");
    gotoxy(posX + count, posY + GAME_CARD_HEIGHT - 1);
    printf(" ");
  }
  //Bordas laterais
  for(int count = 0; count < GAME_CARD_HEIGHT; count++){
    gotoxy(posX , posY + count);
    printf("  ");
    gotoxy(posX + GAME_CARD_WIDTH - 1, posY + count);
    printf("  ");
  }

  if(card != NULL){
    textbackground(gameCardColors[*card - 1]); textcolor(DEFAULT_TEXT_COLOR);

    //Printa fundo da casa
    for(int count = 0; count < GAME_CARD_HEIGHT - 2; count++){
      gotoxy(posX + 2, posY + 1 + count);
      for(int count2 = 0; count2 < GAME_CARD_WIDTH - 3; count2++){
        printf(" ");
      }
    }

    gotoxy(posX + 2, posY + GAME_CARD_HEIGHT / 2);
    int cardValue = pow(2, *card);
    char cardString[GAME_CARD_WIDTH] = {'\0'};
    sprintf(cardString, "%d", cardValue);

    stringCentrilize(cardString, GAME_CARD_WIDTH - 4);
    printf("%s", cardString);
  }

  textbackground(DEFAULT_BG_COLOR); textcolor(DEFAULT_TEXT_COLOR);
}

/*------------------------------------------------------------------------------
 * Printa o tabuleiro do jogo
 *----------------------------------------------------------------------------*/
void print_gameBoard(type_gameState gameState, int posX, int posY){
  for(int collumn = 0; collumn < 4; collumn++){
    for(int line = 0; line < 4; line++){
      print_gameCard(gameState.gameBoard[line][collumn], posX + collumn * (GAME_CARD_WIDTH - 1), posY + line * (GAME_CARD_HEIGHT - 1));
    }
  }

  textbackground(DEFAULT_BG_COLOR);
  textcolor(DEFAULT_TEXT_COLOR);
}
