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
#include "../GlobalRef.hpp"
#include "../Thready.hpp"
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
// Requires nothing for construction
// Requires window and player for thread
class Engine : public Thready {
    private:
        sf::Shader chunkShader;
        std::optional<SkyBox> skyBox;
        std::optional<Crosshair> crosshair;
        ReaderWriterQueue<EngineTask> updateQueue;
        RenderChunkMap renderChunkMap;
        uint32_t blockTexture = 0;
        void thread_main();
        void draw();
        void sendMeshes();
    public:
        void start_thread();
        void newTask(EngineTask&& engineTask);
};
