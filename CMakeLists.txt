
cmake_minimum_required(VERSION 3.19)

project(Qt6Example VERSION 1.0 LANGUAGES CXX)

# Require C++17 or higher
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 packages
find_package(Qt6 6.9 COMPONENTS Core Widgets REQUIRED)

# Enable automatic moc, uic, and rcc generation
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Add the executable target with your source file(s)
add_executable(Qt6Example main.cpp)

# Link Qt libraries
target_link_libraries(Qt6Example PRIVATE Qt6::Core Qt6::Widgets)
