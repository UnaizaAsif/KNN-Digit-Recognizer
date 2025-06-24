cmake_minimum_required(VERSION 3.10)

# Set the project name and C++ standard
project(KNNNNN)
set(CMAKE_CXX_STANDARD 17)

# Specify the path to SFML
set(SFML_DIR "C:/Users/unaiz/OneDrive/Documents/KNNNNN/External/SFML/lib/cmake/SFML")

# Force 64-bit architecture
set(CMAKE_GENERATOR_PLATFORM x64)

# Find SFML package (adjusted for 64-bit version)
find_package(SFML 2.6 REQUIRED graphics window system)

# Add executable
add_executable(KNNNNN
    src/main.cpp
    src/knn.cpp
)

# Include header files
include_directories(include)

# Link SFML libraries
target_link_libraries(KNNNNN sfml-graphics sfml-window sfml-system)
