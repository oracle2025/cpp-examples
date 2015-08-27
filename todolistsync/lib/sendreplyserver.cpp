#include "sendreplyserver.h"
#include <iostream>


SendReplyConnection::SendReplyConnection(boost::asio::io_service& io_service) :
	m_socket(io_service)
{
}


SendReplyConnection::~SendReplyConnection()
{
	std::cout << "~SendReplyConnection()" << std::endl;
}

SendReplyConnection::pointer SendReplyConnection::create(boost::asio::io_service& io_service)
{
	return pointer(new SendReplyConnection(io_service));
}

tcp::socket& SendReplyConnection::socket()
{
    return m_socket;
}

void SendReplyConnection::do_read()
{
	auto self(shared_from_this());
	m_socket.async_read_some(boost::asio::buffer(m_data, max_length),
			[this, self](boost::system::error_code ec, std::size_t length)
			{
				if (!ec)
				{
					std::string tmp(m_data, length);
					m_connection->receive(tmp);
					do_read();
				}
			});
}

void SendReplyConnection::do_write()
{
	std::string value = m_fifo.front();
	m_fifo.pop();
	size_t value_length = value.length();
	size_t max_l = max_length;
	size_t len = std::min(value_length, max_l);
	memcpy(m_data, value.data(), len);
	auto self(shared_from_this());
	boost::asio::async_write(m_socket, boost::asio::buffer(m_data, len),
			[this, self](boost::system::error_code ec, std::size_t /*length*/)
			{
				if (m_fifo.size() > 0) {
					do_write();
				}
			});
}

void SendReplyConnection::setConnection(Connection::pointer connection)
{
	m_connection = connection;
}

void SendReplyConnection::start()
{
	do_read();
}

void SendReplyConnection::write(const std::string &value)
{
	m_fifo.push(value);
	/*size_t value_length = value.length();
	size_t max_l = max_length;
	size_t len = std::min(value_length, max_l);
	memcpy(m_data, value.data(), len);*/
	if (m_fifo.size() == 1) {
		do_write();
	}
}

SendReplyServer::SendReplyServer(int port, factory_function factory) :
	m_factory(factory),
	m_acceptor(m_io_service, tcp::endpoint(tcp::v4(), port))
{
	start_accept();
}
SendReplyServer::pointer SendReplyServer::create(int port, factory_function factory)
{
    return pointer(new SendReplyServer(port, factory));
}

void SendReplyServer::handle_accept(SendReplyConnection::pointer new_connection,
		const boost::system::error_code& error)
{
	if (!error) {
		Connection::pointer c = m_factory(
				boost::bind(&SendReplyConnection::write, new_connection.get(), _1)
				);
		new_connection->setConnection(c);
		new_connection->start();
	}
	start_accept();
}

void SendReplyServer::run()
{
	m_io_service.run();
}

void SendReplyServer::start_accept()
{
	SendReplyConnection::pointer new_connection =
		SendReplyConnection::create(m_io_service);
	m_acceptor.async_accept(new_connection->socket(),
			boost::bind(&SendReplyServer::handle_accept, this, new_connection, boost::asio::placeholders::error));
}

