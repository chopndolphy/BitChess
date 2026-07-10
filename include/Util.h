#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <stdexcept>
#include <filesystem>
#include <climits>
#include <cstdint>
#include <unistd.h>
#if defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

class Util {
    public:
        /** Board index (0-63) to window pixel position (top-left of square). Uses board transform matrix. */
        static glm::vec2 IndexToPosition(size_t boardIndex, const glm::mat4& boardToWindow);
        /** Window pixel position to board square index (0-63). Returns 64 if point is off the board. */
        static size_t PositionToIndex(glm::vec2 windowPos, const glm::mat4& windowToBoard);
        /** Returns true if window point is inside the 8x8 board. */
        static bool IsPointOnBoard(glm::vec2 windowPos, const glm::mat4& windowToBoard);
        static uint64_t IndexToBitBoard(size_t boardIndex);
        static bool PopulateStringBoard(std::string &stringBoard, uint64_t bitBoard, char character);
        static std::filesystem::path AbsProjectDirectory();
    private:
        Util();
};