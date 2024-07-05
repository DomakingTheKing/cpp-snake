cmake_minimum_required(VERSION 3.28)
project(cpp_snake)

set(CMAKE_CXX_STANDARD 20)

# Add the relative path of the directory containing the modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")

add_executable(cpp_snake
        src/main.cpp
        src/Engine.cpp
        headers/Engine.hpp
        src/draw.cpp
        src/input.cpp
        src/snakesection.cpp
        headers/snakesection.hpp
        src/update.cpp
        src/apple.cpp
        headers/apple.hpp
        src/wall.cpp
        headers/wall.hpp
        src/soundengine.cpp
        headers/soundengine.hpp
        src/particles.cpp
        headers/particles.hpp
)

include_directories(headers /usr/include c:/SFML/include)

# Find OpenCV package
find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
    target_link_libraries(cpp_snake ${OpenCV_LIBS})
    message(STATUS "OpenCV Include Dirs: ${OpenCV_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "OpenCV not found!")
endif()

# Find SFML package
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(cpp_snake ${SFML_LIBRARIES})
    message(STATUS "SFML Include Dir: ${SFML_INCLUDE_DIR}")
else()
    message(FATAL_ERROR "SFML not found!")
endif()

# Copy assets to the build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

# Copy DLLs to build directory
if(WIN32)
    # Assuming SFML and OpenCV DLLs are in their respective bin directories
    file(GLOB SFML_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(GLOB OPENCV_DLLS "${OpenCV_DIR}/../bin/*.dll")
    list(APPEND BINARY_DEP_DLLS ${SFML_DLLS} ${OPENCV_DLLS})

    # Debug messages
    message(STATUS "SFML DLLs: ${SFML_DLLS}")
    message(STATUS "OpenCV DLLs: ${OPENCV_DLLS}")

    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()

message(STATUS "CMake Source Dir: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMake Binary Dir: ${CMAKE_BINARY_DIR}")
