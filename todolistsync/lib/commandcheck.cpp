#include "commandcheck.h"
#include <boost/uuid/uuid_io.hpp>

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
std::string CommandCheck::serialize() const
{
	std::stringstream result;
	result << boost::lexical_cast<std::string>(m_id);
	result << ";";
	result << boost::posix_time::to_iso_string(m_timestamp);
	result << ";c";
    return result.str();
}
bool CommandCheck::operator==(const Command &other) const
{
	if (typeid(*this) != typeid(other)) {
		return false;
	}
	return (m_id == other.getId()) &&
		(m_timestamp == other.getTimestamp());
}

