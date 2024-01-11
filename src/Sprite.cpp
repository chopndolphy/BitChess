#include "Sprite.h"

Sprite::Sprite(std::weak_ptr<Shader> shader, glm::vec4 texCoords) {
    this->shader = shader;
    initRenderData(texCoords);
    model = glm::mat4(1.0f);
    this->BoardLocation = 65;
}
Sprite::Sprite(std::weak_ptr<Shader> shader, glm::vec4 texCoords, size_t boardLocation) {
    this->shader = shader;
    initRenderData(texCoords);
    model = glm::mat4(1.0f);
    this->BoardLocation = boardLocation;
}
Sprite::~Sprite() {
    glDeleteVertexArrays(1, &quadVAO);
}
void Sprite::initRenderData(glm::vec4 texCoords) {
    unsigned int VBO;
    float vertices[] = {
        // pos      // tex 
        0.0f, 1.0f, texCoords.x, texCoords.w,
        1.0f, 0.0f, texCoords.z, texCoords.y,
        0.0f, 0.0f, texCoords.x, texCoords.y,

        0.0f, 1.0f, texCoords.x, texCoords.w,
        1.0f, 1.0f, texCoords.z, texCoords.w,
        1.0f, 0.0f, texCoords.z, texCoords.y,
    };
    
    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
void Sprite::Draw(glm::mat4 projection, glm::vec2 position, glm::vec2 size) {
    shader.lock()->activate_shader();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::scale(model, glm::vec3(size, 0.0f));
    shader.lock()->setMat4("model", model);
    shader.lock()->setMat4("projection", projection);
    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
void Sprite::Move(glm::vec2 position) {
    shader.lock()->activate_shader();
    model = glm::translate(model, glm::vec3(position, 0.0f));
    shader.lock()->setMat4("model", model);
}
void Sprite::Scale(glm::vec2 size) {
    shader.lock()->activate_shader();
    model = glm::scale(model, glm::vec3(size, 1.0f));
    shader.lock()->setMat4("model", model);
}