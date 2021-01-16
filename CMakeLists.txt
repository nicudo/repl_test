cmake_minimum_required(VERSION 3.10)
find_package(Boost)
# set the project name
project(test)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(main.out main.cpp)

add_custom_target(run
    COMMAND echo "Will run main!\\n--------------"
    COMMAND main.out
    COMMAND echo "--------------"
    DEPENDS main.out
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
    VERBATIM
)