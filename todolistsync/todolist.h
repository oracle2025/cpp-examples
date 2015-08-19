#ifndef _TODOLIST_H_
#define _TODOLIST_H_

#include <string>
#include <memory>
#include <list>
#include <chrono>
#include <boost/uuid/uuid.hpp>
#include "todolog.h"

class TodoList
{
public:
	typedef boost::uuids::uuid id;
	typedef std::chrono::system_clock::time_point timestamp;
	typedef std::shared_ptr<TodoList> pointer;
	static pointer create();

	id add(const std::string &value);
	void edit(id id_, const std::string &value);
	void remove(id id_);
	void check(id id_);
	void uncheck(id id_);
	std::list<id> ids() const;
	std::string get(id id_) const;
	bool checked(id id_) const;

private:
	TodoLog::pointer m_log;
	TodoList();
	TodoList(TodoList const&) = delete;
	TodoList& operator=(TodoList const&) = delete;
};

#endif /* _TODOLIST_H_ */
