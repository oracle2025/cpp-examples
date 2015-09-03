#include "todolistclient.h"
#include <iostream>
#include <boost/array.hpp>
#include <boost/algorithm/string.hpp>
#include "commandparser.h"

using boost::asio::ip::tcp;

TodoListClient::TodoListClient(TodoLog::pointer log, const std::string &server) :
	m_log(log)
{
	m_client = SendReplyClient::create(server, 2015,
			[this](const std::string& value) {
				receive(value);
			});
}
TodoListClient::pointer TodoListClient::create(TodoLog::pointer log, const std::string &server)
{
    return pointer(new TodoListClient(log, server));
}
void TodoListClient::send(Command::pointer cmd)
{
	m_client->send(cmd->serialize());
}
void TodoListClient::get()
{
	m_client->send("get");
}


/*void TodoListClient::send(const std::string &output)
{
	m_client->send(output);
}*/
void TodoListClient::receive(const std::string& value)
{
	std::string input(value);
	std::size_t remaining = input.length();
	while (remaining && input.length() > 1) {
		Command::pointer cmd = CommandParser::parse(input, remaining);
		if (cmd) {
			m_log->add(cmd);
			if (remaining) {
				input = input.substr(remaining);
			}
		} else {
			remaining = 0;
		}
	}
}

void TodoListClient::run()
{
	m_client->run();
}


void TodoListClient::close()
{
	m_client->close();
}

