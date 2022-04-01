#include "CancelEvent.h"

CancelEvent::CancelEvent(const Time& t, int id) :Event(t, id)
{
}
void CancelEvent::Execute()
{
	//remove from the list in company
}