# Nom de l'exécutable
TARGET = game_of_graphs

# Compilateur C++
CC = g++

# Options de compilation
CFLAGS = -std=c++11 -Wall

# Fichiers source
SRCS = main.cpp

# Fichiers objets générés à partir des fichiers source
OBJS = $(SRCS:.cpp=.o)

# Règle pour la cible principale
# Règle pour la cible principale
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Règle générique pour la compilation des fichiers source en fichiers objets
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyer les fichiers objets et l'exécutable
clean:
	rm -f $(OBJS) $(TARGET)

# Règle "all" pour tout compiler
all: $(TARGET)

.PHONY: clean