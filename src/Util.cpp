#include "Util.h"

glm::vec2 Util::IndexToPosition(size_t boardIndex, glm::vec2 squareSize, glm::vec2 boardOffset) { // calculates screen coordinate for a board position based on index
    float posX = (boardOffset.x + (squareSize.x * (static_cast<float>(boardIndex % 8))));
    float posY = (boardOffset.y + (squareSize.y * (glm::floor(static_cast<float>(boardIndex / 8)))));
    return glm::vec2(posX, posY);
}
size_t Util::PositionToIndex(glm::vec2 screenPos, glm::vec2 squareSize, glm::vec2 boardOffset) { // returns a bitboard with a 1 located at the screenPos input
    return static_cast<size_t>(glm::floor((screenPos.x - boardOffset.x) / squareSize.x) + 
                     (8 * glm::floor((screenPos.y - boardOffset.y)/ squareSize.y)));
}
uint64_t Util::IndexToBitBoard(size_t boardIndex) {
    uint64_t bitBoard = 0x8000000000000000;
    bitBoard >>= boardIndex;
    return bitBoard;
}
bool Util::PopulateStringBoard(std::string &stringBoard, uint64_t bitBoard, char character) {
    if (stringBoard.size() != 64) {
        throw std::runtime_error("String Board is not precisely 64 characters long");
        return false;
    } else {
        uint64_t biterator = 0x8000000000000000;
        for (size_t i = 0; i < 64; i++) {
            if (biterator & bitBoard) {
                stringBoard.at(i) = character;
            }
            biterator >>= 1;
        }
        return true;
    }
}
std::filesystem::path Util::AbsProjectDirectory() {
    char path[FILENAME_MAX];
    ssize_t count = readlink("/proc/self/exe", path, FILENAME_MAX);
    return std::filesystem::path(std::string(path, (count > 0) ? count : 0)).parent_path().parent_path().string();
}
