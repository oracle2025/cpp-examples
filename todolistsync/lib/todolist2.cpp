#include "todolist2.h"



TodoList2::TodoList2(const std::string& server)
{
}

TodoList2::pointer TodoList2::create(const std::string &server)
{
    return /* something */;
}

void TodoList2::from_connection(Command::pointer cmd)
{
}

void TodoList2::from_display(Command::pointer cmd)
{
}

void TodoList2::setDisplay(ITodoListDisplay *display)
{
}

