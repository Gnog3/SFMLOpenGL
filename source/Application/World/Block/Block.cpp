#include "Block.hpp"

constexpr std::array<float, 3> Block::getOffset(Direction direction, uint8_t stage) {
    using std::array;
    array<vector3f, 6> startingPoints{
            vector3f{0, 1, 0},
            vector3f{1, 0, 1},
            vector3f{0, 1, 0},
            vector3f{1, 1, 1},
            vector3f{0, 1, 1},
            vector3f{1, 1, 0}
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

Block::Block(uint8_t id) : id(id) {}

uint8_t Block::getId() const {
    return id;
}

bool Block::isBlock() {
    return true;
}
void Block::genVertices(sf::Vector3<uint8_t> blockPosition, Adjoins adjoins, std::vector<float>& vertices,
                        std::vector<uint32_t>& indices) {
    uint32_t adjoinsAmount = adjoins.amount();
    if (adjoinsAmount == 6)
        return;
    vertices.reserve(vertices.size() + (6 * 4 * 8 - adjoinsAmount * 4 * 8));
    indices.reserve(indices.size() + (6 * 6 - adjoinsAmount * 6));
    uint32_t indexBase = vertices.size() / 8;
    Adjoins sides = ~adjoins;
    constexpr bool (Adjoins::* funcs[])() const {
            &Adjoins::isUp,
            &Adjoins::isDown,
            &Adjoins::isLeft,
            &Adjoins::isRight,
            &Adjoins::isFront,
            &Adjoins::isBack
    };
    uint32_t x = id % 16;
    uint32_t y = id / 16;
    sf::Vector2f texCoords((float) x / 16, (float) y / 16);
    for_range<0, 6>([&]<auto i>() {
        if ((sides.*funcs[i])()) {
            for_range<0, 4>([&]<auto j>() {
                constexpr vector3f offset = getOffset(static_cast<Direction>(i), j);
                std::array<float, 8> arr;
                arr[0] = (float) blockPosition.x + offset[0];
                arr[1] = (float) blockPosition.y + offset[1];
                arr[2] = (float) blockPosition.z + offset[2];
                arr[3] = normals[i][0];
                arr[4] = normals[i][1];
                arr[5] = normals[i][2];
                arr[6] = texCoords.x + texCoordsOffset[j][0];
                arr[7] = texCoords.y + texCoordsOffset[j][1];
                vertices.insert(vertices.end(), arr.begin(), arr.end());
            });
            std::array<uint32_t, 6> arr;
            arr[0] = indexBase + 0;
            arr[1] = indexBase + 1;
            arr[2] = indexBase + 2;
            arr[3] = indexBase + 1;
            arr[4] = indexBase + 3;
            arr[5] = indexBase + 2;
            indices.insert(indices.end(), arr.begin(), arr.end());
            indexBase += 4;
        }
    });
}

