cmake_minimum_required(VERSION 2.8.9)
project(qthello)

add_definitions(-std=c++11 -Wall)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Quick)

add_executable(qthello
	qthello.cpp
	)
target_include_directories(qthello PRIVATE
	${Qt5Widgets_INCLUDE_DIRS}
	)
target_link_libraries(qthello
	Qt5::Core
	Qt5::Widgets
	)
