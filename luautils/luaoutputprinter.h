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
 Copyright (C) 2017, Fredrik Persson <fpersson.se@gmail.com>
 */

#ifndef LUAOUTPUTPRINTER_H
#define LUAOUTPUTPRINTER_H

#include <iostream>
#include <memory>

#include <QStringList>
#include <QDebug>

extern "C" {
#include <lua5.2/lua.h>
#include <lua5.2/lualib.h>
#include <lua5.2/lauxlib.h>
}

//#include "utils/flog.h"
#include "luaunixcolor.h"

namespace luautils {
    class OutputPrinter {
    public:
        explicit OutputPrinter(const QStringList &keywords);
        void updateKeywords(const QStringList &keywords){m_keywords=keywords;}
        void colorizeOutput(const QString &line);
    private:
        QStringList m_keywords;
        lua_State *m_luaState;

        std::string parseInLua(std::string msg);
    };
} //namespace


#endif //LUAOUTPUTPRINTER_H
