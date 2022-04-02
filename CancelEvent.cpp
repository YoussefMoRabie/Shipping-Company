#include "CancelEvent.h"

CancelEvent::CancelEvent(Company* p, const Time& t, int id) :Event(p, t, id)
{
}
void CancelEvent::Execute()
{
	//REMOVE FROM NORMAL LIST
}