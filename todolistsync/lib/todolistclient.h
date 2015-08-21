#ifndef _TODOLIST_CLIENT_H_
#define _TODOLIST_CLIENT_H_

#include <string>

class TodoListClient
{
public:
	TodoListClient();
	void send(const std::string &output);
private:
	TodoListClient(TodoListClient const&) = delete;
	TodoListClient& operator=(TodoListClient const&) = delete;
};

#endif /* _TODOLIST_CLIENT_H_ */
