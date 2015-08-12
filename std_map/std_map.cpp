/* Programming Examples using std::map */

#include <iostream>
#include <map>
#include <string>
#include <ostream>
#include <boost/container/flat_map.hpp>

typedef std::string string;

enum class error_codes {
	hardware,
	software,
	communication
};

void std_map_example_1()
{
	std::map<int, string> mymap = {
		{1, "hardware"},
		{2, "software"},
		{3, "communication"}};

}

/*class ErrorCode : private std::map<error_codes, string> {*/
class ErrorCode : private boost::container::flat_map<error_codes, string> {
	public:
		ErrorCode(error_codes code);
		string str() const;
		/*friend std::ostream & operator<<(std::ostream &os, const ErrorCode& p);*/
	private:
		error_codes m_error;
};

ErrorCode::ErrorCode(error_codes code) :
	m_error(code)
{
	(*this)[error_codes::hardware] = "hardware";
	(*this)[error_codes::software] = "software";
	(*this)[error_codes::communication] = "communication";
}

string ErrorCode::str() const
{
	return at(m_error);
}
std::ostream & operator<<(std::ostream &os, const ErrorCode& p)
{
	return os << p.str();
}

void std_map_example_2()
{
	ErrorCode myerror(error_codes::hardware);
	std::cout << "Error: " << myerror.str() << std::endl;
	std::cout << "Error: " << myerror << std::endl;
}

class KeyType
{
	public:
		KeyType(int i) : m_key(i) {
		}
	private:
		int m_key;
		/*friend bool operator> (const KeyType &cK1, const KeyType &cK2);
		friend bool operator<= (const KeyType &cK1, const KeyType &cK2);*/
		friend bool operator< (const KeyType &cK1, const KeyType &cK2);
		/*friend bool operator>= (const KeyType &cK1, const KeyType &cK2);*/
};
/*bool operator> (const KeyType &cK1, const KeyType &cK2)
{
	return cK1.m_key > cK2.m_key;
}
bool operator<= (const KeyType &cK1, const KeyType &cK2)
{
	return cK1.m_key <= cK2.m_key;
}*/
bool operator< (const KeyType &cK1, const KeyType &cK2)
{
	return cK1.m_key < cK2.m_key;
}
/*bool operator>= (const KeyType &cK1, const KeyType &cK2)
{
	return cK1.m_key >= cK2.m_key;
}*/

void std_map_example_3()
{
	KeyType mykey(3);
	KeyType mykey2(2);

	std::map<KeyType, string> mymap;

	mymap[mykey] ="hello World";
	mymap[mykey2] ="bla";
	if (mykey2 < mykey) {
		std::cout << "mykey2 < mykey" << std::endl;
	}
	std::cout << "mymap[mykey]: " << mymap.at(mykey) << std::endl;
	std::cout << "mymap[mykey2]: " << mymap.at(mykey2) << std::endl;
}


class Config : private boost::container::flat_map<string, string> {
	public:
		Config();
		string get(const string &key, const string &defaultvalue = "") const;
		void set(const string &key, const string &value);
		friend std::ostream & operator<<(std::ostream &os, const Config& p);
};
Config::Config()
{
}
string Config::get(const string &key, const string &defaultvalue) const
{
	if (count(key)) {
		return at(key);
	}
	return defaultvalue;
}
void Config::set(const string &key, const string &value)
{
	(*this)[key] = value;
}
std::ostream & operator<<(std::ostream &os, const Config& p)
{
	for (auto it = p.begin(); it != p.end(); it++) {
		auto i = *it;
		os << "\"" << i.first << "\" : \"" << i.second << "\"";
		if (it + 1 != p.end()) {
			os << "," << std::endl;
		}
	}
	return os;
}

void std_map_example_4()
{
	Config config;
	config.set("Filename", "hello.cpp");
	config.set("Username", "peter");
	std::cout << config << std::endl;
}

/* std::map:
 *   empty
 *   size
 *   max_size
 *   clear
 *   insert
 *   insert_or_assign
 *   emplace
 *   emplace_hint
 *   try_emplace
 *   erase
 *   swap
 *   count
 *   find
 *   equal_range
 *	 lower_bound
 *	 upper_bound
 *
 */
void std_map_example_5()
{
	std::multimap<int, string> mymap = {
		{1, "eins"},
		{2, "zwei"},
		{2, "zwei einhalb"},
		{3, "drei"}};


	auto range = mymap.equal_range(2);
	for (auto i = range.first; i != range.second; i++) {
		std::cout << (*i).first << " " << (*i).second << std::endl;
	}
	for (auto i = mymap.begin(); i != mymap.end(); i++) {
		std::cout << "map: " << (*i).first << " " << (*i).second << std::endl;
	}


}

int main(int argc, const char *argv[])
{
	std::cout << "Programming Examples using std::map" << std::endl;
	/*std_map_example_1();*/
	/*std_map_example_2();*/
	/*std_map_example_3();*/
	/*std_map_example_4();*/
	std_map_example_5();
	return 0;
}
