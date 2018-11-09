get_filename_component(example ${CMAKE_CURRENT_SOURCE_DIR} NAME)

cmake_minimum_required(VERSION 2.8.11)

project(${example} CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (CMAKE_CXX_STANDARD 11)

FILE(GLOB CPPS "*.cpp")
FILE(GLOB HEADERS "*.h")

#add_executable(${example} ${example}.cpp)
add_executable(${example} ${CPPS} ${HEADERS})

#target_include_directories(${example} PRIVATE ${Boost_INCLUDE_DIRS})

#target_link_libraries(${example} ${Boost_LIBRARIES} ${FLTK_LIBRARIES})

#add_custom_command(TARGET ${example} POST_BUILD COMMAND ${example})

