SRC=vector_main.cpp
OBJ=${SRC:.cpp=.o}
ELSE=thread3_1.o vector_main.o
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