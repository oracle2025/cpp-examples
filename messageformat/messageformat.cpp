#include <iostream>
#include <string>
#include <boost/uuid/uuid_io.hpp>
#include <boost/date_time.hpp>
#include <boost/uuid/string_generator.hpp>

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

bool is_valid_uuid(const std::string& str)
{
	//regexp: a-f0-9 8* - 4* - 4* - 12*
	return false;
}
boost::uuids::uuid parse_id(const std::string &str)
{
	return boost::uuids::string_generator()(str);
}
boost::posix_time::ptime parse_timestamp(const std::string &str)
{
	return boost::posix_time::from_iso_string(str);
}
command_type parse_type(const std::string &str)
{
	switch (str[0]) {
		case 'a':
			return command_type::add;
		case 'e':
			return command_type::edit;
		case 'c':
			return command_type::check;
		case 'u':
			return command_type::uncheck;
		case 'r':
			return command_type::remove;
		default:
			break;
	}
	return command_type::invalid;
}
std::string parse_text(int len, const std::string &str)
{
	return "";
}


command parse(const std::string& input)
{
	command result;
	std::string uuid_str, ts_str, cmd_str, text_str;//Is there a "range" type?
	int text_len;

	if (!is_valid_uuid(uuid_str)) {
		result.type = command_type::invalid;
		return result;
	}

	result.id = parse_id(uuid_str);
	result.timestamp = parse_timestamp(ts_str);
	result.type = parse_type(cmd_str);
	result.text = parse_text(text_len, text_str);


	return result;
}

int main(int argc, const char *argv[])
{
	std::string add_cmd = "ecb9be51-1b6b-4571-a067-1627308b8191;2015-08-19T14:56:25.749355;a;11;Helle World";
	std::string edit_cmd = "ecb9be51-1b6b-4571-a067-1627308b8191;2015-08-19T14:56:25.749355;e;11;Hello World";
	std::string check_cmd = "ecb9be51-1b6b-4571-a067-1627308b8191;2015-08-19T14:56:25.749355;c";
	std::string uncheck_cmd = "ecb9be51-1b6b-4571-a067-1627308b8191;2015-08-19T14:56:25.749355;u";
	std::string remove_cmd = "ecb9be51-1b6b-4571-a067-1627308b8191;2015-08-19T14:56:25.749355;r";
	return 0;
}
