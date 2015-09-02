#include "todolistwidget.h"
/*#include <iostream>*/
#include <FL/fl_draw.H>
#include <boost/uuid/uuid_generators.hpp>

TodoListWidget::TodoListWidget(int x, int y, int w, int h, const char *label) :
	Fl_Browser_(x, y, w, h, label)
{
	/*type(FL_SELECT_BROWSER);*/
	type(FL_HOLD_BROWSER);
	when(FL_WHEN_RELEASE);
	first = last = selected = 0;

	/*add("Get Milk");
	add("Call Joe");*/

	/*cb_item *p = (cb_item*)malloc(sizeof(cb_item));
	p->next = 0;
	p->prev = 0;
	p->checked = 0;
	p->selected = 0;
	p->text = "Get Milk";

	if (last == 0) {
		first = last = p;
	} else {
		last->next = p;
		p->prev = last;
		last = p;
	}

	p = (cb_item*)malloc(sizeof(cb_item));
	p->next = 0;
	p->prev = 0;
	p->checked = 0;
	p->selected = 0;
	p->text = "Call Joe";

	if (last == 0) {
		first = last = p;
	} else {
		last->next = p;
		p->prev = last;
		last = p;
	}*/
	
}
#define CHECK_SIZE (textsize()-2)
int TodoListWidget::handle(int event)
{
	if (Fl::event_x() < CHECK_SIZE*2) {
		switch (event) {
			case FL_PUSH:
				/*std::cout << "PUSH" << std::endl;*/
				break;
			case FL_DRAG:
				/*std::cout << "DRAG" << std::endl;*/
				break;
			case FL_RELEASE:
				void *l = find_item(Fl::event_y());
				if (l) {
					cb_item *i = (cb_item *)l;
					if (i->checked) {
						i->checked = 0;
					} else {
						i->checked = 1;
					}
					redraw_line(l);
				}
				/*std::cout << "RELEASE " << Fl::event_x() << " " << CHECK_SIZE << std::endl;*/
				break;
		}
	}
	return Fl_Browser_::handle(event);
}
int TodoListWidget::item_height(void *) const
{
    return textsize() + 2;
}

int TodoListWidget::item_selected(void *v) const
{
	cb_item *i = (cb_item *)v;
	return i->selected;
}

int TodoListWidget::item_width(void *v) const
{
	fl_font(textfont(), textsize());
	return int(fl_width(((cb_item *)v)->text.c_str())) + CHECK_SIZE + 8;
}

void *TodoListWidget::item_first() const
{
	return first;
}

void *TodoListWidget::item_next(void *l) const
{
	return ((cb_item *)l)->next;
}

void *TodoListWidget::item_prev(void *l) const
{
	return ((cb_item *)l)->prev;
}

void TodoListWidget::item_select(void *v, int state)
{
	cb_item *i = (cb_item *)v;

	i->selected = state;
	if (state) {
		selected = i;
	} else {
		selected = 0;
	}
	/*if (state) {
		if (i->selected) {
			i->selected = 0;
		} else {
			i->selected = 1;
		}
	}*/
}

void TodoListWidget::setTodoList(TodoList::pointer todolist)
{
	m_todolist = todolist;
}

void TodoListWidget::item_draw(void *v, int X, int Y, int W, int H) const
{
	cb_item *i = (cb_item *)v;
	const char *s = i->text.c_str();
	int tsize = textsize();
	Fl_Color col = active_r() ? textcolor() : fl_inactive(textcolor());
	int cy = Y + (tsize + 1 - CHECK_SIZE) / 2;
	X += 2;

	fl_color(active_r() ? FL_FOREGROUND_COLOR : fl_inactive(FL_FOREGROUND_COLOR));
	if (i->selected) {
		col = fl_contrast(col, selection_color());
	}
	fl_color(col);
	fl_loop(X, cy, X, cy + CHECK_SIZE,
	        X + CHECK_SIZE, cy + CHECK_SIZE, X + CHECK_SIZE, cy);
	if (i->checked) {
	  int tx = X + 3;
	  int tw = CHECK_SIZE - 4;
	  int d1 = tw/3;
	  int d2 = tw-d1;
	  int ty = cy + (CHECK_SIZE+d2)/2-d1-2;
	  for (int n = 0; n < 3; n++, ty++) {
	    fl_line(tx, ty, tx+d1, ty+d1);
	    fl_line(tx+d1, ty+d1, tx+tw-1, ty+d1-d2+1);
	  }
	}
	fl_font(textfont(), tsize);
	fl_draw(s, X + CHECK_SIZE + 8, Y + tsize - 1);
}



boost::uuids::uuid TodoListWidget::value() const
{
	if (selected) {
		return selected->id;
	}
    return boost::uuids::nil_uuid();
    //uuid.is_null();
    //uuid.is_nil();
}

std::string TodoListWidget::text(boost::uuids::uuid line) const
{
	if (ids_to_items_.find(line) == ids_to_items_.end()) {
    	return std::string();
	}
	cb_item *p = ids_to_items_.at(line);
	return p->text;
}

void TodoListWidget::add(const std::string& value)
{
	cb_item *p = new cb_item;
	p->next = 0;
	p->prev = 0;
	p->checked = 0;
	p->selected = 0;
	p->text = value;
	p->id = boost::uuids::random_generator()();
	p->created_at = boost::posix_time::microsec_clock::universal_time();
	if (last) {
		last->next = p;
		p->prev = last;
		last = p;
	} else {
		first = last = p;
	}
	ids_to_items_[p->id] = p;
	redraw_line(p);
}

void TodoListWidget::remove(boost::uuids::uuid line)
{
	if (ids_to_items_.find(line) == ids_to_items_.end()) {
		return;
	}
	cb_item *p = ids_to_items_.at(line);
	deleting(p);
	if (p->prev) {
		p->prev->next = p->next;
	} else {
		first = p->next;
	}

	if (!p->next) {
		last = p->prev;
	}
	if (selected == p) {
		selected = 0;
	}
	ids_to_items_.erase(ids_to_items_.find(line));
	delete p;
}

void TodoListWidget::text(boost::uuids::uuid line, const std::string& value)
{
	if (ids_to_items_.find(line) == ids_to_items_.end()) {
		return;
	}
	cb_item *p = ids_to_items_.at(line);
	p->text = value;
	redraw_line(p);
}

