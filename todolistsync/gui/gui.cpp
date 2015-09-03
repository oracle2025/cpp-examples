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

TodoListWidget *g_list_view;
Fl_Button *g_edit_button;
Fl_Button *g_delete_button;

void add_cb(Fl_Widget*, void*)
{
	const char *result;
	result = fl_input("Add Entry:", "");
	if (!result) {
		return;
	}
	if (std::string(result).empty()) {
		return;
	}

	g_list_view->add(result);
}

void edit_cb(Fl_Widget*, void*)
{
	TodoListWidget::line_t line = g_list_view->value();
	if (line.is_nil()) {
		return;
	}
	const char *result;
	result = fl_input("Edit Entry:", g_list_view->text(line).c_str());
	if (!result) {
		return;
	}
	if (std::string(result).empty()) {
		return;
	}

	g_list_view->text(line, result);
}
void list_view_cb(Fl_Widget*, void*);
void delete_cb(Fl_Widget*, void*)
{
	TodoListWidget::line_t line = g_list_view->value();
	if (line.is_nil()) {
		return;
	}
	if (fl_choice("Delete Entry: \n%s", "No, Cancel", "Yes, Delete!", 0, g_list_view->text(line).c_str())) {
		g_list_view->remove(line);
		list_view_cb(g_list_view, 0);
	}
}
void list_view_cb(Fl_Widget*, void*)
{
	if (!g_list_view->value().is_nil()) {
		g_edit_button->activate();
		g_delete_button->activate();
	} else {
		g_edit_button->deactivate();
		g_delete_button->deactivate();
	}
}
void window_cb(Fl_Widget* w, void*)
{
	/*{
		std::ofstream todofile;
		todofile.open(std::string(getenv("HOME"))+"/.todolist");
		for (int i = 1; i <= g_list_view->size(); i++) {
			todofile << g_list_view->text(i) << std::endl;
		}
		todofile.close();
	}*/

	Fl_Window *window = dynamic_cast<Fl_Window*>(w);
	window->hide();
}

int main(int argc, char *argv[])
{
	Fl_Window *window = new Fl_Window(480, 640);

	/*TodoListWidget *list = new TodoListWidget(0, 0, 480, 640);
	list->setTodoList(TodoList::create("localhost"));
	list->add("Get Milk");
	list->add("Call Joe");
	window->resizable(list);
	window->end();
	window->show(argc, argv);
	
	return Fl::run();*/
	
	Fl_Button *add_button = new Fl_Button(0, 0, 480, 25, "Add Entry");

	//Fl_Browser *list_view = g_list_view = new Fl_Hold_Browser(0, 25, 480, 590);
	TodoListWidget *list_view = g_list_view = new TodoListWidget(0, 25, 480, 590);

	TodoList::pointer todolist = TodoList::create("localhost");
	//todolist->run();
	std::thread t([todolist](){ todolist->run(); });

	list_view->setTodoList(todolist);

	Fl_Button *edit_button = g_edit_button = new Fl_Button(0, 615, 240, 25, "Edit Entry");

	Fl_Button *delete_button = g_delete_button = new Fl_Button(240, 615, 240, 25, "Delete Entry");

	add_button->callback(add_cb);
	edit_button->callback(edit_cb);
	delete_button->callback(delete_cb);
	window->callback(window_cb);

	edit_button->deactivate();
	delete_button->deactivate();

	/*{
		std::string line;
		std::ifstream todofile(std::string(getenv("HOME"))+"/.todolist");
		if (todofile.is_open()) {
			while (getline(todofile, line)) {
				g_list_view->add(line.c_str());
			}
			todofile.close();
		}
	}*/

	list_view->callback(list_view_cb);
	/* The following works, but it cannot capture variables, ... */
	/*list_view->callback(
			[](Fl_Widget*, void*) {
				if (g_list_view->value()) {
					g_edit_button->activate();
					g_delete_button->activate();
				} else {
					g_edit_button->deactivate();
					g_delete_button->deactivate();
				}
			});*/

	window->resizable(list_view);

	window->end();

	window->show(argc, argv);

	int result = Fl::run();

	todolist->close();
	t.join();
	
	return result;
}
