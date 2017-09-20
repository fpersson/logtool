//
// Created by fredrik on 2017-09-20.
//

#include "luaunixcolor.h"
namespace Color {
    int exportTextColorTable(lua_State *state){
        //text_color
        int nobjects = 16; //should be size of array
        lua_createtable(state, 0, nobjects);

        lua_pushstring(state, Text::Default.c_str());
        lua_setfield(state, -2, "Default");

        lua_pushstring(state, Text::Black.c_str());
        lua_setfield(state, -2, "Black");

        lua_pushstring(state, Text::Red.c_str());
        lua_setfield(state, -2, "Red");

        lua_pushstring(state, Text::Green.c_str());
        lua_setfield(state, -2, "Green");

        lua_pushstring(state, Text::Green.c_str());
        lua_setfield(state, -2, "Green");

        lua_pushstring(state, Text::Yellow.c_str());
        lua_setfield(state, -2, "Yellow");

        lua_pushstring(state, Text::Blue.c_str());
        lua_setfield(state, -2, "Blue");

        lua_pushstring(state, Text::Magenta.c_str());
        lua_setfield(state, -2, "Magenta");

        lua_pushstring(state, Text::Cyan.c_str());
        lua_setfield(state, -2, "Cyan");

        lua_pushstring(state, Text::LightGray.c_str());
        lua_setfield(state, -2, "LightGray");

        lua_pushstring(state, Text::DarkGray.c_str());
        lua_setfield(state, -2, "DarkGray");

        lua_pushstring(state, Text::LightRed.c_str());
        lua_setfield(state, -2, "LightRed");

        lua_pushstring(state, Text::LightGreen.c_str());
        lua_setfield(state, -2, "LightGreen");

        lua_pushstring(state, Text::LightYellow.c_str());
        lua_setfield(state, -2, "LightYellow");

        lua_pushstring(state, Text::LightBlue.c_str());
        lua_setfield(state, -2, "LightBlue");

        lua_pushstring(state, Text::LightMagenta.c_str());
        lua_setfield(state, -2, "LightMagenta");

        lua_pushstring(state, Text::LightCyan.c_str());
        lua_setfield(state, -2, "LightCyan");

        lua_pushstring(state, Text::White.c_str());
        lua_setfield(state, -2, "White");

        lua_setglobal(state, "Text");

        return 1;
    }

    int exportBackColorTable(lua_State *state){
        //text_color
        int nobjects = 16; //should be size of array
        lua_createtable(state, 0, nobjects);

        lua_pushstring(state, Background::Default.c_str());
        lua_setfield(state, -2, "Default");

        lua_pushstring(state, Background::Black.c_str());
        lua_setfield(state, -2, "Black");

        lua_pushstring(state, Background::Red.c_str());
        lua_setfield(state, -2, "Red");

        lua_pushstring(state, Background::Green.c_str());
        lua_setfield(state, -2, "Green");

        lua_pushstring(state, Background::Green.c_str());
        lua_setfield(state, -2, "Green");

        lua_pushstring(state, Background::Yellow.c_str());
        lua_setfield(state, -2, "Yellow");

        lua_pushstring(state, Background::Blue.c_str());
        lua_setfield(state, -2, "Blue");

        lua_pushstring(state, Background::Magenta.c_str());
        lua_setfield(state, -2, "Magenta");

        lua_pushstring(state, Background::Cyan.c_str());
        lua_setfield(state, -2, "Cyan");

        lua_pushstring(state, Background::LightGray.c_str());
        lua_setfield(state, -2, "LightGray");

        lua_pushstring(state, Background::DarkGray.c_str());
        lua_setfield(state, -2, "DarkGray");

        lua_pushstring(state, Background::LightRed.c_str());
        lua_setfield(state, -2, "LightRed");

        lua_pushstring(state, Background::LightGreen.c_str());
        lua_setfield(state, -2, "LightGreen");

        lua_pushstring(state, Background::LightYellow.c_str());
        lua_setfield(state, -2, "LightYellow");

        lua_pushstring(state, Background::LightBlue.c_str());
        lua_setfield(state, -2, "LightBlue");

        lua_pushstring(state, Background::LightMagenta.c_str());
        lua_setfield(state, -2, "LightMagenta");

        lua_pushstring(state, Background::LightCyan.c_str());
        lua_setfield(state, -2, "LightCyan");

        lua_pushstring(state, Background::White.c_str());
        lua_setfield(state, -2, "White");

        lua_setglobal(state, "Background");

        return 1;
    }

    int exportTextFormatTable(lua_State *state){
        //text_color
        int nobjects = 7; //should be size of array
        lua_createtable(state, 0, nobjects);

        lua_pushstring(state, Format::Reset.c_str());
        lua_setfield(state, -2, "Reset");

        lua_pushstring(state, Format::Bold.c_str());
        lua_setfield(state, -2, "Bold");

        lua_pushstring(state, Format::Dim.c_str());
        lua_setfield(state, -2, "Dim");

        lua_pushstring(state, Format::UnderLine.c_str());
        lua_setfield(state, -2, "UnderLine");

        lua_pushstring(state, Format::Blink.c_str());
        lua_setfield(state, -2, "Blink");

        lua_pushstring(state, Format::Invert.c_str());
        lua_setfield(state, -2, "Invert");

        lua_pushstring(state, Format::Hidden.c_str());
        lua_setfield(state, -2, "Hidden");

        lua_setglobal(state, "TextFormat");

        return 1;
    }

} //namespace