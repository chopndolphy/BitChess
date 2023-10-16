SRC_FILES = BishopView.cpp BishopViewConsole.cpp ChessBoardView.cpp ChessBoardViewConsole.cpp ChessPieceView.cpp KingView.cpp KingViewConsole.cpp KnightView.cpp KnightViewConsole.cpp PawnView.cpp PawnViewConsole.cpp QueenView.cpp QueenViewConsole.cpp RookView.cpp RookViewConsole.cpp UserInterface.cpp UserInterfaceConsole.cpp
DIR_NAME = interface

BUILD := $(addprefix ../, $(BUILD))
IDIR  := $(addprefix ../, $(IDIR))
OBJ_FILES = $(SRC_FILES:%.cpp=$(BUILD)/%.o)
override CXXFLAGS += $(IDIR:%=-I%)

all: $(OBJ_FILES) 

$(BUILD)/%.o: %.cpp $(IDIR)/$(DIR_NAME)/%.h | $(BUILD) 
	$(CXX) $(CXXFLAGS) -c $< -o $@    