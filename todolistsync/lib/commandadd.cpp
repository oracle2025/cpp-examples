#include "commandadd.h"
#include <sstream>
#include <boost/uuid/uuid_io.hpp>

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
std::string CommandAdd::serialize() const
{
	std::stringstream result;
	result << boost::lexical_cast<std::string>(m_id);
	result << ";";
	result << boost::posix_time::to_iso_string(m_timestamp);
	result << ";a;";
	result << m_text.length() << ";" << m_text;
    return result.str();
}

