#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <dlfcn.h>
#include <boost/filesystem/operations.hpp>
#include "reloadingwidget.h"

void thread_message(void * userdate) {
	std::cout << "Thread Message Received" << std::endl;
}

typedef const char* (*string_from_lib_f)();
typedef void* (*get_widget_f)();

std::time_t last_modified;

void callback(void*) {
	//std::cout << "Tick" << std::endl;

	boost::filesystem::path p("libsample.dylib");
	std::time_t t = boost::filesystem::last_write_time( p ) ;
	if (t != last_modified) {
		std::cout << "On " << std::ctime( &t ) << std::endl;
		last_modified = t;
	}


	Fl::repeat_timeout(1.0, callback);    // retrigger timeout
}

int main(int argc, char *argv[])
{
	std::cout << "Hello"  << std::endl;

	boost::filesystem::path p("libsample.dylib");
	last_modified  = boost::filesystem::last_write_time( p ) ;

	const char* libfilename = "libsample.dylib";

	auto handle = dlopen(libfilename, RTLD_LAZY);

	if (!handle) {
		std::cout << dlerror() << std::endl;
		return -1;
	}

	auto symbol = (string_from_lib_f)dlsym(handle, "string_from_lib");
	if (!symbol) {
		std::cout << "string_from_lib not found" << std::endl;
	}

	std::cout << symbol() << std::endl;

	auto get_widget = (get_widget_f)dlsym(handle, "get_widget");



	Fl::lock();
	Fl_Window *window = new Fl_Window(1200,600);
	
	//Fl_Widget *widget = (Fl_Widget*)get_widget();
	Fl_Widget *widget = new ReloadingWidget("libaddressbook.dylib", 0, 0, window->w(), window->h());

	/*Fl_Box *box = new Fl_Box(20,40,300,100,"Hello, World!");
	box->box(FL_UP_BOX);
	box->labelfont(FL_BOLD+FL_ITALIC);
	box->labelsize(36);
	box->labeltype(FL_SHADOW_LABEL);*/
	window->end();
	window->show(argc, argv);
	Fl::add_timeout(1.0, callback);       // set up first timeout
	return Fl::run();
}
