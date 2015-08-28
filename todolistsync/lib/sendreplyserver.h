#ifndef _SEND_REPLY_SERVER_H_
#define _SEND_REPLY_SERVER_H_

#include <algorithm>
#include <string>
#include <functional>
#include <memory>
#include <queue>
#include <boost/bind.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>

class Connection
{
	public:
		typedef std::shared_ptr<Connection> pointer;
		typedef std::function<void(const std::string& value)> reply_function;
		virtual ~Connection() {}
		virtual void receive(const std::string& value) = 0;
		//make this also a lambda instead of a virtual?
	protected:
		Connection(reply_function send_) :
			send(send_) {}
		reply_function send;
};

using boost::asio::ip::tcp;

class SendReplyConnection : public boost::enable_shared_from_this<SendReplyConnection>
{
	public:
		typedef boost::shared_ptr<SendReplyConnection> pointer;
		static pointer create(boost::asio::io_service& io_service);
		~SendReplyConnection();
		tcp::socket& socket();
		void setConnection(Connection::pointer connection);
		void start();
		void write(const std::string &value);
	private:
		SendReplyConnection(boost::asio::io_service& io_service);
		void do_read();
		void do_write();
		tcp::socket m_socket;
		enum { max_length = 1024 };
		char m_data[max_length];
		Connection::pointer m_connection;
		std::queue<std::string> m_fifo;
};
class SendReplyServer
{
	public:
		typedef std::shared_ptr<SendReplyServer> pointer;
		typedef std::function<Connection::pointer(Connection::reply_function)> factory_function;
		static pointer create(int port, factory_function factory);
		void run();
		void handle_accept(SendReplyConnection::pointer new_connection,
				const boost::system::error_code& error);
		void start_accept();
	private:
		SendReplyServer(int port, factory_function factory);
		factory_function m_factory;
		boost::asio::io_service m_io_service;
		tcp::acceptor m_acceptor;
};

#endif /* _SEND_REPLY_SERVER_H_ */
