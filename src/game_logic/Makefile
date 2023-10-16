SRC_FILES = Bishop.cpp ChessBoard.cpp ChessPiece.cpp GamePlay.cpp King.cpp Knight.cpp Pawn.cpp Player.cpp Queen.cpp Rook.cpp
DIR_NAME = game_logic

BUILD := $(addprefix ../, $(BUILD))
IDIR  := $(addprefix ../, $(IDIR))
OBJ_FILES = $(SRC_FILES:%.cpp=$(BUILD)/%.o)
override CXXFLAGS += $(IDIR:%=-I%)

all: $(OBJ_FILES) 

$(BUILD)/%.o: %.cpp $(IDIR)/$(DIR_NAME)/%.h | $(BUILD) 
	$(CXX) $(CXXFLAGS) -c $< -o $@    