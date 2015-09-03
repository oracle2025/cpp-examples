#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Hold_Browser.H>
#include <FL/fl_ask.H>
#include <string>
#include <iostream>
#include <fstream>
#include <thread>
#include "todolistwidget.h"
#include "todolistwindow.h"

int main(int argc, char *argv[])
{

	Fl::lock();

	TodoListWindow *w = new TodoListWindow(480, 640);

	TodoList::pointer todolist = TodoList::create("localhost");
	std::thread t([todolist](){ todolist->run(); });

	/*list_view->setTodoList(todolist);*/

	w->show(argc, argv);

	int result = Fl::run();

	todolist->close();
	t.join();
	
	return result;
}
