#pragma once

#include <string>
#include <vector>
#include <map>
#include <optional>
#include <memory>

using OptionalMap = std::optional<std::map<std::string, std::vector<std::string>>>;

class TAObject
{
public:
    bool valid = false;

    virtual TAObject& Parse(std::string&, OptionalMap = std::nullopt); 

    virtual TAObject* Create();

    virtual std::string& getString();
protected:
    std::string defaultName = "Text Adventure Object";
};