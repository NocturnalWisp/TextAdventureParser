#pragma once

#include <map>

#include "text_adventure.hpp"

#include "ta_object.hpp"
#include "ta_objects/ta_scene.hpp"
#include "ta_objects/ta_item.hpp"
#include "ta_objects/ta_event.hpp"

class Parser
{
public:
    Parser();

public:
    TextAdventure Parse(std::string& file);

private:
    const std::map<std::string, TAObject*> parseStrategies =
    {
        { "scenes", new TAScene() },
        { "items", new TAItem() },
        { "events", new TAEvent() }
    };

    ~Parser()
    {
        for (auto strategy : parseStrategies)
        {
            strategy.second = NULL;
            delete strategy.second;
        }
    }
};