
FILE(GLOB CPPS "*.cpp")
FILE(GLOB HEADERS "*.h")

add_executable(todolistgui ${CPPS} ${HEADERS})
target_include_directories(todolistgui PRIVATE ${Boost_INCLUDE_DIRS} ../lib)
target_link_libraries(todolistgui todolist ${Boost_LIBRARIES} ${FLTK_LIBRARIES})

