#pragma once

#include <SFML/System/Vector3.hpp>
#include "../../Thing.hpp"
enum class ThingContainerTypeType {
        StaticBlock,
        DynamicBlock,
        Component
};

class IThingContainer {
    private:
        Thing thing = Thing::wool_black;
    public:
        //explicit IThingContainer(Thing thing) : thing(thing){}
        virtual ~IThingContainer() = default;
        virtual ThingContainerTypeType typeType() = 0;
        Thing type();
        virtual void draw() = 0;
};
