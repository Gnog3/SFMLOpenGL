#include "Engine.hpp"

Engine::Engine(sf::RenderWindow& window, Player& player) : window(window), player(player) {
    std::cout << "Constructing Engine..." << std::endl;
    std::cout << "Engine constructed." << std::endl;
}
void Engine::thread_main() {
    std::cout << "Engine thread started." << std::endl;
    window.setActive(true);
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
    inited = true;
    inited_cond.notify_all();
    std::cout << "Engine init complete." << std::endl;
    
    while (!stopRequire) {
        draw();
        sendMeshes();
    }
    
    
    skyBox = std::nullopt;
    crosshair = std::nullopt;
    window.setActive(false);
    std::cout << "Engine thread stopped." << std::endl;
}
void Engine::draw() {
    glClearColor(0.0f, 0.6f, 0.6f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 view = player.getViewMatrix();
    glm::mat4 projection = player.getProjectionMatrix();
    glm::mat4 vp = player.getVpMatrix();
    skyBox->draw(projection * glm::mat4(glm::mat3(view)));
    sf::Shader::bind(&chunkShader);
    chunkShader.setUniform("VP", sf::Glsl::Mat4(&vp[0][0]));
    for (auto& chunk : renderChunkMap) {
        chunk.second.draw(blockTexture, player.getPlayerPos(), chunkShader);
    }
    crosshair->draw();
    window.display();
}
void Engine::sendMeshes() {
    EngineTask engineTask;
    if (updateQueue.try_dequeue(engineTask)) {
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
    thread.emplace(&Engine::thread_main, this);
}
void Engine::requireStop() {
    stopRequire = true;
}
void Engine::waitStop() {
    requireStop();
    if (thread) {
        thread->join();
    }
}
void Engine::waitInit() {
    std::unique_lock<std::mutex> lock(inited_mutex);
    while (!inited) {
        inited_cond.wait(lock);
    }
}
void Engine::newTask(EngineTask&& engineTask) {
    updateQueue.enqueue(std::move(engineTask));
}
