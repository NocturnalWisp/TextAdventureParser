#pragma once

#include <string>
#include <vector>

class TAObject
{
public:
    virtual std::vector<TAObject> Parse(std::vector<std::string>);
};