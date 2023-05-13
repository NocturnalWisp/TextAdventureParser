#include "../include/ta_object.hpp"

TAObject& TAObject::Parse(std::string& str, OptionalMap m)
{
    return *this;
}

std::string& TAObject::getString()
{
    return defaultName;
}

std::string TAObject::getClass()
{
    return "TAObject";
}