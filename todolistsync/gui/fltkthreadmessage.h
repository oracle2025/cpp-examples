#ifndef _FLTK_THREAD_MESSAGE_
#define _FLTK_THREAD_MESSAGE_

#include <functional>

/**
 * @brief Sends a Message to the FLTK Main Thread
 * Usage: FltkThreadMessage::create([listview](){ listview->add("bla"); });
 */
class FltkThreadMessage
{
	public:
		typedef std::function<void()> thread_function;
		static void create(thread_function func);
		void doit();
	private:
		FltkThreadMessage(thread_function func);
		thread_function m_function;
		FltkThreadMessage(FltkThreadMessage const&) = delete;
		FltkThreadMessage& operator=(FltkThreadMessage const&) = delete;
};


#endif /* _FLTK_THREAD_MESSAGE_ */
