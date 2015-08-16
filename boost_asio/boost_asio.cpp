#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>
#include <chrono>

#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <ctime>

class FingerState
{
	public:
		FingerState() :
			m_uptime(2),
			m_requests(0)
		{
		}
		std::string uptime() const
		{
			std::stringstream out;
			out << m_uptime;
			return out.str();
		}
		int requests() {
			m_requests++;
			return m_requests;
		}
	private:
		int m_uptime;
		int m_requests;
};

using namespace boost::asio;
using namespace boost::asio::ip;

class SimpleEchoServer
{
	public:
		SimpleEchoServer(int port);
		virtual ~SimpleEchoServer() {}
		virtual std::string request() = 0;
};

SimpleEchoServer::SimpleEchoServer(int port)
{
}

class SimpleEchoExample : public SimpleEchoServer
{
	public:
		SimpleEchoExample() :
			SimpleEchoServer(4321)
		{
		}
		std::string request()
		{
			return "Hello World!";
		}
};

io_service ioservice;
tcp::endpoint tcp_endpoint{tcp::v4(), 2014};
tcp::acceptor tcp_acceptor{ioservice, tcp_endpoint};
tcp::socket tcp_socket{ioservice};
std::string data;

void accept_handler(const boost::system::error_code &ec);

void write_handler(const boost::system::error_code &ec,
		std::size_t bytes_transferred)
{
	if (!ec) {
		std::cout << "write_handler" << std::endl;
		tcp_socket.shutdown(tcp::socket::shutdown_send);
	}
}

void accept_handler(/*tcp_connection::pointer new_connection, */const boost::system::error_code &ec)
{
	if (!ec)
	{
		std::cout << "accept_handler" << std::endl;
		std::time_t now = std::time(nullptr);
		data = std::ctime(&now);
		async_write(tcp_socket, buffer(data), write_handler);
	}
}

class myserver
{
	public:
		void write();
		void accept();
};

int main(int argc, const char *argv[])
{
	tcp_acceptor.listen();
	tcp_acceptor.async_accept(tcp_socket, accept_handler);
	ioservice.run();
	/*FingerState state;
	std::cout << "Hello" << std::endl;
	std::cout << "Uptime: " << state.uptime() << std::endl;
	std::cout << "Requests: " << state.requests() << std::endl;

	auto start = std::chrono::system_clock::now();


	io_service ioservice;
	steady_timer timer{ioservice, std::chrono::seconds{3}};
	timer.async_wait([&start](const boost::system::error_code &ec)
			{ std::cout << "3 sec" << std::endl;
			auto now = std::chrono::system_clock::now();
			auto now_c = std::chrono::system_clock::to_time_t(now);
			std::cout << std::put_time(std::localtime(&now_c), "%c") << std::endl;
			});

	ioservice.run();*/

	return 0;
}
