#ifndef _COMMAND_PARSER_H_
#define _COMMAND_PARSER_H_

#include "command.h"
#include <string>
#include <boost/uuid/uuid_io.hpp>
#include <boost/date_time.hpp>


enum class command_type {
	invalid = 0,
	add,
	edit,
	check,
	uncheck,
	remove,
};
struct command {
	boost::uuids::uuid id;
	boost::posix_time::ptime timestamp;
	command_type type;
	std::string text;
};
class CommandParser
{
public:
	static Command::pointer parse(const std::string &input);
private:
	static std::string type_to_string(command_type t);

	static void debug_print_command(const command& cmd);

	static boost::uuids::uuid parse_id(const std::string &str);
	static boost::posix_time::ptime parse_timestamp(const std::string &str);
	static command_type parse_type(const std::string &str);
};

#endif /* _COMMAND_PARSER_H_ */
