#include <iostream>
#include <thread>
#include "todolist.h"
#include "todolistclient.h"

int main(int argc, const char *argv[])
{
	std::cout << "TodoList Client" << std::endl;

	/*TodoListClient::pointer client = TodoListClient::create("localhost");
	client->send("ecb9be51-1b6b-4571-a067-1627308b8191;20150820T090315.190570;a;11;Helle World");*/

	TodoList::pointer todo_list = TodoList::create("localhost");
	//Add a client id uuid to each command?
	//
	//Get List from Server and display it.
	
	//std::thread t([todo_list](){ todo_list->run(); });

	todo_list->sync();
	todo_list->run();
	// Can only be started, when connect is finished!
	//todo_list->sync(); // <-- Fetches List from Server

/*	TodoList::id id_milk = todo_list->add("Get Milk");
	TodoList::id id_lettre = todo_list->add("Send Lettre");
	TodoList::id id_call = todo_list->add("Call Sam");

	todo_list->edit(id_lettre, "Send Lettre to Sam");
	todo_list->remove(id_call);
	todo_list->check(id_lettre);*/

	//well, cout try a todo_list->m_client->run() here??
	//t.join();

	return 0;
}
