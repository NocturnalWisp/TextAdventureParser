#pragma once

#include <string>
#include <tuple>
#include <vector>
#include <map>
#include <functional>

template<typename T>
using StringMap = std::map<std::string, T>;

template<typename T>
using StringMapIt = typename StringMap<T>::iterator;

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

    bool HasDeliminator(std::string& og, char deliminator)
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
    
    std::tuple<std::string, std::string> SpliceString(std::string const& og, char deliminator, bool truncate = false)
    {
        std::string first, second;
        bool doneFirst = false;
        for (char c : og)
        {
            if (truncate && c == ' ')
                continue;

            if (c == deliminator)
                doneFirst = true;
            else
            {
                if (!doneFirst)
                    first.push_back(c);
                else
                    second.push_back(c);
            }
        }

        return {first, second};
    }

    // Returns a map of indented items.
    std::map<std::string, std::vector<std::string>> GetHeaders(std::vector<std::string>& lines, bool applyColonRemoval = false, int indentCount = 0)
    {
        auto headers = std::map<std::string, std::vector<std::string>>();

        std::vector<std::string> internalLines = std::vector<std::string>();
        bool inLineHeader = false;
        std::string lineHeader;
        for (std::string line : lines)
        {
            if (line[0] == '#' || line[0] == 0)
                continue;

            if (line[indentCount*4] == ' ' && inLineHeader)
            {
                internalLines.push_back(line);
                continue;
            }

            if (inLineHeader)
            {
                headers.insert(std::pair(lineHeader, internalLines));
                internalLines.clear();
            }

            lineHeader = applyColonRemoval ? std::get<0>(SpliceString(line, ':', true)) : line;
            inLineHeader = true;
        }

        // Insert the last header.
        headers.insert(std::pair(lineHeader, internalLines));

        return headers;
    }

    // Finds the first key that matches a passed list of keys.
    template <typename T>
    constexpr StringMapIt<T> FindFor(StringMapIt<T> first, StringMapIt<T> last, std::vector<std::string> keys)
    {
        for (; first != last; ++first)
        {
            for (auto key = 0; key < keys.size(); key++)
                if (keys[key].compare(first->first) == 0)
                    return first;
        }
        return last;
    }

    void HandleAppend(std::string& str, std::string item)
    {
        str.append(item);
    }

    void HandleAppend(std::vector<std::string>& list, std::string item)
    {
        list.push_back(item);
    }

    // Uses the find for to grab the contents of headers found by keys.
    template <typename T, typename U>
    void HandleGrabLines(std::map<std::string, T>& m,
        std::vector<std::string> keys,
        U& target)
    {
        auto header = FindFor<T>
            (m.begin(), m.end(), keys);
        
        if (header != m.end())
            for (auto line : header->second)
                HandleAppend(target, line);
    }
}