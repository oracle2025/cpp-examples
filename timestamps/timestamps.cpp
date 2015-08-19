#include <chrono>
#include <iostream>
#include <boost/date_time.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

typedef std::chrono::system_clock::time_point timestamp;

int main(int argc, const char *argv[])
{
	timestamp ts = std::chrono::system_clock::now();

	std::time_t t = std::chrono::system_clock::to_time_t(ts);
	std::cout << "Timestamp: ctime(time_t): " << std::ctime(&t);

	std::cout << "Time since epoch: " << ts.time_since_epoch().count() << std::endl;

	std::string serialized = "Wed Aug 19 15:52:13 2015";
	


	boost::gregorian::date d;
	d = boost::gregorian::from_simple_string("2013-01-01");
	std::cout << "boost::gregorian: " << boost::gregorian::to_simple_string(d) << std::endl;

	boost::posix_time::ptime ptimedate = boost::posix_time::time_from_string("2002-01-20 23:59:59.000");

	//std::string ts("20020131T235959");
	//ptime t(from_iso_string(ts))
	//http://www.boost.org/doc/libs/1_59_0/doc/html/date_time/posix_time.html
	
	std::cout << "posix_time: " << boost::posix_time::to_simple_string(ptimedate) << std::endl;
	std::cout << "posix_time: " << boost::posix_time::to_simple_string(boost::posix_time::microsec_clock::universal_time()) << std::endl;
	std::cout << "posix_time: " << boost::posix_time::to_iso_string(boost::posix_time::microsec_clock::universal_time()) << std::endl;
	std::cout << "posix_time: " << boost::posix_time::to_iso_extended_string(boost::posix_time::microsec_clock::universal_time()) << std::endl;

	boost::uuids::uuid id = boost::uuids::random_generator()();

	std::string idstr = boost::lexical_cast<std::string>(id);

	std::cout << "idstr: " << idstr << std::endl;

	boost::uuids::uuid id2 = boost::uuids::string_generator()(idstr);

	std::cout << "parsed: " << boost::lexical_cast<std::string>(id2) << std::endl;

	std::cout << (id == id2) << std::endl;
	

	
	return 0;
}
