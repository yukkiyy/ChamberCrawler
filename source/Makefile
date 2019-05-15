CXX = g++-5
CXXFLAGS = -g -std=c++14 -Wall -MMD -Werror=vla -I/opt/X11/lib
EXEC =cc3k+
OBJECTS = barriersuit.o dragon.o human.o pctype.o treasure.o boostatk.o dragonhoard.o item.o phoenix.o troll.o boostdef.o dungeon.o main.o player.o vampire.o cell.o dwarf.o major.o poisonhealth.o void.o chamber.o elves.o merchant.o potion.o wall.o character.o enemy.o merchanthoard.o restorehealth.o werewolf.o compass.o floor.o normal.o smallhorde.o woundatk.o floortile.o observer.o stair.o wounddef.o direction.o game.o orc.o subject.o door.o goblin.o passage.o textdisplay.o invalid.o utility.o window.o mingyu.o

DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -L/opt/X11/lib -lX11 -lXpm -lncurses

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
