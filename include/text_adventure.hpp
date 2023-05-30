#pragma once

#include <vector>

#include "ta_objects/ta_scene.hpp"
#include "ta_objects/ta_item.hpp"
#include "ta_objects/ta_event.hpp"

namespace tap {
class TextAdventure
{
public:
    ~TextAdventure();
public:
    std::vector<TAScene*> scenes;
    std::vector<TAItem*> items;
    std::vector<TAEvent*> events;

    void ParseStrategy(TAObject* object);

    std::string getString();
};
}