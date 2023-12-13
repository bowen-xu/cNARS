cmake_minimum_required(VERSION 3.16)

set(CMAKE_SH "CMAKE_SH-NOTFOUND")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MACOSX_RPATH OFF)

# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_COMPILER "g++")

project(cNARS)

find_package(Boost 1.45.0)
include_directories(${Boost_INCLUDE_DIRS})
find_package(fmt)
find_package(GTest REQUIRED)

add_subdirectory(pybind11)

message(STATUS pybind11_INCLUDE_DIRS=${pybind11_INCLUDE_DIRS})
message(STATUS pybind11_INCLUDE_DIR=${pybind11_INCLUDE_DIR})

file(GLOB SOURCES_NARSESE Narsese/src/*.cpp)
file(GLOB SOURCES_PARSER Narsese/Parser/*.cpp)
file(GLOB SOURCES_INTERPRETER Interpreter/src/*.cpp)
file(GLOB SOURCES_UTILS utils/*.cpp)
file(GLOB SOURCES_CONFIG Config.cpp Global.cpp)
file(GLOB SOURCES_TEST Tests/*.cpp)
set(SOURCES_NARSESE ${SOURCES_NARSESE} CACHE INTERNAL "Narsese source files")
set(SOURCES_PARSER ${SOURCES_PARSER} CACHE INTERNAL "Parser source files")
set(SOURCES_INTERPRETER ${SOURCES_INTERPRETER} CACHE INTERNAL "Interpreter source files")
set(SOURCES_UTILS ${SOURCES_UTILS} CACHE INTERNAL "Utils source files")
set(SOURCES_CONFIG ${SOURCES_CONFIG} CACHE INTERNAL "Config source files")

pybind11_add_module(narsese Narsese.cpp Narsese/src/Term.cpp ${SOURCES_NARSESE} ${SOURCES_UTILS} ${SOURCES_PARSER} ${SOURCES_CONFIG} ${SOURCES_INTERPRETER})
target_include_directories(narsese PUBLIC
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/Narsese"
    "${PROJECT_SOURCE_DIR}/Narsese/Parser"
    "${PROJECT_SOURCE_DIR}/Interpreter"
    "${PROJECT_SOURCE_DIR}/utils"
)

target_link_libraries(narsese ${Boost_LIBRARIES})
target_link_libraries(narsese PRIVATE fmt::fmt)

add_executable(main main.cpp ${SOURCES_UTILS} ${SOURCES_PARSER} ${SOURCES_CONFIG} ${SOURCES_INTERPRETER} ${SOURCES_NARSESE})

target_include_directories(main PUBLIC
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/Narsese"
    "${PROJECT_SOURCE_DIR}/Narsese/Parser"
    "${PROJECT_SOURCE_DIR}/Interpreter"
    "${PROJECT_SOURCE_DIR}/utils"
    ${pybind11_INCLUDE_DIR}
    ${pybind11_INCLUDE_DIRS}
)

target_link_libraries(main
    ${Boost_LIBRARIES}
    fmt::fmt
    pybind11::module
    pybind11::embed
)

enable_testing()
add_executable(tests Tests/test_parser.cpp ${SOURCES_TEST} ${SOURCES_NARSESE} ${SOURCES_UTILS} ${SOURCES_PARSER} ${SOURCES_CONFIG} ${SOURCES_INTERPRETER})
target_link_libraries(tests
    GTest::gtest_main
    fmt::fmt
    pybind11::module
    pybind11::embed
)
target_include_directories(tests PUBLIC
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/Narsese"
    "${PROJECT_SOURCE_DIR}/Narsese/Parser"
    "${PROJECT_SOURCE_DIR}/Interpreter"
    "${PROJECT_SOURCE_DIR}/utils"
    ${pybind11_INCLUDE_DIR}
    ${pybind11_INCLUDE_DIRS}
)
include(GoogleTest)
gtest_discover_tests(tests)

