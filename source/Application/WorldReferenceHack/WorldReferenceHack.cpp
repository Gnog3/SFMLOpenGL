#include "WorldReferenceHack.hpp"

World*& WRef::getPtrRef() {
    static World* ptr = nullptr;
    return ptr;
}
void WRef::setWorld(World* world) {
    getPtrRef() = world;
}
World& WRef::ref() {
    return *getPtrRef();
}
