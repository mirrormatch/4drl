
CPP=g++
CFLAGS=-g -Wall
IFLAGS=
LFLAGS=-lncurses

FILES=\
	ColorPairs.o \
	CompoundRoom.o \
	DataManager.o \
	Entity.o \
	Entrance.o \
	Exit.o \
	GameState.o \
	IntroView.o \
	Level.o \
	Main.o \
	MainView.o \
	Player.o \
	PlayerCreateView.o \
	Room.o \
	View.o

EXECUTABLE=4drl

main: $(FILES)
	$(CPP) -o $(EXECUTABLE) $(LFLAGS) $(FILES)

clean:
	rm -rf $(FILES) $(EXECUTABLE)

%.o: %.cpp
	$(CPP) $(CFLAGS) $(IFLAGS) -c $^ -o $@
