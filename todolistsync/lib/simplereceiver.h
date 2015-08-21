#ifndef _SIMPLERECEIVER_H_
#define _SIMPLERECEIVER_H_

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/enable_shared_from_this.hpp>


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
	static pointer create(boost::asio::io_service& io_service, std::function<void(const std::string&)> f);
	boost::asio::ip::tcp::socket& socket();
	void start();
private:
	RecvConnection(boost::asio::io_service& io_service, std::function<void(const std::string&)> f);
	void handle_read(const boost::system::error_code&, size_t length);
	boost::asio::ip::tcp::socket socket_;
	std::function<void(const std::string&)> m_function;
	char buffer_[512];
};

class SimpleReceiver
{
public:
	typedef boost::shared_ptr<SimpleReceiver> pointer;
	static pointer create(int port, std::function<void(const std::string&)> f);
	~SimpleReceiver() {}
	void run();
private:
	SimpleReceiver(int port, std::function<void(const std::string&)> f);
	void start_accept();
	void handle_accept(RecvConnection::pointer new_connection,
			const boost::system::error_code& error);
	boost::asio::io_service io_service_;
	boost::asio::ip::tcp::acceptor acceptor_;
	std::function<void(const std::string&)> m_function;
};


#endif /* _SIMPLERECEIVER_H_ */
