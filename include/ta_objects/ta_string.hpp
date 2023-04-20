#include "../ta_object.hpp"

class TAString : public TAObject
{
public:
    TAString(){}
    TAString(std::string str) : str(str) {}
public:
    std::string str;
};