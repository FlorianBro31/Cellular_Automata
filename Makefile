SOURCES = src/Main.c src/Debug.c src/Objects.c src/Texte.c src/Update.c src/Utils.c
OBJS = $(addsuffix .o, $(basename $(SOURCES)))
LIBS = -lSDL2 -lSDL2_ttf
TARGET = game
COMPILER = gcc

%.o:%.cpp
	$(COMPILER) -c -o $@ $<

#run the program
#run: all
#	./$(TARGET)

all:$(TARGET)
	@echo Build complete

$(TARGET):$(OBJS)
	$(COMPILER) -o $@ $^ $(LIBS)
	
#Cleaning
.PHONY: clean
clean:
	-rm $(OBJS)
