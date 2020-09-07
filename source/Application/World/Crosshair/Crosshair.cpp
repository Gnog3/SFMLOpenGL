#include "Crosshair.hpp"

Crosshair::Crosshair() {
    shader.loadFromFile("Data/Shaders/line.vertex.glsl", "Data/Shaders/line.fragment.glsl");
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) nullptr);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
void Crosshair::draw() const {
    sf::Shader::bind(&shader);
    glBindVertexArray(vaoId);
    glDrawArrays(GL_LINES, 0, 4);
    glBindVertexArray(0);
    sf::Shader::bind(nullptr);
}
