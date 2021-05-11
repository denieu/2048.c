#Compilador
COMPILADOR=gcc
#Compilador Resources
COMPILADOR_RC=windres
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
#Diretorio dos recursos
RC=./resources
#Libs a linkas ao projeto
LIBFLAGS=-lconio

#Flags compilador RC
FLAGS_RC=-O coff -o
#Para otimizar e mostrar mais avisos
FLAGS= -g -Wall
#Para encontrar as bibliotecas utilizadas(em "-lm", apenas um exemplo, caso seu compilador nao faca isso por voce)
LIBS= -lm -L$(LIB) $(LIBFLAGS)

#Pega todos arquivos .c e muda os nomes para .o
#Fontes .c
FONTES=$(wildcard $(SRC)/*.c)
#Retirar prefixo e sufixo
OBJLIMPAR=$(notdir $(basename $(FONTES)))
#Adicionar novo prefixo e sufixo
OBJETOS=$(addprefix $(OBJ)/, $(addsuffix .o, $(OBJLIMPAR)))

#Pega os arquivos .rc e muda para .res
RECURSOS=$(wildcard $(RC)/*.rc)
#Retirar prefixo e sufixo
RCLIMPAR=$(notdir $(basename $(RECURSOS)))
#Adicionar novo prefixo e sufixo
RES=$(addprefix $(OBJ)/, $(addsuffix .res, $(RCLIMPAR)))

.PHONY: all clean

all: compilar_rc compilar $(NOME_EXECUTAVEL)

#Compilar e criar os arquivos-recurso
compilar_rc: $(RES)
#Arquivos .o do projeto
compilar: $(OBJETOS)

#Compilar e criar os arquivos-recurso
$(OBJ)/%.res: $(RC)/%.rc
	$(COMPILADOR_RC) $< $(FLAGS_RC) $@

#Compilar e criar os arquivos-objetos
$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	$(COMPILADOR) $(FLAGS) -c $< -I $(INCLUDE) -o $@

#Linkar e criar o executavel
$(NOME_EXECUTAVEL): $(OBJETOS)
	$(COMPILADOR) $(FLAGS) $(RES) $(OBJETOS) $(LIBS) -o $(BIN)/$@

#Executar programa
run:
	$(BIN)/$(NOME_EXECUTAVEL)

#Limpar executavel
clean:
	rm -f $(OBJ)/*.o
	rm -f $(OBJ)/*.res
	rm -f $(BIN)/$(NOME_EXECUTAVEL)