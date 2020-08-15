#pragma once
#include <array>
#include <memory>
#include "../Thing.hpp"
#include "IThingContainer/IThingContainer.hpp"

typedef std::unique_ptr<IThingContainer> ThingContainers[static_cast<size_t>(Thing::Amount)];