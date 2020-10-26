SRC=threadEx5.cpp
OBJ=${SRC:.cpp=.o}
ELSE=threadEx2.o threadEx3.o threadEx4.o threadEx5.o
EXE=exec
CXX=g++ -std=c++11 -pthread
CXXFLAG=-I.

all: $(OBJ)
	@$(CXX) -o $(EXE) $^

%.o: %.cpp Vector.hpp
	@$(CXX) -c $< $(CXXFLAG)

.PHONY: clean
clean:
	@rm $(OBJ) $(EXE) $(ELSE)