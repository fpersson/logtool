cmake_minimum_required (VERSION 2.8.11)
project(logtool)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Core)
find_package(Qt5SerialPort)

# todo give this some love...
add_executable(logtool main.cpp utils/filereader.cpp utils/flog.cpp app/rs232reader.cpp app/logtool.cpp app/logcat.cpp app/blacklistmanager.cpp utils/filewatcher.cpp utils/linuxfilewatcher.cpp utils/outputprinter.cpp)
# Use the Widgets module from Qt 5.
target_link_libraries(logtool Qt5::Core Qt5::SerialPort)
