#ifndef _TODO_LIST_SERVER_2_H_
#define _TODO_LIST_SERVER_2_H_

#include "sendreplyserver.h"
#include "todolog.h"
#include <memory>

class TodoListServer2
{
	public:
		typedef std::shared_ptr<TodoListServer2> pointer;
		static pointer create();
		void start();

		TodoLog::pointer log() const;
	private:
		TodoLog::pointer m_log;
		SendReplyServer::pointer m_server;
		void receive(const std::string &inpput);
		TodoListServer2();
		TodoListServer2(TodoListServer2 const&) = delete;
		TodoListServer2& operator=(TodoListServer2 const&) = delete;
};

#endif /* _TODO_LIST_SERVER_2_H_ */
