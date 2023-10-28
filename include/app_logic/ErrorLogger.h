#pragma once

#include "app_logic/Enums.h"

class UserInterface;
class ErrorLogger {
    public:
        static void relayError(ErrorCode code, UserInterface* interface);
};