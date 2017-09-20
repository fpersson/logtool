//
// Created by fredrik on 2017-09-20.
//

#ifndef LUAUNIXCOLOR_H
#define LUAUNIXCOLOR_H

#include <string>
#include "utils/unix_color.h"

extern "C"
{
#include <lua5.2/lua.h>
#include <lua5.2/lualib.h>
#include <lua5.2/lauxlib.h>
}

namespace Color {
    int exportTextColorTable(lua_State *state);
    int exportBackColorTable(lua_State *state);
    int exportTextFormatTable(lua_State *state);
} //namespace


#endif