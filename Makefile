INCLIBS = -Ilib
LDLIBS += lib/libSDL3.a lib/libSDL3_ttf.a -lm -lfreetype

all: snake

common/utils.o: common/utils.c
	$(CC) -Wall -c common/utils.c -o common/utils.o

draw/draw.o: draw/draw.c
	$(CC) -Wall -c draw/draw.c -o draw/draw.o $(INCLIBS)

entity/food.o: entity/food.c
	$(CC) -Wall -c entity/food.c -o entity/food.o $(INCLIBS)

entity/player.o: entity/player.c
	$(CC) -Wall -c entity/player.c -o entity/player.o $(INCLIBS)

snake: common/utils.o draw/draw.o entity/food.o entity/player.o
	$(CC) -Wall main.c common/utils.o draw/draw.o entity/food.o entity/player.o -o snake $(INCLIBS) $(LDLIBS)

clean:
	rm -rfv snake common/*.o draw/*.o entity/*.o