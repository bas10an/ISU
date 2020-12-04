SRC=main.cpp MsgQueue.cpp Message.cpp
OBJ=${SRC:.cpp=.o}
DEPS=MsgQueue.hpp Message.hpp mutex.hpp
ELSE=
EXE=exec
CXX=g++ -std=c++11 -pthread
CXXFLAG=-I.

all: $(OBJ)
	$(CXX) -o $(EXE) $^

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAG)

.PHONY: clean
clean:
	rm $(OBJ) $(EXE) $(ELSE)