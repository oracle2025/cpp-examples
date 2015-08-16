#include <boost/asio/io_service.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>
#include <iostream>
#include <ctime>
using namespace boost::asio::ip;

std::string make_daytime_string()
{
	std::string data;
	std::time_t now = std::time(nullptr);
	data = std::ctime(&now);
	return data;
}


class tcp_connection
	: public boost::enable_shared_from_this<tcp_connection>
{
	public:
		typedef boost::shared_ptr<tcp_connection> pointer;
		static pointer create(boost::asio::io_service& io_service)
		{
			return pointer(new tcp_connection(io_service));
		}

		tcp::socket& socket()
		{
			return socket_;
		}
		void start()
		{
			std::cout << "tcp_connection::start()" << std::endl;
			message_ = make_daytime_string();
			boost::asio::async_write(socket_, boost::asio::buffer(message_),
					boost::bind(&tcp_connection::handle_write, shared_from_this(),
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
		}
		~tcp_connection()
		{
			std::cout << "~tcp_connection()" << std::endl;
		}
	private:
		tcp_connection(boost::asio::io_service& io_service)
			: socket_(io_service)
		{
		}

		void handle_write(const boost::system::error_code& /*error*/, size_t /*bytes_trensferred*/ )
		{
		}
		tcp::socket socket_;
		std::string message_;
};

class tcp_server
{
	public:
		tcp_server(boost::asio::io_service& io_service)
    		: acceptor_(io_service, tcp::endpoint(tcp::v4(), 2014))
 		{
    		start_accept();
  		}
	private:
		void start_accept()
  		{
  			std::cout << "tcp_server::start_accept()" << std::endl;
    		tcp_connection::pointer new_connection =
      			tcp_connection::create(acceptor_.get_io_service());

    		acceptor_.async_accept(new_connection->socket(),
        			boost::bind(&tcp_server::handle_accept, this, new_connection,
          				boost::asio::placeholders::error));
  		}
 		void handle_accept(tcp_connection::pointer new_connection,
      			const boost::system::error_code& error)
  		{
  			std::cout << "tcp_server::handle_accept()" << std::endl;
    		if (!error)
    		{
      			new_connection->start();
    		}

    		start_accept();
  		}
		tcp::acceptor acceptor_;
};

int main(int argc, const char *argv[])
{
	try {
		boost::asio::io_service io_service;
		tcp_server server(io_service);
		io_service.run();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
