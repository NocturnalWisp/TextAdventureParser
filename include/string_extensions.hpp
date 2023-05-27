#pragma once

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <map>
#include <functional>
#include <numeric>

#include "ta_objects/ta_string.hpp"

using HeaderMap = std::map<std::string, std::pair<size_t, std::vector<std::string>>>;

using HeaderMapIt = typename HeaderMap::const_iterator;

namespace
{
    std::vector<std::string> GetLines(std::string& file)
    {
        std::vector<std::string> lines;
        std::string str = std::string();
        for (char c : file)
        {
            if (c == '\n')
            {
                lines.push_back(str);
                str = std::string();
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
        char allowedDelim = ' ')
    {
        for (; first != last; ++first)
        {
            for (auto key = 0; key < keys.size(); key++)
            {
                if (keys[key].compare(first->first) == 0)
                    return first;
                
                if (allowedDelim != ' ' &&
                    (allowedDelim + keys[key]).compare(first->first) == 0)
                {
                    usedDelim = allowedDelim;
                    return first;
                }
            }
        }
        return last;
    }

    // Uses the find for to grab the contents of headers found by keys.
    template <typename TAObj>
    void HandleGrabLines(HeaderMap const& m,
        std::vector<std::string> keys,
        char allowedDelims,
        std::function<void(std::pair<size_t, std::string>, char)> handleAppend,
        bool trim = true)
    {
        auto usedDelim = ' ';
        auto header = FindFor
            (m.begin(), m.end(), keys, allowedDelims, usedDelim);
        
        if (header == m.end())
        {
            std::cerr << "Failed to find header by any of these keys: [";
            for (auto key : keys)
                std::cerr << key << ", ";
            std::cerr << "\b\b]" << std::endl;
            return;
        }

        for (auto line : header->second.second)
        {
            if (trim)
            {
                auto trimmed = ltrim(line);
                handleAppend(std::pair(header->second.first, trimmed), usedDelim);
            }
            else
                handleAppend(std::pair(header->second.first, line), usedDelim);
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

    std::string CombineString(std::vector<std::string>& list)
    {
        return ltrim(std::accumulate(
        std::next(list.begin()), 
        list.end(), 
        list[0], 
        [](std::string a, std::string b) {
            return ltrim(a) + "\n" + ltrim(b);
        }));
    }

    std::string CombineString(std::vector<std::string> const& list)
    {
        return ltrim(std::accumulate(
        std::next(list.begin()), 
        list.end(), 
        list[0], 
        [](std::string a, std::string b) {
            return ltrim(a) + ltrim(b);
        }));
    }
}