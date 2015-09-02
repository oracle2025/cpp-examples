#include "todolog.h"
#include <boost/uuid/uuid_io.hpp>
#include <iostream>
#include <typeinfo>
#include <map>

TodoLog::TodoLog()
{
}

std::list<TodoListEntry::pointer> TodoLog::evaluate()
{
	// order log by timestamps
	// std::list<Command::pointer> m_log;
	m_log.sort([](const Command::pointer &p1, const Command::pointer &p2) {
			return (p1->getTimestamp() < p2->getTimestamp());
			});
	std::map<Command::id, TodoListEntry::pointer> tmpmap;
	for (auto i: m_log) {
		i->doit(tmpmap);
	}
	std::list<TodoListEntry::pointer> result;
	for (auto i: tmpmap) {
		result.push_back(i.second);
	}
	result.sort([](const TodoListEntry::pointer &p1, const TodoListEntry::pointer &p2) {
			return (p1->getTimestamp() < p2->getTimestamp());
			});
	// add entrys to a map
	// (optional: Sort Map into list)
	// return list;
	return result;
}

TodoLog::pointer TodoLog::create()
{
    return pointer(new TodoLog);
}
void TodoLog::add(Command::pointer cmd)
{
	//Find Add Duplicates?
	for (auto i: m_log) {
		//make this more efficient with a multi_map on id?
		if (*i == *cmd) {
			return;
		}
	}
	m_log.push_back(cmd);
	debug_print_log();
	debug_eval_log();
}
void TodoLog::debug_print_log() const
{
	std::cout << "-- debug_print_log BEGIN --" << std::endl;
	for (auto i: m_log) {
		/*std::time_t t = std::chrono::system_clock::to_time_t(i->getTimestamp());*/
		std::cout << "ID: " << i->getId();
		std::cout << " Type: " << typeid(*i).name();
		std::cout << " Timestamp: " << i->getTimestamp() << std::endl;//std::ctime(&t);
	}
	std::cout << "-- debug_print_log END --" << std::endl;
}
void TodoLog::debug_eval_log()
{
	std::cout << "-- List: --" << std::endl;
	for (auto i: evaluate()) {
		std::cout << "[" << (i->getChecked()?"X":" ") << "] " << i->getText() << std::endl;
	}
	std::cout << "-- List END --" << std::endl;
}
std::list<Command::pointer> TodoLog::compress() const
{
	std::list<Command::pointer> result;
	//Render the final log, and then recreate with using timestamps from the last change, ...
	//
    return result;
}
std::vector<std::string> TodoLog::serialize() const
{
	std::vector<std::string> result(m_log.size());
	int index = 0;
	for (auto i: m_log) {
		result[index] = i->serialize();
		index++;
	}
	return std::move(result);
}

