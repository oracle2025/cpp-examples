#include "commandremove.h"
#include <boost/uuid/uuid_io.hpp>

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
std::string CommandRemove::serialize() const
{
	std::stringstream result;
	result << boost::lexical_cast<std::string>(m_id);
	result << ";";
	result << boost::posix_time::to_iso_string(m_timestamp);
	result << ";r";
    return result.str();
}
bool CommandRemove::operator==(const Command &other) const
{
	if (typeid(*this) != typeid(other)) {
		return false;
	}
	return (m_id == other.getId()) &&
		(m_timestamp == other.getTimestamp());
}

