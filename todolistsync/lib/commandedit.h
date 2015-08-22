#ifndef _COMMAND_EDIT_H_
#define _COMMAND_EDIT_H_

#include "command.h"
#include <string>

class CommandEdit : public Command
{
public:
	static Command::pointer create(Command::id id_, Command::timestamp timestamp_, const std::string &text);
	void doit(std::map<id, TodoListEntry::pointer> &l);
	std::string serialize() const;
private:
	CommandEdit(Command::id id_, Command::timestamp timestamp_, const std::string &text);
	std::string m_text;
};

#endif /* _COMMAND_EDIT_H_ */
