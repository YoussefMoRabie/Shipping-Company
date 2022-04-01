#include "PrompteEvent.h"

PrompteEvent::PrompteEvent(const Time& t, int id, float x) :Event(t, id)
{
	ExtraMoney = (x > 0) ? x : 100;
}
void PrompteEvent::Execute()
{
	//needs compant lists
}
