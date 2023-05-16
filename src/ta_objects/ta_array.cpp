#include "../../include/ta_objects/ta_array.hpp"

TAArray::TAArray(std::vector<TAObject *> objects) : objects(objects)
{
    valid = true;
}

TAObject& TAArray::Parse(std::string& str, OptionalMap m)
{
    return *this;
}

TAObject* TAArray::Create()
{
    return new TAArray({});
}

std::string& TAArray::getString()
{
    str = "%";
    for (auto object : objects)
    {
        str.append(object->getString() + "&");
    }
    return str;
}

std::string TAArray::getClass()
{
    return "TAArray";
}