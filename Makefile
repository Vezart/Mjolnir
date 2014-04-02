# define libraries
ifeq ($(shell uname),Darwin)
LIB = -DMAC -framework OPENGL -framework GLUT
else
LIB = -lGL -lGLU -lglut
endif
#LIB2 = libim/libim.a jpeg/libjpeg.a

# define makefile targets
CC = g++ 
BIN = mjolnir

ifeq ($(shell hostname),turing)
all:
else
all: $(BIN) $(LIB2)
endif#CUSTOM JPEG LIBRARY COMPILATION; MAY NEED TO REPLACE W/ PNG
#jpeg/libjpeg.a:
	#cd jpeg;make;cd ..
#libim/libim.a:
	#cd libim;make;cd ..

clean: 
	/bin/rm -f $(BIN) $(LIB2)

#ADD NEW .CPP FILES HERE:
mjolnir: 
	$(CC) -o mjolnir Mjolnir.cpp Board.cpp Tile.cpp Player.cpp Sentinel.cpp Soundblast.cpp $(LIB) 
