#include "World.hpp"


World::World() {
    glEnable(GL_DEPTH_TEST);
    
    chunkShader.loadFromFile("Data/Shaders/plane.vertex.glsl", "Data/Shaders/plane.fragment.glsl");
    skyBox = std::make_unique<SkyBox>("Data/Shaders/skybox.vertex.glsl", "Data/Shaders/skybox.fragment.glsl",
                                      std::vector<std::string>{
                                              "Data/SkyBoxTextures/right.bmp",
                                              "Data/SkyBoxTextures/left.bmp",
                                              "Data/SkyBoxTextures/top.bmp",
                                              "Data/SkyBoxTextures/bottom.bmp",
                                              "Data/SkyBoxTextures/front.bmp",
                                              "Data/SkyBoxTextures/back.bmp"
                                      });
    crosshair.construct();
    sf::Image image;
    image.loadFromFile("Data/texture.png");
    sf::Vector2u size = image.getSize();
    glGenTextures(1, &blockTexture);
    glBindTexture(GL_TEXTURE_2D, blockTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    float data[] = {
            0.0f, 0.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 1.0f / 16.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 1.0f / 16.0f,
            1.0f, 0.0f, 1.0f / 16.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 1.0f / 16.0f,
            1.0f, 1.0f, 1.0f / 16.0f, 1.0f / 16.0f,
//            0.0f, 0.0f, 0.0f, 0.0f,
//            0.0f, 0.0f, 0.0f, 0.0f,
//
//            1.0f, 0.0f, 1.0f / 16.0f, 0.0f,
//            1.0f, 0.0f, 1.0f / 16.0f, 0.0f,
//
//            0.0f, 1.0f, 0.0f, 1.0f / 16.0f,
//            0.0f, 1.0f, 0.0f, 1.0f / 16.0f,
//
//            1.0f, 0.0f, 1.0f / 16.0f, 0.0f,
//            1.0f, 0.0f, 1.0f / 16.0f, 0.0f,
//            0.0f, 1.0f, 0.0f, 1.0f / 16.0f,
//
//            0.0f, 1.0f, 0.0f, 1.0f / 16.0f,
//            1.0f, 1.0f, 1.0f / 16.0f, 1.0f / 16.0f,
//
//            1.0f, 1.0f, 1.0f / 16.0f, 1.0f / 16.0f
    };
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    glGenBuffers(1, &planeVbo);
    glBindBuffer(GL_ARRAY_BUFFER, planeVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
World::~World() = default;
Block* World::getBlock(sf::Vector3<int64_t> position) {
    sf::Vector3i chunk = Chunk::getChunk(position);
    auto chunkSearch = chunkMap.find(chunk);
    if (chunkSearch != chunkMap.end()) {
        Chunk& chunkRef = chunkSearch->second;
        return chunkRef.getBlock(Block::getPositionChunkRel(position));
    }
    return nullptr;
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
void World::draw(Player& player) {
    glm::mat4 view = player.getViewMatrix();
    glm::mat4 projection = player.getProjectionMatrix();
    glm::mat4 vp = player.getVpMatrix();
    skyBox->draw(projection * glm::mat4(glm::mat3(view))); // TODO: need to be optimized()()
    sf::Shader::bind(&chunkShader);
    chunkShader.setUniform("VP", sf::Glsl::Mat4(&vp[0][0]));
//    Timer timer;
    for (auto& chunk : chunkMap) {
        
        Chunk& c = chunk.second;
        if (c.getChanged()) {
            c.calculateVertices(chunkMap);
            c.sendVertices();
        }
        c.draw(blockTexture, player.getPlayerPos(), chunkShader);
    }
    crosshair->draw();
//    timer.printMicroseconds();
//    sf::Shader::bind(nullptr);
}
void World::placeBlock(std::unique_ptr<Block> block, sf::Vector3<int64_t> position) {
    sf::Vector3i chunkPosition = Chunk::getChunk(position);
    Chunk* chunk;
    try {
        chunk = &chunkMap.at(chunkPosition);
    } catch (std::out_of_range&) {
        chunk = &chunkMap.emplace(std::make_pair(sf::Vector3i(chunkPosition), Chunk(sf::Vector3i(chunkPosition), planeVbo))).first->second;
    }
    sf::Vector3<uint8_t> blockPositionChunkRel = Block::getPositionChunkRel(position);
    chunk->placeBlock(blockPositionChunkRel, std::move(block));
}
void World::removeBlock(sf::Vector3<int64_t> position) {
    sf::Vector3i chunkPosition = Chunk::getChunk(position);
    Chunk* chunk;
    try {
        chunk = &chunkMap.at(chunkPosition);
    } catch (std::out_of_range&) {
        return;
    }
    sf::Vector3<uint8_t> blockPositionChunkRel = Block::getPositionChunkRel(position);
    chunk->removeBlock(blockPositionChunkRel);
}
