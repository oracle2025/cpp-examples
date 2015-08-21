#ifndef _COMMAND_PARSER_H_
#define _COMMAND_PARSER_H_

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
class CommandParser
{
public:
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
private:
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
public:
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
};

#endif /* _COMMAND_PARSER_H_ */
