#include <iostream>
#include <string>
#include "todolist.h"
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>


/*
 * "Over the Wire" Format:
 *
 * ecb9be51-1b6b-4571-a067-1627308b8191;2015-08-19T14:07:51.046841;a;11;Hello World
 * id;timestamp;command;length;string
 * length and string are optional (or rather, only for commands that need it
 *
 * a ... add (has string)
 * r ... remove
 * e ... edit (has string)
 * c ... check
 * u ... uncheck
 */

int main(int argc, const char *argv[])
{
	TodoList::pointer todo_list = TodoList::create();

	TodoList::id id_milk = todo_list->add("Get Milk");
	TodoList::id id_lettre = todo_list->add("Send Lettre");
	TodoList::id id_call = todo_list->add("Call Sam");

	for (auto i : todo_list->ids()) {
		std::cout 
			<< boost::lexical_cast<std::string>(i) << ": " 
			<< todo_list->get(i) << std::endl;
	}

	todo_list->edit(id_lettre, "Send Lettre to Sam");
	todo_list->remove(id_call);
	todo_list->check(id_lettre);

	//send log to server?

	
	return 0;
}
