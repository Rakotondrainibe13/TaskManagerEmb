cmake_minimum_required(VERSION 3.10)

project(TaskManagerEmb VERSION 1.0 LANGUAGES CXX)

# Set the path to your Qt installation
set(QT_PATH /opt/Qt/6.7.2/gcc_64)

# Find the required Qt packages
set(CMAKE_PREFIX_PATH ${QT_PATH})
find_package(Qt6 REQUIRED COMPONENTS Core Sql Quick)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)


add_subdirectory(src)
add_subdirectory(google_test)
