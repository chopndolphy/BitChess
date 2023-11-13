SRC_FILES = ErrorLogger.cpp Coord.cpp
DIR_NAME = app_logic

BUILD := $(addprefix ../, $(BUILD))
IDIR  := $(addprefix ../, $(IDIR))
OBJ_FILES = $(SRC_FILES:%.cpp=$(BUILD)/%.o)
override CXXFLAGS += $(IDIR:%=-I%)

all: $(OBJ_FILES) 

$(BUILD)/%.o: %.cpp $(IDIR)/$(DIR_NAME)/%.h | $(BUILD) 
	$(CXX) $(CXXFLAGS) -c $< -o $@    