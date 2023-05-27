#pragma once

#include <string>
#include <vector>
#include <map>
#include <optional>
#include <memory>

using LineList = std::vector<std::pair<size_t, std::string>>;
using OptionalMap = std::optional<std::map<std::string, std::pair<size_t, LineList>>>;

class TAObject
{
public:
    bool valid = false;

    virtual TAObject& Parse(std::string&, OptionalMap = std::nullopt); 

    // Used for the main Text Adventure objects (Scenes, Items, and Events)
    virtual TAObject* Create() = 0;

    virtual std::string& getString();

    virtual std::string getClass() = 0;
protected:
    std::string defaultName = "Text Adventure Object";
};