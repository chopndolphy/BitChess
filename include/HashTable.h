#pragma once
#include <array>
#include <stdint.h>

struct HashTable {
    std::array<std::array<uint64_t, 14>, 64> SquaresPieces;
    uint64_t WhitesTurn;
    uint64_t CastleBQ;
    uint64_t CastleBK;
    uint64_t CastleWQ;
    uint64_t CastleWK;
};