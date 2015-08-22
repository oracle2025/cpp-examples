#include "commandedit.h"
#include <sstream>
#include <boost/uuid/uuid_io.hpp>

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
std::string CommandEdit::serialize() const
{
	std::stringstream result;
	result << boost::lexical_cast<std::string>(m_id);
	result << ";";
	result << boost::posix_time::to_iso_string(m_timestamp);
	result << ";e;";
	result << m_text.length() << ";" << m_text;
    return result.str();
}

