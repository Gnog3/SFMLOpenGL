#pragma once

class World;

namespace WRef {
    void setWorld(World* world);
    World*& getPtrRef();
    World& ref();
}
