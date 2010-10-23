
CPP=g++
CFLAGS=-g -Wall
IFLAGS=
LFLAGS=-lncurses

FILES=Main.o GameState.o View.o
EXECUTABLE=4drl

main: $(FILES)
	$(CPP) -o $(EXECUTABLE) $(LFLAGS) $(FILES)

clean:
	rm -rf $(FILES) $(EXECUTABLE)

%.o: %.cpp
	$(CPP) $(CFLAGS) $(IFLAGS) -c $^ -o $@
