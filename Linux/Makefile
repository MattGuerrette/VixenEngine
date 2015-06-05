CC=g++
LIB_FLAGS= -std=c++11 -Wall -w -shared -fPIC
EXE_FLAGS= -std=c++11 -Wall -w -g
USR_INC:= -I/usr/include/ -I/usr/local/include/
VCORE_INC:= -I../include/ -I../include/vcore/ -I../dependencies/jsoncpp/ $(USR_INC)
VCORE_SRC:= $(wildcard ../source/vcore/*.cpp ../dependencies/jsoncpp/*.cpp)
VCORE_LIB:= -L/usr/lib64/
VGRAPHICS_INC:= -I../include/ -I../include/vcore/ -I../include/vgraphics $(USR_INC)
VGRAPHICS_SRC:= $(wildcard ../source/vgraphics/*.cpp)
VGRAPHICS_LIB:= -L/usr/lib64/
VGAME_INC:= -I../include/ -I../include/vcore/ -I../include/vgraphics/ -I../include/vgame/ $(USR_INC)
VGAME_SRC:= $(wildcard ../source/vgame/*.cpp)
VGAME_LIB:= -L/usr/lib64/
EXE_INC:= -I../include/ -I../include/vcore/ -I../include/vgraphics/ -I../include/vgame/ $(USR_INC) -I/include/
EXE_SRC:= $(wildcard src/*.cpp)
EXE_LIB:= -L/usr/lib64/nvidia-bumblebee/tls -L/usr/lib64/nvidia-bumblebee  -L/usr/lib64  -L/usr/local/lib -lvgame -lvgraphics -lvaudio -lvcore -lSDL2 -lGLEW -lGL -lGLU -lfreeimage -larchive -ltinyxml2 -lassimp
LIB_OUTDIR:= /usr/local/lib/

VCORE_TARGET:= libvcore.so
VGRAPHICS_TARGET:= libvgraphics.so
VGAME_TARGET:= libvgame.so

EXE:= vtest

all: vcore vgraphics vgame $(EXE)

vcore:
	$(CC) $(LIB_FLAGS) $(VCORE_INC) $(VCORE_SRC) $(VCORE_LIB) -o $(LIB_OUTDIR)$(VCORE_TARGET)

vgraphics:
	$(CC) $(LIB_FLAGS) $(VGRAPHICS_INC) $(VGRAPHICS_SRC) $(VGRAPHICS_LIB) -o $(LIB_OUTDIR)$(VGRAPHICS_TARGET)

vgame:
	$(CC) $(LIB_FLAGS) $(VGAME_INC) $(VGAME_SRC) $(VGAME_LIB) -o $(LIB_OUTDIR)$(VGAME_TARGET)

$(EXE):
	$(CC) $(EXE_FLAGS) $(EXE_INC) $(EXE_SRC) $(EXE_LIB) -o $(EXE)

valgrind:
	valgrind --leak-check=yes --log-file="valgrind_output.txt" --track-origins=yes ./$(EXE)
clean:
	rm $(EXE)
