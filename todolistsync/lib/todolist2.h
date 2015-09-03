#ifndef _TODO_LIST_2_H_
#define _TODO_LIST_2_H_

#include "command.h"
#include "todolistclient.h"
#include "todolog.h"
#include "itodolistdisplay.h"

class TodoList2
{
public:
	typedef std::shared_ptr<TodoList2> pointer;
	static TodoList2::pointer create(const std::string &server);

	void setDisplay(ITodoListDisplay *display);

	void from_display(Command::pointer cmd);
	void from_connection(Command::pointer cmd);

private:
	TodoList2(const std::string& server);
	TodoListClient::pointer m_connection; //ITodoListDisplay
	ITodoListDisplay *m_display;   //ITodoListDisplay
	TodoLog::pointer m_log;


	TodoList2(TodoList2 const&) = delete;
	TodoList2& operator=(TodoList2 const&) = delete;
};

#endif /* _TODO_LIST_2_H_ */
