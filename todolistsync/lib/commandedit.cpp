#include "commandedit.h"

CommandEdit::CommandEdit(Command::id id_, Command::timestamp timestamp_, const std::string &text) :
	Command(id_, timestamp_), m_text(text)
{
}

Command::pointer CommandEdit::create(Command::id id_, Command::timestamp timestamp_, const std::string &text)
{
	return pointer(new CommandEdit(id_, timestamp_, text));
}

void CommandEdit::doit(std::map<id, TodoListEntry::pointer> &l)
{
	if (l.count(m_id)) {
		l.at(m_id)->setText(m_text);
	}
}

