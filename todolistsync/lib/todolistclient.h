#ifndef _TODOLIST_CLIENT_H_
#define _TODOLIST_CLIENT_H_

#include <string>
#include <memory>

class TodoListClient
{
public:
	typedef std::shared_ptr<TodoListClient> pointer;
	static pointer create(const std::string &server);
	void send(const std::string &output);
private:
	TodoListClient(const std::string &server);
	TodoListClient(TodoListClient const&) = delete;
	TodoListClient& operator=(TodoListClient const&) = delete;
	std::string m_server;
};

#endif /* _TODOLIST_CLIENT_H_ */
