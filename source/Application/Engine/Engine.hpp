#pragma once

#include <thread>
#include <optional>
#include <condition_variable>
#include <mutex>
#include <SFML/Graphics.hpp>
#include "../World/SkyBox/SkyBox.hpp"
#include "../World/Crosshair/Crosshair.hpp"
#include "../Player/Player.hpp"
#include "RenderChunkMap.hpp"
#include "readerwriterqueue.h"
#include "../World/Chunk/Chunk.hpp"

using namespace moodycamel;

struct EngineTask {
    sf::Vector3<int64_t> chunkPosition;
    std::vector<PlaneVertex> vertexData;
    std::vector<uint32_t> indexData;
    EngineTask() = default;
    EngineTask(EngineTask&& other) noexcept {
        chunkPosition = other.chunkPosition;
        vertexData = std::move(other.vertexData);
        indexData = std::move(other.indexData);
    }
    EngineTask& operator=(const EngineTask& other) = default;
};

class Engine {
    private:
        sf::RenderWindow& window;
        Player& player;
        sf::Shader chunkShader;
        std::optional<SkyBox> skyBox;
        std::optional<std::thread> thread;
        std::optional<Crosshair> crosshair;
        std::mutex inited_mutex;
        std::condition_variable inited_cond;
        ReaderWriterQueue<EngineTask> updateQueue;
        RenderChunkMap renderChunkMap;
        uint32_t blockTexture = 0;
        volatile bool stopRequire = false;
        volatile bool inited = false;
        void thread_main();
        void draw();
        void sendMeshes();
    public:
        Engine(sf::RenderWindow& window, Player& player);
        void start_thread();
        void requireStop();
        void waitStop();
        void waitInit();
        void newTask(EngineTask&& engineTask);
};
