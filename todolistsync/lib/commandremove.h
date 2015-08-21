#ifndef _COMMAND_REMOVE_H_
#define _COMMAND_REMOVE_H_

#include "command.h"
#include <string>

class CommandRemove : public Command
{
public:
	static pointer create(id id_, timestamp timestamp_);
	void doit(std::map<id, TodoListEntry::pointer> &l);
private:
	CommandRemove(id id_, timestamp timestamp_);
};

#endif /* _COMMAND_REMOVE_H_ */
