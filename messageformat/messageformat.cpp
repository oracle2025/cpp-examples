#include <iostream>
#include <string>
#include <cstdlib>
#include <boost/uuid/uuid_io.hpp>
#include <boost/date_time.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

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

std::string type_to_string(command_type t)
{
	switch (t) {
		case command_type::invalid:
			return "invalid";
		case command_type::add:
			return "add";
		case command_type::edit:
			return "edit";
		case command_type::check:
			return "check";
		case command_type::uncheck:
			return "uncheck";
		case command_type::remove:
			return "remove";
	}
}

void debug_print_command(const command& cmd)
{
	std::cout << "Id: " << cmd.id << std::endl;
	std::cout << "Timestamp: " << cmd.timestamp << std::endl;
	std::cout << "Type: " << type_to_string(cmd.type) << std::endl;
	std::cout << "Text: " << cmd.text << std::endl;
}

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
	command invalid;
	invalid.type = command_type::invalid;
	//tokens = split(input);
	//len(tokens) < 3: return invalid;
	/*
	 * string line("test\ttest2\ttest3");
	 * vector<string> strs;
	 * boost::split(strs,line,boost::is_any_of("\t"));
	 */

	std::vector<std::string> tokens;
	boost::split(tokens, input, boost::is_any_of(";"));

	/*for (int i = 0; i < tokens.size(); i++) {
		std::cout << "[" << i << "]: " << tokens[i] << std::endl;
	}*/

	if (tokens.size() < 3) {
		return invalid;
	}
	command result;
	result.id = parse_id(tokens[0]);
	result.timestamp = parse_timestamp(tokens[1]);
	result.type = parse_type(tokens[2]);
	result.text = "";

	if ((result.type == command_type::add ||
			result.type == command_type::edit) &&
			tokens.size() >= 5) {
		int text_len;
		text_len = std::atoi(tokens[3].c_str());
		std::size_t start = 0;
		for (int i = 0; i < 4; i++) {
			start = input.find(";", start) + 1;
		}
		std::string text_str = input.substr(start, text_len);
		result.text = text_str;
		/*std::cout << "Text: " << text_str << std::endl;*/
	}
	/*if (!is_valid_uuid(uuid_str)) {
		result.type = command_type::invalid;
		return result;
	}*/
	return result;
}

int main(int argc, const char *argv[])
{
	/*
	 * uuid: 64bit?
	 * timestamp? 32bit?
	 * cmd: 8bit
	 * len: 32bit?
	 * Rest: Variable
	 */
	std::string add_cmd = "ecb9be51-1b6b-4571-a067-1627308b8191;20150820T090315.190570;a;11;Helle World";
	std::string edit_cmd = "ecb9be51-1b6b-4571-a067-1627308b8191;20150820T090315.190570;e;11;Hello;World";
	std::string check_cmd = "ecb9be51-1b6b-4571-a067-1627308b8191;20150820T090315.190570;c";
	std::string uncheck_cmd = "ecb9be51-1b6b-4571-a067-1627308b8191;20150820T090315.190570;u";
	std::string remove_cmd = "ecb9be51-1b6b-4571-a067-1627308b8191;20150820T090315.190570;r";

	std::string empty_cmd;
	std::string invalid_id;
	std::string invalid_timestamp;
	std::string invalid_cmd;
	std::string inconsistant_text_size1;
	std::string inconsistant_text_size2;

	command cmd1 = parse(add_cmd);
	command cmd2 = parse(edit_cmd);
	command cmd3 = parse(check_cmd);
	command cmd4 = parse(uncheck_cmd);
	command cmd5 = parse(remove_cmd);
	debug_print_command(cmd1);
	debug_print_command(cmd2);
	debug_print_command(cmd3);
	debug_print_command(cmd4);
	debug_print_command(cmd5);
	return 0;
}
