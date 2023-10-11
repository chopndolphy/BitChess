#include "ErrorLogger.h"

void ErrorLogger::relayError(ErrorCode code, UserInterface* interface) {
    switch (code) {
    case MOVE01:
        interface->displayError("ERROR MOVE01: Illegal move.");
        break;
    case MOVE02:
        interface->displayError("ERROR MOVE02: Move would put/leave player's king in check.");
        break;
    case GAME01:
        interface->displayError("ERROR GAME01: Unable to determine gamestate.");
        break;
    default:
        interface->displayError("INVALID ERROR CODE: Uknown error. Error code invalid.");
        break;
    }
}