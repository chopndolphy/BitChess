# Directories
SRC = src
BUILD = build
INCLUDE = include
LIB = lib

ALL_INCLUDES = -I./$(LIB) -I$(GLAD_INC) -I./$(INCLUDE) -I./$(STB_IMAGE) -I./$(GLM)
GLAD = ./$(LIB)/glad
GLAD_INC = $(GLAD)/include
STB_IMAGE = $(LIB)/stb_image
GLM = $(LIB)/glm

# Compiler and flags
CC = gcc
CXX = g++
CFLAGS = -Wall -O2 -g $(ALL_INCLUDES)
# CFLAGS = -Wall -ggdb -O3 $(INCLUDES)
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -pedantic -g -O2 -D_GLIBCXX_DEBUG $(ALL_INCLUDES)
# CXXFLAGS = -Wall -ggdb -O3 $(INCLUDES)
LDFLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

# SHARED OBJECTS AND TARGETS  (Targets are executables)

# Shared objects by multiple executables
CPP_FILES := Shader.cpp Renderer2D.cpp Sprite.cpp Game.cpp MyGlWindow.cpp Texture2D.cpp ResourceManager.cpp Board.cpp Util.cpp BlackSelectingMoveState.cpp BlackSelectingPieceState.cpp WhiteSelectingMoveState.cpp WhiteSelectingPieceState.cpp
OBJECTS := $(CPP_FILES:.cpp=.o) glad.o flecs.o stb_image.o
OBJECTS := $(addprefix $(BUILD)/, $(OBJECTS))

# Targets
CPP_EXEC := chess.cpp
TARGETS_OBJ := $(CPP_EXEC:%.cpp=$(BUILD)/%.o)
TARGETS := $(TARGETS_OBJ:%.o=%)

# RECIPES
all: $(TARGETS)

# executables depend on shared objects
$(TARGETS): $(OBJECTS) 

# Link
# Secondary expansions allow to use the automatic variable $@ in the prerequisites list.
# https://www.gnu.org/software/make/manual/html_node/Secondary-Expansion.html
.SECONDEXPANSION:
$(TARGETS): $(OBJECTS) $$@.o 
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compile objects
# Order of recipes matter. Recipe 2 has to be before recipe 3 to take into account .h prerrequisites. 

# recipe 1: Complie glad
$(BUILD)/glad.o: $(GLAD)/src/glad.c $(GLAD)/include/glad/glad.h | $(BUILD)
	$(CC) -c $(CFLAGS) -o $@ $< 

#stb_image:
$(BUILD)/stb_image.o: $(STB_IMAGE)/stb_image.cpp $(STB_IMAGE)/stb_image.h | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# recipe 2: compile objects - cpp files with header files
$(BUILD)/%.o: $(SRC)/%.cpp $(INCLUDE)/%.h | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

# recipe 3: compile executables - cpp files without header files
$(BUILD)/%.o: $(SRC)/%.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@    

# PHONY
.PHONY : all clean run

clean :
	rm -rf $(BUILD)

run: $(TARGETS)
	./$(BUILD)/chess

$(BUILD):
	mkdir -p $(BUILD)