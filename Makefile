CXX:=clang++
CXXFLAGS:=-std=c++14 -Wall -Wextra -Werror -I. -g
LDFLAGS:=`simple2d --libs` -lpthread -lpython2.7 -L. -g

OBJ:=main.o BoardGraphics.o pyWrap.o Interfacing.o
DEP:=BoardGraphics.hpp pyWrap.hpp ReadBoard.hpp SpeechSynthesis.hpp Interfacing.hpp

ENGINEOBJ:=GameEngine/ai.o GameEngine/game_engine.o GameEngine/structs.o GameEngine/debug_output.o GameEngine/game_interface.o GameEngine/user_io.o
ENGINEDEP:=GameEngine/ai.hpp GameEngine/game_engine.hpp GameEngine/user_io.hpp GameEngine/debug_output.hpp GameEngine/game_interface.hpp GameEngine/enum.hpp GameEngine/structs.hpp

.PHONY: all clean

all : RoboTutor

clean :
	rm -f RoboTutor libGameEngine.a *.o *.pyc GameEngine/*.o

RoboTutor : $(OBJ) libGameEngine.a
	$(CXX) $(OBJ) -o RoboTutor $(LDFLAGS) -lGameEngine

%.o : %.cpp $(DEP) $(ENGINEDEP)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

libGameEngine.a : $(ENGINEOBJ) 
	ar rvs libGameEngine.a $(ENGINEOBJ)
