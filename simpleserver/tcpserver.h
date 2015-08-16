#ifndef _TCPSERVER_H_
#define _TCPSERVER_H_

#include <boost/asio/io_service.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>


class TCPConnection : public boost::enable_shared_from_this<TCPConnection>
{
	public:
		typedef boost::shared_ptr<TCPConnection> pointer;
		static pointer create(boost::asio::io_service& io_service, std::function<std::string()> f)
		{
			return pointer(new TCPConnection(io_service, f));
		}
		boost::asio::ip::tcp::socket& socket() { return socket_; }
		void start()
		{
			message_ = m_function();
			boost::asio::async_write(socket_, boost::asio::buffer(message_),
					boost::bind(&TCPConnection::handle_write, shared_from_this(),
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
		}
	private:
		TCPConnection(boost::asio::io_service& io_service, std::function<std::string()> f)
			:socket_(io_service),
			m_function(f)
		{}
		void handle_write(const boost::system::error_code&, size_t) {}
		boost::asio::ip::tcp::socket socket_;
		std::string message_;
		std::function<std::string()> m_function;
};

class TCPServer
{
public:
	TCPServer(int port, std::function<std::string()> f)
		: acceptor_(io_service_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
		m_function(f)
	{
		start_accept();
	}
	~TCPServer() {}
	void run()  
	{
		io_service_.run();
	}
private:
	void start_accept()
	{
		TCPConnection::pointer new_connection =
			TCPConnection::create(acceptor_.get_io_service(), m_function);
		acceptor_.async_accept(new_connection->socket(),
				boost::bind(&TCPServer::handle_accept, this, new_connection, boost::asio::placeholders::error));
	}
	void handle_accept(TCPConnection::pointer new_connection,
			const boost::system::error_code& error)
	{
		if (!error) {
			new_connection->start();
		}
		start_accept();
	}
	boost::asio::io_service io_service_;
	boost::asio::ip::tcp::acceptor acceptor_;
	std::function<std::string()> m_function;
};

#endif /* _TCPSERVER_H_ */
