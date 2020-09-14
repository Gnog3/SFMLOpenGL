#include "Engine.hpp"

Engine::Engine() {
    chunkShader.loadFromFile("Data/Shaders/chunk.vertex.glsl", "Data/Shaders/chunk.fragment.glsl");
    skyBox = std::make_unique<SkyBox>("Data/Shaders/skybox.vertex.glsl", "Data/Shaders/skybox.fragment.glsl",
                                      std::vector<std::string>{
                                              "Data/SkyBoxTextures/right.bmp",
                                              "Data/SkyBoxTextures/left.bmp",
                                              "Data/SkyBoxTextures/top.bmp",
                                              "Data/SkyBoxTextures/bottom.bmp",
                                              "Data/SkyBoxTextures/front.bmp",
                                              "Data/SkyBoxTextures/back.bmp"
                                      });
    sf::Image image;
    image.loadFromFile("Data/texture.png");
    sf::Vector2u size = image.getSize();
    glGenTextures(1, &blockTexture);
    glBindTexture(GL_TEXTURE_2D, blockTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}
void Engine::thread_main() {
    while (!stopRequire) {
        draw();
        sendMeshes();
    }
}
void Engine::draw() {

}
void Engine::sendMeshes() {

}
void Engine::start_thread() {
    thread = std::make_unique<std::thread>(&Engine::thread_main, this);
}
