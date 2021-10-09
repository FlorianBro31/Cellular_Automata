SRCS:= src/Main.c src/Debug.c src/Objects.c src/Texte.c src/Update.c src/Utils.c
OBJS:= src/Main.o src/Debug.o src/Objects.o src/Texte.o src/Update.o src/Utils.o
TARGET:= bin/game
COMPILER:= clang
#SRCS:= $(wildcard src/*.c)
#OBJS:= $(SRCS:.c=.o)
#Probably a good way to automate this but for my sanity I'll do it the dumb way

#run the program
run: all
	./$(TARGET)
#link all the object file together
all: main_obj
	$(COMPILER) -o $(TARGET) $(OBJS) -lSDL2 -lSDL2_ttf

#build the object files
main_obj: debug_obj
	$(COMPILER) -o src/Main.o -c src/Main.c

debug_obj: objects_obj
	$(COMPILER) -o src/Debug.o -c src/Debug.c

objects_obj: texte_obj
	$(COMPILER) -o src/Objects.o -c src/Objects.c

texte_obj: update_obj
	$(COMPILER) -o src/Texte.o -c src/Texte.c

update_obj: utils_obj
	$(COMPILER) -o src/Update.o -c src/Update.c

utils_obj:
	$(COMPILER) -o src/Utils.o -c src/Utils.c

#Cleaning
.PHONY: clean
clean:
	-rm $(OBJS)
