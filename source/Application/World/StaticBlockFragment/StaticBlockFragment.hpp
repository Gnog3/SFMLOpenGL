#pragma once
#include <memory>
#include <vector>
#include <SFML/System/Vector3.hpp>

class StaticBlockFragment {
    private:
        std::vector<float> vertexData;
        std::vector<sf::Vector3i> blocks;
    public:
        void addBlock(sf::Vector3i position);
        size_t getSize();
        std::vector<float>& getVertices();
};



