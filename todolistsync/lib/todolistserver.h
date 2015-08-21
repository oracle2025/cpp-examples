#ifndef _TODOLIST_SERVER_H_
#define _TODOLIST_SERVER_H_

#include <memory>
#include "todolog.h"
#include "simplereceiver.h"

class TodoListServer
{
public:
	typedef std::shared_ptr<TodoListServer> pointer;
	static pointer create();
	void start();
private:
	TodoLog::pointer m_log;
	SimpleReceiver::pointer m_receiver;
	void receive(const std::string &input);
	TodoListServer();
	TodoListServer(TodoListServer const&) = delete;
	TodoListServer& operator=(TodoListServer const&) = delete;
};

#endif /* _TODOLIST_SERVER_H_ */
