#pragma once

#include <iostream>
#include <string>

using namespace std;

namespace tap
{
    class ParseException : public std::exception
    {
    private:
        std::string message;
    public:
        ParseException(std::string msg, size_t lineNumber, size_t characterNumber)
        {
            message = "Parse error: " + msg + " at line [" + to_string(lineNumber) + "] Character [" + to_string(characterNumber) + "]."; 
        }
        
        const char* what() const noexcept override
        {
            return message.c_str();
        }
    };
};