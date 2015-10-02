CC=g++
COMPILER_DEFINES= -DVIX_OPENGL_BUILD
LIB_FLAGS= -std=c++11 -Wall -w -g -shared -fPIC $(COMPILER_DEFINES)
EXE_FLAGS= -std=c++11 -Wall -w -g $(COMPILER_DEFINES)
USR_INC:= -I/usr/include/ -I/usr/include/lua5.2/ -I/usr/local/include/
VCORE_INC:= -I../include/ -I../include/vcore/ $(USR_INC)
VCORE_SRC:= $(wildcard ../source/vcore/*.cpp ../dependencies/jsoncpp/*.cpp)
VCORE_LIB:= -L/usr/lib64/
VGRAPHICS_INC:= -I../include/ -I../include/vcore/ -I../include/vgraphics -I../include/vgraphics/opengl $(USR_INC)
VGRAPHICS_SRC:= $(wildcard ../source/vgraphics/*.cpp ../source/vgraphics/opengl/*.cpp)
VGRAPHICS_LIB:= -L/usr/lib64/
VGAME_INC:= -I../include/ -I../dependencies/x64/lua-intf/ -I../include/vcore/ -I../include/vgraphics/ -I../include/vgraphics/opengl -I../include/vgame/ $(USR_INC)
VGAME_SRC:= $(wildcard ../source/vgame/*.cpp)
VGAME_LIB:= -L/usr/lib64/
EXE_INC:= -I../include/ -I../include/vcore/ -I../include/vgraphics/ -I../include/vgraphics/opengl -I../include/vgame/ $(USR_INC) -Iinclude/
EXE_SRC:= $(wildcard src/*.cpp)
EXE_LIB:= -L/usr/lib/x86_64-linux-gnu -L/usr/local/lib -lvgame -lvgraphics -lvcore -lSDL2 -lGLEW -lGL -lGLU -llua5.2 -lfreeimage -larchive -ltinyxml2 -lassimp
LIB_OUTDIR:= /usr/local/lib/

VCORE_TARGET:= libvcore.so
VGRAPHICS_TARGET:= libvgraphics.so
VGAME_TARGET:= libvgame.so

OUT_DIR:=
EXE:= vtest

all: vcore vgraphics vgame $(EXE)

vcore:
	$(CC) $(LIB_FLAGS) $(VCORE_INC) $(VCORE_SRC) $(VCORE_LIB) -o $(LIB_OUTDIR)$(VCORE_TARGET)

vgraphics:
	$(CC) $(LIB_FLAGS) $(VGRAPHICS_INC) $(VGRAPHICS_SRC) $(VGRAPHICS_LIB) -o $(LIB_OUTDIR)$(VGRAPHICS_TARGET)

vgame:
	$(CC) $(LIB_FLAGS) $(VGAME_INC) $(VGAME_SRC) $(VGAME_LIB) -o $(LIB_OUTDIR)$(VGAME_TARGET)

$(EXE):
	$(CC) $(EXE_FLAGS) $(EXE_INC) $(EXE_SRC) $(EXE_LIB) -o $(OUT_DIR)$(EXE)

valgrind:
	valgrind --leak-check=yes --log-file="valgrind_output.txt" --track-origins=yes ./$(OUT_DIR)$(EXE)
clean:
	rm $(EXE)
