#ifndef _ITODOLISTDISPLAY_H_
#define _ITODOLISTDISPLAY_H_

#include <boost/uuid/uuid.hpp>
#include <boost/date_time.hpp>
#include <string>
#include <functional>
#include "command.h"

class ITodoListDisplay
{
	public:
		typedef std::function<void(Command::pointer)> from_display_function;

		virtual void send(Command::pointer cmd) = 0;
		virtual void setFromDisplayFunction(from_display_function func) = 0;
};

class ITodoListMap
{
	public:
		virtual void add(
				boost::uuids::uuid line,
				const std::string& value,
				boost::posix_time::ptime timestamp) = 0;
		virtual void add(const std::string& value) = 0;
		virtual void text(boost::uuids::uuid line, const std::string& value) = 0;
		virtual void remove(boost::uuids::uuid line) = 0;
		virtual void check(boost::uuids::uuid line) = 0;
		virtual void uncheck(boost::uuids::uuid line) = 0;
};

#endif /* _ITODOLISTDISPLAY_H_ */
