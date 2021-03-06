#ifndef _COMMAND_CHECK_H_
#define _COMMAND_CHECK_H_

#include "command.h"
#include <string>

class CommandCheck : public Command
{
public:
	static pointer create(id id_, timestamp timestamp_);
	static pointer create(id id_);
	void doit(std::map<id, TodoListEntry::pointer> &l);
	void doit(ITodoListMap* l);
	std::string serialize() const;
	bool operator==(const Command &other) const;
private:
	CommandCheck(id id_, timestamp timestamp_);
};

#endif /* _COMMAND_CHECK_H_ */
