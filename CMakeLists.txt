cmake_minimum_required (VERSION 2.8.11)
project(logtool)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

option(UseLua "UseLua" OFF)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Core)
find_package(Qt5SerialPort)

set(BASE_SRC
    app/rs232reader.cpp
    app/logtool.cpp
    app/logcat.cpp
    app/blacklistmanager.cpp
    utils/filereader.cpp
    utils/flog.cpp
    utils/filewatcher.cpp
    utils/linuxfilewatcher.cpp
    utils/outputprinter.cpp
)

if(UseLua)
    add_definitions(-DLUA_ENABLED)
    find_package(Lua)

    if(LUA_FOUND)
        message("Lua [OK]")
    endif(LUA_FOUND)

    set(LUALIBS
        ${LUA_LIBRARIES}
        luautils/luaoutputprinter.cpp
    )
endif(UseLua)

# todo give this some love...

if(UseLua)
    add_executable(logtool main.cpp ${BASE_SRC} ${LUALIBS})
    target_link_libraries(logtool Qt5::Core Qt5::SerialPort ${LUA_LIBRARIES})
else()
    add_executable(logtool main.cpp ${BASE_SRC})
    # Use the Widgets module from Qt 5.
    target_link_libraries(logtool Qt5::Core Qt5::SerialPort)
endif()