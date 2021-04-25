#Compilador
COMPILADOR=gcc
#Nome do seu executavel
NOME_EXECUTAVEL=2048c
#Diretorio dos arquivos binarios
BIN=./bin
#Diretorio dos arquivos .h e .hpp
INCLUDE=./includes
#Diretorio dos arquivos-objetos
OBJ=./obj
#Diretorio dos arquivos .c e .cpp
SRC=./src
#Diretorio dos arquivos de bibliotecas
LIB=./libs
#Libs a linkas ao projeto
LIBFLAGS=-lconio

#Para otimizar e mostrar mais avisos
FLAGS= -O3 -Wall
#Para encontrar as bibliotecas utilizadas(em "-lm", apenas um exemplo, caso seu compilador nao faca isso por voce)
LIBS= -lm -L$(LIB) $(LIBFLAGS)

#Pega todos arquivos .c e muda os nomes para .o
#Fontes .c
FONTES=$(wildcard $(SRC)/*.c)
#Retirar prefixo e sufixo
OBJLIMPAR=$(notdir $(basename $(FONTES)))
#Adicionar novo prefixo e sufixo
OBJETOS=$(addprefix $(OBJ)/, $(addsuffix .o, $(OBJLIMPAR)))

.PHONY: all clean

all: compilar $(NOME_EXECUTAVEL)

#Arquivos .o do projeto
compilar: $(OBJETOS)

#Compilar e criar os arquivos-objetos
$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	$(COMPILADOR) $(FLAGS) -c $< -I $(INCLUDE) -o $@

#Linkar e criar o executavel
$(NOME_EXECUTAVEL): $(OBJETOS)
	$(COMPILADOR) $(FLAGS) $(OBJETOS) $(LIBS) -o $(BIN)/$@

#Executar programa
run:
	$(BIN)/$(NOME_EXECUTAVEL)

#Limpar executavel
clean:
	rm -f $(OBJ)/*.o
	rm -f $(BIN)/$(NOME_EXECUTAVEL)