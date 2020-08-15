#pragma once

#include <cstdint>
#include <vector>
//#include "../WorldReferenceHack/WorldReferenceHack.hpp"
#include "IThingContainer/IThingContainer.hpp"
class IBlockFragmentContainer : public IThingContainer {
    protected:
        typedef std::pair<sf::Vector3i, Thing> ThingPair;
//        std::vector<ThingPair> getAdjoiningBlocks(sf::Vector3i position) {
//            World& world = WRef::ref();
//            std::vector<ThingPair> nearbyBlocks;
//            for (auto& i : {-1, 1}) {
//                for (auto& j : {-1, 1}) {
//                    for (auto& k : {-1, 1}) {
//                        sf::Vector3i checkingPosition = position + sf::Vector3i(i, j, k);
//                        std::pair<ThingContainerTypeType, Thing> pair = world.things[checkingPosition];
//                        ThingContainerTypeType checkingType = pair.first;
//                        if (checkingType == ThingContainerTypeType::StaticBlock ||
//                            checkingType == ThingContainerTypeType::DynamicBlock) {
//                            nearbyBlocks.emplace_back(checkingPosition, pair.second);
//                        }
//                    }
//                }
//            }
//            return nearbyBlocks;
//        }
    public:
        virtual void addBlock(sf::Vector3i position, uint32_t state = 0) = 0;
        virtual void removeBlock(sf::Vector3i position) = 0;
};