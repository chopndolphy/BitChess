#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Texture2D.h"

class Sprite {
    public:
        Sprite(Shader &shader);
        ~Sprite();
        void DrawSprite(Texture2D &texure, glm::vec2 position, 
            glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, 
            glm::vec3 color = glm::vec3(1.0f));
    private:
        Shader shader;
        unsigned int quadVAO;
        void initRenderData();
};