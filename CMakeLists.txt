cmake_minimum_required(VERSION 3.16)

set( CMAKE_CXX_COMPILER "g++" )
set( CMAKE_SH "CMAKE_SH-NOTFOUND" )
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_BUILD_TYPE Debug)

project(cNARS)

find_package(Boost 1.45.0 COMPONENTS spirit) 
include_directories(${Boost_INCLUDE_DIRS})
find_package(fmt)
find_package(GTest REQUIRED)


file(GLOB SOURCES_NARSESE Narsese/src/*.cpp )
file(GLOB SOURCES_PARSER Narsese/Parser/*.cpp )
file(GLOB SOURCES_INTERPRETER Interpreter/src/*.cpp )
file(GLOB SOURCES_UTILS utils/*.cpp )
file(GLOB SOURCES_CONFIG Config.cpp Global.cpp)
file(GLOB SOURCES_TEST Tests/*.cpp )

add_executable(main main.cpp ${SOURCES_NARSESE} ${SOURCES_UTILS} ${SOURCES_PARSER} ${SOURCES_CONFIG} ${SOURCES_INTERPRETER})


target_include_directories(main PUBLIC
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/Narsese"
    "${PROJECT_SOURCE_DIR}/Narsese/Parser"
    "${PROJECT_SOURCE_DIR}/Interpreter"
    "${PROJECT_SOURCE_DIR}/utils"
)
target_link_libraries(main ${Boost_LIBRARIES})
target_link_libraries(main fmt::fmt)

enable_testing()
add_executable(tests Tests/test_parser.cpp ${SOURCES_TEST} ${SOURCES_NARSESE} ${SOURCES_UTILS} ${SOURCES_PARSER} ${SOURCES_CONFIG} ${SOURCES_INTERPRETER})
target_link_libraries(tests GTest::gtest_main)
target_link_libraries(tests fmt::fmt)
target_include_directories(tests PUBLIC
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/Narsese"
    "${PROJECT_SOURCE_DIR}/Narsese/Parser"
    "${PROJECT_SOURCE_DIR}/Interpreter"
    "${PROJECT_SOURCE_DIR}/utils"
)
include(GoogleTest)
gtest_discover_tests(tests)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")