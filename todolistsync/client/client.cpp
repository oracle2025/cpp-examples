#include <iostream>
#include "todolist.h"
#include "todolistclient.h"

int main(int argc, const char *argv[])
{
	std::cout << "TodoList Client" << std::endl;

	/*TodoListClient::pointer client = TodoListClient::create("localhost");
	client->send("ecb9be51-1b6b-4571-a067-1627308b8191;20150820T090315.190570;a;11;Helle World");*/

	TodoList::pointer todo_list = TodoList::create("localhost");
	//Add a client id uuid to each command?

	TodoList::id id_milk = todo_list->add("Get Milk");
	TodoList::id id_lettre = todo_list->add("Send Lettre");
	TodoList::id id_call = todo_list->add("Call Sam");

	todo_list->edit(id_lettre, "Send Lettre to Sam");
	todo_list->remove(id_call);
	todo_list->check(id_lettre);

	return 0;
}
