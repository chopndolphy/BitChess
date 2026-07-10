#include "Util.h"

glm::vec2 Util::IndexToPosition(size_t boardIndex, const glm::mat4& boardToWindow) {
    float col = static_cast<float>(boardIndex % 8);
    float row = glm::floor(static_cast<float>(boardIndex) / 8.0f);
    glm::vec4 boardPos(col, row, 0.0f, 1.0f);
    glm::vec4 windowPos = boardToWindow * boardPos;
    return glm::vec2(windowPos.x, windowPos.y);
}

size_t Util::PositionToIndex(glm::vec2 windowPos, const glm::mat4& windowToBoard) {
    glm::vec4 p(windowPos.x, windowPos.y, 0.0f, 1.0f);
    glm::vec4 boardPos = windowToBoard * p;
    float bx = boardPos.x;
    float by = boardPos.y;
    if (bx < 0.0f || bx >= 8.0f || by < 0.0f || by >= 8.0f)
        return 64u;
    int col = static_cast<int>(glm::floor(bx));
    int row = static_cast<int>(glm::floor(by));
    if (col < 0 || col >= 8 || row < 0 || row >= 8)
        return 64u;
    return static_cast<size_t>(col + row * 8);
}

bool Util::IsPointOnBoard(glm::vec2 windowPos, const glm::mat4& windowToBoard) {
    glm::vec4 p(windowPos.x, windowPos.y, 0.0f, 1.0f);
    glm::vec4 boardPos = windowToBoard * p;
    float bx = boardPos.x;
    float by = boardPos.y;
    return bx >= 0.0f && bx < 8.0f && by >= 0.0f && by < 8.0f;
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
    // Resolve the running executable's path (platform specific), then walk up
    // one directory: the binary lives in <project>/build/, resources in
    // <project>/shaders and <project>/textures.
    std::filesystem::path exePath;
#if defined(__APPLE__)
    char buffer[PATH_MAX];
    uint32_t size = sizeof(buffer);
    if (_NSGetExecutablePath(buffer, &size) == 0) {
        exePath = std::filesystem::canonical(buffer);
    }
#elif defined(__linux__)
    char buffer[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", buffer, PATH_MAX);
    if (count > 0) {
        exePath = std::filesystem::path(std::string(buffer, count));
    }
#endif
    return exePath.parent_path().parent_path();
}
