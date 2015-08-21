#include "commandremove.h"

CommandRemove::CommandRemove(id id_, timestamp timestamp_)
	: Command(id_, timestamp_)
{
}

Command::pointer CommandRemove::create(id id_, timestamp timestamp_)
{
	return pointer(new CommandRemove(id_, timestamp_));
}

void CommandRemove::doit(std::map<id, TodoListEntry::pointer> &l)
{
	if (l.count(m_id)) {
		l.erase(m_id);
	}
}

