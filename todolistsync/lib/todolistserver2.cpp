#include "todolistserver2.h"
#include <boost/algorithm/string.hpp>

class TodoListConnection : public Connection
{
	public:
		static Connection::pointer create(TodoLog::pointer log, Connection::reply_function send_);
		void receive(const std::string &value);
	private:
		TodoListConnection(TodoLog::pointer log, Connection::reply_function send_);
		TodoLog::pointer m_log;
};

Connection::pointer TodoListConnection::create(TodoLog::pointer log, Connection::reply_function send_)
{
	return Connection::pointer(new TodoListConnection(log, send_));
}
TodoListConnection::TodoListConnection(TodoLog::pointer log, Connection::reply_function send_) :
	Connection(send_),
	m_log(log)
{
}
void TodoListConnection::receive(const std::string &value)
{
	using namespace boost::algorithm;
	std::cout << "receive: " << value << std::endl;
	std::string strcmd = trim_copy(value);
	if (strcmd == "get") {
		for (auto i: m_log->serialize()) {
			send(i+"\n");
		}
		//for (auto i: m_log) {send(i->serialize());}
		//Add a send fifo DONE
		return;
	} else if (strcmd == "cget") {
		return;
	} 
	//m_log->add(parse(value));
	//if value == "get", reply with log
	//if value == "cget", reply with compressed log
	/*Command::pointer cmd = CommandParser::parse(input);
	if (cmd) {
		m_log->add(cmd);
	}*/
}

TodoListServer2::TodoListServer2() :
	m_log(TodoLog::create())
{
	m_server = SendReplyServer::create(2015,
			boost::bind(&TodoListConnection::create, m_log, _1));
}

TodoListServer2::pointer TodoListServer2::create()
{
	return pointer(new TodoListServer2);
}

void TodoListServer2::receive(const std::string &inpput)
{
}

void TodoListServer2::start()
{
	m_server->run();
}
TodoLog::pointer TodoListServer2::log() const
{
    return m_log;
}

