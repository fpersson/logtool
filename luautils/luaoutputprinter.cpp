//
// Created by fredrik on 2017-09-20.
//

#include "luaoutputprinter.h"

/**
 * @todo [done] create a lua state
 * @todo [done] bind parsing to lua
 * @todo export all keywords to lua
 * @todo export all colors to lua
 * @todo build demo script
 */

namespace luautils {
    OutputPrinter::OutputPrinter(const QStringList &keywords):m_keywords(keywords){
        m_luaState = luaL_newstate();
        luaL_openlibs(m_luaState);

        int status = luaL_dofile(m_luaState, "./scripts/test.lua"); //@todo remove hardcoded file

        Color::exportTextFormatTable(m_luaState);
        Color::exportBackColorTable(m_luaState);
        Color::exportTextColorTable(m_luaState);

        if(status !=0 ){
            qDebug() << "script not found";
        }

    }

    void OutputPrinter::colorizeOutput(const QString &line) {
        std::string formated_string = "";
        if (line.size() > 1) {
            std::cout << parseInLua(line.toStdString()) << std::endl;
        }
    }

    std::string OutputPrinter::parseInLua(std::string msg) {
        std::string retStr;
        size_t len;

        lua_getglobal(m_luaState, "parseString");
        if(lua_isfunction(m_luaState, -1)){
            lua_pushstring(m_luaState, msg.c_str());
            lua_pcall(m_luaState, 1,1,0);

            const char *cstr = lua_tolstring(m_luaState, -1, &len);
            std::string nstr(cstr, len);
            retStr = nstr;
            lua_pop(m_luaState, 1);
        }else{
            qDebug() << "function parseString not found in script";
        }

        return retStr;
    }

}//namespace