cmake_minimum_required (VERSION 2.8.11)
project(logtool)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Core)

# Tell CMake to create the helloworld executable
add_executable(logtool main.cpp utils/filereader.cpp utils/flog.cpp app/logcat.cpp utils/filewatcher.cpp utils/linuxfilewatcher.cpp)

# Use the Widgets module from Qt 5.
target_link_libraries(logtool Qt5::Core)
