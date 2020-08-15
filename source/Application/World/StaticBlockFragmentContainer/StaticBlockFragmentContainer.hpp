#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-default-arguments"
#pragma once

#include <memory>
#include <atomic>
#include <cstring>
#include <SFML/System.hpp>
#include <SFML/Graphics/Image.hpp>
#include "../IBlockFragmentContainer.hpp"
#include "../StaticBlockFragment/StaticBlockFragment.hpp"
#include "../../ogl.hpp"

class StaticBlockFragmentContainer : public IBlockFragmentContainer {
    private:
        static constexpr int a[] {1, 2, 3, 4};
        
        std::vector<StaticBlockFragment> fragments;
        std::atomic_bool rebuilt = true;
        size_t vertexSize = 0;
        uint32_t vaoid = 0;
        uint32_t vboid = 0;
        uint32_t textureId = 0;
    public:
        explicit StaticBlockFragmentContainer(std::string& texturePath);
        ~StaticBlockFragmentContainer() override;
        ThingContainerTypeType typeType() override;
        void addBlock(sf::Vector3i position, uint32_t state = 0) override;
        void removeBlock(sf::Vector3i position) override;
        void draw() override;
};

#pragma clang diagnostic pop