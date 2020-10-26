SOURCES=threadEx6.cpp
OBJECTS=$(addprefix $(BUILD_DIR)/, $(SOURCES:.cpp=.o))
DEPS=$(addprefix $(BUILD_DIR)/, $(SOURCES:.cpp=.d))
EXE=prog
CXXFLAGS=-I.
ARCH=target

ifeq (${ARCH},host)
CXX=g++ -std=c++11 -pthread
BUILD_DIR=build/host
BIN_DIR=bin/host
endif

ifeq (${ARCH},target)
CXX=arm-rpizw-g++ -std=c++11 -pthread
BUILD_DIR=build/target
BIN_DIR=bin/target
endif



$(addprefix $(BIN_DIR)/, $(EXE)): $(DEPS) $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

$(addprefix $(BUILD_DIR)/, %.o): %.cpp
	@echo $@ $^
	${CXX} -c -o $@ $^ ${CXXFLAGS}

$(addprefix $(BUILD_DIR)/, %.d): %.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) -MT$@ -MM $(CXXFLAGS) $< > $@
	$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $^ >> $@


clean:
	@rm -f $(BIN_DIR)/$(EXE) $(OBJECTS) $(DEPS)

ifneq ($(filter-out clean format tidy,$(MAKECMDGOALS)),)
-include $(DEPS)
endif