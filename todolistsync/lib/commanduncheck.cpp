#include "commanduncheck.h"

CommandUncheck::CommandUncheck(id id_, timestamp timestamp_)
	: Command(id_, timestamp_)
{
}

Command::pointer CommandUncheck::create(id id_, timestamp timestamp_)
{
	return pointer(new CommandUncheck(id_, timestamp_));
}

void CommandUncheck::doit(std::map<id, TodoListEntry::pointer> &l)
{
	if (l.count(m_id)) {
		l.at(m_id)->setChecked(false);
	}
}

