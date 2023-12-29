#include "Sprite.h"

Sprite::Sprite(Shader &shader, glm::vec4 texCoords) {
    this->shader = shader;
    initRenderData(texCoords);
}
Sprite::~Sprite() {
    glDeleteVertexArrays(1, &this->quadVAO);
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
void Sprite::DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color) {
    this->shader.activate_shader();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));

    model = glm::translate(model, glm::vec3(0.5 * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));

    this->shader.setMat4("model", model);
    this->shader.setVec3("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}