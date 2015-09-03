#ifndef _TODO_LIST_WIDGET_H_
#define _TODO_LIST_WIDGET_H_

#include <FL/Fl_Browser_.H>
#include "todolist.h"
#include <boost/uuid/uuid.hpp>
#include <boost/date_time.hpp>
#include <map>
#include <string>
#include "itodolistdisplay.h"

class TodoListWidget : public Fl_Browser_
{
  		void *item_first() const;
  		void *item_next(void *l) const;
  		void *item_prev(void *l) const;
  		int item_height(void *) const;
  		int item_width(void *v) const;
		void item_draw(void *v, int X, int Y, int W, int H) const;
  		void item_select(void *v, int state);
  		int item_selected(void *v) const;

		struct cb_item {
			cb_item *next;
			cb_item *prev;
			char checked;
			char selected;
			std::string text;
			boost::uuids::uuid id;
			boost::posix_time::ptime created_at;
		};
  	private:
		cb_item *first;
		cb_item *last;
		cb_item *selected;
		/*cb_item *cache;
		int cached_item;*/
		std::map<boost::uuids::uuid, cb_item*> ids_to_items_;
		/*int nchecked_;
		cb_item *find_item(int) const;
		int lineno(cb_item *) const;*/

	public:
		typedef boost::uuids::uuid line_t;
		TodoListWidget(int x, int y, int w, int h, const char *label = 0);
		void setTodoList(TodoList::pointer todolist);


		void add(const std::string& value);
		boost::uuids::uuid value() const;
		std::string text(boost::uuids::uuid line) const;
		void text(boost::uuids::uuid line, const std::string& value);
		void remove(boost::uuids::uuid line);

		void check(boost::uuids::uuid line);
		void uncheck(boost::uuids::uuid line);

	private:
		TodoList::pointer m_todolist;
		int handle(int event);
};

#endif /* _TODO_LIST_WIDGET_H_ */
