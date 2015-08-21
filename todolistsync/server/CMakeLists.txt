
FILE(GLOB CPPS "*.cpp")
FILE(GLOB HEADERS "*.h")

add_executable(todolistserver ${CPPS} ${HEADERS})
target_include_directories(todolistserver PRIVATE ${Boost_INCLUDE_DIRS} ../lib)
target_link_libraries(todolistserver todolist ${Boost_LIBRARIES} ${FLTK_LIBRARIES})

