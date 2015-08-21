#include "command.h"
#include "todolist.h"

Command::Command(Command::id id_, Command::timestamp timestamp_)
	: m_id(id_), m_timestamp(timestamp_)
{
}

Command::id Command::getId() const
{
    return m_id;
}

Command::timestamp Command::getTimestamp() const
{
    return m_timestamp;
}

std::string Command::serialize() const
{
    return "";
}

