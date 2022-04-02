#include "PreparationEvent.h"
#include "Cargo.h"
#include "Def.h"
PreparationEvent::PreparationEvent(Company* p, CARGO_TYPE ty, const Time& t, int id, float d, float l, float c) :Event(p, t, id)
{
	type = ty;
	dist = (d > 0) ? d : 10;
	loadTime = (l > 0) ? l : 10;
	cost = (c > 0) ? c : 10;

}
void PreparationEvent::Execute()
{
	Cargo *c=new Cargo(type, ET, ID, dist, loadTime, cost);
	cPtr->AddCargo(c);
}