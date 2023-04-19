#pragma once

#include <iostream>
#include <string>
#include <algorithm>

#include "../ta_object.hpp"
#include "../string_extensions.hpp"

class TAScene : public TAObject
{
public:
    std::string name;
    std::string desc;
    std::vector<std::string> items;
    std::vector<std::string> exits;

    std::vector<TAObject> Parse(std::vector<std::string> scenes) override
    {
        auto parsedScenes = std::vector<TAObject>();

        for (auto& s : scenes)
            s = s.substr(4);
        
        // Main scene header.
        auto headersForScenes = GetHeaders(scenes, true);

        for (auto headerForScene : headersForScenes)
        {
            TAScene scene = TAScene();
            scene.name = headerForScene.first;

            // Property headers. (Desc, items, exits, etc...)
            auto propertyHeaders = GetHeaders(headerForScene.second, true, 1);

            HandleGrabLines(
                propertyHeaders,
                { "description", "desc" },
                scene.desc
            );

            HandleGrabLines(
                propertyHeaders,
                { "items" },
                scene.items
            );

            HandleGrabLines(
                propertyHeaders,
                { "exits" },
                scene.exits
            );

            std::cout <<std::endl;
            std::cout << scene.name << scene.desc;
            for (auto item : scene.items)
                std::cout << item;
            for (auto exit : scene.exits)
                std::cout << exit;
            std::cout << std::endl;

            parsedScenes.push_back(scene);
        }

        return parsedScenes;
    }
};