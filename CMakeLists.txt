cmake_minimum_required(VERSION 3.16)

set( CMAKE_CXX_COMPILER "g++" )
set( CMAKE_SH "CMAKE_SH-NOTFOUND" )
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_BUILD_TYPE Debug)

project(cNARS)

find_package(Boost 1.45.0 COMPONENTS spirit) 
include_directories(${Boost_INCLUDE_DIRS}) 


file(GLOB SOURCES_NARSESE Narsese/src/*.cpp )
file(GLOB SOURCES_PARSER Narsese/Parser/*.cpp )
file(GLOB SOURCES_UTILS utils/*.cpp )
file(GLOB SOURCES_CONFIG *.cpp )

add_executable(main main.cpp ${SOURCES_NARSESE} ${SOURCES_UTILS} ${SOURCES_PARSER} ${SOURCES_CONFIG})


target_include_directories(main PUBLIC
"${PROJECT_SOURCE_DIR}"
"${PROJECT_SOURCE_DIR}/Narsese"
"${PROJECT_SOURCE_DIR}/Narsese/Parser"
"${PROJECT_SOURCE_DIR}/utils"
)
target_link_libraries(main ${Boost_LIBRARIES})
