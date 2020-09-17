#include "World.hpp"

Block* World::getBlock(sf::Vector3<int64_t> position) {
    sf::Vector3i chunk = Chunk::getChunk(position) * 16;
    auto chunkSearch = chunkMap.find(sf::Vector3<int64_t>(chunk));
    if (chunkSearch != chunkMap.end()) {
        Chunk& chunkRef = chunkSearch->second;
        return chunkRef.getBlock(Block::getPositionChunkRel(position));
    }
    return nullptr;
}
void World::placeBlockSendData(uint8_t id, sf::Vector3<int64_t> position) {
    //sf::Vector3i chunkPosition = Chunk::getChunk(position);
    Chunk* chunk;
    sf::Vector3<int64_t> offsetPosition = (sf::Vector3<int64_t>) Chunk::getChunk(position) * 16ll;
    try {
        chunk = &chunkMap.at(offsetPosition);
    } catch (std::out_of_range&) {
        chunk = &chunkMap.emplace(sf::Vector3i(offsetPosition), sf::Vector3i(offsetPosition)).first->second;
    }
    sf::Vector3<uint8_t> blockPositionChunkRel = Block::getPositionChunkRel(position);
    chunk->placeBlock(blockPositionChunkRel, id);
    ChunkVertexData chunkVertexData = chunk->calculateVertices(chunkMap);
    EngineTask engineTask;
    engineTask.chunkPosition = offsetPosition;
    engineTask.vertexData = std::move(chunkVertexData.vertexData);
    engineTask.indexData = std::move(chunkVertexData.indexData);
    engine.newTask(std::move(engineTask));
}
void World::removeBlockSendData(sf::Vector3<int64_t> position) {
    Chunk* chunk;
    sf::Vector3<int64_t> offsetPosition = (sf::Vector3<int64_t>) Chunk::getChunk(position) * 16ll;
    try {
        chunk = &chunkMap.at(offsetPosition);
    } catch (std::out_of_range&) {
        chunk = &chunkMap.emplace(sf::Vector3i(offsetPosition), sf::Vector3i(offsetPosition)).first->second;
    }
    sf::Vector3<uint8_t> blockPositionChunkRel = Block::getPositionChunkRel(position);
    chunk->removeBlock(blockPositionChunkRel);
    ChunkVertexData chunkVertexData = chunk->calculateVertices(chunkMap);
    EngineTask engineTask;
    engineTask.chunkPosition = offsetPosition;
    engineTask.vertexData = std::move(chunkVertexData.vertexData);
    engineTask.indexData = std::move(chunkVertexData.indexData);
    engine.newTask(std::move(engineTask));
}
void World::thread_main() {
    std::cout << "World thread started." << std::endl;
    while (!stopRequire) {
        WorldTask worldTask;
        externalQueue.wait_dequeue(worldTask);
        if (stopRequire) break;
        if (worldTask.type == WorldTaskType::SingleBlockPlace) {
            placeBlockSendData(1, worldTask.position);
        } else if (worldTask.type == WorldTaskType::SingleBlockRemove) {
            removeBlockSendData(worldTask.position);
        }
    }
    std::cout << "World thread stopped." << std::endl;
}
RayCastResult World::rayCast(sf::Vector3<double> position, sf::Vector3f direction, float maxDist) {
    RayCastResult ret{};
    float t = 0.0f;
    sf::Vector3<int64_t> i(
            floor(position.x),
            floor(position.y),
            floor(position.z)
    );
    sf::Vector3f step(
            (direction.x > 0.0f) ? 1.0f : -1.0f,
            (direction.y > 0.0f) ? 1.0f : -1.0f,
            (direction.z > 0.0f) ? 1.0f : -1.0f
    );
    constexpr double infinity = std::numeric_limits<double>::infinity();
    
    sf::Vector3<double> tDelta(
            (direction.x == 0.0f) ? infinity : abs(1.0f / direction.x),
            (direction.y == 0.0f) ? infinity : abs(1.0f / direction.y),
            (direction.z == 0.0f) ? infinity : abs(1.0f / direction.z)
    );
    
    sf::Vector3<double> dist(
            (step.x > 0) ? ((double) i.x + 1 - position.x) : (position.x - i.x),
            (step.y > 0) ? ((double) i.y + 1 - position.y) : (position.y - i.y),
            (step.z > 0) ? ((double) i.z + 1 - position.z) : (position.z - i.z)
    );
    
    sf::Vector3<double> tMax(
            (tDelta.x < infinity) ? tDelta.x * dist.x : infinity,
            (tDelta.y < infinity) ? tDelta.y * dist.y : infinity,
            (tDelta.z < infinity) ? tDelta.z * dist.z : infinity
    );
    
    int steppedIndex = -1;
    
    while (t < maxDist) {
        if (getBlock(i) != nullptr) {
            ret.end = position + (sf::Vector3<double>) (t * direction);
            ret.iend = i;
            ret.norm = sf::Vector3f();
            ret.isFound = true;
            if (steppedIndex == 0) ret.norm.x = -step.x;
            if (steppedIndex == 1) ret.norm.y = -step.y;
            if (steppedIndex == 2) ret.norm.z = -step.z;
            return ret;
        }
        if (tMax.x < tMax.y) {
            if (tMax.x < tMax.z) {
                i.x += step.x;
                t = tMax.x;
                tMax.x += tDelta.x;
                steppedIndex = 0;
            } else {
                i.z += step.z;
                t = tMax.z;
                tMax.z += tDelta.z;
                steppedIndex = 2;
            }
        } else {
            if (tMax.y < tMax.z) {
                i.y += step.y;
                t = tMax.y;
                tMax.y += tDelta.y;
                steppedIndex = 1;
            } else {
                i.z += step.z;
                t = tMax.z;
                tMax.z += tDelta.z;
                steppedIndex = 2;
            }
        }
    }
    ret.iend = i;
    ret.end = position + (sf::Vector3<double>) (t * direction);
    ret.norm = sf::Vector3f();
    ret.isFound = false;
    return ret;
}
World::World(Engine& engine) : engine(engine) {

}
World::~World() = default;
void World::start_thread() {
    thread.emplace(&World::thread_main, this);
}
void World::requireStop() {
    stopRequire = true;
    WorldTask worldTask;
    worldTask.type = WorldTaskType::WorldThreadStop;
    externalQueue.enqueue(std::move(worldTask));
}
void World::waitStop() {
    requireStop();
    if (thread) {
        thread->join();
    }
}
void World::newTask(WorldTask&& worldTask) {
    externalQueue.enqueue(std::move(worldTask));
}
void World::oneBlock(WorldTaskType worldTaskType, sf::Vector3<int64_t> position) {
    WorldTask worldTask;
    worldTask.position = position;
    worldTask.type = worldTaskType;
    newTask(std::move(worldTask));
}
