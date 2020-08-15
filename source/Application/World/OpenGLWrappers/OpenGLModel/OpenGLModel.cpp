#include "OpenGLModel.hpp"


void OpenGLModel::addPoint(glm::vec3 point, glm::vec3 color, glm::vec3 normal) {
    arr.reserve(arr.size() + 3);
    arr.push_back(point);
    arr.push_back(color);
    arr.push_back(normal);
}

void OpenGLModel::addLine(glm::vec3 p1, glm::vec3 p2, glm::vec3 color, glm::vec3 normal) {
    addPoint(p1, color, normal);
    addPoint(p2, color, normal);
}

void OpenGLModel::addTriangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 color, glm::vec3 normal) {
    addPoint(p1, color, normal);
    addPoint(p2, color, normal);
    addPoint(p3, color, normal);
}

void OpenGLModel::addRectangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, glm::vec3 color, glm::vec3 normal) {
    addTriangle(p3, p2, p1, color, normal);
    addTriangle(p1, p4, p3, color, normal);
}

void OpenGLModel::addCollider(glm::vec3 p1,
                              glm::vec3 p2,
                              glm::vec3 p3,
                              glm::vec3 p4,
                              glm::vec3 p5,
                              glm::vec3 p6,
                              glm::vec3 p7,
                              glm::vec3 p8,
                              glm::vec3 color,
                              glm::vec3 f1,
                              glm::vec3 f2,
                              glm::vec3 f3,
                              glm::vec3 f4,
                              glm::vec3 f5,
                              glm::vec3 f6) {
    addRectangle(p1, p2, p3, p4, color, f1);
    addRectangle(p8, p7, p6, p5, color, f2);
    addRectangle(p4, p8, p5, p1, color, f3);
    addRectangle(p2, p6, p7, p3, color, f4);
    addRectangle(p1, p5, p6, p2, color, f5);
    addRectangle(p3, p7, p8, p4, color, f6);
}

size_t OpenGLModel::size() const {
    return arr.size();
}

const std::vector<glm::vec3>& OpenGLModel::link() const {
    return arr;
}

