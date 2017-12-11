CXX:=clang++
CXXFLAGS:=-std=c++14 -Wall -Wextra -Werror -O3 -I.
LDFLAGS:=`simple2d --libs` -lpthread -lpython2.7

OBJ:=main.o
DEP:=

all : RoboTutor

RoboTutor : $(OBJ)
	$(CXX) $(OBJ) -o RoboTutor $(LDFLAGS)

%.o : %.cpp $(DEP)
	$(CXX) -c $< -o $@ $(CXXFLAGS)
