#include "World.hpp"

World::World() {
    glEnable(GL_DEPTH_TEST);
    
    shader.loadFromFile("Shaders/m.vertex.glsl", "Shaders/m.fragment.glsl");
    skyBox = std::make_unique<SkyBox>("Shaders/skybox.vertex.glsl", "Shaders/skybox.fragment.glsl",
                                      std::vector<std::string>{
                                              "SkyBoxTextures/right.bmp",
                                              "SkyBoxTextures/left.bmp",
                                              "SkyBoxTextures/top.bmp",
                                              "SkyBoxTextures/bottom.bmp",
                                              "SkyBoxTextures/front.bmp",
                                              "SkyBoxTextures/back.bmp"
                                      });
    glGenTextures(1, &blockTexture);
    glBindTexture(GL_TEXTURE_2D, blockTexture);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    sf::Image image;
    image.loadFromFile("texture.png");
    sf::Vector2u size = image.getSize();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    chunk = std::make_unique<Chunk>(sf::Vector3i());
    std::unique_ptr<Block> block = std::make_unique<Block>(1);
    chunk->placeBlock(sf::Vector3<uint8_t>(5, 5, 5), std::move(block));
    chunk->calculateVertices(chunkMap);
    chunk->sendVertices();
}
World::~World() = default;
void World::draw(Player& player) {
    glm::mat4 view = player.getViewMatrix();
    glm::mat4 projection = player.getProjectionMatrix();
    glm::mat4 vp = player.getVpMatrix();
    skyBox->draw(projection * glm::mat4(glm::mat3(view))); // TODO: need to be optimized()()
    sf::Shader::bind(&shader);
    shader.setUniform("VP", sf::Glsl::Mat4(&vp[0][0]));
    chunk->draw(blockTexture);
    sf::Shader::bind(nullptr);
}
