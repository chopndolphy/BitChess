#include "ErrorLogger.h"
void ErrorLogger::relayError(ErrorCode code, Player* player, UserInterface* interface) {
    switch (code) {
    case MOV01:
        interface->displayError("ERROR MOV01: Illegal Move");
        break;
    
    default:
        break;
    }
}