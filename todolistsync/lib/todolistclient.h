#ifndef _TODOLIST_CLIENT_H_
#define _TODOLIST_CLIENT_H_

#include <string>
#include <memory>
#include <queue>
#include "todolog.h"
#include "sendreplyclient.h"

class TodoListClient
{
	public:
		typedef std::shared_ptr<TodoListClient> pointer;
		static pointer create(TodoLog::pointer log, const std::string &server);
		//void send(const std::string &output);
		void send(Command::pointer cmd);
		void get();

		void run();

	private:
		void receive(const std::string& value);
		TodoListClient(TodoLog::pointer log, const std::string &server);
		TodoListClient(TodoListClient const&) = delete;
		TodoListClient& operator=(TodoListClient const&) = delete;
		TodoLog::pointer m_log;
		SendReplyClient::pointer m_client;
};

#endif /* _TODOLIST_CLIENT_H_ */
