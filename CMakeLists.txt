cmake_minimum_required(VERSION 3.10)
find_package(Boost)
project(test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/include)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()

file(GLOB repl_FILES *.cpp include/*.hpp)
if(XCODE)
    add_executable(main.out ${repl_FILES})
else()
    add_executable(main.out main.cpp)
endif()

add_custom_target(run
    COMMAND echo "Will run main!\\n--------------"
    COMMAND main.out
    COMMAND echo "--------------"
    DEPENDS main.out
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
    VERBATIM
)
