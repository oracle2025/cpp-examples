#include "todolistentry.h"

TodoListEntry::TodoListEntry(id id_, const std::string &text, timestamp timestamp_)
	: m_id(id_), m_text(text), m_checked(false), m_timestamp(timestamp_)
{
}

bool TodoListEntry::getChecked() const
{
    return m_checked;
}

TodoListEntry::id TodoListEntry::getId() const
{
    return m_id;
}

TodoListEntry::pointer TodoListEntry::create(id id_, const std::string &text, timestamp timestamp_)
{
	return pointer(new TodoListEntry(id_, text, timestamp_));
}

std::string TodoListEntry::getText() const
{
    return m_text;
}

void TodoListEntry::setChecked(bool checked)
{
	m_checked = checked;
}

void TodoListEntry::setText(const std::string& text)
{
	m_text = text;
}
TodoListEntry::timestamp TodoListEntry::getTimestamp() const
{
	return m_timestamp;
}

