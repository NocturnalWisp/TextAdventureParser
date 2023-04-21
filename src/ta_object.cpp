#include "../include/ta_object.hpp"

TAObject& TAObject::Parse(std::string& str, OptionalMap m)
{
    return *this;
}

TAObject* TAObject::Create()
{
    return new TAObject;
}

std::string& TAObject::getString()
{
    return name;
}