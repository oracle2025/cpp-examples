
FILE(GLOB CPPS "*.cpp")
FILE(GLOB HEADERS "*.h")

add_executable(todolistclient ${CPPS} ${HEADERS})
target_include_directories(todolistclient PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(todolistclient todolist ${Boost_LIBRARIES} ${FLTK_LIBRARIES})

