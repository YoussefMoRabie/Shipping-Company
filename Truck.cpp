#include"Truck.h"
#include<iostream>
using namespace std;

Truck::Truck(int id, TRUCK_TYPE T, int TC, float MT, int j, float S)
{
	ID = id;
	Type = T;
	Truck_Capacity = TC;
	Maintenance_Time = MT;
	J = j;
	Speed = S;
	Journeys_Till_Check = j;
}
TRUCK_TYPE Truck:: GetType() const
{
	return Type;
}
int Truck::GetCapacity() const
{
	return Truck_Capacity;
}
void Truck::set_DInterval() {
	float temp = 2* Delivery_Distance/ GetSpeed() + GetCapacity() * container.GetFront()->get_item()->GetLU_Time();

	Delivery_Interval = temp;
}
int Truck:: GetJTC() {
	return Journeys_Till_Check;
}
int Truck::GetContainer_count() {
	return container.GetCount();
}
void Truck::restore_JTC() {
	Journeys_Till_Check = J;
}
void Truck::DecrementJTC() {
	Journeys_Till_Check--;
}
float Truck::GetMaintenanceTime() const
{
	
	return Maintenance_Time;
}
void Truck::set_finish_point(const Time& t) {
	finish_point = t;
}
Time Truck::get_finish_point() {
	return finish_point;
}
float Truck:: GetSpeed() const
{
	return Speed;
}
float Truck::GetDeliveryInterval()
{
	return Delivery_Interval;
}
int Truck:: GetID() const
{
	return ID;
}
void Truck::load(Cargo* x, float delivery_time)
{
	if (container.QueueEmpty())
		Delivery_Distance=x->GetDistance();
	container.EnQueue(x, 100/delivery_time);
	if (x->GetLU_Time() > move_counter)
		move_counter = x->GetLU_Time();
}
Cargo* Truck::unload() {
	if (GetContainer_count() > 0) {
		Cargo* c_temp;
		container.DeQueue(c_temp);
		return c_temp;
	}
	return nullptr;
}
void Truck::count_down()
{
	move_counter--;
}
int Truck::get_move_counter()
{
	return move_counter;
}
float Truck::Get_nearest_dis() {
	if (GetContainer_count() > 0)
		return container.GetFront()->get_item()->GetDistance();
	else
		return Delivery_Distance;
}
Time Truck::Get_nearest_stop() {
	return Nearest_stop;
}
void Truck::set_nearest_stop(Time t) {
	int l_t = container.GetFront()->get_item()->GetLU_Time();
	Nearest_stop = t + l_t;
}
void Truck::print()
{
	if (container.QueueEmpty())
		return;

	ui_p->print(to_string(ID));
	if (container.Peek()->GetType() == CARGO_TYPE::VIP)
	{
		ui_p->print("{");
		container.print();
		ui_p->print("} ");
	}
	else if (container.Peek()->GetType() == CARGO_TYPE::SPECIAL)
	{
		ui_p->print("(");
		container.print();
		ui_p->print(") ");
	}
	else if (container.Peek()->GetType() == CARGO_TYPE::NORMAL)
	{
		ui_p->print("[");
		container.print();
		ui_p->print("] ");
	}
}
ostream& operator<<(ostream& out, const Truck* t)
{
	out << t->GetID();
	return out;
}