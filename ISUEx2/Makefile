SRC=threadEx4.cpp
OBJ=${SRC:.cpp=.o}
ELSE=threadEx2.o threadEx3.o
EXE=exec
CXX=g++ -std=c++11 -pthread
CXXFLAG=-I.

all: $(OBJ)
	@$(CXX) -o $(EXE) $^

%.o: %.cpp
	@$(CXX) -c $< $(CXXFLAG)

.PHONY: clean
clean:
	@rm $(OBJ) $(EXE) $(ELSE)