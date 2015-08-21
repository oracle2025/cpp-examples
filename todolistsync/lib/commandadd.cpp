#include "commandadd.h"

CommandAdd::CommandAdd(Command::id id, Command::timestamp timestamp, const std::string &text)
	: Command(id, timestamp), m_text(text)
{
}

Command::pointer CommandAdd::create(Command::id id, Command::timestamp timestamp, const std::string &text)
{
    return Command::pointer(new CommandAdd(id, timestamp, text));
}

void CommandAdd::doit(std::map<id, TodoListEntry::pointer> &l)
{
	l[m_id] = TodoListEntry::create(m_id, m_text);
}

