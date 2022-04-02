#include "PromoteEvent.h"

PromoteEvent::PromoteEvent(Company* p, const Time& t, int id, float x) :Event(p, t, id)
{
	ExtraMoney = (x > 0) ? x : 100;
}
void PromoteEvent::Execute()
{
	Cargo* ptr;
	/*if (cPtr->Find_Normal_Cargo(ID, ptr))
	{
		ptr->PromoteToVip(ExtraMoney);
		//REMOVE FROM THE NORMAL LIST
		//ADD TO VIP LIST
	}
	*/
}
