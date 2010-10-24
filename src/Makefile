
CPP=g++
CFLAGS=-g -Wall
IFLAGS=
LFLAGS=-lncurses

FILES=\
	Main.o \
	GameState.o \
	View.o \
	ColorPairs.o \
	Level.o \
	MainView.o \
	Room.o \
	CompoundRoom.o \
	Entity.o \
	DataManager.o \
	Player.o \
	Entrance.o \
	Exit.o

EXECUTABLE=4drl

main: $(FILES)
	$(CPP) -o $(EXECUTABLE) $(LFLAGS) $(FILES)

clean:
	rm -rf $(FILES) $(EXECUTABLE)

%.o: %.cpp
	$(CPP) $(CFLAGS) $(IFLAGS) -c $^ -o $@
