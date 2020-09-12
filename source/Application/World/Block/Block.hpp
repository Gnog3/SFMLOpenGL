#pragma once

#include <SFML/System.hpp>
#include <cstdint>
#include <vector>
#include <array>
#include <cassert>
#include "../../static_for/static_for.hpp"
#include "../../Direction.hpp"
#include "../Adjoins/Adjoins.hpp"

class Block {
    private:
        using vector3f = std::array<float, 3>;
        using vector2f = std::array<float, 2>;
        static constexpr vector3f getOffset(Direction direction, uint8_t stage);
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
        Block() = default;
        explicit Block(uint8_t id);
        [[nodiscard]] uint8_t getId() const;
        virtual void genVertices(sf::Vector3<uint8_t> blockPosition,
                                 Adjoins adjoins,
                                 std::vector<float>& vertices,
                                 std::vector<uint32_t>& indices);
};
