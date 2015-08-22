#include "commanduncheck.h"
#include <boost/uuid/uuid_io.hpp>

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
std::string CommandUncheck::serialize() const
{
	std::stringstream result;
	result << boost::lexical_cast<std::string>(m_id);
	result << ";";
	result << boost::posix_time::to_iso_string(m_timestamp);
	result << ";u";
    return result.str();
}

