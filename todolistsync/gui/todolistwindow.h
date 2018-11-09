#ifndef _TODO_LIST_WINDOW_H_
#define _TODO_LIST_WINDOW_H_

#include <FL/Fl_Window.H>

class TodoListWidget;
class Fl_Button;

class TodoListWindow : public Fl_Window
{
public:
	TodoListWindow(int w, int h, const char* title = 0);
	~TodoListWindow();

	void cbAddButton(Fl_Widget* w);
	void cbEditButton(Fl_Widget* w);
	void cbDeleteButton(Fl_Widget* w);
	void cbWindow(Fl_Widget* w);
	void cbListView(Fl_Widget* w);

	TodoListWidget *todoListWidget() const;

private:
	TodoListWidget *m_list_view;
	Fl_Button *m_add_button;
	Fl_Button *m_edit_button;
	Fl_Button *m_delete_button;

};

#endif /* _TODO_LIST_WINDOW_H_ */
