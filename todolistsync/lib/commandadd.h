#ifndef _COMMAND_ADD_H_
#define _COMMAND_ADD_H_

#include "command.h"
#include <string>

class CommandAdd : public Command
{
public:
	static Command::pointer create(Command::id id, Command::timestamp timestamp, const std::string &text);
	void doit(std::map<id, TodoListEntry::pointer> &l);
private:
	CommandAdd(Command::id id, Command::timestamp timestamp, const std::string &text);
	std::string m_text;
};

#endif /* _COMMAND_ADD_H_ */
