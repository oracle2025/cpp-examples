#ifndef _TODOLIST_H_
#define _TODOLIST_H_

#include <string>
#include <memory>
#include <list>
#include <boost/uuid/uuid.hpp>
#include <boost/date_time.hpp>
#include "todolog.h"
#include "todolistclient.h"

class TodoList
{
public:
	typedef boost::uuids::uuid id;
	//typedef std::chrono::system_clock::time_point timestamp;
	typedef boost::posix_time::ptime timestamp;
	typedef std::shared_ptr<TodoList> pointer;
	static pointer create(const std::string& server);

	id add(const std::string &value);
	void edit(id id_, const std::string &value);
	void remove(id id_);
	void check(id id_);
	void uncheck(id id_);
	std::list<id> ids() const;
	std::string get(id id_) const;
	bool checked(id id_) const;

	void sync();

	void run();
	void close();

private:
	void log(Command::pointer cmd);
	TodoLog::pointer m_log;
	TodoListClient::pointer m_client;
	TodoList(const std::string& server);
	TodoList(TodoList const&) = delete;
	TodoList& operator=(TodoList const&) = delete;
};

#endif /* _TODOLIST_H_ */
