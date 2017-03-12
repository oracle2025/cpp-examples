get_filename_component(example ${CMAKE_CURRENT_SOURCE_DIR} NAME)

cmake_minimum_required(VERSION 2.8.11)

project(${exercise} CXX)

include (GenerateExportHeader)


set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.54 REQUIRED COMPONENTS unit_test_framework date_time regex system)
find_package(FLTK REQUIRED)

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "(GNU|Clang)")
    set(CMAKE_CXX_FLAGS "-std=c++11")
endif()

add_executable(${example} ${example}.cpp)

target_include_directories(${example} PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries(${example} ${Boost_LIBRARIES} ${FLTK_LIBRARIES})

#add_custom_command(TARGET ${example} POST_BUILD COMMAND ${example})

include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_library(sample SHARED lib.h lib.cpp)
generate_export_header(sample)








