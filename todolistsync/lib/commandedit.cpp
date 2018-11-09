#include "commandedit.h"
#include <sstream>
#include <boost/uuid/uuid_io.hpp>
#include "itodolistdisplay.h"

CommandEdit::CommandEdit(Command::id id_, Command::timestamp timestamp_, const std::string &text) :
	Command(id_, timestamp_), m_text(text)
{
}

Command::pointer CommandEdit::create(Command::id id_, Command::timestamp timestamp_, const std::string &text)
{
	return pointer(new CommandEdit(id_, timestamp_, text));
}
Command::pointer CommandEdit::create(Command::id id_, const std::string &text)
{
	return create(id_, boost::posix_time::microsec_clock::universal_time(), text);
}

void CommandEdit::doit(std::map<id, TodoListEntry::pointer> &l)
{
	if (l.count(m_id)) {
		l.at(m_id)->setText(m_text);
	}
}
void CommandEdit::doit(ITodoListMap* l)
{
	l->text(m_id, m_text);
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
bool CommandEdit::operator==(const Command &other) const
{
	if (typeid(*this) != typeid(other)) {
		return false;
	}
	return (m_id == other.getId()) &&
		(m_timestamp == other.getTimestamp()) &&
		(m_text == dynamic_cast<const CommandEdit*>(&other)->m_text);
}

