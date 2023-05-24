#pragma once

#include <map>
#include <iostream>
#include <string>
#include <vector>

#include "../include/string_extensions.hpp"

#include "text_adventure.hpp"

#include "ta_object.hpp"
#include "ta_objects/ta_scene.hpp"
#include "ta_objects/ta_item.hpp"
#include "ta_objects/ta_event.hpp"

#include "ta_exceptions/ta_parse_exception.hpp"

class TAScene;

class Parser
{
public:
    Parser();

    ~Parser()
    {
        for (auto strategy : parseStrategies)
        {
            strategy.second = NULL;
            delete strategy.second;
        }
    }

public:
    TextAdventure Parse(std::string& file);
    static std::map<std::string, std::vector<std::string>> GetHeaders(std::vector<std::string>&, bool applyColonRemoval = false, int indentCount = 0);

private:
    const std::map<std::string, TAObject*> parseStrategies =
    {
        { "scenes", new TAScene() },
        { "items", new TAItem() },
        { "events", new TAEvent() }
    };
};