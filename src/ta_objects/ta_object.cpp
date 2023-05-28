#include "../../include/ta_objects/ta_object.hpp"

using namespace tap;

TAObject& TAObject::Parse(std::string& str, OptionalMap m)
{
    return *this;
}

std::string& TAObject::getString()
{
    return defaultName;
}

int TAObject::getType()
{
    return 0;
}