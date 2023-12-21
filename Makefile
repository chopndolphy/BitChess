# compiler and flags
export CXX=g++
export CXXFLAGS = -std=c++17 -O2 -g -Wall -Wextra -pedantic

BIN=bin
BASEBUILD=build
BASEIDIR=include
export IDIR=../$(BASEIDIR)
export BUILD=../$(BASEBUILD)
export SRC=src

# := is needed to avoid a recursive expansion
#https://stackoverflow.com/questions/1605623/how-can-i-affect-path-in-a-makefile-variable-why-is-my-example-not-working
libraries := app_logic game_logic interface
libraries := $(addprefix src/, $(libraries))

target := chess_game chess_game_test
target := $(addprefix bin/, $(target))

all: $(target)

$(target): $(libraries) | $(BASEBUILD)
	@echo "Compiling $(target)"
	$(CXX) $(CXXFLAGS) $(BASEIDIR:%=-I%) -o $@ $(patsubst $(BIN)/%, $(SRC)/%.cpp, $@) $(BASEBUILD)/*.o 

$(libraries): | $(BASEBUILD) 
	$(MAKE) -C $@

clean:
	rm -rf $(BASEBUILD)

test: $(target)
	@echo "Running test"
	@./bin/chess_game_test 	

run: $(target)
	@echo "Running program"
	@./bin/chess_game

.PHONY: all clean test run $(libraries)

$(BASEBUILD):
	mkdir -p $(BASEBUILD)