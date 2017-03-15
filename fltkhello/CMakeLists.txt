get_filename_component(example ${CMAKE_CURRENT_SOURCE_DIR} NAME)

cmake_minimum_required(VERSION 2.8.11)

project(${exercise} CXX)

include (GenerateExportHeader)


set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.54 REQUIRED COMPONENTS unit_test_framework date_time regex system filesystem)
find_package(FLTK REQUIRED)

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "(GNU|Clang)")
    set(CMAKE_CXX_FLAGS "-std=c++11")
endif()

add_executable(${example}
	${example}.cpp
	reloadingwidget.cpp
	reloadingwidget.h)

target_include_directories(${example} PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries(${example} ${Boost_LIBRARIES} ${FLTK_LIBRARIES})

#add_custom_command(TARGET ${example} POST_BUILD COMMAND ${example})

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${Boost_INCLUDE_DIRS})
add_library(sample SHARED lib.h lib.cpp)
target_link_libraries(sample ${FLTK_LIBRARIES})
generate_export_header(sample)

fltk_wrap_ui(Ui addressbookwidget.fl)
add_library(addressbook SHARED 
	addressbook.h
	addressbook.cpp
	#addressbookwidget.h
	#addressbookwidget.cpp
	${Ui_FLTK_UI_SRCS}
	)
target_link_libraries(addressbook ${FLTK_LIBRARIES})
generate_export_header(addressbook)







