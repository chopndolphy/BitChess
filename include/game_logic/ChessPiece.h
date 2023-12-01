#pragma once
#include <vector>
#include <cstdlib>
#include "app_logic/Enums.h"
#include "app_logic/ErrorLogger.h"
#include "game_logic/ChessBoard.h"
#include "interface/ChessPieceView.h" 

class ChessPiece {
    public:
        virtual ~ChessPiece();
        void move(const Coord destination) {
            board->setPieceAt(location, destination);
            location = destination;
            movedYet = true;
        }
        virtual bool isLegalMove(Coord destination) const = 0;
        Color getColor() const {
            return color;
        }
        const Coord getLocation() const {
            return location;
        }
        bool hasDoubleMoved() const {
            return doubleMoved;
        }
        const std::string getConsoleView() const {
            return view->getConsoleDisplay();
        }
    protected:
        Coord location;
        Color color;
        bool movedYet;
        bool doubleMoved = false;
        ChessBoard* board;
        ChessPieceView* view;
        void createView(Color color, PieceType type);
};