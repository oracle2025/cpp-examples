#include "todolistclient.h"
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

TodoListClient::TodoListClient(const std::string &server) :
	m_server(server)
{
}
TodoListClient::pointer TodoListClient::create(const std::string &server)
{
    return pointer(new TodoListClient(server));
}

void TodoListClient::send(const std::string &output)
{
	try
  	{

    	boost::asio::io_service io_service;

    	tcp::resolver resolver(io_service);
    	tcp::resolver::query query(m_server, "2015");
    	tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    	tcp::socket socket(io_service);
    	boost::asio::connect(socket, endpoint_iterator);

      	boost::array<char, 128> buf;
      	boost::system::error_code error;

		size_t len = socket.write_some(boost::asio::buffer(output, output.length()));
        //size_t len = socket.read_some(boost::asio::buffer(buf), error);

      	if (error == boost::asio::error::eof) {
        	; // Connection closed cleanly by peer.
      	} else if (error)
        	throw boost::system::system_error(error); // Some other error.

        //std::cout.write(buf.data(), len);
  	}
  	catch (std::exception& e)
  	{
    	std::cerr << e.what() << std::endl;
  	}
}

