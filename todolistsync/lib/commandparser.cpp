#include "commandparser.h"

#include "commandadd.h"
#include "commandremove.h"
#include "commandedit.h"
#include "commandcheck.h"
#include "commanduncheck.h"
#include <cstdlib>
#include <boost/uuid/uuid_io.hpp>
#include <boost/date_time.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/classification.hpp>


Command::pointer CommandParser::parse(const std::string &input, std::size_t &remaining)
{
	remaining = 0;
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
    	return Command::pointer();
	}
	command result;
	result.id = parse_id(tokens[0]);
	result.timestamp = parse_timestamp(tokens[1]);
	result.type = parse_type(tokens[2]);
	result.text = "";

	{
		std::size_t start = 0;
		for (int i = 0; i < 2; i++) {
			start = input.find(";", start) + 1;
		}
		start += 1;
		remaining = start;
	}

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
		remaining = start+text_len;
		/*std::cout << "Text: " << text_str << std::endl;*/
	}
	/*if (!is_valid_uuid(uuid_str)) {
		result.type = command_type::invalid;
		return result;
	}*/
	Command::pointer cmd;
	switch(result.type) {
		case command_type::add:
			cmd = CommandAdd::create(result.id, result.timestamp, result.text);
			break;
		case command_type::edit:
			cmd = CommandEdit::create(result.id, result.timestamp, result.text);
			break;
		case command_type::check:
			cmd = CommandCheck::create(result.id, result.timestamp);
			break;
		case command_type::uncheck:
			cmd = CommandUncheck::create(result.id, result.timestamp);
			break;
		case command_type::remove:
			cmd = CommandRemove::create(result.id, result.timestamp);
			break;
		case command_type::invalid:
			break;
	}

	return cmd;
}
boost::posix_time::ptime CommandParser::parse_timestamp(const std::string &str)
{
	return boost::posix_time::from_iso_string(str);
}

boost::uuids::uuid CommandParser::parse_id(const std::string &str)
{
	std::cout << "Parse Id: " << str << std::endl;
	return boost::uuids::string_generator()( boost::algorithm::trim_copy(str) );
}

command_type CommandParser::parse_type(const std::string &str)
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

std::string CommandParser::type_to_string(command_type t)
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

void CommandParser::debug_print_command(const command& cmd)
{
	std::cout << "Id: " << cmd.id << std::endl;
	std::cout << "Timestamp: " << cmd.timestamp << std::endl;
	std::cout << "Type: " << type_to_string(cmd.type) << std::endl;
	std::cout << "Text: " << cmd.text << std::endl;
}

