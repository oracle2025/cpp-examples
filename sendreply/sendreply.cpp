#include <iostream>
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
		Connection(reply_function send_) :
			send(send_) {}
		virtual void receive(const std::string& value) = 0;
	protected:
		reply_function send;
};

class StringConnection : public Connection
{
	public:
		StringConnection(const std::string &reply, Connection::reply_function send_) :
			Connection(send_),
			m_reply(reply) {}
		static Connection::pointer create(const std::string &reply, reply_function send_)
		{
			return Connection::pointer(new StringConnection(reply, send_));
		}
		void receive(const std::string& value)
		{
			std::cout << "Received: " << value << std::endl;
			send(m_reply);
		}
	private:
		std::string m_reply;
};

using boost::asio::ip::tcp;

class SendReplyConnection : public boost::enable_shared_from_this<SendReplyConnection>
{
	public:
		typedef boost::shared_ptr<SendReplyConnection> pointer;
		static pointer create(boost::asio::io_service& io_service) {
			return pointer(new SendReplyConnection(io_service));
		}
		~SendReplyConnection()
		{
			std::cout << "~SendReplyConnection" << std::endl;
		}
		tcp::socket& socket()
		{
			return socket_;
		}

		void setConnection(Connection::pointer connection)
		{
			m_connection = connection;
		}

		void start()
		{
		    do_read();
		}
		void write(const std::string &value)
		{
			//Push the string to a fifo here!
			size_t value_length = value.length();
			size_t max_l = max_length;
			size_t len = std::min(value_length, max_l);
			memcpy(data_, value.data(), len);
			do_write(len);
			//Copy value to data_ and call do_write(value.length())
		}
	private:
		SendReplyConnection(boost::asio::io_service& io_service)
		  	: socket_(io_service)
		{
		}
		void do_read()
  		{
    		auto self(shared_from_this());
    		socket_.async_read_some(boost::asio::buffer(data_, max_length),
        			[this, self](boost::system::error_code ec, std::size_t length)
        			{
          				if (!ec)
          				{
          					std::string tmp(data_, length);
							m_connection->receive(tmp);
                            /*do_write(length);*/
                            do_read();
          				}
        			});
  		}

  		void do_write(std::size_t length)
  		{
    		auto self(shared_from_this());
    		boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
    				//Copy from fifo to a tmp string, that is deleted, later..
                    //[this, self, tmpstring](boost::system::error_code ec, std::size_t [>length<])
        			[this, self](boost::system::error_code ec, std::size_t /*length*/)
        			{/*if (!fifo.empty()) do_write(fifo.top().length()) cout << fifo.length*/});
  		}
		tcp::socket socket_;
		enum { max_length = 1024 };
		char data_[max_length];
		Connection::pointer m_connection;
};

class SendReplyServer
{
	public:
		typedef std::function<Connection::pointer(Connection::reply_function)> factory_function;
		SendReplyServer(int port, factory_function factory) :
				m_factory(factory),
				acceptor_(io_service_, tcp::endpoint(tcp::v4(), port))
		{
			start_accept();
		}
		void run()
		{
			io_service_.run();
		}
		void handle_accept(SendReplyConnection::pointer new_connection,
				const boost::system::error_code& error)
		{
			if (!error) {
				std::cout << "handle_accept" << std::endl;
				Connection::pointer c = m_factory(
						boost::bind(&SendReplyConnection::write, new_connection.get(), _1)
						);
				new_connection->setConnection(c);
				new_connection->start();
			}
			start_accept();
		}
		void start_accept()
		{
			std::cout << "start_accept" << std::endl;
			SendReplyConnection::pointer new_connection = 
				SendReplyConnection::create(io_service_);
			acceptor_.async_accept(new_connection->socket(),
					boost::bind(&SendReplyServer::handle_accept, this, new_connection, boost::asio::placeholders::error));
		}
	private:
		factory_function m_factory;
		boost::asio::io_service io_service_;
		boost::asio::ip::tcp::acceptor acceptor_;
};

int main(int argc, const char *argv[])
{
	SendReplyServer server(2015, boost::bind(&StringConnection::create, "Hello\n", _1));

	server.run();
	
	return 0;
}
