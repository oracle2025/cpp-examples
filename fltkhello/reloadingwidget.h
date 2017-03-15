#ifndef _RELOADINGWIDGET_H_
#define _RELOADINGWIDGET_H_

#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <string>
#include <ctime>

class ReloadingWidget : public Fl_Group
{
	public:
		ReloadingWidget(const char* dylibfilename, int x, int y, int w, int h);
		~ReloadingWidget();

		void timeout();
	private:
		void load_widget();
		std::string m_dylibfilename;
		void *m_handle;
		Fl_Widget *m_widget;
		std::time_t m_last_modified;
};

#endif /* _RELOADINGWIDGET_H_ */
