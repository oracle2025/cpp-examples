#ifndef _TODOLOG_H_
#define _TODOLOG_H_

#include "command.h"
#include "todolistentry.h"
#include <memory>
#include <list>

class TodoLog
{
public:
	typedef std::shared_ptr<TodoLog> pointer;
	static pointer create();
	void add(Command::pointer cmd);
	std::list<TodoListEntry::pointer> evaluate();
private:
	TodoLog();
	TodoLog(TodoLog const&) = delete;
	TodoLog& operator=(TodoLog const&) = delete;
	std::list<Command::pointer> m_log;

	void debug_print_log() const;
	void debug_eval_log();
};

#endif /* _TODOLOG_H_ */
