#include "sendreplyclient.h"
#include <iostream>


using boost::asio::ip::tcp;

SendReplyClient::pointer SendReplyClient::create(const std::string &server, int port, reply_function reply_)
{
	return pointer(new SendReplyClient(server, port, reply_));
}
SendReplyClient::SendReplyClient(const std::string &server, int port, reply_function reply_) :
	reply(reply_),
	m_socket(m_io_service),
	m_connected(false)
{
	tcp::resolver resolver(m_io_service);
	auto endpoint_iterator = resolver.resolve({ server, std::to_string(port) });
 	boost::asio::async_connect(m_socket, endpoint_iterator,
        	[this](boost::system::error_code ec, tcp::resolver::iterator)
        	{
          		if (!ec) {
          			m_connected = true;
          			if (!m_fifo.empty()) {
          				do_write();
          			}
            		do_read();
          		} else {
          			std::cerr << "connect error " << ec.value() << std::endl;
          		}
        	});
}
void SendReplyClient::do_read()
{
	m_socket.async_read_some(
			boost::asio::buffer(m_data, max_length),
			[this](boost::system::error_code ec, std::size_t length)
			{
				if (!ec) {
					reply(std::string(m_data, length));
					do_read();
				} else {
					std::cerr << "read error " << ec.value() << std::endl;
					m_connected = false;
					m_socket.close();
				}
			});
}
void SendReplyClient::do_write()
{
	if (m_fifo.empty()) {
		return;
	}
	std::size_t data_length = std::min(std::size_t(max_length), m_fifo.front().length());
	memcpy(m_data, m_fifo.front().data(), data_length);
	boost::asio::async_write(m_socket,
			boost::asio::buffer(m_data, data_length),
			[this](boost::system::error_code ec, std::size_t)
			{
				if (!ec) {
					m_fifo.pop();
					if (!m_fifo.empty()) {
						do_write();
					}
				} else {
					std::cerr << "write error " << ec.value() << std::endl;
					m_connected = false;
					m_socket.close();
				}
			});
}

SendReplyClient::~SendReplyClient()
{
}


void SendReplyClient::run()
{
	m_io_service.run();
}

void SendReplyClient::send(const std::string &value)
{
	m_io_service.post(
			[this, value]() {
				m_fifo.push(value);
				if (m_connected && m_fifo.size() == 1) {
					do_write();
				}
			});

}

