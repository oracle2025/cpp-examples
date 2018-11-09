#ifndef _COMMAND_UNCHECK_H_
#define _COMMAND_UNCHECK_H_

#include "command.h"
#include <string>

class CommandUncheck : public Command
{
public:
	static pointer create(id id_, timestamp timestamp_);
	static pointer create(id id_);
	void doit(std::map<id, TodoListEntry::pointer> &l);
	void doit(ITodoListMap* l);
	std::string serialize() const;
	bool operator==(const Command &other) const;
private:
	CommandUncheck(id id_, timestamp timestamp_);
};

#endif /* _COMMAND_UNCHECK_H_ */
