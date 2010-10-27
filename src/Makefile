
CPP=g++
CFLAGS=-g -Wall
IFLAGS=
LFLAGS=-lncurses

FILES=\
	ArmorItem.o \
	BodyArmor.o \
	ColorPairs.o \
	CompoundRoom.o \
	Consumable.o \
	DataManager.o \
	DeathView.o \
	Entity.o \
	Entrance.o \
	Exit.o \
	GameState.o \
	Helm.o \
	Implant.o \
	IntroView.o \
	Inventory.o \
	InventoryView.o \
	Item.o \
	Level.o \
	Main.o \
	MainView.o \
	Monster.o \
	Node.o \
	Pants.o \
	Pathfinder.o \
	Player.o \
	PlayerCreateView.o \
	Room.o \
	Sight.o \
	View.o \
	Weapon.o

EXECUTABLE=4drl

main: $(FILES)
	$(CPP) -o $(EXECUTABLE) $(LFLAGS) $(FILES)

clean:
	rm -rf $(FILES) $(EXECUTABLE)

%.o: %.cpp
	$(CPP) $(CFLAGS) $(IFLAGS) -c $^ -o $@
