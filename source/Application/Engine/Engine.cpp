#include "Engine.hpp"

void Engine::thread_main() {
    std::cout << "Engine thread started." << std::endl;
    P::Window().setActive(true);
    chunkShader.loadFromFile("Data/Shaders/chunk.vertex.glsl", "Data/Shaders/chunk.fragment.glsl");
    skyBox.emplace("Data/Shaders/skybox.vertex.glsl", "Data/Shaders/skybox.fragment.glsl",
                   std::vector<std::string>{
                           "Data/SkyBoxTextures/right.bmp",
                           "Data/SkyBoxTextures/left.bmp",
                           "Data/SkyBoxTextures/top.bmp",
                           "Data/SkyBoxTextures/bottom.bmp",
                           "Data/SkyBoxTextures/front.bmp",
                           "Data/SkyBoxTextures/back.bmp"
                   });
    crosshair.emplace();
    sf::Image image;
    image.loadFromFile("Data/texture.png");
    sf::Vector2u size = image.getSize();
    glGenTextures(1, &blockTexture);
    glBindTexture(GL_TEXTURE_2D, blockTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    std::cout << "Engine init complete." << std::endl;
    set_inited();
    
    while (isOn()) {
        draw();
        sendMeshes();
    }
    
    skyBox = std::nullopt;
    crosshair = std::nullopt;
    P::Window().setActive(false);
    std::cout << "Engine thread stopped." << std::endl;
}
void Engine::draw() {
    glClearColor(0.0f, 0.6f, 0.6f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 view = P::Player().getViewMatrix();
    glm::mat4 projection = P::Player().getProjectionMatrix();
    glm::mat4 vp = P::Player().getVpMatrix();
    skyBox->draw(projection * glm::mat4(glm::mat3(view)));
    sf::Shader::bind(&chunkShader);
    chunkShader.setUniform("VP", sf::Glsl::Mat4(&vp[0][0]));
    for (auto& chunk : renderChunkMap) {
        chunk.second.draw(blockTexture, P::Player().getPlayerPos(), chunkShader);
    }
    crosshair->draw();
    P::Window().display();
}
void Engine::sendMeshes() {
    EngineTask engineTask;
    while (updateQueue.try_dequeue(engineTask)) {
        RenderChunk* chunk;
        try {
            chunk = &renderChunkMap.at(engineTask.chunkPosition);
        } catch (std::out_of_range&) {
            chunk = &renderChunkMap.emplace(engineTask.chunkPosition, engineTask.chunkPosition).first->second;
        }
        chunk->update(engineTask.vertexData, engineTask.indexData);
    }
}
void Engine::start_thread() {
    Thready::start_thread(&Engine::thread_main, this);
}
void Engine::newTask(EngineTask&& engineTask) {
    updateQueue.enqueue(std::move(engineTask));
}
