#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <stdexcept>
#include <filesystem>
#include <unistd.h>

class Util {
    public:
        static glm::vec2 IndexToPosition(size_t boardIndex, glm::vec2 squareSize, glm::vec2 boardOffset);
        static size_t PositionToIndex(glm::vec2 screenPos, glm::vec2 squareSize, glm::vec2 boardOffset);
        static uint64_t IndexToBitBoard(size_t boardIndex);
        static bool PopulateStringBoard(std::string &stringBoard, uint64_t bitBoard, char character);
        static std::filesystem::path AbsProjectDirectory();
    private:
        Util();
};