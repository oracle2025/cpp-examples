#include <iostream>
#include <string>
#include "todolist.h"
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>


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


	
	return 0;
}
