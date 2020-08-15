#include "World.hpp"

World::World() {
    glEnable(GL_DEPTH_TEST);
    
    shader.loadFromFile("Shaders/m.vertex.glsl", "Shaders/m.fragment.glsl");
    skyBox = std::make_unique<SkyBox>("Shaders/skybox.vertex.glsl", "Shaders/skybox.fragment.glsl", std::vector<std::string>{
            "SkyBoxTextures/right.bmp",
            "SkyBoxTextures/left.bmp",
            "SkyBoxTextures/top.bmp",
            "SkyBoxTextures/bottom.bmp",
            "SkyBoxTextures/front.bmp",
            "SkyBoxTextures/back.bmp"
    });
}
World::~World() = default;
void World::draw(Player& player) {
    glm::mat4 view = player.getViewMatrix();
    glm::mat4 projection = player.getProjectionMatrix();
    glm::mat4 vp = player.getVpMatrix();
    skyBox->draw(projection * glm::mat4(glm::mat3(view))); // TODO: need to be optimized()()
    sf::Shader::bind(&shader);
    shader.setUniform("VP", sf::Glsl::Mat4(&vp[0][0]));
    sf::Shader::bind(nullptr);
}
