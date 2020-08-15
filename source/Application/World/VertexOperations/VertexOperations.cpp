#include "VertexOperations.hpp"

std::array<float, 18> makeRectangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4) {
    return std::array<float, 18>{
            p3.x, p3.y, p3.z, p2.x, p2.y, p2.z, p1.x, p1.y, p1.z,
            p1.x, p1.y, p1.z, p4.x, p4.y, p4.z, p3.x, p3.y, p3.z
    };
}