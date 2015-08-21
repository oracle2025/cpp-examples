#include "commandcheck.h"

CommandCheck::CommandCheck(id id_, timestamp timestamp_)
	: Command(id_, timestamp_)
{
}

Command::pointer CommandCheck::create(id id_, timestamp timestamp_)
{
	return pointer(new CommandCheck(id_, timestamp_));
}

void CommandCheck::doit(std::map<id, TodoListEntry::pointer> &l)
{
	if (l.count(m_id)) {
		l.at(m_id)->setChecked(true);
	}
}

