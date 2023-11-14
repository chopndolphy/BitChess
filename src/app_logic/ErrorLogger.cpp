#include "app_logic/ErrorLogger.h"
#include "interface/UserInterface.h"

void ErrorLogger::relayError(ErrorCode code, UserInterface* interface) {
    switch (code) {
    case ErrorCode::MOVE01:
        interface->displayError("ERROR MOVE01: Illegal move.");
        break;
    case ErrorCode::MOVE02:
        interface->displayError("ERROR MOVE02: Move would put/leave player's king in check.");
        break;
    case ErrorCode::GAME01:
        interface->displayError("ERROR GAME01: Unable to determine gamestate.");
        break;
    default:
        interface->displayError("INVALID ERROR CODE: Uknown error. Error code invalid.");
        break;
    }
}