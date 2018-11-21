
/*
This file is part of OGS Board game constructor:
  https://github.com/OGStudio/ogs-board-game-constructor

Copyright (C) 2018 Opensource Game Studio

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef OGS_BOARD_GAME_CONSTRUCTOR_FORMAT_H
#define OGS_BOARD_GAME_CONSTRUCTOR_FORMAT_H

// printfString Start
#include <cstdarg>

// printfString End
// urlToParameters Start
#include <map>

// urlToParameters End

namespace bgc
{
namespace format
{

// printfString Start
//! Construct a string using printf-like syntax.
std::string printfString(const char *fmt, ...)
{
    const int PRINTF_STRING_MAX_STRLEN = 1024;
    va_list args;
    char msg[PRINTF_STRING_MAX_STRLEN];
    va_start(args, fmt);
    vsnprintf(msg, PRINTF_STRING_MAX_STRLEN, fmt, args);
    va_end(args);
    return msg;
}
// printfString End
// splitString Start
//! Split a string into a list of strings using a single character.
std::vector<std::string> splitString(const std::string &s, const char *c)
{
    size_t pos = 0;
    bool proceed = true;
    bool hasChar = false;
    std::vector<std::string> result;
    while (proceed)
    {
        auto id = s.find(c, pos);
        if (id != std::string::npos)
        {
            result.push_back(s.substr(pos, id - pos));
            pos = id + 1;
            hasChar = true;
        }
        else
        {
            result.push_back(s.substr(pos, s.length()));
            proceed = false;
            // If delimiting char has not been found,
            // the result should only contain original string.
        }
    }
    return result;
}
// splitString End
// stringStartsWith Start
//! Find prefix in the provided string.
bool stringStartsWith(const std::string &s, const std::string &prefix)
{
    // Source: https://stackoverflow.com/a/8095127
    // Topic: how to check string start in C++
    return
        (prefix.length() <= s.length()) &&
        std::equal(prefix.begin(), prefix.end(), s.begin())
        ;
}
// stringStartsWith End
// stringsToString Start
//! Combine several strings into single one
std::string stringsToString(
    const std::vector<std::string> &strings,
    const std::string &separator = ", "
) {
    std::string result;
    for (auto item : strings)
    {
        // Items after the first one.
        if (!result.empty())
        {
            result += separator + item;
        }
        // First item.
        else
        {
            result = item;
        }
    }

    return result;
}
// stringsToString End

// urlToParameters Start
typedef std::map<std::string, std::string> Parameters;
//! Convert query parameters starting after `?` that are in the form of `key=value` to parameters.
Parameters urlToParameters(int argc, char *argv[])
{
    Parameters parameters;

    // No URL has been provided. Nothing to parse.
    if (argc < 3)
    {
        return parameters;
    }

    auto query = argv[2];
    auto options = format::splitString(query, "&");

    for (auto option : options)
    {
        auto keyAndValue = format::splitString(option, "=");
        if (keyAndValue.size() == 2)
        {
            auto key = keyAndValue[0];
            auto value = keyAndValue[1];
            parameters[key] = value;
        }
    }

    // Add "base" parameter.
    parameters["base"] = argv[1];

    return parameters;
}
// urlToParameters End

} // namespace format
} // namespace bgc

#endif // OGS_BOARD_GAME_CONSTRUCTOR_FORMAT_H

