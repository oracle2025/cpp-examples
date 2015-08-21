
FILE(GLOB CPPS "*.cpp")
FILE(GLOB HEADERS "*.h")

add_library(todolist STATIC ${CPPS} ${HEADERS})
target_include_directories(todolist PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(todolist ${Boost_LIBRARIES} ${FLTK_LIBRARIES})
