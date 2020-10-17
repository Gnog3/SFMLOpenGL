#pragma once

#include <SFML/System.hpp>
#include <cstdint>
#include <vector>
#include <array>
#include <cassert>
#include "../../static_for/static_for.hpp"
#include "../../Direction.hpp"
#include "../Adjoins/Adjoins.hpp"
#include "../../Engine/PlaneVertex.hpp"
#include "../ChunkVertexData.hpp"

class Block {
    private:
        using vector3f = std::array<float, 3>;
        using vector2f = std::array<float, 2>;
        static constexpr std::array<float, 3> getOffset(Direction direction, uint8_t stage) {
            using std::array;
            array<vector3f, 6> startingPoints{
                    vector3f{0, 1, 0}, // up
                    vector3f{1, 0, 1}, // down
                    vector3f{0, 1, 0}, // left
                    vector3f{1, 1, 1}, // right
                    vector3f{0, 1, 1}, // front
                    vector3f{1, 1, 0} // back
            };
            array<array<vector3f, 6>, 2> stages{
                    array<vector3f, 6>{
                            vector3f{1, 0, 0},
                            vector3f{-1, 0, 0},
                            vector3f{0, 0, 1},
                            vector3f{0, 0, -1},
                            vector3f{1, 0, 0},
                            vector3f{-1, 0, 0}
                    },
                    array<vector3f, 6>{
                            vector3f{0, 0, 1},
                            vector3f{0, 0, -1},
                            vector3f{0, -1, 0},
                            vector3f{0, -1, 0},
                            vector3f{0, -1, 0},
                            vector3f{0, -1, 0}
                    }
            };
            vector3f startingPoint = startingPoints[direction];
            if (stage & 1u) {
                vector3f offset = stages[0][direction];
                startingPoint[0] += offset[0];
                startingPoint[1] += offset[1];
                startingPoint[2] += offset[2];
            }
            if (stage & 2u) {
                vector3f offset = stages[1][direction];
                startingPoint[0] += offset[0];
                startingPoint[1] += offset[1];
                startingPoint[2] += offset[2];
            }
            return startingPoint;
        }
        static constexpr vector3f normals[6]{
                vector3f{0, 1, 0},
                vector3f{0, -1, 0},
                vector3f{-1, 0, 0},
                vector3f{1, 0, 0},
                vector3f{0, 0, 1},
                vector3f{0, 0, -1}
        };
        static constexpr vector2f texCoordsOffset[]{
                vector2f{0, 0},
                vector2f{1.0f / 16.0f, 0},
                vector2f{0, 1.0f / 16.0f},
                vector2f{1.0f / 16.0f, 1.0f / 16.0f}
        };
    protected:
        uint8_t id;
    public:
        static sf::Vector3<uint8_t> getPositionChunkRel(sf::Vector3<int64_t> blockPosition);
        Block() : id(0) {};
        explicit Block(uint8_t id);
        [[nodiscard]] uint8_t getId() const;
        template<int side>
        __forceinline void genVertices(sf::Vector3<uint8_t> blockPosition, ChunkVertexData& data, sf::Vector2f texCoords) const {
            uint32_t indexBase = data.vertexData.size();
            for_range<0, 4>([&]<auto j>() {
                constexpr vector3f offset = getOffset(static_cast<Direction>(side), j);
                PlaneVertex planeVertex;
                planeVertex.position.x = (float) blockPosition.x + offset[0];
                planeVertex.position.y = (float) blockPosition.y + offset[1];
                planeVertex.position.z = (float) blockPosition.z + offset[2];
                planeVertex.normal.x = normals[side][0];
                planeVertex.normal.y = normals[side][1];
                planeVertex.normal.z = normals[side][2];
                planeVertex.texCoord.x = texCoords.x + texCoordsOffset[j][0];
                planeVertex.texCoord.y = texCoords.y + texCoordsOffset[j][1];
                data.vertexData.push_back(planeVertex);
            });
            std::array<uint32_t, 6> arr{};
            if constexpr (Down == static_cast<Direction>(side)) {
                arr[0] = indexBase + 1;
                arr[1] = indexBase + 2;
                arr[2] = indexBase + 0;
                arr[3] = indexBase + 3;
                arr[4] = indexBase + 2;
                arr[5] = indexBase + 1;
            } else {
                arr[0] = indexBase + 0;
                arr[1] = indexBase + 2;
                arr[2] = indexBase + 1;
                arr[3] = indexBase + 1;
                arr[4] = indexBase + 2;
                arr[5] = indexBase + 3;
            }
            data.indexData.insert(data.indexData.end(), arr.begin(), arr.end());
        }
};
