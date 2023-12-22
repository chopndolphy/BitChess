# compiler and flags
export CXX=g++
export CXXFLAGS = -std=c++17 -O2 -g -Wall -Wextra -pedantic

BIN=bin
BASEBUILD=build
BASEIDIR=include
TEST=test

export IDIR=../$(BASEIDIR)
export BUILD=../$(BASEBUILD)
export SRC=src

# := is needed to avoid a recursive expansion
#https://stackoverflow.com/questions/1605623/how-can-i-affect-path-in-a-makefile-variable-why-is-my-example-not-working
libraries := app_logic game_logic interface
libraries := $(addprefix src/, $(libraries))

target := chess_game
target := $(addprefix bin/, $(target))

testtargets := coord_test board_test
testtargets := $(addprefix bin/, $(testtargets))

all: $(target)

$(target): $(libraries) | $(BASEBUILD)
	@echo "Compiling $(target)"
	$(CXX) $(CXXFLAGS) $(BASEIDIR:%=-I%) -o $@ $(patsubst $(BIN)/%, $(SRC)/%.cpp, $@) $(BASEBUILD)/*.o

$(testtargets): $(libraries) | $(BASEBUILD)
	@echo "Compiling $@"
	$(CXX) $(CXXFLAGS) $(BASEIDIR:%=-I%) -o $@ $(TEST)/$(notdir $@)/$(notdir $@).cpp $(BASEBUILD)/*.o
	@./$@ < $(TEST)/$(notdir $@)/input.txt $@ > $(TEST)/$(notdir $@)/output.txt
	@diff $(TEST)/$(notdir $@)/expected.txt $(TEST)/$(notdir $@)/output.txt
	@> $(TEST)/$(notdir $@)/output.txt
	@echo "$@ successful"

$(libraries): | $(BASEBUILD) 
	$(MAKE) -C $@

clean:
	rm -rf $(BASEBUILD)

test: $(testtargets)
	@echo "All tests successful"

run: $(target)
	@echo "Running program"
	@./bin/chess_game

maketest:
	@./scripts/make_test.sh $(N)

.PHONY: all clean test run maketest $(libraries)

$(BASEBUILD):
	mkdir -p $(BASEBUILD)