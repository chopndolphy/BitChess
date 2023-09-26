CXX=g++
CXXFLAGS= -g -std=c++11 -pedantic -Wall -Wextra

BIN=bin
BUILD=build
DOC=doc
IDIR=include
LIB=lib
SPIKE=spike
SRC=src
TEST=test

override CXXFLAGS += $(IDIR:%=-I%)

CXX_SRCS = MachineController.cpp Product.cpp Reader.cpp ScoMachine.cpp Transaction.cpp UserInterface.cpp
OBJS = $(CXX_SRCS:%.cpp=$(BUILD)/%.o)
HEAD = $(CXX_SRCS:%.cpp=$(BUILD)/%.h)

MAIN_DEPS = $(SRC)/self_checkout.cpp $(IDIR)/MachineController.h $(IDIR)/UserInterface.h $(IDIR)/ScoMachine.h $(IDIR)/MachineState.h

main: $(BIN)/self_checkout

# Main executable
$(BIN)/self_checkout: $(OBJS) $(BUILD)/self_checkout.o | $(BIN)
	$(CXX) -o $@ $^

# Main.o
$(BUILD)/self_checkout.o: $(MAIN_DEPS) | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $(patsubst $(BUILD)/%.o,$(SRC)/%.cpp,$@) -o $@

#Test executable
$(BIN)/$(T): $(OBJS) $(BUILD)/$(T).o | $(BIN)
	$(CXX) -o $@ $^

#Test.o
$(BUILD)/$(T).o: $(TEST)/$(T).cpp $(IDIR)/MachineController.h | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $(TEST)/$(T).cpp -o $@

#Spike executable
$(SPIKE)/$(S).out: $(SPIKE)/$(S).cpp | $(BIN)
	$(CXX) -g $^ -o $@

# All .o files
$(BUILD)/%.o: $(SRC)/%.cpp $(IDIR)/%.h | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $(patsubst $(BUILD)/%.o,$(SRC)/%.cpp,$@) -o $@

# Depends on UserInterface.h
$(BUILD)/MachineController.o: $(IDIR)/UserInterface.h | $(BUILD)

# Depends on ScoMachine.h
$(BUILD)/MachineController.o: $(IDIR)/ScoMachine.h | $(BUILD)

# Depends on Transaction.h
$(BUILD)/MachineController.o $(BUILD)/UserInterface.o: $(IDIR)/Transaction.h | $(BUILD)

# Depends on Product.h
$(BUILD)/Transaction.o $(BUILD)/ScoMachine.o $(BUILD)/UserInterface.o: $(IDIR)/Product.h | $(BUILD)

# Depends on Reader.h
$(BUILD)/ScoMachine.o: $(IDIR)/Reader.h | $(BUILD)

# Depends on MachineState.h
$(BUILD)/MachineController.o $(BUILD)/ScoMachine.o: $(IDIR)/Transaction.h | $(BUILD)

$(BUILD):
	mkdir -p $(BUILD)

$(BIN):
	mkdir -p $(BIN)

.phony: clean test spike

clean:
	rm -rf $(BUILD)
	rm $(SPIKE)/*.out

test: $(BIN)/$(T)

spike: $(SPIKE)/$(S).out