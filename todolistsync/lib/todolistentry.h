#ifndef _TODOLIST_ENTRY_H_
#define _TODOLIST_ENTRY_H_

#include <memory>
#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/date_time.hpp>

class TodoListEntry
{
public:
	typedef std::shared_ptr<TodoListEntry> pointer;
	typedef boost::uuids::uuid id;
	typedef boost::posix_time::ptime timestamp;
	static pointer create(id id_, const std::string &text, timestamp timestamp_);

	id getId() const;
	std::string getText() const;
	bool getChecked() const;
	timestamp getTimestamp() const;

	void setText(const std::string& text);
	void setChecked(bool checked);
private:
	TodoListEntry(id id_, const std::string &text, timestamp timestamp_);
	TodoListEntry(TodoListEntry const&) = delete;
	TodoListEntry& operator=(TodoListEntry const&) = delete;

	id m_id;
	std::string m_text;
	bool m_checked;
	timestamp m_timestamp;
};

#endif /* _TODOLIST_ENTRY_H_ */
