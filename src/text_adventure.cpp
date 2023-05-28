#include "../include/text_adventure.hpp"

using namespace tap;

TextAdventure::~TextAdventure()
{
    for (auto scene : scenes)
        delete scene;
    scenes.clear();

    for (auto item : items)
        delete item;
    items.clear();

    for (auto event : events)
        delete event;
    events.clear();
}