#include "simplereceiver.h"
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>

RecvConnection::RecvConnection(boost::asio::io_service& io_service, std::function<void(const std::string&)> f)
	:
		socket_(io_service),
		m_function(f)
{}


boost::asio::ip::tcp::socket& RecvConnection::socket()
{
	return socket_;
}

RecvConnection::pointer RecvConnection::create(boost::asio::io_service& io_service,
		std::function<void(const std::string&)> f)
{
	return pointer(new RecvConnection(io_service, f));
}

void RecvConnection::handle_read(const boost::system::error_code&, size_t length)
{
	buffer_[length] = '\0';
	m_function(buffer_);
}

void RecvConnection::start()
{
	boost::asio::async_read(socket_, boost::asio::buffer(buffer_, 512),
			boost::bind(&RecvConnection::handle_read, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));

}

SimpleReceiver::pointer SimpleReceiver::create(int port, std::function<void(const std::string&)> f)
{
	return pointer(new SimpleReceiver(port, f));
}

SimpleReceiver::SimpleReceiver(int port, std::function<void(const std::string&)> f)
: acceptor_(io_service_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)), m_function(f)
{
	start_accept();
}

void SimpleReceiver::handle_accept(RecvConnection::pointer new_connection,
		const boost::system::error_code& error)
{
	if (!error) {
		new_connection->start();
	}
	start_accept();
}

void SimpleReceiver::run()
{
	io_service_.run();
}

void SimpleReceiver::start_accept()
{
	RecvConnection::pointer new_connection = 
		RecvConnection::create(acceptor_.get_io_service(), m_function);
	acceptor_.async_accept(new_connection->socket(),
			boost::bind(&SimpleReceiver::handle_accept, this, new_connection, boost::asio::placeholders::error));
}

