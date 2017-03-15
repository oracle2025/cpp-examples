#include "reloadingwidget.h"
#include <dlfcn.h>
#include <iostream>
#include <boost/filesystem/operations.hpp>
#include <FL/Fl_Window.H>

typedef void* (*get_widget_f)(int x, int y, int w, int h);

static void reloading_widget_timeout_callback(void* p)
{
	((ReloadingWidget*)p)->timeout();
}

ReloadingWidget::ReloadingWidget(const char* dylibfilename, int x, int y, int w, int h) :
	Fl_Group(x, y, w, h),
	m_dylibfilename(dylibfilename),
	m_handle(nullptr)
{
	load_widget();

	end();

	boost::filesystem::path p(m_dylibfilename);
	m_last_modified = boost::filesystem::last_write_time( p ) ;

	Fl::add_timeout(1.0, reloading_widget_timeout_callback, this);
}
ReloadingWidget::~ReloadingWidget()
{
	dlclose(m_handle);
}
void ReloadingWidget::timeout()
{
	boost::filesystem::path p(m_dylibfilename);
	std::time_t t = boost::filesystem::last_write_time( p ) ;
	if (t != m_last_modified) {
		std::cout << "On " << std::ctime( &t ) << std::endl;
		m_last_modified = t;

		remove(m_widget);
		delete m_widget; m_widget = nullptr;

		begin();
		load_widget();
		end();
		window()->redraw();
	}

	Fl::repeat_timeout(1.0, reloading_widget_timeout_callback, this);
}
void ReloadingWidget::load_widget()
{
	if (m_handle) {
		dlclose(m_handle);
		m_handle = nullptr;
	}
	m_handle = dlopen(m_dylibfilename.c_str(), RTLD_LAZY);

	if (!m_handle) {
		std::cout << dlerror() << std::endl;
		return;
	}


	auto get_widget = (get_widget_f)dlsym(m_handle, "get_widget");
	if (!get_widget) {
		std::cout << "get_widget not found" << std::endl;
	}

	m_widget = (Fl_Widget*)get_widget(0, 0, w(), h());
}

