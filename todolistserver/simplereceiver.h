#ifndef _SIMPLERECEIVER_H_
#define _SIMPLERECEIVER_H_

#include <boost/asio/io_service.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>
#include <iostream>


/*
 * USAGE:
 *
 * SimpleReceiver server(2014, [](const std::string &input){std::cout << input << std::endl;});
 *
 */

class RecvConnection : public boost::enable_shared_from_this<RecvConnection>
{
public:
	typedef boost::shared_ptr<RecvConnection> pointer;
	static pointer create(boost::asio::io_service& io_service, std::function<void(const std::string&)> f)
	{
		return pointer(new RecvConnection(io_service, f));
	}
	boost::asio::ip::tcp::socket& socket() { return socket_; }
	void start()
	{
		boost::asio::async_read(socket_, boost::asio::buffer(buffer_, 512),
				boost::bind(&RecvConnection::handle_read, shared_from_this(),
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));

	}
private:
	RecvConnection(boost::asio::io_service& io_service, std::function<void(const std::string&)> f) :
		socket_(io_service),
		m_function(f)
	{}
	void handle_read(const boost::system::error_code&, size_t length)
	{
		buffer_[length] = '\0';
		/*std::cout << buffer_ << std::endl;*/
		m_function(buffer_);
	}
	boost::asio::ip::tcp::socket socket_;
	std::function<void(const std::string&)> m_function;
	/*std::string buffer_;*/
	char buffer_[512];
};

class SimpleReceiver
{
public:
	SimpleReceiver(int port, std::function<void(const std::string&)> f)
		: acceptor_(io_service_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)), m_function(f)
	{
		start_accept();
	}
	~SimpleReceiver() {}
	void run()
	{
		io_service_.run();
	}
private:
	void start_accept()
	{
		RecvConnection::pointer new_connection = 
			RecvConnection::create(acceptor_.get_io_service(), m_function);
		acceptor_.async_accept(new_connection->socket(),
				boost::bind(&SimpleReceiver::handle_accept, this, new_connection, boost::asio::placeholders::error));
	}
	void handle_accept(RecvConnection::pointer new_connection,
			const boost::system::error_code& error)
	{
		if (!error) {
			new_connection->start();
		}
		start_accept();
	}
	boost::asio::io_service io_service_;
	boost::asio::ip::tcp::acceptor acceptor_;
	std::function<void(const std::string&)> m_function;
};


#endif /* _SIMPLERECEIVER_H_ */
