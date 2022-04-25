#include "PromoteEvent.h"

PromoteEvent::PromoteEvent(Company* p, const Time& t, int id, float x) :Event(p, t, id)
{
	ExtraMoney = (x > 0) ? x : 100;
}
void PromoteEvent::Execute()
{
	cPtr->Upgrade_Normal_Cargo(ID, ExtraMoney);
}
