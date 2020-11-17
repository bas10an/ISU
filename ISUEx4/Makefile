SRC=2_1_PAL2000_impl.cpp
OBJ=${SRC:.cpp=.o}
ELSE=2_1_PAL2000_impl.o 2_2_PAL2000_impl.o
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