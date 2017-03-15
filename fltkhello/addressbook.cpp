#include "addressbook.h"
#include "addressbookwidget.h"

void * get_widget(int x, int y, int w, int h)
{
	AddressBookWidget *widget = new AddressBookWidget(x, y, w, h);
	//widget->name_input->static_value("Hallo Welt");
	return widget;
}


