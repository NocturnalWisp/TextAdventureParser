#pragma once

#ifndef DEBUGTAP
#define DEBUGTAP
#endif

#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "../include/string_extensions.hpp"

#include "text_adventure.hpp"

#include "ta_objects/ta_object.hpp"
#include "ta_objects/ta_scene.hpp"
#include "ta_objects/ta_item.hpp"
#include "ta_objects/ta_event.hpp"

#include "ta_exceptions/ta_parse_exception.hpp"

namespace tap {
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
    TextAdventure Parse(std::string);
    static HeaderMap GetHeaders(LineList&, bool applyColonRemoval = false, int indentCount = 0);

    static size_t startHeaderLine;

private:
    const std::map<std::string, TAObject*> parseStrategies =
    {
        { "scenes", new TAScene() },
        { "items", new TAItem() },
        { "events", new TAEvent() }
    };

};
}