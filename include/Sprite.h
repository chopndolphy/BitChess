#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Texture2D.h"

#include <memory>
class Sprite {
    public:
        Sprite(std::weak_ptr<Shader> shader, glm::vec4 texCoords);
        Sprite(std::weak_ptr<Shader> shader, glm::vec4 texCoords, size_t boardLocation);
        ~Sprite();
        void Draw(glm::mat4 projection, glm::vec2 position, glm::vec2 size);
        void Move(glm::vec2 position);
        void Scale(glm::vec2 size);
        size_t BoardLocation;
        void setHovering(bool hovering) {
            shader.lock()->activate_shader();
            shader.lock()->setBool("hoverOver", hovering);
        }
    private:
        std::weak_ptr<Shader> shader;
        unsigned int quadVAO;
        void initRenderData(glm::vec4 texCoords);
        glm::mat4 model;
};