#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "todolistentry.h"
#include <memory>
#include <chrono>
#include <map>
#include <boost/uuid/uuid.hpp>

class Command
{
public:
	typedef boost::uuids::uuid id;
	typedef std::chrono::system_clock::time_point timestamp;
	typedef std::shared_ptr<Command> pointer;
	virtual ~Command() {}
	virtual void doit(std::map<id, TodoListEntry::pointer> &l) = 0;
	//virtual void doit(TodoLog *log) = 0;

	id getId() const;
	timestamp getTimestamp() const;
protected:
	Command(id id_, timestamp timestamp_);
 	id m_id;
	timestamp m_timestamp;
private:
	Command(Command const&) = delete;
	Command& operator=(Command const&) = delete;
};
#endif /* _COMMAND_H_ */
