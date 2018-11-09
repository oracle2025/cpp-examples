#ifndef _COMMAND_EDIT_H_
#define _COMMAND_EDIT_H_

#include "command.h"
#include <string>

class CommandEdit : public Command
{
public:
	static Command::pointer create(Command::id id_, Command::timestamp timestamp_, const std::string &text);
	static Command::pointer create(Command::id id_, const std::string &text);
	void doit(std::map<id, TodoListEntry::pointer> &l);
	void doit(ITodoListMap* l);
	std::string serialize() const;
	bool operator==(const Command &other) const;
private:
	CommandEdit(Command::id id_, Command::timestamp timestamp_, const std::string &text);
	std::string m_text;
};

#endif /* _COMMAND_EDIT_H_ */
