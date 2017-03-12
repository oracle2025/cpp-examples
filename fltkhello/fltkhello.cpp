#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <dlfcn.h>

void thread_message(void * userdate) {
	std::cout << "Thread Message Received" << std::endl;
}

typedef const char* (*string_from_lib_f)();

int main(int argc, char *argv[])
{
	std::cout << "Hello"  << std::endl;


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



	Fl::lock();
	Fl_Window *window = new Fl_Window(340,180);
	Fl_Box *box = new Fl_Box(20,40,300,100,"Hello, World!");
	box->box(FL_UP_BOX);
	box->labelfont(FL_BOLD+FL_ITALIC);
	box->labelsize(36);
	box->labeltype(FL_SHADOW_LABEL);
	window->end();
	window->show(argc, argv);
	return Fl::run();
}
