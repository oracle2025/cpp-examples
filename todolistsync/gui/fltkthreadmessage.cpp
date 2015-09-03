#include "fltkthreadmessage.h"
#include <FL/Fl.H>

static void fltk_thread_handler(void *msg)
{
	FltkThreadMessage *message_object = (FltkThreadMessage*)msg;
	message_object->doit();
	delete message_object;
}

FltkThreadMessage::FltkThreadMessage(thread_function func) :
	m_function(func)
{
	FltkThreadMessage *msg = new FltkThreadMessage(func);
	Fl::awake(fltk_thread_handler, (void*)msg);
}

void FltkThreadMessage::create(thread_function func)
{
}

void FltkThreadMessage::doit()
{
	m_function();
}

