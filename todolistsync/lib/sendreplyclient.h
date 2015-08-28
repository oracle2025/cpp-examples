#ifndef _SEND_REPLY_CLIENT_H_
#define _SEND_REPLY_CLIENT_H_

#include <memory>
#include <string>
#include <queue>
#include <functional>
#include <boost/asio.hpp>

class SendReplyClient
{
	public:
		typedef std::shared_ptr<SendReplyClient> pointer;
		typedef std::function<void(const std::string&)> reply_function;

		~SendReplyClient();

		static pointer create(const std::string &server, int port, reply_function reply_);

		void send(const std::string &value);
		void run();
	private:
		SendReplyClient(const std::string &server, int port, reply_function reply_);
		reply_function reply;
		boost::asio::io_service m_io_service;
		boost::asio::ip::tcp::socket m_socket;
		bool m_connected;

		std::queue<std::string> m_fifo;
		enum { max_length = 1024 };
		char m_data[max_length];

		void do_read();
		void do_write();

		SendReplyClient(SendReplyClient const&) = delete;
		SendReplyClient& operator=(SendReplyClient const&) = delete;
};

#endif /* _SEND_REPLY_CLIENT_H_ */
