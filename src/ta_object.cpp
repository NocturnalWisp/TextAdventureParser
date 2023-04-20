#include "../include/ta_object.hpp"

TAObject& TAObject::Parse(std::string& str, OptionalMap m = std::nullopt)
{
    valid = true;
    return *this;
} 