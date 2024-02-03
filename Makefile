default: invaders

OBJ=main.o
CFLAGS+=-I/opt/homebrew/include
LDFLAGS+=-L/opt/homebrew/lib
LIBS+=-lSDL2

invaders: $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS) $(LIBS)

clean:
	$(RM) invaders $(OBJ)
