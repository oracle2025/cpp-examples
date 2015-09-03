#ifndef _ITODOLISTDISPLAY_H_
#define _ITODOLISTDISPLAY_H_

#include <boost/uuid/uuid.hpp>
#include <string>

class ITodoListDisplay
{
	public:
		virtual void add(const std::string& value) = 0;
		virtual void text(boost::uuids::uuid line, const std::string& value) = 0;
		virtual void remove(boost::uuids::uuid line) = 0;
		virtual void check(boost::uuids::uuid line) = 0;
		virtual void uncheck(boost::uuids::uuid line) = 0;
};

#endif /* _ITODOLISTDISPLAY_H_ */
