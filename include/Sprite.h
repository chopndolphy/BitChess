#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Texture2D.h"

#include <memory>
class Sprite {
    public:
        Sprite(std::weak_ptr<Shader> shader, glm::vec4 texCoords, glm::vec2 position, glm::vec2 size);
        ~Sprite();
        void Draw();
        void Move(glm::vec2 position);
    private:
        std::weak_ptr<Shader> shader;
        unsigned int quadVAO;
        void initRenderData(glm::vec4 texCoords);
        glm::mat4 model;
};