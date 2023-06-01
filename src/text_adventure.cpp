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

void TextAdventure::ParseStrategy(TAObject* object)
{
    if (object->getType() == TAScene().getType())
    {
        scenes.push_back((TAScene*)object);
    }
    else if (object->getType() == TAItem().getType())
    {
        items.push_back((TAItem*)object);
    }
    else if (object->getType() == TAEvent().getType())
    {
        events.push_back((TAEvent*)object);
    }
    else
    {
        delete object;
    }
}

std::string TextAdventure::getString()
{
    std::string output;
    for (auto scene : scenes)
    {
        output.append("\n" + scene->name->getString() + "\n");
        if (scene->desc != nullptr)
            output.append(scene->desc->getString() + "\n");
        for (auto item : scene->items)
            if (item != nullptr)
                output.append(item->getString() + "\n");
        for (auto exit : scene->exits)
            output.append(std::get<0>(exit).getString() + " : " + std::get<1>(exit).getString() + "\n");
        output.append("\n");
    }

    for (auto item : items)
    {
        output.append("\n" + item->name.getString() + "\n");
        output.append(item->desc.getString() + "\n");
        for (auto action : item->actions)
            if (action != nullptr)
                output.append(action->getString() + "\n");
        output.append("\n");
    }

    for (auto event : events)
    {
        output.append("\n" + event->name.getString() + "\n");
        output.append(event->desc.getString() + "\n");
        for (auto action : event->actions)
            if (action != nullptr)
                output.append(action->getString() + "\n");
        output.append("\n");
    }

    return output;
}