#pragma once

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <map>
#include <functional>
#include <numeric>

#include "ta_objects/ta_string.hpp"

using HeaderMap = std::map<std::string, std::pair<size_t, std::vector<std::pair<size_t, std::string>>>>;

using HeaderMapIt = typename HeaderMap::const_iterator;

namespace
{
    std::vector<std::pair<size_t, std::string>> GetLines(std::string& file)
    {
        std::vector<std::pair<size_t, std::string>> lines;
        std::string str = std::string();

        size_t lineNumber = 0;
        for (char c : file)
        {
            if (c == '\n')
            {
                lines.push_back(std::pair(lineNumber, str));
                str = std::string();
                lineNumber++;
            }
            else
            {
                str.push_back(c);
            }
        }

        return lines;
    }

    bool HasDeliminator(std::string const& og, char deliminator)
    {
        bool has = false;
        for (char c : og)
        {
            if (c == deliminator)
            {
                has = true;
                break;
            }
        }

        return has;
    }

    std::vector<char> HasDeliminator(std::string const& og, std::vector<char> deliminators)
    {
        std::vector<char> has;
        for (char c : og)
        {
            for (char delim : deliminators)
            {
                if (c == delim)
                {
                    has.push_back(delim);
                }
            }
        }

        return has;
    }

    std::string RemoveDeliminators(std::string const& og)
    {
        std::string newString;
        for (char c : og)
        {
            if (std::isalnum(c) || c == ' ' || c == '_' || c == '-')
                newString.push_back(c);
        }

        return newString;
    }
    
    std::tuple<std::string, std::string> SpliceString(std::string const& og, char deliminator, bool truncate = false)
    {
        std::string first, second;
        bool doneFirst = false;
        bool foundFirstChar = false;
        for (char c : og)
        {
            if (truncate && !foundFirstChar && c != 0 && c != ' ')
                foundFirstChar = true;

            if (truncate && !foundFirstChar)
                continue;

            if (c == deliminator)
            {
                doneFirst = true;
                continue;
            }

            if (!doneFirst)
                first.push_back(c);
            else
                second.push_back(c);
        }

        return {first, second};
    }

    inline std::string ltrim(std::string const& s, const char t = ' ')
    {
        return s.substr(s.find_first_not_of(t));
    }

    // Finds the first key that matches a passed list of keys.
    HeaderMapIt FindFor(HeaderMapIt first,
        HeaderMapIt last,
        std::vector<std::string> const& keys,
        char& usedDelim,
        std::vector<char> allowedDelims = std::vector<char>())
    {
        for (; first != last; ++first)
        {
            for (auto key = 0; key < keys.size(); key++)
            {
                if (keys[key].compare(first->first) == 0)
                    return first;
                
                if (allowedDelims.size() > 0)
                {
                    for (char allowedDelim : allowedDelims)
                    {
                        if ((allowedDelim + keys[key]).compare(first->first) == 0)
                        {
                            usedDelim = allowedDelim;
                            return first;
                        }
                    }
                }
            }
        }
        return last;
    }

    // Uses the find for to grab the contents of headers found by keys.
    void HandleGrabLines(HeaderMap const& m,
        std::vector<std::string> keys,
        std::vector<char> allowedDelims,
        std::function<void(std::pair<size_t, std::string>, std::pair<size_t, char>)> handleAppend,
        bool trim = true,
        std::function<void()> failed = nullptr)
    {
        auto usedDelim = ' ';
        auto header = FindFor
            (m.begin(), m.end(), keys, usedDelim, allowedDelims);
        
        if (header == m.end())
        {
            failed();
            return;
        }

        for (auto line : header->second.second)
        {
            if (trim)
            {
                auto trimmed = ltrim(line.second);
                handleAppend(std::pair(line.first, trimmed), std::pair(header->second.first, usedDelim));
            }
            else
                handleAppend(std::pair(line.first, line.second), std::pair(header->second.first, usedDelim));
        }
    }

    // Handle Append deals with adding the content of headers to a string or list.
    void HandleAppend(std::string& str, std::string item)
    {
        str.append(item);
    }

    void HandleAppend(TAString& str, TAString const& item)
    {
        str.str.append(item.str);
    }

    void HandleAppend(TAString& str, std::string const& item)
    {
        str.str.append(item);
    }

    template<typename T, typename U>
    void HandleAppend(std::vector<T>& list, U item)
    {
        list.push_back(item);
    }

    std::string CombineString(LineList& list)
    {
        std::string result;
        for (int i = 0; i < list.size(); i++)
        {
            result.append(ltrim(list[i].second));
            if (i < list.size()-1)
            {
                result.append("\n");
            }
        }
        return result;
    }

    std::string CombineString(LineList const& list)
    {
        std::string result;
        for (int i = 0; i < list.size(); i++)
        {
            result.append(ltrim(list[i].second));
            if (i < list.size()-1)
            {
                result.append("\n");
            }
        }
        return result;
    }
}