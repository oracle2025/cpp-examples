#ifndef _COMMAND_CHECK_H_
#define _COMMAND_CHECK_H_

#include "command.h"
#include <string>

class CommandCheck : public Command
{
public:
	static pointer create(id id_, timestamp timestamp_);
	void doit(std::map<id, TodoListEntry::pointer> &l);
	std::string serialize() const;
private:
	CommandCheck(id id_, timestamp timestamp_);
};

#endif /* _COMMAND_CHECK_H_ */
