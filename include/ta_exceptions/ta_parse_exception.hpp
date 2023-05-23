#pragma once

#include <iostream>
#include <string>

using namespace std;

namespace tap
{
    class ParseException
    {
    private:
        std::string message;
        size_t lineNumber;
        size_t characterNumber;
    public:
    ParseException(std::string msg, size_t lineNumber, size_t characterNumber)
        : message(msg), lineNumber(lineNumber), characterNumber(characterNumber) {}
    
    std::string Result()
    {
        return "Parse error: " + message + " at line [" + to_string(lineNumber) + "] Character [" + to_string(characterNumber) + "].";
    }
    };
};