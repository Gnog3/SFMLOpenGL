#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"
#pragma once

#include <memory>
#include <tuple>
#include <optional>
#include <queue>
#include <SFML/Graphics.hpp>
#include <glm.hpp>
#include <GL/glew.h>
#include "Chunk/Chunk.hpp"
#include "ChunkMap.hpp"
#include "Crosshair/Crosshair.hpp"
#include "../Engine/Engine.hpp"
#include <blockingconcurrentqueue.h>

struct RayCastResult {
    sf::Vector3<double> end;
    sf::Vector3<int64_t> iend;
    sf::Vector3f norm;
    bool isFound = false;
};
enum class WorldTaskType {
    SingleBlockPlace,
    SingleBlockRemove,
    ChunkUpdate,
    WorldThreadStop
};
struct WorldTask {
    WorldTaskType type;
    sf::Vector3<int64_t> position;
    WorldTask() = default;
    WorldTask(WorldTask&& other) noexcept {
        type = other.type;
        position = other.position;
    }
    WorldTask& operator=(const WorldTask& other) noexcept {
        type = other.type;
        position = other.position;
        return *this;
    }
};

class Client;

class World {
    private:
        ChunkMap chunkMap;
        Engine& engine;
        std::optional<std::thread> thread;
        volatile bool stopRequire = false;
        BlockingConcurrentQueue<WorldTask> externalQueue;
        Block* getBlock(sf::Vector3<int64_t> position);
        void placeBlockSendData(uint8_t id, sf::Vector3<int64_t> position);
        void removeBlockSendData(sf::Vector3<int64_t> position);
        void thread_main();
    public:
        explicit World(Engine& engine);
        ~World();
        RayCastResult rayCast(sf::Vector3<double> position, sf::Vector3f direction, float maxDist);
        void start_thread();
        void requireStop();
        void waitStop();
        void newTask(WorldTask&& worldTask);
        void oneBlock(WorldTaskType worldTaskType, sf::Vector3<int64_t> position);
};

#pragma clang diagnostic pop