#include "World.hpp"

World::World() {
    glEnable(GL_DEPTH_TEST);
    
    shader.loadFromFile("Shaders/m.vertex.glsl", "Shaders/m.fragment.glsl");
    lightBoxShader.loadFromFile("Shaders/lightbox.vertex.glsl", "Shaders/lightbox.fragment.glsl");
    skyBox.emplace("Shaders/skybox.vertex.glsl", "Shaders/skybox.fragment.glsl", std::vector<std::string>{
            "SkyBoxTextures/right.bmp",
            "SkyBoxTextures/left.bmp",
            "SkyBoxTextures/top.bmp",
            "SkyBoxTextures/bottom.bmp",
            "SkyBoxTextures/front.bmp",
            "SkyBoxTextures/back.bmp"
    });
    OpenGLModel model;
    model.addCollider(
            glm::vec3(-1.0, 1.0, 1.0),
            glm::vec3(1.0, 1.0, 1.0),
            glm::vec3(1.0, -1.0, 1.0),
            glm::vec3(-1.0, -1.0, 1.0),
            glm::vec3(-1.0, 1.0, -1.0),
            glm::vec3(1.0, 1.0, -1.0),
            glm::vec3(1.0, -1.0, -1.0),
            glm::vec3(-1.0, -1.0, -1.0),
            glm::vec3(1.0, 1.0, 1.0),
            glm::vec3(0, 0, 1.0),
            glm::vec3(0, 0, -1.0),
            glm::vec3(-1.0, 0, 0),
            glm::vec3(1.0, 0, 0),
            glm::vec3(0, 1.0, 0),
            glm::vec3(0, -1.0, 0)
    );
    glGenVertexArrays(1, &vaoid);
    glBindVertexArray(vaoid);
    modelVBO.create(GL_ARRAY_BUFFER, GL_STATIC_DRAW, model.size());
    modelVBO.bind();
    modelVBO.fill(0, model.link());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) (3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) (6 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
World::~World() {
    glDeleteVertexArrays(1, &vaoid);
}
void World::draw(Player& player) {
    glm::mat4 view = player.getViewMatrix();
    glm::mat4 projection = player.getProjectionMatrix();
    glm::mat4 vp = player.getVpMatrix();
    skyBox->draw(projection * glm::mat4(glm::mat3(view))); // TODO: need to be optimized()()
    sf::Shader::bind(&shader);
    shader.setUniform("VP", sf::Glsl::Mat4(&vp[0][0]));
    glBindVertexArray(vaoid);
    glDrawArrays(GL_TRIANGLES, 0, 6000);
    glBindVertexArray(0);
    sf::Shader::bind(nullptr);
}
