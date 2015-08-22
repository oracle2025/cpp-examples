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

