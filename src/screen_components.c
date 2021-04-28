#include "../includes/screen_components.h"

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

/*------------------------------------------------------------------------------
 * Printa duas strings centralizadas em duas colunas
 *----------------------------------------------------------------------------*/
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

  gotoxy(posX, posY);

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
 * Printa o menu de dentro do jogo
 *----------------------------------------------------------------------------*/
void print_inGameMenu(int posX, int posY){
  gotoxy(posX, posY);
  SET_COLOR(LIGHTGRAY, BLACK);
  printTwoCollumns("Tecla", "Acao", 11, 11);

  SET_COLOR(DARKGRAY, WHITE);
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

  SET_COLOR(DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
}

/*------------------------------------------------------------------------------
 * Printa o status do jogo, score e movimentos
 *----------------------------------------------------------------------------*/
void print_gameStatus(type_gameState gameState, int posX, int posY){
  char number[30] = {'\0'};

  gotoxy(posX, posY);
  SET_COLOR(LIGHTGRAY, BLACK);
  printf("         Score         ");

  gotoxy(posX, posY + 3);
  printf("       Movimentos      ");

  gotoxy(posX, posY + 1);
  SET_COLOR(DARKGRAY, WHITE);
  sprintf(number, "%d", gameState.score);
  stringCentrilize(number, 23);
  printf("%s", number);

  gotoxy(posX, posY + 4);
  sprintf(number, "%d", gameState.moves);
  stringCentrilize(number, 23);
  printf("%s", number);

  SET_COLOR(DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
}

/*------------------------------------------------------------------------------
 * Printa o ranking dentro jogo, score e jogadores
 *----------------------------------------------------------------------------*/
void print_inGameRanking(type_leaderboard * leaderboard, int posX, int posY){
  char number[15] = {'\0'};
  char name[15] = {'\0'};

  SET_COLOR(LIGHTGRAY, BLACK);
  gotoxy(posX, posY);
  printf("        Ranking        ");

  SET_COLOR(DARKGRAY, WHITE);
  for(int count = 0;count<11; count++){
    gotoxy(posX, posY+count+1);

    if(leaderboard->points[count] != 0)
      sprintf(number, "%d", leaderboard->points[count]);
    else
      sprintf(number, " ");
    strcpy(name, leaderboard->name[count]);

    printTwoCollumns(number, name, 11, 11);
  }

  SET_COLOR(DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
}

/*------------------------------------------------------------------------------
 * Printa a borda do tabuleiro
 *----------------------------------------------------------------------------*/
void print_gameBoardEdges(int posX, int posY){
  SET_COLOR(LIGHTGRAY, BLACK);

  for(int line = 0; line < 5; line++){
    for(int count = 0; count < (GAME_CARD_WIDTH * 4) - 2; count++){
      gotoxy(posX + count, posY + (line * (GAME_CARD_HEIGHT - 1)));
      printf(" ");
    }
    for(int count = 0; count < 25; count++){
      gotoxy(posX + (line * (GAME_CARD_WIDTH - 1)), posY + count);
      printf("  ");
    }
  }
  SET_COLOR(DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
}

/*------------------------------------------------------------------------------
 * Printa um casa do tabuleiro
 *----------------------------------------------------------------------------*/
void print_gameCard(type_gameCard * card, int posX, int posY){
  SET_COLOR(card != NULL ? card->color : DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);

  //Printa fundo da casa
  for(int count = 0; count < GAME_CARD_HEIGHT - 2; count++){
    gotoxy(posX + 2, posY + 1 + count);
    for(int count2 = 0; count2 < GAME_CARD_WIDTH - 3; count2++){
      printf(" ");
    }
  }

  if(card != NULL){
    gotoxy(posX + 2, posY + GAME_CARD_HEIGHT / 2);
    char cardString[GAME_CARD_WIDTH] = {'\0'};
    sprintf(cardString, "%d", card->value);

    stringCentrilize(cardString, GAME_CARD_WIDTH - 3);
    printf("%s", cardString);
  }

  SET_COLOR(DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
}

/*------------------------------------------------------------------------------
 * Printa o tabuleiro do jogo
 *----------------------------------------------------------------------------*/
void print_gameBoard(type_gameState * gameState, int posX, int posY){
  for(int collumn = 0; collumn < 4; collumn++){
    for(int line = 0; line < 4; line++){
      print_gameCard(gameState->gameBoard[line][collumn], posX + collumn * (GAME_CARD_WIDTH - 1), posY + line * (GAME_CARD_HEIGHT - 1));
    }
  }

  SET_COLOR(DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
}

/*------------------------------------------------------------------------------
 * Printa o componente que informa vitorio ou derrota do jogador
 *----------------------------------------------------------------------------*/
void print_endGameStatus(enum_gameStatus status, int posX, int posY){
  char spaces[30] = {'\0'};
  char endString[30] = {'\0'};

  //Printa a borda mais escura
  textbackground(LIGHTGRAY);
  sprintf(spaces, " ");
  stringCentrilize(spaces, 19);
  
  for(int count = 0; count < 5; count++){
    gotoxy(posX, posY + count);
    printf("  ");
    
    gotoxy(posX + 21, posY + count);
    printf("  ");

    if(count % 2 == 0){
      gotoxy(posX + 2, posY + count);
      printf("%s", spaces);
    }
  }
 
  //Printa os espaços claros
  textbackground(DARKGRAY);

  for(int count = 1; count <= 3; count++){
    gotoxy(posX + 2, posY + count);
    printf("%s", spaces);
  }

  //Printa oe stado do game
  if(status == GAME_WIN){
    textcolor(LIGHTGREEN);
    sprintf(endString, "Vitoria");
  }
  else if(status == GAME_LOSE){
    textcolor(RED);
    sprintf(endString, "Derrota");
  }
  stringCentrilize(endString, 19);

  gotoxy(posX + 2, posY + 2);
  printf("%s", endString);

  //Volta para as cores default
  SET_COLOR(DEFAULT_BG_COLOR, DEFAULT_TEXT_COLOR);
}

/*------------------------------------------------------------------------------
 * Printa componente que pede para o usuario digitar algo
 *----------------------------------------------------------------------------*/
void print_querryUserString(const char * placeholder, int posX, int posY, COLORS color1, COLORS color2){
  char string[30] = {'\0'};

  gotoxy(posX, posY);
  SET_COLOR(color1, BLACK);
  sprintf(string, "%s", placeholder);
  stringCentrilize(string, 23);
  printf("%s", string);

  gotoxy(posX, posY + 1);
  SET_COLOR(color2, WHITE);
  sprintf(string, " ");
  stringCentrilize(string, 23);
  printf("%s", string);

  gotoxy(posX + 1, posY + 1);
}