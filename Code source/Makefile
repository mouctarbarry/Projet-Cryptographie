

#
# Variables:
#
CC = gcc
BIN = AutoDecrypt
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
 
 
#
# Flags d'erreurs:
#
ERROR_CFLAGS = -Wall -W -pedantic -lm
 
 
#
# Flags pour le compilateur:
#
GLIB_CFLAGS = $$(pkg-config --cflags glib-2.0)
PANGO_CFLAGS = $$(pkg-config --cflags pango)
GTK_CFLAGS = $$(pkg-config --cflags gtk+-2.0)
 
CFLAGS = $(ERROR_FLAGS) $(GLIB_CFLAGS) $(PANGO_CFLAGS) $(GTK_CFLAGS)
 
 
#
# Flags pour l'editeur de liens:
#
GLIB_LDFLAGS = $$(pkg-config --libs glib-2.0)
PANGO_LDFLAGS = $$(pkg-config --libs pango)
GTK_LDFLAGS = $$(pkg-config --libs gtk+-2.0)
 
LDFLAGS = $(ERROR_FLAGS) $(GLIB_LDFLAGS) $(PANGO_LDFLAGS) $(GTK_LDFLAGS)
 
 
#
# Construction du programme:
#
all: $(BIN)
	@./$(BIN)
 
$(BIN): $(SRC)
	@$(CC) $(CFLAGS) -c $(SRC)
	@$(CC) $(LDFLAGS) -o $(BIN) $(OBJ) -lm
 
 
#
# Nettoyage:
#
clean:
	@rm -f *.o *~ core $(BIN)
	
rmproper: clean
	@rm -f 
	
