#ifndef SFMLOPENGL_OPENGLMODEL_HPP
#define SFMLOPENGL_OPENGLMODEL_HPP

/*
 * float vertex x  float vertex y  float vertex z
 * float color  r  float color  g  float color  b
 * float normal x  float normal y  float normal z
 *
 *
 */
#include <glm.hpp>
#include <vector>
class OpenGLModel {
    private:
        std::vector<glm::vec3> arr;
    public:
        void addPoint(glm::vec3 point, glm::vec3 color, glm::vec3 normal);
        void addLine(glm::vec3 p1, glm::vec3 p2, glm::vec3 color, glm::vec3 normal);
        void addTriangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 color, glm::vec3 normal);
        void addRectangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, glm::vec3 color, glm::vec3 normal);
        void addCollider(glm::vec3 p1,
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
                         glm::vec3 f6
        );
        [[nodiscard]] size_t size() const;
        [[nodiscard]] const std::vector<glm::vec3>& link() const;
};


#endif //SFMLOPENGL_OPENGLMODEL_HPP
