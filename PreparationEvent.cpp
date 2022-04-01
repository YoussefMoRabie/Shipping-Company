#include "PreparationEvent.h"
#include "Cargo.h"
PreparationEvent::PreparationEvent(CARGO_TYPE ty, const Time& t, int id, float d, float l, float c) :Event(t, id)
{
	type = ty;
	dist = (d > 0) ? d : 10;
	loadTime = (l > 0) ? l : 10;
	cost = (c > 0) ? c : 10;

}
void PreparationEvent::Execute()
{
	Cargo c(ET, loadTime, type, dist, cost);
	//add to the list after company is made
}