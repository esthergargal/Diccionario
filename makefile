# Esther García Gallego
# INGENIERÍA INFORMÁTICA 2ºB
# Práctica 4 ED - Diccionario


# Carpeta donde se guardan los ejecutables
BIN = ./bin
# Compilador
CC = g++
# Carpeta donde se guarda la documentación
DOC = ./doc
# Carpeta donde se guardan los .h
INCLUDE = ./include
# Carpeta donde se guardan los objetos
OBJ = ./obj
# Carpeta donde se guardan los .cpp
SRC = ./src
# Navegador
BROWSER = firefox

diccionario:
	$(CC) -o $(BIN)/diccionario -I$(INCLUDE) $(SRC)/testdiccionario.cpp

clean:
	@echo "Limpiando..."
	rm -f $(OBJ)/* $(BIN)/*

doxy:
	@echo "Creando documentación..."
	doxygen doxyfile

display_doxy:
	@echo "Mostrando documentación..."
	$(BROWSER) $(DOC)/html/index.html &
