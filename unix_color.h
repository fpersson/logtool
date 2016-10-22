#ifndef UNIX_COLOR_H
#define UNIX_COLOR_H
/*
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor,
 Boston, MA  02110-1301, USA.

 ---
 Copyright (C) 2016, Fredrik Persson <fpersson.se@gmail.com>
 */

#include <string>
#include <map>

/**
 * @note this list is only for 16 color, a 256color version have to be done by someone else.
 * @example std::cout << COLOR::Text::Red << "Red." << std::endl;
 */
namespace Color{
    namespace Text{
        const std::string Default = "\e[39m";
        const std::string Black = "\e[30m";
        const std::string Red = "\e[31m";
        const std::string Green = "\e[32m";
        const std::string Yellow = "\e[33m";
        const std::string Blue = "\e[34m";
        const std::string Magenta = "\e[35m";
        const std::string Cyan = "\e[36m";
        const std::string LightGray = "\e[37m";

        const std::string DarkGray = "\e[90m";
        const std::string LightRed = "\e[91m";
        const std::string LightGreen = "\e[92m";
        const std::string LightYellow = "\e[93m";
        const std::string LightBlue = "\e[94m";
        const std::string LightMagenta = "\e[95m";
        const std::string LightCyan = "\e[96m";
        const std::string White = "\e[97m";
    }

    namespace Background{
        const std::string Default = "\e[49m";
        const std::string Black = "\e[40m";
        const std::string Red = "\e[41m";
        const std::string Green = "\e[42m";
        const std::string Yellow = "\e[43m";
        const std::string Blue = "\e[44m";
        const std::string Magenta = "\e[45m";
        const std::string Cyan = "\e[46m";
        const std::string LightGray = "\e[47m";

        const std::string DarkGray = "\e[100m";
        const std::string LightRed = "\e[101m";
        const std::string LightGreen = "\e[102m";
        const std::string LightYellow = "\e[103m";
        const std::string LightBlue = "\e[104m";
        const std::string LightMagenta = "\e[105m";
        const std::string LightCyan = "\e[106m";
        const std::string White = "\e[107m";
    }

    namespace Format{
        const std::string Reset = "\e[0m";
        const std::string Bold = "\e[1m";
        const std::string Dim = "\e[2m"; //not supported in Konsole
        const std::string UnderLine = "\e[4m";
        const std::string Blink = "\e[5m";
        const std::string Invert = "\e[7m";
        const std::string Hidden = "\e[8m"; //not supported in Konsole
    }
}

#endif // UNIX_COLOR_H
