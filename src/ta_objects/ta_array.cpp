#include "../../include/ta_objects/ta_array.hpp"

using namespace tap;

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
    for (auto object : objects)
    {
        str.append(object->getString() + ", ");
    }
    str = str.substr(0, str.size()-2);
    return str;
}

int TAArray::getType()
{
    return 2;
}