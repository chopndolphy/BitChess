#pragma once
#include "UserInterface.h"
#include "Enums.h"

class ErrorLogger {
    public:
        static void relayError(ErrorCode code, UserInterface* interface);
};