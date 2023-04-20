#pragma once

#include <string>
#include <vector>
#include <map>
#include <optional>

using OptionalMap = std::optional<std::map<std::string, std::vector<std::string>>>;

class TAObject
{
public:
    bool valid = false;

    virtual TAObject& Parse(std::string&, OptionalMap); 
};