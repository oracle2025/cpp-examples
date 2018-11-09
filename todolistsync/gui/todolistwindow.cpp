#include "todolistwindow.h"
#include <FL/Fl_Button.H>
#include <FL/fl_ask.H>
#include "todolistwidget.h"


static void cb_add_button(Fl_Widget *w, void *t)
{
	((TodoListWindow*)t)->cbAddButton(w);
}
static void cb_edit_button(Fl_Widget *w, void *t)
{
	((TodoListWindow*)t)->cbEditButton(w);
}
static void cb_delete_button(Fl_Widget *w, void *t)
{
	((TodoListWindow*)t)->cbDeleteButton(w);
}
static void cb_list_view(Fl_Widget *w, void *t)
{
	((TodoListWindow*)t)->cbListView(w);
}
static void cb_window(Fl_Widget *w, void *t)
{
	((TodoListWindow*)t)->cbWindow(w);
}

TodoListWindow::TodoListWindow(int w, int h, const char* title) :
	Fl_Window(480, 640, title)
{
	m_add_button = new Fl_Button(0, 0, 480, 25, "Add Entry");

	m_list_view = new TodoListWidget(0, 25, 480, 590);

	m_edit_button = new Fl_Button(0, 615, 240, 25, "Edit Entry");

	m_delete_button = new Fl_Button(240, 615, 240, 25, "Delete Entry");

	m_add_button->callback(cb_add_button, this);
	m_delete_button->callback(cb_delete_button, this);
	m_edit_button->callback(cb_edit_button, this);
	m_list_view->callback(cb_list_view, this);
	callback(cb_window, this);

	m_edit_button->deactivate();
	m_delete_button->deactivate();

	resizable(m_list_view);

	end();
}

TodoListWindow::~TodoListWindow()
{
}

void TodoListWindow::cbAddButton(Fl_Widget* w)
{
	const char *result;
	result = fl_input("Add Entry:", "");
	if (!result) {
		return;
	}
	if (std::string(result).empty()) {
		return;
	}
	m_list_view->add(result);
}

void TodoListWindow::cbDeleteButton(Fl_Widget* w)
{
	TodoListWidget::line_t line = m_list_view->value();
	if (line.is_nil()) {
		return;
	}
	if (fl_choice("Delete Entry: \n%s", "No, Cancel", "Yes, Delete!", 0, m_list_view->text(line).c_str())) {
		m_list_view->remove(line);
		cbListView(m_list_view);
	}
}

void TodoListWindow::cbEditButton(Fl_Widget* w)
{
	TodoListWidget::line_t line = m_list_view->value();
	if (line.is_nil()) {
		return;
	}
	const char *result;
	result = fl_input("Edit Entry:", m_list_view->text(line).c_str());
	if (!result) {
		return;
	}
	if (std::string(result).empty()) {
		return;
	}

	m_list_view->text(line, result);
}

void TodoListWindow::cbListView(Fl_Widget* w)
{
	if (!m_list_view->value().is_nil()) {
		m_edit_button->activate();
		m_delete_button->activate();
	} else {
		m_edit_button->deactivate();
		m_delete_button->deactivate();
	}
}

void TodoListWindow::cbWindow(Fl_Widget* w)
{
	hide();
}
TodoListWidget *TodoListWindow::todoListWidget() const
{
    return m_list_view;
}

