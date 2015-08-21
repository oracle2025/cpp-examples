#include <iostream>
#include "todolistserver.h"

int main(int argc, const char *argv[])
{
	std::cout << "TodoList Server" << std::endl;

	TodoListServer::pointer server = TodoListServer::create();
	server->start();

	return 0;
}
